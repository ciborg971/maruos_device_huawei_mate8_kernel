
#include <product_config.h>
#include <partition.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/fs.h>
#include "load_image.h"
#include <linux/slab.h>
#include <asm/unistd.h>
#include <asm/uaccess.h>
#include <linux/libfdt.h>
#include <linux/of.h>
#include "device_tree.h"


#ifdef CONFIG_TZDRIVER
#include <teek_client_api.h>
#include <teek_client_id.h>
#endif

#ifdef CONFIG_TZDRIVER
#define SECBOOT_BUFLEN  		  (0x100000)
#define DRV_RESET_NAME_MAX        (255)
#define DRV_RESET_BLK_MAX         (50)
#define DRV_RESET_BLK_DEV          "/dev/block/mmcblk0p"

#ifndef VRL_SIZE
#define VRL_SIZE				(4 * 1024)
#endif
#define IMAGE_HEADER_SIZE		(128)
#define HEADER_IN_VRL_OFFSET	(VRL_SIZE - IMAGE_HEADER_SIZE)

static 	u32 g_modem_addr = 0;
static 	u32 g_hifi_addr = 0;
static 	u32 g_dsp_addr = 0;
static 	u32 g_xdsp_addr = 0;
static  u8 SECBOOT_BUFFER[SECBOOT_BUFLEN]; /*1M Bytes*/
typedef enum SVC_SECBOOT_IMG_TYPE SECBOOT_IMG_TYPE;

extern struct partition partitions[];
s32 load_vrl_from_image_to_os(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype);
s32 load_vrl_from_partition_to_os(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype);
s32 load_dsp_data_to_os_from_filesystem(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype);
s32 load_dsp_data_to_os_from_partition(TEEC_Session *session);
s32 load_xdsp_data_to_os_from_partition(TEEC_Session *session);

int bsp_get_vrl_index(const char *partion_name)
{
	int ptn_number  = 0;
	int i = 0;
	int vrl_index = 0;
	s32 ret = SEC_ERROR;

	if(NULL == partion_name) {
        sec_print_err("partion_name(%p) is null", partion_name);
        return ret;
    }
	
	ptn_number = sizeof(partitions) / sizeof(struct partition);
	
    for (i = 0; i < ptn_number; i++) {
	    if (NULL == partitions[i].name) {
	        sec_print_err("partitions[%d].name: now we get a NULL pointer!", i);
	        continue;
	    }

		if (!strcmp(partion_name, partitions[i].name)) {
			vrl_index = i + 1;
			break;
		}
    }

	if (i >= ptn_number) {
       sec_print_err("partion_name(%s) is not in partion table!\n", partion_name);
	   return ret;
    }

	return vrl_index;
}

int bsp_read_file(const char *path_name, unsigned int offset,
		unsigned int length, char *buffer)
{
	int ret = -1;
	struct file *fp;
	loff_t pos = 0;
	mm_segment_t fs;

	if((NULL == path_name) || (NULL == buffer)) {
        sec_print_err("path_name(%p) or buffer(%p) is null", path_name, buffer);
        return SEC_ERROR;
	}


	fp = filp_open(path_name, O_RDONLY, 0600);
	if (IS_ERR(fp)) {
		sec_print_err("filp_open(%s) failed", path_name);
		goto error;
	}

	ret = vfs_llseek(fp, offset, SEEK_SET);
	if (ret < 0) {
		sec_print_err("seek ops failed, ret %d", ret);
		goto error2;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);

	pos = fp->f_pos;
	ret = vfs_read(fp, (char __user *) buffer, length, &pos);
	if (ret != length) {
		sec_print_err("read ops failed, path_name %s ret=%d(len=%d)", path_name,ret, length);
		set_fs(fs);
		goto error2;
	}
	set_fs(fs);

	filp_close(fp, NULL);

	return SEC_OK;

	error2: filp_close(fp, NULL);
	error:
	sec_print_err("failed");
	return SEC_ERROR;
}


int bsp_read_bin(const char *partion_name, unsigned int offset, unsigned int length, char *buffer)
{
    int ret          = -1;
    int i            = 0;
    int current_ptn_number  = 0;
    char *pathname   = NULL;
    char blk_number[DRV_RESET_BLK_MAX] = {0};
    struct file *fp;
    mm_segment_t fs;
    loff_t pos = 0;

    if((NULL == partion_name) || (NULL == buffer)) {
        sec_print_err("partion_name(%p) or buffer(%p) is null", partion_name, buffer);
        return SEC_ERROR;
    }

    /*get resource*/
    pathname = (char *)kmalloc(DRV_RESET_NAME_MAX, GFP_KERNEL);
    if (!pathname) {
        sec_print_err("pathname malloc failed" );
        return SEC_ERROR;
    }

    current_ptn_number = sizeof(partitions) / sizeof(struct partition);

    /*open file*/
    for (i = 0; i < current_ptn_number; i++) {
        if (NULL == partitions[i].name) {
            sec_print_err("partitions[%d].name: now we get a NULL pointer!", i);
            continue;
        }

        /*if equal*/
        if (!strcmp(partion_name, partitions[i].name)) {
            memset(pathname, 0, DRV_RESET_NAME_MAX);
            strncat(pathname, DRV_RESET_BLK_DEV, DRV_RESET_NAME_MAX-1);

            snprintf(blk_number,sizeof(blk_number), "%d", i);
            strncat(pathname, blk_number, DRV_RESET_NAME_MAX-1);

            break;
        }
    }

    if (i >= current_ptn_number) {
        sec_print_err("partion_name(%s) is not in partion table!\n", partion_name);
        goto error;
    }

    fp = filp_open(pathname, O_RDONLY, 0600);
    if (IS_ERR(fp)) {
        sec_print_err("filp_open(%s) failed", pathname);
        goto error;
    }

    ret = vfs_llseek(fp, offset, SEEK_SET);
    if(ret < 0) {
        sec_print_err("seek ops failed, ret %d", ret);
        goto error2;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);

    pos = fp->f_pos;
    ret = vfs_read(fp, (char __user *)buffer, length, &pos);
    if (ret != length) {
        sec_print_err("read ops failed, ret=%d(len=%d)", ret, length);
        set_fs(fs);
        goto error2;
    }
    set_fs(fs);

    filp_close(fp, NULL);


    /*free resource*/
    if(NULL != pathname) {
       kfree(pathname);
       pathname = NULL;
    }

    return SEC_OK;

error2:
    filp_close(fp, NULL);

error:
    /*释放资源2*/
    if(NULL != pathname) {
       kfree(pathname);
       pathname = NULL;
    }

    sec_print_err("failed");
    return SEC_ERROR;

}

