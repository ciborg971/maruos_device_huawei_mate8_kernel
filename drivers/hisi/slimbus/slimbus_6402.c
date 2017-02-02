/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/delay.h>

#include "slimbus_device.h"
#include "csmi.h"
#include "slimbus_drv.h"
#include "slimbus.h"
#include <hisi/hilog.h>
#include <dsm/dsm_pub.h>

/*lint -e750*/
#define LOG_TAG "Slimbus_6402"

#define SLIMBUS_AUDIO_PLAYBACK_CHANNELS (2)
#define SLIMBUS_AUDIO_CAPTURE_CHANNELS	(2)
#define SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS   (4)
#define SLIMBUS_VOICE_DOWN_CHANNELS 	(2)
#define SLIMBUS_VOICE_UP_CHANNELS		(4)
#define SLIMBUS_VOICE_UP_2CH			(2)
#define SLIMBUS_IMAGE_DOWNLOAD_CHANNELS (1)
#define SLIMBUS_ECREF_CHANNELS			(2)
#define SLIMBUS_SOUND_TRIGGER_CHANNELS	(2)
#define SLIMBUS_VOICE_UP_SOUNDTRIGGER	(2)

#define SLIMBUS_CHANNELS_MAX			(4)

#define REG_VIR_ADDR_MAP(phyAddr)		 ioremap(phyAddr, sizeof(unsigned long))
#define REG_VIR_ADDR_UNMAP(virAddr) 	 iounmap(virAddr)
#define PMU_AUDIOCLK_ADDR				 (0xfff34428)

typedef struct slimbus_device_hi6402 {
	slimbus_device_t					dev;
	uint8_t 							generic_la; 			/* generic device logical address  */
	uint8_t 							voice_up_chnum; 		/* channel numbers of voice up */
	uint8_t 							audio_up_chnum; 		/* channel numbers of audio up */
	uint32_t							page_sel_addr;
	struct mutex						mutex;
}slimbus_device_hi6402_t;

slimbus_device_hi6402_t *hi6402_device;

