
/**
 * @file sre_mcsem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������˼��ź���ģ��Ķ���ͷ�ļ��� \n
 */

#ifndef _SRE_MCSEM_H
#define _SRE_MCSEM_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**@defgroup SRE_mcsem �˼��ź���
  *@ingroup SRE_comm
  */
/**
 * @ingroup SRE_mcsem
 * �˼��ź����ȴ�ʱ���趨����ʾ���õȴ���
 */
#define OS_WAIT_FOREVER       0xFFFFFFFF

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺��ʼ���˼��ź����ڴ治�㡣
 *
 * ֵ: 0x02001300
 *
 * �������: ���ӹ���̬�ڴ�����Ĵ�С��
 */
#define OS_ERRNO_MCSEM_NO_MEMORY              SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x00)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺�˼��ź�������Ƿ������󡢱���δ��������ɾ������
 *
 * ֵ: 0x02001301
 *
 * �������: ����������ź���������Ƿ���󣬱����Ƿ��Ѵ�����
 */
#define OS_ERRNO_MCSEM_INVALID                SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x01)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺����ָ��Ϊ�ա�
 *
 * ֵ: 0x02001302
 *
 * �������: ��������ָ���Ƿ�Ϊ�ա�
 */
#define OS_ERRNO_MCSEM_PTR_NULL               SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x02)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺û�п��к˼��ź�����
 *
 * ֵ: 0x02001303
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_MCSEM_ALL_BUSY               SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x03)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺�˼��ź�����ȡʧ�ܡ�
 *
 * ֵ: 0x02001304
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_MCSEM_UNAVAILABLE            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x04)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺��ֹ�жϴ����������ں˼��ź�����
 *
 * ֵ: 0x02001305
 *
 * �������: �鿴�Ƿ����ж���ʹ���˺˼��ź�������ϵͳ��֧���ж���ʹ�ú˼��ź�����
 */
#define OS_ERRNO_MCSEM_PEND_INTERR            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x05)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺�����л�����ʱ����ֹ���������ں˼��ź�����
 *
 * ֵ: 0x02001306
 *
 * �������: �鿴�Ƿ�����������ʱʹ���˺˼��ź�������ϵͳ��֧����������ʱʹ�ú˼��ź�����
 */
#define OS_ERRNO_MCSEM_PEND_IN_LOCK           SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x06)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺�˼��ź����ȴ���ʱ��
 *
 * ֵ: 0x02001307
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_MCSEM_TIMEOUT                SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x07)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺�˼��ź��������������Χ��
 *
 * ֵ: 0x02001308
 *
 * �������: �鿴������ź�������ֵ�Ƿ���Ч��
 */
#define OS_ERRNO_MCSEM_OVERFLOW               SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x08)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺�������ں˼��ź���������
 *
 * ֵ: 0x02001309
 *
 * �������: �����Ƿ������������ڸú˼��ź�����
 */
#define OS_ERRNO_MCSEM_PENDED                 SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x09)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺�˼��ź�����������ǿ�ʱ��Դ����ʧ�ܡ�
 *
 * ֵ: 0x0200130A
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_MCSEM_PENDED_NULL            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0A)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺���֧�ֺ˼��ź�����Ϊ�㡣
 *
 * ֵ: 0x0200130B
 *
 * �������: ���˼��ź�������ѡ���к˼��ź��������Ƿ�Ϊ�㡣
 */
