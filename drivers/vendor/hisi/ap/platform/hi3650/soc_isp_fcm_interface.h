/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_fcm_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:39
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_FCM.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_FCM_INTERFACE_H__
#define __SOC_ISP_FCM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) FCM
 ****************************************************************************/
/* �Ĵ���˵����channel enable and setting.
   λ����UNION�ṹ:  SOC_ISP_FCM_CFG_UNION */
#define SOC_ISP_FCM_CFG_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x20*(CHANNEL_NBR_range)))

/* �Ĵ���˵����internal information for debugging.
   λ����UNION�ṹ:  SOC_ISP_FCM_DEBUG_UNION */
#define SOC_ISP_FCM_DEBUG_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x4+0x20*(CHANNEL_NBR_range)))

/* �Ĵ���˵����SW write request.
   λ����UNION�ṹ:  SOC_ISP_FCM_SW_WR_REQ_UNION */
#define SOC_ISP_FCM_SW_WR_REQ_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x10+0x20*(CHANNEL_NBR_range)))

/* �Ĵ���˵����SW write done.
   λ����UNION�ṹ:  SOC_ISP_FCM_SW_WR_DONE_UNION */
#define SOC_ISP_FCM_SW_WR_DONE_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x14+0x20*(CHANNEL_NBR_range)))

/* �Ĵ���˵����SW read line request.
   λ����UNION�ṹ:  SOC_ISP_FCM_SW_RD_REQ_UNION */
#define SOC_ISP_FCM_SW_RD_REQ_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x18+0x20*(CHANNEL_NBR_range)))

/* �Ĵ���˵����SW read done.
   λ����UNION�ṹ:  SOC_ISP_FCM_SW_RD_DONE_UNION */
#define SOC_ISP_FCM_SW_RD_DONE_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x1C+0x20*(CHANNEL_NBR_range)))





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
                     (1/1) FCM
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_FCM_CFG_UNION
 �ṹ˵��  : CFG �Ĵ����ṹ���塣��ַƫ����:0x20*(CHANNEL_NBR_range)����ֵ:0x00000000�����:32
 �Ĵ���˵��: channel enable and setting.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffer_depth : 13; /* bit[0-12] : Number of lines which can be stored in memory (the size depends on expected frame size)
                                                        0x0: unused
                                                        1: 1 line
                                                        2: 2 lines
                                                        ...
                                                        0x1000: 4096 lines
                                                        ��
                                                        0x1FFF: 8191 lines */
        unsigned int  reserved_0   : 3;  /* bit[13-15]: reserved */
        unsigned int  read_source  : 1;  /* bit[16]   : Read port source 
                                                        0: HW interface
                                                        1: SW interface */
        unsigned int  reserved_1   : 7;  /* bit[17-23]: reserved */
        unsigned int  write_source : 1;  /* bit[24]   : Write port source 
                                                        0: HW interface
                                                        1: SW interface */
        unsigned int  reserved_2   : 6;  /* bit[25-30]: reserved */
        unsigned int  enable       : 1;  /* bit[31]   : Enables the channel functionality */
    } reg;
} SOC_ISP_FCM_CFG_UNION;
#endif
#define SOC_ISP_FCM_CFG_buffer_depth_START  (0)
#define SOC_ISP_FCM_CFG_buffer_depth_END    (12)
#define SOC_ISP_FCM_CFG_read_source_START   (16)
#define SOC_ISP_FCM_CFG_read_source_END     (16)
#define SOC_ISP_FCM_CFG_write_source_START  (24)
#define SOC_ISP_FCM_CFG_write_source_END    (24)
#define SOC_ISP_FCM_CFG_enable_START        (31)
#define SOC_ISP_FCM_CFG_enable_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FCM_DEBUG_UNION
 �ṹ˵��  : DEBUG �Ĵ����ṹ���塣��ַƫ����:0x4+0x20*(CHANNEL_NBR_range)����ֵ:0x00000000�����:32
 �Ĵ���˵��: internal information for debugging.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  active_lines : 13; /* bit[0-12] : number of lines active in memory ( maximum allowed depends on COUNT_WIDTH)
                                                        0x0: 0 line
                                                        0x1: 1 line
                                                        ...
                                                        0x1FFF : 8191 lines */
        unsigned int  fcm_sm       : 3;  /* bit[13-15]: one channel FCM FSM for debug */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ISP_FCM_DEBUG_UNION;
