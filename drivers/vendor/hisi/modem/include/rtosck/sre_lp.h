/**
 * @file sre_lp.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ���������LP��h�ļ��� \n
 */
#ifndef _SRE_LP_H
#define _SRE_LP_H
#include "sre_base.h"
#include "sre_sys.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**@defgroup sre_lp ��̬���غͲ���ģ��
 * @ingroup sre_lp
 */

/**
 * @ingroup sre_lp
 * ����bin��������
 */
#define OS_LP_BASE_BIN_GROUP_NAME                       0x0

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��Ԫ�ŷǷ���Ϊ0ֵ���߳������������á�
 *
 * ֵ: 0x02001e01
 *
 *�������:����LP��Ԫ�źϷ���
 */
#define OS_ERRNO_LP_NO_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_LP, 0x01)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��ԪcrcУ��ʧ�ܡ�
 *
 * ֵ: 0x02001e02
 *
 *�������:����LP�ļ�����ȷ��
 */
#define OS_ERRNO_LP_CRC_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x02)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����ļ��еı�ʾͷ����ȷ��
 *
 * ֵ: 0x02001e03
 *
 *�������:��̬�����ļ���������ʾ����"SP"�������������������ļ�
 */
#define OS_ERRNO_LP_SP_FLAG_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x03)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����ļ����ļ�������ȷ��
 *
 * ֵ: 0x02001e04
 *
 *�������:��̬�����ļ��ļ�������ȷ��������������
 */
#define OS_ERRNO_LP_SP_NAME_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x04)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP�ļ��ṹ��������汾�Ŵ���
 *
 * ֵ: 0x02001e05
 *
 *�������:��������LP�ļ����߶˵�LP�ļ��ṹЭ��汾����SRE_LPGetVersion��ȡ�İ汾���Ƿ�һ��,��鹤�߶�Э��汾�Ƿ���ȷ
 */
#define OS_ERRNO_LP_PROTOCOL_VER_INVALID                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x05)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP�ļ��ظ����ء�
 *
 * ֵ: 0x02001e06
 *
 *�������:���������Ƿ���LP�ļ��ظ����أ����޸�
 */
#define OS_ERRNO_LP_LOADED                              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x06)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����ļ��д�����������еĴ���β�һ�¡�
 *
 * ֵ: 0x02001e07
 *
 *�������:����makepatch.ini�ļ��еľ�̬���������������SRE_LPGroupInfoReg�ӿ��е������Ƿ���ͬ
 */
#define OS_ERRNO_LP_CODE_ADDR_NOT_SUIT                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x07)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����ļ������ݶ��������еĹ������ݶλ�˽�����ݶβ�һ�¡�
 *
 * ֵ: 0x02001e08
 *
 *�������:����makepatch.ini�ļ��еľ�̬�����������ݶκ�˽�����ݶ�������SRE_LPGroupInfoReg�ӿ��е������Ƿ���ͬ
 */
#define OS_ERRNO_LP_DATA_ADDR_NOT_SUIT                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x08)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP�����У�LP��Ԫδ����.
 *
 * ֵ: 0x02001e09
 *
 *�������:��ȷ��LP��Ԫ�Ѽ���.
 */
#define OS_ERRNO_LP_NOT_LOADED                          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x09)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��LP��Ԫ�Ѿ����ڼ���״̬��
 *
 * ֵ: 0x02001e0a
 *
 *�������:��
 */
#define OS_ERRNO_LP_IS_ACTIVE                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��LP��Ԫ�Ѿ�����ȥ����״̬��
 *
 * ֵ: 0x02001e0c
 *
 *�������:��
 */
#define OS_ERRNO_LP_IS_DEACTIVE                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ���Ϊ�ա�
 *
 * ֵ: 0x02001e0d
 *
 *�������:�鿴�����ָ������Ƿ�Ϊ��
 */
#define OS_ERRNO_LP_INPUT_IS_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0d)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ���������Ȳ��������߻���������Ϊ0����������Ƿ���ȷ��
 *
 * ֵ: 0x02001e0e
 *
 *�������:�鿴����Ļ���������
 */
#define OS_ERRNO_LP_BUF_NOT_ENOUGH                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0e)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �ڴ�����ʧ�ܣ�LP������������Ҫ��̬�����ڴ档
 *
 * ֵ: 0x02001e0f
 *
 *�������:�뽫�ڴ�ռ��ʵ����
 */
#define OS_ERRNO_LP_MEM_NOT_ENOUGH                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x0f)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: 6108/6181ֻ֧�־�̬����(SP)��
 *
 * ֵ: 0x02001e10
 *
 *�������:���6108��6181ƽ̨�Ƿ�����Ϊ��̬�������߶�̬����(DP/DL/DL_DP)��
 */
#define OS_ERRNO_LP_6108_6181_DLDP_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x10)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬����(SP)��ѯ���صĴ�������ݳ���ʱָ����LP���Ͳ��Ϸ���
 *
 * ֵ: 0x02001e11
 *
 *�������:ȷ����ѯ��̬������������ݳ�����Ϣʱָ��LP���е�LP���ͱ���ΪSP��
 */
#define OS_ERRNO_LP_SP_TYPE_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x11)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬������Ԫ����ο�ʼ��ַС�ڲ�����������׵�ַ�����߾�̬������Ԫ����γ�������������η�Χ��
 *
 * ֵ: 0x02001e12
 *
 *�������:���龲̬������Ԫ����ο�ʼ��ַ���ʵ����Ӳ���������δ�С
 */
#define OS_ERRNO_LP_CODE_OVER_FLOW                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x12)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬������Ԫ���ݶο�ʼ��ַС�ڲ��������ݶ��׵�ַ�����߾�̬������Ԫ���ݶγ������������ݶη�Χ��
 *
 * ֵ: 0x02001e13
 *
 *�������:���龲̬������Ԫ���ݶο�ʼ��ַ���ʵ����Ӳ��������ݶδ�С
 */
#define OS_ERRNO_LP_DATA_OVER_FLOW                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x13)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�������߶�̬����ɾ�������У�ԭ����ָ��ƻ������ܻ��˲���״̬��
 *
 * ֵ: 0x02001e14
 *
 *�������:��̬�������߶�̬����ɾ�������У�ԭ����ָ��ƻ������ܻ��˲���״̬
 */
#define OS_ERRNO_LP_INSTRUCTION_DESTROYED               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x14)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�������߶�̬�������صĲ������������������������ơ�
 *
 * ֵ: 0x02001e15
 *
 *�������:�������ýӿ�������������Ƿ���ȷ
 */
#define OS_ERRNO_LP_FUNC_OVERFLOW                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x15)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����е�LP�ļ����Ȳ�����ȷ��LP�ļ�����
 *
 * ֵ: 0x02001e16
 *
 *�������:���LP�ļ���ȷ�ԣ�������������LP�ļ�
 */
#define OS_ERRNO_LP_FILE_IS_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x16)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �ظ�ע���LP����Ϣ��һ�¡�
 *
 * ֵ: 0x02001e17
 *
 *�������:ȷ��LP����Ϣ�ظ�ע��ʱע�������Ϣ���������ǰһ����ͬ(��������ID����������������ò�����)
 */
#define OS_ERRNO_LP_INFO_REPEAT_DIFFER                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x17)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ָ�����������Ϣδ����ʼ����
 *
 * ֵ: 0x02001e18
 *
 *�������:����Ӧ�������Ƿ��к�û�е���SRE_LPGroupInfoReg��ʼ�����߳�ʼ��ʧ�ܻ��߾���DSSNUM���ô���
 */
#define OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x18)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���أ���̬��������������ͬ
 *
 * ֵ: 0x02001e19
 *
 *�������:�޸���ͬ�Ķ���Ϊ��ͬ������
 */
#define OS_ERRNO_LP_SEC_NAME_SAME                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x19)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP����ͬ������ʧ�ܣ���ʱ��
 *
 * ֵ: 0x02001e1a
 *
 *�������:��
 */
#define OS_ERRNO_LP_START_SYN_FAIL                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ػ�̬�������÷ǲ����滻����CALL�ض�λ����
 *
 * ֵ: 0x02001e1b
 *
 *�������:ȷ�Ϸ����Ƿ�4�ֽڶ���򳬹�call���÷�Χ��
 */
#define OS_ERRNO_LP_CALL_OFFECT_ERROR                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LPȥ����ʱLP����ͬ������ʧ�ܡ�
 *
 * ֵ: 0x02001e1c
 *
 *�������:��
 */
#define OS_ERRNO_LP_DEACTIVE_SYN_PHASE_FAIL              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ͬ����������Ҫ���빲���ڴ棬�����ڴ�����ʧ�ܡ�
 *
 * ֵ: 0x02001e1d
 *
 *�������:�����ú���Ĺ����ڴ�ռ䡣
 */
#define OS_ERRNO_LP_ALLOC_COMM_MEM_FAIL                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1d)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����ͬ������ʧ�ܡ�
 *
 * ֵ: 0x02001e1e
 *
 *�������:��
 */
#define OS_ERRNO_LP_SET_PARA_FAIL                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1e)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���������У��Ѿ����صĲ�����Ԫ���ٴμ��صĲ�����Ԫ��һ�¡�crcУ�鲻ͨ����
 *
 * ֵ: 0x02001e1f
 *
 *�������:��ȷ���Ѿ����صľ�̬������Ԫ���ٴμ��صľ�̬������Ԫһ����
 */
#define OS_ERRNO_LP_INCLUDE_OLDFILE_FUNC_UNCOVERED        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x1f)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP����FLAG����ȷ��������"SP"��"DL"��"DP"��Cortex-A7��Cortex-A9ƽ̨����Ϊ"DP"��
 *
 * ֵ: 0x02001e20
 *
 *�������:���汾�Ƿ�������ȷ����һ��LP��־�Ƿ���"SP"��"DL"��"DP"֮һ��Cortex-A7��Cortex-A9ƽ̨����Ϊ"DP"��
 */
#define OS_ERRNO_LP_IDENT_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x20)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP�ļ���crcУ��ʧ�ܡ�
 *
 * ֵ: 0x02001e21
 *
 *�������:��ȷ���Ƿ���ȷ����
 */
#define OS_ERRNO_LP_PACKET_CRC_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x21)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���ز������ȡLP�ļ��е����LP��Ԫ��ʱ����Ļ�������ַ(pucBuf)��4�ֽڶ��롣
 *
 * ֵ: 0x02001e22
 *
 *�������:��֤��λ�������ַ(pucBuf)4�ֽڶ��롣
 */
#define OS_ERRNO_LP_BUF_ADDR_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x22)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ���õĲ����������(��ʼ��ַ������)δ����cache line����(SD6181/SD6108Ϊ64�ֽڣ�SD6182Ϊ128�ֽ�)������˽�в�����δ����4�ֽڶ��롣
 *
 * ֵ: 0x02001e23
 *
 *�������:�������ò��������������ʼ��ַ�����ȡ�
 */
#define OS_ERRNO_LP_REG_NOT_ALIGN                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x23)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��Ԫ�������������Ϊ0��
 *
 * ֵ: 0x02001e24
 *
 *�������:������õ�LP��Ԫ���������
 */
#define OS_ERRNO_LP_REG_FUNC_NUM_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x24)


/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��ѯ��̬���ػ�̬�����Ķ���Ϣʱָ��LP���LP���ʹ���
 *
 * ֵ: 0x02001e25
 *
 *�������:ʹ��SRE_LPSectionInfoGet�ӿڲ�ѯָ��LP�����Ϣʱ��ӦLP���Ͳ���Ϊ��̬��������(LP_TYPE_SP)��
 */
#define OS_ERRNO_LP_SEC_INFO_QUERY_LP_TYPE_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x25)


/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬����ELF�ζ������
 *
 * ֵ: 0x02001e26
 *
 *�������:�鿴��̬���ػ�̬����ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_LP_SEC_ALIGN_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x26)


/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬��������LP��Ԫû�б����ء�
 *
 * ֵ: 0x02001e27
 *
 *�������:���ھ�̬������������������鿴��̬�����м��ص�ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_LP_SP_NOT_LOADED                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x27)


/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬�������ű��ͷ��ÿ�����Žڵ�Ĵ�С����
 *
 * ֵ: 0x02001e28
 *
 *�������:�鿴��̬���ػ�̬����ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_LP_ITEM_SIZE_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x28)

/**
  * @ingroup sre_lp
  * ���LP�����붨��: ע�ᱣ��LP��Ԫ״̬�Ĺ��Ӻ���Ϊ�ա�
  *
  * ֵ: 0x02001e29
  *
  *�������:�Ų�ע�ᱣ��LP��Ԫ״̬�Ĺ��Ӻ����Ƿ�Ϊ�ա�
  */
#define OS_ERRNO_LP_REG_STATESAVEHOOK_NULL                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x29)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����ID����
 *
 * ֵ: 0x02001e2a
 *
 *�������:������õľ���ID�Ƿ�С�ھ������������õľ���ID�Ƿ�����������ID��ͻ��
 */
#define OS_ERRNO_LP_IMAGE_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���ò�һ��
 *
 * ֵ: 0x02001e2b
 *
 *�������:��ȷ�����������LP������Ϣ������������š�������ַ���������ȡ�оƬ��������һ��
 */
#define OS_ERRNO_LP_CONFIG_NOT_SAME                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��󲹶��Ͷ�̬���ؿ���ܵ�Ԫ����������Ч
 *
 * ֵ: 0x02001e2c
 *
 *�������:��ȷ��LP�ܵ�Ԫ����config�ļ������÷�ΧΪ[1,9999]
 */
