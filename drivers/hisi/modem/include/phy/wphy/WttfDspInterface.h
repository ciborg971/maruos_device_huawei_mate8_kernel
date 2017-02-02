/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : WttfDspInterface.h
  �� �� ��   : V1.00
  ��    ��   : ������
  ��������   : 2007��7��13��
  ����޸�   :
  ��������   : WttfDspInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��7��13��
    ��    ��   : ������
    �޸�����   : �����ļ�

  2.��    ��   : 2007��10��10��
    ��    ��   : ������
    �޸�����   : �������۵��½ӿڷ�����ARMֻ��DSP���ڽӿڣ�
                 ARM��BBP�޽ӿڣ������û���ӿ�

  3.��    ��   : 2008��02��25��
    ��    ��   : ������
    �޸�����   : ����HSUPA�ӿ�

  3.��    ��   : 2008��5��20��
    ��    ��   : changyuhui
    �޸�����   : AT2D003457

  4.��    ��   : 2008��6��17��
    ��    ��   : shijieke
    �޸�����   : ��WTTFPHY_MAC_DPCCH_PWR_IND_STRU��Ϣ�����������������
                 ���з��书��sAllowUlMaxPower�ӿ�
******************************************************************************/

#ifndef __WTTFDSPINTERFACE_H__
#define __WTTFDSPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "WUeSpec.h"
#include "DspInterface.h"
#include "product_config.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define WTTFPHY_WAIT_WTTF_NEW_MACE_ACTIVE_FLAG          (0x33553355)
#define WTTFPHY_NOTICE_WTTF_MACE_REL_FLAG               (0x55335533)

#define WTTFPHY_SLOT_NUM_PER_FRAME                  (15)            /*ÿ֡ʱ϶����15��*/
#define WTTFPHY_IVALID_TX_POWER                     (0x7fff)        /* DSP�ϱ��ı�ʾ��Чֵ�ķ��书�� */

#define WTTFPHY_INVALID_SFN                         (0xffff)        /*��ЧSFN*/


/* MAC E ����� */
#define WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM                (4)             /* Э��ջ ��DSP Э���õ�MAC E/I ʵ�� ����RB���� */

#define WTTFPHY_MAC_UPA_MAX_CS_RB_NUM                 (3)             /* Э��ջ ��DSP Э���õ�MAC E ʵ�� CS RB���� */

#define WTTFPHY_MAC_UPA_MAX_PS_RB_NUM                 (5)             /* Э��ջ ��DSP Э���õ�MAC E ʵ�� ҵ��RB����:
                                                                    V3R2/V7, PS RB������չΪ5��
                                                                    ��Э��ջ����DSP�ĸ�������WTTFPHY_MAC_UPA_MAX_PS_RB_NUM ʱ��DSP������飬��������ʧ�� */



/*R4��ع��ܺ궨��*/
#define WTTFPHY_MAX_PHY_DATA_REQ_HEAD_CTRL_LEN      (52)            /* ��λ:�ֽ�,ID_MAC_PHY_DATA_REQԭ�����ͷ����*/
#define WTTFPHY_MAX_PHY_DATA_REQ_LEN                (1024)          /* MAC_PHY_DATA_REQ R99������󳤶�,384*1024/(100*8) = 491(BYTE),Ϊ����������ȡֵ1024 */
#define WTTFPHY_MAX_PHY_DATA_REQ_EXPT_CTRL_LEN      (36)            /* ��λ:�ֽ�,ID_MAC_PHY_DATA_REQԭ���쳣���Ʋ��ֳ���*/
#define WTTFPHY_MAX_PHY_DATA_REQ_RESERVE_LEN        (36)                        /* ��λ:�ֽ�,ID_MAC_PHY_DATA_REQԭ�ﱣ�����ֳ��ȣ�����չʹ��*/

/* 1152,��λ:�ֽ�,ID_MAC_PHY_DATA_REQԭ��ռ������ռ��ܳ��� */
#define WTTFPHY_MAX_PHY_DATA_REQ_TOTAL_LEN          ((WTTFPHY_MAX_PHY_DATA_REQ_HEAD_CTRL_LEN) \
                                                    +(WTTFPHY_MAX_PHY_DATA_REQ_LEN)           \
                                                    +(WTTFPHY_MAX_PHY_DATA_REQ_EXPT_CTRL_LEN) \
                                                    +(WTTFPHY_MAX_PHY_DATA_REQ_RESERVE_LEN))

#define WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_LEN        (4)                         /* ����1����Ļ����־��ռ4�ֽ� */
#define WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_LEN       (4)                         /* ����2����Ļ����־��ռ4�ֽ� */

/* BBP�������ݸ�RAM��С */
#define WTTFPHY_MAX_PHY_DATA_IND_TURBO_HEAD_LEN     (24*4)          /* ��λ:�ֽ�,PHY_MAC_DATA_IND TURBO���� RAM������Ϣ��󳤶�*/
#define WTTFPHY_MAX_PHY_DATA_IND_TURBO_DATA_LEN     (256*4)         /* PHY_MAC_DATA_IND ������󳤶�,��λ�ֽ�:256*4,256��Turbo�����������ռ�,BBP���  */

/* ��λ:�ֽ�,PHY_MAC_DATA_IND TURBO����RAM������ռ��ܳ���,BBP��� */
#define WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN    ( (WTTFPHY_MAX_PHY_DATA_IND_TURBO_HEAD_LEN) \
                                                    + (WTTFPHY_MAX_PHY_DATA_IND_TURBO_DATA_LEN))

#define WTTFPHY_MAX_VTB_RAM_LEN                     (128*4)         /* ��λ:�ֽ�,PHY_MAC_DATA_IND ά�ر����� RAM�ܿռ䳤��,BBP���  */
#define WTTFPHY_MAX_VTB_BCH_LEN                     (32*4)          /* ��λ:�ֽ�,BBP�ṩ��ά�ر�����ռ���PCCPCH(Ҳ��ϵͳ��Ϣ)ռ��32����(32bit)���ⲿ��BBPֱ���ṩ��WRR��WTTF�û���ӿڲ��漰��*/
#define WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN       (24*4)          /* ��λ:�ֽ�,PHY_MAC_DATA_IND ά�ر����� RAM������Ϣ��󳤶� */
/*��λ:�ֽ�,PHY_MAC_DATA_IND ά�ر��������ݲ���ռ������ռ���󳤶� */
#define WTTFPHY_MAX_PHY_DATA_IND_VTB_DATA_LEN       ((WTTFPHY_MAX_VTB_RAM_LEN   \
                                                    - WTTFPHY_MAX_VTB_BCH_LEN)  \
                                                    - WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN)

/* ��λ:�ֽ�,PHY_MAC_DATA_IND ά�ر�����RAMȥ��PCCPCH�������ݺ�ռ�������ܿռ䳤��,BBP���  */
#define WTTFPHY_MAX_PHY_DATA_IND_VTB_TOTAL_LEN      ( (WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN)   \
                                                    + (WTTFPHY_MAX_PHY_DATA_IND_VTB_DATA_LEN))

#define WTTFPHY_MAX_AMR_DATA_REQ_LEN                (256-8)                     /* ��λ:�ֽ�,PHY_RLC_AMR_DATA_REQ ������󳤶ȣ�ʵ������36���ֽڣ�������������,8���ֽ��ǿ���ͷ���� */
#define WTTFPHY_MAX_AMR_DATA_REQ_TOTAL_LEN          (WTTFPHY_MAX_AMR_DATA_REQ_LEN + 8)          /* ��λ:�ֽ�,PHY_RLC_AMR_DATA_REQԭ��ռ�������ܿռ䳤��,8���ֽ��ǿ���ͷ���� */
#define WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_LEN         (256-8)                     /* ��λ:�ֽ�,WTTFPHY_MAC_DL_AMR_DECIPHER_BUF ������󳤶ȣ�ʵ������36���ֽڣ�������������,8���ֽ��ǿ���ͷ���� */
#define WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_TOTAL_LEN   (WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_LEN + 8)          /* ��λ:�ֽ�,WTTFPHY_MAC_DL_AMR_DECIPHER_BUFԭ��ռ�������ܿռ䳤��,8���ֽ��ǿ���ͷ����  */
#define WTTFPHY_MAX_AMR_DATA_IND_LEN                (256-8)                     /* ��λ:�ֽ�,MAC_PHY_AMR_DATA_IND ������󳤶ȣ�ʵ������36���ֽڣ�������������,8���ֽ��ǿ���ͷ���� */

#define WTTFPHY_MAX_TFC_BCBD_IND_TOTAL_LEN          (8 + ( PS_WUE_MAX_UL_TFC_NUM * 2 ) )

#define WTTFPHY_MAX_DPCCH_PWR_IND_LEN               (36)                        /* ��λ:�ֽ�*/
#define WTTFPHY_MAX_DPCCH_PWR_IND_TOTAL_LEN         (WTTFPHY_MAX_DPCCH_PWR_IND_LEN) /* ��λ:�ֽ�*/
#define WTTFPHY_MAX_BETA_HS_IND_LEN                 8
#define WTTFPHY_MAX_BETA_HS_IND_RESERVE_LEN         (72)                        /* ��λ:�ֽ�*/
#define WTTFPHY_MAX_BETA_HS_IND_TOTAL_LEN           ( WTTFPHY_MAX_BETA_HS_IND_LEN                \
                                                    + WTTFPHY_MAX_BETA_HS_IND_RESERVE_LEN)

#define WTTFPHY_MAX_MAIL_BOX_RESERVE_LEN            (512)                       /* ��λ:�ֽ�*/
#define WTTFPHY_MAX_MAIL_BOX_TOTAL_LEN              ( WTTFPHY_MAX_PHY_DATA_REQ_TOTAL_LEN        \
                                                    + WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_LEN       \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN  \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_VTB_TOTAL_LEN    \
                                                    + WTTFPHY_MAX_AMR_DATA_REQ_TOTAL_LEN        \
                                                    + WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_TOTAL_LEN        \
                                                    + WTTFPHY_MAX_TFC_BCBD_IND_TOTAL_LEN        \
                                                    + WTTFPHY_MAX_DPCCH_PWR_IND_TOTAL_LEN       \
                                                    + WTTFPHY_MAX_BETA_HS_IND_TOTAL_LEN         \
                                                    + WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_LEN      \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN  \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_VTB_TOTAL_LEN)       /* ��λ:�ֽ� */


#define WTTFPHY_MAC_PHY_DATA_REQ_ADDR               (ARM_DSP_R99_DATA_BASE_ADDR)

/* ��1�����������ַ */
#define WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_ADDR       ( WTTFPHY_MAC_PHY_DATA_REQ_ADDR             \
                                                    + WTTFPHY_MAX_PHY_DATA_REQ_TOTAL_LEN)