#endif
#define SOC_ISP_FCM_DEBUG_active_lines_START  (0)
#define SOC_ISP_FCM_DEBUG_active_lines_END    (12)
#define SOC_ISP_FCM_DEBUG_fcm_sm_START        (13)
#define SOC_ISP_FCM_DEBUG_fcm_sm_END          (15)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FCM_SW_WR_REQ_UNION
 �ṹ˵��  : SW_WR_REQ �Ĵ����ṹ���塣��ַƫ����:0x10+0x20*(CHANNEL_NBR_range)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW write request.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  request  : 10; /* bit[0-9]  : Number of lines that the SW intends to write in the buffer. This register must not be written when request is diferent from 0 - this information is auto-cleared when the FCM acknowledges it.
                                                    0: not possible
                                                    1: 1 line
                                                    2: 2 lines
                                                    ...
                                                    0x3FF: 1023 lines */
        unsigned int  end      : 1;  /* bit[10]   : end of frame information (pulse) */
        unsigned int  reserved : 21; /* bit[11-31]: reserved */
    } reg;
} SOC_ISP_FCM_SW_WR_REQ_UNION;
#endif
#define SOC_ISP_FCM_SW_WR_REQ_request_START   (0)
#define SOC_ISP_FCM_SW_WR_REQ_request_END     (9)
#define SOC_ISP_FCM_SW_WR_REQ_end_START       (10)
#define SOC_ISP_FCM_SW_WR_REQ_end_END         (10)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FCM_SW_WR_DONE_UNION
 �ṹ˵��  : SW_WR_DONE �Ĵ����ṹ���塣��ַƫ����:0x14+0x20*(CHANNEL_NBR_range)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW write done.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  done     : 10; /* bit[0-9]  : specify the number of lines that the software has prepared/written
                                                    0: not possible
                                                    1: 1 line
                                                    2: 2 lines
                                                    ...
                                                    0x3FF: 1023 lines */
        unsigned int  reserved : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_ISP_FCM_SW_WR_DONE_UNION;
#endif
#define SOC_ISP_FCM_SW_WR_DONE_done_START      (0)
#define SOC_ISP_FCM_SW_WR_DONE_done_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FCM_SW_RD_REQ_UNION
 �ṹ˵��  : SW_RD_REQ �Ĵ����ṹ���塣��ַƫ����:0x18+0x20*(CHANNEL_NBR_range)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW read line request.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  request  : 10; /* bit[0-9]  : Number of lines that the SW intends to write in the buffer. This register must not be written when request is diferent from 0 - this information is auto-cleared when the FCM acknowledges it.
                                                    0: not possible
                                                    1: 1 line
                                                    2: 2 lines
                                                    ...
                                                    0x3FF: 1023 lines */
        unsigned int  end      : 1;  /* bit[10]   :  */
        unsigned int  reserved : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_FCM_SW_RD_REQ_UNION;
#endif
#define SOC_ISP_FCM_SW_RD_REQ_request_START   (0)
#define SOC_ISP_FCM_SW_RD_REQ_request_END     (9)
#define SOC_ISP_FCM_SW_RD_REQ_end_START       (10)
#define SOC_ISP_FCM_SW_RD_REQ_end_END         (10)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FCM_SW_RD_DONE_UNION
 �ṹ˵��  : SW_RD_DONE �Ĵ����ṹ���塣��ַƫ����:0x1C+0x20*(CHANNEL_NBR_range)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW read done.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  done     : 10; /* bit[0-9]  : specify the number of lines that the software has prepared/written
                                                    0: not possible
                                                    1: 1 line
                                                    2: 2 lines
                                                    ...
                                                    0x3FF: 1023 lines */
        unsigned int  reserved : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_ISP_FCM_SW_RD_DONE_UNION;
#endif
#define SOC_ISP_FCM_SW_RD_DONE_done_START      (0)
#define SOC_ISP_FCM_SW_RD_DONE_done_END        (9)






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

#endif /* end of soc_isp_fcm_interface.h */
