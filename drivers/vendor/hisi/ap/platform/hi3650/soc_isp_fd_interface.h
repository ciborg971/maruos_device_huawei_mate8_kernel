/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_fd_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:40
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_FD.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_FD_INTERFACE_H__
#define __SOC_ISP_FD_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) FD
 ****************************************************************************/
/* �Ĵ���˵����control register
   λ����UNION�ṹ:  SOC_ISP_FD_CTRL_UNION */
#define SOC_ISP_FD_CTRL_ADDR(base)                    ((base) + (0x0000))

/* �Ĵ���˵����face detection result count register
   λ����UNION�ṹ:  SOC_ISP_FD_RESULT_CNT_UNION */
#define SOC_ISP_FD_RESULT_CNT_ADDR(base)              ((base) + (0x0004))

/* �Ĵ���˵����detection condition setting register
   λ����UNION�ṹ:  SOC_ISP_FD_DETECT_CONDITION_UNION */
#define SOC_ISP_FD_DETECT_CONDITION_ADDR(base)        ((base) + (0x0008))

/* �Ĵ���˵����detection area (starting X-coordinate) setting register
   λ����UNION�ṹ:  SOC_ISP_FD_DETECT_START_X_UNION */
#define SOC_ISP_FD_DETECT_START_X_ADDR(base)          ((base) + (0x000c))

/* �Ĵ���˵����detection area (starting Y-coordinate) setting register
   λ����UNION�ṹ:  SOC_ISP_FD_DETECT_START_Y_UNION */
#define SOC_ISP_FD_DETECT_START_Y_ADDR(base)          ((base) + (0x0010))

/* �Ĵ���˵����detection area(X-direction size) setting register
   λ����UNION�ṹ:  SOC_ISP_FD_DETECT_SIZE_X_UNION */
#define SOC_ISP_FD_DETECT_SIZE_X_ADDR(base)           ((base) + (0x0014))

/* �Ĵ���˵����detection area(Y-direction size) setting register
   λ����UNION�ṹ:  SOC_ISP_FD_DETECT_SIZE_Y_UNION */
#define SOC_ISP_FD_DETECT_SIZE_Y_ADDR(base)           ((base) + (0x0018))

/* �Ĵ���˵����threshold setting register
   λ����UNION�ṹ:  SOC_ISP_FD_THRESHOLD_UNION */
#define SOC_ISP_FD_THRESHOLD_ADDR(base)               ((base) + (0x001c))

/* �Ĵ���˵����non raster base address
   λ����UNION�ṹ:  SOC_ISP_FD_BASE_ADDR_UNION */
#define SOC_ISP_FD_BASE_ADDR_ADDR(base)               ((base) + (0x0020))

/* �Ĵ���˵����version register
   λ����UNION�ṹ:  SOC_ISP_FD_VERSION_UNION */
#define SOC_ISP_FD_VERSION_ADDR(base)                 ((base) + (0x0038))

/* �Ĵ���˵����detection result (X-coordinate register[1-35]
   λ����UNION�ṹ:  SOC_ISP_FD_RESULT_X_UNION */
#define SOC_ISP_FD_RESULT_X_ADDR(base, result_range)  ((base) + (0x0400+(result_range)*16))

/* �Ĵ���˵����detection result (Y-coordinate) register[1-35]
   λ����UNION�ṹ:  SOC_ISP_FD_RESULT_Y_UNION */
#define SOC_ISP_FD_RESULT_Y_ADDR(base, result_range)  ((base) + (0x0404+(result_range)*16))

/* �Ĵ���˵����detection result (confidence level/size) register[1-35]
   λ����UNION�ṹ:  SOC_ISP_FD_RESULT_LS_UNION */
#define SOC_ISP_FD_RESULT_LS_ADDR(base, result_range)  ((base) + (0x0408+(result_range)*16))

/* �Ĵ���˵����detection result (angle) register[1-35]
   λ����UNION�ṹ:  SOC_ISP_FD_RESULT_ANGLE_UNION */