#define OS_ERRNO_LP_NUM_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��LPʹ�õķ�����ʼ��ַ�Ƿ�
 *
 * ֵ: 0x02001e2d
 *
 *�������:ȷ��������ʼ��ַ(#OS_LP_SHARE_NC_PT_ADDR)��0
 */
#define OS_ERRNO_LP_MEMPT_ADDR_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2d)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��LPʹ�õķ�����СΪ0
 *
 * ֵ: 0x02001e2e
 *
 *�������:ȷ��������С(#OS_PATCH_SHARE_NC_PT_SIZE)��0
 */
#define OS_ERRNO_LP_MEMPT_SIZE_IS_ZERO                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2e)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP�Ĵ�����������0x40000000
 *
 * ֵ: 0x02001e2f
 *
 *�������:SD6181/SD6108/SD6182�Ĵ����������0x4000000���µĵ�ַ�ռ䣬����XTENSA��ֻ֧��1G�ռ��ڵĺ������ã�
 *����LP�Ĵ����������ڴ��ڵ���0x40000000�Ŀռ䣬LP����󣬱��򲹶��������޷������丸��������ˣ�
 *LP�Ĵ�����Ӧ��������0x40000000���µĿռ䡣
 */
#define OS_ERRNO_LP_CODE_PUT_IN_ANOTHER_1G                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x2f)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �������������������
 *
 * ֵ: 0x02001e30
 *
 *�������:�������������������С��1
 */
#define OS_ERRNO_LP_AREA_NUM_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x30)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����������Ĵ�������ô���
 *
 * ֵ: 0x02001e31
 *
 *�������:��̬�����������Ĵ������ʼ��ַ�����Ⱦ�����Ϊ0
 */
#define OS_ERRNO_LP_CFG_CODE_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x31)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����������Ĺ������ݶ����ô���
 *
 * ֵ: 0x02001e32
 *
 *�������:��̬�����������Ĺ������ݶ���ʼ��ַ�����Ⱦ�����Ϊ0�����ݶ��ܳ��Ȳ���С�ڹ������ݶεĳ���
 */
#define OS_ERRNO_LP_CFG_SDATA_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x32)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬������������˽�����ݶ����ô���
 *
 * ֵ: 0x02001e33
 *
 *�������:1����̬������������˽�����ݶ���ʼ��ַ����Ϊ0�����û��˽�����ݣ�˽�����ݶεĳ��ȿ�����Ϊ0������ʼ��ַ����Ϊ0
 *         2������̬�����������Ĺ�������Ϊ�٣���ζ�Ų�����������˽���ڴ棬����SD6181/SD6108��L1�ռ䣩����ֻ�������˽�����ݡ�
 *            ����˽�����ݶ��Ѿ�ͨ���ṹ��#LP_SP_AREA_INFO��uwDataShareAreaAddr��uwDataShareAreaSize��Ա�������ã�
 *            ��˽ṹ���uwDataAreaSize���ܴ���uwDataShareAreaSize��
 */
#define OS_ERRNO_LP_CFG_PDATA_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x33)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���������������ݶ����ô���
 *
 * ֵ: 0x02001e34
 *
 *�������:1������̬�����������Ĺ�������Ϊ�棬��SD6181/SD6108/SD6182�Ĺ���/˽�����ݶ�ֻ�ܷ����ڹ����ڴ棨SD6181/SD6182��L2/L3/DDR��SD6108��L2/DDR����
 *         2������̬�����������Ĺ�������Ϊ�٣���SD6181/SD6108/SD6182��˽�����ݶ�ֻ�ܷ�����˽���ڴ棨SD6181/SD6108��L1��SD6182��LL2����
 */
#define OS_ERRNO_LP_CFG_DATA_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x34)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����������Ŵ���
 *
 * ֵ: 0x02001e35
 *
 *�������:��̬�����������Ų��ܴ��ڵ���SRE_LPGroupInfoRegע�����󲹶�������uwAreaNum
 */
#define OS_ERRNO_LP_AREA_NO_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x35)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬����L1��ַ����������Ϊȫ�ֵ�ַ
 *
 * ֵ: 0x02001e36
 *
 *�������:SD6181/SD6108������̬����������������L1ʱ����ʹ��˽�е�ַ��(0, 0x10000000)����������ȫ�ֵ�ַ��[0x80000000, 0x8FFFFFFF]����
 */
#define OS_ERRNO_LP_GLB_L1_ADDR                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x36)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬��������β��������DRAM�����ݶβ��������IRAM
 *
 * ֵ: 0x02001e37
 *
 *�������:����XTENSA��Ӳ�����ƣ�����β��������DRAM��RISC170��0x01000000~0x0101FFFF��DSP170��0x01000000~0x0107FFFF����
 *         ���ݶβ��������IRAM��RISC170��0x01020000~0x0103FFFF��DSP170��0x01080000~0x0109FFFF�������Ҵ���λ������ݶε���
 *ʼ��ַ���ϴ���λ������ݶεĳ��Ȳ��ܳ��������õ�IRAM����DRAM�ڴ�ռ䣬���Ų飻
 */
#define OS_ERRNO_LP_L1_ADDR_ERR                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x37)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: оƬ���ʹ���
 *
 * ֵ: 0x02001e38
 *
 *�������:оƬ���ͼȷ�SD6181��Ҳ��SD6108��Ҳ��SD6182��
 */
#define OS_ERRNO_LP_CHIP_TYPE_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x38)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �����LP��Ԫ״̬����ȷ,���п���״̬ҲΪ�Ƿ���
 *
 * ֵ: 0x02001e39
 *
 *�������:����д��ȷ��LP��Ԫ״̬
 */
#define OS_ERRNO_LP_STATE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x39)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ���õĺ˵���Ŀ��֮ǰ���õĲ�ͬ�����õĺ���С�ڱ�Imageʵ�����еĺ�����
 *
 * ֵ: 0x02001e3a
 *
 *�������:���DSS��Ŀ����ȷ�ԣ����߼��imageID�Ƿ����ô���
 */
#define OS_ERRNO_LP_DSS_NUM_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ء���̬���������Դ���
 *
 * ֵ: 0x02001e3b
 *
 *�������:���ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_LP_SECTION_FLAG_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ػ�̬����ʱ�����ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02001e3c
 *
 *�������:����LP���ڴ������С��
 */
#define OS_ERRNO_LP_MEM_ALLOC_ERROR                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����ض�λ�Σ���ͷ��С����
 *
 * ֵ: 0x02001e3d
 *
 *�������:���ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_LP_REL_ENTSIZE_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3d)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ػ�̬����ʱELF�ļ�ͷ����
 *
 * ֵ: 0x02001e3e
 *
 *�������:���ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_LP_ELF_HEAD_ERROR                          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3e)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ػ�̬����ʱELF�α�ͷ����
 *
 * ֵ: 0x02001e3f
 *
 *�������:���ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_LP_ELF_SEC_HEAD_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x3f)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ػ�̬����ʱELF����ϢУ�����
 *
 * ֵ: 0x02001e40
 *
 *�������:���ELF�ļ��Ƿ������⡣
 */
#define OS_ERRNO_LP_ELF_SEC_NUM_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x40)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ػ�̬��������ʱ��ȡ����Ϣ����
 *
 * ֵ: 0x02001e41
 *
 *�������:��鶯̬���ض�̬�����������Ķ��Ƿ��Ѿ�ע�ᡣ
 */
#define OS_ERRNO_LP_SEC_INFO_GET_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x41)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP����Ϣע�ᣬ���ָ��Ϊ�ա�
 *
 * ֵ: 0x02001e42
 *
 *�������:���LP����Ϣע��ʱ���ָ���Ƿ�Ϊ�ա�
 */
#define OS_ERRNO_LP_PARA_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x42)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP����ʱ��LP�������ͺͺ�֧�ֵ����Ͳ�����
 *
 * ֵ: 0x02001e43
 *
 *�������:����ע������ͺ�LP���������Ƿ�һ�¡�
 */
#define OS_ERRNO_LP_FETCH_TYPE_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x43)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����滻�ĺ������������û����õĲ�����Ԫ������滻������
 *
 * ֵ: 0x02001e44
 *
 *�������:����LP��Ԫ��󲹶��滻���������ã����߼��ٶ�̬���������滻�ĸ�����
 */
#define OS_ERRNO_LP_FETCH_REPLACE_FUNC_OVERFLOW             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x44)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ط��ź����а汾�ķ����ظ�������߶�̬����ȫ�ֱ��������ظ����塣
 *
 * ֵ: 0x02001e45
 *
 *�������:��鶯̬�����ļ�������ź����а汾�ķ����Ƿ��ظ����߼�鶯̬�����ļ����涨��ı����Ƿ��ظ����ظ�����ɾ����
 */
#define OS_ERRNO_LP_FETCH_DL_FUNC_REDEFINE                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x45)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �ض�λ���Ŷ�Ӧ��ָ�����Ͳ�֧��
 *
 * ֵ: 0x02001e46
 *
 *�������:�鿴��Ŀ���ļ�����ĺ��Ƿ��OS֧�ֵĺ�ƥ�䣬����ָ��ܹ�������ѡ��ȡ�
 */
#define OS_ERRNO_LP_INST_TYPE_ERROR                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x46)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ע���LP���ʹ���
 *
 * ֵ: 0x02001e47
 *
 *�������:�Ų�ע���LP�����Ƿ���#LP_TYPEö�ٵ�����֮һ,����CORTEX-AXƽ̨�����ͱ���ΪLP_TYPE_DP��
 */
#define OS_ERRNO_LP_REG_LP_TYPE_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x47)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LPģ��δ��ʼ����ע��LP����Ϣ�ľ���û�о�����ʼ����
 *
 * ֵ: 0x02001e48
 *
 *�������:����Ƿ�OS��LPģ��ü�����û�򿪣����߳�ʼ��û����ɡ�
 */
#define OS_ERRNO_LP_NOT_INITED                              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x48)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�������ò�����Ϊ�ա�
 *
 * ֵ: 0x02001e49
 *
 *�������:����Ƿ�δ���þ�̬��������������LP���ʹ���
 */
#define OS_ERRNO_LP_HPAREAINFO_IS_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x49)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬������̬�������ö���Ϊ�ա�
 *
 * ֵ: 0x02001e4a
 *
 *�������:����Ƿ�δ���ö�̬������̬���ض�������LP���ʹ���
 */
#define OS_ERRNO_LP_DLDPAREAINFO_IS_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬�����Ķ�������ʼ��ַ���߳������ô���
 *
 * ֵ: 0x02001e4b
 *
 *�������:��̬���ض�̬�����Ķ�������ʼ��ַ�����Ⱦ�����Ϊ0
 */
#define OS_ERRNO_LP_CFG_SEC_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬�����Ķ�������Ϊ��
 *
 * ֵ: 0x02001e4c
 *
 *�������:��̬���ض�̬�����Ķ������ֲ���Ϊ��
 */
#define OS_ERRNO_LP_CFG_SEC_NAME_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �������ڴ��������
 *
 * ֵ: 0x02001e4d
 *
 *�������:���LP�ڴ��������Ĵ�С��
 */
#define OS_ERRNO_LP_SECTAB_MEM_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4d)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �����������
 *
 * ֵ: 0x02001e4e
 *
 *�������:ELF�ļ��ĸ�ʽ��Ҫ��Ĳ����ϡ�
 */
#define OS_ERRNO_LP_SECTAB_READ_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4e)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���غͶ�̬��������ʱ��RO_DATA�����
 *
 * ֵ: 0x02001e4f
 *
 *�������:����RO_DATA�εĿռ䡣
 */
#define OS_ERRNO_LP_RO_DATA_OVERFLOW                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x4f)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �����ض�λʱL32Rָ���ض�λ���󣬿�����ƫ��������0x3FFFF������ƫ������4�ֽڶ���
 *
 * ֵ: 0x02001e50
 *
 *�������:�鿴�������Ƿ������⡣
 */
#define OS_ERRNO_LP_L32R_OFFECT_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x50)


/**
 * @ingroup sre_lp
 * ���LP�����붨��: ������������
 *
 * ֵ: 0x02001e51
 *
 *�������:ELF�Ķθ�������Ϊ0����ȷ�ϲ�����̬�����ļ�����ȷ�ԡ�
 */
#define OS_ERRNO_LP_SEC_NUM_ADDR_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x51)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��ʱ���ű����ɴ���
 *
 * ֵ: 0x02001e52
 *
 *�������:SD6182ƽ̨,�������LP���������С����ȷ�ϲ�����̬�����ļ�����ȷ�ԡ�
 */
#define OS_ERRNO_LP_SYM_BUILD_ERROR                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x52)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LOCAL L2��ַ����������Ϊȫ�ֵ�ַ(Cluster Local L2 Global Address)��
 *
 * ֵ: 0x02001e53
 *
 *�������:SD6181/SD6108/SD6182��ʹ��SP��˽�в����������ں�Local L2��ַʱ����ʹ��˽�е�ַ��(0, 0x0807FFFF)����������ȫ�ֵ�ַ��[0x90000000, 0x9A47FFFF]����
 */
#define OS_ERRNO_LP_GLB_L2_ADDR                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x53)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP����ʱ��ӦLP��Ԫ��LP���ʹ���
 *
 * ֵ: 0x02001e54
 *
 *�������:LP����ʱLP�����Ƿ���ȷ��
 */
#define OS_ERRNO_LP_SYN_SET_TYPE_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x54)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���أ���̬������Ҫ�������ű�ģ�顣
 *
 * ֵ: 0x02001e55
 *
 *�������:ʹ�ö�̬���ض�̬������Ҫ�򿪷��ű�ģ�顣
 */
#define OS_ERRNO_LP_DEPEND_SYMBOL_INITED                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x55)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ذ��Ͷ�̬����������֮�󣬴�������
 *
 * ֵ: 0x02001e56
 *
 *�������:�������εĿռ䡣
 */
#define OS_ERRNO_LP_CODE_OVERFLOW                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x56)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ذ��Ͷ�̬����������֮��DATA�����
 *
 * ֵ: 0x02001e57
 *
 *�������:����DATA�εĿռ䡣
 */
#define OS_ERRNO_LP_DATA_OVERFLOW                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x57)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ذ��Ͷ�̬����������֮��BSS�����
 *
 * ֵ: 0x02001e58
 *
 *�������:����BSS�εĿռ䡣
 */
#define OS_ERRNO_LP_BSS_OVERFLOW                            SRE_ERRNO_OS_ERROR(OS_MID_LP,0x58)

/**
  * @ingroup sre_lp
  * ���LP�����붨��: LP������ID��ʹ���У�����ȥע���LP��Ϣ�����顣
  *
  * ֵ: 0x02001e59
  *
  *�������:�Ų�LP��������Ϣȥע��ʱ��̬���ؼ�LP������Ϣ��ID���������LP��Ԫ�Ƿ�û�д��ڿ���״̬��
  */
#define OS_ERRNO_LP_GROUP_ID_IN_USE                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x59)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����LP��Ԫ���ƿ�ʧ��
 *
 * ֵ: 0x02001e5b
 *
 *�������:�����ص�LP��Ԫ�����Ƿ��Ѿ��������õ����LP��Ԫ����
 */
#define OS_ERRNO_LP_PATCH_INDEX_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ���򲹶�������СС��16�ֽ�
 *
 * ֵ: 0x02001e5c
 *
 *�������:��鱻�򲹶��ĺ����Ƿ�С��16�ֽڡ�
 */
#define OS_ERRNO_LP_PATCH_FUNC_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ���ڴ�����ʼ��ʧ��
 *
 * ֵ: 0x02001e5d
 *
 *�������:������õĶ��Ƿ�̫С�����ߵ�ַ���ô���
 */
#define OS_ERRNO_LP_MEM_INIT_FAILD                          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5d)


/**
  * @ingroup sre_lp
  * ���LP�����붨��: ARM MOVW/MOVTָ���ض�λ����
  *
  * ֵ: 0x02001e5e
  *
  *�������:���ELF�ļ��Ƿ���ȷ��
  */
