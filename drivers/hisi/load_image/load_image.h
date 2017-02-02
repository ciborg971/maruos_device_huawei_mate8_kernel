

#ifndef _LOAD_IMAGE_H_
#define _LOAD_IMAGE_H_

#ifdef __cplusplus 
extern "C"
{
#endif

#define PTN_VRL_NAME               	"vrl"
#define PTN_MODEM_NAME			    "modem"
#define PTN_HIFI_NAME			    "fw_hifi"
#ifdef CONFIG_BALONG_MODEM_REMOVE_HEAD
#define PTN_MODEM_DSP_NAME			"/modem_dsp/sec_lphy.bin"
#define PTN_MODEM_XDSP_NAME			"/modem_dsp/sec_xphy_mcore.bin"
#else
#define PTN_MODEM_DSP_NAME			"modem_dsp"
#define PTN_MODEM_XDSP_NAME			"modem_dsp"
#endif
#define PTN_MODEM_TAS_NAME			"/modem_dsp/sec_tas.img"
#define PTN_MODEM_WAS_NAME			"/modem_dsp/sec_was.img"
#define PTN_MODEM_CAS_NAME			"/modem_dsp/sec_cas.img"
#define PTN_MODEM_DTB_NAME			"modem_dtb"
#define HIFI_RUN_ADDR               (0x35400000)

#define sec_print_err(fmt, ...)   (printk(KERN_ERR "[sec]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define sec_print_info(fmt, ...)   (printk(KERN_INFO "[sec]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define SEC_OK      			(0)
#define SEC_ERROR  				(-1)

#define VRL_SIZE					(0x1000)  /*VRL 4K*/
#define HIFI_SEC_MAX_NUM            32

typedef enum {
	BSP_CCORE = 0,
	BSP_HIFI,
	BSP_BBE,
	BSP_CDSP,
	BSP_CCORE_TAS,
	BSP_CCORE_WAS,
	BSP_CCORE_CAS,
	BSP_BUTT
} BSP_CORE_TYPE_E;

struct image_head
{
	char image_name[16];
	char image_version[32];

	unsigned int image_index;
	unsigned int image_length;
	unsigned int load_addr;
	unsigned int crc;
	unsigned int is_sec;

	char reserved[128 - 16 - 32 -sizeof(unsigned int) * 5];
};

struct dsp_sect_desc_stru{
	unsigned short             	  usNo;
	unsigned char                 ucTcmType;
	unsigned char                 ucLoadType;
	unsigned int                  ulFileOffset;
	unsigned int                  ulTargetAddr;
	unsigned int                  ulSectSize;
};

struct dsp_bin_header_stru{
	char                          acDescription[24];
	unsigned int                  ulFileSize;
	unsigned int                  ulSectNum;
	struct dsp_sect_desc_stru     astSect[0];
};

struct drv_hifi_image_sec {
	unsigned short						sn;
	unsigned char						type;
	unsigned char						load_attib;
	unsigned int						src_offset;
	unsigned int						des_addr;
	unsigned int						size;
};

struct drv_hifi_image_head {
	char								time_stamp[24];
	unsigned int						image_size;
	unsigned int						sections_num;
	struct drv_hifi_image_sec			sections[HIFI_SEC_MAX_NUM];
};

extern int bsp_reset_request(BSP_CORE_TYPE_E ecoretype);
extern int bsp_reset_loadimage(BSP_CORE_TYPE_E ecoretype);
extern int bsp_image_seccheck(BSP_CORE_TYPE_E ecoretype);

#ifdef __cplusplus
}
#endif
#endif

