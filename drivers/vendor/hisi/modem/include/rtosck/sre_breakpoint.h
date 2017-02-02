/**
 * @file sre_breakpoint.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������ϵ����ģ��Ķ���ͷ�ļ��� \n
 */

/** @defgroup SRE_breakpoint �ϵ����
 *@ingroup SRE_inspect
 */

#ifndef _SRE_BREAK_POINT_H
#define _SRE_BREAK_POINT_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**
 * @ingroup SRE_breakpoint
 * �ϵ������Ͷ���
 */
typedef UINT32  BP_HANDLE_T;

/**
 * @ingroup SRE_breakpoint
 * �ϵ�����
 */
typedef enum
{
    BP_TYPE_INSTRCTION       = 0,  /**< ָ��ϵ�     */
    BP_TYPE_DATA_READ        = 1,  /**< ���ݶ��ϵ�   */
    BP_TYPE_DATA_WRITE       = 2,  /**< ����д�ϵ�   */
    BP_TYPE_DATA_READ_WRITE  = 3,  /**< ���ݶ�д�ϵ㣬SD6183��Ч */
    BP_TYPE_INVALID
}OS_BP_TYPE_E;

/**
 * @ingroup SRE_breakpoint
 * �ϵ��������С����
 */
typedef enum
{
    BP_MON_SIZE_001 = 0,   /**<��������СΪ1�ֽ�    */
    BP_MON_SIZE_002 = 1,   /**<��������СΪ2�ֽ�    */
    BP_MON_SIZE_004 = 2,   /**<��������СΪ4�ֽ�    */
    BP_MON_SIZE_008 = 3,   /**<��������СΪ8�ֽ�    */
    BP_MON_SIZE_016 = 4,   /**<��������СΪ16�ֽ�   */
    BP_MON_SIZE_032 = 5,   /**<��������СΪ32�ֽڣ�SD6183��Ч   */
    BP_MON_SIZE_064 = 6,   /**<��������СΪ64�ֽڣ�SD6183��Ч   */
    BP_MON_SIZE_INVALID    /**<��������С�Ƿ�       */
}OS_BP_MON_SIZE_E;

/**@ingroup SRE_breakpoint
 * �ϵ���������:��Ӷϵ�ʱ����ľ��ָ��Ϊ�ա�
 *
 * ֵ: 0x02002201
 *
 * �������:��Ӷϵ�ʱ����ȷ������ľ��ָ��Ϸ���
 */
#define OS_ERRNO_BP_ADD_PTR_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_BP,0x01)

/**@ingroup SRE_breakpoint
 * �ϵ���������:��Ӷϵ�ʱ����Ķϵ����ͷǷ���
 *
 * ֵ: 0x02002202
 *
 * �������:��ȷ������Ķϵ�����ΪBP_TYPE_INSTRCTION��BP_TYPE_DATA_READ��BP_TYPE_DATA_WRITE��BP_TYPE_DATA_READ_WRITE����һ��(SD6183��֧��ǰ����)��
 */
#define OS_ERRNO_BP_TYPE_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_BP,0x02)

/**@ingroup SRE_breakpoint
 * �ϵ���������:��Ӷϵ�ʱ����ļ�������С�Ƿ���
 *
 * ֵ: 0x02002203
 *
 * �������:��ȷ������ļ�������С�Ϸ�:�������ݶϵ㣬�Ϸ���Χ��OS_BP_MON_SIZE_E���壬����ָ��ϵ㣬�Ϸ�ֵֻ��ΪBP_MON_SIZE_001��
 */
#define OS_ERRNO_BP_MON_SIZE_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_BP,0x03)

/**@ingroup SRE_breakpoint
 * �ϵ���������:��Ӷϵ�ʱ����ļ��������ʼ��ַ�����㰴��������С�����Ҫ��
 *
 * ֵ: 0x02002204
 *
 * �������:��ȷ������ļ��������ʼ��ַ����������С���롣
 */
#define OS_ERRNO_BP_MON_ADDR_NOT_ALIGN                      SRE_ERRNO_OS_ERROR(OS_MID_BP,0x04)

/**@ingroup SRE_breakpoint
 * �ϵ���������:�ϵ���Դ�ľ���
 *
 * ֵ: 0x02002205
 *
 * �������:����ɾ������ʹ�õĶϵ㡣
 */
#define OS_ERRNO_BP_RES_NOT_AVALIABLE                       SRE_ERRNO_OS_ERROR(OS_MID_BP,0x05)

/**@ingroup SRE_breakpoint
 * �ϵ���������:ɾ���ϵ�ʱ����Ķϵ����Ƿ���
 *
 * ֵ: 0x02002206
 *
 * �������:��ȷ������Ķϵ�����ͨ��SRE_BreakPointAdd�õ��ģ��Ҹöϵ�δ��ɾ������
 */
#define OS_ERRNO_BP_REMOVE_INVALID_HANDLE                   SRE_ERRNO_OS_ERROR(OS_MID_BP,0x06)

