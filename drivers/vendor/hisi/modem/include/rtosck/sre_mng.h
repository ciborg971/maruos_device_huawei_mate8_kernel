/**
 * @file sre_mng.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������SRE MNG�Ķ���ͷ�ļ��� \n
 */

/** @defgroup SRE_mng SRE MNG
  * @ingroup SRE_kernel
  */

#ifndef _SRE_MNG_H
#define _SRE_MNG_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_mng
 * SRE MNGʹ�õĺ�����ṹ��
 * SD6183 ��34��Ӳ�̣߳�64bit��������
 */

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
typedef unsigned long long SRE_COREMASK;
#else
typedef unsigned int SRE_COREMASK;
#endif

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG�����VMID�Ƿ���
 *
 * ֵ: 0x02002f01
 *
 * �������: VMID��ȡֵ��Χ[0,7]��
 */
#define OS_ERRNO_SREMNG_VMID_VALUE_ERR               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x01)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����ʵ���������ʵ��ַmemmap���Ϊ�ա�
 *
 * ֵ: 0x02002f02
 *
 * �������: ���ʵ�������ӿڴ����memmap��������ȷ�Ľṹ��ָ�롣
 */
#define OS_ERRNO_SREMNG_MEMMAP_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x02)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����ĺ�bitmap���Ϊ�ա�
 *
 * ֵ: 0x02002f03
 *
 * �������: ���SREMNG�ӿڴ���ĺ�bitmap��������ȷ�Ľṹ��ָ�롣
 */
#define OS_ERRNO_SREMNG_CORE_BITMAP_NULL             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x03)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺����ʵ��ʱ������û����ʵ��ID�ĵ�ַΪ�ա�
 *
 * ֵ: 0x02002f04
 *
 * �������: ����ʵ��ʱ��ȷ��������û����ʵ��ID�ĵ�ַ��Ϊ�ա�
 */
#define OS_ERRNO_SREMNG_INST_ID_ADDR_NULL            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x04)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����ʵ������ĺ�bitmap���Ϸ�����Ϊ0��
 *
 * ֵ: 0x02002f05
 *
 * �������: ���ʵ�������ӿڴ���ĺ�bitmap��������ȷ�Ĳ�����
 */
#define OS_ERRNO_SREMNG_CORE_BITMAP_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x05)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG�����ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002f06
 *
 * �������: ����SRE MNG�����ϵͳʹ�õ��ڴ�ռ䡣
 */
#define OS_ERRNO_SREMNG_NO_MEMORY                    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x06)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNGʵ�������������࣬�޿��õ�ʵ����Դ��
 *
 * ֵ: 0x02002f07
 *
 * �������: ��ȷ�����������ʵ������������8��
 */
#define OS_ERRNO_SREMNG_INST_ID_EXHAUST             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x07)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG�����鴴��ָ���Ľ��������ͷǷ���
 *
 * ֵ: 0x02002f08
 *
 * �������: ���������������ֻ��ΪPG_TYPE_PROCESS����PG_TYPE_BMCORE��
 */
#define OS_ERRNO_SREMNG_PG_TYPE_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x08)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG�����鴴��ָ���Ļ���bin��νṹ��ΪNULL��
 *
 * ֵ: 0x02002f09
 *
 * �������: ��鴴��������Ļ���bin���ָ�벢������ȷ�Ĳ�����
 */
#define OS_ERRNO_SREMNG_BIN_PARA_NULL                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x09)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����bin���ص�elf�ļ�ͷ��εĴ�СУ����� ��
 *
 * ֵ: 0x02002f0a
 *
 * �������: ȷ������Ļ���bin�ļ���ȷ�ԡ�
 */
#define OS_ERRNO_MNG_BIN_ELF_SEC_HEAD_ERROR          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0a)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG�����ʵ��ID�Ƿ���
 *
 * ֵ: 0x02002f0b
 *
 * �������: ȷ�������ʵ��ID������ʵ��֧�ֵ����ֵ��
 */
#define OS_ERRNO_SREMNG_INSTID_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0b)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG�����ʵ��IDΪδ����ʵ����
 *
 * ֵ: 0x02002f0c
 *
 * �������: ȷ�������ʵ��IDΪ�Ѵ�����ʵ����
 */
#define OS_ERRNO_SREMNG_INSTID_UNCREATE              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0c)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG���������鴫��ĺ�bitmap����������ʵ���ĺ�bitmap��
 *
 * ֵ: 0x02002f0d
 *
 * �������: ȷ��������ĺ�bitmapΪ������ʵ�����Ӽ���
 */
#define OS_ERRNO_SREMNG_PG_COREBITMAP_OVERINST       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0d)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG������������شӺ˶�ʱ�Ҳ������õ�δӳ������������ַ�ռ䡣
 *
 * ֵ: 0x02002f0e
 *
 * �������: ȷ�����������ʱ���˵�����δӳ��ռ䲻С��10M��
 */
#define OS_ERRNO_MNG_BIN_LOAD_NO_VALID_VA            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0e)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG���ػ���bin�����ļ����Ȳ���ȷ��
 *
 * ֵ: 0x02002f0f
 *
 * �������: ȷ������Ļ���bin�������ļ��ĳ��ȵ���ȷ�ԡ�
 */
#define OS_ERRNO_MNG_BIN_LEN_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x0f)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG���ػ���bin������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002f10
 *
 * �������: ���������ʵ�����ڴ���Դ��
 */
#define OS_ERRNO_MNG_BIN_MEMALLOC_FAILED             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x10)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����bin���ص�elf�ļ�ͷУ�����
 *
 * ֵ: 0x02002f11
 *
 * �������: ȷ������Ļ���bin�ļ���ȷ�ԡ�
 */
#define OS_ERRNO_MNG_BIN_ELF_HEAD_ERROR              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x11)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����bin���ص�elf�ļ����ʹ���
 *
 * ֵ: 0x02002f12
 *
 * �������: ȷ������Ļ���bin�ļ���ȷ�ԡ�
 */
#define OS_ERRNO_MNG_BIN_ELF_FILETYPE_ERROR          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x12)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����bin���ص�elf�Ķθ�������ȷ��
 *
 * ֵ: 0x02002f13
 *
 * �������: ȷ������Ļ���bin�ļ���ȷ�ԡ�
 */
#define OS_ERRNO_MNG_BIN_ELF_SEC_NUM_ERROR           SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x13)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����bin���������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002f14
 *
 * �������: ȷ��SRE MNG����bin������ڴ��㹻��
 */
#define OS_ERRNO_MNG_BIN_MANAGE_NO_MEMORY            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x14)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����bin���ز����Ļ���bin�ļ���Ϣ����ȷ��
 *
 * ֵ: 0x02002f15
 *
 * �������: ȷ��SRE MNG����bin����ʱ����Ļ���bin�ļ���Ϣ����ȷ��,������buffer�׵�ַ��Ҫ4�ֽڶ��롣
 */
#define OS_ERRNO_SREMNG_BIN_PARA_INVALID             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x15)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬����صĶ�̬����Ϣָ��Ϊ�ա�
 *
 * ֵ: 0x02002f16
 *
 * �������: ȷ��SRE MNG��̬�����ʱ����Ķ�̬����Ϣָ�����ȷ�ԡ�
 */
#define OS_ERRNO_SREMNG_DLIB_PARA_NULL               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x16)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬����صĶ�̬����Ϣ����ȷ��
 *
 * ֵ: 0x02002f17
 *
 * �������: ȷ��SRE MNG��̬�����ʱ����Ķ�̬����Ϣָ�����ȷ��,������buffer�׵�ַ��Ҫ4�ֽڶ��롣
 */
#define OS_ERRNO_SREMNG_DLIB_PARA_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x17)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬�����ָ���Ľ�����Ƿ���
 *
 * ֵ: 0x02002f18
 *
 * �������: ȷ��SRE MNG��̬�����ʱָ���Ľ�����ŵ���ȷ�ԡ�
 */
#define OS_ERRNO_SREMNG_DLIBLOAD_PG_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x18)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNGָ���Ľ�������δ������
 *
 * ֵ: 0x02002f19
 *
 * �������: ȷ����SRE MNG����Ľ�����IDΪ�Ѵ����Ľ����顣
 */
#define OS_ERRNO_SREMNG_PG_UNCREATED                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x19)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG�����Ľ������ѱ�������
 *
 * ֵ: 0x02002f19
 *
 * �������: һ�������鲻�ܱ��ظ�����������ֹͣ����������
 */
#define OS_ERRNO_SREMNG_PG_ALREADY_STARTED           SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1a)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNGֹͣ�Ľ�������δ������
 *
 * ֵ: 0x02002f1b
 *
 * �������: ����ֹͣ��������״̬�Ľ����顣
 */
