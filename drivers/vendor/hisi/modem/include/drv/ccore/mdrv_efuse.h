#ifndef __MDRV_CCORE_EFUSE_H__
#define __MDRV_CCORE_EFUSE_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_efuse_common.h"


    /************************************************************************
     *  �� �� ��  : mdrv_efuse_read_huk
     *  ��������  :  ��ȡ�HUKֵ��
     *  �������  :  pbuf   buffer��ַ
     *               len    buffer�ĳ���(�ֽ���)
     *
     *  �������  : ��
     *  �� �� ֵ  :  0           �����ɹ���
     *                           ����    ����ʧ�ܡ�
     *
     *************************************************************************/
     int mdrv_efuse_read_huk(unsigned char *pbuf, unsigned int len);

#ifdef __cplusplus
}
#endif
#endif

