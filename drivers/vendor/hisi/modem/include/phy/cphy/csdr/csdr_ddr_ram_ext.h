

#ifndef __CSDR_DDR_RAM_EXT_H__
#define __CSDR_DDR_RAM_EXT_H__

#include "product_config.h"

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
 *                     ZSPʹ��DDR�е�ַ�Ķ���                               *
 *                                                                          *
*****************************************************************************/
/*************** HRPD DDR��SDR��CTTF�Ĺ������ݵ�ַ ****************/
#define CSDR_CTTF_HRPD_REQUIRE_LEN          ( 0x4 )     /* ��λ:Byte */
#define CSDR_CTTF_HRPD_F_DATA_BUFFER_LEN    ( 0xF00 )   /* ���й���6Ƭ����buffer��ÿƬ��СΪ640 Byte����3840 Byte */
#define CSDR_CTTF_HRPD_R_DATA_BUFFER_LEN    ( 0x600 )   /* ��������MAC layer packetΪ12288 bit����1536 Byte */

#define CSDR_HRPD_DDR_RAM_BASE              ( CSDR_DDR_RAM_BASE + 0x0 )

/**
 * This address is used to require share-memory address between SDR and MAC in
 * HRPD. To read it, user can know where to inquire the address of
 * CSDR_HRPD_ADDR_INFO_STRU. The start address of CSDR_HRPD_ADDR_INFO_STRU is
 * stored into CSDR_HRPD_REQUIRE_ADDR. So user first read the address stored in
 * CSDR_HRPD_ADDR_INFO_STRU, then jump to CSDR_HRPD_ADDR_INFO_STRU. It's
 * familiar with HSUPA and 1x.
 */
#define CSDR_HRPD_REQUIRE_ADDR              ( CSDR_HRPD_DDR_RAM_BASE )

/* HRPD, CTTF��CSDR ����decode,�������ݶ�Ӧ buffer */
#define CSDR_CTTF_HRPD_F_DATA_BUFFER_ADDR   (  CSDR_HRPD_REQUIRE_ADDR \
                                             + CSDR_CTTF_HRPD_REQUIRE_LEN )

/* HRPD, CTTF��CSDR ����encode, MAC�����buffer */
#define CSDR_CTTF_HRPD_R_DATA_BUFFER_ADDR   ( CSDR_CTTF_HRPD_F_DATA_BUFFER_ADDR \
                                             + CSDR_CTTF_HRPD_F_DATA_BUFFER_LEN )


/*************** 1X DDR��SDR��CTTF�Ĺ������ݵ�ַ ****************/
#define CSDR_CTTF_1X_REQUIRE_LEN            ( 0x4 )
#define CSDR_CTTF_1X_F_DATA_BUFFER_LEN      ( 0xA48 )
#define CSDR_DDR_RAM_FCH_PING_LEN           ( 0x300 )
#define CSDR_DDR_RAM_FCH_PANG_LEN           ( 0x300 )
#define CSDR_DDR_RAM_SCH_PING_LEN           ( 0x3000 )
#define CSDR_DDR_RAM_SCH_PANG_LEN           ( 0x3000 )
#define CSDR_DDR_RAM_SCCH_PING_LEN          ( 0x180 )
#define CSDR_DDR_RAM_SCCH_PANG_LEN          ( 0x180 )
#define CSDR_DDR_RAM_DCCH_PING_LEN          ( 0x300 )
#define CSDR_DDR_RAM_DCCH_PANG_LEN          ( 0x300 )
#define CSDR_DDR_RAM_BCCH_PING_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_BCCH_PANG_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_CCCH_PING_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_CCCH_PANG_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_PCH_PING_LEN           ( 0x180 )
#define CSDR_DDR_RAM_PCH_PANG_LEN           ( 0x180 )
#define CSDR_DDR_RAM_SYNCH_PING_LEN         ( 0x180 )
#define CSDR_DDR_RAM_SYNCH_PANG_LEN         ( 0x180 )

/* 1X��HRPD��ַ���*/
#define CSDR_DDR_RAM_HRPD_1X_PROTECTION_LEN ( 0x10 )

/* 1X��DDR�������ݵ�ַ����HRPD֮�� */
#define CSDR_1X_DDR_RAM_BASE                ( CSDR_CTTF_HRPD_R_DATA_BUFFER_ADDR \
                                             + CSDR_CTTF_HRPD_R_DATA_BUFFER_LEN \
                                             + CSDR_DDR_RAM_HRPD_1X_PROTECTION_LEN )


/* CTTF��SDR ����decode������encodeͷ����ַ��Ϣ,��Ӧ�ṹCTTF_CSDR_1X_ADDR_INFO_STRU */
#define CSDR_CTTF_1X_REQUIRE_ADDR           ( CSDR_1X_DDR_RAM_BASE )

/**
 * This address is used to require share-memory address between SDR and MAC in
 * 1x. To read it, user can know where to inquire the address of
 * CTTF_CSDR_1X_ADDR_INFO_STRU. The start address of
 * CTTF_CSDR_1X_ADDR_INFO_STRU is stored into CTTF_CSDR_1X_REQUIRE_ADDR. So
 * user first read the address stored in CTTF_CSDR_1X_REQUIRE_ADDR, then jump
 * to CTTF_CSDR_1X_ADDR_INFO_STRU. It's familiar with HSUPA.
 */
