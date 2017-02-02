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

#ifndef __HI_CIPHER_H__
#define __HI_CIPHER_H__

/*
 * Project: hi
 * Module : cipher
 */

#if 0
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif
#endif
/********************************************************************************/
/*    cipher �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_CIPHER_CTRL_OFFSET                             (0x0) /* CIPHERģ����ƼĴ��� */
#define    HI_CIPHER_PRI_OFFSET                              (0x4) /* CIPHER���ȼ����ƼĴ����� */
#define    HI_TOTAL_BD_NUM_OFFSET                            (0x8) /* ��BD���� */
#define    HI_INVALID_BD_NUM_OFFSET                          (0xC) /* �Ƿ�BD���� */
#define    HI_DMA_CFG_OFFSET                                 (0x14) /* dma���üĴ��� */
#define    HI_CIPHER_VERSION_OFFSET                          (0x18) /* cipher�汾�Ĵ��� */
#define    HI_TEST_REG0_OFFSET                               (0x20) /* ���ԼĴ��� */
#define    HI_TEST_REG1_OFFSET                               (0x24) /* ���ԼĴ��� */
#define    HI_TEST_REG2_OFFSET                               (0x28) /* ���ԼĴ��� */
#define    HI_CIPHER_DEBUG20_OFFSET                          (0x2C) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG0_OFFSET                           (0x30) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG1_OFFSET                           (0x34) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG2_OFFSET                           (0x38) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG3_OFFSET                           (0x3C) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG4_OFFSET                           (0x40) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG5_OFFSET                           (0x44) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG6_OFFSET                           (0x48) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG7_OFFSET                           (0x4C) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG8_OFFSET                           (0x50) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG9_OFFSET                           (0x54) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG10_OFFSET                          (0x58) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG11_OFFSET                          (0x5C) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG12_OFFSET                          (0x60) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG13_OFFSET                          (0x64) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG14_OFFSET                          (0x68) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG15_OFFSET                          (0x6C) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG16_OFFSET                          (0x70) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG17_OFFSET                          (0x74) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG18_OFFSET                          (0x78) /* debug�Ĵ��� */
#define    HI_CIPHER_DEBUG19_OFFSET                          (0x7C) /* debug�Ĵ��� */
#define    HI_CH0_SOFTRESET_OFFSET                           (0x80) /* ͨ��0��λ�Ĵ��� */
#define    HI_CH0_EN_OFFSET                                  (0x84) /* ͨ��0ʹ�ܼĴ��� */
#define    HI_CH0_CONFIG_OFFSET                              (0x88) /* ͨ��0���üĴ��� */
#define    HI_CH0_BDQ_BADDR_OFFSET                           (0x8C) /* ͨ��0 BDQ����ַ�Ĵ��� */
#define    HI_CH0_BDQ_SIZE_OFFSET                            (0x90) /* ͨ��0 BDQ��С�Ĵ��� */
#define    HI_CH0_BDQ_PTR_OFFSET                             (0x94) /* ͨ��0 BDQ��дָ��Ĵ����� */
#define    HI_CH0_BDQ_RADDR_OFFSET                           (0x98) /* ͨ��0 BDQ����ַ�Ĵ����� */
#define    HI_CH0_BDQ_WADDR_OFFSET                           (0x9C) /* ͨ��0 BDQд��ַ�Ĵ����� */
#define    HI_CH0_BD_NUM_OFFSET                              (0xA0) /* ��ʾͨ��0�����BD���� */
#define    HI_CH0_INVALID_BD_NUM_OFFSET                      (0xA4) /* ��ʾͨ��0�������ЧBD�� */
#define    HI_CH1_SOFTRESET_OFFSET                           (0x100) /* ͨ��1��λ�Ĵ��� */
#define    HI_CH1_EN_OFFSET                                  (0x104) /* ͨ��1ʹ�ܼĴ��� */
#define    HI_CH1_CONFIG_OFFSET                              (0x108) /* ͨ��1���üĴ��� */
#define    HI_CH1_BDQ_BADDR_OFFSET                           (0x10C) /* ͨ��1 BDQ����ַ�Ĵ��� */
#define    HI_CH1_BDQ_SIZE_OFFSET                            (0x110) /* ͨ��1 BDQ��С�Ĵ��� */
#define    HI_CH1_BDQ_PTR_OFFSET                             (0x114) /* ͨ��1 BDQ��дָ��Ĵ����� */
#define    HI_CH1_BDQ_RADDR_OFFSET                           (0x118) /* ͨ��1 BDQ����ַ�Ĵ����� */
#define    HI_CH1_BDQ_WADDR_OFFSET                           (0x11C) /* ͨ��1 BDQд��ַ�Ĵ����� */
#define    HI_CH1_BD_NUM_OFFSET                              (0x120) /* ��ʾͨ��1�����BD���� */
#define    HI_CH1_INVALID_BD_NUM_OFFSET                      (0x124) /* ��ʾͨ��1�������ЧBD�� */
#define    HI_CH2_SOFTRESET_OFFSET                           (0x180) /* ͨ��2��λ�Ĵ��� */
#define    HI_CH2_EN_OFFSET                                  (0x184) /* ͨ��2ʹ�ܼĴ��� */
#define    HI_CH2_CONFIG_OFFSET                              (0x188) /* ͨ��2���üĴ��� */
#define    HI_CH2_BDQ_BADDR_OFFSET                           (0x18C) /* ͨ��2 BDQ����ַ�Ĵ��� */
#define    HI_CH2_BDQ_SIZE_OFFSET                            (0x190) /* ͨ��2 BDQ��С�Ĵ��� */
#define    HI_CH2_BDQ_PTR_OFFSET                             (0x194) /* ͨ��2 BDQ��дָ��Ĵ����� */
#define    HI_CH2_BDQ_RADDR_OFFSET                           (0x198) /* ͨ��2 BDQ����ַ�Ĵ����� */
#define    HI_CH2_BDQ_WADDR_OFFSET                           (0x19C) /* ͨ��2 BDQд��ַ�Ĵ����� */
#define    HI_CH2_BD_NUM_OFFSET                              (0x1A0) /* ��ʾͨ��1�����BD���� */
#define    HI_CH2_INVALID_BD_NUM_OFFSET                      (0x1A4) /* ��ʾͨ��1�������ЧBD�� */
#define    HI_CH3_SOFTRESET_OFFSET                           (0x200) /* ͨ��3��λ�Ĵ��� */
#define    HI_CH3_EN_OFFSET                                  (0x204) /* ͨ��3ʹ�ܼĴ��� */
#define    HI_CH3_CONFIG_OFFSET                              (0x208) /* ͨ��3���üĴ��� */
#define    HI_CH3_BDQ_BADDR_OFFSET                           (0x20C) /* ͨ��3 BDQ����ַ�Ĵ��� */
#define    HI_CH3_BDQ_SIZE_OFFSET                            (0x210) /* ͨ��3 BDQ��С�Ĵ��� */
#define    HI_CH3_BDQ_PTR_OFFSET                             (0x214) /* ͨ��3 BDQ��дָ��Ĵ����� */
#define    HI_CH3_BDQ_RADDR_OFFSET                           (0x218) /* ͨ��3 BDQ����ַ�Ĵ����� */
#define    HI_CH3_BDQ_WADDR_OFFSET                           (0x21C) /* ͨ��3 BDQд��ַ�Ĵ����� */
#define    HI_CH3_BD_NUM_OFFSET                              (0x220) /* ��ʾͨ��3�����BD���� */
#define    HI_CH3_INVALID_BD_NUM_OFFSET                      (0x224) /* ��ʾͨ��3�������ЧBD�� */
#define    HI_CH4_SOFTRESET_OFFSET                           (0x280) /* ͨ��4��λ�Ĵ��� */
#define    HI_CH4_EN_OFFSET                                  (0x284) /* ͨ��4ʹ�ܼĴ��� */
#define    HI_CH4_CONFIG_OFFSET                              (0x288) /* ͨ��4���üĴ��� */
#define    HI_CH4_BDQ_BADDR_OFFSET                           (0x28C) /* ͨ��4 BDQ����ַ�Ĵ��� */
#define    HI_CH4_BDQ_SIZE_OFFSET                            (0x290) /* ͨ��4 BDQ��С�Ĵ��� */
#define    HI_CH4_BDQ_PTR_OFFSET                             (0x294) /* ͨ��4 BDQ��дָ��Ĵ����� */
#define    HI_CH4_BDQ_RADDR_OFFSET                           (0x298) /* ͨ��4 BDQ����ַ�Ĵ����� */
#define    HI_CH4_BDQ_WADDR_OFFSET                           (0x29C) /* ͨ��4 BDQд��ַ�Ĵ����� */
#define    HI_CH4_BD_NUM_OFFSET                              (0x2A0) /* ��ʾͨ��4�����BD���� */
#define    HI_CH4_INVALID_BD_NUM_OFFSET                      (0x2A4) /* ��ʾͨ��4�������ЧBD�� */
#define    HI_CH_INT_PKT_INTERVAL_OFFSET                     (0x400) /* �жϰ�����Ĵ��� */
#define    HI_CIPHER_INT_STATUS_OFFSET                       (0x404) /* cipher�ж�״̬�Ĵ��� */
#define    HI_CIPHER_INT0_STATUS_OFFSET                      (0x408) /* cipher�жϼĴ���0 */
#define    HI_CIPHER_INT0_MASK_OFFSET                        (0x40C) /* cipher�ж����μĴ���0 */
#define    HI_CIPHER_INT0_MSTATUS_OFFSET                     (0x410) /* cipher��������֮����ж�״̬�Ĵ���0 */
#define    HI_CIPHER_INT1_STATUS_OFFSET                      (0x414) /* cipher�жϼĴ���1 */
#define    HI_CIPHER_INT1_MASK_OFFSET                        (0x418) /* cipher�ж����μĴ���1 */
#define    HI_CIPHER_INT1_MSTATUS_OFFSET                     (0x41C) /* cipher��������֮����ж�״̬�Ĵ���1 */
#define    HI_CIPHER_INT2_STATUS_OFFSET                      (0x420) /* cipher�жϼĴ���2 */
#define    HI_CIPHER_INT2_MASK_OFFSET                        (0x424) /* cipher�ж����μĴ���2 */
#define    HI_CIPHER_INT2_MSTATUS_OFFSET                     (0x428) /* cipher��������֮����ж�״̬�Ĵ���2 */
#define    HI_CH0_RDQ_BADDR_OFFSET                           (0x480) /* ͨ��0 RD���л���ַ */
#define    HI_CH0_RDQ_SIZE_OFFSET                            (0x484) /* ͨ��0 RD���д�С */
#define    HI_CH0_RDQ_PTR_OFFSET                             (0x488) /* ͨ��0 RD���еĶ�дָ�� */
#define    HI_CH0_RDQ_RADDR_OFFSET                           (0x48C) /* ͨ��0 RD���еĶ���ַ */
#define    HI_CH0_RDQ_WADDR_OFFSET                           (0x490) /* ͨ��0 RD���е�д��ַ */
#define    HI_CH1_RDQ_BADDR_OFFSET                           (0x500) /* ͨ��1 RD���л���ַ */
#define    HI_CH1_RDQ_SIZE_OFFSET                            (0x504) /* ͨ��1 RD���д�С */
#define    HI_CH1_RDQ_PTR_OFFSET                             (0x508) /* ͨ��1 RD���еĶ�дָ�� */
#define    HI_CH1_RDQ_RADDR_OFFSET                           (0x50C) /* ͨ��1 RD���еĶ���ַ */
#define    HI_CH1_RDQ_WADDR_OFFSET                           (0x510) /* ͨ��1 RD���е�д��ַ */
#define    HI_CH2_RDQ_BADDR_OFFSET                           (0x580) /* ͨ��2 RD���л���ַ */
#define    HI_CH2_RDQ_SIZE_OFFSET                            (0x584) /* ͨ��2 RD���д�С */
#define    HI_CH2_RDQ_PTR_OFFSET                             (0x588) /* ͨ��2 RD���еĶ�дָ�� */
#define    HI_CH2_RDQ_RADDR_OFFSET                           (0x58C) /* ͨ��2 RD���еĶ���ַ */
#define    HI_CH2_RDQ_WADDR_OFFSET                           (0x590) /* ͨ��2 RD���е�д��ַ */
#define    HI_CH3_RDQ_BADDR_OFFSET                           (0x600) /* ͨ��3 RD���л���ַ */
#define    HI_CH3_RDQ_SIZE_OFFSET                            (0x604) /* ͨ��3 RD���д�С */
#define    HI_CH3_RDQ_PTR_OFFSET                             (0x608) /* ͨ��3 RD���еĶ�дָ�� */
#define    HI_CH3_RDQ_RADDR_OFFSET                           (0x60C) /* ͨ��3 RD���еĶ���ַ */
#define    HI_CH3_RDQ_WADDR_OFFSET                           (0x610) /* ͨ��3 RD���е�д��ַ */
#define    HI_CH4_RDQ_BADDR_OFFSET                           (0x680) /* ͨ��4 RD���л���ַ */
#define    HI_CH4_RDQ_SIZE_OFFSET                            (0x684) /* ͨ��4 RD���д�С */
#define    HI_CH4_RDQ_PTR_OFFSET                             (0x688) /* ͨ��4 RD���еĶ�дָ�� */
#define    HI_CH4_RDQ_RADDR_OFFSET                           (0x68C) /* ͨ��4 RD���еĶ���ַ */
#define    HI_CH4_RDQ_WADDR_OFFSET                           (0x690) /* ͨ��4 RD���е�д��ַ */
#define    HI_KEY_RAM_OFFSET                                 (0x800) /* cipher�ڲ���key ram */