#define OS_ERRNO_SREMNG_PG_NOT_START                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1b)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG���ض�̬��ָ���ĺ�bitmap�����˽�����ĺ�bitmap��
 *
 * ֵ: 0x02002f1c
 *
 * �������: ȷ�Ͽ�ļ��غ˷�Χ��
 */
#define OS_ERRNO_SREMNG_DLIB_COREBITMAP_OVERINST     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1c)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG���ض�̬�������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002f1d
 *
 * �������: ���������ʵ�����ڴ���Դ��
 */
#define OS_ERRNO_MNG_DLIB_MEMALLOC_FAILED            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1d)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺���ض�̬��ʱ���������Ľ�����δ������
 *
 * ֵ: 0x02002f1e
 *
 * �������: �������������ټ��ض�̬�⡣
 */
#define OS_ERRNO_SREMNG_DLIBLOAD_PG_NOT_RUNNING      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1e)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNGж�ض�̬�����νṹ��ָ��Ϊ�ա�
 *
 * ֵ: 0x02002f1f
 *
 * �������: ȷ��ж�ض�̬�����νṹ��ָ�����ȷ�ԡ�
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_PARA_NULL        SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x1f)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG���صĻ���bin��δ�ҵ�OS��vecbase�Ρ�
 *
 * ֵ: 0x02002f20
 *
 * �������: ȷ�ϼ��صĻ���bin����ȷ�ԡ�
 */
#define OS_ERRNO_MNG_BIN_NO_VECBASE_SECTION           SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x20)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG���صĻ���bin��δ�ҵ��Ӻ˵����������Ρ�
 *
 * ֵ: 0x02002f21
 *
 * �������: ȷ�ϴӺ�Ҳ������OS_SEC_DATA_RESET_VECTOR�����ݶΡ�
 */
#define OS_ERRNO_MNG_BIN_NO_CORE_RESET_DATA_SECTION   SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x21)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG�����Ӻ�ʱ�������ֿռ������������ʧ�ܡ�
 *
 * ֵ: 0x02002f22
 *
 * �������: �����Ӻ�ʱȷ�����ֿռ��ѳ�ʼ����
 */
#define OS_ERRNO_MNG_START_PARA_FIND_FAILED           SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x22)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����ʵ��ָ����ʵ��IDΪ0��
 *
 * ֵ: 0x02002f23
 *
 * �������: SRE MNG����ʵ��ָ����ʵ��ID��Χ[1, 7]��
 */
#define OS_ERRNO_SREMNG_INST_ID_CONFLICTED            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x23)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG �˺�û�ж�Ӧ�Ľ�����
 *
 * ֵ: 0x02002f24
 *
 * �������: �˺Ŵ��󣬻������δ������
 */
#define OS_ERRNO_SREMNG_PG_UNEXIST                    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x24)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ������ָ���ĺ��������
 *
 * ֵ: 0x02002f25
 *
 * �������: ȷ�����˵ĺ�ID�ٽ���SRE MNG�Ĳ�����
 */
#define OS_ERRNO_SREMNG_MASTER_CORE_BITMAP_ERR        SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x25)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ���������ռ�ʧ��
 *
 * ֵ: 0x02002f26
 *
 * �������: ���������ռ䡣
 */
#define OS_ERRNO_MNG_NSM_MEM_ALLOC_FAILED             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x26)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG���ز������ȴ��Ӻ˽����ʱ
 *
 * ֵ: 0x02002f27
 *
 * �������: ���Ӻ˼��ش���Ľ����
 */
#define OS_ERRNO_MNG_LOAD_WAIT_SLAVE_CORE_OVERTIME         SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x27)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬����ص�elf�ļ�ͷУ�����
 *
 * ֵ: 0x02002f28
 *
 * �������: ȷ������Ķ�̬���ļ���ȷ�ԡ�
 */
#define OS_ERRNO_MNG_LIB_ELF_HEAD_ERROR               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x28)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺0��ʵ��������ɾ����
 *
 * ֵ: 0x02002f29
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_SREMNG_MCPU_INSTID_DELETE_FORBIDDEN  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x29)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺0��ʵ���ĺ�bitmap�������
 *
 * ֵ: 0x02002f2a
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_SREMNG_MASTER_COREMASK_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2a)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG����ʵ�����������顣
 *
 * ֵ: 0x02002f2b
 *
 * �������: ȷ�ϴ��������鴫���ʵ���ŵ���ȷ�ԡ�
 */
#define OS_ERRNO_SREMNG_MCPU_PG_CREATE_ERR            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2b)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNGж�ز������ȴ��Ӻ˽����ʱ
 *
 * ֵ: 0x02002f2c
 *
 * �������: ���Ӻ�ж�ش���Ľ����
 */
#define OS_ERRNO_MNG_UNLOAD_WAIT_SLAVE_CORE_OVERTIME  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2c)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬��ж�صĶ�̬����Ϣ����ȷ��
 *
 * ֵ: 0x02002f2d
 *
 * �������: ȷ��SRE MNG��̬��ж��ʱ����Ķ�̬����Ϣ��ж�ؿ�����ָ�벻Ϊ�պ�ָ����ж�غ�����ָ�벻Ϊ�ա�
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_PARA_INVALID      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2d)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNGж�ز����������ʵ��ID�Ƿ���
 *
 * ֵ: 0x02002f2e
 *
 * �������: ж�ز�����ȷ�������ʵ��ID������ʵ��֧�ֵ����ֵ��
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_INSTID_INVALID    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2e)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ز�����ʵ����δReady��
 *
 * ֵ: 0x02002f2f
 *
 * �������: ��ȷ����ǰж�ز�����Ӧ��ʵ�����������ʵ����Դ��������ɡ�
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_INST_NOT_READY    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x2f)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬��ж��ʱָ���Ľ�����Ƿ���
 *
 * ֵ: 0x02002f30
 *
 * �������: ȷ��SRE MNG��̬��ж��ʱָ���Ľ�����ŵ���ȷ�ԡ�
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_PG_INVALID        SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x30)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ض�̬��ʱ���������Ľ�����δ������
 *
 * ֵ: 0x02002f31
 *
 * �������: �����������鲢��ɼ��ض�̬��󣬲��ܽ���ж�ض�����
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_PG_NOT_RUNNING    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x31)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ض�̬��ʱδ�ҵ�ָ���Ŀ���
 *
 * ֵ: 0x02002f32
 *
 * �������: �����������鲢��ɸö�̬��ļ��ض����󣬲��ܽ��иö�̬���ж�ض�����
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_NAME_NOT_FIND     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x32)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ض�̬��ʱδ�ҵ��ڲ���¼�Ĺ���Ԫ���UnitNO
 *
 * ֵ: 0x02002f33
 *
 * �������: ����ȷ���п���غ��ڲ�һ�������ɶ�Ӧ�Ĺ���Ԫ��ţ�ֻ�����ڴ汻��ʱ���ſ��ܷ��ظô����롣
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_LOCAL_ID_NOT_FIND SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x33)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺ʵ����Դ����ʱָ����MMUҳ��ռ�Ƿ�
 *
 * ֵ: 0x02002f34
 *
 * �������: MMUҳ���׵�ַ����ΪNULL���׵�ַ����4K���룬MMUҳ��ռ����4K��
 */
#define OS_ERRNO_SREMNG_INST_RES_CFG_MMU_TBL_ERR      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x34)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ض�̬��ʱ����ĺ�bitmap���Ϸ�����Ϊ0��
 *
 * ֵ: 0x02002f35
 *
 * �������: ���ʵ�������ӿڴ���ĺ�bitmap,ȷ���䴫����ȷ�Ĳ�����
 */
#define OS_ERRNO_SREMNG_DLIB_UNLOAD_CORE_BITMAP_INVALID  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x35)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ض�̬��ָ���ĺ�bitmap�����˽�����ĺ�bitmap��
 *
 * ֵ: 0x02002f36
 *
 * �������: ȷ�Ͽ��ж�غ˷�Χ��
 */
 #define OS_ERRNO_SREMNG_DLIB_UNLOAD_COREBITMAP_OVERINST SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x36)

 /**
 * @ingroup SRE_mng
 * SRE MNG�����룺���ض�̬��ʱ��Ϊ�����ڲ�LOCAL ID��������ʱ����ʱ�����ڴ治�㡣
 *
 * ֵ: 0x02002f37
 *
 * �������: ��������LOCAL ID������ڴ��С��
 */
 #define OS_ERRNO_SREMNG_DLIB_LOAD_ALLOC_NO_MEMORY       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x37)

  /**
  * @ingroup SRE_mng
  * SRE MNG�����룺���˸��Ӻ����ڴ�����ʱָ��������㼶�Ƿ���
  *
  * ֵ: 0x02002f38
  *
  * �������: ����ڴ����ýӿڴ���ĸ�������㼶��
  */
 #define OS_ERRNO_SREMNG_MEMCFG_PHY_LEVEL_INVALID         SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x38)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ELF�ļ���bufû��4�ֽڶ��롣
 *
 * ֵ: 0x02002f80
 *
 * �������: �û���֤buf 4�ֽڶ��롣
 */
