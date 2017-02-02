#include <boot.h>
#include <debug.h>
#include <platform.h>
#include <bsp_memmap.h>
//#include <bsp_version.h>

#include <fdt_ops.h>
#include <partition_ops.h>
#include <hi_modem.h>
#include <module.h>
#include <system.h>
#include <boardid.h>
#include <emmc_ops.h>
#include <hkadc.h>
#include <hisi_secureboot.h>
#include <modemid.h>
#include <module_level.h>
#include <loadm_balong.h>
#include <sys.h>

/*lint --e{838,826,712}*/
#ifdef FASTBOOT_MODEM_REMOVE_HEAD
#define VRL_MODEM_SIZE			(4 * 1024)
#define HEAD_OFFSET_IN_VRL		(4 * 1024 - 128)
#define MODEM_OFFSET_IN_VRL		(32 * 4 * 1024)
#endif

#define EMMC_BLOCK_SIZE			512
#define DSP_IMAGE_NAME "DSP"

unsigned int modem_addr = 0;

int load_modem_image(void)
{
	unsigned offset = 0;
	unsigned bytes = 0;         /* the data size of read, 0 means read all partition */
	struct ptentry *ptn = NULL;
	void *img_addr = NULL;
	unsigned char *img_head = NULL;
	char *str_modem = "modem";
#ifdef FASTBOOT_MODEM_REMOVE_HEAD
	char *str_vrl = "vrl";
#else
	unsigned head_size = 0;
#endif
	struct image_head *head;
#ifdef HISI_SECBOOT
	unsigned int ret;
	struct secboot_operators *secboot_ops;
	char secinfo[64] = {0};
#endif

	struct partition_operators *part_ops = get_operators(PARTITION_MODULE_NAME_STR);
	if(!part_ops){
		PRINT_ERROR("can not get part_ops!\n");
		return -1;
	}
	struct emmc_operators *emmc_ops = NULL;

    writel(LOAD_MODEM_ERROR_FLAG, (SHM_BASE_ADDR + SHM_OFFSET_LOADM));
	emmc_ops = get_operators(EMMC_MODULE_NAME_STR);
	if(!emmc_ops){
		PRINT_ERROR("can not get emmc_ops!\n");
		return -1;
	}
#ifdef FASTBOOT_MODEM_REMOVE_HEAD
	img_head = alloc(VRL_MODEM_SIZE);
	offset = MODEM_OFFSET_IN_VRL;
	if (NULL == img_head) {
		PRINT_ERROR("load_modem: alloc error.\n");
		return -1;
    }
	ptn = part_ops->find_ptn(str_vrl);
	if (0 == ptn) {
		PRINT_ERROR("can't find ptn VRL modem\n");
		return -1;
	}
	/* read head info */
	bytes = VRL_MODEM_SIZE;
	if (emmc_ops->emmc_read(ptn, offset, (void *)img_head, &bytes)) {
		PRINT_ERROR("read modem fail\n");
		return -1;
	}
	head = (struct image_head*)((unsigned char *)img_head + HEAD_OFFSET_IN_VRL);
	/* it will overlap head_size ahead of load_addr, does it mater??? */
	img_addr = (void *)((unsigned long)head->load_addr);
	bytes = head->image_length;

	ptn = part_ops->find_ptn(str_modem);
	if (0 == ptn) {
		PRINT_ERROR("can't find ptn VRL modem\n");
		return -1;
	}
#else
	head_size = sizeof(struct image_head);
	img_head = alloc(EMMC_BLOCK_SIZE);
	if (NULL == img_head) {
		PRINT_ERROR("load_modem: alloc error.\n");
		return -1;
    }
	ptn = part_ops->find_ptn(str_modem);

	if (0 == ptn) {
		PRINT_ERROR("can't find ptn modem\n");
		return -1;
	}
	/* read head info */
	bytes = EMMC_BLOCK_SIZE;
	if (emmc_ops->emmc_read(ptn, offset, (void *)img_head, &bytes)) {
		PRINT_ERROR("read modem fail\n");
		return -1;
	}

	head = (struct image_head*)img_head;

	/* it will overlap head_size ahead of load_addr, does it mater??? */
	img_addr = (void *)((unsigned long)head->load_addr - head_size);
	bytes = head->image_length + head_size;
#endif

	bytes = (bytes < ptn->length*EMMC_BLOCK_SIZE) ? bytes : ptn->length*EMMC_BLOCK_SIZE;
	if (bytes % 64 != 0)
		bytes = bytes + 64 - (bytes % 64);

	offset = 0;
	/* read the whole modem image to img_addr.
	this will load image head to load_addr - head_size, and
	image data to load_addr. */
	if (emmc_ops->emmc_read(ptn, offset, (void *)img_addr, &bytes)) {
		PRINT_ERROR("read modem fail\n");
		return -1;
	}

    /*lint -save -e570*/
    writel(LOAD_MODEM_OK_FLAG, (SHM_BASE_ADDR + SHM_OFFSET_LOADM));
    writel(head->load_addr, (SHM_BASE_ADDR + SHM_OFFSET_LOADM) + 4);
    writel(head->image_length, (SHM_BASE_ADDR + SHM_OFFSET_LOADM) + 8);
    /*lint -restore*/

	modem_addr = (uintptr_t) img_addr;
	/* change to use RAM verification. */
#ifdef HISI_SECBOOT
	secboot_ops = get_operators(SECBOOT_MODULE_NAME_STR);
	if(!secboot_ops){
		PRINT_ERROR("can not get secboot_ops!\n");
		return -1;
	}

	ret = secboot_ops->get_secinfo(secinfo, ptn->name, modem_addr, bytes);
	if (SECBOOT_RET_SUCCESS != ret) {
		PRINT_ERROR("%s: secure get_secinfo error, hold system!\n", __func__);
		secboot_ops->hold_system();
	}
#endif

	return 0;
}

