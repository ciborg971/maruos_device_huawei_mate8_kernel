/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hi6xxx_temp_cfg.h
  �� �� ��   : ����
  ��    ��   : liuyi 
  ��������   : 2014��11��3��
  ����޸�   :
  ��������   : ����v8 hkadc ���ö�١��ṹ��
  ע������   ��������������������������
               ���ļ�����������CP�ļ��ĸ���
			   vendor\hisi\include\drv\common\mdrv_temp_cfg.h
			   vendor\hisi\include\drv\common\mdrv_hkadc_common.h
			   �޸ı��ļ�ʱע��ͬ���޸�
			   ������������������������

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __HI6XXX_TEMP_CFG__
#define __HI6XXX_TEMP_CFG__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*mdrv_temp_cfg.h begin*/
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*����hkadc����ͨ����*/
typedef enum hkadcChan
{
    HKADC_CHAN_INVALID = -1,
    HKADC_CHAN_0 = 0x00,
    HKADC_CHAN_1,
    HKADC_CHAN_2,
    HKADC_CHAN_3,
    HKADC_CHAN_4,
    HKADC_CHAN_5,
    HKADC_CHAN_6,
    HKADC_CHAN_7,
    HKADC_CHAN_8,
	HKADC_CHAN_9,
	HKADC_CHAN_10,
    HKADC_CHAN_11,
	HKADC_CHAN_12,

    HKADC_CHAN_MAX
}HKADCCHANNUM;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
struct drv_hkadc_map
{
    unsigned int logic_chan;
    unsigned int phy_chan;
    unsigned int nv_id;
    unsigned int nv_len;
    unsigned int modem_id;
    char * name;
};

/* �¶�������ṹ */
typedef struct hkadc_chan_out
{
    unsigned short volt_l;    /* ���ص�HKADC��ѹֵ����λ:���� */
    unsigned short volt_r;   /* ���ص�HKADC��ѹֵȡ�� */
    short          temp_l;     /* ���ص��¶�ֵ����λ:���϶� */
    short          temp_r;    /* ���ص��¶�ֵȡ�� */
}DRV_CHANNEL_OUTPUT;

/* �¶ȵ�ѹ��Ӧ��ṹ */
typedef struct hkadc_tem_value
{
    short   temp;             /* �¶ȵ㣬��λ:���϶� */
    unsigned short volt;      /* ��ѹ�㣬��λ:���� */
}TEM_VOLT_TABLE;

/* �������bit�ṹ */
typedef struct hkadc_out_config
{
   unsigned int out_prop:2;
   unsigned int out_wake:1;
   unsigned int out_vol_temp:1;
   unsigned int out_reserv1:4;
   unsigned int out_acore:1;
   unsigned int out_ccore:1;
   unsigned int out_reserv2:22;
} OUT_PROP_CONFIG;

/* �¶��������ṹ */
typedef struct hkadc_chan_config
{
    union
    {
        unsigned int out_config;       /* bit0-bit1 0:����� 1:������� 2:ѭ����� */
                                       /* bit2 1:������� 0:�ǻ������ */
                                       /* bit3: 0:ֻ�����ѹ 1:��ѹ�¶Ⱦ���� */
                                       /* bit8: A����� */
                                       /* bit9: C����� */
        struct hkadc_out_config bit_out_config;
    } outcfg;

    unsigned int have_config;
    unsigned short out_peroid;     /* ѭ�����ʱ��ѭ�����ڣ���λ:�� */
    unsigned short temp_data_len;  /* �¶�ת������ */
    struct hkadc_tem_value temp_table[32]; /* �¶�ת����ʵ�ʳ��Ȳμ�temp_data_len */
} DRV_CHANNEL_CONFIG;

/* ϵͳ�ŵ��¶ȱ������ýṹ */
typedef struct sys_temp_cfg
{
    unsigned short enable;       /* bit0:���±���ʹ�� bit1:���±���ʹ�� 1 ʹ�� 0 �ر�*/
    unsigned short hkadc_id;      /* ϵͳ�ŵ��¶ȱ�����hkadcͨ��ID */
    unsigned short high_thres;     /* ϵͳ�ŵ���±����ĵ�ѹ��ֵ ���¶�Խ�ߣ���ѹԽ��*/
    unsigned short high_count;    /* ϵͳ�ŵ���±����������ޣ����˺�ϵͳ�ػ� */
    unsigned short low_thres;      /* ϵͳ�ŵ���±����ĵ�ѹ��ֵ ���¶�Խ�ͣ���ѹԽ��*/
    unsigned short low_count;     /* ϵͳ�ŵ���±����������ޣ����˺�ϵͳ�ػ� */
    unsigned int   reserved[2];   /*����*/
} DRV_SYS_TEMP_PRO;

