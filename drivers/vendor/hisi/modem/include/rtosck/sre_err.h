/**
 * @file sre_err.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������������ͷ�ļ��� \n
 */

 /**
 *@defgroup  SRE_err  ������
 *@ingroup SRE_inspect
*/

 /**
 *@defgroup  SRE_cda  CDA
 *@ingroup SRE_inspect
*/
/**
*@defgroup  SRE_cda  CDA
*@ingroup SRE_inspect
*/

#ifndef _SRE_ERR_H
#define _SRE_ERR_H
#include "sre_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_cda
 * CDA��¼��Ϣ������ջ������ڴ��������ʼ��ַ�ʹ�С��
 */
typedef struct tagPtInfo
{
    UINT32 uwAddr;                  /**< �ڴ������ʼ��ַ   */
    UINT32 uwSize;                  /**< �ڴ�����Ĵ�С     */
}CDA_PT_INFO_S;

/**
*@ingroup SRE_err
*
*@brief �������Ӻ�����
*
*@par ����:
*������Ĺ��Ӻ������û��Զ���Ĵ�����������Ҫ���ϸù��Ӻ����Ĳ���Ҫ��
*
*@attention �ޡ�
*
*@param pcFileName [IN] ����#CHAR *�������ļ�����
*@param uwLineNo [IN] ����#UINT32 ��������кš�
*@param uwErrorNo [IN] ����#UINT32���û�����Ĵ����롣
*@param uwParaLen [IN] ����#UINT32�����pPara�ĳ��ȡ�
*@param pPara [IN] ����#VOID *����¼�û����ڴ����������������
*
*@retval ��
*@par ����:
*<li>sre_err.h���ýӿ��������ڵ�ͷ�ļ���</li>
*@since UniDSP V100R001C01
*@see ��
*/
typedef VOID (*SRE_ERRORHANDLE_FUNC)(CHAR    *pcFileName,
                                     UINT32   uwLineNo,
                                     UINT32   uwErrorNo,
                                     UINT32   uwParaLen,
                                     VOID     *pPara);

/**
*@ingroup SRE_err
*
*@brief �������
*
*@par ����:
*�û�����OS�ڲ�ʹ�øú����ص�#SRE_ErrRegHook��ע��Ĺ��Ӻ��������⣬OS�ڲ�ʹ�ô˽ӿ�ʱ�������¼��ش����롣
*@attention
* <ul>
* <li>ϵͳ��������μ�⣬�û�SRE_ErrHandle��ȫ����������������롣</li>
* <li>�û�����SRE_ErrHandle�ӿ�ʱ��ֻ��ص��û�ע�ṳ�Ӻ�����������д������¼����������Ҳ�����¼Trace�켣�ʹ����쳣����</li>
* </ul>
*
*@param pcFileName [IN] ����#CHAR *�����������ļ�����������__FILE__��Ϊ���롣
*@param uwLineNo   [IN] ����#UINT32�����������ڵ��кţ�������__LINE__��Ϊ���롣
*@param uwErrorNo  [IN] ����#UINT32���û�����Ĵ����롣
*@param uwParaLen  [IN] ����#UINT32�����pPara�ĳ��ȡ�
*@param pPara      [OUT]����#VOID *����¼�û����ڴ����������������
*
*@retval #SRE_OK      0x00000000���������ɹ���
*@par ����:
*<li>sre_err.h: �ýӿ��������ڵ�ͷ�ļ���</li>
*@since UniDSP V100R001C01
*@see ��
*/
extern UINT32 SRE_ErrHandle( CHAR *pcFileName, UINT32 uwLineNo, UINT32 uwErrorNo, UINT32 uwParaLen, VOID *pPara );

