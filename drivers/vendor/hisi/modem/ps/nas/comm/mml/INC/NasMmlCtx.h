
#ifndef _NAS_MML_CTX_H_
#define _NAS_MML_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "ComInterface.h"
#include  "product_config.h"

/* Added by zwx247453 for APR�������, 2015-08-25, begin */
#include  "gunas_errno.h"
/* Added by zwx247453 for APR�������, 2015-08-25, end */

#include "MmcLmmInterface.h"

#include "omringbuffer.h"
#include "NasErrorLog.h"

#include "NasNvInterface.h"

#include "NasMsccPifInterface.h"
#include "CssInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MML_CLASSMARK2_LEN                          (4)                     /* ClassMark2����󳤶� */
#define NAS_MML_CLASSMARK3_LEN                          (33)                     /* ClassMark3����󳤶� */
#define NAS_MML_MAX_IMEISV_LEN                          (16)                    /* Imeisv����󳤶� */
#define NAS_MML_MAX_NETWORK_CAPABILITY_LEN              (9)                     /* network capability����󳤶� */
#define NAS_MML_MAX_UE_NETWORK_CAPABILITY_LEN           (13)                    /* ue network capability����󳤶�*/
#define NAS_MML_MIN_UE_NETWORK_CAPABILITY_LEN           (2)                     /* ue network capability����С����*/
#define NAS_MML_DEFAULT_UE_NETWORK_CAPABILITY_LEN       (4)                     /* ue network capability��Ĭ�ϳ���*/
#define NAS_MML_DEFAULT_UE_NET_CAP_FIRST_VALUE          (0xE0)
#define NAS_MML_DEFAULT_UE_NET_CAP_THIRD_VALUE          (0xC0)
#define NAS_MML_MAX_CS_REG_FAIL_CNT                     (4)                     /* CS����ע��ʧ�ܵ��������ô�����en_NV_Item_Register_Fail_Cnt��ע��ʧ�ܴ������ȡֵ*/
#define NAS_MML_MAX_PS_REG_FAIL_CNT                     (5)                     /* PS����ע��ʧ�ܵ�Э��������*/
#define NAS_MML_DEFAULT_ROAM_BROKER_REG_FAIL_CNT        (2)                     /* PS����CS����ע��ʧ�ܵ�Ĭ�ϴ����������ô������跢������,en_NV_Item_Register_Fail_Cnt��ע��ʧ�ܴ���Ĭ��ֵ */
#define NAS_MML_MAX_IMSI_LEN                            (9)                     /* ����IMSI�ĳ��� */
#define NAS_MML_MAX_PTMSI_LEN                           (4)                     /* ����PTMSI�ĳ��� */
#define NAS_MML_MAX_TMSI_LEN                            (4)                     /* ����TMSI�ĳ��� */
#define NAS_MML_MAX_PTMSI_SIGNATURE_LEN                 (3)                     /* ����PTMSI Signature�ĳ��� */

#define NAS_MML_ADDITIONAL_OLD_RAI_IEI_LEN              (6)                     /* ADDITIONAL OLD RAI ѡ���IEI�ĳ���ֵ */

#define NAS_MML_MAX_NORETRYCAUSE_NUM                        (8)


#define NAS_MML_MAX_LAC_LEN                             (2)                     /* LAC�ĳ��� */
#define NAS_MML_SIM_FORMAT_PLMN_LEN                     (3)                     /* Sim����ʽ��Plmn���� */
#define NAS_MML_PLMN_WITH_RAT_UNIT_LEN                  (5)                     /* sim���д����뼼������Ļ���Ԫ�س��ȣ���6F62�ļ��Ļ������ȵ�ԪΪ5 */
#define NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET          (3)                     /* sim���д����뼼�������н��뼼������ʼλ��ƫ�� */
#define NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET         (4)                     /* sim���д����뼼�������н��뼼������ʼλ��ƫ�� */

#define NAS_MML_DEFAULT_CLASSMARK1_VALUE                (0x57)
#define NAS_MML_DEFAULT_CLASSMARK2_FIRST_VALUE          (0x57)
#define NAS_MML_DEFAULT_CLASSMARK2_SECOND_VALUE         (0x18)
#define NAS_MML_DEFAULT_CLASSMARK2_THIRD_VALUE          (0x81)
#define NAS_MML_DEFAULT_CLASSMARK2_FOURTH_VALUE         (0x00)

#define NAS_MML_DEFAULT_NETWORKCAPABILITY_LEN           (0x02)
#define NAS_MML_DEFAULT_NETWORKCAPABILITY_FIRST_VALUE   (0xE5)
#define NAS_MML_DEFAULT_NETWORKCAPABILITY_SECOND_VALUE  (0x40)
#define NAS_MML_MSG_NAME_ID_LENGTH                      (0x04)
#define NAS_MML_MSG_TIMER_ID_LENGTH                     (0x08)                  /* TIMER��Ϣ�ṹ��ĳ��� */

#define NAS_MML_DEFAULT_IMEI_VALUE                      (0x01)

#define NAS_MML_DEFAULT_MAX_FORB_ROAM_LA_NUM            (10)                    /* Ĭ������ֹ��LA����*/
#define NAS_MML_SIM_PLMN_ID_LEN                         (3)                     /* SIM����PLMN ID�ĳ��� */
#define NAS_MML_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */
#define NAS_MML_CS_LOCI_SIM_FILE_LEN                    (11)                    /* USIM��LOCI�ļ��ĳ��� */
#define NAS_MML_PS_KEY_USIM_FILE_LEN                    (33)                    /* USIM��PSKEY�ļ��ĳ��� */
#define NAS_MML_PS_KC_SIM_FILE_LEN                      (9)                     /* SIM����EFKc�ĳ��� */
#define NAS_MML_CS_KEY_USIM_FILE_LEN                    (33)                    /* USIM��PSKEY�ļ��ĳ��� */
#define NAS_MML_CS_KC_SIM_FILE_LEN                      (9)                     /* SIM����EFKc�ĳ��� */
#define NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE       (4)                     /* EFPSLOCI�ļ���PTMSI Signature��λ�� */
#define NAS_MML_LAI_POS_EFLOCI_FILE                     (4)                     /* EFLOCI�ļ���LAI��λ�� */
#define NAS_MML_RAI_POS_EFPSLOCI_FILE                   (7)                     /* EFPSLOCI�ļ���RAI��λ�� */
#define NAS_MML_CK_POS_EFKEY_FILE                       (1)                     /* EFKEY��CK��λ�� */
#define NAS_MML_PLMN_LOCI_SIM_FILE_LEN                  (14)                    /* USIM��PSLOCI�ļ��ĳ��� */
#define NAS_MML_LRPLMNSI_SIM_FILE_LEN                   (1)                     /* LAST RPLMN SELECTION IND�ļ��ĳ��� */
#define NAS_MML_EHPLMNPI_SIM_FILE_LEN                   (1)                     /* LAST RPLMN SELECTION IND�ļ��ĳ��� */


#define NAS_MML_SIM_FILE_LEN_VALID                      (0x00)                  /* SIM���ļ����ȺϷ�         */
#define NAS_MML_GSMKC_INVALID                           (0x00)                  /* CK��Чֵ�ĺ궨��         */
#define NAS_MML_CK_INVALID                              (0x00)                  /* CK��Чֵ�ĺ궨��         */
#define NAS_MML_IK_INVALID                              (0x00)                  /* IK��Чֵ�ĺ궨��         */
#define NAS_MML_CKSN_INVALID                            (0x07)                  /* CKSN��Чֵ�ĺ궨��       */
#define NAS_MML_IMSI_INVALID                            (0xFF)                  /* IMSI����Чֵ�ĺ궨��     */
#define NAS_MML_PTMSI_INVALID                           (0xFF)                  /* P-TMSI��Чֵ�ĺ궨��                     */
#define NAS_MML_TMSI_INVALID                            (0xFF)                  /* TMSI��Чֵ�ĺ궨��                     */
#define NAS_MML_IMSI_INVALID                            (0xFF)
#define NAS_MML_LAC_LOW_BYTE_INVALID                    (0xFF)                  /* ��Ϣ�б�ɾ����RAI��LAC���ֽڵ�ȡֵ       */
#define NAS_MML_LAC_HIGH_BYTE_INVALID                   (0xFE)                  /* ��Ϣ�б�ɾ����RAI��LAC���ֽڵ�ȡֵ       */
#define NAS_MML_RAC_INVALID                             (0xFF)                  /* ��Ϣ����Ч��RAC��ֵ */
#define NAS_MML_CELLID_INVALID                          (0xFFFFFFFF)
#define NAS_MML_PTMSI_SIGNATURE_INVALID                 (0xFF)                  /* P-TMSI signature����Чȡֵ               */
#define NAS_MML_LAC_INVALID_SPECAL_IN_SIM               (0x00)                  /* SIM�б�ɾ����RAI��LAC��ȡֵ              */
#define NAS_MML_UPDATE_STATUS_MASK_IN_SIM               (0x07)                  /* SIM����update status��bitλ */
#define NAS_MML_LRPLMN_SELECTION_IND_VALID              (0x01)                  /* LAST RPLMN SELECTION IND���ܿ��� */
#define NAS_MML_LRPLMN_SELECTION_IND_INVALID            (0x00)                  /* LAST RPLMN SELECTION IND����δ���� */
#define NAS_MML_MCC_FOURTH_BYTES_VALID                  (0x00)                  /* �жϹ�������ĸ��ֽ�ֻ��Ϊ0 */
#define NAS_MML_MAX_DIGIT_VALUE                         (9)
#define NAS_MML_BYTE_MASK                               (0xFF)

#define NAS_MML_LOW_BYTE_INVALID                        (0x0F)

#define NAS_MML_MCC_LOW_VALUE_MASK                      (0x0000FFFF)
#define NAS_MML_MCC_THIRD_BYTE_VALUE_MASK               (0x00FF0000)
#define NAS_MML_PCS1900_MCC_LOW_VALUE                   (0x00000103)
#define NAS_MML_PCS1900_MCC_HIGH_VALUE_RANGE            (0x00060000)
#define NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0          (0x00)
#define NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F          (0x0F)

#define NAS_MML_INDIA_MCC_LOW_VALUE                     (0x00000004)
#define NAS_MML_INDIA_MCC_LOW_VALUE_RANGE               (0x00040000)
#define NAS_MML_INDIA_MCC_HIGH_VALUE_RANGE              (0x00060000)
#define NAS_MML_OCTET_MOVE_ONE_BITS                     (0x01)                  /* ��һ���ֽ��ƶ�2λ */
#define NAS_MML_OCTET_MOVE_FIVE_BITS                    (0x05)                  /* ��һ���ֽ��ƶ�5λ */
#define NAS_MML_OCTET_EIGHT_BITS                        (0x08)
#define NAS_MML_OCTET_LOW_FIVE_BITS                     (0x1f)                  /* ��ȡһ���ֽ��еĵ�5λ */


#define NAS_MML_INVALID_MCC                             (0xffffffff)            /* MCC����Чֵ */
#define NAS_MML_INVALID_MNC                             (0xffffffff)            /* MNC����Чֵ */
#define NAS_MML_PLMN_ID_ZERO                            (0x00)                  /* ����PLMNid������λȫ0 */
#define NAS_MML_OCTET_LOW_FOUR_BITS                     (0x0f)                  /* ��ȡһ���ֽ��еĵ�4λ */
#define NAS_MML_OCTET_HIGH_FOUR_BITS                    (0xf0)                  /* ��ȡһ���ֽ��еĸ�4λ */
#define NAS_MML_OCTET_LOW_TWO_BITS                      (0x03)                  /* ��ȡһ���ֽ��еĵ�2λ */
#define NAS_MML_OCTET_LOW_THREE_BITS                    (0x07)                  /* ��ȡһ���ֽ��еĵ�3λ */
#define NAS_MML_OCTET_MOVE_TWO_BITS                     (0x02)                  /* ��һ���ֽ��ƶ�2λ */
#define NAS_MML_HO_WAIT_SYS_INFO_DEFAULT_LEN_VALUE      (5000)                  /* CSFB HO��Ĭ�ϵ�ϵͳ��Ϣ��ֵ����λĬ��ΪMS */
#define NAS_MML_ONE_THOUSAND_MILLISECOND                (1000)                  /* 1000MS */

#define NAS_MML_OCTET_MOVE_THREE_BITS                   (0x03)                  /* ��һ���ֽ��ƶ�3λ */
#define NAS_MML_MNC_LENGTH_TWO_BYTES_IN_IMSI            (0x02)

#define NAS_MML_OCTET_MOVE_FOUR_BITS                    (0x04)                  /* ��һ���ֽ��ƶ�4λ */
#define NAS_MML_OCTET_MOVE_EIGHT_BITS                   (0x08)                  /* ��һ���ֽ��ƶ�8λ */
#define NAS_MML_OCTET_MOVE_TWELVE_BITS                  (0x0C)                  /* ��һ���ֽ��ƶ�8λ */
#define NAS_MML_OCTET_MOVE_SIXTEEN_BITS                 (0x10)                  /* ��һ���ֽ��ƶ�16λ */
#define NAS_MML_OCTET_MOVE_TWENTY_FOUR_BITS             (0x18)                 /* ��һ���ֽ��ƶ�24λ */

#define NAS_MML_NET_MODE_BIT_MASK_WAS_SYS_INFO          (0x01)                  /* WRRϵͳ��Ϣ�е�����ģʽ��Ӧ��Bitλ */
#define NAS_MML_ATTATCH_IND_BIT_MASK_WAS_SYS_INFO       (0x01)                  /* WRRϵͳ��Ϣ�е�Attach/Detachģʽ��Ӧ��Bitλ */

#define NAS_MML_INVALID_INDEX                           (0xFFFFFFFF)            /* ��Ч��Indexֵ */

#define NAS_MML_INVALID_EVENT_TYPE                      (0xFFFFFFFF)            /* ��Ч���¼����͵�ֵ */



#define NAS_MML_INVALID_SIM_RAT                         (0x0)                   /* SIM������Ч�Ľ��뼼�� */
#define NAS_MML_SIM_RAT_UTRN                            (0x8000)
#define NAS_MML_SIM_RAT_E_UTRN                          (0x4000)
#define NAS_MML_SIM_RAT_GSM                             (0x0080)
#define NAS_MML_SIM_RAT_GSM_COMPACT                     (0x0040)
#define NAS_MML_SIM_RAT_ALL_SUPPORT                     (0xFFFF)
#define NAS_MML_SIM_ALL_GSM_RAT                         (0x00C0)
#define NAS_MML_SIM_UTRN_GSM_RAT                        (0x8080)
#define NAS_MML_SIM_NO_RAT                              (0x0000)

#define NAS_MML_SIM_ALL_RAT_SUPPORT_LTE                 (0xC0C0)
#define NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE          (0xC080)
#define NAS_MML_SIM_ALL_RAT                             (0x80C0)
#define NAS_MML_SIM_UE_SUPPORT_RAT                      (0x8080)

#define NAS_MML_UMTS_CK_LEN                             (16)                    /* UMTS��CK���� */
#define NAS_MML_UMTS_IK_LEN                             (16)                    /* UMTS��IK���� */
#define NAS_MML_GSM_KC_LEN                              (8)                     /* GSM��KC���� */

#define NAS_MML_MAX_EHPLMN_NUM                          (16)                    /* EHPLMN���ĸ��� */
#define NAS_MML_MAX_HPLMN_WITH_RAT_NUM                  (16)                    /* HPLMNWithRat���ĸ��� */
#define NAS_MML_MAX_USERPLMN_NUM                        (100)                   /* USERPLMN���ĸ��� */

#define NAS_MML_MAX_OPERPLMN_NUM                        (256)                   /* OPERPLMN���ĸ��� */

#define NAS_MML_MAX_SELPLMN_NUM                         (85)                    /* SELPLMN���ĸ��� */

/* PLMN��LA�Ľ�ֹ��Ϣ�Ĵ洢�ṹ */
#define NAS_MML_MAX_FORBPLMN_NUM                        (20)                    /* forbidden PLMNs������ */
#define NAS_MML_MAX_FORBGPRSPLMN_NUM                    (16)                     /* forbidden PLMNs for GPRS service������ */
#define NAS_MML_MAX_FORBLA_FOR_ROAM_NUM                 (16)                    /* forbidden las for roaming�������� */
#define NAS_MML_MAX_FORBLA_FOR_REG_NUM                  (10)                    /* forbidden las for regional provision�������� */

/* �����ϱ���EPLMN�������� */
#define NAS_MML_MAX_NETWORK_EQUPLMN_NUM                 (15)                    /* ��Ч��PLMN��������                     */
/* EPLMN�������� */
#define NAS_MML_MAX_EQUPLMN_NUM                         (18)                    /* ��Ч��PLMN��������                     */

#define NAS_MML_MAX_PLATFORM_RAT_NUM                    (7)                     /* ƽ̨֧�ֵ������뼼������ */
#define NAS_MML_MIN_PLATFORM_RAT_NUM                    (1)                     /* ƽ̨֧�ֵ���С���뼼������ */

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_MML_MAX_RAT_NUM                             (3)                     /* ��ǰ֧�ֵĽ��뼼������ */
#else
#define NAS_MML_MAX_RAT_NUM                             (2)                     /* ��ǰ֧�ֵ�GU���뼼������ */
#endif

#define NAS_MML_MAX_3GPP2_RAT_NUM                       (2)

#define NAS_MML_MAX_ROAM_PLMN_NUM                       (4)                     /* ������������Plmn���� */
#define NAS_MML_DFAULT_NATIONAL_ROAM_PLMN_NUM           (0x01)
#define NAS_MML_DFAULT_NOT_ROAM_PLMN_NUM                (0x00)
#define NAS_MML_DFAULT_NATIONAL_ROAM_MCC                (0x50005)
#define NAS_MML_DFAULT_NATIONAL_ROAM_MNC                (0xF0100)

#define NAS_MML_MAX_NATIONAL_MCC_NUM           (0x05)

#define NAS_MML_MAX_OPER_LONG_NAME_LEN                  (100)                    /* ���ձ��ʵ����չ��255�ֽ�*/
#define NAS_MML_MAX_OPER_SHORT_NAME_LEN                 (100)                    /* ���ձ��ʵ����չ��255�ֽ� */

#define NAS_MML_MAX_WHITE_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */
#define NAS_MML_MAX_BLACK_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

#define NAS_MML_MAX_USER_CFG_IMSI_PLMN_NUM              (6)                     /* �û����õ�����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MML_MAX_USER_CFG_EHPLMN_NUM                 (6)                     /* �û����õ�EHplmn�ĸ��� */

#define NAS_MML_MAX_DISABLED_RAT_PLMN_NUM               (24)                    /* ��ֹ���뼼����PLMN ID�������� */


#define NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM             (8)                     /* ��չ���û����õ�EHplmn���������*/

#define NAS_MML_MAX_ROAMING_REJECT_NO_RETRY_CAUSE_NUM               (8)

#define NAS_MML_MAX_USER_OPLMN_VERSION_LEN               (8)               /* �û����õ�OPLMN�汾����󳤶� */
#define NAS_MML_MAX_USER_OPLMN_IMSI_NUM                  (6)               /* �û����õ�OPLMN����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MML_MAX_USER_CFG_OPLMN_NUM                   (256)             /* �û����õ�OPLMN�������� */
#define NAS_MML_MAX_GROUP_CFG_OPLMN_NUM                  (50)              /* �����������õ�OPLMN�������� */
#define NAS_MML_MAX_USER_CFG_OPLMN_GROUP_INDEX           (5)             /* �������õ������Index,֧������(0-5)��6�� */
#define NAS_MML_OPLMN_WITH_RAT_UNIT_LEN                  (5)               /* �û����õĴ����뼼��OPLMN������Ԫ���ȣ���6F61�ļ��Ļ������ȵ�ԪΪ5 */
#define NAS_MML_MAX_USER_CFG_OPLMN_DATA_LEN              (1280)            /* �û�����OPLMN������ֽ���*/
#define NAS_MML_MAX_GROUP_CFG_OPLMN_DATA_LEN             (250)             /* ��������OPLMN������ֽ���*/

/* �ڲ���Ϣ����������Ϣ����Ϊlist�����������֧��Lʱ1028�ֽڣ�֧��Lʱ1412�ֽ�  */
/* �ڲ���Ϣ���ĳ��� */
#if (FEATURE_ON == FEATURE_LTE)
#define NAS_MML_MAX_INTERNAL_MSG_LEN                    (1500)
#else
#define NAS_MML_MAX_INTERNAL_MSG_LEN                    (1100)
#endif

#if (FEATURE_ON == FEATURE_LTE)
/* �ڲ���Ϣ�������ĳ��� */
#define NAS_MML_MAX_MSG_QUEUE_SIZE                      (36)
#else
/* �ڲ���Ϣ�������ĳ��� */
#define NAS_MML_MAX_MSG_QUEUE_SIZE                      (14)
#endif

/* ��ϢID����Чֵ */
#define NAS_MML_INVALID_INTERNAL_MSG_ID                 (0xFFFF)

/* USIM�ļ���FILE ID */
#define NAS_MML_READ_HPLMN_SEL_FILE_ID                  (0x6F62)
#define NAS_MML_READ_FORBIDDEN_PLMN_LIST_FILE_ID        (0x6F7B)
#define NAS_MML_READ_UPLMN_SEL_FILE_ID                  (0x6F60)
#define NAS_MML_READ_OPLMN_SEL_FILE_ID                  (0x6F61)
#define NAS_MML_READ_HPLMN_PERI_FILE_ID                 (0x6F31)
#define NAS_MML_READ_PLMN_SEL_FILE_ID                   (0x6F30)
#define NAS_MML_READ_MNC_LENGTH_FILE_ID                 (0x6FAD)
#define NAS_MML_READ_UST_FILE_ID                        (0x6F38)
#define NAS_MML_READ_EHPLMN_FILE_ID                     (0x6FD9)
#define NAS_MML_READ_EHPLMNPI_FILE_ID                   (0x6FDB)
#define NAS_MML_READ_LRPLMNSI_FILE_ID                   (0x6FDC)
#define NAS_MML_READ_CS_LOC_FILE_ID                     (0x6F7E)
#define NAS_MML_READ_PS_LOC_FILE_ID                     (0x6F73)
#define NAS_MML_READ_SIM_PS_LOC_FILE_ID                 (0x6f53)
#define NAS_MML_READ_CS_CKIK_FILE_ID                    (0x6F08)
#define NAS_MML_READ_PS_KEY_FILE_ID                     (0x6F09)
#define NAS_MML_READ_CS_KC_FILE_ID                      (0x6F20)
#define NAS_MML_READ_PS_KC_FILE_ID                      (0x6F52)
#define NAS_MML_READ_USIM_CS_KC_FILE_ID                 (0x4F20)
#define NAS_MML_READ_USIM_PS_KC_FILE_ID                 (0x4F52)

#define NAS_MML_READ_ACTING_HPLMN_FILE_ID               (0x4F34)

#define NAS_MML_UE_RFPOWER_INVALID                      (0x1fff)                /* UE RF Power����Чֵ */
#define NAS_MML_UE_FREQ_INVALID                         (0xffff)                /* UE FREQ����Чֵ */
#define NAS_MML_RSSI_UPPER_LIMIT                        (0)                     /* RSSI������ */
#define NAS_MML_RSSI_LOWER_LIMIT                        (-114)                  /* RSSI������ */

#define NAS_MML_RSSI_UNVALID                            (-114)                  /* RSSI����Чֵ */


#define NAS_MML_GSM_CHANNEL_QUAL_INVALID                (99)                    /* Gģ���ŵ���������Чֵ */
#define NAS_MML_UTRA_BLER_INVALID                       (99)                    /* W�������ʵ���Чֵ */
#define NAS_MML_RSCP_UPPER_LIMIT                        (0)                     /* RSCP������ */
#define NAS_MML_RSCP_LOWER_LIMIT                        (-140)                  /* RSCP������ */
#define NAS_MML_UTRA_RSCP_UNVALID                       (-140)                  /* RSCP����Чֵ */
#define NAS_MML_LOWER_RSSI_LEVEL                        (0)                     /* RSSI�ĵȼ� */

/* ע�������Ϣ */
#define NAS_MML_T3212_INFINITE_TIMEOUT_VALUE            (0)
#define NAS_MML_CS_INVALID_DRX_LEN                      (0)
#define NAS_MML_PS_INVALID_DRX_LEN                      (0)

/* ϵͳ���������Ϣ */
#define NAS_MML_LTE_ALL_BAND_SUPPORTED                  (0xFFFFFFFF)
#define NAS_MML_LTE_ALL_BAND_INVALID                    (0x00)

/* С��������� */
#define NAS_MML_AT_CELL_MAX_NUM                         (8)

#define NAS_MML_ADDITIONAL_OLD_RAI_IEI_LEN              (6)                     /* ADDITIONAL OLD RAI ѡ���IEI�ĳ���ֵ */

#define NAS_MML_PC_RECUR_COMPRESS_DATA_LEN              (12000)                 /* PC�ط�ѹ������������ȣ���λ���ֽ� */

#define NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER             (5)                     /* �������εĹ����������� */

#define NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER         (10)                     /* BG�Ѳ����ǹ�����Ĺ����������� */
#define NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST      (5)                     /* ����ԭ��ֵ����б� */

#define NAS_MML_MAX_PS_BEARER_NUM                       (11)                    /* ���PS���ظ��� */
#define NAS_MML_MIN_NSAPI                               (5)                     /* ��ӦNSAPI5 */
#define NAS_MML_MAX_NSAPI                               (15)                    /* ��ӦNSAPI15 */
#define NAS_MML_NSAPI_OFFSET                            (5)                     /* PDP����������������nsapi*/
#define NAS_MML_EMERGENCY_NUM_MAX_LEN                   (46)                    /* Emergency Number information������ֽ��� */
#define NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS          (16)                    /* Emergency Number Lists��������         */
#define NAS_MML_MIN_EMERGENCY_NUM_LEN                   (3)
#define NAS_MML_MAX_EMERGENCY_NUM_LEN                   (48)
#define NAS_MML_MIN_EMERGENCY_NUM_INFO_LEN              (2)
#define NAS_MML_MAX_EMERGENCY_NUM_INFO_LEN              (42)                    /*  */



#define NAS_MML_TAC_LOW_BYTE_INVALID                    (0xFF)
#define NAS_MML_TAC_HIGH_BYTE_INVALID                   (0xFE)


/* 6F31���ļ����� */
#define NAS_MML_HPLMN_PERI_FILE_LEN                     (1)

#define NAS_MML_MAX_SYS_SUBMODE_NUM                     (9)

#define NAS_MML_MAX_IMSI_FORBIDDEN_LIST_NUM             (16)
#define NAS_MML_MAX_RAT_FORBIDDEN_LIST_NUM              (8)


#define NAS_MML_PS_DEFAULT_DRX_SPLIT_PG_CYCLE_CODE      (32)                    /* Ĭ�ϳ�ʼֵ�������Ҫ�������� */
#define NAS_MML_PS_DEFAULT_DRX_SPLIT_ON_CCCH            (0)                     /* Ĭ�ϲ�֧��CCCH�ϵ�Split pg cycle */
#define NAS_MML_PS_DEFAULT_NON_DRX_TIMER                (0)                     /* Ĭ�ϳ�ʼֵ */
#define NAS_MML_PS_UE_UTRAN_DEFAULT_DRX_LEN             (0)                     /* Ĭ�ϳ�ʼֵ */
#define NAS_MML_PS_UE_LTE_DEFAULT_DRX_LEN               (0)                     /* Ĭ�ϳ�ʼֵ */
#define NAS_MML_NON_DRX_TIMER_MAX                       (7)                     /* ��ЧֵΪ0-7 */

#define NAS_MML_MNC_LENGTH_THREE_BYTES_IN_IMSI          (3)                     /*���ж�ȡ��ָʾMNC�ĳ��ȣ�Ĭ��Ϊ3*/

#define NAS_MML_SIGN_REPORT_MSG_TYPE                     (7)                    /* nas����RRMM_AT_MSG_REQʱ����һ�����ö�������
                                                                                   RRC_NAS_AT_CELL_SIGN|RRC_NAS_AT_CELL_ID|RRC_NAS_AT_CELL_BLER*/
#define NAS_MML_NET_RAT_TYPE_INVALID                    (0xFF)

#define NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX         (0XFFFFFFFF)
#define NAS_MML_T3212_START_SCEAN_MASK1_MAX_BIT_INDEX       (31)                /* BIT0~BIT31 */
#define NAS_MML_T3212_START_SCENE_VALID_BIT_INDEX_VALUE     (1)
#define NAS_MML_T3212_DEFAULT_UNIT_LEN                      (6 * 60)            /* 360s */
#define NAS_MML_T3212_CFG_MAX_VALUE                         (18 * 60 * 60)      /* 18Сʱ */

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_MML_ENABLE_LTE_TIMER_DEFAULT_LEN            (5 * 60 * 1000)         /* Ĭ��enable lte timerʱ��5���� */
#endif

#define NAS_MML_SIXTY_SECOND                            (60)                    /* 60�� */
#define NAS_MML_SIXTY_MINUTE                            (60)                    /* 60min */


#define NAS_MML_PS_TRANSFER_FROM_MODEM1_TO_MODEM0           (1)

#define NAS_MML_CS_REG_END_SESSION_DEFAULT_DELAY_TIME       (1000)              /* CsRegĬ���ӳ�ʱ�� */
#define NAS_MML_PS_REG_END_SESSION_DEFAULT_DELAY_TIME       (2000)              /* PsRegĬ���ӳ�ʱ�� */
#define NAS_MML_CS_REG_END_SESSION_MAX_DELAY_TIME           (10000)             /* CsReg����ӳ�ʱ�� */
#define NAS_MML_PS_REG_END_SESSION_MAX_DELAY_TIME           (10000)             /* PsReg����ӳ�ʱ�� */