/********************************************************************************/
/*    cipher �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    cipher_srst                : 1; /* [0..0] cipherģ�鸴λ��д1��λcipherģ�飬����ʱcipherռ�����ߣ���������ִ�и�λ��ֱ��cipher�ͷ������Ժ�ſ�ʼ��λ����λ�����˼Ĵ����Զ���0�� */
        unsigned int    cipher_cg_en               : 1; /* [1..1] cipher�Զ�ʱ���ſ�ʹ�� */
        unsigned int    reserved                   : 29; /* [30..2] ������ */
        unsigned int    cipher_busy                : 1; /* [31..31] cipherģ��æ��־����5������ͨ�����κ�һ�����ƼĴ�����æ��־Ϊ1�������־��Ϊ1�� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_CTRL_T;    /* CIPHERģ����ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    idata_threshold            : 28; /* [27..0] ͨ������������ֵ����λ���ֽڣ������������������ݡ�������������ȼ�ͨ�����������󣬵�ǰͨ����������������ʼ�����������������������ֵ�������������ǰͨ����ͣ�����ȼ���Ϊ��ͣ�����ͨ����ʼ������ͨ��2��ͨ��3֧�������������ƹ��ܡ� */
        unsigned int    ch_pri                     : 1; /* [28..28] ͨ��0��ͨ��1���ȼ���0��ͨ��0Ϊ������ȼ���1��ͨ��1Ϊ������ȼ���ͨ��2��ͨ��3�����ȼ����ǵ���ͨ��0��ͨ��1���Ҹ����������ƼĴ�����ִ�С� */
        unsigned int    reserved                   : 3; /* [31..29]  */
    } bits;
    unsigned int    u32;
}HI_CIPHER_PRI_T;    /* CIPHER���ȼ����ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    total_bd_num               : 32; /* [31..0] ��ʾcipher�Ѿ������BD������5��ͨ�����ܺͣ�ֻ������д��0 */
    } bits;
    unsigned int    u32;
}HI_TOTAL_BD_NUM_T;    /* ��BD���� */

typedef union
{
    struct
    {
        unsigned int    invalid_bd_num             : 32; /* [31..0] ��ʾcipher�յ�����ЧBD������5��ͨ�����ܺͣ�ֻ������д��0 */
    } bits;
    unsigned int    u32;
}HI_INVALID_BD_NUM_T;    /* �Ƿ�BD���� */

typedef union
{
    struct
    {
        unsigned int    rd_id                      : 3; /* [2..0] RD��дͨ����ID */
        unsigned int    obuf_id                    : 3; /* [5..3] OBUFдͨ����ID */
        unsigned int    ocd_id                     : 3; /* [8..6] OCD��ͨ����ID */
        unsigned int    icd_id                     : 3; /* [11..9] ICD��ͨ����ID */
        unsigned int    ibuf_id                    : 3; /* [14..12] IBUF��ͨ����ID */
        unsigned int    reserved_1                 : 1; /* [15..15] ���� */
        unsigned int    rd_pri                     : 3; /* [18..16] RD��дͨ�������ȼ� */
        unsigned int    obuf_pri                   : 3; /* [21..19] OBUFдͨ�������ȼ� */
        unsigned int    ocd_pri                    : 3; /* [24..22] OCD��ͨ�������ȼ� */
        unsigned int    icd_pri                    : 3; /* [27..25] ICD��ͨ�������ȼ� */
        unsigned int    ibuf_pri                   : 3; /* [30..28] IBUF��ͨ�������ȼ� */
        unsigned int    reserved_0                 : 1; /* [31..31] ���� */
    } bits;
    unsigned int    u32;
}HI_DMA_CFG_T;    /* dma���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    spram_mem_ctrl             : 16; /* [15..0] cipher�ڲ�spram�Ŀ����ź� */
        unsigned int    atpram_mem_ctrl            : 16; /* [31..16] cipher�ڲ�atpram�Ŀ����ź� */
    } bits;
    unsigned int    u32;
}HI_TEST_REG0_T;    /* ���ԼĴ��� */