int get_modemid(unsigned int *modemid)
{
	int ret = 0;
	struct device_node * np = NULL;

	np = of_find_compatible_node(NULL, NULL, CHIP_COMPITABLE_STR);
	if(NULL == np)
	{
		sec_print_err("-----can not find %s node by compatible\n",CHIP_COMPITABLE_STR);
		return SEC_ERROR;
	}
	ret = of_property_read_u32(np, MODEMID_STR, modemid);
	if(SEC_OK == ret)
	{
		sec_print_info("find modemid by dts: %x\n", *modemid);
		return SEC_OK;
	}
	else
	{
		sec_print_err("-----can not find %s node by compatible node\n",MODEMID_STR);
		return SEC_ERROR;
	}
}

unsigned int get_dtb_entry(unsigned int modemid, struct modem_dt_table_t *dt_hdr, struct modem_dt_entry_t *dt_entry_ccore)
{
	uint32_t i;
	uint8_t sec_id[4]={0};
	struct modem_dt_entry_t *dt_entry_ptr = NULL;

	sec_id[0] = MODEMID_K_BITS(modemid);
	sec_id[1] = MODEMID_H_BITS(modemid);
	sec_id[2] = MODEMID_M_BITS(modemid);
	sec_id[3] = MODEMID_L_BITS(modemid);


	/* 获取与modemid匹配的acore/ccore dt_entry 指针,复用dtctool，modem config.dts中将boardid配置为对应modem_id值 */
	dt_entry_ptr = (struct modem_dt_entry_t *)((char *)dt_hdr + sizeof(struct modem_dt_table_t));
	for (i = 0; i < dt_hdr->num_entries; i++)
	{
        if ((dt_entry_ptr->boardid[0] == sec_id[0]) &&
        (dt_entry_ptr->boardid[1] == sec_id[1]) &&
        (dt_entry_ptr->boardid[2] == sec_id[2]) &&
        (dt_entry_ptr->boardid[3] == sec_id[3]))
        {
		sec_print_info("[%d],modemid(0x%x, 0x%x, 0x%x, 0x%x)\n",
                i, dt_entry_ptr->boardid[0], dt_entry_ptr->boardid[1], dt_entry_ptr->boardid[2], dt_entry_ptr->boardid[3]);

			memcpy((void *)dt_entry_ccore, (void *)dt_entry_ptr, sizeof(modem_dt_entry_t));
			break;
	    }
        dt_entry_ptr++;
	}

	if(i == dt_hdr->num_entries) {
        return SEC_ERROR;
    }

	return SEC_OK;
}

/*
 * Function name:TEEK_init.
 * Discription:Init the TEEC and get the context
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ context: context.
 * return value:
 *      @ TEEC_SUCCESS-->success, others-->failed.
 */
static s32 TEEK_init(TEEC_Session *session, TEEC_Context *context)
{
    TEEC_Result result;
    TEEC_UUID svc_uuid = TEE_SERVICE_SECBOOT;
    TEEC_Operation operation = {0};
    u8 package_name[] = "sec_boot";
    u32 root_id = 0;

    result = TEEK_InitializeContext(
            NULL,
            context);

    if(result != TEEC_SUCCESS) {
        sec_print_err("TEEK_InitializeContext failed!\n");
        result = SEC_ERROR;
        goto error;
    }

    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT);
    operation.params[2].tmpref.buffer = (void *)(&root_id);
    operation.params[2].tmpref.size = sizeof(root_id);
    operation.params[3].tmpref.buffer = (void *)(package_name);
    operation.params[3].tmpref.size = strlen(package_name) + 1;
    result = TEEK_OpenSession(
            context,
            session,
            &svc_uuid,
            TEEC_LOGIN_IDENTIFY,
            NULL,
            &operation,
            NULL);

    if (result != TEEC_SUCCESS)
    {
        sec_print_err("TEEK_OpenSession failed!\n");
        result = SEC_ERROR;
        TEEK_FinalizeContext(context);
    }

error:

    return result;
}


/*
 * Function name:reset_soc_image.
 * Discription:reset the core in sec_OS, like modem and hifi core  .
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the core to reset.
 * return value:
 *      @ TEEC_SUCCESS-->success, others-->failed.
 */
s32 reset_soc_image(TEEC_Session *session,
		  SECBOOT_IMG_TYPE  image)
{
	TEEC_Result result;
	TEEC_Operation operation;
	u32 origin;

	operation.started = 1;
	operation.cancel_flag = 0;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_NONE,
						TEEC_NONE,
						TEEC_NONE);

    operation.params[0].value.a = image; /*MODEM/HIFI*/
    result = TEEK_InvokeCommand(
                                session,
                               SECBOOT_CMD_ID_RESET_IMAGE ,
                                &operation,
                                &origin);
    if (result != TEEC_SUCCESS) {
		sec_print_err("reset  failed, result is 0x%x!\n", result);
		result = SEC_ERROR;
	}

	return result;
}

/*
 * Function name:start_soc_image.
 * Discription:start the image verification, if success, unreset the soc
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the image to verification and unreset
 *      @ run_addr: the image entry address
 * return value:
 *      @ TEEC_SUCCESS-->success, others-->failed.
 */
s32 verify_soc_image(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
                        u32 run_addr)
{
	TEEC_Result result;
	TEEC_Operation operation;
	u32 origin;

	operation.started = 1;
	operation.cancel_flag = 0;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_VALUE_INPUT,
						TEEC_NONE,
						TEEC_NONE);

     operation.params[0].value.a = image;
     operation.params[1].value.a = run_addr;
     operation.params[1].value.b = 0;/*SECBOOT_LOCKSTATE , not used currently*/
     result = TEEK_InvokeCommand(
                                    session,
                                   SECBOOT_CMD_ID_VERIFY_DATA_TYPE,
                                    &operation,
                                    &origin);
     if (result != TEEC_SUCCESS){
		sec_print_err("start  failed, result is 0x%x!\n", result);
		result = SEC_ERROR;
	}
	return result;
}