#define NAS_MML_CALL_MAX_UMTS_CODEC_TYPE_NUM                (7)
#define NAS_MML_CALL_UMTS_CODEC_TYPE_AMR                    (5)
#define NAS_MML_CALL_UMTS_CODEC_TYPE_AMR2                   (6)
#define NAS_MML_CALL_UMTS_CODEC_TYPE_AMRWB                  (10)

#define NAS_MML_CALL_BC_MAX_SPH_VER_NUM                     (6)
#define NAS_MML_CALL_BC_VAL_SPH_VER_FR_1                    (0)
#define NAS_MML_CALL_BC_VAL_SPH_VER_FR_2                    (2)
#define NAS_MML_CALL_BC_VAL_SPH_VER_FR_3                    (4)
#define NAS_MML_CALL_BC_VAL_SPH_VER_HR_1                    (1)
#define NAS_MML_CALL_BC_VAL_SPH_VER_HR_3                    (5)
#define NAS_MML_CALL_BC_VAL_SPH_VER_FR_5                    (8)

#define NAS_MML_MAX_LOG_EVENT_STATE_NUM                     (60)                /* ����������Ϣ���ֵ */

#define NAS_MML_DEFAULT_T3402_LEN                           (12 * 60 * 1000)         /* T3402��ʱ��Ĭ��ʱ��12����*/
#define NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM                    (16)
#define NAS_MML_MAX_TIME_SLICE                              (0xFFFFFFFF)

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-10-10, begin */
#define NAS_MML_MAX_TIME_TICK                               (0xFFFFFFFF)
#define NAS_MML_SECOND_TO_TICK                              (100)
#define NAS_MML_CUSTOMIZED_FORB_LA_TIMER_PRECISION          (100) 
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-10-10, end */

#define NAS_MML_ONE_SECOND_TIME_SLICES                      (32768)                  /* �ݶ�1sʹ��32Kʱ��������, 1s = 1*32K slice = 32768 slice */

