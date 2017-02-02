/**
 * @file sre_exc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������쳣ģ��Ķ���ͷ�ļ��� \n
 */

/**@defgroup SRE_exc �쳣�ӹ�
  *@ingroup SRE_inspect
*/

#ifndef _SRE_EXC_H
#define _SRE_EXC_H

#include "sre_base.h"
#include "sre_hook.h"
#include "sre_sys.h"
#include "sre_hw_ecc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//ĿǰUOS��֧���쳣�Խӹܹ���
//#if (OS_OPTION_EXC == YES)

/**
 *@ingroup SRE_exc
 *�쳣������: ��ȡ�쳣��������Ϣ�ӿ����Ϊ��ָ�롣
 *
 *ֵ��0x02001c02
 *
 *���������������ָ����Ч�ԡ�
 */
#define OS_ERRNO_EXC_PARA_INVLAID                               SRE_ERRNO_OS_ERROR(OS_MID_EXC,0x2)

/**
 *@ingroup SRE_exc
 *�쳣������: Cortex-Ax���õĸ�λ����ʧ�ڴ���ʼ��ַû��4�ֽڶ��롣
 *
 *ֵ��0x02001c04
 *
 *���������A7,A9 ���õĸ�λ����ʧ�ڴ���ʼ��ַ����4�ֽڶ��롣
 */
#define OS_ERRNO_EXC_RESET_NOLOSE_MEM_ADDR_NOT_ALIGN            SRE_ERRNO_OS_ERROR(OS_MID_EXC,0x4)

/**
 *@ingroup SRE_exc
 *�쳣������: �쳣ģ��ע���쳣���Ӻ���Ϊ�ա�
 *
 *ֵ��0x02001c09
 *
 *����������鿴ע���쳣���Ӻ����Ƿ�Ϊ�ա�
 */
#define OS_ERRNO_EXC_REG_HOOK_PTR_NULL                          SRE_ERRNO_OS_ERROR(OS_MID_EXC,0x9)

/**
 *@ingroup SRE_exc
 *�쳣������: �쳣ע�ắ����,double�쳣ջ�ռ�����̫С��
 *
 *ֵ��0x02001c0a
 *
 *���������������double�쳣ջ�ռ�ĳ��ȣ�ʹ֮��С���쳣�Ĵ�����ϢEXC_REGS_S��3��(double�쳣,NMI�쳣,Debug�쳣����)��
 */
#define OS_ERRNO_EXC_REGISTER_DOUBLE_EXC_STACK_TOOSMALL              SRE_ERRNO_OS_ERROR(OS_MID_EXC,0xa)

/**
 *@ingroup SRE_exc
 *�쳣������: �ж����ȼ����뱻�ȣ�����ϵͳ�쳣������
 *
 *ֵ��0x03001c0b
 *
 *���������
 *��Ʒ����ͨ��&g_auwIntMask�ҵ������ŵ�ַ���ж��Ƿ������µ�ֵ
 *SD6108/SD6181 DSP:0xC00010C0 0x307F8D20 0x0F80201E 0x00000201
 *SD6108/SD6181 CPU:0x000000C0 0xF07F9B20 0x0F80201E 0x00000401
 *SD6182:0x2BFFB8C1 0xD400043C 0x00000302
 *������ǣ�˵�����뱻�ȣ������ж����ȼ��������ڵ��ڴ��д����ݶϵ㣬��λΪ�λ�����ж����ȼ����뱻�ȵĴ���
 */
#define OS_ERRNO_EXC_INTERRUPT_LEVEL_MASK_ERROT                      SRE_ERRNO_OS_FATAL(OS_MID_EXC,0xb)

/**
 *@ingroup SRE_exc
 *�쳣������: Hac��ʱ������δע�ᡣ
 *
 *ֵ��0x03001c12
 *
 *�������������˷�֧�����������һ����Hac��ʱ����soc�е�interrupt�Ĵ������壬�����жϵ��ȵ����쳣��֧��
 *һ�����ж����ȼ����뱻�ȣ����½��������֧��Ȼ�����ڲ�Ʒû��ע������쳣�Ĺ��ӣ���˽�������������
 *��Ʒ����ͨ��&g_auwIntMask�ҵ������ŵ�ַ���ж��Ƿ������µ�ֵ
 *SD6108/SD6181 DSP:0xC00010C0 0x307F8D20 0x0F80201E 0x00000201
 *SD6108/SD6181 CPU:0x000000C0 0xF07F9B20 0x0F80201E 0x00000401
 *SD6182:0x2BFFB8C1 0xD400043C 0x00000302
 *������붼��ȷ������hac���ֳ�ʱ�����ˡ�
 */
#define OS_ERRNO_EXC_HAC_EXCEPTION_HOOK_NOREG                       SRE_ERRNO_OS_FATAL(OS_MID_EXC, 0x12)

/**
 *@ingroup SRE_exc
 *�쳣������: �����쳣��Ϣ����ṹ���ڴ�����ʧ�ܡ�
 *
 *ֵ��0x02001c13
 */
#define OS_ERRNO_EXC_INFO_STRUC_MALLOC_FAIL                         SRE_ERRNO_OS_ERROR(OS_MID_EXC, 0x13)


/**
 *@ingroup SRE_exc
 *����ջ������������
 */
#define EXC_CSTK_DEAPTH             10

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220)||(OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:ָ��Ԥȡ�����쳣��
 */
#define OS_EXCCAUSE_INSTRPIFDATAERROR_CAUSE                 12

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:����Ԥ��ȡ�����쳣��
 */
#define OS_EXCCAUSE_LOADSTOREPIFDATAERROR_CAUSE             13

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:WriteError�����쳣��
 */
#define OS_EXCCAUSE_WRITEERROR             67

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:ECC�����쳣��
 */
#define OS_EXCCAUSE_ECCERROR               68

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:NMI�ж��쳣��
 */
#define OS_EXCCAUSE_NMIERROR               69

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:�ظ�λ�쳣��
 */
#define OS_EXCCAUSE_RESET_REENTRY          70

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:Double�쳣��
 */
#define OS_EXCCAUSE_DOUBLEERROR            71

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:���������쳣��
 */
#define OS_EXCCAUSE_FATALERROR             72

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:ջԽ���쳣��
 */
#define OS_EXCCAUSE_STACKOVERFLOW          73

/**
 *@ingroup SRE_exc
 *SD6182/SD6157�쳣��������:Ӳ���ź��������쳣��
 */
#define OS_EXCCAUSE_HWSEMERROR             74

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:ָ��ϵ��쳣��
 */
#define OS_EXCCAUSE_INSTRUCTION_BP         75

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181�쳣��������:���ݶϵ��쳣��
 */
#define OS_EXCCAUSE_DATA_BP                76

#if ((OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220)||(OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 *@ingroup SRE_exc
 *SD6182�쳣��������:Hac�����쳣��
 */
#define OS_EXCCAUSE_HACERROR               77

/**
 *@ingroup SRE_exc
 *SD6182/SD6157�쳣��������:Msgm�����쳣��
 */
#define OS_EXCCAUSE_MSGM_ERROR             78

/**
 *@ingroup SRE_exc
 *SD6182/SD6157�쳣��������:msgQ bus err�쳣��
 */
#define OS_EXCCAUSE_MSGQBUSERROR           79

#endif

#endif

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 *@ingroup SRE_exc
 * ����ջ��Ϣ�ṹ�塣
 */
typedef struct tagCstkStackInfo
{
    UINT32  uwStackAddr;                /**< ������ջ���ַ */
    UINT32  uwInstrAddr;                /**< �������ص�ַ   */
} CSTK_FRAME_INFO_S;
#endif

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170))

/*
 *�쳣ʱ��¼��ipc������Ϣ,ע��ͬ�����²��Դ���Ľṹ��TST_IPC_STATUS_S��
 */
typedef struct tagIpcStatus
{
    UINT32 vuwSrc;
    UINT32 vuwData[2];
} IPC_STATUS_S;


/**
 *@ingroup SRE_exc
 *SD6181ƽ̨�·���ȫ��Ӳ���ź����쳣��־��
 */
#define  GHWSEM_ERR_FLAG                   0x1

/**
 *@ingroup SRE_exc
 *SD6181ƽ̨�·����ֲ�Ӳ���ź����쳣��־��
 */
#define  LHWSEM_ERR_FLAG                   0x2

/**
 * @ingroup SRE_exc
 * Ӳ���ź�������ṹ��
 * SD6181ƽ̨Ӳ���ź�������ṹ����Ϣ
 */
typedef struct tagTensilicaHwSemErrInfo
{
    UINT8   ucHwSemType;               /**< �����Ӳ���ź������ͣ�GHWSEM_ERR_FLAG(��ʾȫ��)��LHWSEM_ERR_FLAG(��ʾ�ֲ�)*/
    UINT8   ucResvered;                /**< Ԥ��                                                                     */
    UINT16  usResvered;                /**< Ԥ��                                                                     */
    UINT32  uwHwsemErr;                 /**< Ӳ���ź����쳣��Ϣ                                                      */
} HWSEM_ERR_S;

