

/*lint --e{530,525,628,666,801,830} */

#include "clk_balong_core.h"
#include <osl_generic.h>
#include <osl_malloc.h>
#include <bsp_sysctrl.h>
#include <bsp_icc.h>
#include <bsp_abb.h>

//#define CCLK_DEBUG

//#define  CCLK_P532  /* P532����enable/disable/status���֣�V7R5����enable/disable/ctrl status/status���� */
#define HI_CLK_GATE_DISABLE_OFFSET		    0x4  /* disable�Ĵ��������enable�Ĵ�����ƫ�ƶ���0x4 */

unsigned int g_status_reg_offset_to_enable = 0; /* status�Ĵ��������enable�Ĵ�����ƫ�� */


#define WIDTH_TO_MASK(width)	(((unsigned int)1 << (width)) - 1)  /* �õ�width��1 */


/* һ���������ֵ����������m����r */
#define MULT_ROUND_UP(r, m) ((r) * (m) + ((m) - 1))

#ifndef DIV_ROUND_UP  /* n/d ����ȡ�� */
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#endif

#ifndef ULONG_MAX
#define ULONG_MAX	(~0UL)
#endif

#define CLK_DIS_REG_NUM  5  /* �رռĴ������������5�� */
#define CLK_AUTO_GATING_REG_NUM     5  /* ���5���Զ��ſؼĴ��� */

typedef enum tag_E_HS_CRG_AREA{
	HS_CRG_AO,
	HS_CRG_PD,
	HS_CRG_MDM
}E_HS_CRG_AREA;

struct hi_periclk {
	struct clk_hw	hw;
	void 	*enable;	/* enable register */
	void 	*reset;		/* reset register */
	u32		ebits;		/* bits in enable/disable register */
	u32		rbits;		/* bits in reset/unreset register */
	const char 	*friend;
	spinlock_t	*lock;
};

struct hi_muxclk {
	struct clk_hw	hw;
	u32 reg;		/* mux register */
	u8		shift;
	u8		width;
	u32		mbits;		/* mask bits in mux register */
	spinlock_t	*lock;
};

struct hi_divclk {
	struct clk_hw	hw;
	u32     reg;		        /* ��Ƶ�Ĵ�����ַ */
	u8		shift;              /* ��Ƶbit��ʼ��bit���������bit10-8��ʾ��Ƶbit����ô��ֵΪ8 */
	u8		width;              /* ��Ƶbit�������bit10-8��ʾ��Ƶbit����ô��ֵΪ3 */
	u8      is_n_plus_1_div;    /* �Ƿ���N+1��Ƶ�� */
	u32		mbits;		        /* mask bits in divider register */
	u32     en_ref_before_set_div; /* ���÷�ƵǰҪ�ȴ򿪲ο�ʱ�� */
	const struct clk_div_table	*table;
	spinlock_t	*lock;
};

struct hi_gateclk {
	struct clk_hw   hw;
	u32             reg;             /* �ſ�ʹ�ܼĴ�����ַ */
	u8		        bit_idx;          /* �ſ�ʹ��λ */
	u8		        flags;
	u8              is_virtual;       /* �Ƿ�������ʱ�� */
	u8              auto_gate_bit;    /* �Զ��ſؿ���λ */
	u32             auto_gate_base;  /* �Զ��ſؼĴ�����ַ */
	u32             auto_gate_offset; /* �Զ��ſؼĴ���ƫ�� */
	spinlock_t	    *lock;
};

struct drv_clk_mux {
	struct clk_hw	hw;
	u32             reg;
	u32		        *table;
	u32		        mask;
	u8		        shift;
	u8		        flags;
	spinlock_t	    *lock;
};

struct drv_clk_fixed_rate {
	struct clk_hw   hw;
	unsigned long	fixed_rate;
	u8		        flags;
	u8              reserved[3];
};

struct drv_clk_fixed_factor {
	struct clk_hw	hw;
	unsigned int	mult;
	unsigned int	div;
};



struct hs_crg_base {
	u32 ptr_ao_crg_base;
	u32 ptr_pd_crg_base;
	u32 ptr_mdm_crg_base;
	spinlock_t	    lock;
};

enum ENUM_PLL_CTRL_BY_CCORE{
	CTRL_BY_CCORE_WPLL    = 0,
	CTRL_BY_CCORE_GPLL    = 1,
	PLL_CTRL_BY_CCORE_BUTT
};

/* remote pll��A�˷���C�˵���Ϣ��C�˻ظ���A�˵���Ϣʹ��ͬһ���ṹ�� */
struct  remote_pll_ctrl_msg{
	unsigned int  pll_id;     /* CTRL_BY_CCORE_WPLL, CTRL_BY_CCORE_GPLL */
	unsigned int  op_type;    /* en:1,dis:0 */
	int           op_result;  /* C�˲��������0�������ɹ���-1������ʧ�� */
};


static struct hs_crg_base g_stru_hs_crg_base;


static void   *drv_clk_get_base(struct device_node *ptr_device_node);
static  unsigned int drv_clk_ffs(unsigned int x);
static  unsigned int drv_clk_fls(unsigned int x);


/*lint -save -e438 */
/*****************************************************************************
* �� �� ��	:  drv_clk_ffs
*
* ��������	:  �ҵ�һ�����е�һ��Ϊ1��bit�ı��
               ��0x0������0����0x3������1����0xC0000000������31
*
* �������	:  x:u32��ֵ
* �������	:  ��
*
* �� �� ֵ	:  һ�����е�һ��Ϊ1��bit�ı��
*
*****************************************************************************/
static  unsigned int drv_clk_ffs(unsigned int x)
{
	unsigned int r = 1;

	if (!x)
		return 0;
	if (!(x & 0xffff)) {
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}
	if (!(x & 1)) {

		r += 1;
	}
	return r;
}


/*****************************************************************************
* �� �� ��	:  drv_clk_fls
*
* ��������	:  �ҵ�һ���������һ��Ϊ1��bit�ı��
               ��0x0������0����0x3������2����0xC0000000������32
*
* �������	:  x:u32��ֵ
* �������	:  ��
*
* �� �� ֵ	:  һ���������һ��Ϊ1��bit�ı��
*
*****************************************************************************/
static  unsigned int drv_clk_fls(unsigned int x)
{
	unsigned int r = 32;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {

		r -= 1;
	}
	return r;
}
/*lint -restore +e438 */


#define to_clk_fixed_factor(_hw) container_of(_hw, struct drv_clk_fixed_factor, hw)

/*lint -save -e160 -e713 -e830 -e438 */
#define do_div(n,base) ({ \
int __res; \
__res = ((unsigned long) n) % (unsigned) base; \
n = ((unsigned long) n) / (unsigned) base; \
__res; })
/*lint -restore +e160 +e713 +e830 +e438 */

static unsigned long drv_clk_fixed_factor_recalc_rate(struct clk_hw *ptr_hw, unsigned long parent_rate)
{
	struct drv_clk_fixed_factor *ptr_clk_fixed_factor = to_clk_fixed_factor(ptr_hw);
	unsigned long long int rate;

	rate = (unsigned long long int)parent_rate * ptr_clk_fixed_factor->mult;
	/*lint -save -e160 -e713 -e830 -e438 -e522 */
	do_div(rate, ptr_clk_fixed_factor->div);
	/*lint -restore +e160 +e713 +e830 +e438 +e522 */
	return (unsigned long)rate;
}


static int drv_clk_fixed_factor_set_rate(struct clk_hw *ptr_hw, unsigned long rate, unsigned long parent_rate)
{
	return 0;
}

static long drv_clk_fixed_factor_round_rate(struct clk_hw *ptr_hw, unsigned long rate, unsigned long *prate)
{
	struct drv_clk_fixed_factor *ptr_clk_fixed_factor = to_clk_fixed_factor(ptr_hw);

	if (__drv_clk_get_flags(ptr_hw->clk) & CLK_SET_RATE_PARENT) 
	{
		unsigned long best_parent;

		best_parent = (rate / ptr_clk_fixed_factor->mult) * ptr_clk_fixed_factor->div;
		*prate = __drv_clk_round_rate(__drv_clk_get_parent(ptr_hw->clk), best_parent);
	}

	return (*prate / ptr_clk_fixed_factor->div) * ptr_clk_fixed_factor->mult; /*lint !e713*/
}

struct clk_ops clk_fixed_factor_ops = {
	.round_rate = drv_clk_fixed_factor_round_rate,
	.set_rate = drv_clk_fixed_factor_set_rate,
	.recalc_rate = drv_clk_fixed_factor_recalc_rate,
};


