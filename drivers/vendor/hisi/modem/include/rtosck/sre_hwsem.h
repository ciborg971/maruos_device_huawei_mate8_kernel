/**
 * @file sre_hwsem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������Ӳ���ź����Ķ���ͷ�ļ��� \n
 */

/** @defgroup SRE_hwsem Ӳ���ź���
  * @ingroup SRE_comm
  */

#ifndef _SRE_HWSEM_H
#define _SRE_HWSEM_H

#include "sre_base.h"
#include "sre_hwi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź�����Դ����:ȫ��Ӳ���ź�����Դ��
 */
#define SRE_HWSEM_SHARE_GLOBAL    0

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź�����Դ����:cluster�ڲ�Ӳ���ź�����Դ��
 */
#define SRE_HWSEM_SHARE_CLUSTER   1

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź�������ģʽ:������Ӳ���ź�����Դ��
 */
#define SRE_HWSEM_MODE_MUTEX      0

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź�������ģʽ:������Ӳ���ź�����Դ���ʡ�
 * ��ǰֻ��6181֧�ָù���ģʽ
 */
#define SRE_HWSEM_MODE_CNT        1

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺����Ӳ���ź�����Դʱ��������ַǷ���
 *
 * ֵ: 0x02002401
 *
 * �������: Ӳ���ź���������Ϊ0xFFFFFFFF��������osԤ����0xFFFFFFFE��ͻ��
 */
#define OS_ERRNO_HWSEM_NAME_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x01)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺����Ӳ���ź�����Դʱ�������ģʽ�Ƿ���
 *
 * ֵ: 0x02002402
 *
 * �������: uwMode��α����� SRE_HWSEM_MODE_MUTEX��
 */
#define OS_ERRNO_HWSEM_MODE_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x02)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺����Ӳ���ź�����Դʱ�������Ӳ���ź���IDָ��Ϊ�ա�
 *
 * ֵ: 0x02002403
 *
 * �������: ȷ�������ָ��ǿա�
 */
#define OS_ERRNO_HWSEM_ID_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x03)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺ɾ��Ӳ���ź�����Դʱ��������Ӳ���ź���ID��4λ������ȫ��Ҳ���Ǿֲ���Դ���͡�
 *
 * ֵ: 0x02002404
 *
 * �������: Ӳ���ź���ID����ͨ��SRE_HwSemCreate�ӿ����á�
 */
#define OS_ERRNO_HWSEM_NOT_ANY_TYPE               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x04)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺SD6108/SD6181ƽ̨: ɾ��Ӳ���ź�����Դʱ���������ֲ�Ӳ���ź���ID�ĵ�16λ�����������Դ������
 *
 * ֵ: 0x02002405
 *
 * �������: Ӳ���ź���ID����ͨ��SRE_HwSemCreate�ӿ����á�
 */
#define OS_ERRNO_HWSEM_LHWSEM_EXCEED_MAX          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x05)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺SD6108/SD6181ƽ̨: ɾ��Ӳ���ź�����Դʱ��������ȫ��Ӳ���ź���ID�ĵ�20λ�����������Դ������
 *
 * ֵ: 0x02002406
 *
 * �������: Ӳ���ź���ID����ͨ��SRE_HwSemCreate�ӿ����á�
 */
#define OS_ERRNO_HWSEM_GHWSEM_EXCEED_MAX          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x06)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺SD6108/SD6181ƽ̨:ɾ��Ӳ���ź�����Դʱ��������Ӳ���ź���ID��24��27λ�Ĺ���ģʽ�������Ϣ��ƥ�䡣
 *
 * ֵ: 0x02002407
 *
 * �������: Ӳ���ź���ID����ͨ��SRE_HwSemCreate����SRE_HwSemCreateById�ӿ����á�
 */
#define OS_ERRNO_HWSEM_MODE_NOT_MATCH             SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x07)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺����Ӳ���ź�����Դʱ���������޿��õ�Ӳ���ź�����Դ��
 *
 * ֵ: 0x02002408
 *
 * �������: Ӳ���ź�����Դ���ޣ�����Դ�ľ�ʱ�������ͷŲ�����Դ������ʹ�á�
 */
#define OS_ERRNO_HWSEM_EXHAUST                    SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x08)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺����Ӳ���ź�����Դʱ���������ظ�������
 *
 * ֵ: 0x02002409
 *
 * �������: ͬһӲ���ź�����Դ���ɽ����ظ�������
 */
#define OS_ERRNO_HWSEM_CREATED                     SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x09)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺ʹ��Ӳ���ź�����Դʱ����������Ӳ���ź����ѱ�ɾ������δ������
 *
 * ֵ: 0x0200240a
 *
 * �������: ����Ӳ���ź����Ƿ��Ѿ���ɾ������δ������
 */
#define OS_ERRNO_HWSEM_DELETED                    SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x0a)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺SD6183ƽ̨:VMID��bitλ���ֵ����ȷ
 *
 * ֵ: 0x0200240b
 *
 * �������: VMID��bitλ���ֵ��Χ[0,0xFF]
 */
#define OS_ERRNO_HWSEM_VMID_BIT_MAP_ERR          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x0b)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺��ȡӲ���ź���������Ϣ���ʧ�ܡ�
 *
 * ֵ: 0x02002410
 *
 * �������: �鿴����������Ӳ���ź���ID�Ƿ���ȷ��
 */
#define OS_ERRNO_HWSEM_INT_POINT_NULL             SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x10)

/**@ingroup SRE_hwsem
 * Ӳ���ź��������룺SD6108/SD6181/SD6182/SD6157ƽ̨: Ӳ���ź�����ʼ��ʱ�����������ж�ʧ��
 *
 * ֵ: 0x02002411
 *
 * �����������
 */
#define OS_ERRNO_HWSEM_INIT_FAILED                SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x11)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: SD6181ƽ̨: Ӳ���ź���ģʽ3��������ɾ��ʱ��������жϺŷǷ�
 *
 * ֵ: 0x02002412
 *
 * �������������Ϸ��жϺţ�DSP�жϺŷ�Χ[15,22]��CPU�жϺŷ�Χ[15,21]
 */
#define OS_ERRNO_HWSEM_HWINUM_INVALID             SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x12)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: SD6181ƽ̨: Ӳ���ź���ģʽ3����ʱ����Ӧ��Ӳ���ź���ID�Ѿ����жϡ�
 *
 * ֵ: 0x02002413
 *
 * �������������δ�󶨵�Ӳ���ź���ID��
 */
#define OS_ERRNO_HWSEM_INT_ISSET                  SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x13)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: SD6181ƽ̨: Ϊȫ��Ӳ���ź��������澯�ж�ʱʧ�ܡ�
 *
 * ֵ: 0x02002414
 *
 * ����������̶�ʹ��22���жϣ���ȷ�ϸ��ж���Դ�Ƿ��б���Ϊ��ռ����Դʹ�á�
 */