#define OS_ERRNO_LP_ARM_MOVE_RELOC_ERROR                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5e)

/**
  * @ingroup sre_lp
  * ���LP�����붨��: THUMB MOVW/MOVTָ���ض�λ����
  *
  * ֵ: 0x02001e5f
  *
  *�������:���ELF�ļ��Ƿ���ȷ��
  */
#define OS_ERRNO_LP_THUMB_MOVE_RELOC_ERROR                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x5f)

/**
 * @ingroup sre_lp
 * ���LP�����붨��:��Global�����ڴ�����ʧ�ܡ�
 *
 * ֵ: 0x02001e60
 *
 *�������:�ʵ����LP�����Ĵ�С��
 */
#define OS_ERRNO_LP_MEM_ERROR                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x60)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��Ԫ�������õ�̫С
 *
 * ֵ: 0x02001e61
 *
 *�������:����LP��Ԫ�����ø���
 */
#define OS_ERRNO_LP_NUM_TOO_SMALL                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0x61)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: 6108��6181��6182ƽ̨LPʹ�õ��ڴ�����Ų�����0,1
 *
 * ֵ: 0x02001e62
 *
 *�������:����LPʹ�õ��ڴ�����Ŵ���1��С�����LP������
 */
#define OS_ERRNO_LP_MEM_PT_NO_ERROR                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0x62)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����ݹ���ò����滻����call�ض�λʧ�ܡ�
 *
 * ֵ: 0x02001e63
 *
 *�������:ȷ��LP�ļ��и÷����Ƿ�4�ֽڶ���򳬹�call���÷�Χ��
 */
#define OS_ERRNO_LP_RECUR_CALL_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x63)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP�ļ����ʹ���
 *
 * ֵ: 0x02001e64
 *
 *�������:���TENSILICAƽ̨�Ƿ�ʹ����ARMԴ�ļ����Ĳ�������ARMƽ̨ʹ����TENSILICAԴ�ļ����Ĳ���
 */
#define OS_ERRNO_LP_ELF_FILETYPE_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x64)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬�����ǵݹ鲹���滻����call�ض�λʧ�ܡ�
 *
 * ֵ: 0x02001e65
 *
 *�������:ȷ�ϻ����汾��ĸ÷����Ƿ�4�ֽڶ���򳬹�call���÷�Χ�����еĵݹ���á�
 */
#define OS_ERRNO_LP_NONRECUR_CALL_ERROR                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x65)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬��������24λ�������ض�λ����
 *
 * ֵ: 0x02001e66
 *
 *�������:ȷ��ARMָ���Ƿ�4�ֽڶ���򳬹�24λ���������÷�Χ[-32M,32M]��
 */
#define OS_ERRNO_LP_ARM_PC24_OFFECT_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x66)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬��������22λ������ָ���ض�λ����
 *
 * ֵ: 0x02001e67
 *
 *�������:ȷ��Thumbָ���Ƿ�2�ֽڶ���򳬹�22λ������ָ����÷�Χ[-16M,16M]��
 */
#define OS_ERRNO_LP_THUMB_CALL_OFFECT_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x67)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬��������9λ������ָ���ض�λ����
 *
 * ֵ: 0x02001e68
 *
 *�������:ȷ��Thumbָ���Ƿ�2�ֽڶ���򳬹�8λ������ָ����÷�Χ[-256B,254B]��
 */
#define OS_ERRNO_LP_THUMB_JUMP8_OFFECT_ERROR                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x68)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬��������11λ��������ָ���ض�λ����
 *
 * ֵ: 0x02001e69
 *
 *�������:ȷ��Thumbָ���Ƿ�2�ֽڶ���򳬹�11λ������ָ����÷�Χ[-2M,2M]��
 */
#define OS_ERRNO_LP_THUMB_JUMP11_OFFECT_ERROR               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x69)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �����ض�λʱ����ָ��slot0�ϵ�L32Rָ���ض�λ���󣬿�����ƫ��������0x3FFFF������ƫ������4�ֽڶ���
 *
 * ֵ: 0x02001e6a
 *
 *�������:�鿴�������Ƿ������⡣
 */
#define OS_ERRNO_LP_L32R_64_S0_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �����ض�λʱ����ָ��slot2�ϵ�L32Rָ���ض�λ���󣬿�����ƫ��������0x3FFFF������ƫ������4�ֽڶ���
 *
 * ֵ: 0x02001e6b
 *
 *�������:�鿴�������Ƿ������⡣
 */
#define OS_ERRNO_LP_L32R_64_S2_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬��������16λABS��ָ���ض�λ����
 *
 * ֵ: 0x02001e6c
 *
 *�������:ȷ��ARMָ���Ƿ�2�ֽڶ���򳬹�16λ������ָ����÷�Χ[-16M,16M]��
 */
#define OS_ERRNO_LP_ARM_ABS16_OFFECT_ERROR                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬��������12λABS��ָ���ض�λ����
 *
 * ֵ: 0x02001e6d
 *
 *�������:ȷ��ARMָ���Ƿ�2�ֽڶ���򳬹�12λ������ָ����÷�Χ[-2M,2M]��
 */
#define OS_ERRNO_LP_ARM_ABS12_OFFECT_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6d)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬��������8λABS��ָ���ض�λ����
 *
 * ֵ: 0x02001e6e
 *
 *�������:ȷ��ARMָ���Ƿ�2�ֽڶ���򳬹�8λ������ָ����÷�Χ[-256B,256B]��
 */
#define OS_ERRNO_LP_ARM_ABS8_OFFECT_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6e)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��̬���ض�̬��������5λABS����ָ���ض�λ����
 *
 * ֵ: 0x02001e6f
 *
 *�������:ȷ��Thumbָ���Ƿ�2�ֽڶ���򳬹�5λ������ָ����÷�Χ[-32B,32B]��
 */
#define OS_ERRNO_LP_THUMB_ABS5_OFFECT_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x6f)


/**
 * @ingroup sre_lp
 * ϵͳ�������ܴ�����:LP������Ϣ��ĸ������ô���
 *
 * ֵ: 0x02001e70
 *
 * �������: �鿴ʵ����ÿ�������õ����LP������Ϣ������Ƿ����0���������õ���������Ϣ��������ܳ���254��(Xtensaƽ̨)��CORTEX-AXƽ̨����Ϊ1��
 *
 */
#define OS_ERRNO_LP_MAG_INFO_GROUP_NUM_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x70)


/**
 * @ingroup sre_lp
 * ���LP�����붨��: LPע��ʱ�Ҳ������е�LP�����顣
 *
 * ֵ: 0x02001e71
 *
 *�������:�Ų�ע��ʱ�Ѿ�ע���LP������Ϣ������Ƿ��ѳ������õ�LP��������Ϣ�������
 */
#define OS_ERRNO_LP_REG_NOT_FIND_IDLE_GROUP                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x71)

/**
  * @ingroup sre_lp
  * ���LP�����붨��: LP������ID�����á�
  *
  * ֵ: 0x02001e72
  *
  *�������:�鿴����LP�ӿ�ʱ��ζ�̬���ؼ�LP������Ϣ��IDֵ���ܴ��ڵ������õ����LP�����������
  */
#define OS_ERRNO_LP_GROUP_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x72)


/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��ͬGroup�䶯̬������̬���ض��������õľ�̬�����Ĵ���Σ��������ݶλ�˽�����ݶ��������ص���
 *
 * ֵ: 0x02001e73
 *
 *�������:ͨ��SRE_LP_ERRREPORT_HOOK_FUNCPTR���Ӳ鿴LP_ERROR_REPORT_INFO��鲻ͬGroup�䶯̬������̬���ض�֮���������õľ�̬�����Ĵ���Σ��������ݶλ�˽�����ݶ��Ƿ��������ص���
 */
#define OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_ANOTHER_GROUP_WITH_SP      SRE_ERRNO_OS_ERROR(OS_MID_LP,0x73)

/**
  * @ingroup sre_lp
  * ���LP�����붨��: ע����ص������ϱ����Ӻ���Ϊ�ա�
  *
  * ֵ: 0x02001e74
  *
  *�������:�Ų�ע����ص������ϱ��Ĺ��Ӻ����Ƿ�Ϊ�ա�
  */
#define OS_ERRNO_LP_REG_ERRREPORTHOOK_NULL                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x74)



/**
  * @ingroup sre_lp
  * ���LP�����붨��: LP��������Ч�˷�Χ����
  *
  * ֵ: 0x02001e75
  *
  *�������:��Ч�˷�Χ����Ϊ0�����뵱ǰ���к˷�Χû�н�����
  */
#define OS_ERRNO_LP_CORE_BIT_MAP_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x75)

/**
  * @ingroup sre_lp
  * ���LP�����붨��: ��̬LP��Ԫ��û�а�1������
  *
  * ֵ: 0x02001e76
  *
  *�������:��̬��һ��LP�ļ��У����밴1�������鿴LP�ļ��Ƿ���ȷ��
  */
#define OS_ERRNO_LP_PATNO_INCREASE_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x76)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��һ�����ڲ�����һ���������ݶ��ڶ����Ԫ���ڡ�
 *
 * ֵ: 0x02001e79
 *
 *�������:���鱾��Ĺ������ݶ��Ƿ��ڶ����Ԫ���ڡ�
 */
#define OS_ERRNO_LP_SHARED_SEC_IN_MULTI_UNIT               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x79)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �򲹶���LP�鲻Ϊ�������ڵ��顣
 *
 * ֵ: 0x02001e7a
 *
 *�������:��鶯̬����Դ���еĺ����Ƿ�Ϊ������Ĳ���������
 */
#define OS_ERRNO_LP_FETCH_DP_GOURP_ERROR                   SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �Ҳ���ָ������ID��Ӧ��������ID��
 *
 * ֵ: 0x02001e7b
 *
 *�������:���ָ�������ָ�������Ĺ������Ƿ����ע�ᡣ
 */
#define OS_ERRNO_LP_NOT_FIND_GROUP_ID                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �Ҳ���ָ��������Ӧ�εĶ���Ϣ��
 *
 * ֵ: 0x02001e7c
 *
 *�������:���ָ�������Ƿ��Ѿ�ע����߲�ѯ�Ķ����Ƿ�����ڵ�ǰ���С�
 */
#define OS_ERRNO_LP_NOT_FIND_GROUP_SECTION_INFO            SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����SRE_LPUnitDependedLinkGetʱ���������������uwUnitNumIn�Ĵ�СΪ0��
 *
 * ֵ: 0x02001e7d
 *
 *�������:��������uwUnitNumIn�ǲ���Ϊ0��
 */
#define OS_ERRNO_LP_DEPEND_LIST_NUM_IS_ZERO                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7d)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����SRE_LPUnitDependedLinkGetʱ���������������uwUnitNumIn�Ĵ�СС���������е�ʵ�ʴ�С��
 *
 * ֵ: 0x02001e7e
 *
 *�������:�����û�ʵ�ʵĴ�С����������������
 */
#define OS_ERRNO_LP_DEPEND_LIST_NUM_IS_LITTLE              SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7e)


/**
 * @ingroup sre_lp
 * ���LP�����붨��:��ͬGroup�䶯̬������̬���ض�֮���������ص���
 *
 * ֵ: 0x02001e7f
 *
 *�������:ͨ��SRE_LP_ERRREPORT_HOOK_FUNCPTR���Ӳ鿴LP_ERROR_REPORT_INFO��鲻ͬGroup�䶯̬������̬���ض�֮���Ƿ��������ص���
 */
#define OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_ANOTHER_GROUP    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x7f)


/**
 * @ingroup sre_lp
 * ���LP�����붨��: ͬһ��Group�ھ�̬�������������ڴ���Σ��������ݶΣ�˽�����ݶ�֮���������ص���
 *
 * ֵ: 0x02001e80
 *
 *�������:ͨ��SRE_LP_ERRREPORT_HOOK_FUNCPTR���Ӳ鿴LP_ERROR_REPORT_INFO��龲̬�������������ڵĴ���Σ��������ݶΣ�˽�����ݶ�֮����Ƿ����ص���
 */
#define OS_ERRNO_LP_SP_AREA_OVERLAY_IN_SAME_AREA          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x80)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ͬһ��Group�ڲ�ͬ��̬�������������Σ��������ݶΣ�˽�����ݶ�֮���������ص���
 *
 * ֵ: 0x02001e81
 *
 *�������:ͨ��SRE_LP_ERRREPORT_HOOK_FUNCPTR���Ӳ鿴LP_ERROR_REPORT_INFO���ͬһ��Group�ڲ�ͬ��̬�������������Σ��������ݶΣ�˽�����ݶ�֮����Ƿ����ص���
 */
#define OS_ERRNO_LP_SP_AREA_OVERLAY_IN_SAME_GROUP          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x81)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��ͬGroup�侲̬�������������Σ��������ݶΣ�˽�����ݶ�֮���������ص���
 *
 * ֵ: 0x02001e82
 *
 *�������:ͨ��SRE_LP_ERRREPORT_HOOK_FUNCPTR���Ӳ鿴LP_ERROR_REPORT_INFO��鲻ͬGroup�侲̬�������������Σ��������ݶΣ�˽�����ݶ�֮����Ƿ����ص���
 */
#define OS_ERRNO_LP_SP_AREA_OVERLAY_IN_ANOTHER_GROUP       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x82)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��ͬGroup�侲̬�������������Σ��������ݶΣ�˽�����ݶ��붯̬������̬���ض��������ص���
 *
 * ֵ: 0x02001e83
 *
 *�������:ͨ��SRE_LP_ERRREPORT_HOOK_FUNCPTR���Ӳ鿴LP_ERROR_REPORT_INFO��鲻ͬGroup�侲̬�������������Σ��������ݶΣ�˽�����ݶ��붯̬������̬���ض��������ص���
 */
#define OS_ERRNO_LP_SP_AREA_OVERLAY_IN_ANOTHER_GROUP_WITH_DLDP     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x83)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ͬһ��Group�ڶ�̬������̬���ض�֮���������ص���
 *
 * ֵ: 0x02001e84
 *
 *�������:ͨ��SRE_LP_ERRREPORT_HOOK_FUNCPTR���Ӳ鿴LP_ERROR_REPORT_INFO���ͬһ��Group�ڶ�̬������̬���ض�֮���Ƿ��������ص���
 */
#define OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_SAME_GROUP                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x84)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: DP��������������DP�ķ��š�
 *
 * ֵ: 0x02001e85
 *
 *�������:��鵱ǰ���ص�DP�Ƿ�ʹ�õ���������DP�еı������ߺ�����
 */
#define OS_ERRNO_LP_DP_DEPEND_DP_NOT_SAME_GROUP                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x85)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����ε�ַ��������ΪLOCAL L2�ڴ档
 *
 * ֵ: 0x02001e86
 *
 *�������:���GROUP��ַ�����Ƿ�ѹ���ε�ַ������LOCAL L2�ڴ档
 */
