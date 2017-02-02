

#ifndef __NASLMMPUBLIC_H__
#define __NASLMMPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmCore.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_LMM_RIGHT_SHIFT_HALF_BYTE       4       /* ���ư���ֽڳ��� */

#define NAS_LMM_HEX_DIGIT_F                 0x0F    /* 16����F */

#define NAS_LMM_DEC_DIGIT_0                 0       /* 10����0 */
#define NAS_LMM_DEC_DIGIT_1                 1       /* 10����1 */
#define NAS_LMM_DEC_DIGIT_2                 2       /* 10����2 */
#define NAS_LMM_DEC_DIGIT_3                 3       /* 10����3 */
#define NAS_LMM_DEC_DIGIT_4                 4       /* 10����4 */
#define NAS_LMM_DEC_DIGIT_5                 5       /* 10����5 */
#define NAS_LMM_DEC_DIGIT_6                 6       /* 10����6 */
#define NAS_LMM_DEC_DIGIT_7                 7       /* 10����7 */
#define NAS_LMM_DEC_DIGIT_8                 8       /* 10����8 */
#define NAS_LMM_DEC_DIGIT_9                 9       /* 10����9 */

#define NAS_EMM_SECOND_TRANSFER_MILLISECOND    1000
#define NAS_EMM_MINUTE_TRANSFER_MILLISECOND    60000

#define NAS_LMM_LOW_HALF_BYTE_MASK          0xF0    /* �Ͱ��ֽ����� */
#define NAS_LMM_HIGH_HALF_BYTE_MASK         0x0F    /* �߰��ֽ����� */

#define NAS_LMM_MIN(n1,n2)                  (((n1)>(n2))?(n2):(n1))


#define NAS_EMMC_PLMNID_INVALID              VOS_TRUE
#define NAS_EMMC_PLMNID_VALID                VOS_FALSE
#define NAS_EMM_BUFFER_MSG_COUNT            16          /*����QUE�Ĵ�Сȷ��*/

#define NAS_LMM_HEX_DIGIT_FF                 0xff

#define NAS_LMM_NVIM_ALG_VALID_IE            0x03

#define NAS_LMM_MEM_CMP_EQUAL                0
#define NAS_LMM_NULL                         0


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*******************************************************************************
 ö����    : NAS_LMM_ERROR_CODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : MM����ԭ��ֵ����.ÿ��MM����ԭ��ֵ��32bit, ����bit31-16��ʾ����ԭ
             �����, bit15-0��ʾ����ԭ��С��.

*******************************************************************************/
enum NAS_LMM_ERROR_CODE_ENUM
{
    NAS_LMM_SUCC                         = 0x00000000,
    NAS_LMM_FAIL                                     ,

    /*======== FSMר�ã�״̬�����������Ϣ ========*/
    NAS_LMM_MSG_DISCARD                              ,       /* ��������Ϣ��������Ϣ�����õ�ǰ״̬����Ҳ�����棬 */
    NAS_LMM_MSG_HANDLED                              ,       /* ����Ϣ�ѱ���ǰ״̬���������ǻ��� */

    NAS_LMM_STORE_HIGH_PRIO_MSG                      ,
    NAS_LMM_STORE_MID_PRIO_MSG                       ,       /*��ʱ����*/
    NAS_LMM_STORE_LOW_PRIO_MSG                       ,       /*��ʱ����*/

    NAS_EMMC_STORE_HIGH_PRIO_MSG                      ,
    NAS_EMMC_STORE_MID_PRIO_MSG                       ,       /*��ʱ����*/
    NAS_EMMC_STORE_LOW_PRIO_MSG                       ,       /*��ʱ����*/


    NAS_LMM_NOT_TRAVEL_BUFFER_MSG                    ,       /* ����������� */
    NAS_LMM_TRAVEL_BUFFER_MSG                        ,       /* ��Ҫ��������BUF��Ļ�����Ϣ */

    NAS_LMM_ERR_CODE_PARA_INVALID                    ,       /*��Ϣ������Ч*/
    NAS_LMM_ERR_CODE_PTR_NULL                        ,       /* ��ָ�� */
    NAS_LMM_ERR_CODE_ARRAY_OVERFLOW                  ,       /* ����Խ�� */

    NAS_LMM_STATE_IS_STABLE                          ,       /*  ״̬��������̬ */
    NAS_LMM_STATE_IS_UNSTABLE                        ,       /*  ״̬�����ڷ���̬ */
    NAS_LMM_STATE_IS_TRANSIENT                       ,       /*  ״̬�����ڽ���������*/

