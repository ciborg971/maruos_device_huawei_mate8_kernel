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



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ScCommCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_SC_CONTEXT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


#if (VOS_WIN32 == VOS_OS_VER)
static SC_CONTEXT_STRU                  g_stScCtx = {
    /* SC_COMM_GLOBAL_VAR */
    {
        {
            ".\\yaffs0\\SC\\Pers\\CKFile.bin",
            ".\\yaffs0\\SC\\Pers\\DKFile.bin",
            ".\\yaffs0\\SC\\Pers\\AKFile.bin",
            ".\\yaffs0\\SC\\Pers\\PIFile.bin",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I0.bin",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I1.bin"
        },
        {
            ".\\yaffs0\\SC\\Pers\\CKSign.hash",
            ".\\yaffs0\\SC\\Pers\\DKSign.hash",
            ".\\yaffs0\\SC\\Pers\\AKSign.hash",
            ".\\yaffs0\\SC\\Pers\\PISign.hash",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I0.hash",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I1.hash"
        }
    },
    /* SC_FAC_GLOBAL_VAR */
    {
        SC_AUTH_STATUS_UNDO,
        "",
        VOS_FALSE,
        ""
    },
    /* SC_APSEC_GLOBAL_VAR */
    {
        0,
        {0, 0},
        0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        SC_SECURITY_FILE_STATE_IDEL,
        {
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR}
        },
        ".\\SecureDataA.bin",
        ".\\SecureDataC.bin"
    }
};
#else
static SC_CONTEXT_STRU                  g_stScCtx = {
    /* SC_COMM_GLOBAL_VAR */
    {
        {
            "/mnvm2:0/SC/Pers/CKFile.bin",
            "/mnvm2:0/SC/Pers/DKFile.bin",
            "/mnvm2:0/SC/Pers/AKFile.bin",
            "/mnvm2:0/SC/Pers/PIFile.bin",
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I2.bin",
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.bin",
#endif
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
#endif
        },
        {
            "/mnvm2:0/SC/Pers/CKSign.hash",
            "/mnvm2:0/SC/Pers/DKSign.hash",
            "/mnvm2:0/SC/Pers/AKSign.hash",
            "/mnvm2:0/SC/Pers/PISign.hash",
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I2.hash",
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.hash",
#endif
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
#endif
        }
    },
    /* SC_FAC_GLOBAL_VAR */
    {
        SC_AUTH_STATUS_UNDO,
        "",
        VOS_FALSE,
        ""
    },
    /* SC_APSEC_GLOBAL_VAR */
    {
        0,
        {0, 0},
        0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        SC_SECURITY_FILE_STATE_IDEL,
        {
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR}
        },
        "/mnvm2:0/SC/Apsec/SecureDataA.bin",
        "/mnvm2:0/SC/Apsec/SecureDataC.bin"
    }
};

#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


SC_CONTEXT_STRU* SC_CTX_GetScCtxAddr(VOS_VOID)
{
    return &(g_stScCtx);
}


SC_COMM_GLOBAL_STRU*  SC_CTX_GetCommGlobalVarAddr( VOS_VOID )
{
    return &g_stScCtx.stScCommGlobalVar;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

