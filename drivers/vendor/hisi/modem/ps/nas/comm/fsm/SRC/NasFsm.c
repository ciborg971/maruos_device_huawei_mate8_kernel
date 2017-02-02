
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasFsm.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2010��11��13��
  ����޸�   :
  ��������   : NAS��״̬������������
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include <stdlib.h> /* bsearch,qsort */
#include "vos.h"

#include "NasFsm.h"
#include "NasComm.h"
#include "PsCommonDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_FSM_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_FSM_StaCompare
 ��������  : NAS״̬���ȽϺ���,�ڶ�״̬ת�Ʊ���п�������ʱ�õ�
 �������  : pstSta1: �Ƚϵ�״̬1
             pstSta2: �Ƚϵ�״̬2
 �������  : ��
 ����ֵ    : 0 : ״̬1��״̬2���
             -1: ״̬1С��״̬2
              1: ״̬1����״̬2
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_INT32  NAS_FSM_StaCompare(
    const VOS_VOID                      *pSta1,
    const VOS_VOID                      *pSta2
)
{
    NAS_STA_STRU                  *pstSta1;
    NAS_STA_STRU                  *pstSta2;

    pstSta1 = (NAS_STA_STRU *)pSta1;
    pstSta2 = (NAS_STA_STRU *)pSta2;

    /*  ���״̬1С��״̬2,����-1 */
    if (pstSta1->ulState < pstSta2->ulState)
    {
        return -1;
    }

    /*  ���״̬1����״̬2,����0 */
    if (pstSta1->ulState == pstSta2->ulState)
    {
        return 0;
    }

    /*  ���״̬1����״̬2,����1 */
    return 1;
}


/*****************************************************************************
 �� �� ��  : NAS_FSM_ActCompare
 ��������  : �¼��ȽϺ������ڶ��¼��������п�������ʱ�õ�
 �������  : pstAct1 : �¼�1
             pstAct2 : �¼�2
 �������  : ��
 ����ֵ    : 0  : �¼�1���¼�2���
             -1 : �¼�1С���¼�2
              1 : �¼�1�����¼�2
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_INT32  NAS_FSM_ActCompare(
    const VOS_VOID                  *pAct1,
    const VOS_VOID                  *pAct2
)
{
    NAS_ACT_STRU                  *pstAct1;
    NAS_ACT_STRU                  *pstAct2;

    pstAct1 = (NAS_ACT_STRU *)pAct1;
    pstAct2 = (NAS_ACT_STRU *)pAct2;

    /*  ����¼�1С���¼�2,����-1 */
    if (pstAct1->ulEventType < pstAct2->ulEventType)
    {
        return -1;
    }

    /*  ����¼�1�����¼�2,����0 */
    if (pstAct1->ulEventType == pstAct2->ulEventType)
    {
        return 0;
    }

    /*  ����¼�1�����¼�2,����0 */
    return 1;
}
NAS_ACTION_FUNC NAS_FSM_FindAct(
    NAS_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState,
    VOS_UINT32                          ulEventType
)
{
    /* Ҫ���ҵ�״̬ */
    NAS_STA_STRU                        stKeySta;
    /* Ҫ���ҵ�״̬ */
    NAS_STA_STRU                       *pstRetSta;
    /* Ҫ���ҵ��¼� */
    NAS_ACT_STRU                        stKeyAct;
    /* ���ص��¼�   */
    NAS_ACT_STRU                       *pstRetAct;


    PS_MEM_SET(&stKeySta, 0x00, sizeof(stKeySta));
    PS_MEM_SET(&stKeyAct, 0x00, sizeof(stKeyAct));


    pstRetSta         = VOS_NULL_PTR;
    pstRetAct         = VOS_NULL_PTR;

    stKeySta.ulState  = ulState;

    /*lint -e586*/
    /* ����C���ԵĿ⺯��bsearch��״̬ת�Ʊ��в�����Ӧ���¼������ */
    pstRetSta         = (NAS_STA_STRU*) bsearch( &stKeySta,
                                                 pstFsmDesc->pStaTable,
                                                 pstFsmDesc->ulSize,
                                                 sizeof(NAS_STA_STRU),
                                                 (NAS_FSM_COMP_FUNC)NAS_FSM_StaCompare );
    /*lint +e586*/

    /* ����Ҳ�����Ӧ���¼������,���ô�����,����VOS_NULL_PTR */
    if (VOS_NULL_PTR == pstRetSta)
    {
        /* �˴���ԭ������ͬ��������Dopra���ش����룬
           ����ֱ�ӷ��ؿ�ָ�룬��ʾ����Ϣû�б���״̬������ */
        return (NAS_ACTION_FUNC) VOS_NULL_PTR;
    }

    stKeyAct.ulEventType = ulEventType;

    /*lint -e586*/
    /* ����C���ԵĿ⺯��bsearch���¼�������в�����Ӧ���¼������� */
    pstRetAct = (NAS_ACT_STRU*) bsearch ( &stKeyAct,
                                    pstRetSta->pActTable,
                                    pstRetSta->ulSize,
                                    sizeof(NAS_ACT_STRU),
                                    (NAS_FSM_COMP_FUNC)NAS_FSM_ActCompare );
    /*lint +e586*/

    /* ����Ҳ�����Ӧ���¼�������,���ô�����,����VOS_NULL_PTR */
    if (VOS_NULL_PTR == pstRetAct)
    {
        /* �˴���ԭ������ͬ��������Dopra���ش����룬
           ����ֱ�ӷ��ؿ�ָ�룬��ʾ����Ϣû�б���״̬������ */
        return (NAS_ACTION_FUNC) VOS_NULL_PTR;
    }

    return (pstRetAct->pfActionFun);

}