#define OS_ERRNO_MNG_ELF_BUF_NOT_ALIGN                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x80)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ȫʵ������ռ䲻��
 *
 * ֵ: 0x02002f81
 *
 * �������: ����ȫʵ������Ŀռ�
 */
#define OS_ERRNO_MNG_CHIP_MEM_NOT_ENOUGH              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x81)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG оƬ�ڹ������pl2��sl2
 *
 * ֵ: 0x02002f82
 *
 * �������: оƬ�ڹ���β��ܷ�pl2��sl2
 */
#define OS_ERRNO_MNG_CHIP_SH_PHY_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x82)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ʵ���ڹ���β�����pl2
 *
 * ֵ: 0x02002f83
 *
 * �������: ʵ���������pl2���ܴﵽ������Ҫ���������ڴ�
 */
#define OS_ERRNO_MNG_INST_SH_PL2_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x83)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ʵ���ڹ���β�����sl2
 *
 * ֵ: 0x02002f84
 *
 * �������: ʵ���������sl2���ܴﵽ������Ҫ���������ڴ�
 */
#define OS_ERRNO_MNG_INST_SH_SL2_ERR                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x84)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG bss�����Բ���
 *
 * ֵ: 0x02002f85
 *
 * �������:ELF�ļ����ƻ���������°汾�ļ�
 */
#define OS_ERRNO_MNG_ELF_BSS_ATTRI_ERR                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x85)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG �����Ͳ���
 *
 * ֵ: 0x02002f86
 *
 * �������:ELF�ļ����ƻ���������°汾�ļ�
 */
#define OS_ERRNO_MNG_ELF_SEC_TYPE_ERR                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x86)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG оƬ�ڹ����ڴ��ͷ�ʧ��
 *
 * ֵ: 0x02002f87
 *
 * �������:�����ڴ汻�ƻ�����������оƬ
 */
#define OS_ERRNO_MNG_CHIP_MEM_FREE_ERR                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x87)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG �Ҳ������ʴ�С�������ڴ�
 *
 * ֵ: 0x02002f88
 *
 * �������:�����ڴ治�����������ö�Ӧ�㼶�������ڴ�
 */
#define OS_ERRNO_MNG_PHY_MEM_ERR                      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x88)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ʵ����corebit MAPȫ��
 *
 * ֵ: 0x02002f89
 *
 * �������:ʵ����corebit MAP���ԣ������ų����롣
 */
#define OS_ERRNO_MNG_INST_CORE_MAP_ZERO               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x89)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG  Va����ʧ��
 *
 * ֵ: 0x02002f8a
 *
 * �������:����Va��Դ
 */
#define OS_ERRNO_MNG_VA_ALLOC_ERR                     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8a)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG  ��̬��֧��оƬ�ڹ���
 *
 * ֵ: 0x02002f8B
 *
 * �������:������̬����оƬ�ڹ����ڴ棬�����޸�
 */
#define OS_ERRNO_MNG_DL_CHIP_MEM_UNSUPORT             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8b)
/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG  ��̬��֧��оƬ�ڹ���
 *
 * ֵ: 0x02002f8c
 *
 * �������:������̬����ʵ���ڹ����ڴ棬�����޸�
 */
#define OS_ERRNO_MNG_DL_INST_MEM_UNSUPORT             SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8c)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG  �Ҳ���ϵͳջ
 *
 * ֵ: 0x02002f8d
 *
 * �������:�Ҳ���ϵͳջ
 */
#define OS_ERRNO_MNG_SYS_STACK_UNEXIST                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8d)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG data�����Բ���
 *
 * ֵ: 0x02002f8e
 *
 * �������:ELF�ļ����ƻ���������°汾�ļ�
 */
#define OS_ERRNO_MNG_ELF_DATA_ATTRI_ERR               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8e)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ����bin�����Դ���
 *
 * ֵ: 0x02002f8f
 *
 * �������:����bin�ε�lsp���ô���
 */
#define OS_ERRNO_MNG_SEC_ATTRI_ERR                    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x8f)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG ����bin�����Դ���
 *
 * ֵ: 0x02002f90
 *
 * �������:����bin�ε�lsp���ô���
 */
#define OS_ERRNO_MNG_HOLE_ALLOC_ERR                   SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x90)


/**
 * @ingroup SRE_mng
 * SRE MNG�����룺�����Ľ������������
 *
 * ֵ: 0x02002f91
 *
 * �������: ����ÿ��ʵ������ȷ�������������������������32��
 */
#define OS_ERRNO_SREMNG_PG_EXHAUST                    SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x91)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺���ض�̬��ʱ��鵽��̬���ظ�(����Ķ�̬��������̬��ID��ý����������еĶ�̬����ͬ)��
 *
 * ֵ: 0x02002f92
 *
 * �������: ��ȷ������ͬһ�������鲻���ظ����ض�̬�⡣
 */
#define OS_ERRNO_SREMNG_DLIB_LOAD_REPEAT              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x92)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺����������ʱ����Ĵ�Ž�����ID�ĵ�ַΪ�ա�
 *
 * ֵ: 0x02002f93
 *
 * �������: ����������ʱ��ȷ������Ĵ�Ž�����ID�ĵ�ַ��Ϊ�ա�
 */
#define OS_ERRNO_SREMNG_PG_ID_ADDR_NULL               SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x93)

/**
 * @ingroup SRE_mng
 * �����룺�ڴ��������Ϊ��
 *
 * ֵ: 0x02002f94
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_SREMNG_MEM_CFG_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x94)

/**
 * @ingroup SRE_mng
 * �����룺�ڴ������ڹ������ֿռ���û���ҵ�
 *
 * ֵ: 0x02002f95
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_HW_MEM_CFG_NAME_FIND_FAILED          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x95)

/**
 * @ingroup SRE_mng
 * �����룺�������ֿռ��������ڴ�ʧ�ܣ����ͳ����������ռ�ľ������⣬Ҳ�п����������ռ����鱻�ȣ����µ���
 *
 * ֵ: 0x02002f96
 *
 * �������: ȷ�������ռ�ʣ���ڴ棬������������ľ����������¹滮�����ռ��ʹ�á�
 */
#define OS_ERRNO_SREMNG_MEM_CFG_NAME_ALLOC_FAILED     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x96)

/**
 * @ingroup SRE_mng
 * �����룺ָ����core ID�Ƿ�
 *
 * ֵ: 0x02002f97
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_SREMNG_MEM_CFG_CORE_ID_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x97)

/**
 * @ingroup SRE_mng
 * �����룺ָ����ʵ��ID�Ƿ�,�����uwInstIdʵ���Ų���Ϊ0(OS����)�������Ǵ��ڵ������֧�ֵ�ʵ����8
 *
 * ֵ: 0x02002f98
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_SREMNG_MEM_CFG_INST_ID_INVALID       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x98)

/**
 * @ingroup SRE_mng
 * �����룺ָ���Ľ�����ID�Ƿ�
 *
 * ֵ: 0x02002f99
 *
 * �������: ��ȷ������Ľ�����IDΪ����������ʱ���ص�ID��
 */
#define OS_ERRNO_SREMNG_PG_ID_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x99)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺������ʵ����δReady��
 *
 * ֵ: 0x02002f9a
 *
 * �������: ��ȷ����ǰ������Ӧ��ʵ�����������ʵ����Դ��������ɡ�
 */
#define OS_ERRNO_SREMNG_INST_NOT_READY                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9a)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺���Զ��Ѿ������Դ���õ�ʵ��������Դ���á�
 *
 * ֵ: 0x02002f9b
 *
 * �������: ����ʵ����Դʱ��ȷ����ʵ��δ�����Դ���á�
 */
#define OS_ERRNO_SREMNG_INST_RES_CONFIG_REPEAT        SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9b)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺���������ڴ�ʱ�����������ڴ�ֵΪ0
 *
 * ֵ: 0x02002f9c
 *
 * �������: ȷ�ϸ�ָ���˼���BIN�����Ƕ�����ʱ�������ڴ��Ƿ��Ѿ����䣬���ѷ��䣬�������֮ǰ���ڴ�����ʱ�ľ�����Ҫ���������ڴ�SIZE��
 */