#define OS_ERRNO_HWSEM_GHWSEM_INIT_FAILED         SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x14)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: SD6181ƽ̨: Ӳ���ź���ģʽ3�ظ�ɾ��ʧ��
 *
 * ֵ: 0x02002415
 *
 * �����������֤Ӳ���ź���ģʽ3ɾ��ʱֻ����һ�Ρ�
 */
#define OS_ERRNO_HWSEM_REPEAT_DEL                 SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x15)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź���ȫ�ָ������ò����á�
 *
 * ֵ: 0x02002416
 *
 * ������������Ӳ���ź���ȫ�����ø����Ƿ񳬹���Χ��6108��Χ[0-27]��6181��Χ[0-339]��SD6182/SD6157/SD6183����Ч��
 */
#define OS_ERRNO_HWSEM_GLOBE_NUM_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x16)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź����ֲ��������ò����á�
 *
 * ֵ: 0x02002417
 *
 * ������������Ӳ���ź����ֲ����ø����Ƿ񳬹���Χ��6108��Χ(0-32)��6181��Χ(0-32)��SD6182/SD6157/SD6183����Ч��
 */
#define OS_ERRNO_HWSEM_LOCAL_NUM_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x17)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź�����������Ϊ�ա�
 *
 * ֵ: 0x02002418
 *
 * ������������Ӳ���ź������������Ƿ�Ϊ�ա�
 */
#define OS_ERRNO_HWSEM_CREATE_PARA_NULL           SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x18)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź������Ͳ����á�
 *
 * ֵ: 0x0200241b
 *
 * �����������������Ӳ���ź��������Ƿ���ȷ����α�����SRE_HWSEM_SHARE_GLOBAL or SRE_HWSEM_SHARE_CLUSTER��
 */
#define OS_ERRNO_HWSEM_TYPE_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x1b)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺SD6183ƽ̨: VMID��ֵ����ȷ
 *
 * ֵ: 0x0200241c
 *
 * �������: VMIDֵ�ķ�Χ[0,7]
 */
#define OS_ERRNO_HWSEM_VMID_VALUE_ERR          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x1c)


/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź�����ʼ��ʱ���ڴ���䲻�㡣
 *
 * ֵ: 0x0200241f
 *
 * �����������������˽��FSC��̬������
 */
#define OS_ERRNO_HWSEM_NO_MEMORY                  SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x1f)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź�����PEND����ʱ�������ID����
 *
 * ֵ: 0x02002420
 *
 * ��������������IDֵ�����Ǵ����ӿڷ��ص��ź���ID��
 */
#define OS_ERRNO_HWSEM_PEND_ID_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x20)


/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź�����PEND����ʱ������Ļ�ȡ�жϿ���ֵ��ָ��Ϊ�ա�
 *
 * ֵ: 0x02002421
 *
 * �����������֤��ȡ�жϿ����Ƶ�ָ��Ϊ�ǿա�
 */
#define OS_ERRNO_HWSEM_INTVALUE_NULL              SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x21)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź�����POST����ʱ�������ID����
 *
 * ֵ: 0x02002422
 *
 * ��������������IDֵ�����Ǵ����ӿڷ��ص��ź���ID��
 */
#define OS_ERRNO_HWSEM_POST_ID_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x22)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: Ӳ���ź���ע�����õĸ�����һ�´���
 *
 * ֵ: 0x02002423
 *
 * �����������Ҫ���еĺ����õĸ�����һ�¡�
 */
#define OS_ERRNO_HWSEM_NUM_NOT_SAME               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x23)

/**@ingroup SRE_hwsem
 * Ӳ���ź���������: SD6182��SD6157��SD6183ƽ̨�ϣ�Ӳ���ź�����δ�ͷţ�����ɾ����
 *
 * ֵ: 0x02002424
 *
 * �����������Ҫ���ͷŸ�Ӳ���ź�����
 */
#define OS_ERRNO_HWSEM_NOT_POST                   SRE_ERRNO_OS_ERROR(OS_MID_HWSEM,0x24)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: ����ʵ����������ʱ�����ȫ��Ӳ���ź�����ʼID�Ƿ���
 *
 * ֵ: 0x02002425
 *
 * �������: ��ȷ�������ȫ��Ӳ���ź�����ʼID�����������(SD6182Ϊ63��SD6157Ϊ31��SD6183Ϊ127)���Ҳ�����0(0��Ӳ���ź����̶���OS����ʵ���以�Ᵽ��)��
 */
#define OS_ERRNO_HWSEM_CFG_GLB_START_ID_INVALID   SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x25)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: ����ʵ����������ʱ�����ȫ��Ӳ���ź��������Ƿ���
 *
 * ֵ: 0x02002426
 *
 * �������: ��ȷ�������ȫ��Ӳ���ź���������С��3��(OS����ÿ��ʵ��ʹ��3��)��SD6182������64����SD6157������32����SD6183������128����
 */
#define OS_ERRNO_HWSEM_CFG_GLB_NUM_INVALID        SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x26)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: ����ʵ����������ʱ���õ�ȫ��Ӳ���ź�������Ƿ���
 *
 * ֵ: 0x02002427
 *
 * �������: ��ȷ�������ȫ��Ӳ���ź�����ʼ��ź͸��������������ںϷ���Χ�ڣ�SD6182:[1,63]��SD6157:[1,31], SD6183:[1,127]��
 */
#define OS_ERRNO_HWSEM_CFG_GLB_REGION_INVALID     SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x27)


/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: ����ʵ����������ʱ����ľֲ�Ӳ���ź�����ʼID����
 *
 * ֵ: 0x02002428
 *
 * �������: ��ȷ������ľֲ�Ӳ���ź�����ʼID�����������(SD6157/SD6182:15��SD6183:31)��
 */
#define OS_ERRNO_HWSEM_CFG_LOCAL_START_ID_INVALID SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x28)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: SD6182/SD6157/SD6183ƽ̨: ����ʵ����������ʱ����ľֲ�Ӳ���ź��������Ƿ���
 *
 * ֵ: 0x02002429
 *
 * �������: ��ȷ������ľֲ�Ӳ���ź�������������(SD6157/SD6182:16��SD6183:32)��
 */
#define OS_ERRNO_HWSEM_CFG_LOCAL_NUM_INVALID      SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x29)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: ����ʵ����������ʱ���õľֲ�Ӳ���ź�������Ƿ���
 *
 * ֵ: 0x0200242a
 *
 * �������: ��ȷ������ľֲ�Ӳ���ź�����ʼ��ź͸��������������䷶Χ��(SD6157/SD6182:[1,16]��SD6183:[1,32])��
 */