#define OS_ERRNO_MCSEM_MAXNUM_NULL            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0B)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺����#SRE_McSemPendListGetʱ����ָ���uwBufLenС��4��
 *
 * ֵ: 0x0200130C
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_MCSEM_INPUT_ERROR            SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0C)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺����#SRE_McSemPendListGetʱ��ָ�����ڴ�ռ䲻�㣬�޷�����ȫ������������PID��
 *
 * ֵ: 0x0200130D
 *
 * �������: ����uwBufLen����Ϊ(#OS_TSK_MAX_SUPPORT_NUM + 1) * #OS_MAX_CORE_NUM * 4bytes��
 */
#define OS_ERRNO_MCSEM_INPUT_BUF_NOT_ENOUGH   SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0D)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺��ͬ�����ϵĺ˼��ź���������һ�����˼��ź���ע��ʧ�ܡ�
 *
 * ֵ: 0x0200130E
 *
 * �������: ����ÿ���˵����˼��ź�����������һ���ࡣ
 */
#define OS_ERRNO_MCSEM_NUM_NOT_SAME           SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0E)

/**
 * @ingroup SRE_mcsem
 * �˼��ź��������룺�˼��ź�����ĳ�����ظ�������
 *
 * ֵ: 0x0200130F
 *
 * �������: �������ź����Ƿ񱻴�������
 */
#define OS_ERRNO_MCSEM_CREATED                SRE_ERRNO_OS_ERROR(OS_MID_MCSEM, 0x0F)


/**
 * @ingroup SRE_mcsem
 * �˼��ź���������Ͷ��塣
 */
typedef UINT32 MCSEM_HANDLE_T;

/**
 * @ingroup SRE_mcsem
 * �˼��ź���ģ��������Ϣ�Ľṹ�嶨�塣
 */
typedef struct tagMcsemModInfo
{
    UINT16 usMaxNum;                /**< ���֧�ֵĺ˼��ź�����  */
}MCSEM_MOD_INFO_S;


/**
 *@ingroup SRE_mcsem
 *@brief ����һ���˼��ź�����
 *
 *@par ����:
 *�����û�ָ�������ֺͼ���ֵ������һ���˼��ź�����
 *@attention
 *@li �����Ƿ�ɹ����ܵ�"�˼��ź����ü�����"��"���֧�ֺ˼��ź���"����������ơ�
 *@li ����ʱ��Ҫָ�����ƣ���ţ���������ϴ�������ͬ���Ƶĺ˼��ź�������ͬһ������������ֵ�Ե�һ�δ���ʱΪ׼��
 *@li RTOSck�ĺ˼��ź������ڼ������ź���������������ɾ��������Ҫ��ͬ��
 *@li �˼��ź����Ĵ�����ɾ����˰󶨣�����ʹ�ñ��뱾�˴������Ҳ��ܹ��ظ�������
 *@li wCount���ڵ���0ʱ��ʾ����ģʽ���趨������ֵ��һ��pend��Ӧһ��post��������wCountС��0�Ǳ�ʾͬ��ģʽ��-wCount��ʾͬ���Ĵ�����һ��pend��Ҫ��Ӧ-wCount��post����
 *
 *@param wCount [IN] ����Ϊ#INT32����������ʼֵ��ȡֵ��ΧΪ[-254, 254]��
 *@param uwMcSemName [IN] ����#UINT32���˼��ź������ƣ����ڱ�ʶ��˴������Ƿ�Ϊͬһ���˼��ź�����
 *@param puwSemHandle [OUT] ����Ϊ#MCSEM_HANDLE_T *������˼��ź��������
 *
 *@retval #OS_ERRNO_MCSEM_OVERFLOW 0x02001308����������ʼֵ�������Χ��
 *@retval #OS_ERRNO_MCSEM_ALL_BUSY 0x02001303��û�п��к˼��ź�������������"���֧�ֺ˼��ź���"���á�
 *@retval #OS_ERRNO_MCSEM_PTR_NULL 0x02001302�����ָ��Ϊ�ա�
 *@retval #OS_ERRNO_MCSEM_CREATED  0x0200130F���ظ�������
 *@retval #SRE_OK                  0x00000000�������ɹ���
 *@par ����:
 *@li sre_mcsem.h���ýӿ��������ڵ�ͷ�ļ���
 *@since RTOSck V100R001C01
 *@see SRE_McSemDelete
*/
extern UINT32 SRE_McSemCreate(INT32 wCount, UINT32 uwMcSemName,
                              MCSEM_HANDLE_T *puwSemHandle);

/**
 *@ingroup SRE_mcsem
 *@brief ɾ��һ���˼��ź�����
 *
 *@par ����:
 *�����û�ָ���ĺ˼��ź��������ɾ���˼��ź�����
 *@attention
 *@li RTOSck�ĺ˼��ź������ڼ������ź���������������ɾ��������Ҫ��ͬ��
 *@li RTOSck�ĺ˼��ź������˺˺ţ����˴���ֻ�ܱ���ɾ�����Ҳ����ظ�ɾ����
 *@li ɾ�����������ź��������������0ʱ�Ż�����ɾ���ú˼��ź�����
 *@li ��������������ڸú˼��ź�������ɾ��ʧ�ܡ�
 *
 *@param uwSemHandle [IN] ����Ϊ#MCSEM_HANDLE_T���˼��ź����������Դ�ں˼��ź��������ɹ������ֵ��
 *
 *@retval #OS_ERRNO_MCSEM_INVALID 0x02001301���˼��ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 *@retval #OS_ERRNO_MCSEM_PENDED  0x02001309�������������ڸú˼��ź�������ֹɾ����
 *@retval #SRE_OK                 0x00000000�������ɹ���
 *@par ����:
 *@li sre_mcsem.h���ýӿ��������ڵ�ͷ�ļ���
 *@since RTOSck V100R001C01
 *@see SRE_McSemCreate
*/
extern UINT32 SRE_McSemDelete(MCSEM_HANDLE_T uwSemHandle);

/**
 *@ingroup SRE_mcsem
 *@brief ����˼��ź�����������ֵ������
 *
 *@par ����:
 *�����û�ָ���ĺ˼��ź������������˼��ź�����������ֵ��
 *@attention
 *@li ��������������ڸú˼��ź�����������ʧ�ܡ�
 *
 *@param uwSemHandle [IN] ����Ϊ#MCSEM_HANDLE_T���˼��ź����������Դ�ں˼��ź��������ɹ������ֵ��
 *@param wCount [IN] ����Ϊ#INT32���������趨ֵ��ȡֵ��ΧΪ[-254, 254]��
 *
 *@retval #OS_ERRNO_MCSEM_INVALID  0x02001301���˼��ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 *@retval #OS_ERRNO_MCSEM_OVERFLOW 0x02001308���������趨ֵ�������Χ��
 *@retval #OS_ERRNO_MCSEM_PENDED   0x02001309�������������ڸú˼��ź�������ֹ���衣
 *@retval #SRE_OK                  0x00000000�������ɹ���
 *@par ����:
 *@li sre_mcsem.h���ýӿ��������ڵ�ͷ�ļ���
 *@since RTOSck V100R001C01
 *@see SRE_McSemCreate | SRE_McSemCountGet
*/
extern UINT32 SRE_McSemReset(MCSEM_HANDLE_T uwSemHandle, INT32 wCount);

/**
 *@ingroup SRE_mcsem
 *@brief ��ȡ�˼��ź�����������ֵ��
 *
 *@par ����:
 *�����û�ָ���ĺ˼��ź����������ȡ�˼��ź�����������ֵ��
 *@attention
 *
 *@param uwSemHandle [IN] ����Ϊ#MCSEM_HANDLE_T���˼��ź����������Դ�ں˼��ź��������ɹ������ֵ��
 *@param pwCount     [OUT] ����Ϊ#INT32 * �����ظ��û��ĵ�ǰ�ź�������ֵ����Χ[-254, 254]��
 *
 *@retval #OS_ERRNO_MCSEM_INVALID      0x02001301����ȡʧ�ܣ��˼��ź������������ѱ�ɾ����
 *@retval #OS_ERRNO_MCSEM_INPUT_ERROR  0x0200130C��ָ��Ϊ��
 *@retval #SRE_OK                      0x00000000�������ɹ���
 *@par ����:
 *@li sre_mcsem.h���ýӿ��������ڵ�ͷ�ļ���
 *@since RTOSck V100R001C01
 *@see SRE_McSemCreate | SRE_McSemReset
*/
extern UINT32 SRE_McSemCountGet(MCSEM_HANDLE_T uwSemHandle, INT32 * pwCount);

/**
 *@ingroup SRE_mcsem
 *@brief ����һ���˼��ź�����
 *
 *@par ����:
 *�����û�ָ���ľ���͵ȴ�ʱ�䣬����˼��ź��������������ֵ����0���򷵻سɹ���
 *@attention
 *@li ��osStart֮ǰ���ܵ��øýӿڡ�
 *@li �ȴ�ʱ�����ѡ����ȴ����ȴ��ض�ʱ�䡢���õȴ���
 *@li ��û���ź�����Դʱ������ȴ��ú���ֻ�ܱ�������á�
 *@li ���п�����Դʱ��ϵͳ�����жϺ�������pend�ź����ɹ���
 *@li ��û�п�����Դ����ֹ�жϴ������������������ú˼��ź�����
 *@li ���ϵͳû�д�TICK���أ�������#OS_WAIT_FOREVERģʽ���еȴ���
 *
 *@param uwSemHandle [IN] ����Ϊ#MCSEM_HANDLE_T���˼��ź����������Դ�ں˼��ź��������ɹ������ֵ��
 *@param uwTimeout   [IN] ����Ϊ#UINT32���ȴ�ʱ�����ƣ���λΪtick��ȡֵ��ΧΪ[0, 0xffffffff]��
 *#OS_NO_WAIT��0��ʾ���ȴ���#OS_WAIT_FOREVER��0xffffffff��ʾ���õȴ���
 *
 *@retval #OS_ERRNO_MCSEM_INVALID      0x02001301���˼��ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 *@retval #OS_ERRNO_MCSEM_UNAVAILABLE  0x02001304���˼��ź�����ȴ�ʱ��ȡʧ�ܡ�
 *@retval #OS_ERRNO_MCSEM_PEND_INTERR  0x02001305���жϴ�������ֹ����������
 *@retval #OS_ERRNO_MCSEM_PEND_IN_LOCK 0x02001306��ϵͳ������ԴΪ0�����л�����ʱ����ֹ������������
 *@retval #OS_ERRNO_MCSEM_TIMEOUT      0x02001307������ȴ��˼��ź�����ʱ��
 *@retval #SRE_OK                      0x00000000�������ɹ���
 *@par ����:
 *@li sre_mcsem.h���ýӿ��������ڵ�ͷ�ļ���
 *@since RTOSck V100R001C01
 *@see SRE_McSemPost
*/
extern UINT32 SRE_McSemPend(MCSEM_HANDLE_T uwSemHandle, UINT32 uwTimeout);

/**
 *@ingroup SRE_mcsem
 *@brief �ͷ�ָ���ĺ˼��ź�����
 *
 *@par ����:
 *�����û�ָ���ľ�����ͷź˼��ź�����
 *����ģʽ:
 *��û������ȴ��ú˼��ź�������ֱ�ӽ���������1���ء�
 *������Ϊ�˺˼��ź��������������б��еĵ�һ���������������ģ���
 *ͬ��ģʽ:
 *��û������ȴ��ú˼��ź��������ͷŵĴ���С���趨��ͬ����������ֱ�ӽ���������1���ء�
 *������Ϊ�˺˼��ź��������������б��еĵ�һ���������������ģ���
 *@attention
 *@li ��osStart֮ǰ���ܵ��øýӿ�
 *@li ������ѵ�����Ǳ��ˣ���ᴥ���˼��жϣ����ͻ�������Ĳ�����
 *@li ��δ�����������£�������ѵ��������ȼ����ڵ�ǰ����������̷��������л���
 *
 *@param uwSemHandle [IN] ����Ϊ#MCSEM_HANDLE_T���˼��ź����������Դ�ں˼��ź��������ɹ������ֵ��
 *
 *@retval #OS_ERRNO_MCSEM_INVALID  0x02001301���˼��ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 *@retval #OS_ERRNO_MCSEM_OVERFLOW 0x02001308���˼��ź��������������Χ��
 *@retval #OS_ERRNO_IPC_SHQ_FULL   0x02001486��6181��6108ƽ̨�£����ͺ˼��жϣ��������������
 *@retval #SRE_OK                  0x00000000�������ɹ���
 *@par ����:
 *@li sre_mcsem.h���ýӿ��������ڵ�ͷ�ļ���
 *@since RTOSck V100R001C01
 *@see SRE_McSemPend
*/
extern UINT32 SRE_McSemPost(MCSEM_HANDLE_T uwSemHandle);

/**
 *@ingroup SRE_mcsem
 *@brief ��ȡ�˼��ź����ϵ�����������Ϣ��
 *
 *@par ����:
 *�����û�ָ���ĺ˼��ź����������ȡ�����ڸú˼��ź����ϵ���������Լ���Ӧ������PID��
 *@attention
 *@li �������������ڸú˼��ź������򷵻������ڸú˼��ź�����������Ŀ���Լ���Ӧ�����PID��
 *@li ��û�����������ڸú˼��ź������򷵻������ڸú˼��ź�����������ĿΪ0��
 *@li ��ָ�����ڴ泤��С��ʵ�����賤�ȣ��򷵻ش����룬��ָ�����ڴ��е�����PID��Ȼ��Ч��
 *@li �û�Ӧ��֤�洢����PID���ڴ�ռ��㹻�󣬽��齫uwBufLen����Ϊ(#OS_TSK_MAX_SUPPORT_NUM + 1) * #OS_MAX_CORE_NUM * 4bytes��
 *
 *@param uwSemHandle [IN]  ����Ϊ#MCSEM_HANDLE_T���˼��ź����������Դ�ں˼��ź��������ɹ������ֵ��
 *@param puwTskCnt   [OUT] ����Ϊ#UINT32 *�����ظ��û��������ڸú˼��ź�����������Ŀ��
 *@param puwPidBuf   [OUT] ����Ϊ#UINT32 *�����û�ָ�����ڴ������׵�ַ�����ڴ洢������ָ���˼��ź���������PID��
 *@param uwBufLen    [IN]  ����Ϊ#UINT32���û�ָ�����ڴ�����ĳ��ȣ���λ���ֽڣ���
 *
 *@retval #OS_ERRNO_MCSEM_INVALID               0x02001301���˼��ź������Ϊ�Ƿ�ֵ�����ѱ�ɾ����
 *@retval #OS_ERRNO_MCSEM_INPUT_ERROR           0x0200130C��ָ��Ϊ�ջ���uwBufLenС��4��
 *@retval #OS_ERRNO_MCSEM_INPUT_BUF_NOT_ENOUGH  0x0200130D��ָ�����ڴ�ռ䲻�㣬���ڴ��е�����PID��Ȼ��Ч��
 *@retval #SRE_OK                               0x00000000�������ɹ���
 *@par ����:
 *@li sre_mcsem.h���ýӿ��������ڵ�ͷ�ļ���
 *@since RTOSck V100R001C01
 *@see ��
*/
extern UINT32 SRE_McSemPendListGet( MCSEM_HANDLE_T uwSemHandle,
                                    UINT32 *puwTskCnt,
                                    UINT32 *puwPidBuf,
                                    UINT32  uwBufLen );

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MCSEM_H */