#define NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_DEFAULT_LEN (35)               /* mt csfb��PAGING RSP����ȥ��LAU�ɹ��ı�����ʱ��ʱ������λ�� */
#define NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MIN_LEN (10)                   /* mt csfb��PAGING RSP����ȥ��LAU�ɹ��ı�����ʱ�����ʱ�� */
#define NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MAX_LEN (60)                   /* mt csfb��PAGING RSP����ȥ��LAU�ɹ��ı�����ʱ�����ʱ�� */
#define NAS_MML_VOICE_NOT_PREFER_DISABLED_PLMN_MAX_INVALID_PERIOD       (0xFF)

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM                   (16) /* LTE OOS������2G����3G */
#endif

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
#define NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM                   (16)
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_MML_SIM_TYPE_ENUM_UINT8
 ö��˵��  : ��ǰSIM��������,SIM����USIM��
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_SIM_TYPE_ENUM
{
    NAS_MML_SIM_TYPE_SIM                , /* SIM�� */
    NAS_MML_SIM_TYPE_USIM               , /* USIM�� */
    NAS_MML_SIM_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MML_SIM_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8
 �ṹ˵��  : SIM����UE��ģʽ������ģʽ�����ģʽ
  1.��    ��   : 2011��5��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_SIM_UE_OPER_MODE_ENUM
{
    NAS_MML_SIM_UE_NORMAL_MODE                = 0x00,                           /* normal operation*/
    NAS_MML_SIM_UE_NORAML_SPECIFIC_MODE       = 0x01,                           /* normal operation + specific facilities*/
    NAS_MML_SIM_UE_MAINTENACE_MODE            = 0x02,                           /* maintenance (off line)*/
    NAS_MML_SIM_UE_CELLTEST_MODE              = 0x04,                           /* cell test operation*/
    NAS_MML_SIM_UE_APPROVAL_MODE              = 0x80,                           /* type approval operations*/
    NAS_MML_SIM_UE_APPROVAL_SPECIFIC_MODE     = 0x81,                           /* type approval operations + specific facilities.*/
    NAS_MML_SIM_UE_OPER_MODE_BUTT
};
typedef VOS_UINT8 NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8;


enum NAS_MML_NET_RAT_TYPE_ENUM
{
    NAS_MML_NET_RAT_TYPE_GSM         = NAS_MSCC_PIF_NET_RAT_TYPE_GSM,           /* GSM���뼼�� */
    NAS_MML_NET_RAT_TYPE_WCDMA       = NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    NAS_MML_NET_RAT_TYPE_LTE         = NAS_MSCC_PIF_NET_RAT_TYPE_LTE,           /* LTE���뼼�� */
    NAS_MML_NET_RAT_TYPE_1X          = NAS_MSCC_PIF_NET_RAT_TYPE_1X,            /* 1X���뼼�� */
    NAS_MML_NET_RAT_TYPE_HRPD        = NAS_MSCC_PIF_NET_RAT_TYPE_HRPD,          /* 1X���뼼�� */
    NAS_MML_NET_RAT_TYPE_BUTT                                                   /* ��Ч�Ľ��뼼�� */
};
typedef NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 NAS_MML_NET_RAT_TYPE_ENUM_UINT8;


enum NAS_MML_3GPP2_RAT_TYPE_ENUM
{
    NAS_MML_3GPP2_RAT_TYPE_CDMA1X,
    NAS_MML_3GPP2_RAT_TYPE_HRPD,
    NAS_MML_3GPP2_RAT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8;


enum NAS_MML_PLATFORM_RAT_TYPE_ENUM
{
    NAS_MML_PLATFORM_RAT_TYPE_GSM,           /* GSM���뼼�� */
    NAS_MML_PLATFORM_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    NAS_MML_PLATFORM_RAT_TYPE_TD_SCDMA,      /* TDSCDMA���뼼�� */
    NAS_MML_PLATFORM_RAT_TYPE_LTE,           /* LTE���뼼�� */
    NAS_MML_PLATFORM_RAT_TYPE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT8 NAS_MML_PLATFORM_RAT_TYPE_ENUM_UINT8;
/*****************************************************************************
 ö����    : NAS_MML_NET_MODE_ENUM_UINT8
 �ṹ˵��  : ����ģʽ
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_NET_MODE_ENUM
{
    NAS_MML_NET_MODE_INVALID,                                                   /* ����ģʽ�Ƿ� */
    NAS_MML_NET_MODE_I,                                                         /* ����ģʽI */
    NAS_MML_NET_MODE_II,                                                        /* ����ģʽII */
    NAS_MML_NET_MODE_III,                                                       /* ����ģʽIII */
    NAS_MML_NET_MODE_BUTT                                                       /* ��Ч������ģʽ */
};
typedef VOS_UINT8 NAS_MML_NET_MODE_ENUM_UINT8;
enum NAS_MML_3GPP_REL_ENUM
{
    NAS_MML_3GPP_REL_R4,                                                        /* R4 */
    NAS_MML_3GPP_REL_R5,                                                        /* R5 */
    NAS_MML_3GPP_REL_R6,                                                        /* R6 */
    NAS_MML_3GPP_REL_R7,                                                        /* R7 */
	NAS_MML_3GPP_REL_R8,                                                        /* R8 */
    NAS_MML_3GPP_REL_R9,                                                        /* R9 */
    NAS_MML_3GPP_REL_R10,                                                       /* R10 */

    NAS_MML_3GPP_REL_R11,                                                       /* R11 */

    NAS_MML_3GPP_REL_BUTT                                                       /* ��Чֵ */
};
typedef VOS_UINT8 NAS_MML_3GPP_REL_ENUM_UINT8;


enum NAS_MML_GMM_PROC_TYPE_ENUM
{
    NAS_MML_GMM_PROC_TYPE_ATTACH        = 0, /*ע��, ��������PSע������ע��*/
    NAS_MML_GMM_PROC_TYPE_NORMAL_RAU    = 1, /*����·��������,��������PS·�������º����·��������*/
    NAS_MML_GMM_PROC_TYPE_PERIOD_RAU    = 2, /*������·��������,��������PS·�������º����·��������*/
    NAS_MML_GMM_PROC_TYPE_INVALID       = 3  /*��Ч������*/
};

typedef VOS_UINT16 NAS_MML_GMM_PROC_TYPE_ENUM_UINT16;


enum NAS_MML_GMM_PROC_FLAG_ENUM
{
    NAS_MML_GMM_PROC_FLAG_START       = 0, /*ע��, ��������PSע������ע��*/
    NAS_MML_GMM_PROC_FLAG_FINISH      = 1, /*����·��������,��������PS·�������º����·��������*/
    NAS_MML_GMM_PROC_FLAG_INVALID     = 2  /*��Чֵ*/
};
typedef VOS_UINT16 NAS_MML_GMM_PROC_FLAG_ENUM_UINT16;
enum NAS_MML_SM_PROC_FLAG_ENUM
{
    NAS_MML_SM_PROC_FLAG_START       = 0,  /* psҵ��ʼ*/
    NAS_MML_SM_PROC_FLAG_FINISH      = 1, /* psҵ����� */
    NAS_MML_SM_PROC_FLAG_INVALID     = 2  /*��Чֵ*/
};
typedef VOS_UINT8 NAS_MML_SM_PROC_FLAG_ENUM_UINT8;



/*****************************************************************************
 ö����    : NAS_MML_MSC_REL_ENUM_UINT8
 �ṹ˵��  : MS�ϱ�MSC�İ汾
 1.��    ��   : 2011��6��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_MSC_REL_ENUM
{
    NAS_MML_MSC_REL_R97,                                                        /* Rel.97���ն���PS/CS��������ϱ��Լ���Rel.97�汾���ն� */
    NAS_MML_MSC_REL_R99,                                                        /* Rel.99���ն���PS/CS��������ϱ��Լ���Rel.99�汾���նˣ� */
    NAS_MML_MSC_REL_AUTO,                                                       /* Auto���ն˸��ݽ�������ȡ����Ϣ�������ϱ��Լ���Э��ȼ���Ĭ��ֵ�� */
    NAS_MML_MSC_REL_BUTT
};
typedef VOS_UINT8 NAS_MML_MSC_REL_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MML_SGSN_REL_ENUM_UINT8
 �ṹ˵��  : MS�ϱ�SGSN�İ汾
 1.��    ��   : 2011��6��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_SGSN_REL_ENUM
{
    NAS_MML_SGSN_REL_R97,                                                       /* Rel.97���ն���PS/CS��������ϱ��Լ���Rel.97�汾���ն� */
    NAS_MML_SGSN_REL_R99,                                                       /* Rel.99���ն���PS/CS��������ϱ��Լ���Rel.99�汾���նˣ� */
    NAS_MML_SGSN_REL_AUTO,                                                      /* Auto���ն˸��ݽ�������ȡ����Ϣ�������ϱ��Լ���Э��ȼ���Ĭ��ֵ�� */
    NAS_MML_SGSN_REL_BUTT
};
typedef VOS_UINT8 NAS_MML_SGSN_REL_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MML_TIN_TYPE_ENUM_UINT8
 �ṹ˵��  : TIN������
  1.��    ��   : 2011��6��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����Ӳ�������
*****************************************************************************/
enum NAS_MML_TIN_TYPE_ENUM
{
    NAS_MML_TIN_TYPE_PTMSI,                                                     /* TIN����ΪPTMSI */
    NAS_MML_TIN_TYPE_GUTI,                                                      /* TIN����ΪGUTI */
    NAS_MML_TIN_TYPE_RAT_RELATED_TMSI,                                          /* TIN����ΪRAT_RELATED_TMSI */
    NAS_MML_TIN_TYPE_INVALID,                                                   /* TIN������Ч */
    NAS_MML_TIN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MML_TIN_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MML_LAST_RPLMN_SEL_IND_ENUM_UINT8
 �ṹ˵��  :  EFLRPLMNSI�ļ�������This EF contains an indication to the ME for
              the selection of the RPLMN or the home network at switch on, or
              following recovery from lack of coverage.Last RPLMN Selection Indication
  1.��    ��   : 2011��6��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����Ӳ�������
*****************************************************************************/
enum NAS_MML_LAST_RPLMN_SEL_IND_ENUM
{
    NAS_MML_LAST_RPLMN_SEL_IND_RPLMN,                                           /* The UE shall attempt registration on the last RPLMN*/
    NAS_MML_LAST_RPLMN_SEL_IND_HPLMN,                                           /* The UE shall attempt registration on the home network */
    NAS_MML_LAST_RPLMN_SEL_IND_BUTT
};
typedef VOS_UINT8 NAS_MML_LAST_RPLMN_SEL_IND_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MML_EHPLMN_PRESENT_IND_ENUM_UINT8
 �ṹ˵��  :  EF_EHPLMNPI�ļ�������This EF contains an indication to the ME for
              the presentation of the available EHPLMN(s) during I-WLAN selection procedures.
  1.��    ��   : 2011��6��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����Ӳ�������
*****************************************************************************/
enum NAS_MML_EHPLMN_PRESENT_IND_ENUM
{
    /* '00' - No preference for the display mode
    -   '01' - Display the highest-priority available EHPLMN only
    -   '02' - Display all the available EHPLMNs*/

    NAS_MML_EHPLMN_PRESENT_IND_NO_PREF  = 0x00,
    NAS_MML_EHPLMN_PRESENT_IND_HIGHEST  = 0x01,
    NAS_MML_EHPLMN_PRESENT_IND_ALL      = 0x02,
    NAS_MML_EHPLMN_PRESENT_IND_BUTT
};
typedef VOS_UINT8 NAS_MML_EHPLMN_PRESENT_IND_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MML_ROAM_CAPABILITY_ENUM_UINT8
 �ṹ˵��  :  ��¼����������
  1.��    ��   : 2011��6��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����Ӳ�������
*****************************************************************************/
enum NAS_MML_ROAM_CAPABILITY_ENUM
{
    NAS_MML_ROAM_NATION_ON_INTERNATION_ON       = 0,                            /* �������ڹ������� */
    NAS_MML_ROAM_NATION_ON_INTERNATION_OFF      = 1,                            /* �����������Σ��رչ������� */
    NAS_MML_ROAM_NATION_OFF_INTERNATION_ON      = 2,                            /* �رչ������Σ������������� */
    NAS_MML_ROAM_NATION_OFF_INTERNATION_OFF     = 3,                            /* �رչ��ڹ������� */
    NAS_MML_ROAM_BUTT
};
typedef VOS_UINT8 NAS_MML_ROAM_CAPABILITY_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MML_MS_MODE_ENUM_UINT8
 �ṹ˵��  :  ��¼�ֻ�ģʽ
  1.��    ��   : 2011��6��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����Ӳ�������
*****************************************************************************/
enum NAS_MML_MS_MODE_ENUM
{
    NAS_MML_MS_MODE_PS_CS,                                                      /* CS��PS��֧�� */
    NAS_MML_MS_MODE_PS_ONLY,                                                    /* ��֧��PS�� */
    NAS_MML_MS_MODE_CS_ONLY,                                                    /* ��֧��CS�� */
    NAS_MML_MS_MODE_NULL,                                                       /* ��֧���κ��� */
    NAS_MML_MS_MODE_BUTT
};
typedef VOS_UINT8 NAS_MML_MS_MODE_ENUM_UINT8;



enum NAS_MML_LTE_CS_SERVICE_CFG_ENUM
{
    NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS = 1,           /* ֧��cs fallback��sms over sgs*/
    NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY,                   /* ֧��sms over sgs only*/
    NAS_MML_LTE_SUPPORT_1XCSFB,                              /* ֧��1XCSFB */
    NAS_MML_LTE_SUPPORT_BUTT
};
typedef VOS_UINT8 NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8;
enum NAS_MML_LTE_UE_OPERATION_MODE_ENUM
{
    NAS_MML_LTE_UE_OPERATION_MODE_PS_1,              /* operation mode Ϊps mode1 */
    NAS_MML_LTE_UE_OPERATION_MODE_PS_2,              /* operation mode Ϊps mode2 */
    NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1,           /* operation mode Ϊcs ps mode1 */
    NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2,           /* operation mode Ϊcs ps mode2 */
    NAS_MML_LTE_UE_OPERATION_MODE_BUTT
};
typedef VOS_UINT8 NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8;


enum NAS_MML_LTE_UE_USAGE_SETTING_ENUM
{
    NAS_MML_LTE_UE_USAGE_SETTING_VOICE_CENTRIC,      /* �������� */
    NAS_MML_LTE_UE_USAGE_SETTING_DATA_CENTRIC,       /* �������� */
    NAS_MML_LTE_UE_USAGE_SETTIN_BUTT
};

typedef VOS_UINT8 NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8;


enum NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM
{
    NAS_MML_CS_VOICE_ONLY,                                /* ��֧��CS���� */
    NAS_MML_IMS_PS_VOICE_ONLY,                            /* ��֧��IMS PS���� */
    NAS_MML_CS_VOICE_PREFER_IMS_PS_VOICE_AS_SECONDARY,    /* CS�������ȣ�IMS PS������֮ */
    NAS_MML_IMS_PS_VOICE_PREFER_CS_VOICE_AS_SECONDARY,    /* IMS PS�������ȣ�CS������֮ */
    NAS_MML_VOICE_DOMAIN_PREFER_BUTT
};

typedef VOS_UINT8 NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8;



enum NAS_MML_CSFB_SERVICE_STATUS_ENUM
{
    NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST,                     /* Ŀǰ������CSFB���� */
    NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST,            /* Ŀǰ��CSFB��MO������ҵ�������� */
    NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST,            /* Ŀǰ��CSFB��MO������ҵ�������� */
    NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST,            /* Ŀǰ��CSFB�Ľ����������� */
    NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST,                      /* Ŀǰ��CSFB��MT������ */
    NAS_MML_CSFB_SERVICE_STATUS_BUTT
};

typedef VOS_UINT8 NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8;
enum NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM
{
    NAS_MML_ADDITION_UPDATE_RSLT_NO_ADDITION_INFO = 0,                          /* û�ж������Ϣ */
    NAS_MML_ADDITION_UPDATE_RSLT_CSFB_NOT_PREFERRED,                            /* CS Fallback not preferred*/
    NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY,                                      /* ����ֻ֧�ֶ���  */
    NAS_MML_ADDITION_UPDATE_RSLT_BUTT
};

typedef VOS_UINT8 NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8;
enum NAS_MML_TIMER_INFO_ENUM
{
    NAS_MML_TIMER_STOP = 0,
    NAS_MML_TIMER_START,
    NAS_MML_TIMER_EXP,
    NAS_MML_TIMER_BUTT
};
typedef VOS_UINT8 NAS_MML_TIMER_INFO_ENUM_UINT8;


enum NAS_MML_PS_BEARER_STATE_ENUM
{
    NAS_MML_PS_BEARER_STATE_INACTIVE = 0,                                       /* ������ȥ����״̬ */
    NAS_MML_PS_BEARER_STATE_ACTIVE,                                             /* �����ļ���״̬ */
    NAS_MML_PS_BEARER_STATE_BUTT
};
typedef VOS_UINT8 NAS_MML_PS_BEARER_STATE_ENUM_UINT8;


enum NAS_MML_PS_BEARER_ISR_ENUM
{
    NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT,                                     /* �����ļ�����ISR����ǰ */
    NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT,                                      /* �����ļ�����ISR����� */
    NAS_MML_PS_BEARER_EXIST_BUTT
};
typedef VOS_UINT8 NAS_MML_PS_BEARER_ISR_ENUM_UINT8;




enum NAS_MML_REG_FAIL_CAUSE_ENUM
{

    /* UE�����ཻ����Э����ȷ�������������ԭ��ֵ����չ��ΧΪ[0,255], */
    NAS_MML_REG_FAIL_CAUSE_NULL                                     = 0  ,      /* NULL����ԭ��                          */
    NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR                      = 2  ,      /* IMSI unknown in HLR                      */
    NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS                               = 3  ,      /* Illegal MS                               */
    NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR                      = 4  ,      /* IMSI unknown in VLR                      */
    NAS_MML_REG_FAIL_CAUSE_IMSI_NOT_ACCEPTED                        = 5  ,      /* IMSI not accepted                        */
    NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME                               = 6  ,      /* Illegal ME                               */
    NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW                      = 7  ,      /* GPRS services not allowed                */
    NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW    = 8  ,      /* GPRS services and non-GPRS               */
                                                                                /* services not allowed                     */
    NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED                        = 9  ,      /* MS identity cannot be derived            */
                                                                                /* by the network                           */
    NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED                        = 10 ,      /* Implicitly detached                      */
    NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW                           = 11 ,      /* PLMN not allowed                         */
    NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW                             = 12 ,      /* Location area not allowed                */
    NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW                           = 13 ,      /* Roaming not allowed in                   */
                                                                                /* this location area                       */
    NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN              = 14 ,      /* GPRS services not allowed in this PLMN   */
    NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL                          = 15 ,      /* No Suitable Cells In Location Area       */
    NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE                          = 16 ,      /* MSC temporarily not reachable            */
    NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE                          = 17 ,      /* Network failure                          */

    NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_NOT_AVAILABLE                  = 18,       /* CS domain not available                  */

    NAS_MML_REG_FAIL_CAUSE_ESM_FAILURE                              = 19 ,      /* ESM failure                              */
    NAS_MML_REG_FAIL_CAUSE_MAC_FAILURE                              = 20 ,      /* MAC failure                              */
    NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE                            = 21 ,      /* Synch failure                            */
    NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION                     = 22 ,      /* Congestion                               */
    NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE                     = 23 ,      /* GSM authentication unacceptable          */
    NAS_MML_REG_FAIL_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG              = 25,       /* Not authorized for this CSG              */
    NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT                     = 32 ,      /* Service option not supported             */
    NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE               = 33 ,      /* Requested service option not subscribed  */
    NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER                    = 34 ,      /* Service option temporarily out of order  */
    NAS_MML_REG_FAIL_CAUSE_CALL_CANNOT_IDENTIFY                     = 38 ,      /* Call cannot be identified                */
    NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE             = 39 ,      /* NAS_EMM_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE */
    NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT                       = 40 ,      /* No PDP context activated                 */

    NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE                   = 42,       /* severe network failure */

    NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN                = 48 ,      /* retry upon entry into a new cell (min)   */
    NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL                    = 60 ,      /* retry upon entry into a new cell         */
    NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX                = 63 ,      /* retry upon entry into a new cell (max)   */
    NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG               = 95 ,      /* Semantically incorrect message           */
    NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF                    = 96 ,      /* Invalid mandatory information            */
    NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE               = 97 ,      /* Message type non-existent or             */
                                                                                /* not implemented                          */

    NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE                  = 98 ,      /* Message type not compatible with the     */
                                                                                /* protocol state                           */

    NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED               = 99 ,      /* Information element non-existent or      */
                                                                                /* not implemented                          */
    NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR                     = 100,      /* Conditional IE error                     */
    NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE                       = 101,      /* Message not compatible with              */
                                                                                /* protocol state                           */
    NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR                           = 111,      /* Protocol error, unspecified              */

    /* ����������������ԭ��ֵ����չ��ΧΪ[256,300], */
    NAS_MML_REG_FAIL_CAUSE_AUTH_REJ                                 = 256,      /* ��Ȩ����                                */
    NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED                            = 257,      /* access barred                            */
    NAS_MML_REG_FAIL_CAUSE_COMB_REG_CS_FAIL_OTHER_CAUSE             = 258,      /* other cause expcept #2,#16,#17 and #22 */

    /* UE���Ը�������н���ʧ�ܵľܾ�ԭ��ֵ����չ��ΧΪ[301,400] */
    NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT                            = 301,      /* Timer timeout                            */
    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL                         = 302,      /* RR connection establish failure          */
    NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL                             = 303,      /* RR connection failure                    */
    NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT                            = 304,      /* RR connection abort                      */

    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL_RANDOM_ACCESS_REJECT    = 305,      /*����ʧ��ԭ��ֵϸ��Ϊ�������ʧ�� */

    /* UEδ��������н���ʧ�ܵľܾ�ԭ��ֵ����չ��ΧΪ[401,500] */
    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE                              = 401,      /* Other cause                              */
    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT                = 402,      /* UE����Ϊ��ǰ��֧��                   */
    NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN                           = 403,      /* �Լ���ǰ����Forbidden��Ϣ��            */
    NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS            = 404,      /* �� #12 ע�ᱻ��                      */
    NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM                    = 405,      /* �� #13��#15ע�ᱻ��                  */
    NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS                  = 406,      /* �� #14 ע�ᱻ��                      */
    NAS_MML_REG_FAIL_CAUSE_SIM_INVALID                              = 407,      /* ����Ч                                */
    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI                               = 408,      /* ����detach imsi��ԭ��ֵ                 */
    NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT          = 409,      /* ��������ϢĿǰ��֧�ָ���               */
    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES                = 410,

    NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW                      = 411,      /* psע���ǲ�����ע��                   */
    NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE                         = 412,      /* ESM���ؽ���ʧ�� */
    NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE                        = 413,      /* ע��������û�����detach��ע��ʧ��    */
    NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE                        = 414,      /* ע��������յ�����detach��Ϣ��ע��ʧ�� */
    NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING                            = 415,      /* ע��ʧ��ԭ��T3402��ʱ��������          */

    NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU                    = 416,      /* CSͨ�Ź������ӳٽ���LAU         */

    NAS_MML_REG_FAIL_CAUSE_ECALL_INACTIVE                           = 417,      /*  ��ǰMM����ecall inactive״̬         */

    NAS_MML_REG_FAIL_CAUSE_T3212_RUNNING                            = 418,      /* ע��ʧ��ԭ��T3212��ʱ�������� */

    NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC                    = 419,      /* HO���̽����δ�ϱ�ϵͳ��Ϣ�������CSFB��GU DELAY LAUʱ����ԭ��ֵ */

    /* UEδ��������н����ɹ���ԭ��ֵ */
    NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL                               = 500  ,      /* SUCC����ԭ��                          */

    NAS_MML_REG_FAIL_CAUSE_BUTT
} ;

typedef VOS_UINT16 NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16;

enum NAS_MML_SIM_AUTH_FAIL_ENUM
{
    NAS_MML_SIM_AUTH_FAIL_NULL                  = 0,
    NAS_MML_SIM_AUTH_FAIL_GSM_AUT_UNACCEPTABLE  = 1,
    NAS_MML_SIM_AUTH_FAIL_MAC_FAILURE           = 2,
    NAS_MML_SIM_AUTH_FAIL_SYNC_FAILURE          = 3,
    NAS_MML_SIM_AUTH_FAIL_UMTS_OTHER_FAILURE    = 4,
    NAS_MML_SIM_AUTH_FAIL_GSM_OTHER_FAILURE     = 5,
    NAS_MML_SIM_AUTH_FAIL_LTE_OTHER_FAILURE     = 6,
    NAS_MML_SIM_AUTH_FAIL_BUTT
};
typedef VOS_UINT16 NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16;

/*****************************************************************************
 ö����    : NAS_MML_PLMN_FORBID_TYPE_ENUM_UINT8
 �ṹ˵��  : forbid plmn������
 1.��    ��   : 2011��7��11��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_PLMN_FORBID_TYPE_ENUM
{
    NAS_MML_PLMN_FORBID_NULL                = 0x00,    /* ����δ����ֹ*/                                                      /* ����ģʽI */
    NAS_MML_PLMN_FORBID_PLMN                = 0x01,    /* Plmn����ֹ*/                                                          /* ����ģʽI */
    NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS       = 0x02,    /* Plmn for gprs����ֹ*/                                                     /* ����ģʽII */
    NAS_MML_PLMN_FORBID_ROAM_LA             = 0x04,    /* Plmn for roam LAI����ֹ*/
    NAS_MML_PLMN_FORBID_REG_LA              = 0x08,    /* Plmn for reg LAI����ֹ*/
    NAS_MML_PLMN_FORBID_BUTT                           /* ��Ч������ģʽ */
};
typedef VOS_UINT8 NAS_MML_PLMN_FORBID_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8
 �ṹ˵��  : routing update status
 1.��    ��   : 2011��7��11��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
    0   0   0   :   updated.
    0   0   1   :   not updated.
    0   1   0   :   PLMN not allowed.
    0   1   1   :   Routing Area not allowed.
*****************************************************************************/
enum NAS_MML_ROUTING_UPDATE_STATUS_ENUM
{
    NAS_MML_ROUTING_UPDATE_STATUS_UPDATED,                                  /* 24008Э��4.1.2.2�½�������U1 UPDATED */
    NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED,                              /* 24008Э��4.1.2.2�½�������U2 NOT UPDATED */
    NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED,                         /* ���ܿ���Чʱ����Ϊ��ֵ */
    NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED,                 /* 24008Э��4.1.2.2�½�������U3 ROAMING NOT ALLOWED */
    NAS_MML_ROUTING_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8;


enum NAS_MML_LOCATION_UPDATE_STATUS_ENUM
{
    NAS_MML_LOCATION_UPDATE_STATUS_UPDATED,
    NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED,
    NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED,
    NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED,
    NAS_MML_LOCATION_UPDATE_DISABLED,
    NAS_MML_LOCATION_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_MML_REG_RESULT_ENUM_U8
 �ṹ˵��  : ע����
 1.��    ��   : 2011��7��11��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_REG_RESULT_ENUM
{
    NAS_MML_REG_RESULT_SUCCESS,                          /* ע��ɹ� */
    NAS_MML_REG_RESULT_FAILURE,                          /* ע��ʧ�� */
    NAS_MML_REG_RESULT_ACCESS_BAR,                       /* �����ֹ */
    NAS_MML_REG_RESULT_TIMER_EXP,                        /* ��������Ӧ */
    NAS_MML_REG_RESULT_CN_REJ,                           /* ������ܾ� */
    NAS_MML_REG_RESULT_FORBID,                           /*��ֹ��Ϣ������ATTACH*/
    NAS_MML_REG_RESULT_AUTH_REJ,                         /* ��Ȩʧ�� */
    NAS_MML_REG_RESULT_BUTT
};
typedef VOS_UINT8 NAS_MML_REG_RESULT_ENUM_UINT8;


enum NAS_MML_REG_STATUS_ENUM
{
    NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH       = NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH,       /* δע��δ���� */
    NAS_MML_REG_REGISTERED_HOME_NETWORK         = NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK,         /* ע�ᣬע���� HOME PLMN */
    NAS_MML_REG_NOT_REGISTERED_SEARCHING        = NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING,        /* δע�ᣬ��������PLMN�������ڸ��Ź��� */
    NAS_MML_REG_REGISTERED_DENIED               = NAS_MSCC_PIF_REG_REGISTERED_DENIED,               /* ע�ᱻ�ܾ�����ǰ�û�����������ע�ᣬ�������񱻽�ֹ */
    NAS_MML_REG_UNKNOWN                         = NAS_MSCC_PIF_REG_UNKNOWN,                         /* ������� */
    NAS_MML_REG_REGISTERED_ROAM                 = NAS_MSCC_PIF_REG_REGISTERED_ROAM,                 /* ע�ᣬע���ڷ� HOME PLMN */
    NAS_MML_REG_STATUS_BUTT
};
typedef NAS_MSCC_PIF_REG_STATE_ENUM_UINT8 NAS_MML_REG_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MML_RRC_INTEGRITY_PROTECT_ENUM
 �ṹ˵��  : ע����
 1.��    ��   : 2011��7��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_RRC_INTEGRITY_PROTECT_ENUM
{
    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE         = 0,                              /* �����Ա���δ����    */
    NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE           = 1,                              /* �����Ա�������    */
    NAS_MML_RRC_INTEGRITY_PROTECT_BUTT
};

typedef VOS_UINT8 NAS_MML_RRC_INTEGRITY_PROTECT_ENUM_UINT8;



enum NAS_MML_PROC_TYPE_ENUM
{
    NAS_MML_PROC_ATTACH,
    NAS_MML_PROC_MT_DETACH,
    NAS_MML_PROC_LOCAL_DETACH,
    NAS_MML_PROC_UE_DETACH,
    NAS_MML_PROC_TAU,
    NAS_MML_PROC_RAU,
    NAS_MML_PROC_LAU,
    NAS_MML_PROC_AUTH,
    NAS_MML_PROC_SER,
    NAS_MML_PROC_CM_SER,
    NAS_MML_PROC_COMBINED_ATTACH,
    NAS_MML_PROC_COMBINED_RAU,
    NAS_MML_PROC_PERIODC_RAU,
    NAS_MML_PROC_MM_ABORT,
    NAS_MML_PROC_BUTT
};
typedef VOS_UINT32 NAS_MML_PROC_TYPE_ENUM_U32;


enum NAS_MML_GAS_SUBMODE_ENUM
{
    NAS_MML_GAS_SUBMODE_GSM             = 0,
    NAS_MML_GAS_SUBMODE_GPRS            = 1,
    NAS_MML_GAS_SUBMODE_EDGE            = 2,
    NAS_MML_GAS_SUBMODE_BUTT
};


/*****************************************************************************
 ö����    : NAS_MML_INIT_CTX_TYPE_ENUM_UINT8
 �ṹ˵��  : ��ʼ��MML CTX��Ϣ����
 1.��    ��   : 2011��7��14��
   ��    ��   : zhoujun 40661
   �޸�����   : ����
*****************************************************************************/
enum NAS_MML_INIT_CTX_TYPE_ENUM
{
    NAS_MML_INIT_CTX_STARTUP                    = 0,
    NAS_MML_INIT_CTX_POWEROFF                   = 1,
    NAS_MML_INIT_CTX_BUTT
};
typedef VOS_UINT32 NAS_MML_INIT_CTX_TYPE_ENUM_UINT8;


enum NAS_MML_PERSISTENT_BEARER_STATE_ENUM
{
    NAS_MML_PERSISTENT_BEARER_STATE_NOT_EXIST = 0,
    NAS_MML_PERSISTENT_BEARER_STATE_EXIST     = 1,
    NAS_MML_PERSISTENT_BEARER_STATE_BUTT
};

typedef VOS_UINT8 NAS_MML_PERSISTENT_BEARER_STATE_ENUM_UINT8;




enum    NAS_MML_READ_SIM_FILES_CNF_ENUM
{
    NAS_MML_READ_USIM_FILE_FLG_NULL                         = 0x0,
    NAS_MML_READ_HPLMN_SEL_FILE_ID_FLG                      = 0x1,
    NAS_MML_READ_FORBIDDEN_PLMN_LIST_FILE_ID_FLG            = 0x2,
    NAS_MML_READ_UPLMN_SEL_FILE_ID_FLG                      = 0x4,
    NAS_MML_READ_OPLMN_SEL_FILE_ID_FLG                      = 0x8,
    NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG                     = 0x10,
    NAS_MML_READ_PLMN_SEL_FILE_ID_FLG                       = 0x20,
    NAS_MML_READ_MNC_LENGTH_FILE_ID_FLG                     = 0x40,
    NAS_MML_READ_UST_FILE_ID_FLG                            = 0x80,
    NAS_MML_READ_EHPLMN_FILE_ID_FLG                         = 0x100,
    NAS_MML_READ_EHPLMNPI_FILE_ID_FLG                       = 0x200,
    NAS_MML_READ_LRPLMNSI_FILE_ID_FLG                       = 0x400,
    NAS_MML_READ_CS_LOC_FILE_ID_FLG                         = 0x800,
    NAS_MML_READ_PS_LOC_FILE_ID_FLG                         = 0x1000,
    NAS_MML_READ_SIM_PS_LOC_FILE_ID_FLG                     = 0x2000,
    NAS_MML_READ_CS_CKIK_FILE_ID_FLG                        = 0x4000,
    NAS_MML_READ_PS_KEY_FILE_ID_FLG                         = 0x8000,
    NAS_MML_READ_CS_KC_FILE_ID_FLG                          = 0x10000,
    NAS_MML_READ_PS_KC_FILE_ID_FLG                          = 0x20000,
    NAS_MML_READ_USIM_CS_KC_FILE_ID_FLG                     = 0x40000,
    NAS_MML_READ_USIM_PS_KC_FILE_ID_FLG                     = 0x80000,

    NAS_MML_READ_ACTING_HPLMN_FILE_ID_FLG                   = 0x100000,

    NAS_MML_READ_USIM_FILE_CNF_BUTT
};

typedef VOS_UINT32 NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32;


enum NAS_MML_PLMN_TYPE_ENUM
{
    NAS_MML_PLMN_TYPE_BCCH,
    NAS_MML_PLMN_TYPE_SIM,
    NAS_MML_PLMN_TYPE_UNKNOW,
    NAS_MML_PLMN_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MML_PLMN_TYPE_ENUM_UINT8;


enum NAS_MML_LTE_CAPABILITY_STATUS_ENUM
{
    NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS               = 0,        /* LTE���Բ�����,��δ֪ͨ����� */
    NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS               = 1,        /* LTE���Բ�����,��֪ͨ����� */
    NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_UNNOTIFY_AS              = 2,        /* LTE���Իָ�����,��δ֪ͨ����� */
    NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS              = 3,        /* LTE���Իָ�����,��֪ͨ����� */
    NAS_MML_LTE_CAPABILITY_STATUS_BUTT                              = 4         /* ��Чֵ */
};
typedef VOS_UINT32 NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32;
enum NAS_MML_RRC_SYS_SUBMODE_ENUM
{
    NAS_MML_RRC_SYS_SUBMODE_NULL                  = 0,                /* �޷��� */
    NAS_MML_RRC_SYS_SUBMODE_GSM                   = 1,                /* GSMģʽ */
    NAS_MML_RRC_SYS_SUBMODE_GPRS                  = 2,                /* GPRSģʽ */
    NAS_MML_RRC_SYS_SUBMODE_EDGE                  = 3,                /* EDGEģʽ */
    NAS_MML_RRC_SYS_SUBMODE_WCDMA                 = 4,                /* WCDMAģʽ */
    NAS_MML_RRC_SYS_SUBMODE_HSDPA                 = 5,                /* HSDPAģʽ */
    NAS_MML_RRC_SYS_SUBMODE_HSUPA                 = 6,                /* HSUPAģʽ */
    NAS_MML_RRC_SYS_SUBMODE_HSDPA_HSUPA           = 7,                /* HSDPA+HSUPAģʽ */
    NAS_MML_RRC_SYS_SUBMODE_LTE                   = 8,                /* LTEģʽ */
    NAS_MML_RRC_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8;
enum NAS_MML_NETWORK_MSG_REL_VER_ENUM
{
    NAS_MML_NETWORK_MSG_REL_VER_98_OR_OLDER        = 0,
    NAS_MML_NETWORK_MSG_REL_VER_99_ONWARDS         = 1,
    NAS_MML_NETWORK_MSG_REL_VER_BUTT
};
typedef VOS_UINT8   NAS_MML_NETWORK_MSG_REL_VER_ENUM_UINT8;



enum NAS_MML_NETWORK_SGSN_REL_VER_ENUM
{
    NAS_MML_NETWORK_SGSN_REL_VER_98_OR_OLDER        = 0,
    NAS_MML_NETWORK_SGSN_REL_VER_99_ONWARDS         = 1,
    NAS_MML_NETWORK_SGSN_REL_VER_BUTT
};
typedef VOS_UINT8   NAS_MML_NETWORK_SGSN_REL_VER_ENUM_UINT8;


enum NAS_MML_RESTRICTION_CHANGE_ENUM
{
    NAS_MML_RESTRICTION_NO_CHANGE                   = 0,
    NAS_MML_RESTRICTION_BAR_TO_UNBAR                = 1,
    NAS_MML_RESTRICTION_UNBAR_TO_BAR                = 2,
    NAS_MML_RESTRICTION_BUTT
};

typedef VOS_UINT8   NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8;


enum NAS_MML_HPLMN_TYPE_ENUM
{
    NAS_MML_HPLMN_TYPE_HPLMN,                                                   /* HPLMN */
    NAS_MML_HPLMN_TYPE_EHPLMN,                                                  /* EHPLMN */
    NAS_MML_HPLMN_TYPE_ACTING_HPLMN,                                            /* ACTING-HPLMN */
    NAS_MML_HPLMN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MML_HPLMN_TYPE_ENUM_UINT8;
enum NAS_MML_REG_DOMAIN_ENUM
{
    NAS_MML_REG_DOMAIN_CS    = 0x01,                                            /* ע������ΪCS�� */
    NAS_MML_REG_DOMAIN_PS    = 0x02,                                            /* ע������ΪPS�� */
    NAS_MML_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MML_REG_DOMAIN_ENUM_UINT8;


enum NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
{
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION                    = 1,            /* �������� */
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON                    = 2,            /* ����פ�� */
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION           = 3,            /* ������ѡ���� */
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON                   = 4,            /* ����פ�� */

    NAS_MML_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION            = 5,            /* ������������ע�ᷢ����������HOME�����ϲ���Ч */

    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT
};
typedef VOS_UINT8 NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8;
enum NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM
{
    NAS_MML_LTE_PS_REG_CONTAIN_DRX_PARA                     = 0,                /* LTE ATTACH��TAUЯ����DRX���� */
    NAS_MML_LTE_PS_REG_NOT_CONTAIN_DRX_PARA                 = 1,                /* LTE ATTACH��TAUδЯ��DRX���� */
    NAS_MML_GU_PS_REG_CONTAIN_DRX_PARA                      = 2,                /* GU ATTACH��RAUЯ����DRX���� */
    NAS_MML_GU_PS_REG_NOT_CONTAIN_DRX_PARA                  = 3,                /* GU ATTACH��RAUδЯ��DRX���� */
    NAS_MML_PS_REG_CONTAIN_BUTT
};
typedef VOS_UINT8 NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8;



enum NAS_MML_IMS_NORMAL_REG_STATUS_ENUM
{
    NAS_MML_IMS_NORMAL_REG_STATUS_DEREG        = 0x00,
    NAS_MML_IMS_NORMAL_REG_STATUS_DEREGING     = 0x01,
    NAS_MML_IMS_NORMAL_REG_STATUS_REGING       = 0x02,
    NAS_MML_IMS_NORMAL_REG_STATUS_REG          = 0x03,

    NAS_MML_IMS_NORMAL_REG_STATUS_BUTT         = 0xFF
};
typedef VOS_UINT8 NAS_MML_IMS_NORMAL_REG_STATUS_ENUM_UINT8;



enum NAS_MML_NW_IMS_VOICE_CAP_ENUM
{
    NAS_MML_NW_IMS_VOICE_NOT_SUPPORTED    = 0,
    NAS_MML_NW_IMS_VOICE_SUPPORTED        = 1,

    NAS_MML_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT8 NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8;



enum NAS_MML_AUTO_SRCH_FLG_TYPE_ENUM
{
    NAS_MML_AUTO_SRCH_FLG_TYPE_RPLMN_FIRST               = 0,                /* �Զ���������ʱ������RPLMN */
    NAS_MML_AUTO_SRCH_FLG_TYPE_PLMN_SEL_IND              = 1,      /* PLMN SEL IND�ļ�6FDC�л�ȡPLMN */
    NAS_MML_AUTO_SRCH_FLG_TYPE_HPLMN_FIRST               = 2,                /* �Զ���������ʱ������HPLMN */
    NAS_MML_AUTO_SRCH_FLG_TYPE_RPLMN_WITH_HPLMN_FIRST    = 3,                /* �Զ���������ʱ������RPLMN����ʱ���HPLMN */
    NAS_MML_SEARCH_HPLMN_FLG_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MML_AUTO_SRCH_FLG_TYPE_ENUM_UINT8;




enum NAS_MML_CALL_MODE_ENUM
{
    NAS_MML_ECALL_ONLY            = 0,
    NAS_MML_ECALL_AND_NORMAL_CALL = 1,
    NAS_MML_CALL_MODE_BUTT
};
typedef VOS_UINT8 NAS_MML_CALL_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_MML_LMM_ACCESS_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum NAS_MML_LMM_ACCESS_TYPE_ENUM
{
    NAS_MML_LMM_ACCESS_TYPE_EUTRAN_TDD      = NAS_MSCC_PIF_LMM_ACCESS_TYPE_EUTRAN_TDD,
    NAS_MML_LMM_ACCESS_TYPE_EUTRAN_FDD      = NAS_MSCC_PIF_LMM_ACCESS_TYPE_EUTRAN_FDD,
    NAS_MML_LMM_ACCESS_TYPE_BUTT
};
typedef NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM_UINT8 NAS_MML_LMM_ACCESS_TYPE_ENUM_UINT8;

/* Added by n00355355 for �����ؽ�, 2015-9-24, begin */
/*****************************************************************************
 ö����    : NAS_MML_CS_TRANSACTION_ENUM_UINT8
 �ṹ˵��  : NAS_MML_CS_TRANSACTION_ENUM_UINT8 enCsTransactionTypeȡֵ
  1.��    ��   : 2015��9��24��
    ��    ��   : n00355355
    �޸�����   : �����ؽ�:
                 note:��RRC_NAS_CS_TRANSACTION_ENUM_UINT8����һ��
*****************************************************************************/
enum NAS_MML_CS_TRANSACTION_ENUM
{
    NAS_MML_CS_TRANSACTION_NO_EXIST                   = 0,                         /* ������CSFB ���� */
    NAS_MML_CS_TRANSACTION_MO_NORMAL_EXIST            = 1,                         /* ����CSFB ����ҵ��(CC/SS)���� */
    NAS_MML_CS_TRANSACTION_EMERGENCY_EXIST            = 2,                         /* ����CSFB ������������ */
    NAS_MML_CS_TRANSACTION_MT_EXIST                   = 3,                         /* ����CSFB �������� */
    NAS_MML_CS_TRANSACTION_BUTT
};
typedef VOS_UINT8 NAS_MML_CS_TRANSACTION_ENUM_UINT8;
/* Added by n00355355 for �����ؽ�, 2015-9-24, end */

enum NAS_MML_CALL_STATUS_ENUM
{
    /* csfb mo normal call */
    NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START,                                    /* csfb mo ��ͨ���н�����ʼ */
    NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_SUCC,                                     /* csfb mo ��ͨ���н����ɹ� */
    NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_FAIL,                                     /* csfb mo ��ͨ���н���ʧ�� */

    /* csfb mo emergency call */
    NAS_MML_CSFB_MO_EMC_CALL_SETUP_START,                                       /* csfb mo �������н�����ʼ */
    NAS_MML_CSFB_MO_EMC_CALL_SETUP_SUCC,                                        /* csfb mo �������н����ɹ� */
    NAS_MML_CSFB_MO_EMC_CALL_SETUP_FAIL,                                        /* csfb mo �������н���ʧ�� */

    /* mo normal call */
    NAS_MML_MO_NORMAL_CALL_SETUP_START,                                         /* GU�����н�����ʼ */
    NAS_MML_MO_NORMAL_CALL_SETUP_SUCC,                                          /* GU�����н����ɹ� */
    NAS_MML_MO_NORMAL_CALL_SETUP_FAIL,                                          /* GU�����н���ʧ�� */

    /* mo emergency call */
    NAS_MML_MO_EMC_CALL_SETUP_START,                                            /* GU�½������н�����ʼ */
    NAS_MML_MO_EMC_CALL_SETUP_SUCC,                                             /* GU�½������н����ɹ� */
    NAS_MML_MO_EMC_CALL_SETUP_FAIL,                                             /* GU�½������н���ʧ�� */

    NAS_MML_CALL_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MML_MO_CALL_STATUS_ENUM_UINT8;


enum NAS_MML_SS_STATUS_ENUM
{
    /* csfb mo normal call */
    NAS_MML_CSFB_MO_SS_SETUP_START,                                             /* csfb mo ��ͨ���н�����ʼ */
    NAS_MML_CSFB_MO_SS_SETUP_SUCC,                                              /* csfb mo ��ͨ���н����ɹ� */
    NAS_MML_CSFB_MO_SS_SETUP_FAIL,                                              /* csfb mo ��ͨ���н���ʧ�� */

    /* mo normal call */
    NAS_MML_MO_NORMAL_SS_SETUP_START,                                           /* GU�����н�����ʼ */
    NAS_MML_MO_NORMAL_SS_SETUP_SUCC,                                            /* GU�����н����ɹ� */
    NAS_MML_MO_NORMAL_SS_SETUP_FAIL,                                            /* GU�����н���ʧ�� */

    NAS_MML_SS_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MML_MO_SS_STATUS_ENUM_UINT8;


enum NAS_MML_MT_CM_SRV_STATUS_ENUM
{
    NAS_MML_MT_CM_SRV_SETUP_START,                                           /* GU�±��н�����ʼ */
    NAS_MML_MT_CM_SRV_SETUP_SUCC,                                            /* GU�±��н����ɹ� */
    NAS_MML_MT_CM_SRV_SETUP_FAIL,                                            /* GU�±��н���ʧ�� */

    NAS_MML_MT_CM_SRV_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MML_MT_CM_SRV_STATUS_ENUM_UINT8;



enum NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM
{
    NAS_MML_MT_CSFB_PAGING_TIMER_STOP,                                          /* ������ʱ���Ѿ�ֹͣ */
    NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING,                                        /* ������ʱ���������� */

    NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgName;
    VOS_UINT8                            aucData[4];
}NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU;


typedef struct
{
    VOS_UINT8                                   ucSimPresentStatus;  /* SIM����λ��Ϣ,VOS_TRUE:SIM����λ,VOS_FALSE:SIM������λ */
    NAS_MML_SIM_TYPE_ENUM_UINT8                 enSimType;           /* SIM������,USIM��SIM��*/
    VOS_UINT8                                   ucSimCsRegStatus;    /* SIM��CS���ע�������µĿ��Ƿ���ЧVOS_TRUE:CS��Ŀ���Ч,VOS_FALSE:CS��Ŀ���Ч*/
    VOS_UINT8                                   ucSimPsRegStatus;    /* SIM��PS���ע�������µĿ��Ƿ���ЧVOS_TRUE:PS��Ŀ���Ч,VOS_FALSE:PS��Ŀ���Ч*/
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;    /* status of routing update */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;    /* status of location update */
    VOS_UINT8                                   aucReserve[2];

}NAS_MML_SIM_STATUS_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_MS_IDENTITY_STRU
 �ṹ˵��  : ����SIM��MS��ʶ������IMSI,TMSI,Ptmsi������
  1.��    ��   : 2011��6��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImsi[NAS_MML_MAX_IMSI_LEN];          /* imsi������ */
    VOS_UINT8                           aucPtmsiSignature[NAS_MML_MAX_PTMSI_SIGNATURE_LEN]; /* ptmsi signature������ */
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];        /* ptmsi������ */
    VOS_UINT8                           aucTmsi[NAS_MML_MAX_TMSI_LEN];          /* tmsi������ */
    NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8 enUeOperMode;                           /* ue ����ģʽ */
    VOS_UINT8                           aucReserve[3];
}NAS_MML_SIM_MS_IDENTITY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_PS_SECURITY_INFO_STRU
 �ṹ˵��  : ���浱ǰPS��İ�ȫ������
  1.��    ��   : 2011��6��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCKSN;                                 /* PS���CKSN������ */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                           aucUmtsCk[NAS_MML_UMTS_CK_LEN];         /* PS���CK������ */
    VOS_UINT8                           aucUmtsIk[NAS_MML_UMTS_IK_LEN];         /* PS���IK������ */
    VOS_UINT8                           aucGsmKc[NAS_MML_GSM_KC_LEN];           /* PS���KC������ */
}NAS_MML_SIM_PS_SECURITY_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_CS_SECURITY_INFO_STRU
 �ṹ˵��  : ���浱ǰCS��İ�ȫ������
  1.��    ��   : 2011��6��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCKSN;                                 /* CS���CKSN������ */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                           aucUmtsCk[NAS_MML_UMTS_CK_LEN];         /* CS���CK������ */
    VOS_UINT8                           aucUmtsIk[NAS_MML_UMTS_IK_LEN];         /* CS���IK������ */
    VOS_UINT8                           aucGsmKc[NAS_MML_GSM_KC_LEN];           /* CS���KC������ */
}NAS_MML_SIM_CS_SECURITY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_PLMN_ID_STRU
 �ṹ˵��  : plmn id����Ϣ
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_ID_STRU NAS_MML_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_FORMAT_PLMN_ID
 �ṹ˵��  : Sim PLMN ID�Ĵ洢�ṹ
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/

typedef struct {
    VOS_UINT8                           aucSimPlmn[NAS_MML_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}NAS_MML_SIM_FORMAT_PLMN_ID;


typedef struct
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;                               /* PlMN��ʶ */
    VOS_UINT8                           aucLac[NAS_MML_MAX_LAC_LEN];            /* ע������Ϣ */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCampPlmnNetRat;                       /* PLMN�Ľ��뼼�����յ�ϵͳ��Ϣʱ����*/

    VOS_UINT8                           ucRac;
}NAS_MML_LAI_STRU;
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_MML_TAC_STRU;


typedef struct
{
    NAS_MML_PLMN_ID_STRU                 stPlmnId;
    NAS_MML_TAC_STRU                     stTac;
}NAS_MML_TAI_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_RAI_STRU
 �ṹ˵��  : RAI����Ϣ
 1.��    ��   : 2011��6��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MML_LAI_STRU                    stLai;                                  /* λ������Ϣ */
    VOS_UINT8                           ucRac;                                  /* RAC��Ϣ */
    VOS_UINT8                           aucReserve[3];
}NAS_MML_RAI_STRU;



typedef struct
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8               enMoCallStatus;
    NAS_MML_MO_SS_STATUS_ENUM_UINT8                 enMoSsStatus;
    NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8  enMtCsfbPagingTimerStatus;  /* ����CSFB������ʱ������״̬ */
    VOS_UINT8                                       aucReserve[1];
}NAS_MML_CM_SRV_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_PLMN_WITH_RAT_STRU
 �ṹ˵��  : plmn id����Ϣ�ͽ��뼼��
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;                               /* PLMN ID */
    VOS_UINT16                          usSimRat;                               /* SIM����֧�ֵĽ��뼼�� */
    VOS_UINT8                           aucReserve[2];
}NAS_MML_SIM_PLMN_WITH_RAT_STRU;


typedef struct
{
    VOS_UINT8                               ucEhPlmnNum;                        /* EHPLMN�ĸ���*/
    NAS_MML_LAST_RPLMN_SEL_IND_ENUM_UINT8   enPLMNSelInd;                       /* ����������ѡ���plmn���� */                                                        /* EF_LRPLMNSI������ */
    NAS_MML_EHPLMN_PRESENT_IND_ENUM_UINT8   enEHplmnPresentInd;                 /* EHPLMN�ϱ����û��ķ�ʽ */                                                                              /* ����USIM���ص�EF_EHPLMNPI �����ݵ�ȫ�ֱ����У����ϱ��û��б�ʱʹ�� */

    NAS_MML_HPLMN_TYPE_ENUM_UINT8           enHplmnType;

    NAS_MML_SIM_PLMN_WITH_RAT_STRU          astEhPlmnInfo[NAS_MML_MAX_EHPLMN_NUM];/* EHPLMN ID�б� */
}NAS_MML_SIM_EHPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU
 �ṹ˵��  : ���浱ǰHPLMNwithRat��Ϣ
 1.��    ��   : 2011��6��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHPlmnWithRatNum;                      /* HPLMNwithRat�ĸ���*/
    VOS_UINT8                           aucReserve3[3];
    NAS_MML_SIM_PLMN_WITH_RAT_STRU      astHPlmnWithRatInfo[NAS_MML_MAX_HPLMN_WITH_RAT_NUM];/* HPLMNwithRat�б�*/
}NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_USERPLMN_INFO_STRU
 �ṹ˵��  : ���浱ǰUSERPLMN��Ϣ
 1.��    ��   : 2011��6��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUserPlmnNum;                          /* UPLMN�ĸ���*/
    VOS_UINT8                           aucReserve3[3];
    NAS_MML_SIM_PLMN_WITH_RAT_STRU      astUserPlmnInfo[NAS_MML_MAX_USERPLMN_NUM];/* UPLMN���б�*/
}NAS_MML_SIM_USERPLMN_INFO_STRU;



typedef struct
{
    VOS_UINT16                          usOperPlmnNum;                          /* OPLMN�ĸ���*/
    VOS_UINT8                           aucReserve2[2];
    NAS_MML_SIM_PLMN_WITH_RAT_STRU      astOperPlmnInfo[NAS_MML_MAX_OPERPLMN_NUM];/* OPLMN���б�*/
}NAS_MML_SIM_OPERPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_SELPLMN_INFO_STRU
 �ṹ˵��  : ���浱ǰSelPLMN��Ϣ
  1.��    ��   : 2011��6��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSelPlmnNum;                           /* SELPLMN�ĸ���*/
    VOS_UINT8                           aucReserve3[3];
    NAS_MML_PLMN_ID_STRU                astPlmnId[NAS_MML_MAX_SELPLMN_NUM];     /* SELPLMN���б�*/
}NAS_MML_SIM_SELPLMN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucForbRoamLaNum;                        /* forbidden las for roaming���� */
    VOS_UINT8                           aucReserve[3];
    NAS_MML_LAI_STRU                    astForbRomLaList[NAS_MML_MAX_FORBLA_FOR_ROAM_NUM];/* "forbidden las for roaming" list */
}NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU;


/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
/*****************************************************************************
 �ṹ��    : NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU
 �ṹ˵��  : Forbidden LA��Ϣ��CSע��ʧ��ԭ�� ����Ч��
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    /* ע��ʧ��ԭ�� */
    VOS_UINT16                          usRegFailCause;

    /* ��ֹLAʱ��,��λ:s */
    VOS_UINT16                          usForbLaValidPeriodLen;

    /* �����һ�������Ҫ�ͷ���ʱ�� */
    VOS_UINT16                          usPunishTimeLen;

    VOS_UINT8                           aucRsv[2];
}NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU
 �ṹ˵��  : Forbidden LA������LA���õ�ע��ԭ��ֵ���ͷ�ʱ��
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    /* ֧�ֽ�ֹLA��Чʱ����LA���� */
    VOS_UINT32                                              ulSupportForbLaWithValidPeriodNum;

    /* ��NV�ж�ȡ��CSע��ʧ��ԭ��ֵ�ͳͷ�ʱ����Ϣ */
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_STRU         astForbLaWithValidPeriodCfgList[NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM];
    
}NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU
 �ṹ˵��  : ��ֹLA��Чʱ���б�Ԫ�ṹ
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    NAS_MML_LAI_STRU                    stForbLaWithValidPeriodLai;

    /* ��¼��ֹ��ʼʱ�� */
    VOS_UINT32                          ulForbLaWithValidPeriodBeginTick;

    /* ��¼��ֹLA��Чʱ�������б�ÿ��ʹ��ǰ��Ҫ�ж��Ƿ��������ֹʱ�䵽��
       �����ֹʱ�䵽��̬ɾ��,��nv��ȡ������Ĭ�Ͻ�ֹʱ��ΪȫF���ֵ */
    VOS_UINT32                          ulForbLaWithValidPeriodTick;

    /* ��¼��ƹ�һ��Ƴͷ���ʼʱ�� */
    VOS_UINT32                          ulForbLaWithValidPeriodPunishBeginTick;

    /* ��¼��ƹ�һ�����Ҫ�ͷ���ʱ�� */
    VOS_UINT32                          ulForbLaWithValidPeriodPunishDurationTick;    

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegFailCause;

    VOS_UINT8                           aucRsv[2];
}NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_CS_REG_FAIL_FORB_LA_WITH_VALID_PERIOD_List_STRU
 �ṹ˵��  : NAS MML ��ֹLA��Чʱ���б�ṹ
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    /* ��ֹLA��Чʱ���б�ĳ��� */
    VOS_UINT32                                              ulForbLaWithValidPeriodNum;
    /* ��ֹLA��Чʱ���б� */
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                  astForbLaWithValidPeriodList[NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM];
}NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU;

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_FORBIDPLMN_INFO_STRU
 �ṹ˵��  : ���浱ǰForbid PLMN��Ϣ
  1.��    ��   : 2011��6��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucUsimForbPlmnNum;                      /* SIM���н�ֹ��PLMN ID�ĸ���  */

    VOS_UINT8                                               ucForbPlmnNum;                          /* ��ֹ��PLMN ID�ĸ���         */

    VOS_UINT8                                               ucForbGprsPlmnNum;                      /* ��ֹGPRS��PLMN�ĸ���        */

    VOS_UINT8                                               ucForbRoamLaNum;                        /* forbidden las for roaming����            */

    VOS_UINT8                                               ucForbRegLaNum;                         /* forbidden las for regional provision���� */

    VOS_UINT8                                               aucReserve[3];

    NAS_MML_PLMN_ID_STRU                                    astForbPlmnIdList[NAS_MML_MAX_FORBPLMN_NUM];/* ��ֹ��PLMN ID�б�                        */

    NAS_MML_PLMN_ID_STRU                                    astForbGprsPlmnList[NAS_MML_MAX_FORBGPRSPLMN_NUM];/* "forbidden PLMNs for GPRS service" list  */

    NAS_MML_LAI_STRU                                        astForbRomLaList[NAS_MML_MAX_FORBLA_FOR_ROAM_NUM];/* "forbidden las for roaming" list         */

    NAS_MML_LAI_STRU                                        astForbRegLaList[NAS_MML_MAX_FORBLA_FOR_REG_NUM];/* "forbidden las for regional provision"   */

    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU             stForbLaWithValidPeriod;                /*CSע��ʧ�ܽ�ֹLA�б���Ϣ*/
    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

}NAS_MML_SIM_FORBIDPLMN_INFO_STRU;