#define OS_ERRNO_HWSEM_CFG_LOCAL_REGION_INVALID   SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2a)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: ��λ���ߴ���ָ������ID��Ӳ���ź���ʱ�������ȫ��Ӳ���ź�������ID�Ƿ���
 *
 * ֵ: 0x0200242b
 *
 * �������: ��ȷ�������ȫ��Ӳ���ź�������ID(SD6182:[0,63],SD6157:[0,31],SD6183:[0,127])��Χ�ڣ����Ҳ���Ϊ0(��OSʹ��)�ͱ�ʵ�����Ѿ����ù���Ӳ���ź�����Դ��
 */
#define OS_ERRNO_HWSEM_GLB_PHYSICAL_ID_INVALID    SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2b)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: ��λ���ߴ���ָ������ID��Ӳ���ź���ʱ������ľֲ�Ӳ���ź�������ID�Ƿ���
 *
 * ֵ: 0x0200242c
 *
 * �������: ��ȷ������ľֲ�Ӳ���ź�������ID������Χ��(SD6157/SD6182:[0,15]��SD6183:[0,31])�����Ҳ���Ϊ��ʵ�����Ѿ����ù��ľֲ�Ӳ���ź�����Դ��
 */
#define OS_ERRNO_HWSEM_LOCAL_PHYSICAL_ID_INVALID  SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2c)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���������: ��λָ������ID��Ӳ���ź�������������Ϊ�ֲ�Ӳ���ź���ʱ�������Cluster ID�Ƿ���
 *
 * ֵ: 0x0200242d
 *
 * �������: ��λָ������ID��Ӳ���ź�������������Ϊ�ֲ�Ӳ���ź���ʱ����ȷ������������Cluster ID��(SD6182/SD6183:[0,3],SD6157:[0,0])��Χ�ڡ�
 */
#define OS_ERRNO_HWSEM_CLUSTER_ID_INVALID         SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2d)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺ɾ��Ӳ���ź�����Դʱ��������Ӳ���ź���ID�Ƿ���
 *
 * ֵ: 0x0200242e
 *
 * �������: Ӳ���ź���ID����ͨ��SRE_HwSemCreate����SRE_HwSemCreateById�ӿ����á�
 */
#define OS_ERRNO_HWSEM_DELETE_ID_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2e)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺SD6157�����ֲ�Ӳ���ź���ʧ�ܡ�
 *
 * ֵ: 0x0200242f
 *
 * �������: SD6157��12�����ڵ�clusterû�оֲ�Ӳ���ź��������������ֲ�Ӳ���ź�����
 */
#define OS_ERRNO_HWSEM_LOCAL_CTEATE_FAIL          SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x2f)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺ͨ���Ŵ���
 *
 * ֵ: 0x02002430
 *
 * �������: SD6183ƽ̨ȫ�ֵ�ͨ��������[0,15]���ֲ���ͨ��������[0,3]��
 */
#define OS_ERRNO_HWSEM_CHNO_ERR                   SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x30)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺ͨ����Ŵ���
 *
 * ֵ: 0x02002431
 *
 * �������: SD6183ƽ̨ͨ�����[0,3]��
 */
#define OS_ERRNO_HWSEM_CHGNO_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x31)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺�˺Ŵ���
 *
 * ֵ: 0x02002432
 *
 * �������: SD6183ƽ̨�ĺ˺ŷ�Χ[0,33]��
 */
#define OS_ERRNO_HWSEM_COREID_ERR                 SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x32)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺cluster ID����
 *
 * ֵ: 0x02002433
 *
 * �������: SD6183ƽ̨cluster ID��ȡֵ��[0,4],0:dsp cluster0  1:dsp clustr1 2:dsp clustr2 3:cc clustr 4:main cluster��
 */
#define OS_ERRNO_HWSEM_CLUSTER_ID_ERR             SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x33)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺ȫ��Ӳ���ź������˳���δ�ҵ���ָ����VMID�����ͨ���顣
 *
 * ֵ: 0x02002434
 *
 * �������: ���Ŀ�ĺ˵�VMID�����ú�ȫ��Ӳ���ź���ͨ����VMID�����á�
 */
#define OS_ERRNO_HWSEM_CORE_OR_GCHG_VMID_ERR       SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x34)

/**
 *@ingroup SRE_hwsem
 *Ӳ���ź���������: PEND�ѳ��е�ֱ��ģʽӲ���ź�����
 *
 *ֵ��0x03002435
 *
 *�����������Ҫ�ظ�PEND�ѳ��е�ֱ��ģʽӲ���ź�����
 */
#define OS_ERRNO_HWSEM_PEND_REPEAT                SRE_ERRNO_OS_FATAL(OS_MID_HWSEM, 0x35)

/**
 *@ingroup SRE_hwsem
 *Ӳ���ź���������: POST�����е�ֱ��ģʽӲ���ź�����
 *
 *ֵ��0x03002436
 *
 *�����������ҪPOST�����е�ֱ��ģʽӲ���ź���������PEND��POST��
 */
#define OS_ERRNO_HWSEM_POST_ILLEGAL               SRE_ERRNO_OS_FATAL(OS_MID_HWSEM, 0x36)

/**
 *@ingroup SRE_hwsem
 *Ӳ���ź���������: Ӳ���ź���PEND��ʱ��
 *
 *ֵ��0x02002437
 *
 *����������ͷ�Ӳ���ź�����Դ��
 */
#define OS_ERRNO_HWSEM_PEND_TIMEOUT               SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x37)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺�ֲ�Ӳ���ź������˳���δ�ҵ���ָ����VMID�����ͨ���顣
 *
 * ֵ: 0x02002438
 *
 * �������: ���Ŀ�ĺ˵�VMID�����ú;ֲ�Ӳ���ź���ͨ����VMID�����á�
 */
#define OS_ERRNO_HWSEM_CORE_OR_LCHG_VMID_ERR      SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x38)

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź��������룺Ӳ���ź������˳���ʱȫ�ֻ��߾ֲ���δ�ҵ���ָ����VMID�����ͨ���顣
 *
 * ֵ: 0x02002439
 *
 * �������: �鿴CDA��¼�Ĵ����룬���Ŀ�ĺ˵�VMID�����ú�ȫ�ֻ�ֲ�Ӳ���ź���ͨ����VMID�����á�
 */
#define OS_ERRNO_HWSEM_CORE_OR_CHG_VMID_ERR       SRE_ERRNO_OS_ERROR(OS_MID_HWSEM, 0x39)

#if (OS_CPU_TYPE == OS_SD6183)
/**
 * @ingroup sre_hwsem
 * Ӳ���ź�����cluster ID
 */