/**
 *@ingroup SRE_exc
 * �Ĵ�����Ϣ�ṹ
 *
 * ����:SD6181&SD6108ƽ̨�µ��쳣����ʱ����ļĴ�����Ϣ��
 *
 * ע��:���¼Ĵ�������ȥ������ǰ׺��uw��������ӦоƬ�ֲ��еļĴ�������
 * �ɽӹܵ��쳣����:���˰���ϵͳ�Դ���64���쳣�⣬�����Խӹ������쳣����
 * #define OS_EXCCAUSE_WRITEERROR           67   //write error�쳣
 * #define OS_EXCCAUSE_ECCERROR             68   //L1 ECC�쳣
 * #define OS_EXCCAUSE_NMIERROR             69   //NMI�ж�
 * #define OS_EXCCAUSE_RESET_REENTRY        70   //��λ���������쳣
 * #define OS_EXCCAUSE_DOUBLEERROR          71   //double�쳣
 * #define OS_EXCCAUSE_FATALERROR           72   //���������쳣
 * #define OS_EXCCAUSE_STACKOVERFLOW        73   //ջԽ���쳣
 * #define OS_EXCCAUSE_HWSEMERROR           74   //Ӳ���ź��������쳣
 * #define OS_EXCCAUSE_INSTRUCTION_BP       75   //ָ��ϵ��쳣
 * #define OS_EXCCAUSE_DATA_BP              76   //���ݶϵ��쳣
 */
typedef struct tagTensilicaExcRegInfo
{
    UINT32 uwPC;            /**< pcָ���ַ                             */
    UINT32 uwPS;            /**< ������״̬                             */
    UINT32 uwEXCCAUSE;      /**< ��һ���쳣����                         */
    UINT32 uwEXCVADDR;      /**< ��һ�ζ�ȡ�����ػ�ת���쳣�������ַ   */
    UINT32 uwLBEG;          /**< ѭ����ʼ��ַ                           */
    UINT32 uwLEND;          /**< ѭ��������ַ                           */
    UINT32 uwLCOUNT;        /**< ѭ���������Ĵ���                       */
    UINT32 uwSAR;           /**< ��λ�Ĵ���                             */
    UINT32 auwA[32];        /**< A��32��ͨ�üĴ���                      */
    UINT32 uwWINDOWBASE;    /**< ĿǰAR REG����λ�üĴ���               */
    UINT32 uwWINDOWSTART;   /**< AR REG����pending�Ĵ���                */
    UINT32 uwDEPC;          /**< double �쳣����Ĵ���                  */
    UINT32 uwBR;            /**< br �Ĵ���                              */
    UINT32 uwEPC1;          /**< lv1 �쳣PC�Ĵ���                       */
    UINT32 uwEPC2;          /**< lv2 �쳣PC�Ĵ���                       */
    UINT32 uwEPC3;          /**< lv3 �쳣PC�Ĵ���                       */
    UINT32 uwEPC4;          /**< lv4 �쳣PC�Ĵ���                       */
    UINT32 uwEPC5;          /**< lv5 �쳣PC�Ĵ���                       */
    UINT32 uwEPC6;          /**< lv6 �쳣PC�Ĵ���                       */
    UINT32 uwEPS2;          /**< lv2 �쳣״̬�Ĵ���                     */
    UINT32 uwEPS3;          /**< lv3 �쳣״̬�Ĵ���                     */
    UINT32 uwEPS4;          /**< lv4 �쳣״̬�Ĵ���                     */
    UINT32 uwEPS5;          /**< lv5 �쳣״̬�Ĵ���                     */
    UINT32 uwEPS6;          /**< lv6 �쳣״̬�Ĵ���                     */
    UINT32 uwEXCSAVE1;      /**< lv1 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE2;      /**< lv2 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE3;      /**< lv3 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE4;      /**< lv4 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE5;      /**< lv5 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE6;      /**< lv6 �쳣����Ĵ���                     */
    UINT32 uwINTENABLE;     /**< �ж�ʹ�ܼĴ���                         */
    UINT32 uwINTERRUPT;     /**< �ж�pending�Ĵ���                      */
    UINT32 uwSCOMPARE1;     /**< �����洢�ȽϼĴ���                     */
    UINT32 uwCCOMPARE0;     /**< �ȽϼĴ���0                            */
    UINT32 uwCCOMPARE1;     /**< �ȽϼĴ���1                            */
    UINT32 uwCCOMPARE2;     /**< �ȽϼĴ���2                            */
    UINT32 uwCCOUNT;        /**< �ȽϼĴ�������ֵ                       */
    UINT32 uwCPENABLE;      /**< Э����ʹ�ܼĴ���                       */
    UINT32 uwVECBASE;       /**< ��̬�������ַ                         */
    UINT32 uwDBREAKA0;      /**< ���ݶϵ��ַ0                          */
    UINT32 uwDBREAKA1;      /**< ���ݶϵ��ַ1                          */
    UINT32 uwDBREAKC0;      /**< ���ݶϵ���ƼĴ���0                    */
    UINT32 uwDBREAKC1;      /**< ���ݶϵ���ƼĴ���1                    */
    UINT32 uwDEBUGCAUSE;    /**< ��һ��debug�쳣ԭ��                    */
    UINT32 uwIBREAK0;       /**< ָ��ϵ��ַ0                          */
    UINT32 uwIBREAK1;       /**< ָ��ϵ��ַ1                          */
    UINT32 uwIBREAKENABLE;  /**< ָ��ϵ�ʹ�ܼĴ���                     */
    UINT32 uwICOUNT;        /**< ָ�������                             */
    UINT32 uwICOUNTLEVEL;   /**< ָ������ȼ���ֵ�Ĵ���                 */
    UINT32 uwReserved;      /**< ��������֤���룬��Ҫȥ��               */
    ECC_REGS_S stEccRegInfo;/**< ECC�쳣����Ĵ�����Ϣ                  */
} EXC_REGS_S;

#elif ((OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220)||(OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 *@ingroup SRE_exc
 * SD6182/SD6157ƽ̨�£������ϱ�����CPU��Ӳ���ź����쳣����¼�ĺ˺Ŵ�С��
 */
#define  HWSEM_ERR_DEFAULT_CORE            0xff

/**
 *@ingroup SRE_exc
 *SD6182/SD6157ƽ̨�·���ȫ��Ӳ���ź����쳣��־��
 */
#define  GHWSEM_ERR_FLAG                   0x1

/**
 *@ingroup SRE_exc
 *SD6182/SD6157ƽ̨�·����ֲ�Ӳ���ź����쳣��־��
 */
#define  LHWSEM_ERR_FLAG                   0x2

/**
 * @ingroup SRE_exc
 * Ӳ���ź���������Ϣ���͡�
 * SD6182/SD6157�Ĵ���ṹ����Ϣ��
 */
typedef enum tagTensilicaHwSemErrType
{
    OS_HWSEM_ERR_PEND_IN_QUEUE_SEM    = 1,      /**< �����ڶ����м��������ȡ                       */
    OS_HWSEM_ERR_PEND_BUSY_SEM        = 2,      /**< �����ȡ�Ѿ���ȡ�����ź���                     */
    OS_HWSEM_ERR_POST_OTHER_CORE_SEM  = 3,      /**< �ͷ�����cpuռ�õ��ź���                        */
    OS_HWSEM_ERR_CPU_ID_INVALID       = 4,      /**< ������ͷ��ź�����cpu idԽ��                   */
    OS_HWSEM_ERR_READ_DIRECT_REG      = 5,      /**< �ǲ�ѯģʽ�¶�Direct�Ĵ���                     */
    OS_HWSEM_ERR_WRITE_INDIRECT_REG   = 6,      /**< �Ƕ���ģʽ��дInDirect�Ĵ���                   */
    OS_HWSEM_ERR_WRITE_COMBINED_REG   = 7,      /**< �����ģʽ��дCombined�Ĵ���                   */
    OS_HWSEM_ERR_OPERATE_CNT_REG      = 8,      /**< δʹ�ܼ���ģʽ���Լ���ģʽ�Ĵ������з��ʲ���   */
    OS_HWSEM_ERR_CNT_UNDER_RUN        = 9,      /**< ������under-run�쳣                            */
    OS_HWSEM_ERR_OPERATE_CNT_EN_REG   = 10      /**< �ǵݼ�����ģʽ�£��Լ���ģʽʹ�ܼĴ������з��� */
} HWSEM_ERR_TYPE_E;