struct clk *drv_clk_register_fixed_factor(const char * dev, const char *name,
		const char *parent_name, unsigned long flags,
		unsigned int mult, unsigned int div_val)
{
	struct drv_clk_fixed_factor *ptr_clk_fixed_factor = NULL;
	struct clk_init_data init;
	struct clk *ptr_clk = NULL;

	ptr_clk_fixed_factor = osl_malloc(sizeof(*ptr_clk_fixed_factor));
	if (!ptr_clk_fixed_factor) 
	{
		clk_printf("could not allocate fixed factor clk\n");
		return ERR_PTR(-ENOMEM);
	}
	(void)memset_s(ptr_clk_fixed_factor, sizeof(struct drv_clk_fixed_factor), 0, sizeof(struct drv_clk_fixed_factor));

	ptr_clk_fixed_factor->mult = mult;
	ptr_clk_fixed_factor->div = div_val;
	ptr_clk_fixed_factor->hw.init = &init;

	init.name = name;
	init.ops = &clk_fixed_factor_ops;
	init.flags = flags | CLK_IS_BASIC;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	ptr_clk = drv_clk_register(dev, &ptr_clk_fixed_factor->hw);

	if (IS_ERR(ptr_clk))
	{
		osl_free(ptr_clk_fixed_factor);
	}

	return ptr_clk;
}


void  drv_clk_fixed_factor_setup(struct device_node *ptr_device_node)
{
	struct clk *ptr_clk = NULL;
	const char *clk_name = ptr_device_node->name;
	const char *parent_name = NULL;
	u32 div_val = 1, mult = 1;
	struct clk_lookup    *ptr_clk_lookup = NULL;

	if (of_property_read_u32(ptr_device_node, "clock-div", &div_val)) 
	{
		clk_printf("node %s fixed factor clk must have a clock-div property\n",
			 ptr_device_node->name);
		return;
	}

	if (of_property_read_u32(ptr_device_node, "clock-mult", &mult)) {
		clk_printf("node %s fixed factor clk must have a clock-mult property\n",
			 ptr_device_node->name);
		return;
	}

	if (of_property_read_string(ptr_device_node, "clock-output-names", &clk_name)) 
	{
		clk_printf("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, ptr_device_node->name);
		return;
	}
	parent_name = drv_of_clk_get_parent_name(ptr_device_node, 0);

	ptr_clk = drv_clk_register_fixed_factor(NULL, clk_name, parent_name, 0,	 mult, div_val);
	if (IS_ERR(ptr_clk))
	{
		clk_printf("fail to reigister fixed factor clk %s!\n", clk_name);
		return ;
	}

    ptr_clk_lookup = osl_malloc(sizeof(struct clk_lookup));
	if (!ptr_clk_lookup) 
	{
		clk_printf("could not allocate clk lookup for %s\n", clk_name);
		return ;
	}
	/* ����ɹ� */
	(void)memset_s(ptr_clk_lookup, sizeof(struct clk_lookup), 0, sizeof(struct clk_lookup));
	
	ptr_clk_lookup->dev_id = NULL;
	ptr_clk_lookup->con_id = clk_alloc_copy(ptr_clk->name);
	ptr_clk_lookup->clk = ptr_clk;
	
	drv_clkdev_add(ptr_clk_lookup);
	clk_printf_info("drv_clkdev_add %s ok\n", clk_name);

	return ; 
}

#define to_clk_fixed_rate(_hw) container_of(_hw, struct drv_clk_fixed_rate, hw)

static unsigned long drv_clk_fixed_rate_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	return to_clk_fixed_rate(hw)->fixed_rate;
}

static struct clk_ops g_fixed_rate_ops = {
	.recalc_rate = drv_clk_fixed_rate_recalc_rate,
};


/* ע��fixed_rate�͵�ʱ�� */
struct clk *drv_clk_register_fixed_rate(const char * dev, const char *name,
		const char *parent_name, unsigned long flags,
		unsigned long fixed_rate)
{
	struct drv_clk_fixed_rate *ptr_clk_fixed_rate;
	struct clk *ptr_clk;
	struct clk_init_data init;

	/* �����ڴ� */
	ptr_clk_fixed_rate = osl_malloc(sizeof(struct drv_clk_fixed_rate));
	if (!ptr_clk_fixed_rate) 
	{
		clk_printf("%s: could not allocate fixed clk\n", __func__);
		return ERR_PTR(-ENOMEM);
	}
	/* ����ɹ� */
	(void)memset_s(ptr_clk_fixed_rate, sizeof(struct drv_clk_fixed_rate), 0, sizeof(struct drv_clk_fixed_rate));
	

	init.name = name;
	init.ops = &g_fixed_rate_ops;
	init.flags = flags | CLK_IS_BASIC;
	init.parent_names = (parent_name ? &parent_name: NULL);
	init.num_parents = (parent_name ? 1 : 0);

	/* ��ʼ���ṹ���Ա */
	ptr_clk_fixed_rate->fixed_rate = fixed_rate;
	ptr_clk_fixed_rate->hw.init = &init;

	ptr_clk = drv_clk_register(dev, &ptr_clk_fixed_rate->hw);

	if (IS_ERR(ptr_clk))
		osl_free((void *)ptr_clk_fixed_rate);

	return ptr_clk;
}


void drv_clk_fixed_rate_setup(struct device_node *ptr_device_node)
{
	struct clk *ptr_clk = NULL;
	const char *clk_name = ptr_device_node->name;
	u32 rate = 0;
	struct clk_lookup    *ptr_clk_lookup = NULL;

	clk_printf_info("---------------starting\n");


	if (of_property_read_u32(ptr_device_node, "clock-frequency", &rate))
		return;

	if (of_property_read_string(ptr_device_node, "clock-output-names", &clk_name)) 
	{
		clk_printf("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, ptr_device_node->name);
		return;
	}
	clk_printf_info("clk name = %s\n", clk_name);

	ptr_clk = drv_clk_register_fixed_rate(NULL, clk_name, NULL, CLK_IS_ROOT, rate);
	if (IS_ERR(ptr_clk)) 
	{
		clk_printf("[%s] fail to reigister clk %s!\n", __func__, clk_name);
		return ;
	}
	clk_printf_info("---------------drv_clk_register_fixed_rate ok\n");

    ptr_clk_lookup = osl_malloc(sizeof(struct clk_lookup));
	if (!ptr_clk_lookup) 
	{
		clk_printf("%s: could not allocate clk lookup\n", __func__);
		return ;
	}
	/* ����ɹ� */
	(void)memset_s(ptr_clk_lookup, sizeof(struct clk_lookup), 0, sizeof(struct clk_lookup));
	
	ptr_clk_lookup->dev_id = NULL;
	ptr_clk_lookup->con_id = clk_alloc_copy(ptr_clk->name);
	ptr_clk_lookup->clk = ptr_clk;
	

	drv_clkdev_add(ptr_clk_lookup);

	clk_printf_info("%s drv_clkdev_add ok\n", __func__);

    return ;
}


static unsigned int drv_clk_get_table_maxdiv(const struct clk_div_table *table)
{
	unsigned int maxdiv = 0;
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div_val; clkt++)
	{
		if (clkt->div_val> maxdiv)
		{
			maxdiv = clkt->div_val;
		}
	}
	return maxdiv;
}


/* ��Ӧ��д���Ĵ����е�ֵ��ȡ��Ƶֵ */
static unsigned int drv_clk_get_table_div(const struct clk_div_table *table,
							unsigned int val_should_to_reg)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div_val; clkt++)
	{
		if (clkt->val_to_reg== val_should_to_reg)
		{
			return clkt->div_val;
		}
	}
	return 0;
}

/* �ɷ�Ƶֵ��ȡӦ��д���Ĵ����е�ֵ */
static unsigned int drv_clk_get_table_val(const struct clk_div_table *table,
					 unsigned int div_val)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div_val; clkt++)
	{
		if (clkt->div_val== div_val)
		{
			return clkt->val_to_reg;
		}
	}
	return 0;
}



/* �Ƿ�����Ч�ķ�Ƶֵ */
static bool drv_clk_is_valid_table_div(const struct clk_div_table *table,
				      unsigned int div_val)
{
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div_val; clkt++)
	{
		if (clkt->div_val== div_val)
		{
			return true;
		}
	}
	return false;
}