#define WTTFPHY_MAC_DATA_IND_FIRST_TURBO_ADDR       ( WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_ADDR      \
                                                    + WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_LEN)

#define WTTFPHY_MAC_DATA_IND_FIRST_VTB_ADDR         ( WTTFPHY_MAC_DATA_IND_FIRST_TURBO_ADDR     \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN)

/* BELTA hs ��Ӧ��ַ */
#define WTTFPHY_MAC_BETA_HS_IND_ADDR                ( WTTFPHY_MAC_DATA_IND_FIRST_VTB_ADDR       \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_VTB_TOTAL_LEN)

/* ��2�����������ַ */
#define WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_ADDR       ( WTTFPHY_MAC_BETA_HS_IND_ADDR              \
                                                    + WTTFPHY_MAX_BETA_HS_IND_TOTAL_LEN)

#define WTTFPHY_MAC_DATA_IND_SECOND_TURBO_ADDR      ( WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_ADDR     \
                                                    + WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_LEN)

#define WTTFPHY_MAC_DATA_IND_SECOND_VTB_ADDR        ( WTTFPHY_MAC_DATA_IND_SECOND_TURBO_ADDR    \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN)


/**********************************************************************************
    R5 HSDPA interface start
**********************************************************************************/
/*(8 + 3 + 1),������������Ӧ����8��Ϊ��������ARM�������ܴ����Ķ������ʣ�����3�飬
  ����,ʵ�ֶ�����Ҫ�ж϶����������Ӷ����1�� */
#define WTTFPHY_MAX_HS_PDU_BUF_NUM              (12)

/* ��λ:�ֽ�,��˾UE 7.2Mbps�����ϱ�Ϊ�ȼ�8�� 3.6Mbps�����ϱ�Ϊ�ȼ�5��14.4Mbps�����ϱ�Ϊ�ȼ�10��
   BalongV3֧�ֵĹ����14.4Mbps����Ӧ�ȼ�Ϊ10����ӦЭ���϶����MAC-HS PDU���Ϊ27952 bit,
   Ϊȷ����4�ֽڵ�������������Ϊ27968 bit��Ҳ��3496���ֽ�,Ҳ��874��(32bit) */
#define WTTFPHY_MAX_HS_PDU_LEN                  (3496)


/* ���ڲ���Ӳ����MAC HSͷ������ÿ��MAC-HS ͷЭ���ֶζ�Ҫ���ֽ�Ϊ��λ��ţ�������
   �Ķ������ӿռ��������:
   MAC-HS�ֶ�   ʵ������ռ�(bit)     Ӳ����ͷ����  ����  Ӳ����ͷ��������
                                      ��Ҫ�ռ�(bit)       �ռ䳤�ȣ�bit��
 V��QUEUE ID��TSN     10                     32       1        22
 N SID                10                     32       8        176
 CT                   4                      32       70       1960
 ����4�ֽ�            1                      32       70       2170

 �������ӿռ�Ϊ:22+176+1960+2170 = 4328(bit) = 541(BYTE),���ǵ��ܱ�4������
 ���,���ȡֵ:544(BYTE) = 136 (32bit WORD)      */
#define WTTFPHY_MAX_HS_PDU_BUF_LEN              ( WTTFPHY_MAX_HS_PDU_LEN + 544 )/* ��λ:�ֽ�, ֧��7.2MΪ 2352 BYTE,588 WORD(32bit),
                                                                                ֧��14.4MΪ 4044 BYTE,1011 WORD(32bit) */

/*
#define WTTFPHY_MAC_HS_DATA_IND_CTRL_BUF_ADDR   (ARM_DSP_R5_SHARE_MEM_CTRL_BASE_ADDR)
*/
/**********************************************************************************
    R5 HSDPA interface end
**********************************************************************************/

/**********************************************************************************
    HSUPA interface start
**********************************************************************************/
/* ֧�ּ����ز�, �����������������һ�����뿪�� */
#if 0
#if (FEATURE_ON == FEATURE_DC_UPA)
#define PS_WUE_MAX_CARRIER_CNT                        (2)    /* Dual Carrier */
#else
#define PS_WUE_MAX_CARRIER_CNT                        (1)    /* Singal Carrier */
#endif
#endif

/*����*/
#define PS_WUE_MAX_CARRIER_CNT                        (1)    /* Singal Carrier */

/*  V7֧�� E-DCH category7, ÿ���ز��� ��10ms TB_SIZE=20000 bit�����ǵ� DSP��10ms��Ҫȡһ�����ݣ�
    ����10ms TTI, ARM������ʵʱ�·�����, ���Ի���1��10ms TTI���� 20000/8 = 2500(Byte)
    10ms TTIֻ���ǵ��ز� */
#define PS_WUE_MAX_E_DCH_10MS_PER_PS_RB_BUF_BYTE_SIZE    (2500)

/*  V7֧�� E-DCH category9, ��2ms TB_SIZE=22996 bit�����ǵ� DSP��2ms��Ҫȡһ�����ݣ�
    ���Ի�����Ҫ����ദһЩ������֤DSP�����ݿ�ȡ�������Ƶ���������Ҫ�ﵽ
    8��2ms TTI���� 22996*8/8 = 22,996(Byte)*/
#define PS_WUE_MAX_E_DCH_2MS_PER_PS_RB_BUF_BYTE_SIZE     ((VOS_UINT32)(20000)*(PS_WUE_MAX_CARRIER_CNT))

#define PS_WUE_MAX_E_DCH_PER_PS_RB_BUF_BYTE_SIZE         (PS_WUE_MAX_E_DCH_2MS_PER_PS_RB_BUF_BYTE_SIZE)


/* ÿ������RB����ռ�,��λ:�ֽ�(DSP��16bit��д,DSP����������ַ��Ҫ�����ȡ),
   13.6 Kbps(����RB�����������) * 4(����10ms TTI,4������) * 8(����ش�����) * 10 (10ms TTI)
   = 4352 bit = 544�ֽ�, ʵ����ʹ��1���ֽڣ��������ѭ�������� */
#define PS_WUE_MAX_E_DCH_PER_S_RB_BUF_BYTE_SIZE         (544)

/* CS��ҵ��RB����һ��RB��UM RB׼��һ��TTI������,
   64Kbps(CS RB�����������) * 8(����2ms TTI,8������) * 10 (10ms TTI) = 640 bit = 80Byte */
#define PS_WUE_MAX_E_DCH_PER_CS_RB_BUF_BYTE_SIZE         (80)

/*  ����һ��������������27.2kbps, 10ms��׼����������: 27200bits / (1000ms/10ms) = 272bits
    ��Э������Сrlc pdu��С16bitsΪ��(�����źż�����ӳ���)
    ��Ҫ׼��rlc pdu����: 272bits/16bits  */
#define PS_WUE_S_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH             (20)

/*  ����һ��CS��ҵ����������64kbps, 10ms��׼����������: 64000bits / (1000ms/10ms) = 640bits
    ��Э������Сrlc pdu��С16bitsΪ��(�����źż�����ӳ���)
    ��Ҫ׼��rlc pdu����: 640bits/16bits */
#define PS_WUE_CS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH            (40)


/* �Ե����ز�, ����ǵ���size������category׼��8��TTI����Ҫ25558bit * 8������ / 640bit = 320��
   640bit�Ǹ���SE�ṩ��DS���ἰ, ����640bit����ʱ���Ƿ�ֵ���ܵĴ�� */
#define PS_WUE_PS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH            ((320) * (PS_WUE_MAX_CARRIER_CNT))


/* �����Ҫ���ӿ�(Gֵ)��Ҫ���������Ϊ8�� */
#define PS_WUE_MAC_E_DCH_STATUS_IND_BUF_SIZE                (8)

/* ��MACû����ʷGֵʱ, ʹ��Լ��ֵ��������RLC��Ҫ������Լ��ֵΪ����10��Pdu������
   ����fixed pdu size, ����144bit����, ����flexible pdu size, ������Сpdu��λsize 176bit����
   һ�㶼����RRC�պ�������PHY�����źźܲ�ʱ, ���ȡ������Сֵ144bit�����, 10��pdu��1440bits
   ע���ʱ�����Ƕ��ز����ǵ��ز�, ֻ���յ��ز����� */
#define PS_WUE_E_DCH_STATUS_IND_DEFAULT_G                (1440)

/**********************************************************************************
    HSUPA interface end
**********************************************************************************/


/*V3 R7_7C1 Start */
/**********************************************************************************
    MAC-EHS PHY interface start
**********************************************************************************/
/* V5�����Ż���MACֻ�Ƚ�������MAC-ehsͷ����Ϣ������������RLC����ʱ������CICOM��
   ���ݴ������ж���������MAC-ehs rPdu���򡢾���ݽ������أ���Ҫ����������
   ����Э��涨T1��ʱ����Э��ʱ�����ֵΪ400ms����MAC-ehs PDU����������MAC-ehs
   ��������л����п���ͣ�����ʱ��Ϊ400ms������84MbpsЭ����
   ʵ����Ҫ�����PDU���� = һ��TTI�����TB���� * T1ʱ���ڵ�TTI��
                         =  (4 TB per TTI) * ( 400/2 )  = 800
   �����ڲ�ʱ����Ҫ��һ���ľ��⣬��չϵ��1.2��800 * 1.2 = 960 */
#if (FEATURE_OFF == FEATURE_DC_MIMO)
#define WTTFPHY_MAX_EHS_PDU_BUF_NUM             (440)    /* Mem Reduce */
#else
#define WTTFPHY_MAX_EHS_PDU_BUF_NUM             (880)
#endif

/* ��λ:�ֽ�,HSPA+�����ϱ�Ϊ�ȼ�14��
   ��ӦЭ���϶����MAC-EHS PDU���Ϊ42192 bit,
   ����BBPMASTERҪ��8�ֽڵ���������ȡ42240 bit,��5280���ֽ�,Ҳ��1320��(32bit) */
#define WTTFPHY_MAX_EHS_PDU_LEN                 (5280)

/* ���ڲ���Ӳ����MAC EHSͷ������ÿ��MAC-EHS ͷЭ���ֶζ�Ҫ���ֽ�Ϊ��λ��ţ�������
   �Ķ������ӿռ��������:
   MAC-EHS�ֶ�   ʵ������ռ�(bit)     Ӳ����ͷ����  ����  Ӳ����ͷ����������Ҫ�ռ䳤��(bit)

 BCCHָʾ��rPDU����   0                      32       1        32
 TSN,SI               16                     32       3        48
 LCH-ID,LI,F          16                     32       44       704
 RLC Header           16                     32       44       704
 ����4�ֽ�            8                      32       44       1056
 (��ע: ����Э��ԭ��RLC SDU�ĳ���Ϊ8Bit��������,����RLC SDU�ĳ���Ϊ�䳤������ȷ����ʵ�ʵ�
 �ռ俪������ʵ�ʿ���ռ�õ�BIT�� 8bit/16bit/24bit/32bit��� Ϊ�˱�֤�ռ��㹻��ȡ��С��ռ��BIT
 ����֤)
 �������ӿռ�Ϊ:32+48+704+704+1056 = 2544(bit) = 318(BYTE) ȡ4�ֽڶ���Ϊ320Byte
*/
#define WTTFPHY_MAX_EHS_PDU_BUF_LEN             ( WTTFPHY_MAX_EHS_PDU_LEN + 320 )/* ��λ:�ֽ�,5596 BYTE,1399 WORD(32bit) */