#define OS_ERRNO_MNG_PHY_SIZE_IS_ZERO                SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9c)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺LPģ���ʼ��δ��ɡ�
 *
 * ֵ: 0x02002f9d
 *
 * �������:������������ķ�����ڴ�ռ�ʱ���豣֤LPģ���ʼ����ɡ�
 */
#define OS_ERRNO_MNG_DIS_ASM_LP_INITED              SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9d)


/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬�������صĶ�̬������Ϣ����ȷ��
 *
 * ֵ: 0x02002f9e
 *
 * �������: ȷ��SRE MNG��̬��������ʱ����Ķ�̬������Ϣָ�����ȷ��,������buffer�׵�ַ��Ҫ4�ֽڶ��롣
 */
#define OS_ERRNO_SREMNG_DPAT_PARA_INVALID            SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9e)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬�������ػ���ж��ָ���Ľ�����Ƿ���
 *
 * ֵ: 0x02002f9f
 *
 * �������: ȷ��SRE MNG��̬�������ػ���ж��ʱָ���Ľ�����ŵ���ȷ�ԡ�
 */
#define OS_ERRNO_SREMNG_DPAT_LOAD_PG_INVALID          SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0x9f)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺���ػ���ж�ض�̬����ʱ���������Ľ�����δ������
 *
 * ֵ: 0x02002fa0
 *
 * �������: �������������ټ��ػ���ж�ض�̬������
 */
#define OS_ERRNO_SREMNG_DPAT_LOAD_PG_NOT_RUNNING      SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa0)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺���ض�̬����ʱδ�ҵ�ָ���Ķ�̬�������߽�������
 *
 * ֵ: 0x02002fa1
 *
 * �������: ������������(����̬��򲹶�������Ҫ��ɸö�̬��ļ��ض���)�󣬲��ܽ��ж�̬�����ļ��ض�����
 */
#define OS_ERRNO_SREMNG_DPAT_LOAD_NAME_NOT_FIND         SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa1)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺SRE MNG��̬�������ػ�ж�صĶ�̬������Ϣָ��Ϊ�ա�
 *
 * ֵ: 0x02002fa2
 *
 * �������: ȷ��SRE MNG��̬�������ػ�ж��ʱ����Ķ�̬������Ϣָ�����ȷ�ԡ�
 */
#define OS_ERRNO_SREMNG_DPAT_PARA_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa2)

 /**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ض�̬����ʱ��ָ���Ķ�̬�������߽�����δ���ض�̬������
 *
 * ֵ: 0x02002fa6
 *
 * �������: �ȼ��ض�̬���������ܽ��ж�̬������ж�ض�����
 */
#define OS_ERRNO_SREMNG_DPAT_UNLOAD_NOT_FIND_IN_LIB     SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa6)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ض�̬����ʱδ�ҵ��ڲ���¼�Ĺ���Ԫ���UnitNO
 *
 * ֵ: 0x02002fa7
 *
 * �������: ����ȷ���в������غ��ڲ�һ�������ɶ�Ӧ�Ĺ���Ԫ��ţ�ֻ�����ڴ汻��ʱ���ſ��ܷ��ظô����롣
 */
#define OS_ERRNO_SREMNG_DPAT_UNLOAD_LOCAL_ID_NOT_FIND   SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa7)

 /**
 * @ingroup SRE_mng
 * SRE MNG�����룺ж�ض�̬����ʱδ�ҵ�ָ���Ķ�̬�������߽�������
 *
 * ֵ: 0x02002fa8
 *
 * �������: ������������(����̬��򲹶�������Ҫ��ɸö�̬��ļ��ض���)�󣬲��ܽ��ж�̬������ж�ض�����
 */
#define OS_ERRNO_SREMNG_DPAT_UNLOAD_NAME_NOT_FIND       SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa8)

/**
 * @ingroup SRE_mng
 * SRE MNG�����룺�����˼��ػ�ж�ض�̬����ʱ����̬����߽�����bin����Ϊ�ա�
 *
 * ֵ: 0x02002fa9
 *
 * �������: �������˻���bin��������̬�������ػ���ж��ʱ������Ķ�̬�������߽���������Ϊ�ա�
 */
#define OS_ERRNO_SREMNG_DPAT_LOAD_DLIBNAME_NULL         SRE_ERRNO_OS_ERROR(OS_MID_SREMNG, 0xa9)


/**
 * @ingroup SRE_mng
 *
 * ֧�ֵ����ʵ��������
 */
#define  OS_MAX_SUPPORT_INST      0x8

/**
* @ingroup SRE_mng
* ���غ�ʵ��ȱʡΪ0
*/
#define OS_MNG_MCPU_INST_ID       0

/**
* @ingroup SRE_mng
* ���غ�ʵ���ڵĽ�����ȱʡΪ0
*/
#define OS_MNG_MCPU_PG_ID         0

/**
 * @ingroup SRE_mng
 *
 * �ֲ㼶��memmap�Ľṹ���塣
 */
#define  OS_MNG_HW_CORE_NUM       17
#define  OS_MNG_HW_THREAD_NUM     34
#define  OS_MNG_CLUSTER_NUM       4

typedef struct tagMemAddrLen
{
    UINT32 uwAddr;
    UINT32 uwLen;
}SRE_MEM_ADDR_LEN;

typedef struct tagMemMapPL2
{
    SRE_MEM_ADDR_LEN stVaInfoPL2;                     /**< PL2�����ַ */
    SRE_MEM_ADDR_LEN stPaInfoPL2[OS_MNG_HW_CORE_NUM]; /**< PL2�����ַ */
}SRE_MEMMAP_PL2;
typedef struct tagMemMapSL2
{
    SRE_MEM_ADDR_LEN stVaInfoSL2;                      /**< SL2�����ַ */
    SRE_MEM_ADDR_LEN stPaInfoSL2[OS_MNG_CLUSTER_NUM];  /**< SL2�����ַ */
}SRE_MEMMAP_SL2;
typedef struct tagMemMapL3
{
    SRE_MEM_ADDR_LEN stVaInfoL3;      /**< L3�����ַ */
    SRE_MEM_ADDR_LEN stPaInfoL3;      /**< L3�����ַ */
}SRE_MEMMAP_L3;
typedef struct tagMemMapDDR32
{
    SRE_MEM_ADDR_LEN stVaInfoDDR32;   /**< DDR32�����ַ */
    SRE_MEM_ADDR_LEN stPaInfoDDR32;   /**< DDR32�����ַ */
}SRE_MEMMAP_DDR32;
typedef struct tagMemMapDDR64
{
    SRE_MEM_ADDR_LEN stVaInfoDDR64;   /**< DDR64�����ַ */
    SRE_MEM_ADDR_LEN stPaInfoDDR64;   /**< DDR64�����ַ */
}SRE_MEMMAP_DDR64;

typedef struct tagInstMMUPageInfo
{
    UINT32 uwPageTbl;                 /**< Ӳ�̵߳�1��ҳ���ַ  */
    UINT32 uwSize;                    /**< Ӳ�̵߳�ҳ��ռ��С */
}SRE_INST_MMU_PAGE_INFO;

/**
 * @ingroup SRE_mng
 *
 * �汾�ռ估�䲹���ռ�ṹ���塣
 * ��Ҫʹ��ĳ������㼶�Ŀռ�ʱ����Ӧ����㼶�������ַ�ռ�������һ�ݣ������ַ�ռ��������㼶�������ã�����PL2�ռ���Ҫ��ʵ����ÿ���˽�������ռ����á�
 */
typedef struct tagInstMem
{
    SRE_MEMMAP_PL2   stMemMapPL2;      /**< �汾�ռ�PL2�ڴ���Դ   */
    SRE_MEMMAP_SL2   stMemMapSL2;      /**< �汾�ռ�SL2�ڴ���Դ   */
    SRE_MEMMAP_L3    stMemMapL3;       /**< �汾�ռ�L3�ڴ���Դ    */
    SRE_MEMMAP_DDR32 stMemMapDDR32;    /**< �汾�ռ�DDR32�ڴ���Դ */
    SRE_MEMMAP_DDR64 stMemMapDDR64;    /**< �汾�ռ�DDR64�ڴ���Դ */
    SRE_MEMMAP_PL2   stPatMemMapPL2;   /**< �����ռ�PL2�ڴ���Դ   */
    SRE_MEMMAP_SL2   stPatMemMapSL2;   /**< �����ռ�SL2�ڴ���Դ   */
    SRE_MEMMAP_L3    stPatMemMapL3;    /**< �����ռ�L3�ڴ���Դ    */
    SRE_MEMMAP_DDR32 stPatMemMapDDR32; /**< �����ռ�DDR32�ڴ���Դ */
    SRE_MEMMAP_DDR64 stPatMemMapDDR64; /**< �����ռ�DDR64�ڴ���Դ */
    SRE_INST_MMU_PAGE_INFO stMmuPageInfo[OS_MNG_HW_THREAD_NUM];   /**< ʵ���ڸ���Ӳ�̵߳�MMUҳ����Ϣ */
}SRE_INST_MEM_S;