typedef union
{
    struct
    {
        unsigned int    aes_key_cov                : 1; /* [0..0] aes����ʱ���Ƿ���Ҫ�ߵ�key������1����ʾ��Ҫ�ߵ�����0����ʾ����Ҫ�ߵ����� */
        unsigned int    snow3g_key_cov             : 1; /* [1..1] snow3g����ʱ���Ƿ���Ҫ�ߵ�key������1����ʾ��Ҫ�ߵ�����0����ʾ����Ҫ�ߵ����� */
        unsigned int    cipher_dma_ctrl            : 6; /* [7..2] ����dma�Ŀ����źţ�[5:4]����ʾGMд�����outstanding���[3:2]����ʾGM�������outstanding���[1]�� 1��ʾ��outstandingʹ�ܣ�0��ʾ��outstanding��ʹ�� ��[0]�� 1��ʾдoutstandingʹ�ܣ�0��ʾдoutstanding��ʹ�ܡ� */
        unsigned int    zuc_key_cov                : 1; /* [8..8] zuc����ʱ���Ƿ���Ҫ�ߵ�key������1����ʾ��Ҫ�ߵ�����0����ʾ����Ҫ�ߵ����� */
        unsigned int    reserved_2                 : 1; /* [9..9] ���� */
        unsigned int    snow3g_iv_cov              : 1; /* [10..10] snow3g����ʱ���Ƿ���Ҫ�ߵ�iv������1����ʾ��Ҫ�ߵ�����0����ʾ����Ҫ�ߵ����� */
        unsigned int    reserved_1                 : 5; /* [15..11]  */
        unsigned int    ibuf_dma_req_len           : 5; /* [20..16] ibuf��������������󳤶�����                ֧��0~16                               ��dma_opt=0��Ӧ����ibuf_dma_req_len<=0x10��                 ��dma_opt=1��Ϊ�˷�ֹAXI���߷�ѹ����������ibuf_dma_req_len<=0x0A */
        unsigned int    dma_opt                    : 1; /* [21..21] dma�Ż�ʹ�ܿ���λ                      1��ibuf��outstanding��������ֹ��       0��ibuf��outstanding������ʹ�ܡ� */
        unsigned int    reserved_0                 : 10; /* [31..22] ���� */
    } bits;
    unsigned int    u32;
}HI_TEST_REG1_T;    /* ���ԼĴ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���ԼĴ����� */
    } bits;
    unsigned int    u32;
}HI_TEST_REG2_T;    /* ���ԼĴ��� */

typedef union
{
    struct
    {
        unsigned int    dma_rd_gnt                 : 1; /* [0..0] rd��dma������Ӧ */
        unsigned int    dma_ocd_gnt                : 1; /* [1..1] ocd��dma������Ӧ */
        unsigned int    dma_icd_gnt                : 1; /* [2..2] icd��dma������Ӧ */
        unsigned int    dma_obuf_gnt               : 1; /* [3..3] obuf��dma������Ӧ */
        unsigned int    dma_ibuf_gnt               : 1; /* [4..4] ibuf��dma������Ӧ */
        unsigned int    reserved_3                 : 3; /* [7..5]  */
        unsigned int    dma_rd_req                 : 1; /* [8..8] rd����dma���� */
        unsigned int    dma_ocd_req                : 1; /* [9..9] ocd����dma���� */
        unsigned int    dma_icd_req                : 1; /* [10..10] icd����dma���� */
        unsigned int    dma_obuf_req               : 1; /* [11..11] obuf����dma���� */
        unsigned int    dma_ibuf_req               : 1; /* [12..12] ibuf����dma���� */
        unsigned int    reserved_2                 : 3; /* [15..13]  */
        unsigned int    dma_rd_idle                : 1; /* [16..16] rdû�н���dma���������ڴ��ڿ���״̬ */
        unsigned int    dma_ocd_idle               : 1; /* [17..17] ocdû�н���dma���������ڴ��ڿ���״̬ */
        unsigned int    dma_icd_idle               : 1; /* [18..18] icdû�н���dma���������ڴ��ڿ���״̬ */
        unsigned int    dma_obuf_idle              : 1; /* [19..19] obufû�н���dma���������ڴ��ڿ���״̬ */
        unsigned int    dma_ibuf_idle              : 1; /* [20..20] ibufû�н���dma���������ڴ��ڿ���״̬ */
        unsigned int    reserved_1                 : 3; /* [23..21]  */
        unsigned int    dma_rd_trans_end           : 1; /* [24..24] rdÿ��dma���׵����һ������ */
        unsigned int    dma_ocd_last_read          : 1; /* [25..25] ocdÿ��dma���׵����һ������ */
        unsigned int    dma_icd_last_read          : 1; /* [26..26] icdÿ��dma���׵����һ������ */
        unsigned int    dma_obuf_trans_end         : 1; /* [27..27] obufÿ��dma���׵����һ������ */
        unsigned int    dma_ibuf_last_read         : 1; /* [28..28] ibufÿ��dma���׵����һ������ */
        unsigned int    reserved_0                 : 3; /* [31..29] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG20_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG0_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG1_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG2_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG3_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG4_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG5_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG6_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG7_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG8_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG9_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG10_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG11_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG12_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG13_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG14_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG15_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG16_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG17_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG18_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG19_T;    /* debug�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] д1��λͨ��������ʱͨ��ռ�����ߣ���������ִ�и�λ��ֱ����ͨ���ͷ������Ժ�ſ�ʼ��λ����λ�����˼Ĵ����Զ���0�� */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] д1����λBD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����BD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] д1����λRD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����RD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    reserved                   : 29; /* [31..3] ��˵���� */
    } bits;
    unsigned int    u32;
}HI_CH0_SOFTRESET_T;    /* ͨ��0��λ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1��ʾͨ��ʹ�ܣ�0��ʾͨ����ֹ�� */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] �˼Ĵ�����ʼֵΪ1����Ϊ1ʱ����ʾ�������������ɣ����Կ�ʼ��һ�Σ������ʾ��������������ڽ��С�����������Ϲ������£���cipher��Ͻ����������ʱ�����Ȳ�ѯ�˼Ĵ�������Ϊ1����ʾ���Կ�ʼ������������bit��0��������ѱ�����������һ��BD�е�gen_bd_int��Ϊ��Ч����cipher��������һ��BD����󣬰Ѵ˼Ĵ�����Ϊ1��֪ͨ������Կ�ʼ��һ��������� */
        unsigned int    ch_busy                    : 1; /* [31..31] 1��ʾͨ��������0��ʾͨ����ͣ�� */
    } bits;
    unsigned int    u32;
}HI_CH0_EN_T;    /* ͨ��0ʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] ��ͨ�������Բ�����IV��BD���Ƕ���оƬ�Զ�������0�������Բ�����IV��оƬ���ݲ����Զ�������1�������Բ�����IV�������BD�� */
        unsigned int    iv_num                     : 1; /* [1..1] ��ͨ��BD�к��е�IV������ֻ�е�iv_selΪ1ʱ�����塣0��һ��IV����ʱBD���ȹ̶��ǣ�1������IV������һ��IV��������ЧIV��������ռ���ڴ档 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ����ά����ʽ����RDQ��������Ҫ��д��RDʱ��Cipher�ȴ�ֱ��RDQ������00������дRD��01��ÿ��BD����Ӧ��дRD��others��RD�Ƿ��д��BD���þ�����ֻ��BD�е�gen_rd_en��Чʱ��дRD�� */
        unsigned int    reserved_1                 : 1; /* [4..4] ������ */
        unsigned int    ufield_len                 : 2; /* [6..5] BD��userfield�ֶεĳ��ȣ���λ��32bit�� */
        unsigned int    reserved_0                 : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_CH0_CONFIG_T;    /* ͨ��0���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 BD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��0 BD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_BADDR_T;    /* ͨ��0 BDQ����ַ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 BD Queue��С��������������Ϊ��λ��0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_SIZE_T;    /* ͨ��0 BDQ��С�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] BD���ж�ָ�롣�ɱ���λ�� */
        unsigned int    reserved_0                 : 4; /* [29..26] ���� */
        unsigned int    ch_bdq_empty               : 1; /* [30..30] BD���п� */
        unsigned int    ch_bdq_full                : 1; /* [31..31] BD������ */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_PTR_T;    /* ͨ��0 BDQ��дָ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��0 BD���ж���ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_RADDR_T;    /* ͨ��0 BDQ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��0 BD����д��ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_WADDR_T;    /* ͨ��0 BDQд��ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ch0_bd_num                 : 32; /* [31..0] ��ʾͨ��0�Ѿ������BD��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH0_BD_NUM_T;    /* ��ʾͨ��0�����BD���� */