/* ��ȡ��õķ�Ƶֵ */
static int drv_clk_div_bestdiv(struct clk_hw *hw, unsigned long rate,
				 unsigned long *best_parent_rate)
{
	struct hi_divclk *ptr_div_clk = container_of(hw, struct hi_divclk, hw);
	struct clk *clk_parent = __drv_clk_get_parent(hw->clk);
	unsigned long i = 0;
	unsigned long bestdiv = 0;
	unsigned long parent_rate, best_rate = 0, now_rate, maxdiv;

	maxdiv = drv_clk_get_table_maxdiv(ptr_div_clk->table);

	if (!(__drv_clk_get_flags(hw->clk) & CLK_SET_RATE_PARENT)) 
	{
		parent_rate = *best_parent_rate;
		bestdiv = DIV_ROUND_UP(parent_rate, rate);
		bestdiv = bestdiv == 0 ? 1 : bestdiv;
		bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;
		return (int)bestdiv;
	}


    /* ���ķ�Ƶֵ */
	/*lint -save -e10 -e160 -e40 -e718 -e732 -e746 */
	maxdiv = min(ULONG_MAX / rate, maxdiv);
	clk_printf_info("maxdiv = %d\n", maxdiv);
	/*lint -restore +e10 +e160 +e40 +e718 +e732 +e746 */

	for (i = 1; i <= maxdiv; i++) 
	{
		if (!drv_clk_is_valid_table_div(ptr_div_clk->table, (unsigned int)i))
		{
			continue;
		}
		parent_rate = __drv_clk_round_rate(clk_parent, MULT_ROUND_UP(rate, i));
		now_rate = parent_rate / i;
		if (now_rate <= rate && now_rate > best_rate) 
		{
			bestdiv = i;
			best_rate = now_rate;
			*best_parent_rate = parent_rate;
		}
	}

	if (!bestdiv) 
	{
		bestdiv = drv_clk_get_table_maxdiv(ptr_div_clk->table);
		*best_parent_rate = __drv_clk_round_rate(clk_parent, 1);
	}

	return (int)bestdiv;
}






static void  *drv_clk_div_get_reg(struct clk_hw *hw)
{
	struct hi_divclk *dclk;
	void 	*ret = NULL;
	u32 val = 0;

	dclk = container_of(hw, struct hi_divclk, hw);

	if (dclk->reg) {
		ret = (void *)dclk->reg;
		val = readl((u32)ret);
		val &= dclk->mbits;
		clk_printf("\n[%s]: reg = 0x%p, bits = 0x%x, regval = 0x%x\n",
			hw->clk->name, ret, dclk->mbits, val);
	}

	return ret;
}

static unsigned long drv_clk_div_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct hi_divclk *dclk = container_of(hw, struct hi_divclk, hw);
	unsigned int div_val, val_in_reg;

	val_in_reg = readl(dclk->reg) >> dclk->shift;
	val_in_reg &= WIDTH_TO_MASK(dclk->width);

	div_val = drv_clk_get_table_div(dclk->table, val_in_reg);
	if (!div_val) 
	{
		clk_printf("%s: Invalid divisor for clock %s\n", __func__,
			                               __drv_clk_get_name(hw->clk));
		return parent_rate;
	}

	return parent_rate / div_val;
}

static int drv_clk_divreg_check(struct clk_hw *hw)
{
	unsigned long rate;
	struct clk *clk = hw->clk;
	struct clk *pclk = drv_clk_get_parent(clk);

	rate = drv_clk_div_recalc_rate(hw, drv_clk_get_rate(pclk));
	if (rate == drv_clk_get_rate(clk))
		return 1;
	else
		return 0;
}

static int drv_clk_div_set_rate(struct clk_hw *ptr_clk_hw, unsigned long rate,
				  unsigned long parent_rate)
{
	struct hi_divclk *ptr_div_clk = container_of(ptr_clk_hw, struct hi_divclk, hw);
	unsigned int div_val_should;  /* Ӧ�õķ�Ƶֵ */
	unsigned int val_to_reg_bits; /* Ӧ��д���Ĵ��������Ӧbit��ֵ����Ӧ�ý�101д��bit10-8����ô��ֵΪ5����
                                     д����Щbit��û�й�ϵ
	                               */
	unsigned long flags = 0;
	u32 data;

    /* ���÷�Ƶǰ����ο�ʱ�Ӵ򿪣��������ò���Ч */	
	if (1 == ptr_div_clk->en_ref_before_set_div)
	{
		(void)__drv_clk_enable(ptr_clk_hw->clk);
	}

	div_val_should = parent_rate / rate;
	val_to_reg_bits = drv_clk_get_table_val(ptr_div_clk->table, div_val_should);

	if (val_to_reg_bits > WIDTH_TO_MASK(ptr_div_clk->width))
	{
		val_to_reg_bits = WIDTH_TO_MASK(ptr_div_clk->width);
	}

	if (ptr_div_clk->lock)
	{
		spin_lock_irqsave(ptr_div_clk->lock, flags);
	}

	data = readl(ptr_div_clk->reg);
	data &= ~(WIDTH_TO_MASK(ptr_div_clk->width) << ptr_div_clk->shift);  /* ����Ӧ��bit���� */
	data |= val_to_reg_bits << ptr_div_clk->shift;  
	data |= ptr_div_clk->mbits;
	writel(data, ptr_div_clk->reg);
    (void)readl(ptr_div_clk->reg);

	if (ptr_div_clk->lock)
	{
		spin_unlock_irqrestore(ptr_div_clk->lock, flags);
	}

	if (1 == ptr_div_clk->en_ref_before_set_div)
	{
		__drv_clk_disable(ptr_clk_hw->clk);
	}

	return 0;
}

static long drv_clk_div_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	int div_val;  /* ��Ƶֵ */

	if (!rate)
	{
		rate = 1;
	}


	div_val = drv_clk_div_bestdiv(hw, rate, prate);  /* �ҵ���ѷ�Ƶֵ */

	return (long)(*prate / (unsigned long)div_val);
}



static struct clk_ops g_div_ops = {
	.recalc_rate  = drv_clk_div_recalc_rate,
	.round_rate   = drv_clk_div_round_rate,
	.set_rate     = drv_clk_div_set_rate,
	.check_divreg = drv_clk_divreg_check,
	.get_reg      = drv_clk_div_get_reg,
};