slimbus_channel_property_t audio_playback[SLIMBUS_AUDIO_PLAYBACK_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t audio_capture[SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t voice_down[SLIMBUS_VOICE_DOWN_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t voice_up[SLIMBUS_VOICE_UP_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t img_download[SLIMBUS_IMAGE_DOWNLOAD_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t ec_ref[SLIMBUS_ECREF_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t sound_trigger[SLIMBUS_SOUND_TRIGGER_CHANNELS] = {{0,{0,},{{0,},},},};

/* channel numbers */
uint8_t chnum_table[SLIMBUS_TRACK_MAX] =
										{
											SLIMBUS_AUDIO_PLAYBACK_CHANNELS,
											SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS,
											SLIMBUS_VOICE_DOWN_CHANNELS,
											SLIMBUS_VOICE_UP_CHANNELS,
											SLIMBUS_IMAGE_DOWNLOAD_CHANNELS,
											SLIMBUS_ECREF_CHANNELS,
											SLIMBUS_SOUND_TRIGGER_CHANNELS,
										};
/* channel index */
uint32_t cn_table[SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] =
										{
											{AUDIO_PLAY_CHANNEL_LEFT, AUDIO_PLAY_CHANNEL_RIGHT},
											{AUDIO_CAPTURE_CHANNEL_LEFT, AUDIO_CAPTURE_CHANNEL_RIGHT, VOICE_UP_CHANNEL_MIC1, VOICE_UP_CHANNEL_MIC2},
											{VOICE_DOWN_CHANNEL_LEFT, VOICE_DOWN_CHANNEL_RIGHT},
											{VOICE_UP_CHANNEL_MIC1, VOICE_UP_CHANNEL_MIC2, AUDIO_CAPTURE_CHANNEL_LEFT, AUDIO_CAPTURE_CHANNEL_RIGHT},
											{IMAGE_DOWNLOAD},
											{VOICE_ECREF, AUDIO_ECREF},
											{SOUND_TRIGGER_CHANNEL_LEFT, SOUND_TRIGGER_CHANNEL_RIGHT},
										};
/* source port number */
uint8_t source_pn_table[SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] =
										{
											{AUDIO_PLAY_SOC_LEFT_PORT, AUDIO_PLAY_SOC_RIGHT_PORT},
											{AUDIO_CAPTURE_6402_LEFT_PORT, AUDIO_CAPTURE_6402_RIGHT_PORT, VOICE_UP_6402_MIC1_PORT, VOICE_UP_6402_MIC2_PORT},
											{VOICE_DOWN_SOC_LEFT_PORT, VOICE_DOWN_SOC_RIGHT_PORT},
											{VOICE_UP_6402_MIC1_PORT, VOICE_UP_6402_MIC2_PORT, AUDIO_CAPTURE_6402_LEFT_PORT, AUDIO_CAPTURE_6402_RIGHT_PORT},
											{IMAGE_DOWNLOAD_SOC_PORT},
											{VOICE_6402_ECREF_PORT, AUDIO_6402_ECREF_PORT},
											{BT_CAPTURE_6402_LEFT_PORT, BT_CAPTURE_6402_RIGHT_PORT},
										};
/* sink port number */
uint8_t sink_pn_table[SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] =
										{
											{AUDIO_PLAY_6402_LEFT_PORT, AUDIO_PLAY_6402_RIGHT_PORT},
											{AUDIO_CAPTURE_SOC_LEFT_PORT, AUDIO_CAPTURE_SOC_RIGHT_PORT, VOICE_UP_SOC_MIC1_PORT, VOICE_UP_SOC_MIC2_PORT},
											{VOICE_DOWN_6402_LEFT_PORT, VOICE_DOWN_6402_RIGHT_PORT},
											{VOICE_UP_SOC_MIC1_PORT, VOICE_UP_SOC_MIC2_PORT, AUDIO_CAPTURE_SOC_LEFT_PORT, AUDIO_CAPTURE_SOC_RIGHT_PORT},
											{IMAGE_DOWNLOAD_6402_PORT},
											{VOICE_SOC_ECREF_PORT, AUDIO_SOC_ECREF_PORT},
											{BT_CAPTURE_SOC_LEFT_PORT, BT_CAPTURE_SOC_RIGHT_PORT},
										};
/* segment length */
uint16_t sl_table[SLIMBUS_RF_MAX][SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] =
										{
											/* 24.576M */
											{
												{6, 6}, 						/* audio playback */
												{6, 6, 6, 6},					/* audio capture */
												{6, 6}, 						/* voice down */
												{6, 6, 6, 6},					/* voice up */
												{5},							/* image download */
												{4, 4}, 						/* EC_REF */
												{4,4},
											},
											/* 6.144M */
											{
												{6, 6}, 						/* audio playback */
												{4, 4}, 						/* audio capture */
												{4, 4}, 						/* voice down */
												{4, 4, 4, 4},					/* voice up */
												{5},							/* image download */
												{0},							/* voice EC_REF */
											},
										};
/* segment distribution */
uint16_t sd_table[SLIMBUS_RF_MAX][SLIMBUS_TRACK_MAX][SLIMBUS_CHANNELS_MAX] =
										{
											/* 24.576M */
											{
												{0xC94, 0xCB4}, 				/* audio playback */
												{0xCD4, 0xCF4, 0xC9A, 0xCBA},	/* audio capture */
												{0x15A, 0x17A}, 				/* voice down 8k */
												{0x1DA, 0x1FA, 0x55A, 0x57A},	/* voice up 8k */
												{0xC0B},						/* image download */
												{0xC90, 0xCB0}, 				/* EC_REF */
												{0xC28, 0xC2C}, 				/* sound trigger */
											},
											/* 6.144M */
											{
												{0xc24, 0xc2a}, 				/* audio playback */
												{0xc30, 0xc34}, 				/* audio capture */
												{0x58, 0x5c},					/* voice down 8k */
												{0x78, 0x7c, 0x458, 0x45C}, 	/* voice up 8k */
												{0xC0B},						/* image download */
												{0},							/* voice EC_REF */
											},
										};

uint16_t sd_voice_down_16k[SLIMBUS_RF_MAX][SLIMBUS_CHANNELS_MAX] =
										{
											{0xDA,	0xFA},						/* 24.576M voice down 16k*/
											{0x38,	0x3C},						/* 6.144M voice down 16k*/
										};

uint16_t sd_voice_up_16k[SLIMBUS_RF_MAX][SLIMBUS_CHANNELS_MAX] =
										{
											{0x4DA, 0x4FA, 0x8DA, 0x8FA},		/* 24.576M voice up 16k*/
											{0x438, 0x43c, 0x838, 0x83c},		/* 6.144M voice up 16k*/
										};
uint16_t sd_soundtrigger_48k[SLIMBUS_CHANNELS_MAX] =
										{0xC88, 0xC8C};

/* presence rate */
slimbus_presence_rate_t pr_table[SLIMBUS_RF_MAX][SLIMBUS_TRACK_MAX] =
										{
											{SLIMBUS_PR_48K, SLIMBUS_PR_48K,
											 SLIMBUS_PR_8K, SLIMBUS_PR_8K,
											 SLIMBUS_PR_768K, SLIMBUS_PR_48K, SLIMBUS_PR_192K},
											{SLIMBUS_PR_48K, SLIMBUS_PR_48K,
											 SLIMBUS_PR_8K, SLIMBUS_PR_8K,
											 SLIMBUS_PR_192K, SLIMBUS_PR_48K},
										};

extern void hi6402_reg_read_register(
				int  (*read_1byte)(void *pdata, unsigned int reg),
				int  (*read_4byte)(void *pdata, unsigned int reg));
extern void hi6402_reg_write_register(
				void (*write_1byte)(void *pdata, unsigned int reg, unsigned int val),
				void (*write_4byte)(void *pdata, unsigned int reg, unsigned int val));

void hi6402_param_init(slimbus_device_t *dev)
{
	slimbus_device_hi6402_t *hi6402  = (slimbus_device_hi6402_t *)dev;
	slimbus_channel_property_t	 *pchprop = NULL;
	slimbus_rf_type_t			  rf = hi6402->dev.rf;
	slimbus_transport_protocol_t  tp = SLIMBUS_TP_ISOCHRONOUS;
	int 	track_type = 0;
	uint8_t source_la = SOC_LA_GENERIC_DEVICE;
	uint8_t sink_la   = HI6402_LA_GENERIC_DEVICE;
	int 	ch		  = 0;
	int 	i		  = 0;

	for (track_type = SLIMBUS_TRACK_AUDIO_PLAY; track_type < SLIMBUS_TRACK_MAX; track_type++) {
		source_la = SOC_LA_GENERIC_DEVICE;
		sink_la   = HI6402_LA_GENERIC_DEVICE;
		tp		  = SLIMBUS_TP_ISOCHRONOUS;

		switch (track_type) {
		case SLIMBUS_TRACK_AUDIO_PLAY:
			pchprop = audio_playback;
			break;
		case SLIMBUS_TRACK_AUDIO_CAPTURE:
			pchprop = audio_capture;
			source_la = HI6402_LA_GENERIC_DEVICE;
			sink_la   = SOC_LA_GENERIC_DEVICE;
			break;
		case SLIMBUS_TRACK_VOICE_DOWN:
			pchprop = voice_down;
			break;
		case SLIMBUS_TRACK_VOICE_UP:
			pchprop = voice_up;
			source_la = HI6402_LA_GENERIC_DEVICE;
			sink_la   = SOC_LA_GENERIC_DEVICE;
			break;
		case SLIMBUS_TRACK_IMAGE_LOAD:
			pchprop = img_download;
			tp		= SLIMBUS_TP_PUSHED;
			break;
		case SLIMBUS_TRACK_ECREF:
			pchprop = ec_ref;
			source_la = HI6402_LA_GENERIC_DEVICE;
			sink_la   = SOC_LA_GENERIC_DEVICE;
			break;
		case SLIMBUS_TRACK_SOUND_TRIGGER:
			pchprop = sound_trigger;
			source_la = HI6402_LA_GENERIC_DEVICE;
			sink_la   = SOC_LA_GENERIC_DEVICE;
			break;
		default:
			pr_err("[%s:%d] track type is invalid: %d\n", __FUNCTION__, __LINE__, track_type);
			return;
		}

		for (ch = 0; ch < chnum_table[track_type]; ch++) {
			memset(pchprop, 0, sizeof(slimbus_channel_property_t));

			pchprop->cn 	   = cn_table[track_type][ch];
			pchprop->source.la = source_la;
			pchprop->source.pn = source_pn_table[track_type][ch];
			pchprop->sink_num  = 1;
			for (i = 0; i < pchprop->sink_num; i++) {
				pchprop->sinks[i].la  = sink_la;
				pchprop->sinks[i].pn  = sink_pn_table[track_type][ch];
			}
			pchprop->tp 	   = tp;
			pchprop->sd 	   = sd_table[rf][track_type][ch];
			pchprop->sl 	   = sl_table[rf][track_type][ch];
			pchprop->fl 	   = 0;
			pchprop->pr 	   = pr_table[rf][track_type];
			pchprop->af 	   = SLIMBUS_AF_NOT_APPLICABLE;
			pchprop->dt 	   = SLIMBUS_DF_NOT_INDICATED;
			pchprop->cl 	   = 0;
			if (SLIMBUS_TP_PUSHED == tp) {
				pchprop->dl    = pchprop->sl - 1;
			} else {
				pchprop->dl    = pchprop->sl;
			}
			pchprop->active    = 0;

			pchprop++;
		}
	}

	return;
}

static int hi6402_param_set(
				slimbus_device_t *dev,
				slimbus_track_type_t   track_type,
				slimbus_track_param_t *params)
{
	slimbus_device_hi6402_t *hi6402  = (slimbus_device_hi6402_t *)dev;
	slimbus_channel_property_t	 *pchprop = NULL;
	slimbus_track_type_t		  track;
	slimbus_rf_type_t			  rf	  = hi6402->dev.rf;
	int 	ch = 0;

	pr_info("[%s:%d] track type:%d, rate:%d, chnum:%d\n", __FUNCTION__, __LINE__, track_type, params->rate, params->channels);

	if ((SLIMBUS_TRACK_VOICE_DOWN == track_type) || (SLIMBUS_TRACK_VOICE_UP == track_type)) {
		track = SLIMBUS_TRACK_VOICE_DOWN;
		pchprop = &voice_down[0];

		for (ch=0; ch < chnum_table[track]; ch++) {
			if (params->rate == 8000) {
				pchprop->sd 	   = sd_table[rf][track][ch];
				pchprop->pr 	   = pr_table[rf][track];
			} else if (params->rate == 16000) {
				pchprop->sd 	   = sd_voice_down_16k[rf][ch];
				pchprop->pr 	   = SLIMBUS_PR_16K;
			} else {
				pr_err("[%s:%d] sample rate is invalid: %d\n", __FUNCTION__, __LINE__, params->rate);
			}

			pchprop++;
		}

		track = SLIMBUS_TRACK_VOICE_UP;
		pchprop = &voice_up[0];
		if (SLIMBUS_TRACK_VOICE_UP == track_type) {
			hi6402->voice_up_chnum = params->channels;
		}

		for (ch=0; ch < chnum_table[track]; ch++) {
			if (params->rate == 8000) {
				pchprop->sd 	   = sd_table[rf][track][ch];
				pchprop->pr 	   = pr_table[rf][track];
			} else if (params->rate == 16000) {
				pchprop->sd 	   = sd_voice_up_16k[rf][ch];
				pchprop->pr 	   = SLIMBUS_PR_16K;
			} else {
				pr_err("[%s:%d] sample rate is invalid: %d\n", __FUNCTION__, __LINE__, params->rate);
			}

			pchprop++;
		}
	} else if (SLIMBUS_TRACK_AUDIO_CAPTURE == track_type) {
		hi6402->audio_up_chnum = params->channels;
	} else if (SLIMBUS_TRACK_SOUND_TRIGGER == track_type) {
		track = SLIMBUS_TRACK_SOUND_TRIGGER;
		pchprop = &sound_trigger[0];
		for (ch=0; ch < chnum_table[track]; ch++) {
			if (params->rate == 192000) {
				pchprop->sd 	   = sd_table[rf][track][ch];
				pchprop->pr 	   = pr_table[rf][track];
			} else if (params->rate == 48000) {
				pchprop->sd 	   = sd_soundtrigger_48k[ch];
				pchprop->pr 	   = SLIMBUS_PR_48K;
			}
			pchprop++;
		}
	} else {
		pr_err("[%s:%d] track type is invalid: %d\n", __FUNCTION__, __LINE__, track_type);
	}

	return 0;
}

extern struct dsm_client *dsm_audio_client;
static int hi6402_element_read(
				slimbus_device_t  *dev,
				uint32_t				byte_address,
				slimbus_slice_size_t	slice_size,
				void				   *value)
{
	static int slimbus_dmd_flag = 1;
	slimbus_device_hi6402_t *hi6402 = (slimbus_device_hi6402_t *)dev;
	uint32_t reg_page = byte_address & (~0xff);
	uint8_t *paddr = (uint8_t*)&byte_address;
	uint8_t ret = 0;

	BUG_ON(slice_size >= SLIMBUS_SS_SLICE_BUT);

	mutex_lock(&hi6402_device->mutex);
	if (hi6402->page_sel_addr != reg_page) {
			ret  = slimbus_drv_element_write(hi6402->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (paddr+1));
			ret += slimbus_drv_element_write(hi6402->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (paddr+2));
			ret += slimbus_drv_element_write(hi6402->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (paddr+3));

		hi6402->page_sel_addr = reg_page;
	}
	ret += slimbus_drv_element_read(hi6402->generic_la, SLIMBUS_USER_DATA_BASE_ADDR + *paddr, slice_size, (uint8_t *)value);
	mutex_unlock(&hi6402_device->mutex);

	if (ret) {
		SLIMBUS_LIMIT_ERR("read error! slice_size=%d, addr=0x%x!\n", slice_size, byte_address);
		if (1 == slimbus_dmd_flag) {
			if (!dsm_client_ocuppy(dsm_audio_client)) {
				dsm_client_record(dsm_audio_client, "slice_size=%d, addr=0x%x\n",slice_size, byte_address);
				dsm_client_notify(dsm_audio_client, DSM_HI6402_SLIMBUS_READ_ERR);
				slimbus_dmd_flag = 0;
			}
		}
		return -EFAULT;
	}
	SLIMBUS_RECOVER_INFO("read recover, slice_size=%d, addr=%x!\n", slice_size, byte_address);

	return 0;
}

static int hi6402_element_write(
				slimbus_device_t  *dev,
				uint32_t				byte_address,
				slimbus_slice_size_t	slice_size,
				void				   *value)
{
	slimbus_device_hi6402_t *hi6402 = (slimbus_device_hi6402_t *)dev;
	uint32_t reg_page = byte_address & (~0xff);
	uint8_t *paddr = (uint8_t*)&byte_address;
	uint8_t ret = 0;

	BUG_ON(slice_size >= SLIMBUS_SS_SLICE_BUT);

	mutex_lock(&hi6402_device->mutex);
	if (hi6402->page_sel_addr != reg_page) {
			ret  = slimbus_drv_element_write(hi6402->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (paddr+1));
			ret += slimbus_drv_element_write(hi6402->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (paddr+2));
			ret += slimbus_drv_element_write(hi6402->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (paddr+3));

			hi6402->page_sel_addr = reg_page;
	}
	ret += slimbus_drv_element_write(hi6402->generic_la, (SLIMBUS_USER_DATA_BASE_ADDR + *paddr), slice_size, (uint8_t *)value);
	mutex_unlock(&hi6402_device->mutex);

	if (ret) {
		SLIMBUS_LIMIT_ERR("write error! slice_size=%d, addr=0x%x!\n", slice_size, byte_address);
		return -EFAULT;
	}
	SLIMBUS_RECOVER_INFO("write recover, slice_size=%d, addr=%x!\n", slice_size, byte_address);

	return 0;
}

unsigned int slimbus_reg_read_u32(unsigned int pAddr)
{
	unsigned int value = 0;
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	value = readl(virAddr);
	REG_VIR_ADDR_UNMAP(virAddr);

	return value;
}

int slimbus_hi6402_read_1byte(
				void				   *pdata,
				unsigned int			reg)
{
	static int value = 0;
	int retry_count = 0;
	static uint32_t info0 = 0xa1;
	static uint32_t info1 = 0xa2;
	static uint32_t info2 = 0xa3;
	static uint32_t info3 = 0xa4;

	if (hi6402_device == NULL) {
		SLIMBUS_LIMIT_ERR("hi6402_device not allocate!\n");
		return -ENXIO;
	}

	value = 0x5A;
	do {
		hi6402_element_read(&hi6402_device->dev, reg, SLIMBUS_SS_1_BYTE, &value);

		if (value == 0x5A) {
			SLIMBUS_LIMIT_INFO("SLIMbus read1byte retry: reg:%#x, val:%#x !\n", reg, value);
			retry_count++;
			mdelay(1);
		}
	} while ((value == 0x5A) && (retry_count <= 3));

	if (retry_count > 0) {
		uint32_t pmu_audioclk_val = 0;

		info0 = 0xa1;
		info1 = 0xa2;
		info2 = 0xa3;
		info3 = 0xa4;
		slimbus_drv_request_info(0x21, 0x400, SLIMBUS_SS_1_BYTE, &info0);
		slimbus_drv_request_info(0x40, 0x400, SLIMBUS_SS_1_BYTE, &info1);
		slimbus_drv_request_info(0x20, 0x400, SLIMBUS_SS_1_BYTE, &info2);
		slimbus_drv_request_info(0x41, 0x400, SLIMBUS_SS_1_BYTE, &info3);
		pmu_audioclk_val = slimbus_reg_read_u32(PMU_AUDIOCLK_ADDR);
		SLIMBUS_LIMIT_INFO("SLIMbus info: %#x, %#x, %#x, %#x ! clk: %#x \n", info0, info1, info2, info3, pmu_audioclk_val);
	}
	return value;
}
EXPORT_SYMBOL(slimbus_hi6402_read_1byte);

int slimbus_hi6402_read_4byte(
				void				   *pdata,
				unsigned int			reg)
{
	static int value = 0;
	static int valbyte = 0;
	int retry_count = 0;

	if (hi6402_device == NULL) {
		SLIMBUS_LIMIT_ERR("hi6402_device not allocate!\n");
		return -ENXIO;
	}

	value = 0x6A6A6A6A;
	valbyte = 0;
	do {
		hi6402_element_read(&hi6402_device->dev, reg, SLIMBUS_SS_4_BYTES, &value);
		hi6402_element_read(&hi6402_device->dev, 0x20007022, SLIMBUS_SS_1_BYTE, &valbyte);
		hi6402_element_read(&hi6402_device->dev, 0x20007023, SLIMBUS_SS_4_BYTES, &value);

		if (value == 0x6A6A6A6A) {
			SLIMBUS_LIMIT_INFO("SLIMbus read4byte retry: reg:%#x, val:%#x !\n", reg, value);
			retry_count++;
			mdelay(1);
		}
	} while ((value == 0x6A6A6A6A) && (retry_count <= 3));

	return value;
}
EXPORT_SYMBOL(slimbus_hi6402_read_4byte);

void slimbus_hi6402_write_1byte(
				void				   *pdata,
				unsigned int			reg,
				unsigned int			val)
{
	if (hi6402_device == NULL) {
		SLIMBUS_LIMIT_ERR("hi6402_device not allocate!\n");
		return;
	}

	hi6402_element_write(&hi6402_device->dev, reg, SLIMBUS_SS_1_BYTE, &val);
}
EXPORT_SYMBOL(slimbus_hi6402_write_1byte);

void slimbus_hi6402_write_4byte(
				void				   *pdata,
				unsigned int			reg,
				unsigned int			val)
{
	if (hi6402_device == NULL) {
		SLIMBUS_LIMIT_ERR("hi6402_device not allocate!\n");
		return;
	}

	hi6402_element_write(&hi6402_device->dev, reg, SLIMBUS_SS_4_BYTES, &val);
}
EXPORT_SYMBOL(slimbus_hi6402_write_4byte);

void slimbus_hi6402_read_pageaddr(void)
{
	static int page0 = 0;
	static int page1 = 0;
	static int page2 = 0;

	if (hi6402_device == NULL) {
		SLIMBUS_LIMIT_ERR("hi6402_device not allocate!\n");
		return;
	}

	page0 = 0xA5;
	page1 = 0xA5;
	page2 = 0xA5;
	mutex_lock(&hi6402_device->mutex);
	slimbus_drv_element_read(hi6402_device->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (uint8_t *)&page0);
	slimbus_drv_element_read(hi6402_device->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (uint8_t *)&page1);
	slimbus_drv_element_read(hi6402_device->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (uint8_t *)&page2);
	mutex_unlock(&hi6402_device->mutex);

	pr_info("[%s:%d] hi6402 page addr:%#x, page0:%#x, page1:%#x, page2:%#x !\n",
		__FUNCTION__, __LINE__, hi6402_device->page_sel_addr, page0, page1, page2);
}
EXPORT_SYMBOL(slimbus_hi6402_read_pageaddr);

static int hi6402_track_configure(
				slimbus_device_t	  *dev,
				slimbus_track_type_t		track_type,
				slimbus_track_param_t	   *params)
{
	slimbus_device_hi6402_t *hi6402 = (slimbus_device_hi6402_t *)dev;
	int ret = 0;

	switch (track_type) {
	case SLIMBUS_TRACK_AUDIO_PLAY:
		ret = slimbus_drv_track_configure(audio_playback, SLIMBUS_AUDIO_PLAYBACK_CHANNELS);
		break;
	case SLIMBUS_TRACK_AUDIO_CAPTURE:
		ret = slimbus_drv_track_configure(audio_capture, hi6402->audio_up_chnum);
		break;
	case SLIMBUS_TRACK_VOICE_DOWN:
		ret = slimbus_drv_track_configure(voice_down, SLIMBUS_VOICE_DOWN_CHANNELS);
		break;
	case SLIMBUS_TRACK_VOICE_UP:
		if (!(hi6402->voice_up_chnum)) {
			hi6402->voice_up_chnum = SLIMBUS_VOICE_UP_CHANNELS;
		}
		ret += slimbus_drv_track_configure(voice_up, hi6402->voice_up_chnum);

		break;
	case SLIMBUS_TRACK_IMAGE_LOAD:
		ret = slimbus_drv_track_configure(img_download, SLIMBUS_IMAGE_DOWNLOAD_CHANNELS);
		break;
	case SLIMBUS_TRACK_ECREF:
		ret = slimbus_drv_track_configure(ec_ref, SLIMBUS_ECREF_CHANNELS);
		break;
	case SLIMBUS_TRACK_SOUND_TRIGGER:
		ret = slimbus_drv_track_configure(sound_trigger, SLIMBUS_SOUND_TRIGGER_CHANNELS);
		ret = slimbus_drv_track_configure(voice_up, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
		break;

	default:
		ret = -EINVAL;
		pr_err("[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track_type);
		HiLOGE("audio", LOG_TAG, "[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track_type);
		break;
	}

	return ret;
}

static int hi6402_track_activate(
				slimbus_device_t	  *dev,
				slimbus_track_type_t  track_type)
{
	slimbus_device_hi6402_t *hi6402 = (slimbus_device_hi6402_t *)dev;
	int ret = 0;

	switch (track_type) {
	case SLIMBUS_TRACK_AUDIO_PLAY:
		ret = slimbus_drv_track_activate(audio_playback, SLIMBUS_AUDIO_PLAYBACK_CHANNELS);
		break;
	case SLIMBUS_TRACK_AUDIO_CAPTURE:
		ret = slimbus_drv_track_activate(audio_capture, hi6402->audio_up_chnum);
		break;
	case SLIMBUS_TRACK_VOICE_DOWN:
		ret = slimbus_drv_track_activate(voice_down, SLIMBUS_VOICE_DOWN_CHANNELS);
		break;
	case SLIMBUS_TRACK_VOICE_UP:
		ret = slimbus_drv_track_activate(voice_up, hi6402->voice_up_chnum);
		break;
	case SLIMBUS_TRACK_IMAGE_LOAD:
		ret = slimbus_drv_track_activate(img_download, SLIMBUS_IMAGE_DOWNLOAD_CHANNELS);
		break;
	case SLIMBUS_TRACK_ECREF:
		ret = slimbus_drv_track_activate(ec_ref, SLIMBUS_ECREF_CHANNELS);
		break;
	case SLIMBUS_TRACK_SOUND_TRIGGER:
		ret = slimbus_drv_track_activate(sound_trigger, SLIMBUS_SOUND_TRIGGER_CHANNELS);
		ret = slimbus_drv_track_activate(voice_up, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
		break;

	default:
		ret = -EINVAL;
		pr_err("[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track_type);
		HiLOGE("audio", LOG_TAG, "[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track_type);
		break;
	}

	return ret;
}

static int hi6402_track_deactivate(
				slimbus_device_t	  *dev,
				slimbus_track_type_t  track_type)
{
	slimbus_device_hi6402_t *hi6402 = (slimbus_device_hi6402_t *)dev;
	int ret = 0;

	switch (track_type) {
	case SLIMBUS_TRACK_AUDIO_PLAY:
		ret = slimbus_drv_track_deactivate(audio_playback, SLIMBUS_AUDIO_PLAYBACK_CHANNELS);
		break;
	case SLIMBUS_TRACK_AUDIO_CAPTURE:
		ret = slimbus_drv_track_deactivate(audio_capture, hi6402->audio_up_chnum);
		break;
	case SLIMBUS_TRACK_VOICE_DOWN:
		ret = slimbus_drv_track_deactivate(voice_down, SLIMBUS_VOICE_DOWN_CHANNELS);
		break;
	case SLIMBUS_TRACK_VOICE_UP:
		ret = slimbus_drv_track_deactivate(voice_up, hi6402->voice_up_chnum);
		break;
	case SLIMBUS_TRACK_IMAGE_LOAD:
		ret = slimbus_drv_track_deactivate(img_download, SLIMBUS_IMAGE_DOWNLOAD_CHANNELS);
		break;
	case SLIMBUS_TRACK_ECREF:
		ret = slimbus_drv_track_deactivate(ec_ref, SLIMBUS_ECREF_CHANNELS);
		break;
	case SLIMBUS_TRACK_SOUND_TRIGGER:
		ret = slimbus_drv_track_deactivate(sound_trigger, SLIMBUS_SOUND_TRIGGER_CHANNELS);
		ret = slimbus_drv_track_deactivate(voice_up, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
		break;
	default:
		ret = -EINVAL;
		pr_err("[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track_type);
		HiLOGE("audio", LOG_TAG,  "[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track_type);
		break;
	}

	return ret;
}

static int hi6402_track_remove(
				slimbus_device_t	  *dev,
				slimbus_track_type_t  track_type)
{
	slimbus_device_hi6402_t *hi6402 = (slimbus_device_hi6402_t *)dev;
	int ret = 0;

	switch (track_type) {
	case SLIMBUS_TRACK_AUDIO_PLAY:
		ret = slimbus_drv_track_remove(audio_playback, SLIMBUS_AUDIO_PLAYBACK_CHANNELS);
		break;
	case SLIMBUS_TRACK_AUDIO_CAPTURE:
		ret = slimbus_drv_track_remove(audio_capture, hi6402->audio_up_chnum);
		break;
	case SLIMBUS_TRACK_VOICE_DOWN:
		ret = slimbus_drv_track_remove(voice_down, SLIMBUS_VOICE_DOWN_CHANNELS);
		break;
	case SLIMBUS_TRACK_VOICE_UP:
		ret = slimbus_drv_track_remove(voice_up, hi6402->voice_up_chnum);
		hi6402->voice_up_chnum = SLIMBUS_VOICE_UP_2CH;
		break;
	case SLIMBUS_TRACK_IMAGE_LOAD:
		ret = slimbus_drv_track_remove(img_download, SLIMBUS_IMAGE_DOWNLOAD_CHANNELS);
		break;
	case SLIMBUS_TRACK_ECREF:
		ret = slimbus_drv_track_remove(ec_ref, SLIMBUS_ECREF_CHANNELS);
		break;
	case SLIMBUS_TRACK_SOUND_TRIGGER:
		ret = slimbus_drv_track_remove(sound_trigger, SLIMBUS_SOUND_TRIGGER_CHANNELS);
		ret = slimbus_drv_track_remove(voice_up, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
		break;
	default:
		ret = -EINVAL;
		pr_err("[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track_type);
		HiLOGE("audio", LOG_TAG, "[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track_type);
		break;
	}

	return ret;
}

static int hi6402_switch_framer (
				slimbus_device_type_t	framer_type,
				slimbus_bus_config_t   *bus_config)
{
	int ret = 0;
	uint8_t la;

	la = slimbus_drv_get_framerla(framer_type);
	if (la == 0) {
		pr_err("[%s:%d] invalid la:%d framer_type:%#x \n", __FUNCTION__, __LINE__, la, framer_type);
		return -EINVAL;
	}
	if (hi6402_device->dev.rf == SLIMBUS_RF_6144) {
		if (framer_type == SLIMBUS_DEVICE_HI6402) {
			ret = slimbus_drv_switch_framer(la, 4, 18, bus_config);
		} else if (framer_type == SLIMBUS_DEVICE_SOC) {
			ret = slimbus_drv_switch_framer(la, 17, 3, bus_config);
		}
	} else if (hi6402_device->dev.rf == SLIMBUS_RF_24576) {
		ret = slimbus_drv_switch_framer(la, 4, 3, bus_config);
	}

	return ret;
}

static int hi6402_pause_clock(
				slimbus_restart_time_t newrestarttime) {
	int ret = 0;

	ret = slimbus_drv_pause_clock(newrestarttime);

	return ret;
}

/*
 * create hi6402 slimbus device
 * @device, pointer to created instance
 *
 * return 0, if success
 */
int create_hi6402_slimbus_device(struct platform_device *pdev, slimbus_device_t **device)
{
	slimbus_device_hi6402_t *hi6402_dev = NULL;
	const char *bustype = NULL;
	int   ret = 0;

	hi6402_dev = kmalloc(sizeof(struct slimbus_device_hi6402), GFP_KERNEL);
	if (!hi6402_dev) {
		pr_info("[%s:%d] malloc slimbus failed!\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}
	memset(hi6402_dev, 0, sizeof(struct slimbus_device_hi6402));

	hi6402_dev->dev.element_read		= hi6402_element_read;
	hi6402_dev->dev.element_write		= hi6402_element_write;
	hi6402_dev->dev.track_configure 	= hi6402_track_configure;
	hi6402_dev->dev.track_activate		= hi6402_track_activate;
	hi6402_dev->dev.track_deactivate	= hi6402_track_deactivate;
	hi6402_dev->dev.track_remove		= hi6402_track_remove;
	hi6402_dev->dev.switch_framer		= hi6402_switch_framer;
	hi6402_dev->dev.pause_clock 		= hi6402_pause_clock;
	hi6402_dev->dev.param_set			= hi6402_param_set;

	hi6402_dev->generic_la		= HI6402_LA_GENERIC_DEVICE;
	hi6402_dev->voice_up_chnum	= SLIMBUS_VOICE_UP_2CH;;
	hi6402_dev->audio_up_chnum	= SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS;//default is 4mic
	hi6402_dev->page_sel_addr	= 1;

	*device = &(hi6402_dev->dev);
	hi6402_device = hi6402_dev;

	ret = of_property_read_string(pdev->dev.of_node, "slimbus-ssi-sel", &bustype);
	if(ret)
	{
		pr_info("[%s:%d] of_property_read_string error!bus type:%s!,ret:%d\n", __FUNCTION__, __LINE__, bustype, ret);
		return -EFAULT;
	}

	pr_info("[%s:%d] bus type:%s!\n", __FUNCTION__, __LINE__, bustype);

	if (!strcmp(bustype, "slimbus")) {
		pr_info("[%s:%d] register slimbus read/write function!\n", __FUNCTION__, __LINE__);
		hi6402_reg_read_register(slimbus_hi6402_read_1byte, slimbus_hi6402_read_4byte);
		hi6402_reg_write_register(slimbus_hi6402_write_1byte, slimbus_hi6402_write_4byte);
	} else if (!strcmp(bustype, "ssi")) {
		pr_info("[%s:%d] ssi interface!\n", __FUNCTION__, __LINE__);
	} else {
		pr_err("[%s:%d] interface error!\n", __FUNCTION__, __LINE__);
		HiLOGE("audio", LOG_TAG,  "[%s:%d] interface error!\n", __FUNCTION__, __LINE__);
	}

	mutex_init(&hi6402_device->mutex);

	return 0;
}

int release_hi6402_slimbus_device(slimbus_device_t *device)
{
	struct slimbus_device_hi6402 *hi6402 = (struct slimbus_device_hi6402 *)device;
	if (hi6402 != NULL) {
		mutex_destroy(&(hi6402->mutex));
		kfree(hi6402);
		hi6402 = NULL;
	}

	return 0;
}

