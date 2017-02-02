/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : DspInterface.h
  �� �� ��   : ����
  ��    ��   : ���� 46160
  ��������   : 2008��7��17��
  ����޸�   :
  ��������   : Э��ջ��DSP֮���ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��7��17��
    ��    ��   : ���� 46160
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DSPINTERFACE_H__
#define __DSPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/
#include "vos.h"

/******************************************************************************
 2 �궨��
******************************************************************************/
#define CPHY_MOD_ID_WCDMA                    0x00
#define CPHY_MOD_ID_GSMGPRS                  0x01
#define CPHY_MOD_ID_MP3_ENCODE               0x10
#define CPHY_MOD_ID_MP3_DECODE               0x11
#define CPHY_MOD_ID_WMA                      0x12
#define CPHY_MOD_ID_AAC                      0x13
#define CPHY_MOD_ID_AMR_EFR_FR               0x14
#define CPHY_MOD_ID_HR                       0x15
#define CPHY_MOD_ID_EFR                      0x16
#define CPHY_MOD_ID_FR                       0x17
#define CPHY_MOD_ID_VOMATE                   0x18

#define CPHY_INFO_NUM_MAX                    12

#define DSP_REG_ACTUAL_ADDR(base, offset)   (((unsigned long)base)+(offset))

#define BIT_N(num)                          ( 0x01L << ( num ) )

#define SHPA_LDF_BUFFER_SIZE                2048

/* unit is K 16bit */
#define ZSP_ITCM_LEN                        192

/* unit is K 16bit */
#define ZSP_DTCM_LEN                        160


/* the real size of mailbox on physical address */
#define PP_MAILBOX_REAL_SIZE                2048

/* the real size of mailbox on physical address */
#define NPP_MAILBOX_REAL_SIZE               1024

#define ZSP_UP_MAILBOX_MAX_SIZE             4096

/******************************************************************************/
/* NMI����  */
/******************************************************************************/
#define SOC_SC_NMI_INT_LEVEL                        9           /*ARM����DSP�ж�λ*/
#define DSP_NMI_BIT                                 0           /*����ZSP NMI�ж�*/

#define ZSP_NMI_INT_TYPE_DRX                        0x02        /* DRX�ڼ�ʹ�� */
#define ZSP_NMI_INT_TYPE_LDF                        0x04        /* ��¼LDF�ļ� */
#define ZSP_NMI_INT_TYPE_HALT                       0x08        /* ����DSP��������ģʽʹ�� */
#define ZSP_NMI_INT_TYPE_INIT                       0x10        /* ����DSP�����ϵ��ʼ�� */
#define ZSP_NMI_INT_TYPE_SLAVE                      0x20        /* ���ڴ�ģ˯���»��� */

#define ZSP_NMI_INT_LDF_REG1_VALUE                  0x5A5A5A5A
#define ZSP_NMI_INT_LDF_REG2_VALUE                  0xA5A5A5A5

/* ZSP_SLEEP_TYPE_ADDR��16����ȡֵ��Χ:ZSP˯���������� */
#define ZSP_SLEEP_INIT                              0x00010000  /* ��ʱ�ϵ�����ģʽ,��ARM��ʼ����� */
#define ZSP_SLEEP_DRX                               0x00020000  /* ��DRX������˯�� */
#define ZSP_SLEEP_FLYMODE                           0x00040000  /* �����ģʽ/�����͹��Ķ�����˯�� */
/* ZSP_SLEEP_TYPE_ADDR��16����ȡֵ��Χ:ZSP����˯������Ļ��ѷ�ʽ */
#define ZSP_SLEEP_NORMAL                            0x00000000  /* DRX��ͨ˯��,��ҪNMI�жϻ��� */
#define ZSP_SLEEP_RESET                             0x00000001  /* DRX�����µ��˯��,��Ҫ�⸴λ���� */

/*������ZSP_IPC_HALT_INT_TYPE��ַ������ȡֵ*/
#define ZSP_HALT_BACKUP_REG                         0
#define ZSP_HALT_NO_BACKUP_REG                      1
#define ZSP_HALT_INVALID_REG                        0x77
/******************************************************************************/
/* IPC�жϷ���� */
/******************************************************************************/
/* ARM->DSP */
#define GHPA_IMI_INT_MASKBIT                        2           /*NPP*/
#define DSP_USB_START_BIT                           3           /*SD����д��ʼ*/
#define DSP_USB_STOP_BIT                            4           /*SD����дֹͣ*/
#define DSP_ANTEN_EXIST_BIT                         5           /*������*/
#define DSP_ANTEN_NOEXIST_BIT                       6           /*������*/
#define SHPA_IMI_INT_BIT_PA_TEMP_BIT                BIT_N(12)   /*�·�PA�¶�*/
#define BBP_MASTER_READY_BIT                        13          /*֪ͨDSP��BBP MASTER����˯��*/
#define SHPA_IMI_INT_MASKBIT                        14          /*����DSP*/
#define SHPA_HALT_IMI_INT_MASKBIT                   15          /*֪ͨDSP����HALT*/