typedef struct
{
    NAS_MML_SIM_EHPLMN_INFO_STRU         stEhPlmnInfo;                          /* EHPLMN�б���Ϣ */
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU stHplmnWithRatInfo;                    /* HPLMNWithRat�б���Ϣ */
    NAS_MML_SIM_USERPLMN_INFO_STRU       stUserPlmnInfo;                        /* UPLMN�б���Ϣ */
    NAS_MML_SIM_OPERPLMN_INFO_STRU       stOperPlmnInfo;                        /* OPLMN�б���Ϣ */
    NAS_MML_SIM_SELPLMN_INFO_STRU        stSelPlmnInfo;                         /* SELPLMN�б���Ϣ */
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU     stForbidPlmnInfo;                      /* ��ֹ������Ϣ */
    VOS_UINT32                           ulSimHplmnTimerLen;                    /* SIM��HPLMN��ʱ��ʱ�� */

    VOS_UINT8                            ucUsimMncLen;                          /* Usim�ļ���ָʾ��Mnc���ȣ�Ĭ��Ϊ3λ */
    VOS_UINT8                            aucReserve[3];
}NAS_MML_SIM_PLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_SIM_NATIVE_CONTENT_STRU
 �ṹ˵��  : SIM���ļ��б����ԭʼ����
  1.��    ��   : 2011��12��1��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucCsLociInfoFile[NAS_MML_CS_LOCI_SIM_FILE_LEN];
    VOS_UINT8                                   aucPsLociInfoFile[NAS_MML_PS_LOCI_SIM_FILE_LEN];
}NAS_MML_SIM_NATIVE_CONTENT_STRU;


/*****************************************************************************
 ö����    : NAS_MML_SIM_INFO_STRU
 �ṹ˵��  : SIM����Ϣ,����SIM��״̬,MS Identity,CS��PS��İ�ȫ�����Լ�SIM����PLMN��Ϣ
  1.��    ��   : 2011��6��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�

  2.��    ��   : 2011��12��1��
    ��    ��   : zhoujun /40661
    �޸�����   : ����SIM���ļ��б����ԭʼ�����Ա�д��ʱ���бȽ�
*****************************************************************************/
typedef struct
{
    NAS_MML_SIM_STATUS_STRU             stSimStatus;                            /* SIM��״̬ */
    NAS_MML_SIM_MS_IDENTITY_STRU        stMsIdentity;                           /* MS Identity��Ϣ */
    NAS_MML_SIM_PS_SECURITY_INFO_STRU   stPsSecurity;                           /* PS��İ�ȫ���� */
    NAS_MML_SIM_CS_SECURITY_INFO_STRU   stCsSecurity;                           /* CS��İ�ȫ���� */
    NAS_MML_SIM_PLMN_INFO_STRU          stSimPlmnInfo;                          /* SIM���б����PLMN��Ϣ */
    NAS_MML_SIM_NATIVE_CONTENT_STRU     stSimNativeContent;                     /* SIM���ļ��б����ԭʼ�����Ա�д��ʱ���бȽ� */
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;                             /* ecallģʽ */
    VOS_UINT8                           aucReserve[3];
}NAS_MML_SIM_INFO_STRU;
typedef struct
{
    NAS_MML_3GPP_REL_ENUM_UINT8      enMsGsmRel;                                /* NV�б����Gģ��3GPP�İ汾 */
    NAS_MML_3GPP_REL_ENUM_UINT8      enMsWcdmaRel;                              /* NV�б����Wģ��3GPP�İ汾 */
    NAS_MML_SGSN_REL_ENUM_UINT8      enMsSgsnRel;                               /* NV�б����MS֧��SGSN�İ汾����Ҫ�����ն��ϱ���SGSN�汾 */
    NAS_MML_MSC_REL_ENUM_UINT8       enMsMscRel;                                /* NV�б����MS֧��MSC�İ汾����Ҫ�����ն��ϱ���MSC�汾 */
    NAS_MML_3GPP_REL_ENUM_UINT8      enLteNasRelease;                           /* NV�б����Lģ��3GPP�İ汾 */
}NAS_MML_MS_3GPP_REL_STRU;



typedef struct
{
    NAS_MML_NETWORK_MSG_REL_VER_ENUM_UINT8        enNetMscRel;                            /* �����·���MSG��Э��汾��Ϣ */
    NAS_MML_NETWORK_SGSN_REL_VER_ENUM_UINT8       enNetSgsnRel;                           /* �����·���SGSN��Э��汾��Ϣ */
    VOS_UINT8                           aucReserve[2];
}NAS_MML_NETWORK_3GPP_REL_STRU;



typedef struct
{
    VOS_UINT8                           ucUeNetCapLen;                           /* UE Network Capability�ĳ��� */
    VOS_UINT8                           aucUeNetCap[NAS_MML_MAX_UE_NETWORK_CAPABILITY_LEN]; /* L��ue network capability*/
    VOS_UINT8                           aucRsv[2];
}NAS_MML_UE_NETWORK_CAPABILITY_STRU;


typedef struct
{
    VOS_UINT8                               ucRatNum;                                   /* ƽ̨֧�ֵĽ��뼼���ĸ��� */
    NAS_MML_PLATFORM_RAT_TYPE_ENUM_UINT8    aenRatPrio[NAS_MML_MAX_PLATFORM_RAT_NUM];   /* ƽ̨֧�ֵĽ��뼼�������ȼ�˳�� */
}NAS_MML_PLATFORM_RAT_CAP_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MML_MS_NETWORK_CAPACILITY_STRU
 �ṹ˵��  : GU MS Network Capability
 1.��    ��   : 2011��11��8��
   ��    ��   : zh00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNetworkCapabilityLen;                 /* GU�����������ĳ��� */
    VOS_UINT8                           aucNetworkCapability[NAS_MML_MAX_NETWORK_CAPABILITY_LEN];/*GU��network capability*/
    VOS_UINT8                           aucReserv[3];
}NAS_MML_MS_NETWORK_CAPACILITY_STRU;


typedef struct
{
    VOS_UINT32                          ulGsmCapability;
}NAS_MML_PLATFORM_BAND_CAP_STRU;


typedef struct
{
    VOS_UINT8                           ucClassmark1;                           /* classmark 1 information */
    VOS_UINT8                           aucClassmark2[NAS_MML_CLASSMARK2_LEN];  /* classmark 2 information */
    VOS_UINT8                           aucFddClassmark3[NAS_MML_CLASSMARK3_LEN];  /* classmark 3 information ��0λ����ʵ�ʳ��� */
    VOS_UINT8                           aucTddClassmark3[NAS_MML_CLASSMARK3_LEN];  /* classmark 3 information ��0λ����ʵ�ʳ��� */
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  stMsNetworkCapability;                  /* MS network capability*/
    VOS_UINT8                           aucImeisv[NAS_MML_MAX_IMEISV_LEN];      /* IMEISV */

    NAS_MML_UE_NETWORK_CAPABILITY_STRU  stUeNetworkCapbility;                   /* ��¼nv��ue network capability������ */

    NAS_MML_PLATFORM_RAT_CAP_STRU       stPlatformRatCap;                       /* ��¼NV�е�ƽ̨���뼼������ */
    NAS_MML_PLATFORM_BAND_CAP_STRU      stPlatformBandCap;                      /* ��¼NV�е�ƽ̨ͨ·BAND���� */
}NAS_MML_MS_CAPACILITY_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MML_MS_BAND_INFO_STRU
 �ṹ˵��  : MS band������
 1.��    ��   : 2011��6��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU NAS_MML_MS_BAND_INFO_STRU;


typedef NAS_MSCC_PIF_RAT_PRIO_STRU NAS_MML_PLMN_RAT_PRIO_STRU;


typedef struct
{
    VOS_UINT8                           ucRatNum;                               /* ��ǰ֧�ֵĽ��뼼������  */
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8   aucRatPrio[NAS_MML_MAX_3GPP2_RAT_NUM];  /* �������ȼ����б� index��ʾ���ȼ�����,0��ߣ�2��� */
    VOS_UINT8                           aucReserved[1];
}NAS_MML_3GPP2_RAT_PRIO_STRU;



typedef struct
{
    VOS_UINT8                           ucGsmImsSupportFlag;    /**< GSM IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUtranImsSupportFlag;  /**< UNTRAN IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucLteImsSupportFlag;    /**< LTE IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucGsmEmsSupportFlag;    /**< GSM EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUtranEmsSupportFlag;  /**< UNTRAN EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucLteEmsSupportFlag;    /**< LTE EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           aucReserved[2];
}NAS_MML_IMS_RAT_SUPPORT_STRU;



typedef struct
{
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag;            /* IMS����ʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucSmsOnImsSupportFlag;                  /* IMS����ʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucVideoCallOnImsSupportFlag;            /* IMS��VIDEO CALLʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUssdOnImsSupportFlag;                 /* IMS USSDҵ��ʹ���VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
}NAS_MML_IMS_CAPABILITY_STRU;


typedef struct
{
    NAS_MML_IMS_RAT_SUPPORT_STRU        stImsRatSupport;
    NAS_MML_IMS_CAPABILITY_STRU         stImsCapability;
}NAS_MML_IMS_CONFIG_STRU;


typedef struct
{

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;/* ȥʹ��LTE������� */

    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;

    VOS_UINT32                                              ulDisableLteRoamFlg;/* ��ֹLTE���ε��µ�disable LTE��� */
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;  /* LTE֧�ֵ� cs��ҵ������*/



    NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8                 enLteUeUsageSetting;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPreference;
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;           /* �ֻ�ģʽ */
    VOS_UINT8                                               ucPsAutoAttachFlg;  /* PS�Զ�Attach��־ */
    VOS_UINT8                                               aucReserve[3];
    NAS_MML_MS_BAND_INFO_STRU                               stMsBand;           /* ��ǰMS֧�ֵ�Ƶ�� */
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;      /* ���뼼���Լ����ȼ� */

    NAS_MML_3GPP2_RAT_PRIO_STRU                             st3Gpp2RatList;     /* 3GPP2���뼼���Լ����ȼ� */
    NAS_MML_IMS_CONFIG_STRU                                 stImsConfig;        /* IMS���������Ϣ */

    VOS_UINT8                                               ucDelayedCsfbLauFlg;

    VOS_UINT8                                               ucSyscfgTriHighRatSrchFlg;
    VOS_UINT8                                               aucReserved2[2];
}NAS_MML_MS_SYS_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_RPLMN_CFG_INFO_STRU
 �ṹ˵��  : NVIM���е�RPLMN����������Ϣ
 1.��    ��   : 2011��6��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucLastImsi[NAS_MML_MAX_IMSI_LEN];/* �ϴα����IMSI������ */
    VOS_UINT8                                   aucReserve[3];
    NAS_MML_TIN_TYPE_ENUM_UINT8                 enTinType;                      /* TIN���� */
    VOS_UINT8                                   ucMultiRATRplmnFlg;             /* �Ƿ�֧�ֶ�Rplmn,H3G��������,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
    /*�ϴιػ�ʱ��ע��ɹ���plmn�Ľ��뼼��������ע��ʧ��RPLMNɾ���󣬸�ֵ��Ȼ����Ч,VOS_FALSE:��֧��,VOS_TRUE:֧��*/
    VOS_UINT8                                   ucLastRplmnRatFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enLastRplmnRat;                 /* NVIM�б�����ϴιػ�ǰRPLMN�Ľ��뼼�� */
    NAS_MML_PLMN_ID_STRU                        stWRplmnInNV;                   /* NVIM�б����Wģ��RPLMN */
    NAS_MML_PLMN_ID_STRU                        stGRplmnInNV;                   /* NVIM�б����Gģ��RPLMN */
}NAS_MML_RPLMN_CFG_INFO_STRU;
typedef struct
{
    VOS_UINT8                            ucActiveFlg;                           /* �Ƿ�ʹ�ö��Ƶ�HPLMNAct�Ľ��뼼�����ȼ���VOS_TRUE:���VOS_FALSE:δ���� */
	VOS_UINT8                            ucReserved;
    VOS_UINT16                           usPrioHplmnAct;                            /* ���Ƶ� HPLMN �����Ƚ��뼼������ʽ�� Usim�ļ�6f62�Ľ��뼼����ͬ */
}NAS_MML_PRIO_HPLMNACT_CFG_STRU;
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;
    VOS_UINT8                           ucEhplmnListNum;
    VOS_UINT8                           aucResv[2];
    NAS_MML_PLMN_ID_STRU                astImsiPlmnList[NAS_MML_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_MML_PLMN_ID_STRU                astEhPlmnList[NAS_MML_MAX_USER_CFG_EHPLMN_NUM];
}NAS_MML_USER_CFG_EHPLMN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU
 �ṹ˵��  : NVIM���б�����û�������չ��EHPLMN��
 1.��    ��   : 2014��12��19��
   ��    ��   : wx270776
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUserCfgEhplmnNum;
    NAS_MML_USER_CFG_EHPLMN_INFO_STRU   astUserCfgEhplmnInfo[NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM];
}NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                            /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                         /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MML_MAX_USER_OPLMN_VERSION_LEN];         /* �û����õ�OPMN�İ汾�� */
    VOS_UINT16                          usOplmnListNum;                                         /* �û����õĵ�OPlmn�ĸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                                      /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           aucResv[3];
    NAS_MML_PLMN_ID_STRU                astImsiPlmnList[NAS_MML_MAX_USER_OPLMN_IMSI_NUM];
}NAS_MML_USER_CFG_OPLMN_INFO_STRU;
typedef struct
{
    VOS_UINT8   ucAccBarPlmnSearchFlg;
    VOS_UINT8   ucReserve[3];
}NAS_MML_ACC_BAR_PLMN_SEARCH_FLG_STRU;

typedef struct
{
    VOS_UINT8                                               ucEhplmnSupportFlg;                     /* EHPLMN�����Ƿ�֧��,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
    NAS_MML_AUTO_SRCH_FLG_TYPE_ENUM_UINT8                   enAutoSearchHplmnFlg;                   /* ��¼�Ƿ�֧��Э��Ҫ������Զ�ģʽ��������������Hplmn������,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
    VOS_UINT8                                               ucManualSearchHplmnFlg;                 /* ��¼�Ƿ�֧��Э��Ҫ����ֶ���������Eplmnʧ�ܺ��Ƿ�����Hplmn��Ҫ��,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
    VOS_UINT8                                               ucHplmnSearchPowerOn;                   /* ��������������HPLMN,VOS_FALSE:��֧��,VOS_TRUE:֧�� */

    NAS_MML_PRIO_HPLMNACT_CFG_STRU      stPrioHplmnActCfg;                         /* ���Ƶ�HPlmnAct�����Ƚ������� */
    VOS_UINT8                           ucActingHPlmnSupportFlg;                /* ACTING-HPLMN�����Ƿ�֧��,VOS_FALSE:��֧��,VOS_TRUE:֧�� */

    VOS_UINT8                           ucAddEhplmnWhenSrchHplmnFlg;
    VOS_UINT8                           aucReserve[2];
    

    NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU stUserCfgExtEhplmnInfo;
}NAS_MML_HPLMN_CFG_INFO_STRU;




typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* �������Ƿ�� */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enHighPrioRatType;                      /* ����֧�ֵĽ��뼼�� */
    VOS_UINT8                           aucReserve[2];
    NAS_MML_PLMN_ID_STRU                stHighPrioPlmnId;                       /* ����֧�ֵ�PLMN ID,����������ѡ���PLMN ID,���ܵ�ǰפ����HPLMN�� */
    NAS_MML_PLMN_ID_STRU                stSimHPlmnId;                           /* SIM����HPLMN ID */
}NAS_MML_AIS_ROAMING_CFG_STRU;



/*****************************************************************************
 �ṹ��    : NAS_MML_ROAM_CFG_INFO_STRU
 �ṹ˵��  : NVIM���е��������ö�����Ϣ
 1.��    ��   : 2011��6��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRoamFeatureFlg;                   /*��¼���������Ƿ񼤻�,VOS_FALSE:������,VOS_TRUE:����*/
    NAS_MML_ROAM_CAPABILITY_ENUM_UINT8      enRoamCapability;                   /*��¼�û����õ���������*/
    VOS_UINT8                               ucNotRoamNum;                       /*��¼���β�֧��ʱ����ע������*/
    VOS_UINT8                               ucNationalRoamNum;                  /*��¼�������δ�ʱ����ע������*/
    NAS_MML_PLMN_ID_STRU                    astRoamPlmnIdList[NAS_MML_MAX_ROAM_PLMN_NUM]; /*��¼���������б�*/
    NAS_MML_AIS_ROAMING_CFG_STRU            stAisRoamingCfg;
    VOS_UINT8                               ucRoamSearchRPLMNFlg;                     /*����ʱ����RPLMN��־*/
    VOS_UINT8                               aucReserve[3];
    VOS_UINT32                              aucNationalMccList[NAS_MML_MAX_NATIONAL_MCC_NUM];                 /*��Ӫ�̶��Ƶı����Ĺ�����*/
}NAS_MML_ROAM_CFG_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* Ĭ������HPLMN���������Ƿ���Ч��־,NV���Ƿ񼤻�VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulDefaultMaxHplmnLen;                   /* Ĭ�ϵ�����HPLMN�������� */
}NAS_MML_DEFAULT_MAX_HPLMN_TIMER_PERIOD_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* H3G��������VPLMN�·��״���HPLMN��ʱ��ʱ��NV�����������Ƿ񼤻VOS_TRUE:NV��VOS_FALSE:NV��δ����*/
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulNonFirstHplmnTimerLen;                /* H3G�������Լ����NVIM�л�ȡ����HPLMN��ʱ��ʱ������0��ʾ��Ҫ���������ȼ��� */
}NAS_MML_NON_FIRST_HPLMN_TIMER_PERIOD_STRU;


typedef struct
{
    VOS_UINT8                           ucCustomMccNum;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          aulCostumMccList[NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER];/* �������εĹ������б� */
}NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU;
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                             /* �ö�ʱ���Ƿ�ʹ�� */
    VOS_UINT8                           ucTdThreshold;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer��ʱ����һ�ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer��ʱ����һ��ʱ������������ */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer��ʱ�����״δε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat �ѱ���ֹ���������������Ե�ʱ�� ��λ:��*/
}NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU;


/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/*****************************************************************************
 �ṹ��    : NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU
 �ṹ˵��  : en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG NV��ṹ
 1.��    ��   : 2015��4��28��
   ��    ��   : c00318887
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTriggerBGSearchFlag;  /* 0: mmc�յ������ȼ�PLMN����ʱ������BG SEARCH; 1:mmc�յ������ȼ�PLMN����ʱ����BG SEARCH */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulSearchDelayLen;             /* BG SEARCH Delay ʱ�� ��λ: ms  */
}NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU;

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

typedef struct
{
    NAS_MML_DEFAULT_MAX_HPLMN_TIMER_PERIOD_STRU         stDefaultMaxHplmnTimerPeriod;   /* ��¼en_NV_Item_Default_Hplmn_Srch_Peri NV�����Ϣ*/
    VOS_UINT32                                          ulFirstStartHplmnTimerLen;      /* �״�����HPLMN��ʱ��,Ĭ��Ϊ2���� */
    NAS_MML_NON_FIRST_HPLMN_TIMER_PERIOD_STRU           stNonFirstHplmnTimerPeriod;     /* ��¼en_NV_Item_SearchHplmnTtimerValue NV�����Ϣ*/
    VOS_UINT8                                           ucEnhancedHplmnSrchFlg;         /* ��ǿ��Hplmn����,���綨��: ����Hplmn Timer��ʱ��,ֻҪû��פ����home PLMN��,Ҳ��Ҫ�����˶�ʱ��,��һ������2Min,��������T Min���� VOS_TRUE:valid;VOS_FALSE:INVALID*/
    VOS_UINT8                                           ucSpecialRoamFlg;               /* Vplmn��Hplmn��ͬ������ʱ,�Ƿ�����ص�Hplmn,VOS_TRUE:�����HPLMN;VOS_FALSE:�������HPLMN */
    VOS_UINT8                                           ucScanCtrlFlg;                  /* �������Ʊ�ʶ��VOS_TRUEΪ���VOS_FALSEΪδ���� */
    VOS_UINT8                                           aucReserve[1];

    NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU        stBgSearchRegardlessMcc;

    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU              stHighRatHplmnTimerCfg;

    /* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
    NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU stHighPrioPlmnRefreshTriggerBGSearchCfg;
    /* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

}NAS_MML_BG_SEARCH_CFG_INFO_STRU;


typedef struct
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT8                           aucReserve[3];
}NAS_MML_PLMN_WITH_RAT_STRU;


typedef struct
{
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    VOS_UINT32                          ulPlmnDisabledBeginSlice;   /* ��¼��ֹ��ʼʱ�䣬��Ϊ���ܴ��ڷ�ת��������Ҫ��¼�½�ֹ��ʼʱ��*/

    /* ��¼�ͷ�ʱ�䣬���б�ÿ��ʹ��ǰ��Ҫ�ж��Ƿ��������ֹʱ�䵽��
       �����ֹʱ�䵽��̬ɾ��,��nv��ȡ������Ĭ�Ͻ�ֹʱ��ΪȫF���ֵ */
    VOS_UINT32                          ulPlmnDisabledForbiddenSlice;

    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;
}NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU;



typedef struct
{
    VOS_UINT32                                          ulDisabledRatPlmnNum;                   /* ֧�ֽ�ֹ���뼼����PLMN����,����Ϊ0��ʾ��֧�ָ����� */
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU    astDisabledRatPlmnId[NAS_MML_MAX_DISABLED_RAT_PLMN_NUM];/* ��ֹ���뼼����PLMN��RAT��Ϣ */
}NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    NAS_MML_PLMN_WITH_RAT_STRU          astPlmnId[NAS_MML_MAX_EHPLMN_NUM];
}NAS_MML_PLMN_LIST_WITH_RAT_STRU;



enum NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
{
    NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE                   = 0,           /* ����δ���� */
    NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_BLACK                      = 1,           /* �������������� */
    NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_WHITE                      = 2,           /* �������������� */
    NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8;
enum NAS_MML_PLATFORM_SUPPORT_RAT_ENUM
{
    NAS_MML_PLATFORM_SUPPORT_RAT_GERAN                   = 0,           /* GERAN */
    NAS_MML_PLATFORM_SUPPORT_RAT_UTRAN                   = 1,           /* UTRAN����WCDMA/TDS-CDMA */
    NAS_MML_PLATFORM_SUPPORT_RAT_EUTRAN                  = 2,           /* E-UTRAN */
    NAS_MML_PLATFORM_SUPPORT_RAT_BUTT
};
typedef VOS_UINT8 NAS_MML_PLATFORM_SUPPORT_RAT_ENUM_UINT8;
typedef struct
{
    NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8   enSwitchFlag;                                           /*�����Ƿ���Ч�����ܵ�����  */
    VOS_UINT8                                           ucImsiListNum;                                          /*������Ч��SIM����Ŀ(������/������)  */
    VOS_UINT8                                           ucForbidRatNum;                                         /*��ֹRAT����Ŀ  */
    VOS_UINT8                                           aucReserve[1];
    NAS_MML_PLMN_ID_STRU                                astImsiList[NAS_MML_MAX_IMSI_FORBIDDEN_LIST_NUM];       /* SIM���б� (������/������) */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                     aenForbidRatList[NAS_MML_MAX_RAT_FORBIDDEN_LIST_NUM];   /*��ֹ�Ľ��뼼��  */
}NAS_MML_RAT_FORBIDDEN_LIST_STRU;
typedef struct
{
    VOS_UINT8                           ucPlmnNum;                     /* ֧��DAM���Ե�������� */
    VOS_UINT8                           aucReserved[3];
    NAS_MML_PLMN_ID_STRU                astPlmnId[NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM];
}NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU;

typedef NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU NAS_MML_DAM_IMSI_PLMN_LIST_STRU;
typedef struct
{
    NAS_MML_DAM_IMSI_PLMN_LIST_STRU    stImsiPlmnList;  /* IMSI PLMN MCC-MNC���б�,��Ӧ��Ӫ�̺Ŷ�        */
    NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU stDamPlmnList; /* DAM������Ч��PLMN�б� */
} NAS_MML_DAM_PLMN_INFO_CONFIG_STRU;



typedef struct
{
    VOS_UINT32                              ulT3212NvActiveFlg;
    VOS_UINT32                              ulT3212StartSceneCtrlBitMask;       /* BIT0~BIT31  ���ڿ�����·ʧ�ܺ�����T3212ʱ���Ƿ�ʹ�õ�ǰNV���õ�ʱ�� */
    VOS_UINT32                              ulT3212Phase1TimeLen;               /* t3212��ʱ����1�׶ε�ʱ��,��λΪms */
    VOS_UINT32                              ulT3212Phase1Count;                 /* t3212��ʱ����1�׶εĴ��� */
    VOS_UINT32                              ulT3212Phase2TimeLen;               /* t3212��ʱ����2�׶ε�ʱ��,��λΪms  */
    VOS_UINT32                              ulT3212Phase2Count;                 /* t3212��ʱ����2�׶εĴ��� */
}NAS_MML_T3212_TIMER_INFO_CONFIG_STRU;
enum NAS_MML_RAT_CAPABILITY_STATUS_ENUM
{
    NAS_MML_RAT_CAPABILITY_STATUS_DISABLE                   = 0,
    NAS_MML_RAT_CAPABILITY_STATUS_REENABLE                  = 1,
    NAS_MML_RAT_CAPABILITY_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8;



typedef struct
{
    NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8   ucGsmCapaStatus;
    NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8   ucUtranCapaStatus;
    NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8   ucLteCapaStatus;
    VOS_UINT8                                  ucIsImsiInForbiddenListFlg;
}NAS_MML_RAT_FORBIDDEN_STATUS_STRU;



typedef struct
{
    VOS_UINT8                               ucWhitePlmnLockNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    VOS_UINT8                               ucBlackPlmnLockNum;                     /* ֧�ֺ������ĸ���,����Ϊ0ʱ��ʾ��֧�ֺ����� */
    VOS_UINT8                               aucReserve[2];
    NAS_MML_PLMN_ID_STRU                    astWhitePlmnId[NAS_MML_MAX_WHITE_LOCK_PLMN_NUM];
    NAS_MML_PLMN_ID_STRU                    astBlackPlmnId[NAS_MML_MAX_BLACK_LOCK_PLMN_NUM];
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU stDisabledRatPlmnInfo;               /* ��ֹ���뼼����PLMN�������� */
}NAS_MML_PLMN_LOCK_CFG_INFO_STRU;
typedef struct
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                  enRegCause;
    NAS_MML_REG_DOMAIN_ENUM_UINT8                       enDomain;
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8    enAction;
}NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU;


typedef struct
{
    VOS_UINT8                                           ucActiveFlag;
    VOS_UINT8                                           ucCount;
    VOS_UINT8                                           auReserv[2];
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU	        astSingleDomainFailActionList[NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST];
}NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU;


typedef struct
{
    VOS_UINT8                                           ucAdditionalLauFlag;
    VOS_UINT8                                           auReserv[3];
    NAS_MML_LAI_STRU                                    stLai;
}NAS_MML_SOR_ADDITIONAL_LAU_STRU;


typedef struct
{
    VOS_UINT8                                           ucStkSteeringOfRoamingSupportFlg;       /* �Ƿ�֧��stk streer of roaming�������,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
    VOS_UINT8                                           ucCsRejSearchSupportFlg;                /* vodafone��������������,CS��ʧ���Ĵκ��·���������,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
    VOS_UINT8                                           ucRoamBrokerActiveFlag;                 /* Roam broker���Լ���ı�־:VOS_TRUE:���Դ򿪣�VOS_FALSE:����δ�򿪣�*/
    VOS_UINT8                                           ucRoamBrokerRegisterFailCnt;            /* Roam broker����ע��ʧ�ܵĴ���*/
    VOS_UINT8                                           ucMaxForbRoamLaFlg;                     /* NV�����õ�����ֹLA�����Ƿ���Ч: VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                                           ucMaxForbRoamLaNum;                     /* NV�����õ�����ֹLA���� */
    VOS_UINT8                                           ucNvGsmForbidFlg;                       /* NVָʾGSM�Ƿ��ֹ��־��VOS_TRUE:YES;VOS_FALSE:NO */
    VOS_UINT8                                           ucSingleDomainFailPlmnSrchFlag;         /* DT�������󣬵���ע�ᱻ�ܺ���Ҫ�������� */
    VOS_UINT8                                           ucPsOnlyCsServiceSupportFlg;            /* ����������ΪPS ONLYʱ���Ƿ�֧��CS����źͺ���ҵ��(�������г���)*/
    VOS_UINT8                                           ucWcdmaPriorityGsmFlg;                  /*H3G���� W����������GSM����*/
    VOS_UINT16                                          usAppConfigSupportFlg;                  /*����Ӧ�ð汾*/

	NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU     stSingleDomainFailActionCtx;
    VOS_UINT8                                           ucRegFailNetWorkFailureCustomFlg;

	VOS_UINT8                                           ucUserAutoReselActiveFlg;                    /* �Ƿ�����LTE�������α��:VOS_TRUE ��ʾ����LTE�������� VOS_FALSE ��ʾ��ֹLTE�������� */

    VOS_UINT8                                           ucSortAvailalePlmnListRatPrioFlg;    /* �Ƿ�syscfg���ý��뼼�����ȼ�����ߵ����������б��ʶ��1:��; 0:���Ǹ��������簴���������������粻����*/
    /* ����������ΪCS ONLYʱ���Ƿ�֧��PS����ź�����ҵ�� */
    VOS_UINT8                                           ucCsOnlyDataServiceSupportFlg;


    VOS_UINT8                                           ucLteDisabledRauUseLteInfoFlag;  /* L disableʱrau�Ƿ���Ҫ��l�»�ȡ��ȫ�����Ļ�gutiӳ����Ϣ��VOS_TRUE:L disabled rau��l��ȡ��ȫ�����Ļ�gutiӳ����Ϣ��VOS_FALSE:L disable��rau����l��ȡ��ȫ�����Ļ�gutiӳ����Ϣ */
    VOS_UINT8                                           aucReserved[3];

    NAS_MML_SOR_ADDITIONAL_LAU_STRU                     stAdditionalLau;
}NAS_MML_MISCELLANEOUS_CFG_INFO_STRU;

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
/*****************************************************************************
 �ṹ��    : NAS_MML_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU
 �ṹ˵��  : NVIM���еĵ�һ�׶�ʱ��
 1.��    ��   : 2015��8��26��
   ��    ��   : c00318887
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;                           /* ��ʱ����Ƶ�һ�׶������ı�ʾ */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulTotalTimeLen;                         /* ��һ�׶�������ʱ��,��λ:s */
}NAS_MML_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU;

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */


