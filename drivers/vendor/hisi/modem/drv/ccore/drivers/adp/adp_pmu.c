
/*lint --e{537}*/
#include "product_config.h"
#include "mdrv_pmu.h"
#include "bsp_pmu.h"
/*****************************************************************************
*  �� �� ��  : mdrv_pmu_dcxo_fre_compensate
*  ��������  : Ϊdcxo��ȡƵ�ʲ���
*  �������  : value:��Ҫ���ڵ�ֵ
*              
*  �������  : ��
*  �� �� ֵ  : null
*             
******************************************************************************/   
void mdrv_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value)
{
    bsp_pmu_dcxo_fre_compensate(dcxoId,value);
}