/**
 * @ingroup SRE_mng
 *
 * ���������͵�ö�ٶ��塣
 */
typedef enum
{
    PG_TYPE_PROCESS = 0,               /**< ����������Ϊ����    */
    PG_TYPE_BMCORE,                    /**< ����������Ϊ���    */
    PG_TYPE_INVALID
}PG_TYPE_E;

/**
 * @ingroup SRE_mng
 *
 * �����ڴ�����Ͷ��塣
 */
typedef enum
{
    MEM_TYPE_PL2 = 0,
    MEM_TYPE_SL2,
    MEM_TYPE_L3,
    MEM_TYPE_DDR32,
    MEM_TYPE_DDR64,
    MEM_TYPE_INVALID
}MEM_TYPE_E;

/**
 * @ingroup SRE_mng
 *
 * SRE_mng��ǰ����״̬��ö�ٶ��塣
 */
typedef enum
{
    /*SRE_InsCreate*/
    INS_CREATE_BEGIN              = 0x101,  /**< ��ʼ����ʵ��    */
    INS_CREATE_END                = 0x102,  /**< ʵ����������    */
    /*SRE_InstResCfg*/
    INS_RES_CFG_BEGIN             = 0x103,  /**< ��ʼ����ʵ����Դ    */
    INS_RES_CFG_MEM_REG           = 0x104,  /**< �����ø���ʵ������Դע�ᵽ�ڴ����ģ��    */
    INS_RES_CFG_END               = 0x105,  /**< ��������ʵ����Դ    */
    /*SRE_InsDelete*/
    INS_DELETE_BEGIN              = 0x106,  /**< ��ʼɾ��ʵ��    */
    INS_DELETE_NSM_OBJ_DELETE     = 0x107,  /**< ʵ��ɾ��ʱɾ����������    */
    INS_DELETE_SSC_MEM_DELETE     = 0x108,  /**< ʵ��ɾ��ʱSSC�ڴ��ͷ�    */
    INS_DELETE_MEM_FREE           = 0x109,  /**< ʵ��ɾ��ʱ�����ڴ����ģ���ͷ�ʵ�������ڴ�    */
    INS_DELETE_END                = 0x10A,  /**< ����ɾ��ʵ��    */
    /*SRE_PgCreate*/
    PG_CREATE_BEGIN               = 0x10B,  /**< ��ʼ�����鴴��    */
    PG_CREATE_START_BIN_LOAD      = 0x10C,  /**< �����鴴��ʱ��ʼBIN����    */
    PG_CREATE_MEM_GROUP_ADD       = 0x10D,  /**< �����鴴��ʱ��ʼMemGroup�����   */
    PG_CREATE_UINT_MEM_ALLOC      = 0x10E,  /**< �����鴴��ʱ��ʼΪ����bin����汾�ռ�  */
    PG_CREATE_START_BM_BIN_COPY   = 0x10F,  /**< �����鴴��ʱ��ʼ�ѻ���bin����������汾�ռ�    */
    PG_CREATE_END                 = 0x110,  /**< ���������鴴��    */
    /*SRE_MemCfg*/
    MEM_CONFIG_START              = 0x111,  /**< ��ʼ�Ӻ��ڴ�����    */
    MEM_CONFIG_SYS_STACK          = 0x112,  /**< �Ӻ�����ϵͳջ�ڴ�    */
    MEM_CONFIG_TASK_STACK         = 0x113,  /**< �Ӻ���������ջ�ڴ�     */
    MEM_CONFIG_FSC_PT_MEM         = 0x114,  /**< �Ӻ�����˽��FSC�ڴ�     */
    MEM_CONFIG_TRACE_MEM          = 0x115,  /**< �Ӻ�����trace�ڴ�     */
    MEM_CONFIG_MMU_PA2VA_MEM      = 0x116,  /**< �Ӻ�����MMU��PA2VA�ڴ�  */
    MEM_CONFIG_MC_FSC_PT_MEM      = 0x117,  /**< �Ӻ����ù���FSC�ڴ�   */
    MEM_CONFIG_LP_SHARE_MEM       = 0x118,  /**< �Ӻ�����LP�����ڴ�   */
    MEM_CONFIG_SYMBOL_TBL_MEM     = 0x119,  /**< �Ӻ����÷��ű��ڴ�  */
    MEM_CONFIG_END                = 0x11A,  /**< �����Ӻ��ڴ�����   */
    /*SRE_PgStart*/
    PG_START_BEGIN                = 0x11B,  /**< ��ʼ����������    */
    PG_START_NSM_MMU_ASSGIN       = 0x11C,  /**< ����������ʱӳ�����bin�����ռ�    */
    PG_START_STACK_ASSGIN         = 0x11D,  /**< ����������ʱӳ�����bin��ϵͳջ    */
    PG_START_MMU_TLB_ASSGIN       = 0x11E,  /**< ����������ʱӳ�����bin��ҳ��ռ�   */
    PG_START_SLAVE_BOOT_SET       = 0x11F,  /**< ����������ʱ���û���bin��������   */
    PG_START_SLAVE_WAKEUP         = 0x120,  /**< ����������ʱ���ѴӺ�    */
    PG_START_END                  = 0x121,  /**< ��������������    */
    /*SRE_DlibLoadFromFile*/
    DLIB_LOAD_START               = 0x122,  /**< ��ʼ���ض�̬��    */
    DLIB_LOAD_CTRL_MEM_ALLOC      = 0x123,  /**< ���ض�̬��ʱ���붯̬����ƿ� */
    DLIB_LOAD_UNIT_MEM_ALLOC      = 0x124,  /**< ���ض�̬��ʱ���붯̬������Ҫ���ڴ�ռ�  */
    DLIB_LOAD_MCPU_FETCH_ACTIVE   = 0x125,  /**< ���ض�̬��ʱ�������˵ļ��ؼ������   */
    DLIB_LOAD_FETCH_MSG_SEND      = 0x126,  /**< ���ض�̬��ʱ�Ӻ˼��ض�̬����Ϣ���� */
    DLIB_LOAD_FETCH_MSG_RECIVE    = 0x127,  /**< ���ض�̬��ʱ�Ӻ˼��ض�̬����Ϣ���� */
    DLIB_LOAD_END                 = 0x128,  /**< �������ض�̬��    */
    /*SRE_DlibUnload*/
    DLIB_UNLOAD_START             = 0x129,  /**< ��ʼ��̬��ж�� */
    DLIB_UNLOAD_MCPU_REMOVE       = 0x12A,  /**< ��̬��ж��ʱ�����Ƴ���̬�� */
    DLIB_UNLOAD_MCPU_UINT_MEM_FREE= 0x12B,  /**< ��̬��ж��ʱ���˶�̬���ڴ��ͷ�  */
    DLIB_UNLOAD_REMOVE_MSG_SEND   = 0x12C,  /**< ��̬��ж��ʱ�Ӻ˺��Ƴ���̬����Ϣ���� */
    DLIB_UNLOAD_REMOVE_MSG_RECIVE = 0x12D,  /**< ��̬��ж��ʱ�Ӻ˺��Ƴ���̬����Ϣ���� */
    DLIB_UNLOAD_BM_CORE_UINT_FREE = 0x12E,  /**< ��̬��ж��ʱ�Ӻ��ͷŶ�̬��ռ�õİ汾�ռ�  */
    DLIB_UNLOAD_END               = 0x12F,  /**< ������̬��ж�� */
    /*SRE_DpatLoadFromFile*/
    DPAT_LOAD_START               = 0x130,  /**< ��ʼ���ض�̬����    */
    DPAT_LOAD_CTRL_MEM_ALLOC      = 0x131,  /**< ���ض�̬����ʱ���붯̬�������ƿ� */
    DPAT_LOAD_UNIT_MEM_ALLOC      = 0x132,  /**< ���ض�̬����ʱ���붯̬��������Ҫ���ڴ�ռ�  */
    DPAT_LOAD_MCPU_FETCH_ACTIVE   = 0x133,  /**< ���ض�̬����ʱ�������˵ļ��ؼ������   */
    DPAT_LOAD_FETCH_MSG_SEND      = 0x134,  /**< ���ض�̬����ʱ�Ӻ˼��ض�̬������Ϣ���� */
    DPAT_LOAD_FETCH_MSG_RECIVE    = 0x135,  /**< ���ض�̬����ʱ�Ӻ˼��ض�̬������Ϣ���� */
    DPAT_LOAD_END                 = 0x136,  /**< �������ض�̬����    */

    DPAT_UNLOAD_START             = 0x137,  /**< ��ʼ��̬����ж�� */
    DPAT_UNLOAD_MCPU_REMOVE       = 0x138,  /**< ��̬����ж��ʱ�����Ƴ���̬���� */
    DPAT_UNLOAD_MCPU_UINT_MEM_FREE= 0x139,  /**< ��̬����ж��ʱ���˶�̬�����ڴ��ͷ�  */
    DPAT_UNLOAD_REMOVE_MSG_SEND   = 0x13A,  /**< ��̬����ж��ʱ�Ӻ˺��Ƴ���̬������Ϣ���� */
    DPAT_UNLOAD_REMOVE_MSG_RECIVE = 0x13B,  /**< ��̬����ж��ʱ�Ӻ˺��Ƴ���̬������Ϣ���� */
    DPAT_UNLOAD_BM_CORE_UINT_FREE = 0x13C,  /**< ��̬����ж��ʱ�Ӻ��ͷŶ�̬����ռ�õĲ����ռ�  */
    DPAT_UNLOAD_END               = 0x13D,  /**< ������̬����ж�� */
}SRE_MNG_STATUS_E;