/* DSP->ARM */
#define SHPA_IMI_INT_BIT_UPA_STATUS_IND_BIT         BIT_N(1)    /*W UPAҪ���ж�*/
#define GHPA_IMI_INT_BIT_GHPA_NPP_BIT               BIT_N(2)    /*NPP*/
#define SHPA_IMI_INT_BIT_DDR_BEGIN_BIT              BIT_N(3)    /*DSP����ARM DDR*/
#define SHPA_IMI_INT_BIT_DDR_END_BIT                BIT_N(4)    /*����ARM˯��*/
#define SHPA_IMI_INT_BIT_R99_BIT                    BIT_N(5)    /*��ȡW ��������������*/
#define SHPA_IMI_INT_BIT_PP_HALT_BIT                BIT_N(6)    /*G HALT�жϣ�����PP����������*/
#define SHPA_IMI_INT_BIT_MAC_HALT_BIT               BIT_N(7)	/*����������������*/
#define SHPA_IMI_INT_BIT_R99_HALT_BIT               BIT_N(8)    /*W HALT�жϣ���������������������*/
#define SHPA_IMI_INT_BIT_RFA_CONNECT_BIT            BIT_N(9)    /*DSP��������̬*/
#define GHPA_IMI_INT_BIT_FORCE_WAKE_BIT             BIT_N(10)   /*GDSPʹ���˴�bitλ*/
#define SHPA_IMI_INT_BIT_RFA_MONITOR_BIT            BIT_N(11)   /*DSP����IDLE̬*/
#define SHPA_IMI_INT_BIT_SHPA_ACTIVE_BIT            BIT_N(12)   /*�⸴λDSP�ظ�*/
#define SHPA_IMI_INT_BIT_SLEEP_HALT_BIT             BIT_N(13)   /*W HALT�ж�*/
#define SHPA_IMI_INT_BIT_SHPA_SWAP_BIT              BIT_N(14)   /*����DSP�ظ�*/
#define GHPA_IMI_INT_BIT_SLEEP_HALT_BIT             BIT_N(15)   /*G HALT�ж�*/
#define SHPA_IMI_INT_BIT_LOW_POWER_HALT_BIT         BIT_N(16)   /* ��ģ֪ͨARM,DSP����˯�� */
#define SHPA_IMI_INT_BIT_WAKE_LTE_BIT               BIT_N(17)   /* ��ģ֪ͨARM,����LDSP */
#define SHPA_IMI_INT_BIT_WAKE_TD_BIT                BIT_N(18)   /* ��ģ֪ͨARM,����TDSP */
#define SHPA_IMI_INT_BIT_DPA_RPT_BIT                BIT_N(19)   /* DPA�ϱ��жϸ�TTF */




/****************************************************************************
 *                   ZSPʹ��AHB�����еĵ�ַ�Ļ���                           *
 *                                                                          *
 ****************************************************************************/

/* ˵�� 1:��ͼ�е�ַ��λΪbyte
        2:AHB�����ܵĿռ��СΪ32Kbyte

              ----------------------------------- <---------- 0x0000
              | GSM DRX ����(��PS�нӿ����)    |
               ---------------------------------  <---------- 0x0020
              | ��������(��PS�нӿ����)        |
              |                                 |
               ---------------------------------  <---------- 0x01B0
              | NV���ơ�������Ϣ�޸Ĵ���,ARM    |
              | ������ַ                        |
               ---------------------------------  <---------- 0x01D0
              |                                 |
              |         AHB�����·�����         |
              |                                 |
               ---------------------------------  <---------- 0x2710
              |                                 |
              |         R99����������           |
              |        (��PS�нӿ����)         |
              |                                 |
               ---------------------------------  <---------- 0x3AD0
              |                                 |
              |          DRX �������           |
               ---------------------------------  <---------- 0x3BFC
              |                                 |
              |         AHB�����Ϸ�����         |
              |                                 |
              |                                 |
               ---------------------------------  <---------- 0x7D70
              |     DSP����ռ䵵���ϱ�         |
              |     (WDSP��PS�нӿ����)        |
               ---------------------------------  <---------- 0x7E00
              |     (GDSP��PS�нӿ����)        |
               ---------------------------------  <---------- 0x7F00
              |   R5��������DMA������ַ         |
               ---------------------------------  <---------- 0x7F20
              |   R5��������(��PS�нӿ����)    |
               ---------------------------------  <---------- 0x7F3C
              |   APC��DMA���Ƽ�����ַ          |
               ---------------------------------  <---------- 0x7F8C
              |                                 |
              |                                 |
              |   AHB����DMA���Ƽ�����ַ        |
              |                                 |
              |                                 |
              ----------------------------------- <---------- 0x8000  */

/*=========================== ��������ʹ����ص�ַ ===========================*/
/* NMI INT Type: 0x01 -- wakeup WDSP;0x02 -- wakeup GDSP;0x04 -- LDF function */

 /* NMI�жϹ����б�Ĵ���:0x01-����W,0x02-����G,0x04-��λDSP */
#define ZSP_NMI_INT_TYPE_REG            DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0020)

/* NMI�ж�״̬�б�Ĵ���1 */
#define ZSP_NMI_INT_LDF_REG1            DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0024)

