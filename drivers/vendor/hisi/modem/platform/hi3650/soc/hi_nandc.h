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

#ifndef __HI_NANDC_H__
#define __HI_NANDC_H__

/*
 * Project: hi
 * Module : nandc
 */
#include <hi_base.h>
#include <bsp_memmap.h>



/********************************************************************************/
/*    nandc �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_NFC_CON_OFFSET                                 (0x0) /* NANDC���üĴ����� */
#define    HI_NFC_PWIDTH_OFFSET                              (0x4) /* ��д���������üĴ����� */
#define    HI_NFC_OPIDLE_OFFSET                              (0x8) /* ����������üĴ����� */
#define    HI_NFC_CMD_OFFSET                                 (0xC) /* ���������üĴ����� */
#define    HI_NFC_ADDRL_OFFSET                               (0x10) /* ��λ��ַ���üĴ����� */
#define    HI_NFC_ADDRH_OFFSET                               (0x14) /* ��λ��ַ���üĴ����� */
#define    HI_NFC_DATA_NUM_OFFSET                            (0x18) /* ��д������Ŀ���üĴ����� */
#define    HI_NFC_OP_OFFSET                                  (0x1C) /* �����Ĵ����� */
#define    HI_NFC_STATUS_OFFSET                              (0x20) /* ״̬�Ĵ����� */
#define    HI_NFC_INTEN_OFFSET                               (0x24) /* �ж�ʹ�ܼĴ����� */
#define    HI_NFC_INTS_OFFSET                                (0x28) /* �ж�״̬�Ĵ����� */
#define    HI_NFC_INTCLR_OFFSET                              (0x2C) /* �ж�����Ĵ����� */
#define    HI_NFC_LOCK_OFFSET                                (0x30) /* ����ַ���üĴ����� */
#define    HI_NFC_LOCK_SA0_OFFSET                            (0x34) /* ����ʼ��ַ0���üĴ����� */
#define    HI_NFC_LOCK_SA1_OFFSET                            (0x38) /* ����ʼ��ַ1���üĴ����� */
#define    HI_NFC_LOCK_SA2_OFFSET                            (0x3C) /* ����ʼ��ַ2���üĴ����� */
#define    HI_NFC_LOCK_SA3_OFFSET                            (0x40) /* ����ʼ��ַ3���üĴ����� */
#define    HI_NFC_LOCK_EA0_OFFSET                            (0x44) /* ��������ַ0���üĴ����� */
#define    HI_NFC_LOCK_EA1_OFFSET                            (0x48) /* ��������ַ1���üĴ����� */
#define    HI_NFC_LOCK_EA2_OFFSET                            (0x4C) /* ��������ַ2���üĴ����� */
#define    HI_NFC_LOCK_EA3_OFFSET                            (0x50) /* ��������ַ3���üĴ����� */
#define    HI_NFC_EXPCMD_OFFSET                              (0x54) /* ��չҳ����Ĵ����� */
#define    HI_NFC_EXBCMD_OFFSET                              (0x58) /* ��չ������Ĵ����� */
#define    HI_NFC_ECC_TEST_OFFSET                            (0x5C) /* ECC���ԼĴ����� */
#define    HI_NFC_DMA_CTRL_OFFSET                            (0x60) /* DMA���ƼĴ����� */
#define    HI_NFC_BADDR_D_OFFSET                             (0x64) /* �����������Ļ���ַ�Ĵ����� */
#define    HI_NFC_BADDR_OOB_OFFSET                           (0x68) /* ����OOB���Ļ���ַ�Ĵ����� */
#define    HI_NFC_DMA_LEN_OFFSET                             (0x6C) /* ���ͳ��ȼĴ����� */
#define    HI_NFC_OP_PARA_OFFSET                             (0x70) /* ���������Ĵ����� */
#define    HI_NFC_VERSION_OFFSET                             (0x74) /* nandc�汾�Ĵ����� */
#define    HI_NFC_SEGMENT_ID_OFFSET                          (0x84) /* DMA��дnandflash�����ݶ�ID�Ĵ����� */
#define    HI_NFC_FIFO_EMPTY_OFFSET                          (0x90) /* �ڲ�fifo״̬�Ĵ����� */
#define    HI_NFC_BOOT_SET_OFFSET                            (0x94) /* boot�����趨�Ĵ����� */
#define    HI_NF_LP_CTRL_OFFSET                              (0x9C) /* nandc �ĵ͹��Ŀ��ƼĴ����� */
#define    HI_NFC_ERR_NUM0_BUF0_OFFSET                       (0xA0) /* nandflash ��һ��buffer����ͳ�ƼĴ���0 */
#define    HI_NFC_ERR_NUM1_BUF0_OFFSET                       (0xA4) /* nandflash ��һ��buffer����ͳ�ƼĴ���1 */
#define    HI_NFC_ERR_NUM0_BUF1_OFFSET                       (0xA8) /* nandflash �ڶ���buffer����ͳ�ƼĴ���0 */
#define    HI_NFC_ERR_NUM1_BUF1_OFFSET                       (0xAC) /* nandflash �ڶ���buffer����ͳ�ƼĴ���1 */
#define    HI_NF_RB_MODE_OFFSET                              (0xB0) /* nandflash ��ready_busyģʽ�Ĵ����� */
#define    HI_NFC_BADDR_D1_OFFSET                            (0xB4) /* �����������Ļ���ַ�Ĵ���1�� */
#define    HI_NFC_BADDR_D2_OFFSET                            (0xB8) /* �����������Ļ���ַ�Ĵ���2�� */
#define    HI_NFC_BADDR_D3_OFFSET                            (0xBC) /* �����������Ļ���ַ�Ĵ���3�� */
#define    HI_NFC_BOOT_CFG_OFFSET                            (0xC4) /* nandflash ��boot���üĴ��� */
#define    HI_NFC_OOB_SEL_OFFSET                             (0xC8) /* 16bit ECC��OOB������ѡ��Ĵ��� */
#define    HI_NFC_MEM_CTRL_OFFSET                            (0xCC) /* ����mem���� */
#define    HI_NFC_SYNC_TIMING_OFFSET                         (0xD0) /* ͬ��NAND��дʱ����� */
#define    HI_NFC_DLL_CONTROL_OFFSET                         (0xD4) /* DLLģ��������Ϣ */
#define    HI_NFC_DLL_STATUS_OFFSET                          (0xD8) /* DLLģ��״̬��Ϣ */