/**
*@ingroup SRE_err
*
*@brief ��ȡ��ǰ�̼߳�¼�����һ�������롣
*
*@par ����:
*��ȡ��ǰ�̼߳�¼�����һ�������롣������߳�δ��¼�����룬�򷵻�0�������¼�˴����룬�򷵻ؼ�¼�����һ�������롣
*@attention
* <ul>
* <li>�û�����SRE_ErrHandle�ϱ��Ĵ����벻�ᱻ��¼��������һ�������벻������������롣</li>
* <li>�ڴ�ģ���ʼ�����ǰ���øýӿڣ��򷵻�0��</li>
* </ul>
*
*@param ��
*
*@retval #������ ��ǰ�߳��ϱ������һ��������
*@par ����:
*<li>sre_err.h: �ýӿ��������ڵ�ͷ�ļ���</li>
*@since RTOSck V100R002C00
*@see ��
*/
extern UINT32 SRE_GetLastError(VOID);

/**
*@ingroup SRE_cda
*
*@brief ��ȡCDA������Ϣ������
*
*@par ����:
*��ȡ����ջ��ʼ��ַ�ͳ���(��������ʱ��Ч)���Լ���ǰ�˴��������з�����ʼ��ַ�Լ����ȡ�
*@attention
* <ul>
* <li>pstCdaPtInfo����һ�����飬����������CDA_PT_INFO_S��Ϊ��ֹ����дԽ�磬��ȷ������ռ��㹻��</li>
* <li>��������Ԫ��˳��Ϊ���û����õ�����ջ+osĬ�ϴ����ķ���+�û����õķ��������CDAʹ��ʵ����</li>
* <li>���pstCdaPtInfo�����Null���ӿڲ��᷵�ش����룬���������سɹ���</li>
* </ul>
*
*@param pstCdaPtInfo [OUT] ����#CDA_PT_INFO_S *����������ջ���ڴ�������׵�ַ�볤�ȡ�
*
*@retval ��
*@par ����:
*<li>sre_err.h: �ýӿ��������ڵ�ͷ�ļ���</li>
*@since UniDSP V100R001C01
*@see ��
*/
extern VOID SRE_CdaInfoGet(CDA_PT_INFO_S *pstCdaPtInfo);

/**
*@ingroup SRE_err
*
*@brief ע���û�������Ĺ��Ӻ�����
*
*@par ����:
*ע��pfnHook��Ϊ�û����Ӻ������ڵ���SRE_ErrHandle�ӿڽ��д�����ʱ�Ըù��ӽ��е��á�
*@attention
* <ul>
* <li>�����pfnHookΪNULL,��Ϊȡ�����ӡ�</li>
* <li>�������ظ��򸲸�ע�ᡣ</li>
* <li>�û�����Ĺ��Ӻ����������#SRE_ERRORHANDLE_FUNC�������ʽ������ֻ�ܶ���һ�����Ӻ�����</li>
* <li>�û�����SRE_ErrRegHookע��ص����Ӻ���ʱ�����Ӻ������治���е���SRE_ErrHandle���ߵ���OS���������ϱ�������������������ܻ������ѭ���������û���֤��</li>
* <li>�û�����SRE_ErrRegHookע��ص����Ӻ���ʱ�����Ӻ����������е����ϱ��Ĵ�����Ϣ��ֻ�е�һ�ε��û�ִ�У�����ô���ȼ�¼�����д�����Ϣ���ټ�¼��������ʱ�Ĵ�����Ϣ��</li>
* </ul>
*
*@param pfnHook [IN] ����#SRE_ERRORHANDLE_FUNC���û����Ӻ����ĺ궨�塣
*
*@retval #OS_ERRNO_HOOK_FULL              0x02001604���ظ�ע��������ӡ�
*@retval #SRE_OK                          0x00000000��ע��ɹ���
*@par ����:
*<li>sre_err.h���ýӿ��������ڵ�ͷ�ļ���</li>
*@since UniDSP V100R001C01
*@see ��
*/
extern UINT32 SRE_ErrRegHook(SRE_ERRORHANDLE_FUNC pfnHook);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_ERR_H */