typedef union
{
    struct
    {
        unsigned int    ch0_invalid_bd_num         : 32; /* [31..0] ��ʾͨ��0�Ѿ��������ЧBD��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH0_INVALID_BD_NUM_T;    /* ��ʾͨ��0�������ЧBD�� */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] д1��λͨ��������ʱͨ��ռ�����ߣ���������ִ�и�λ��ֱ����ͨ���ͷ������Ժ�ſ�ʼ��λ����λ�����˼Ĵ����Զ���0�� */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] д1����λBD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����BD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] д1����λRD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����RD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    reserved                   : 29; /* [31..3] ��˵���� */
    } bits;
    unsigned int    u32;
}HI_CH1_SOFTRESET_T;    /* ͨ��1��λ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1��ʾͨ��ʹ�ܣ�0��ʾͨ����ֹ�� */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] �˼Ĵ�����ʼֵΪ1����Ϊ1ʱ����ʾ�������������ɣ����Կ�ʼ��һ�Σ������ʾ��������������ڽ��С�����������Ϲ������£���cipher��Ͻ����������ʱ�����Ȳ�ѯ�˼Ĵ�������Ϊ1����ʾ���Կ�ʼ������������bit��0��������ѱ�����������һ��BD�е�gen_bd_int��Ϊ��Ч����cipher��������һ��BD����󣬰Ѵ˼Ĵ�����Ϊ1��֪ͨ������Կ�ʼ��һ��������� */
        unsigned int    ch_busy                    : 1; /* [31..31] 1��ʾͨ��������0��ʾͨ����ͣ�� */
    } bits;
    unsigned int    u32;
}HI_CH1_EN_T;    /* ͨ��1ʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] ��ͨ�������Բ�����IV��BD���Ƕ���оƬ�Զ�������0�������Բ�����IV��оƬ���ݲ����Զ�������1�������Բ�����IV�������BD�� */
        unsigned int    iv_num                     : 1; /* [1..1] ��ͨ��BD�к��е�IV������ֻ�е�iv_selΪ1ʱ�����塣0��һ��IV����ʱBD���ȹ̶��ǣ�1������IV������һ��IV��������ЧIV��������ռ���ڴ档 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ����ά����ʽ����RDQ��������Ҫ��д��RDʱ��Cipher�ȴ�ֱ��RDQ������00������дRD��01��ÿ��BD����Ӧ��дRD��others��RD�Ƿ��д��BD���þ�����ֻ��BD�е�gen_rd_en��Чʱ��дRD�� */
        unsigned int    reserved_1                 : 1; /* [4..4] ������ */
        unsigned int    ufield_len                 : 2; /* [6..5] BD��userfield�ֶεĳ��ȣ���λ��32bit�� */
        unsigned int    reserved_0                 : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_CH1_CONFIG_T;    /* ͨ��1���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 BD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��1 BD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_BADDR_T;    /* ͨ��1 BDQ����ַ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 BD Queue��С��������������Ϊ��λ��0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_SIZE_T;    /* ͨ��1 BDQ��С�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] BD���ж�ָ�롣�ɱ���λ�� */
        unsigned int    reserved_0                 : 4; /* [29..26] ���� */
        unsigned int    ch1_bdq_empty              : 1; /* [30..30] B���п� */
        unsigned int    ch1_bdq_full               : 1; /* [31..31] BD������ */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_PTR_T;    /* ͨ��1 BDQ��дָ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��1 BD���ж���ַ���ɱ���λ�� */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_RADDR_T;    /* ͨ��1 BDQ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��1 BD����д��ַ���ɱ���λ�� */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_WADDR_T;    /* ͨ��1 BDQд��ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ch1_bd_num                 : 32; /* [31..0] ��ʾͨ��1�Ѿ������BD����ֻ��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH1_BD_NUM_T;    /* ��ʾͨ��1�����BD���� */

typedef union
{
    struct
    {
        unsigned int    ch1_invalid_bd_num         : 32; /* [31..0] ��ʾͨ��1�Ѿ��������ЧBD����ֻ��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH1_INVALID_BD_NUM_T;    /* ��ʾͨ��1�������ЧBD�� */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] д1��λͨ��������ʱͨ��ռ�����ߣ���������ִ�и�λ��ֱ����ͨ���ͷ������Ժ�ſ�ʼ��λ����λ�����˼Ĵ����Զ���0�� */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] д1����λBD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����BD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] д1����λRD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����RD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    reserved                   : 29; /* [31..3] ��˵���� */
    } bits;
    unsigned int    u32;
}HI_CH2_SOFTRESET_T;    /* ͨ��2��λ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1��ʾͨ��ʹ�ܣ�0��ʾͨ����ֹ�� */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] �˼Ĵ�����ʼֵΪ1����Ϊ1ʱ����ʾ�������������ɣ����Կ�ʼ��һ�Σ������ʾ��������������ڽ��С�����������Ϲ������£���cipher��Ͻ����������ʱ�����Ȳ�ѯ�˼Ĵ�������Ϊ1����ʾ���Կ�ʼ������������bit��0��������ѱ�����������һ��BD�е�gen_bd_int��Ϊ��Ч����cipher��������һ��BD����󣬰Ѵ˼Ĵ�����Ϊ1��֪ͨ������Կ�ʼ��һ��������� */
        unsigned int    ch_busy                    : 1; /* [31..31] 1��ʾͨ��������0��ʾͨ����ͣ�� */
    } bits;
    unsigned int    u32;
}HI_CH2_EN_T;    /* ͨ��2ʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] ��ͨ�������Բ�����IV��BD���Ƕ���оƬ�Զ�������0�������Բ�����IV��оƬ���ݲ����Զ�������1�������Բ�����IV�������BD�� */
        unsigned int    iv_num                     : 1; /* [1..1] ��ͨ��BD�к��е�IV������ֻ�е�iv_selΪ1ʱ�����塣0��һ��IV����ʱBD���ȹ̶��ǣ�1������IV������һ��IV��������ЧIV��������ռ���ڴ档 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ����ά����ʽ����RDQ��������Ҫ��д��RDʱ��Cipher�ȴ�ֱ��RDQ������00������дRD��01��ÿ��BD����Ӧ��дRD��others��RD�Ƿ��д��BD���þ�����ֻ��BD�е�gen_rd_en��Чʱ��дRD�� */
        unsigned int    reserved_1                 : 1; /* [4..4] ������ */
        unsigned int    ufield_len                 : 2; /* [6..5] BD��userfield�ֶεĳ��ȣ���λ��32bit�� */
        unsigned int    reserved_0                 : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_CH2_CONFIG_T;    /* ͨ��2���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 BD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��2 BD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_BADDR_T;    /* ͨ��2 BDQ����ַ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 BD Queue��С��������������Ϊ��λ��0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_SIZE_T;    /* ͨ��2 BDQ��С�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] BD���ж�ָ�롣�ɱ���λ�� */
        unsigned int    reserved_0                 : 4; /* [29..26] ���� */
        unsigned int    ch2_bdq_empty              : 1; /* [30..30] BD���п� */
        unsigned int    ch2_bdq_full               : 1; /* [31..31] BD������ */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_PTR_T;    /* ͨ��2 BDQ��дָ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��2 BD���ж���ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_RADDR_T;    /* ͨ��2 BDQ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��2 BD����д��ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_WADDR_T;    /* ͨ��2 BDQд��ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ch2_bd_num                 : 32; /* [31..0] ��ʾͨ��2�Ѿ������BD����ֻ��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH2_BD_NUM_T;    /* ��ʾͨ��1�����BD���� */

typedef union
{
    struct
    {
        unsigned int    ch2_invalid_bd_num         : 32; /* [31..0] ��ʾͨ��2�Ѿ��������ЧBD����ֻ��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH2_INVALID_BD_NUM_T;    /* ��ʾͨ��1�������ЧBD�� */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] д1��λͨ��������ʱͨ��ռ�����ߣ���������ִ�и�λ��ֱ����ͨ���ͷ������Ժ�ſ�ʼ��λ����λ�����˼Ĵ����Զ���0�� */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] д1����λBD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����BD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] д1����λRD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����RD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    reserved                   : 29; /* [31..3] ��˵���� */
    } bits;
    unsigned int    u32;
}HI_CH3_SOFTRESET_T;    /* ͨ��3��λ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1��ʾͨ��ʹ�ܣ�0��ʾͨ����ֹ�� */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] �˼Ĵ�����ʼֵΪ1����Ϊ1ʱ����ʾ�������������ɣ����Կ�ʼ��һ�Σ������ʾ��������������ڽ��С�����������Ϲ������£���cipher��Ͻ����������ʱ�����Ȳ�ѯ�˼Ĵ�������Ϊ1����ʾ���Կ�ʼ������������bit��0��������ѱ�����������һ��BD�е�gen_bd_int��Ϊ��Ч����cipher��������һ��BD����󣬰Ѵ˼Ĵ�����Ϊ1��֪ͨ������Կ�ʼ��һ��������� */
        unsigned int    ch_busy                    : 1; /* [31..31] 1��ʾͨ��������0��ʾͨ����ͣ�� */
    } bits;
    unsigned int    u32;
}HI_CH3_EN_T;    /* ͨ��3ʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] ��ͨ�������Բ�����IV��BD���Ƕ���оƬ�Զ�������0�������Բ�����IV��оƬ���ݲ����Զ�������1�������Բ�����IV�������BD�� */
        unsigned int    iv_num                     : 1; /* [1..1] ��ͨ��BD�к��е�IV������ֻ�е�iv_selΪ1ʱ�����塣0��һ��IV����ʱBD���ȹ̶��ǣ�1������IV������һ��IV��������ЧIV��������ռ���ڴ档 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ����ά����ʽ����RDQ��������Ҫ��д��RDʱ��Cipher�ȴ�ֱ��RDQ������00������дRD��01��ÿ��BD����Ӧ��дRD��others��RD�Ƿ��д��BD���þ�����ֻ��BD�е�gen_rd_en��Чʱ��дRD�� */
        unsigned int    reserved_1                 : 1; /* [4..4] ������ */
        unsigned int    ufield_len                 : 2; /* [6..5] BD��userfield�ֶεĳ��ȣ���λ��32bit�� */
        unsigned int    reserved_0                 : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_CH3_CONFIG_T;    /* ͨ��3���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 BD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��3 BD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_BADDR_T;    /* ͨ��3 BDQ����ַ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 BD Queue��С��������������Ϊ��λ��0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_SIZE_T;    /* ͨ��3 BDQ��С�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] BD���ж�ָ�롣�ɱ���λ�� */
        unsigned int    reserved_0                 : 4; /* [29..26] ���� */
        unsigned int    ch3_bdq_empty              : 1; /* [30..30] BD���п� */
        unsigned int    ch3_bdq_full               : 1; /* [31..31] BD������ */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_PTR_T;    /* ͨ��3 BDQ��дָ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��3 BD���ж���ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_RADDR_T;    /* ͨ��3 BDQ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��3 BD����д��ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_WADDR_T;    /* ͨ��3 BDQд��ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ch3_bd_num                 : 32; /* [31..0] ��ʾͨ��3�Ѿ������BD����ֻ��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH3_BD_NUM_T;    /* ��ʾͨ��3�����BD���� */