/********************************************************************************/
/*    nandc �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    op_mode                    : 1; /* [0..0] NANDC����ģʽ���á�0��NANDC����bootģʽ��1��NANDC����normalģʽ�� */
        unsigned int    pagesize                   : 3; /* [3..1] NAND Flash��ҳ��С��000��������001��2KByte��010��4KByte��011��8KByte��100��16KByte��101~111����������λֵ�ɹܽ�NFC_PAGE_SIZE������ */
        unsigned int    bus_width                  : 1; /* [4..4] NAND Flash�������߿�ȡ�0��8bit��1��16bit����λֵ�ɹܽ�NFC_BUS_WIDE������ */
        unsigned int    reserved_2                 : 2; /* [6..5] ������ */
        unsigned int    cs_ctrl                    : 1; /* [7..7] Ƭѡ���ơ�0����NAND FlashΪbusyʱ������Ƭѡ�ź�Ϊ0��1����NAND FlashΪbusyʱ����Ƭѡ�ź���λ1����ģʽ��ӦNAND Flash��cs do not careģʽ�� */
        unsigned int    rb_sel                     : 1; /* [8..8] ����Ӷ��NANDFlash���������Ƭѡ��ʱ��Ч��0��NAND Flash��������ͬһ��ready/busy�źţ�1��NAND Flash����ʹ�ø��Զ�����ready/busy�źš���ֻ��һ��NAND Flash����ʱ��ֻ��Ƭѡ�ź�ce0��ready_busy0�� */
        unsigned int    ecc_type                   : 3; /* [11..9] ECCģʽѡ��000����ECC��001��1bit ģʽ��010��4bitģʽ��011��16bitģʽ��100��24bits ģʽ for 1KB��101��40bitsģʽ��110: 64bitsģʽ��111����������λֵ�ɹܽ�NFC_ECC_TYPE������ */
        unsigned int    reserved_1                 : 1; /* [12..12] ������ */
        unsigned int    randomizer_en              : 1; /* [13..13] randomizer���ܡ�0������randomizer���ܣ�1����randomizer���ܡ� */
        unsigned int    nf_mode                    : 2; /* [15..14] NAND Flash�ӿ�����ѡ��00���첽nand�ӿڣ�01��toggle nand�ӿڣ�10��onfi2.3 nand�ӿڣ�11��onfi3.0 nand�ӿڡ� */
        unsigned int    reserved_0                 : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_CON_T;    /* NANDC���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    w_lcnt                     : 4; /* [3..0] NAND Flashд�źŵ͵�ƽ��ȡ�0x1��0xF��2��16���ӿ�ʱ�����ڡ� */
        unsigned int    r_lcnt                     : 4; /* [7..4] NAND Flash���źŵ͵�ƽ��ȡ�0x2��0xF��3��16���ӿ�ʱ�����ڡ� */
        unsigned int    rw_hcnt                    : 4; /* [11..8] NAND Flash��/д�źŸߵ�ƽ��ȡ�0x1��0xF��2��16���ӿ�ʱ�����ڡ� */
        unsigned int    reserved                   : 20; /* [31..12] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_PWIDTH_T;    /* ��д���������üĴ����� */