#define SOC_ISP_FD_RESULT_ANGLE_ADDR(base, result_range)  ((base) + (0x040c+(result_range)*16))





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
                     (1/1) FD
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_CTRL_UNION
 �ṹ˵��  : CTRL �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x69A54280�����:32
 �Ĵ���˵��: control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]    : Soft Reset (Masked) */
        unsigned int  RUN      : 1;  /* bit[1]    : Process Start request
                                                    0��(Disable)
                                                    1��Process Start Request */
        unsigned int  FINISH   : 1;  /* bit[2]    : Process Completion Flag Clear
                                                    0��(Disable)
                                                    1��Process Complete Flag Clear */
        unsigned int  reserved_1: 3;  /* bit[3-5]  :  */
        unsigned int  RD_IID   : 7;  /* bit[6-12] : Read Index ID used for indexing the MMU */
        unsigned int  RD_SID   : 6;  /* bit[13-18]: Read Stream ID used for indexing the MMU */
        unsigned int  WR_IID   : 7;  /* bit[19-25]: Write Index ID used for indexing the MMU */
        unsigned int  WR_SID   : 6;  /* bit[26-31]: Write Stream ID used for indexing the MMU */
    } reg;
} SOC_ISP_FD_CTRL_UNION;
#endif
#define SOC_ISP_FD_CTRL_RUN_START       (1)
#define SOC_ISP_FD_CTRL_RUN_END         (1)
#define SOC_ISP_FD_CTRL_FINISH_START    (2)
#define SOC_ISP_FD_CTRL_FINISH_END      (2)
#define SOC_ISP_FD_CTRL_RD_IID_START    (6)
#define SOC_ISP_FD_CTRL_RD_IID_END      (12)
#define SOC_ISP_FD_CTRL_RD_SID_START    (13)
#define SOC_ISP_FD_CTRL_RD_SID_END      (18)
#define SOC_ISP_FD_CTRL_WR_IID_START    (19)
#define SOC_ISP_FD_CTRL_WR_IID_END      (25)
#define SOC_ISP_FD_CTRL_WR_SID_START    (26)
#define SOC_ISP_FD_CTRL_WR_SID_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_RESULT_CNT_UNION
 �ṹ˵��  : RESULT_CNT �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: face detection result count register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DNUM     : 6;  /* bit[0-5] : Face Detection Result Count: Valid range 0x0 ~ 0x23 (Max 35) */
        unsigned int  reserved : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_FD_RESULT_CNT_UNION;
#endif
#define SOC_ISP_FD_RESULT_CNT_DNUM_START      (0)
#define SOC_ISP_FD_RESULT_CNT_DNUM_END        (5)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_DETECT_CONDITION_UNION
 �ṹ˵��  : DETECT_CONDITION �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection condition setting register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MIN      : 2;  /* bit[0-1] : Min Face Size Settings
                                                   0x0��Set the min face size to 20 pixel
                                                   0x1��Set the min face size to 25 pixel
                                                   0x2��Set the min face size to 32 pixel
                                                   0x3��Set the min face size to 40 pixel */
        unsigned int  DIR      : 4;  /* bit[2-5] : Detection direction settings
                                                   0x0��Detects the face of UP direction(0���45��)
                                                   0x1��Detects the face of RIGHT direction(90���45��)
                                                   0x2��Detects the face of LEFT direction(270���45��)
                                                   0x3��Detects the face of DOWN direction(180���45��)
                                                   0x4��Detects the face of UP direction(0���135��)
                                                   0x5��Detects the face of RIGHT direction(90���135��)
                                                   0x6��Detects the face of LEFT direction(270���135��)
                                                   0x7��Detects the face of DOWN direction(180���135��)
                                                   0x8��Detects the face of alldirection(0�㡫359��) */
        unsigned int  reserved : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_FD_DETECT_CONDITION_UNION;
#endif
#define SOC_ISP_FD_DETECT_CONDITION_MIN_START       (0)
#define SOC_ISP_FD_DETECT_CONDITION_MIN_END         (1)
#define SOC_ISP_FD_DETECT_CONDITION_DIR_START       (2)
#define SOC_ISP_FD_DETECT_CONDITION_DIR_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_DETECT_START_X_UNION
 �ṹ˵��  : DETECT_START_X �Ĵ����ṹ���塣��ַƫ����:0x000c����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection area (starting X-coordinate) setting register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  STARTX   : 10; /* bit[0-9]  : Starting X-Coordinates: Valid range
                                                    When QVGA setting, 0��STARTX��160 (by 1 pixel)
                                                    When WQVGA+ setting, 0��STARTX��267 (by 1 pixel)
                                                    When VGA setting, 0��STARTX��480 (by 2 pixel, even values only)
                                                    When WVGA+ setting, 0��STARTX��694 (by 2 pixel, even values only) */
        unsigned int  reserved : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_FD_DETECT_START_X_UNION;