/**
 * @ingroup SRE_exc
 * Ӳ���ź�������ṹ�塣
 * SD6182/SD6157�Ĵ���ṹ����Ϣ��
 */
typedef struct tagTensilicaHwSemErrInfo
{
    UINT8  ucHwSemType;               /**< �����Ӳ���ź������ͣ�GHWSEM_ERR_FLAG(��ʾȫ��)��LHWSEM_ERR_FLAG(��ʾ�ֲ�)*/
    UINT8  ucHwsemClustId;            /**< ��ID�������Ӳ���ź�������Ϊ�ֲ�ʱ��Ч                                    */
    UINT8  ucHwSemId;                 /**< �����Ӳ���ź���ID                                                        */
    UINT8  ucHwsemCoreId;             /**< ����Ӳ���ź�������ĺ˺ţ���ЧʱΪ#HWSEM_ERR_DEFAULT_CORE                 */
    HWSEM_ERR_TYPE_E  enHwsemErrTpye; /**< Ӳ���ź����Ĵ�������                                                      */
} HWSEM_ERR_S;

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:AXI����slverr����
 */
#define MSGM_EXC_TYPE_AXI_SLVERR     0

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:AXI����decerr����
 */
#define MSGM_EXC_TYPE_AXI_DECERR     1

/**
 *@ingroup SRE_exc
 *SD6182 MSGM�쳣����:LSI���ߴ���
 */
#define MSGM_EXC_TYPE_LSI_ERR        2

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:filter������Ϣ������ʧ����, ��ǰ���ӹܡ�
 */
#define MSGM_EXC_TYPE_DBG_LOST       3

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:������Ϣ�����������
 */
#define MSGM_EXC_TYPE_NOR_OV         4

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:������Ϣ���������ʧ����
 */
#define MSGM_EXC_TYPE_NOR_OV_LOST    5

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:������Ϣ����creditʧ�����
 */
#define MSGM_EXC_TYPE_CRED_MM        8

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:������Ϣ�����������
 */
#define MSGM_EXC_TYPE_SH_OV          9

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:ͬ�����������Ϣ�Ƿ�����
 */
#define MSGM_EXC_TYPE_SYNC_ERR      12

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:ͬ��������Ϣ����������ʧ����
 */
#define MSGM_EXC_TYPE_SYNC_LOST     13

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM�쳣����:ͬ����Ϣ���г�ʱ����
 */
#define MSGM_EXC_TYPE_SYNC_TOT      14

/*
 *@ingroup SRE_exc
 * �Ĵ�����Ϣ�ṹ
 *
 * ����:SD6182/SD6157ƽ̨�µ��쳣����ʱ�����MSGM�쳣�Ĵ�����Ϣ��
*/
typedef struct tagMsgmExcInfo
{
    UINT8   ucExcMsgm;              /**< �쳣MSGM��ʶ��0��ʾGMSGM��1��ʾLMSGM */
    UINT8   ucExcType;              /**< MSGM�쳣���� */
    UINT8   ucSynTotQue;            /**< ͬ����Ϣ��ʱ����ID���쳣����ΪMSGM_EXC_TYPE_SYNC_TOTʱ��¼ */
    UINT8   ucSynErrMsgQue;         /**< ͬ����Ϣ��Ч����ID���쳣����ΪMSGM_EXC_TYPE_SYNC_ERRʱ��¼ */
    UINT32  uwSynErrMsgData;        /**< ͬ����Ϣ��Ч��32bit���ݣ��쳣����ΪMSGM_EXC_TYPE_SYNC_ERRʱ��¼ */
    UINT8   ucNorOvCnt;             /**< ��ͨ��Ϣ����������쳣����ΪMSGM_EXC_TYPE_NOR_OVʱ��¼ */
    UINT8   ucNorOvCore;            /**< ��ͨ��Ϣ�����Ӧ�˺ţ��쳣����ΪMSGM_EXC_TYPE_NOR_OVʱ��¼ */
    UINT8   ucNorOvQport;           /**< ��ͨ��Ϣ�����ӦQPort��ţ��쳣����ΪMSGM_EXC_TYPE_NOR_OVʱ��¼ */
    UINT8   ucNorOvQue;             /**< ��ͨ��Ϣ�����Ӧ���б�ţ��쳣����ΪMSGM_EXC_TYPE_NOR_OVʱ��¼ */
    UINT32  uwNorOvPtr;             /**< ��ͨ��Ϣ�������ָ�룬�쳣����ΪMSGM_EXC_TYPE_NOR_OV�������������������ʱ��¼ */
    UINT8   ucShOvQue;              /**< ������Ϣ�������ID���쳣����ΪMSGM_EXC_TYPE_SH_OVʱ��¼ */
    UINT8   ucSynLostQue;           /**< ͬ����Ϣ������ʧ����ID���쳣����ΪMSGM_EXC_TYPE_SYNC_LOSTʱ��¼ */
    UINT8   ucNorOvLostCnt;         /**< ��ͨ��Ϣ���������ʧ�������쳣����ΪMSGM_EXC_TYPE_NOR_OV_LOSTʱ��¼ */
    UINT8   ucNorOvLostQue;         /**< ��ͨ��Ϣ���������ʧ�ĵ�һ�����кţ��쳣����ΪMSGM_EXC_TYPE_NOR_OV_LOSTʱ��¼ */
    UINT32  uwCreditVioError;       /**< ��ͨ��ϢCredit��ƥ����Ϣ(�Ĵ���MSGM_CRED_VIO), �쳣����ΪMSGM_EXC_TYPE_CRED_MMʱ��¼  */
    UINT32  uwLsiVioBusError;       /**< LSI���ߴ�������ͼ�¼(�Ĵ���MSGM_LSI_VIO), �쳣����ΪMSGM_EXC_TYPE_LSI_ERRʱ��¼  */
    UINT32  uwLsiVioBusErrorAddr;   /**< LSI���ߴ���ʱ�ķ��ʵ�ַ(�Ĵ���MSGM_LSI_VIO_ADDR),�쳣����ΪMSGM_EXC_TYPE_LSI_ERRʱ��¼ */
}MSGM_EXC_INFO_S;

/**
 *@ingroup SRE_exc
 * �Ĵ�����Ϣ�ṹ
 *
 * ����:SD6182/SD6157ƽ̨�µ��쳣����ʱ����ļĴ�����Ϣ��
 *
 * ע��:���¼Ĵ�������ȥ������ǰ׺��uw��������ӦоƬ�ֲ��еļĴ�������
 * �ɽӹܵ��쳣����:���˰���ϵͳ�Դ���64���쳣�⣬�����Խӹ������쳣����
 * #define OS_EXCCAUSE_WRITEERROR           67   //write error�쳣
 * #define OS_EXCCAUSE_ECCERROR             68   //���� ECC�쳣
 * #define OS_EXCCAUSE_NMIERROR             69   //NMI�ж�
 * #define OS_EXCCAUSE_RESET_REENTRY        70   //��λ���������쳣
 * #define OS_EXCCAUSE_DOUBLEERROR          71   //double�쳣
 * #define OS_EXCCAUSE_FATALERROR           72   //���������쳣
 * #define OS_EXCCAUSE_STACKOVERFLOW        73   //ջԽ���쳣
 * #define OS_EXCCAUSE_HWSEMERROR           74   //Ӳ���ź����쳣
 * #define OS_EXCCAUSE_INSTRUCTION_BP       75   //ָ��ϵ��쳣
 * #define OS_EXCCAUSE_DATA_BP              76   //���ݶϵ��쳣
 * #define OS_EXCCAUSE_HACERROR             77   //HAC�쳣
 * #define OS_EXCCAUSE_MSGM_ERROR           78   //Msgm�����쳣
 * #define OS_EXCCAUSE_MSGQBUSERROR         79   //msgQ bus err�쳣
 */