#define WTTFPHY_MAC_EHS_RPDU_MAX_NUM            (3)    /*the max number of rpdu*/

/*  if the TSN field extension is configured(��������DC+MIMO֧�ֵȼ�), ÿ��TTI�����ɴﵽ44��RSDU
    ����V9R1оƬ���(��֧��DC)��rSdu�������ֻ��26��
*/
#define WTTFPHY_MAC_EHS_RSDU_MAX_NUM            (26)   /*the max number of rsdu */

#define WTTFPHY_MAC_EHS_RSDUHEAD_PAD_LEN        (2)    /*ÿ��RSDUͷǰ��ճ��������ֽ� */

#define WTTFPHY_MAC_EHS_SDU_4BYTE_LEN           ((WTTFPHY_MAX_EHS_PDU_BUF_LEN/4) - 48)    /* 1344��(32bit),48:MAC-EHSЭ��ͷӲ����������ռ�ռ� */

#define WTTFPHY_MAC_EHS_DATA_IND_CTRL_BUF_ADDR  (ARM_DSP_R7_SHARE_MEM_CTRL_BASE_ADDR)
/*
#define WTTFPHY_MAC_EHS_DATA_IND_CTRL_BUF_ADDR  (ARM_DSP_R7_SHARE_MEM_CTRL_BASE_ADDR)
#define WTTFPHY_MAC_EHS_DATA_IND_DATA_BUF_ADDR  (ARM_DSP_R7_SHARE_MEM_DATA_BASE_ADDR)
*/
/* ========================================================================
   BBP Master�����и���Ӳ���ṩ�Ľӿ�Լ�� R5�� R7�Ĺ������� EHS��������:
   TB HEAD �Ĵ�СΪ64 WORD �������� TB DATA�Ĵ�СΪ1.5K WORD

   BBP��Э��ջ֮���µĽӿڹ涨����:
        8bit   8bit       8bit  8bit
        ����   BCCH/PCCH  RSDU  RPDU
        RPDU1  QUEUE ID   TSN1  SI1
        RPDU2  QUEUE ID   TSN2  SI2
        RPDU3  QUEUE ID   TSN3  SI3
        ����   LCH_ID1    L1(11bit)
        ����   LCH_ID2    L2
        ����   LCH_ID3    L3
        ...
        ����   LCH_ID44   L44              Total(48 WORD)
 =========================================================================*/
/* ��Ӳ���Ĺ��Լ��,Ƭ��SRAMͷ��Ҫ64 WORD��ϸ�ṹ���ϱ�����V9R1оƬ���TB Head��С��256�ֽڲü�Ϊ128�ֽ� */
#define WTTFPHY_MAC_HSDPA_TB_HEAD_SIZE                  (128) /* 32 WORD = 128 Byte */

/* ���㷽�� ���� = 60ms / 2ms * 4(TTI��TB��ĸ���)
    ����ĸ�����Ҫ���ݵ���ľ���ֵ�����趨 */
#if (FEATURE_OFF == FEATURE_DC_MIMO)
#define WTTFPHY_MAC_HSDPA_TB_HEAD_NUM                   (440)  /* Mem Reduce */
#else
#define WTTFPHY_MAC_HSDPA_TB_HEAD_NUM                   (880)
#endif

/* ��λ:�ֽ�,HSPA+�����ϱ�Ϊ�ȼ�14��
   ��ӦЭ���϶����MAC-EHS PDU���Ϊ42192 bit,��5274���ֽ�
   ����8�ֽڵ���������ȡ5280���ֽ�,Ҳ��1320��(32bit)
   ���ڲ���Ӳ�����룬���д洢TB�����������Ӷ���Ŀռ䣬����WTTFPHY_MAC_EHS_SDU_4BYTE_LEN���㣬Ϊ5408�ֽ�
*/
#define WTTFPHY_MAC_HSDPA_TB_DATA_SIZE                  (WTTFPHY_MAC_EHS_SDU_4BYTE_LEN * 4)

/* TBͷ�����߸�����Ԥ��3֡����30�飬�ټ���10������
   �������ߴ�СΪ400�����������������ֵһ��
*/
#if(FEATURE_ON == FEATURE_SMALL_MAILBOX)
#define WTTFPHY_MAC_HSDPA_TB_DATA_NUM                   (51) /* ����CPUռ���ʿ���С���䷽��ֻ����42M */
#else
    #if (FEATURE_OFF == FEATURE_DC_MIMO)
    #define WTTFPHY_MAC_HSDPA_TB_DATA_NUM               (440) /* ����TB��ĸ��� */  /* Mem Reduce */
    #else
    #define WTTFPHY_MAC_HSDPA_TB_DATA_NUM               (880) /* ����TB��ĸ��� */
    #endif
#endif

/**********************************************************************************
    MAC-EHS PHY interface end
**********************************************************************************/
/*WCDMA CS Transmission Delay Optimize begin*/

#define WTTF_PHY_DL_MAX_AMR_DECIPHER_TRCH_NUM       (3)
#define WTTF_PHY_DL_MAX_AMR_DECIPHER_KEY_BYTE_SIZE  (52) /* CLASS B ���405bit = 52byte */
#define WTTF_PHY_DL_MAX_AMR_DECIPHER_PARAM_NUM      (3)

/*WCDMA CS Transmission Delay Optimize end*/

/* V3 R7_7C1 End */

/* ����WTTF��PHY֮���API���ã������ص�����������������8�� */
#define WTTFPHY_ITF_API_MAX_PARA_CNT                (8)

/*  һ�����ж��Ƿ񵽴Ｄ��ʱ��ȳ����������ж�һ����Χ��
    ������һ���㣬���������Ľ�׳�� */
#define  WTTFPHY_CFG_ACT_CFN_PROTECT_RANGE          (12)
#define  WTTFPHY_CFG_ACT_CFN_PROTECT_RANGE_DSDS     (20)
#define  WTTFPHY_CFG_ACT_CFN_PROTECT_RANGE_GCF      (8)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum WTTFPHY_CCTRCH_ENUM
{
    WTTFPHY_PCCPCH                      = 0,
    WTTFPHY_SCCPCH                      = 1,
    WTTFPHY_DL_DPCH                     = 2,
    WTTFPHY_PRACH                       = 3,
    WTTFPHY_UL_DPCH                     = 4,
    WTTFPHY_CCTRCH_BUTT
};
typedef VOS_UINT16 WTTFPHY_CCTRCH_ENUM_UINT16;


enum WTTFPHY_ACCESS_ENUM
{
    WTTFPHY_AICH_NACK                   = 0,                /* ������յ�AICH NACK */
    WTTFPHY_AICH_ACK                    = 1,                /* ������յ�AICH ACK��������Ϣ����Ҳ���ͳɹ� */
    WTTFPHY_AICH_NO_ACK                 = 2,                /* �����û���յ�AICH����Ӧ*/
    WTTFPHY_AICH_NO_PRACH               = 3,                /* a.PRACH�ŵ�������;
                                                                b.MAC_PHY_ACCESS_REQ�������󣬻��ߣ���������쳣��״̬�յ���MAC_PHY_ACCESS_REQ��Ϣ��MAC_PHY_ACCESS_REQ���󳡾��£����ٷ���ǰ���������; */
    WTTFPHY_ACCESS_BUTT                                     /* �����ͳһ��BUTT����Ϊ���һ��ö��ֵ��*/
} ;
typedef VOS_UINT16 WTTFPHY_ACCESS_ENUM_UINT16;


enum WTTFPHY_MUTEX_ENUM
{
    WTTFPHY_MUTEX_DATA_NOT_EXIST        = 0,                /* ��������������ݣ�  ��д�����ɶ�;*/
    WTTFPHY_MUTEX_DATA_EXIST            = 1,                /* ��������������ݣ�����д��  �ɶ�;*/
    WTTFPHY_MUTEX_BUTT
};
typedef VOS_UINT16 WTTFPHY_MUTEX_ENUM_UINT16;

/*****************************************************************************
 ö����    : WTTFPHY_RF_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RF�Ƿ���ڱ�־
*****************************************************************************/
enum WTTFPHY_RF_ENUM
{
    WTTFPHY_RF_NOT_EXIST        = 0,                        /* RF��Դ������ */
    WTTFPHY_RF_EXIST            = 1,                        /* RF��Դ���� */
    WTTFPHY_RF_BUTT
};
typedef VOS_UINT16 WTTFPHY_RF_ENUM_UINT16;

/*****************************************************************************
 ö����    : WTTFPHY_MAC_RESET_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����reset����
*****************************************************************************/
enum WTTFPHY_MAC_RESET_TYPE_ENUM
{
    WTTFPHY_MAC_EHS_RESET                      = 0,            /* ָʾreset mac ehs ʵ��*/
    WTTFPHY_MAC_RESET_TYPE_BUTT
};
typedef VOS_UINT16 WTTFPHY_MAC_RESET_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : WTTFPHY_MAC_RESET_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : MACʵ�帴λָʾ�ظ�

*****************************************************************************/
enum WTTFPHY_MAC_RESET_RESULT_ENUM
{
    WTTFPHY_MAC_RESET_SUCCESS                  = 0,                /* MACʵ�帴λ�ɹ� */
    WTTFPHY_MAC_RESET_ERROR                    = 1,                /* MACʵ�帴λʧ�� */
    WTTFPHY_MAC_RESET_RESULT_BUTT
} ;
typedef VOS_UINT16 WTTFPHY_MAC_RESET_RESULT_ENUM_UINT16;

/*****************************************************************************
 ö����    : WTTFPHY_MAC_STATUS_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ֪ͨ MAC�ײ�״̬��Ϣ,�յ���MACֹͣ���η���

*****************************************************************************/
enum WTTFPHY_MAC_STATUS_IND_ENUM
{
    WTTFPHY_MAC_STATUS_IND_OUT_OF_SYNC                = 1,                 /* a L1 synchronisation failure */
    WTTFPHY_MAC_STATUS_IND_MAX_EDCH_RESOURCE          = 2,                  /* the maximum E-DCH resource allocation for CCCH */
    WTTFPHY_MAC_STATUS_IND_NO_MACI_FOR_TRANS          = 3,                 /* no MAC-i PDU for transmission */
    WTTFPHY_MAC_STATUS_IND_RL_RELEASE                 = 4,                 /* �ŵ��ͷ�(����PHY��·�ͷź�������) */
    WTTFPHY_MAC_STATUS_IND_MAX_PERIOD_COLLISION       = 5,                 /* the maximum  period for collision resolution and no E-AGCH with the UE's E-RNTI */
    WTTFPHY_MAC_STATUS_IND_EXPLICIT_RELEASE           = 6,                 /* explicit common E-DCH resource release */
    WTTFPHY_MAC_STATUS_IND_IMPLICIT_RELEASE           = 7,                 /* implicit common E-DCH resource release */
    WTTFPHY_MAC_STATUS_IND_BUTT                                           /* �����ͳһ��BUTT����Ϊ���һ��ö��ֵ */
};
typedef VOS_UINT16 WTTFPHY_MAC_STATUS_IND_ENUM_UINT16;


