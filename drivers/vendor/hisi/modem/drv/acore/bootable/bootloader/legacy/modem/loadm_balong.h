#ifndef _FASTBOOT_LOADM_BALONG_H_
#define _FASTBOOT_LOADM_BALONG_H_

#include <platform.h>
#include "bsp_sram.h"
#include "bsp_shared_ddr.h"
#include "product_config.h"


#define MODEM_TDS_SIZE		(0x40000)		/* 0.25 MB*/
#define MODEM_DSP_SIZE		(0x300000)		/* 3 MB*/

#define DSP_PARTITON_SIZE	(4*1024*1024)

#define LOAD_MODEM_OK_FLAG      (0xABCD5132)
#define LOAD_MODEM_ERROR_FLAG   (0xFFFFFFFF)

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

int load_modem_image(void);

int load_modem_dsp(void);

#endif