#define OS_ERRNO_LP_SHARE_SECTION_ADDR_IN_LL2                       SRE_ERRNO_OS_ERROR(OS_MID_LP,0x86)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: DL��������DP�ķ��ţ���������DP��
 *
 * ֵ: 0x02001e87
 *
 *�������:��鵱ǰ���ص�DL�Ƿ��õ���DP�еı������ߺ�����
 */
#define OS_ERRNO_LP_DL_DEPEND_DP                                    SRE_ERRNO_OS_ERROR(OS_MID_LP,0x87)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ������Ĺ�����������ص����߹�������Բ�һ�¡�
 *
 * ֵ: 0x02001e88
 *
 *�������:ͨ��ע��SRE_LPErrReportHookAdd�鿴���������������������ĸ�����������ص��������Բ�һ�¡�
 */
#define OS_ERRNO_LP_DLDP_SHARE_AREA_OVERLAY_IN_ANOTHER_GROUP        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x88)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �û����õ���Ч�˷�Χ���ô���
 *
 * ֵ: 0x02001e89
 *
 *�������:�����Ч��bit�����Ƿ��е�ǰƽ̨�����ڵĺ�����Ϊ��Ч�ˡ�
 */
#define OS_ERRNO_LP_VALID_CORE_BIT_TAB_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x89)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��Ԫ����ʧ�ܡ�
 *
 * ֵ: 0x02001e8a
 *
 *�������:���LP��Ԫ����ʱ״̬�Ƿ��#UNIT_STATE_DEACTIVATED�������ڼ���#UNIT_STATE_ACTIVATING״̬��
 */
#define OS_ERRNO_LP_ACTIVE_FAIL                                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP��Ԫȥ����ʧ�ܡ�
 *
 * ֵ: 0x02001e8b
 *
 *�������:���LP��Ԫȥ����ʱ״̬�Ƿ��#UNIT_STATE_ACTIVATED��������ȥ����#UNIT_STATE_DEACTIVATING״̬��
 */
#define OS_ERRNO_LP_DEACTIVE_FAIL                                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λʱ������֮ǰδ���ع��Ķ�̬����߶�̬������
 *
 * ֵ: 0x02001e8c
 *
 *�������:����Ƿ����֮ǰ��δ���صĶ�̬���̬������
 */
#define OS_ERRNO_LP_RESET_LOAD_FAIL                                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λ��δ���ʱ���ǹ��Ϻ�����̬��������̬����ز�����
 *
 * ֵ: 0x02001e8e
 *
 *�������:LP���˸�λ��δ���ʱ���ǹ��Ϻ˲���������̬��������̬����ز�����
 */
#define OS_ERRNO_LP_RESET_NOT_FETCH                                SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8e)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λ��δ���ʱ���ǹ��Ϻ�����̬��������̬�⼤�������
 *
 * ֵ: 0x02001e8f
 *
 *�������:LP���˸�λ��δ���ʱ���ǹ��Ϻ˲���������̬��������̬�⼤�������
 */
#define OS_ERRNO_LP_RESET_NOT_ACTIVE                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x8f)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λ��δ���ʱ������������̬��������̬��ȥ���������
 *
 * ֵ: 0x02001e90
 *
 *�������:LP���˸�λ��δ���ʱ������������̬��������̬��ȥ���������
 */
#define OS_ERRNO_LP_RESET_NOT_DEACTIVE                             SRE_ERRNO_OS_ERROR(OS_MID_LP,0x90)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λ��δ���ʱ������������̬��������̬���Ƴ�������
 *
 * ֵ: 0x02001e91
 *
 *�������:LP���˸�λ��δ���ʱ������������̬��������̬���Ƴ�������
 */
#define OS_ERRNO_LP_RESET_NOT_REMOVE                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x91)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λ��δ���ʱ��������������ע�������
 *
 * ֵ: 0x02001e92
 *
 *�������:LP���˸�λ��δ���ʱ�����ɽ��в��������Ϻ˵���ע�������
 */
#define OS_ERRNO_LP_RESET_NOT_GROUP_REG                            SRE_ERRNO_OS_ERROR(OS_MID_LP,0x92)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λ��δ���ʱ����������ȥע�������
 *
 * ֵ: 0x02001e93
 *
 *�������:LP���˸�λ��δ���ʱ�����ɽ������ȥע�������
 */
#define OS_ERRNO_LP_RESET_NOT_GROUP_UNREG                          SRE_ERRNO_OS_ERROR(OS_MID_LP,0x93)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λ����ʱ����������λ�����ĺ˲��ǹ��Ϻˡ�
 *
 * ֵ: 0x02001e94
 *
 *�������:ֻ���ù��Ϻ��������Ϻ˵ĸ�λ������
 */
#define OS_ERRNO_LP_RESET_CORE_ERR                                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0x94)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����ע������Ĺ����з����˵��˸�λ��
 *
 * ֵ: 0x03001e95
 *
 *�������:������������ʽ��λ��
 */
#define OS_ERRNO_LP_RESET_CORE_IN_REG                              SRE_ERRNO_OS_FATAL(OS_MID_LP,0x95)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����ȥע������Ĺ����з����˵��˸�λ��
 *
 * ֵ: 0x03001e96
 *
 *�������:������������ʽ��λ��
 */
#define OS_ERRNO_LP_RESET_CORE_IN_UNREG                            SRE_ERRNO_OS_FATAL(OS_MID_LP,0x96)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �������ز����Ĺ����з����˵��˸�λ��
 *
 * ֵ: 0x03001e97
 *
 *�������:������������ʽ��λ��
 */
#define OS_ERRNO_LP_RESET_CORE_IN_FETCH                            SRE_ERRNO_OS_FATAL(OS_MID_LP,0x97)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ������������Ĺ����з����˵��˸�λ��
 *
 * ֵ: 0x03001e98
 *
 *�������:������������ʽ��λ��
 */
#define OS_ERRNO_LP_RESET_CORE_IN_ACTIVE                           SRE_ERRNO_OS_FATAL(OS_MID_LP,0x98)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ����ȥ��������Ĺ����з����˵��˸�λ��
 *
 * ֵ: 0x03001e99
 *
 *�������:������������ʽ��λ��
 */
#define OS_ERRNO_LP_RESET_CORE_IN_DEACTIVE                         SRE_ERRNO_OS_FATAL(OS_MID_LP,0x99)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: �����Ƴ������Ĺ����з����˵��˸�λ��
 *
 * ֵ: 0x03001e9a
 *
 *�������:������������ʽ��λ��
 */
#define OS_ERRNO_LP_RESET_CORE_IN_REMOVE                           SRE_ERRNO_OS_FATAL(OS_MID_LP,0x9a)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��������ز�����û������������Ĺ����з����˵��˸�λ����������ȥ���û�����Ƴ��Ĺ����з����˵��˸�λ��
 *
 * ֵ: 0x03001e9b
 *
 *�������:������������ʽ��λ��
 */
#define OS_ERRNO_LP_CORE_RESET_FAIL                                SRE_ERRNO_OS_FATAL(OS_MID_LP,0x9b)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λʱ���ܴ���֮ǰδ���ڵ��顣
 *
 * ֵ: 0x02001e9c
 *
 *�������:����Ƿ���LP���˸�λʱ�򴴽���֮ǰδ���ڵ��顣
 */
#define OS_ERRNO_LP_RESET_NOT_REG_NEW_GROUP                        SRE_ERRNO_OS_ERROR(OS_MID_LP,0x9c)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP���˸�λʱ���ܼ���֮ǰ����ȴδ���ص��顣
 *
 * ֵ: 0x02001e9d
 *
 *�������:����Ƿ���LP���˸�λʱ������������δ���ء�
 */
#define OS_ERRNO_LP_RESET_ACTIVE_NOT_LOAD_UNIT                     SRE_ERRNO_OS_ERROR(OS_MID_LP,0x9d)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: LP����DP��ʱ��HOT PATCH TABLE�ռ䲻�㡣
 *
 * ֵ: 0x02001e9e
 *
 *�������:ɾ��һЩ��ʹ�õĲ��������¼��ء�
 */
#define OS_ERRNO_LP_HP_TABLE_ALLOC_FAIL                            SRE_ERRNO_OS_ERROR(OS_MID_LP,0x9e)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: ��Ҫ������Ŀ�ĺ�æ�����ܽ��ж�̬���ػ���ж�ز�����
 *
 * ֵ: 0x02001e9f
 *
 *�������:����Ƿ�����ͬһ�������в����Ķ�̬���ػ���ж�ز�����
 */
#define OS_ERRNO_LP_HANDLE_CORE_BUSY                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0x9f)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: HIDSPָ���ض�λʧ�ܡ�
 *
 * ֵ: 0x02001ea0
 *
 *�������:����ض�λ�����Ƿ������⡣
 */
#define OS_ERRNO_LP_HIDSP_RELOC_FAIL                               SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa0)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: SD6183��LPģ���NSM�ռ������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02001ea1
 *
 *�������:����NSM�ռ��ڴ档
 */
#define OS_ERRNO_LP_NSM_MEM_ALLOC_FAILED                           SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa1)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: SD6183��LPģ��δ��ɳ�ʼ����
 *
 * ֵ: 0x02001ea2
 *
 *�������:��ʼ��δ���ǰ�����ܵ��ò����ӿڡ�
 */
#define OS_ERRNO_LP_INITL_UNFINISH                                  SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa2)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: DP������DLû�м��ء�
 *
 * ֵ: 0x02001ea3
 *
 *�������:�������д򲹶��Ķ�̬���Ƿ�û�м��أ����޸�
 */
#define OS_ERRNO_LP_DP_DEPEND_DL_NOT_LOADED                         SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa3)

/**
 * @ingroup sre_lp
 * ���LP�����붨��: SD6183�ĴӺ˶�̬���̬��������ʧ�ܡ� 
 *
 * ֵ: 0x02001ea4
 *
 *�������:ͨ��ע��SRE_ErrRegHook���Ӻ˷��صľ���Ĵ����롣
 */
#define OS_ERRNO_LP_CORE_LOAD_ERROR                                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa4)

/**
 * @ingroup sre_lp
 * ���LP�����붨��:���˵Ĳ�������MMUӳ����С��СС��8K���롣
 *
 * ֵ: 0x02001ea5
 *
 *�������:�������ڴ��ڲ��������ռ������룬���д洢�򲹶�ʱ����תָ�SD6183ָ����������С8K���룬��鲹��������Ӧ�ռ�ӳ���С�Ƿ�С��8K��
 */
#define OS_ERRNO_LP_INIT_ALIGN_ERROR                                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa5)

/**
 * @ingroup sre_lp
 * ���LP�����붨��:SD6183ƽ̨����̬�����滻�ĺ�����Ϊ���򲹶��Ķ�̬�����С�
 *
 * ֵ: 0x02001ea6
 *
 *�������:��̬����ֻ���滻��Ӧ�Ķ�̬���еĺ����������滻������̬�⺯��
 */
#define OS_ERRNO_LP_DP_FUN_REPLACE_ERROR                                 SRE_ERRNO_OS_ERROR(OS_MID_LP,0xa6)

/**
 * @ingroup sre_lp
 *
 * ���ڵĽṹ���塣
 */
typedef struct DATE_STRU
{
    UINT16  uwYear;                     /**< �꣬��Χ1970~2100      */
    UINT8   ucMonth;                    /**< �£���Χ1~12           */
    UINT8   ucDate;                     /**< �գ���Χ1~31           */
} DATE_T;

/**
 * @ingroup sre_lp
 *
 * ʱ��Ľṹ���塣
 */
typedef struct TIME_STRU
{
    UINT8   ucHour;                     /**< ʱ����Χ0~23           */
    UINT8   ucMinute;                   /**< �֣���Χ0~59           */
    UINT8   ucSecond;                   /**< �룬��Χ0~59           */
    UINT8   ucPadding;                  /**< ����                   */
} TIME_T;

/**
 * @ingroup sre_lp
 * LP��Ԫ״̬ö�ٶ��塣
 * UNIT_STATE_ACTIVATING   : ���ڼ���״̬��
 * UNIT_STATE_ACTIVATED    : �Ѿ�����״̬��
 * UNIT_STATE_DEACTIVATING : ����ȥ����״̬��
 * UNIT_STATE_DEACTIVATED  : �Ѿ�ȥ����״̬��
 * UNIT_STATE_IDLE         : ����״̬��
 * UNIT_STATE_BUTT         : �Ƿ�״̬��
 */
typedef enum tagPatchState
{
    UNIT_STATE_ACTIVATED    = 0x01,      /**< ����״̬��       */
    UNIT_STATE_DEACTIVATED  = 0x02,      /**< ȥ����״̬��     */
    UNIT_STATE_IDLE         = 0x03,      /**< ����״̬��       */
    UNIT_STATE_ACTIVATING   = 0x04,      /**< �������̬��     */
    UNIT_STATE_DEACTIVATING = 0x05,      /**< ȥ�������̬��   */
    UNIT_STATE_BUTT                      /**< �Ƿ�״̬��       */
} LP_UNIT_STATE;

/**
*@ingroup sre_lp
*@brief LP״̬�洢�������Ͷ��塣
*
*@par ����:
*LP��Ԫ״̬�洢�����������Ͷ��壬��LP���ء�ȥ�������к�ȥ����ʱ���øù��ӽ���LP��Ԫ״̬�Ĵ洢��
*@attention ��
*
*@param uwImageId       [IN] ����#UINT32 ����̬���õľ���
*@param uwGroupName     [IN] ����#UINT32��ע������Ϣʱ��������
*@param uwUnitNo        [IN] ����#UINT32�����߶�����LP��Ԫ��ʱ���û�ָ���ĵ�Ԫ�š�
*@param enUnitState     [IN] ����#LP_UNIT_STATE�����߶�����LP��Ԫ��ʱ���û�ָ���ĵ�Ԫ�š�
*
*@retval #SRE_OK 0���ɹ����ء�
*@retval #OS_ERROR -1���ɹ�ʧ�ܡ�
*
*@par ����:
*sre_lp.h���ú��������������ڵ�ͷ�ļ�
*@since RTOSck V100R002C00
*@see �ޡ�
*/
typedef UINT32 (*SRE_SAVEPATCHSTATE_FUNCPTR)(UINT32 uwImageId, UINT32 uwGroupName, UINT32 uwUnitNo, LP_UNIT_STATE enUnitState);

/**
 * @ingroup sre_lp
 * LP��ע����ص�������Ϣ�ϱ��ṹ�嶨�塣
 */