/* NMI�ж�״̬�б�Ĵ���2 */
#define ZSP_NMI_INT_LDF_REG2            DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0028)

/*0x0: ��ʼ���Ĵ���, 0x1: ����ʼ���Ĵ���*/
#define ZSP_IPC_HALT_INT_TYPE           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x002c)

/* 1)DSP˯�����͵�ַ����,ȡֵ��Χ�μ�ZSP_SLEEP_*�ĺ궨�� */
/* 2)��16bit��ʾ˯�߳���,����ZSP_SLEEP_INIT,ZSP_SLEEP_DRX,ZSP_SLEEP_FLYMODE;
     ��16bit��ʾZSP˯�ߵķ�ʽ,����ZSP_SLEEP_NORMAL,ZSP_SLEEP_RESET */
/* 3)�״��ϵ���OAM��ʼ����(ZSP_SLEEP_INIT|ZSP_SLEEP_NORMAL) */
#define ZSP_SLEEP_TYPE_ADDR             DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0030)

/*����*/
#define ZSP_NMI_INT_LDF_REGRSV2         DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x005C)



/*============================AHB OM���� ������ַ====================*/
#define ZSP_OM_MAIL_BOX_LOCK_ADDR       DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x01C8)


/*=================����ģʽ�������͹���״̬��֪ARM�Ƿ��Ѿ�˯��================*/
#define ZSP_IPC_HALT_STATUS_ADDR        DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x01CC)


/*============================AHB�����·������ַ:ARM->DSP====================*/

/* ARM�·���Ϣ��WDSP ���������С */
#define R99_DL_MAILBOX_REAL_SIZE        (9536)

/* AHB����ӿ�*/
#define R99_ARM2DSP_BASE_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x01D0)

#define NPP_UL_MAILBOX_REAL_SIZE        4096
#define NPP_DSP2ARM_BASE_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x1400)

#define NPP_DL_MAILBOX_REAL_SIZE        4096
#define NPP_ARM2DSP_BASE_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0400)


/*======================R99�������ַ(WPHY-TTF�ӿ�)========================*/

/* R99�û����������ַ,R99�û�������λ��AHB RAM�� */
#define ARM_DSP_R99_DATA_BASE_ADDR      DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x2710)


/*=========================== ��������(����DRX�����Ϣ)=======================*/
#define ZSP_DRX_INFO_BEGIN_ADDR         DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x3AD0)
#define ZSP_DRX_INFO_END_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x3BFC)


/*============================AHB�����ϱ������ַ:DSP->ARM====================*/

/* DSP �ϱ���Ϣ�� ARM ���������С */
#define R99_UL_MAILBOX_REAL_SIZE        (16752)

/* AHB����ӿ�*/
#define R99_DSP2ARM_BASE_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x3C00)

#define PP_DL_MAILBOX_REAL_SIZE          4096
#define PP_ARM2DSP_BASE_ADDR             DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x4000)

#define PP_UL_MAILBOX_REAL_SIZE          8192
#define PP_DSP2ARM_BASE_ADDR             DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x5000)

/*===========================DSP�ڲ�������ʼ��ַ�ϱ�ram========================*/

/* R5�û��������Ϣ����ַ,R5�û��������Ϣ����λ��AHB������ */
#define ARM_DSP_R5_R7_SHARE_MEM_HEAD_CTRL_BASE_ADDR         DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x7F20)

/* R6�û��������Ϣ����ַ,R6�û��������Ϣ����λ��ZSP TCM�� */
/* �˵�ַ���ڲ�ѯR6�û��������Ϣ����ַ, ��ΪFPGA��UPA PHY-MAC�����ַ��ȡ��ʽ�ı������ */
#define ARM_DSP_R6_SHARE_MEM_CTRL_INQUIRE_ADDR      DSP_REG_ACTUAL_ADDR(ZSP_DTCM_BASE_ADDR, 0x0000)


/* R7�û��������Ϣ����ַ,R5�û��������Ϣ����λ��AHB������ */
#define ARM_DSP_R5_R7_SHARE_MEM_DATA_CTRL_BASE_ADDR         DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x7F30)


/* AHB����DMA���Ƽ�����ַ  */
#define AHB_MAIL_DMA_LLI_PARA_LOW_ADDR          ((PHY_UINT32)0x7F90)

/* AHB����DMA���Ƽ�����ַ,Gģʹ��, 0x7000 -  0x7500 ΪDMA������ַ��ÿ��DMAͨ�� 40*32bit */
#define UCOM_AHB_DMA_LLI_START_ADDR             ((PHY_UINT32)0x2800)

/****************************************************************************
 *                   ZSP ITCM������Ļ���                                 *
 *                                                                          *
 ****************************************************************************/


/****************************************************************************
 *                   ZSP DTCM������Ļ���                                 *
 *                                                                          *
 ****************************************************************************/


/*===================================APM����==================================*/


#define DSP_SHARE_MEMORY_SINGLE_SPACE       0x2A


/* APM������ز��֣�DSP�ɶ�ARM����д */
#define APM_DSP_READABLE       	            (0x7788)
/* APM������ز��֣�DSP���ɶ�ARM��д */
#define APM_ARM_WRITABLE                    (0x99AA)
/*==================================GDSPԭ������==============================*/