typedef struct tagTensilicaExcRegInfo
{
    UINT32 uwPC;            /**< pcָ���ַ                             */
    UINT32 uwPS;            /**< ������״̬                             */
    UINT32 uwEXCCAUSE;      /**< ��һ���쳣����                         */
    UINT32 uwEXCVADDR;      /**< ��һ�ζ�ȡ�����ػ�ת���쳣�������ַ   */
    UINT32 uwLBEG;          /**< ѭ����ʼ��ַ                           */
    UINT32 uwLEND;          /**< ѭ��������ַ                           */
    UINT32 uwLCOUNT;        /**< ѭ���������Ĵ���                       */
    UINT32 uwSAR;           /**< ��λ�Ĵ���                             */
    UINT32 auwA[64];        /**< A��64��ͨ�üĴ���                      */
    UINT32 uwWINDOWBASE;    /**< ĿǰAR REG����λ�üĴ���               */
    UINT32 uwWINDOWSTART;   /**< AR REG����pending�Ĵ���                */
    UINT32 uwDEPC;          /**< double �쳣����Ĵ���                  */
    UINT32 uwBR;            /**< br �Ĵ���                              */
    UINT32 uwEPC1;          /**< lv1 �쳣PC�Ĵ���                       */
    UINT32 uwEPC2;          /**< lv2 �쳣PC�Ĵ���                       */
    UINT32 uwEPC3;          /**< lv3 �쳣PC�Ĵ���                       */
    UINT32 uwEPC4;          /**< lv4 �쳣PC�Ĵ���                       */
    UINT32 uwEPC5;          /**< lv5 �쳣PC�Ĵ���                       */
    UINT32 uwEPS2;          /**< lv2 �쳣״̬�Ĵ���                     */
    UINT32 uwEPS3;          /**< lv3 �쳣״̬�Ĵ���                     */
    UINT32 uwEPS4;          /**< lv4 �쳣״̬�Ĵ���                     */
    UINT32 uwEPS5;          /**< lv5 �쳣״̬�Ĵ���                     */
    UINT32 uwEXCSAVE1;      /**< lv1 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE2;      /**< lv2 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE3;      /**< lv3 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE4;      /**< lv4 �쳣����Ĵ���                     */
    UINT32 uwEXCSAVE5;      /**< lv5 �쳣����Ĵ���                     */
    UINT32 uwINTENABLE;     /**< �ж�ʹ�ܼĴ���                         */
    UINT32 uwINTERRUPT;     /**< �ж�pending�Ĵ���                      */
    UINT32 uwCCOMPARE0;     /**< �ȽϼĴ���0                            */
    UINT32 uwCCOMPARE1;     /**< �ȽϼĴ���1                            */
    UINT32 uwCCOUNT;        /**< �ȽϼĴ�������ֵ                       */
    UINT32 uwCPENABLE;      /**< Э����ʹ�ܼĴ���                       */
    UINT32 uwVECBASE;       /**< ��̬�������ַ                         */
    UINT32 uwDBREAKA0;      /**< ���ݶϵ��ַ0                          */
    UINT32 uwDBREAKA1;      /**< ���ݶϵ��ַ1                          */
    UINT32 uwDBREAKC0;      /**< ���ݶϵ���ƼĴ���0                    */
    UINT32 uwDBREAKC1;      /**< ���ݶϵ���ƼĴ���1                    */
    UINT32 uwDEBUGCAUSE;    /**< ��һ��debug�쳣ԭ��                    */
    UINT32 uwIBREAK0;       /**< ָ��ϵ��ַ0                          */
    UINT32 uwIBREAK1;       /**< ָ��ϵ��ַ1                          */
    UINT32 uwIBREAKENABLE;  /**< ָ��ϵ�ʹ�ܼĴ���                     */
    UINT32 uwICOUNT;        /**< ָ�������                             */
    UINT32 uwICOUNTLEVEL;   /**< ָ������ȼ���ֵ�Ĵ���                 */
    UINT32 uwResvered0;     /**< ���뱣��,����ȥ�����м�                */
    ECC_REGS_S stEccRegInfo;/**< ECC�쳣����Ĵ�����Ϣ                  */
} EXC_REGS_S;

#elif (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
typedef struct tagAXExcRegInfo
{
    UINT32 uwCPSR;  /**< CPSR����״̬�Ĵ���������Ԥȡָ���쳣ʱ������Ӳ�����Ƶ����⣬�˼Ĵ�����T��־λ�ᱻ��Ϊ1                        */
    UINT32 uwSCTLR; /**< �쳣ʱ��SCTLR�Ĵ���                                                                                           */
    UINT32 uwDFAR;  /**< �쳣ʱ��DFAR�Ĵ���                                                                                            */
    UINT32 uwDFSR;  /**< �쳣ʱ��DFSR�Ĵ���                                                                                            */
    UINT32 uwIFSR;  /**< �쳣ʱ��IFSR�Ĵ���                                                                                            */
    UINT32 uwR0;    /**< RO�Ĵ���                                                                                                      */
    UINT32 uwR1;    /**< R1�Ĵ���                                                                                                      */
    UINT32 uwR2;    /**< R2�Ĵ���                                                                                                      */
    UINT32 uwR3;    /**< R3�Ĵ���                                                                                                      */
    UINT32 uwR4;    /**< R4�Ĵ���                                                                                                      */
    UINT32 uwR5;    /**< R5�Ĵ���                                                                                                      */
    UINT32 uwR6;    /**< R6�Ĵ���                                                                                                      */
    UINT32 uwR7;    /**< R7�Ĵ���                                                                                                      */
    UINT32 uwR8;    /**< R8�Ĵ���                                                                                                      */
    UINT32 uwR9;    /**< R9�Ĵ���                                                                                                      */
    UINT32 uwR10;   /**< R1O�Ĵ���                                                                                                     */
    UINT32 uwR11;   /**< R11�Ĵ���                                                                                                     */
    UINT32 uwR12;   /**< R12�Ĵ���                                                                                                     */
    UINT32 uwSP;    /**< ����ջָ��                                                                                                    */
    UINT32 uwLR;    /**< ���򷵻ص�ַ�����쳣ʱ����һ��ָ�������������쳣�����������쳣��ջԽ���쳣ʱ������Ӳ���������⣬��ֵ��׼ȷ*/
    UINT32 uwPC;    /**< �쳣ʱ��PCָ��(Ԥȡָ���쳣ʱ����¼��4�ֽڶ��봦������һ��ָ���ַ�������쳣ʱ����¼�쳣ʱ��PCֵ)           */
}EXC_REGS_S;

/**
 *@ingroup SRE_exc
 *Cortex-AX�쳣��������:�Ƿ�ָ���쳣��
 */
#define OS_EXCEPT_UNDEF_INSTR      1

/**
 *@ingroup SRE_exc
 *Cortex-AX�쳣��������:��������쳣��
 */
#define OS_EXCEPT_SWI              2

/**
 *@ingroup SRE_exc
 *Cortex-AX�쳣��������:Ԥȡָ���쳣��
 */
#define OS_EXCEPT_PREFETCH_ABORT   3

/**
 *@ingroup SRE_exc
 *Cortex-AX�쳣��������:������ֹ�쳣��
 */
#define OS_EXCEPT_DATA_ABORT       4

/**
 *@ingroup SRE_exc
 *Cortex-AX�쳣��������:�����ж��쳣��
 */
#define OS_EXCEPT_FIQ              5

/**
 *@ingroup SRE_exc
 *Cortex-AX�쳣��������:���������쳣��
 */
#define OS_EXCEPT_FATALERROR       6

/**
 *@ingroup SRE_exc
 *Cortex-AX�쳣��������:ջԽ���쳣��
 */
#define OS_EXCEPT_STACKOVERFLOW    7

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:������Ϣ�����������
 */
#define MSGM_EXC_TYPE_NOR_OV            0

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:������Ϣ���������ʧ����
 */
#define MSGM_EXC_TYPE_NOR_OV_LOST       1

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:������Ϣ����creditʧ�����
 */
#define MSGM_EXC_TYPE_CRED_MM           2

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:������Ϣ�����������
 */
#define MSGM_EXC_TYPE_SH_OV             3

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:ͬ�����������Ϣ�Ƿ�����
 */
#define MSGM_EXC_TYPE_SYNC_ERR          4

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:ͬ����Ϣ���г�ʱ����
 */
#define MSGM_EXC_TYPE_SYNC_TOT          5

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:AXI����decerr����
 */
#define MSGM_EXC_TYPE_AXI_DECERR        6

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:AXI����slverr����
 */
#define MSGM_EXC_TYPE_AXI_SLVERR        7

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:LSI���ߴ���
 */
#define MSGM_EXC_TYPE_LSI_ERR           8

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:LSI����vmid��lockȨ�޴���
 */
#define MSGM_EXC_TYPE_LSI_VMLOCK_ERR    9

/**
 *@ingroup SRE_exc
 *SD6183 MSGM�쳣����:ͬ��������Ϣ����������ʧ����
 */
#define MSGM_EXC_TYPE_SYNC_LOST         14