typedef struct tagLPErrorReportInfo
{
    UINT32 uwCompImageId;       /* �Ƚ϶������龵��ID */
    UINT32 uwCompGroupName;     /* �Ƚ϶���������     */
    CHAR *pcCompLpName;         /* �Ƚ϶����������̬��������ΪSP_CODE,SP_SHARED,SP_PRIVATE  */
    UINT32 uwComIndex;          /* �ȽϵĶ�����       */
    UINT32 uwCompLpAddr;        /* �Ƚ϶���ʼ��ַ     */
    UINT32 uwCompLpSize;        /* �Ƚ϶γ���         */
    UINT32 uwOverlayImageId;    /* �ص��������龵��ID */
    UINT32 uwOverlayGroupName;  /* �ص�����������     */
    CHAR  *pcOverlayLpName;     /* �ص������������̬��������ΪSP_CODE,SP_SHARED,SP_PRIVATE  */
    UINT32 uwOverLayIndex;      /* �ص��εĶ�����     */
    UINT32 uwOverLayLpAddr;     /* �ص�����ʼ��ַ     */
    UINT32 uwOverLaySize;       /* �ص��γ���         */
} LP_ERROR_REPORT_INFO;

/**
*@ingroup sre_lp
*@brief ���ö��ص�������Ϣ�洢�������Ͷ��塣
*
*@par ����:
*���ö��ص�������Ϣ�洢�������Ͷ��壬����ע��ʱ�Զ��ص�����Ķ�λ��
*@attention ��
*
*@param pstErrorReportInfo     [IN] ����#LP_ERROR_REPORT_INFO��LP��ע����ص�������Ϣ�ϱ��ṹ�嶨�塣
*
*@retval VOID��
*
*@par ����:
*sre_lp.h���ú��������������ڵ�ͷ�ļ�
*@since RTOSck V100R002C00
*@see �ޡ�
*/
typedef VOID (*SRE_LP_ERRREPORT_HOOK_FUNCPTR)(LP_ERROR_REPORT_INFO *pstErrorReportInfo);

/*
 *@ingroup sre_lp
 *@brief ��̬��������̬��������̬�������о���ͳһ������Ϣ
*/
typedef struct tagImagePubInfo
{
    UINT32 uwGroupNum;      /**< �û����õ�LP������Ϣ����������              */
    UINT32 uwMaxLPUnitNum;  /**< �û����õ����Ԫ����(��̬�������� + ��̬�������� + ��̬���ؿ����)    */
    UINT32 uwLPPtNo;        /**< ��LPʹ�õ��ڴ������                        */
    UINT32 uwLPPtAddr;      /**< ��LPʹ�õ��ڴ������ʼ��ַ                  */
    UINT32 uwLPPtSize;      /**< ��LPʹ�õ��ڴ������С                      */
    UINT32 uwChipType;      /**< оƬ����,��SD6181/SD6108/SD6182��Ҫ���ø��� */
} LP_PUB_INFO;

/*
 *@ingroup sre_lp
 *@brief ���SP��������Ϣ
*/
typedef struct tagHPAreaInfo
{
    BOOL   bAreaIsShare;         /**< �������Ƿ��ڹ����ڴ�,08/81ֻ��L1��˽���ڴ棬82ֻ��Local L2��˽���ڴ� */
    UINT32 uwCodeAreaAddr;       /**< ������������ʼ��ַ         */
    UINT32 uwCodeAreaSize;       /**< ������������С             */
    UINT32 uwDataShareAreaAddr;  /**< ����������������ʼ��ַ     */
    UINT32 uwDataShareAreaSize;  /**< ����������������С         */
    UINT32 uwDataPriAreaAddr;    /**< ����˽����������ʼ��ַ     */
    UINT32 uwDataAreaSize;       /**< ������������С             */
} LP_SP_AREA_INFO;

/*
 *@ingroup sre_lp
 *@brief ���LP��̬������̬���ض�����Ϣ
*/
typedef struct tagDLDPAreaInfo
{
    CHAR  *pcSecName;            /**< �û����öε����֣������ֲ����ظ�                    */
    UINT32 uwSecAreaAddr;        /**< ����ʼ��ַ��cacheLine���루ȡCPU cacheLine��DSP cacheLine�����ֵ��������ε���ʼ��ַ����������0x40000000���� */
    UINT32 uwSecAreaSize;        /**< �δ�С����λ��byte��Ҫ��cacheLine��������           */
    BOOL   bSecShared;           /**< �Ƿ���乲�����ݶ�                                  */
} LP_DL_DP_SEC_INFO;

/**
 * @ingroup sre_lp
 * ��Ԫ����Ϣ����
 */
typedef struct tagLPGroupQueryInfo
{
    UINT32 uwTotalSize;          /**< �ε��ܴ�С             */
    UINT32 uwFreeSize;           /**< �ο��пռ���ܴ�С     */
    UINT32 uwMaxAvailableSize;   /**< �ε������ô�С       */
} LP_SEC_QUERY_INFO;

/**
 * @ingroup sre_lp
 * Load&Patchע������ö�ٶ��塣
 */
typedef enum tagLPRegType
{
    LP_TYPE_NULL  = 0,           /**< �Ƿ�LP����              */
    LP_TYPE_SP    = 1,           /**< ��̬��������            */
    LP_TYPE_DL    = 2,           /**< ��̬��������            */
    LP_TYPE_DP    = 4,           /**< ��̬��������            */
    LP_TYPE_DP_DL = 6,           /**< ��̬�����Ͷ�̬��������  */
} LP_TYPE;

/*
 *@ingroup sre_lp
 *@brief ��������Ϣ�ṹ�嶨��
*/
typedef struct tagLPDependGroupInfo
{
    UINT32 *pstDependGrpNameBuf; /**< ��������������          */
    UINT32 DependGrpNum;         /**< ���������              */
} LP_DEPEND_GROUP_INFO_S;

/*
 *@ingroup sre_lp
 *@brief ������Ԫ��Ϣ�ṹ�嶨��
*/
typedef struct tagUnitDependedInfo
{
    UINT32  uwGroupID;           /**< ע��ʱ���ص���ID                       */
    UINT32  uwUnitNo;            /**< ���߶�����LP��Ԫ��ʱ���û�ָ���ĵ�Ԫ�� */
} UNIT_DEPENDED_INFO;

/**
 * @ingroup sre_lp
 * LP��ע����Ϣ�ṹ�嶨�塣
 */
typedef struct tagLPGroupRegInfo
{
    LP_TYPE enLPType;                      /**< ��֧�ֵ�����                  (������:��̬��(SP)+��̬����(DP)����̬��(DL)����̬����(DP)����̬����(SP))               */
    UINT32 uwCoreBitTab;                   /**< �����Ч�˷�Χ��BitMap��,ÿ��bit��Ӧһ������ˣ���Ч�˲��ܿ����bin(��Xtensa��Ч)(������:��̬��+��̬��������̬�⡢��̬��������̬����)*/
    UINT32 uwPatMaxFuncNum;                /**< ��Ԫ������滻����          (������:��̬�����Ͷ�̬����)                                        */
    UINT32 uwOverTime;                     /**< ���ͬ����ʱʱ�䣬��λms      (��Xtensa��Ч)(������:��̬��������̬���ء���̬����)                */
    UINT32 uwSPDssNum;                     /**< ����֧�ֵĺ˵ĸ�����          (��Xtensa��Ч)(������:��̬����)                                    */
    UINT32 uwAreaNum;                      /**< �θ�������̬��/��̬���������߲�������������̬������ (��Xtensa��Ч)(������:��̬��+��̬��������̬�⡢��̬��������̬����)*/
    LP_SP_AREA_INFO *pstSPAreaInfo;        /**< ��̬�����Ĳ�������Ϣ          (��Xtensa��Ч)(������:��̬����)                                    */
    LP_DL_DP_SEC_INFO *pstDLDPSecInfo;     /**< ��̬�⶯̬�����Ķ���Ϣ        (��Xtensa��Ч)(������:��̬��+��̬��������̬�⡢��̬����)           */
    UINT32 uwSearchNum;                    /**< ���������                    (��Xtensa��Ч)(������:��̬��+��̬��������̬�⡢��̬����)           */
    UINT32 *puwSearchLink;                 /**< ��������������ʽ��ÿ��Ԫ�ض�Ӧһ������ (��Xtensa��Ч)(������:��̬��+��̬��������̬�⡢��̬����)  */
} LP_GROUP_REG_INFO;


/**
 * @ingroup sre_lp
 * Load&Patch����Traceö�١�
 */
typedef enum tagLPLoadTrace
{
    LP_FETCH_ACTIVE_ENTRY  = 0,              /**< osLPUnitFetchActive,���յ�������Ϣ����ʼ��̬����*/
    LP_MCPU_FETCH_ENTRY    = 1,              /**< osLPMcpuUnitFetchActive,��ʼ���˶�̬����*/
    LP_DL_FETCH_ENTRY      = 2,              /**< osLPDLFetch,��ʼ��̬�����*/
    LP_DP_FETCH_ENTRY      = 3,              /**< osLPDPFetch,��ʼ��̬��������*/
    LP_DYN_ELF_RELOCA      = 4,              /**< osLPElfFetchRelocate,����ELF�������ض�λ*/
    LP_ALL_CORE_CACHE_INV  = 5,              /**< osLPAllCoreCacheInv,��ʼ���к���ЧCACHE*/
    LP_DYN_TBL_TBL_BUILD   = 6,              /**< osLPDynSymTabBuild,��ʼ��Ӷ�̬���ŵ����ű�*/
    LP_ALL_CORE_SYN_FETCH  = 7,              /**< osLPAllCoreSynFetch,���к˿�ʼͬ�������ض�λ*/
    LP_RELOCA_AND_RELOAD   = 8,              /**< osLPRelocAndReload,�����ض�λ�Ͷμ�������*/
    LP_MMU_SEC_PROC        = 9,              /**< osLPMmuSecProc,��ʼ�ο���*/
    LP_INST_RELOCAL        = 10,             /**< osLPSecRelocBuild,��ʼָ����ض�λ*/
    LP_SEC_RELOAD          = 11,             /**< osLPReLoad,���жε�cache��Ч*/
    LP_INST_RELOC_AGAIN    = 12,             /**< osLPHidspRelocAgain,�Էǻ���bin�ķ��Ž������ض�λ��˫����������*/
    LP_ACTIVE_ENTRY        = 13,             /**< osLPActive,��ʼ��̬�⼤��*/
    LP_DL_EXC_FUN_ENTRY    = 14,             /**< osLPExcFunc,��ʼ��̬�����ں���ִ��*/
    LP_DP_REPLACE_ENTRY    = 15,             /**< osLPReplacePatch,��ʼ��̬�ⲹ�������滻*/
    LP_DL_EXC_FUN_PROC     = 16,             /**< osLPExcAMPPatch,ͬ��ִ�г���ں�����������Ϣ*/
    LP_DP_ROLL_BACK_FUN    = 17,             /**< osLPRollbackFun,���˲�������*/
    LP_DP_REPLACE_PATCH_FUN= 18,             /**< osLPReplacePatchFun,�滻��������*/
    LP_EXC_USER_FUN_OVER   = 19,             /**< osLPExcPatchFun,��̬�����ں���ִ�н���*/
    LP_ALL_CORE_FETCH_OVER = 20,             /**< osLPUnitFetchActive,��̬����ؼ�����ɿ�ʼ������Ϣ������*/
    LP_MCPU_FETCH_OVER     = 21,             /**< osLPMcpuUnitFetchActive,���˶�̬�������*/
    LP_SLAVE_REMOVE_ENTRY  = 22,             /**< osLPSlaveRemove,���յ�������Ϣ����ʼ��̬��ж��*/
    LP_REMOVE_ENTRY        = 23,             /**< osLPRemove,��ʼ��̬��ж��*/
    LP_UNIT_ROLLBACK       = 24,             /**< osLPRollback,��ʼ���˶�̬����߶�̬����*/
    LP_UNIT_DEACTIVE_START = 25,             /**< osLPDeactiveProc,���붯̬ȥ��������*/
    LP_UNIT_DEACTIVE_END   = 26,             /**< osLPDeactiveProc,ȥ�����������*/
    LP_ALL_CORE_SYN_REMOVE = 27,             /**< osLPAllCoreSynRemove,�������к˵Ķ�̬��Ԫͬ���Ƴ�*/ 
    LP_UNIT_CTRL_FREE      = 28,             /**< osLPUnitSecRollBack,���е�Ԫ���ƿ��ͷ�*/
    LP_SLAVE_REMOVE_OVER   = 29,             /**< osLPSlaveRemove,��̬��ж����ɿ�ʼ������Ϣ������*/
    LP_MCPU_REMOVE_OVER    = 30,             /**< osLPMCPURemove,���˶�̬��ж�����*/
} LP_TRACE_PHASE;


