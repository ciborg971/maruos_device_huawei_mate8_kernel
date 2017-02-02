#include <bsp_abb.h>

/*****************************************************************************
 �� �� ��  : mdrv_abb_set_reg
 ��������  : set ABB register data
 �������  : regAddr --- �����üĴ�����ַ,ABB��ַλ��Ϊ9bit,32bit������չ
             setData --- ���õ�ֵ,ABB����λ��Ϊ8bit,32bit������չ
 �������  : ��
 �� �� ֵ  : 0    - successful
             -1   - unsuccessful
*****************************************************************************/
int mdrv_abb_set_reg(unsigned int regAddr, unsigned int setData)
{   
    int ret;
	ret = bsp_abb_write(regAddr, setData);
    return ret;    
}

/*****************************************************************************
 �� �� ��  : mdrv_abb_set_reg
 ��������  : get ABB register data
 �������  : regAddr --- �����Ĵ�����ַ,ABB��ַλ��Ϊ9bit,32bit������չ
 �������  : *getData --- ��żĴ���ֵ,ABB����λ��Ϊ8bit,32bit������չ
 �� �� ֵ  : 0    - successful
             -1 - unsuccessful
*****************************************************************************/
int mdrv_abb_get_reg(unsigned int regAddr, unsigned int *data)
{
    int ret;
	ret = bsp_abb_read(regAddr, data);    
    return ret;    
}