static int  drv_clk_div_get_name_div_table(struct device_node *ptr_device_node, const char **clk_name, u32 data[])
{
	if (of_property_read_string(ptr_device_node, "clock-output-names", clk_name)) 
	{
		clk_printf("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, ptr_device_node->name);
		return -1;
	}

	/* ��Ƶֵ�� */
	if (of_property_read_u32_array(ptr_device_node, "hisilicon,clkdiv-table", &data[0], 2)) 
    {  /*lint !e525*/
		clk_printf("node %s doesn't have clkdiv-table property!\n", ptr_device_node->name);
		return -1;
	}

    return 0;
}
void  drv_clk_div_setup(struct device_node *ptr_device_node)
{
	struct clk *clk;
	const char *clk_name, **parent_names;
	struct clk_init_data *init;
	struct clk_div_table *table;
	struct hi_divclk *ptr_div_clk;
	void  *reg_base;
	unsigned int div_val_num;  /* ��Ƶֵ���� */
	unsigned int i = 0;
	u32 data[2] = {0};
	unsigned int max_div, min_div;
	struct clk_lookup *ptr_clk_lookup = NULL;

	

	reg_base = drv_clk_get_base(ptr_device_node);
	if (!reg_base) 
	{
		clk_printf("[%s] fail to get reg_base!\n", __func__);
		return;
	}

    if (drv_clk_div_get_name_div_table(ptr_device_node, &clk_name, data))
    {
		clk_printf("drv_clk_div_get_name_div_table err\n");
		return;
    }

    
    max_div = data[0];
    min_div = data[1];


	div_val_num = max_div - min_div + 1;  /* ��Ƶֵ�ĸ��� */

	/* ��Ƶֵ����<0,0>���� */
	table = osl_malloc(sizeof(struct clk_div_table) * (div_val_num + 1));
	if (!table) 
	{
		clk_printf("fail to alloc table!\n");
		return;
	}
	/* ����ɹ� */
	(void)memset_s(table, sizeof(struct clk_div_table) * (div_val_num + 1), 0, sizeof(struct clk_div_table) * (div_val_num + 1));



	/* ��Ƶ������ʱ��ֻ��һ����ʱ�� */
	parent_names = osl_malloc(sizeof(char *) * 1);
	if (!parent_names) 
	{
		clk_printf("fail to alloc parent_names!\n");
		goto err_par;
	}
	/* ����ɹ� */
	(void)memset_s(parent_names, sizeof(char *) * 1, 0, sizeof(char *) * 1);
	
	parent_names[0] = drv_of_clk_get_parent_name(ptr_device_node, 0);

	ptr_div_clk = osl_malloc(sizeof(struct hi_divclk));
	if (!ptr_div_clk) 
	{
		clk_printf("fail to alloc dclk!\n");
		goto err_dclk;
	}
	/* ����ɹ� */
	(void)memset_s(ptr_div_clk, sizeof(struct hi_divclk), 0, sizeof(struct hi_divclk));



    /* ������N��Ƶ����N+1��Ƶ */
	if (of_property_read_bool(ptr_device_node, "n_plus_1_div"))  /* N+1��Ƶ */
	{
	    ptr_div_clk->is_n_plus_1_div = 1;
	}
	
	for (i = 0; i < div_val_num; i++) 
	{
		table[i].div_val = min_div + i;
		if (1 == ptr_div_clk->is_n_plus_1_div) /* N+1��Ƶ */
		{
			table[i].val_to_reg= table[i].div_val - 1;
		}
		else  /* N��Ƶ */
		{
			table[i].val_to_reg= table[i].div_val;
		}
	}

	/* ���÷�Ƶǰ�Ƿ���Ҫ�򿪲ο�ʱ�� */
	if (of_property_read_bool(ptr_device_node, "en_ref_before_set_div"))  
	{
	    ptr_div_clk->en_ref_before_set_div = 1;
	}

	
	init = osl_malloc(sizeof(struct clk_init_data));
	if (!init) 
	{
		clk_printf("fail to alloc init!\n");
		goto err_init;
	}
	/* ����ɹ� */
	(void)memset_s(init, sizeof(struct clk_init_data), 0, sizeof(struct clk_init_data));

	/* ����div�Ĵ���ƫ�ƺͷ�Ƶbit��mask */
	if (of_property_read_u32_array(ptr_device_node, "hisilicon,clkdiv", &data[0], 2)) 
	{
		clk_printf("node %s is not fixed div but it doesn't have clkdiv property!\n", ptr_device_node->name);
		goto err_clk;
	}

	
	init->name = clk_alloc_copy(clk_name);
	init->ops = &g_div_ops;
	init->parent_names = parent_names;
	init->num_parents = 1;

	ptr_div_clk->reg = (u32)reg_base + data[0];
	ptr_div_clk->shift = (u8)(drv_clk_ffs(data[1]) - 1);
	ptr_div_clk->width = (u8)(drv_clk_fls(data[1]) - drv_clk_ffs(data[1]) + 1);

	ptr_div_clk->mbits = data[1] << 16;
	ptr_div_clk->lock = &g_stru_hs_crg_base.lock;
	ptr_div_clk->hw.init = init;
	ptr_div_clk->table = table;

	clk_printf_info("----clk %s ---is_n_plus_1_div=%d--shift = %d  width = %d\n", 
	            ptr_div_clk->hw.init->name, ptr_div_clk->is_n_plus_1_div, ptr_div_clk->shift, 
	            ptr_div_clk->width);


	
	clk = drv_clk_register(NULL, &ptr_div_clk->hw);
	if (IS_ERR(clk)) 
	{
		clk_printf("[%s] fail to register div clk %s!\n", __func__, clk_name);
		goto err_clk;
	}

	ptr_clk_lookup = osl_malloc(sizeof(struct clk_lookup));
	if (IS_ERR(ptr_clk_lookup))
	{
		clk_printf("[%s] fail to osl_malloc clk %s!\n", __func__, clk_name);
		goto err_clk;
	}
	/* ����ɹ� */
	(void)memset_s(ptr_clk_lookup, sizeof(struct clk_lookup), 0, sizeof(struct clk_lookup));
	

	ptr_clk_lookup->dev_id = NULL;
	ptr_clk_lookup->con_id = clk->name;
	ptr_clk_lookup->clk = clk;
	

	drv_clkdev_add(ptr_clk_lookup);

	return;
err_clk:
	osl_free((void *)init);
err_init:
	osl_free((void *)ptr_div_clk);
err_dclk:
	osl_free((void *)parent_names);
err_par:
	osl_free((void *)table);
}






static int  drv_clk_parse_mux(struct device_node *ptr_device_node, unsigned char *ptr_parents_num)
{
	int i, cnt;

	for (i = 0, cnt = 0;; i++, cnt++) 
	{
		if (!of_parse_phandle(ptr_device_node, "clocks", i))
		{
			break;
		}
	}

	for (i = 0; i < cnt; i++) 
	{
		if (!drv_of_clk_get_parent_name(ptr_device_node, i)) 
		{
			clk_printf("[%s] cannot get %dth parent_clk name!\n", __func__, i);
			return -ENOENT;
		}
	}
	*ptr_parents_num = (u8)cnt;

	return 0;
}


#define to_clk_mux(_hw) container_of(_hw, struct drv_clk_mux, hw)



static int drv_clk_mux_set_parent(struct clk_hw *hw, u8 idx)
{
	struct drv_clk_mux *mux = to_clk_mux(hw);
	u32 val = 0;
	unsigned long flags = 0;
	unsigned int idx_this = 0;

	if (mux->table)
	{
		idx_this = mux->table[idx];
	}
	else 
	{
		if (mux->flags & CLK_MUX_INDEX_BIT)
		{
			idx_this = ((unsigned int)1 << drv_clk_ffs(idx_this));
		}

		if (mux->flags & CLK_MUX_INDEX_ONE)
		{
			idx_this++;
		}
	}

	if (mux->lock)
	{
		spin_lock_irqsave(mux->lock, flags);
	}

	val = readl(mux->reg);
	val &= ~(mux->mask << mux->shift);
	val |= idx_this << mux->shift;
	writel(val, mux->reg);
    (void)readl(mux->reg);

	if (mux->lock)
	{
		spin_unlock_irqrestore(mux->lock, flags);
	}

	return 0;
}

static u8 drv_clk_mux_get_parent(struct clk_hw *hw)
{
	struct drv_clk_mux *mux = to_clk_mux(hw);
	unsigned int father_num = __drv_clk_get_num_parents(hw->clk);
	u32 value = 0;
	unsigned int i = 0;

	value = readl(mux->reg) >> mux->shift;
	value &= mux->mask;

	if (mux->table) 
	{
		for (i = 0; i < father_num; i++)
		{
			if (mux->table[i] == value)
			{
				return (u8)i;
			}
		}
		return ((u8)(-EINVAL)); /* ǿת���أ���Ȼ>= ��ʱ�Ӹ��� */
	}

	if (value && (mux->flags & CLK_MUX_INDEX_BIT))
	{
		value = drv_clk_ffs(value) - 1;
	}

	if (value && (mux->flags & CLK_MUX_INDEX_ONE))
	{
		value--;
	}

	if (value >= father_num)
	{
		return ((u8)(-EINVAL)); /* ǿת���أ���Ȼ>= ��ʱ�Ӹ��� */
	}

	return (u8)value;
}


static struct clk_ops g_mux_ops = {
	.get_parent = drv_clk_mux_get_parent,
	.set_parent = drv_clk_mux_set_parent,
};


struct clk *drv_clk_register_mux_table(const char * dev, const char *name,
		const char **father_names, 
		u8 father_num, 
		unsigned long clk_flags,
		void  *reg_base_addr, 
		u8 offset, 
		u32 mask,
		u8 mux_clk_flags, 
		u32 *table, 
		spinlock_t *lock)
{
	struct drv_clk_mux *mux_clk = NULL;
	struct clk *clk = NULL;
	struct clk_init_data init_data = {0};

	mux_clk = osl_malloc(sizeof(struct drv_clk_mux));
	if (!mux_clk) 
	{
		clk_printf("allocate mux-clk fail\n");
		return ERR_PTR(-ENOMEM);
	}
	/* ����ɹ� */
	(void)memset_s(mux_clk, sizeof(struct drv_clk_mux), 0, sizeof(struct drv_clk_mux));

	init_data.name = name;
	init_data.ops = &g_mux_ops;
	init_data.flags = clk_flags | CLK_IS_BASIC;
	init_data.parent_names = father_names;
	init_data.num_parents = father_num;

	/* ��ʼ���ṹ�� */
	mux_clk->reg = (u32)reg_base_addr;
	mux_clk->shift = offset;
	mux_clk->mask = mask;
	mux_clk->flags = mux_clk_flags;
	mux_clk->lock = lock;
	mux_clk->table = table;
	mux_clk->hw.init = &init_data;

	clk = drv_clk_register(dev, &mux_clk->hw);

	if (IS_ERR(clk))
		osl_free((void *)mux_clk);

	return clk;
}


struct clk *drv_clk_register_mux(const char * dev, const char *name,
		const char **parent_names, u8 num_parents, unsigned long flags,
		void  *reg, u8 shift, u8 width,
		u8 clk_mux_flags, spinlock_t *lock)
{
	u32 mask = BIT(width) - 1;

	return drv_clk_register_mux_table(dev, name, parent_names, num_parents,
				      flags, reg, shift, mask, clk_mux_flags,
				      NULL, lock);
}





static void  drv_clk_mux_setup(struct device_node *ptr_device_node)
{
	struct clk    *pstruClk = NULL;
	const char    *clk_name = NULL;
	const char    **parent_names = NULL;
	unsigned int  rdata[2] = {0};
	unsigned int  width = 0;
	unsigned char parents_num = 0;
	unsigned char shift = 0;
	unsigned char flag = 0;
	void   *base_addr = NULL;
	void   *reg_addr = NULL;
	int           i = 0;
	int           ret = -1;
	struct clk_lookup *ptr_clk_lookup = NULL;


	clk_printf_info("drv_clk_mux_setup starting--------------------\n");

	base_addr = drv_clk_get_base(ptr_device_node);
	if (!base_addr) 
	{
		clk_printf("fail to get base!\n");
		return;
	}

	if (of_property_read_string(ptr_device_node, "clock-output-names", &clk_name)) 
	{
		clk_printf("%s node doesn't have clock-output-name property!\n", ptr_device_node->name);
		return;
	}

	if (of_property_read_u32_array(ptr_device_node, "hisilicon,clkmux-reg", &rdata[0], 2)) 
    {
		clk_printf("%s node doesn't have clkmux-reg property!\n", ptr_device_node->name);
		return;
	}

	if (of_property_read_bool(ptr_device_node, "hiword"))
	{
		flag = CLK_MUX_HIWORD_MASK;

	}

	if (of_property_read_bool(ptr_device_node, "clk_mux_index_bit"))
	{
		flag |= CLK_MUX_INDEX_BIT;

	}
	else
	{
		flag |= CLK_MUX_INDEX_ONE;
	}

	ret = drv_clk_parse_mux(ptr_device_node, &parents_num);
	if (ret) 
	{
		clk_printf("%s node cannot get num_parents!\n", ptr_device_node->name);
		return;
	}

	parent_names = osl_malloc(sizeof(char *) * parents_num);
	if (!parent_names) 
	{
		clk_printf("fail to alloc parent_names!\n");
		return;
	}
	/* ����ɹ� */
	(void)memset_s(parent_names, sizeof(char *) * parents_num, 0, sizeof(char *) * parents_num);
	
	for (i = 0; i < parents_num; i++)
	{
		parent_names[i] = drv_of_clk_get_parent_name(ptr_device_node, i);
	}

	reg_addr = (void*)((unsigned long)base_addr + rdata[0]);
	shift = (u8)(drv_clk_ffs(rdata[1]) - 1);
	width = (u8)(drv_clk_fls(rdata[1]) - drv_clk_ffs(rdata[1]) + 1);

	pstruClk = drv_clk_register_mux(NULL, clk_name, parent_names, parents_num,
				     CLK_SET_RATE_PARENT, reg_addr, shift, (u8)width,
				     flag, &g_stru_hs_crg_base.lock);
	if (IS_ERR(pstruClk)) 
	{
		clk_printf("fail to register mux clk %s!\n", clk_name);
		goto err_clk;
	}

	ptr_clk_lookup = osl_malloc(sizeof(struct clk_lookup));
	if (IS_ERR(ptr_clk_lookup))
	{
		clk_printf("[%s] fail to osl_malloc clk %s!\n",
				__func__, pstruClk->name);
		goto err_clk;
	}
	/* ����ɹ� */
	(void)memset_s(ptr_clk_lookup, sizeof(struct clk_lookup), 0, sizeof(struct clk_lookup));

	ptr_clk_lookup->dev_id = NULL;
	ptr_clk_lookup->con_id = pstruClk->name;
	ptr_clk_lookup->clk = pstruClk;
	

	drv_clkdev_add(ptr_clk_lookup);

	return;
err_clk:
	osl_free((void *)parent_names);
}



/* modem���ü���,��Щʱ�ӱ�C�˹���оƬĬ�ϴ򿪣�cclk��ʼ��ʱ�ر���Щʱ�ӣ���ȡ��usrAppInit.c��modem_clk_init */
static void drv_modem_disable_non_on_clk(struct device_node *ptr_device_node)
{
	void                      *reg_base = NULL;
	unsigned int              reg_num = 0;
	unsigned int              reg_offset[CLK_DIS_REG_NUM] = {0}; 
	unsigned int              reg_val[CLK_DIS_REG_NUM] = {0};
	unsigned int              i = 0;
	int                       ret = -1;

	reg_base = drv_clk_get_base(ptr_device_node);
	if (!reg_base) 
	{
		clk_printf("fail to get reg_base!\n");
		return;
	}

	clk_printf_info("modem dis reg_base = 0x%08x\n", reg_base);

	/* ��ȡ�Ĵ������� */
	ret = of_property_read_u32(ptr_device_node, "reg_num", &reg_num);
	if (0 == ret)
	{
		clk_printf_info("reg_num = 0x%08x\n", reg_num);

		/* ��ȡƫ�� */
	    ret = of_property_read_u32_array(ptr_device_node, "reg_offset", &reg_offset[0], reg_num);
		if (0 == ret)
		{
		    clk_printf_info("reg_offset 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n", reg_offset[0], 
				                                                                   reg_offset[1],
				                                                                   reg_offset[2],
				                                                                   reg_offset[3],
				                                                                   reg_offset[4]);
			/* ��ȡӦ��д��ļĴ���ֵ */
		    ret = of_property_read_u32_array(ptr_device_node, "reg_val", &reg_val[0], reg_num);
			if (0 == ret)
			{
    		    clk_printf_info("reg_val 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n", reg_val[0], 
					                                                                   reg_val[1],
					                                                                   reg_val[2],
					                                                                   reg_val[3],
					                                                                   reg_val[4]);
			    /* д�Ĵ��� */
				for (i = 0; i < reg_num; i++)
				{
					writel(reg_val[i], (unsigned int)((unsigned int)reg_base + reg_offset[i]));
                    (void)readl((u32)((u32)reg_base + reg_offset[i] -4 + g_status_reg_offset_to_enable));
				}
			}
		}
	}
    return ;
}

static void drv_clk_en_auto_gating(struct device_node *ptr_device_node)
{
	void                      *reg_base = NULL;
	unsigned int              reg_num = 0;
	unsigned int              reg_offset[CLK_AUTO_GATING_REG_NUM] = {0}; 
	unsigned int              reg_val[CLK_AUTO_GATING_REG_NUM] = {0};
	unsigned int              reg_val_tmp = 0;
	unsigned int              i = 0;
	int                       ret = -1;

	reg_base = drv_clk_get_base(ptr_device_node);
	if (!reg_base) 
	{
		clk_printf("fail to get reg_base!\n");
		return;
	}

	clk_printf_info("en auto_gating reg_base = 0x%08x\n", reg_base);

	/* ��ȡ�Ĵ������� */
	ret = of_property_read_u32(ptr_device_node, "reg_num", &reg_num);
	if (0 == ret)
	{
		clk_printf_info("reg_num = 0x%08x\n", reg_num);

		/* ��ȡƫ�� */
	    ret = of_property_read_u32_array(ptr_device_node, "reg_offset", &reg_offset[0], reg_num);
		if (0 == ret)
		{
		    clk_printf_info("reg_offset 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n", reg_offset[0], 
				                                                                   reg_offset[1],
				                                                                   reg_offset[2],
				                                                                   reg_offset[3],
				                                                                   reg_offset[4]);
			/* ��ȡӦ��д��ļĴ���ֵ */
		    ret = of_property_read_u32_array(ptr_device_node, "reg_val", &reg_val[0], reg_num);
			if (0 == ret)
			{
    		    clk_printf_info("reg_val 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n", reg_val[0], 
					                                                                   reg_val[1],
					                                                                   reg_val[2],
					                                                                   reg_val[3],
					                                                                   reg_val[4]);
			    /* �ȶ���д�Ĵ��� */
				for (i = 0; i < reg_num; i++)
				{
				    reg_val_tmp = readl((unsigned int)((unsigned int)reg_base + reg_offset[i]));
					reg_val_tmp |= reg_val[i];
					writel(reg_val_tmp, (unsigned int)((unsigned int)reg_base + reg_offset[i]));
                    (void)readl((unsigned int)((unsigned int)reg_base + reg_offset[i]));
				}
			}
		}
	}

    return ;
}










static int drv_clk_gate_disable_auto_gating(struct clk_hw *ptr_clk_hw)
{
	struct hi_gateclk *ptr_gate_clk = NULL;
	unsigned int      reg_val = 0;

	clk_printf_info("Entering drv_clk_gate_disable_auto_gating-----------clk name %s----\n", ptr_clk_hw->clk->name);

	ptr_gate_clk = container_of(ptr_clk_hw, struct hi_gateclk, hw);

	clk_printf_info("auto_gating base=0x%08x offset=0x%08x bit=%d\n", 
		             ptr_gate_clk->auto_gate_base, ptr_gate_clk->auto_gate_offset, ptr_gate_clk->auto_gate_bit);


	/* ������ʱ�Ӳ���ʵ�ʼĴ��� */
	if ((1 != ptr_clk_hw->clk->is_virtual_clk) && (0 != ptr_gate_clk->auto_gate_base))
	{
        reg_val = readl(ptr_gate_clk->auto_gate_base + ptr_gate_clk->auto_gate_offset);
	    reg_val &= ~((unsigned int)1 << ptr_gate_clk->auto_gate_bit);
		writel(reg_val, ptr_gate_clk->auto_gate_base + ptr_gate_clk->auto_gate_offset);
        (void)readl(ptr_gate_clk->auto_gate_base + ptr_gate_clk->auto_gate_offset);
	}


    return 0;
}

static int drv_clk_gate_enable_auto_gating(struct clk_hw *ptr_clk_hw)
{
	struct hi_gateclk *ptr_gate_clk;
	unsigned int      reg_val = 0;

	clk_printf_info("Entering drv_clk_gate_enable_auto_gating-----------clk name %s----\n", ptr_clk_hw->clk->name);

	ptr_gate_clk = container_of(ptr_clk_hw, struct hi_gateclk, hw);

	clk_printf_info("auto_gating base=0x%08x offset=0x%08x bit=%d\n", 
		             ptr_gate_clk->auto_gate_base, ptr_gate_clk->auto_gate_offset, ptr_gate_clk->auto_gate_bit);


	/* ������ʱ�Ӳ���ʵ�ʼĴ��� */
	if ((1 != ptr_clk_hw->clk->is_virtual_clk) && (0 != ptr_gate_clk->auto_gate_base))
	{
        reg_val = readl(ptr_gate_clk->auto_gate_base + ptr_gate_clk->auto_gate_offset);
	    reg_val |= ((unsigned int)1 << ptr_gate_clk->auto_gate_bit);
		writel(reg_val, ptr_gate_clk->auto_gate_base + ptr_gate_clk->auto_gate_offset);
        (void)readl(ptr_gate_clk->auto_gate_base + ptr_gate_clk->auto_gate_offset);
	}


    return 0;
}


static int drv_clk_gate_is_enabled(struct clk_hw *ptr_clk_hw)
{
	struct hi_gateclk *ptr_clk_gate;
	unsigned int      reg_val = 0;

	clk_printf_info("Entering drv_clk_gate_is_enabled-------%s--------is_virtual_clk = %d\n", 
		ptr_clk_hw->clk->name, ptr_clk_hw->clk->is_virtual_clk);

	ptr_clk_gate = container_of(ptr_clk_hw, struct hi_gateclk, hw);


	if (1 != ptr_clk_hw->clk->is_virtual_clk)  /* ������ʱ�ӣ����Ĵ�����ȷ��ʱ�Ӵ򿪻��ǹر� */
	{
	    clk_printf_info("status reg=0x%x  bit=%d\n", ptr_clk_gate->reg + g_status_reg_offset_to_enable, ptr_clk_gate->bit_idx);
		reg_val = readl(ptr_clk_gate->reg + g_status_reg_offset_to_enable);
		clk_printf_info("status reg_val=0x%08x\n", reg_val);
	    reg_val &= ((u32)1 << ptr_clk_gate->bit_idx);
	    return reg_val ? 1 : 0;
	}
	else  /*  ����ʱ�� */
	{
	    return ptr_clk_hw->clk->enable_count ? 1 : 0;
	}

}


static void drv_clk_gate_disable(struct clk_hw *ptr_clk_hw)
{
	struct hi_gateclk *ptr_clk_gate;
	unsigned int      reg_val = 0;

	clk_printf_info("Entering drv_clk_gate_disable-----------clk name %s----\n", ptr_clk_hw->clk->name);

	ptr_clk_gate = container_of(ptr_clk_hw, struct hi_gateclk, hw);

	/* ������ʱ�Ӳ���ʵ�ʼĴ�����д1�ر�ʱ�ӣ�д0��Ӱ�� */
	if (1 != ptr_clk_hw->clk->is_virtual_clk)
	{
	    reg_val |= ((unsigned int)1 << ptr_clk_gate->bit_idx);
		writel(reg_val, ptr_clk_gate->reg + HI_CLK_GATE_DISABLE_OFFSET);
        (void)readl(ptr_clk_gate->reg + g_status_reg_offset_to_enable);
	}

	return ;
}


static int drv_clk_gate_enable(struct clk_hw *ptr_clk_hw)
{
	struct hi_gateclk *ptr_gate_clk;
	unsigned int      reg_val = 0;

	clk_printf_info("Entering drv_clk_gate_enable-----------clk name %s----\n", ptr_clk_hw->clk->name);

	ptr_gate_clk = container_of(ptr_clk_hw, struct hi_gateclk, hw);

	clk_printf_info("enable reg=0x%x  bit=%d\n", ptr_gate_clk->reg, ptr_gate_clk->bit_idx);


	/* ������ʱ�Ӳ���ʵ�ʼĴ�����д1��ʱ�ӣ�д0��Ӱ�� */
	if (1 != ptr_clk_hw->clk->is_virtual_clk)
	{
	    reg_val |= ((unsigned int)1 << ptr_gate_clk->bit_idx);
		writel(reg_val, ptr_gate_clk->reg);
        (void)readl(ptr_gate_clk->reg + g_status_reg_offset_to_enable);
	}


	return 0;
}

static struct clk_ops g_gate_ops = {
	.enable		         = drv_clk_gate_enable,
	.disable	         = drv_clk_gate_disable,
	.is_enabled          = drv_clk_gate_is_enabled,
	.enable_auto_gating  = drv_clk_gate_enable_auto_gating,
	.disable_auto_gating = drv_clk_gate_disable_auto_gating,
};


static void  drv_clk_gate_setup(struct device_node *ptr_device_node)
{
	struct hi_gateclk    *ptr_hi_gate_clk;
	struct clk_init_data *ptr_clk_init_data;
	struct clk           *ptr_clk;
	const char           *clk_name;

	const char           **parent_names;
	void          *reg_base;
	u32                  au32_data[2] = {0};
	u32                  auto_gating_data[3] = {0};
	struct clk_lookup    *ptr_clk_lookup = NULL;

	reg_base = drv_clk_get_base(ptr_device_node);
	if (!reg_base) 
	{
		clk_printf("fail to get reg_base!\n");
		return;
	}



	if (of_property_read_string(ptr_device_node, "clock-output-names", &clk_name)) 
	{
		clk_printf("[%s] %s node doesn't have clock-output-name property!\n",
			                  __func__, ptr_device_node->name);
		return;
	}
	


	/* ����ʱ��ֻ��һ���̶��ĸ�ʱ�� */
	parent_names = osl_malloc(sizeof(char *));
	if (!parent_names) 
	{
		clk_printf("[%s] fail to alloc parents_names!\n", __func__);
		return;
	}
	/* ����ɹ� */
	(void)memset_s(parent_names, sizeof(char *), 0, sizeof(char *));

	parent_names[0] = drv_of_clk_get_parent_name(ptr_device_node, 0);


    /* Ϊgate clk�����ڴ� */
	ptr_hi_gate_clk = osl_malloc(sizeof(struct hi_gateclk));
	if (!ptr_hi_gate_clk) 
	{
		clk_printf("[%s] fail to alloc gate clk!\n", __func__);
		goto err_gateclk;
	}
	/* ����ɹ� */
	(void)memset_s(ptr_hi_gate_clk, sizeof(struct hi_gateclk), 0, sizeof(struct hi_gateclk));

    /* Ϊʱ�ӳ�ʼ�����������ڴ� */
	ptr_clk_init_data = osl_malloc(sizeof(struct clk_init_data));
	if (!ptr_clk_init_data) 
	{
		clk_printf("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	/* ����ɹ� */
	(void)memset_s(ptr_clk_init_data, sizeof(struct clk_init_data), 0, sizeof(struct clk_init_data));

	
	ptr_clk_init_data->name = clk_alloc_copy(clk_name);
	ptr_clk_init_data->ops = &g_gate_ops;
	ptr_clk_init_data->flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED;
	ptr_clk_init_data->parent_names = parent_names;
	ptr_clk_init_data->num_parents = 1;

	ptr_hi_gate_clk->lock = &g_stru_hs_crg_base.lock;
	ptr_hi_gate_clk->hw.init = ptr_clk_init_data;
	
    /* �Ƿ�������ʱ�� */
	if (of_property_read_bool(ptr_device_node, "isvirtual"))
	{
		ptr_hi_gate_clk->hw.isvirtual = 1;
		clk_printf_info("----------%s isvirtual\n", ptr_clk_init_data->name);


	}
	else /* ������ʱ�� */
	{
		
		if (of_property_read_u32_array(ptr_device_node, "hisilicon,gate_offset_bit", &au32_data[0], 2)) 
		{
			clk_printf("[%d] %s node doesn't have gate_offset_bit property!\n",
				                  __LINE__, ptr_device_node->name);
			return;
		}

		ptr_hi_gate_clk->reg = (u32)reg_base + au32_data[0];
		ptr_hi_gate_clk->bit_idx = (u8)au32_data[1];

		clk_printf_info("#####---gate offset=0x%x bit=%d\n", au32_data[0], au32_data[1]);
	}

    /* ��ȡaux_flag��־ */
	if (of_property_read_bool(ptr_device_node, "aux_flag"))
	{
		ptr_hi_gate_clk->hw.aux_flag = 1;
		clk_printf_info("----------%s -----------aux_flag\n", ptr_clk_init_data->name);
	}

    /* �Ƿ���Ҷ�ӽڵ� */
	if (of_property_read_bool(ptr_device_node, "leaf_clk"))
	{
		ptr_hi_gate_clk->hw.leaf_flag = 1;
		clk_printf_info("----------%s -----------leaf_clk\n", ptr_clk_init_data->name);
	}

    /* �Զ��ſ���� */
	if (0 != of_property_read_u32_array(ptr_device_node, "hisilicon,auto_gate_base_offset_bit", &auto_gating_data[0], 3)) 
	{
		clk_printf_info("-------%s ---has no auto_gate_base_offset_bit property\n", ptr_clk_init_data->name);
		//return ;
	}
	ptr_hi_gate_clk->auto_gate_offset = auto_gating_data[1];
	ptr_hi_gate_clk->auto_gate_bit = (u8)auto_gating_data[2];
	/* ����sys ctrl�ӿڣ��õ������ַ */
	ptr_hi_gate_clk->auto_gate_base = (u32)bsp_sysctrl_addr_get((void*)auto_gating_data[0]);
	

    /* ע��ʱ�� */
	ptr_clk = drv_clk_register(NULL, &ptr_hi_gate_clk->hw);
	if (IS_ERR(ptr_clk)) 
	{
		clk_printf("[%s] fail to reigister clk %s!\n",
			                   __func__, clk_name);
		goto err_clk;
	}

    clk_printf_info("#####---drv_clk_register  ok\n");



	ptr_clk_lookup = osl_malloc(sizeof(struct clk_lookup));
	if (IS_ERR(ptr_clk_lookup))
	{
		clk_printf("[%s] fail to osl_malloc clk %s!\n",
				__func__, ptr_clk->name);
		goto err_clk;
	}

	/* ����ɹ� */
	(void)memset_s(ptr_clk_lookup, sizeof(struct clk_lookup), 0, sizeof(struct clk_lookup));

	ptr_clk_lookup->dev_id = NULL;
	ptr_clk_lookup->con_id = clk_alloc_copy(ptr_clk->name);
	ptr_clk_lookup->clk = ptr_clk;
	

	drv_clkdev_add(ptr_clk_lookup);


	return;
err_clk:
	osl_free((void *)ptr_clk_init_data);
err_init:
	osl_free((void *)ptr_hi_gate_clk);
err_gateclk:
	osl_free((void *)parent_names);
}

static const struct of_device_id g_astru_of_device_id_match[] = {
	{ .compatible = "hisilicon,clk-ao-crg_mdm",	  .data = (void *)HS_CRG_AO, },
	{ .compatible = "hisilicon,clk-pd-crg_mdm",	  .data = (void *)HS_CRG_PD, },
	{ .compatible = "hisilicon,clk-mdm-crg_mdm",  .data = (void *)HS_CRG_MDM, },
    {}
};

static const struct of_device_id g_astru_of_device_id_init[] = 
{
		{ .compatible = "hisilicon,hisi-clk-fixed_mdm", .data = drv_clk_fixed_rate_setup, },
		{ .compatible = "hisilicon,hisi-clk-mux_mdm",   .data = drv_clk_mux_setup, },
		{ .compatible = "hisilicon,hisi-clk-div_mdm",   .data = drv_clk_div_setup, },
		{ .compatible = "hisilicon,hisi-clk-gate_mdm",  .data = drv_clk_gate_setup, },
		{ .compatible = "hisilicon,fixed_factor_mdm",   .data = drv_clk_fixed_factor_setup, },
		{ .compatible = "hisilicon,modem_non_on_clk",   .data = drv_modem_disable_non_on_clk, },
		{ .compatible = "hisilicon,auto_gating",        .data = drv_clk_en_auto_gating, },
        {}
};


static unsigned int drv_clk_reg_node_info_get(struct device_node *np, u32 idx)
{
	const __be32 *spec_ptr = NULL;
	const __be32 *prop = NULL;
	unsigned int cells_size = 0, len = 0;
	unsigned int na = 0, ns = 0;

	spec_ptr = (const __be32 *)of_get_property(np, "reg", (int *)&len);
	len /= 4;

	if (NULL == spec_ptr)
	{
		clk_printf("cannot find reg property\n");
		return 0;
	}

	prop = (const __be32 *)of_get_property(np, "#address-cells", NULL);
	if(NULL != prop)
	{
		na = be32_to_cpup(prop);
	}

	prop = of_get_property(np, "#size-cells", NULL);
	if(NULL != prop)
	{
		ns = be32_to_cpup(prop);
	}

	cells_size = na + ns;
	if(cells_size == 0)
	{
		cells_size = 2;
	}
	if((idx * cells_size) > len)/*lint !e737*/
	{
		clk_printf("index = %d is out of range\n", idx);
		return 0;
	}

	return (unsigned int)of_read_number((const __be32 *)((unsigned int)spec_ptr + idx *cells_size) , 1);
}

static int drv_clk_get_status_offset_to_enable(struct device_node *ptr_device_node)
{
    struct device_node        *ptr_device_node_parent = NULL;
    unsigned int              read_data_from_node = 0;
   
	/* �õ�status�Ĵ��������enable�Ĵ�����ƫ�� */
	if (!g_status_reg_offset_to_enable)  /* ֻ��ֵһ�� */
	{
		ptr_device_node_parent = of_get_parent(ptr_device_node);
		if (!ptr_device_node_parent) 
		{
			clk_printf("node %s doesn't have parent node!\n", ptr_device_node->name);
			return -1;
		}
		
		if (of_property_read_u32(ptr_device_node_parent, "status_reg_offset", &read_data_from_node)) 
		{
			clk_printf("[%d] %s node doesn't have status_reg_offset property!\n",
				                  __LINE__, ptr_device_node_parent->name);
			return -1;
		}

		g_status_reg_offset_to_enable = read_data_from_node;
	}
    
    return 0;
}

static void   *drv_clk_get_base(struct device_node *ptr_device_node)
{
	struct device_node        *ptr_device_node_parent = NULL;
	const struct of_device_id *ptr_of_device_id_match = NULL;
	void                      *ptr_ret = NULL;
	unsigned int              phy_addr = 0;

	ptr_device_node_parent = of_get_parent(ptr_device_node);
	if (!ptr_device_node_parent) 
	{
		clk_printf("[%s] node %s doesn't have parent node!\n", __func__, ptr_device_node->name);
		goto out;
	}
	ptr_of_device_id_match = of_match_node(g_astru_of_device_id_match, ptr_device_node_parent);
	if (!ptr_of_device_id_match) 
	{
		clk_printf("[%s] parent node %s doesn't match!\n", __func__, ptr_device_node_parent->name);
		goto out;
	}

    if (drv_clk_get_status_offset_to_enable(ptr_device_node_parent))
    {
        clk_printf("drv_clk_get_status_offset_to_enable err\n", ptr_device_node_parent->name);
        goto out;
    }


    switch ((unsigned int)ptr_of_device_id_match->data) 
    {
		case HS_CRG_AO:
			if (!g_stru_hs_crg_base.ptr_ao_crg_base)
			{
				/* ��ȡreg��Ϣ�������ַ */
				phy_addr = drv_clk_reg_node_info_get(ptr_device_node_parent, 0);
				/* ����sys ctrl�ӿڣ��õ������ַ */
				ptr_ret = (void *)bsp_sysctrl_addr_get((void*)phy_addr);
				g_stru_hs_crg_base.ptr_ao_crg_base = (u32)ptr_ret;
			} 
			else 
			{
				ptr_ret = (void*)g_stru_hs_crg_base.ptr_ao_crg_base;
			}
			break;
		case HS_CRG_PD:
			if (!g_stru_hs_crg_base.ptr_pd_crg_base) 
			{
				//ptr_ret = of_iomap(ptr_device_node_parent, 0);
				/* ��ȡreg��Ϣ�������ַ */
				phy_addr = drv_clk_reg_node_info_get(ptr_device_node_parent, 0);
				
				/* ����sys ctrl�ӿڣ��õ������ַ */
				ptr_ret = (void *)bsp_sysctrl_addr_get((void*)phy_addr);
				g_stru_hs_crg_base.ptr_pd_crg_base = (u32)ptr_ret;
			} 
			else 
			{
				ptr_ret = (void*)g_stru_hs_crg_base.ptr_pd_crg_base;
			}
			break;
		case HS_CRG_MDM:
			if (!g_stru_hs_crg_base.ptr_mdm_crg_base) 
			{
				//ptr_ret = of_iomap(ptr_device_node_parent, 0);
			    /* ��ȡreg��Ϣ�������ַ */
				phy_addr = drv_clk_reg_node_info_get(ptr_device_node_parent, 0);

				/* ����sys ctrl�ӿڣ��õ������ַ */
				ptr_ret = (void *)bsp_sysctrl_addr_get((void*)phy_addr);
				g_stru_hs_crg_base.ptr_mdm_crg_base = (u32)ptr_ret;
			} 
			else 
			{
				ptr_ret = (void*)g_stru_hs_crg_base.ptr_mdm_crg_base;
			}
			break;

		default:
			{
				clk_printf("[%s] cannot find the match node!\n", __func__);
				ptr_ret = NULL;
			}
			break;
	}
out:
	return ptr_ret;
}



void  bsp_clk_init(void)
{

    //clk_printf_info("######### hi_clk_init start ######### \n");

    (void)memset_s(&g_stru_hs_crg_base, sizeof(struct hs_crg_base), 0, sizeof(struct hs_crg_base));
	
	spin_lock_init(&g_stru_hs_crg_base.lock);


    drv_of_clk_init(g_astru_of_device_id_init);

    clk_printf("ccore clk init succeeded\n");

    return ;
}

/* ������sio������ʱ�ӣ���A��ʹ�ã�������ԴͷΪABB��WPLL����C�˿���WPLL���ص� */
static struct remote_pll_ctrl_msg g_remote_pll_ctrl_msg;
static unsigned int g_remote_clk_chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_REMOTE_CLK;
#define REMOTE_CLK_OP_OK            0
#define REMOTE_CLK_OP_ERR           -1
#define REMOTE_CLK_OP_INVALID_CLK   -2

static void drv_operate_wpll(struct  remote_pll_ctrl_msg  *rx_msg)
{
    int ret = 0;

    if (1 == rx_msg->op_type) /* �� */
    {
        ret = bsp_abb_pll_enable(PWC_COMM_MODE_REMOTE_CLK_W, PWC_COMM_MODEM_0, PWC_COMM_CHANNEL_0);
        if (ret)  /* ����ʧ�� */
        {
            clk_printf("WPLL abb_ch_pll_enable err ret[%d]\n", ret);
            g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_ERR;
        }
        else  /* �����ɹ� */
        {
            g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_OK;
        }
    }
    else /* �� */
    {
        ret = bsp_abb_pll_disable(PWC_COMM_MODE_REMOTE_CLK_W, PWC_COMM_MODEM_0, PWC_COMM_CHANNEL_0);
        if (ret)
        {
            clk_printf("WPLL abb_ch_pll_disable err ret[%d]\n", ret);
            g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_ERR;
        }
        else  /* �����ɹ� */
        {
            g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_OK;
        }
    }
}

static void drv_operate_gpll(struct  remote_pll_ctrl_msg  *rx_msg)
{
    int ret = 0;

    if (1 == rx_msg->op_type) /* �� */
    {
        ret = bsp_abb_pll_enable(PWC_COMM_MODE_REMOTE_CLK_G, PWC_COMM_MODEM_0, PWC_COMM_CHANNEL_0);
        if (ret)
        {
            clk_printf("GPLL abb_ch_pll_enable err ret[%d]\n", ret);
            g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_ERR;
        }
        else  /* �����ɹ� */
        {
            g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_OK;
        }
    }
    else /* �� */
    {
        ret = bsp_abb_pll_disable(PWC_COMM_MODE_REMOTE_CLK_G, PWC_COMM_MODEM_0, PWC_COMM_CHANNEL_0);
        if (ret)
        {
            clk_printf("GPLL abb_ch_pll_disable err ret[%d]\n", ret);
            g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_ERR;
        }
        else  /* �����ɹ� */
        {
            g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_OK;
        }
    }
}

static void drv_handle_rx_msg(struct  remote_pll_ctrl_msg  *rx_msg)
{
    
	/* ������Ϣ��ͶƱ */
	if (CTRL_BY_CCORE_WPLL == rx_msg->pll_id)
	{
	    drv_operate_wpll(rx_msg);
	}
	else if (CTRL_BY_CCORE_GPLL == rx_msg->pll_id)
	{
        drv_operate_gpll(rx_msg);
	}
	else
	{
		clk_printf("invalid pll_id[0x%x]\n", rx_msg->pll_id);
		g_remote_pll_ctrl_msg.op_result = REMOTE_CLK_OP_INVALID_CLK;
	}
    
}
static int remote_clk_rx_deal(unsigned int channel_id , unsigned int len, void* context)
{	
	struct  remote_pll_ctrl_msg  rx_msg = {0};
	int rx_tx_len = 0;

    /* �õ�A����Ϣ */
	rx_tx_len = bsp_icc_read(g_remote_clk_chan_id, (u8*)&rx_msg, sizeof(struct remote_pll_ctrl_msg));
	if(rx_tx_len != (int)sizeof(struct remote_pll_ctrl_msg))
	{
		clk_printf("read len(0x%x) != expected len(0x%x).\n", rx_tx_len, sizeof(struct remote_pll_ctrl_msg));
		return -1;
	}

    drv_handle_rx_msg(&rx_msg);

	/* ��PLL����������ظ�A�� */
    rx_tx_len = bsp_icc_send(ICC_CPU_APP, g_remote_clk_chan_id, (unsigned char*)&g_remote_pll_ctrl_msg, (u32)sizeof(struct remote_pll_ctrl_msg));
    if(rx_tx_len != (int)sizeof(struct remote_pll_ctrl_msg))
    {
        clk_printf("ccore reply len(0x%x) != expected len(0x%x).\n", rx_tx_len, sizeof(struct remote_pll_ctrl_msg));
        return -1;
    }

    return 0;
}

/* ע��ICC�ص� */
void bsp_remote_clk_init(void)
{
    int ret = 0;

    ret = bsp_icc_event_register(g_remote_clk_chan_id, (read_cb_func)remote_clk_rx_deal, NULL, NULL, NULL);
    if(ret)
    {
        clk_printf("ccore bsp_icc_event_register err ret[%d]\n", ret);
        return ;
    }  

    return ;
}