/*****************************************************************************
 ö����    : WTTFPHY_MAC_STATUS_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ֪ͨ MAC�ײ�״̬��Ϣ,�յ���MACֹͣ���η���

*****************************************************************************/
enum WTTFPHY_UL_EFACH_LOCH_TYPE_ENUM
{
    WTTFPHY_UL_EFACH_LOCH_TYPE_CCCH                        = 1,                 /* ������ǿFACH����ʹ��CCCH�߼��ŵ����� */
    WTTFPHY_UL_EFACH_LOCH_TYPE_DCCH_DTCH                   = 2,                 /* ������ǿFACH����ʹ��DCCH�߼��ŵ����� */

    WTTFPHY_UL_EFACH_LOCH_TYPE_BUTT                                             /* ���һ��ö��ֵ */
};
typedef VOS_UINT16 WTTFPHY_UL_EFACH_LOCH_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : WTTFPHY_MAC_RACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ֪ͨ MAC�ײ�״̬��Ϣ,�յ���MACֹͣ���η���

*****************************************************************************/
enum WTTFPHY_MAC_RACH_TYPE_ENUM
{
    WTTFPHY_MAC_RACH_TYPE_NORMAL                           = 1,                 /* ���������������Ϊ��ͨ��ʽ  */
    WTTFPHY_MAC_RACH_TYPE_EFACH                            = 2,                 /* ���������������Ϊ������ǿFACH��ʽ */

    WTTFPHY_MAC_RACH_TYPE_BUTT                                                  /* ���һ��ö��ֵ */
};
typedef VOS_UINT16 WTTFPHY_MAC_RACH_TYPE_ENUM_UINT16;

enum WTTFPHY_PDU_SIZE_TYPE_ENUM
{
    WTTFPHY_PDU_SIZE_FIXED_SIZE_TYPE         = 0,   /*PDU Size�̶���������*/
    WTTFPHY_PDU_SIZE_FLEX_SIZE_TYPE          = 1,   /*PDU Size�ɱ䳤������*/

    WTTFPHY_PDU_SIZE_TYPE_BUTT
};
typedef VOS_UINT16 WTTFPHY_PDU_SIZE_TYPE_ENUM_UINT16;


/* ��ö��ֵ������ΪWTTF��PHY֮��ı�κ�����������±꣬�����Ա�������ܳ���WTTFPHY_ITF_API_MAX_PARA_CNT */
enum WTTFPHY_SLOT0_ISR_PARA_TYPE_ENUM
{
    WTTFPHY_SLOT0_ISR_SFN               = 0,    /* �ص������ĵ�1������ΪSFN */
    WTTFPHY_SLOT0_ISR_CFN               = 1,    /* �ص������ĵ�2������ΪCFN */
    WTTFPHY_SLOT0_ISR_BUTT
};
typedef VOS_UINT16 WTTFPHY_SLOT0_ISR_PARA_TYPE_ENUM_UINT16;

enum WTTFPHY_RL_STATUS_TYPE_ENUM
{
    WTTFPHY_RL_STATUS_USEABLE           = 0,   /*�����ṩ�ɿ������RL����RL����*/
    WTTFPHY_RL_STATUS_UNUSEABLE         = 1,   /*�����ṩ�ɿ������RL����RL������*/

    WTTFPHY_RL_STATUS_TYPE_BUTT
};
typedef VOS_UINT16 WTTFPHY_RL_STATUS_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
enum WTTFPHY_MSG_TYPE_ENUM
{
    ID_MAC_PHY_ACCESS_REQ               = 0x1109,           /* _H2ASN_MsgChoice WTTFPHY_ACCESS_REQ_STRU */
    ID_PHY_MAC_ACCESS_CNF               = 0x3002,           /* _H2ASN_MsgChoice WTTFPHY_ACCESS_CNF_STRU */

    ID_MAC_PHY_E_ACCESS_REQ             = 0x1110,           /* _H2ASN_MsgChoice WTTFPHY_ACCESS_REQ_STRU */
    ID_PHY_MAC_E_ACCESS_CNF             = 0x3016,           /* _H2ASN_MsgChoice WTTFPHY_ACCESS_CNF_STRU */

    ID_MAC_PHY_AMR_DATA_IND             = 0x1101,           /* _H2ASN_MsgChoice WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU */
    ID_PHY_RLC_AMR_DATA_REQ             = 0x3101,           /* _H2ASN_MsgChoice WTTFPHY_AMR_DATA_REQ_BUF_STRU */

    ID_MAC_PHY_DATA_REQ                 = 0x1301,           /* _H2ASN_MsgChoice WTTFPHY_PHY_DATA_REQ_BUF_STRU */
    ID_PHY_MAC_DATA_IND                 = 0x3001,           /* _H2ASN_MsgChoice WTTFPHY_MAC_DATA_IND_TURBO_BUF_STRU */

    ID_PHY_MAC_TFC_BCBD_IND             = 0x3003,           /* _H2ASN_MsgChoice WTTFPHY_MAC_TFC_BCBD_IND_STRU */
    ID_PHY_MAC_DPCCH_PWR_IND            = 0x3004,           /* _H2ASN_MsgChoice WTTFPHY_MAC_DPCCH_PWR_IND_STRU */

    ID_PHY_MAC_HS_PDU_DATA_IND          = 0x3005,           /* _H2ASN_MsgChoice WTTFPHY_MAC_HS_DATA_IND_DATA_BUF_STRU */

    ID_PHY_MAC_BETA_HS_IND              = 0x3006,           /* _H2ASN_MsgChoice WTTFPHY_MAC_BETA_HS_IND_STRU */

    ID_PHY_MAC_COMPRESS_MODE_UPDATE_IND = 0x3008,           /* _H2ASN_MsgChoice WTTFPHY_PHY_MAC_COMPRESS_MODE_UPDATE_IND_STRU */

    ID_MAC_PHY_FLUSH_VITUAL_BO_REQ      = 0x3010,           /* _H2ASN_MsgChoice WTTFPHY_MAC_PHY_E_FLUSH_VIRTUAL_BO_REQ_STRU */

    ID_PHY_MAC_EHS_PDU_DATA_IND         = 0x4001,           /* _H2ASN_MsgChoice WTTFPHY_MAC_EHS_PDU_STRU */

    ID_MAC_PHY_MAC_RESET_REQ            = 0x4004,           /* _H2ASN_MsgChoice WTTFPHY_MAC_RESET_REQ_STRU */
    ID_PHY_MAC_MAC_RESET_CNF            = 0x3018,           /* _H2ASN_MsgChoice WTTFPHY_MAC_RESET_CNF_STRU */

    ID_PHY_MAC_UPA_DATA_STATUS_IND      = 0x3019,           /* _H2ASN_Skip */

    ID_PHY_MAC_RL_STATUS_IND            = 0x3020,           /* _H2ASN_MsgChoice WTTFPHY_PHY_RL_STATUS_IND_STRU */

    ID_MAC_PHY_UPA_PDU_DATA_REQ         = 0x3054,           /* _H2ASN_MsgChoice WTTFMAC_PHY_UPA_DATA_STRU */

    ID_PHY_MAC_UPA_SCHED_STATUS_IND     = 0x3055,           /* _H2ASN_MsgChoice WTTFPHY_PHY_UPA_SCHED_STATUS_IND_STRU */

    ID_RTT_STUB_WTTF_PHY_DATA_REQ       = 0x300e,           /* _H2ASN_Skip */   /* _H2ASN_MsgChoice RTT_STUB_WTTF_PHY_DATA_REQ_STRU */  /*��Ϣͨ��*/
    ID_RTT_STUB_PHY_WTTF_DATA_IND       = 0x300f,           /* _H2ASN_Skip */   /* _H2ASN_MsgChoice RTT_STUB_PHY_WTTF_DATA_IND_STRU */  /*��Ϣͨ��*/

    ID_WTTF_PHY_DL_DECIPHER_PARAM_REQ   = 0x5001,           /* _H2ASN_MsgChoice WTTF_PHY_DL_DECIPHER_PARAM_REQ_STRU */

    ID_MAC_PHY_AMR_DATA_READY_IND       = 0x5002,           /* _H2ASN_MsgChoice WTTFPHY_MAC_PHY_AMR_DATA_READY_IND_STRU */

    WTTFPHY_MSG_TYPE_BUTT
} ;
typedef VOS_UINT16  WTTFPHY_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/******************************************************************************************************
�ṹ��    : WTTFPHY_ACCESS_REQ_STRU
�ṹ˵��  : DSP(PHY)��ARM(HPA)���������е����ݲ�������
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;          /*��Ϣ����*/
    VOS_UINT16                          usOpId;             /*������ʶ*/
    VOS_UINT16                          usAscNum;           /*[0,7],����ҵ����ţ���Ӧ���������������Դ:����ʱ϶��ǰ��ǩ��,���Ͷ�ΪVOS_UINT16��Ϊ����6511��������*/
    VOS_INT16                           sPowerPpm;          /*[-5,10],dB,��Ϣ���Ʋ���(���ΪDPCCH)�����һ��Preamble�ķ��书��֮��,���Ͷ�ΪVOS_INT16��Ϊ����6511��������*/
} WTTFPHY_ACCESS_REQ_STRU;

/******************************************************************************************************
�ṹ��    : WTTFPHY_ACCESS_CNF_STRU
�ṹ˵��  : DSP(PHY)��ARM(HPA)���������е����ݲ�������
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;          /*��Ϣ����*/
    VOS_UINT16                          usOpId;             /*������ʶ*/
    WTTFPHY_ACCESS_ENUM_UINT16          enAccessInfoInd;    /*ȡֵ:MAC_ACCESS_ENUM*/
    WTTFPHY_RF_ENUM_UINT16              enRfExistFlag;      /*RF��Դ���ڱ�־*/
} WTTFPHY_ACCESS_CNF_STRU;

