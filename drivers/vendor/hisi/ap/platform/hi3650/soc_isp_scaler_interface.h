/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_scaler_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:03
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_SCALER.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_SCALER_INTERFACE_H__
#define __SOC_ISP_SCALER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) SCALER
 ****************************************************************************/
/* �Ĵ���˵����H first pixel
   λ����UNION�ṹ:  SOC_ISP_SCALER_IHLEFT_UNION */
#define SOC_ISP_SCALER_IHLEFT_ADDR(base)              ((base) + (0x0000))

/* �Ĵ���˵����H Last  pixel
   λ����UNION�ṹ:  SOC_ISP_SCALER_IHRIGHT_UNION */
#define SOC_ISP_SCALER_IHRIGHT_ADDR(base)             ((base) + (0x0004))

/* �Ĵ���˵����H Chroma phase offset
   λ����UNION�ṹ:  SOC_ISP_SCALER_UV_HOFFSET_UNION */
#define SOC_ISP_SCALER_UV_HOFFSET_ADDR(base)          ((base) + (0x0008))

/* �Ĵ���˵����V first line
   λ����UNION�ṹ:  SOC_ISP_SCALER_IVTOP_UNION */
#define SOC_ISP_SCALER_IVTOP_ADDR(base)               ((base) + (0x000C))

/* �Ĵ���˵����V last line
   λ����UNION�ṹ:  SOC_ISP_SCALER_IVBOTTOM_UNION */
#define SOC_ISP_SCALER_IVBOTTOM_ADDR(base)            ((base) + (0x0010))

/* �Ĵ���˵����V Chroma phase offset
   λ����UNION�ṹ:  SOC_ISP_SCALER_UV_VOFFSET_UNION */
#define SOC_ISP_SCALER_UV_VOFFSET_ADDR(base)          ((base) + (0x0014))

/* �Ĵ���˵����H Inc for Luma
   λ����UNION�ṹ:  SOC_ISP_SCALER_IHINC_UNION */
#define SOC_ISP_SCALER_IHINC_ADDR(base)               ((base) + (0x0018))

/* �Ĵ���˵����V Inc for Luma
   λ����UNION�ṹ:  SOC_ISP_SCALER_IVINC_UNION */
#define SOC_ISP_SCALER_IVINC_ADDR(base)               ((base) + (0x001C))

/* �Ĵ���˵����bypass mode
   λ����UNION�ṹ:  SOC_ISP_SCALER_BYPASS_UNION */
#define SOC_ISP_SCALER_BYPASS_ADDR(base)              ((base) + (0x0024))

/* �Ĵ���˵����output format
   λ����UNION�ṹ:  SOC_ISP_SCALER_FORMAT_UNION */
#define SOC_ISP_SCALER_FORMAT_ADDR(base)              ((base) + (0x0028))

/* �Ĵ���˵����H override conf
   λ����UNION�ṹ:  SOC_ISP_SCALER_OVERRIDEH_UNION */
#define SOC_ISP_SCALER_OVERRIDEH_ADDR(base)           ((base) + (0x002C))

/* �Ĵ���˵����V override conf
   λ����UNION�ṹ:  SOC_ISP_SCALER_OVERRIDEV_UNION */
#define SOC_ISP_SCALER_OVERRIDEV_ADDR(base)           ((base) + (0x0030))

/* �Ĵ���˵����H-GKM H pos
   λ����UNION�ṹ:  SOC_ISP_SCALER_IH_HPOS_UNION */
#define SOC_ISP_SCALER_IH_HPOS_ADDR(base)             ((base) + (0x0034))

/* �Ĵ���˵����V-GKM H pos
   λ����UNION�ṹ:  SOC_ISP_SCALER_IV_HPOS_UNION */
#define SOC_ISP_SCALER_IV_HPOS_ADDR(base)             ((base) + (0x0038))

/* �Ĵ���˵����H-GKM V pos
   λ����UNION�ṹ:  SOC_ISP_SCALER_IH_VPOS_UNION */
#define SOC_ISP_SCALER_IH_VPOS_ADDR(base)             ((base) + (0x003C))

/* �Ĵ���˵����V-GKM V pos
   λ����UNION�ṹ:  SOC_ISP_SCALER_IV_VPOS_UNION */
#define SOC_ISP_SCALER_IV_VPOS_ADDR(base)             ((base) + (0x0040))

/* �Ĵ���˵����used to force the clock which is generally controlled by HW
   λ����UNION�ṹ:  SOC_ISP_SCALER_FORCE_CLK_ON_CFG_UNION */