/*OM mailbox physical address*/
#define OM_MAILBOX_BASE_ADDR                DSP_REG_ACTUAL_ADDR(ZSP_DTCM_BASE_ADDR, 0x6c30)





/*================================WPHY����������ص�ַ========================*/

/* 0x1210 ~ 0x121F: total 16 byte */
#define ZSP_G_INT_REG                       DSP_REG_ACTUAL_ADDR(GBBP_BASE_ADDR,0x1210) /*0x20211210
 */

/* 0x0000 ~ 0x003F: total 64 byte */
#define ZSP_W_INT_REG                       DSP_REG_ACTUAL_ADDR(WBBP_BASE_ADDR,0x0000) /*0x20200000
 */

/* 0x0000 ~ 0x1FFFF: total (128*1024) byte */
#define BBP_ALL_REG                         DSP_REG_ACTUAL_ADDR(WBBP_BASE_ADDR,0x0000) /*0x20200000
 */

/* 0x1100 ~ 0x112F: total 48 byte */
#define ZSP_W_DRX_REG1                      DSP_REG_ACTUAL_ADDR(WDRX_BBP_BASE_ADDR,0x1100) /*x20221100
 */

/* 0x1170 ~ 0x1177: total 8 byte */
#define ZSP_W_DRX_REG2                      DSP_REG_ACTUAL_ADDR(WDRX_BBP_BASE_ADDR,0x1170) /*0x20221170
 */

/* 0x1160 ~ 0x1163: total 4 byte */
#define ZSP_W_DRX_REG3                      DSP_REG_ACTUAL_ADDR(WDRX_BBP_BASE_ADDR,0x1160) /*0x20221160
 */

/* 0x10A8 ~ 0x10AB: tatal 4 byte */
#define ZSP_W_SYS_CLK_CTRL_REG1             DSP_REG_ACTUAL_ADDR(WBBP_BASE_ADDR,0x10a8) /*0x202010A8
 */

/* 0x8238 ~ 0x823B: tatal 4 byte */
#define ZSP_W_SYS_CLK_CTRL_REG2             DSP_REG_ACTUAL_ADDR(WBBP_BASE_ADDR,0x8238) /*0x20208238
 */

/* 0x01C0 ~ 0x01D3: total 20 byte */
#define ZSP_DMA_CHANNEL6_STATUS_REG         DSP_REG_ACTUAL_ADDR(DMAC_BASE_ADDR,0x01c0) /*0x203801C0
 */


/*****************************************************************************
 *                                                                           *
 *                 ZSP LDF ����������ص�ַ�����ݳ���(Byte)                  *
 *                                                                           *
 *****************************************************************************/

/* SECT 00 -- ������Դ:�ļ�ͷ��־��LDF����ʱ��;����:4 Byte + 4 byte */
#define ZSP_LDF_FILE_CREATE_INFO_LEN        ( 8 )

/* SECT 01 -- ������Դ:ld�ļ�APMDOWNMBOX��LOAD��Ϣ;����:80 Byte */
#define ZSP_LDF_APM_LOAD_INFO_ADDR          ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_APM_LOAD_INFO_LEN           ( 80 )

/* SECT 02 -- ������Դ:ld�ļ�COMMON_DEBUG_DATA��;����:2.5K Byte */
#define ZSP_LDF_COM_DEBUG_DATA_ADDR         ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x3F400 ) )
#define ZSP_LDF_COM_DEBUG_DATA_LEN          ( 2560 )

/* SECT 03 -- ������Դ:ld�ļ�TEST��;����:0.5K Byte */
#define ZSP_LDF_TEST_DATA_ADDR              ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x3FE00 ) )
#define ZSP_LDF_TEST_DATA_LEN               ( 512 )

/* SECT 04 -- ������Դ:ld�ļ�APMDOWNMBOX��;����:1K Byte */
#define ZSP_LDF_APM_DOWN_BOX_ADDR           ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_APM_DOWN_BOX_LEN            ( 1024 )

/* SECT 05 -- ������Դ:ld�ļ�OVERLAY_DATA_PHY��;����:1K Byte */
#define ZSP_LDF_OVERLAY_DATA_ADDR           ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x1F400 ) )
#define ZSP_LDF_OVERLAY_DATA_LEN            ( 1024 )

/* SECT 06 -- ������Դ:BBP���мĴ���;����:128K Byte */
#define ZSP_LDF_BBP_REG_ADDR                ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_BBP_REG_LEN                 ( 128*1024 )

/* SECT 07 -- ������Դ:BBP G/WģINT�ж���ؼĴ���;����:16 Byte + 64 Byte */
#define ZSP_LDF_G_INT_REG_ADDR              ( DSP_REG_ACTUAL_ADDR( GBBP_BASE_ADDR, 0x1210 ) )
#define ZSP_LDF_G_INT_REG_LEN               ( 16 )
#define ZSP_LDF_W_INT_REG_ADDR              ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_W_INT_REG_LEN               ( 64 )