/*****************************************************************************
 �ṹ��    : NAS_MML_AVAIL_TIMER_CFG_STRU
 �ṹ˵��  : NVIM���еĶ��������������
 1.��    ��   : 2011��6��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* available timer��ʱ����һ�ε�ʱ�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* available timer��ʱ����һ�εĴ��� */
    VOS_UINT32                          ulDeepSearchTimeLen;                    /* available timer��ʱ����˯��ʱ�� */
    VOS_UINT32                          ulDeepSearchTimeCount;

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
    NAS_MML_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU       stPlmnSearchPhaseOneTotalTimerCfg;     /* �ù̶�ʱ�����Ƶ�һ�׶�������ʱ����������Ϣ */
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

}NAS_MML_AVAIL_TIMER_CFG_STRU;

#if (FEATURE_ON == FEATURE_LTE)

typedef struct
{
    VOS_UINT8                          ucImsiListNum;                                           /* LTE OOS������2G����3G */
    VOS_UINT8                          aucReserve[3];
    NAS_MML_PLMN_ID_STRU               astImsiList[NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM]; /* LTE OOS������2G����3G */
}NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU;
#endif


typedef struct
{
    VOS_UINT8                           ucLteRoamAllowedFlg;                    /* �Ƿ�����LTE�������α��:VOS_TRUE ��ʾ����LTE�������� VOS_FALSE ��ʾ��ֹLTE�������� */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          aulRoamEnabledMccList[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];/* �������εĹ������б� */
}NAS_MML_LTE_INTERNATION_ROAM_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* ���ű����Ƿ�ʹ�� VOS-TRUE:���ű���֧�� VOS_FALSE:���ű��ܲ�֧�� */
    VOS_UINT8                           aucReserve[3];
}NAS_MML_DAIL_REJECT_CFG_STRU;
enum NAS_MML_CHANGE_REJ_TYPE_ENUM
{
    NAS_MML_CHANGE_REJ_TYPE_CS_REG,        /* CS��ע������(LU)�ܾ� */
    NAS_MML_CHANGE_REJ_TYPE_PS_REG,        /* PS��ע������(ATTACH/RAU)�ܾ� */
    NAS_MML_CHANGE_REJ_TYPE_DETACH,        /* ����PS Detach ���ܾ̾� */
    NAS_MML_CHANGE_REJ_TYPE_PS_SER_REJ,    /* PS service request���ܾ̾� */
    NAS_MML_CHANGE_REJ_TYPE_MM_ABORT,      /* MM ABORT���ܾ̾� */
    NAS_MML_CHANGE_REJ_TYPE_CM_SER_REJ,    /* CM Service request���ܾ̾�ԭ */
    NAS_MML_CHANGE_REJ_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8;


typedef struct
{
    VOS_UINT8                           ucHplmnPsRejCauseChangedCout; /* HPLMN PS/EPS��ܾ�ԭ��ֵ�޸�Ϊ#17�Ĵ��� */
    VOS_UINT8                           ucHplmnCsRejCauseChangedCout; /* HPLMN CS��ܾ�ԭ��ֵ�޸�Ϊ#17�Ĵ��� */
    VOS_UINT8                           ucVplmnPsRejCauseChangedCout; /* VPLMN PS/EPS��ܾ�ԭ��ֵ�޸�Ϊ#17�Ĵ��� */
    VOS_UINT8                           ucVplmnCsRejCauseChangedCout; /* VPLMN CS��ܾ�ԭ��ֵ�޸�Ϊ#17�Ĵ��� */
}NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU;

typedef NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU NAS_MML_CHANGE_NW_CAUSE_CFG_STRU;


typedef struct
{
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                        stChangeNWCauseCfg; /* �û����þܾ�ԭ��ֵ��Ϣ */
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                  stRejCauseChangedCounter;
}NAS_MML_CHANGE_NW_CAUSE_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucRelPsSigConFlg; /*�Ƿ��������������������*/

    VOS_UINT8                           ucPdpExistNotStartT3340Flag; /* rau��attach���󲻴�follow on������ظ�attach accept��rau acceptҲ����follow on������pdp�����ĳ����Ƿ���Ҫ����T3340,0:��Ҫ����T3340; 1:����Ҫ���� */
    VOS_UINT8                           aucRsv[2];

    VOS_UINT32                          ulT3340TimerLen;  /* ���õ�GMM T3340��ʱ�� ��λ:�� */
}NAS_MML_REL_PS_SIGNAL_CON_INFO_STRU;


typedef struct
{
    VOS_UINT8   ucLauRejCauseNum;
    VOS_UINT8   ucLauRejTimes;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucLauRejCause[NAS_MML_MAX_NORETRYCAUSE_NUM];
}NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU;



typedef struct
{
    VOS_UINT8   ucNoRetryRejectCauseNum;
    VOS_UINT8   aucNoRetryRejectCause[NAS_MML_MAX_NORETRYCAUSE_NUM];
    VOS_UINT8   aucReserve[3];
}NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucIgnoreAuthRejFlg;
    VOS_UINT8                           ucHplmnCsAuthRejCounter;
    VOS_UINT8                           ucHplmnPsAuthRejCounter;
    VOS_UINT8                           ucMaxAuthRejNo;
}NAS_MML_IGNORE_AUTH_REJ_INFO_STRU;


typedef struct
{
    VOS_UINT32                                              ulHoWaitSysinfoTimeLen;  /* CSFB HO ���̵�ϵͳ��Ϣʱ��,��λΪ���� */

    NAS_MML_LTE_INTERNATION_ROAM_CFG_STRU                   stLteRoamCfg;       /* LTE�������ζ������� */


    VOS_UINT8                                               ucCsfbEmgCallLaiChgLauFirstFlg;   /* csfb ��������GU,LAI�ı�����lau�����Ƚ��к��б�־��
                                                                                  VOS_TRUE:LAI�ı�����lau�ٽ��н������У�VOS_FALSE:LAI�ı��Ƚ��н������н�������LAU*/
    VOS_UINT8                                               ucIsrSupportFlg;

    VOS_UINT8                                               ucIsRauNeedFollowOnCsfbMtFlg;
    VOS_UINT8                                               ucIsDelFddBandSwitchOnFlg;


    VOS_UINT32                                              ulCsPsMode13GPPEnableLteTimerLen;  /* 1)cs ps mode1 L����ע��eps only�ɹ�cs����#16/#17/#22������������disable lteʱ����enable lte��ʱ��ʱ��
                                                                                               2)cs ps mode1 L����ע��cs eps��ʧ��ԭ��ֵother cause ������������disable lte����enable lte��ʱ��ʱ�� */


    VOS_UINT32                                              ulCsfbEmgCallEnableLteTimerLen; /* L�½��������޷�����csfb��gu��ͨ��������gu����disable lte����enable lte��ʱ��ʱ��,��λ:����*/
    VOS_UINT8                                               ucDisableLTEOnBandFlg;       /* ����WCDMA BAND����LTE */
    VOS_UINT8                                               ucUltraFlashCsfbSupportFlg;  /* Ultra Flash Csfb�Ƿ�֧�� */
    VOS_UINT8                                               ucIsRauNeedFollowOnCsfbMoFlg;

    VOS_UINT8                                               ucEnableLteTrigPlmnSearchFlag;  /* enable lte���Ƿ񴥷�������ʶ��0:������������1:��������*/
    VOS_UINT8                                               ucAddDamPlmnInDisablePlmnWithRatListFlag; /* ��DAM���� disable lte���Ƿ�DAM��lte��������ֹ���뼼�������б��У�VOS_TRUE:��Ҫ���룻VOS_FALSE:����Ҫ���� */
    VOS_UINT8                                               aucReserved[3];

    /* ����ԭ��ֵΪ#16��#17��#18������ע��ɹ���Additional Update Result IE��Ϣ��
    ָʾSMS Only��CSFB Not Preferred��Ҫdisable lteʱ�����Э��汾���ڵ���R11��
    ���ñ��ܾ���PLMN��RAT��¼�ڽ�ֹ���뼼�������б��еĳͷ�ʱ�䣬���Ϊ0xFF��ʾ���óͷ�
    ��λ:���� */
    VOS_UINT32                                              ulLteVoiceNotAvailPlmnForbiddenPeriod;


    VOS_UINT8                                               ucLteRejCause14Flg;       /* Lte #14�ܾ��Ż���־ */
    VOS_UINT8                                               aucReserve1[3];
    VOS_UINT32                                              ulLteRejCause14EnableLteTimerLen;/* Lte #14�ܾ��Ż���disable LTEʱ�� */

}NAS_MML_LTE_CUSTOM_CFG_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucImsVoiceInterSysLauEnable;            /* Ims Voice ����ʱ������L->GU��ϵͳ�л����Ƿ���Ҫǿ�ƽ���LAU */
    VOS_UINT8                           ucImsVoiceMMEnable;          /* Ims Voice �ƶ��Թ����Ƿ��  VOS_TRUE--�򿪣�VOS_FALSE--�ر�*/
    VOS_UINT8                           acReserved[2];
}NAS_MML_IMS_VOICE_MOBILE_MANAGEMENT;


typedef struct
{
    VOS_UINT32                           ulCsRegEndSessionDelayTime;              /* Lau�ӳ�ʱ������λ:���� */
    VOS_UINT32                           ulPsRegEndSessionDelayTime;              /* Rau�ӳ�ʱ������λ:���� */
}NAS_MML_DSDS_END_SESSION_DELAY_STRU;


typedef struct
{
    VOS_UINT8  ucCnt;
    VOS_UINT8  aucUmtsCodec[NAS_MML_CALL_MAX_UMTS_CODEC_TYPE_NUM];
}NAS_MML_CALL_UMTS_CODEC_TYPE_STRU;



typedef struct
{
    VOS_UINT8                           ucCodecTypeNum;
    VOS_UINT8                           aucCodecType[NAS_MML_CALL_BC_MAX_SPH_VER_NUM];
    VOS_UINT8                           ucReserve;
}NAS_MML_CALL_GSM_CODEC_TYPE_STRU;


enum NAS_MML_CARRY_EPLMN_SWITCH_FLAG_ENUM
{
    NAS_MML_CARRY_EPLMN_SWITCH_OFF                     = 0,           /* �رմ��Ż� */
    NAS_MML_CARRY_EPLMN_SWITCH_ON_FOR_ROAM             = 1,           /* �Ż��򿪣����ǽ�������ʱ��Ч */
    NAS_MML_CARRY_EPLMN_SWITCH_ON_FOR_ALL              = 2,           /* �Ż��򿪣�����������ζ���Ч */
    NAS_MML_CARRY_EPLMN_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MML_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8;
typedef struct
{
    NAS_MML_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8              enSwitchFlag;
    VOS_UINT8                                               ucCarryEplmnSceneSwitchOn;
    VOS_UINT8                                               ucCarryEplmnSceneAreaLost;
    VOS_UINT8                                               ucCarryEplmnSceneAvailableTimerExpired;
    VOS_UINT8                                               ucCarryEplmnSceneSysCfgSet;
    VOS_UINT8                                               ucCarryEplmnSceneDisableLte;
    VOS_UINT8                                               ucCarryEplmnSceneEnableLte;
    VOS_UINT8                                               ucCarryEplmnSceneCSFBServiceRej;
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT8                                               ucReserved4;
}NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU;


typedef struct
{
    VOS_UINT8   ucCmSrvExistTrigPlmnSearch;                                                     /* ҵ�����ʱ�Ƿ񴥷����� */
    VOS_UINT8   ucCmSrvTrigPlmnSearchCauseNum;                                                  /* ����ҵ�����ʱ���������ı���ԭ��ֵ���� */
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucCmSrvTrigPlmnSearchCause[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];   /* ����ҵ�����ʱ���������ı���ԭ��ֵ */
    VOS_UINT8   aucReserve[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];                    /* Ԥ����ע�ᱻ�ܴ�������ʹ�� */
}NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU;

typedef struct
{
    NAS_MML_RPLMN_CFG_INFO_STRU         stRplmnCfg;                             /* RPLMN�Ķ������� */
    NAS_MML_HPLMN_CFG_INFO_STRU         stHplmnCfg;                             /* HPLMN�Ķ������� */
    NAS_MML_ROAM_CFG_INFO_STRU          stRoamCfg;                              /* ROAM�Ķ������� */
    NAS_MML_BG_SEARCH_CFG_INFO_STRU     stBgSearchCfg;                          /* BG�����Ķ������� */
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU     stPlmnLockCfg;                          /* ������������,������������� */
    NAS_MML_AVAIL_TIMER_CFG_STRU        stAvailTimerCfg;                        /* ������������Ʒ��������ʱ�䶨������ */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU stMiscellaneousCfg;                     /* ��Ӫ������Ķ������� */
    NAS_MML_DAIL_REJECT_CFG_STRU        stDailRejectCfg;                        /* ���ű��ܶ������� */

    VOS_UINT8                           ucPlmnExactlyCompareFlg;                /*Plmn��ȷ�Ƚϱ��,ʹ��ͬһMCC����2λ��3λMNC�Ĺ��Ҳ����Ǻܶ࣬
                                                                                 �������ڵ�������MNC��λ��0��Fʱ��ֻҪMNC�ĵ���λ��ͬ��
                                                                                 ����Ϊ������MNC����ͬ�ģ�������Ҫ�������֣�����410-310��410-31������MCC��ͬ��PLMN��*/
    VOS_UINT8                           ucSupportCsServiceFlg;                  /* �Ƿ�֧��cs����ҵ�������ͨ������vpҵ��VOS_TRUE:֧��cs����ҵ��VOS_FALSE:��֧��cs����ҵ��*/

    VOS_UINT8                           ucHplmnRegisterCtrlFlg;                 /* HPLMN��ע�ᱻ�ܺ��Ƿ������ظ�ע���� */


    VOS_UINT8                           ucH3gCtrlFlg;

    NAS_MML_LTE_CUSTOM_CFG_INFO_STRU    stLteCustomCfgInfo;

    NAS_MML_CHANGE_NW_CAUSE_INFO_STRU stChangeNWCauseInfo;

    NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU  stRoamingRejectNoRetryInfo;

    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU        stLauRejNoRetryWhenCmSrvExistCfgInfo;

    NAS_MML_RAT_FORBIDDEN_LIST_STRU             stRatForbiddenListInfo;
    NAS_MML_RAT_FORBIDDEN_STATUS_STRU           stRatFirbiddenStatusCfg;

    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU           stIgnoreAuthRejInfo;

    NAS_MML_USER_CFG_OPLMN_INFO_STRU    stUserCfgOPlmnInfo;
    VOS_UINT8                           ucSupportAccBarPlmnSearchFlg;         /* ��HPLMN/RPLMN�����ֹ���Ƿ���PLMN������*/

    VOS_UINT8                           ucSvlteSupportFlag;

    VOS_UINT16                          usDsdsRfShareSupportFlg;

    VOS_UINT8                           ucLcEnableFLg;

    VOS_UINT8		                    ucPsTransferOffAreaModeFlg;						/* SVLTE �Ƿ�������ʽ*/
    VOS_UINT8                           acReserved[2];

    /* ��NV�ж�ȡ�Ƿ���Ҫǿ��LAU��IMS�ƶ��Թ����nv */
    NAS_MML_IMS_VOICE_MOBILE_MANAGEMENT stImsVoiceMM;
    VOS_UINT8                           uc3GPPUplmnNotPrefFlg;
    VOS_UINT8                           ucSupportSrvccFlg;

    VOS_UINT8                           ucDsdsMultiModemModeFlg;

    VOS_UINT8                           ucCsmoSupportedFlg;

    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;

    VOS_UINT16                          usMtCsfbPagingProcedureLen;



    NAS_MML_DSDS_END_SESSION_DELAY_STRU    stDsdsEndSesssionDelay;
    NAS_MML_CALL_UMTS_CODEC_TYPE_STRU   stCallUmtsCodecType;
    NAS_MML_CALL_GSM_CODEC_TYPE_STRU    stCallGsmCodecType;
    /*��NV �ж�ȡ����������������õ�T3340ʱ��*/
    NAS_MML_REL_PS_SIGNAL_CON_INFO_STRU stRelPsSigConInfo;

    NAS_MML_DAM_PLMN_INFO_CONFIG_STRU    stDamPlmnInfoCfg;    /* ֧��DAM���Ե�������Ϣ */

    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU  stT3212Info;

    /* ����NV�����õ����������Ż�ʱ��ȡ������Ϣ�Ľ��뼼�����ȼ� */
    NAS_MML_PLMN_RAT_PRIO_STRU          stGetGeoPrioRatList;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU   stLteOos2GPrefPlmnSelCfg;
#endif

    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    VOS_UINT8                           aucReserve[3];


    /* ��EPLMN��Чʱ��ˢ��EPLMNʱ���Ƿ�ɾ��RPLMN�Ķ��� */
    VOS_UINT8                           ucDeleteRplmnWhenEplmnInvalidFlg;
    
    VOS_UINT8                           ucPsRegFailMaxTimesTrigLauOnceFlg;
    VOS_UINT8                           ucKeepSrchHplmnEvenRejByCause13Flg;
    VOS_UINT8                           ucEpsRejByCause14InVplmnAllowPsRegFlg;
    NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU            stCarryEplmnWhenSrchRplmnCfg;
    NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                   stLauRejTrigPlmnSearchCfg;

    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU    stForbLaWithValidPeriodCfg;
    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */
}NAS_MML_CUSTOM_CFG_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MML_MS_CFG_INFO_STRU
 �ṹ˵��  : MS֧�ֵ�MS��������
 1.��    ��   : 2011��6��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MML_MS_3GPP_REL_STRU            stMs3GppRel;                            /* ֧�ֵ�Э��汾 */
    NAS_MML_MS_CAPACILITY_INFO_STRU     stMsCapability;                         /* MS���ֻ����� */
    NAS_MML_MS_SYS_CFG_INFO_STRU        stMsSysCfgInfo;                         /* ϵͳ������Ϣ */
    NAS_MML_CUSTOM_CFG_INFO_STRU        stCustomCfg;                            /* NVIM�еĶ�����Ϣ */
}NAS_MML_MS_CFG_INFO_STRU;


typedef struct
{
    VOS_UINT32                      ulCellId;                       /*С��ID*/

    VOS_INT16                       sCellRssi;
    VOS_INT16                       sCellRSCP;                      /*С���ź�����*/

} NAS_MMC_CELL_VALUE_STRU;


typedef struct
{
    VOS_UINT8                       ucRssiLevel;                    /* RSSI�ȼ� */
    VOS_UINT8                       ucChannalQual;                  /* �ź����� */
    VOS_UINT8                       aucReserve[2];

    VOS_INT16                       sRssiValue;                     /* �ź����� */
    VOS_INT16                       sRscpValue;
} NAS_MMC_RSSI_VALUE_STRU;
typedef struct
{
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    VOS_UINT32                  ulArfcn;                                /* С��Arfcn */
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    VOS_UINT8                   ucCellNum;                              /*С����Ŀ*/
    VOS_UINT8                   ucRssiNum;                              /* �ź��������� */
    VOS_UINT8                   aucReserve[2];                          /* ����λ */
    NAS_MMC_CELL_VALUE_STRU     astCellInfo[NAS_MML_AT_CELL_MAX_NUM];   /*С��ID*/
    NAS_MMC_RSSI_VALUE_STRU     astRssiInfo[NAS_MML_AT_CELL_MAX_NUM];   /*�ź�����*/
    VOS_UINT16                  usCellDlFreq;                           /*С��Ƶ��(����)*/
    VOS_UINT16                  usCellUlFreq;                           /*��ǰƵ��(����)*/
    VOS_INT16                   sUeRfPower;                             /*���书��*/
}NAS_MML_CAMP_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_CAMP_PLMN_INFO_STRU
 �ṹ˵��  : MMC��ǰפ��PLMN����Ϣ
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU NAS_MML_OPERATOR_NAME_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucUtranNcellExist;
    VOS_UINT8                           ucLteNcellExist;
    VOS_UINT8                           aucReserve[2];
}NAS_MML_RRC_NCELL_INFO_STRU;



typedef struct
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;                           /* ��ǰ��������뼼�� */
    NAS_MML_NET_MODE_ENUM_UINT8         enNetworkMode;                          /* ��ǰפ��������ģʽ */
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode;                           /* ��ǰפ�������ϵͳģʽ */

    VOS_UINT8                           ucReserve;

    NAS_MML_LAI_STRU                    stLai;                                  /* ��ǰפ�������PLMN ID��λ���� */
    NAS_MML_LAI_STRU                    stOldLai;                               /* �ϴ�פ�������LAI��Ϣ */
    VOS_UINT8                           ucRac;                                  /* ��ǰפ�������RAC */
    NAS_MML_LMM_ACCESS_TYPE_ENUM_UINT8  enLmmAccessType;                        /* פ����LTE�µĽ���ģʽTDD/FDD */
    VOS_UINT8                           aucReserve[2];
    NAS_MML_CAMP_CELL_INFO_STRU         stCampCellInfo;                         /* ��ǰפ����С����Ϣ */
    NAS_MML_OPERATOR_NAME_INFO_STRU     stOperatorNameInfo;                     /* ��ǰפ������Ӫ��������Ϣ */
    NAS_MML_RRC_NCELL_INFO_STRU         stRrcNcellInfo;
}NAS_MML_CAMP_PLMN_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucRestrictPagingRsp;          /*�Ƿ�������ӦѰ�� */
    VOS_UINT8                           ucRestrictRegister;           /*�Ƿ�����ע�� */
    VOS_UINT8                           ucRestrictNormalService;      /* �Ƿ���������ҵ�� */
    VOS_UINT8                           ucRestrictEmergencyService;   /* �Ƿ����ƽ���ҵ�� */
}NAS_MML_ACCESS_RESTRICTION_STRU;

typedef struct
{
    NAS_MML_TIMER_INFO_ENUM_UINT8                      enT3412Status;           /* T3412��ʱ��������״̬:0-ֹͣ��1-���У�2-��ʱ*/
    NAS_MML_TIMER_INFO_ENUM_UINT8                      enT3423Status;           /* T3423��ʱ��������״̬:0-ֹͣ��1-���У�2-��ʱ*/
    NAS_MML_TIMER_INFO_ENUM_UINT8                      enT3402Status;           /* T3402��ʱ��������״̬:0-ֹͣ��1-���У�2-��ʱ*/
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8       enAdditionUpdateRsltInfo;/* ����attach��tau����ظ������Additional update result IE���� */
    NAS_MML_REG_STATUS_ENUM_UINT8                      enEpsRegStatus;           /* PS���ע���� */

    VOS_UINT8                                          ucIsRelCauseCsfbHighPrio; /* VOS_TRUE��ʾ������н�������ʱ��ԭ��RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL
                                                                                 VOS_FALSE��ʾ������н�������ʱ��ԭ��RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL*/
    VOS_UINT8                                          aucReserved[1];


    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8                     enNwImsVoCap; /* EPS�����IMS Voice ֧�� */

    VOS_UINT32                                          ulT3402Len;      /* ��λ����*/
}NAS_MML_EPS_DOMAIN_INFO_STRU;



typedef struct
{
    NAS_MML_PS_BEARER_STATE_ENUM_UINT8                 enPsBearerState;         /* PS����״̬�����ȥ���� */
    NAS_MML_PS_BEARER_ISR_ENUM_UINT8                   enPsBearerIsrFlg;        /* PS���ؼ�������ISR����ǰ���Ǽ���� */
    VOS_UINT8                                          ucPsActPending;          /* ���ڼ�������е�PS���� */
    VOS_UINT8                                          ucPsDeactPending;
}NAS_MML_PS_BEARER_CONTEXT_STRU;
typedef struct
{
    VOS_UINT8                           ucCategory;                             /* �������к������� */
    VOS_UINT8                           ucEmcNumLen;                            /*���������볤�ȣ���aucEmcNum����Ч����*/
    VOS_UINT8                           aucEmcNum[NAS_MML_EMERGENCY_NUM_MAX_LEN];
}NAS_MML_EMERGENCY_NUM_STRU;


typedef struct
{
    VOS_UINT8                      ucEmergencyNumber;                           /* ������������� */
    VOS_UINT8                      ucReserved[3];
    VOS_UINT32                     ulMcc;
    NAS_MML_EMERGENCY_NUM_STRU     aucEmergencyList[NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS]; /* �����������б� */

}NAS_MML_EMERGENCY_NUM_LIST_STRU;



typedef struct
{
    VOS_UINT8                           ucCsSupportFlg;                         /* ��ǰCS���Ƿ�֧�� */
    VOS_UINT8                           ucAttFlg;                               /* CS����ҪATT�ı�־,VOS_FALSE:����Ҫ,VOS_TRUE:��Ҫ  */
    VOS_UINT8                           ucCsAttachAllow;                        /* CS���Ƿ�����ע��,VOS_TRUE:����CS��ע��,VOS_FALSE:������CS��ע�� */
    NAS_MML_REG_STATUS_ENUM_UINT8       enCsRegStatus;                          /* CS���ע���� */
    NAS_MML_ACCESS_RESTRICTION_STRU     stCsAcRestriction;                      /* ��ǰCS������������ */
    VOS_UINT32                          ulT3212Len;                             /* T3212��ʱ����ʱ�� */
    VOS_UINT32                          ulCsDrxLen;                             /* CS��DRX�ĳ��� */
    VOS_UINT32                          ulCsRegisterBarToUnBarFlag;             /* CS���Bar��UnBar��ת���־ */
    NAS_MML_LAI_STRU                    stLastSuccLai;                          /* CS�����һ��ע��ɹ���LAI��Ϣ��ע��ʧ�ܺ���Ҫɾ��LAI�����ֵΪ��Чֵ */
    NAS_MML_CM_SRV_STATUS_STRU          stCmSrvStatus;

}NAS_MML_CS_DOMAIN_INFO_STRU;
typedef struct
{
    VOS_UINT8                                               ucSplitPgCycleCode; /* SPLIT PG CYCLE CODE*/
    VOS_UINT8                                               ucUeUtranPsDrxLen;  /* CN Specific DRX cycle length coefficien */
    VOS_UINT8                                               ucUeEutranPsDrxLen; /* DRX value for S1 mode */
    VOS_UINT8                                               ucWSysInfoDrxLen;   /* Wasϵͳ��Ϣ��Я����DrxLength */
    VOS_UINT8                                               ucLSysInfoDrxLen;   /* Lϵͳ��Ϣ��Я����DrxLength */
    VOS_UINT8                                               ucSplitOnCcch;      /* SPLIT on CCCH */
    VOS_UINT8                                               ucNonDrxTimer;      /* non-DRX  timer*/
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8              enPsRegisterContainDrx; /* psע���Ƿ�Я����DRX����*/
}NAS_MML_PS_DOMAIN_DRX_PARA_STRU;