#define SOC_ISP_SCALER_FORCE_CLK_ON_CFG_ADDR(base)    ((base) + (0x50))





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
                     (1/1) SCALER
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IHLEFT_UNION
 �ṹ˵��  : IHLEFT �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: H first pixel
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihleft   : 29; /* bit[0-28] : Position of first pixel in active area. Qu13.16 ( Qu n.m )
                                                    0:first pixel in input stream (n=0 , m=0 )
                                                    0x8000: first half pixel (n= 0, m=0,5)
                                                    0x10000:second pixel in input stream (n=1, m=0)
                                                    n.m :(n+1),m th pixel in input stream  */
        unsigned int  reserved : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_SCALER_IHLEFT_UNION;
#endif
#define SOC_ISP_SCALER_IHLEFT_ihleft_START    (0)
#define SOC_ISP_SCALER_IHLEFT_ihleft_END      (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IHRIGHT_UNION
 �ṹ˵��  : IHRIGHT �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: H Last  pixel
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihright  : 29; /* bit[0-28] : Position of last pixel in active area. Qu13.16 (Qu n.m )
                                                    0x1FFFFFF means no crop
                                                    otherwise. For correct rescaling we should have ihright = ihleft+hinc ( ohsize-1):
                                                    0:first pixel in input stream (n=0, m=0)
                                                    0x8000: first half pixel (n=0,m=0,5)
                                                    0x10000:second pixel in input stream
                                                    n.m:(n+1),m th pixel in input stream */
        unsigned int  reserved : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_SCALER_IHRIGHT_UNION;
#endif
#define SOC_ISP_SCALER_IHRIGHT_ihright_START   (0)
#define SOC_ISP_SCALER_IHRIGHT_ihright_END     (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_UV_HOFFSET_UNION
 �ṹ˵��  : UV_HOFFSET �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: H Chroma phase offset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  uv_hoffset : 4;  /* bit[0-3] : Phase offset for horizontal chroma resampling. Qu4.0
                                                     0:No offset
                                                     1:1/16 phase offset
                                                     2:2/16 phase offset
                                                     n:n/16 phase offset */
        unsigned int  reserved   : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_SCALER_UV_HOFFSET_UNION;
#endif
#define SOC_ISP_SCALER_UV_HOFFSET_uv_hoffset_START  (0)
#define SOC_ISP_SCALER_UV_HOFFSET_uv_hoffset_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IVTOP_UNION
 �ṹ˵��  : IVTOP �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: V first line
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivtop    : 29; /* bit[0-28] : Position of first line in active area. Qu13.16
                                                    0:first line in input stream (n=0 , m=0 )
                                                    0x8000: first half line (n= 0, m=0,5)
                                                    0x10000:second line in input stream (n=1, m=0)
                                                    n.m :(n+1),m th line in input stream  */
        unsigned int  reserved : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_SCALER_IVTOP_UNION;
#endif
#define SOC_ISP_SCALER_IVTOP_ivtop_START     (0)
#define SOC_ISP_SCALER_IVTOP_ivtop_END       (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IVBOTTOM_UNION
 �ṹ˵��  : IVBOTTOM �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: V last line
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivbottom : 29; /* bit[0-28] : Position of last line in active area. Qu13.16
                                                    0x1FFFFFF means no crop
                                                    otherwise. For correct rescaling we should have ivbottom=ivtop+vinc(ovsize-1):
                                                    0:first line in input stream (n=0, m=0)
                                                    0x8000: first half line (n=0,m=0,5)
                                                    0x10000:second line in input stream
                                                    n.m:(n+1),m th line in input stream */
        unsigned int  reserved : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_SCALER_IVBOTTOM_UNION;
#endif
#define SOC_ISP_SCALER_IVBOTTOM_ivbottom_START  (0)
#define SOC_ISP_SCALER_IVBOTTOM_ivbottom_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_UV_VOFFSET_UNION
 �ṹ˵��  : UV_VOFFSET �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: V Chroma phase offset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  uv_voffset : 4;  /* bit[0-3] : Phase offset for vertical chroma resampling. Qu4.0
                                                     0:No offset
                                                     1:1/16 phase offset
                                                     2:2/16 phase offset
                                                     n:n/16 phase offset */
        unsigned int  reserved   : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_SCALER_UV_VOFFSET_UNION;
#endif
#define SOC_ISP_SCALER_UV_VOFFSET_uv_voffset_START  (0)
#define SOC_ISP_SCALER_UV_VOFFSET_uv_voffset_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IHINC_UNION
 �ṹ˵��  : IHINC �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00010000�����:32
 �Ĵ���˵��: H Inc for Luma
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihinc    : 20; /* bit[0-19] : Horizontal increment (Qu4.16) for Luma.Ratio= Input Size/output Size. IHINC = 2^16 * (Input Size-1)/(output Size-1)
                                                    0x7FE6 means upscaling by 2 (ratio = 0.5 and input size=640)
                                                    0x10000 means ratio 1
                                                    0x200CD means downscaling by 2 (ratio=2 and input size=640)  */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_SCALER_IHINC_UNION;