/*
 *@ingroup SRE_exc
 * �Ĵ�����Ϣ�ṹ
 *
 * ����:SD6183ƽ̨�µ��쳣����ʱ�����MSGM�쳣�Ĵ�����Ϣ��
*/
typedef struct tagMsgmExcInfo
{
    UINT8   ucExcMsgm;              /**< �쳣MSGM��ʶ��0��ʾGMSGM��1��ʾLMSGM */
    UINT8   ucExcType;              /**< MSGM�쳣���� */
    UINT8   ucSynTotQue;            /**< ͬ����Ϣ��ʱ����ID���쳣����ΪMSGM_EXC_TYPE_SYNC_TOTʱ��¼ */
    UINT8   ucSynErrMsgQue;         /**< ͬ����Ϣ��Ч����ID���쳣����ΪMSGM_EXC_TYPE_SYNC_ERRʱ��¼ */
    UINT32  uwSynErrMsgData;        /**< ͬ����Ϣ��Ч��32bit���ݣ��쳣����ΪMSGM_EXC_TYPE_SYNC_ERRʱ��¼ */
    UINT8   ucNorOvCnt;             /**< ��ͨ��Ϣ����������쳣����ΪMSGM_EXC_TYPE_NOR_OVʱ��¼ */
    UINT8   ucNorOvCore;            /**< ��ͨ��Ϣ�����Ӧ�˺ţ��쳣����ΪMSGM_EXC_TYPE_NOR_OVʱ��¼ */
    UINT8   ucNorOvQport;           /**< ��ͨ��Ϣ�����ӦQPort��ţ��쳣����ΪMSGM_EXC_TYPE_NOR_OVʱ��¼ */
    UINT8   ucNorOvQue;             /**< ��ͨ��Ϣ�����Ӧ���б�ţ��쳣����ΪMSGM_EXC_TYPE_NOR_OVʱ��¼ */
    UINT32  uwNorOvPtr;             /**< ��ͨ��Ϣ�������ָ�룬�쳣����ΪMSGM_EXC_TYPE_NOR_OV�������������������ʱ��¼ */
    UINT8   ucShOvQue;              /**< ������Ϣ�������ID���쳣����ΪMSGM_EXC_TYPE_SH_OVʱ��¼ */
    UINT8   ucSynLostQue;           /**< ͬ����Ϣ������ʧ����ID���쳣����ΪMSGM_EXC_TYPE_SYNC_LOSTʱ��¼ */
    UINT8   ucNorOvLostCnt;         /**< ��ͨ��Ϣ���������ʧ�������쳣����ΪMSGM_EXC_TYPE_NOR_OV_LOSTʱ��¼ */
    UINT8   ucNorOvLostQue;         /**< ��ͨ��Ϣ���������ʧ�ĵ�һ�����кţ��쳣����ΪMSGM_EXC_TYPE_NOR_OV_LOSTʱ��¼ */
    UINT32  uwCreditVioError;       /**< ��ͨ��ϢCredit��ƥ����Ϣ(�Ĵ���MSGM_CRED_VIO), �쳣����ΪMSGM_EXC_TYPE_CRED_MMʱ��¼  */
    UINT32  uwLsiVioBusError;       /**< LSI���ߴ�������ͼ�¼(�Ĵ���MSGM_LSI_VIO), �쳣����ΪMSGM_EXC_TYPE_LSI_ERRʱ��¼  */
    UINT32  uwLsiVioBusErrorAddr;   /**< LSI���ߴ���ʱ�ķ��ʵ�ַ(�Ĵ���MSGM_LSI_VIO_ADDR),�쳣����ΪMSGM_EXC_TYPE_LSI_ERRʱ��¼ */
    UINT32  uwLsiVioBusErrorID;     /**< LSI���߷��������������ID��vmid(�Ĵ���MSGM_LSI_VIO_ID) */
    UINT32  uwLsiVioVMLock;         /**< LSIȨ���쳣��������(�Ĵ���MSGM_LSI_VMLOCK_VIO) */
    UINT32  uwLsiVioVMLockAddr;     /**< LSI����vmid����lockȨ�޷�����������ַ(�Ĵ���MSGM_LSI_VMLOCKVIO_ADDR) */
    UINT32  uwLsiVioVMLockID;       /**< LSI����vmid����lockȨ�޷��������������ID��vmid(�Ĵ���MSGM_LSI_VMLOCKVIO_ID) */
}MSGM_EXC_INFO_S;

/**
 *@ingroup SRE_exc
 * HIDSP�쳣�Ĵ�����Ϣ�ṹ
 *
 *
 */
typedef struct tagExcRegInfo
{
    UINT32  uwUSP;         /* �����쳣ǰ��USP�Ĵ���ֵ                      */
    UINT32  uwSP;          /* �����쳣ǰ��SSP�Ĵ���ֵ                      */
    UINT32  uwISR;         /* �����쳣����쳣���ISR�Ĵ���ֵ              */
    UINT32  uwEMADDR;      /* �����쳣���EMADDR�Ĵ���ֵ�������쳣�ĵ�ַ   */
    UINT32  uwLBEG0;
    UINT32  uwLEND0;
    UINT32  uwLCOUNT0;
    UINT32  uwPrex1;
    UINT32  uwLBEG1;
    UINT32  uwLEND1;
    UINT32  uwLCOUNT1;
    UINT32  uwCIDR;
    UINT32  auwA[32];
    UINT32  auwV[16][4];
    UINT32  uwBX;
    UINT32  uwCBEGIN;
    UINT32  uwCEND;
    UINT32  uwPrex2;
    UINT32  uwPC;          /* �����쳣�ֳ���PC�Ĵ���ֵ     */
    UINT32  uwPreSR;       /* �����쳣ǰ��SR�Ĵ���ֵ       */
    UINT32  uwPreISR;      /* �����쳣ǰ��ISR�Ĵ���ֵ      */
    UINT32  uwPreEmaddr;   /* �����쳣ǰ��Emaddr�Ĵ���ֵ   */
}EXC_REGS_S;

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LDP,ȡ����cache��żУ�����
 */
#define OS_DATA_LOAD_ERR_LDP        0

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LDT,ȡ����cache tag��żУ�����
 */
#define OS_DATA_LOAD_ERR_LDT        1

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LSL,ȡ�������ݴ���(SLVERR)��
 */
#define OS_DATA_LOAD_ERR_LSL        2

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LDE,ȡ���ݶ�����ַ����(DECERR)��
 */
#define OS_DATA_LOAD_ERR_LDE        3

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LEE,ȡ����ר�ô���
 */
#define OS_DATA_LOAD_ERR_LEE        4

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LUM,ȡ���ݷǶ������
 */
#define OS_DATA_LOAD_ERR_LUM        5

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LMH,MMU�������д���
 */
#define OS_DATA_LOAD_ERR_LMH        6

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LMT,ȡ����MMU����tag(����TLBУ��Ҳ�����ڸ��쳣����)��żУ�����
 */
#define OS_DATA_LOAD_ERR_LMT        7

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LPF,MMUҳ����
 */
#define OS_DATA_LOAD_ERR_LPF        8

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LPV, MMU��Ȩ��Υ�档
 */
#define OS_DATA_LOAD_ERR_LPV        9

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LXS,ȡ����MMU AXI�������ݴ���(SLVERR)��
 */
#define OS_DATA_LOAD_ERR_LXS        10

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LXD,ȡ����MMU AXI������ַ����(DECERR)��
 */
#define OS_DATA_LOAD_ERR_LXD        11

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LMU,ȡ���ݲ�֧�ֵ�MMUҳ��С����
 */
#define OS_DATA_LOAD_ERR_LMU        12

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_LOAD_ERR, ȡ�����쳣
 *HIDSP�쳣��������:LMP,MPU����
 */
#define OS_DATA_LOAD_ERR_LMP        13

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SUM, �����ݷǶ����ڴ����
 */
#define OS_DATA_STORE_MMU_ERR_SUM   14

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SMH, MMU�������д���
 */
#define OS_DATA_STORE_MMU_ERR_SMH   15

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SIM, ��ʽѹջʱ������MMU����
 */
#define OS_DATA_STORE_MMU_ERR_SIM   16

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SPF, MMUҳ����
 */
#define OS_DATA_STORE_MMU_ERR_SPF   17

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SPV, MMU��Ȩ��Υ�档
 */
#define OS_DATA_STORE_MMU_ERR_SPV   18

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SXS, ������MMU AXI�������ݴ���(SLVERR)��
 */
#define OS_DATA_STORE_MMU_ERR_SXS   19

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SXD, ������MMU AXI������ַ����(DECERR)��
 */
#define OS_DATA_STORE_MMU_ERR_SXD   20

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SMT, ������MMU����tag(����TLBУ��Ҳ�����ڸ��쳣����)��żУ�����
 */
#define OS_DATA_STORE_MMU_ERR_SMT   21

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DATA_STORE_MMU_ERR, ������MMU�쳣
 *HIDSP�쳣��������:SMU, �����ݲ�֧�ֵ�MMUҳ��С����
 */
#define OS_DATA_STORE_MMU_ERR_SMU   22

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_ILLEGAL, �Ƿ�ָ���쳣
 *HIDSP�쳣��������:IOP, �Ƿ�������-δ����Ĳ�������������Ƿ�ָ�
 */
#define OS_ILLEGAL_IOP              23

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_ILLEGAL, �Ƿ�ָ���쳣
 *HIDSP�쳣��������:IIT, ʹ�÷Ƿ���ָ��������͡�
 */
#define OS_ILLEGAL_IIT              24

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_ILLEGAL, �Ƿ�ָ���쳣
 *HIDSP�쳣��������:IIO, ʹ�÷Ƿ���ָ���������
 */