/***********************************************************************************************
�ṹ��    : WTTFPHY_EFACH_ACCESS_REQ_STRU
�ṹ˵��  : WDSP(PHY)��ARM(MAC)���������е���ǿ���������������
***********************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16            enMsgName;          /*��Ϣ����*/
    VOS_UINT16                              usOpId;             /*������ʶ*/
    VOS_UINT16                              usAscNum;           /*[0,7],����ҵ����ţ���Ӧ���������������Դ:����ʱ϶��ǰ��ǩ��,���Ͷ�ΪVOS_UINT16��Ϊ����6511��������*/
    WTTFPHY_UL_EFACH_LOCH_TYPE_ENUM_UINT16  usEFachLochType;    /*[0x1,0x2], 0x1:CCCH; 0x2:DCCH/DTCH */
} WTTFPHY_EFACH_ACCESS_REQ_STRU;

/***********************************************************************************************
�ṹ��    : WTTFPHY_EFACH_ACCESS_CNF_STRU
�ṹ˵��  : WDSP(PHY)��ARM(HPA)���������е���ǿ�������ظ�����
***********************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16         enMsgName;             /*��Ϣ����*/
    VOS_UINT16                           usOpId;                /*������ʶ*/
    WTTFPHY_ACCESS_ENUM_UINT16           enAccessInfoInd;       /*ȡֵ:MAC_ACCESS_ENUM*/
    WTTFPHY_MAC_STATUS_IND_ENUM_UINT16   enAccessStatusInd;     /*ȡֵ:MAC_E_ACCESS_ENUM ����enAccessInfoInd ΪWTTFPHY_AICH_ACKʱ��enAccessStatusInd����Ч
                                                                  enAccessInfoInd ΪWTTFPHY_AICH_ACKʱ, �Ѿ�����E-DCH�ŵ���Դ, �������������:
                                                                  (1)NW�ظ�UE access ACK
                                                                  (2)NW�ظ�UE access NACK+��ЧEAI
                                                                */
} WTTFPHY_EFACH_ACCESS_CNF_STRU;

/***********************************************************************************************
�ṹ��    : WTTFPHY_EFACH_ACCESS_INFO_STRU
�ṹ˵��  : WDSP(PHY)��ARM(MAC)���������е���ǿ�����������
***********************************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16            enMutexFlag;        /* ��д���*/
    VOS_UINT16                           ausReserve1[1];     /* 4�ֽڶ��룬���� */
    WTTFPHY_EFACH_ACCESS_REQ_STRU        stEAccessReq;       /* ��ǿ����������� */
    VOS_UINT16                           ausMagicNum1[4];     /* �����������չ, Ŀǰ�̶�Ϊ0x55AA55AA */
    WTTFPHY_EFACH_ACCESS_CNF_STRU        stEAccessCnf;         /* ��ǿ�������ظ� */
    VOS_UINT16                           ausMagicNum2[4];     /*�����������չ, Ŀǰ�̶�Ϊ0x55AA55AA */
} WTTFPHY_EFACH_ACCESS_INFO_STRU;
/* E_CELL_FACH_UL ADD END */

/******************************************************************************************************
�ṹ��    : WTTFPHY_PHY_RLC_AMR_DATA_REQ_STRU
�ṹ˵��  : DSP(PHY)��ARM(RLC)���������е����ݲ�������
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ԭ���ʶ  */
    VOS_UINT16                          usIf1Head;          /* IF1����֡ͷ��Ϣ */
    VOS_UINT16                          ausAmrData[2];      /* AMR����֡���� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
} WTTFPHY_PHY_RLC_AMR_DATA_REQ_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU
�ṹ˵��  : DSP(PHY)��ARM(MAC)���������е����ݲ�������
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ԭ���ʶ */
    VOS_UINT16                          usIf1Head;          /* IF1����֡ͷ��Ϣ */
    VOS_UINT16                          ausAmrData[2];      /* AMR����֡���� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : WTTFPHY_AMR_DATA_REQ_BUF_STRU
 �ṹ˵��  : DSP(PHY)��ARM(RLC)������AMR����������
             aucData[WTTFPHY_MAX_PHY_DATA_REQ_LEN]ָʾ�����ݲ����������:WTTFPHY_PHY_RLC_AMR_DATA_REQ_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          enMsgName;              /* ��Ϣ��־ ID_CODEC_MAC_AMR_DATA_IND */
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;            /* ��д���*/
    VOS_UINT16                          enCodecType;            /* 0:NB,1:WB ˵����NB����AMR-NB��AMR-NB2��WBָAMR-WB */
    VOS_UINT16                          enFrameType;            /* AMR����֡���� ȡֵ��Χ:0-15 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
} WTTFPHY_AMR_DATA_REQ_BUF_STRU;

/*****************************************************************************
 �ṹ��    : WTTFPHY_AMR_DATA_IND_BUF_STRU
 �ṹ˵��  : DSP(PHY)��ARM(MAC)������AMR����������

             ARM(MAC): ��ǰ��AMR��������д��WTTFPHY_AMR_DATA_IND_BUF_STRU����Ӧ���ݲ��֣�����WTTFPHY_MUTEX_DATA_EXIST,
             DSP(PHY): ��6ms�жϷ��������߸�AMR����,����WTTFPHY_MUTEX_DATA_NOT_EXIST;

             aucData[WTTFPHY_MAX_AMR_DATA_IND_LEN]ָʾ�����ݲ����������:WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausReserve1[1];         /* 4�ֽڶ��룬����*/
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;            /* ��д���*/
    VOS_UINT16                          usDataLen;              /* [0..36],aucData[]���ֳ���,��λ:�ֽڣ���ֵ����4�ı��� */
    VOS_UINT16                          ausReserve2[1];         /* 4�ֽڶ��룬����*/
    VOS_UINT8                           aucData[WTTFPHY_MAX_AMR_DATA_IND_LEN]; /* �������ݣ��������:WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}WTTFPHY_AMR_DATA_IND_BUF_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_UL_TRCH_DATA_STRU
�ṹ˵��  : ���д����ŵ�����:usTfi��usTrchId
******************************************************************************************************/
typedef struct
{
    VOS_UINT16                          usTrchId;           /* [1,32],�����ŵ���ʶ*/
    VOS_UINT16                          usTfi;              /* [0,63],�����ʽ��ʶ */
} WTTFPHY_UL_TRCH_DATA_STRU;


/* WTTFPHY_DL_TRCH_DATA_STRU */
typedef struct
{
    VOS_UINT32                          ulCrcBitMap;        /* ÿ����ָʾһ��������CRC���,����:bit0 =1 ������1�������CRCУ����ȷ��bit3 =0 ������4�������CRCУ�鲻��ȷ */
    VOS_UINT16                          usTrchDataLen;      /* [0��352],��λ:��(32BIT)���������ŵ����ݵĳ��� */
    VOS_UINT8                           ucTfi;              /* [0,63],�����ʽ��ʶ */
    VOS_UINT8                           ucTrchId;           /* [1,32],�����ŵ�ID*/
}WTTFPHY_DL_TRCH_DATA_STRU;


/*****************************************************************************
 �ṹ��    : WTTFPHY_UL_OVER_TIMER_CFG_STRU
 �ṹ˵��  : CELL_DCH̬�ýṹ����Ч
             DSP��6ms�ж�ʱ�����������������以����ΪDATA_NOT_EXIST,
             ��ARM�ṩ�ĸó�ʱ�쳣������������BBP;
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrSchedCfn;     /* ����֡��, ��ǰ����ʱ�̵�CFN */
    VOS_UINT16                          usCurrSchedTrchCnt; /* ��ǰ����ʱ�����д����ŵ�����;ֻ��ӦDCH�����Ƿ񵽴�TTI�߽����ʱ�̾���;*/
    WTTFPHY_UL_TRCH_DATA_STRU           astCurrSchedTrchInfo[PS_WUE_MAX_DCH_NUM];  /* ��ǰ����ʱ�̴����ŵ���Ӧ��TFI�б�,��Ӧ����Ϊ0bps��һ��TFI=0 */

} WTTFPHY_UL_OVER_TIME_CFG_STRU;

/*****************************************************************************
 �ṹ��    : WTTFPHY_PHY_DATA_REQ_BUF_STRU
 �ṹ˵��  : DSP��ARM������DPCH/P-RACH�ŵ�������ṹ

             ARM(MAC): ��ǰ1֡д������,����WTTFPHY_MUTEX_DATA_EXIST,
             DSP(PHY): DSP��6ms�жϷ���������ȶ������ݣ�д��DSP��BBP�Ĺ�����,����WTTFPHY_MUTEX_DATA_NOT_EXIST;
*****************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;            /* ��д��� */
    VOS_UINT16                          ausReserve1[1];         /* 4�ֽڶ��룬�����ֶΣ���ʹ�� */

    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;              /* ԭ��ID */
    WTTFPHY_CCTRCH_ENUM_UINT16          enCctrchID;             /* ������ŵ���ʶ */
    VOS_UINT16                          usCFN;                  /* ��ǰCFN,ֻ��CELL-DCH״̬����Ч */
    VOS_UINT16                          usUlTrchCnt;            /* ���д����ŵ����� */
    WTTFPHY_UL_TRCH_DATA_STRU           astUlTrchDataInfo[PS_WUE_MAX_DCH_NUM];  /* �����ŵ���ǰʹ�õ�TFI�б� */
    VOS_UINT32                          ulSerialNum;            /* ARM��0˳�����,DSP�жϸ�ֵ�Ƿ�˳�����1�������˳�����1����DSP�ṩ����Ϣ�ĳ�����Ϣ*/

    VOS_UINT16                          ausReserve2[1];         /* 4�ֽڶ��룬�����ֶΣ���ʹ�� */
    VOS_UINT16                          usDataLen;              /* ���ݳ���,��λ:�ֽ�,����ֵ����4��������,��Χ[0..WTTFPHY_MAX_PHY_DATA_REQ_LEN-1] */
    VOS_UINT8                           aucData[WTTFPHY_MAX_PHY_DATA_REQ_LEN];   /* �������ݿ� */

    WTTFPHY_UL_OVER_TIME_CFG_STRU       stUlOverTimeCfg;        /* DSP��6ms�ж�ʱ�����������������以����ΪDATA_NOT_EXIST,��ARM�ṩ�ĸó�ʱ�쳣������������BBP;*/

    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

} WTTFPHY_PHY_DATA_REQ_BUF_STRU;