/*
 * Function name:trans_vrl_to_os.
 * Discription:transfer vrl data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the data of the image to transfer.
 *      @ buf: the buf in  kernel to transfer
 *      @ size: the size to transfer.
 * return value:
 *      @ TEEC_SUCCESS-->success, others--> failed.
 */
static s32 trans_vrl_to_os(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
		  void * buf,
		  const unsigned int size)
{
	TEEC_Result result;
	TEEC_Operation operation;
	u32 origin;

	operation.started = 1;
	operation.cancel_flag = 0;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_MEMREF_TEMP_INPUT,
						TEEC_NONE,
						TEEC_NONE);

	operation.params[0].value.a = image;
	operation.params[1].tmpref.buffer = (void *)buf;
	operation.params[1].tmpref.size = size;

	result = TEEK_InvokeCommand(
				session,
				SECBOOT_CMD_ID_COPY_VRL_TYPE,
				&operation,
				&origin);
	if (result != TEEC_SUCCESS) {
		sec_print_err("invoke failed!\n");
		result = SEC_ERROR;
	}

	return result;
}

/*
 * Function name:trans_data_to_os.
 * Discription:transfer image data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the data of the image to transfer.
 *      @ run_addr: the image entry address.
 *      @ buf: the buf in  kernel to transfer
 *      @ offset: the offset to run_addr.
 *      @ size: the size to transfer.
 * return value:
 *      @ TEEC_SUCCESS-->success, others--> failed.
 */
static s32 trans_data_to_os(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
                        u32 run_addr,
		  void * buf,
		  const unsigned int offset,
		  const unsigned int size)
{
	TEEC_Result result;
	TEEC_Operation operation;
	u32 origin;

	operation.started = 1;
	operation.cancel_flag = 0;
	operation.paramTypes = TEEC_PARAM_TYPES(
						TEEC_VALUE_INPUT,
						TEEC_VALUE_INPUT,
						TEEC_VALUE_INPUT,
						TEEC_NONE);
		
	operation.params[0].value.a = image;
	operation.params[1].value.a = run_addr;
	operation.params[1].value.b = offset;
	operation.params[2].value.a = (u32)virt_to_phys(buf);
	operation.params[2].value.b = size;

	result = TEEK_InvokeCommand(
				session,
				SECBOOT_CMD_ID_COPY_DATA_TYPE,
				&operation,
				&origin);			
	if (result != TEEC_SUCCESS) {
		sec_print_err("invoke failed!\n");
		result = SEC_ERROR;
	}

	return result;
}

/*
 * Function name:load_data_to_os.
 * Discription:cut the  image data to 1M per block, and trans them to  sec_OS.
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the data of the image to transfer.
 *      @ part_name: image's partition name. 
 *      @ run_addr: the image entry address.
 *      @ offset: the offset to run_addr.
 *      @ sizeToRead: total  size of the image.
 * return value:
 *      @ SEC_OK-->success, others--> failed.
 */
static s32 load_data_to_os(TEEC_Session *session, 
                        SECBOOT_IMG_TYPE  image,
                        char* part_name,
                        u32 run_addr,
                        u32 offset,
                        u32 sizeToRead)
{
	u32 read_bytes;
	u32 end_bytes;
	u32 copy_bytes;
	u32 timers;
	u32 i;
	s32 ret = SEC_ERROR;

	/*split the size to be read to each 64K bytes.*/
	timers = sizeToRead / SECBOOT_BUFLEN;
	if (sizeToRead % SECBOOT_BUFLEN)	
	timers = timers + 1;

	end_bytes = sizeToRead;

	/*call flash_read each time to read to memDst.*/
	for (i = 0; i < timers; i++)
	{
		if (end_bytes >= SECBOOT_BUFLEN)
			read_bytes = SECBOOT_BUFLEN;
		else
			read_bytes = end_bytes;

		if (bsp_read_bin(part_name, offset + i * SECBOOT_BUFLEN, read_bytes, (void *)SECBOOT_BUFFER)) {
			sec_print_err("%s: err: flash_read\n", __func__);
			return SEC_ERROR;
		}

		if (end_bytes >= SECBOOT_BUFLEN) {
			if (SECBOOT_BUFLEN != read_bytes) {
				sec_print_err("%s: err: SECBOOT_BUFLEN:%d != read_bytes:%d\r\n", __func__, SECBOOT_BUFLEN, read_bytes);
				return SEC_ERROR;
			}
			copy_bytes = SECBOOT_BUFLEN;
		} else {
			if (end_bytes > read_bytes) {
				sec_print_err("%s: err: end_bytes:%d!= read_bytes:%d\r\n", __func__, end_bytes, read_bytes);
				return SEC_ERROR;
			}
			copy_bytes = end_bytes;
		}

		ret = trans_data_to_os(session, image, run_addr, (void *)(SECBOOT_BUFFER), (i * SECBOOT_BUFLEN), copy_bytes);
		if (SEC_ERROR == ret)
		{
			sec_print_err("image trans to os is failed, error code 0x%x\r\n", ret);
			return SEC_ERROR;
		}

		end_bytes -= copy_bytes;
	}

	if (0 != end_bytes) {
		sec_print_err("%s: end_bytes = 0x%x\n", __func__, end_bytes);
		return SEC_ERROR;
	}

	return SEC_OK;
}

/*
 * Function name:load_modem_vrl_to_os.
 * Discription:load modem  image's VRL  data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 * return value:
 *      @ SEC_OK--> success, others--> failed.
 */
s32 load_vrl_to_os(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype)
{
#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
	s32 ret = SEC_ERROR;
	switch(ecoretype) {
	case BSP_CCORE:
	case BSP_HIFI:
		ret = load_vrl_from_partition_to_os(session, ecoretype);
		break;
	case BSP_BBE:
	case BSP_CDSP:
		ret = load_vrl_from_image_to_os(session, ecoretype);
		break;
	default:
		sec_print_err("image type is error!\n");
		return SEC_ERROR;
		break;
	}
	return ret;
#else
	return load_vrl_from_partition_to_os(session, ecoretype);
#endif
}

