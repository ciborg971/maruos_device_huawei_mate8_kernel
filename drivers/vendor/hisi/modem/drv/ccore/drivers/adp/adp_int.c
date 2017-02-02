#include <product_config.h>
#include <soc_interrupts.h>
//#include <mdrv_int.h>
#include <osl_irq.h>
#include <bsp_vic.h>

/*lint --e{438, 801} */

typedef int  (*pFUNCPTR)(void);
typedef void (*VOIDFUNCPTR)(unsigned int );
#include <mdrv_int_comm.h>

struct irq_num_map
{
	BSP_INT_TYPE_E int_type;
	unsigned int irq_num;
};

static const struct irq_num_map irq_nums[] = {
	{BSP_INT_TYPE_GBBP_DSP                 , INT_LVL_GBBP_DSP},                 /* GSM1 预留非DRX中断(g1_int_bbp_to_dsp)         */
	{BSP_INT_TYPE_GBBP_GSML_NODRX_INTR     , INT_LVL_GBBP_GSML_NODRX_INTR},     /* PHY_104M时钟域中断(含掉电区与非掉电区)        */
	{BSP_INT_TYPE_GBBP_AWAKE_DSP           , INT_LVL_GBBP_AWAKE_DSP},           /* GSM1 预留DRX唤醒中断(g1_int_bbp_to_dsp_32k)   */
	{BSP_INT_TYPE_GBBP_GSML_RESERVED_INTR  , INT_LVL_GBBP_GSML_RESERVED_INTR},  /* PHY_32K时钟域中断(仅含非掉电区)               */
	{BSP_INT_TYPE_GBBP                     , INT_LVL_GBBP},                     /* GSM1 非DRX中断(g1_int_bbp_to_cpu)             */
	{BSP_INT_TYPE_GBBP_AWAKE               , INT_LVL_GBBP_AWAKE},               /* GSM1 DRX唤醒中断(g1_int_bbp_to_cpu_32k)       */
	{BSP_INT_TYPE_GBBP1_DSP                , INT_LVL_GBBP1_DSP},                /* GSM2 预留非DRX中断(g2_int_bbp_to_dsp)         */
	{BSP_INT_TYPE_GBBP1_AWAKE_DSP          , INT_LVL_GBBP1_AWAKE_DSP},          /* GSM2 预留DRX唤醒中断(g2_int_bbp_to_dsp_32k)   */
	{BSP_INT_TYPE_GBBP1                    , INT_LVL_GBBP1},                    /* GSM2 非DRX中断(g2_int_bbp_to_cpu)             */
	{BSP_INT_TYPE_GBBP1_AWAKE              , INT_LVL_GBBP1_AWAKE},              /* GSM2 DRX唤醒中断(g2_int_bbp_to_cpu_32k)       */
	{BSP_INT_TYPE_WBBP_0MS                 , INT_LVL_WBBP_0MS},                 /* card1 0ms中断                                 */
	{BSP_INT_TYPE_WBBP_AWAKE               , INT_LVL_WBBP_AWAKE},               /* 睡眠、唤醒中断                                */
	{BSP_INT_TYPE_WBBP_SWITCH              , INT_LVL_WBBP_SWITCH},              /* 时钟切换中断                                  */
	{BSP_INT_TYPE_WBBP1_0MS                , INT_LVL_WBBP1_0MS},                /* Card2 0ms 中断                                */
	{BSP_INT_TYPE_WBBP_CARD2_0MS_INTR      , INT_LVL_WBBP_CARD2_0MS_INTR},      /* Card2 0ms 中断                                */
	{BSP_INT_TYPE_WBBP_SEARCH              , INT_LVL_WBBP_SEARCH},              /* 小区搜索中断                                  */
	{BSP_INT_TYPE_WBBP_SEARCH_INTR         , INT_LVL_WBBP_SEARCH_INTR},         /* 小区搜索中断                                  */
	{BSP_INT_TYPE_WBBP_RAKE                , INT_LVL_WBBP_RAKE},                /* Rake解调上报中断                              */
	{BSP_INT_TYPE_WBBP_RAKE_INTR           , INT_LVL_WBBP_RAKE_INTR},           /* Rake解调上报中断                              */
	{BSP_INT_TYPE_WBBP_DECODE              , INT_LVL_WBBP_DECODE},              /* 译码数据上报中断                              */
	{BSP_INT_TYPE_WBBP_DECODE_INTR         , INT_LVL_WBBP_DECODE_INTR},         /* 译码数据上报中断                              */
	{BSP_INT_TYPE_WBBP_TIME                , INT_LVL_WBBP_TIME},                /* card1定时中断                                 */
	{BSP_INT_TYPE_WBBP_CARD1_TIME_INTR     , INT_LVL_WBBP_CARD1_TIME_INTR},     /* card1定时中断                                 */
	{BSP_INT_TYPE_WBBP1_TIME               , INT_LVL_WBBP1_TIME},               /* card2定时中断                                 */
	{BSP_INT_TYPE_WBBP_CARD2_TIME_INTR     , INT_LVL_WBBP_CARD2_TIME_INTR},     /* card2定时中断                                 */
	{BSP_INT_TYPE_WBBP_MULTI_SEARCH        , INT_LVL_WBBP_MULTI_SEARCH},        /* 多径搜索测量中断                              */
	{BSP_INT_TYPE_WBBP_MULTI_SEARCH_INTR   , INT_LVL_WBBP_MULTI_SEARCH_INTR},   /* 多径搜索测量中断                              */
	{BSP_INT_TYPE_WBBP_BBPMST              , INT_LVL_WBBP_BBPMST},              /* 译码BBP Master上报中断                        */
	{BSP_INT_TYPE_BBPMASTER                , INT_LVL_BBPMASTER},                /* 译码BBP Master上报中断                        */
	{BSP_INT_TYPE_CTU_INT_G                , INT_LVL_CTU_INT_G},                /* CTU产生与G模相关的中断(G可以为主模，也可以为从模)*/
	{BSP_INT_TYPE_CTU_INT_W                , INT_LVL_CTU_INT_W},                /* CTU产生与W模相关的中断(W可以为主模，也可以为从模)*/
	{BSP_INT_TYPE_INT12_G2                 , INT_LVL_INT12_G2},                 /* 暂未适配                                         */
	{BSP_INT_TYPE_UPACC_DSP                , INT_LVL_GU_UPACC_DSP},             /* 需要后续确认                                     */
	{BSP_INT_TYPE_UPACC_INTR               , INT_LVL_UPACC_INTR},               /* 需要后续确认                                     */
	{BSP_INT_TYPE_CICOM_DL                 , INT_LVL_CICOM_DL},
	{BSP_INT_TYPE_CICOM_UL                 , INT_LVL_CICOM_UL},
	{BSP_INT_TYPE_CICOM1_DL                , INT_LVL_GU_CICOM1_DL},
	{BSP_INT_TYPE_CICOM1_UL                , INT_LVL_GU_CICOM1_UL},
    {BSP_INT_TYPE_HDLC_FRM                 , INT_LVL_GU_HDLC_FRM},
    {BSP_INT_TYPE_HDLC_DEF                 , INT_LVL_GU_HDLC_DEF},
	{BSP_INT_TYPE_LBBP_AWAKE               , INT_LVL_LTE_ARM_WAKEUP_INT},
	{BSP_INT_TYPE_TBBP_AWAKE               , INT_LVL_TDS_DRX_ARM_WAKEUP_INT},
	{BSP_INT_TYPE_CBBP_INTR01              , INT_LVL_CBBP_INTR01},
	{BSP_INT_TYPE_CBBP_INTR02              , INT_LVL_CBBP_INTR02},
	{BSP_INT_TYPE_CBBP_INTR04              , INT_LVL_CBBP_INTR04},
	{BSP_INI_TYPE_COMM_32K_INT             , INT_LVL_COMM_32K},
	{BSP_INT_TYPE_GUCBBP_AXIMST_ERR0       , INT_LVL_GUC_BBPMST_INT0},      /* GUC BBP AXI MST输出的错误中断0 */
	};