/**
 * @ingroup SRE_mng
 *
 * �߼��ڴ�������㼶��ӳ���ϵ�ṹ���塣
 */
typedef struct tagMemToLevel
{
    CHAR *pcMemString;
    MEM_TYPE_E eMemLevel;
}SRE_MEM_TO_LEVEL;

/**
 * @ingroup SRE_mng
 *
 * �����鴴��ʱָ���Ļ���bin����Ϣ�ṹ���塣
 */
typedef struct tagBinLoadInfo
{
    UINT8  *pcBinName;                /**< ����bin�������ַ���                 */
    UINT8  *pucBinBuf;                /**< ����bin�Ķ�����buffer               */
    UINT32  uwFileLen;                /**< ����bin�Ķ�����buffer����           */
    PG_TYPE_E ePgType;                /**<���������ͣ���˻��û�����           */
}SRE_BIN_LOAD_PARA_STRU;

/**
 * @ingroup SRE_mng
 *
 * ��̬�����ʱָ���Ķ�̬����Ϣ�ṹ���塣
 */
typedef struct tagDlibLoadInfo
{
    UINT32  uwInstID;                 /**< ʵ��ID                               */
    UINT32  uwPgID;                   /**< ������ID                             */
    UINT32  uwDlibID;                 /**< ��̬��ID                             */
    UINT8  *pucDlibName;              /**< ��̬����                             */
    SRE_COREMASK *pCoreBitMap;        /**< ��̬����صĺ�����                   */
    UINT8  *pucDlibBuf;               /**< ��̬��Ķ�����buffer                 */
    UINT32  uwFileLen;                /**< ��̬���buffer�ĳ���                 */
    UINT32  uwLogicMemNum;            /**< ��̬��Ķ���������㼶��ϵ�ṹ����� */
    SRE_MEM_TO_LEVEL *pstLogicMemStr; /**< ��̬��Ķ���������㼶��ϵ�ṹ��     */
}SRE_DLIB_LOAD_PARA_STRU;

/**
 * @ingroup SRE_mng
 *
 * ��̬��ж��ʱָ���Ķ�̬����Ϣ�ṹ���塣
 */
typedef struct tagDlibUnloadInfo
{
    UINT32  uwInstID;                 /**< ʵ��ID             */
    UINT32  uwPgID;                   /**< ������ID           */
    UINT32  uwDlibID;                 /**< ��̬��ID           */
    UINT8   *pucDlibName;             /**< ��̬����           */
    SRE_COREMASK *pCoreBitMap;        /**< ��̬����صĺ����� */
}SRE_DLIB_UNLOAD_PARA_STRU;

/**
 * @ingroup SRE_mng
 *
 * �򲹶�ʱָ���Ĳ�����Ϣ�ṹ���塣
 */
typedef struct tagBinInfo
{
    UINT32  uwInstID;          /**< ʵ��ID                                              */
    UINT32  uwPgID;            /**< ������ID                                            */
    UINT8  *pucPatFileName;    /**< �����ļ���                                          */
    UINT8  *pucDPatBuf;        /**< �����ļ�������buffer                                */
    UINT32  uwFileLen;         /**< �����ļ�buffer����                                  */
    UINT32  uwDlibID;          /**< ���򲹶��Ķ�̬��ID                                  */
    UINT8  *pucDlibName;       /**< ���򲹶��Ĳ��������߽������������˽�������Ĭ��ΪNULL*/
}SRE_DPAT_LOAD_PARA_STRU;


/**
 * @ingroup SRE_mng
 *
 * MemCfg�ڴ�ṹ���塣
 */
typedef struct tagMemCfg
{
    //���¸�����������ã�ÿ���˿������ò�ͬ
    UINT32 uwSysStackAreaSize;       //ϵͳջ��С
    UINT32 uwSysStackAreaMemLevel;   //ϵͳջ�������ڴ�㼶
    UINT32 uwTskStackAreaSize;       //��������ջ��С(��Ч,������0)
    UINT32 uwTskStackAreaMemLevel;   //����ջ�������ڴ�㼶(��Ч)
    UINT32 uwFscPtSize;             //˽��FSC������С
    UINT32 uwFscPtMemLevel;         //˽��FSC�����ڴ�㼶
    UINT32 uwTraceAreaSize;         //Trace�ڴ��С
    UINT32 uwTraceAreaMemLevel;      //Trace�ڴ�����
    UINT32 uwMmuPhy2VirAreaSize;            //MMU�����ַ�������ַת��ӳ����С
    UINT32 uwMmuPhy2VirAreaMemLevel;        //MMU�����ַ�������ַת��ӳ����ڴ�㼶

    //���¸������ʵ�����ã�ʵ����ÿ����������ͬ
    UINT32 uwMcFscPtSize;           //����̬FSC������С
    UINT32 uwMcFscPtMemLevel;       //����̬FSC�����ڴ�㼶
    UINT32 uwLPShareNcPtSize;       //����������С��
    UINT32 uwLPShareNcPtMemLevel;   //���������ڴ�����

    //���¸������������(image)���ã���������ÿ����������ͬ
    UINT32 uwSymTblNcPtSize;        //���ű��ڴ������С���������ڸ�����������ͬ
    UINT32 uwSymTblNcPtMemLevel;    //���ű��ڴ�����ڴ�㼶
} OS_MEM_CFG_S;

/**
 * @ingroup  SRE_mng
 * @brief ���ôӺ˵��ڴ�
 *
 * @par ����:
 * ���ôӺ˵��ڴ���������Ӱ汾�ռ�Ϊ�Ӻ�����������ڴ档
 *
 *
 * @attention
 *
 * @param  uwCoreId    [IN] ����#UINT32���˺ţ�ȡֵ��ΧΪ[0,OS_MAX_CORE_NUM)��
 * @param  uwInstId    [IN] ����#UINT32��ʵ��ID��ȡֵ��ΧΪ[0,OS_MAX_SUPPORT_INST)��
 * @param  pstMemCfg   [IN] ����#OS_MEM_CFG_S���ڴ����ò�����

 * @retval #OS_ERRNO_SREMNG_MEM_CFG_NULL                     0x02002f94���ڴ��������Ϊ�ա�
 * @retval #OS_ERRNO_SREMNG_MEM_CFG_CORE_ID_INVALID          0x02002f97��ָ����core ID�Ƿ���
 * @retval #OS_ERRNO_SREMNG_MEM_CFG_INST_ID_INVALID          0x02002f98��ָ����ʵ�� ID�Ƿ���
 * @retval #OS_ERRNO_SREMNG_INST_NOT_READY                   0x02002f9a��������ʵ����δReady��
 * @retval #OS_ERRNO_SREMNG_PG_UNEXIST                       0x02002f24���˺�û�ж�Ӧ�Ľ����顣
 * @retval #OS_ERRNO_SREMNG_MEM_CFG_NAME_ALLOC_FAILED        0x02002f96���������ֿռ��������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_SREMNG_MEMCFG_PHY_LEVEL_INVALID         0x02002f38�����õ�����㼶�Ƿ���
 * @retval #SRE_OK                                           0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li></li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_MemCfg(UINT32 uwCoreId, UINT32 uwInstId, OS_MEM_CFG_S* pstMemCfg);

/**
 * @ingroup  SRE_mng
 * @brief ����ʵ����
 *
 * @par ����:
 * ����һ��ʵ����
 *
 * @attention
 * <ul>
 * <li>�������غ˻����ؽ��̣�ϵͳ��Ĭ��Ϊ�䴴��ʵ���������û���ʾ���øýӿڽ���ʵ��������</li>
 * <li>���øýӿ����ʵ����������Ҫ����SRE_InstResCfg�ӿڽ���ʵ����Դ���á�</li>
 * </ul>
 *
 * @param  uwVMID        [IN] ����#UINT32��ʵ����VMID����Χ[0,7]��
 * @param  uwAppVaBase   [IN] ����#UINT32����ǰ��Ч��
 * @param  puwInstId     [OUT] ����#UINT32 *�����ڴ洢ʵ��ID�ĵ�ַ��
 *
 * @retval #OS_ERRNO_SREMNG_VMID_VALUE_ERR      0x02002f01��SRE MNG�����VMID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_INST_ID_ADDR_NULL   0x02002f04������ʵ��ʱ������û����ʵ��ID�ĵ�ַΪ��
 * @retval #OS_ERRNO_SREMNG_INST_ID_EXHAUST     0x02002f07��SRE MNGʵ�������������࣬�޿��õ�ʵ����Դ
 * @retval #OS_ERRNO_SREMNG_NO_MEMORY           0x02002f06��SREMNG������ڴ治��
 * @retval #SRE_OK                              0x00000000��ʵ�������ɹ���
 * @par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_InstDelete
 */