#define CTTF_CSDR_1X_REQUIRE_ADDR           ( CSDR_CTTF_1X_REQUIRE_ADDR )

/* CTTF��SDR ����decode,�������ݶ�Ӧ buffer ��Ӧ�ṹCSDR_CTTF_1X_F_DATA_BUFFER_STRU */
#define CSDR_CTTF_1X_F_DATA_BUFFER_ADDR     (  CSDR_CTTF_1X_REQUIRE_ADDR \
                                             + CSDR_CTTF_1X_REQUIRE_LEN )

/* DPP���FCH�ŵ�LLR���ping��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_FCH_PING_ADDR          (  CSDR_CTTF_1X_F_DATA_BUFFER_ADDR \
                                             + CSDR_CTTF_1X_F_DATA_BUFFER_LEN )

/* DPP���FCH�ŵ�LLR���pang��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_FCH_PANG_ADDR          (  CSDR_DDR_RAM_FCH_PING_ADDR \
                                             + CSDR_DDR_RAM_FCH_PING_LEN )

/* ����1��FCH LLR�ռ䣬�ֱ��� */
/* DPP���FCH�ŵ�LLR���ping��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_FCH_PING_RSHIFT1_ADDR  (  CSDR_DDR_RAM_FCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_FCH_PANG_LEN )

/* DPP���FCH�ŵ�LLR���pang��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_FCH_PANG_RSHIFT1_ADDR  (  CSDR_DDR_RAM_FCH_PING_RSHIFT1_ADDR \
                                             + CSDR_DDR_RAM_FCH_PING_LEN )

/* DPP���SCH�ŵ�LLR���ping��ſռ�, �ܴ�С12288��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SCH_PING_ADDR          (  CSDR_DDR_RAM_FCH_PANG_RSHIFT1_ADDR \
                                             + CSDR_DDR_RAM_FCH_PANG_LEN )

/* DPP���SCH�ŵ�LLR���pang��ſռ�, �ܴ�С12288��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SCH_PANG_ADDR          (  CSDR_DDR_RAM_SCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SCH_PING_LEN )

/* DPP���SCCH�ŵ�LLR���ping��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SCCH_PING_ADDR         (  CSDR_DDR_RAM_SCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SCH_PANG_LEN )

/* DPP���SCCH�ŵ�LLR���pang��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SCCH_PANG_ADDR         (  CSDR_DDR_RAM_SCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SCCH_PING_LEN )

/* DPP���DCCH�ŵ�LLR���ping��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_DCCH_PING_ADDR         (  CSDR_DDR_RAM_SCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SCCH_PANG_LEN )

/* DPP���DCCH�ŵ�LLR���pang��ſռ�, �ܴ�С768��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_DCCH_PANG_ADDR         (  CSDR_DDR_RAM_DCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_DCCH_PING_LEN )

/* DPP���BCCH�ŵ�LLR���ping��ſռ�, �ܴ�С3072��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_BCCH_PING_ADDR         (  CSDR_DDR_RAM_DCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_DCCH_PANG_LEN )

/* DPP���BCCH�ŵ�LLR���pang��ſռ�, �ܴ�С3072��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_BCCH_PANG_ADDR         (  CSDR_DDR_RAM_BCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_BCCH_PING_LEN )

/* DPP���CCCH�ŵ�LLR���ping��ſռ�, �ܴ�С3072��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_CCCH_PING_ADDR         (  CSDR_DDR_RAM_BCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_BCCH_PANG_LEN )

/* DPP���CCCH�ŵ�LLR���pang��ſռ�, �ܴ�С3072��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_CCCH_PANG_ADDR         (  CSDR_DDR_RAM_CCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_CCCH_PING_LEN )

/* DPP���PCH�ŵ�LLR���ping��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_PCH_PING_ADDR          (  CSDR_DDR_RAM_CCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_CCCH_PANG_LEN )

/* DPP���PCH�ŵ�LLR���pang��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_PCH_PANG_ADDR          (  CSDR_DDR_RAM_PCH_PING_ADDR \
                                             + CSDR_DDR_RAM_PCH_PING_LEN )

/* DPP���SYNCH�ŵ�LLR���ping��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SYNCH_PING_ADDR        (  CSDR_DDR_RAM_PCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_PCH_PANG_LEN )

/* DPP���SYNCH�ŵ�LLR���pang��ſռ�, �ܴ�С384��symbol��ÿ��symbolռ8bit */
#define CSDR_DDR_RAM_SYNCH_PANG_ADDR        (  CSDR_DDR_RAM_SYNCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SYNCH_PING_LEN )

/* CTTF��ENC����ǰ���ݴ�ſռ� */
#define CTTF_CSDR_1X_R_DATA_BUFFER_ADDR     ( CSDR_DDR_RAM_SYNCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SYNCH_PANG_LEN )

//#if ( CSDR_CTTF_HRPD_R_DATA_BUFFER_ADDR % 4 != 0 )
//#error "CSDR_CTTF_HRPD_R_DATA_BUFFER_ADDR needs to be 4 byte aligned!"
//#endif
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


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

#endif /* end of csdr_ddr_ram_ext.h */

