/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __SOC_ONCHIP_H__
#define __SOC_ONCHIP_H__

#include "bsp_memmap.h"

/*--------------------------------------------------------------*
 * �궨��                                                    *
 *--------------------------------------------------------------*/

#define M3_TCM_ADDR                    (0x10000000)	 /* TCM��ʼ��ַ */
#define M3_TCM_SIZE                    (64*1024)     /* 64K */

#define SRAM_ADDR                      (0x4FE00000)     /* AXI Memory��ʼ��ַ */
#define SRAM_SIZE                      (128*1024)       /* AXI Memory��С */

/* ��������������TCM����,BootLoader��������Ҫ������ */
#define M3_TCM_SHARE_DATA_SIZE sizeof(tOcrShareData)
#define M3_TCM_SHARE_DATA_ADDR (SRAM_ADDR + SRAM_SIZE - M3_TCM_SHARE_DATA_SIZE)

/* OnChipRom���й���־���Ծٱ�־����tOcrShareData�ṹ���� */
#define OCR_INITED_FLAG_ADDR    (SRAM_ADDR + SRAM_SIZE - 4)
#define OCR_AUTO_ENUM_FLAG_ADDR (SRAM_ADDR + SRAM_SIZE - 8)
#define OCR_INITED_FLAG_VALUE   (0x23456789)
#define OCR_UNINITED_FLAG_VALUE (0xA55A6789)


#define AUTO_ENUM_FLAG_VALUE    0x82822828

/* ֻ��OEM CA�в���OEM ID��HWID,��CA���� */
#define KEY_OEMID_INDEX        sizeof(KEY_STRUCT)
#define KEY_HWID_INDEX         (KEY_OEMID_INDEX+0x04)

#define BL_LEN_INDEX            (144 * 4)    /* bootload.bin�ļ�����(Byte)������bootload.bin�ļ��е�ƫ���ֽ��� */
#define ROOT_CA_INDEX           (BL_LEN_INDEX + 4)   /* ��CA��Image��λ�� */

#define ROOT_CA_LEN            260      /*CA֤��ĳ��� 260 Byte*/
#define OEM_CA_LEN             268      /*CA֤��ĳ��� 268 Byte*/
#define IDIO_LEN               128      /*ǩ���ĳ��� 128 Byte*/

#define MAX_N_LENGTH    32

#define SHA256_HASH_SIZE  8       /*HASHǩ��ռ��word��*/

#define MD5_HASH_SIZE   4       /* MD5ժҪ��ռ��word�� */

#ifndef __ASSEMBLY__
/*--------------------------------------------------------------*
 * ���ݽṹ                                                     *
 *--------------------------------------------------------------*/

/* ��Կ��ʽ */
typedef struct
{
    unsigned short eLen;    /* E������64bitsΪ��λ��ȡֵ��ΧΪ0~15��0��ʾ16 */
    unsigned short nLen;    /* N������32bitsΪ��λ��ȡֵ��ΧΪ0~31��0��ʾ32 */
    unsigned int   e[MAX_N_LENGTH];       /* ��e(��Կ) */
    unsigned int   n[MAX_N_LENGTH];       /* ģ�� */
}KEY_STRUCT;


/* ǩ��У�麯��ָ�� */
typedef int (*idioIdentifyPtr)(unsigned int dataAddr, unsigned int dataLen, KEY_STRUCT *pKey, unsigned int* pIdio);

/* ����Hashֵ����ָ�� */
typedef int (*SHA256HashPtr)(unsigned int dataAddr, unsigned int dataLen, unsigned int* hash);

/* ����RSA����ָ�� */
typedef int (*RSAPtr)(KEY_STRUCT *pKey, unsigned int* pIndata, unsigned int* pOutdata);

/* �������ݽṹ��,����AXI����,�������¼�Ԫ��(�������ǰ��) */
typedef struct tagOcrShareData
{
    int errNo;

    /* ������ָ�� */
    SHA256HashPtr   SHA256Hash;
    RSAPtr          RSA;
    idioIdentifyPtr idioIdentify;

    /* �������ݶ� */
    int    bSecEn;
    int    bRootCaInited;
    KEY_STRUCT *pRootKey;
    unsigned int  ulEnumFlag;
    unsigned int  ulOcrInitedFlag;
}tOcrShareData;
#endif /* __ASSEMBLY__ */

#endif