extern UINT32 SRE_InstCreate(UINT32 uwVMID, UINT32 uwAppVaBase, UINT32 *puwInstId);

/**
 * @ingroup  SRE_mng
 * @brief ����ʵ����Դ��
 *
 * @par ����:
 * Ϊʵ��uwInstID����pstMemMap��pCoreBitMapָ������Դ��
 *
 * @attention ��
 *
 * @param  uwInstId      [IN] ����#UINT32��ʵ��ID��
 * @param  pstMemMap     [IN] ����#SRE_INST_MEM_S*��ʵ���ڴ���Դ��
 * @param  pCoreBitMap   [IN] ����#SRE_COREMASK*��ʵ���ĺ�Bitmapָ�롣
 *
 * @retval #OS_ERRNO_SREMNG_MEMMAP_NULL             0x02002f02����ʵ��ַmemmap���Ϊ��
 * @retval #OS_ERRNO_SREMNG_CORE_BITMAP_NULL        0x02002f03����bitmapָ�����Ϊ��
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID          0x02002f0b�������ʵ��ID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_INSTID_UNCREATE         0x02002f0c�������ʵ��IDΪδ����ʵ��
 * @retval #OS_ERRNO_SREMNG_CORE_BITMAP_INVALID     0x02002f05����bitmapΪȫ0
 * @retval #OS_ERRNO_SREMNG_NO_MEMORY               0x02002f06��SREMNG������ڴ治��
 * @retval #OS_ERRNO_SREMNG_INST_RES_CONFIG_REPEAT  0x02002f9b�����Զ��Ѿ������Դ���õ�ʵ��������Դ����
 * @retval #SRE_OK                                  0x00000000��ʵ�������ɹ���
 * @par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_InstDelete
 */
extern UINT32 SRE_InstResCfg(UINT32 uwInstID, SRE_INST_MEM_S *pstMemMap, SRE_COREMASK *pCoreBitMap);

/**
 * @ingroup  SRE_mng
 * @brief ɾ��ʵ����
 *
 * @par ����:
 * ɾ��һ��ʵ����
 *
 * @attention ��
 *
 * @param  uwInstId    [IN] ����#UINT32����ɾ����ʵ��ID��
 *
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID      0x02002f0b��ʵ��ID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_INSTID_UNCREATE     0x02002f0c��ָ����ʵ����δ����
 * @retval #SRE_OK                              0x00000000��ʵ��ɾ���ɹ���
 * @par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_InstCreate
 */
extern UINT32 SRE_InstDelete(UINT32 uwInstId);

/**
 * @ingroup  SRE_mng
 * @brief ���������顣
 *
 * @par ����:
 * ����һ�������顣
 *
 * @attention ��
 *
 * @param  uwInstId     [IN] ����#UINT32��������������ʵ����
 * @param  pCoreBitMap  [IN] ����#SRE_COREMASK*��ʵ���ĺ�Bitmapָ�룬SD6183��Ӳ�̹߳�34���˸�����
 * @param  pPgAttr      [IN] ����#VOID*��������Ļ���bin��Ϣ�ṹ, ��Ա��Ϣ��ͨ���ṹ������SRE_BIN_LOAD_PARA_STRU���롣
 * @param  puwPgId      [OUT] ����#UINT32*, ���ڴ洢������ID��
 *
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID         0x02002f0b��ʵ��ID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_INSTID_UNCREATE        0x02002f0c��ָ����ʵ����δ����
 * @retval #OS_ERRNO_SREMNG_CORE_BITMAP_NULL       0x02002f03����bitmapָ�����Ϊ��
 * @retval #OS_ERRNO_SREMNG_PG_TYPE_INVALID        0x02002f08�����������ͷǷ�
 * @retval #OS_ERRNO_SREMNG_BIN_PARA_NULL          0x02002f09������bin��νṹ��ָ��ΪNULL
 * @retval #OS_ERRNO_SREMNG_BIN_PARA_INVALID       0x02002f15������bin�ļ���Ϣ����ȷ
 * @retval #OS_ERRNO_SREMNG_PG_COREBITMAP_OVERINST 0x02002f0d��������ĺ�bitmap��������ʵ���ĺ�bitmap
 * @retval #OS_ERRNO_SREMNG_NO_MEMORY              0x02002f06��SREMNG������ڴ治��
 * @retval #OS_ERRNO_MNG_BIN_LOAD_NO_VALID_VA      0x02002f0e������δԤ�������Ĳ�С��10M�������ַ�ռ�
 * @retval #OS_ERRNO_MNG_BIN_LEN_INVALID           0x02002f0f������bin��Ϣ��ָ�����ļ����Ȳ���ȷ
 * @retval #OS_ERRNO_MNG_BIN_MEMALLOC_FAILED       0x02002f10�����ػ���bin������ڴ�ʧ��
 * @retval #OS_ERRNO_MNG_BIN_ELF_HEAD_ERROR        0x02002f11������bin���ص�elf�ļ�ͷУ�����
 * @retval #OS_ERRNO_MNG_BIN_ELF_FILETYPE_ERROR    0x02002f12������bin���ص�elf�ļ����ʹ���
 * @retval #OS_ERRNO_MNG_BIN_ELF_SEC_HEAD_ERROR    0x02002f0a��ELF�ļ�ͷ��δ�С��У�����
 * @retval #OS_ERRNO_MNG_BIN_ELF_SEC_NUM_ERROR     0x02002f13��elf�Ķθ�������ȷ
 * @retval #SRE_OK                                 0x00000000�������鴴���ɹ���
 * @par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_PgStart
 */
extern UINT32 SRE_PgCreate(UINT32 uwInstId, SRE_COREMASK * pCoreBitMap, VOID* pPgAttr, UINT32 *puwPgId);

/**
 * @ingroup  SRE_mng
 * @brief ���������顣
 *
 * @par ����:
 * ����һ�������顣
 *
 * @attention ��
 *
 * @param  uwPgId      [IN] ����#UINT32���������Ľ�����ID��
 *
 * @retval #OS_ERRNO_SREMNG_PG_ID_INVALID       0x02002f99��ָ���Ľ�����ID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_PG_UNCREATED        0x02002f19��ָ���Ľ�������δ����
 * @retval #OS_ERRNO_SREMNG_PG_ALREADY_STARTED  0x02002f1a���������ѱ�����
 * @retval #OS_ERRNO_MNG_START_PARA_FIND_FAILED 0x02002f22�������Ӻ�ʱ�������ֿռ������������ʧ��
 * @retval #SRE_OK                              0x00000000�������������ɹ���
 * @par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_PgCreate
 */
extern UINT32 SRE_PgStart(UINT32 uwPgId);

/**
 * @ingroup  SRE_mng
 * @brief ��̬����ء�
 *
 * @par ����:
 * ���ض�̬�⡣
 *
 * @attention ��
 *
 * @param  pstPara    [IN] ����#SRE_DLIB_LOAD_PARA_STRU*�������صĶ�̬��ṹ��Ϣ��
 * @param  pcFileName [IN] ����#CHAR *����ǰ�ɲ����룬������Lib����
 *
 * @retval #OS_ERRNO_SREMNG_DLIB_PARA_NULL            0x02002f16����̬����Ϣָ��Ϊ��
 * @retval #OS_ERRNO_SREMNG_DLIB_PARA_INVALID         0x02002f17����̬����Ϣ����ȷ
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID            0x02002f0b��ʵ��ID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_INSTID_UNCREATE           0x02002f0c��ָ����ʵ����δ����
 * @retval #OS_ERRNO_SREMNG_DLIBLOAD_PG_INVALID       0x02002f18��ָ���Ľ�����Ƿ�
 * @retval #OS_ERRNO_SREMNG_DLIB_COREBITMAP_OVERINST  0x02002f1c��������ĺ�bitmap��������ʵ���ĺ�bitmap
 * @retval #OS_ERRNO_SREMNG_DLIBLOAD_PG_NOT_RUNNING   0x02002f1e�����ض�̬��ʱ���������Ľ�����δ����
 * @retval #OS_ERRNO_SREMNG_DLIB_LOAD_REPEAT          0x02002f92�����ض�̬��ʱ��鵽��̬���ظ�
 * @retval #OS_ERRNO_SREMNG_NO_MEMORY                 0x02002f06��SREMNG������ڴ治��
 * @retval #SRE_OK                                    0x00000000����̬����سɹ���
 * @par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_DlibUnload
 */