typedef struct
{
    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16      enGmmProcType;        /* GMM�������� */
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16      enGmmProcFlag;        /* GMM���̱�־ */
}NAS_MML_GMM_PROC_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucPsSupportFlg;                         /* ��ǰCS���Ƿ�֧�� */
    VOS_UINT8                           ucPsAttachAllow;                        /* PS���Ƿ�����ע��,VOS_TRUE:����PS��ע��,VOS_FALSE:������PS��ע�� */
    NAS_MML_REG_STATUS_ENUM_UINT8       enPsRegStatus;                          /* PS���ע���� */
    VOS_UINT8                           ucPsLocalDetachFlag;                    /* svlte��̬��gmm�յ�mtc�Ķ���ָʾ����¸ñ���Ϊvos_true,gmm��lnas
                                                                                   �����յ�detach ps����������detach*/

    NAS_MML_ACCESS_RESTRICTION_STRU     stPsAcRestriction;                      /* ��ǰPS������������ */
    VOS_UINT32                          ulPsRegisterBarToUnBarFlag;             /* PS���Bar��UnBar��ת���־ */
    NAS_MML_RAI_STRU                    stLastSuccRai;                          /* PS�����һ��ע��ɹ���RAI��Ϣ��ע��ʧ�ܺ���Ҫɾ��RAI�����ֵΪ��Чֵ */

    NAS_MML_PS_DOMAIN_DRX_PARA_STRU     stPsDomainDrxPara;                      /* PS��DRX������Ϣ */
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoCap; /* PS������Ims Voice ֧������ */
    VOS_UINT8                           acReserved[3];

    NAS_MML_GMM_PROC_INFO_STRU          stGmmProcInfo;                          /* ��¼GMM������Ϣ */
    NAS_MML_SM_PROC_FLAG_ENUM_UINT8     enSmProcFlag;                           /* ��¼sm������Ϣ�����Ƿ���pdp����ȥ�����modify������*/
}NAS_MML_PS_DOMAIN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucEquPlmnNum;                           /* ��ǰEquPLMN�ĸ��� */
    VOS_UINT8                           ucValidFlg;                             /* ��ЧPLMN��Ч���:VOS_TRUE:EPLMN��Ч,VOS_FALSE:EPLMN��Ч */
                                                                                /* EPLMN��ɾ����EPLMN����Ϊ0ʱ��Ч,�����������Ч */
    VOS_UINT8                           aucReserved[2];
    NAS_MML_PLMN_ID_STRU                astEquPlmnAddr[NAS_MML_MAX_EQUPLMN_NUM];/* ��ǰEquPLMN�б� */
}NAS_MML_EQUPLMN_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucCsSigConnStatusFlg;                   /* CS�����������Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucPsSigConnStatusFlg;                   /* PS�����������Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucPsTbfStatusFlg;                       /* TBF�����Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucRrcStatusFlg;                         /* RRC�����Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucCsServiceConnStatusFlg;               /* CS��ҵ�������Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucCsServiceBufferFlg;                   /* CS�򻺴�ҵ���Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucPsServiceBufferFlg;                   /* PS�򻺴�ҵ���Ƿ����,VOS_FALSE:������,VOS_TRUE:����,�˱�����ʱ��Ҫ����,��Ҫԭ��ΪMMC��ʱ����Ҫ�ж� */
    VOS_UINT8                           ucPdpStatusFlg;                         /* PDP�Ƿ񼤻�,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucEpsSigConnStatusFlg;                  /* EPS�����������Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucEpsServiceConnStatusFlg;              /* EPS��ҵ�������Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucEmergencyServiceFlg;                  /* �ж��Ƿ��ǽ������� */
    VOS_UINT8                           ucPsTcServiceFlg;                       /* PS�򴥷���TCҵ���Ƿ���ڣ�VOS_FALSE:�����ڣ�VOS_TRUE:����
                                                                                   CS�򴥷���TCҵ��ʱ��ֱ��ʹ��CS��ҵ�����Ӵ��ڵı�־ */
    VOS_UINT8                           ucEmcPdpStatusFlg;                      /* ����PDN�Ƿ���ڱ�־,VOS_FALSE:������,VOS_TRUE:���� */

    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;/* ��ʶ��ǰ�Ƿ���CSFB���� */
    VOS_UINT8                                               aucReserved[2];
}NAS_MML_CONN_STATUS_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucImsVoiceAvail;         /* VOS_TRUE:  IMS voice����
                                                                                        VOS_FALSE: IMS voice������ */
    NAS_MML_IMS_NORMAL_REG_STATUS_ENUM_UINT8                enImsNormalRegSta;
    VOS_UINT8                                               ucImsCallFlg;           /* VOS_TRUE:����IMS call;VOS_FALSE:������IMS call */

    NAS_MML_PERSISTENT_BEARER_STATE_ENUM_UINT8               enPersistentBearerState;
}NAS_MML_IMS_DOMAIN_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucRfAvailFlg;                           /* RF��Դ�Ƿ���ñ��:VOS_TRTUE:Ĭ��RF��Դ����;�յ�RRM����Դ����ָʾ������
                                                                                                      VOS_FALSE:RF��Դ������:ASͨ�������ظ�.RRLL_REL_IND,����ָʾ֪ͨMMCΪNO RFʱ����;  */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;                              /* �ϱ�NO RFʱ��Ľ��뼼�� */
    VOS_UINT8                           aucReserved[2];

}NAS_MML_NO_RF_INFO_STRU;
typedef struct
{
    /* ��ǰС��ϵͳ��Ϣ�а����Ĺ��� plmn id�ĸ��� */
    VOS_UINT8                           ucSuitPlmnNum;
    VOS_UINT8                           aucReserved[3];

    /* С��ϵͳ��Ϣ�а�������� ����plmn id�ĸ���   */
    NAS_MML_PLMN_ID_STRU                astSuitPlmnList[MMC_LMM_MAX_SRCH_PLMN_NUM];
} NAS_MML_SUIT_PLMN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_ORIGNAL_REJECT_CAUSE_STRU
 �ṹ˵��  :  ����ܾ�ԭ��ֵ��Ϣ
 1.��    ��   : 2015��4��29��
   ��    ��   : g00322017
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOriginalRejectCause;
    VOS_UINT8                           aucReserved[3];
}NAS_MML_ORIGNAL_REJECT_CAUSE_STRU;



typedef struct
{
    NAS_MML_CAMP_PLMN_INFO_STRU         stCampPlmnInfo;                         /* ��ǰפ��PLMN��Ϣ */
    NAS_MML_CS_DOMAIN_INFO_STRU         stCsDomainInfo;                         /* ��ǰCS����Ϣ */
    NAS_MML_PS_DOMAIN_INFO_STRU         stPsDomainInfo;                         /* ��ǰPS����Ϣ */
    NAS_MML_MS_BAND_INFO_STRU           stBandInfo;                             /* ��ǰפ����BAND��Ϣ */
    NAS_MML_NETWORK_3GPP_REL_STRU       stNetwork3GppRel;                       /* ��ǰ�����Э��汾 */
    NAS_MML_EQUPLMN_INFO_STRU           stEquPlmnInfo;                          /* EQUPLMN��Ϣ */
    NAS_MML_CONN_STATUS_INFO_STRU       stConnStatus;                           /* ��ǰ���Ӵ���״̬ */
    NAS_MML_EPS_DOMAIN_INFO_STRU        stEpsDomainInfo;                        /* EPS����Ϣ */
    NAS_MML_PS_BEARER_CONTEXT_STRU      astPsBearerContext[NAS_MML_MAX_PS_BEARER_NUM];  /* PS������������Ϣ */
    NAS_MML_EMERGENCY_NUM_LIST_STRU     stEmergencyNumList;

    NAS_MML_IMS_DOMAIN_INFO_STRU        stImsDomainInfo;                        /* IMS����Ϣ */

    NAS_MML_NO_RF_INFO_STRU             stNoRfInfo;

    NAS_MML_SUIT_PLMN_LIST_STRU         stSuitPlmnListInfo;                     /* ��ǰС��ϵͳ��Ϣ�а����Ĺ��� plmn id��Ϣ */

    NAS_MML_ORIGNAL_REJECT_CAUSE_STRU   stOriginalRejectCause;
}NAS_MML_NETWORK_INFO_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* ��ϢID */
    VOS_UINT8                           aucReserve[2];

    VOS_UINT8                           aucBuf[NAS_MML_MAX_INTERNAL_MSG_LEN];   /* ��Ϣ���� */
}NAS_MML_INTERNAL_MSG_BUF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_INTERNAL_MSG_QUEUE_STRU
 �ṹ˵��  : ����NAS MM ���ڲ���Ϣ������
 1.��    ��   : 2011��6��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    /* NAS MM���ڲ���Ϣ���� */
    NAS_MML_INTERNAL_MSG_BUF_STRU       astNasMmMsgQueue[NAS_MML_MAX_MSG_QUEUE_SIZE];

    /* ������Ϣ��ʱ����buff,����ֲ�����ʱֱ��ʹ�øÿռ�,Ϊ�˱��ⷢ���ڲ���Ϣʱ
    ռ�ýϴ��ջ�ռ� */
    NAS_MML_INTERNAL_MSG_BUF_STRU       stSendMsgBuf;

    /*�ڲ���Ϣ������е�����βָ��*/
    VOS_UINT8                           ucTail;

    /*�ڲ���Ϣ������е�����ͷָ��*/
    VOS_UINT8                           ucHeader;

    VOS_UINT16                          usReserved;
} NAS_MML_INTERNAL_MSG_QUEUE_STRU;



typedef struct
{
    VOS_UINT8                           ucOmConnectFlg;                         /* PC���ߵ�����״̬, VOS_TRUE: ������; VOS_FALSE: δ���� */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* PC����ʹ��NAS��PC�طű�־ , VOS_TRUE:ʹ��; VOS_FALSE: δʹ�� */
    VOS_UINT8                           aucRsv2[2];
}NAS_MML_OM_MAINTAIN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucUeSndPcRecurFlg;                       /* PC�ط��Ƿ���Ҫ����ȫ�ֱ���,VOS_TRUE:��Ҫ, VOS_FALSE:����Ҫ, */
    VOS_UINT8                           ucRsv3[3];
}NAS_MML_UE_MAINTAIN_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucErrLogCtrlFlag;                       /* ERRLOG�򿪱�ʶ */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usAlmLevel;                             /* ���ϸ澯���� */
}NAS_MML_ERRLOG_CTRL_INFO_STRU;


typedef struct
{
    OM_RING_ID                          pstRingBuffer;                          /* MM��Ĺ����� */
    VOS_UINT32                          ulOverflowCnt;                          /* Ringbuf����Ĵ��� */
}NAS_MML_ERRLOG_BUFF_INFO_STRU;


typedef struct
{
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCurrState;                            /* ��ǰ�Ĺ���״̬ */
    VOS_UINT32                          ulPositionNum;
    NAS_MNTN_POSITION_INFO_STRU         astPositionInfo[NAS_ERR_LOG_MAX_POSITION_RECORD_NUM];
    VOS_UINT32                          ulStateNum;
    NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU astStateInfo[NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM];
}NAS_MML_ERRLOG_CSFB_MT_INFO_STRU;

/* Added by zwx247453 for CHR optimize, 2015-03-13 begin */
/*****************************************************************************
 �ṹ��    : NAS_MML_ERRLOG_PAGING_INFO_STRU
 �ṹ˵��  : NAS_MML_ERRLOG_PAGING_INFO_STRU��Ϣ
 1.��    ��   : 2015��03��13��
   ��    ��   : zwx247453
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucGMsIdType;
    VOS_UINT8                               ucGPagingType;
    VOS_UINT8                               aucReserve1[2];
    VOS_UINT32                              ulWCnDomainId;
    VOS_UINT32                              ulWPagingType;
    VOS_UINT32                              ulWPagingCause;
    VOS_UINT32                              ulWPagingUeId;
}NAS_MML_ERRLOG_PAGING_INFO_STRU;
/* Added by zwx247453 for CHR optimize, 2015-03-13 end */

typedef struct
{
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32       enOosEvent;                         /* �����¼� */
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32       enCsOosCause;                       /* CS����ԭ�� */
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32       enPsOosCause;                       /* PS����ԭ�� */
    VOS_UINT32                              ulSearchType;                       /* �������� */
    NAS_MML_PLMN_ID_STRU                    stPlmnId;                           /* ����PLMN */
    VOS_UINT32                              ulPlmnSrchReqSlice;                 /* ����ʱ��� */
    NAS_ERR_LOG_RATMODE_ENUM_UINT8          enSrchRat;                          /* �������뼼�� */
    VOS_UINT8                               aucReserve1[3];
    VOS_UINT32                              ulSearchCount;                      /* ����������¼ͳ�� */
    VOS_UINT32                              ulCfgRecordNum;                     /* NV���ü�¼�Ĵ��� */
    VOS_UINT8                               ucCfgActiveFlag;                    /* NV�������Ƿ񼤻� */
    VOS_UINT8                               aucReserve2[3];
}NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU;


typedef struct
{
    VOS_UINT32                                      ulBandScanStartSlice;   /* CSS Multi-Band SCAN�Ŀ�ʼʱ�� */
    VOS_UINT32                                      ulBandScanFinishSlice;  /* CSS Multi-Band SCAN�Ľ���ʱ�� */
    CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8           enResult;               /* ɨ���������û��ɨ������������쳣ʱ��Я���Ľ��ʱʧ�� */
    CSS_COVERAGE_TYPE_ENUM_UINT8                    enGsmCoverageType;      /* ���ɨƵ������ָʾ���Ǹ������������ϱ��Ľ��ֻ�и��������ǻ�����ɨƵ��� */
    CSS_COVERAGE_TYPE_ENUM_UINT8                    enUmtsFddCoverageType;  /* ͬ��*/
    CSS_COVERAGE_TYPE_ENUM_UINT8                    enLteCoverageType;      /* ͬ��*/
}NAS_MML_ERRLOG_FFT_BAND_SCAN_INFO_STRU;


typedef struct
{
    VOS_UINT8                                   ucSrchRslt;             /* GET_GEO��MCC�Ľ�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8        enMccRatType;           /* GET_GEO�ҵ�MCC�Ľ��뼼������,ֻ�е���MCCʱ����ֵ����Ч */
    VOS_UINT8                                   aucRsv[2];
    VOS_UINT32                                  ulSrchStartSlice;       /* GET_GEO����MCC�Ŀ�ʼʱ��� */
    VOS_UINT32                                  ulSrchFinishSlice;      /* GET_GEO����MCC�Ľ���ʱ��� */
    NAS_MML_ERRLOG_FFT_BAND_SCAN_INFO_STRU      stCssBandScanInfo;      /* GET_GEOִ��CSS Multi-Band SCAN�Ľ�� */
}NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU;
typedef struct
{
    NAS_MML_ERRLOG_CTRL_INFO_STRU       stCtrlInfo;
    NAS_MML_ERRLOG_BUFF_INFO_STRU       stBuffInfo;
    NAS_MML_ERRLOG_CSFB_MT_INFO_STRU    stCsfbMtInfo;
    /* Added by zwx247453 for CHR optimize, 2015-03-13 begin */
    NAS_MML_ERRLOG_PAGING_INFO_STRU     stPagingInfo;
    /* Added by zwx247453 for CHR optimize, 2015-03-13 end */
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU  stNwSrchInfo;
    /* FFT����MCC���ͳ���ϱ� */
    NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU   stFftSrchInfo;
}NAS_MML_ERRLOG_MNTN_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucFtmCtrlFlag;                          /* ���̲˵��򿪱�ʶ */
    VOS_UINT8                           aucReserved[3];
}NAS_MML_FTM_MNTN_INFO_STRU;
typedef struct
{
    VOS_UINT32                          ulReceiveTime;                          /* ����ʱ�� */
    VOS_UINT16                          usSendPid;                              /* ����PID */
    VOS_UINT16                          usReceivePid;                           /* ����PID */
    VOS_UINT16                          usMsgName;                              /* ��Ϣ��  */
    VOS_UINT8                           ucMmcFsmId;                             /* MMC��ǰ״̬����ʶ */
    VOS_UINT8                           ucMmcState;                             /* MMC��ǰ״̬ */
    VOS_UINT8                           ucGmmState;                             /* GMM��ǰ״̬ */
    VOS_UINT8                           ucMmState;                              /* MM��ǰ״̬ */
    VOS_UINT8                           aucReserve[2];
}NAS_MML_EVENT_STATE_STRU;


typedef struct
{
    NAS_MML_EVENT_STATE_STRU            stEventState[NAS_MML_MAX_LOG_EVENT_STATE_NUM];
    VOS_UINT32                          ulExitTime;
    VOS_UINT8                           ucLatestIndex;
    VOS_UINT8                           ucReserve[3];
}NAS_MML_LOG_EVENT_STATE_STRU;


typedef struct
{
    NAS_MML_OM_MAINTAIN_INFO_STRU       stOmMaintainInfo;
    NAS_MML_UE_MAINTAIN_INFO_STRU       stUeMaintainInfo;
    NAS_MML_ERRLOG_MNTN_INFO_STRU       stErrLogMntnInfo;
    NAS_MML_FTM_MNTN_INFO_STRU          stFtmMntnInfo;
    NAS_MML_LOG_EVENT_STATE_STRU        stLogEventState;

}NAS_MML_MAINTAIN_CTX_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MML_CTX_INFO_STRU
 �ṹ˵��  : MML_CTX��Ϣ
 1.��    ��   : 2011��6��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MML_SIM_INFO_STRU               stSimInfo;                              /* SIM��Ϣ */
    NAS_MML_MS_CFG_INFO_STRU            stMsCfgInfo;                            /* MS��������Ϣ */
    NAS_MML_NETWORK_INFO_STRU           stNetworkInfo;                          /* ��ǰפ����������Ϣ */
    NAS_MML_INTERNAL_MSG_QUEUE_STRU     stInternalMsgQueue;                     /* MM�Ӳ���ڲ���Ϣ���� */
    NAS_MML_MAINTAIN_CTX_STRU           stMaintainInfo;
}NAS_MML_CTX_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
NAS_MML_SIM_FORBIDPLMN_INFO_STRU* NAS_MML_GetForbidPlmnInfo( VOS_VOID );

NAS_MML_BG_SEARCH_CFG_INFO_STRU* NAS_MML_GetBgSearchCfg( VOS_VOID );

NAS_MML_CONN_STATUS_INFO_STRU* NAS_MML_GetConnStatus(VOS_VOID);

VOS_VOID NAS_MML_SetRrcConnStatusFlg(
    VOS_UINT8                           ucRrcStatusFlg
);

VOS_VOID NAS_MML_SetCsSigConnStatusFlg(
    VOS_UINT8                           ucCsSigConnStatusFlg
);

VOS_UINT8 NAS_MML_GetCsSigConnStatusFlg(VOS_VOID);

VOS_VOID NAS_MML_SetPsSigConnStatusFlg(
    VOS_UINT8                           ucPsSigConnStatusFlg
);

VOS_VOID NAS_MML_SetPsTbfStatusFlg(
    VOS_UINT8                           ucPsTbfStatusFlg
);

VOS_UINT8 NAS_MML_GetPsTbfStatusFlg( VOS_VOID );


VOS_VOID NAS_MML_SetEpsSigConnStatusFlg(
    VOS_UINT8                           ucEpsSigConnStatusFlg
);

VOS_VOID NAS_MML_SetEpsServiceConnStatusFlg(
    VOS_UINT8                           ucEpsServiceConnStatusFlg
);

VOS_VOID NAS_MML_SetCsServiceConnStatusFlg(
    VOS_UINT8                           ucCsServiceConnStatusFlg
);

VOS_UINT8 NAS_MML_GetCsServiceConnStatusFlg(VOS_VOID);

VOS_VOID NAS_MML_SetCsServiceBufferStatusFlg(
    VOS_UINT8                           ucCsServiceBufferStatusFlg
);

VOS_VOID NAS_MML_SetPsServiceBufferStatusFlg(
    VOS_UINT8                           ucPsServiceBufferStatusFlg
);

VOS_UINT8 NAS_MML_GetPsServiceBufferStatusFlg(VOS_VOID);

VOS_VOID NAS_MML_SetCsEmergencyServiceFlg(
    VOS_UINT8                           ucEmergencyServiceFlg
);

VOS_UINT8 NAS_MML_GetCsEmergencyServiceFlg(VOS_VOID );
VOS_VOID NAS_MML_SetPsTcServiceFlg(
    VOS_UINT8                           ucPsTcServiceFlg
);

NAS_MML_CS_DOMAIN_INFO_STRU* NAS_MML_GetCsDomainInfo( VOS_VOID );

NAS_MML_LAI_STRU* NAS_MML_GetCsLastSuccLai( VOS_VOID );

VOS_UINT32 NAS_MML_GetCsLastSuccLac( VOS_VOID );

NAS_MML_PLMN_ID_STRU*  NAS_MML_GetCsLastSuccPlmnId( VOS_VOID );

VOS_UINT32  NAS_MML_GetCsLastSuccMcc( VOS_VOID );

VOS_UINT32  NAS_MML_GetCsLastSuccMnc( VOS_VOID );


NAS_MML_RAI_STRU* NAS_MML_GetPsLastSuccRai( VOS_VOID );

VOS_UINT8 NAS_MML_GetCsRejSearchSupportFlg( VOS_VOID );
VOS_UINT8 NAS_MML_GetRoamBrokerActiveFlag( VOS_VOID );

VOS_VOID NAS_MML_SetCsRejSearchSupportFlg(
    VOS_UINT8                           ucCsRejSearchSupportFlg
);


VOS_UINT8 NAS_MML_GetDtSingleDomainPlmnSearchFlag( VOS_VOID );

VOS_VOID NAS_MML_SetDtSingleDomainPlmnSearchFlag(
    VOS_UINT8                           ucPlmnSrchFlag
);

VOS_UINT8 NAS_MML_GetRoamBrokerRegisterFailCnt( VOS_VOID );

VOS_VOID NAS_MML_SetRoamBrokerRegisterFailCnt(
    VOS_UINT8                           ucRoamBrokerRegisterFailCnt
);


NAS_MML_MS_BAND_INFO_STRU* NAS_MML_GetCurrBandInfo( VOS_VOID );


NAS_MML_CAMP_PLMN_INFO_STRU* NAS_MML_GetCurrCampPlmnInfo( VOS_VOID );

NAS_MML_LAI_STRU*  NAS_MML_GetCurrCampLai( VOS_VOID );

VOS_UINT32  NAS_MML_GetCurrCampLac( VOS_VOID );

NAS_MML_LAI_STRU*  NAS_MML_GetOldCampLai( VOS_VOID );


VOS_UINT8 NAS_MML_GetCurrCampRac(VOS_VOID);

VOS_UINT32 NAS_MML_GetCurrCampArfcn(VOS_VOID);

VOS_VOID NAS_MML_SetCurrCampArfcn(
    VOS_UINT32                          ulArfcn
);

NAS_MML_CAMP_CELL_INFO_STRU* NAS_MML_GetCampCellInfo( VOS_VOID );


NAS_MML_NET_RAT_TYPE_ENUM_UINT8  NAS_MML_GetCurrNetRatType( VOS_VOID );

VOS_VOID  NAS_MML_SetCurrNetRatType(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
);

VOS_UINT8 NAS_MML_GetRfAvailFlg( VOS_VOID );
VOS_VOID NAS_MML_SetRfAvailFlg(
    VOS_UINT8                           ucRfAvailFlg
);
VOS_VOID  NAS_MML_SetCurrRatRfAvailFlg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType,
    VOS_UINT8                           ucRfAvail
);

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MML_GetNoRfRatType( VOS_VOID );




VOS_VOID  NAS_MML_SetCurrSysSubMode(
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode
);
NAS_MML_PLMN_ID_STRU*  NAS_MML_GetCurrCampPlmnId( VOS_VOID );

NAS_MML_EQUPLMN_INFO_STRU* NAS_MML_GetEquPlmnList( VOS_VOID );

NAS_MML_SUIT_PLMN_LIST_STRU* NAS_MML_GetSuitPlmnList(VOS_VOID);
VOS_VOID  NAS_MML_InitSuitPlmnListInfo(
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnListInfo
);
VOS_UINT8 NAS_MML_GetEpsServiceConnStatusFlg(VOS_VOID);
NAS_MML_GMM_PROC_INFO_STRU *NAS_MML_GetGmmProcInfo( VOS_VOID );
VOS_VOID NAS_MML_SetGmmProcFlag(
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16   enGmmProcFlag
);

NAS_MML_SM_PROC_FLAG_ENUM_UINT8 NAS_MML_GetSmProcFlag(VOS_VOID);
VOS_VOID NAS_MML_SetSmProcFlag(
    NAS_MML_SM_PROC_FLAG_ENUM_UINT8     enSmProcFlag
);
VOS_VOID NAS_MML_SetGmmProcType(
    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16   enGmmProcType
);


VOS_UINT32 NAS_MML_GetVoiceNotAvailPlmnForbiddenPeriod(VOS_VOID);
VOS_VOID NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(
    VOS_UINT32                          ulLteVoiceNotAvailPlmnForbiddenPeriod
);

NAS_MML_3GPP_REL_ENUM_UINT8   NAS_MML_GetLte3gppRelVersion(VOS_VOID);
NAS_MML_PERSISTENT_BEARER_STATE_ENUM_UINT8  NAS_MML_GetPersistentBearerState(VOS_VOID);
VOS_VOID    NAS_MML_SetPersistentBearerState(
    NAS_MML_PERSISTENT_BEARER_STATE_ENUM_UINT8              enPersistentBearerState
);
VOS_VOID  NAS_MML_SetLte3gppRelVersion(
    NAS_MML_3GPP_REL_ENUM_UINT8         enLteNasRelease
);


NAS_MML_HPLMN_CFG_INFO_STRU* NAS_MML_GetHplmnCfg( VOS_VOID );

NAS_MML_CTX_STRU*  NAS_MML_GetMmlCtx( VOS_VOID );

NAS_MML_MS_3GPP_REL_STRU* NAS_MML_GetMs3GppRel(VOS_VOID);

NAS_MML_MS_CAPACILITY_INFO_STRU* NAS_MML_GetMsCapability(VOS_VOID);

VOS_UINT8* NAS_MML_GetImeisv( VOS_VOID );

NAS_MML_MS_CFG_INFO_STRU* NAS_MML_GetMsCfgInfo( VOS_VOID );

NAS_MML_MS_MODE_ENUM_UINT8 NAS_MML_GetMsMode( VOS_VOID);


NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8 NAS_MML_GetLteCsServiceCfg( VOS_VOID);




VOS_UINT8   NAS_MML_GetLteRoamAllowedFlg(VOS_VOID);

VOS_UINT32 NAS_MML_GetDisableLteRoamFlg( VOS_VOID);

VOS_VOID NAS_MML_GetRoamEnabledMccList(VOS_UINT32 *pulMcc);

VOS_UINT8 NAS_MML_GetDailRejectCfg( VOS_VOID);

VOS_VOID NAS_MML_SetDisableLteRoamFlg(
    VOS_UINT32                          ulDisableFlg
);

VOS_VOID NAS_MML_SetRoamEnabledMccList(VOS_UINT32 *pulMcc);

VOS_VOID NAS_MML_SetRoamRplmnSearchFlg(VOS_UINT8 pulRoamRplmnFlg);
VOS_UINT8 NAS_MML_GetRoamRplmnSearchFlg(VOS_VOID);
VOS_VOID NAS_MML_SetDisableLTEOnBandFlg(VOS_UINT8 ucDisableLTEOnBandFlg);
VOS_UINT8 NAS_MML_GetDisableLTEOnBandFlg(VOS_VOID);
VOS_UINT32 *NAS_MML_GetNationalMCCList(VOS_VOID);
VOS_VOID NAS_MML_SetNationalMCCList(VOS_UINT32 *pulMcc);

VOS_VOID NAS_MML_SetUltraFlashCsfbSupportFlg(
    VOS_UINT8                           ucUltraFlashCsfbSupportFlg
);
VOS_UINT8 NAS_MML_GetUltraFlashCsfbSupportFlg(VOS_VOID);

VOS_VOID NAS_MML_SetLteRoamAllowedFlg(
    VOS_UINT8                           ucAllowedFlg
);

VOS_VOID NAS_MML_SetDailRejectCfg(
    VOS_UINT8                           ucEnableFlg
);


NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU* NAS_MML_GetRoamingRejectNoRetryCfg( VOS_VOID );


NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU* NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo( VOS_VOID );

VOS_VOID NAS_MML_InitHplmnAuthRejCounter(
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU                      *pstAuthRejInfo
);

NAS_MML_IGNORE_AUTH_REJ_INFO_STRU * NAS_MML_GetAuthRejInfo(
    VOS_VOID
);

VOS_VOID NAS_MML_SetIgnoreAuthRejFlg(
    VOS_UINT8                           ucIgnoreAuthRejFlg
);