/* SECT 08 -- ��ͬSECT 02 */
/* SECT 09 -- ��ͬSECT 03 */
/* SECT 10 -- ��ͬSECT 04 */
/* SECT 11 -- ��ͬSECT 05 */
/* SECT 12 -- ��ͬSECT 06 */

/* SECT 13 -- ������Դ:WBBP DRX���;����:256 Byte + 4 Byte + 4 Byte */
#define ZSP_LDF_W_DRX_REG_ADDR              ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x21100 ) )
#define ZSP_LDF_W_DRX_REG_LEN               ( 256 )
#define ZSP_LDF_W_SYS_CLK_REG1_ADDR         ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x10A8 ) )
#define ZSP_LDF_W_SYS_CLK_REG1_LEN          ( 4 )
#define ZSP_LDF_W_SYS_CLK_REG2_ADDR         ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x8238 ) )
#define ZSP_LDF_W_SYS_CLK_REG2_LEN          ( 4 )

/* SECT 14 -- ������Դ:ld�ļ�ITCM��;����:512K Byte */
#define ZSP_LDF_ITCM_DATA_ADDR              ( DSP_REG_ACTUAL_ADDR( ZSP_ITCM_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_ITCM_DATA_LEN               ( 512*1024 )

/* SECT 15 -- ������Դ:ld�ļ�DTCM��;����:272K Byte */
#define ZSP_LDF_DTCM_DATA_ADDR              ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_DTCM_DATA_LEN               ( 272*1024 )

/* SECT 16 -- ������Դ:DL AHB��������;����:0x00002510 Byte,ʵ�ʻ�ȡ:10240 Byte */
#define ZSP_LDF_DL_AHB_DATA_ADDR            ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x1d8 ) )
#define ZSP_LDF_DL_AHB_DATA_LEN             ( 10240 )

/* SECT 17 -- ������Դ:DL AHB��������;����:0x00004148 Byte,ʵ�ʻ�ȡ:18432 Byte */
#define ZSP_LDF_UL_AHB_DATA_ADDR            ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x3c00 ) )
#define ZSP_LDF_UL_AHB_DATA_LEN             ( 18432 )

/* SECT 18 -- ������Դ:DL/UL AHB����ͷ;����:40 Byte + 40 Byte */
#define ZSP_LDF_DL_AHB_HEAD_ADDR            ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x1d8 ) )
#define ZSP_LDF_DL_AHB_HEAD_LEN             ( 40 )
#define ZSP_LDF_UL_AHB_HEAD_ADDR            ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x3c00 ) )
#define ZSP_LDF_UL_AHB_HEAD_LEN             ( 40 )

/* SECT 19 -- ������Դ:Dma6��ABB����;����:20 Byte + 124 Byte */
#define ZSP_LDF_DMA_CHANNEL6_ADDR           ( DSP_REG_ACTUAL_ADDR( DMAC_BASE_ADDR, 0x1C0 ) )
#define ZSP_LDF_DMA_CHANNEL6_LEN            ( 20 )
#define ZSP_LDF_ABB_REG_LEN                 ( 31*4 )

/* SECT 20 -- ������Դ:DRX������мĴ���;����:284 Byte */
#define ZSP_LDF_DRX_DATA_ADDR               ( ZSP_DRX_INFO_BEGIN_ADDR )
#define ZSP_LDF_DRX_DATA_LEN                ( ZSP_DRX_INFO_END_ADDR - ZSP_DRX_INFO_BEGIN_ADDR )

/* SECT 21 -- ������Դ:AHB��ַ0~0x1d8����������Ϣ;����:472 Byte */
#define ZSP_LDF_AHB_DATA_ADDR               ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_AHB_DATA_LEN                ( 0x01D8 )

/* SECT 22 -- ������Դ:ARM������ص�DRX��Ϣ;����:** Byte */
/* SECT 23 -- ������Դ:�ļ�β��־��LDF����ʱ��;����:4 Byte + 4 byte */