#endif
#define SOC_ISP_SCALER_IHINC_ihinc_START     (0)
#define SOC_ISP_SCALER_IHINC_ihinc_END       (19)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IVINC_UNION
 �ṹ˵��  : IVINC �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00010000�����:32
 �Ĵ���˵��: V Inc for Luma
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivinc        : 20; /* bit[0-19] : Vertical increment (Qu4.16) for Luma.Ratio= Input Size/output size. IVINC = 2^16 *(Input Size-1)/(output Size-1)
                                                        0x7FE6 means upscaling by 2 (ratio = 0.5 and input size=640)
                                                        0x10000 means ratio 1
                                                        0x200CD means downscaling by 2 (ratio=2 and input size=640)  */
        unsigned int  halflinemode : 1;  /* bit[20-20]: recommended value is 1 when vertical scaling ratio is in range [1/6 1/2] ( 1/6<= ratio <= 1/2 ) AND output hsize <= LINE_SIZE/2. ( LINE_SIZE= 4424 for scaler#1, LINE_SIZE= 1924 for scaler#2, LINE_SIZE = 640 for scaler#3 ). Otherwise half line mode = 0 
                                                        0 : half line mode not selected 4-tap is used for vertical scaling
                                                        1: half line mode is selected, 6-tap is used for vertical scaling */
        unsigned int  reserved     : 11; /* bit[21-31]:  */
    } reg;
} SOC_ISP_SCALER_IVINC_UNION;
#endif
#define SOC_ISP_SCALER_IVINC_ivinc_START         (0)
#define SOC_ISP_SCALER_IVINC_ivinc_END           (19)
#define SOC_ISP_SCALER_IVINC_halflinemode_START  (20)
#define SOC_ISP_SCALER_IVINC_halflinemode_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_BYPASS_UNION
 �ṹ˵��  : BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000003�����:32
 �Ĵ���˵��: bypass mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 2;  /* bit[0-1] : SCALER bypass mode
                                                   0b00: no bypass
                                                   0b01: horizontal scaling bypass
                                                   0b10 :vertical scaling bypass
                                                   0b11 : vertical and horizontal scaling bypass. 
                                                   When updating this register the firmware must make sure that there are no data processed in the module  */
        unsigned int  reserved : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_SCALER_BYPASS_UNION;
#endif
#define SOC_ISP_SCALER_BYPASS_bypass_START    (0)
#define SOC_ISP_SCALER_BYPASS_bypass_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_FORMAT_UNION
 �ṹ˵��  : FORMAT �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: output format
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  outformat : 2;  /* bit[0-1] : Output format
                                                    0:YUV422 UYVY
                                                    1:YUV420 NV12 (not valid when bypass=0b1x)
                                                    2:YUV422 VYUY
                                                    3:YUV420 NV21 (not valid when bypass=0b1x) */
        unsigned int  reserved  : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_SCALER_FORMAT_UNION;
