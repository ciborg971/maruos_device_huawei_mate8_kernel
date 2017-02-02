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
#include  "CsdDebug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if( FEATURE_ON == FEATURE_CSD )

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
CSD_UL_STATUS_INFO_STRU                 g_stCsdStatusInfo = {0};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID CSD_ShowULStatus(VOS_VOID)
{
    vos_printf("CSD�յ��������ݵĸ���                             %d\n",g_stCsdStatusInfo.ulULRecvPktNum);
    vos_printf("CSD���л��������ݰ��ĸ���                         %d\n",g_stCsdStatusInfo.ulULSaveBuffPktNum);
    vos_printf("CSD�������ʧ�ܵĴ���                             %d\n",g_stCsdStatusInfo.ulULEnQueFail);
    vos_printf("CSD�������л��������                             %d\n",g_stCsdStatusInfo.ulULSendPktNum);
    vos_printf("CSD������������ʱ�Ӷ����л�ȡ����ָ�����Ŀ       %d\n",g_stCsdStatusInfo.ulULQueNullNum);
    vos_printf("CSD������������sk_bufferͷת����IMMͷʧ�ܵİ���Ŀ %d\n",g_stCsdStatusInfo.ulULZcToImmFailNum);
    vos_printf("CSD�����������ݲ���DICCͨ��ʧ�ܵİ���Ŀ           %d\n",g_stCsdStatusInfo.ulULInsertDiccFailNum);
    vos_printf("\r\n");

    return;
}

VOS_VOID CSD_ShowDLStatus(VOS_VOID)
{
    vos_printf("CSD�յ��������ݵĸ���                             %d\n",g_stCsdStatusInfo.ulDLRecvPktNum);
    vos_printf("CSD�������л��������                             %d\n",g_stCsdStatusInfo.ulDLSendPktNum);
    vos_printf("CSD���з���ʧ�ܰ�����Ŀ                           %d\n",g_stCsdStatusInfo.ulDLSendFailNum);
    vos_printf("\r\n");

    return;
}

VOS_VOID CSD_Help(VOS_VOID)
{
    vos_printf("********************CSD�����Ϣ************************\n");
    vos_printf("CSD_ShowULStatus                         ��ʾCSD����ͳ����Ϣ\n");
    vos_printf("CSD_ShowDLStatus                         ��ʾCSD����ͳ����Ϣ\n");

    return;
}









#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
