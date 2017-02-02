/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_frame_merger_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-04-08 11:46:50
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��8��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_FRAME_MERGER.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_FRAME_MERGER_INTERFACE_H__
#define __SOC_ISP_FRAME_MERGER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) FRAME_MERGER
 ****************************************************************************/
/* �Ĵ���˵����Configuration register.
   λ����UNION�ṹ:  SOC_ISP_FRAME_MERGER_CFG_UNION */
#define SOC_ISP_FRAME_MERGER_CFG_ADDR(base)           ((base) + (0x0))

/* �Ĵ���˵����Debug control register.
   λ����UNION�ṹ:  SOC_ISP_FRAME_MERGER_DEBUG_CFG_UNION */
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_ADDR(base)     ((base) + (0x4))

/* �Ĵ���˵����Debug register.
   λ����UNION�ṹ:  SOC_ISP_FRAME_MERGER_DEBUG_UNION */
#define SOC_ISP_FRAME_MERGER_DEBUG_ADDR(base)         ((base) + (0x8))





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/

/****************************************************************************
                     (1/1) FRAME_MERGER
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_FRAME_MERGER_CFG_UNION
 �ṹ˵��  : CFG �Ĵ����ṹ���塣��ַƫ����:0x0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Configuration register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : Mode of Operation
                                                   0: normal
                                                   1: interleaved */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_FRAME_MERGER_CFG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_CFG_mode_START      (0)
#define SOC_ISP_FRAME_MERGER_CFG_mode_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FRAME_MERGER_DEBUG_CFG_UNION
 �ṹ˵��  : DEBUG_CFG �Ĵ����ṹ���塣��ַƫ����:0x4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Debug control register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fe2_fifo_peak_en : 1;  /* bit[0]   : enable the FE2 FIFO peak functionality */
        unsigned int  reserved         : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_FRAME_MERGER_DEBUG_CFG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_fe2_fifo_peak_en_START  (0)
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_fe2_fifo_peak_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FRAME_MERGER_DEBUG_UNION
 �ṹ˵��  : DEBUG �Ĵ����ṹ���塣��ַƫ����:0x8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Debug register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fe2_fifo_peak         : 16; /* bit[0-15] : FE2 FIFO level peak */
        unsigned int  fe2_fsm_router        : 5;  /* bit[16-20]: FE2 router FSM state */
        unsigned int  fe2_fsm_pack          : 2;  /* bit[21-22]: FE2 pack FSM state */
        unsigned int  fe2_fsm_unpack        : 2;  /* bit[23-24]: FE2 unpack FSM state */
        unsigned int  fe2_fsm_pressure_mode : 1;  /* bit[25]   : FE2 pressure mode FSM state  */
        unsigned int  reserved              : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_FRAME_MERGER_DEBUG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fifo_peak_START          (0)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fifo_peak_END            (15)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_router_START         (16)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_router_END           (20)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pack_START           (21)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pack_END             (22)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_unpack_START         (23)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_unpack_END           (24)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pressure_mode_START  (25)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pressure_mode_END    (25)






/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_isp_frame_merger_interface.h */