#endif
#define SOC_ISP_FD_DETECT_START_X_STARTX_START    (0)
#define SOC_ISP_FD_DETECT_START_X_STARTX_END      (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_DETECT_START_Y_UNION
 �ṹ˵��  : DETECT_START_Y �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection area (starting Y-coordinate) setting register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  STARTY   : 8;  /* bit[0-7] : Starting Y-Coordinates: Valid range
                                                   When QVGA setting, 0��STARTY��120 (by 1 pixel)
                                                   When WQVGA+ setting, 0��STARTY��120 (by 1 pixel)
                                                   When VGA setting, 0��STARTY��360 (by 2 pixel, even values only)
                                                   When WVGA+ setting, 0��STARTY��360 (by 2 pixel, even values only) */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_FD_DETECT_START_Y_UNION;
#endif
#define SOC_ISP_FD_DETECT_START_Y_STARTY_START    (0)
#define SOC_ISP_FD_DETECT_START_Y_STARTY_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_DETECT_SIZE_X_UNION
 �ṹ˵��  : DETECT_SIZE_X �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection area(X-direction size) setting register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SIZEX    : 10; /* bit[0-9]  : X-Direction Size (QVGA/WQVGA+ setting��by 1 pixel,
                                                    VGA/WVGA+ setting��by 2 pixel) */
        unsigned int  reserved : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_FD_DETECT_SIZE_X_UNION;
#endif
#define SOC_ISP_FD_DETECT_SIZE_X_SIZEX_START     (0)
#define SOC_ISP_FD_DETECT_SIZE_X_SIZEX_END       (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_DETECT_SIZE_Y_UNION
 �ṹ˵��  : DETECT_SIZE_Y �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection area(Y-direction size) setting register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SIZEY    : 9;  /* bit[0-8] : Y-Direction Size (QVGA/QVGA+ setting��by 1 pixel,
                                                   VGA/WVGA+ setting��by 2 pixel) */
        unsigned int  reserved : 23; /* bit[9-31]:  */
    } reg;
} SOC_ISP_FD_DETECT_SIZE_Y_UNION;
#endif
#define SOC_ISP_FD_DETECT_SIZE_Y_SIZEY_START     (0)
#define SOC_ISP_FD_DETECT_SIZE_Y_SIZEY_END       (8)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_THRESHOLD_UNION
 �ṹ˵��  : THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x001c����ֵ:0x00000005�����:32
 �Ĵ���˵��: threshold setting register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DHIT     : 4;  /* bit[0-3] : Threshold : Valid range - 0x0��0x9. */
        unsigned int  reserved : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_FD_THRESHOLD_UNION;
#endif
#define SOC_ISP_FD_THRESHOLD_DHIT_START      (0)
#define SOC_ISP_FD_THRESHOLD_DHIT_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_BASE_ADDR_UNION
 �ṹ˵��  : BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: non raster base address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 12; /* bit[0-11] :  */
        unsigned int  base_address : 20; /* bit[12-31]: Non-raster R/W address base (aligned on 4K).
                                                        This offset should be used for FPGA only. 
                                                        It cannot be updated during frame processing
                                                        => no HW protection implemented */
    } reg;
} SOC_ISP_FD_BASE_ADDR_UNION;
#endif
#define SOC_ISP_FD_BASE_ADDR_base_address_START  (12)
#define SOC_ISP_FD_BASE_ADDR_base_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_VERSION_UNION
 �ṹ˵��  : VERSION �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000302�����:32
 �Ĵ���˵��: version register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VER      : 13; /* bit[0-12] : Version information */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_FD_VERSION_UNION;