#define OS_ILLEGAL_IIO              25

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_ILLEGAL, �Ƿ�ָ���쳣
 *HIDSP�쳣��������:IIC, VLIW��ʹ���˷Ƿ���ָ����ϡ�
 */
#define OS_ILLEGAL_IIC              26

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_ILLEGAL, �Ƿ�ָ���쳣
 *HIDSP�쳣��������:IVO, �Ƿ���VLIW��ʼ��ַ��VLIW��ʼ��ַ����Ϊ3�ı�����
 */
#define OS_ILLEGAL_IVO              27

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_ILLEGAL, �Ƿ�ָ���쳣
 *HIDSP�쳣��������:IVW, �Ƿ�VLIW�Ŀ��-VLIW̫��
 */
#define OS_ILLEGAL_IVW              28

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PPE, ָ��cache��żУ�����
 */
#define OS_PFETCHERR_PPE            29

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PMT, ָ��MMU����tag��żУ�����
 */
#define OS_PFETCHERR_PMT            30

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PFB, ������ߴ���
 */
#define OS_PFETCHERR_PFB            31

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PTP, ָ��tag��żУ�����
 */
#define OS_PFETCHERR_PTP            32

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PMH, MMU�������д���
 */
#define OS_PFETCHERR_PMH            33

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PPF, MMUҳ����
 */
#define OS_PFETCHERR_PPF            34

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PPV, MMU��Ȩ��Υ�档
 */
#define OS_PFETCHERR_PPV            35

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PXS, ����MMU AXI�������ݴ���(SLVERR)��
 */
#define OS_PFETCHERR_PXS            36

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PXD, ����MMU AXI��ַ����(DECERR)��
 */
#define OS_PFETCHERR_PXD            37

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PPS, MMU��֧�ֵ�ҳ��С����
 */
#define OS_PFETCHERR_PPS            38

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PMP, MPU����
 */
#define OS_PFETCHERR_PMP            39

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PRIVILEGE_ERR, Ȩ���쳣
 *HIDSP�쳣��������:����Ȩģʽ��������Ȩģʽ����Դ��Ȩ�޴���
 */
#define OS_PRIVILEGE_ERR_PER        40

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DIV_ZERO_ERR, ��0�쳣
 *HIDSP�쳣��������:����Ϊ0���쳣��
 */
#define OS_DIV_ZERO_ERR_ZDE         41

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_DEBUG_EXCP, debug�쳣
 *HIDSP�쳣��������:debug�쳣��
 */
#define OS_DEBUG_EXCP_DBG           42

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_SYSCALL, syscall�쳣
 *HIDSP�쳣��������:syscall�쳣��
 */
#define OS_SYSCALL_SYS              43

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_CPENABLE_PRO, ʸ���Ĵ����쳣
 *HIDSP�쳣��������:ʸ���Ĵ����쳣��
 */
#define OS_CPENABLE_PRO_CSP         44

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_MSG_QUE_ERR, MSGQ�쳣
 *HIDSP�쳣��������:MSGQ�쳣��
 */
#define OS_MSG_QUE_ERR_MSA          45

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_MSG_QUE_ERR, MSGQ�쳣
 *HIDSP�쳣��������:�����ڵ���Ϣ������
 */
#define OS_MSG_QUE_ERR_MSC          46

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_PFETCH_ERR, Ԥȡָ���쳣
 *HIDSP�쳣��������:PFS, ָ��ԤȡL2��ַ����(DECERR)��
 */
#define OS_PFETCHERR_PFS            47

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_FATALERROR, ���������쳣
 *HIDSP�쳣��������:����OS���������쳣��
 */
#define OS_EXCCAUSE_FATALERROR      48

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_STACKOVERFLOW, ջԽ���쳣
 *HIDSP�쳣��������:��������ջԽ���쳣��
 */
#define OS_EXCCAUSE_STACKOVERFLOW   49

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_NMIERROR, NMI�ж�
 *HIDSP�쳣��������:NMI�жϡ�
 */
#define OS_EXCCAUSE_NMIERROR        69

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_PCC_ERROR, PCC�����쳣
 *HIDSP�쳣��������:PCC�����쳣��
 */
#define OS_EXCCAUSE_PCC_ERROR               70

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_DCC_ERROR, DCC�����쳣
 *HIDSP�쳣��������:DCC�����쳣��
 */
#define OS_EXCCAUSE_DCC_ERROR               71

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_MMU_ERROR, MMU�����쳣
 *HIDSP�쳣��������:MMU�����쳣��
 */
#define OS_EXCCAUSE_MMU_ERROR               72
/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_HWSEMERROR, Ӳ���ź����쳣��
 *HIDSP�쳣��������:Ӳ���ź����쳣��
 */
#define OS_EXCCAUSE_HWSEMERROR      74

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_MSGM_ERROR, MSGM�����쳣
 *HIDSP�쳣��������:MSGM�쳣��
 */
#define OS_EXCCAUSE_MSGM_ERROR      78

/**
 *@ingroup SRE_exc
 *HIDSP�쳣����:OS_EXCCAUSE_MCHWTMRERROR, ȫ��Ӳ����ʱ�������쳣
 *HIDSP�쳣��������:ȫ��Ӳ����ʱ���쳣��
 */
#define OS_EXCCAUSE_MCHWTMRERROR    80

/**
 *@ingroup SRE_exc
 * SD6183ƽ̨�£����ڲ���ʶ��CPU ID��Ӳ���ź����쳣��¼�ĺ˺š�
 */
#define  HWSEM_ERR_DEFAULT_CORE            0xff

/**
 *@ingroup SRE_exc
 *SD6183ƽ̨�·���ȫ��Ӳ���ź����쳣��־��
 */
#define  GHWSEM_ERR_FLAG                   0x1

/**
 *@ingroup SRE_exc
 *SD6183ƽ̨�·����ֲ�Ӳ���ź����쳣��־��
 */
#define  LHWSEM_ERR_FLAG                   0x2

/**
 * @ingroup SRE_exc
 * Ӳ���ź�����¼�Ĵ�����Ϣ���ͣ�1-6��6�֣�HWSEM_ERR_S�е�ucHwsemErrTpye��¼��
 * SD6183�Ĵ���ṹ����Ϣ��
 */
typedef enum tagHiDSPHwSemErrType
{
    OS_HWSEM_ERR_PEND_IN_QUEUE_SEM    = 1,      /**< �����ڶ����м��������ȡ                          */
    OS_HWSEM_ERR_PEND_BUSY_SEM        = 2,      /**< �����ȡ�Ѿ���ȡ�����ź���                        */
    OS_HWSEM_ERR_POST_OTHER_CORE_SEM  = 3,      /**< �ͷ�����cpuռ�õ��ź���                           */
    OS_HWSEM_ERR_CPUID_OVERFLOW       = 4,      /**< ������ͷŵ�CPUIDԽ��                             */
    OS_HWSEM_ERR_READ_DIRECT_REG      = 5,      /**< �ǲ�ѯģʽ�¶�Direct�Ĵ���                        */
    OS_HWSEM_ERR_WRITE_INDIRECT_REG   = 6,      /**< �Ƕ���ģʽ��дInDirect�Ĵ���                      */
} HWSEM_ERR_TYPE_E;

/**
 * @ingroup SRE_exc
 * Ӳ���ź�����¼��COMM�������Ϣ���ͣ���bit��λ�������ж��bit�����ϣ�HWSEM_ERR_S�е�ucHwsemCommErrTpye��¼��
 * SD6183�Ĵ���ṹ����Ϣ��
 */
typedef enum tagHiDSPHwSemCommErrType
{
    OS_HWSEM_ERR_1BIT_ECC             = 0,   /**< Bit0��λ��ʾ:���л������ģʽ�£��洢������CPU ID 1bit ECC���� */
    OS_HWSEM_ERR_2BIT_ECC             = 1,   /**< Bit1��λ��ʾ:���л������ģʽ�£��洢������CPU ID 2bit ECC���� */
    OS_HWSEM_ERR_SW_ACCESS_VMID       = 2,   /**< Bit2��λ��ʾ:������ʵ�VMID����                                */
    OS_HWSEM_ERR_CPU_ID_INVALID       = 3,   /**< Bit3��λ��ʾ:����ʶ��CPUID���ź�������                         */
    OS_HWSEM_ERR_WRITE_LOCK_REG       = 4,   /**< Bit4��λ��ʾ:Lock�����д��lock�����Ĵ���                      */
}HWSEM_ERR_COMM_TYPE_E;

