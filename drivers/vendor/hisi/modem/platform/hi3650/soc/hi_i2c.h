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

#ifndef __HI_I2C_H__
#define __HI_I2C_H__

/*
 * Project: hi
 * Module : i2c
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    i2c �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_I2C_CTRL_OFFSET                                (0x0) /* I2C���ƼĴ����� */
#define    HI_I2C_COM_OFFSET                                 (0x4) /* I2C����Ĵ����� */
#define    HI_I2C_ICR_OFFSET                                 (0x8) /* I2C�ж�����Ĵ����� */
#define    HI_I2C_SR_OFFSET                                  (0xC) /* I2C״̬�Ĵ����� */
#define    HI_I2C_SCL_H_OFFSET                               (0x10) /* I2C SCL�ߵ�ƽ�������Ĵ����� */
#define    HI_I2C_SCL_L_OFFSET                               (0x14) /* I2C SCL�͵�ƽ�������Ĵ����� */
#define    HI_I2C_TXR_OFFSET                                 (0x18) /* I2C�������ݼĴ����� */
#define    HI_I2C_RXR_OFFSET                                 (0x1C) /* I2C�������ݼĴ����� */

/********************************************************************************/
/*    i2c �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    int_done_mask              : 1; /* [0..0] ���ߴ�������ж����Ρ�0�������жϣ�1���������жϡ� */
        unsigned int    int_arb_loss_mask          : 1; /* [1..1] �����ٲ�ʧ���ж����Ρ�0�������жϣ�1���������жϡ� */
        unsigned int    int_ack_err_mask           : 1; /* [2..2] �ӻ�ACK�����ж����Ρ�0�������жϣ�1���������жϡ� */
        unsigned int    int_rx_mask                : 1; /* [3..3] ���������ж����Ρ�0�������жϣ�1���������жϡ� */
        unsigned int    int_tx_mask                : 1; /* [4..4] ���������ж����Ρ�0�������жϣ�1���������жϡ� */
        unsigned int    int_stop_mask              : 1; /* [5..5] ����ֹͣ�������ͽ����ж����Ρ�0�������жϣ�1���������жϡ� */
        unsigned int    int_start_mask             : 1; /* [6..6] ������ʼ�������ͽ����ж����Ρ�0�������жϣ�1���������жϡ� */
        unsigned int    int_mask                   : 1; /* [7..7] I2C�ж������Ρ�0�����������жϣ�1�������������жϡ� */
        unsigned int    i2c_en                     : 1; /* [8..8] I2Cʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved                   : 23; /* [31..9] ������ */
    } bits;
    unsigned int    u32;
}HI_I2C_CTRL_T;    /* I2C���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    op_stop                    : 1; /* [0..0] ����ֹͣ����������0������������1��������Ч�� */
        unsigned int    op_we                      : 1; /* [1..1] ����д������0������������1��������Ч�� */
        unsigned int    op_rd                      : 1; /* [2..2] ������������0������������1��������Ч�� */
        unsigned int    op_start                   : 1; /* [3..3] ������ʼ����������0������������1��������Ч�� */
        unsigned int    op_ack                     : 1; /* [4..4] ������Ϊ�������Ƿ���ACK��0������ACK��1��������ACK�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_I2C_COM_T;    /* I2C����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    clr_int_done               : 1; /* [0..0] ���ߴ�������жϱ�־�����0��������жϱ�־��1������жϱ�־�� */
        unsigned int    clr_int_arb_loss           : 1; /* [1..1] �����ٲ�ʧ���жϱ�־�����0��������жϱ�־��1������жϱ�־�� */
        unsigned int    clr_int_ack_err            : 1; /* [2..2] �ӻ�ACK�����жϱ�־�����0��������жϱ�־��1������жϱ�־�� */
        unsigned int    clr_int_rx                 : 1; /* [3..3] ���������жϱ�־�����0��������жϱ�־��1������жϱ�־�� */
        unsigned int    clr_int_tx                 : 1; /* [4..4] ���������жϱ�־�����0��������жϱ�־��1������жϱ�־�� */
        unsigned int    clr_int_stop               : 1; /* [5..5] ����ֹͣ�������ͽ����жϱ�־�����0��������жϱ�־��1������жϱ�־�� */
        unsigned int    clr_int_start              : 1; /* [6..6] ������ʼ�������ͽ����жϱ�־�����0��������жϱ�־��1������жϱ�־�� */
        unsigned int    reserved                   : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_I2C_ICR_T;    /* I2C�ж�����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    int_done                   : 1; /* [0..0] ���ߴ�������жϱ�־��0�����жϱ�־������1���жϱ�־������ */
        unsigned int    int_arb_loss               : 1; /* [1..1] �����ٲ�ʧ���жϱ�־��0�����жϱ�־������1���жϱ�־������ */
        unsigned int    int_ack_err                : 1; /* [2..2] �ӻ�ACK�����жϱ�־��0�����жϱ�־������1���жϱ�־������ */
        unsigned int    int_rx                     : 1; /* [3..3] ���������жϱ�־��0�����жϱ�־������1���жϱ�־������ */
        unsigned int    int_tx                     : 1; /* [4..4] ���������жϱ�־��0�����жϱ�־������1���жϱ�־������ */
        unsigned int    int_stop                   : 1; /* [5..5] ����ֹͣ�������ͽ����жϱ�־��0�����жϱ�־������1���жϱ�־������ */
        unsigned int    int_start                  : 1; /* [6..6] ������ʼ�������ͽ����жϱ�־��0�����жϱ�־������1���жϱ�־������ */
        unsigned int    bus_busy                   : 1; /* [7..7] ����æ��0�����У�1��æ�� */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_I2C_SR_T;    /* I2C״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    scl_h                      : 16; /* [15..0] scl_h*2��SCL�ߵ�ƽ�������� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_I2C_SCL_H_T;    /* I2C SCL�ߵ�ƽ�������Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    scl_l                      : 16; /* [15..0] scl_l*2��SCL�͵�ƽ�������� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_I2C_SCL_L_T;    /* I2C SCL�͵�ƽ�������Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    i2c_txr                    : 8; /* [7..0] �����������ݡ����ͽ�����I2Cģ�鲻���޸�I2C_TXR���ݡ� */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_I2C_TXR_T;    /* I2C�������ݼĴ����� */