/**
 *@ingroup sre_lp
 *@brief LP��������Ϣע�ắ����
 *
 *@par ����:
 *ע��LP����Ϣ������
 *@attention
 * <ul>
 * <li>��̬���غͶ�̬����uwAreaNum��ֵ��pstDLDPSecInfo �����õĽ�������Ҫһ�¡�</li>
 * <li>��̬����uwAreaNum��ֵ��pstSPAreaInfo �����õĲ���������Ҫһ�¡�</li>
 * <li>��̬���غͶ�̬�������õĽ������ֲ���Ϊ�պ��ظ�������֮��Ҳ�����غϡ�</li>
 * <li>��̬�����Ĳ�����֮�䲻���غϣ�����Ҫ�빤�߶˱���һ�¡�</li>
 * <li>SD6182/SD6181/SD6108�������Ĵ���λ����������õĵ�ַ�ռ䲻�ܳ���0x40000000��ַ������ʹ�û�����⡣</li>
 * <li>�ӿ��о���ID����ȷ����Ҫ�û���֤��������OS_SYS_IMAGE_ID��</li>
 * <li>���ʹ�ö�̬���أ���̬��������Ҫ�򿪷��ű�ü����ء�</li>
 * <li>ARMƽֻ̨��ʹ�õ��˶�̬������</li>
 * <li>��̬���ؼ���̬��������Ϣע��ʱ��ַ�����ص���������Ҫ128�ֽڶ���(����cache line)�������ֲ����ظ���</li>
 * <li>ע��ӿ�ͨ��uwImageIdע�ᣬ���ע���������һ�·��ض�SRE_OK�������ͬһ����̬���ؼ���̬����������Ϣ��ID��</li>
 * <li>����ע��ӿ�ע��ɹ�n�Σ���Ҫ�������ע��ӿ�n�Σ���������ɾ��ע����Ϣ��</li>
 * </ul>
 *
 *@param uwImageId          [IN] ����#UINT32 ������ID��һ�������Ӧһ������BIN�� ����id (SD6182ƽ̨[0,16]��SD6181ƽ̨[0,19]��SD6108ƽ̨[0,12]��AX[0,0])����Ҫ�û���֤����ȷ�ԡ�
 *@param uwGroupName        [IN] ����#UINT32 ��������Ϣ������������Ψһ������0x0Ԥ��������BINʹ�á�
 *@param pstGroupInfo       [IN] ����#LP_GROUP_REG_INFO *������Ϣע��ָ�룬����Ϣ�����������á�����������Ч�˵ȡ�
 *@param puwGroupID         [OUT]����#UINT32*����ID����ע��ӿ�ע�����䣬������LP���ء�����Ȳ���������ʹ����ID��
 *
 *@retval #OS_ERRNO_LP_6108_6181_DLDP_INVALID              0x02001e10, 6108/6181ֻ֧�־�̬������
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                    0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_INFO_REPEAT_DIFFER                  0x02001e17���ظ�ע���LP����Ϣ��һ�¡�
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_IMAGE_ID_INVALID                    0x02001e2a������ID����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                       0x02001e0d�����Ϊ�ա�
 *@retval #OS_ERRNO_LP_BUF_NOT_ENOUGH                      0x02001e0e��LP���������Ȳ���ȷ��
 *@retval #OS_ERRNO_LP_IDENT_INVALID                       0x02001e20�����ǺϷ���LP�ļ���
 *@retval #OS_ERRNO_LP_FILE_IS_INVALID                     0x02001e16��LP�ļ����Ȳ���ȷ��
 *@retval #OS_ERRNO_LP_PACKET_CRC_INVALID                  0x02001e21��LP�ļ���crcУ��ʧ�ܡ�
 *@retval #OS_ERRNO_LP_PROTOCOL_VER_INVALID                0x02001e05��LP�ļ��ṹ��������汾�Ŵ���
 *@retval #OS_ERRNO_LP_INCLUDE_OLDFILE_FUNC_UNCOVERED      0x02001e1f��LP�����У��Ѿ����صĲ�����Ԫ���ٴμ��ص�LP��Ԫ��һ�¡�crcУ�鲻ͨ����
 *@retval #OS_ERRNO_LP_SEC_NAME_SAME                       0x02001e19����̬���أ���̬��������������ͬ��
 *@retval #OS_ERRNO_LP_SP_AREA_OVERLAY_IN_SAME_AREA        0x02001e80��ͬһ��Group�ھ�̬�������������ڴ���Σ��������ݶΣ�˽�����ݶ�֮���������ص���
 *@retval #OS_ERRNO_LP_SP_AREA_OVERLAY_IN_SAME_GROUP       0x02001e81��ͬһ��Group�ڲ�ͬ��̬�������������Σ��������ݶΣ�˽�����ݶ�֮���������ص���
 *@retval #OS_ERRNO_LP_SP_AREA_OVERLAY_IN_ANOTHER_GROUP    0x02001e82����ͬGroup�侲̬�������������Σ��������ݶΣ�˽�����ݶ�֮���������ص���
 *@retval #OS_ERRNO_LP_SP_AREA_OVERLAY_IN_ANOTHER_GROUP_WITH_DLDP 0x02001e83����ͬGroup�侲̬�������������Σ��������ݶΣ�˽�����ݶ��붯̬������̬���ض��������ص���
 *@retval #OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_SAME_GROUP     0x02001e84��ͬһ��Group�ڶ�̬������̬���ض�֮���������ص���
 *@retval #OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_ANOTHER_GROUP  0x02001e7f����ͬGroup�䶯̬������̬���ض�֮���������ص���
 *@retval #OS_ERRNO_LP_DLDP_AREA_OVERLAY_IN_ANOTHER_GROUP_WITH_SP 0x02001e73����ͬGroup�䶯̬������̬���ض��������õľ�̬�����Ĵ���Σ��������ݶλ�˽�����ݶ��������ص���
 *@retval #OS_ERRNO_LP_NOT_INITED                          0x02001e48��LPģ��δ��ʼ����û�о��������ʼ����
 *@retval #OS_ERRNO_LP_HPAREAINFO_IS_NULL                  0x02001e49����̬�����������ò�������
 *@retval #OS_ERRNO_LP_DLDPAREAINFO_IS_NULL                0x02001e4a����̬������̬���ر������ö�����
 *@retval #OS_ERRNO_LP_CFG_SEC_INVALID                     0x02001e4b����̬���ض�̬�����Ķ�������ʼ��ַ���߳������ô���
 *@retval #OS_ERRNO_LP_CFG_SEC_NAME_INVALID                0x02001e4c����̬���ض�̬�����Ķ��������ֲ���Ϊ�ա�
 *@retval #OS_ERRNO_LP_GLB_L2_ADDR                         0x02001e53��LOCAL L2��ַ����������Ϊȫ�ֵ�ַ��
 *@retval #OS_ERRNO_LP_DEPEND_SYMBOL_INITED                0x02001e55����̬���أ���̬������Ҫ�������ű�ģ�顣
 *@retval #OS_ERRNO_LP_REG_NOT_FIND_IDLE_GROUP             0x02001e71��LPע��ʱ�Ҳ����������еĹ����顣
 *@retval #OS_ERRNO_LP_REG_FUNC_NUM_INVALID                0x02001e24��LP��Ԫ�������������Ϊ0��
 *@retval #OS_ERRNO_LP_CORE_BIT_MAP_INVALID                0x02001e75��LP��������Ч�˷�Χ����
 *@retval #OS_ERRNO_LP_CODE_PUT_IN_ANOTHER_1G              0x02001e2f��LP�Ĵ�����������0x40000000��
 *@retval #OS_ERRNO_LP_CFG_CODE_INVALID                    0x02001e31����̬�����������Ĵ�������ô���
 *@retval #OS_ERRNO_LP_REG_NOT_ALIGN                       0x02001e23�����õĲ����������(��ʼ��ַ������)δ����cache line����(SD6181/SD6108Ϊ64�ֽڣ�SD6182Ϊ128�ֽ�)������˽�в�����δ����4�ֽڶ��롣
 *@retval #OS_ERRNO_LP_SHARE_SECTION_ADDR_IN_LL2           0x02001e86������ε�ַ��������ΪLOCAL L2�ڴ档
 *@retval #OS_ERRNO_LP_DLDP_SHARE_AREA_OVERLAY_IN_ANOTHER_GROUP  0x02001e88��������Ĺ�����������ص����߹�������Բ�һ�¡�
 *@retval #OS_ERRNO_LP_VALID_CORE_BIT_TAB_ERROR            0x02001e89���û����õ���Ч�˷�Χ���ô���
 *@retval #OS_ERRNO_LP_RESET_NOT_GROUP_REG                 0x02001e92��LP���˸�λ��δ���ʱ��������������ע�������
 *@retval #OS_ERRNO_LP_RESET_CORE_ERR                      0x02001e94��LP���˸�λ����ʱ����������λ�����ĺ˲��ǹ��Ϻˡ�
 *@retval #OS_ERRNO_LP_RESET_NOT_REG_NEW_GROUP             0x02001e9c��LP���˸�λʱ���ܴ���֮ǰδ���ڵ��顣
 *@retval #SRE_OK                                          0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPGroupInfoUnReg
 */
extern UINT32 SRE_LPGroupInfoReg(UINT32 uwImageId, UINT32 uwGroupName, LP_GROUP_REG_INFO *pstGroupInfo, UINT32* puwGroupID);

/**
 *@ingroup sre_lp
 *@brief LP��������Ϣȥע�ắ����
 *
 *@par ����:
 *ȥע��ָ��LP������ID��Ӧ��LP����Ϣ������
 *@attention
 * <ul>
 * <li>ȥע��ӿ��л����LP������ID���������LP��Ԫ��״̬���������LP�Ķ��ǿ��У��ſ������ע���LP��������Ϣ��</li>
 * </ul>
 *
 *@param uwGroupID [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                    0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_GROUP_ID_IN_USE                     0x02001e59��LP������ID��ʹ���У�����ȥע��ò�����Ϣ�����顣
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_RESET_NOT_GROUP_UNREG               0x02001e93��LP���˸�λ��δ���ʱ����������ȥע�������
 *@retval #SRE_OK                                          0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPGroupInfoReg
 */
extern UINT32 SRE_LPGroupInfoUnReg (UINT32 uwGroupID);

/**
 *@ingroup sre_lp
 *@brief ����LP��Ԫ״̬�Ĺ��Ӻ���ע�ᡣ
 *
 *@par ����:
 *������LP��Ԫ״̬�Ĺ���ע�ᵽ��ǰ�����С�
 *@attention
 * <ul>
 * <li>ÿ������ע��һ��LP��Ԫ״̬���湳�ӣ����ڼ�¼LP���������е�LP��Ԫ״̬��</li>
 * </ul>
 *
 *@param pfnHook [IN]����#SRE_SAVEPATCHSTATE_FUNCPTR�����油��״̬�Ĺ��Ӻ������͡�
 *
 *@retval #OS_ERRNO_LP_REG_STATESAVEHOOK_NULL            0x02001e29��ע�ᱣ�油��״̬�Ĺ��Ӻ���Ϊ�ա�
 *@retval #OS_ERRNO_LP_NOT_INITED                        0x02001e48������ģ��δ��ʼ����û�о��������ʼ����
 *@retval #SRE_OK                                        0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPGroupInfoReg
 */
extern UINT32 SRE_LPUnitStateSaveHookReg(SRE_SAVEPATCHSTATE_FUNCPTR pfnHook);

/**
 *@ingroup sre_lp
 *@brief ��̬���ػ򲹶����غ�����
 *
 *@par ����:
 *���������е�LP�ļ����ص�ָ��LP������ID��Ӧ�Ĳ���������ָ���Ķ��С�
 *@attention
 * <ul>
 * <li>1�����򲹶�������С��С��16�ֽڡ�C���Ա�������ĺ����Ѿ�����У�飬�д����뷵�أ�
 * elf�ļ����ṩ������Ա�������ĺ�����С��Ϣ�����޷��жϣ����û����б�֤������ϵͳ������쳣��</li>
 * <li>2�����������Ԫ֮����ַ������������з������þͻᰴ�ռ���˳�����������ϵ��</li>
 * <li>3��֧��C�ݹ鲹���滻������CALL�ض�λ,��֧�ֻ��ݹ鲹���滻������CALL�ض�λ,��Ϊ��ຯ���ķ��Ŵ�СΪ0��</li>
 * <li>4��ARMƽ̨�²����ļ���ʹ�õ�ȫ�ֱ������븳ֵ����ָ���λ�������-fno-common����ѡ����򲹶�����ʧ�ܣ��޷��ҵ����š�</li>
 * </ul>
 *
 *@param uwGroupID      [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param pucBuf         [IN] ����#UINT8 *��LP��Ԫ�ļ��ذ�����ʼ��ַ������ʼ��ַ����4�ֽڶ��룬��Ԫ�Ű����ڼ��ذ��С�
 *@param uwLength       [IN] ����#UINT32 ��LP��Ԫ�ļ��ذ��Ĵ�С��
 *
 *@retval #OS_ERRNO_LP_BUF_ADDR_NOT_ALIGN                  0x02001e22, ��������ַ(pucBuf)��4�ֽڶ��롣
 *@retval #OS_ERRNO_LP_SP_FLAG_INVALID                     0x02001e03����̬��������ʱ�����ļ��еı�ʾͷ��������������־��
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                    0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                0x02001e18��ָ��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                       0x02001e0d�����Ϊ�ա�
 *@retval #OS_ERRNO_LP_BUF_NOT_ENOUGH                      0x02001e0e����̬���ػ򲹶����������Ȳ���ȷ��
 *@retval #OS_ERRNO_LP_IDENT_INVALID                       0x02001e20�����ǺϷ���LP�ļ���
 *@retval #OS_ERRNO_LP_FILE_IS_INVALID                     0x02001e16����̬���ػ�LP�ļ����Ȳ���ȷ��
 *@retval #OS_ERRNO_LP_PACKET_CRC_INVALID                  0x02001e21����̬���ػ�LP�ļ���crcУ��ʧ�ܡ�
 *@retval #OS_ERRNO_LP_PROTOCOL_VER_INVALID                0x02001e05��LP�ļ��ṹ��������汾�Ŵ���
 *@retval #OS_ERRNO_LP_LOADED                              0x02001e06����̬���ػ򲹶��ļ��ظ����ء�
 *@retval #OS_ERRNO_LP_INCLUDE_OLDFILE_FUNC_UNCOVERED      0x02001e1f����̬���ػ򲹶������У��Ѿ����ص�LP��Ԫ���ٴμ��ص�LP��Ԫ��һ�¡�crcУ�鲻ͨ����
 *@retval #OS_ERRNO_LP_CALL_OFFECT_ERROR                   0x02001e1b����̬���ض�̬�������÷ǲ����滻����CALL�ض�λ����
 *@retval #OS_ERRNO_LP_REG_FUNC_NUM_INVALID                0x02001e24��LP��Ԫ�������������Ϊ0��
 *@retval #OS_ERRNO_LP_SEC_ALIGN_ERROR                     0x02001e26��ELF�ζ������
 *@retval #OS_ERRNO_LP_ITEM_SIZE_ERROR                     0x02001e28�����ű��ͷ��ÿ�����Žڵ�Ĵ�С����
 *@retval #OS_ERRNO_LP_INST_TYPE_ERROR                     0x02001e46���ض�λ���Ŷ�Ӧ��ָ�����Ͳ�֧�֡�
 *@retval #OS_ERRNO_LP_RECUR_CALL_ERROR                    0x02001e63����̬�����ݹ���ò����滻����call�ض�λʧ�ܡ�
 *@retval #OS_ERRNO_LP_NONRECUR_CALL_ERROR                 0x02001e65����̬�����ǵݹ鲹���滻����call�ض�λʧ�ܡ�
 *@retval #OS_ERRNO_LP_ELF_FILETYPE_ERROR                  0x02001e64��LP�ļ����ʹ���
 *@retval #OS_ERRNO_LP_ARM_PC24_OFFECT_ERROR               0x02001e66��24λ��������תָ���ض�λ����
 *@retval #OS_ERRNO_LP_THUMB_CALL_OFFECT_ERROR             0x02001e67��22λ��������תָ���ض�λ����
 *@retval #OS_ERRNO_LP_THUMB_JUMP8_OFFECT_ERROR            0x02001e68��9λ��������תָ���ض�λ����
 *@retval #OS_ERRNO_LP_THUMB_JUMP11_OFFECT_ERROR           0x02001e69��11λ��������תָ���ض�λ����
 *@retval #OS_ERRNO_LP_ARM_ABS16_OFFECT_ERROR              0x02001e6c��16λ������ABSָ���ض�λ����
 *@retval #OS_ERRNO_LP_ARM_ABS12_OFFECT_ERROR              0x02001e6d��12λ������ABSָ���ض�λ����
 *@retval #OS_ERRNO_LP_ARM_ABS8_OFFECT_ERROR               0x02001e6e��8λ������ABSָ���ض�λ����
 *@retval #OS_ERRNO_LP_THUMB_ABS5_OFFECT_ERROR             0x02001e6f��5λ������ABSָ���ض�λ����
 *@retval #OS_ERRNO_LP_SEC_INFO_GET_ERROR                  0x02001e41����̬���ػ�̬��������ʱ��ȡ����Ϣ����
 *@retval #OS_ERRNO_LP_FETCH_TYPE_ERROR                    0x02001e43��LP����ʱ��LP�������ͺͺ�֧�ֵ����Ͳ�����
 *@retval #OS_ERRNO_LP_FETCH_DP_GOURP_ERROR                0x02001e7a���򲹶���LP�鲻Ϊ�������ڵ��顣
 *@retval #OS_ERRNO_LP_CODE_ADDR_NOT_SUIT                  0x02001e07����̬�����ļ��д�����������еĴ���β�һ�¡�
 *@retval #OS_ERRNO_LP_DATA_ADDR_NOT_SUIT                  0x02001e07����̬�����ļ������ݶ��������еĹ������ݶλ�˽�����ݶβ�һ�¡�
 *@retval #OS_ERRNO_LP_SP_NAME_INVALID                     0x02001e04����̬�����ļ����ļ�������ȷ��
 *@retval #OS_ERRNO_LP_CRC_INVALID                         0x02001e02��LP��ԪcrcУ��ʧ�ܡ�
 *@retval #OS_ERRNO_LP_CODE_PUT_IN_ANOTHER_1G              0x02001e2f��LP�Ĵ�����������0x40000000��
 *@retval #OS_ERRNO_LP_SP_NOT_LOADED                       0x02001e27����̬��������LP��Ԫû�б����ء�
 *@retval #OS_ERRNO_LP_SECTAB_MEM_ERROR                    0x02001e4d���������ڴ��������
 *@retval #OS_ERRNO_LP_SYM_BUILD_ERROR                     0x02001e52����ʱ���ű����ɴ���
 *@retval #OS_ERRNO_LP_FUNC_OVERFLOW                       0x02001e15����̬�������߶�̬�������صĲ������������������������ơ�
 *@retval #OS_ERRNO_LP_CODE_OVER_FLOW                      0x02001e12����̬������Ԫ����ο�ʼ��ַС�ڲ�����������׵�ַ�����߾�̬������Ԫ����γ�������������η�Χ��
 *@retval #OS_ERRNO_LP_DATA_OVER_FLOW                      0x02001e13����̬������Ԫ���ݶο�ʼ��ַС�ڲ��������ݶ��׵�ַ�����߾�̬������Ԫ���ݶγ������������ݶη�Χ��
 *@retval #OS_ERRNO_LP_DP_DEPEND_DP_NOT_SAME_GROUP         0x02001e85��DP��������������DP�ķ��š�
 *@retval #OOS_ERRNO_LP_DL_DEPEND_DP                       0x02001e87��DL��������DP�ķ��ţ���������DP��
 *@retval #OS_ERRNO_LP_RESET_LOAD_FAIL                     0x02001e8c��LP���˸�λʱ������֮ǰδ���ع��Ķ�̬����߶�̬������
 *@retval #OS_ERRNO_LP_RESET_NOT_FETCH                     0x02001e8e��LP���˸�λ��δ���ʱ���ǹ��Ϻ�����̬��������̬����ز�����
 *@retval #OS_ERRNO_LP_RESET_CORE_ERR                      0x02001e94��LP���˸�λ����ʱ����������λ�����ĺ˲��ǹ��Ϻˡ�
 *@retval #SRE_OK                                          0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPUnitRemove
 */