typedef union
{
    struct
    {
        unsigned int    ch3_invalid_bd_num         : 32; /* [31..0] ��ʾͨ��3�Ѿ��������ЧBD����ֻ��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH3_INVALID_BD_NUM_T;    /* ��ʾͨ��3�������ЧBD�� */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] д1��λͨ��������ʱͨ��ռ�����ߣ���������ִ�и�λ��ֱ����ͨ���ͷ������Ժ�ſ�ʼ��λ����λ�����˼Ĵ����Զ���0�� */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] д1����λBD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����BD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] д1����λRD���У�����ʱͨ����busy����ȵ���ǰBD������Ϻ����RD���У�ͬʱ��λ�Զ����㡣 */
        unsigned int    reserved                   : 29; /* [31..3] ��˵���� */
    } bits;
    unsigned int    u32;
}HI_CH4_SOFTRESET_T;    /* ͨ��4��λ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1��ʾͨ��ʹ�ܣ�0��ʾͨ����ֹ�� */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] �˼Ĵ�����ʼֵΪ1����Ϊ1ʱ����ʾ�������������ɣ����Կ�ʼ��һ�Σ������ʾ��������������ڽ��С�����������Ϲ������£���cipher��Ͻ����������ʱ�����Ȳ�ѯ�˼Ĵ�������Ϊ1����ʾ���Կ�ʼ������������bit��0��������ѱ�����������һ��BD�е�gen_bd_int��Ϊ��Ч����cipher��������һ��BD����󣬰Ѵ˼Ĵ�����Ϊ1��֪ͨ������Կ�ʼ��һ��������� */
        unsigned int    ch_busy                    : 1; /* [31..31] 1��ʾͨ��������0��ʾͨ����ͣ�� */
    } bits;
    unsigned int    u32;
}HI_CH4_EN_T;    /* ͨ��4ʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] ��ͨ�������Բ�����IV��BD���Ƕ���оƬ�Զ�������0�������Բ�����IV��оƬ���ݲ����Զ�������1�������Բ�����IV�������BD�� */
        unsigned int    iv_num                     : 1; /* [1..1] ��ͨ��BD�к��е�IV������ֻ�е�iv_selΪ1ʱ�����塣0��һ��IV����ʱBD���ȹ̶��ǣ�1������IV������һ��IV��������ЧIV��������ռ���ڴ档 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ����ά����ʽ����RDQ��������Ҫ��д��RDʱ��Cipher�ȴ�ֱ��RDQ������00������дRD��01��ÿ��BD����Ӧ��дRD��others��RD�Ƿ��д��BD���þ�����ֻ��BD�е�gen_rd_en��Чʱ��дRD�� */
        unsigned int    reserved_1                 : 1; /* [4..4] ������ */
        unsigned int    ufield_len                 : 2; /* [6..5] BD��userfield�ֶεĳ��ȣ���λ��32bit�� */
        unsigned int    reserved_0                 : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_CH4_CONFIG_T;    /* ͨ��4���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 BD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��4 BD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_BADDR_T;    /* ͨ��4 BDQ����ַ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 BD Queue��С��������������Ϊ��λ��0����ʾ���д�СΪ1255����ʾ���д�СΪ256 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_SIZE_T;    /* ͨ��4 BDQ��С�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] BD���ж�ָ�롣�ɱ���λ�� */
        unsigned int    reserved_0                 : 4; /* [29..26] ���� */
        unsigned int    ch4_bdq_empty              : 1; /* [30..30] BD���п� */
        unsigned int    ch4_bdq_full               : 1; /* [31..31] BD������ */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_PTR_T;    /* ͨ��4 BDQ��дָ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��4 BD���ж���ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_RADDR_T;    /* ͨ��4 BDQ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] ͨ��4 BD����д��ַ���ɱ���λ�� */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_WADDR_T;    /* ͨ��4 BDQд��ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ch4_bd_num                 : 32; /* [31..0] ��ʾͨ��4�Ѿ������BD����ֻ��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH4_BD_NUM_T;    /* ��ʾͨ��4�����BD���� */

typedef union
{
    struct
    {
        unsigned int    ch4_invalid_bd_num         : 32; /* [31..0] ��ʾͨ��4�Ѿ��������ЧBD����ֻ��������д���� */
    } bits;
    unsigned int    u32;
}HI_CH4_INVALID_BD_NUM_T;    /* ��ʾͨ��4�������ЧBD�� */

typedef union
{
    struct
    {
        unsigned int    ch0_pkt_num                : 4; /* [3..0] ͨ��0 BD DONE�жϰ��������0��5�����ݰ���1��10�����ݰ���n��10*��n+1�������ݰ� */
        unsigned int    ch1_pkt_num                : 4; /* [7..4] ͨ��1 BD DONE�жϰ��������0��5�����ݰ���1��10�����ݰ���n��10*��n+1�������ݰ� */
        unsigned int    ch2_pkt_num                : 4; /* [11..8] ͨ��2 BD DONE�жϰ��������0��5�����ݰ���1��10�����ݰ���n��10*��n+1�������ݰ� */
        unsigned int    ch3_pkt_num                : 4; /* [15..12] ͨ��3 BD DONE�жϰ��������0��5�����ݰ���1��10�����ݰ���n��10*��n+1�������ݰ� */
        unsigned int    timeout_time               : 9; /* [24..16] ��ʱ�ж���ֵ��4��ͨ�����á���λ��20us�� */
        unsigned int    ch4_pkt_num                : 4; /* [28..25] ͨ��4 BD DONE�жϰ��������0��5�����ݰ���1��10�����ݰ���n��10*��n+1�������ݰ� */
        unsigned int    reserved                   : 3; /* [31..29] ������ */
    } bits;
    unsigned int    u32;
}HI_CH_INT_PKT_INTERVAL_T;    /* �жϰ�����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    cipher_int0                : 1; /* [0..0] CIPHER_INT0_STATUS�жϼĴ����е��ж��Ƿ����ж������󡣿ɱ���λ */
        unsigned int    cipher_int1                : 1; /* [1..1] CIPHER_INT1_STATUS�жϼĴ����е��ж��Ƿ����ж������󡣿ɱ���λ */
        unsigned int    cipher_int2                : 1; /* [2..2] CIPHER_INT2_STATUS�жϼĴ����е��ж��Ƿ����ж������󡣿ɱ���λ */
        unsigned int    reserved                   : 29; /* [31..3] ������ */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT_STATUS_T;    /* cipher�ж�״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    ch0_bdq_full               : 1; /* [0..0] ͨ��0 BDQ���жϡ���BDQ��ʱ������жϡ� */
        unsigned int    ch0_rdq_full               : 1; /* [1..1] ͨ��0 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch0_nbd_done               : 1; /* [2..2] ͨ��0�����������ĿN��BD֮��������жϡ�N��ֵ��CH0_INT_PKT_INTERVAL�� */
        unsigned int    ch0_bd_done                : 1; /* [3..3] ͨ��0��BD��gen_int_enΪ1ʱ���ڵ�ǰBD�Ĳ�����ɺ�������жϡ� */
        unsigned int    ch0_allbd_done             : 1; /* [4..4] ͨ��0��BDQ�����һ��BD������ɺ�������жϡ� */
        unsigned int    ch0_integrity_err          : 1; /* [5..5] ͨ��0�����Լ������жϡ� */
        unsigned int    reserved_3                 : 2; /* [7..6]  */
        unsigned int    ch1_bdq_full               : 1; /* [8..8] ͨ��1 BDQ���жϡ���BDQ��ʱ������жϡ� */
        unsigned int    ch1_rdq_full               : 1; /* [9..9] ͨ��1 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch1_nbd_done               : 1; /* [10..10] ͨ��1�����������ĿN��BD֮��������жϡ�N��ֵ��CH0_INT_PKT_INTERVAL�� */
        unsigned int    ch1_bd_done                : 1; /* [11..11] ͨ��1��BD��gen_int_enΪ1ʱ���ڵ�ǰBD�Ĳ�����ɺ�������жϡ� */
        unsigned int    ch1_allbd_done             : 1; /* [12..12] ͨ��1��BDQ�����һ��BD������ɺ�������жϡ� */
        unsigned int    ch1_integrity_err          : 1; /* [13..13] ͨ��1�����Լ������жϡ� */
        unsigned int    reserved_2                 : 2; /* [15..14]  */
        unsigned int    ch2_bdq_full               : 1; /* [16..16] ͨ��2 BDQ���жϡ���BDQ��ʱ������жϡ� */
        unsigned int    ch2_rdq_full               : 1; /* [17..17] ͨ��2 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch2_nbd_done               : 1; /* [18..18] ͨ��2�����������ĿN��BD֮��������жϡ�N��ֵ��CH0_INT_PKT_INTERVAL�� */
        unsigned int    ch2_bd_done                : 1; /* [19..19] ͨ��2��BD��gen_int_enΪ1ʱ���ڵ�ǰBD�Ĳ�����ɺ�������жϡ� */
        unsigned int    ch2_allbd_done             : 1; /* [20..20] ͨ��2��BDQ�����һ��BD������ɺ�������жϡ� */
        unsigned int    ch2_integrity_err          : 1; /* [21..21] ͨ��2�����Լ������жϡ� */
        unsigned int    reserved_1                 : 2; /* [23..22]  */
        unsigned int    ch3_bdq_full               : 1; /* [24..24] ͨ��3 BDQ���жϡ���BDQ��ʱ������жϡ� */
        unsigned int    ch3_rdq_full               : 1; /* [25..25] ͨ��3 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch3_nbd_done               : 1; /* [26..26] ͨ��3�����������ĿN��BD֮��������жϡ�N��ֵ��CH0_INT_PKT_INTERVAL�� */
        unsigned int    ch3_bd_done                : 1; /* [27..27] ͨ��3��BD��gen_int_enΪ1ʱ���ڵ�ǰBD�Ĳ�����ɺ�������жϡ�д1���ж� */
        unsigned int    ch3_allbd_done             : 1; /* [28..28] ͨ��3��BDQ�����һ��BD������ɺ�������жϡ�д1���ж� */
        unsigned int    ch3_integrity_err          : 1; /* [29..29] ͨ��3�����Լ������жϡ�д1���жϡ� */
        unsigned int    reserved_0                 : 2; /* [31..30] ��������״̬�Ĵ����ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT0_STATUS_T;    /* cipher�жϼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    int0_mask                  : 32; /* [31..0] ��cipher_int0_status��λ��Ӧ���ж����μĴ��� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT0_MASK_T;    /* cipher�ж����μĴ���0 */