typedef enum tagHwSemCluster
{
    OS_HWSEM_LOCAL_CLUSTER0 = 0,/**< �ֲ�DSP cluster 0 ID  */
    OS_HWSEM_LOCAL_CLUSTER1 = 1,/**< �ֲ�DSP cluster 1 ID  */
    OS_HWSEM_LOCAL_CLUSTER2 = 2,/**< �ֲ�DSP cluster 2 ID  */
    OS_HWSEM_LOCAL_CLUSTER3 = 3,/**< �ֲ�CC cluster 0 ID   */
    OS_HWSEM_MAIN_CLUSTER = 4   /**< ȫ��Ӳ���ź�����ID     */
} OS_HWSEM_CLUSTER_E;
#endif

/**
 * @ingroup SRE_hwsem
 * ����ģʽӲ���ź�����������
 */
typedef VOID (* HWSEM_PROC_FUNC)( UINT32);


/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���ģ�鴴�������Ľṹ�嶨�塣
 */
typedef struct tagHwsemCreatePara
{
    UINT32   uwName;                         /**< Ӳ���ź������ƣ��ź�����Դ��Ψһ��ʶ  */
    UINT8    ucMode;                         /**< Ӳ���ź�����ģʽ��ģʽ��ǰ��֧�ֻ���SRE_HWSEM_MODE_MUTEX*/
    UINT8    ucType;                         /**< Ӳ���ź��������ͣ�����Ϊȫ��SRE_HWSEM_SHARE_GLOBAL��ֲ�SRE_HWSEM_SHARE_CLUSTER*/
    UINT16   usHwiNum;                       /**< ����ģʽ�жϺţ��ݲ�ʹ��  */
    HWSEM_PROC_FUNC    pfnHwsemHandler;      /**< Ӳ���ź�������ģʽ�ص��������ݲ�ʹ�� */
    UINT32   uwArg;                          /**< Ӳ���ź�������ģʽ�ص������������ݲ�ʹ�� */
} HWSEM_CREATE_PARA_S;

/**
 * @ingroup SRE_hwsem
 * Ӳ���ź���ģ��������Ϣ�Ľṹ�嶨�塣
 */
typedef struct tagHwsemModInfo
{
    UINT32 uwGMaxNum;                /**< ���֧�ֵ�ȫ��Ӳ���ź�����  */
    UINT32 uwLMaxNum;                /**< ���֧�ֵľֲ�Ӳ���ź�����  */
}HWSEM_MOD_INFO_S;

/**
 * @ingroup  SRE_hwsem
 * @brief ����Ӳ���ź�����
 *
 * @par ����:
 * �����û�ָ����ģʽ�����ͣ�����Ӳ���ź�����Դ��
 *
 * @attention
 * <ul>
 * <li>Ӳ���ź������ڶ��֮��Ļ��⡣</li>
 * <li>���������Ҫʹ��ͬһӲ���ź�����Դ����ÿ���˾�����д�����������һ��Ҫ��ͬ��</li>
 * <li>һ��Ӳ���ź�����Դ����Ӧһ��Ӳ���ź�����Դ���ʲ�ͬ��Դ��������Ͻ�����������</li>
 * <li>��ǰ��֧�ֻ������ģʽ��</li>
 * <li>������SD6108��SD6181��SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>���ڵ͹���ģʽ�£����ܻ�رղ��־ֲ�Ӳ���ź���������ʹ�þֲ�Ӳ���ź�����Դʱ����Ҫ�û���֤�ֲ�Ӳ���ź�����Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * </ul>
 *
 * @param  pstCreatePara [IN] ����#HWSEM_CREATE_PARA_S *��Ӳ���ź�������������
 * @param  puwHwSemId    [OUT] ����#UINT32 *���洢���ظ��û���Ӳ���ź����߼�ID���û�ʹ�ô�ID���к�����Ӳ���ź�����Դ�����ͷ�ɾ���Ȳ�����
 *
 * @retval #OS_ERRNO_HWSEM_NAME_INVALID         0x02002401��Ӳ���ź������Ƿ���
 * @retval #OS_ERRNO_HWSEM_ID_NULL              0x02002403�������Ӳ���ź���IDָ��Ϊ�ա�
 * @retval #OS_ERRNO_HWSEM_CREATED              0x02002409��ͬһӲ���ź�����Դ���ظ�������
 * @retval #OS_ERRNO_HWSEM_EXHAUST              0x02002408���޿��õ�Ӳ���ź�����Դ��
 * @retval #OS_ERRNO_HWSEM_CREATE_PARA_NULL     0x02002418��Ӳ���ź��������ṹ��ָ��Ϊ�ա�
 * @retval #OS_ERRNO_HWSEM_TYPE_INVALID         0x0200241b���������Դ���ͷǷ���
 * @retval #OS_ERRNO_HWSEM_MODE_INVALID         0x02002402������Ӳ���ź�����Դʱ�������ģʽ�Ƿ���
 * @retval #OS_ERRNO_HWSEM_LOCAL_CTEATE_FAIL    0x0200242f��12�˲��������ֲ�Ӳ���ź���(ֻ��SD6157оƬ��Ч)��
 * @retval #SRE_OK                              0x00000000������Ӳ���ź�����Դ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemDelete
 */
extern UINT32 SRE_HwSemCreate (HWSEM_CREATE_PARA_S *pstCreatePara, UINT32 *puwHwSemId);

/**
 * @ingroup  SRE_hwsem
 * @brief ɾ��Ӳ���ź�����
 *
 * @par ����:
 * ɾ��ָ����Ӳ���ź�����Դ��
 *
 * @attention
 * <ul>
 * <li>�������ʹ����ͬһӲ���ź�����Դ��ÿ���˾������ɾ���ӿ��ͷ���Դ��</li>
 * <li>���ڵ͹���ģʽ�£����ܻ�رղ��־ֲ�Ӳ���ź���������ɾ���ֲ�Ӳ���ź�����Դʱ����Ҫ�û���֤�ֲ�Ӳ���ź�����Դ�ɱ���������(δ���ض�)������ᵼ�º˹�����</li>
 * <li>������SD6108��SD6181��SD6182��SD6157��SD6183ƽ̨��</li>
 * </ul>
 * @param  uwHwSemId   [IN] ����#UINT32��Ӳ���ź����߼�ID��ͨ��SRE_HwSemCreate�ӿ����á�
 *
 * @retval #OS_ERRNO_HWSEM_DELETED              0x0200240a����Ӳ���ź�����Դ�ѱ�ɾ����
 * @retval #OS_ERRNO_HWSEM_NOT_ANY_TYPE         0x02002404����Ӳ���ź������ʹ���
 * @retval #OS_ERRNO_HWSEM_GHWSEM_EXCEED_MAX    0x02002406����Ӳ���ź�����Դȫ�ָ����Ƿ���
 * @retval #OS_ERRNO_HWSEM_LHWSEM_EXCEED_MAX    0x02002405����Ӳ���ź�����Դ�ֲ������Ƿ���
 * @retval #OS_ERRNO_HWSEM_INT_POINT_NULL       0x02002410����ȡӲ���ź���������Ϣ���ʧ�ܡ�
 * @retval #OS_ERRNO_HWSEM_MODE_NOT_MATCH       0x02002407����Ӳ���ź�����Դģʽ���¼��ƥ�䡣
 * @retval #OS_ERRNO_HWSEM_DELETE_ID_INVALID    0x0200242e�������Ӳ���ź����߼�ID�Ƿ���
 * @retval #OS_ERRNO_HWSEM_NOT_POST             0x02002424����Ӳ���ź�����Դ��δ�ͷš�
 * @retval #SRE_OK                              0x00000000��ɾ��Ӳ���ź�����Դ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemCreate
 */
