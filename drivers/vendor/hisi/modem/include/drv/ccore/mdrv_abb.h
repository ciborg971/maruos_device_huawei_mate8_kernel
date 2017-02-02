#ifndef __MDRV_CCORE_ABB_H__
#define __MDRV_CCORE_ABB_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
* �� �� ��  : mdrv_abb_set_reg
*
* ��������  : ����abb�Ĵ���
*
* �������  : unsigned int regAddr �Ĵ����ĵ�ַƫ��
*             unsigned int setData �Ĵ������õ�ֵ
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_abb_set_reg(unsigned int regAddr, unsigned int setData);
/*****************************************************************************
* �� �� ��  : mdrv_abb_get_reg
*
* ��������  : ��ȡabb�Ĵ�����ֵ
*
* �������  : unsigned int regAddr �Ĵ����ĵ�ַƫ��
*             unsigned int *data   �洢�Ĵ�����ֵַ��buffer
* �������  : unsigned int *data   �洢�Ĵ�����ֵַ
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_abb_get_reg(unsigned int regAddr, unsigned int *data);

#ifdef __cplusplus
}
#endif
#endif