typedef union
{
    struct
    {
        unsigned int    wait_ready_wait            : 4; /* [3..0] NAND Flash��ready�źű��֮����ʱһ��ʱ��,֮����ܷ������źŶ����ݡ���ʱ��������Ϊ��frb_idle*8�� */
        unsigned int    cmd2_wait                  : 4; /* [7..4] ������command2֮��ĵȴ���������0000��1111��1��16���ӿ�ʱ�����ڡ� */
        unsigned int    rsv                        : 4; /* [11..8] ������ */
        unsigned int    addr_wait                  : 4; /* [15..12] ������address֮��ĵȴ���������0000��1111������ֵ����ʱ�Ľӿ�ʱ��������Ϊ��addr_wait*8�� */
        unsigned int    cmd1_wait                  : 4; /* [19..16] ������command1֮��ĵȴ���������0000��1111��1��16���ӿ�ʱ�����ڡ� */
        unsigned int    frb_wait                   : 4; /* [23..20] ������д���������ʱһ��ʱ�䣬Ȼ���ټ��ready�ź��Ƿ��Ϊ�ߵ�ƽ����ʱ�Ľӿ�ʱ��������Ϊ��frb_wait*8�� */
        unsigned int    reserved                   : 8; /* [31..24] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_OPIDLE_T;    /* ����������üĴ����� */

typedef union
{
    struct
    {
        unsigned int    cmd1                       : 8; /* [7..0] Controller����NAND Flash�ĵ�1����� */
        unsigned int    cmd2                       : 8; /* [15..8] Controller����NAND Flash�ĵ�2����� */
        unsigned int    read_status_cmd            : 8; /* [23..16] Read status������ */
        unsigned int    reserved                   : 8; /* [31..24] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_CMD_T;    /* ���������üĴ����� */

typedef union
{
    struct
    {
        unsigned int    addr_l                     : 32; /* [31..0] NAND Flash��32bit��ַ�� */
    } bits;
    unsigned int    u32;
}HI_NFC_ADDRL_T;    /* ��λ��ַ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    addr_h                     : 8; /* [7..0] NAND Flash��8bit��ַ�� */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_ADDRH_T;    /* ��λ��ַ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    nfc_data_num               : 14; /* [13..0] ����NANDC�����д�����ݸ��������9120�ֽڡ�ֻ��ecc_type����00ʱ��Ч�� */
        unsigned int    reserved                   : 18; /* [31..14] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_DATA_NUM_T;    /* ��д������Ŀ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    read_status_en             : 1; /* [0..0] �ñ�־Ϊ1ʱ��ʹ����NAND������status��0x70�������NAND Flash��ȡ״̬���ݣ����ص�����д��NANDC״̬�Ĵ�����nf_status���У�����д���ڲ�buffer����0����ֹ��1��ʹ�ܡ� */
        unsigned int    read_data_en               : 1; /* [1..1] ������״̬������NAND Flash������ʹ�ܡ�read_data_en��write_data_en����ͬʱΪ1��0����ֹ��1��ʹ�ܡ� */
        unsigned int    wait_ready_en              : 1; /* [2..2] �ȴ�ready/busy�źű��ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    cmd2_en                    : 1; /* [3..3] ��command2����ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    write_data_en              : 1; /* [4..4] ��NAND Flashд����ʹ�ܡ�read_data_en��write_data_en ����ͬʱΪ1��0����ֹ��1��ʹ�ܡ� */
        unsigned int    addr_en                    : 1; /* [5..5] ��NANDд������ַʹ�� �� 0����ֹ��1��ʹ�ܡ� */
        unsigned int    cmd1_en                    : 1; /* [6..6] ��command1����ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    nf_cs                      : 2; /* [8..7] ѡ�������NAND Flash������00��cs0��  01��cs1��10��cs2��  11��cs3�� */
        unsigned int    address_cycles             : 3; /* [11..9] ����NAND Flash�ĵ�ַ�������� */
        unsigned int    read_id_en                 : 1; /* [12..12] ����toggle nand���ñ�־Ϊһָʾ�������ж�״̬�Ĵ���������0���Ƕ�ID������1����ID������ */
        unsigned int    rw_reg_en                  : 1; /* [13..13] ����ͬ��nand���ж�д�Ĵ���������0����д���ݲ�����1����д�Ĵ��������� */
        unsigned int    reserved                   : 18; /* [31..14] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_OP_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    nfc_ready                  : 1; /* [0..0] ָʾ����������һ�β�����ǰ������״̬��0��controller���ڽ��в�����1��������ɣ����Խ�����һ�������дoperation�Ĵ�������nandc����ʱ����λ�Զ����㡣 */
        unsigned int    nf0_ready                  : 1; /* [1..1] Ƭѡ0��Ӧ��nand������ready/busy�ź�״̬������������flash������ʹ�ø��Զ�����ready_busy�ź�ʱ��Ч����ΪĬ�������nandFlash��������ͬһ��ready/busy�źţ���bit��λֵΪ0�� */
        unsigned int    nf1_ready                  : 1; /* [2..2] Ƭѡ1��Ӧ��nand������ready/busy�ź�״̬������������flash������ʹ�ø��Զ�����ready_busy�ź�ʱ��Ч����ΪĬ�������nandFlash��������ͬһ��ready/busy�źţ���bit��λֵΪ0�� */
        unsigned int    nf2_ready                  : 1; /* [3..3] Ƭѡ2��Ӧ��nand������ready/busy�ź�״̬������������flash������ʹ�ø��Զ�����ready_busy�ź�ʱ��Ч����ΪĬ�������nandFlash��������ͬһ��ready/busy�źţ���bit��λֵΪ0�� */
        unsigned int    nf3_ready                  : 1; /* [4..4] Ƭѡ3��Ӧ��nand������ready/busy�ź�״̬������������flash������ʹ�ø��Զ�����ready_busy�ź�ʱ��Ч����ΪĬ�������nandFlash��������ͬһ��ready/busy�źţ���bit��λֵΪ0�� */
        unsigned int    reserved_1                 : 3; /* [7..5] ������ */
        unsigned int    nf_status                  : 8; /* [15..8] ��Flash���ص�NAND Flash��status���ݡ�ֻ��operation�Ĵ�����read_status��־Ϊ1���ҸüĴ�����nandc_ready��־Ϊ1ʱ��Ч�� */
        unsigned int    nfc_ecc_type               : 3; /* [18..16] NAND�������ڲ�ʹ�õ�ecc������Ϣ����ȡ������ֵ�����nfc_con�Ĵ���ecc_type��ͬ�� */
        unsigned int    nfc_randomizer_en          : 1; /* [19..19] NAND�������ڲ�ʹ��randomizer״̬��0����ֹ��1��ʹ�ܡ� */
        unsigned int    reserved_0                 : 12; /* [31..20] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_STATUS_T;    /* ״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    op_done_en                 : 1; /* [0..0] Nfc���β��������жϡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    cs0_done_en                : 1; /* [1..1] Ƭѡcs0��Ӧ��ready busy�ź��ɵͱ�ߣ������жϡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    cs1_done_en                : 1; /* [2..2] Ƭѡcs1��Ӧ��ready busy�ź��ɵͱ�ߣ������жϡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    cs2_done_en                : 1; /* [3..3] Ƭѡcs2��Ӧ��ready busy�ź��ɵͱ�ߣ������жϡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    cs3_done_en                : 1; /* [4..4] Ƭѡcs3��Ӧ��ready busy�ź��ɵͱ�ߣ������жϡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    err_valid_en               : 1; /* [5..5] �ɾ����Ĵ��󣬲����жϡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    err_invalid_en             : 1; /* [6..6] ���ɾ������󣬲����жϡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    ahb_op_en                  : 1; /* [7..7] Nfc��дflash�����ڼ䣬cpu��дnfc buffer�����ж�ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    wr_lock_en                 : 1; /* [8..8] ��lock��ַ����д���������ж�ʹ��0����ֹ��1��ʹ�ܡ� */
        unsigned int    dma_done_en                : 1; /* [9..9] dma��������ж�ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    dma_err_en                 : 1; /* [10..10] dma�������߳��ִ����ж�ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    reserved                   : 21; /* [31..11] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_INTEN_T;    /* �ж�ʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    op_done                    : 1; /* [0..0] controller���β��������жϡ�дoperation�Ĵ����󣬸ñ�־�Զ����㡣0�����жϣ�1�����жϡ� */
        unsigned int    cs0_done                   : 1; /* [1..1] Ƭѡcs0��Ӧ�� ready busy�ź��ɵͱ�ߣ������жϡ����������flash������ͬʱ��������ʹ�ø��Զ�����ready_busy�ź�ʱ��Ч�����򣬸�bitһֱ����Ϊ0��0�����жϣ�1�����жϡ� */
        unsigned int    cs1_done                   : 1; /* [2..2] Ƭѡcs1��Ӧ�� ready busy�ź��ɵͱ�ߣ������жϡ����������flash������ͬʱ��������ʹ�ø��Զ�����ready_busy�ź�ʱ��Ч�����򣬸�bitһֱ����Ϊ0��0�����жϣ�1�����жϡ� */
        unsigned int    cs2_done                   : 1; /* [3..3] Ƭѡcs2��Ӧ�� ready busy�ź��ɵͱ�ߣ������жϡ����������flash������ͬʱ��������ʹ�ø��Զ�����ready_busy�ź�ʱ��Ч�����򣬸�bitһֱ����Ϊ0��0�����жϣ�1�����жϡ� */
        unsigned int    cs3_done                   : 1; /* [4..4] Ƭѡcs3��Ӧ�� ready busy�ź��ɵͱ�ߣ������жϡ����������flash������ͬʱ��������ʹ�ø��Զ�����ready_busy�ź�ʱ��Ч�����򣬸�bitһֱ����Ϊ0��0�����жϣ�1�����жϡ� */
        unsigned int    err_valid                  : 1; /* [5..5] �ɾ����Ĵ���1bit����ģʽ�£�У��512byte�����г���1it���󣬲����жϡ�4bit����ģʽ�£�eccУ��1024byte�����г���1��8bit���󣬲����жϡ�8bit����ģʽ�£�У��1024byte���ݳ���1 ��16bit���ϴ��󣬲����жϡ�24bit����ģʽ�£�У��1024byte�����г���1��24bit���󣬲����жϡ�40bit����ģʽ�£�У��1024byte�����г���1��40bit���󣬲����жϡ�64bit����ģʽ�£�У��1024byte�����г���1��64bit���󣬲����жϡ�0�����жϣ�1�����жϡ� */
        unsigned int    err_invalid                : 1; /* [6..6] ���ɾ����Ĵ���1bit����ģʽ�£�У��512byte�����г���2bit���ϴ��󣬲����жϡ�4bit����ģʽ�£�У��1024byte�����г���8bit���ϴ��󣬲����жϡ�8bit����ģʽ�£�У��1024byte�����г���16bit���ϴ��󣬲����жϡ�24bit����ģʽ�£�У��1024byte�����г���24bit���ϴ��󣬲����жϡ�40bit����ģʽ�£�У��1024byte�����г���40bit���ϴ��󣬲����жϡ�64bit����ģʽ�£�У��1024byte�����г���64bit���ϴ��󣬲����жϡ�0�����жϣ�1�����жϡ� */
        unsigned int    ahb_op_err                 : 1; /* [7..7] Nfc��flash�������ݲ����ڼ䣬cpu��дnfc buffer��0�����жϣ�1�����жϡ� */
        unsigned int    wr_lock_err                : 1; /* [8..8] ��lock��ַ����д������0�����жϣ�1�����жϡ� */
        unsigned int    dma_done                   : 1; /* [9..9] dma��������жϡ�0�����жϣ�1�����жϡ� */
        unsigned int    dma_err                    : 1; /* [10..10] dma�������߳��ִ����жϡ�0�����жϣ�1�����жϡ� */
        unsigned int    reserved                   : 21; /* [31..11] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_INTS_T;    /* �ж�״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    op_done_clr                : 1; /* [0..0] ���op_done�жϣ�д1����� */
        unsigned int    cs0_done_clr               : 1; /* [1..1] ���cs0_done�жϣ�д1����� */
        unsigned int    cs1_done_clr               : 1; /* [2..2] ���cs1_done�жϣ�д1����� */
        unsigned int    cs2_done_clr               : 1; /* [3..3] ���cs2_done�жϣ�д1����� */
        unsigned int    cs3_done_clr               : 1; /* [4..4] ���cs3_done�жϣ�д1����� */
        unsigned int    err_valid_clr              : 1; /* [5..5] ���err_valid�жϣ�д1����� */
        unsigned int    err_invalid_clr            : 1; /* [6..6] ���err_invalid�жϣ�д1����� */
        unsigned int    ahb_op_err_clr             : 1; /* [7..7] ���ahb_op_err �жϣ�д1����� */
        unsigned int    wr_lock_err_clr            : 1; /* [8..8] ���wr_lock_err�жϣ�д1����� */
        unsigned int    dma_done_clr               : 1; /* [9..9] ���dma_done��д1����� */
        unsigned int    dma_err_clr                : 1; /* [10..10] ���dma�������ߴ����жϣ�д1����� */
        unsigned int    reserved                   : 21; /* [31..11] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_INTCLR_T;    /* �ж�����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    lock_down                  : 1; /* [0..0] Flash lockģʽ��1��lock-downģʽ��һ����д1��ֻ��Ӳ��reset���ܶԸ�λд0��0��lockģʽ�� */
        unsigned int    global_lock_en             : 1; /* [1..1] Flashȫ��lockʹ�ܡ�1��ʹ�ܣ�0����ֹ�� */
        unsigned int    lock_en                    : 1; /* [2..2] Flash lockʹ�ܡ�1��ʹ�ܣ�0����ֹ�� */
        unsigned int    lock_excmd_en              : 1; /* [3..3] �����չд����������п�����ӵ���������Ա�����ַ����д����ʹ�ܡ�1��ʹ�ܣ�0����ֹ�� */
        unsigned int    reserved                   : 28; /* [31..4] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_T;    /* ����ַ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_lock_addr0           : 19; /* [18..0] �����׵�ַ0�����λ��Ӧflash row addr[5]�� */
        unsigned int    flash_lock_cs              : 2; /* [20..19] �����׵�ַ0��Ӧ��Ƭѡ��00��Ƭѡ0��01��Ƭѡ1��10��Ƭѡ2��11��Ƭѡ3�� */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_SA0_T;    /* ����ʼ��ַ0���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_lock_addr1           : 19; /* [18..0] �����׵�ַ1�����λ��Ӧflash row addr[5]�� */
        unsigned int    flash_lock_cs              : 2; /* [20..19] �����׵�ַ1��Ӧ��Ƭѡ��00��Ƭѡ0��01��Ƭѡ1��10��Ƭѡ2��11��Ƭѡ3�� */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_SA1_T;    /* ����ʼ��ַ1���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_lock_addr2           : 19; /* [18..0] �����׵�ַ2�����λ��Ӧflash row addr[5]�� */
        unsigned int    flash_lock_cs              : 2; /* [20..19] �����׵�ַ2��Ӧ��Ƭѡ��00��Ƭѡ0��01��Ƭѡ1��10��Ƭѡ2��11��Ƭѡ3�� */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_SA2_T;    /* ����ʼ��ַ2���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_lock_addr3           : 19; /* [18..0] �����׵�ַ3�����λ��Ӧflash row addr[5]�� */
        unsigned int    flash_lock_cs              : 2; /* [20..19] �����׵�ַ3��Ӧ��Ƭѡ��00��Ƭѡ0��01��Ƭѡ1��10��Ƭѡ2��11��Ƭѡ3�� */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_SA3_T;    /* ����ʼ��ַ3���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_lock_eaddr0          : 19; /* [18..0] ���������ַ0�����λ��Ӧflash row addr[5]�� */
        unsigned int    flash_lock_cs              : 2; /* [20..19] ���������ַ0��Ӧ��Ƭѡ��00��Ƭѡ0��01��Ƭѡ1��10��Ƭѡ2��11��Ƭѡ3�� */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_EA0_T;    /* ��������ַ0���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_lock_eaddr1          : 19; /* [18..0] ���������ַ1�����λ��Ӧflash row addr[5]�� */
        unsigned int    flash_lock_cs              : 2; /* [20..19] ���������ַ1��Ӧ��Ƭѡ��00��Ƭѡ0��01��Ƭѡ1��10��Ƭѡ2��11��Ƭѡ3�� */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_EA1_T;    /* ��������ַ1���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_lock_eaddr2          : 19; /* [18..0] ���������ַ2�����λ��Ӧflash row addr[5]�� */
        unsigned int    flash_lock_cs              : 2; /* [20..19] ���������ַ2��Ӧ��Ƭѡ��00��Ƭѡ0��01��Ƭѡ1��10��Ƭѡ2��11��Ƭѡ3�� */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_EA2_T;    /* ��������ַ2���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_lock_eaddr3          : 19; /* [18..0] ���������ַ3�����λ��Ӧflash row addr[5]�� */
        unsigned int    flash_lock_cs              : 2; /* [20..19] ���������ַ3��Ӧ��Ƭѡ��00��Ƭѡ001��Ƭѡ110��Ƭѡ211��Ƭѡ3 */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_EA3_T;    /* ��������ַ3���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    ex_pcmd0                   : 8; /* [7..0] Flash��չҳд��������0�� */
        unsigned int    ex_pcmd1                   : 8; /* [15..8] Flash��չҳд��������1�� */
        unsigned int    ex_pcmd2                   : 8; /* [23..16] Flash��չҳд��������2�� */
        unsigned int    ex_pcmd3                   : 8; /* [31..24] Flash��չҳд��������3 */
    } bits;
    unsigned int    u32;
}HI_NFC_EXPCMD_T;    /* ��չҳ����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ex_bcmd0                   : 8; /* [7..0] Flash��չ��д��������0�� */
        unsigned int    ex_bcmd1                   : 8; /* [15..8] Flash��չ��д��������1�� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_EXBCMD_T;    /* ��չ������Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    enc_only                   : 1; /* [0..0] ֻ����ʹ�ܡ���üĴ���λд1ʱ������ECC���룬����������дNAND Flash�����üĴ���λʱ������ֵ���壺1��ECC����������0�����ڱ���롣 */
        unsigned int    dec_only                   : 1; /* [1..1] ֻ����ʹ�ܡ���üĴ���λд1ʱ������ECC���룬����������дNAND Flash�����üĴ���λʱ������0�� */
        unsigned int    ecc_mask                   : 1; /* [2..2] ECC�������롣1��������eccУ��;�������дNANDFlash���ݽṹ�԰���ecc_type�ĸ�ʽ����ת����0����ecc_type��ֵ�����Ƿ����У��;��� */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    bb_err                     : 1; /* [4..4] ��Ϊbad_block��bootʧ�ܡ�0�����ǻ��飬��boot��1�����飬bootʧ�ܣ� */
        unsigned int    reserved_0                 : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_ECC_TEST_T;    /* ECC���ԼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dma_start                  : 1; /* [0..0] ����dma���������bitд1����DMA��������bit����Ϊ1��ֱ��dma�������������bitд0��Ч������dma�����󣬶���bit�������0����ʾdma���������� */
        unsigned int    dma_wr_en                  : 1; /* [1..1] DMA��дʹ�ܡ�0������1��д�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ������ */
        unsigned int    burst4_en                  : 1; /* [4..4] burst4ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    burst8_en                  : 1; /* [5..5] burst8ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    burst16_en                 : 1; /* [6..6] burst16ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    dma_addr_num               : 1; /* [7..7] ��ַ����0��5����ַ��1��4����ַ�� */
        unsigned int    dma_nf_cs                  : 2; /* [9..8] ѡ��DMA������NAND Flash������00��cs0��  01��cs1��10��cs2��  11��cs3�� */
        unsigned int    rsv                        : 1; /* [10..10] ������ */
        unsigned int    wr_cmd_disable             : 1; /* [11..11] ѡ��DMAд����ʱ���Ƿ񷢳�д���0��NANDC����������дNAND Flashʱ��1��NANDCֻ����д���ݵ�ʱ�򣬲�����д����ʱ��ֻ��DMAдNAND Flashʱ��Ч�� */
        unsigned int    dma_rd_oob                 : 1; /* [12..12] DMA������ʱ��ѡ����ֻ��OOB��������page����0��������page��1��ֻ��OOB������ */
        unsigned int    reserved_0                 : 19; /* [31..13] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_DMA_CTRL_T;    /* DMA���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    base_addr_d                : 32; /* [31..0] ��дDDR�������Ļ���ַ�� */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_D_T;    /* �����������Ļ���ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    base_addr_oob              : 32; /* [31..0] ��OOB�����ݵ�DDR����ַ�� */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_OOB_T;    /* ����OOB���Ļ���ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 16; /* [15..0] ������ */
        unsigned int    len_oob                    : 12; /* [27..16] DMAдnandflashʱOOB���ĳ���,��Ҫ����(4byte)���롣(ֻ��ECC0ģʽ����Ч,������ECCģʽ�£�oob�ĳ����ǹ̶��ģ� */
        unsigned int    reserved_0                 : 4; /* [31..28] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_DMA_LEN_T;    /* ���ͳ��ȼĴ����� */

typedef union
{
    struct
    {
        unsigned int    data_rw_en                 : 1; /* [0..0] NAND Flash��������дʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    oob_rw_en                  : 1; /* [1..1] NAND Flash��������дʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    data_edc_en                : 1; /* [2..2] У��ʹ�ܡ�0����ֹ��1��ʹ�ܡ����ģʽ�£�����ECC��ʹ�ܡ�������ģʽ�£�����У��ʹ�ܡ� */
        unsigned int    oob_edc_en                 : 1; /* [3..3] oob��У��ʹ�ܡ�0����ֹ��1��ʹ�ܡ����ģʽ�£���oob������ECC��ʹ�ܡ�������ģʽ�£���oob������У��ʹ�ܡ� */
        unsigned int    reserved                   : 28; /* [31..4] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_OP_PARA_T;    /* ���������Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    version                    : 12; /* [11..0] �汾�š� */
        unsigned int    reserved                   : 20; /* [31..12] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_VERSION_T;    /* nandc�汾�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    last_flag                  : 1; /* [0..0] �����ڲ�bufferһ�β���ֻ��8K������page sizeΪ16K��������ͨ���˼Ĵ�������ʾ�Ƿ��䵽���һ��8KB���ݡ�0:��ǰ��д�������һ��8K���ݶΡ�1:��ǰ��д�����һ��8K���ݶΡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_SEGMENT_ID_T;    /* DMA��дnandflash�����ݶ�ID�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    empty_dbg                  : 24; /* [23..0] �ڲ�FIFO��empty�ź�״̬�����������á� */
        unsigned int    reserved                   : 8; /* [31..24] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_FIFO_EMPTY_T;    /* �ڲ�fifo״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    block_size                 : 2; /* [1..0] Bootʱ��NAND Flash���������߿�ȡ�00��64 page��01��128page��10��256 page��11��512 page����λ���ֵ�ɹܽ�NFC_BLOCK_SIZE������ */
        unsigned int    addr_num                   : 1; /* [2..2] Bootʱ��NANDC����NAND Flash�����ĵ�ַ��Ŀ��0��4����ַ���ڣ�1��5����ַ���ڡ���λ���ֵ�ɹܽ�NFC_ADDR_NUM������ */
        unsigned int    rsv                        : 29; /* [31..3] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_BOOT_SET_T;    /* boot�����趨�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    clk_gate_en                : 1; /* [0..0] ʱ���ſ�ѡ��0��ʱ��ȫ��ʹ�ܡ�1������ecc_typeֵ���رղ�ʹ�õ�ģ��ʱ�ӡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_NF_LP_CTRL_T;    /* nandc �ĵ͹��Ŀ��ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    err_num0_buf0              : 32; /* [31..0] ����2KB��4KB��8KB��16KB pagesize��һ��buffer������ǰ4KB���ݴ���ͳ�ƼĴ�����bit[31:24]������KB���ݾ�����������ͳ�ƼĴ�����bit[23:16]������KB���ݾ�����������ͳ�ƼĴ�����bit[15:8]���ڶ�KB���ݾ�����������ͳ�ƼĴ�����bit[7:0]����һKB���ݾ�����������ͳ�ƼĴ����� */
    } bits;
    unsigned int    u32;
}HI_NFC_ERR_NUM0_BUF0_T;    /* nandflash ��һ��buffer����ͳ�ƼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    err_num1_buf0              : 32; /* [31..0] ����8KB��16KB pagesize��һ��buffer��������4KB���ݴ���ͳ�ƼĴ�����bit[31:24]���ڰ�KB���ݾ�����������ͳ�ƼĴ�����bit[23:16]������KB���ݾ�����������ͳ�ƼĴ�����bit[15:8]������KB���ݾ�����������ͳ�ƼĴ�����bit[7:0]������KB���ݾ�����������ͳ�ƼĴ����� */
    } bits;
    unsigned int    u32;
}HI_NFC_ERR_NUM1_BUF0_T;    /* nandflash ��һ��buffer����ͳ�ƼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    err_num0_buf1              : 32; /* [31..0] ����16KB pagesize���ڶ���buffer������������ͳ�ƼĴ���0��bit[31:24]������KB���ݾ�����������ͳ�ƼĴ�����bit[23:16]������KB���ݾ�����������ͳ�ƼĴ�����bit[15:8]���ڶ�KB���ݾ�����������ͳ�ƼĴ�����bit[7:0]����һKB���ݾ�����������ͳ�ƼĴ����� */
    } bits;
    unsigned int    u32;
}HI_NFC_ERR_NUM0_BUF1_T;    /* nandflash �ڶ���buffer����ͳ�ƼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    err_num1_buf1              : 32; /* [31..0] ����16KB pagesize���ڶ���buffer������������ͳ�ƼĴ���1��bit[31:24]���ڰ�KB���ݾ�����������ͳ�ƼĴ�����bit[23:16]������KB���ݾ�����������ͳ�ƼĴ�����bit[15:8]������KB���ݾ�����������ͳ�ƼĴ�����bit[7:0]������KB���ݾ�����������ͳ�ƼĴ����� */
    } bits;
    unsigned int    u32;
}HI_NFC_ERR_NUM1_BUF1_T;    /* nandflash �ڶ���buffer����ͳ�ƼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    status                     : 1; /* [0..0] ready_busyģʽ�Ĵ�����0����ͳ��ready�źţ�1��micron��enhanced clear nand�źš� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_NF_RB_MODE_T;    /* nandflash ��ready_busyģʽ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    base_addr_d1               : 32; /* [31..0] ��дDDR�������Ļ���ַһ�� */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_D1_T;    /* �����������Ļ���ַ�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    base_addr_d2               : 32; /* [31..0] ��дDDR�������Ļ���ַ���� */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_D2_T;    /* �����������Ļ���ַ�Ĵ���2�� */