extern UINT32 SRE_HwSemDelete(UINT32 uwHwSemId);

/**
 * @ingroup  SRE_hwsem
 * @brief ���жϲ���ȡ����Ӳ���ź�����
 *
 * @par ����:
 * ���ģʽ�£����жϻ�ȡָ���Ļ���ģʽ��Ӳ���ź�����
 *
 * @attention
 * <ul>
 * <li>���ñ��ӿں����жϡ����Pendʧ�ܣ�ϵͳ�᷵�ص����ж�֮ǰ��״̬��</li>
 * <li>Pend�ӿ�ʹ�õ����һ����Ӳ���ź��������󷵻ص�ID��</li>
 * <li>Pend�ӿ�ֻ�����ڻ���ģʽ��Ӳ���ź�����</li>
 * <li>Pend�ӿڵ��óɹ�����POST֮ǰ���ɿ��жϣ������������л������������ϵͳ�����ķ��ա�</li>
 * <li>������SD6108��SD6181��SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>���ڵ͹���ģʽ�£����ܻ�رղ��־ֲ�Ӳ���ź���������ʹ�þֲ�Ӳ���ź�����Դִ��Pend����ʱ����Ҫ�û���֤�ֲ�Ӳ���ź�����Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * </ul>
 *
 * @param  uwHwSemId   [IN]  ����#UINT32���ź���ID��
 * @param  puvIntSave  [OUT] ����#UINTPTR *�����ж�ǰ��PS״ֵ̬��
 *
 * @retval #OS_ERRNO_HWSEM_INTVALUE_NULL       0x02002421��PEND����ʱ������Ļ�ȡ�жϿ���ֵ��ָ��Ϊ�ա�
 * @retval #OS_ERRNO_HWSEM_PEND_ID_INVALID     0x02002420��PEND����ʱ�������ID����
 * @retval #OS_ERRNO_HWSEM_DELETED             0x0200240a��PEND����ʱ��Ӳ���ź���δ���������Ѿ���ɾ����
 * @retval #SRE_OK                             0x00000000��PENDӲ���ź�����Դ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemPost
 */
extern UINT32 SRE_HwSemPend(UINT32 uwHwSemId, UINTPTR *puvIntSave);

/**
 * @ingroup  SRE_hwsem
 * @brief �ָ��жϲ��ͷŻ���Ӳ���ź�����
 *
 * @par ����:
 * ���ģʽ�£��ָ��жϲ��ͷ�ָ���Ļ���ģʽ��Ӳ���ź�����
 *
 * @attention
 * <ul>
 * <li>���ӿ���Ҫ��SRE_HwSemPend����ʹ�á����ý���֮��Ὺ�жϡ�</li>
 * <li>���ӿ���Ҫʹ���߱�֤uvIntSaveֵ����ȷ�ԣ���������ϵͳ�쳣��</li>
 * <li>Post�ӿ�ʹ�õ����һ����Ӳ���ź��������󷵻ص�ID��</li>
 * <li>Post�ӿ�ֻ�����ڻ���ģʽ��Ӳ���ź�����</li>
 * <li>����Post�ӿڳɹ�֮ǰ�����ɿ��жϣ������������л������������ϵͳ�����ķ��ա�</li>
 * <li>������SD6108��SD6181��SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>���ڵ͹���ģʽ�£����ܻ�رղ��־ֲ�Ӳ���ź���������ʹ�þֲ�Ӳ���ź�����ԴPost����ʱ����Ҫ�û���֤�ֲ�Ӳ���ź�����Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * </ul>
 *
 * @param  uwHwSemId [IN] ����#UINT32���ź���ID��
 * @param  uvIntSave [IN] ����#UINTPTR�����ж�Pend����ʱ���ص�ֵ��
 *
 * @retval #OS_ERRNO_HWSEM_POST_ID_INVALID     0x02002422��POST����ʱ�������ID����
 * @retval #OS_ERRNO_HWSEM_DELETED             0x0200240a��POST����ʱ��Ӳ���ź���δ���������Ѿ���ɾ����
 * @retval #OS_ERRNO_HWSEM_POST_ILLEGAL        0x03002436��POST�����е�ֱ��ģʽӲ���ź�����
 * @retval #SRE_OK                             0x00000000��POSTӲ���ź�����Դ�ɹ���
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemPend
 */
extern UINT32 SRE_HwSemPost(UINT32 uwHwSemId, UINTPTR uvIntSave);

#if (OS_OPTION_HWSEM_DIRECT == YES)
/**
 * @ingroup  SRE_hwsem
 * @brief ��һ��ʱ���ڣ����жϲ���ȡ����Ӳ���ź�����
 *
 * @par ����:
 * ֱ��ģʽ�£���һ��ʱ���ڣ����жϻ�ȡָ���Ļ���ģʽ��Ӳ���ź�����
 *
 * @attention
 * <ul>
 * <li>���ñ��ӿں����жϡ����Pendʧ�ܣ�ϵͳ�᷵�ص����ж�֮ǰ��״̬��</li>
 * <li>Pend�ӿ�ʹ�õ����һ����Ӳ���ź��������󷵻ص�ID��</li>
 * <li>Pend�ӿ�ֻ�����ڻ���ģʽ��Ӳ���ź�����</li>
 * <li>Pend�ӿڵ��óɹ�����POST֮ǰ���ɿ��жϣ������������л������������ϵͳ�����ķ��ա�</li>
 * <li>Pend��ʱ�󷵻أ���ҵ�����о�����ʱ������󲻳���100ms������100ms��100ms����ȫF��ʾ���õȴ���</li>
 * <li>������SD6182��SD6157ƽ̨��</li>
 * </ul>
 *
 * @param  uwHwSemId   [IN]  ����#UINT32���ź���ID��
 * @param  uwTimeOut   [IN]  ����#UINT32��PEND��ʱʱ�䣬��λ��us��
 * @param  puvIntSave  [OUT] ����#UINTPTR *�����ж�ǰ��PS״ֵ̬��
 *
 * @retval #OS_ERRNO_HWSEM_INTVALUE_NULL       0x02002421��PEND����ʱ������Ļ�ȡ�жϿ���ֵ��ָ��Ϊ�ա�
 * @retval #OS_ERRNO_HWSEM_PEND_ID_INVALID     0x02002420��PEND����ʱ�������ID����
 * @retval #OS_ERRNO_HWSEM_DELETED             0x0200240a��PEND����ʱ��Ӳ���ź���δ���������Ѿ���ɾ����
 * @retval #OS_ERRNO_HWSEM_PEND_REPEAT         0x03002435��PEND�ѳ��е�ֱ��ģʽӲ���ź�����
 * @retval #OS_ERRNO_HWSEM_PEND_TIMEOUT        0x02002437��Ӳ���ź���PEND��ʱ��
 * @retval #SRE_OK                             0x00000000��PENDӲ���ź�����Դ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwSemPend
 */