typedef union
{
    struct
    {
        unsigned int    i2c_rxr                    : 8; /* [7..0] �����������ݡ�I2C_RXR������I2C_SR bit[3]=1ʱ��������Ч��ͬʱ���ݽ����ֵ���һ��������֮ǰ�� */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_I2C_RXR_T;    /* I2C�������ݼĴ����� */


/********************************************************************************/
/*    i2c ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_i2c_ctrl_int_done_mask,int_done_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_arb_loss_mask,int_arb_loss_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_ack_err_mask,int_ack_err_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_rx_mask,int_rx_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_tx_mask,int_tx_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_stop_mask,int_stop_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_start_mask,int_start_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_mask,int_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_i2c_en,i2c_en,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_reserved,reserved,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_com_op_stop,op_stop,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_we,op_we,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_rd,op_rd,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_start,op_start,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_ack,op_ack,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_reserved,reserved,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_done,clr_int_done,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_arb_loss,clr_int_arb_loss,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_ack_err,clr_int_ack_err,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_rx,clr_int_rx,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_tx,clr_int_tx,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_stop,clr_int_stop,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_start,clr_int_start,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_reserved,reserved,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_done,int_done,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_arb_loss,int_arb_loss,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_ack_err,int_ack_err,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_rx,int_rx,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_tx,int_tx,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_stop,int_stop,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_start,int_start,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_bus_busy,bus_busy,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_reserved,reserved,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_scl_h_scl_h,scl_h,HI_I2C_SCL_H_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_H_OFFSET)
HI_SET_GET(hi_i2c_scl_h_reserved,reserved,HI_I2C_SCL_H_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_H_OFFSET)
HI_SET_GET(hi_i2c_scl_l_scl_l,scl_l,HI_I2C_SCL_L_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_L_OFFSET)
HI_SET_GET(hi_i2c_scl_l_reserved,reserved,HI_I2C_SCL_L_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_L_OFFSET)
HI_SET_GET(hi_i2c_txr_i2c_txr,i2c_txr,HI_I2C_TXR_T,HI_I2C_BASE_ADDR, HI_I2C_TXR_OFFSET)
HI_SET_GET(hi_i2c_txr_reserved,reserved,HI_I2C_TXR_T,HI_I2C_BASE_ADDR, HI_I2C_TXR_OFFSET)
HI_SET_GET(hi_i2c_rxr_i2c_rxr,i2c_rxr,HI_I2C_RXR_T,HI_I2C_BASE_ADDR, HI_I2C_RXR_OFFSET)
HI_SET_GET(hi_i2c_rxr_reserved,reserved,HI_I2C_RXR_T,HI_I2C_BASE_ADDR, HI_I2C_RXR_OFFSET)

#endif // __HI_I2C_H__

