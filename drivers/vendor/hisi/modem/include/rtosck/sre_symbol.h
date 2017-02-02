/**
 * @file sre_symbol.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ���������ű�ģ���ͷ�ļ� \n
 */

/**
 * @defgroup SRE_symbol ���ű�
 * @ingroup SRE_inspect
*/

#ifndef _SRE_SYMBOL_H
#define _SRE_SYMBOL_H

#include "sre_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_symbol
 * ���ű���������:���ָ��Ϊ�ա�
 *
 * ֵ: 0x02002900
 *
 * �������: �Ų麯������Ƿ�Ϊ��
 *
 */
#define OS_ERRNO_SYMBOL_PARA_POINT_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x00)

/**
 * @ingroup SRE_symbol
 * ���ű���������:���ű�����ڴ�����ʧ�ܡ�
 *
 * ֵ: 0x02002901
 *
 * �������: �����ű����ķ����ڴ��С�Ƿ��û���OS�ڴ��������
 *
 */
#define OS_ERRNO_SYMBOL_MEM_ALLOC_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x01)

/**
 * @ingroup SRE_symbol
 * ���ű���������:�����ض��塣
 *
 * ֵ: 0x02002902
 *
 * �������:����Ƿ��з���������
 *
 */
#define OS_ERRNO_SYMBOL_REDEFINE_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x02)

/**
 * @ingroup SRE_symbol
 * ���ű���������:�ڷ��ű���û�в��ҵ���ַƥ��ķ��Žڵ㡣
 *
 * ֵ: 0x02002903
 *
 * �������: ��ȷ�ϲ��ҵĵ�ַ�Ƿ���ȷ
 *
 */
#define OS_ERRNO_SYMBOL_FIND_ADDR_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x03)

/**
 * @ingroup SRE_symbol
 * ���ű���������:�ڷ��ű���û�в��ҵ���������ƥ��ķ��Žڵ㡣
 *
 * ֵ: 0x02002904
 *
 * �������: ��ȷ�ϲ��ҵķ������Ƿ���ȷ
 *
 */
#define OS_ERRNO_SYMBOL_FIND_NAME_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x04)

/**
 * @ingroup SRE_symbol
 * ���ű���������:���ű�ڵ�ɾ��ʧ�ܣ���̬���ű�����ɾ����
 *
 * ֵ: 0x02002905
 *
 * �������: �鿴ɾ���ķ������Ӧ��UnitInterNo�Ƿ�����ȷ��UnitInterNoΪ0��ʾ��̬�����������ɾ����
 *
 */
#define OS_ERRNO_SYMBOL_REMOVE_ID_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x05)

/**
 * @ingroup SRE_symbol
 * ���ű���������:��̬��ӷ����������ID�뾲̬���ظ���
 *
 * ֵ: 0x02002906
 *
 * �������: �鿴��̬��ӷ���������UnitInterNo�Ƿ���ȷ������Ϊ0(UnitInterNoΪ0��ʾ��̬������)��
 *
 */
#define OS_ERRNO_SYMBOL_PARA_ID_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x06)

/**
 * @ingroup SRE_symbol
 * ���ű���������:���ű���ʹ�õľ���ID�����á�
 *
 * ֵ: 0x02002907
 *
 * �������: ����ڳ�ʼ��ʱ�����ô����룬����Ƿ���ͬһ�����ظ���ʼ�����߾���ID���ô���
 *           �����ʹ��ʱ�����ô����룬�鿴��Ӧ�����Ƿ���ڻ��߸þ���ķ��ű��Ƿ�򿪡�
 *
 */
#define OS_ERRNO_SYMBOL_IMAGE_ID_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x07)

/**
 * @ingroup SRE_symbol
 * ���ű���������:���ű����õķ�����ʼ��ַ���С���Ϸ���
 *
 * ֵ: 0x02002908
 *
 * �������: �û����õķ����Ų�Ϊ0ʱ�����ű�ģ�����õķ�����ʼ��ַ���ߴ�С����Ϊ0��
 *
 */
#define OS_ERRNO_SYMBOL_ADDR_SIZE_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x08)

/**
 * @ingroup SRE_symbol
 * ���ű���������:���ű����õķ����Ų��Ϸ���
 *
 * ֵ: 0x02002909
 *
 * �������: SD6183/SD6182/SD6108/SD6181/SD6157ƽ̨�����ű�ģ������Ų�������Ϊ0��
 *
 */
#define OS_ERRNO_SYMBOL_PT_NUM_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x09)

/**
 * @ingroup SRE_symbol
 * ���ű���������:ͬһ������ű����õķ���������һ�¡�
 *
 * ֵ: 0x0200290a
 *
 * �������: SD6182/SD6157/SD6183/SD6108/SD6181ƽ̨�����ͬһ����sre_config.h�з��ű�ģ����������Ƿ���ͬ��
 *
 */