VOS_VOID NAS_MML_SetMaxAuthRejNo(
    VOS_UINT8                           ucMaxAuthRejNo
);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID NAS_MML_SetCallMode(
    NAS_MML_CALL_MODE_ENUM_UINT8       enCallMode
);
NAS_MML_CALL_MODE_ENUM_UINT8  NAS_MML_GetCallMode(VOS_VOID);
#endif

VOS_VOID  NAS_MML_InitRoamingRejectNoRetryInfo(
    NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU           *pstRetryInfo
);

VOS_VOID NAS_MML_SetMsMode(NAS_MML_MS_MODE_ENUM_UINT8 enMsMode);

NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32 NAS_MML_GetLteCapabilityStatus(VOS_VOID);

MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32 NAS_MML_GetDisableLteReason( VOS_VOID);

VOS_VOID NAS_MML_SetLteDisabledRauUseLteInfoFlag(VOS_UINT8 ucLteDisabledUseLteInfoFlag);
VOS_UINT8 NAS_MML_GetLteDisabledRauUseLteInfoFlag( VOS_VOID);


VOS_VOID NAS_MML_SetLteCapabilityStatus(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
);

VOS_VOID NAS_MML_SetDisableLteReason(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
);

VOS_VOID NAS_MML_SetLteCsServiceCfg(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg
);

VOS_UINT8 NAS_MML_GetPsAutoAttachFlg(VOS_VOID);



VOS_VOID NAS_MML_SetUserAutoReselActiveFlg(VOS_UINT8 ucActiveFlag);

VOS_UINT8 NAS_MML_GetUserAutoReselActiveFlg(VOS_VOID);


NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MML_GetMsPrioRatList( VOS_VOID );

NAS_MML_3GPP2_RAT_PRIO_STRU* NAS_MML_GetMs3Gpp2PrioRatList( VOS_VOID );

NAS_MML_MS_BAND_INFO_STRU* NAS_MML_GetMsSupportBand( VOS_VOID );

NAS_MML_NETWORK_3GPP_REL_STRU* NAS_MML_GetNetwork3GppRel( VOS_VOID );

NAS_MML_NETWORK_INFO_STRU* NAS_MML_GetNetworkInfo( VOS_VOID );

NAS_MML_PLMN_LOCK_CFG_INFO_STRU* NAS_MML_GetPlmnLockCfg( VOS_VOID );

NAS_MML_CUSTOM_CFG_INFO_STRU* NAS_MML_GetCustomCfg( VOS_VOID );

NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU* NAS_MML_GetDisabledRatPlmnInfo( VOS_VOID );


NAS_MML_RAT_FORBIDDEN_LIST_STRU* NAS_MML_GetRatForbiddenListCfg( VOS_VOID );

NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetGsmForbiddenStatusFlg( VOS_VOID );

NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetUtranForbiddenStatusFlg( VOS_VOID );

NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetLteForbiddenStatusFlg( VOS_VOID );

VOS_VOID NAS_MML_SetGsmForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enGsmCapaStatus );

VOS_VOID NAS_MML_SetUtranForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enUtranCapaStatus );

VOS_VOID NAS_MML_SetLteForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enLteCapaStatus );

VOS_UINT8 NAS_MML_GetImsiInForbiddenListFlg( VOS_VOID );

VOS_VOID NAS_MML_SetImsiInForbiddenListFlg(
    VOS_UINT8 ucIsImsiInForbiddenList
);

NAS_MML_PS_DOMAIN_INFO_STRU* NAS_MML_GetPsDomainInfo( VOS_VOID );

VOS_VOID NAS_MML_SetPsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enPsRegStatus
);

VOS_VOID NAS_MML_SetCsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enCsRegStatus
);

NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetPsRegStatus( VOS_VOID );

NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetCsRegStatus( VOS_VOID );


NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetEpsRegStatus( VOS_VOID );

VOS_VOID NAS_MML_SetEpsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enEpsRegStatus
);


NAS_MML_ROAM_CFG_INFO_STRU* NAS_MML_GetRoamCfg( VOS_VOID );

NAS_MML_AIS_ROAMING_CFG_STRU* NAS_MML_GetAisRoamingCfg( VOS_VOID );



NAS_MML_PRIO_HPLMNACT_CFG_STRU* NAS_MML_GetPrioHplmnActCfg( VOS_VOID );


VOS_VOID NAS_MML_SetRelCauseCsfbHighPrioFlg(
    VOS_UINT8       ucFlg
);

VOS_UINT32 NAS_MML_GetRelCauseCsfbHighPrioFlg( VOS_VOID );

NAS_MML_RPLMN_CFG_INFO_STRU* NAS_MML_GetRplmnCfg( VOS_VOID );

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MML_GetLastRplmnRat( VOS_VOID );

VOS_VOID NAS_MML_SetLastRplmnRat(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enRat);

NAS_MML_SIM_CS_SECURITY_INFO_STRU* NAS_MML_GetSimCsSecurity(VOS_VOID);

NAS_MML_SIM_EHPLMN_INFO_STRU* NAS_MML_GetSimEhplmnList(VOS_VOID);

NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU* NAS_MML_GetSimHplmnWithRatList(VOS_VOID);

NAS_MML_SIM_INFO_STRU*  NAS_MML_GetSimInfo( VOS_VOID );

NAS_MML_SIM_MS_IDENTITY_STRU* NAS_MML_GetSimMsIdentity(VOS_VOID);

VOS_UINT8* NAS_MML_GetSimImsi(VOS_VOID);
VOS_UINT8* NAS_MML_GetUeIdPtmsi(VOS_VOID);
VOS_VOID NAS_MML_SetUeIdPtmsi(
    VOS_UINT8                          *pucPtmsi
);
VOS_UINT8* NAS_MML_GetUeIdPtmsiSignature(VOS_VOID);
VOS_VOID NAS_MML_SetUeIdPtmsiSignature(
    VOS_UINT8                          *pucPtmsiSignature
);
VOS_UINT8* NAS_MML_GetUeIdTmsi(VOS_VOID);
VOS_VOID NAS_MML_SetUeIdTmsi(
    VOS_UINT8                          *pucTmsi
);

VOS_VOID NAS_MML_SetUeOperMode(
    NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8 enUeOperMode
);

NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8 NAS_MML_GetUeOperMode(VOS_VOID);

NAS_MML_SIM_OPERPLMN_INFO_STRU* NAS_MML_GetSimOperPlmnList(VOS_VOID);

NAS_MML_SIM_PS_SECURITY_INFO_STRU* NAS_MML_GetSimPsSecurity(VOS_VOID);
VOS_VOID NAS_MML_SetSimPsSecurity(
    NAS_MML_SIM_PS_SECURITY_INFO_STRU   *pstSimPsSecruity

);


NAS_MML_SIM_SELPLMN_INFO_STRU* NAS_MML_GetSimSelPlmnList(VOS_VOID);

NAS_MML_SIM_STATUS_STRU* NAS_MML_GetSimStatus(VOS_VOID);

NAS_MML_SIM_USERPLMN_INFO_STRU* NAS_MML_GetSimUserPlmnList(VOS_VOID);

VOS_UINT8 NAS_MML_GetStkSteeringOfRoamingSupportFlg( VOS_VOID );

VOS_VOID  NAS_MML_InitBgSearchCfgInfo(
    NAS_MML_BG_SEARCH_CFG_INFO_STRU     *pstBgSearchCfg
);
VOS_VOID NAS_MML_InitRssiValue(
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCellInfo
);
VOS_VOID NAS_MML_InitCampRai(
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo
);

VOS_VOID  NAS_MML_InitCampPlmnInfo(
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo
);
VOS_VOID  NAS_MML_InitConnStatusInfo(
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus
);
VOS_VOID  NAS_MML_InitCsDomainInfo(
    NAS_MML_CS_DOMAIN_INFO_STRU         *pstCsDomainInfo
);
VOS_VOID  NAS_MML_InitCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_CTX_STRU                    *pstMmlCtx
);
VOS_VOID  NAS_MML_InitCustomCfgInfo(
    NAS_MML_CUSTOM_CFG_INFO_STRU        *pstCustomCfg
);
VOS_VOID  NAS_MML_InitEquPlmnInfo(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);
VOS_VOID  NAS_MML_InitHplmnCfgInfo(
    NAS_MML_HPLMN_CFG_INFO_STRU         *pstHplmnCfg
);
VOS_VOID  NAS_MML_InitInternalMsgQueue(
    NAS_MML_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MM�Ӳ���ڲ���Ϣ���� */
);
VOS_VOID  NAS_MML_InitMiscellaneousCfgInfo(
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfg
);
VOS_VOID  NAS_MML_InitMs3GppRel(
    NAS_MML_MS_3GPP_REL_STRU            *pstMs3GppRel
);
VOS_VOID  NAS_MML_InitMsCapability(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability
);
VOS_VOID  NAS_MML_InitMsCfgCtx(
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfgInfo
);
VOS_VOID  NAS_MML_InitMsCurrBandInfoInfo(
    NAS_MML_MS_BAND_INFO_STRU         *pstMsBandInfo
);
VOS_VOID  NAS_MML_InitMsSysCfgInfo(
    NAS_MML_MS_SYS_CFG_INFO_STRU        *pstMsSysCfgInfo
);
VOS_VOID  NAS_MML_InitNetwork3GppRel(
    NAS_MML_NETWORK_3GPP_REL_STRU            *pstNetwork3GppRel
);
VOS_VOID  NAS_MML_InitNetworkCtx(
    NAS_MML_NETWORK_INFO_STRU           *pstNetworkInfo
);
VOS_VOID  NAS_MML_InitPlmnLockCfgInfo(
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU     *pstPlmnLockCfg
);

VOS_VOID  NAS_MML_InitRatForbiddenList(
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList
);

VOS_VOID  NAS_MML_InitRatForbiddenStatusCfg(
    NAS_MML_RAT_FORBIDDEN_STATUS_STRU  *pstRatCapaStatus
);

VOS_VOID  NAS_MML_InitPsDomainInfo(
    NAS_MML_PS_DOMAIN_INFO_STRU         *pstPsDomainInfo
);

VOS_VOID  NAS_MML_InitDisabledRatPlmnCfgInfo(
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg
);

VOS_VOID NAS_MML_InitEpsDomainInfo(
    NAS_MML_EPS_DOMAIN_INFO_STRU        *pstEpsDomainInfo
);
VOS_VOID  NAS_MML_InitRoamCfgInfo(
    NAS_MML_ROAM_CFG_INFO_STRU          *pstRoamCfg
);
VOS_VOID  NAS_MML_InitRplmnCfgInfo(
    NAS_MML_RPLMN_CFG_INFO_STRU         *pstRplmnCfg
);
VOS_VOID  NAS_MML_InitSimCsSecurityCtx(
    NAS_MML_SIM_CS_SECURITY_INFO_STRU   *pstCsSecurity
);
VOS_VOID  NAS_MML_InitCsSecurityUmtsCkInvalid(VOS_VOID);
VOS_VOID  NAS_MML_InitCsSecurityUmtsIkInvalid(VOS_VOID);

VOS_VOID  NAS_MML_InitSimEhPlmnInfo(
    NAS_MML_SIM_EHPLMN_INFO_STRU        *pstEhPlmnInfo
);
VOS_VOID  NAS_MML_InitSimForbidPlmnInfo(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo
);

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
VOS_VOID NAS_MML_InitForbLaWithValidPeriodCfg(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
);

VOS_VOID  NAS_MML_InitForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod

);

NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU* NAS_MML_GetForbLaWithValidPeriodCfg( VOS_VOID );

NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU* NAS_MML_GetForbLaWithValidPeriodList( VOS_VOID );

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */
VOS_VOID  NAS_MML_InitSimHPlmnWithRatInfo(
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU *pstHplmnWithRatInfo
);
VOS_VOID  NAS_MML_InitSimInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_SIM_INFO_STRU              *pstSimInfo
);
VOS_VOID  NAS_MML_InitSimMsIdentityInfoCtx(
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity
);
VOS_VOID  NAS_MML_InitUeIdPtmisInvalid(VOS_VOID);
VOS_VOID  NAS_MML_InitUeIdPtmsiSignatureInvalid(VOS_VOID);
VOS_VOID  NAS_MML_InitUeIdTmsiInvalid(VOS_VOID);

VOS_VOID  NAS_MML_InitSimOperPlmnInfo(
    NAS_MML_SIM_OPERPLMN_INFO_STRU      *pstOperPlmnInfo
);
VOS_VOID  NAS_MML_InitSimPlmnInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_SIM_PLMN_INFO_STRU         *pstSimStatusInfo
);
VOS_VOID  NAS_MML_InitSimPsSecurityCtx(
    NAS_MML_SIM_PS_SECURITY_INFO_STRU   *pstPsSecurity
);
VOS_VOID  NAS_MML_InitPsSecurityGsmKcInvalid(VOS_VOID);
VOS_VOID  NAS_MML_InitPsSecurityUmtsCkInvalid(VOS_VOID);
VOS_VOID  NAS_MML_InitPsSecurityUmtsIkInvalid(VOS_VOID);
VOS_VOID  NAS_MML_InitCsSecurityGsmKcInvalid(VOS_VOID);

VOS_VOID  NAS_MML_InitSimSelPlmnInfo(
    NAS_MML_SIM_SELPLMN_INFO_STRU        *pstSelPlmnInfo
);

VOS_VOID  NAS_MML_InitSimStatusInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_SIM_STATUS_STRU             *pstSimStatusInfo
);
VOS_VOID  NAS_MML_InitSimUserPlmnInfo(
    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnInfo
);
VOS_VOID NAS_MML_SetMs3GppRel(
    NAS_MML_MS_3GPP_REL_STRU            *pstMs3GppRel
);
VOS_VOID NAS_MML_SetSimCsSecurity(
    NAS_MML_SIM_CS_SECURITY_INFO_STRU   *pstSimCsSecruity
);

VOS_UINT8 NAS_MML_GetSimCsSecurityCksn(VOS_VOID);
VOS_VOID NAS_MML_SetSimCsSecurityCksn(
    VOS_UINT8                           ucCksn
);
VOS_UINT8* NAS_MML_GetSimCsSecurityUmtsCk(VOS_VOID);
VOS_VOID NAS_MML_SetSimCsSecurityUmtsCk(
    VOS_UINT8                           *pucUmtsCk
);
VOS_UINT8* NAS_MML_GetSimCsSecurityUmtsIk(VOS_VOID);
VOS_VOID NAS_MML_SetSimCsSecurityUmtsIk(
    VOS_UINT8                           *pucUmtsIk
);
VOS_UINT8* NAS_MML_GetSimCsSecurityGsmKc(VOS_VOID);
VOS_VOID NAS_MML_SetSimCsSecurityGsmKc(
    VOS_UINT8                           *pucGsmKc
);



VOS_VOID NAS_MML_SetSimEhplmnList(
    NAS_MML_SIM_EHPLMN_INFO_STRU        *pstEhplmnList
);

NAS_MML_SIM_PLMN_INFO_STRU* NAS_MML_GetSimPlmnInfo(VOS_VOID);

VOS_VOID NAS_MML_SetSimForbidPlmnList(
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU    *pstForbidPlmnInfo
);

VOS_VOID NAS_MML_SetSimHplmnTimerLen(
    VOS_UINT32                          ulSimHplmnTimerLen
);

VOS_UINT32 NAS_MML_GetSimHplmnTimerLen(VOS_VOID);

VOS_VOID NAS_MML_SetSimHplmnWithRatList(
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU    *pstHplmnWithRatList
);
VOS_VOID NAS_MML_SetSimMsIdentity(
    NAS_MML_SIM_MS_IDENTITY_STRU        *pstSimMsIdentity

);
VOS_VOID NAS_MML_SetSimOperPlmnList(
    NAS_MML_SIM_OPERPLMN_INFO_STRU*     pstOperPlmnList
);

VOS_UINT8 NAS_MML_GetSimPsSecurityCksn(VOS_VOID);
VOS_VOID NAS_MML_SetSimPsSecurityCksn(
    VOS_UINT8                           ucCksn
);
VOS_UINT8* NAS_MML_GetSimPsSecurityUmtsCk(VOS_VOID);
VOS_VOID NAS_MML_SetSimPsSecurityUmtsCk(
    VOS_UINT8                           *pucUmtsCk
);
VOS_UINT8* NAS_MML_GetSimPsSecurityUmtsIk(VOS_VOID);
VOS_VOID NAS_MML_SetSimPsSecurityUmtsIk(
    VOS_UINT8                           *pucUmtsIk
);
VOS_UINT8* NAS_MML_GetSimPsSecurityGsmKc(VOS_VOID);
VOS_VOID NAS_MML_SetSimPsSecurityGsmKc(
    VOS_UINT8                           *pucGsmKc
);

VOS_VOID NAS_MML_SetSimSelPlmnList(
    NAS_MML_SIM_SELPLMN_INFO_STRU       *pstSelPlmnList
);

VOS_VOID NAS_MML_SetSimPresentStatus(
    VOS_UINT8                           ucSimPresentStatus
);

VOS_VOID NAS_MML_SetSimCsRegStatus(
    VOS_UINT8                           ucSimCsRegStatus
);

VOS_VOID NAS_MML_SetSimPsRegStatus(
    VOS_UINT8                           ucSimPsRegStatus
);

VOS_VOID NAS_MML_SetPsUpdateStatus(
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus
);
NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8 NAS_MML_GetPsUpdateStatus(VOS_VOID);

VOS_VOID NAS_MML_SetCsUpdateStatus(
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus
);
NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8 NAS_MML_GetCsUpdateStatus(VOS_VOID);

VOS_VOID NAS_MML_SetSimUserPlmnList(
    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnList
);

VOS_UINT8 NAS_MML_GetSimPsRegStatus(VOS_VOID);


VOS_UINT8 NAS_MML_GetSimCsRegStatus(VOS_VOID);


NAS_MML_SIM_TYPE_ENUM_UINT8 NAS_MML_GetSimType(VOS_VOID);
VOS_VOID NAS_MML_SetSimType(
    NAS_MML_SIM_TYPE_ENUM_UINT8                 enSimType
);

VOS_UINT8 NAS_MML_GetSimPresentStatus(VOS_VOID);

VOS_UINT8 NAS_MML_GetEHplmnSupportFlg( VOS_VOID );


VOS_UINT8 NAS_MML_GetCsAttachAllowFlg( VOS_VOID );

VOS_UINT8 NAS_MML_GetPsAttachAllowFlg( VOS_VOID );

VOS_VOID NAS_MML_SetCsAttachAllowFlg(
    VOS_UINT8                           ucCsAttachAllowFlg
);

VOS_VOID NAS_MML_SetPsAttachAllowFlg(
    VOS_UINT8                           ucPsAttachAllowFlg
);

VOS_UINT8 *NAS_MML_GetOperatorNameShort(VOS_VOID);

VOS_UINT8 *NAS_MML_GetOperatorNameLong(VOS_VOID);

NAS_MML_OPERATOR_NAME_INFO_STRU* NAS_MML_GetOperatorNameInfo(VOS_VOID);

NAS_MML_AVAIL_TIMER_CFG_STRU* NAS_MML_GetAvailTimerCfg( VOS_VOID );
VOS_VOID  NAS_MML_InitAvailTimerCfgInfo(NAS_MML_AVAIL_TIMER_CFG_STRU  *pstAvailTimerCfg);

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
NAS_MML_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU* NAS_MML_GetPlmnSearchPhaseOneTotalTimerCfg(VOS_VOID);
VOS_UINT8 NAS_MML_GetPlmnSearchPhaseOneTotalTimerActiveFlag(VOS_VOID);
VOS_UINT32 NAS_MML_GetPlmnSearchPhaseOneTotalTimerLen(VOS_VOID);
/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

VOS_VOID  NAS_MML_InitUserCfgExtEHplmnInfo(
    NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU  *pstUserCfgExtEhplmnInfo
);

VOS_VOID NAS_MML_SetStkSteeringOfRoamingSupportFlg(
    VOS_UINT8                           ucStkSteeringOfRoamingSupportFlg
);

VOS_VOID NAS_MML_SetPsAutoAttachFlg(
    VOS_UINT8                           usPsAutoAttachFlg
);
NAS_MML_MISCELLANEOUS_CFG_INFO_STRU* NAS_MML_GetMiscellaneousCfgInfo( VOS_VOID );

VOS_UINT8 NAS_MML_GetPsRestrictRegisterFlg(VOS_VOID);
VOS_UINT8 NAS_MML_GetPsRestrictPagingFlg(VOS_VOID);
VOS_UINT8 NAS_MML_GetCsRestrictRegisterFlg(VOS_VOID);
VOS_UINT8 NAS_MML_GetCsRestrictPagingFlg(VOS_VOID);
VOS_VOID NAS_MML_SetCsRestrictRegisterFlg(
    VOS_UINT8                           ucCsRestrictionRegisterFlg
);
VOS_VOID NAS_MML_SetCsRestrictPagingFlg(
    VOS_UINT8                           ucCsRestrictionRegisterFlg
);
NAS_MML_ACCESS_RESTRICTION_STRU* NAS_MML_GetCsAcRestrictionInfo(VOS_VOID);
NAS_MML_ACCESS_RESTRICTION_STRU* NAS_MML_GetPsAcRestrictionInfo(VOS_VOID);

VOS_UINT8 NAS_MML_GetCsRestrictNormalServiceFlg(VOS_VOID);
VOS_UINT8 NAS_MML_GetCsRestrictEmergencyServiceFlg(VOS_VOID);

VOS_VOID NAS_MML_SetCsRestrictNormalServiceFlg(
    VOS_UINT8                           ucCsRestrictiNormalServiceFlg
);

VOS_VOID NAS_MML_SetCsRestrictEmergencyServiceFlg(
    VOS_UINT8                           ucCsRestrictiEmergencyServiceFlg
);

VOS_UINT8 NAS_MML_GetPsRestrictNormalServiceFlg(VOS_VOID);
VOS_UINT8 NAS_MML_GetPsRestrictEmergencyServiceFlg(VOS_VOID);


VOS_VOID NAS_MML_SetPsRestrictNormalServiceFlg(
    VOS_UINT8                           ucPsRestrictNormalServiceFlg
);


VOS_VOID NAS_MML_SetPsRestrictEmergencyServiceFlg(
    VOS_UINT8                           ucPsRestrictiEmergencyServiceFlg
);

VOS_VOID NAS_MML_SetPsRestrictRegisterFlg(
    VOS_UINT8                           ucPsRestrictionRegisterFlg
);
VOS_VOID NAS_MML_SetPsRestrictPagingFlg(
    VOS_UINT8                           ucPsRestrictionRegisterFlg
);

VOS_VOID NAS_MML_ClearCsPsRestrictionAll(VOS_VOID);


VOS_UINT32 NAS_MML_GetPsRegisterBarToUnBarFlg(VOS_VOID);

VOS_VOID NAS_MML_SetPsRegisterBarToUnBarFlg(
    VOS_UINT32                           ulPsUnBarFlg
);

VOS_UINT32 NAS_MML_GetCsRegisterBarToUnBarFlg(VOS_VOID);

VOS_VOID NAS_MML_SetCsRegisterBarToUnBarFlg(
    VOS_UINT32                           ulCsUnBarFlag
);


NAS_MML_TIN_TYPE_ENUM_UINT8 NAS_MML_GetTinType( VOS_VOID );

NAS_MML_UE_NETWORK_CAPABILITY_STRU* NAS_MML_GetUeNetWorkCapability(VOS_VOID);


VOS_VOID NAS_MML_SetUeNetWorkCapability(
NAS_MML_UE_NETWORK_CAPABILITY_STRU *pstUeNetworkCapbility);

NAS_MML_PLATFORM_RAT_CAP_STRU* NAS_MML_GetPlatformRatCap(VOS_VOID);
VOS_VOID NAS_MML_SetRoamCapability(
    NAS_MML_ROAM_CAPABILITY_ENUM_UINT8  enRoamCapability
);


VOS_VOID NAS_MML_SetMsSysCfgBand(
    NAS_MML_MS_BAND_INFO_STRU          *pstMsBand
);


VOS_VOID NAS_MML_SetMsSysCfgPrioRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
);

VOS_VOID NAS_MML_SaveEquPlmnList (
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstNewEquPlmnList
);
VOS_VOID NAS_MML_UpdateGURplmn (
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
);

VOS_VOID NAS_MML_SetEplmnValidFlg(
    VOS_UINT8                           ucEplmnValidFlg
);

VOS_UINT8 NAS_MML_GetEplmnValidFlg(VOS_VOID);

VOS_UINT8* NAS_MML_GetSimCsLociFileContent( VOS_VOID );

VOS_UINT8* NAS_MML_GetSimPsLociFileContent( VOS_VOID );

VOS_VOID  NAS_MML_UpdateSimCsLociFileContent(
    VOS_UINT8                          *pucCsLociFileContent
);

VOS_VOID  NAS_MML_UpdateSimPsLociFileContent(
    VOS_UINT8                          *pucPsLociFileContent
);




VOS_VOID  NAS_MML_InitMaintainInfo(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_MAINTAIN_CTX_STRU          *pstMaintainInfo
);

VOS_UINT8 NAS_MML_GetUePcRecurFlg(VOS_VOID);

VOS_VOID NAS_MML_SetUePcRecurFlg(
    VOS_UINT8                           ucUePcRecurFlg
);

VOS_UINT8 NAS_MML_GetOmConnectFlg(VOS_VOID);

VOS_VOID NAS_MML_SetOmConnectFlg(
    VOS_UINT8                           ucOmConnectFlg
);

VOS_UINT8 NAS_MML_GetOmPcRecurEnableFlg(VOS_VOID);

VOS_VOID NAS_MML_SetOmPcRecurEnableFlg(
    VOS_UINT8                           ucOmPcRecurEnableFlg
);

NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8 NAS_MML_GetCsfbServiceStatus( VOS_VOID );
NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8 NAS_MML_GetVoiceDomainPreference( VOS_VOID );
NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8 NAS_MML_GetLteUeUsageSetting( VOS_VOID );

VOS_UINT8 NAS_MML_GetLteImsSupportFlg( VOS_VOID );
VOS_UINT8 NAS_MML_GetVoiceCallOnImsSupportFlag( VOS_VOID );
VOS_UINT8 NAS_MML_GetSmsOnImsSupportFlag( VOS_VOID );
VOS_UINT8 NAS_MML_GetVideoCallOnImsSupportFlag( VOS_VOID );
VOS_UINT8 NAS_MML_GetUssdOnImsSupportFlag( VOS_VOID );

NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3412Status(VOS_VOID);
NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3423Status(VOS_VOID);
NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3402Status(VOS_VOID);
VOS_VOID NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8 enCsfbServiceStatus);
VOS_VOID NAS_MML_SetLteUeUsageSetting(
    NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8                 enUeUsageSetting
);
VOS_VOID NAS_MML_SetVoiceDomainPreference(
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPrefer
);

VOS_VOID NAS_MML_SetLteImsSupportFlg(
    VOS_UINT8                           ucImsSupportFlg
);
VOS_VOID NAS_MML_SetVoiceCallOnImsSupportFlag(
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag
);
VOS_VOID NAS_MML_SetSmsOnImsSupportFlag(
    VOS_UINT8                           ucSmsOnImsSupportFlag
);
VOS_VOID NAS_MML_SetVideoCallOnImsSupportFlag(
    VOS_UINT8                           ucVideoCallOnImsSupportFlag
);
VOS_VOID NAS_MML_SetUssdOnImsSupportFlag(
    VOS_UINT8                           ucUssdOnImsSupportFlag
);

VOS_VOID NAS_MML_SetT3412Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus);

VOS_VOID NAS_MML_SetT3423Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus);
VOS_VOID NAS_MML_SetT3402Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus);
VOS_VOID NAS_MML_InitEpsDomainInfo(
    NAS_MML_EPS_DOMAIN_INFO_STRU       *pstEpsDomainInfo
);

VOS_VOID NAS_MML_InitImsDomainInfo(
    NAS_MML_IMS_DOMAIN_INFO_STRU       *pstImsDomainInfo
);
NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8 NAS_MML_GetAdditionUpdateRslt(VOS_VOID);
VOS_VOID NAS_MML_SetAdditionUpdateRslt(
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdRslt
);

VOS_VOID NAS_MML_InitPsBearerContext(
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx
);

NAS_MML_PS_BEARER_CONTEXT_STRU* NAS_MML_GetPsBearerCtx( VOS_VOID );

VOS_VOID NAS_MML_InitEmergencyNumList(
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList
);

VOS_VOID NAS_MML_SetEmergencyNumList (
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmcNumList
);

NAS_MML_EMERGENCY_NUM_LIST_STRU* NAS_MML_GetEmergencyNumList (VOS_VOID);

VOS_VOID NAS_MML_SetTinType(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
);

VOS_VOID NAS_MML_SetPsBearerCtx(
    VOS_UINT8                           ucRabId,
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx
);


VOS_VOID NAS_MML_SetHoWaitSysinfoTimerLen(
    VOS_UINT32                          ulHoWaitSysinfoTimeLen
);

VOS_UINT32 NAS_MML_GetHoWaitSysinfoTimerLen(VOS_VOID);

VOS_VOID NAS_MML_SetCsfbEmgCallLaiChgLauFirstFlg(
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg
);

VOS_UINT8 NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg(VOS_VOID);


VOS_UINT8 NAS_MML_GetScanCtrlEnableFlg(VOS_VOID);
VOS_VOID NAS_MML_SetScanCtrlEnableFlg(VOS_UINT8 ucScanCtrlEnableFlg);