typedef struct tagHiDSPHwSemErrInfo
{
    UINT8  ucHwSemType;               /**< �����Ӳ���ź������ͣ�GHWSEM_ERR_FLAG(��ʾȫ��)��LHWSEM_ERR_FLAG(��ʾ�ֲ�)*/
    UINT8  ucHwsemClustId;            /**< ��ID�������Ӳ���ź�������Ϊ�ֲ�ʱ��Ч                                    */
    UINT8  ucHwSemId;                 /**< �����Ӳ���ź���ID                                                        */
    UINT8  ucHwsemCoreId;             /**< ����Ӳ���ź�������ĺ˺ţ���ЧʱΪ#HWSEM_ERR_DEFAULT_CORE                 */
    UINT8  ucHwsemOwner;              /**< �����Ӳ���ź����ĳ��к˵ĺ˺ţ���ЧʱΪ#HWSEM_ERR_DEFAULT_CORE           */
    UINT8  ucHwsemQueueCPUNum;        /**< �����Ӳ���ź����Ķ����е�CPU����                                         */
    UINT8  ucHwsemErrTpye;            /**< Ӳ���ź�����¼�Ĵ������ͣ�1-6��6�֣� ����SD6183ö��HWSEM_ERR_TYPE_E       */
    UINT8  ucHwsemCommErrTpye;        /**< Ӳ���ź���COMM��������ͣ���bit��¼������SD6183ö��HWSEM_ERR_COMM_TYPE_E  */
} HWSEM_ERR_S;

/**
 * @ingroup SRE_exc
 * ȫ��Ӳ����ʱ����¼�Ĵ�����Ϣ���ͣ�1-3��3�֣�MCHWTMR_EXC_INFO_S�е�uwMcHwtmrErrTpye��¼��
 * SD6183�Ĵ���ṹ����Ϣ��
 */
typedef enum tagMcHwtmrErrType
{
    OS_MCHWTMR_ERR_VMID    = 1,      /**< VMID������               */
    OS_MCHWTMR_ERR_LOCK    = 2,      /**< Υ��LOCK����               */
    OS_MCHWTMR_ERR_VMLOCK  = 3,      /**< VMID��������Υ��LOCK���� */
} MCHWTMR_ERR_TYPE_E;

typedef struct tagMcHwtmrErrInfo
{
    UINT32  uwMcHwtmrErrTpye;        /**< ȫ��Ӳ����ʱ���������ͣ�1-3��3�֣� ����SD6183ö��MCHWTMR_ERR_TYPE_E*/
} MCHWTMR_EXC_INFO_S;

typedef struct tagMcDCCErrInfo
{
    UINT32  uwDccIntStatus;           /**< �����DCC�����ж�״̬*/
    UINT32  uwDccL2WErr;              /**< Data Cache L2 Memory Access Error Attribute Register      */
    UINT32  uwDccEccAddr;             /**< Data Cache ECC Error Address                              */
} DCC_ERR_S;

#endif

#if (OS_OPTION_KERNEL_PROCESS == YES)
/*
 *@ingroup SRE_exc
 *
 *�û����Կ����쳣��Ϣ
 */
typedef struct tageExcListObject
{
    struct tageExcListObject *pstPrev;
    struct tageExcListObject *pstNext;

}EXC_LIST_OBJECT_S;

#endif


typedef struct tagExcInfo
{
    CHAR        acOSVer[OS_SYS_OS_VER_LEN];                  /**< OS�汾��                                         */
    CHAR        acAppVer[OS_SYS_APP_VER_LEN];                /**< ��Ʒ�汾��                                       */
    UINT32      uwExcCause;                                  /**< �쳣ԭ��                                         */

    UINT32      uwThreadType;                                /**< �쳣ǰ���߳�����                                 */
    UINT32      uwThreadID;                                  /**< �쳣ǰ���߳�ID, ��ID���塶TID = LTID | ProcessID | COREID | GTID>*/

#if (OS_OPTION_KERNEL_PROCESS == YES)

    EXC_LIST_OBJECT_S stExcInfoList;                         /**< �����쳣��Ϣ����ָ��                             */

#endif

    UINT16      usByteOrder;                                 /**< �ֽ���                                           */
    UINT16      usCpuType;                                   /**< CPU����                                          */
    UINT32      uwCpuID;                                     /**< CPU ID                                           */
    CPU_TICK    stCpuTick;                                   /**< CPU Tick                                         */
    UINT32      uwNestCnt;                                   /**< �쳣Ƕ�׼���                                     */
    UINT32      uwSp;                                        /**< �쳣ǰջָ��                                     */
    UINT32      uwStackBottom;                               /**< �쳣ǰջ��                                       */
    EXC_REGS_S  stRegInfo;                                   /**< �쳣����ʱ�ĺ��ڼĴ�����������Ϣ��82\57����λ��152�ֽڴ������иĶ��������sre_platform.eh�е�OS_EXC_REGINFO_OFFSET�� */

#if ((OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220)||(OS_HARDWARE_PLATFORM == OS_HACCC))
    CSTK_FRAME_INFO_S   astStackLayer[EXC_CSTK_DEAPTH];      /**< ����ջ�������                                   */
    HWSEM_ERR_S     stHwSemErrInfo;                          /**< Ӳ���ź����쳣����Ĵ�����Ϣ                     */
    MSGM_EXC_INFO_S stMsgmExcInfo;                           /**< MSGM�쳣��Ϣ                                     */
    UINT32          uwMsgqBusErrorCoreId;                    /**< ����msgQ bus error�쳣�ĺ˺�                     */
#endif

#if ((OS_HARDWARE_PLATFORM == OS_RISC170)||(OS_HARDWARE_PLATFORM == OS_DSP170))
    CSTK_FRAME_INFO_S   astStackLayer[EXC_CSTK_DEAPTH];      /**< ����ջ�������                                   */
    HWSEM_ERR_S         stHwSemErrInfo;                      /**< Ӳ���ź����쳣����Ĵ�����Ϣ                     */
    IPC_STATUS_S        auwIpcStatus[8];                     /**< ipc����״̬��ÿ����ֻ��8��mailbox                */
#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
    HWSEM_ERR_S     stHwSemErrInfo;
    DCC_ERR_S       stDccErrInfo;                            /**< DCC������Ϣ                                      */
    MSGM_EXC_INFO_S stMsgmExcInfo;                           /**< MSGM�쳣��Ϣ                                     */
    MCHWTMR_EXC_INFO_S stMcHwtmrExcInfo;                     /**< ȫ��Ӳ����ʱ���쳣��Ϣ                           */
#endif
} EXC_INFO_S;

/**
 *@ingroup SRE_exc
 *@brief �����쳣�Ĵ���״̬�������Ͷ��塣
 *
 *@par ����:
 *�ڵ��˸�λʱ����ִ��ʧ�ܵķ�����Ϣͨ���ù��Ӻ������б��档
 *@attention �ޡ�
 *
 *@param uwState [IN] ����#UINT32���쳣����ĳ�����Ϣ��
 *
 *@retval �ޡ�
 *
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ���
 *@since UniDSP V100R001C01
 *@see ��
 */
typedef VOID (* EXC_STATE_TRACE_HOOK)(UINT32 uwState);

/**
 *@ingroup SRE_exc
 *@brief �������Թ��Ӻ������Ͷ��塣
 *
 *@par ����:
 *ͨ���ú������Ͷ����������Թ��Ӻ�����
 *@attention �ޡ�
 *
 *@param �ޡ�
 *
 *@retval �ޡ�
 *
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ���
 *@since UniDSP V100R001C01
 *@see ��
 */
typedef VOID (* SRE_LASTWORDS_FUNC)(VOID);

/**
 *@ingroup SRE_exc
 *@brief �쳣���������Ͷ��塣
 *
 *@par ����:
 *ͨ���쳣���������Ͷ����쳣���������ӣ���¼�쳣��Ϣ��
 *@attention �ޡ�
 *
 *@param pstExcRegs [IN] ����#EXC_REGS_S *���쳣ʱ�Ĵ�����Ϣ��
 *
 *@retval TRUE��ϵͳ�ڷ����쳣��(��������ش����)������ѭ�����ȴ�������
 *@retval FALSE��ϵͳ�ڷ����쳣��(��������ش����)�������С�
 *
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ���
 *@since UniDSP V100R001C01
 *@see ��
 */
typedef BOOL (* EXC_PROC_FUNC)(EXC_INFO_S *pstExcInfo);

/**
 *@ingroup SRE_exc
 *@brief Hac��ʱ�����쳣���������Ͷ��塣
 *
 *@par ����:
 *ͨ��Hac��ʱ�����쳣���������Ͷ����쳣���������ӣ���Ʒͨ���鿴Hac��ʱ�Ĵ����ж��Ƿ���ڳ�ʱ��������ڳ�ʱ����TRUE(1)����������ڳ�ʱ��˵��ϵͳ�����쳣������FALSE(0),ϵͳ�����쳣�ӹܡ�
 *@attention �ޡ�
 *
 *@param VOID
 *
 *@retval TRUE��ϵͳ��⵽HAC��ʱ������֮��OS���ж϶�������
 *@retval FALSE��ϵͳδ��⵽HAC��ʱ������֮��OS���쳣����
 *
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ���
 *@since UniDSP V200R003C06
 *@see ��
 */