extern UINT32 SRE_DlibLoadFromFile(SRE_DLIB_LOAD_PARA_STRU *pstPara, CHAR *pcFileName);

/**
 * @ingroup  SRE_mng
 * @brief ж�ض�̬�⡣
 *
 * @par ����:
 * ж�ض�̬�⡣
 *
 * @attention ��
 *
 * @param  pstPara    [IN] ����#SRE_DLIB_UNLOAD_PARA_STRU*����ж�صĶ�̬��ṹ��Ϣ��
 *
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_PARA_NULL           0x02002f1f��ж�ض�̬�����νṹ��ָ��Ϊ��
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_PARA_INVALID        0x02002f2d����̬��ж�صĶ�̬����Ϣ����ȷ
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_INSTID_INVALID      0x02002f2e��ж�ز����������ʵ��ID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_INST_NOT_READY      0x02002f2f��ж�ز�����ʵ����δReady
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_PG_INVALID          0x02002f30����̬��ж��ʱָ���Ľ�����Ƿ�
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_PG_NOT_RUNNING      0x02002f31��ж�ض�̬��ʱ���������Ľ�����δ����
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_CORE_BITMAP_INVALID 0x02002f35��ж�ض�̬��ʱ����ĺ�bitmap���Ϸ�����Ϊ0
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_COREBITMAP_OVERINST 0x02002f36��ж�ض�̬��ָ���ĺ�bitmap�����˽�����ĺ�bitmap
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_NAME_NOT_FIND       0x02002f32��ж�ض�̬��ʱδ�ҵ�ָ���Ŀ���
 * @retval #OS_ERRNO_SREMNG_DLIB_UNLOAD_LOCAL_ID_NOT_FIND   0x02002f33��ж�ض�̬��ʱδ�ҵ��ڲ���¼�Ĺ���Ԫ���UnitNO
 * @retval #OS_ERRNO_MNG_UNLOAD_WAIT_SLAVE_CORE_OVERTIME    0x02002f2c��ж�ز������ȴ��Ӻ˽����ʱ
 * @retval #OS_ERRNO_LP_NOT_LOADED                          0x02001e09��LP�����У�LP��Ԫδ����.
 * @retval #OS_ERRNO_LP_HANDLE_CORE_BUSY                    0x02001e9f����Ҫ������Ŀ�ĺ�æ�����ܽ��ж�̬���ػ���ж�ز���
 * @retval #SRE_OK                                          0x00000000��ж�ض�̬��ɹ���
 * @par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_DlibLoadFromFile
 */
extern UINT32 SRE_DlibUnload(SRE_DLIB_UNLOAD_PARA_STRU *pstPara);

/**
 * @ingroup  SRE_mng
 * @brief ���ض�̬������
 *
 * @par ����:
 * ���ض�̬������
 *
 * @attention ��
 *
 * @param  pstPara    [IN] ����#SRE_DPAT_LOAD_PARA_STRU*�������صĶ�̬�����ṹ��Ϣ��pucPatFileNameΪNULLʱ����ʾж�ض�Ӧ��̬������
 * @param  pcFileName [IN] ����#CHAR *����ǰ�ɲ����룬������Pat����
 *
 * @retval #OS_ERRNO_SREMNG_DPAT_PARA_NULL                  0x02002fa2����̬������Ϣָ��Ϊ��
 * @retval #OS_ERRNO_SREMNG_DPAT_PARA_INVALID               0x02002f9e����̬�������ػ�ж�������Ϣ����ȷ
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID                  0x02002f0b��ʵ��ID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_INST_NOT_READY                  0x02002f9a��������ʵ����δReady
 * @retval #OS_ERRNO_SREMNG_DPAT_LOAD_PG_INVALID            0x02002f9f��ָ���Ľ�����Ƿ�
 * @retval #OS_ERRNO_SREMNG_DPAT_LOAD_PG_NOT_RUNNING        0x02002fa0�����ػ�ж�ض�̬����ʱ���������Ľ�����δ����
 * @retval #OS_ERRNO_SREMNG_DPAT_LOAD_DLIBNAME_NULL         0x02002fa9�����ػ�ж�ز���(�����˻���BIN)�Ľ�������߶�̬����Ϊ�ա�
 * @retval #OS_ERRNO_SREMNG_DPAT_LOAD_NAME_NOT_FIND         0x02002fa1�����ػ�ж�ز����Ľ�������߶�̬����δ�ҵ���
 * @retval #OS_ERRNO_SREMNG_DPAT_UNLOAD_NAME_NOT_FIND       0x02002fa8��δ�ҵ���Ӧ�Ķ�̬��������
 * @retval #OS_ERRNO_SREMNG_DPAT_UNLOAD_LOCAL_ID_NOT_FIND   0x02002fa7��ж�ض�̬����ʱδ�ҵ��ڲ���¼�Ĺ���Ԫ���UnitNO
 * @retval #OS_ERRNO_SREMNG_DPAT_UNLOAD_NOT_FIND_IN_LIB     0x02002fa6��SRE MNG�����룺ж�ض�̬����ʱ��ָ���Ķ�̬�������߽�����δ���ض�̬������
 * @retval #OS_ERRNO_MNG_UNLOAD_WAIT_SLAVE_CORE_OVERTIME    0x02002f2c��ж�ز������ȴ��Ӻ˽����ʱ
 * @retval #OS_ERRNO_LP_NOT_LOADED                          0x02001e09��LP�����У�LP��Ԫδ����.
 * @retval #OS_ERRNO_LP_HANDLE_CORE_BUSY                    0x02001e9f����Ҫ������Ŀ�ĺ�æ�����ܽ��ж�̬���ػ���ж�ز���
 * @retval #SRE_OK                                          0x00000000����̬�������سɹ���

 * @par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_DpatLoadFromFile(SRE_DPAT_LOAD_PARA_STRU *pstPara, CHAR *pcFileName);

/**
 *@ingroup sre_lp
 *@brief ���÷�����ڴ�ռ䡣
 *
 *@par ����:�û����÷�����ڴ�ռ����ʼ��ַ�ʹ�С�������洢����๤�߽���ʱ��Ҫ��������Ϣ��
 *
 *@attention
 * <ul>
 * <li>��ַ�Ϳռ��С��4k���루MMUҳ��ӳ����Ҫ����
 * <li>�õ�ַ�ռ䰴����ʵ��ַһ�½���ӳ�䣬�Ҹÿռ䲻����������;��
 * <li>�ÿռ��������ã�������޷�������
 * <li>�ÿռ������ˣ������ֲ���ʹ��������򷴻��Ҳ��֧�ֽ�����
 * <li>�ÿռ�ʹ������ʵ��������������Դ֮�����ڽ���������֮ǰ(���������������ڶ�̬�����֮ǰ)�������˵��ã�ÿ��ʵ��������һ�Σ������ܱ�֤���еĶ�̬�ⶼ����ȷ������
 * </ul>
 *
 *@param  uwInstId [IN] ����#UINT32��ʵ��ID��
 *@param uwBufAddr  [IN] ����#UINT32���û��趨�ڴ�ռ����ʼ��ַ��
 *@param uwBufSize  [IN] ����#UINT32���趨�ռ��С��
 *
 * @retval #OS_ERRNO_SREMNG_INSTID_INVALID      0x02002f0b��ʵ��ID�Ƿ�
 * @retval #OS_ERRNO_SREMNG_INST_NOT_READY      0x02002f9a��������ʵ����δReady��
 * @retval #OS_ERRNO_MNG_DIS_ASM_LP_INITED      0x02002f9d������δ���LPģ���ʼ����
 * @retval #SRE_OK                              0x00000000���ɹ����ء�
 *
 *@par ����:
 * <ul><li>sre_mng.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_DisasmAreaSet(UINT32 uwInstID, UINT32 uwBufAddr, UINT32 uwBufSize);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MNG_H */

/**
 * History:
 * 2015-02-06.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