    /*================ PUBM-TIMER =================*/
    NAS_LMM_ERR_CODE_GET_STATE_TIMER_CTRL_ADDR_FAIL  ,       /* ��ȡ״̬��ʱ�����ƿ��ַʧ�� */
    NAS_LMM_ERR_CODE_GET_PTL_TIMER_CTRL_ADDR_FAIL    ,       /* ��ȡЭ�鶨ʱ�����ƿ��ַʧ�� */
    NAS_LMM_ERR_CODE_PTL_TIMER_EXCEED_MAX_BOUND      ,       /* Э�鶨ʱ���������ʱ������   */
    NAS_LMM_ERR_CODE_RESUME_NOT_SUSPEND_STATE_TIMER  ,       /* �ָ�û�б������״̬��ʱ��   */

    /*================ ATTACH ģ�� ================*/
    /*================ DETACH ģ�� ================*/
    /*================ TAU ģ�� ===================*/
    /*================ SERVICE ģ�� ===============*/
    /*================ PUB ģ�� ===================*/
    NAS_LMM_MSG_CAN_BE_HANDLED_BY_PRE_STATE          ,       /* NAS_EMM_JudgeFirstBufMsgCanBeProc��ʹ��,
                                                               ��ǰ״̬���Դ����յ�����Ϣ */

    NAS_LMM_ERR_CODE_HARD_USIM                       ,

    NAS_LMM_ERR_CODE_FAIL                            ,       /* ������Ĵ��� */

    NAS_LMM_ERR_CODE_BUTT
};
typedef VOS_UINT32 NAS_LMM_ERROR_CODE_ENUM_UINT32;
typedef NAS_LMM_ERROR_CODE_ENUM_UINT32   NAS_EMM_ERROR_CODE_ENUM_UINT32;
typedef NAS_LMM_ERROR_CODE_ENUM_UINT32   NAS_EMMC_ERROR_CODE_ENUM_UINT32;


enum NAS_LMM_MATCH_RESULT_ENUM
{
    NAS_LMM_MATCH_FAIL                      = 0,
    NAS_LMM_MATCH_SUCCESS                   = 1,
    NAS_LMM_MATCH_PTR_NULL                  = 2,
    NAS_LMM_MATCH_RESULT_BUTT
};
typedef VOS_UINT32  NAS_LMM_MATCH_RESULT_ENUM_UINT32;


enum NAS_LMM_IE_FORMAT_ENUM
{
    NAS_LMM_IE_FORMAT_V                 = 0x00,
    NAS_LMM_IE_FORMAT_LV                = 0x01,
    NAS_LMM_IE_FORMAT_TLV               = 0x02,
    NAS_LMM_IE_FORMAT_LV_E              = 0x03,

    NAS_LMM_IE_FORMAT_BUTT
};
typedef VOS_UINT8 NAS_LMM_IE_FORMAT_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_LMM_AddPlmnInPlmnList
       (
           const   NAS_MM_PLMN_ID_STRU         *pstPlmnId,
           NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
           VOS_UINT32                          ulListNumMax
       );
extern VOS_VOID    NAS_LMM_AddTaInTaList
       (
           const   NAS_MM_TA_STRU              *pstTa,
           NAS_MM_TA_LIST_STRU                 *pstTaList,
           VOS_UINT32                          ulListNumMax
       );
extern VOS_VOID    NAS_LMM_ClearPlmnList(NAS_MM_PLMN_LIST_STRU  *pstPlmnList);
extern VOS_VOID  NAS_LMM_ClearTaList(NAS_MM_FORB_TA_LIST_STRU  *pstTaList);
extern VOS_VOID    NAS_LMM_DeletePlmnFromPlmnList
       (
           const   NAS_MM_PLMN_ID_STRU         *pstPlmnId,
           NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
           VOS_UINT32                          ulListNumMax
       );
extern VOS_VOID    NAS_LMM_DeleteTaFromTaList
       (
           const   NAS_MM_TA_STRU              *pstTa,
           NAS_MM_TA_LIST_STRU                 *pstTaList,
           VOS_UINT32                          ulListNumMax
       );
extern VOS_VOID    NAS_LMM_GetMccFromPlmn
       (
           const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
           VOS_UINT8                           *pucMcc1,
           VOS_UINT8                           *pucMcc2,
           VOS_UINT8                           *pucMcc3
       );
extern VOS_VOID    NAS_LMM_GetMccMncFromPlmn
       (
           const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
           VOS_UINT32                          *pulMCC,
           VOS_UINT32                          *pulMNC
       );