typedef BOOL (* HACTIMEOUT_PROC_FUNC)(VOID);

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 *@ingroup SRE_exc
 *ģ��������Ϣ�ṹ�塣
 */
typedef struct tagExcModInfo
{
    EXC_PROC_FUNC           pfnExcepHook;           /**< �쳣ʱ�û�ע��ĺ�������                    */
    VOID                    *pResetNoLoseMemAddr;  /**< ��λ����ʧ�ڴ����ʼ��ַ                    */
    UINT32                  uwResetNoLoseMemSize;   /**< ��λ����ʧ�ڴ�Ĵ�С                        */
} EXC_MOD_INFO_S;

#else
/**
 *@ingroup SRE_exc
 *ģ��������Ϣ�ṹ�塣
 */
typedef struct tagExcModInfo
{
    HACTIMEOUT_PROC_FUNC    pfnHacExtHook;          /**< Hac�쳣����                                */
    EXC_PROC_FUNC           pfnExcepHook;           /**< �쳣ʱ�û�ע��ĺ�������                    */
    UINT32                  uwStackSize;            /**< �����쳣ʱ�����ջ�Ĵ�С                    */
    VOID                    *pDoubleExcStackStart;  /**< DoubleException��ջ��ʼ��ַ                */
    UINT32                  uwDoubleExcStackSize;   /**< DoubleException��ջ��С                    */
} EXC_MOD_INFO_S;
#endif

/**
 *@ingroup SRE_exc
 *@brief �쳣�������׵�ַ�ͳ��Ȼ�ȡ������
 *
 *@par ����:
 *��ȡ�쳣��Ϣ���������׵�ַ���С��
 *@attention �쳣����ʱ���ɸ��ݻ��������׵�ַ�ʹ�С��������ȡ���쳣��Ϣ�����쳣ʱ���˼��ڴ�ֵΪ0��
 *
 *@param ppBufAddr [OUT] ����#VOID **�����ػ������׵�ַ��
 *@param puwBufLen [OUT] ����#UINT32 *�����������ȡ�
 *
 *@retval #OS_ERRNO_EXC_PARA_INVLAID 0x02001c02�����ָ��Ϊ�ա�
 *@retval #SRE_OK                    0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ�
 *@since UniDSP V100R001C01
 *@see ��
 */
extern UINT32 SRE_ExcGetBufInfo(VOID **ppBufAddr, UINT32 *puwBufLen);

/**
 *@ingroup SRE_exc
 *@brief �û�ע���쳣�����ӡ�
 *
 *@par ����:
 *ע���쳣�����ӡ�
 *@attention
 * <ul>
 * <li>�����ע��ù���ʱ�����һ��ע��Ĺ�����Ч��
 * <li>ע��Ĺ��Ӻ�������Ϊ�գ���һ��ע�ṳ�Ӻ���������ͨ��ע��պ�������ȡ����
 * </ul>
 *
 *@param pfnHook [IN] ����#EXC_PROC_FUNC�����Ӻ�����
 *
 *@retval #OS_ERRNO_EXC_REG_HOOK_PTR_NULL 0x02001c09�����Ӻ���Ϊ��
 *@retval #SRE_OK 0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ�
 *@since UniDSP V100R001C02
 *@see ��
 */
extern UINT32 SRE_ExcRegHook( EXC_PROC_FUNC pfnHook );

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 *@ingroup SRE_exc
 *@brief �û�ע��Hac��ʱ�����쳣�����û����ӡ�
 *
 *@par ����:
 *ע��Hac��ʱ�����쳣�����û����ӡ�
 *@attention �����ע��ù���ʱ�����һ��ע��Ĺ�����Ч��
 *
 *@param pfnHook [IN] ����#HACTIMEOUT_PROC_FUNC�����Ӻ�����
 *
 *
 *@retval #OS_ERRNO_EXC_REG_HOOK_PTR_NULL 0x02001c09�����Ӻ���Ϊ�ա�
 *@retval #SRE_OK 0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ���
 *@since UniDSP V200R003C06
 *@see ��
 */
extern UINT32 SRE_HacTimeOutCheckHook( HACTIMEOUT_PROC_FUNC pfnHook );
#endif

/**
 * @ingroup  SRE_exc
 * @brief ��ȡRTOSck�쳣��ڵ�ַ��
 *
 * @par ����:
 * TensilicaоƬ�Լ�HIDSPоƬ�ṩ��һ��Ӳ��TraceBuffer���ܣ�����ʵʱѭ����¼ָ��ִ�������������쳣����ʱ��Ϊ����TraceBuffer�е���Ϣ���쳣�������ָ�������ǣ�
 * Ӧ��ֹͣ��¼ָ�������û����������API��ȡ�쳣��ڵ�ַ,���õ�Ӳ��Trace�ṩ��һ�������Ĵ�������PC������Ĵ�����ֵ��ͬʱ��TraceBuffer�Զ�ֹͣ
 * ָ�����ļ�¼��
 * @attention ��
 *
 * <ul>
 * <li>��</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ������ַ                  ������ַ���쳣����ĺ�����ַ��
 * @par ����:
 * sre_exc.h���ýӿ��������ڵ�ͷ�ļ���
 * @since UniDSP V200R003C05
 * @see ��
 */
extern VOID * SRE_ExcEntryGet(VOID);

/**
 *@ingroup SRE_exc
 *@brief �������Թ���ע�ắ����
 *
 *@par ����:
 *ע���������Թ��ӵ��������������С�
 *@attention
 *
 *@param ptrHook [IN] ����#SRE_LASTWORDS_FUNC�����Ӻ�����
 *
 *@retval #OS_ERRNO_HOOK_TYPE_INVALID  0x02001600����ι������ͷǷ�
 *@retval #OS_ERRNO_HOOK_PTR_NULL      0x02001602����ι��ӵ�ַΪNULL
 *@retval #OS_ERRNO_HOOK_FULL          0x02001604��HOOK���������ø���Ϊ0
 *@retval #OS_ERRNO_HOOK_EXISTED       0x02001603��HOOK�Ѵ���
 *@retval #SRE_OK 0x00000000���ɹ����ء�
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ�
 *@since UniDSP V100R001C02
 *@see SRE_LastWordsDisHook
 */
#define SRE_LastWordsRegHook(pfnHook) SRE_HookAdd(OS_HOOK_LAST_WORDS, (OS_VOID_FUNC)(SRE_LASTWORDS_FUNC)pfnHook)

/**
 *@ingroup SRE_exc
 *@brief �������Թ���ȡ��������
 *
 *@par ����:
 *����ע����������Թ��Ӵ�������ɾ����
 *@attention ��
 *
 *@param ptrHook [IN] ����#SRE_LASTWORDS_FUNC�����Ӻ�����
 *
 *@retval #OS_ERRNO_HOOK_TYPE_INVALID  0x02001600����ι������ͷǷ�
 *@retval #OS_ERRNO_HOOK_PTR_NULL      0x02001602����ι��ӵ�ַΪNULL
 *@retval #OS_ERRNO_HOOK_NOT_EXISTED   0x02001605��HOOK������
 *@retval #SRE_OK 0x00000000���ɹ����ء�
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ�
 *@since UniDSP V100R001C02
 *@see SRE_LastWordsRegHook
 */
#define SRE_LastWordsDisHook(pfnHook) SRE_HookDel(OS_HOOK_LAST_WORDS, (OS_VOID_FUNC)(SRE_LASTWORDS_FUNC)pfnHook)

/**
 * @ingroup  SRE_exc
 * @brief ��ȡ�쳣�������ַ��
 *
 * @par ����:
 * ��ȡ�쳣�������ַ��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval #����ֵ       ��ַ���쳣������ĵ�ַ
 * @par ����:
 * <ul><li>sre_exc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see NA
 */
extern VOID * SRE_ExcGetVectorTable(VOID);

/**
 *@ingroup SRE_exc
 *@brief ���˸�λ��Դ���ա�
 *
 *@par ����:
 *���˸�λ��Դ���ա�
 *@attention
 * <ul>
 * <li>�ýӿڽ�֧��SD6182оƬ��</li>
 * <li>���ձ��˴�����Ӳ���ź�����Դ���˼���Ϣ��ռ�Ĺ����ڴ���Դ��hunt���˼��ź���ռ�õ�1�ŷ�����Դ��
 * </ul>
 *
 *@param ��
 *
 *@retval ��
 *
 *@par ����:
 *sre_exc.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R003C00
 *@see ��
 */
extern VOID SRE_ExcSingleCoreReclaim();

//#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_EXC_H */


