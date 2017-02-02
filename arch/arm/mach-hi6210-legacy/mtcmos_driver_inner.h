

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include <regulator_info.h>

#ifndef __MTCMOS_DRIVER_INNER_H__
#define __MTCMOS_DRIVER_INNER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*mtcmos ��Ӧ�ļĴ���*/
#if defined(CHIP_BB_HI6210)
/*B050 Modify*/
#else
#define CALC_REG_OFFSET_BASE_ADDR 0

#define SC_MTCMOS_STAT0 SOC_AO_SCTRL_SC_MTCMOS_STAT0_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_MTCMOS_STAT1 SOC_AO_SCTRL_SC_MTCMOS_STAT1_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_PW_EN0 SOC_AO_SCTRL_SC_PW_EN0_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_PW_EN1 SOC_AO_SCTRL_SC_PW_EN1_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_PW_DIS0 SOC_AO_SCTRL_SC_PW_DIS0_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_PW_DIS1 SOC_AO_SCTRL_SC_PW_DIS1_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#endif


#define MTCMOS_ON_STATUS 1
/*�����Ӧ��mskֵ*/
#define CALC_REG_MSK(bit_start, bit_end) \
    (((0x1 << (bit_end - bit_start + 1)) - 1) << bit_start)

/*mtcmos �ȶ�ʱ��*/
#define TCXO_FREQ 19200000 //19.2Mhz
#define MTCMOS_PWON_TIME 10 //10us
#define MTCMOS_PWON_TIME_COUNTER (TCXO_FREQ * MTCMOS_PWON_TIME / 1000000)
#define MTCMOS_PWON_STATE_CHECK_COUNTER 200

/*mtcmosƽ̨��ʼIDֵ*/
#define PLATFORM_MTCMOS_BEGIN_ID MTCMOS_ID_BEGIN

#define lock(x) mutex_lock(x)
#define unlock(x)  mutex_unlock(x)
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
#if defined(CHIP_BB_HI6210)
/*B050 Modify*/
enum mcmos_vcc_enum {
/*MTCMOS Block 1*/
    VCC_ENUM_BEGIN = 0,
    VCC_BLOCK1_START = VCC_ENUM_BEGIN,
    VCC_PERI = VCC_BLOCK1_START,
    VCC_G3D,
    VCC_CODECISP,
    VCC_MCPU,
    VCC_BBPHARQMEM,
    VCC_HIFI,
    VCC_ACPUCLUSTER,
    VCC_BLOCK1_END,
/*MTCMOS in acpu_sc*/
    VCC_ACPU1 = VCC_BLOCK1_END,
    VCC_ACPU2,
    VCC_ACPU3,
    VCC_ENUM_END,
};
#else
enum mcmos_vcc_enum {
/*MTCMOS Block 1*/
    VCC_ENUM_BEGIN = 0,
    VCC_BLOCK1_START = VCC_ENUM_BEGIN,
    VCC_G2D = VCC_BLOCK1_START,
    VCC_EDC0,
    VCC_EDC1,
    VCC_ISP,
    VCC_ENC,
    VCC_DEC,
    VCC_HIFI,
    VCC_VPP,
    VCC_DSPBBE,
    VCC_GBBP1,
    VCC_GBBP2,
    VCC_LTEBBP,
    VCC_BBPCOMM2,
    VCC_WTDBBP1,
    VCC_WTDBBP2,
    VCC_BLOCK1_END,
/*MTCMOS Block 2*/
    VCC_BLOCK2_START = VCC_BLOCK1_END,
    VCC_ACPU1 = VCC_BLOCK2_START,
    VCC_ACPU2,
    VCC_ACPU3,
    VCC_CM3MEM,
    VCC_MCPU,
    VCC_BLOCK2_END,
    VCC_ENUM_END = VCC_BLOCK2_END,
};
#endif

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*mtcmos��Դ�ȶ��������Ĵ������ݽṹ*/
struct mtcmos_pwup_time_reg_stru {
    unsigned int pwup_time_reg;  //mtcmos��Դ�ȶ��������Ĵ���
    unsigned int pwup_time_mask; //mtcmos��Դ�ȶ��������Ĵ�������λ
    unsigned int pwup_time_start_bit;//mtcmos��Դ�ȶ��������Ĵ�����ʼλ
};
/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


extern int mtcmos_power_is_on( int id );

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mtcmos_driver_inner.h */