s32 load_vrl_from_image(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype)
{
	s32 ret = SEC_ERROR;
	char path_name[255] = {0};

	switch (ecoretype) {
	case BSP_BBE:
		strncpy(path_name, PTN_MODEM_DSP_NAME, sizeof(path_name));
		break;
	case BSP_CDSP:
		strncpy(path_name, PTN_MODEM_XDSP_NAME, sizeof(path_name));
		break;
	case BSP_CCORE_TAS:
		strncpy(path_name, PTN_MODEM_TAS_NAME, sizeof(path_name));
		break;
	case BSP_CCORE_WAS:
		strncpy(path_name, PTN_MODEM_WAS_NAME, sizeof(path_name));
		break;
	case BSP_CCORE_CAS:
		strncpy(path_name, PTN_MODEM_CAS_NAME, sizeof(path_name));
		break;
	default:
		sec_print_err("image type is error!\n");
		return SEC_ERROR;
		break;
	}
	/*get image vrl info*/
	ret = bsp_read_file((const char*) path_name, 0, VRL_SIZE,
			(void *) SECBOOT_BUFFER);
	if (ret < 0) {
		sec_print_err("fail to read the vrl of image,error code 0x%x\r\n", ret);
		return SEC_ERROR;
	}
	return SEC_OK;
}


s32 load_vrl_from_image_to_os(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype)
{
	s32 ret = SEC_ERROR;
	ret = load_vrl_from_image(session, ecoretype);
	if (ret < 0) {
		sec_print_err("fail to load_vrl_from_image,error code 0x%x\r\n", ret);
		return SEC_ERROR;
	}

	/* trans the vrl to secure os. */
	ret = trans_vrl_to_os(session,(SECBOOT_IMG_TYPE)ecoretype, (void *)SECBOOT_BUFFER, VRL_SIZE);
	if (SEC_ERROR == ret)
	{
		sec_print_err("image vrl trans to secureos is failed, error code 0x%x\r\n", ret);
		return SEC_ERROR;
	}

	return SEC_OK;
}

/*
 * Function name:load_vrl_from_partition_to_os.
 * Discription:load modem  image's VRL  data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 * return value:
 *      @ SEC_OK--> success, others--> failed.
 */
s32 load_vrl_from_partition_to_os(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype)
{
     s32 ret = SEC_ERROR;
	 int vrl_index = 0;

	 switch(ecoretype)
	 {
	 case BSP_CCORE:
		vrl_index = bsp_get_vrl_index(PTN_MODEM_NAME);
		break;
	 case BSP_HIFI:
		vrl_index = bsp_get_vrl_index(PTN_HIFI_NAME);
		break;
     case BSP_BBE:
		vrl_index = bsp_get_vrl_index(PTN_MODEM_DSP_NAME);
		break;
     case BSP_CDSP:
		vrl_index = bsp_get_vrl_index(PTN_MODEM_XDSP_NAME);
		break;
	default:
		sec_print_err("image type is error!\n");
		return SEC_ERROR;
		break;
	 }

	 if(vrl_index < 0)
	 {
		sec_print_err( "fail to find image ptn\r\n");
		return SEC_ERROR;
	 }

	/*get image vrl info*/
	ret  = bsp_read_bin((const char*)PTN_VRL_NAME, (vrl_index * VRL_SIZE), VRL_SIZE, (void *)SECBOOT_BUFFER);
	if (ret < 0)
	{
		sec_print_err( "fail to read the vrl of image,error code 0x%x\r\n", ret);
		return SEC_ERROR;
	}

	/* trans the vrl to secure os. */
	ret = trans_vrl_to_os(session,(SECBOOT_IMG_TYPE)ecoretype, (void *)SECBOOT_BUFFER, VRL_SIZE);
	if (SEC_ERROR == ret)
	{
		sec_print_err("image vrl trans to secureos is failed, error code 0x%x\r\n", ret);
		return SEC_ERROR;
	}

	return SEC_OK;
}

/*
 * Function name:load_modem_data_to_os.
 * Discription:load modem  image  data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 * return value:
 *      @ SEC_OK--> success, others--> failed.
 */
s32 load_modem_data_to_os(TEEC_Session *session)
{
	s32 ret = SEC_ERROR;
	u32 head_size = 0;
	struct image_head *header = NULL;
	const char      *image_name = PTN_MODEM_NAME;
	unsigned int bytes = 0;
#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
	int vrl_index = 0;
#endif

	head_size = sizeof(struct image_head);
	header  = (struct image_head *)kmalloc(head_size, GFP_KERNEL);
	if(NULL  == header)
	{
		sec_print_err("modem header malloc fail\n");
		goto err_out;
	}
	memset((void*)header, 0, head_size);

	/*get the elf*/
#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
	vrl_index = bsp_get_vrl_index(PTN_MODEM_NAME);
	 if(vrl_index < 0)
	 {
		sec_print_err( "fail to find image ptn\r\n");
		goto err_out;
	 }
	ret  = bsp_read_bin((const char*)PTN_VRL_NAME, (vrl_index * VRL_SIZE), VRL_SIZE, (void *)SECBOOT_BUFFER);
	memcpy((unsigned char *)header,(unsigned char *)SECBOOT_BUFFER + HEADER_IN_VRL_OFFSET ,head_size);
#else
	ret = bsp_read_bin((const char*)image_name, 0, head_size, (char *)header);
#endif
	if (ret < 0)
	{
		sec_print_err("fail to read the head of modem image\n");
		ret = SEC_ERROR;
		goto err_out;
	}

	bytes = header->image_length;
	if (bytes % 64 != 0)
		bytes = bytes + 64 - (bytes % 64);
	/*load modem data to sec os*/
#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
	ret = load_data_to_os(session, MODEM, PTN_MODEM_NAME, header->load_addr, 0, bytes);
#else
	ret = load_data_to_os(session, MODEM, PTN_MODEM_NAME, header->load_addr-head_size, 0, header->image_length+head_size);
#endif
	if(SEC_ERROR == ret)
	{
		sec_print_err("load modem data to secureos fail, error code 0x%x\r\n", ret);
		goto err_out;
	}
#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
	g_modem_addr = header->load_addr;
#else
	g_modem_addr = header->load_addr-head_size;
#endif
err_out:
	if(NULL != header)
	{
		kfree(header);
		header = NULL;
	}
	return ret;

}