/**@ingroup SRE_breakpoint
 * �ϵ���������:ɾ��ջԽ����ģ��ʹ�õĶϵ���Դ��
 *
 * ֵ: 0x02002207
 *
 * �������:��ȷ������Ķϵ�����ͨ��SRE_BreakPointAdd�õ��ģ�����OS��ջԽ��ģ��ʹ�õĶϵ���Դ��
 */
#define OS_ERRNO_BP_REMOVE_STKMON_HANDLE                    SRE_ERRNO_OS_ERROR(OS_MID_BP,0x07)

/**
*@ingroup SRE_breakpoint
*@brief ��Ӷϵ㡣
*
*@par ����:
*��uwBpAddr��enSizeָ���ĵ�ַ���䣬����enBpType���͵Ķϵ㣬���ضϵ���puwBpHdl��
*
*@attention
* <ul>
* <li>��֧��SD6108/SD6181/SD6182/SD6157/SD6183ƽ̨��</li>
* <li>SD6108/SD6181/SD6182/SD6157֧��2��ָ��ϵ��2�����ݶϵ㣬���ݶϵ�ļ�ط�ΧΪ1�ֽ�~64�ֽڡ�</li>
* <li>SD6183֧��8���ϵ�(������ָ��/���ݶϵ�)���������ʱ��ط�ΧΪ1�ֽ�~16�ֽڡ�</li>
* <li>��ջԽ��ģ���ʱ����ʹ�õ����ݶϵ����1����</li>
* <li>�ϵ��Ǻ��ڹ��ܣ���ص��Ǳ��˵���Ϊ�������˻��������Ϊ���ᱻ��ء�</li>
* <li>����ָ��ϵ㣬�ϵ�Ĵ���ʱ���Ǻ˼���ִ�б����ָ��ʱ�������û��۲쵽�Ķϵ��ֳ��б����ָ�δ��ִ�С�</li>
* <li>�������ݶϵ㣬�ϵ�Ĵ���ʱ���Ǻ˼�����/д�����������ʱ�������û��۲쵽�Ķϵ��ֳ��б�������ݻ�δ����/д��</li>
* </ul>
*
*@param enBpType  [IN]  ����OS_BP_TYPE_E����ӵĶϵ����͡�
*@param uwBpAddr  [IN]  ����UINT32���ϵ����������ʼ��ַ�����밴enSize���롣
*@param enSize    [IN]  ����OS_BP_MON_SIZE_E���ϵ�������Ĵ�С��
*@param puwBpHdl  [OUT] ����BP_HANDLE_T*�����ڴ�Ŷϵ����ĵ�ַ��
*
*@retval #OS_ERRNO_BP_ADD_PTR_NULL            0x02002201����Ӷϵ�ʱ����ľ��ָ��Ϊ�ա�
*@retval #OS_ERRNO_BP_TYPE_INVALID            0x02002202����Ӷϵ�ʱ����Ķϵ����ͷǷ���
*@retval #OS_ERRNO_BP_MON_SIZE_INVALID        0x02002203����Ӷϵ�ʱ����ļ�������С�Ƿ���
*@retval #OS_ERRNO_BP_MON_ADDR_NOT_ALIGN      0x02002204����Ӷϵ�ʱ����ļ��������ʼ��ַ�����㰴��������С�����Ҫ��
*@retval #OS_ERRNO_BP_RES_NOT_AVALIABLE       0x02002205���ϵ���Դ�ľ���
*@retval #SRE_OK                              0x00000000����Ӷϵ�ɹ���
*@par ����:
*<li>sre_breakpoint.h���ýӿ��������ڵ�ͷ�ļ���</li>
*@since RTOSck V100R003C00
*@see SRE_BreakPointRemove
*/
extern UINT32 SRE_BreakPointAdd(OS_BP_TYPE_E enBpType, UINT32 uwBpAddr,  OS_BP_MON_SIZE_E enSize, BP_HANDLE_T* puwBpHdl);

/**
*@ingroup SRE_breakpoint
*@brief ɾ���ϵ㡣
*
*@par ����:
*ɾ��uwBpHdlָ���Ķϵ㡣
*
*@attention
* <ul>
* <li>��֧��SD6108/SD6181/SD6182/SD6157/SD6183ƽ̨��</li>
* </ul>
*
*@param uwBpHdl  [IN]  ����BP_HANDLE_T���ϵ�����
*
*@retval #OS_ERRNO_BP_REMOVE_INVALID_HANDLE   0x02002206��ɾ���ϵ�ʱ����Ķϵ����Ƿ���
*@retval #OS_ERRNO_BP_REMOVE_STKMON_HANDLE    0x02002207��ɾ��ջԽ����ģ��ʹ�õĶϵ���Դ��
*@retval #SRE_OK                              0x00000000��ɾ���ϵ�ɹ���
*@par ����:
*<li>sre_breakpoint.h���ýӿ��������ڵ�ͷ�ļ���</li>
*@since RTOSck V100R003C00
*@see SRE_BreakPointAdd
*/
extern UINT32 SRE_BreakPointRemove(BP_HANDLE_T uwBpHdl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _SRE_BREAK_POINT_H */