/*****************************************************************************
                            ZSP LDF��������TABLE����

 SECT 00 -- ��Դ:�ļ�ͷ��־��LDF����ʱ��;       ADDR:----------     LEN:8 Byte

 SECT 01 -- ��Դ:ld�ļ�APMDOWNMBOX��LOAD��Ϣ;   ADDR:0x20000000     LEN:80 Byte
 SECT 02 -- ��Դ:ld�ļ�OMMON_DEBUG_DATA��;      ADDR:0x2013F400     LEN:2.5K Byte
 SECT 03 -- ��Դ:ld�ļ�TEST��;                  ADDR:0x2013FE00     LEN:0.5K Byte
 SECT 04 -- ��Դ:ld�ļ�APMDOWNMBOX��;           ADDR:0x20100000     LEN:1K Byte
 SECT 05 -- ��Դ:ld�ļ�VERLAY_DATA_PHY��;       ADDR:0x2011F400     LEN:1K Byte
 SECT 06 -- ��Դ:BBP���мĴ���;                 ADDR:0x20200000     LEN:128K Byte
 SECT 07 -- ��Դ:BBP GģINT�жϼĴ���;          ADDR:0x20211210     LEN:16 Byte
            ��Դ:BBP WģINT�жϼĴ���;          ADDR:0x20200000     LEN:64 Byte
 SECT 08 -- ��Դ:ld�ļ�OMMON_DEBUG_DATA��;      ADDR:0x2013F400     LEN:2.5K Byte
 SECT 09 -- ��Դ:ld�ļ�TEST��;                  ADDR:0x2013FE00     LEN:0.5K Byte
 SECT 10 -- ��Դ:ld�ļ�APMDOWNMBOX��;           ADDR:0x20100000     LEN:1K Byte
 SECT 11 -- ��Դ:ld�ļ�VERLAY_DATA_PHY��;       ADDR:0x2011F400     LEN:1K Byte
 SECT 12 -- ��Դ:BBP���мĴ���;                 ADDR:0x20200000     LEN:128K Byte
 SECT 13 -- ��Դ:WBBP DRX���;                  ADDR:0x20221100     LEN:256 Bytes
            ��Դ:W_SYS_CLK1                     ADDR:0x202010A8     LEN:4 Byte
            ��Դ:W_SYS_CLK2                     ADDR:0x20208238     LEN:4 Byte
 SECT 14 -- ��Դ:ld�ļ���ITCM��;                ADDR:0x20000000     LEN:512K Byte
 SECT 15 -- ��Դ:ld�ļ���DTCM��;                ADDR:0x20100000     LEN:272K Byte
 SECT 16 -- ��Դ:DL AHB����;                    ADDR:0x203001D8     LEN:10K Byte
 SECT 17 -- ��Դ:UL AHB����;                    ADDR:0x20303C00     LEN:18K Byte
 SECT 18 -- ��Դ:DL AHB����ͷ;                  ADDR:0x203001D8     LEN:40 Byte
            ��Դ:DL AHB����ͷ;                  ADDR:0x20303C00     LEN:40 Byte
 SECT 19 -- ��Դ:Dma6�Ĵ���;                    ADDR:0x203801C0     LEN:20 Byte
 SECT 20 -- ��Դ:DRX��ؼĴ���;                 ADDR:0x20303AD0     LEN:300 Byte
 SECT 21 -- ��Դ:AHB 0~0x1d8��Ϣ;               ADDR:0x20300000     LEN:472 Byte

 SECT 22 -- ��Դ:ARM����DRX��Ϣ;                ADDR:----------     LEN:** Byte
 SECT 23 -- ��Դ:LDF����ʱ����ļ�β��־;       ADDR:----------     LEN:8 Byte

 *****************************************************************************/
#define ZSP_LDF_DUMP_DATA_INFO_TABLE    \
ZSP_LDF_DUMP_DATA_INFO_STRU     g_astZspLdfDumpDataTable[] =  \
{   \
    {   ZSP_LDF_APM_LOAD_INFO_ADDR,     ZSP_LDF_APM_LOAD_INFO_LEN   },   \
    {   ZSP_LDF_COM_DEBUG_DATA_ADDR,    ZSP_LDF_COM_DEBUG_DATA_LEN  },   \
    {   ZSP_LDF_TEST_DATA_ADDR,         ZSP_LDF_TEST_DATA_LEN       },   \
    {   ZSP_LDF_APM_DOWN_BOX_ADDR,      ZSP_LDF_APM_DOWN_BOX_LEN    },   \
    {   ZSP_LDF_OVERLAY_DATA_ADDR,      ZSP_LDF_OVERLAY_DATA_LEN    },   \
    {   ZSP_LDF_BBP_REG_ADDR,           ZSP_LDF_BBP_REG_LEN         },   \
    {   ZSP_LDF_G_INT_REG_ADDR,         ZSP_LDF_G_INT_REG_LEN       },   \
    {   ZSP_LDF_W_INT_REG_ADDR,         ZSP_LDF_W_INT_REG_LEN       },   \
    {   ZSP_LDF_COM_DEBUG_DATA_ADDR,    ZSP_LDF_COM_DEBUG_DATA_LEN  },   \
    {   ZSP_LDF_TEST_DATA_ADDR,         ZSP_LDF_TEST_DATA_LEN       },   \
    {   ZSP_LDF_APM_DOWN_BOX_ADDR,      ZSP_LDF_APM_DOWN_BOX_LEN    },   \
    {   ZSP_LDF_OVERLAY_DATA_ADDR,      ZSP_LDF_OVERLAY_DATA_LEN    },   \
    {   ZSP_LDF_BBP_REG_ADDR,           ZSP_LDF_BBP_REG_LEN         },   \
    {   ZSP_LDF_W_DRX_REG_ADDR,         ZSP_LDF_W_DRX_REG_LEN       },   \
    {   ZSP_LDF_W_SYS_CLK_REG1_ADDR,    ZSP_LDF_W_SYS_CLK_REG1_LEN  },   \
    {   ZSP_LDF_W_SYS_CLK_REG2_ADDR,    ZSP_LDF_W_SYS_CLK_REG2_LEN  },   \
    {   ZSP_LDF_ITCM_DATA_ADDR,         ZSP_LDF_ITCM_DATA_LEN       },   \
    {   ZSP_LDF_DTCM_DATA_ADDR,         ZSP_LDF_DTCM_DATA_LEN       },   \
    {   ZSP_LDF_DL_AHB_DATA_ADDR,       ZSP_LDF_DL_AHB_DATA_LEN     },   \
    {   ZSP_LDF_UL_AHB_DATA_ADDR,       ZSP_LDF_UL_AHB_DATA_LEN     },   \
    {   ZSP_LDF_DL_AHB_HEAD_ADDR,       ZSP_LDF_DL_AHB_HEAD_LEN     },   \
    {   ZSP_LDF_UL_AHB_HEAD_ADDR,       ZSP_LDF_UL_AHB_HEAD_LEN     },   \
    {   ZSP_LDF_DMA_CHANNEL6_ADDR,      ZSP_LDF_DMA_CHANNEL6_LEN    },   \
    {   ZSP_LDF_DRX_DATA_ADDR,          ZSP_LDF_DRX_DATA_LEN        },   \
    {   ZSP_LDF_AHB_DATA_ADDR,          ZSP_LDF_AHB_DATA_LEN        }    \
}