/*****************************************************************************
 �ṹ��    : WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU
 �ṹ˵��  : DSP��ARM������DPCH/S-CCPCH�ŵ���������Ʋ��ֽṹ
******************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;        /* ��д���*/
    VOS_UINT16                          usDataLen;          /* [0..232],��λ:��(32BIT),������ͷ��Ϣ,Ҳ��ֻ����aucData[]�������ݳ��� */

    WTTFPHY_CCTRCH_ENUM_UINT16          enCctrchId;         /* ������ŵ���ʶ */
    VOS_UINT8                           ucCfn;              /* [0..255],CFN */
    VOS_UINT8                           ucDlTrchNum;        /* [0..7],��ǰ�����ϱ������д����ŵ��ĸ��� */

    WTTFPHY_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ԭ��ID */
    VOS_UINT16                          usCctrchIndex;      /* ��������������cctrch�������յ�,����WRR��ͬʱ���ö���cctrch����,ͨ������������*/
    VOS_UINT32                          ulSerialNum;        /* ���ڵ��Թ���,PHY��0��˳�������1��MAC�ж�����2�δ����Ƿ����1��������ǣ���MAC�ṩ�쳣������Ϣ; */

    WTTFPHY_DL_TRCH_DATA_STRU           astDlTrchDataInfo[PS_WUE_MAX_DCH_NUM]; /* �����ŵ�������Ϣ��Ԫ */

    VOS_UINT16                          usSfn;              /*  [0..4095],������յ�����ʱ��Ӧ��SFN */
    VOS_UINT8                           aucReserve1[2];

    VOS_UINT32                          aulReserve2[3];     /* �ӿڱ���*/

    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

} WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU;


/*****************************************************************************
 �ṹ��    : WTTFPHY_MAC_DATA_IND_TURBO_BUF_STRU
 �ṹ˵��  : DSP��ARM��DPCH/S-CCPCH�ŵ��������빲����ṹ

             DSP(PHY): DSP�յ�BBP���������жϺ�,��BBP���ݰ��Ƶ��û�����,����WTTFPHY_MUTEX_DATA_EXIST;

             ARM(HPA): HPA�յ�����0ms�жϷ�������PHY_MAC_INFO_IND��Ϣ��,���ù������ڵ��������ݷ��뻷�ζ��У�
                       ���������WTTFPHY_MUTEX_DATA_NOT_EXIST.
******************************************************************************/
typedef struct
{
    WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU    stPhyMacDataIndCtrlParam;   /*DSP��ARM������DPCH/S-CCPCH�ŵ���������Ʋ��ֽṹ*/
    VOS_UINT8                               aucData[WTTFPHY_MAX_PHY_DATA_IND_TURBO_DATA_LEN];  /*enCctrchId��usTrchIdָ���Ĵ����ŵ��ϵĴ�������,ÿ��TB�����ݺ������CRC�Ƿ���ȷ��ָʾ,�������ݴ�ŷ�ʽ���<Hi4131V100R001-��ϵͳ�ӿ�˵����-WTTF-PHY.doc>˵�� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

} WTTFPHY_MAC_DATA_IND_TURBO_BUF_STRU;



/*****************************************************************************
 �ṹ��    : WTTFPHY_MAC_DATA_IND_VITERBI_BUF_STRU
 �ṹ˵��  : DSP��ARM������DPCH/S-CCPCH�ŵ��������빲����ṹ

             DSP(PHY): DSP�յ�BBP���������жϺ�,��BBP���ݰ��Ƶ��û�����,����WTTFPHY_MUTEX_DATA_EXIST;

             ARM(HPA): HPA�յ�����0ms�жϷ�������PHY_MAC_INFO_IND��Ϣ��,���ù������ڵ��������ݷ��뻷�ζ��У�
                       ���������WTTFPHY_MUTEX_DATA_NOT_EXIST.
******************************************************************************/
typedef struct
{
    WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU    stPhyMacDataIndCtrlParam;   /*DSP��ARM������DPCH/S-CCPCH�ŵ���������Ʋ��ֽṹ*/
    VOS_UINT8                               aucData[WTTFPHY_MAX_PHY_DATA_IND_VTB_DATA_LEN];  /*enCctrchId��usTrchIdָ���Ĵ����ŵ��ϵĴ�������,ÿ��TB�����ݺ������CRC�Ƿ���ȷ��ָʾ,�������ݴ�ŷ�ʽ���<Hi4131V100R001-��ϵͳ�ӿ�˵����-WTTF-PHY.doc>˵�� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

} WTTFPHY_MAC_DATA_IND_VITERBI_BUF_STRU;

/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_TFC_BCBD_IND_STRU
�ṹ˵��  : PHYÿ���յ�RRC�����ú��ϱ�һ��
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;        /* ��д���*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;
    VOS_UINT16                          ausReserve[1];     /* 4�ֽڶ���,�ӿڱ���*/
    VOS_UINT16                          usTfcNum;
    VOS_UINT16                          ausTfcBcBd[PS_WUE_MAX_UL_TFC_NUM];/*��8bitΪBc(Ŀǰʵ��Bc�̶�Ϊ15),��8bitΪBd[1..225]�������±꼴ΪTFCI��RRC��֤����㡢MAC�����±��һ����*/
} WTTFPHY_MAC_TFC_BCBD_IND_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_BETA_HS_IND_STRU
�ṹ˵��  : PHYÿ���յ�RRC�����ú��ϱ�һ��
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;        /* ��д���*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;
    VOS_UINT16                          ausReserve[1];      /* 4�ֽڶ���,�ӿڱ���*/
    VOS_UINT16                          usBetaHs;           /* 25.213 4.2.1.2, ��Чֵ[5,6,8,9,12,15,19,24,30] */
} WTTFPHY_MAC_BETA_HS_IND_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_DPCCH_PWR_IND_STRU
�ṹ˵��  : PHYÿ֡9msʱ�̶�Ҫ�ϱ�
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;        /* ��д���*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;
    VOS_INT16                           asDpcchPwr[WTTFPHY_SLOT_NUM_PER_FRAME]; /*[-500..330],��λ��0.1dBm��0x7fff��ʱ϶��Ӧ�ķ��书����Ч������ѹģʱ϶ */
    VOS_INT16                           sAllowUlMaxPower;  /* �����֪ͨ���������������书�ʣ�����TFC��������ѡ�� ��λ��0.1dBm */
} WTTFPHY_MAC_DPCCH_PWR_IND_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_HS_DATA_IND_BUF_STRU
�ṹ˵��  : R5 HSDPA�ӿ�
******************************************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPhyMacHsDataHead;
    VOS_UINT32                          ulPhyMacHsDataTail;
} WTTFPHY_MAC_HS_DATA_IND_CTRL_BUF_STRU;

typedef struct
{
    VOS_UINT8                           aucHsDschData[WTTFPHY_MAX_HS_PDU_BUF_NUM][WTTFPHY_MAX_HS_PDU_BUF_LEN];
} WTTFPHY_MAC_HS_DATA_IND_DATA_BUF_STRU;

typedef struct
{
    VOS_UINT32                          ulPhyMacEhsDataHead;   /*MAC-ehs header pointer*/
    VOS_UINT32                          ulPhyMacEhsDataTail;
} WTTFPHY_MAC_EHS_DATA_IND_CTRL_BUF_STRU;

typedef struct
{
    VOS_UINT8                           aucEhsDschData[WTTFPHY_MAX_EHS_PDU_BUF_NUM][WTTFPHY_MAX_EHS_PDU_BUF_LEN];
} WTTFPHY_MAC_EHS_DATA_IND_DATA_BUF_STRU;

/*****************************************************************************
 �ṹ��    : WTTF_PHY_DL_DECIPHER_PARAM_STRU
 �ṹ˵��  : DSP(PHY)��ARM(MAC)������AMR�������й�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHfn;                  /* ��ά�ɲ��ã��Ե�֪countC*/
    VOS_UINT16                          usCfn;                  /* ��ǰCFN */
    VOS_UINT16                          ausReserve[1];
    VOS_UINT16                          ausDecipherData[WTTF_PHY_DL_MAX_AMR_DECIPHER_TRCH_NUM][WTTF_PHY_DL_MAX_AMR_DECIPHER_KEY_BYTE_SIZE/2];/*PHY����ʶ��VOS_UINT8*/
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
} WTTF_PHY_DL_DECIPHER_PARAM_STRU;

typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;            /* ��д���*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;              /* ԭ���ʶ */
    VOS_UINT16                          usTrchCnt;              /* AMR�ܴ����ŵ��� */
    VOS_UINT16                          ausTrchId[WTTF_PHY_DL_MAX_AMR_DECIPHER_TRCH_NUM];
    WTTF_PHY_DL_DECIPHER_PARAM_STRU     astDeCipherPara[WTTF_PHY_DL_MAX_AMR_DECIPHER_PARAM_NUM];
} WTTF_PHY_DL_DECIPHER_PARAM_REQ_STRU;

/* V3 R7_7C1 End */