s32 load_dsp_data_to_os(TEEC_Session *session)
{
#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
	return load_dsp_data_to_os_from_filesystem(session, BSP_BBE);
#else
	return load_dsp_data_to_os_from_partition(session);
#endif
}

s32 load_xdsp_data_to_os(TEEC_Session *session)
{
#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
	return load_dsp_data_to_os_from_filesystem(session, BSP_CDSP);
#else
	return load_xdsp_data_to_os_from_partition(session);
#endif
}


/*
 * Function name:load_hifi_data_to_os.
 * Discription:load hifi  image  data to sec_OS
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 * return value:
 *      @ SEC_OK--> success, others--> failed.
 */
s32 load_hifi_data_to_os(TEEC_Session *session)
{
	s32 ret = SEC_ERROR;
	u32 head_size = 0;
	struct drv_hifi_image_head *header = NULL;
	const char  *image_name = PTN_HIFI_NAME;

	head_size = sizeof(struct drv_hifi_image_head);
	header  = (struct drv_hifi_image_head *)kmalloc(head_size, GFP_KERNEL);
	if(NULL  == header)
	{
		sec_print_err("hifi header malloc fail\n");
		goto err_out;
	}
	memset((void*)header, 0, head_size);

	/*get the elf*/
	ret = bsp_read_bin((const char*)image_name, 0, head_size, (char *)header);
	if (ret < 0)
	{
		sec_print_err("fail to read the head of hifi image\n");
		ret = SEC_ERROR;
		goto err_out;
	}
	/*load hifi data to sec os*/
	ret = load_data_to_os(session, HIFI, PTN_HIFI_NAME, HIFI_RUN_ADDR-head_size, 0, header->image_size+head_size);
	if(SEC_ERROR == ret)
	{
		sec_print_err("load hifi data to secureos fail, error code 0x%x\r\n", ret);
		goto err_out;
	}
	g_hifi_addr = HIFI_RUN_ADDR-head_size;

err_out:
	if(NULL != header)
	{
		kfree(header);
		header = NULL;
	}
	return ret;
}

#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
/*
 * Function name:load_data_from_image_to_os.
 * Discription:cut the  image data to 1M per block, and trans them to  sec_OS.
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 *      @ image: the data of the image to transfer.
 *      @ part_name: image's partition name.
 *      @ run_addr: the image entry address.
 *      @ offset: the offset to run_addr.
 *      @ sizeToRead: total  size of the image.
 * return value:
 *      @ SEC_OK-->success, others--> failed.
 */
s32 load_data_from_image_to_os(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
                        char* path_name,
                        u32 run_addr,
                        u32 offset,
                        u32 sizeToRead)
{
	u32 read_bytes;
	u32 end_bytes;
	u32 copy_bytes;
	u32 timers;
	u32 i;
	s32 ret = SEC_ERROR;

	/*split the size to be read to each 64K bytes.*/
	/* TODO, length need to 64 byte aligned*/
	if (sizeToRead % 64 != 0)
		sizeToRead = sizeToRead + 64 - (sizeToRead % 64);

	timers = sizeToRead / SECBOOT_BUFLEN;
	if (sizeToRead % SECBOOT_BUFLEN)
	timers = timers + 1;

	end_bytes = sizeToRead;

	/*call flash_read each time to read to memDst.*/
	for (i = 0; i < timers; i++)
	{
		if (end_bytes >= SECBOOT_BUFLEN)
			read_bytes = SECBOOT_BUFLEN;
		else
			read_bytes = end_bytes;

		if (bsp_read_file(path_name, offset + i * SECBOOT_BUFLEN, read_bytes, (void *)SECBOOT_BUFFER)) {
			sec_print_err("%s: err: flash_read\n", __func__);
			return SEC_ERROR;
		}


		if (end_bytes >= SECBOOT_BUFLEN) {
			if (SECBOOT_BUFLEN != read_bytes) {
				sec_print_err("%s: err: SECBOOT_BUFLEN:%d != read_bytes:%d\r\n", __func__, SECBOOT_BUFLEN, read_bytes);
				return SEC_ERROR;
			}
			copy_bytes = SECBOOT_BUFLEN;
		} else {
			if (end_bytes > read_bytes) {
				sec_print_err("%s: err: end_bytes:%d!= read_bytes:%d\r\n", __func__, end_bytes, read_bytes);
				return SEC_ERROR;
			}
			copy_bytes = end_bytes;
		}

		ret = trans_data_to_os(session, image, run_addr, (void *)(SECBOOT_BUFFER), (i * SECBOOT_BUFLEN), copy_bytes);
		if (SEC_ERROR == ret)
		{
			sec_print_err("image trans to os is failed, error code 0x%x\r\n", ret);
			return SEC_ERROR;
		}

		end_bytes -= copy_bytes;
	}

	if (0 != end_bytes) {
		sec_print_err("%s: end_bytes = 0x%x\n", __func__, end_bytes);
		return SEC_ERROR;
	}

	return SEC_OK;
}