typedef union
{
    struct
    {
        unsigned int    base_addr_d3               : 32; /* [31..0] ��дDDR�������Ļ���ַ���� */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_D3_T;    /* �����������Ļ���ַ�Ĵ���3�� */

typedef union
{
    struct
    {
        unsigned int    randomizer_pad             : 1; /* [0..0] Ӳ������ʱrandomizerʹ�������0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    page_size_pad              : 3; /* [3..1] NAND Flash��ҳ��С��000��������001��2KByte��010��4KByte��011��8KByte��100��16KByte��101~111����������λֵ�ɹܽ�NFC_PAGE_SIZE������ */
        unsigned int    ecc_type_pad               : 3; /* [6..4] ECCģʽѡ��000����ECC��001��1bit ģʽ��010��4bitģʽ��011��16bitģʽ��100��24bits ģʽ for 1KB��101��40bitsģʽ��110: 64bitsģʽ��111����������λֵ�ɹܽ�NFC_ECC_TYPE������ */
        unsigned int    block_size_pad             : 2; /* [8..7] Bootʱ��NAND Flash������block���С��00��64 page��01��128page��10��256 page��11��512 page����λ���ֵ�ɹܽ�NFC_BLOCK_SIZE������ */
        unsigned int    addr_num_pad               : 1; /* [9..9] ��ַ����0��4����ַ��1��5����ַ�� */
        unsigned int    bus_width_pad              : 1; /* [10..10] NAND Flash�������߿�ȡ�0��8bit��1��16bit����λֵ�ɹܽ�NFC_BUS_WIDE������ */
        unsigned int    sync_nand_pad              : 1; /* [11..11] �Ƿ�ͬ��������0���첽������1��ͬ�������� */
        unsigned int    reserved                   : 20; /* [31..12] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_BOOT_CFG_T;    /* nandflash ��boot���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    oob_len_sel                : 1; /* [0..0] ����8bit ECC��ѡ��OOB�����ȡ�0������2KB pagesize��OOB����Ϊ8byte������4KB pagesize�����OOB������Ϊ16byte��1��OOB������Ϊ32byte */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_OOB_SEL_T;    /* 16bit ECC��OOB������ѡ��Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    mem_ctrl                   : 5; /* [4..0] ����mem����EMA��EMAW�ܽ�ֵ��[4:1]������EMA�ܽ�ֵ��[0]]������EMAW�ܽ�ֵ�� */
        unsigned int    reserved                   : 27; /* [31..5] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_MEM_CTRL_T;    /* ����mem���� */

typedef union
{
    struct
    {
        unsigned int    rw_psth                    : 4; /* [3..0] toggle������д����dqs��Ч��nf_ce_n��Чʱ������0x0��0xF��1��16������ʱ�����ڡ� */
        unsigned int    post_wdqs                  : 4; /* [7..4] ������nf_dqs�󵼺�ʱ�䡣0x0��0xF��1��16������ʱ�����ڡ� */
        unsigned int    pre_wdqs                   : 4; /* [11..8] д����nf_dqsǰ��ʱ�䡣0x0��0xF��1��16������ʱ�����ڡ�Ҫ��������40ns�� */
        unsigned int    post_rdqs                  : 4; /* [15..12] toggle������nf_re_n�󵼺�ʱ�䡣onfi�����ݺ�dqs����������̬ʱ�䡣0x0��0xF��1��16������ʱ�����ڡ� */
        unsigned int    pre_rdqs                   : 4; /* [19..16] toggle������nf_re_nǰ��ʱ�䡣0x0��0xF��1��16������ʱ�����ڡ�Ҫ��������40ns�� */
        unsigned int    t_dqz                      : 4; /* [23..20] onfi2������dqs��Ч���ٴδ����ʱ������0x0��0xF��1��16������ʱ�����ڡ� */
        unsigned int    t_cad                      : 4; /* [27..24] onfi2������nf_ale��nf_cle����ǰ�ӳ�ʱ�䡣0x0��0xF��1��16������ʱ�����ڡ� */
        unsigned int    reserved                   : 4; /* [31..28] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_SYNC_TIMING_T;    /* ͬ��NAND��дʱ����� */

typedef union
{
    struct
    {
        unsigned int    dll_bypass                 : 1; /* [0..0] DLL��bypass״̬���ж��Ƿ�������ơ�0���������ദ��1��bypass�� */
        unsigned int    dll_stop                   : 1; /* [1..1] dll�Ƿ�ֹͣ����ο�ʱ�����ڡ�1��ʹ�ܣ�0����ֹ�� */
        unsigned int    dll_slave_en               : 1; /* [2..2] slave�Ƿ����master�仯ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    dll_mode                   : 1; /* [3..3] DLL����ģʽ���á�0����������ģʽ��1��Direct����ģʽ��Slave DLL����ʱ�����ɼĴ������õõ��� */
        unsigned int    dll_tune                   : 4; /* [7..4] ��������ǰɨ�����á����õ�tune[3]Ϊ1ʱ��ȥ tune[2:0]��Ϊ0ʱ���� tune[2:0] */
        unsigned int    dll_ssel                   : 8; /* [15..8] DLL����ʱ��������dllmode=1ʱ��Ч�� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_NFC_DLL_CONTROL_T;    /* DLLģ��������Ϣ */

typedef union
{
    struct
    {
        unsigned int    dll_ready                  : 1; /* [0..0] Slave DLL������ɡ�0��û��ɣ�1����ɡ� */
        unsigned int    dll_overflow               : 1; /* [1..1] DLL���ָʾ��0���������1������� */
        unsigned int    dll_lockrd                 : 1; /* [2..2] DLL����ָʾ��0��δ������1�������� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    mdly_tap                   : 8; /* [11..4] Master DLL����ʱ����״̬�� */
        unsigned int    reserved_0                 : 20; /* [31..12] ���� */
    } bits;
    unsigned int    u32;
}HI_NFC_DLL_STATUS_T;    /* DLLģ��״̬��Ϣ */


/********************************************************************************/
/*    nandc ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_nfc_con_op_mode,op_mode,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_pagesize,pagesize,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_bus_width,bus_width,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_2,reserved_2,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_cs_ctrl,cs_ctrl,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_rb_sel,rb_sel,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_ecc_type,ecc_type,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_1,reserved_1,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_randomizer_en,randomizer_en,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_nf_mode,nf_mode,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_0,reserved_0,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_pwidth_w_lcnt,w_lcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_r_lcnt,r_lcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_rw_hcnt,rw_hcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_reserved,reserved,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_opidle_wait_ready_wait,wait_ready_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_cmd2_wait,cmd2_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_rsv,rsv,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_addr_wait,addr_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_cmd1_wait,cmd1_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_frb_wait,frb_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_reserved,reserved,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_cmd_cmd1,cmd1,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_cmd2,cmd2,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_read_status_cmd,read_status_cmd,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_reserved,reserved,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_addrl_addr_l,addr_l,HI_NFC_ADDRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRL_OFFSET)
HI_SET_GET(hi_nfc_addrh_addr_h,addr_h,HI_NFC_ADDRH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRH_OFFSET)
HI_SET_GET(hi_nfc_addrh_reserved,reserved,HI_NFC_ADDRH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRH_OFFSET)
HI_SET_GET(hi_nfc_data_num_nfc_data_num,nfc_data_num,HI_NFC_DATA_NUM_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DATA_NUM_OFFSET)
HI_SET_GET(hi_nfc_data_num_reserved,reserved,HI_NFC_DATA_NUM_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DATA_NUM_OFFSET)
HI_SET_GET(hi_nfc_op_read_status_en,read_status_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_read_data_en,read_data_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_wait_ready_en,wait_ready_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_cmd2_en,cmd2_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_write_data_en,write_data_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_addr_en,addr_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_cmd1_en,cmd1_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_nf_cs,nf_cs,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_address_cycles,address_cycles,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_read_id_en,read_id_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_rw_reg_en,rw_reg_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_reserved,reserved,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_ready,nfc_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf0_ready,nf0_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf1_ready,nf1_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf2_ready,nf2_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf3_ready,nf3_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_reserved_1,reserved_1,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf_status,nf_status,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_ecc_type,nfc_ecc_type,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_randomizer_en,nfc_randomizer_en,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_reserved_0,reserved_0,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_inten_op_done_en,op_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs0_done_en,cs0_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs1_done_en,cs1_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs2_done_en,cs2_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs3_done_en,cs3_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_err_valid_en,err_valid_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_err_invalid_en,err_invalid_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_ahb_op_en,ahb_op_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_wr_lock_en,wr_lock_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_dma_done_en,dma_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_dma_err_en,dma_err_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_reserved,reserved,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_ints_op_done,op_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs0_done,cs0_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs1_done,cs1_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs2_done,cs2_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs3_done,cs3_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_err_valid,err_valid,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_err_invalid,err_invalid,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_ahb_op_err,ahb_op_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_wr_lock_err,wr_lock_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_dma_done,dma_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_dma_err,dma_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_reserved,reserved,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_intclr_op_done_clr,op_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs0_done_clr,cs0_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs1_done_clr,cs1_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs2_done_clr,cs2_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs3_done_clr,cs3_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_err_valid_clr,err_valid_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_err_invalid_clr,err_invalid_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_ahb_op_err_clr,ahb_op_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_wr_lock_err_clr,wr_lock_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_dma_done_clr,dma_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_dma_err_clr,dma_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_reserved,reserved,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_down,lock_down,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_global_lock_en,global_lock_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_en,lock_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_excmd_en,lock_excmd_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_reserved,reserved,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_flash_lock_addr0,flash_lock_addr0,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_reserved,reserved,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_flash_lock_addr1,flash_lock_addr1,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_reserved,reserved,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_flash_lock_addr2,flash_lock_addr2,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_reserved,reserved,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_flash_lock_addr3,flash_lock_addr3,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_reserved,reserved,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_flash_lock_eaddr0,flash_lock_eaddr0,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_reserved,reserved,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_flash_lock_eaddr1,flash_lock_eaddr1,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_reserved,reserved,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_flash_lock_eaddr2,flash_lock_eaddr2,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_reserved,reserved,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_flash_lock_eaddr3,flash_lock_eaddr3,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_reserved,reserved,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd0,ex_pcmd0,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd1,ex_pcmd1,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd2,ex_pcmd2,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd3,ex_pcmd3,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_ex_bcmd0,ex_bcmd0,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_ex_bcmd1,ex_bcmd1,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_reserved,reserved,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_enc_only,enc_only,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_dec_only,dec_only,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_ecc_mask,ecc_mask,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_reserved_1,reserved_1,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_bb_err,bb_err,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_reserved_0,reserved_0,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_start,dma_start,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_wr_en,dma_wr_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_reserved_1,reserved_1,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst4_en,burst4_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst8_en,burst8_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst16_en,burst16_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_addr_num,dma_addr_num,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_nf_cs,dma_nf_cs,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_rsv,rsv,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_wr_cmd_disable,wr_cmd_disable,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_rd_oob,dma_rd_oob,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_reserved_0,reserved_0,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_baddr_d_base_addr_d,base_addr_d,HI_NFC_BADDR_D_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D_OFFSET)
HI_SET_GET(hi_nfc_baddr_oob_base_addr_oob,base_addr_oob,HI_NFC_BADDR_OOB_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_OOB_OFFSET)
HI_SET_GET(hi_nfc_dma_len_reserved_1,reserved_1,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_dma_len_len_oob,len_oob,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_dma_len_reserved_0,reserved_0,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_op_para_data_rw_en,data_rw_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_oob_rw_en,oob_rw_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_data_edc_en,data_edc_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_oob_edc_en,oob_edc_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_reserved,reserved,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_version_version,version,HI_NFC_VERSION_T,HI_NANDC_REGBASE_ADDR, HI_NFC_VERSION_OFFSET)
HI_SET_GET(hi_nfc_version_reserved,reserved,HI_NFC_VERSION_T,HI_NANDC_REGBASE_ADDR, HI_NFC_VERSION_OFFSET)
HI_SET_GET(hi_nfc_segment_id_last_flag,last_flag,HI_NFC_SEGMENT_ID_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SEGMENT_ID_OFFSET)
HI_SET_GET(hi_nfc_segment_id_reserved,reserved,HI_NFC_SEGMENT_ID_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SEGMENT_ID_OFFSET)
HI_SET_GET(hi_nfc_fifo_empty_empty_dbg,empty_dbg,HI_NFC_FIFO_EMPTY_T,HI_NANDC_REGBASE_ADDR, HI_NFC_FIFO_EMPTY_OFFSET)
HI_SET_GET(hi_nfc_fifo_empty_reserved,reserved,HI_NFC_FIFO_EMPTY_T,HI_NANDC_REGBASE_ADDR, HI_NFC_FIFO_EMPTY_OFFSET)
HI_SET_GET(hi_nfc_boot_set_block_size,block_size,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nfc_boot_set_addr_num,addr_num,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nfc_boot_set_rsv,rsv,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nf_lp_ctrl_clk_gate_en,clk_gate_en,HI_NF_LP_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NF_LP_CTRL_OFFSET)
HI_SET_GET(hi_nf_lp_ctrl_reserved,reserved,HI_NF_LP_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NF_LP_CTRL_OFFSET)
HI_SET_GET(hi_nfc_err_num0_buf0_err_num0_buf0,err_num0_buf0,HI_NFC_ERR_NUM0_BUF0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM0_BUF0_OFFSET)
HI_SET_GET(hi_nfc_err_num1_buf0_err_num1_buf0,err_num1_buf0,HI_NFC_ERR_NUM1_BUF0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM1_BUF0_OFFSET)
HI_SET_GET(hi_nfc_err_num0_buf1_err_num0_buf1,err_num0_buf1,HI_NFC_ERR_NUM0_BUF1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM0_BUF1_OFFSET)
HI_SET_GET(hi_nfc_err_num1_buf1_err_num1_buf1,err_num1_buf1,HI_NFC_ERR_NUM1_BUF1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM1_BUF1_OFFSET)
HI_SET_GET(hi_nf_rb_mode_status,status,HI_NF_RB_MODE_T,HI_NANDC_REGBASE_ADDR, HI_NF_RB_MODE_OFFSET)
HI_SET_GET(hi_nf_rb_mode_reserved,reserved,HI_NF_RB_MODE_T,HI_NANDC_REGBASE_ADDR, HI_NF_RB_MODE_OFFSET)
HI_SET_GET(hi_nfc_baddr_d1_base_addr_d1,base_addr_d1,HI_NFC_BADDR_D1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D1_OFFSET)
HI_SET_GET(hi_nfc_baddr_d2_base_addr_d2,base_addr_d2,HI_NFC_BADDR_D2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D2_OFFSET)
HI_SET_GET(hi_nfc_baddr_d3_base_addr_d3,base_addr_d3,HI_NFC_BADDR_D3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D3_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_randomizer_pad,randomizer_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_page_size_pad,page_size_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_ecc_type_pad,ecc_type_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_block_size_pad,block_size_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_addr_num_pad,addr_num_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_bus_width_pad,bus_width_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_sync_nand_pad,sync_nand_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_reserved,reserved,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_oob_sel_oob_len_sel,oob_len_sel,HI_NFC_OOB_SEL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OOB_SEL_OFFSET)
HI_SET_GET(hi_nfc_oob_sel_reserved,reserved,HI_NFC_OOB_SEL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OOB_SEL_OFFSET)
HI_SET_GET(hi_nfc_mem_ctrl_mem_ctrl,mem_ctrl,HI_NFC_MEM_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_MEM_CTRL_OFFSET)
HI_SET_GET(hi_nfc_mem_ctrl_reserved,reserved,HI_NFC_MEM_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_MEM_CTRL_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_rw_psth,rw_psth,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_post_wdqs,post_wdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_pre_wdqs,pre_wdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_post_rdqs,post_rdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_pre_rdqs,pre_rdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_t_dqz,t_dqz,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_t_cad,t_cad,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_reserved,reserved,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_bypass,dll_bypass,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_stop,dll_stop,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_slave_en,dll_slave_en,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_mode,dll_mode,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_tune,dll_tune,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_ssel,dll_ssel,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_reserved,reserved,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_ready,dll_ready,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_overflow,dll_overflow,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_lockrd,dll_lockrd,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_reserved_1,reserved_1,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_mdly_tap,mdly_tap,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_reserved_0,reserved_0,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)

#endif // __HI_NANDC_H__