int mdrv_int_enable(int ulLev)
{
	if(ulLev < INT_LVL_MAX && ulLev >= 0)
		return enable_irq((unsigned int)ulLev);
	else if(ulLev >= INT_LVL_MAX && ulLev < INT_LVL_MAX + 32 * 4)
	{
#ifdef CONFIG_MODULE_VIC
		return bsp_vic_enable(ulLev - INT_LVL_MAX);
#else
		return -1;
#endif
	}
	else
		return -1;
}

int mdrv_int_disable(int ulLev)
{
	if(ulLev < INT_LVL_MAX && ulLev >= 0)
		return disable_irq((unsigned int)ulLev);
	else if(ulLev >= INT_LVL_MAX && ulLev < INT_LVL_MAX + 32 * 4)
	{
#ifdef CONFIG_MODULE_VIC
		return bsp_vic_disable(ulLev - INT_LVL_MAX);
#else
		return -1;
#endif
	}
	else
		return -1;
}

int mdrv_int_connect(int level, VOIDFUNCPTR routine, unsigned int parameter)
{
	if(level < INT_LVL_MAX && level >= 0)
		return osl_int_connect((unsigned int)level,(irq_handler_t)routine,(int)parameter);
	else if(level >= INT_LVL_MAX && level < INT_LVL_MAX + 32 * 4)
	{
#ifdef CONFIG_MODULE_VIC
		return bsp_vic_connect(level - INT_LVL_MAX,(vicfuncptr)routine,parameter);
#else
		return -1;
#endif
	}
	else
		return -1;
}

int mdrv_int_disconnect(int level, unsigned int parameter)
{
	if(level < INT_LVL_MAX && level >= 0)
		return osl_int_disconnect((unsigned int)level, NULL, (int)parameter);
	else if(level >= INT_LVL_MAX && level < INT_LVL_MAX + 32 * 4)
	{
#ifdef CONFIG_MODULE_VIC
		return bsp_vic_disconnect(level - INT_LVL_MAX);
#else
		return -1;
#endif
	}
	else
		return -1;
}

int mdrv_int_get_num (BSP_INT_TYPE_E enIntType)
{
	int i       = 0;
	int int_num = 0;

	while((i < (int)(sizeof(irq_nums) / sizeof(struct irq_num_map))) &&
		(enIntType != irq_nums[i].int_type))
		i++;
	if(i < (int)(sizeof(irq_nums) / sizeof(struct irq_num_map)))
		int_num = (int)irq_nums[i].irq_num;
	return int_num;
}

unsigned int mdrv_int_is_inside_context(void)
{
	return (unsigned int)osl_int_context();
}

void mdrv_int_send_nmi(unsigned int SocBitNO, unsigned int ZspBitNO)
{
	SocBitNO = SocBitNO;
	ZspBitNO = ZspBitNO;
}

void mdrv_int_register_exithook(pFUNCPTR p_Func)
{
	p_Func = p_Func;
}

void mdrv_int_unregister_exithook(void)
{
}

void mdrv_int_register_enterhook(pFUNCPTR p_Func)
{
	p_Func= p_Func;
}

void mdrv_int_unregister_enterhook(void)
{
}