struct hkadc_nv_config
{
    unsigned int outconfig;         /* bit0-bit1 0:����� 1:������� 2:ѭ����� */
                                       /* bit2 1:������� 0:�ǻ������ */
                                       /* bit3: 0:ֻ�����ѹ 1:��ѹ�¶Ⱦ���� */
                                       /* bit8: A����� */
                                       /* bit9: C����� */
    unsigned short outperiod;          /* ѭ�����ʱ��ѭ�����ڣ���λ:�� */
    unsigned short convertlistlen;     /* �¶�ת������ */
    unsigned int   reserved[2];        /* �¶�ת����ʵ�ʳ��Ȳμ�usTempDataLen */
};


typedef struct thermal_data_area
{
    unsigned int       magic_start;    /* ������ʼMagic Code 0x5A5A5A5A*/
    struct hkadc_chan_out chan_out[HKADC_CHAN_MAX];  /* ��ͨ���������,0x4��ʼ*/ /*monan:16 �Ƿ��ΪHKADC_CHAN_MAX ?*/
    struct hkadc_chan_config chan_cfg[HKADC_CHAN_MAX];  /* ��ͨ���������� */
    struct sys_temp_cfg   sys_temp_cfg;    /* ϵͳ�ŵ��±����� */
    unsigned int       hw_ver_id;       /* �汾ID */
    unsigned char     phy_tbl[32];  /*����ͨ��->�߼�ͨ����ӳ���ϵ*/
    unsigned int       debug_flag;     /* ���⿪�� */
    unsigned short     adc_value[HKADC_CHAN_MAX];
    unsigned short     acpu_temp;
    unsigned short     gpu_temp;
    unsigned int       last_slice;     /*A��M��ͬʱ��HKADC��Ҫ��֤�������ζ�HKADC�ļ������1���룬ͨ�������¼��֤A��M��ȡ�ļ��*/
    unsigned int       magic_end;      /* ��������Magic Code 0x5A5A5A5A*/
} DRV_HKADC_DATA_AREA;
/*mdrv_temp_cfg.h end*/

/*mdrv_hkadc_common.h begin*/
/*HKADC��ʱת��ģʽ*/
typedef enum tagHKADC_CONV_MODE_E
{
    HKADC_CONV_DELAY =0,
    HKADC_CONV_NO_DELAY,
    HKADC_CONV_BUTT
}HKADC_CONV_MODE_E;

/*HKADC�¶ȼ������*/
typedef enum HKADC_TEMP_PROTECT_E
{
    HKADC_TEMP_TOP = 0,
    HKADC_TEMP_BATTERY = HKADC_TEMP_TOP,     /*0*/
    HKADC_TEMP_PA0,                          /*1*/
    HKADC_TEMP_PA1,                          /*2*/
    HKADC_TEMP_DCXO0,                        /*3*/
    HKADC_TEMP_DCXO0_LOW,                    /*4*/
    HKADC_TEMP_DCXO1,                        /*5*/
    HKADC_TEMP_DCXO1_LOW,                    /*6*/
    HKADC_TEMP_LCD,                          /*7*/
    HKADC_TEMP_SIM_CARD,                     /*8*/
    HKADC_TEMP_SYSTEMH,                      /*9*/
    HKADC_TEMP_SYSTEML,                      /*10*/
    HKADC_TEMP_BATT_ID,                      /*11*/
    HKADC_TEMP_CAMERA0_ID,                   /*12*/
    HKADC_TEMP_CAMERA1_ID,                   /*13*/
    HKADC_TEMP_CODEC,                        /*14*/
    HKADC_TEMP_CHARGER_ID,                   /*15*/
    HKADC_TEMP_BUTT
}HKADC_TEMP_PROTECT_E;

/*mdrv_hkadc_common.h end*/

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