/*************************************************************
 函 数 名  : load_dsp_data_to_os_from_filesystem
 功能描述  : 从文件系统中的镜像里面读取VRL，然后读取镜像传递给安全os
 输入参数  : TEEC_Session *session, BSP_CORE_TYPE_E ecoretype
 输出参数  : 无
 返 回 值  : 成功返回0,失败返回非0
*************************************************************/
s32 load_dsp_data_to_os_from_filesystem(TEEC_Session *session, BSP_CORE_TYPE_E ecoretype)
{
	s32 ret = SEC_ERROR;
	u32 head_size = 0;
	struct image_head *header = NULL;
	unsigned int bytes = 0;

	head_size = sizeof(struct image_head);
	if(head_size != IMAGE_HEADER_SIZE)
	{
		sec_print_err("dsp head_size error! head_size = %d\n",head_size);
		return ret;
	}

	header  = (struct image_head *)kmalloc(head_size, GFP_KERNEL);
	if(NULL == header)
	{
		sec_print_err("dsp header malloc fail\n");
		return ret;
	}

	memset((void*)header, 0, head_size);

	ret = load_vrl_from_image(session, ecoretype);
	if (ret < 0) {
		sec_print_err("fail to load_vrl_from_image,error code 0x%x\r\n", ret);
		goto err_out;
	}

	memcpy(header, SECBOOT_BUFFER + HEADER_IN_VRL_OFFSET, IMAGE_HEADER_SIZE);

	bytes = header->image_length;
	if (bytes % 64 != 0)
		bytes = bytes + 64 - (bytes % 64);

	switch (ecoretype) {
	case BSP_BBE:
		/*load dsp data to sec os*/
		ret = load_data_from_image_to_os(session, DSP, PTN_MODEM_DSP_NAME, DDR_TLPHY_IMAGE_ADDR, VRL_SIZE, bytes);
		if(SEC_ERROR == ret)
		{
			sec_print_err("load dsp data to secureos fail, error code 0x%x\r\n", ret);
			goto err_out;
		}
		else
		{
			g_dsp_addr = DDR_TLPHY_IMAGE_ADDR;
			sec_print_info("load_dsp_data_to_os success!\n");
			goto err_out;
		}
		break;
	case BSP_CDSP:
		/*load dsp data to sec os*/
		ret = load_data_from_image_to_os(session, XDSP, PTN_MODEM_XDSP_NAME,
			/*DDR_CBBE_IMAGE_ADDR*/header->load_addr, VRL_SIZE, bytes);
		if(SEC_ERROR == ret)
		{
			sec_print_err("load xdsp data to secureos fail, error code 0x%x\r\n", ret);
			goto err_out;
		}
		else
		{
			g_xdsp_addr = header->load_addr;/*DDR_CBBE_IMAGE_ADDR*/
			sec_print_info("load_xdsp_data_to_os success!\n");
			goto err_out;
		}
		break;
	default:
		sec_print_err("load dsp data to from system not support, 0x%x\r\n", ecoretype);
	}
err_out:
        if(header)
        {
                kfree(header);
                header = NULL;
        }
        return ret;
}
#else
/*************************************************************
 函 数 名  : load_dsp_data_to_os_from_partition
 功能描述  : 从文件系统中的镜像里面读取VRL，然后读取镜像传递给安全os
 输入参数  : TEEC_Session *session, BSP_CORE_TYPE_E ecoretype
 输出参数  : 无
 返 回 值  : 成功返回0,失败返回非0
*************************************************************/
s32 load_xdsp_data_to_os_from_partition(TEEC_Session *session)
{
	s32 ret = SEC_ERROR;
	u32 head_size = 0;
	struct dsp_bin_header_stru *header = NULL;
	const char      *image_name = PTN_MODEM_XDSP_NAME;

	head_size = sizeof(struct dsp_bin_header_stru);
	header  = (struct dsp_bin_header_stru *)kmalloc(head_size, GFP_KERNEL);
	if(NULL  == header)
	{
		sec_print_err("dsp header malloc fail\n");
		return ret;
	}
	memset((void*)header, 0, head_size);

	/*get the elf*/
	ret = bsp_read_bin((const char*)image_name, 0, head_size, (char *)header);
	if (SEC_ERROR == ret)
	{
		sec_print_err("fail to read the head of dsp image\n");
		goto err_out;
	}

	/*load dsp data to sec os*/
	if (header->ulFileSize % 64 != 0)
	header->ulFileSize = header->ulFileSize + 64 - (header->ulFileSize % 64);

	ret = load_data_to_os(session, XDSP, PTN_MODEM_DSP_NAME, DDR_TLPHY_IMAGE_ADDR, 0, header->ulFileSize);
	if(SEC_ERROR == ret)
	{
		sec_print_err("load dsp data to secureos fail, error code 0x%x\r\n", ret);
		goto err_out;
	}
	else
	{
		g_xdsp_addr = DDR_TLPHY_IMAGE_ADDR;
		sec_print_info("load_xdsp_data_to_os success!\n");
		goto err_out;
	}

err_out:
	if(header)
	{
		kfree(header);
		header = NULL;
	}
	return ret;
}

s32 load_dsp_data_to_os_from_partition(TEEC_Session *session)
{
	s32 ret = SEC_ERROR;
	u32 head_size = 0;
	u32 img_size = 0;
	struct image_head *header = NULL;
	const char      *image_name = PTN_MODEM_DSP_NAME;

	head_size = sizeof(struct image_head);
	header  = (struct image_head *)kmalloc(head_size, GFP_KERNEL);
	if(NULL  == header)
	{
		sec_print_err("dsp header malloc fail\n");
		return ret;
	}
	memset((void*)header, 0, head_size);

	/*get the elf*/
	ret = bsp_read_bin((const char*)image_name, 0, head_size, (char *)header);
	if (SEC_ERROR == ret)
	{
		sec_print_err("fail to read the head of dsp image\n");
		goto err_out;
	}

	/*load dsp data to sec os*/
	img_size = header->image_length+head_size;
	if (img_size % 64 != 0)
	img_size = img_size + 64 - (img_size % 64);

	ret = load_data_to_os(session, DSP, PTN_MODEM_DSP_NAME, DDR_TLPHY_IMAGE_ADDR-head_size, 0, img_size);
	if(SEC_ERROR == ret)
	{
		sec_print_err("load dsp data to secureos fail, error code 0x%x\r\n", ret);
		goto err_out;
	}
	else
	{
		g_dsp_addr = DDR_TLPHY_IMAGE_ADDR-head_size;
		sec_print_info("load_dsp_data_to_os success!\n");
		goto err_out;
	}

err_out:
	if(header)
	{
		kfree(header);
		header = NULL;
	}
	return ret;
}

#endif //CONFIG_BALONG_MODEM_REMOVE_HEAD

/*
 * Function name:verify_dtb_image.
 * Discription:verify modem dtb image
 * Parameters:
 *      @ session: the bridge from unsec world to sec world.
 * return value:
 *      @ SEC_OK--> success, others--> failed.
 */