#endif
#define SOC_ISP_FD_VERSION_VER_START       (0)
#define SOC_ISP_FD_VERSION_VER_END         (12)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_RESULT_X_UNION
 �ṹ˵��  : RESULT_X �Ĵ����ṹ���塣��ַƫ����:0x0400+(result_range)*16����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection result (X-coordinate register[1-35]
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CENTERX  : 10; /* bit[0-9]  : CENTERX[9:0]��Detection Result Centre X-Coordinates: Valid range
                                                    When QVGA setting, 0x9(9)��0x136(310)
                                                    When WQVGA+ setting, 0x9(9)��0x1A2(418)
                                                    When VGA setting, 0x9(9)��0x276(630)
                                                    When WVGA+ setting, 0x9(9)��0x34C(844) */
        unsigned int  reserved : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_FD_RESULT_X_UNION;
#endif
#define SOC_ISP_FD_RESULT_X_CENTERX_START   (0)
#define SOC_ISP_FD_RESULT_X_CENTERX_END     (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_RESULT_Y_UNION
 �ṹ˵��  : RESULT_Y �Ĵ����ṹ���塣��ַƫ����:0x0404+(result_range)*16����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection result (Y-coordinate) register[1-35]
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CENTERY  : 9;  /* bit[0-8] : Detection Result Center Y-Coordinates : Valid range
                                                   When QVGA setting, 0x9(9)��0x0E6(230)
                                                   When WQVGA�� setting, 0x9(9)��0x0E6(230)
                                                   When VGA setting, 0x9(9)��0x1D6(470)
                                                   When WVGA�� setting, 0x9(9)��0x1D6(470) */
        unsigned int  reserved : 23; /* bit[9-31]:  */
    } reg;
} SOC_ISP_FD_RESULT_Y_UNION;
#endif
#define SOC_ISP_FD_RESULT_Y_CENTERY_START   (0)
#define SOC_ISP_FD_RESULT_Y_CENTERY_END     (8)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_RESULT_LS_UNION
 �ṹ˵��  : RESULT_LS �Ĵ����ṹ���塣��ַƫ����:0x0408+(result_range)*16����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection result (confidence level/size) register[1-35]
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SIZE     : 9;  /* bit[0-8]  : Detection Result Face Size : Valid range
                                                    When QVGA setting, 0x14(20)��0x0CF(207)
                                                    When WQVGA�� setting, 0x14(20)��0x0CF(207)
                                                    When VGA setting, 0x14(20)��0x19E(414)
                                                    When WVGA�� setting, 0x14(20)��0x19E(414) */
        unsigned int  CONF     : 4;  /* bit[9-12] : Confidence Level : Valid range 0x0(Low)��0x9(High) */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_FD_RESULT_LS_UNION;
#endif
#define SOC_ISP_FD_RESULT_LS_SIZE_START      (0)
#define SOC_ISP_FD_RESULT_LS_SIZE_END        (8)
#define SOC_ISP_FD_RESULT_LS_CONF_START      (9)
#define SOC_ISP_FD_RESULT_LS_CONF_END        (12)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FD_RESULT_ANGLE_UNION
 �ṹ˵��  : RESULT_ANGLE �Ĵ����ṹ���塣��ַƫ����:0x040c+(result_range)*16����ֵ:0x00000000�����:32
 �Ĵ���˵��: detection result (angle) register[1-35]
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ANGLE    : 9;  /* bit[0-8]  : Detection result face angle : Valid values
                                                    When DIR=0, 0x0(0��)��0x01E(30��) and 0x14A(330��)��0x167(359��)
                                                    When DIR=1, 0x03C(60��)��0x078(120��)
                                                    When DIR=2, 0x0F0(240��)��0x12C(300��)
                                                    When DIR=3, 0x096(150��)��0x0D2(210��)
                                                    When DIR=4, 0x0(0��)��0x078(120��) and 0x0F0(240��)��0x167(359��)
                                                    When DIR=5, 0x0(0��)��0x0D2(210��) and 0x14A(330��)��0x167(359��)
                                                    When DIR=6, 0x0(0��)��0x01E(30��) and 0x096(150��)��0x167(359��)
                                                    When DIR=7, 0x03C(60��)��0x12C(300��)
                                                    When DIR=8, 0x0(0��)��0x167(359��) */
        unsigned int  POSE     : 3;  /* bit[9-11] : Detection result face rotation : Valid values
                                                    0x1 (Front)
                                                    0x2 (Right Diagonal)
                                                    0x3 (Right)
                                                    0x4 (Left Diagonal)
                                                    0x5 (Left) */
        unsigned int  reserved : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_FD_RESULT_ANGLE_UNION;
#endif
#define SOC_ISP_FD_RESULT_ANGLE_ANGLE_START     (0)
#define SOC_ISP_FD_RESULT_ANGLE_ANGLE_END       (8)
#define SOC_ISP_FD_RESULT_ANGLE_POSE_START      (9)
#define SOC_ISP_FD_RESULT_ANGLE_POSE_END        (11)






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

#endif /* end of soc_isp_fd_interface.h */
