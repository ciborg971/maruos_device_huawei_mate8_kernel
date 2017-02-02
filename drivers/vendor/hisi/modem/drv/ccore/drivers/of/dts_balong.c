
#include <sre_mmu.h>
#include <osl_types.h>
#include <osl_math64.h>
#include <osl_malloc.h>
#include <bsp_shared_ddr.h>
#include <of.h>
#include "dts.h"

/*lint --e{712, 713, 737, 747, 578, 551}*/
static unsigned char g_dt_alloc_data[DT_BOOTM_SIZE + DT_BOOTM_ALIGN] ={0}; /* ����16byte���� */
static unsigned int __alloc_start = (unsigned int)(&g_dt_alloc_data[0]);
static unsigned int __alloc_end   = (unsigned int)(&g_dt_alloc_data[DT_BOOTM_SIZE + DT_BOOTM_ALIGN - 1]);

struct dts_ctrl g_dts_ctrl = {0};

static inline char _tolower(const char c)
{
	return c | 0x20;
}

int _str2int(const char *str, int base, unsigned long long *res)
{
	const char *p = str;
	int val = 0;
	unsigned int cnt = 0;
	unsigned long long result = 0;
	int overflow = 0;
	
	if (base == 0) 
	{
		if (p[0] == '0') 
		{
			if (_tolower(p[1]) == 'x' && isxdigit(p[2]))
				base = 16;
			else
				base = 8;
		} else
		{
			base = 10;
		}
	}
	if (base == 16 && p[0] == '0' && _tolower(p[1]) == 'x')
	{
		p += 2;
	}
	
	while(*p)
	{
		if (isxdigit(*p))
			val = *p - '0';
		else if ('a' <= _tolower(*p) && _tolower(*p) <= 'f')
			val = _tolower(*p) - 'a' + 10;
		else
			break;
		if (val >= base)
			break;
		if (result & (~0ull << 60))  /*lint !e648 */
		{
			if (result > div_u64(ULLONG_MAX - val, base)) /*lint !e732 */
				overflow = 1;
		}
		result = result * base + val;
		cnt++;
		p++;
	}
	if (overflow)
		cnt |= KSTRTOX_OVERFLOW;
	if (cnt & KSTRTOX_OVERFLOW)
		return -ERANGE;
	cnt &= ~KSTRTOX_OVERFLOW;
	if (cnt == 0)
		return -EINVAL;
	if (*p == '\n')
		p++;
	if (*p)
		return -EINVAL;

	*res = result;
	
	return 0;
}


int __must_check strtoint(const char *s, unsigned int base, int *res)
{
	unsigned long long tmp;
	int rv;
	
	if (s[0] == '-') 
	{
		rv = _str2int(s + 1, base, &tmp);
		if (rv)
			return rv;
		if ((long long )(-tmp) >= 0) /*lint !e501 */
			return -ERANGE;
		*res = -tmp; /*lint !e501 */
		return 0;
	} else 
	{
		if (s[0] == '+')
			s++;
		return _str2int(s, base, (unsigned long long *)res);
	}
}

void *dts_early_mem_alloc(unsigned int sz)
{
	void *ptr;

	if(__alloc_start == 0)
	{
		of_pr_err("__alloc_start=0\n");
		return NULL;
	}
	ptr = (void*) __alloc_start;
	__alloc_start = (__alloc_start + sz + DT_BOOTM_ALIGN) & (~DT_BOOTM_ALIGN);
	if(__alloc_start > __alloc_end)
	{
		of_pr_err("error: no memory\n");
		return NULL;
	}

	return ptr;
}


/* ����: Ϊ��Ҫ��չ���豸����չ�ڴ�(��Ҫ����ʵ��) */
void * dts_init_dt_alloc_memory_arch(u64 size, u64 align)
{
	u32 *mem = NULL;
	u32 addr = 0;

	g_dts_ctrl.dev_tree_size += (size + align);

	mem = (u32 *)dts_early_mem_alloc(size + align);
    if(NULL == mem) /*lint !e830 */
    {
		of_pr_err("no memroy for malloc\n");
		return mem;
	}
	addr = OSL_ROUND_UP((int)mem, align); /*lint !e539 */
	if(addr & (align - 1))
	{
		of_pr_err("memory alloced is not aligned\n");
		return NULL;
	}
	return (void *)addr;
}