#define ZSP_LDF_DUMP_SECT_HALT_NO       ( 8 )


/* ��ȡLDF���ݱ���׵�ַ */

/* ��ȡLDF���ݱ��� */


/*****************************************************************************
 *                           ZSP LDF�������Զ���END                          *
 *****************************************************************************/










/****************************************************************************
 *                  WCDMAЭ��ջ��WPHY֮�乲���ڴ�ӿڵ�ַ����(DDR)          *
 *                                                                          *
 ****************************************************************************/

/* HSDPA ARM��DSP��SRAM�ӿ���ʼ��ַ,FPGAƽ̨�ṩ�Ľӿ�SRAM�ĵ�ַ��ʱ����Ϊ0x63f00000~0x64000000����1M�ռ�
   Э��ջ��DSPʹ�õ�Ϊ0x63f00000��ʼ��32KB�ռ� */

/* HSDA+ ARM��DSP��SDRAM�ӿ���ʼ��ַ,��5472*12=65,664(Byte)�ռ� */



#define DSP_DYMAIC_SEG_SIZE                         ( 63 )                      /* DSP��̬�δ�С */

#define PHY_OM_SAR_MASK_ANTSTATE                    (0x1)
#define PHY_OM_SAR_MASK_REDUCTION                   (0x2)


/******************************************************************************
  3 �ṹ����
******************************************************************************/

/*****************************************************************************
 �ṹ��    : ZSP_LDF_DUMP_DATA_INFO_STRU
 �ṹ˵��  : ZSP LDF���ݱ�����Ϣ���׵�ַ�����ݳ��Ƚṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulDataAddr;                                     /* ���ݵ��׵�ַ */
    VOS_UINT32                  ulDataLen;                                      /* ���ݵĳ��� */
}ZSP_LDF_DUMP_DATA_INFO_STRU;


typedef struct
{
    VOS_UINT16                  uhwRxVer;
    VOS_UINT16                  uhwTxVer;
    VOS_UINT16                  uhwRxEcVer;
    VOS_UINT16                  uhwTxEcVer;
    VOS_UINT16                  uhwverlogmsg;
    VOS_UINT16                  uhwResever;

} CPHY_RF_VER_INFO_STRU;

typedef struct
{
    VOS_UINT16                  uhwReslutinfo;             /*DSP��ʼ�����*/
    VOS_UINT16                  ulResever1;

} CPHY_BOOT_RESULT_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulProtect1;
    VOS_UINT32                  ulArmWriteSlice1;
    VOS_UINT32                  ulDspReadSlice1;
    VOS_UINT32                  ulDspMakeVersion;
    VOS_UINT32                  ulDspMakeDate;
    VOS_UINT32                  ulDspMakeTime;
    VOS_UINT32                  ulResever1[2];

    VOS_UINT32                  ulProtect2;
    VOS_UINT32                  ulArmReadSlice2;
    VOS_UINT32                  ulDspWriteSlice2;
    VOS_UINT32                  ulResever2[7];

    VOS_UINT32                  ulProtect3;
    VOS_UINT32                  ulArmWriteSlice3;
    VOS_UINT32                  ulDspReadSlice3;
    VOS_UINT32                  ulResever3[5];

    VOS_UINT32                  ulProtect4;
    VOS_UINT32                  ulArmWriteSlice4;
    VOS_UINT32                  ulDspReadSlice4;
    VOS_UINT32                  ulResever4[5];

    VOS_UINT32                  ulProtect5;
    CPHY_RF_VER_INFO_STRU       stDspVersionInfo;
    VOS_UINT32                  ulArmWriteSlice5;
    VOS_UINT32                  ulDspReadSlice5;
    VOS_UINT32                  ulResever5[5];

    VOS_UINT32                  ulProtect6;
    VOS_UINT32                  ulWphyVerAddr;
    VOS_UINT32                  ulResever6[2];
    VOS_UINT32                  ulHsupaShareCtrlAddr;
    VOS_UINT32                  ulDspModeRptAddr;
    VOS_UINT32                  ulHsupaRptAddr;
    VOS_UINT32                  ulHsupaTtiAddr;
    VOS_UINT32                  ulWReserveRptAddr2;
    VOS_UINT32                  ulWReserveRptAddr3;
    VOS_UINT32                  ulWReserveRptAddr4;
    VOS_UINT32                  ulCpcDrxRptAddr;

    VOS_UINT32                  ulGMsgRptAddr;
    VOS_UINT32                  ulGMsgRptLenAddr;
    VOS_UINT32                  ulGComRptAddr;
    VOS_UINT32                  ulGComRptLenAddr;
    VOS_UINT32                  ulGPsRptAddr;
    VOS_UINT32                  ulGPsRptLenAddr;
    VOS_UINT32                  ulGCsRptAddr;
    VOS_UINT32                  ulGCsRptLenAddr;
    VOS_UINT32                  ulGMailRptAddr;
    VOS_UINT32                  ulGMailptLenAddr;
    VOS_UINT32                  ulGCchRptAddr;
    VOS_UINT32                  ulGCchRptLenAddr;
    VOS_UINT32                  ulGNcellRptAddr;
    VOS_UINT32                  ulGNcellRptLenAddr;
    VOS_UINT32                  ulGDrxRptAddr;
    VOS_UINT32                  ulGDrxRptLenAddr;
    VOS_UINT32                  ulGPwcRptAddr;
    VOS_UINT32                  ulGPwcRptLenAddr;
    VOS_UINT32                  ulGCalRptAddr;
    VOS_UINT32                  ulGCalRptLenAddr;
    VOS_UINT32                  ulGMeasRptAddr;
    VOS_UINT32                  ulGMeasRptLenAddr;
    VOS_UINT32                  ulGDrvRptAddr;
    VOS_UINT32                  ulGDrvRptLenAddr;
    VOS_UINT32                  ulRfFrontEndRptAddr;        /* ǰ�˿�ά�ɲ⣬ÿ֡��ӡ */
    VOS_UINT32                  ulRfFrontEndRptLenAddr;     /* ǰ�˿�ά�ɲⳤ�� */
}CPHY_IPC_INFO_STRU;