typedef union
{
    struct
    {
        unsigned int    int0_mstatus               : 32; /* [31..0] ��������֮����ж�״̬��д1�����Ӧbit���ɱ���λ�� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT0_MSTATUS_T;    /* cipher��������֮����ж�״̬�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    ch0_bdq_empty              : 1; /* [0..0] ͨ��0 BDQ���жϡ���BDQ��������BD�Ѵ�����ʱ������жϡ� */
        unsigned int    ch0_rdq_empty              : 1; /* [1..1] ͨ��0 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch0_timeout                : 1; /* [2..2] cipherһֱæ��һֱû��BD������ɡ���״̬����cipher���ֹ��ϣ���Ҫ���������λ���� */
        unsigned int    reserved_3                 : 5; /* [7..3]  */
        unsigned int    ch1_bdq_empty              : 1; /* [8..8] ͨ��1 BDQ���жϡ���BDQ��������BD�Ѵ�����ʱ������жϡ� */
        unsigned int    ch1_rdq_empty              : 1; /* [9..9] ͨ��1 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch1_timeout                : 1; /* [10..10] cipherһֱæ��һֱû��BD������ɡ���״̬����cipher���ֹ��ϣ���Ҫ���������λ���� */
        unsigned int    reserved_2                 : 5; /* [15..11]  */
        unsigned int    ch2_bdq_empty              : 1; /* [16..16] ͨ��2 BDQ���жϡ���BDQ��������BD�Ѵ�����ʱ������жϡ� */
        unsigned int    ch2_rdq_empty              : 1; /* [17..17] ͨ��2 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch2_timeout                : 1; /* [18..18] cipherһֱæ��һֱû��BD������ɡ���״̬����cipher���ֹ��ϣ���Ҫ���������λ���� */
        unsigned int    reserved_1                 : 5; /* [23..19]  */
        unsigned int    ch3_bdq_empty              : 1; /* [24..24] ͨ��3 BDQ���жϡ���BDQ��������BD�Ѵ�����ʱ������жϡ� */
        unsigned int    ch3_rdq_empty              : 1; /* [25..25] ͨ��3 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch3_timeout                : 1; /* [26..26] cipherһֱæ��һֱû��BD������ɡ���״̬����cipher���ֹ��ϣ���Ҫ���������λ���� */
        unsigned int    reserved_0                 : 5; /* [31..27] ��������״̬�Ĵ����ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT1_STATUS_T;    /* cipher�жϼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    int1_mask                  : 32; /* [31..0] ��cipher_int1_status��λ��Ӧ���ж����μĴ��� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT1_MASK_T;    /* cipher�ж����μĴ���1 */

typedef union
{
    struct
    {
        unsigned int    int1_mstatus               : 32; /* [31..0] ��������֮����ж�״̬��д1�����Ӧbit���ɱ���λ�� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT1_MSTATUS_T;    /* cipher��������֮����ж�״̬�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    ch4_bdq_full               : 1; /* [0..0] ͨ��4 BDQ���жϡ���BDQ��ʱ������жϡ� */
        unsigned int    ch4_rdq_full               : 1; /* [1..1] ͨ��4 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch4_nbd_done               : 1; /* [2..2] ͨ��4�����������ĿN��BD֮��������жϡ�N��ֵ��CH0_INT_PKT_INTERVAL�� */
        unsigned int    ch4_bd_done                : 1; /* [3..3] ͨ��4��BD��gen_int_enΪ1ʱ���ڵ�ǰBD�Ĳ�����ɺ�������жϡ� */
        unsigned int    ch4_allbd_done             : 1; /* [4..4] ͨ��4��BDQ�����һ��BD������ɺ�������жϡ� */
        unsigned int    ch4_bdq_empty              : 1; /* [5..5] ͨ��4 BDQ���жϡ���BDQ��������BD�Ѵ�����ʱ������жϡ� */
        unsigned int    ch4_rdq_empty              : 1; /* [6..6] ͨ��4 RDQ���жϡ���RDQ��ʱ������жϡ� */
        unsigned int    ch4_timeout                : 1; /* [7..7] cipherһֱæ��һֱû��BD������ɡ���״̬����cipher���ֹ��ϣ���Ҫ���������λ���� */
        unsigned int    reserved                   : 24; /* [31..8] ��������״̬�Ĵ����ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT2_STATUS_T;    /* cipher�жϼĴ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ��cipher_int2_status��λ��Ӧ���ж����μĴ��� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT2_MASK_T;    /* cipher�ж����μĴ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ��������֮����ж�״̬��д1�����Ӧbit���ɱ���λ�� */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT2_MSTATUS_T;    /* cipher��������֮����ж�״̬�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 RD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��0 RD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_BADDR_T;    /* ͨ��0 RD���л���ַ */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 RD Queue��С��������������Ϊ��λ������0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_SIZE_T;    /* ͨ��0 RD���д�С */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] RD���ж�ָ�롣�ɱ���λ */
        unsigned int    reserved_0                 : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_PTR_T;    /* ͨ��0 RD���еĶ�дָ�� */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] ͨ��0 RD���ж���ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_RADDR_T;    /* ͨ��0 RD���еĶ���ַ */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] ͨ��0 RD����д��ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_WADDR_T;    /* ͨ��0 RD���е�д��ַ */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 RD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��1 RD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_BADDR_T;    /* ͨ��1 RD���л���ַ */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 RD Queue��С��������������Ϊ��λ������0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_SIZE_T;    /* ͨ��1 RD���д�С */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] RD���ж�ָ�롣�ɱ���λ */
        unsigned int    reserved_0                 : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_PTR_T;    /* ͨ��1 RD���еĶ�дָ�� */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] ͨ��1 RD���ж���ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_RADDR_T;    /* ͨ��1 RD���еĶ���ַ */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] ͨ��1 RD����д��ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_WADDR_T;    /* ͨ��1 RD���е�д��ַ */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 RD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��2 RD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_BADDR_T;    /* ͨ��2 RD���л���ַ */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 RD Queue��С��������������Ϊ��λ������0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_SIZE_T;    /* ͨ��2 RD���д�С */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] RD���ж�ָ�롣�ɱ���λ */
        unsigned int    reserved_0                 : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_PTR_T;    /* ͨ��2 RD���еĶ�дָ�� */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] ͨ��2 RD���ж���ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_RADDR_T;    /* ͨ��2 RD���еĶ���ַ */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] ͨ��2 RD����д��ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_WADDR_T;    /* ͨ��2 RD���е�д��ַ */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 RD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��3 RD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_BADDR_T;    /* ͨ��3 RD���л���ַ */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 RD Queue��С��������������Ϊ��λ������0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_SIZE_T;    /* ͨ��3 RD���д�С */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] RD���ж�ָ�롣�ɱ���λ */
        unsigned int    reserved_0                 : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_PTR_T;    /* ͨ��3 RD���еĶ�дָ�� */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] ͨ��3 RD���ж���ַ���ɱ���λ�� */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_RADDR_T;    /* ͨ��3 RD���еĶ���ַ */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] ͨ��3 RD����д��ַ���ɱ���λ�� */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_WADDR_T;    /* ͨ��3 RD���е�д��ַ */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] ͨ��0 RD���л���ַ��3bit���̶�Ϊ0����Ҫ���ַ64λ���롣 */
        unsigned int    base_addr                  : 29; /* [31..3] ͨ��4 RD���л���ַ��29λ */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_BADDR_T;    /* ͨ��4 RD���л���ַ */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] ͨ��0 RD Queue��С��������������Ϊ��λ������0����ʾ���д�СΪ11023����ʾ���д�СΪ1024 */
        unsigned int    reserved                   : 22; /* [31..10] ��Ա˵���� */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_SIZE_T;    /* ͨ��4 RD���д�С */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD����дָ�롣�ɱ���λ */
        unsigned int    reserved_1                 : 6; /* [15..10] ���� */
        unsigned int    rptr                       : 10; /* [25..16] RD���ж�ָ�롣�ɱ���λ */
        unsigned int    reserved_0                 : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_PTR_T;    /* ͨ��4 RD���еĶ�дָ�� */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] ͨ��4 RD���ж���ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_RADDR_T;    /* ͨ��4 RD���еĶ���ַ */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] ͨ��4 RD����д��ַ���ɱ���λ */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_WADDR_T;    /* ͨ��4 RD���е�д��ַ */

