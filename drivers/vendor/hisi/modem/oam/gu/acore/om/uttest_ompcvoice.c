/* ͷ�ļ����� */
#include "om.h"
#include "omprivate.h"
#include "OmCommonPpm.h"

extern VOS_UINT32                      g_ulPcvStatus;
extern VOS_UINT8                       g_ucPcvComPort;
extern OM_ACPU_DEBUG_INFO              g_stAcpuDebugInfo;



extern VOS_UINT32 OM_PcvOpen(VOS_UINT32 ulPort);
extern VOS_VOID OM_PcvReleaseAll(VOS_VOID);
extern VOS_UINT32 OM_PcvSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr,VOS_UINT32 ulDataLen);



/*******************************************************************
*������: OM_PcvOpen            
*���⺯����������:g_ulPcvStatus״̬��Ϊ�ر�
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvOpen_case1(VOS_VOID)
{
    g_ulPcvStatus = OM_PCV_CHANNEL_BUTT;

    return OM_PcvOpen(0);
}

/*******************************************************************
*������: OM_PcvOpen            
*���⺯����������:g_ulPcvStatus״̬Ϊ�ر�
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvOpen_case2(VOS_VOID)
{
    g_ulPcvStatus = OM_PCV_CHANNEL_CLOSE;

    return OM_PcvOpen(0);
}

/*******************************************************************
*������: OM_PcvReleaseAll            
*���⺯����������:g_ucPcvComPort��ΪVOS_NULL_BYTE
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_VOID uttest_OM_PcvReleaseAll_case1(VOS_VOID)
{
    g_ucPcvComPort = 0;

    OM_PcvReleaseAll();
}

/*******************************************************************
*������: OM_PcvReleaseAll            
*���⺯����������:g_ucPcvComPortΪVOS_NULL_BYTE
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_VOID uttest_OM_PcvReleaseAll_case2(VOS_VOID)
{
    g_ucPcvComPort = VOS_NULL_BYTE;

    OM_PcvReleaseAll();
}

/*******************************************************************
*������: OM_PcvSendData            
*���⺯����������:pucVirAddrΪ��ָ��
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvSendData_case1(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = VOS_NULL_PTR;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 0; 
        
    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*******************************************************************
*������: OM_PcvSendData            
*���⺯����������:pucPhyAddrΪ��ָ��
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvSendData_case2(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = VOS_NULL_PTR;
    ulDataLen  = 0; 
        
    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*******************************************************************
*������: OM_PcvSendData            
*���⺯����������:���ͳɹ�������ȡ�ź���ʧ��
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvSendData_case3(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 1; 
        
    g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = 1;

    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*******************************************************************
*������: OM_PcvSendData            
*���⺯����������:���ͳɹ�����ȡ�ź����ɹ�
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvSendData_case4(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 1; 
        
    g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = 15;

    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*******************************************************************
*������: OM_PcvSendData            
*���⺯����������:����ʧ�ܣ�������ΪBSP_ERROR
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvSendData_case5(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 1; 
        
    g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = 15;

    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*******************************************************************
*������: OM_PcvSendData            
*���⺯����������:����ʧ�ܣ�������Ϊ��������
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvSendData_case6(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 1; 
        
    g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = 15;

    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*******************************************************************
*������: OM_PcvTransmitTaskEntry            
*���⺯����������:����ʧ�ܣ�������Ϊ��������
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_VOID uttest_OM_PcvTransmitTaskEntry_case1(VOS_VOID)
{
    OM_PcvTransmitTaskEntry();
}

/*******************************************************************
*������: OM_PcvTransmitTaskEntry            
*���⺯����������:����uncache�ڴ�ʧ��
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_VOID uttest_OM_PcvTransmitTaskEntry_case2(VOS_VOID)
{
    OM_PcvTransmitTaskEntry();
}

/*******************************************************************
*������: OM_PcvPidInit            
*���⺯����������:phase��ΪVOS_IP_LOAD_CONFIG
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvPidInit_case1(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_FARMALLOC);
}

/*******************************************************************
*������: OM_PcvPidInit            
*���⺯����������:����g_stPcvOmToDspAddr uncache�ڴ�ʧ��
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvPidInit_case2(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}

/*******************************************************************
*������: OM_PcvPidInit            
*���⺯����������:����g_stPcvDspToOmAddr uncache�ڴ�ʧ��
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvPidInit_case3(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}

/*******************************************************************
*������: OM_PcvPidInit            
*���⺯����������:PID��ʼ���ɹ�
*Ԥ�ڽ����           
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvPidInit_case4(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}