extern VOS_VOID    NAS_LMM_GetMncFromPlmn
       (
           const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
           VOS_UINT8                           *pucMnc1,
           VOS_UINT8                           *pucMnc2,
           VOS_UINT8                           *pucMnc3
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_HplmnMatch
       (
           const   NAS_MM_PLMN_ID_STRU         *pstHplmn,
           const   NAS_MM_PLMN_ID_STRU         *pstBcchPlmn
       );
extern  VOS_VOID    NAS_LMM_PlmnCpy
        (
            NAS_MM_PLMN_ID_STRU                *pstDestPlmn,
            const   NAS_MM_PLMN_ID_STRU        *pstOrgPlmn
        );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnIDMatchPlmnList
       (
           const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
           const NAS_MM_PLMN_LIST_STRU         *pstPlmnList
       );
extern VOS_UINT32 NAS_LMM_PlmnIsUndef(const NAS_MM_PLMN_ID_STRU *pstPlmnId);

extern VOS_UINT32 NAS_LMM_TacIsInvalid(const NAS_MM_TAC_STRU *pstTac);

extern VOS_UINT32 NAS_LMM_PlmnIsUnexist(const NAS_MM_PLMN_ID_STRU *pstPlmnId);
extern VOS_VOID    NAS_LMM_PlmnListCpy
       (
           NAS_MM_PLMN_LIST_STRU               *pstDestPlmnList,
           const   NAS_MM_PLMN_LIST_STRU       *pstOrgPlmnList
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnMatch
       (
           const NAS_MM_PLMN_ID_STRU           *pstLocalPlmn,
           const NAS_MM_PLMN_ID_STRU           *pstBcchPlmn
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TacMatch
       (
           const   NAS_MM_TAC_STRU             *pstTac1,
           const   NAS_MM_TAC_STRU             *pstTac2
       );
extern VOS_VOID NAS_LMM_TaCpy
       (
           NAS_MM_TA_STRU                      *pstDestTa,
           const   NAS_MM_TA_STRU              *pstOrgTa
       );
extern NAS_LMM_ERROR_CODE_ENUM_UINT32 NAS_LMM_TaIncrease
       (
           NAS_MM_TAC_STRU                     *pstTac
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatch
       (
           const   NAS_MM_TA_STRU              *pstTa1,
           const   NAS_MM_TA_STRU              *pstTa2
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchTaList
       (
           const   NAS_MM_TA_STRU              *pstTa,
           const   NAS_MM_TA_LIST_STRU         *pstTaList
       );
extern VOS_VOID    NAS_LMM_UndefPlmn
       (
           NAS_MM_PLMN_ID_STRU                 *pstPlmnId
       );

extern VOS_VOID    NAS_LMM_UndefTac
(
    NAS_MM_TAC_STRU                 *pstTac
);
extern VOS_UINT32    NAS_LMM_TacIsUnexist
(
    const NAS_MM_TAC_STRU                 *pstTac
);
extern VOS_UINT32    NAS_LMM_CheckPlmnIsInvalid
(
    const NAS_MM_PLMN_ID_STRU                 *pstPlmnId
);
extern VOS_UINT32    NAS_LMM_CheckMccIsValid
(
    VOS_UINT8   ucMcc1,
    VOS_UINT8   ucMcc2,
    VOS_UINT8   ucMcc3
);
extern VOS_UINT32    NAS_LMM_CheckMncIsValid
(
    VOS_UINT8   ucMnc1,
    VOS_UINT8   ucMnc2,
    VOS_UINT8   ucMnc3
);

extern VOS_UINT32  NAS_LMM_CheckWhetherAnyByteIsFF( const VOS_UINT8 *pucSimRecord,
                                                           const VOS_UINT32 ulIndex,
                                                           const VOS_UINT32 ulLen);
extern VOS_UINT32  NAS_LMM_CheckWhetherAllBytesAreFF(  const VOS_UINT8 *pucSimRecord,
                                                            const VOS_UINT32 ulIndex,
                                                            const VOS_UINT32 ulLen );
extern VOS_UINT32  NAS_LMM_CheckSimRecordHeadValid( const VOS_UINT8 *pucSimRecord,
                                                            const VOS_UINT32 ulIndex,
                                                            const VOS_UINT32 ulLen );
extern VOS_VOID NAS_LMM_SetArrayAllBytesFF( VOS_UINT8 *pucArray,
                                                     const VOS_UINT32 ulLen );
extern VOS_UINT32  NAS_LMM_CheckSecuAlgValid( VOS_UINT8 ucSecuAlg);

extern VOS_UINT32  NAS_LMM_CheckModifyT3402DefaultValue( VOS_VOID);
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnIDMatchHplmnList
(
    const NAS_MM_PLMN_ID_STRU          *pstPlmnId,
    const NAS_MM_PLMN_LIST_STRU        *pstPlmnList
);
extern VOS_UINT32  NAS_LMM_GetPlmnExactlyComparaFlg( VOS_VOID );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32  NAS_LMM_ExactlyPlmnMatch
(
    const NAS_MM_PLMN_ID_STRU          *pstLocalPlmn,
    const NAS_MM_PLMN_ID_STRU          *pstBcchPlmn
);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPublic.h */
