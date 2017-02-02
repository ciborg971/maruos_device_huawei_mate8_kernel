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
	{BSP_INT_TYPE_GBBP_DSP                 , INT_LVL_GBBP_DSP},                 /* GSM1 Ԥ����DRX�ж�(g1_int_bbp_to_dsp)         */
	{BSP_INT_TYPE_GBBP_GSML_NODRX_INTR     , INT_LVL_GBBP_GSML_NODRX_INTR},     /* PHY_104Mʱ�����ж�(����������ǵ�����)        */
	{BSP_INT_TYPE_GBBP_AWAKE_DSP           , INT_LVL_GBBP_AWAKE_DSP},           /* GSM1 Ԥ��DRX�����ж�(g1_int_bbp_to_dsp_32k)   */
	{BSP_INT_TYPE_GBBP_GSML_RESERVED_INTR  , INT_LVL_GBBP_GSML_RESERVED_INTR},  /* PHY_32Kʱ�����ж�(�����ǵ�����)               */
	{BSP_INT_TYPE_GBBP                     , INT_LVL_GBBP},                     /* GSM1 ��DRX�ж�(g1_int_bbp_to_cpu)             */
	{BSP_INT_TYPE_GBBP_AWAKE               , INT_LVL_GBBP_AWAKE},               /* GSM1 DRX�����ж�(g1_int_bbp_to_cpu_32k)       */
	{BSP_INT_TYPE_GBBP1_DSP                , INT_LVL_GBBP1_DSP},                /* GSM2 Ԥ����DRX�ж�(g2_int_bbp_to_dsp)         */
	{BSP_INT_TYPE_GBBP1_AWAKE_DSP          , INT_LVL_GBBP1_AWAKE_DSP},          /* GSM2 Ԥ��DRX�����ж�(g2_int_bbp_to_dsp_32k)   */
	{BSP_INT_TYPE_GBBP1                    , INT_LVL_GBBP1},                    /* GSM2 ��DRX�ж�(g2_int_bbp_to_cpu)             */
	{BSP_INT_TYPE_GBBP1_AWAKE              , INT_LVL_GBBP1_AWAKE},              /* GSM2 DRX�����ж�(g2_int_bbp_to_cpu_32k)       */
	{BSP_INT_TYPE_WBBP_0MS                 , INT_LVL_WBBP_0MS},                 /* card1 0ms�ж�                                 */
	{BSP_INT_TYPE_WBBP_AWAKE               , INT_LVL_WBBP_AWAKE},               /* ˯�ߡ������ж�                                */
	{BSP_INT_TYPE_WBBP_SWITCH              , INT_LVL_WBBP_SWITCH},              /* ʱ���л��ж�                                  */
	{BSP_INT_TYPE_WBBP1_0MS                , INT_LVL_WBBP1_0MS},                /* Card2 0ms �ж�                                */
	{BSP_INT_TYPE_WBBP_CARD2_0MS_INTR      , INT_LVL_WBBP_CARD2_0MS_INTR},      /* Card2 0ms �ж�                                */
	{BSP_INT_TYPE_WBBP_SEARCH              , INT_LVL_WBBP_SEARCH},              /* С�������ж�                                  */
	{BSP_INT_TYPE_WBBP_SEARCH_INTR         , INT_LVL_WBBP_SEARCH_INTR},         /* С�������ж�                                  */
	{BSP_INT_TYPE_WBBP_RAKE                , INT_LVL_WBBP_RAKE},                /* Rake����ϱ��ж�                              */
	{BSP_INT_TYPE_WBBP_RAKE_INTR           , INT_LVL_WBBP_RAKE_INTR},           /* Rake����ϱ��ж�                              */
	{BSP_INT_TYPE_WBBP_DECODE              , INT_LVL_WBBP_DECODE},              /* ���������ϱ��ж�                              */
	{BSP_INT_TYPE_WBBP_DECODE_INTR         , INT_LVL_WBBP_DECODE_INTR},         /* ���������ϱ��ж�                              */
	{BSP_INT_TYPE_WBBP_TIME                , INT_LVL_WBBP_TIME},                /* card1��ʱ�ж�                                 */
	{BSP_INT_TYPE_WBBP_CARD1_TIME_INTR     , INT_LVL_WBBP_CARD1_TIME_INTR},     /* card1��ʱ�ж�                                 */
	{BSP_INT_TYPE_WBBP1_TIME               , INT_LVL_WBBP1_TIME},               /* card2��ʱ�ж�                                 */
	{BSP_INT_TYPE_WBBP_CARD2_TIME_INTR     , INT_LVL_WBBP_CARD2_TIME_INTR},     /* card2��ʱ�ж�                                 */
	{BSP_INT_TYPE_WBBP_MULTI_SEARCH        , INT_LVL_WBBP_MULTI_SEARCH},        /* �ྶ���������ж�                              */
	{BSP_INT_TYPE_WBBP_MULTI_SEARCH_INTR   , INT_LVL_WBBP_MULTI_SEARCH_INTR},   /* �ྶ���������ж�                              */
	{BSP_INT_TYPE_WBBP_BBPMST              , INT_LVL_WBBP_BBPMST},              /* ����BBP Master�ϱ��ж�                        */
	{BSP_INT_TYPE_BBPMASTER                , INT_LVL_BBPMASTER},                /* ����BBP Master�ϱ��ж�                        */
	{BSP_INT_TYPE_CTU_INT_G                , INT_LVL_CTU_INT_G},                /* CTU������Gģ��ص��ж�(G����Ϊ��ģ��Ҳ����Ϊ��ģ)*/
	{BSP_INT_TYPE_CTU_INT_W                , INT_LVL_CTU_INT_W},                /* CTU������Wģ��ص��ж�(W����Ϊ��ģ��Ҳ����Ϊ��ģ)*/
	{BSP_INT_TYPE_INT12_G2                 , INT_LVL_INT12_G2},                 /* ��δ����                                         */
	{BSP_INT_TYPE_UPACC_DSP                , INT_LVL_GU_UPACC_DSP},             /* ��Ҫ����ȷ��                                     */
	{BSP_INT_TYPE_UPACC_INTR               , INT_LVL_UPACC_INTR},               /* ��Ҫ����ȷ��                                     */
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
	{BSP_INT_TYPE_GUCBBP_AXIMST_ERR0       , INT_LVL_GUC_BBPMST_INT0},      /* GUC BBP AXI MST����Ĵ����ж�0 */
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