/*****************************************************************************
 �ṹ��    : CPHY_BOOT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DSP�ϵ�ʱOAM��Ҫ��DSP��.dsp_oam_common_data��д���½ṹ�����ݣ���ʼ��ַ��DRV����ZSP bin���󴫸�OAM
*****************************************************************************/
typedef struct CPHY_BOOT_INFO_STRU
{
    VOS_UINT32                          ulProtect1;             /*������1*/
    VOS_UINT32                          ulValidFlag1;           /*OAM ��������ݵ���д������Ч���*/
    VOS_UINT32                          ulArmWriteSlice;
    VOS_UINT32                          ulDspReadyFlag;
    VOS_UINT32                          ulDspReadSlice;
    VOS_UINT32                          ulUmtsBandBitMap;        /* Ƶ����Чλͼ */
    VOS_UINT32                          ulValidFlag2;            /*������2*/
    VOS_UINT32                          ulCQIAddr;               /*NV CQI��ַ*/
    VOS_UINT32                          ulAPTAddr;               /* APT���׵�ַ */
    VOS_UINT32                          ulETAddr;                /* ET��ַ*/
    VOS_UINT32                          ulValidFlag3;            /*������3*/
    VOS_UINT32                          aulApmModuleAddrInfo[DSP_DYMAIC_SEG_SIZE];
    VOS_UINT32                          ulValidFlag4;            /*������4*/
    VOS_UINT16                          ausPhyOmNvTable[8];      /* �洢NV table��OAM�ӱ���ʼ��ַ��ʼдNV��*/
}CPHY_BOOT_INFO_STRU;




/* �Ͳ���Ľ�������ĳ���*/
#define COM_GPRS_DATA_LEN               (0xc00-2)
typedef struct /*�Ͳ���Ľ�������Ľṹ����*/
{
    VOS_UINT16      uhwAhbWrIndex;                           /* AHB����дָ��ƫ�Ƶ�ַ */
    VOS_UINT16      uhwAhbRdIndex;                           /* AHB�����ָ��ƫ�Ƶ�ַ */
    VOS_UINT16      uhwMutex;                                /* ��GRM�޸Ľӿ�,���ӵĻ����־ */
    VOS_UINT16      uhwRsv;                                  /* ��GRM�޸Ľӿ�,���� */
    VOS_UINT16      auhwDataBuf[COM_GPRS_DATA_LEN];          /* ָ��AHB�����׿黺���ָ��*/
}GPRS_DATA_BUF;
/******************************************************************************
  4 ö�ٶ���
******************************************************************************/


/******************************************************************************
  5 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
  6 ��Ϣͷ����
******************************************************************************/


/******************************************************************************
  7 ��Ϣ����
******************************************************************************/


/******************************************************************************
  8 �ṹ����
******************************************************************************/
extern VOS_UINT32 APM_OamClearSdtLinkStatus( VOS_VOID );
extern VOS_VOID UCOM_SetTemparatureAddr( VOS_UINT32 uwTempratureAddr );
extern VOS_UINT32 UCOM_GetDspShareMemAddr(VOS_VOID);
extern VOS_UINT32 UPHY_MNTN_PhyLdfFileSaving( VOS_VOID );


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DSPINTERFACE_H__ */