#if (LPHY_TOTAL_IMG_SIZE > MODEM_DSP_SIZE)
#error Dsp image over ddr_tlphy_image_size
#endif


int load_modem_dsp()
{
	unsigned offset = 0;        /* offset of read, must be multiple of 512 */
	unsigned bytes;         /* the data size of read, 0 means read all partition */
	struct ptentry *ptn;
	char *img_addr;
	void *dest_addr;
    struct image_head *head;
    unsigned char *img_head;
	unsigned head_size = sizeof(struct image_head);
	char *str_modem = "modem_dsp";

	struct partition_operators *part_ops = get_operators(PARTITION_MODULE_NAME_STR);
	if(!part_ops){
		PRINT_ERROR("can not get part_ops!\n");
		return -1;
	}
	struct emmc_operators *emmc_ops = get_operators(EMMC_MODULE_NAME_STR);
	if(!emmc_ops){
		PRINT_ERROR("can not get emmc_ops!\n");
		return -1;
	}

	img_addr = alloc(DSP_PARTITON_SIZE);
	ptn = part_ops->find_ptn(str_modem);
	if (0 == ptn) {
		PRINT_ERROR("can't find ptn modem dsp\n");
		return -1;
	}

    img_head = alloc(EMMC_BLOCK_SIZE);
	if (NULL == img_head) {
		PRINT_ERROR("load_modem_dsp: alloc error.\n");
		return -1;
    }

    /* read head info */
	bytes = EMMC_BLOCK_SIZE;
	if (emmc_ops->emmc_read(ptn, offset, (void *)img_head, &bytes)) {
		PRINT_ERROR("read modem fail\n");
		return -1;
	}
    head = (struct image_head*)img_head;
    if (memcmp(head->image_name, DSP_IMAGE_NAME, sizeof(DSP_IMAGE_NAME)))
    {
        PRINT_ERROR("dsp image not found\n");
		return -1;
    }

	bytes = DSP_PARTITON_SIZE;
	if (emmc_ops->emmc_read(ptn, offset, (void *)img_addr, &bytes)) {
		PRINT_ERROR("read modem dsp fail\n");
		return -1;
	}
	/*load dsp to DDR_TLPHY_IMAGE_ADDR*/
	//lint --e{835}
	dest_addr = (void *)DDR_TLPHY_IMAGE_ADDR;
	memcpy(dest_addr, (char *)(img_addr + head_size), LPHY_TOTAL_IMG_SIZE);

	return 0;
}