#endif
#define SOC_ISP_SCALER_FORMAT_outformat_START  (0)
#define SOC_ISP_SCALER_FORMAT_outformat_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_OVERRIDEH_UNION
 �ṹ˵��  : OVERRIDEH �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: H override conf
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h_overrideid    : 8;  /* bit[0-7]  : value of overriden horizontal id for coefficient table selection ( 1 out of 11 ).Qu8.0 */
        unsigned int  h_overridephase : 4;  /* bit[8-11] : value of overriden horizontal phase for phase selection ( 1 out of 16 ).Qu4.0 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]:  */
        unsigned int  h_id_overrideen : 1;  /* bit[16-16]: enable SW override of horizontal id of coefficient table 
                                                           0:override disabled
                                                           1:override enabled */
        unsigned int  h_ph_overrideen : 1;  /* bit[17-17]: enable SW override of horizontal phase selection of coefficient table
                                                           0:override disabled
                                                           1:override enabled */
        unsigned int  reserved_1      : 14; /* bit[18-31]:  */
    } reg;
} SOC_ISP_SCALER_OVERRIDEH_UNION;
#endif
#define SOC_ISP_SCALER_OVERRIDEH_h_overrideid_START     (0)
#define SOC_ISP_SCALER_OVERRIDEH_h_overrideid_END       (7)
#define SOC_ISP_SCALER_OVERRIDEH_h_overridephase_START  (8)
#define SOC_ISP_SCALER_OVERRIDEH_h_overridephase_END    (11)
#define SOC_ISP_SCALER_OVERRIDEH_h_id_overrideen_START  (16)
#define SOC_ISP_SCALER_OVERRIDEH_h_id_overrideen_END    (16)
#define SOC_ISP_SCALER_OVERRIDEH_h_ph_overrideen_START  (17)
#define SOC_ISP_SCALER_OVERRIDEH_h_ph_overrideen_END    (17)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_OVERRIDEV_UNION
 �ṹ˵��  : OVERRIDEV �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: V override conf
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_overrideid    : 4;  /* bit[0-3]  : value of overriden vertical id for coefficient table selection ( 1 out of 11). Qu4.0 */
        unsigned int  v_overridephase : 4;  /* bit[4-7]  : value of overriden vertical phase for phase selection ( 1 out of 16). Qu4.0 */
        unsigned int  reserved_0      : 8;  /* bit[8-15] :  */
        unsigned int  v_id_overrideen : 1;  /* bit[16-16]: enable SW override of vertical id selection of coefficient table
                                                           0:override disabled
                                                           1:override enabled */
        unsigned int  v_ph_overrideen : 1;  /* bit[17-17]: enable SW override of vertical phase selection of coefficient table 
                                                           0:override disabled
                                                           1:override enabled */
        unsigned int  reserved_1      : 14; /* bit[18-31]:  */
    } reg;
} SOC_ISP_SCALER_OVERRIDEV_UNION;
#endif
#define SOC_ISP_SCALER_OVERRIDEV_v_overrideid_START     (0)
#define SOC_ISP_SCALER_OVERRIDEV_v_overrideid_END       (3)
#define SOC_ISP_SCALER_OVERRIDEV_v_overridephase_START  (4)
#define SOC_ISP_SCALER_OVERRIDEV_v_overridephase_END    (7)
#define SOC_ISP_SCALER_OVERRIDEV_v_id_overrideen_START  (16)
#define SOC_ISP_SCALER_OVERRIDEV_v_id_overrideen_END    (16)
#define SOC_ISP_SCALER_OVERRIDEV_v_ph_overrideen_START  (17)
#define SOC_ISP_SCALER_OVERRIDEV_v_ph_overrideen_END    (17)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IH_HPOS_UNION
 �ṹ˵��  : IH_HPOS �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: H-GKM H pos
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ih_hpos : 32; /* bit[0-31]: current pixel position in horizontal scaler (debug info). Qu13.16 */
    } reg;
} SOC_ISP_SCALER_IH_HPOS_UNION;
#endif
#define SOC_ISP_SCALER_IH_HPOS_ih_hpos_START  (0)
#define SOC_ISP_SCALER_IH_HPOS_ih_hpos_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IV_HPOS_UNION
 �ṹ˵��  : IV_HPOS �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: V-GKM H pos
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iv_hpos : 32; /* bit[0-31]: current pixel position in vertical scaler (debug info). Qu13.16 */
    } reg;
} SOC_ISP_SCALER_IV_HPOS_UNION;
#endif
#define SOC_ISP_SCALER_IV_HPOS_iv_hpos_START  (0)
#define SOC_ISP_SCALER_IV_HPOS_iv_hpos_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IH_VPOS_UNION
 �ṹ˵��  : IH_VPOS �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: H-GKM V pos
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ih_vpos : 32; /* bit[0-31]: current line position in horizontal scaler (debug info ). Qu13.16 */
    } reg;
} SOC_ISP_SCALER_IH_VPOS_UNION;
#endif
#define SOC_ISP_SCALER_IH_VPOS_ih_vpos_START  (0)
#define SOC_ISP_SCALER_IH_VPOS_ih_vpos_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_IV_VPOS_UNION
 �ṹ˵��  : IV_VPOS �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: V-GKM V pos
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iv_vpos : 32; /* bit[0-31]: current line position in vertical scaler (debug info). Qu13.16 */
    } reg;
} SOC_ISP_SCALER_IV_VPOS_UNION;
#endif
#define SOC_ISP_SCALER_IV_VPOS_iv_vpos_START  (0)
#define SOC_ISP_SCALER_IV_VPOS_iv_vpos_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SCALER_FORCE_CLK_ON_CFG_UNION
 �ṹ˵��  : FORCE_CLK_ON_CFG �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x00000001�����:32
 �Ĵ���˵��: used to force the clock which is generally controlled by HW
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  force_clk_on : 1;  /* bit[0]   : 0: local clock gating is controlled by idle_detector
                                                       1: local clock gating is disabled (clock is ON) */
        unsigned int  reserved     : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_ISP_SCALER_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_SCALER_FORCE_CLK_ON_CFG_force_clk_on_START  (0)
#define SOC_ISP_SCALER_FORCE_CLK_ON_CFG_force_clk_on_END    (0)






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

#endif /* end of soc_isp_scaler_interface.h */