/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU
�ṹ˵��  : HSUPA ARM-DSP���߼��ŵ�����Ŀ�����Ϣ
******************************************************************************************************/
typedef struct
{
    /* [1..15], ֻҪӳ�䵽E-DCH�ŵ�,�߼��ŵ�IDһ������, 15��ʾCCCH */
    VOS_UINT16                          usLochId;

    /*
       ���߼��ŵ���Ӧ�����������ŵ���������, ��λ: �ֽ�
       ����ʹ��MAC-e/i, PS RB:������UE category����д��ֵ�������ڴ�, PS_WUE_MAX_E_DCH_PER_PS_RB_BUF_BYTE_SIZE
                         CS RB:PS_WUE_MAX_E_DCH_PER_CS_RB_BUF_BYTE_SIZE
                         ����:PS_WUE_MAX_E_DCH_PER_S_RB_BUF_BYTE_SIZE
                         RB0:PS_WUE_MAX_E_DCH_CCCH_BUF_BYTE_SIZE
    */
    VOS_UINT16                          usMacPduDataBufLen;

    /* �߼��ŵ��ϳ��ص�PDU size����: fix or flexible */
    WTTFPHY_PDU_SIZE_TYPE_ENUM_UINT16   enPduSizeType;

    /* ��λ:�ֽ�,���������������, pdu size��Ψһֵ,
       ��Loch���ڶ��PDU SIZEʱ, Լ��ʹ����С��PDU SIZE
       CCCHһ��ֻ��һ��PDU SIZE, ����ΪPDU SIZE���а���һ���ֽڵ�CRC
       ����fix sizeʱʹ��
    */
    VOS_UINT16                          usPduSizeByteLen;

    /* ���߼��ŵ���Ӧ�����������ŵ��׵�ַ, Ϊ�̶�ֵ, ���Ǵ˴����ݷ������ʼ��ַ */
    VOS_UINT32                          ulLochDataBufBaseAddr;

    /*
       ARMд,������
       ����flexible sizeʱʹ��:
       ARM���Virtual MAC-is/iʵ��д��MAC-PDUʱ���¡�����һ����д��PduInfo������
       MacPduInfoHeadIdxΪ��Ӧ�߼��ŵ�PduInfo��������±ꡣ
       Ҫ��: ARM��д��PDU�����ڴ��MAC PDU��Ҫͬ����PHY��usMacPduDataBufHeadIdx�����仯, ��ΪARM���������·�
    */
    volatile VOS_UINT16                 usMacPduInfoHeadIdx;

    /*
       ARMд,������
       flexible sizeʱ:
       ARM���Virtual MAC-is/iʵ��д�����ݺ���¡���ֵΪ��һ�����ݷ������ʼ��ַ���ulLochDataBufBaseAddr��ƫ��, ��λ:Byte
       fix sizeʱ:
       ARM���Virtual MAC-es/e or Virtual MAC-is/iʵ��д�����ݺ���¡���ֵΪ��һ�����ݷ������ʼ��ַ���ulLochDataBufBaseAddr��ƫ��, ��λ:Byte
       PHY��usMacPduDataBufHeadIdx�����仯, ��ΪARM���������·�
    */
    volatile VOS_UINT16                  usMacPduDataBufHeadIdx;

    /*
       �����д,ARM��
       flexible sizeʱ:
       [0,15]: MAC PDU Info����һ������MAC PDU Info������(MacPduInfoTailIdx), MacPduInfoTailIdxΪ��Ӧ�߼��ŵ�PduInfo��������±�
       [16,31]: ��һ�����ݷ������ʼ��ַ���ulMacPduDataBufBaseAddr��ƫ��(MacPduDataBufTailIdx), ��λ:Byte
       Ҫ��: PHY���ȡPDU�����ڴ��MAC PDU��Ҫͬ����ͬʱ����MacPduInfoTailIdx��MacPduDataBufTailIdx
       fix sizeʱ:
       [0,15]: ��Ч
       [16,31]: ��һ�����ݷ������ʼ��ַ���ulMacPduDataBufBaseAddr��ƫ��(MacPduDataBufTailIdx), ��λ:Byte
                �������ĵ�λ���ֽ�,usLochBufTailIdx���ӵ�������ֵ��ʼ����usPduSizeByteLen��������
     */
    volatile VOS_UINT32                  ulMacPduInfoTailIdxAndMacPduDataBufTailIdx;

    /*
       ARMд,������
       RLC�����MAC�ĸ��߼��ŵ���BO, ��λ:Byte,
       (ulRlcBoBitLen + Virtual MAC-es/e or Virtual MAC-is/i Loch BO )��ʾ���߼��ŵ�ʵ���ܹ���Ҫ���͵�������
    */
    VOS_UINT32                          ulBoByteLen;
} WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_UPA_DATA_REQ_BUF_STRU
�ṹ˵��  : HSUPA ARM-DSP���߼��ŵ�����Ŀ�����Ϣ
******************************************************************************************************/
typedef struct
{
    /*****************************************************************************
    [0..255],ARM UPA���д�����Ϻ󣬸���CFNֵ,10ms�ڱ������һ�Ρ�
    ��ulNewParaFlag Ϊ��ֵʱ��DSP MAC_E/Iʵ����ÿ����֡����ʱ���жϸ�uwCfn
    �Ƿ���DSP�����ĵ�ǰCFNһ�£������10ms����Ȼû��һ�£������쳣ͳ�ơ�
    *****************************************************************************/
    VOS_UINT32                          ulCfn;

    /*****************************************************************************
    [0,0x33553355]�ò�����Ҫ����DSP��ARM�佨��������Mac-E/Iʱͬ����������á�
    DSP�ڽ���MAC-E/Iʵ���������MAC-E/Iʵ��ļ���ʱ�̵�ʱ������ulNewParaFlag���
    Ϊ0x33553355��֮���ڵ����ж����жϸñ�����Ϊ0x3355335���򲻽����쳣ͳ�ƣ�
    ͬʱ�������������ݷ��ͣ����Ϊ0��������쳣ͳ�ƣ������������ݷ��͡�
    ARM�ڽ��յ�MAC-E/I����������MAC-E/Iʵ��ļ���ʱ�̵�ʱ,���ulNewParaFlag���
    Ϊ0x33553355�������ԭ�еĹ������е����ݣ���������·������ݵ������棬���øñ��
    Ϊ0�������վɲ��������������ݷ��͡�
    *****************************************************************************/
    VOS_UINT32                          ulNewParaFlag;

    /*****************************************************************************
    [0,0x55335533]�ò�����Ҫ����DSP��ARM���ͷ�Mac-E/Iʱͬ����������á�
    DSP���ͷ�MAC-E/Iʵ��ļ���ʱ�̵�ʱ������ulRelParaFlag���Ϊ0x55335533��
    ֮��Ͳ������쳣ͳ�ƣ��������������ݷ��͡�
    ARM���ͷ�MAC-E/Iʵ��ļ���ʱ�̵�ʱ, ����ж�ulRelParaFlag���Ϊ0x55335533��
    ����ջ����е����ݣ��ͷ�Mac-E/Iʵ�壬���øñ��Ϊ0����������������ݷ��͡�
    *****************************************************************************/
    VOS_UINT32                          ulRelParaFlag;

    /* CCCH���� */
    WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU  stMacEDchCCCHRbBuf;

    /* �����±귶Χ:[0..PS_WUE_MAX_LOCH_NUM-1],�±��1ΪLoch IDֵ,
    ����Ԫ��ֵ��Χ:[0..WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM-1],ֵΪastMacEDchSignalRbBuf[]���±�,
    Ҳ��MAC PDU Info����astMacSRbTable[]���±� */
    VOS_UINT32                          aulSignalLochIdx[PS_WUE_MAX_LOCH_NUM];
    VOS_UINT32                          ulEDchSRbCnt;   /* [0..WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM]  */
    WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU  astMacEDchSignalRbBuf[WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM];


    /* �����±귶Χ:[0..PS_WUE_MAX_LOCH_NUM-1],�±��1ΪLoch IDֵ,
    ����Ԫ��ֵ��Χ:[0..WTTFPHY_MAC_UPA_MAX_CS_RB_NUM-1]��ֵΪastMacEDchCsRbBuf[]���±�,
    Ҳ��MAC PDU Info����astMacCsRbTable[]���±� */
    VOS_UINT32                          aulCsLochIdx[PS_WUE_MAX_LOCH_NUM];
    VOS_UINT32                          ulEDchCsRbCnt;   /* [0..WTTFPHY_MAC_UPA_MAX_CS_RB_NUM]*/
    WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU  astMacEDchCsRbBuf[WTTFPHY_MAC_UPA_MAX_CS_RB_NUM];


    /* �����±귶Χ:[0..PS_WUE_MAX_LOCH_NUM-1],�±��1ΪLoch IDֵ,
    ����Ԫ��ֵ��Χ:[0..WTTFPHY_MAC_UPA_MAX_PS_RB_NUM-1]��ֵΪastMacEDchPsRbBuf[]���±�,
    Ҳ��MAC PDU Info����astMacPsRbTable[]���±� */
    VOS_UINT32                          aulPsLochIdx[PS_WUE_MAX_LOCH_NUM];
    VOS_UINT32                          ulEDchPsRbCnt;   /* [0..WTTFPHY_MAC_UPA_MAX_PS_RB_NUM]*/
    WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU  astMacEDchPsRbBuf[WTTFPHY_MAC_UPA_MAX_PS_RB_NUM];
} WTTFPHY_MAC_UPA_DATA_REQ_BUF_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU
�ṹ˵��  : HSUPA ARM-DSP������ӿ�,MAC PDU����ṹ
             usMacPduSize: �䳤size, MAC PDU���ݳ���, ��λbytes
******************************************************************************************************/
typedef struct
{
    VOS_UINT16                          usMacPduSize;   /* MAC PDU���ݳ��ȣ���λbytes*/
}WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_FLEXIBLE_S_RB_PDU_INFO_TABLE_STRU
�ṹ˵��  : ÿ���߼��ŵ���MAC PDU Info��,����ΪPS_WUE_S_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU  astPduInfoList[PS_WUE_S_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH];
}WTTFPHY_MAC_FLEXIBLE_S_RB_PDU_INFO_TABLE_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_FLEXIBLE_CS_RB_PDU_INFO_TABLE_STRU
�ṹ˵��  : ÿ���߼��ŵ���MAC PDU Info��,����ΪPS_WUE_CS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU  astPduInfoList[PS_WUE_CS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH];
}WTTFPHY_MAC_FLEXIBLE_CS_RB_PDU_INFO_TABLE_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_FLEXIBLE_PS_RB_PDU_INFO_TABLE_STRU
�ṹ˵��  : ÿ���߼��ŵ���MAC PDU Info��,����ΪPS_WUE_PS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU  astPduInfoList[PS_WUE_PS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH];
}WTTFPHY_MAC_FLEXIBLE_PS_RB_PDU_INFO_TABLE_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_FLEXIBLE_PDU_INFO_TABLE_STRU
�ṹ˵��  : ȫ���߼��ŵ���MAC PDU Info��,
            SRB   WTTFPHY_MAC_E_MAX_S_RB_NUM��
            CS RB WTTFPHY_MAC_UPA_MAX_CS_RB_NUM��
            PS RB WTTFPHY_MAC_UPA_MAX_PS_RB_NUM��
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MAC_FLEXIBLE_S_RB_PDU_INFO_TABLE_STRU     astMacSRbTable[WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM];
    WTTFPHY_MAC_FLEXIBLE_CS_RB_PDU_INFO_TABLE_STRU    astMacCsRbTable[WTTFPHY_MAC_UPA_MAX_CS_RB_NUM];
    WTTFPHY_MAC_FLEXIBLE_PS_RB_PDU_INFO_TABLE_STRU    astMacPsRbTable[WTTFPHY_MAC_UPA_MAX_PS_RB_NUM];
}WTTFPHY_MAC_FLEXIBLE_PDU_INFO_TABLE_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_PHY_UPA_SCHED_PER_CARRIER_VALUE_STRU
�ṹ˵��  : �ز�Ҫ���ӽṹ
            usGp          �ز���Gp
            usGs          �ز���Gs
            usGn          �ز���Gn
******************************************************************************************************/
typedef struct
{
    VOS_UINT16     usGp;  /* ��Ƶ���ʣ�ฺ��(Gp), [0, 22996], ��λbit */
    VOS_UINT16     usGs;  /* ��Ƶ���õĵ��ȸ���(Gs), [0, 22996], ��λbit */
    VOS_UINT16     usGn;  /* ��Ƶ���õķǵ��ȸ���(Gn), ��λbit */
    VOS_UINT16     ausReserve[1];
}WTTFPHY_PHY_UPA_SCHED_PER_CARRIER_VALUE_STRU;