static s32 verify_dtb_image(TEEC_Session *session,
                        SECBOOT_IMG_TYPE  image,
                        u32 run_addr, u32 modem_id)
{
	s32 ret = SEC_ERROR;
	s32 offset = 0;
	int len = 0;
	u32 i = 0;
    u8 sec_id[4];
    u8 dtb_id[4];
	const struct fdt_property *property = NULL;

    sec_id[0] = MODEMID_K_BITS(modem_id);
    sec_id[1] = MODEMID_H_BITS(modem_id);
    sec_id[2] = MODEMID_M_BITS(modem_id);
    sec_id[3] = MODEMID_L_BITS(modem_id);

	ret = verify_soc_image(session, image, run_addr);
	if (SEC_OK != ret)
    {
        sec_print_err("fail to read the dtb image\n");
		return ret;
    }

    /*Check BoardID Again, incase DTB and VRL are replaced both*/
    offset = fdt_node_offset_by_compatible(phys_to_virt(run_addr), -1, CHIP_COMPITABLE_STR);
    if(offset < 0){
        sec_print_err("-----can not find %s node by compatible offset:%d\n",CHIP_COMPITABLE_STR, offset);
		return SEC_ERROR;
    }

    property = fdt_get_property(phys_to_virt(run_addr), offset, BOARDID_STR, &len);
    if(!property){
        sec_print_err("-----can not find %s \n", "hisi,boardid");
        return SEC_ERROR;
    }

    /*read boardid from dtb*/
    for(i = 0; i < 4; i++) {
        dtb_id[i] = fdt32_to_cpu(*((unsigned int *)property->data + i));
        sec_print_info("dtb_id[%d]:%x\n", i,dtb_id[i]);
    }

    if( (sec_id[0] != dtb_id[0]) || (sec_id[1] != dtb_id[1]) || (sec_id[2] != dtb_id[2]) || (sec_id[3] != dtb_id[3]) )
    {
        sec_print_err("DTB and it's VRL are replaced Both!!!! \n");
        return SEC_ERROR;
    }

	sec_print_err("success to load and verify modem dtb image\n");
	return SEC_OK;
}

s32 load_and_verify_dtb_data(TEEC_Session *session)
{
    s32 ret = SEC_ERROR;
    u32 head_size = BSP_MODEM_DTB_HEADER;
	u32 modem_id = 0;
    struct modem_dt_table_t *header = NULL;
	struct modem_dt_entry_t dt_entry_ptr = {{0}};
    const char *image_name = PTN_MODEM_DTB_NAME;

    header  = (struct modem_dt_table_t *)kmalloc(head_size, GFP_KERNEL);
    if(NULL == header)
    {
       sec_print_err("dtb header malloc fail\n");
       goto err_out;
    }
    memset((void*)header, 0, head_size);

    /*get the elf*/
    ret = bsp_read_bin((const char*)image_name, 0, head_size, (char *)header);
    if (SEC_ERROR == ret)
    {
       sec_print_err("fail to read the head of modem dtb image\n");
       ret = SEC_ERROR;
       goto err_out;
    }

	ret = get_modemid(&modem_id);
	if (SEC_OK != ret)
    {
       sec_print_err("fail to get modem id\n");
       ret = SEC_ERROR;
       goto err_out;
    }

	memset((void *)&dt_entry_ptr, 0, sizeof(dt_entry_ptr));
	ret = get_dtb_entry(modem_id, header, &dt_entry_ptr);
    if (SEC_ERROR == ret)
    {
		sec_print_err("fail to get_dtb_entry\n");
		ret = SEC_ERROR;
		goto err_out;
    }

	ret = bsp_read_bin((const char*)PTN_MODEM_DTB_NAME, dt_entry_ptr.vrl_offset, dt_entry_ptr.vrl_size, SECBOOT_BUFFER);
    if (SEC_ERROR == ret)
    {
		sec_print_err("fail to read the dtb image\n");
		ret = SEC_ERROR;
		goto err_out;
    }

	/* trans the vrl to secure os. */
	ret = trans_vrl_to_os(session, MODEM_DTB, (void *)SECBOOT_BUFFER, VRL_SIZE);
	if (SEC_ERROR == ret)
	{
		sec_print_err("image vrl trans to secureos is failed, error code 0x%x\r\n", ret);
		ret = SEC_ERROR;
        goto err_out;
	}

	/* trans the dtb data to secure os. */
	ret = load_data_to_os(session, MODEM_DTB, PTN_MODEM_DTB_NAME, DDR_MCORE_DTS_ADDR, dt_entry_ptr.dtb_offset, dt_entry_ptr.dtb_size);
    if (SEC_ERROR == ret)
    {
        sec_print_err("fail to load modem dtb image\n");
        ret = SEC_ERROR;
        goto err_out;
    }

	ret = verify_dtb_image(session, MODEM_DTB, DDR_MCORE_DTS_ADDR, modem_id);
	if (SEC_ERROR == ret)
    {
        sec_print_err("fail to verify modem dtb image\n");
        ret = SEC_ERROR;
        goto err_out;
    }

err_out:
    if (header)
    {
        kfree(header);
        header = NULL;
    }
    return ret;
}

/*
 * Function name:bsp_reset_request.
 * Discription:reset the modem/hifi in SEC_OS.
 * Parameters:
 *      @ SECBOOT_IMG_TYPE image type.
 *Called in:
 *      @ modem/hifi_reset_set
 * return value:
 *      @ SEC_OK-->success, others-->failed.
 */
int bsp_reset_request(BSP_CORE_TYPE_E ecoretype)
{
	TEEC_Session session;
	TEEC_Context context;
	s32 ret = SEC_ERROR;

	switch(ecoretype)
	{
		case BSP_CCORE:
			break;
		case BSP_HIFI:
			break;
		case BSP_BBE:
			break;
		case BSP_CDSP:
			break;
		default:
			sec_print_err("ecoretype is error!\n");
			return SEC_ERROR;
	}

	ret = TEEK_init(&session, &context);
	if(SEC_ERROR == ret)
	{
		sec_print_err("TEEK_InitializeContext failed!\n");
		return ret;
	}

	ret = reset_soc_image(&session,(SECBOOT_IMG_TYPE)ecoretype);
	if(SEC_ERROR == ret)
	{
		sec_print_err("reset_soc_image  fail!\n");
		goto err_out;
	}
	sec_print_info("success!\n");
err_out:
	TEEK_CloseSession(&session);
	TEEK_FinalizeContext(&context);

	return ret;
}