VOS_VOID NAS_MML_SetHPlmnType(
    NAS_MML_HPLMN_TYPE_ENUM_UINT8       enHPlmnType
);
NAS_MML_HPLMN_TYPE_ENUM_UINT8 NAS_MML_GetHPlmnType(VOS_VOID);
VOS_UINT8  NAS_MML_GetSingleDomainRegFailActionSupportFlag(VOS_VOID);
NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU*  NAS_MML_GetSingleDomainFailActionCtx(VOS_VOID);

NAS_MML_SOR_ADDITIONAL_LAU_STRU*  NAS_MML_GetSorAdditionalLauCtx(VOS_VOID);

VOS_VOID NAS_MML_InitSorAdditionalLauCtx(VOS_VOID);
VOS_UINT8  NAS_MML_GetRegFailNetWorkFailureCustomFlag(VOS_VOID);
VOS_VOID  NAS_MML_SetRegFailNetWorkFailureCustomFlag(VOS_UINT8 ucRegFailNetWorkFailureCustomFlg);

VOS_UINT8  NAS_MML_GetBgSearchRegardlessMccSupportFlag(VOS_VOID);
NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU*  NAS_MML_GetBgSearchRegardlessMccCtx(VOS_VOID);
VOS_VOID NAS_MML_SetBgSearchRegardlessMccList(VOS_UINT32 *pulMcc, VOS_UINT8 ucMccNum);

VOS_UINT8 NAS_MML_GetActingHplmnSupportFlg( VOS_VOID );
VOS_VOID NAS_MML_SetActingHplmnSupportFlg(VOS_UINT8 ucActingHPlmnSupportFlg);

NAS_MML_PLMN_ID_STRU  NAS_MML_GetImsiHomePlmn(
    VOS_UINT8                          *pucImsi
);


NAS_MML_EHPLMN_PRESENT_IND_ENUM_UINT8  NAS_MML_GetEHplmnPresentInd( VOS_VOID );

VOS_VOID  NAS_MML_SetPsRegContainDrx(
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8 enPsRegContainDrx
);

NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8 NAS_MML_GetPsRegContainDrx(VOS_VOID);

VOS_VOID  NAS_MML_SetNonDrxTimer(VOS_UINT8  ucPsNonDrxTimerLength);

VOS_VOID NAS_MML_SetSplitPgCycleCode(VOS_UINT8  ucSplitPgCycleCode);

VOS_UINT8 NAS_MML_GetNonDrxTimer(VOS_VOID);

VOS_VOID  NAS_MML_SetUeUtranPsDrxLen(VOS_UINT8  ucWPsDrxLength);

VOS_UINT8 NAS_MML_GetUeUtranPsDrxLen(VOS_VOID);

VOS_VOID  NAS_MML_SetUeEutranPsDrxLen(VOS_UINT8  ucLPsDrxLength);

VOS_UINT8 NAS_MML_GetUeEutranPsDrxLen(VOS_VOID);

VOS_VOID  NAS_MML_SetWSysInfoDrxLen(VOS_UINT8  ucWSysInfoDrxLength);

VOS_UINT8 NAS_MML_GetWSysInfoDrxLen(VOS_VOID);

VOS_VOID  NAS_MML_SetLSysInfoDrxLen(VOS_UINT8  ucLmmSysInfoDrxLength);

VOS_UINT8 NAS_MML_GetLSysInfoDrxLen(VOS_VOID);

VOS_UINT8 NAS_MML_GetSplitPgCycleCode(VOS_VOID);

VOS_UINT8 NAS_MML_GetSplitOnCcch(VOS_VOID);

VOS_VOID NAS_MML_SetSplitOnCcch(VOS_UINT8 ucSplitOnCcch);

VOS_UINT8 NAS_MML_GetPlmnExactlyComparaFlg(VOS_VOID);

VOS_VOID  NAS_MML_SetPlmnExactlyComparaFlg(VOS_UINT8  ucPlmnExactlyComparaFlag);

VOS_VOID  NAS_MML_SetHplmnRegisterCtrlFlg(VOS_UINT8  ucHplmnRegisterFlg);
VOS_UINT8 NAS_MML_GetHplmnRegisterCtrlFlg(VOS_VOID);

VOS_VOID  NAS_MML_SetH3gCtrlFlg(VOS_UINT8  ucH3gFlg);
VOS_UINT8 NAS_MML_GetH3gCtrlFlg(VOS_VOID);

VOS_VOID  NAS_MML_SetUsimMncLen(VOS_UINT8  ucUsimMncLength);

VOS_UINT8 NAS_MML_GetUsimMncLen(VOS_VOID);

VOS_UINT8 NAS_MML_GetCsServiceBufferStatusFlg(VOS_VOID);


NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU* NAS_MML_GetUserCfgExtEhplmnInfo( VOS_VOID );

VOS_VOID  NAS_MML_SetSupportCsServiceFLg(VOS_UINT8  ucCsServiceFlg);
VOS_UINT8  NAS_MML_GetSupportCsServiceFLg(VOS_VOID);

VOS_VOID NAS_MML_SetSvlteSupportFlag(
    VOS_UINT8                           ucSvlteSupportFlag
);

VOS_UINT8 NAS_MML_GetSvlteSupportFlag(VOS_VOID);

VOS_VOID NAS_MML_SetPsTransferOffAreaModeFlag(
    VOS_UINT8                           ucPsTransferOffAreaMode
);

VOS_UINT8 NAS_MML_GetPsTransferOffAreaModeFlag(VOS_VOID);



VOS_VOID NAS_MML_SetCsfbEmgCallEnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
);

VOS_UINT32 NAS_MML_GetCsfbEmgCallEnableLteTimerLen(VOS_VOID);

VOS_VOID NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
);
VOS_UINT32 NAS_MML_GetCsPsMode13GPPEnableLteTimerLen(VOS_VOID);



VOS_UINT8 NAS_MML_GetIsrSupportFlg(VOS_VOID);

VOS_VOID NAS_MML_SetIsrSupportFlg(
    VOS_UINT8                           ucIsrSupport
);

OM_RING_ID NAS_MML_GetErrLogRingBufAddr(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer);
VOS_UINT8 NAS_MML_GetFtmCtrlFlag(VOS_VOID);
VOS_VOID NAS_MML_SetFtmCtrlFlag(VOS_UINT8 ucFlag);
VOS_UINT8 NAS_MML_GetErrlogCtrlFlag(VOS_VOID);
VOS_VOID NAS_MML_SetErrlogCtrlFlag(VOS_UINT8 ucFlag);
VOS_UINT16 NAS_MML_GetErrlogAlmLevel(VOS_VOID);
VOS_VOID NAS_MML_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel);
VOS_VOID NAS_MML_InitErrLogMntnInfo(
    NAS_MML_ERRLOG_MNTN_INFO_STRU          *pstErrLogInfo
);
#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32 NAS_MML_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
VOS_UINT32 NAS_MML_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
VOS_UINT32 NAS_MML_GetErrLogRingBufUseBytes(VOS_VOID);
VOS_VOID NAS_MML_CleanErrLogRingBuf(VOS_VOID);
#endif
VOS_UINT32 NAS_MML_RegFailCauseNeedRecord(NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enRegFailCause);

VOS_VOID NAS_MML_SetCsfbMtCurrState(
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState
);
NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32 NAS_MML_GetCsfbMtCurrState(VOS_VOID);
NAS_MML_ERRLOG_CSFB_MT_INFO_STRU* NAS_MML_GetCsfbMtInfoAddr(VOS_VOID);
VOS_VOID NAS_MML_AddCsfbMtRecordPositionNum(VOS_VOID);
VOS_UINT32 NAS_MML_GetCsfbMtRecordPositionNum(VOS_VOID);
VOS_VOID NAS_MML_ClrCsfbMtRecordPositionNum(VOS_VOID);
VOS_VOID NAS_MML_AddCsfbMtRecordStateNum(VOS_VOID);
VOS_UINT32 NAS_MML_GetCsfbMtRecordStateNum(VOS_VOID);
VOS_VOID NAS_MML_ClrCsfbMtRecordStateNum(VOS_VOID);
VOS_VOID NAS_MML_InitCsfbMtInfo(VOS_VOID);
NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU* NAS_MML_GetErrLogNwSearchInfoAddr(VOS_VOID);
VOS_UINT8 NAS_MML_GetErrLogNwSrchCfgActiveFlag(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogNwSrchCfgActiveFlag(VOS_UINT8 ucFlag);
VOS_UINT32 NAS_MML_GetErrLogNwSrchCfgRecordNum(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogNwSrchCfgRecordNum(VOS_UINT32 ucNum);
VOS_VOID NAS_MML_AddErrLogNwSearchCount(VOS_VOID);
VOS_VOID NAS_MML_ClrErrLogNwSearchCount(VOS_VOID);
VOS_UINT32 NAS_MML_GetErrLogOosEvent(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogOosEvent(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32   enOosEvent
);
VOS_UINT32 NAS_MML_GetErrLogCsOosCause(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogCsOosCause(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause
);
VOS_UINT32 NAS_MML_GetErrLogPsOosCause(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogPsOosCause(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause
);
VOS_VOID NAS_MML_InitErrLogNwSearchInfo(VOS_VOID);
VOS_UINT32 NAS_MML_GetErrlogOverflowCnt(VOS_VOID);
VOS_VOID NAS_MML_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt);

/* Added by zwx247453 for CHR optimize, 2015-03-13 begin */
VOS_VOID NAS_MML_SetErrLogGMsIdType(
    VOS_UINT8                               ucGMsIdType
);
VOS_UINT8 NAS_MML_GetErrLogGMsIdType(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogGPagingType(
    VOS_UINT8                               ucGPagingType
);
VOS_UINT8 NAS_MML_GetErrLogGPagingType(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogWCnDomainId(
    VOS_UINT32                              ulWCnDomainId
);
VOS_UINT32 NAS_MML_GetErrLogWCnDomainId(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogWPagingType(
    VOS_UINT32                              ulWPagingType
);
VOS_UINT32 NAS_MML_GetErrLogWPagingType(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogWPagingCause(
    VOS_UINT32                              ulWPagingCause
);
VOS_UINT32 NAS_MML_GetErrLogWPagingCause(VOS_VOID);
VOS_VOID NAS_MML_SetErrLogWPagingUeId(
    VOS_UINT32                              ulWPagingUeId
);
VOS_UINT32 NAS_MML_GetErrLogWPagingUeId(VOS_VOID);
VOS_VOID NAS_MML_InitErrLogPagingInfo(VOS_VOID);
/* Added by zwx247453 for CHR optimize, 2015-03-13 end */

VOS_UINT8 NAS_MML_GetDelayedCsfbLauFlg(VOS_VOID);

VOS_VOID NAS_MML_SetDelayedCsfbLauFlg(
    VOS_UINT8                           ucDelayedCsfbLauFlg
);

VOS_UINT8 NAS_MML_GetIsRauNeedFollowOnCsfbMtFlg(VOS_VOID);

VOS_VOID NAS_MML_SetIsRauNeedFollowOnCsfbMtFlg(
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMtFlg
);



VOS_UINT8 NAS_MML_GetIsRauNeedFollowOnCsfbMoFlg(VOS_VOID);

VOS_VOID NAS_MML_SetIsRauNeedFollowOnCsfbMoFlg(
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMoFlg
);

VOS_VOID NAS_MML_SetIsDelFddBandSwitchOnFlg(
    VOS_UINT8                           ucIsDelFddBandSwitchOnFlg
);

VOS_UINT8 NAS_MML_GetIsDelFddBandSwitchOnFlg(VOS_VOID);


VOS_VOID NAS_MML_SetPsLocalDetachFlag(VOS_UINT8 ucPsLocalDetachFlag );
VOS_UINT8 NAS_MML_GetPsLocalDetachFlag( VOS_VOID );


VOS_UINT8 NAS_MML_GetSupportAccBarPlmnSearchFlg( VOS_VOID );
NAS_MML_USER_CFG_OPLMN_INFO_STRU* NAS_MML_GetUserCfgOPlmnInfo( VOS_VOID );
VOS_VOID NAS_MML_SetSupportAccBarPlmnSearchFlg(
    VOS_UINT8                           ucAccBarPlmnSearchFlg
);
VOS_VOID NAS_MML_SetUserCfgOPlmnInfo(
    NAS_MML_USER_CFG_OPLMN_INFO_STRU       *pstUserCfgOPlmnInfo
);

VOS_VOID  NAS_MML_InitUserCfgOPlmnInfo(
    NAS_MML_USER_CFG_OPLMN_INFO_STRU       *pstUserCfgOPlmnInfo
);



VOS_VOID  NAS_MML_SetRrcLteNcellExistFlg(
    VOS_UINT8                           ucLteNcellExist
);

VOS_UINT8  NAS_MML_GetRrcLteNcellExistFlg( VOS_VOID );

VOS_UINT8  NAS_MML_GetRrcUtranNcellExistFlg( VOS_VOID );

VOS_VOID  NAS_MML_SetRrcUtranNcellExistFlg(
    VOS_UINT8                           ucUtranNcellExist
);

VOS_VOID  NAS_MML_SetDsdsRfShareFlg(
    VOS_UINT16                          usDsdsRfShareFlg
);
VOS_UINT16 NAS_MML_GetDsdsRfShareFlg(VOS_VOID);
VOS_VOID NAS_MML_SetGsmBandCapability(
    VOS_UINT32                          ulBand
);

VOS_UINT32 NAS_MML_GetGsmBandCapability(VOS_VOID);


VOS_VOID    NAS_MML_SetImsNormalRegStatus(
    NAS_MML_IMS_NORMAL_REG_STATUS_ENUM_UINT8    enRegStatus
);

NAS_MML_IMS_NORMAL_REG_STATUS_ENUM_UINT8   NAS_MML_GetImsNormalRegStatus(VOS_VOID);

VOS_VOID    NAS_MML_SetImsVoiceAvailFlg(
    VOS_UINT8       ucAvail
);

VOS_UINT8   NAS_MML_GetImsVoiceAvailFlg(VOS_VOID);

VOS_VOID    NAS_MML_SetImsCallFlg(
    VOS_UINT8                                               ucImsCallFlg
);
VOS_UINT8   NAS_MML_GetImsCallFlg(VOS_VOID);

VOS_VOID NAS_MML_SetEmcPdpStatusFlg(
    VOS_UINT8                           ucEmcPdpStatusFlg
);
VOS_UINT8 NAS_MML_GetEmcPdpStatusFlg( VOS_VOID );



VOS_UINT8 NAS_MML_GetImsVoiceInterSysLauEnableFlg( VOS_VOID );
VOS_VOID NAS_MML_SetImsVoiceInterSysLauEnableFlg( VOS_UINT8 );

VOS_UINT8 NAS_MML_GetImsVoiceMMEnableFlg( VOS_VOID );
VOS_VOID NAS_MML_SetImsVoiceMMEnableFlg( VOS_UINT8 );

NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 NAS_MML_GetGUNwImsVoiceSupportFlg(VOS_VOID);
VOS_VOID NAS_MML_SetGUNwImsVoiceSupportFlg(
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enSupport
);

NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 NAS_MML_GetLteNwImsVoiceSupportFlg(VOS_VOID);
VOS_VOID NAS_MML_SetLteNwImsVoiceSupportFlg(
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enSupport
);

VOS_UINT8 NAS_MML_GetPsSupportFLg(VOS_VOID);

VOS_UINT8 NAS_MML_GetLcEnableFlg(VOS_VOID);

VOS_VOID NAS_MML_SetLcEnableFlg(VOS_UINT8 ucLcEnable);
NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU* NAS_MML_GetHighPrioRatHplmnTimerCfg( VOS_VOID );

VOS_VOID  NAS_MML_InitHighPrioRatHplmnTimerCfgInfo(
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighHplmnTimerCfg
);

VOS_UINT8  NAS_MML_GetHighPrioRatHplmnTimerActiveFlg( VOS_VOID );


VOS_UINT8 NAS_MML_GetHighPrioRatHplmnTimerTdThreshold( VOS_VOID );

VOS_UINT8 NAS_MML_Get3GPP2UplmnNotPrefFlg( VOS_VOID );
VOS_VOID NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_UINT8 uc3GPPUplmnNotPrefFlg);

NAS_MML_DSDS_END_SESSION_DELAY_STRU* NAS_MML_GetDsdsSessionEndDelay(VOS_VOID);
VOS_VOID NAS_MML_SetDsdsEndSessionDelay(
    NAS_MML_DSDS_END_SESSION_DELAY_STRU      *pstDsdsEndSesssionDelay
);
VOS_VOID NAS_MML_InitDsdsSessionEndDelay(
    NAS_MML_DSDS_END_SESSION_DELAY_STRU      *pstDsdsEndSesssionDelay
);

VOS_UINT8 NAS_MML_GetSupportSrvccFlg(VOS_VOID);
VOS_VOID NAS_MML_SetSupportSrvccFlg(
    VOS_UINT8 ucSupportSrvccFlg
);

NAS_MML_CALL_UMTS_CODEC_TYPE_STRU *NAS_MML_CALL_GetCallUmtsCodecType(VOS_VOID);
VOS_VOID NAS_MML_CALL_SetCallUmtsCodecType(
    NAS_MML_CALL_UMTS_CODEC_TYPE_STRU        *pstCodecType
);
VOS_VOID NAS_MML_CALL_InitCallUmtsCodecType(
    NAS_MML_CALL_UMTS_CODEC_TYPE_STRU        *pstCodecType
);
NAS_MML_CALL_GSM_CODEC_TYPE_STRU *NAS_MML_CALL_GetCallGsmCodeType(VOS_VOID);
VOS_VOID NAS_MML_CALL_SetCallGsmCodecType(
    NAS_MML_CALL_GSM_CODEC_TYPE_STRU *pstCodecType
);
VOS_VOID NAS_MML_CALL_InitCallGsmCodecType(
    NAS_MML_CALL_GSM_CODEC_TYPE_STRU *pstCodecType
);

VOS_VOID NAS_MML_InitOldCampLai(
    NAS_MML_LAI_STRU                   *pstLaiInfo
);

VOS_VOID  NAS_MML_InitCallModeInfoCtx(
    NAS_MML_CALL_MODE_ENUM_UINT8        *penCallMode
);


VOS_UINT8 NAS_MML_GetPdpConnStateInfo( VOS_VOID );
VOS_UINT8 NAS_MML_GetSyscfgTriHighRatSrchFlg(VOS_VOID);

VOS_VOID NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_UINT8 ucSyscfgTriHighRatSrchFlg);

NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU *NAS_MML_GetSupportDamPlmnList(VOS_VOID);
VOS_VOID  NAS_MML_InitSupportDamPlmnInfo(
    NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU *pstDamPlmnInfo
);

VOS_VOID NAS_MML_SetT3402Len(VOS_UINT32 ulT3402Len);
VOS_UINT32 NAS_MML_GetT3402Len(VOS_VOID);
VOS_VOID NAS_MML_SetEnableLteTrigPlmnSearchFlag(
    VOS_UINT8                           ucEnableLteTrigPlmnSearchFlag
);
NAS_MML_DAM_IMSI_PLMN_LIST_STRU *NAS_MML_GetDamImsiPlmnList(VOS_VOID);
NAS_MML_DAM_PLMN_INFO_CONFIG_STRU *NAS_MML_GetDamPlmnInfoCfg(VOS_VOID);
VOS_UINT8 NAS_MML_GetEnableLteTrigPlmnSearchFlag(VOS_VOID);
VOS_VOID  NAS_MML_InitDamPlmnInfoCfg(
    NAS_MML_DAM_PLMN_INFO_CONFIG_STRU  *pstDamCfgPlmnInfo
);
VOS_VOID NAS_MML_SetAddDamPlmnInDisablePlmnWithRatListFlag(
    VOS_UINT8                           ucAddDamPlmnInDisablePlmnWithRatListFlag
);

VOS_UINT8 NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag(VOS_VOID);


VOS_VOID NAS_MML_AddLogEventState(VOS_UINT16 usSendPid, VOS_UINT16 usReceivePid, VOS_UINT16 usMsgName);

VOS_VOID NAS_MML_UpdateExitTime(VOS_VOID);

VOS_VOID NAS_MML_InitLogEventState(NAS_MML_LOG_EVENT_STATE_STRU *pstLogEventState);

NAS_MML_T3212_TIMER_INFO_CONFIG_STRU* NAS_MML_GetT3212TimerInfo(VOS_VOID);
VOS_VOID  NAS_MML_InitT3212TimerCfgInfo(
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212CfgInfo
);
VOS_VOID  NAS_MML_InitGetGeoPrioRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstGetGeoRatList
);
VOS_VOID NAS_MML_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMesgHeader
);

extern VOS_VOID  NAS_MML_InitChangeNWCauseInfo(NAS_MML_CHANGE_NW_CAUSE_INFO_STRU *pstChangeNWCauseInfo);
extern VOS_VOID NAS_MML_SetChangeNWCauseCfg(const NAS_MML_CHANGE_NW_CAUSE_CFG_STRU *pstChangeNWCauseCfg);
extern NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU* NAS_MML_GetRejCauseChangedCounter(VOS_VOID);
extern NAS_MML_CHANGE_NW_CAUSE_CFG_STRU* NAS_MML_GetChangeNWCauseCfg(VOS_VOID);
extern VOS_UINT8 NAS_MML_GetChangeNWCauseCfgByRejType(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU   **pstAdaptCause
);
extern VOS_UINT8 NAS_MML_GetHplmnChangeNWCause(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                           ucCause
);
extern VOS_UINT8 NAS_MML_GetVplmnChangeNWCause(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                           ucCause
);
extern VOS_UINT8 NAS_MML_GetHplmnPsRejChangeTo17Flg(VOS_VOID);
extern VOS_UINT8 NAS_MML_GetHplmnCsRejChangeTo17Flg(VOS_VOID);
extern VOS_UINT8 NAS_MML_GetVplmnPsRejChangeTo17Flg(VOS_VOID);
extern VOS_UINT8 NAS_MML_GetVplmnCsRejChangeTo17Flg(VOS_VOID);
extern VOS_VOID NAS_MML_IncHplmnPsRejCauseChangedCounter(VOS_VOID);
extern VOS_VOID NAS_MML_IncHplmnCsRejCauseChangedCounter(VOS_VOID);
extern VOS_VOID NAS_MML_IncVplmnPsRejCauseChangedCounter(VOS_VOID);
extern VOS_VOID NAS_MML_IncVplmnCsRejCauseChangedCounter(VOS_VOID);
extern VOS_VOID NAS_MML_ResetHplmnPsRejCauseChangedCounter(VOS_VOID);
extern VOS_VOID NAS_MML_ResetHplmnCsRejCauseChangedCounter(VOS_VOID);
extern VOS_VOID NAS_MML_ResetVplmnPsRejCauseChangedCounter(VOS_VOID);
extern VOS_VOID NAS_MML_ResetVplmnCsRejCauseChangedCounter(VOS_VOID);
extern VOS_VOID NAS_MML_SetRelPsSigConFlg(VOS_UINT8 ucRelPsSigConFlg);
extern VOS_UINT8 NAS_MML_GetRelPsSigConFlg(VOS_VOID);
extern VOS_VOID NAS_MML_SetRelPsSigConCfg_T3340TimerLen(VOS_UINT32 ulTimerLen);
extern VOS_UINT32 NAS_MML_GetRelPsSigConCfg_T3340TimerLen(VOS_VOID);

extern VOS_VOID NAS_MML_SetLteRejCause14Flg(VOS_UINT8 ucLteRejCause14Flg);
extern VOS_UINT8 NAS_MML_GetLteRejCause14Flg(VOS_VOID);
extern VOS_VOID NAS_MML_SetLteRejCause14EnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
);
extern VOS_UINT32 NAS_MML_GetLteRejCause14EnableLteTimerLen(VOS_VOID);

VOS_VOID NAS_MML_SetPdpExistNotStartT3340Flag(VOS_UINT8 ucPdpExistNotStartT3340Flag);
VOS_UINT8 NAS_MML_GetPdpExistNotStartT3340Flag(VOS_VOID);


NAS_MML_MO_CALL_STATUS_ENUM_UINT8 NAS_MML_GetMoCallStatus( VOS_VOID );
VOS_VOID NAS_MML_SetMoCallStatus(
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus
);
NAS_MML_MO_SS_STATUS_ENUM_UINT8 NAS_MML_GetMoSsStatus( VOS_VOID );
VOS_VOID NAS_MML_SetMoSsStatus(
    NAS_MML_MO_SS_STATUS_ENUM_UINT8      enSsStatus
);

VOS_UINT8 NAS_MML_GetCsfbMoCallSetupFlg(VOS_VOID);


VOS_VOID  NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(
    VOS_UINT8 ucPsRegFailMaxTimesTrigLauOnceFlg
);
VOS_UINT8 NAS_MML_GetPsRegFailMaxTimesTrigLauOnceFlg(VOS_VOID);

VOS_VOID  NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(
    VOS_UINT8 ucKeepSrchHplmnEvenRejByCause13Flg
);
VOS_UINT8 NAS_MML_GetKeepSrchHplmnEvenRejByCause13Flg(VOS_VOID);

VOS_VOID  NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(
    VOS_UINT8 ucEpsRejByCause14InVplmnAllowPsRegFlg
);
VOS_UINT8 NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_VOID);
NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU* NAS_MML_GetCarryEplmnWhenSrchRplmnCfg( VOS_VOID );
NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU* NAS_MML_GetLauRejTrigPlmnSearchCfg(VOS_VOID);

VOS_VOID  NAS_MML_InitCarryEplmnWhenSrchRplmnCfg(
    NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU  *pstCarryEplmnWhenSrchRplmnCfg
);
VOS_VOID NAS_MML_InitLauRejNoRetryWhenCmSrvExistCfg(
    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU *pstLauRejNoRetryWhenCmSrvExist
);
VOS_VOID NAS_MML_InitLauRejTrigPlmnSearchCfg(
    NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                  *pstLauRejTrigPlmnSrchCfg
);

VOS_VOID  NAS_MML_SetDsdsMultiModemModeFlg(
    VOS_UINT8                           ucDsdsMultiModemModeFlg
);
VOS_UINT8 NAS_MML_GetDsdsMultiModemModeFlg(VOS_VOID);
VOS_VOID  NAS_MML_SetLowPrioAnycellSearchLteFlg(
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg    
);
VOS_UINT8  NAS_MML_GetLowPrioAnycellSearchLteFlg(VOS_VOID);
VOS_VOID  NAS_MML_SetCsmoSupportedFlg(
    VOS_UINT8                           ucCsmoSupportedFlg
);

VOS_UINT8 NAS_MML_GetCsmoSupportedFlg(VOS_VOID);

VOS_VOID  NAS_MML_SetHplmnInEplmnDisplayHomeFlg(
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg
);

VOS_UINT8 NAS_MML_GetHplmnInEplmnDisplayHomeFlg(VOS_VOID);
VOS_VOID  NAS_MML_SetProtectMtCsfbPagingProcedureLen(
    VOS_UINT16                          usMtCsfbPagingProcedureLen
);
VOS_UINT16 NAS_MML_GetProtectMtCsfbPagingProcedureLen(VOS_VOID);

VOS_VOID NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(
    VOS_UINT8                           ucDeleteRplmnWhenEplmnInvalidFlg
);
VOS_UINT8 NAS_MML_GetDeleteRplmnWhenEplmnInvalidFlg(VOS_VOID);


NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MML_GetGeoPrioRatList(VOS_VOID);

VOS_VOID  NAS_MML_SetOriginalRejectCause(
    VOS_UINT8                           ucOriginalUeCause
);
/* Modified by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin */
VOS_UINT8  NAS_MML_GetOriginalRejectCause(
    VOS_UINT32 UlAdaptCause
);
/* Modified by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, end */
VOS_VOID NAS_MML_InitOriginalRejectCause(
    NAS_MML_ORIGNAL_REJECT_CAUSE_STRU   *pstOriginalRejectCause
);

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */

VOS_UINT8 NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchFlag(VOS_VOID);
VOS_UINT32 NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchDelayLen(VOS_VOID);
VOS_VOID  NAS_MML_InitHighPrioPlmnRefreshTriggerBGSearchCfgInfo(
    NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU             *pstHighPrioPlmnRefreshTriggerBGSearchCfg
);
VOS_VOID NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchFlag(VOS_UINT8 ucTriggerBGSearchFlag);
VOS_VOID NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchDelayLen(VOS_UINT32 ulSearchDelayLen);

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_MML_InitLteOos2GPrefPlmnSelCfg(NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU *pstLteOos2GPrefPlmnSelCfg);
extern NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU* NAS_MML_GetLteOos2GPrefPlmnSelCfg(VOS_VOID);
#endif

VOS_UINT32 NAS_MML_GetRatIndexInPrioRatList(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8         ucNetRat,
    NAS_MSCC_PIF_RAT_PRIO_STRU                  *pstPrioRatList
);

NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU* NAS_MML_GetErrLogFftSrchInfoAddr(VOS_VOID);
VOS_VOID NAS_MML_InitErrLogFftSrchInfo(VOS_VOID);
VOS_VOID NAS_MML_SetFftSrchStartTime(VOS_UINT32 ulFftStartSlice);
VOS_VOID NAS_MML_SetFftSrchBandScanStartTime(VOS_UINT32 ulBandScanStartSlice);
VOS_VOID NAS_MML_SaveFftSrchBandScanResultAndFinishTime(
    CSS_MULTI_BAND_SCAN_CNF_STRU            *pstBandScanCnf
);
VOS_VOID NAS_MML_SetFftSrchPlmnSrchRatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    enRatType
);
VOS_VOID NAS_MML_SaveFftSrchResultAndFinishTime(
    VOS_UINT8                               ucResult
);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasMmlCtx.h */
