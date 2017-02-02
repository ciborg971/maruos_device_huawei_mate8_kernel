
/*************************************************************************
*   ��Ȩ����(C) 1987-2011, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  mdrv_ftm.h
*
*   ��    �� :  yangzhi
*
*   ��    �� :  ���ļ�����Ϊ"DrvInterface.h", ����V7R1�����Э��ջ֮���API�ӿ�ͳ��
*
*   �޸ļ�¼ :  2011��1��18��  v1.00  yangzhi����
*************************************************************************/

#ifndef __MSP_FTM_H__
#define __MSP_FTM_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    EN_FTM_TMODE_SIGNAL=0,
    EN_FTM_TMODE_NONESIGNAL,
    EN_FTM_TMODE_LOAD,
    EN_FTM_TMODE_RESET,
    EN_FTM_TMODE_SIGNAL_NOCARD,
    EN_FTM_TMODE_OFFLINE,
    EN_FTM_TMODE_UNKNOWN = 6
} FTM_TMODE_ENUM;


/*****************************************************************************
// ��������: FTM_GetMode
// ��������: ��ȡFTM��ǰģʽ��ͬ���ӿ�
//
// ����˵��:
//   pFtmMode [out]: FTM ģʽ
//
//
//
// �� �� ֵ:
//    �ɹ���ERR_MSP_SUCCESS                 ��ʾ�����ɹ�
//    ʧ�ܣ�ERR_MSP_INVALID_PARAMETER       �������Ϊ��
//          ERR_MSP_UNKNOWN                 δ֪����
//          ERR_MSP_NOT_SUPPORT	            ��֧��
//
// ����Ҫ��: MSP��ʼ���󣬷��򷵻ش����� ERR_MSP_UNKNOWN
// ���þ���: TODO: ...
*****************************************************************************/
VOS_UINT32 FTM_GetMode(FTM_TMODE_ENUM* penFtmMode);
#ifdef __cplusplus
}
#endif
#endif