extern UINT32 SRE_HwSemPendInTime(UINT32 uwHwSemId, UINT32 uwTimeOut, UINTPTR *puvIntSave);
#endif

#if (OS_CPU_TYPE == OS_SD6182 || OS_CPU_TYPE == OS_SD6157 || OS_CPU_TYPE == OS_SD6183)
/**
 * @ingroup  SRE_hwsem
 * @brief ��λָ��Ӳ���ź�������ID��Ӳ���ź�����
 *
 * @par ����:
 * ����ָ����Ӳ���ź�������ID����λӲ���ź�����Դ��
 *
 * @attention
 * <ul>
 * <li>����SD6182��SD6157��SD6183ƽ̨ʹ�á�</li>
 * <li>����SD6183ƽ̨����ӿڼ�������COMM�ļĴ����ֲ�����RAT�Ĵ���,��������ҪCOMM��RATȨ�ޡ�</li>
 * <li>���ô˽ӿ�ǰ�����û���֤����λ��Ӳ���ź����Ѿ���ɾ����</li>
 * <li>����λ��Ӳ���ź�������Ϊ0��ȫ��Ӳ���ź�����ͨ�������������õ�Ӳ���ź���(����ʵ��)��</li>
 * <li>��λ�ֲ�Ӳ���ź�����Դʱ����Ҫ�û���ָ֤���ľֲ�Ӳ���ź�����Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * </ul>
 *
 * @param  uwType       [IN] ����#UINT32����λָ������ID��Ӳ���ź������ͣ�Ϊȫ��(#SRE_HWSEM_SHARE_GLOBAL)���߾ֲ�(#SRE_HWSEM_SHARE_CLUSTER)Ӳ���ź�����
 * @param  uwClusterId  [IN] ����#UINT32��Cluster ID(��ID)��ȡֵ��ΧΪ[0,3]��
 * @param  uwHwsemPhyId [IN] ����#UINT32��Ӳ���ź�������ID��ȡֵ��ΧΪʵ�������õ�Ӳ���ź�����Դ��
 *
 * @retval #OS_ERRNO_HWSEM_TYPE_INVALID              0x0200241b���������Դ���ͷǷ���
 * @retval #OS_ERRNO_HWSEM_GLB_PHYSICAL_ID_INVALID   0x0200242b�������ȫ��Ӳ���ź���ID�Ƿ���
 * @retval #OS_ERRNO_HWSEM_CLUSTER_ID_INVALID        0x0200242d�������Cluster ID�Ƿ���
 * @retval #OS_ERRNO_HWSEM_LOCAL_PHYSICAL_ID_INVALID 0x0200242c������ľֲ�Ӳ���ź���ID�Ƿ���
 * @retval #SRE_OK                                   0x00000000����λָ������ID��Ӳ���ź�����Դ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwSemCreateById
 */
extern UINT32 SRE_HwSemReset(UINT32 uwType, UINT32 uwClusterId, UINT32 uwHwsemPhyId);

/**
 * @ingroup  SRE_hwsem
 * @brief ����ָ��Ӳ���ź�������ID��Ӳ���ź�����
 *
 * @par ����:
 * ����ָ����Ӳ���ź�������ID������Ӳ���ź�����Դ��
 *
 * @attention
 * <ul>
 * <li>����SD6182��SD6157��SD6183ƽ̨ʹ�á�</li>
 * <li>Ӳ���ź�������������֮��Ļ��⣨�˼���Ļ��⣩��</li>
 * <li>��һ��ʹ�ô˽ӿ�ǰ�������ȵ��ø�λ�ӿ�(#SRE_HwSemReset)����Ӧ��Ӳ���ź�����Դ���и�λ��</li>
 * <li>��������Ӳ���ź�������ΪOSռ�ú�ʵ���Ѿ����õ�Ӳ���ź�����Դ��</li>
 * <li>ʹ�þֲ�Ӳ���ź�����Դʱ����Ҫ�û���ָ֤���ľֲ�Ӳ���ź�����Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * </ul>
 *
 * @param  uwType       [IN] ����#UINT32������ָ������ID��Ӳ���ź������ͣ�Ϊȫ��(#SRE_HWSEM_SHARE_GLOBAL)���߾ֲ�(#SRE_HWSEM_SHARE_CLUSTER)Ӳ���ź�����
 * @param  uwHwsemPhyId [IN] ����#UINT32��Ӳ���ź�������ID��
 * @param  puwHwSemId   [OUT] ����#UINT32 *���洢���ظ��û���Ӳ���ź����߼�ID���û�ʹ�ô�ID���к�����Ӳ���ź�����Դ�����ͷ�ɾ���Ȳ�����
 *
 * @retval #OS_ERRNO_HWSEM_TYPE_INVALID              0x0200241b���������Դ���ͷǷ���
 * @retval #OS_ERRNO_HWSEM_GLB_PHYSICAL_ID_INVALID   0x0200242b�������ȫ��Ӳ���ź���ID�Ƿ���
 * @retval #OS_ERRNO_HWSEM_LOCAL_PHYSICAL_ID_INVALID 0x0200242c������ľֲ�Ӳ���ź���ID�Ƿ���
 * @retval #OS_ERRNO_HWSEM_CREATED                   0x02002409��ͬһӲ���ź�����Դ���ظ�������
 * @retval #OS_ERRNO_HWSEM_LOCAL_CTEATE_FAIL         0x0200242f��12�˲��������ֲ�Ӳ���ź���(ֻ��SD6157оƬ��Ч)��
 * @retval #SRE_OK                                   0x00000000������Ӳ���ź�����Դ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwSemCreate | SRE_HwSemReset
 */