extern UINT32 SRE_LPUnitFetch(UINT32 uwGroupID, UINT8 *pucBuf, UINT32 uwLength);

/**
 *@ingroup sre_lp
 *@brief ��̬���ذ��򲹶��Ƴ�������
 *
 *@par ����:
 *ɾ��ָ��LP������ID��Ӧ��ָ��������̬���ص�Ԫ��ͬʱɾ�������ڸ�LP��Ԫ�ŵ����в�����̬���ص�Ԫ��
 *@attention
 * <ul>
 * <li>��Ϊɾ����(������̬����)��Ԫû�б��ݣ�����ɾ��ʧ��ʱ�ѱ�ɾ���������ĵ�Ԫ���ᱻ���ˡ�</li>
 * </ul>
 *
 *@param uwGroupID     [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param uwUnitNo      [IN] ����#UINT32 �����߶�����LP��Ԫ��ʱ���û�ָ���ĵ�Ԫ�š�
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_NOT_LOADED                         0x02001e09����̬���ػ򲹶���Ԫδ���ء�
 *@retval #OS_ERRNO_LP_MEM_NOT_ENOUGH                     0x02001e0f���ڴ�����ʧ�ܣ�LP������������Ҫ��̬�����ڴ档
 *@retval #OS_ERRNO_LP_RESET_NOT_REMOVE                   0x02001e91��LP���˸�λ��δ���ʱ������������̬��������̬���Ƴ�������
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPUnitFetch
 */
extern UINT32 SRE_LPUnitRemove(UINT32 uwGroupID, UINT32 uwUnitNo);

/**
 *@ingroup sre_lp
 *@brief ��̬���ػ򲹶��������
 *
 *@par ����:
 *����ָ��LP������ID��ָ��LP��Ԫ��ͬʱ�����LP��Ԫ������������LP��Ԫ��
 *@attention
 * <ul>
 * <li>���ڲ�����˵�������ʵ�ֺ����滻�����ڶ�̬���ؼ�����ִ�ж�̬���ص���ں��� ��</li>
 * </ul>
 *
 *@param uwGroupID     [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param uwUnitNo      [IN] ����#UINT32 �����߶�����LP��Ԫ��ʱ���û�ָ���ĵ�Ԫ�ţ���ȡֵ��Χ[1,9999]��
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_NO_INVALID                         0x02001e01����̬���ػ򲹶���Ԫ�Ŵ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_NOT_LOADED                         0x02001e09����̬���ػ򲹶���Ԫδ���ء�
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d�����Ϊ�ա�
 *@retval #OS_ERRNO_LP_MEM_NOT_ENOUGH                     0x02001e0f���ڴ�����ʧ�ܣ�LP������������Ҫ��̬�����ڴ档
 *@retval #OS_ERRNO_LP_IS_ACTIVE                          0x02001e0a����̬���ص�Ԫ�򲹶���Ԫ�Ѿ����ڼ���״̬��
 *@retval #OS_ERRNO_LP_IS_RUNNING                         0x02001e0b����̬���ص�Ԫ�򲹶���Ԫ�Ѿ���������״̬��
 *@retval #OS_ERRNO_LP_ALLOC_COMM_MEM_FAIL                0x02001e1d��ͬ������������Ĺ����ڴ�ʧ�ܡ�
 *@retval #OS_ERRNO_LP_SET_PARA_FAIL                      0x02001e1e������ͬ������ʧ�ܡ�
 *@retval #OS_ERRNO_LP_ACTIVE_FAIL                        0x02001e8a��LP��Ԫ����ʧ�ܡ�
 *@retval #OS_ERRNO_LP_RESET_NOT_ACTIVE                   0x02001e8f��LP���˸�λ��δ���ʱ���ǹ��Ϻ�����̬��������̬�⼤�������
 *@retval #OS_ERRNO_LP_RESET_CORE_ERR                     0x02001e94��LP���˸�λ����ʱ����������λ�����ĺ˲��ǹ��Ϻˡ�
 *@retval #OS_ERRNO_LP_RESET_ACTIVE_NOT_LOAD_UNIT         0x02001e9d��LP���˸�λʱ���ܼ���֮ǰ����ȴδ���ص��顣
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPUnitDeactive
 */
extern UINT32 SRE_LPUnitActive(UINT32 uwGroupID, UINT32 uwUnitNo);

/**
 *@ingroup sre_lp
 *@brief ��̬���ػ򲹶�ȥ�������
 *
 *@par ����:
 *ȥ����ָ��LP������ID��ָ��LP��Ԫ��ͬʱȥ���������ڸ�LP��Ԫ�ŵ�����LP��Ԫ��
 *@attention
 * <ul>
 * <li>���ڲ���ȥ��������ǽ��к����滻�����ڶ�̬����ȥ������ִ�ж�̬���ص��˳�������</li>
 * </ul>
 *
 *@param uwGroupID     [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param uwUnitNo      [IN] ����#UINT32 �����߶�����LP��Ԫ��ʱ���û�ָ���ĵ�Ԫ�ţ���ȡֵ��Χ[1, 9999]��
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_NO_INVALID                         0x02001e01����̬���ػ򲹶���Ԫ�Ŵ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_NOT_LOADED                         0x02001e09����̬���ػ򲹶���Ԫδ���ء�
 *@retval #OS_ERRNO_LP_MEM_NOT_ENOUGH                     0x02001e0f���ڴ�����ʧ�ܣ�LP������������Ҫ��̬�����ڴ档
 *@retval #OS_ERRNO_LP_IS_DEACTIVE                        0x02001e0c����̬���ػ򲹶���Ԫ�Ѿ�����ȥ����״̬��
 *@retval #OS_ERRNO_LP_IS_RUNNING                         0x02001e0b����̬���ػ򲹶���Ԫ�Ѿ���������״̬��
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d�����ָ��Ϊ�ա�
 *@retval #OS_ERRNO_LP_ALLOC_COMM_MEM_FAIL                0x02001e1d��ͬ������������Ĺ����ڴ�ʧ�ܡ�
 *@retval #OS_ERRNO_LP_SET_PARA_FAIL                      0x02001e1e������ͬ������ʧ�ܡ�
 *@retval #OS_ERRNO_LP_START_SYN_FAIL                     0x02001e1a��ͬ������ʧ�ܡ�
 *@retval #OS_ERRNO_LP_DEACTIVE_SYN_PHASE_FAIL            0x02001e1c��ͬ���׶β���ʧ�ܡ�
 *@retval #OS_ERRNO_LP_DEACTIVE_FAIL                      0x02001e8b��LP��Ԫȥ����ʧ�ܡ�
 *@retval #OS_ERRNO_LP_RESET_NOT_DEACTIVE                 0x02001e90��LP���˸�λ��δ���ʱ������������̬��������̬��ȥ���������
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPUnitActive
 */
extern UINT32 SRE_LPUnitDeactive(UINT32 uwGroupID, UINT32 uwUnitNo);

/**
 *@ingroup sre_lp
 *@brief ��̬���ػ�̬��������Ϣ��ѯ
 *
 *@par ����:
 *��ѯָ��LP������ID�еĶ�̬���ػ�̬�����λ�����Ϣ��
 *@attention
 * <ul>
 * <li>ֻ֧�ֶ�̬���ؼ���̬����(DL&DP)��</li>
 * <li>��֧��CORTEX-AXƽ̨��</li>
 * </ul>
 *@param uwGroupID      [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param pcSecName      [IN] ����#CHAR * ����ѯ�Ķ�����
 *@param pstSecInfo     [OUT] ����#LP_SEC_QUERY_INFO *���������Ϣ��ѯ�����ָ�롣
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_SEC_INFO_QUERY_LP_TYPE_INVALID     0x02001e25����ѯ��̬���ػ�̬�����Ķ���Ϣʱָ��LP���LP���ʹ���
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d�����ָ��Ϊ�ա�
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPSectionInfoGet(UINT32 uwGroupID, CHAR *pcSecName, LP_SEC_QUERY_INFO *pstSecInfo);

/**
 *@ingroup sre_lp
 *@brief �Ѽ��صĴ���ĳ״̬�Ķ�̬���ذ��򲹶�������ѯ������
 *
 *@par ����:
 *��ѯ�Ѽ��ص�ָ��LP������ID�д���ĳ״̬��̬���ذ��򲹶���Ԫ������
 *@attention ��
 *
 *@param uwGroupID     [IN] ����#UINT32 ����̬���ؼ�����������Ϣ��ID����Ҫ�û���֤����ȷ�ԡ�
 *@param enUnitState   [IN] ����#LP_UNIT_STATE ����Ԫ״̬��֧�� UNIT_STATE_ACTIVATED(����)�� UNIT_STATE_DEACTIVATED(ȥ����)��
 *@param puwUnitNum    [OUT] ����#UINT32 *����ѯ���ĵ�Ԫ����
 *
 *@retval #[0, ���õ����LP��Ԫ����]��ĳLP��Ԫ״̬���Ԫ�����������õ����LP��Ԫ����Ϊ9999��
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d�����ָ��Ϊ�ա�
 *@retval #OS_ERRNO_LP_STATE_INVALID                      0x02001e39�������LP��Ԫ״̬����ȷ��
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPGetNumByState(UINT32 uwGroupID, LP_UNIT_STATE enUnitState, UINT32 *puwUnitNum);

/**
 *@ingroup sre_lp
 *@brief �Ѽ��صĶ�̬���ص�Ԫ�򲹶���Ԫ������ѯ������
 *
 *@par ����:
 *��ѯ�Ѽ��ص�ָ��LP������ID���Ѽ��صĶ�̬���ص�Ԫ�򲹶���Ԫ�ܸ�����
 *@attention ��
 *
 *@param uwGroupID     [IN] ����#UINT32 ��LP������ID����Ҫ�û���֤����ȷ�ԡ�
 *@param puwUnitNum    [OUT] ����#UINT32 *����ѯ���ĵ�Ԫ����
 *
 *@retval #[0, ���õ����LP��Ԫ����]����ȡ������Ԫ�ĸ����������õ����LP��Ԫ����Ϊ9999��
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d�����ָ��Ϊ�ա�
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPGetTotalNum(UINT32 uwGroupID, UINT32 *puwUnitNum);

/**
 *@ingroup sre_lp
 *@brief ��̬���ص�Ԫ�򲹶���Ԫ״̬��ѯ������
 *
 *@par ����:
 *��ѯָ��LP������ID��ָ��������Ԫ��̬���ص�Ԫ��״̬��
 *@attention ��
 *
 *@param uwGroupID     [IN]  ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param uwUnitNo      [IN]  ����#UINT32�� ���߶�����LP��Ԫ��ʱ���û�ָ���ĵ�Ԫ�ţ���ȡֵ��Χ[1,9999]��
 *@param penUnitState  [OUT] ����#LP_UNIT_STATE *���õ�Ԫ״̬����ָ�롣
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72������������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18������������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d�����油��״̬��ָ��Ϊ�ա�
 *@retval #OS_ERRNO_LP_NOT_LOADED                         0x02001e09����LP��Ԫδ���ء�
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPGetUnitState(UINT32 uwGroupID, UINT32 uwUnitNo, LP_UNIT_STATE *penUnitState);

/**
 *@ingroup sre_lp
 *@brief ��̬���ػ򲹶��������汾��Ϣ��ѯ������
 *
 *@par ����:
 *��ѯָ��LP������ID�е�LPЭ�������汾��Ϣ(����ǹ��߶�����LP�ļ�ʱ��".o"�ļ������".pat"��Э���ʽ�汾������μ���".pat"�ļ�ʱ��Ҫƥ���Э���ʽ)��
 *@attention ��
 *
 *@param uwImageID       [IN]  ����#UINT32 ����̬���õľ���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param pucImageVersion [OUT] ����#UCHAR * ����汾��Ϣ��ѯ���ָ�롣
 *@param uwLength        [IN] ����#UINT32 ������汾��Ϣ��С��
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d�����ָ��Ϊ�ա�
 *@retval #OS_ERRNO_LP_BUF_NOT_ENOUGH                     0x02001e0e�����������Ȳ�����
 *@retval #OS_ERRNO_LP_IMAGE_ID_INVALID                   0x02001e2a������ID����
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPGetVersion(UINT32 uwImageID, UCHAR *pucImageVersion, UINT32 uwLength);

/**
 *@ingroup sre_lp
 *@brief ��̬�����������ʹ�������ѯ��
 *
 *@par ����:
 *��ѯָ��LP������ID�е�ָ���������Ĵ����ʹ����������ز���������ռ��ʹ�ó��ȡ�
 *@attention
 * <ul>
 * <li>ֻ֧�־�̬����(SP)��</li>
 * </ul>
 *
 *@param uwGroupID      [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param uwPatAreaNo    [IN] ����#UINT32 �����߶�����������ʱ���û�ָ���Ĳ�������š�
 *@param puwLen         [OUT] ����#UINT32 * ��ѯ�����ܳ���ָ�롣
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d������ָ��Ϊ�ա�
 *@retval #OS_ERRNO_LP_AREA_NO_INVALID                    0x02001e35�������������Ŵ���
 *@retval #OS_ERRNO_LP_SP_TYPE_ERROR                      0x02001e11����ѯ���صĴ�������ݳ���ʱָ����LP���Ͳ��Ϸ�����
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPGetLoadShareDataLen | SRE_LPGetLoadDataLen
 */
