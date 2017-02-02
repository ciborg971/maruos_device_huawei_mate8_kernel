#include <osl_bio.h>
#include <soc_memmap.h>
#include <product_config.h>
#ifdef CONFIG_PMIC_HI6551
#include <hi_smartstar.h>
#endif
#ifdef CONFIG_PMIC_HI6559
#include <hi_bbstar.h>
#endif
#include <bsp_pmu.h>


#ifdef CONFIG_PMIC_HI6551
void bsp_hi6551_reg_write( u16 addr, u8 value)
{
    writel((u32) value,(u32)(HI_PMUSSI0_REGBASE_ADDR + (addr << 2)));
}
/*��λ:mv*/
int bsp_pmu_volt_set(int volt_id,int voltage_mv)
{
    int iret=0;

    switch(volt_id)
    {
        case PMIC_HI6551_BUCK3:
            if(925 == voltage_mv)
                bsp_hi6551_reg_write(HI6551_VSET_BUCK3_ADJ_OFFSET,0x07);
            else if(950 == voltage_mv)
                bsp_hi6551_reg_write(HI6551_VSET_BUCK3_ADJ_OFFSET,0x08);
            else
                iret = -1;
            break;
        case PMIC_HI6551_LDO03:
            if(950 == voltage_mv)
                bsp_hi6551_reg_write(HI6551_LDO3_REG_ADJ_OFFSET,0x13);
            else
            {

                iret = -1;
            }
            break;
        default:
            iret = -1;
            break;

    }
    return iret;
}

#elif defined(CONFIG_PMIC_HI6559)
/*****************************************************************************
 �� �� ��  : bsp_hi6559_reg_write
 ��������  : д�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_reg_write(u16 addr, u8 value)
{
    writel((u32) value,(u32)(HI_PMUSSI0_REGBASE_ADDR + (addr << 2)));
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_volt_set
 ��������  : ���õ�Դ��ѹ
 �������  : @volt_id: ��ԴID
             @voltage_mv: ��ѹֵ(mV)
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 bsp_pmu_volt_set(s32 volt_id,s32 voltage_mv)
{
    s32 iret=0;

    switch(volt_id)
    {
        case PMIC_HI6559_BUCK3:
            if(924 == voltage_mv)
            {
                bsp_hi6559_reg_write(HI6559_VSET_BUCK3_ADJ_OFFSET,0x1C);
            }
            else if(948 == voltage_mv)
            {
                bsp_hi6559_reg_write(HI6559_VSET_BUCK3_ADJ_OFFSET,0x1F);
            }
            else
            {
                iret = -1;
            }
            break;
        case PMIC_HI6559_LDO03:
            if(925 == voltage_mv)
            {
                bsp_hi6559_reg_write(HI6559_LDO3_REG_ADJ_OFFSET,0x04);
            }
            else if(950 == voltage_mv)
            {
                bsp_hi6559_reg_write(HI6559_LDO3_REG_ADJ_OFFSET,0x05);
            }
            else
            {
                iret = -1;
            }
            break;
        default:
            iret = -1;
            break;

    }
    return iret;
}
#else
s32 bsp_pmu_volt_set(s32 volt_id,s32 voltage)
{
    return 0;
}
s32 bsp_pmu_resume(void)
{
    return 0;
}
#endif