extern UINT32 SRE_HwSemCreateById(UINT32 uwType, UINT32 uwHwsemPhyId, UINT32 *puwHwSemId);
#endif

#if (OS_CPU_TYPE == OS_SD6183)

#if (OS_OPTION_USR_PROCESS == NO)

/**
 * @ingroup  SRE_hwsem
 * @brief ����ͨ��VMID��
 *
 * @par ����:
 * ����ĳ��cluster��ĳ��ͨ��(8��Ӳ���ź���һ��ͨ��)��VMID bit��
 * @attention
 * <ul>
 * <li>����SD6183ƽ̨ʹ�á�</li>
 * <li>��MCPU(����)���ã�����Ӳ�����ϱ������жϡ�</li>
 * <li>main����֮�󣬵���Ӳ���ź�����VMID���ã�������ܳ���Ӳ���ź���VMID������ʹ�ܵ������</li>
 * </ul>
 *
 * @param  uwClusterID [IN] ����#UINT32��cluster ID��ȡֵ[0,4]������ο�#OS_HWSEM_CLUSTER_E��
 * @param  uwChNo [IN] ����#UINT32��ͨ���ţ�ȫ��Ӳ���ź���ȡֵ[0,15]���ֲ�Ӳ���ź���ȡֵ[0,3]��
 * @param  uwChVmidBitMap [IN] ����#UINT32��ͨ��VMID��8bit��ȡֵ[0,0xFF]��
 *
 * @retval #SRE_OK                          0x00000000�����óɹ���
 * @retval #OS_ERRNO_HWSEM_CLUSTER_ID_ERR   0x02002433��cluster ID����
 * @retval #OS_ERRNO_HWSEM_CHNO_ERR         0x02002430��ͨ���Ŵ���
 * @retval #OS_ERRNO_HWSEM_VMID_BIT_MAP_ERR 0x0200240b��VMID��bitλ���ֵ����ȷ��
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_HwsemIntVmidSet
 */
extern UINT32 SRE_HwsemChVmidSet(UINT32 uwClusterID, UINT32 uwChNo, UINT32 uwChVmidBitMap);

/**
 * @ingroup  SRE_hwsem
 * @brief �ж�VMID���á�
 *
 * @par ����:
 * ��������˺�����ȫ��Ӳ���ź����;ֲ�(4��cluster)Ӳ���ź������ж�VMID��
 * @attention
 * <ul>
 * <li>����SD6183ƽ̨ʹ�á�</li>
 * <li>��MCPU(����)���ã�����Ӳ�����ϱ������жϡ�</li>
 * <li>main����֮�󣬵���Ӳ���ź�����VMID���ã�������ܳ���Ӳ���ź���VMID������ʹ�ܵ������</li>
 * </ul>
 *
 * @param  uwCoreID [IN] ����#UINT32���˺ţ�ȡֵ[0,33]��
 * @param  uwIntVmidBitMap [IN] ����#UINT32��ͨ��VMID��8bit����ȡֵ[0,0xFF]��
 *
 * @retval #SRE_OK                          0x00000000�����óɹ���
 * @retval #OS_ERRNO_HWSEM_COREID_ERR       0x02002432���˺Ŵ���
 * @retval #OS_ERRNO_HWSEM_VMID_BIT_MAP_ERR 0x0200240b��VMID��bitλ���ֵ����ȷ��
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_HwsemChVmidSet
 */
extern UINT32 SRE_HwsemIntVmidSet(UINT32 uwCoreID, UINT32 uwIntVmidBitMap);

/**
 * @ingroup  SRE_hwsem
 * @brief ͨ����VMID���á�
 *
 * @par ����:
 * ��ͨ���������ȫ��Ӳ���ź����;ֲ�(4��cluster)Ӳ���ź�����ͨ����VMID��
 * @attention
 * <ul>
 * <li>����SD6183ƽ̨ʹ�á�</li>
 * <li>��MCPU(����)���ã�����Ӳ�����ϱ������жϡ�</li>
 * <li>main����֮�󣬵���Ӳ���ź�����VMID���ã�������ܳ���Ӳ���ź���VMID������ʹ�ܵ������</li>
 * </ul>
 *
 * @param  uwChgNo [IN] ����#UINT32��ͨ����ţ�ȡֵ[0,3]��
 * @param  uwChgVmid [IN] ����#UINT32��ͨ��VMID��3bit����ȡֵ[0,7]��
 *
 * @retval #SRE_OK                           0x00000000�����óɹ���
 * @retval #OS_ERRNO_HWSEM_VMID_VALUE_ERR    0x0200241c��VMID��ֵ����ȷ��
 * @retval #OS_ERRNO_HWSEM_CHGNO_ERR         0x02002431��ͨ����Ŵ���
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_HwsemChVmidSet
 */
extern UINT32 SRE_HwsemChgVmidSet(UINT32 uwChgNo, UINT32 uwChgVmid);