/******************************************************************************************************
�ṹ��    : WTTFPHY_PHY_UPA_SCHED_STATUS_IND_VALUE_STRU
�ṹ˵��  : ���ز�Ҫ���ӽṹ
******************************************************************************************************/
typedef struct
{
    VOS_UINT16                                      usCfn;           /* [0..255], ��PHY�ڷ���Gֵʱ��д */
    VOS_UINT16                                      usCarrierCnt;    /* ��Ƶ����, �޸���Ƶʱ, ��1, Ŀǰ���2�� */
    /*����Ƶ��Ҫ����������: ����astPerCarrierValue[0]Ϊ����Ƶ, ֮���Ϊ����Ƶ*/
    WTTFPHY_PHY_UPA_SCHED_PER_CARRIER_VALUE_STRU    astPerCarrierValue[PS_WUE_MAX_CARRIER_CNT];
    VOS_UINT16                                      ausExt[4];       /* Ԥ��4��16bit����չ */
}WTTFPHY_PHY_UPA_SCHED_STATUS_IND_VALUE_STRU;

/******************************************************************************************************
�ṹ��    : WTTFPHY_PHY_UPA_SCHED_STATUS_IND_STRU
�ṹ˵��  : �����Ҫ���ӿ�,����8��Ҫ���ӽṹ�Ļ��λ���
            ulHeadIdx ������д����
            ulTailIdx Э��ջ��������
            ����������д����ʱ����û���µ�Ҫ����Ϣ
******************************************************************************************************/
typedef struct
{
   VOS_UINT32                                   ulHeadIdx;    /*������д����*/
   VOS_UINT32                                   ulTailIdx;    /*Э��ջ��������*/
   WTTFPHY_PHY_UPA_SCHED_STATUS_IND_VALUE_STRU  astDCSchedStatusInd[PS_WUE_MAC_E_DCH_STATUS_IND_BUF_SIZE];
}WTTFPHY_PHY_UPA_SCHED_STATUS_IND_STRU;
/* E_CELL_FACH_UL ADD END */


/******************************************************************************************************
�ṹ��    : WTTFPHY_PHY_UPA_BASE_ADDR_INFO_STRU
�ṹ˵��  : ����㹲��������ʵ��ַ�ṹ
            ����3����ַ
            1\PHY Data REQ�����׵�ַ
            2\PDU Info���׵�ַ
            3\PHYҪ����Ϣ�׵�ַ
******************************************************************************************************/
typedef struct
{
    VOS_UINT32      ulPhyDataReqBufAddr; /*WTTFPHY_MAC_UPA_DATA_REQ_BUF_STRU */
    VOS_UINT32      ulPduInfoTableAddr;  /*WTTFPHY_MAC_FLEXIBLE_PDU_INFO_TABLE_STRU*/
    VOS_UINT32      ulSchedStatsIndAddr; /*WTTFPHY_PHY_UPA_SCHED_STATUS_IND_STRU*/
}WTTFPHY_PHY_UPA_BASE_ADDR_INFO_STRU;


/******************************************************************************************************
�ṹ��    : WTTFPHY_PHY_MAC_COMPRESS_MODE_UPDATE_IND_STRU
�ṹ˵��  : Ӳ�л����˺�DSP�������ѹģ����Ϣ����֤��ȷ�ԡ���ϵͳ�л�����Ŀǰ��֧��
******************************************************************************************************/
typedef struct
{
    VOS_UINT16                                  usTGPSI;                        /* TGPS��ʶ       */
    VOS_UINT16                                  usTGPSStaus;                    /* TGPS״̬��־   */
    VOS_UINT16                                  ulTGCnt;                        /* ��¼��TGPS�Ѽ���֡�� */
    VOS_UINT16                                  usReserve1;
} WTTFPHY_TGPS_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16            enMsgName;          /*��Ϣ����*/        /*_H2ASN_Skip*/
    VOS_UINT16                              usOpId;             /*������ʶ*/
    VOS_UINT16                              usCfn;
    VOS_UINT16                              usTGPSCnt;                              /* TGPS���� */
    WTTFPHY_TGPS_INFO_STRU                  astTGPSInfo[PS_WUE_MAX_TGPS_NUM];
} WTTFPHY_PHY_MAC_COMPRESS_MODE_UPDATE_IND_STRU;


/******************************************************************************************************
�ṹ��    : MAC_FLUSH_DATA_PER_LOCH_STRU
�ṹ˵��  : WTTF MAC����Ϣ֪ͨDSP���Vitual BO
             �̶�/����size, ����MAC��ǰ����Data Buf Head��Pdu Info Head����PHY
******************************************************************************************************/
typedef struct
{
    WTTFPHY_PDU_SIZE_TYPE_ENUM_UINT16   enPduSizeType;          /* �߼��ŵ��ϳ��ص�PDU size����: fix or flexible */
    VOS_UINT16                          usLochLabel;            /* ��Χ:[2..65]*/

    VOS_UINT16                          usDataBufEndPos;        /* ��ʾData Buf Head
                                                                   SRB:usEndPos<=(PS_WUE_MAX_E_DCH_PER_S_RB_BUF_BYTE_SIZE),
                                                                   CS TRB:usEndPos<=(PS_WUE_MAX_E_DCH_PER_CS_RB_BUF_BYTE_SIZE)
                                                                   PS TRB:usEndPos<=(PS_WUE_MAX_E_DCH_PER_PS_RB_BUF_BYTE_SIZE);
                                                                */
    VOS_UINT16                          usPduInfoEndPos;        /* ��ʾPdu Info Head
                                                                   SRB:usEndPos<=(PS_WUE_S_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH),
                                                                   CS TRB:usEndPos<=(PS_WUE_CS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH)
                                                                   PS TRB:usEndPos<=(PS_WUE_PS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH)
                                                                */
}MAC_FLUSH_DATA_PER_LOCH_STRU;

/******************************************************************************************************
�ṹ��    : WTTFPHY_MAC_PHY_UPA_FLUSH_VIRTUAL_BO_REQ_STRU
�ṹ˵��  : WTTF MAC����Ϣ֪ͨDSP���Vitual BO ֱ�� usEndPosλ�á�
            ĿǰӦ�ó���:
            (1)��RLC����Resetʱ�������е�Vitual BO������Ա㷢��Reset/Reset ACK PDU;
            (2)��AM/UM RLCʵ����ؽ��������ؽ�����ȫ���ؽ���ʱ��, ����ɵ�rlc pdu size pdu
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;              /*��Ϣ����*/    /*_H2ASN_Skip*/
    VOS_UINT16                          usLochCnt;              /* ��Χ:[1.. PS_WUE_MAX_E_DCH_LOCH_NUM],PS_WUE_MAX_E_DCH_LOCH_NUM =12 */
    MAC_FLUSH_DATA_PER_LOCH_STRU        astEFlushDataPerLoch[PS_WUE_MAX_E_DCH_LOCH_NUM];
} WTTFPHY_MAC_PHY_UPA_FLUSH_VIRTUAL_BO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WTTFPHY_MAC_RESET_REQ_STRU
 Э����  : 11.6.4.8, 25.321, R7
 ASN.1���� :
 �ṹ˵��  : MACʵ�帴λָʾ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16              enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    VOS_INT16                                 sActiveTime;      /* ����ʱ��:
                                                                   Ŀǰ��ֻ��MAC-ehs Treset��ʱ����ʱ����,
                                                                   �̶�Ϊ-1, �������� */
    WTTFPHY_MAC_RESET_TYPE_ENUM_UINT16        enResetType;      /* ��λ����:
                                                                   ��Ȼ��25.321�Ͽ�, Ŀǰֻ��MAC-ehs��λ,
                                                                   ���ǿ��ǵ�Э���ݽ�,
                                                                   ���Ƕ����enResetType, �Ա���չ */
    VOS_UINT16                                ausFeedback[4];   /* �ش���Ϣ(��MAC��д) */
}WTTFPHY_MAC_RESET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WTTFPHY_MAC_RESET_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MACʵ�帴λָʾ��Ӧ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16              enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    WTTFPHY_MAC_RESET_RESULT_ENUM_UINT16      enIndicator;      /* ���ý��,0����ɹ�, ��������ʧ�� */
    VOS_UINT16                                ausFeedback[4];   /* �ش���Ϣ(��PHY��д,
                                                                   ������WTTFPHY_MAC_RESET_REQ_STRU��ausFeedback[4]��ͬ) */
    VOS_UINT16                                usReserve1;
}WTTFPHY_MAC_RESET_CNF_STRU;

/* BBPMASTER�ṩ��������µ�ע��ص��������� */
typedef void (*PVOIDFUNC)(void);

/* ���в����ĺ����ص����� */
typedef VOS_UINT32 (*PRARAFUNC)(VOS_UINT32 ulParaCnt, VOS_UINT32 aulParaValue[]);

/*****************************************************************************
 �ṹ��    : WTTFPHY_PHY_RL_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY��RL Statusָʾ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16              enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    WTTFPHY_RL_STATUS_TYPE_ENUM_UINT16        enRlStatus;       /* RL Status,0�������, 1�������� */
    VOS_UINT16                                usReserve1;
}WTTFPHY_PHY_RL_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : WTTFPHY_MAC_PHY_AMR_DATA_READY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC����PHY��������������Ready��Ϣָʾ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16              enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usReserve1;
}WTTFPHY_MAC_PHY_AMR_DATA_READY_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ȫ�ֱ�������
*****************************************************************************/
/* AMR���ݵ�ַ */
#define WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_ADDR()    WTTF_GetPhyMacDlAmrDecipherAddr()

/* TFCI��ӦBcBd��ַ */
#define WTTFPHY_MAC_DPCCH_PWR_IND_ADDR()          WTTF_GetPhyMacDpcchPwrIndAddr()

/*****************************************************************************
  11 ��������
*****************************************************************************/
#ifdef FEATURE_DSP2ARM
extern WTTFPHY_PHY_UPA_BASE_ADDR_INFO_STRU* WPHY_GetMacPhyUpaBaseAddrInfo(VOS_VOID);
#endif

extern WTTF_PHY_DL_DECIPHER_PARAM_REQ_STRU* WTTF_GetPhyMacDlAmrDecipherAddr(VOS_VOID);
extern WTTFPHY_MAC_DPCCH_PWR_IND_STRU* WTTF_GetPhyMacDpcchPwrIndAddr(VOS_VOID);

/* BBPMASTER�ṩ��������µ�ע��ص����� */
extern VOS_UINT32 PHY_REG_ElectrifyCallFun(PVOIDFUNC   pElectrifyFun);
extern VOS_UINT32 PHY_REG_UnelectrifyCallFun(PVOIDFUNC   pUnelectrifyFun);

/* UPA�ṩ��Ҫ��ע��ص����� */
extern VOS_UINT32 PHY_REG_UpaStatusIndCallFun(PVOIDFUNC   pUpaStatusIndFun);

/* DPA�����ṩ��ע��ص����� */
extern VOS_UINT32 PHY_REG_DpaRptCallFun(PVOIDFUNC   pDpaRptFun);

/* Slot0ʱPHY֪ͨTTF��ע��ص�����,���жϳ����е���ע��Ļص����� */
extern VOS_UINT32 PHY_REG_WcdmaSlot0IsrCallFun(PRARAFUNC pWcdmaSlot0Fun);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of WttfDspInterface.h */


