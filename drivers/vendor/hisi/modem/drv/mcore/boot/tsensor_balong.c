#include <osl_common.h>
#include <osl_bio.h>
#include "hi_base.h"
#include "hi_tsensor.h"

#ifdef TSENSOR_NEW
#include <soc_onchiprom.h>
#include <soc_memmap.h>
#else
#include <hi_syssc.h>
#endif

#ifdef TSENSOR_NEW
#define TEMCODE_TO_TEMPERATURE(c) ((c-125)*165/806-40)
#define CODE_DATA_MASK 0x3FF /* bit0~9 is data */
#define CODE_SIGN_MASK 0x400 /* bit11 is signal */
int g_trim_tem = 0;

/*
 * efuse��дֵ(code)���¶�(temp)�Ķ�Ӧ��ϵ
 * bit��Ϊ11bits��MSBΪ����λ��1��ʾ����0��ʾ������Ϊ0.25�棨ÿbit������Ч��ֵΪ[-1023��1023]���¶ȿ���д��ΧΪ[-255.75�棬255.75��]��
 */
int code2temperature(int code)
{
    int temp = 0;

    temp = (code & CODE_DATA_MASK) / 4;

    return (code & CODE_SIGN_MASK) ? -temp : temp;
}
/* ***********************************
* chip�¶Ȼ�ȡ�ӿڣ�ע��:
* (1)�¶Ȳɼ�ʱ������Ϊ1.5ms
* (2)����1300(��130��)���붪��
*************************************/
int chip_tem_get(void)
{
    unsigned main_tem = 0;

    unsigned main_code = 0;

    main_code = readl(HI_TSENSOR_BASE_ADDR + HI_TEMP1_OFFSET);

    main_tem = TEMCODE_TO_TEMPERATURE(main_code);

    return main_tem + g_trim_tem;
}

int get_trim_temp(void)
{
    tOcrShareData *p_share_data = (tOcrShareData *)M3_TCM_SHARE_DATA_ADDR;
    unsigned int efuse_val = 0;
    int tem_from_tsensor = 0;
    int tem_base = 0;
    int ret = 0;

    ret = p_share_data->efuse_read(16, &efuse_val, 1);    
    if(ret)
    {
        return ret;
    }

    tem_from_tsensor = code2temperature(efuse_val & (CODE_SIGN_MASK | CODE_DATA_MASK));
    tem_base = code2temperature((efuse_val >> 11) & (CODE_SIGN_MASK | CODE_DATA_MASK));
    
    g_trim_tem = tem_base - tem_from_tsensor;
    
    return 0;
}

int tsensor_init(void)
{
    /* ͬһͨ������32�Σ���β������þ�ֵ��ͨ��ѡ��local��ת��ʱ��Ϊ0.512ms*/
    writel(0x60400, HI_TSENSOR_BASE_ADDR + HI_TEMP_CONFIG1_OFFSET); 

    /* ����ȥʹ�ܺ�ȴ� */
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_WAIT_BYPASS1_OFFSET); 

    /* ȥʹ�ܺ�ȴ�ʱ��5us */
    writel(0x1F4, HI_TSENSOR_BASE_ADDR + HI_TEMP_WAIT_TIME1_OFFSET); 

    /* �����ж�temp_mskint/temp_rst */
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_INT_MSK1_OFFSET);
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_RST_MSK1_OFFSET);

    /* ����У׼�㷨��ʹ��tsensor */
    writel(0x1, HI_TSENSOR_BASE_ADDR + HI_TEMP_DET_EN1_OFFSET);

    /* ��ȡ�����¶�ֵ */
    return get_trim_temp();
}



#else
#define TEMCODE_TO_TEMPERATURE(c) (((c)*200-60*255)*10/255)

short trim_array[]={0,8,16,23,31,39,47,55,-8,-16,-23,-31,-39,-47,-55,-62};


int tsensor_init(void)
{

    set_hi_temp_config_sample_num(0x2);    /*ͬһͨ�������Ĵ���*/

    set_hi_temp_config_sample_mode(0x2);    /*��β������þ�ֵ*/

    set_hi_temp_config_test(0x0);           /*Tsensorͨ��ѡ��local*/

    //set_hi_temp_config_ct_sel(0x01);        /*ת��ʱ��Ϊ6.144ms*/
    
    set_hi_temp_config_ct_sel(0x0);        /*ת��ʱ��Ϊ0.768ms*/
    
    set_hi_temp_dis_time_temp_dis_time(0x6);/*�л�Tsensorʱ����*/
    
    set_hi_temp_en_temp_en(0x1);    /*ʹ��*/
    
    
    return 0;
}

/* ***********************************
* chip�¶Ȼ�ȡ�ӿڣ�ע��:
* (1)�¶Ȳɼ�ʱ������Ϊ1.5ms
* (2)����1300(��130��)���붪��
*************************************/
int chip_tem_get(void)
{
    int main_tem = 0;
    int trim_tem = 0;
    
    int main_code = 0;
    int trim_code = 0;
	    
    main_code = get_hi_temp_temp();
    trim_code = get_hi_sc_stat86_efuse_tsensor_trim() & ((0x1 << 8) - 1);

    main_tem = TEMCODE_TO_TEMPERATURE(main_code);
    trim_tem = trim_array[trim_code & 0xF];
    
    return (main_tem + trim_tem);

}
#endif