/*****************************************************************************
 �� �� ��    : NAS_FSM_StaSort
 ��������    : ��״̬ת�Ʊ�ͺ������ÿ���¼�����������п�������
 �������    : pstTbl   :״̬ת�Ʊ�
               ulSize   :״̬ת�Ʊ�Ĵ�С
 �������    : ������״̬ת�Ʊ�
 ����ֵ      : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
 *****************************************************************************/
VOS_VOID NAS_FSM_StaSort(
    NAS_STA_STRU                       *pstTbl,
    VOS_UINT32                          ulSize
)
{
    VOS_UINT32                          ulIndex;

    /*lint -e586*/
    /* ����C���ԵĿ⺯��qsort��pTable���п������� */
    qsort(pstTbl, ulSize, sizeof(NAS_STA_STRU), (NAS_FSM_COMP_FUNC)NAS_FSM_StaCompare);
    /*lint +e586*/

    /* ��ÿһ���¼������������C���ԵĿ⺯��qsort���п������� */
    for (ulIndex = 0; ulIndex < ulSize; ulIndex++)
    {
        /*lint -e586*/
        qsort( pstTbl->pActTable,
               pstTbl->ulSize,
               sizeof(NAS_ACT_STRU),
               (NAS_FSM_COMP_FUNC)NAS_FSM_ActCompare );
        /*lint +e586*/

        /* �������е���һ��STA_STRUԪ���еĶ������������ */
        pstTbl++;
    }
}


/*****************************************************************************
 �� �� ��    : NAS_FSM_RegisterFsm
 ��������    : �Ǽ�״̬����
 �������    : pucName        :״̬������
               ulSize         :״̬ת�Ʊ��С
               pstStaTbl      :״̬ת�Ʊ�
               pfExceptHandle :�쳣������
 �������    :  pstFsmDesc     :״̬��������
 ����ֵ      :  ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
 *****************************************************************************/
VOS_VOID NAS_FSM_RegisterFsm(
    NAS_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_CHAR                           *pucName,
    VOS_UINT32                          ulSize,
    NAS_STA_STRU                       *pstStaTbl,
    NAS_EXCEP_FUN                       pfExceptHandle,
    NAS_INIT_FUN                        pfInitHandle
)
{
    /* �����ڲ��� */
    if ( ( VOS_NULL_PTR == pstFsmDesc )
      || ( VOS_NULL_PTR == pstStaTbl ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC ,
                     "NAS_FSM_RegisterFsm,Parameter null ptr,pFsmDesc,pStaTable");


        return;
    }

    /* ��״̬���������ṹ���и�ֵ */
    pstFsmDesc->ulSize         = ulSize;
    pstFsmDesc->pStaTable      = pstStaTbl;
    pstFsmDesc->pfExceptHandle = pfExceptHandle;
    pstFsmDesc->pfInitHandle   = pfInitHandle;

    if (VOS_NULL_PTR == pucName)
    {
        pstFsmDesc->aucName[0] = '\0';
    }
    else
    {
        PS_MEM_CPY(pstFsmDesc->aucName,pucName,NAS_FSM_NAME_LENGTH);
        pstFsmDesc->aucName[NAS_FSM_NAME_LENGTH - 1] = '\0';
    }

    /* ��״̬ת�Ʊ�������� */
    NAS_FSM_StaSort(pstStaTbl, ulSize);

    return;

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