#define OS_ERRNO_SYMBOL_PT_PARA_NOT_SAME                     SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x0a)

/**
 * @ingroup SRE_symbol
 * ���ű���������:���ݷ�������ȡ���ŵ�ַʱ�������ָ�����ΪNULL��
 *
 * ֵ: 0x0200290b
 *
 * �������: ���ݷ�������ȡ���ŵ�ַʱ���뱣֤�����ָ���������ΪNULL��
 *
 */
#define OS_ERRNO_SYMBOL_GET_ADDR_PTR_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x0b)


/**
* @ingroup SRE_symbol
* δ����ķ������͡�
*
*/
#define OS_SYM_UNDF        0x0

/**
* @ingroup SRE_symbol
* ȫ�ַ������͡�
*
*/
#define OS_SYM_GLOBAL      0x1

/**
* @ingroup SRE_symbol
* ����η������͡�
*
*/
#define OS_SYM_TEXT        0x2

/**
* @ingroup SRE_symbol
* ���ݶη������͡�
*
*/
#define OS_SYM_DATA        0x4

/**
* @ingroup SRE_symbol
* absolute�������͡�
*
*/
#define OS_SYM_ABS         0x8

/**
* @ingroup SRE_symbol
* ͨ�÷������͡�
*
*/
#define OS_SYM_COMM        0x10

/**
* @ingroup SRE_symbol
*  ȱʡ������ID�š�
*
*/
#define OS_SYMBOL_REVID    0x0

/**
* @ingroup SRE_symbol
* ���÷��ű�ģ����Ϣ��
*
*/
typedef struct tagSymbolModInfo
{
    UINT32 uwInitPhase;        /**<  ���ű��ʼ�����      */
    UINT32 uwSymRegNum;        /**<  ���ű������          */
    VOID*  uwSymRegAddr;       /**<  ���ű������ʼ��ַ    */
    UINT32 uwSymRegSize;       /**<  ���ű������С        */
#if (OS_OPTION_SYMBOL_COREBITMAP == YES)
    UINT32 uwSymUnitNum;       /**<  ���ű���һ��������ע���LP��Ԫ��*/
#endif

} SYMBOL_MOD_INFO_S;


/**
 * @ingroup SRE_symbol
 * �����������ڵ�ṹ�嶨�塣
 *
 */
typedef struct tagSllNode
{
    struct tagSllNode *pstNext;/**<������ָ����һ���ڵ��ָ��*/
} OS_SLL_NODE_S;


/**
 * @ingroup SRE_symbol
 * Hash��Ľڵ�ṹ�塣
 *
 */
typedef struct tagSymbolNode   /**< HASH_SYMBOL_NODE - entry in symbol table */
{
    OS_SLL_NODE_S stNameHNode;     /**< hash node (must come first)     */
    CHAR*       pcName;            /**< ָ���������ָ��                */
    VOID*       pscValue;          /**< ���ŵ�ַ                        */
    UINT8       ucType;            /**< ��������: OS_SYM_UNDF&OS_SYM_GLOBAL&OS_SYM_ABS&OS_SYM_TEXT&OS_SYM_DATA��   */
    UINT8       ucSymGroupID;      /**< ���Ŷ�̬��ӵ���ID��0~0xfeΪLPʹ��(ֵΪLP��GroupID+1)��0xffΪshellʹ��,֧��SRE_MNG�����¸��ֶ�Ϊ��Ч*/
    UINT16      usUnitInterNo;     /**< ���ŵ�������ԪID��1~9999ΪLPʹ��(ֵΪLP���ڲ�������Ԫ��)��0xfffeΪshellʹ��*/
    UINT32      uwSize;            /**< ���ŵĳ���                      */
} OS_SYMBOL_NODE_S;


/**
 * @ingroup SRE_symbol
 * Hash���ÿ������ͷ�ṹ�嶨�壬�ֱ�ָ���������β�ڵ㡣
 *
 */
typedef struct tagSllList
{
    OS_SLL_NODE_S *pstHead;  /**< ����ͷָ��*/
    OS_SLL_NODE_S *pstTail;  /**< ����βָ��*/
} OS_SLL_LIST_S;

/**
 * @ingroup SRE_symbol
 * Hash���ͷ��ͳ�����ű����Ϣ��
 *
 */
typedef struct tagSymbolTbl
{
    UINT32   uwElements;           /**< Hash����Hash����ĸ���      */
    UINT32   uwKeyArg;             /**< Hash�������                */
    UINT32   uwInitPhase;          /**< ���ű��ʼ�����            */
    UINT32   uwSymPartId;          /**< ���ű�������ڵ��ڴ������  */
    UINT32   uwSymbolNum;          /**< Hash���з��ŵĸ���          */
    OS_SLL_LIST_S *pstHashTbl;     /**< ָ��Hash���������ָ��      */
} OS_SYMBOL_TBL_S;


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_SYMBOL_H */

/**
 * History:
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/

