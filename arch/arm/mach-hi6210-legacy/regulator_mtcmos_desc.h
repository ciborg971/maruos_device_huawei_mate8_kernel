

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


#ifndef __REGULATOR_MTCMOS_DESC_H__
#define __REGULATOR_MTCMOS_DESC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/


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


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/

struct regulator_desc regulators[] = {
    /*MTCMOS Begin*/
    [MTCMOS1_ID] = {
        .name = MTCMOS1_NAME,
        .id = MTCMOS1_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS1_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS2_ID] = {
        .name = MTCMOS2_NAME,
        .id = MTCMOS2_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS2_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS3_ID] = {
        .name = MTCMOS3_NAME,
        .id = MTCMOS3_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS3_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS4_ID] = {
        .name = MTCMOS4_NAME,
        .id = MTCMOS4_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS4_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS5_ID] = {
        .name = MTCMOS5_NAME,
        .id = MTCMOS5_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS5_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS6_ID] = {
        .name = MTCMOS6_NAME,
        .id = MTCMOS6_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS6_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS7_ID] = {
        .name = MTCMOS7_NAME,
        .id = MTCMOS7_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS7_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS8_ID] = {
        .name = MTCMOS8_NAME,
        .id = MTCMOS8_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS8_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS9_ID] = {
        .name = MTCMOS9_NAME,
        .id = MTCMOS9_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS9_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS10_ID] = {
        .name = MTCMOS10_NAME,
        .id = MTCMOS10_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS10_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS11_ID] = {
        .name = MTCMOS11_NAME,
        .id = MTCMOS11_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS11_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS12_ID] = {
        .name = MTCMOS12_NAME,
        .id = MTCMOS12_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS12_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS13_ID] = {
        .name = MTCMOS13_NAME,
        .id = MTCMOS13_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS13_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS14_ID] = {
        .name = MTCMOS14_NAME,
        .id = MTCMOS14_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS14_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS15_ID] = {
        .name = MTCMOS15_NAME,
        .id = MTCMOS15_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS15_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS16_ID] = {
        .name = MTCMOS16_NAME,
        .id = MTCMOS16_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS16_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS17_ID] = {
        .name = MTCMOS17_NAME,
        .id = MTCMOS17_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS17_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS18_ID] = {
        .name = MTCMOS18_NAME,
        .id = MTCMOS18_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS18_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS19_ID] = {
        .name = MTCMOS19_NAME,
        .id = MTCMOS19_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS19_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS20_ID] = {
        .name = MTCMOS20_NAME,
        .id = MTCMOS20_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS20_TYPE,
        .owner = THIS_MODULE,
    },
}


/*****************************************************************************
  10 ��������
*****************************************************************************/












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of regulator_mtcmos_desc.h */
