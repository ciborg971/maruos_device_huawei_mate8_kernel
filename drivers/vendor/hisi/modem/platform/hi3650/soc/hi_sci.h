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

#ifndef __HI_SCI_H__
#define __HI_SCI_H__

/*
 * Project: hi
 * Module : SCI
 */

/********************************************************************************/
/*    SCI �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_SCI_SCI_DATA_OFFSET                            (0x0) /* SCI���ݼĴ��������ڷ��ͻ�����ַ�����SCI����������ݽӿڡ����ֻ��������SCI_CR1[mode]Ϊ1֮�󣬲ſɶԴ˼Ĵ�������д��������SCI_CR1[mode]Ϊ0ʱ���������ԶԸüĴ�����д���������������á� */
#define    HI_SCI_SCI_CR0_OFFSET                             (0x4) /* SCI���ƼĴ��������ڿ���ʱ��ֹͣ����żУ�顢�������֡�����λ����ȹ��ܡ� */
#define    HI_SCI_SCI_CR1_OFFSET                             (0x8) /* SCI���ƼĴ��������ڿ���ͬ��/�첽������ģʽ�����ͽ���ģʽ���鳬ʱ��ATR��ʱ�ȹ��ܡ� */
#define    HI_SCI_SCI_CR2_OFFSET                             (0xC) /* SCI���ƼĴ�����д�üĴ�������Ӧλ�ᴥ��SCI�Կ��ļ���ͷŻ���λ��������SCI�������ͷſ���״̬ʱ���ԸüĴ�����д�����������ԡ�������ʱ�򣬶�SCI_CR2[finish]д1��ʹSCI�������Ϳ��ͷ����С�(CH)(CL)����ԸüĴ�����д���������ں��ʵĿ������׶ν��С������ʵ�д������������Ԥ�ڵĺ����(CL)ֻ�е����ܿ�������֮��������ܶԿ�������λ������ */
#define    HI_SCI_SCI_CLKICC_OFFSET                          (0x10) /* ���ܿ�ʱ��Ƶ�ʼĴ������üĴ����������ⲿ���ܿ�ʱ�ӵķ�Ƶ���ӡ����ܿ�ʱ��Ƶ�ʵļ��㹫ʽΪ��FSCI_CLK=(FREFCLK)/(clkicc+1)x2 �����У�FSCI_CLKΪʱ��Ƶ�ʣ�FREFCLKΪ�ο�ʱ��Ƶ�ʣ�clkiccΪSCI_CLKICC[clkicc]���õ�ֵ�� */
#define    HI_SCI_SCI_VALUE_OFFSET                           (0x14) /* ETU��SCI_BAUD�������Ĵ��������ڼ���ETU��������Ϊ5��255֮�������ֵ��ETU�ļ��㹫ʽΪ��Etu=(1+baud) x value��baudΪSCI_BAUD[baud]���õ�ֵ��valueΪSCI_VALUE[value]���õ�ֵ�� */
#define    HI_SCI_SCI_BAUD_OFFSET                            (0x18) /* ������ʱ�ӷ�Ƶֵ�Ĵ��������ڼ���ETU����������Ϊ0x1��0xFFFF֮�������ֵ����μ���SCI_VALUE����ETU�ļ��㹫ʽ�� */
#define    HI_SCI_SCI_TIDE_OFFSET                            (0x1C) /* ���ͽ���FIFO�������ֵ�Ĵ�����(NH)(NL)TXFIFO�е��ַ�ֻ���ڳɹ����ͺ�Żᱻ�Ƴ��� */
#define    HI_SCI_SCI_DMACR_OFFSET                           (0x20) /* DMA���ƼĴ��������ڿ���DMA���ͺͽ������ݡ� */
#define    HI_SCI_SCI_STABLE_OFFSET                          (0x24) /* ���ܿ������ȶ�ʱ��Ĵ����������ܿ�����ź�SCI_DETECT�ź���Ч����Ҫ�ȶ�����SCI_STABLE�Ĵ���ֵ��Ӧ�Ĺ̶���ʱ��TSTABLE������TSTABLEʱ�䣨��λΪ�룩�󴥷�cardinintr�жϣ��������ܿ�����ȷ���롣 */
#define    HI_SCI_SCI_ATIME_OFFSET                           (0x28) /* ���ܿ�����ʱ��Ĵ������üĴ�����[atime]λ����ָʾ����λ�ͼ����3���׶εĳ���ʱ�䡣(NH)(NL)Ϊ���㿨��λ��Ҫ��SCI_ATIME[atime]����Ϊ40000���ӿڿ�ʱ�ӣ�SCI_CLK�����ڡ�(NL)�ò���Ҳ�����������ܿ��Ե�Դ�ȶ���Ҫ�� */
#define    HI_SCI_SCI_DTIME_OFFSET                           (0x2C) /* ���ܿ��ͷ�ʱ��Ĵ������üĴ�����{dtime]λ����ָʾ���ͷŵ�3���׶εĳ���ʱ�䣬��λΪSCI�ο�ʱ�����ڡ� */
#define    HI_SCI_SCI_ATRSTIME_OFFSET                        (0x30) /* �ȴ���ʼ����ATRʱ����ֵ�Ĵ������������ܿ�ʱ�Ӷ����˴����ܿ���λ��������ʼ����ATR��һ���ַ���ʱ����ֵ��ATR�ȴ���ʼ���ճ�ʱ��ᴥ��atrstoutintr�жϣ���SCI_RIS[atrstoutim]��1��(NH)SCI_ATRSTIME[atrstime]���������ʼ��Ϊ40000��SCI_CLK�ӿڿ�ʱ�����ڡ� */
#define    HI_SCI_SCI_ATRDTIME_OFFSET                        (0x34) /* ����ATRʱ����ֵ�Ĵ�����SCI�ڽ���ATR�����У��ӵ�һ��ATR�ַ���ʼ���յ����һ��ATR�ַ����ս�������������üĴ����������ʱ�䣨��ETUΪ��λ�����ᴥ���жϣ���SCI_RIS[atrdtoutris]��1��(NH)(NL)��ʹ�øüĴ���֮ǰ������������SCI_CR1[atrden]Ϊ1����ʹ�ܳ�ʱ�������ơ�(NL)����Э�飬�üĴ�����������Ϊ19200��ETU����0x4B00�� */
#define    HI_SCI_SCI_STOPTIME_OFFSET                        (0x38) /* ʱ��ֹͣʱ��Ĵ�����������ʱ��ֹͣʱ������SCI_STOPTIME�������ʱ�䣨��λΪSCI�ӿڿ�ʱ��SCI_CLK���ڣ������ܿ�ʱ����Ч���������жϣ���SCI_RIS[clkstpris]��1��(NH)����Э�飬��ֵ��СΪ1860��SCIʱ�����ڣ���SCI_STOPTIME[stoptime]��Ҫ����Ϊ0x744�� */
#define    HI_SCI_SCI_STARTTIME_OFFSET                       (0x3C) /* ���ܿ�ʱ�ӻָ�ʱ��Ĵ�����������ʱ�ӻָ�ʱ������SCI_STARTTIME�������ʱ�䣨��λΪSCI�ӿڿ�ʱ��SCI_CLK���ڣ���SCI�����ܿ����ܽ������ݴ��䣬�������жϣ���SCI_RIS[clkactris]��1��(NH)����Э�飬��ֵ��СӦΪ700��SCIʱ�����ڣ���SCI_STARTTIME[starttimr]������Ҫ����Ϊ0x2BC�� */
#define    HI_SCI_SCI_RETRY_OFFSET                           (0x40) /* ���ͽ������Դ����Ĵ������üĴ��������˷��ͻ���������ش��Ĵ�������������Ϊ��(I)��SCI_CR0[txnak]ʹ��ʱ��SCI�����շ��Ƿ��ʶУ�����SCI_RETRY[rxretry]�������У���������´����������������������txerrintr�жϣ���SCI_RIS[txerrris]��1��(I)��SCI_CR0[rxnak]ʹ��ʱ��SCI����յ��������Ƿ����У�����SCI_RETRY[txretry]�������У���������´��������������������ô�����Ȼ���մ��󣬽�SCI_DATA[parity]��1�� */
#define    HI_SCI_SCI_CHTIMELS_OFFSET                        (0x44) /* �����ַ������ʱ��ֵ��16λ�Ĵ�����SCI_CHTIME�Ĵ�������ӿ����յ������������ַ�����ʼ��֮����������ʱ��������ETUΪ��λ����������յ����ַ������ʱ�ᴥ��chtoutintr�жϣ���SCI_RIS[chtoutris]��1��(CH)SCI_CHTIME�Ĵ������ɵ�16λ�Ĵ���SCI_CHTIMELS�͸�16λ�Ĵ���SCI_CHTIMEMS��ɡ������дSCI_CHTIMEMSʱ��SCI_CHTIME����������Ч����дSCI_CHTIMELSʱSCI_CHTIME�Ż���Ч���������SCI_CHTIME���������ø�16λ�������õ�16λ�� */
#define    HI_SCI_SCI_CHTIMEMS_OFFSET                        (0x48) /* �����ַ������ʱ��ֵ��16λ�Ĵ����� */
#define    HI_SCI_SCI_BLKTIMELS_OFFSET                       (0x4C) /* ���տ�����ʱ��ֵ��16λ�Ĵ�����SCI_BLKTIME������տ���������ʱ��������ETUΪ��λ������ʱ��������ʼʱ�������һ�����͵������ַ�����ʼ�أ������ǵ�һ���ӿ����صĽ����ַ�ʱ�̡������ʱ�ᴥ��blktoutintr�жϣ���SCI_RIS[blkoutim]��1��(CH)SCI_BLKTIME�Ĵ������ɵ�16λ�Ĵ���SCI_BLKTIMELS�͸�16λ�Ĵ���SCI_BLKTIMEMS��ɡ������дSCI_BLKTIMEMSʱ��SCI_BLKTIME����������Ч��дSCI_BLKTIMELSʱSCI_BLKTIME�Ż���Ч���������SCI_BLKTIME���������ø�16λ�������õ�16λ�� */
#define    HI_SCI_SCI_BLKTIMEMS_OFFSET                       (0x50) /* ���տ�����ʱ��ֵ��16λ�Ĵ����� */
#define    HI_SCI_SCI_CHGUARD_OFFSET                         (0x54) /* �ַ��䱣��ʱ�����Ĵ������üĴ������嵱SCI�����������ַ�ʱ�����������ַ���ʼ��֮����С����Ķ��Ᵽ��ʱ�䣨��ETUΪ��λ��������Э���ж����ȫ�ֽӿ��ֽ�TC1����ATR�����еõ��������� */
#define    HI_SCI_SCI_BLKGUARD_OFFSET                        (0x58) /* ��䱣��ʱ�����Ĵ����������������ַ��Ĵ��䷽���෴ʱ������ʼ��֮���ʱ����ΪSCI_BLKGUARD�� */
#define    HI_SCI_SCI_RXTIME_OFFSET                          (0x5C) /* ����FIFO����ʱ��ֵ�Ĵ�����������FIFO�����ַ��ҳ���SCI_RXTIME�������ʱ����Ȼû�б��������򴥷����ն���ʱ�ж�scirtout��SCI_RIS[rtoutris]����1��(CH)����ʹ�ý���FIFO����ʱ�жϹ���ʱ��SCI_RXTIME[rxtime]����Ϊ0x0000�� */
#define    HI_SCI_SCI_FIFOSTATUS_OFFSET                      (0x60) /* FIFO״̬�Ĵ����� */
#define    HI_SCI_SCI_TXCOUNT_OFFSET                         (0x64) /* ����FIFO���ݸ����Ĵ�����(NH)(NL)���üĴ������ط���FIFO���ַ��ĸ��������������ڷ��͵��ַ�����(NL)�������ַ��������ִ���T0Э�飩�������ش����������������ֵ����SCI_RETRY�ж��壩���ᴥ��txerr�жϣ���SCI_RIS[txerrris]��1����ʱ�ڽ�����һ�δ���֮ǰ������FIFO���뱻��գ�д�üĴ������� */
#define    HI_SCI_SCI_RXCOUNT_OFFSET                         (0x68) /* ����FIFO���ݸ����Ĵ����� */
#define    HI_SCI_SCI_IMSC_OFFSET                            (0x6C) /* �ж����μĴ�����BitֵΪ0��ʾ���Σ�Ϊ1��ʾ�����Ρ� */
#define    HI_SCI_SCI_RIS_OFFSET                             (0x70) /* ԭʼ�жϼĴ������üĴ��������ж�����֮ǰ��ԭʼ�жϡ�BitֵΪ0��ʾ���жϣ�Ϊ1��ʾ���жϡ� */
#define    HI_SCI_SCI_MIS_OFFSET                             (0x74) /* ���κ��жϼĴ������üĴ����ǳ�ʼ�жϾ������κ�Ľ����BitֵΪ0��ʾ���жϣ�Ϊ1��ʾ���жϡ� */
#define    HI_SCI_SCI_ICR_OFFSET                             (0x78) /* �ж�����Ĵ�����BitֵΪ0��ʾ������жϣ�Ϊ1��ʾ����жϡ� */
#define    HI_SCI_SCI_SYNCACT_OFFSET                         (0x7C) /* ͬ��ģʽ����Ĵ������üĴ�������ͬ��ģʽ������ʹ�ܡ�ʱ��ʹ�ܡ���λ�͵�Դ���Ƶȣ����ṩ״̬�Ĵ�������Ӧ��״̬λ�ڼ���ͷš��ȸ�λ�������Զ����¡� */
#define    HI_SCI_SCI_SYNCTX_OFFSET                          (0x80) /* ͬ��ģʽ����ʱ�Ӻ��������Ĵ������üĴ������ڿ���ͬ��ģʽ�·���ʱ�Ӻ����ݡ� */
#define    HI_SCI_SCI_SYNCRX_OFFSET                          (0x84) /* ͬ��ģʽ����ʱ�Ӻ��������Ĵ������üĴ������ڿ���ͬ��ģʽ�½���ʱ�Ӻ����ݡ� */

#endif // __HI_SCI_H__