typedef union
{
    struct
    {
        unsigned int    key                        : 32; /* [31..0] cipher�ڲ���key ram */
    } bits;
    unsigned int    u32;
}HI_KEY_RAM_T;    /* cipher�ڲ���key ram */

#if 0
/********************************************************************************/
/*    cipher ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_cipher_ctrl_cipher_srst,cipher_srst,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_cipher_cg_en,cipher_cg_en,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_reserved,reserved,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_cipher_busy,cipher_busy,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_pri_idata_threshold,idata_threshold,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_ch_pri,ch_pri,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_reserved,reserved,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_total_bd_num_total_bd_num,total_bd_num,HI_TOTAL_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_TOTAL_BD_NUM_OFFSET)
HI_SET_GET(hi_invalid_bd_num_invalid_bd_num,invalid_bd_num,HI_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_dma_cfg_rd_id,rd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_obuf_id,obuf_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ocd_id,ocd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_icd_id,icd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ibuf_id,ibuf_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_reserved_1,reserved_1,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_rd_pri,rd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_obuf_pri,obuf_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ocd_pri,ocd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_icd_pri,icd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ibuf_pri,ibuf_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_reserved_0,reserved_0,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_test_reg0_spram_mem_ctrl,spram_mem_ctrl,HI_TEST_REG0_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG0_OFFSET)
HI_SET_GET(hi_test_reg0_atpram_mem_ctrl,atpram_mem_ctrl,HI_TEST_REG0_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG0_OFFSET)
HI_SET_GET(hi_test_reg1_aes_key_cov,aes_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_snow3g_key_cov,snow3g_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_cipher_dma_ctrl,cipher_dma_ctrl,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_zuc_key_cov,zuc_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_reserved_2,reserved_2,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_snow3g_iv_cov,snow3g_iv_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_reserved_1,reserved_1,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_ibuf_dma_req_len,ibuf_dma_req_len,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_dma_opt,dma_opt,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_reserved_0,reserved_0,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg2_reserved,reserved,HI_TEST_REG2_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG2_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_gnt,dma_rd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_gnt,dma_ocd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_gnt,dma_icd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_gnt,dma_obuf_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_gnt,dma_ibuf_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_3,reserved_3,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_req,dma_rd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_req,dma_ocd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_req,dma_icd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_req,dma_obuf_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_req,dma_ibuf_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_2,reserved_2,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_idle,dma_rd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_idle,dma_ocd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_idle,dma_icd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_idle,dma_obuf_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_idle,dma_ibuf_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_1,reserved_1,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_trans_end,dma_rd_trans_end,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_last_read,dma_ocd_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_last_read,dma_icd_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_trans_end,dma_obuf_trans_end,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_last_read,dma_ibuf_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_0,reserved_0,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug0_reserved,reserved,HI_CIPHER_DEBUG0_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG0_OFFSET)
HI_SET_GET(hi_cipher_debug1_reserved,reserved,HI_CIPHER_DEBUG1_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG1_OFFSET)
HI_SET_GET(hi_cipher_debug2_reserved,reserved,HI_CIPHER_DEBUG2_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG2_OFFSET)
HI_SET_GET(hi_cipher_debug3_reserved,reserved,HI_CIPHER_DEBUG3_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG3_OFFSET)
HI_SET_GET(hi_cipher_debug4_reserved,reserved,HI_CIPHER_DEBUG4_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG4_OFFSET)
HI_SET_GET(hi_cipher_debug5_reserved,reserved,HI_CIPHER_DEBUG5_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG5_OFFSET)
HI_SET_GET(hi_cipher_debug6_reserved,reserved,HI_CIPHER_DEBUG6_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG6_OFFSET)
HI_SET_GET(hi_cipher_debug7_reserved,reserved,HI_CIPHER_DEBUG7_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG7_OFFSET)
HI_SET_GET(hi_cipher_debug8_reserved,reserved,HI_CIPHER_DEBUG8_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG8_OFFSET)
HI_SET_GET(hi_cipher_debug9_reserved,reserved,HI_CIPHER_DEBUG9_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG9_OFFSET)
HI_SET_GET(hi_cipher_debug10_reserved,reserved,HI_CIPHER_DEBUG10_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG10_OFFSET)
HI_SET_GET(hi_cipher_debug11_reserved,reserved,HI_CIPHER_DEBUG11_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG11_OFFSET)
HI_SET_GET(hi_cipher_debug12_reserved,reserved,HI_CIPHER_DEBUG12_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG12_OFFSET)
HI_SET_GET(hi_cipher_debug13_reserved,reserved,HI_CIPHER_DEBUG13_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG13_OFFSET)
HI_SET_GET(hi_cipher_debug14_reserved,reserved,HI_CIPHER_DEBUG14_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG14_OFFSET)
HI_SET_GET(hi_cipher_debug15_reserved,reserved,HI_CIPHER_DEBUG15_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG15_OFFSET)
HI_SET_GET(hi_cipher_debug16_reserved,reserved,HI_CIPHER_DEBUG16_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG16_OFFSET)
HI_SET_GET(hi_cipher_debug17_reserved,reserved,HI_CIPHER_DEBUG17_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG17_OFFSET)
HI_SET_GET(hi_cipher_debug18_reserved,reserved,HI_CIPHER_DEBUG18_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG18_OFFSET)
HI_SET_GET(hi_cipher_debug19_reserved,reserved,HI_CIPHER_DEBUG19_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG19_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_srst,ch_srst,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_reserved,reserved,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_en_ch_en,ch_en,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_reserved,reserved,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_pack_en,pack_en,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_ch_busy,ch_busy,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_config_iv_sel,iv_sel,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_iv_num,iv_num,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_rdq_ctrl,rdq_ctrl,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_reserved_1,reserved_1,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_ufield_len,ufield_len,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_reserved_0,reserved_0,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_bdq_baddr_base_addr_l,base_addr_l,HI_CH0_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_baddr_base_addr,base_addr,HI_CH0_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_size_size,size,HI_CH0_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_bdq_size_reserved,reserved,HI_CH0_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_wptr,wptr,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_reserved_1,reserved_1,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_rptr,rptr,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_reserved_0,reserved_0,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_ch_bdq_empty,ch_bdq_empty,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_ch_bdq_full,ch_bdq_full,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_raddr_addr,addr,HI_CH0_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_waddr_addr,addr,HI_CH0_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch0_bd_num_ch0_bd_num,ch0_bd_num,HI_CH0_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH0_BD_NUM_OFFSET)
HI_SET_GET(hi_ch0_invalid_bd_num_ch0_invalid_bd_num,ch0_invalid_bd_num,HI_CH0_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH0_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_srst,ch_srst,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_reserved,reserved,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_en_ch_en,ch_en,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_reserved,reserved,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_pack_en,pack_en,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_ch_busy,ch_busy,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_config_iv_sel,iv_sel,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_iv_num,iv_num,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_rdq_ctrl,rdq_ctrl,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_reserved_1,reserved_1,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_ufield_len,ufield_len,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_reserved_0,reserved_0,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_bdq_baddr_base_addr_l,base_addr_l,HI_CH1_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_baddr_base_addr,base_addr,HI_CH1_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_size_size,size,HI_CH1_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_bdq_size_reserved,reserved,HI_CH1_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_wptr,wptr,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_reserved_1,reserved_1,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_rptr,rptr,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_reserved_0,reserved_0,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_ch1_bdq_empty,ch1_bdq_empty,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_ch1_bdq_full,ch1_bdq_full,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_raddr_addr,addr,HI_CH1_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_waddr_addr,addr,HI_CH1_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch1_bd_num_ch1_bd_num,ch1_bd_num,HI_CH1_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH1_BD_NUM_OFFSET)
HI_SET_GET(hi_ch1_invalid_bd_num_ch1_invalid_bd_num,ch1_invalid_bd_num,HI_CH1_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH1_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_srst,ch_srst,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_reserved,reserved,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_en_ch_en,ch_en,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_reserved,reserved,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_pack_en,pack_en,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_ch_busy,ch_busy,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_config_iv_sel,iv_sel,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_iv_num,iv_num,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_rdq_ctrl,rdq_ctrl,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_reserved_1,reserved_1,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_ufield_len,ufield_len,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_reserved_0,reserved_0,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_bdq_baddr_base_addr_l,base_addr_l,HI_CH2_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_baddr_base_addr,base_addr,HI_CH2_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_size_size,size,HI_CH2_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_bdq_size_reserved,reserved,HI_CH2_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_wptr,wptr,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_reserved_1,reserved_1,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_rptr,rptr,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_reserved_0,reserved_0,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_ch2_bdq_empty,ch2_bdq_empty,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_ch2_bdq_full,ch2_bdq_full,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_raddr_addr,addr,HI_CH2_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_waddr_addr,addr,HI_CH2_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch2_bd_num_ch2_bd_num,ch2_bd_num,HI_CH2_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH2_BD_NUM_OFFSET)
HI_SET_GET(hi_ch2_invalid_bd_num_ch2_invalid_bd_num,ch2_invalid_bd_num,HI_CH2_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH2_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_srst,ch_srst,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_reserved,reserved,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_en_ch_en,ch_en,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_reserved,reserved,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_pack_en,pack_en,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_ch_busy,ch_busy,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_config_iv_sel,iv_sel,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_iv_num,iv_num,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_rdq_ctrl,rdq_ctrl,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_reserved_1,reserved_1,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_ufield_len,ufield_len,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_reserved_0,reserved_0,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_bdq_baddr_base_addr_l,base_addr_l,HI_CH3_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_baddr_base_addr,base_addr,HI_CH3_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_size_size,size,HI_CH3_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_bdq_size_reserved,reserved,HI_CH3_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_wptr,wptr,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_reserved_1,reserved_1,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_rptr,rptr,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_reserved_0,reserved_0,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_ch3_bdq_empty,ch3_bdq_empty,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_ch3_bdq_full,ch3_bdq_full,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_raddr_addr,addr,HI_CH3_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_waddr_addr,addr,HI_CH3_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch3_bd_num_ch3_bd_num,ch3_bd_num,HI_CH3_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH3_BD_NUM_OFFSET)
HI_SET_GET(hi_ch3_invalid_bd_num_ch3_invalid_bd_num,ch3_invalid_bd_num,HI_CH3_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH3_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_srst,ch_srst,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_reserved,reserved,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_en_ch_en,ch_en,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_reserved,reserved,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_pack_en,pack_en,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_ch_busy,ch_busy,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_config_iv_sel,iv_sel,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_iv_num,iv_num,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_rdq_ctrl,rdq_ctrl,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_reserved_1,reserved_1,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_ufield_len,ufield_len,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_reserved_0,reserved_0,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_bdq_baddr_base_addr_l,base_addr_l,HI_CH4_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_baddr_base_addr,base_addr,HI_CH4_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_size_size,size,HI_CH4_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_bdq_size_reserved,reserved,HI_CH4_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_wptr,wptr,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_reserved_1,reserved_1,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_rptr,rptr,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_reserved_0,reserved_0,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_ch4_bdq_empty,ch4_bdq_empty,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_ch4_bdq_full,ch4_bdq_full,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_raddr_addr,addr,HI_CH4_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_waddr_addr,addr,HI_CH4_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch4_bd_num_ch4_bd_num,ch4_bd_num,HI_CH4_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH4_BD_NUM_OFFSET)
HI_SET_GET(hi_ch4_invalid_bd_num_ch4_invalid_bd_num,ch4_invalid_bd_num,HI_CH4_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH4_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch0_pkt_num,ch0_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch1_pkt_num,ch1_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch2_pkt_num,ch2_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch3_pkt_num,ch3_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_timeout_time,timeout_time,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch4_pkt_num,ch4_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_reserved,reserved,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int0,cipher_int0,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int1,cipher_int1,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int2,cipher_int2,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_reserved,reserved,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_bdq_full,ch0_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_rdq_full,ch0_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_nbd_done,ch0_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_bd_done,ch0_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_allbd_done,ch0_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_integrity_err,ch0_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_3,reserved_3,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_bdq_full,ch1_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_rdq_full,ch1_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_nbd_done,ch1_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_bd_done,ch1_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_allbd_done,ch1_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_integrity_err,ch1_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_2,reserved_2,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_bdq_full,ch2_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_rdq_full,ch2_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_nbd_done,ch2_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_bd_done,ch2_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_allbd_done,ch2_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_integrity_err,ch2_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_1,reserved_1,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_bdq_full,ch3_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_rdq_full,ch3_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_nbd_done,ch3_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_bd_done,ch3_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_allbd_done,ch3_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_integrity_err,ch3_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_0,reserved_0,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_mask_int0_mask,int0_mask,HI_CIPHER_INT0_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_MASK_OFFSET)
HI_SET_GET(hi_cipher_int0_mstatus_int0_mstatus,int0_mstatus,HI_CIPHER_INT0_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_MSTATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_bdq_empty,ch0_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_rdq_empty,ch0_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_timeout,ch0_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_3,reserved_3,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_bdq_empty,ch1_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_rdq_empty,ch1_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_timeout,ch1_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_2,reserved_2,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_bdq_empty,ch2_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_rdq_empty,ch2_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_timeout,ch2_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_1,reserved_1,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_bdq_empty,ch3_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_rdq_empty,ch3_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_timeout,ch3_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_0,reserved_0,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_mask_int1_mask,int1_mask,HI_CIPHER_INT1_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_MASK_OFFSET)
HI_SET_GET(hi_cipher_int1_mstatus_int1_mstatus,int1_mstatus,HI_CIPHER_INT1_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_MSTATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bdq_full,ch4_bdq_full,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_rdq_full,ch4_rdq_full,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_nbd_done,ch4_nbd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bd_done,ch4_bd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_allbd_done,ch4_allbd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bdq_empty,ch4_bdq_empty,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_rdq_empty,ch4_rdq_empty,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_timeout,ch4_timeout,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_reserved,reserved,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_mask_reserved,reserved,HI_CIPHER_INT2_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_MASK_OFFSET)
HI_SET_GET(hi_cipher_int2_mstatus_reserved,reserved,HI_CIPHER_INT2_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_MSTATUS_OFFSET)
HI_SET_GET(hi_ch0_rdq_baddr_base_addr_l,base_addr_l,HI_CH0_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_baddr_base_addr,base_addr,HI_CH0_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_size_size,size,HI_CH0_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_rdq_size_reserved,reserved,HI_CH0_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_wptr,wptr,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_reserved_1,reserved_1,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_rptr,rptr,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_reserved_0,reserved_0,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_raddr_raddr,raddr,HI_CH0_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_waddr_waddr,waddr,HI_CH0_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_baddr_base_addr_l,base_addr_l,HI_CH1_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_baddr_base_addr,base_addr,HI_CH1_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_size_size,size,HI_CH1_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_rdq_size_reserved,reserved,HI_CH1_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_wptr,wptr,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_reserved_1,reserved_1,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_rptr,rptr,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_reserved_0,reserved_0,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_raddr_raddr,raddr,HI_CH1_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_waddr_waddr,waddr,HI_CH1_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_baddr_base_addr_l,base_addr_l,HI_CH2_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_baddr_base_addr,base_addr,HI_CH2_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_size_size,size,HI_CH2_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_rdq_size_reserved,reserved,HI_CH2_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_wptr,wptr,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_reserved_1,reserved_1,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_rptr,rptr,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_reserved_0,reserved_0,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_raddr_raddr,raddr,HI_CH2_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_waddr_waddr,waddr,HI_CH2_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_baddr_base_addr_l,base_addr_l,HI_CH3_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_baddr_base_addr,base_addr,HI_CH3_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_size_size,size,HI_CH3_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_rdq_size_reserved,reserved,HI_CH3_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_wptr,wptr,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_reserved_1,reserved_1,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_rptr,rptr,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_reserved_0,reserved_0,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_raddr_raddr,raddr,HI_CH3_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_waddr_waddr,waddr,HI_CH3_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_baddr_base_addr_l,base_addr_l,HI_CH4_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_baddr_base_addr,base_addr,HI_CH4_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_size_size,size,HI_CH4_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_rdq_size_reserved,reserved,HI_CH4_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_wptr,wptr,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_reserved_1,reserved_1,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_rptr,rptr,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_reserved_0,reserved_0,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_raddr_raddr,raddr,HI_CH4_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_waddr_waddr,waddr,HI_CH4_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_key_ram_key,key,HI_KEY_RAM_T,HI_CIPHER_BASE_ADDR, HI_KEY_RAM_OFFSET)
#endif
#endif // __HI_CIPHER_H__