/*
 * Function name:bsp_image_seccheck.
 * Discription:local seccheck for modem/dsp.
 * Parameters:
 *      @ BSP_CORE_TYPE_E image type.
 *Called in:
 *      @ modem/dsp start
 * return value:
 *      @ SEC_OK-->success, others-->failed.
*/
int bsp_image_seccheck (BSP_CORE_TYPE_E ecoretype)
{
    s32 ret = SEC_ERROR;
    TEEC_Session session;
    TEEC_Context context;
    u32 origin;
    TEEC_Operation operation;

	if((BSP_CCORE != ecoretype) && (BSP_HIFI != ecoretype) && (BSP_BBE != ecoretype))
	{
		sec_print_err("ecoretype is error!\n");
		return SEC_ERROR;
	}

    /*TEEK_init do prepare for start SecureOs*/
    ret = TEEK_init(&session, &context);
    if(SEC_ERROR == ret)
    {
       sec_print_err("TEEK_InitializeContext failed!\n");
       return ret;
    }
	if(BSP_CCORE == ecoretype)
	{
		sec_print_err("Jasper load_and_verify_dtb_data %x!\n",ecoretype);
		ret = load_and_verify_dtb_data(&session);
		if(SEC_ERROR == ret)
		{
			sec_print_err("load_and_verify_dtb_data fail!\n");
			goto err_out;
		}
	}

	ret = load_vrl_to_os(&session, ecoretype);
	if(SEC_ERROR == ret)
	{
		sec_print_err("load_vrl_to_os fail result 0x%x!\n", ret);
		goto err_out;
	}

    operation.started = 1;
    operation.cancel_flag = 0;
    /*Configure the local checking parameters*/
    operation.paramTypes = TEEC_PARAM_TYPES(
                                         TEEC_VALUE_INPUT,
                                         TEEC_VALUE_INPUT,
                                         TEEC_NONE,
                                         TEEC_NONE);
    operation.params[0].value.a = ecoretype;
    operation.params[1].value.b = 0;/*SECBOOT_LOCKSTATE , not used currently*/
    /*TEEK_InvokeCommand do the local checking for modem*/
    ret = TEEK_InvokeCommand(
               &session,
               SECBOOT_CMD_ID_VERIFY_DATA_TYPE_LOCAL,
               &operation,
               &origin);
	if (ret != TEEC_SUCCESS) {
		sec_print_err("image local check failed, result is 0x%x!\n", ret);
		ret = SEC_ERROR;
		goto err_out;
	}
	sec_print_info("success!\n");
err_out:
	TEEK_CloseSession(&session);
	TEEK_FinalizeContext(&context);

	return ret;
}


/*
 * Function name:load_check_sec_image.
 * Discription:load the image to secureOS and the SecureOS verify it.
 * Parameters:
 *      @ void.
 *Called in:
 *      @ ccorereset_task
 * return value:
 *      @ SEC_OK-->success, others-->failed.
 */
int bsp_reset_loadimage (BSP_CORE_TYPE_E ecoretype)
{
	TEEC_Session session;
	TEEC_Context context;
	s32 ret = SEC_ERROR;
	u32 image_addr = 0;
	switch(ecoretype)
	{
		case BSP_CCORE:
			break;
		case BSP_HIFI:
			break;
		case BSP_BBE:
			break;
		case BSP_CDSP:
			break;
		case BSP_CCORE_TAS://not avail in austin, go through
		case BSP_CCORE_WAS://go through
		case BSP_CCORE_CAS://go through
		default:
			sec_print_err("ecoretype is error!\n");
			return SEC_ERROR;
	}	

	ret = TEEK_init(&session, &context);
	if(SEC_ERROR == ret)
	{
		sec_print_err("TEEK_InitializeContext failed!\n");
		return ret;
	}

	ret = reset_soc_image(&session,(SECBOOT_IMG_TYPE)ecoretype);
	if(SEC_ERROR == ret)
	{
		sec_print_err("reset_soc_image fail!\n");
		goto err_out;
	}

	if(BSP_CCORE == ecoretype)
	{
		ret = load_and_verify_dtb_data(&session);
		if(SEC_ERROR == ret)
		{
			sec_print_err("load_and_verify_dtb_data fail!\n");
			goto err_out;
		}
	}
	ret = load_vrl_to_os(&session, ecoretype);
	if(SEC_ERROR == ret)
	{
		sec_print_err("load_vrl_to_os fail!\n");
		goto err_out;
	}

	switch(ecoretype)
	{
	case BSP_CCORE:
		ret = load_modem_data_to_os(&session);
		if(SEC_ERROR == ret)
		{
			sec_print_err("load_modem_data_to_os fail!\n");
			goto err_out;
		}
		image_addr = g_modem_addr;
		break;
	case BSP_HIFI:
		ret = load_hifi_data_to_os(&session);
		if(SEC_ERROR == ret)
		{
			sec_print_err("load_hifi_data_to_os fail!\n");
			goto err_out;
		}
		image_addr = g_hifi_addr;
		break;
	case BSP_BBE:
		ret = load_dsp_data_to_os(&session);
		if(SEC_ERROR == ret)
		{
			sec_print_err("load_dsp_data_to_os fail!\n");
			goto err_out;
		}
		image_addr = g_dsp_addr;
		break;
	case BSP_CDSP:
		ret = load_xdsp_data_to_os(&session);
		if(SEC_ERROR == ret)
		{
			sec_print_err("load_xdsp_data_to_os fail!\n");
			goto err_out;
		}
		image_addr = g_xdsp_addr;
		break;
	case BSP_CCORE_TAS:// go through, not avail
	case BSP_CCORE_WAS:
	case BSP_CCORE_CAS:
	default:
			sec_print_err("ecoretype is error!\n");
			return SEC_ERROR;
	}


	/*end of trans all data, start verify, if success, unreset the SOC*/
	ret = verify_soc_image(&session,(SECBOOT_IMG_TYPE)ecoretype, image_addr);
	if(SEC_ERROR == ret)
	{
		sec_print_err("start_soc_image  fail!\n");
		goto err_out;
	}
	sec_print_info("success!\n");
err_out:
	TEEK_CloseSession(&session);
	TEEK_FinalizeContext(&context);

	return ret;
}

#endif