extern UINT32 SRE_LPGetLoadCodeLen(UINT32 uwGroupID, UINT32 uwPatAreaNo, UINT32 *puwLen);

/**
 *@ingroup sre_lp
 *@brief ��̬�������������ݶ�ʹ�������ѯ��
 *
 *@par ����:
 *��ѯָ������������ID�е�ָ���������Ĺ������ݶ�ʹ����������ز������������ݿռ��ʹ�ó��ȡ�
 *@attention
 * <ul>
 * <li>ֻ֧�־�̬����(SP)��</li>
 * </ul>
 *
 *@param uwGroupID      [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param uwPatAreaNo    [IN] ����#UINT32 �����߶�����������ʱ���û�ָ���Ĳ�������š�
 *@param puwLen         [OUT] ����#UINT32 * ��ѯ�����ܳ���ָ�롣
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d������ָ��Ϊ�ա�
 *@retval #OS_ERRNO_LP_AREA_NO_INVALID                    0x02001e35�������������Ŵ���
 *@retval #OS_ERRNO_LP_SP_TYPE_ERROR                      0x02001e11����ѯ���صĴ�������ݳ���ʱָ����LP���Ͳ��Ϸ�����
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPGetLoadCodeLen | SRE_LPGetLoadDataLen
 */
extern UINT32 SRE_LPGetLoadShareDataLen(UINT32 uwGroupID, UINT32 uwPatAreaNo, UINT32 *puwLen);

/**
 *@ingroup sre_lp
 *@brief ��̬������˽�����ݶ�ʹ�������ѯ��
 *
 *@par ����:
 *��ѯָ��LP������ID�е�ָ����������˽�����ݶ�ʹ����������ز�����˽�����ݿռ��ʹ�ó��ȡ�
 *@attention
 * <ul>
 * <li>ֻ֧�־�̬����(SP)��</li>
 * </ul>
 *
 *@param uwGroupID      [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param uwPatAreaNo    [IN] ����#UINT32 ��SP�������š�
 *@param puwLen         [OUT] ����#UINT32 * ��ѯ�����ܳ���ָ�롣
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d������ָ��Ϊ�ա�
 *@retval #OS_ERRNO_LP_AREA_NO_INVALID                    0x02001e35��SP�������Ŵ���
 *@retval #OS_ERRNO_LP_SP_TYPE_ERROR                      0x02001e11����ѯ���صĴ�������ݳ���ʱָ����LP���Ͳ��Ϸ�����
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPGetLoadCodeLen | SRE_LPGetLoadShareDataLen
 */
extern UINT32 SRE_LPGetLoadDataLen(UINT32 uwGroupID, UINT32 uwPatAreaNo, UINT32 *puwLen);

/**
 *@ingroup sre_lp
 *@brief ��̬���ػ򲹶�ͬ������ʱ�����á�
 *
 *@par ����:
 *����ָ��LP������ID��ͬ���ĳ�ʱʱ�䣨��λ��ms����
 *@attention
 * <ul>
 * <li>���Ϊ���ó�ʱʱ��Ϊ0����������ΪĬ�ϵĳ�ʱʱ��15000ms��</li>
 * </ul>
 *
 *@param uwGroupID      [IN] ����#UINT32 ��ע��ʱ���ص���ID����Ҫ�û���֤����ȷ�ԡ�
 *@param uwOverTime     [IN] ����#UINT32 ��ͬ����ʱʱ�䣬��λΪms��
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��LP������Ϣ��δ����ʼ����
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPSetOverTime(UINT32 uwGroupID, UINT32 uwOverTime);

/**
 *@ingroup sre_lp
 *@brief ��ѯLP��Ԫ�š�
 *
 *@par ����:
 *��ȡָ��LP�ļ��������е�LP��Ԫ�š�
 *
 *@attention
 * <ul>
 * <li>����Ƕ�̬���ذ������Ƕ�̬���������ýӿڻ�ȡ�ö�̬���ذ����߲�������Ӧ��LP��Ԫ�š�</li>
 * <li>����Ǿ�̬���������ȡ�þ�̬�����������Ĳ����е����LP��Ԫ�š�</li>
 * </ul>
 *
 *@param pucBuf    [IN]  ����#UINT8*����������ַ��
 *@param uwLength  [IN]  ����#UINT32�����������ȣ�LP�ļ����ȣ���
 *@param puwUnitNo [OUT] ����#UINT32*����Ԫ�š�
 *
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                      0x02001e0d����̬���ػ򲹶�������Ϊ�ա�
 *@retval #OS_ERRNO_LP_BUF_ADDR_NOT_ALIGN                 0x02001e22, ��������ַ(pucBuf)��4�ֽڶ��롣
 *@retval #OS_ERRNO_LP_BUF_NOT_ENOUGH                     0x02001e0e����̬���ػ򲹶����������Ȳ���ȷ��
 *@retval #OS_ERRNO_LP_IDENT_INVALID                      0x02001e20�����ǺϷ���LP�ļ���
 *@retval #OS_ERRNO_LP_FILE_IS_INVALID                    0x02001e16����̬���ػ򲹶�LP�ļ����Ȳ���ȷ��
 *@retval #OS_ERRNO_LP_PACKET_CRC_INVALID                 0x02001e21��LP�ļ���crcУ��ʧ�ܡ�
 *@retval #OS_ERRNO_LP_CRC_INVALID                        0x02001e02��LP��ԪcrcУ��ʧ�ܡ�
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPGetUnitNo(UINT8* pucBuf, UINT32 uwLength, UINT32* puwUnitNo);

/**
 *@ingroup sre_lp
 *@brief ��ȡĳ��״̬������صĵ�Ԫ�š�
 *
 *@par ����:
 *��ȡָ����̬���ؼ�����LP������Ϣ��ID��ĳ��״̬��ټ��ص�LP��Ԫ�š�
 *
 *@attention ��
 *
 *@param uwGroupID     [IN] ����#UINT32����̬���ؼ�����LP������Ϣ��ID��
 *@param enUnitState   [IN] ����#LP_UNIT_STATE������ĳһ��״̬��֧�� UNIT_STATE_ACTIVATED(����)��UNIT_STATE_DEACTIVATED(ȥ����)��
 *@param puwUnitNo     [OUT] ����#UINT32*��������Ԫ�š�
 *
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                   0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED               0x02001e18��ָ����LP������δ��ʼ����
 *@retval #OS_ERRNO_LP_STATE_INVALID                      0x02001e39�������LP��Ԫ״̬����ȷ��
 *@retval #SRE_OK                                         0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPGetLastUnitNo(UINT32 uwGroupID, LP_UNIT_STATE enUnitState, UINT32* puwUnitNo);

/**
 *@ingroup sre_lp
 *@brief  ����������ѯ��ID��
 *
 *@par ����:
 *����������ѯ��ID��
 *
 *@attention ��
 *
 *@param uwImageID     [IN] ����#UINT32����̬���õľ���ID��
 *@param uwGroupName   [IN] ����#UINT32��ע��ʱ��������
 *@param puwGroupID    [OUT] ����#UINT32*����ѯ������ID��
 *
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                        0x02001e0d����̬���ػ򲹶�������Ϊ�ա�
 *@retval #OS_ERRNO_LP_IMAGE_ID_INVALID                     0x02001e2a������ID����
 *@retval #OS_ERRNO_LP_NOT_FIND_GROUP_ID                    0x02001e72���Ҳ���ָ������ID��Ӧ��������ID��
 *@retval #SRE_OK                                           0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */

extern UINT32 SRE_LPGroupIdGet (UINT32  uwImageID, UINT32  uwGroupName, UINT32  *puwGroupID);

/**
 *@ingroup sre_lp
 *@brief  ��ȡ��Ԫ�ı�������ϵ��
 *
 *@par ����:
 *��ѯָ��LP���Ӧ��LP�ⲿ��Ԫ�ŵı�������ϵ��
 *
 *@attention
 * <ul>
 * <li>����������������������˳��Ϊ���ϵ��£�������������ϵ��A��B��C������C��D��������������ΪDCBA�����洢�ռ䲻���������󽫷��ش����롣</li>
 * </ul>
 *
 *@param uwGroupID          [IN]  ����#UINT32 ��ע��ʱ���ص���ID��
 *@param uwUnitNo           [IN]  ����#UINT32 �����߶�����LP��Ԫ��ʱ���û�ָ���ĵ�Ԫ�š�
 *@param uwUnitNumIn        [IN]  ����#UINT32���������Ĵ�С���ܹ��洢�����Ԫ����
 *@param astDependedLink[]  [OUT] ����#UNIT_DEPENDED_INFO ������Ԫ�ı���������������ʽ��
 *@param puwUnitNumOut      [OUT] ����#UINT32* ���ܵı������������������ռ䲻��ʱ����ֵ������uwUnitNumIn��
 *
 *@retval #OS_ERRNO_LP_INPUT_IS_NULL                        0x02001e0d����̬���ػ�̬����������Ϊ�ա�
 *@retval #OS_ERRNO_LP_DEPEND_LIST_NUM_IS_ZERO              0x02001e7d������SRE_LPUnitDependedLinkGetʱ���������������uwUnitNumIn�Ĵ�СΪ0��
 *@retval #OS_ERRNO_LP_NO_INVALID                           0x02001e01����̬���ص�Ԫ�Ż�LP��Ԫ�Ŵ���
 *@retval #OS_ERRNO_LP_GROUP_ID_INVALID                     0x02001e72��LP������ID���Ϸ���
 *@retval #OS_ERRNO_LP_MANAGE_UNIT_NOT_USED                 0x02001e18������Ϣδ����ʼ����
 *@retval #OS_ERRNO_LP_DEPEND_LIST_NUM_IS_LITTLE            0x02001e7e�������������uwUnitNumIn�Ĵ�СС����ʵ��С��
 *@retval #OS_ERRNO_LP_NOT_LOADED                           0x02001e09����LP��Ԫδ���ء�
 *@retval #OS_ERRNO_LP_MEM_NOT_ENOUGH                       0x02001e0f���ڴ�����ʧ�ܡ�
 *@retval #SRE_OK                                           0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see ��
 */
extern UINT32 SRE_LPUnitDependedLinkGet(UINT32 uwGroupID, UINT32 uwUnitNo,  UINT32 uwUnitNumIn, UNIT_DEPENDED_INFO astDependedLink[], UINT32* puwUnitNumOut);

/**
 *@ingroup sre_lp
 *@brief ��ע������ϱ����Ӻ���ע�ᡣ
 *
 *@par ����:
 *����ע�������Ϣ�ϱ����û���
 *@attention
 * <ul>
 * </ul>
 *
 *@param pfnHook [IN]����#SRE_LP_ERRREPORT_HOOK_FUNCPTR��������ע�������Ϣ�ϱ����Ӻ������͡�
 *
 *@retval #OS_ERRNO_LP_REG_ERRREPORTHOOK_NULL            0x02001e74��ע�ᱣ��LP��Ԫ״̬�Ĺ��Ӻ���Ϊ�ա�
 *@retval #OS_ERRNO_LP_NOT_INITED                        0x02001e48��LPģ��δ��ʼ����û�о��������ʼ����
 *@retval #SRE_OK                                        0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see SRE_LPGroupInfoReg
 */
extern UINT32 SRE_LPErrReportHookAdd(SRE_LP_ERRREPORT_HOOK_FUNCPTR pfnHook);

#if(OS_OPTION_LP_CORE_RESET == YES)

/**
 *@ingroup sre_lp
 *@brief ��ɸ�λ֪ͨ�ӿڡ�
 *
 *@par ����:
 *���˸�λ��ɺ󣬵��øýӿڱ�ʾ���˸�λ��ɡ�
 *@attention
 * <ul>
 *<li>����֪ͨ�ӿڣ�������Ը�λ�����ڵ������Fetch/Active����ʱ����Ҫ������������Ч�˲��롣</li>
 *<li>���øýӿ�֪ͨOS��λ���Ѿ�����ؼ��أ���Fetch/Active����</li>
 *<li>���Ϻ˸�λ�������ɹ�ǰ�����ܶԹ��Ϻ˽��ж�̬��/��̬�����Ļָ��������ڹ��Ϻ˵Ķ�̬��/��̬����û����ȫ�ָ�ǰ������SRE_LPCoreReloadOK�����ܵ��º���ҵ�������쳣��</li>
 * </ul>
 *
 *@param  ��
 *
 *@retval ��
 *
 *@par ����:
 *sre_lp.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R002C00
 *@see
 */
extern VOID SRE_LPCoreReloadOk(VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _SRE_LP_H */

/*
 * History: \n
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