/*****************************************************************************
 �� �� ��  : irq_of_parse_and_map
 ��������  : ��dtb�ļ�������Ӧ�ڵ��"interrupts"����ֵ, ע�����ʽΪ:interrupts = <0 32 4>
 �������  : struct device_node *dev ����ΪNULL; int index��Ӧ"interrupts"����cells����
 �������  : ��
 �� �� ֵ  : �жϺ�
 ע������  : �ú�����C��ֻ��parse, û��map����, Ϊ�˱��ֺ�linux�ӿ�һ��
 �޸���ʷ  :
   ��  ��  : 2014��8��8��
   �޸�����: �����ɺ���
*****************************************************************************/
unsigned int irq_of_parse_and_map(struct device_node *dev, int index)
{
	u32 intsize = 3; /* interrupt-cells ֵȡ�� */
	const __be32 *intspec = NULL;
	u32 intlen = 0;
	u32 irq[3] = {0};
	u32 i = 0;

	of_pr_debug("%s, %s, %d\n", dev->full_name, dev->name, dev->type);

	/* Get the interrupts property */
	intspec = of_get_property(dev, "interrupts", (int *)&intlen);
	if (intspec == NULL)
	{
		of_pr_err("interrpts node value is null\n");
		return 0;
	}
	intlen /= sizeof(*intspec);

	of_pr_debug(" intspec=%d intlen=%d, intsize=%d\n", be32_to_cpup(intspec), intlen, intsize);

	/* Check index */
	if ((index + 1) * intsize > intlen)
	{
		of_pr_err("index error\n");
		return 0;
	}

	intspec = intspec + index * intsize;

	/* Get new specifier and map it */
	for (i = 0; i < intsize; i++)
	{
		irq[i] = of_read_number(intspec +i, 1);
	}
	of_pr_debug("irq[3]={%d, %d, %d}\n", irq[0], irq[1], irq[2]);

	return irq[1];
}

int of_reg_info_get(struct device_node *np, int index, u64 *start, u64 *size)
{
	const __be32 *spec = NULL;
	const __be32 *prop = NULL;
	int cells_size = 0, len = 0;
	int na = 0, ns = 0;
	of_pr_debug("%s, %s, %d\n", np->full_name, np->name, np->type);

	spec = of_get_property(np, "reg", (int *)&len);
	len /= 4;

	if (NULL == spec)
	{
		of_pr_err("cannot find reg property\n");
		return -1;
	}
	of_pr_debug("spec=0x%x, len=%d\n", spec, len);

	prop = of_get_property(np, "#address-cells", NULL);
	if(NULL != prop)
	{
		na = be32_to_cpup(prop);
	}
	of_pr_debug("#address-cells=%d", na);

	prop = of_get_property(np, "#size-cells", NULL);
	if(NULL != prop)
	{
		ns = be32_to_cpup(prop);
	}
	of_pr_debug("#size-cells=%d", ns);

	cells_size = na + ns;
	if(cells_size == 0)
	{
		na = 1;
		ns = 1;
		cells_size = 2;
	}
	if((index * cells_size) >= len)
	{
		of_pr_err("index = %d is out of range\n", index);
		return -2;
	}

	*start = of_read_number(spec + index *cells_size , 1);
	*size  = of_read_number(spec + index *cells_size + na, ns);
	of_pr_debug("reg = <0x%x 0x%x>\n", (u32)start, (u32)size);

	return 0;
}

/*****************************************************************************
 �� �� ��  : of_iomap
 ��������  : ��dtb�ļ�������Ӧ�ڵ��"reg"����ֵ, ע�����ʽΪ:reg = <��ʼ��ַ ��С>
 �������  : struct device_node *np ����ΪNULL; int index��Ӧ"reg"����cells����
 �������  : ��
 �� �� ֵ  : ӳ���������ַ, ע����ccore,�����ַ�������ַһ��
 ע������  : �ýӿ�ӳ����ڴ�����Ϊ: device,strongly-ordered���������Կ���vmStateSet�����޸�
 �޸���ʷ  :
   ��  ��  : 2014��8��8��
   �޸�����: �����ɺ���
*****************************************************************************/
void *of_iomap(struct device_node *np, int index)
{
	u32 addr = 0;
	u64 start = 0, size = 0;

	if(of_reg_info_get(np, index, &start, &size))
	{
		return NULL;
	}

	addr = (u32)start;
	return ioremap((MMU_VA_T)addr, (u32)size);
}

void bsp_dts_init(void)
{
	INIT_LIST_HEAD(&g_dts_ctrl.aliases_list);
	
	spin_lock_init(&g_dts_ctrl.dn_lock); /*lint !e123 */
	g_dts_ctrl.dev_tree_size = 0;

	g_dts_ctrl.dtb_file_header = (struct boot_param_header *)DDR_MCORE_DTS_ADDR;
	if (be32_to_cpu(g_dts_ctrl.dtb_file_header->magic) != OF_DT_HEADER)
	{
		of_pr_err("invalid dtb image, dts init error\n");
		return ;
	}

	(void)dts_scan_flat_dt(dts_init_dt_scan_root, NULL);	

	dts_tree_unflat();
	g_dts_ctrl.state = 1;
}