/**
 * @ingroup  SRE_hwsem
 * @brief ���˳������롣
 *
 * @par ����:
 * �ͷ�ָ���˳��е�Ӳ���ź����������ú˵�Ӳ���ź�����������
 * @attention
 * <ul>
 * <li>����SD6183ƽ̨ʹ�á�</li>
 * </ul>
 *
 * @param  uwCoreID [IN] ����#UINT32���˺ţ�ȡֵ[0,33]��
 *
 * @retval #SRE_OK                                  0x00000000�����سɹ���
 * @retval #OS_ERRNO_HWSEM_COREID_ERR               0x02002432���˺Ŵ���
 * @retval #OS_ERRNO_HWSEM_CORE_OR_GCHG_VMID_ERR    0x02002434��ȫ��ͨ����VMIDƥ��ʧ�ܡ�
 * @retval #OS_ERRNO_HWSEM_CORE_OR_LCHG_VMID_ERR    0x02002438���ֲ�ͨ����VMIDƥ��ʧ�ܡ�
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_HwsemPendCancel(UINT32 uwCoreID);

#endif

#endif

#if (OS_CPU_TYPE == OS_SD6181)
/**
 * @ingroup  SRE_hwsem
 * @brief ����ģʽ3Ӳ���ź�����
 *
 * @par ����:
 * Ӳ���ź���ģʽ3�����ӿڣ������жϺź��жϴ�������
 *
 * @attention
 * <ul>
 * <li>����SD6181ƽ̨ʹ�á�</li>
 * <li>Ӳ���ź���ID�Ź̶���ȡֵΪ[414-coreID*2,415-coreID*2]������</li>
 * <li>���õ��жϺţ���ѡ��Χ[15~22]��</li>
 * <li>�ýӿ�ֻ��ҪPend�˵��ô�����</li>
 * <li>�û���Ҫ���жϴ������ӿ��е���SRE_HwiClearPendingBit����жϱ�־λ��</li>
 * <li>����Ӳ������жϴ���ʱ�ӣ������û������жϷ�������������жϣ���ִ�������Ĳ������������Ա�֤���㹻��ʱ�佫�ж������</li>
 * <li>��ε���Ч�����û���֤��OS�ڲ�û�ж��ź���ID�����жϡ�</li>
 * </ul>
 *
 * @param  uwHwsemID      [IN]   ����#UINT32��ģʽ3Ӳ���ź���ID,Ӳ���ź���IDȡֵ��Χ[414-coreID*2,415-coreID*2]��
 * @param  uwHwiNum       [IN]   ����#UINT32��VIC�����жϺţ�CPUƽ̨��ѡ��Χ[15~21]��DSPƽ̨��ѡ��Χ[15~22]��
 * @param  pfnHandler     [IN]   ����#VOID *���жϴ������ӿڣ��û���Ҫ�ڸýӿ��е���SRE_HwiClearPendingBit����жϱ�־λ��
 * @param  uwArg          [IN]   ����#UINT32������Ӳ�жϴ�����ʱ���ݵĲ�����
 *
 * @retval #OS_ERRNO_HWSEM_HWINUM_INVALID       0x02002412��Ӳ���ź���ģʽ3����ʱ��������жϺŷǷ���
 * @retval #OS_ERRNO_HWSEM_INT_ISSET            0x02002413��Ӳ���ź���ģʽ3����ʱ����Ӧ��Ӳ���ź���ID�Ѿ����жϡ�
 * @retval #OS_ERRNO_HWI_PROC_FUNC_NULL         0x02001403�������Ӳ�жϴ�����Ϊ�ա�
 * @retval #OS_ERRNO_HWI_ALREADY_CREATED        0x02001402�������жϺ��Ѿ�������
 * @retval #SRE_OK                              0x00000000��Ӳ���ź���ģʽ3�����ɹ���
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemDeleteEx
 */
extern UINT32 SRE_HwSemCreateEx(UINT32 uwHwsemID, UINT32 uwHwiNum, HWI_PROC_FUNC pfnHandler, HWI_ARG_T uwArg);

/**
 * @ingroup  SRE_hwsem
 * @brief ɾ��ģʽ3Ӳ���ź�����
 *
 * @par ����:
 * Ӳ���ź���ģʽ3ɾ���ӿڣ�ɾ������ʱ���жϺš�
 *
 * @attention
 * <ul>
 * <li>����SD6181ƽ̨ʹ�ã������ɴ����������ø�ɾ���ӿڽ���ɾ������ɾ��ʱ���ź�����Դ�����Ѿ�ʹ����ϡ�</li>
 * <li>Ӳ���ź���ID�Ź̶���ȡֵΪ[414-coreID*2,415-coreID*2]������</li>
 * <li>���õ��жϺţ���ѡ��Χ[15~22]��</li>
 * <li>��ε���Ч�����û���֤��OS�ڲ�û�ж��ź���ID�����жϡ�</li>
 * </ul>
 *
 * @param  uwHwsemID      [IN]   ����#UINT32��ģʽ3Ӳ���ź���ID,Ӳ���ź���IDȡֵ��Χ[414-coreID*2,415-coreID*2]��
 * @param  uwHwiNum       [IN]   ����#UINT32��VIC�����жϺţ�CPUƽ̨��ѡ��Χ[15~21]��DSPƽ̨��ѡ��Χ[15~22]��
 *
 * @retval #OS_ERRNO_HWSEM_HWINUM_INVALID       0x02002402��Ӳ���ź���ģʽ3ɾ��ʱ��������жϺŷǷ���
 * @retval #OS_ERRNO_HWSEM_REPEAT_DEL           0x02002405��Ӳ���ź���ģʽ3ɾ���ظ�ɾ����
 * @retval #SRE_OK                              0x00000000��Ӳ���ź���ģʽ3ɾ���ɹ���
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemCreateEx
*/
extern UINT32 SRE_HwSemDeleteEx(UINT32 uwHwsemID, UINT32 uwHwiNum);

/**
 * @ingroup  SRE_hwsem
 * @brief ��ȡģʽ3Ӳ���ź�����
 *
 * @par ����:
 * ��ģʽ3Ӳ���ź�������Pend����, �趨������ֵ��
 *
 * @attention
 * <ul>
 * <li>��ģ������SD6181��Ч��</li>
 * <li>���ó�ʼ����ֵ���µļ�����ֵ�������0������ԭ���ļ������������0������ᴥ��Ӳ���ź����쳣��</li>
 * <li>Ӳ���ź���ID�Ź̶���ȡֵΪ[414-coreID*2,415-coreID*2]������</li>
 * <li>��ε���Ч�����û���֤��OS�ڲ�û�ж��ź���ID�����жϡ�</li>
 * </ul>
 *
 * @param    uwHwSemID     [IN]   ����#UINT32��ģʽ3Ӳ���ź���ID��
 * @param    uwInitCount   [IN]   ����#UINT32��ģʽ3Ӳ���ź�����ֵ��������ѡ��Χ[1~255]��
 *
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemPostEx
 */
extern VOID SRE_HwSemPendEx(UINT32 uwHwSemID, UINT32 uwInitCount);

/**
 * @ingroup  SRE_hwsem
 * @brief �ͷ�ģʽ3Ӳ���ź�����
 *
 * @par ����:
 * ��ģʽ3Ӳ���ź�������Post�������ź�����Դ�ļ���ֵ����1��������ֵΪ0ʱ���򴥷�pend���жϡ�
 *
 * @attention
 * <ul>
 * <li>��ģ������SD6181��Ч��</li>
 * <li>�����ȵ���#SRE_HwSemPendEx�ӿڣ����ܵ��øýӿڡ�</li>
 * <li>���øýӿ�ʱ�����뱣֤�ź�����Դ�ļ���ֵ��Ϊ0������ᴥ��Ӳ���ź����쳣��</li>
 * <li>Ӳ���ź���ID�Ź̶���ȡֵΪ[414-coreID*2,415-coreID*2]������</li>
 * <li>��ε���Ч�����û���֤��OS�ڲ�û�ж��ź���ID�����жϡ�</li>
 * </ul>
 *
 * @param    uwHwSemID     [IN]   ����#UINT32��ģʽ3Ӳ���ź���ID��
 *
 * @par ����:
 * <ul><li>sre_hwsem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwSemPendEx
 */
extern VOID SRE_HwSemPostEx(UINT32 uwHwSemID);
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_HWSEM_H */


