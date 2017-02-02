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

#ifndef __HI6551_H__
#define __HI6551_H__

/*
 * Project: hi
 * Module : hi6551
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    hi6551 �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI6551_STATUS1_OFFSET                          (0x1) /* ״̬��־1�Ĵ����� */
#define    HI6551_STATUS2_OFFSET                          (0x2) /* ״̬��־2�Ĵ����� */
#define    HI6551_IRQ1_OFFSET                             (0x3) /* �ж�1�Ĵ����� */
#define    HI6551_IRQ2_OFFSET                             (0x4) /* �ж�2�Ĵ����� */
#define    HI6551_IRQ3_OFFSET                             (0x5) /* �ж�3�Ĵ����� */
#define    HI6551_IRQ4_OFFSET                             (0x6) /* �ж�4�Ĵ����� */
#define    HI6551_COUL_IRQ_OFFSET                         (0x7) /* ���ؼ��жϼĴ����� */
#define    HI6551_IRQ1_MASK_OFFSET                        (0x8) /* �ж�����1�Ĵ����� */
#define    HI6551_IRQ2_MASK_OFFSET                        (0x9) /* �ж�����2�Ĵ����� */
#define    HI6551_IRQ3_MASK_OFFSET                        (0xA) /* �ж�����3�Ĵ����� */
#define    HI6551_IRQ4_MASK_OFFSET                        (0xB) /* �ж�����4�Ĵ����� */
#define    HI6551_COUL_IRQ_MASK_OFFSET                    (0xC) /* ���ؼ��жϼĴ����� */
#define    HI6551_SCP_RECORD1_OFFSET                      (0xD) /* ��·������¼1�Ĵ����� */
#define    HI6551_OCP_RECORD1_OFFSET                      (0xE) /* ����������¼1�Ĵ����� */
#define    HI6551_OCP_RECORD2_OFFSET                      (0xF) /* ����������¼2�Ĵ����� */
#define    HI6551_OCP_RECORD3_OFFSET                      (0x10) /* ����������¼3�Ĵ����� */
#define    HI6551_OCP_RECORD4_OFFSET                      (0x11) /* ����������¼4�Ĵ����� */
#define    HI6551_OCP_RECORD5_OFFSET                      (0x12) /* ����������¼5�Ĵ����� */
#define    HI6551_OCP_RECORD6_OFFSET                      (0x13) /* ����������¼6�Ĵ����� */
#define    HI6551_OCP_RECORD7_OFFSET                      (0x14) /* ����������¼7�Ĵ����� */
#define    HI6551_NP_IRQ1_RECORD_OFFSET                   (0x15) /* �ж�1���µ��¼�Ĵ����� */
#define    HI6551_NP_IRQ2_RECORD_OFFSET                   (0x16) /* �ж�2���µ��¼�Ĵ����� */
#define    HI6551_NP_IRQ3_RECORD_OFFSET                   (0x17) /* �ж�3���µ��¼�Ĵ����� */
#define    HI6551_NP_SCP_RECORD1_OFFSET                   (0x18) /* ��·�������µ��¼1�Ĵ����� */
#define    HI6551_NP_OCP_RECORD1_OFFSET                   (0x19) /* �����������µ��¼1�Ĵ����� */
#define    HI6551_NP_OCP_RECORD2_OFFSET                   (0x1A) /* �����������µ��¼2�Ĵ����� */
#define    HI6551_NP_OCP_RECORD3_OFFSET                   (0x1B) /* �����������µ��¼3�Ĵ����� */
#define    HI6551_NP_OCP_RECORD4_OFFSET                   (0x1C) /* �����������µ��¼4�Ĵ����� */
#define    HI6551_NP_OCP_RECORD5_OFFSET                   (0x1D) /* �����������µ��¼5�Ĵ����� */
#define    HI6551_NP_OCP_RECORD6_OFFSET                   (0x1E) /* �����������µ��¼6�Ĵ����� */
#define    HI6551_NP_OCP_RECORD7_OFFSET                   (0x1F) /* �����������µ��¼7�Ĵ����� */
#define    HI6551_OCP_DEB_OFFSET                          (0x20) /* OCPȥ�������ڼĴ����� */
#define    HI6551_ONOFF8_OFFSET                           (0x21) /* ���ؿ���8�Ĵ����� */
#define    HI6551_OCP_SCP_MOD_CTRL1_OFFSET                (0x22) /* BUCK0-3�����Ͷ�·����ģʽ���ƼĴ����� */
#define    HI6551_OCP_SCP_MOD_CTRL2_OFFSET                (0x23) /* BUCK4-7�����Ͷ�·����ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL3_OFFSET                    (0x24) /* LDO1-4��������ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL4_OFFSET                    (0x25) /* LDO5-8��������ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL5_OFFSET                    (0x26) /* LDO9-12��������ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL6_OFFSET                    (0x27) /* LDO13-16��������ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL7_OFFSET                    (0x28) /* LDO17-20��������ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL8_OFFSET                    (0x29) /* LDO21-ldo23��������ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL9_OFFSET                    (0x2A) /* LVS2-5��������ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL10_OFFSET                   (0x2B) /* LVS2-5��������ģʽ���ƼĴ����� */
#define    HI6551_OCP_MOD_CTRL11_OFFSET                   (0x2C) /* LVS9-10,BOOST��������ģʽ���ƼĴ����� */
#define    HI6551_ENABLE1_OFFSET                          (0x2D) /* ��Դģ��ʹ��1�Ĵ����� */
#define    HI6551_DISABLE1_OFFSET                         (0x2E) /* ��Դģ��ر�1�Ĵ����� */
#define    HI6551_ONOFF_STATUS1_OFFSET                    (0x2F) /* ��Դģ�鿪��״̬1�Ĵ����� */
#define    HI6551_ENABLE2_OFFSET                          (0x30) /* ��Դģ��ʹ��2�Ĵ����� */
#define    HI6551_DISABLE2_OFFSET                         (0x31) /* ��Դģ��ر�2�Ĵ����� */
#define    HI6551_ONOFF_STATUS2_OFFSET                    (0x32) /* ��Դģ�鿪��״̬2�Ĵ����� */
#define    HI6551_ENABLE3_OFFSET                          (0x33) /* ��Դģ��ʹ��3�Ĵ����� */
#define    HI6551_DISABLE3_OFFSET                         (0x34) /* ��Դģ��ر�3�Ĵ����� */
#define    HI6551_ONOFF_STATUS3_OFFSET                    (0x35) /* ��Դģ�鿪��״̬3�Ĵ����� */
#define    HI6551_ENABLE4_OFFSET                          (0x36) /* ��Դģ��ʹ��4�Ĵ����� */
#define    HI6551_DISABLE4_OFFSET                         (0x37) /* ��Դģ��ر�4�Ĵ����� */
#define    HI6551_ONOFF_STATUS4_OFFSET                    (0x38) /* ��Դģ�鿪��״̬4�Ĵ����� */
#define    HI6551_ENABLE5_OFFSET                          (0x39) /* ��Դģ��ʹ��5�Ĵ����� */
#define    HI6551_DISABLE5_OFFSET                         (0x3A) /* ��Դģ��ر�5�Ĵ����� */
#define    HI6551_ONOFF_STATUS5_OFFSET                    (0x3B) /* ��Դģ�鿪��״̬5�Ĵ����� */
#define    HI6551_ENABLE6_OFFSET                          (0x3C) /* ��Դģ��ʹ��6�Ĵ����� */
#define    HI6551_DISABLE6_OFFSET                         (0x3D) /* ��Դģ��ر�6�Ĵ����� */
#define    HI6551_ONOFF_STATUS6_OFFSET                    (0x3E) /* ��Դģ�鿪��״̬6�Ĵ����� */
#define    HI6551_ENABLE7_OFFSET                          (0x3F) /* ��Դģ��ʹ��7�Ĵ����� */
#define    HI6551_SIMCARD_EN_OFFSET                       (0x40) /* SIM��ʹ�ܼĴ����� */
#define    HI6551_SIM0_CFG_OFFSET                         (0x41) /* SIM��0���üĴ����� */
#define    HI6551_SIM1_CFG_OFFSET                         (0x42) /* SIM��1���üĴ����� */
#define    HI6551_SIM_DEB_OFFSET                          (0x43) /* SIM���ж�ȥ���ĵ��ڼĴ����� */
#define    HI6551_ECO_MOD_CFG1_OFFSET                     (0x44) /* ��Դģ���Ƿ����PMU����ECOģʽ����1�Ĵ����� */
#define    HI6551_ECO_MOD_CFG2_OFFSET                     (0x45) /* ��Դģ���Ƿ����PMU����ECOģʽ����2�Ĵ����� */
#define    HI6551_ECO_MOD_CFG3_OFFSET                     (0x46) /* ��Դ�Ƿ�ǿ����PMU����ECOģʽ����3�Ĵ����� */
#define    HI6551_ECO_MOD_CFG4_OFFSET                     (0x47) /* ��Դ�Ƿ�ǿ����PMU����ECOģʽ����4�Ĵ����� */
#define    HI6551_ENB3_ECO_MARK_OFFSET                    (0x48) /* ��ENB3Ӳ�ߺ�ECO������ص������źżĴ����� */
#define    HI6551_BUCK01_REG1_ADJ_OFFSET                  (0x49) /* BUCK0��BUCK1����1�Ĵ����� */
#define    HI6551_BUCK01_REG2_ADJ_OFFSET                  (0x4A) /* BUCK0��BUCK1����2�Ĵ����� */
#define    HI6551_BUCK01_REG3_ADJ_OFFSET                  (0x4B) /* BUCK0��BUCK1����3�Ĵ����� */
#define    HI6551_BUCK01_REG4_ADJ_OFFSET                  (0x4C) /* BUCK0��BUCK1����4�Ĵ����� */
#define    HI6551_BUCK01_REG5_ADJ_OFFSET                  (0x4D) /* BUCK0��BUCK1����5�Ĵ����� */
#define    HI6551_BUCK01_REG6_ADJ_OFFSET                  (0x4E) /* BUCK0��BUCK1����6�Ĵ����� */
#define    HI6551_BUCK01_REG7_ADJ_OFFSET                  (0x4F) /* BUCK0��BUCK1����7�Ĵ����� */
#define    HI6551_BUCK01_REG8_ADJ_OFFSET                  (0x50) /* BUCK0��BUCK1����8�Ĵ����� */
#define    HI6551_BUCK01_REG9_ADJ_OFFSET                  (0x51) /* BUCK0��BUCK1����9�Ĵ����� */
#define    HI6551_BUCK01_REG10_ADJ_OFFSET                 (0x52) /* BUCK0��BUCK1����10�Ĵ����� */
#define    HI6551_BUCK01_REG11_ADJ_OFFSET                 (0x53) /* BUCK0��BUCK1����11�Ĵ����� */
#define    HI6551_BUCK01_REG12_ADJ_OFFSET                 (0x54) /* BUCK0��BUCK1����12�Ĵ����� */
#define    HI6551_BUCK01_REG13_ADJ_OFFSET                 (0x55) /* BUCK0��BUCK1����13�Ĵ����� */
#define    HI6551_BUCK01_REG14_ADJ_OFFSET                 (0x56) /* BUCK0��BUCK1����14�Ĵ����� */
#define    HI6551_BUCK01_REG15_ADJ_OFFSET                 (0x57) /* BUCK0��BUCK1����15�Ĵ����� */
#define    HI6551_BUCK01_REG16_ADJ_OFFSET                 (0x58) /* BUCK0��BUCK1����16�Ĵ����� */
#define    HI6551_BUCK01_REG17_ADJ_OFFSET                 (0x59) /* BUCK0��BUCK1����17�Ĵ����� */
#define    HI6551_BUCK2_REG1_ADJ_OFFSET                   (0x5A) /* BUCK2����1�Ĵ����� */
#define    HI6551_BUCK2_REG2_ADJ_OFFSET                   (0x5B) /* BUCK2����2�Ĵ����� */
#define    HI6551_BUCK2_REG3_ADJ_OFFSET                   (0x5C) /* BUCK2����3�Ĵ����� */
#define    HI6551_BUCK2_REG4_ADJ_OFFSET                   (0x5D) /* BUCK2����4�Ĵ����� */
#define    HI6551_BUCK2_REG5_ADJ_OFFSET                   (0x5E) /* BUCK2����5�Ĵ����� */
#define    HI6551_BUCK2_REG6_ADJ_OFFSET                   (0x5F) /* BUCK2����6�Ĵ����� */
#define    HI6551_BUCK2_REG7_ADJ_OFFSET                   (0x60) /* BUCK2����7�Ĵ����� */
#define    HI6551_BUCK2_REG8_ADJ_OFFSET                   (0x61) /* BUCK2����8�Ĵ����� */
#define    HI6551_BUCK2_REG9_ADJ_OFFSET                   (0x62) /* BUCK2����9�Ĵ����� */
#define    HI6551_BUCK2_REG10_ADJ_OFFSET                  (0x63) /* BUCK2����10�Ĵ����� */
#define    HI6551_BUCK2_REG11_ADJ_OFFSET                  (0x64) /* BUCK2����11�Ĵ����� */
#define    HI6551_BUCK2_REG12_ADJ_OFFSET                  (0x65) /* BUCK2����12�Ĵ����� */
#define    HI6551_BUCK3_REG1_ADJ_OFFSET                   (0x66) /* BUCK3����1�Ĵ����� */
#define    HI6551_BUCK3_REG2_ADJ_OFFSET                   (0x67) /* BUCK3����2�Ĵ����� */
#define    HI6551_BUCK3_REG3_ADJ_OFFSET                   (0x68) /* BUCK3����3�Ĵ����� */
#define    HI6551_BUCK3_REG4_ADJ_OFFSET                   (0x69) /* BUCK3����4�Ĵ����� */
#define    HI6551_BUCK3_REG5_ADJ_OFFSET                   (0x6A) /* BUCK3����5�Ĵ����� */
#define    HI6551_BUCK3_REG6_ADJ_OFFSET                   (0x6B) /* BUCK3����6�Ĵ����� */
#define    HI6551_BUCK3_REG7_ADJ_OFFSET                   (0x6C) /* BUCK3����7�Ĵ����� */
#define    HI6551_BUCK3_REG8_ADJ_OFFSET                   (0x6D) /* BUCK3����8�Ĵ����� */
#define    HI6551_BUCK3_REG9_ADJ_OFFSET                   (0x6E) /* BUCK3����9�Ĵ����� */
#define    HI6551_BUCK3_REG10_ADJ_OFFSET                  (0x6F) /* BUCK3����10�Ĵ����� */
#define    HI6551_BUCK3_REG11_ADJ_OFFSET                  (0x70) /* BUCK3����11�Ĵ����� */
#define    HI6551_BUCK3_REG12_ADJ_OFFSET                  (0x71) /* BUCK3����12�Ĵ����� */
#define    HI6551_BUCK4_REG1_ADJ_OFFSET                   (0x72) /* BUCK4����1�Ĵ����� */
#define    HI6551_BUCK4_REG2_ADJ_OFFSET                   (0x73) /* BUCK4����2�Ĵ����� */
#define    HI6551_BUCK4_REG3_ADJ_OFFSET                   (0x74) /* BUCK4����3�Ĵ����� */
#define    HI6551_BUCK4_REG4_ADJ_OFFSET                   (0x75) /* BUCK4����4�Ĵ����� */
#define    HI6551_BUCK4_REG5_ADJ_OFFSET                   (0x76) /* BUCK4����5�Ĵ����� */
#define    HI6551_BUCK4_REG6_ADJ_OFFSET                   (0x77) /* BUCK4����6�Ĵ����� */
#define    HI6551_BUCK4_REG7_ADJ_OFFSET                   (0x78) /* BUCK4����7�Ĵ����� */
#define    HI6551_BUCK4_REG8_ADJ_OFFSET                   (0x79) /* BUCK4����8�Ĵ����� */
#define    HI6551_BUCK4_REG9_ADJ_OFFSET                   (0x7A) /* BUCK4����9�Ĵ����� */
#define    HI6551_BUCK4_REG10_ADJ_OFFSET                  (0x7B) /* BUCK4����10�Ĵ����� */
#define    HI6551_BUCK4_REG12_ADJ_OFFSET                  (0x7C) /* BUCK4����12�Ĵ����� */
#define    HI6551_BUCK5_REG1_ADJ_OFFSET                   (0x7D) /* BUCK5����1�Ĵ����� */
#define    HI6551_BUCK5_REG2_ADJ_OFFSET                   (0x7E) /* BUCK5����2�Ĵ����� */
#define    HI6551_BUCK5_REG3_ADJ_OFFSET                   (0x7F) /* BUCK5����3�Ĵ����� */
#define    HI6551_BUCK5_REG4_ADJ_OFFSET                   (0x80) /* BUCK5����4�Ĵ����� */
#define    HI6551_BUCK5_REG5_ADJ_OFFSET                   (0x81) /* BUCK5����5�Ĵ����� */
#define    HI6551_BUCK5_REG6_ADJ_OFFSET                   (0x82) /* BUCK5����6�Ĵ����� */
#define    HI6551_BUCK5_REG7_ADJ_OFFSET                   (0x83) /* BUCK5����7�Ĵ����� */
#define    HI6551_BUCK5_REG8_ADJ_OFFSET                   (0x84) /* BUCK5����8�Ĵ����� */
#define    HI6551_BUCK5_REG9_ADJ_OFFSET                   (0x85) /* BUCK5����9�Ĵ����� */
#define    HI6551_BUCK5_REG10_ADJ_OFFSET                  (0x86) /* BUCK5����10�Ĵ����� */
#define    HI6551_BUCK5_REG12_ADJ_OFFSET                  (0x87) /* BUCK5����12�Ĵ����� */
#define    HI6551_BUCK5_REG13_ADJ_OFFSET                  (0x88) /* BUCK5����13�Ĵ����� */
#define    HI6551_BUCK5_REG14_ADJ_OFFSET                  (0x89) /* BUCK5����14�Ĵ����� */
#define    HI6551_BUCK6_REG1_ADJ_OFFSET                   (0x8A) /* BUCK6����1�Ĵ����� */
#define    HI6551_BUCK6_REG2_ADJ_OFFSET                   (0x8B) /* BUCK6����2�Ĵ����� */
#define    HI6551_BUCK6_REG3_ADJ_OFFSET                   (0x8C) /* BUCK6����3�Ĵ����� */
#define    HI6551_BUCK6_REG4_ADJ_OFFSET                   (0x8D) /* BUCK6����4�Ĵ����� */
#define    HI6551_BUCK6_REG5_ADJ_OFFSET                   (0x8E) /* BUCK6����5�Ĵ����� */
#define    HI6551_BUCK6_REG6_ADJ_OFFSET                   (0x8F) /* BUCK6����6�Ĵ����� */
#define    HI6551_BUCK6_REG7_ADJ_OFFSET                   (0x90) /* BUCK6����7�Ĵ����� */
#define    HI6551_BUCK6_REG8_ADJ_OFFSET                   (0x91) /* BUCK6����8�Ĵ����� */
#define    HI6551_BUCK6_REG9_ADJ_OFFSET                   (0x92) /* BUCK6����9�Ĵ����� */
#define    HI6551_BUCK6_REG10_ADJ_OFFSET                  (0x93) /* BUCK6����10�Ĵ����� */
#define    HI6551_BUCK6_REG11_ADJ_OFFSET                  (0x94) /* BUCK6����11�Ĵ����� */
#define    HI6551_BUCK6_REG12_ADJ_OFFSET                  (0x95) /* BUCK6����12�Ĵ����� */
#define    HI6551_CHG_PUMP2_ADJ_OFFSET                    (0x96) /* CHG_PUMP2���ڼĴ����� */
#define    HI6551_VSET_BUCK01_ADJ_OFFSET                  (0x97) /* BUCK01��ѹ���ڼĴ����� */
#define    HI6551_VSET_BUCK2_ADJ_OFFSET                   (0x98) /* BUCK2��ѹ���ڼĴ����� */
#define    HI6551_VSET_BUCK3_ADJ_OFFSET                   (0x99) /* BUCK3��ѹ���ڼĴ����� */
#define    HI6551_VSET_BUCK4_ADJ_OFFSET                   (0x9A) /* BUCK3��ѹ���ڼĴ����� */
#define    HI6551_VSET_BUCK5_ADJ_OFFSET                   (0x9B) /* BUCK5��ѹ���ڼĴ����� */
#define    HI6551_VSET_BUCK6_ADJ_OFFSET                   (0x9C) /* BUCK6��ѹ���ڼĴ����� */
#define    HI6551_LDO1_REG_ADJ_OFFSET                     (0x9D) /* LDO1���ڼĴ����� */
#define    HI6551_LDO2_REG_ADJ_OFFSET                     (0x9E) /* LDO2���ڼĴ����� */
#define    HI6551_LDO3_REG_ADJ_OFFSET                     (0x9F) /* LDO3���ڼĴ����� */
#define    HI6551_LDO4_REG_ADJ_OFFSET                     (0xA0) /* LDO4���ڼĴ����� */
#define    HI6551_LDO5_REG_ADJ_OFFSET                     (0xA1) /* LDO5���ڼĴ����� */
#define    HI6551_LDO6_REG_ADJ_OFFSET                     (0xA2) /* LDO6���ڼĴ����� */
#define    HI6551_LDO7_REG_ADJ_OFFSET                     (0xA3) /* LDO7���ڼĴ����� */
#define    HI6551_LDO8_REG_ADJ_OFFSET                     (0xA4) /* LDO8���ڼĴ����� */
#define    HI6551_LDO9_REG_ADJ_OFFSET                     (0xA5) /* LDO9���ڼĴ����� */
#define    HI6551_LDO10_REG_ADJ_OFFSET                    (0xA6) /* LDO10���ڼĴ����� */
#define    HI6551_LDO11_REG_ADJ_OFFSET                    (0xA7) /* LDO11���ڼĴ����� */
#define    HI6551_LDO12_REG_ADJ_OFFSET                    (0xA8) /* LDO12���ڼĴ����� */
#define    HI6551_LDO13_REG_ADJ_OFFSET                    (0xA9) /* LDO13���ڼĴ����� */
#define    HI6551_LDO14_REG_ADJ_OFFSET                    (0xAA) /* LDO14���ڼĴ����� */
#define    HI6551_LDO15_REG_ADJ_OFFSET                    (0xAB) /* LDO15���ڼĴ����� */
#define    HI6551_LDO16_REG_ADJ_OFFSET                    (0xAC) /* LDO16���ڼĴ����� */
#define    HI6551_LDO17_REG_ADJ_OFFSET                    (0xAD) /* LDO17���ڼĴ����� */
#define    HI6551_LDO18_REG_ADJ_OFFSET                    (0xAE) /* LDO18���ڼĴ����� */
#define    HI6551_LDO19_REG_ADJ_OFFSET                    (0xAF) /* LDO19���ڼĴ����� */
#define    HI6551_LDO20_REG_ADJ_OFFSET                    (0xB0) /* LDO20���ڼĴ����� */
#define    HI6551_LDO21_REG_ADJ_OFFSET                    (0xB1) /* LDO21���ڼĴ����� */
#define    HI6551_LDO22_REG_ADJ_OFFSET                    (0xB2) /* LDO22���ڼĴ����� */
#define    HI6551_LDO23_REG_ADJ_OFFSET                    (0xB3) /* LDO23���ڼĴ����� */
#define    HI6551_LDO24_REG_ADJ_OFFSET                    (0xB4) /* LDO24���ڼĴ����� */
#define    HI6551_PMUA_REG_ADJ_OFFSET                     (0xB5) /* PMUA���ڼĴ����� */
#define    HI6551_LVS_ADJ1_OFFSET                         (0xB6) /* LVS����1�Ĵ����� */
#define    HI6551_LVS_ADJ2_OFFSET                         (0xB7) /* LVS����2�Ĵ����� */
#define    HI6551_LVS_ADJ3_OFFSET                         (0xB8) /* LVS����3�Ĵ����� */
#define    HI6551_BOOST_ADJ0_OFFSET                       (0xB9) /* BOOST����0�Ĵ����� */
#define    HI6551_BOOST_ADJ1_OFFSET                       (0xBA) /* BOOST����1�Ĵ����� */
#define    HI6551_BOOST_ADJ2_OFFSET                       (0xBB) /* BOOST����2�Ĵ����� */
#define    HI6551_BOOST_ADJ3_OFFSET                       (0xBC) /* BOOST����3�Ĵ����� */
#define    HI6551_BOOST_ADJ4_OFFSET                       (0xBD) /* BOOST����4�Ĵ����� */
#define    HI6551_BOOST_ADJ5_OFFSET                       (0xBE) /* BOOST����5�Ĵ����� */
#define    HI6551_BOOST_ADJ6_OFFSET                       (0xBF) /* BOOST����6�Ĵ����� */
#define    HI6551_BOOST_ADJ7_OFFSET                       (0xC0) /* BOOST����7�Ĵ����� */
#define    HI6551_BOOST_ADJ8_OFFSET                       (0xC1) /* BOOST����8�Ĵ����� */
#define    HI6551_BOOST_ADJ9_OFFSET                       (0xC2) /* BOOST����9�Ĵ����� */
#define    HI6551_BOOST_ADJ10_OFFSET                      (0xC3) /* BOOST����10�Ĵ����� */
#define    HI6551_BOOST_ADJ11_OFFSET                      (0xC4) /* BOOST����11�Ĵ����� */
#define    HI6551_CLASSD_ADJ0_OFFSET                      (0xC5) /* CLASSD����0�Ĵ����� */
#define    HI6551_CLASSD_ADJ1_OFFSET                      (0xC6) /* CLASSD����1�Ĵ����� */
#define    HI6551_CLASSD_ADJ2_OFFSET                      (0xC7) /* CLASSD����2�Ĵ����� */
#define    HI6551_BANDGAP_THSD_ADJ1_OFFSET                (0xC8) /* BANDGAP��THSD����1�Ĵ����� */
#define    HI6551_BANDGAP_THSD_ADJ2_OFFSET                (0xC9) /* BANDGAP��THSD����2�Ĵ����� */
#define    HI6551_DR_FLA_CTRL1_OFFSET                     (0xCA) /* DR��˸ģʽ����1�Ĵ����� */
#define    HI6551_DR_FLA_CTRL2_OFFSET                     (0xCB) /* DR��˸ģʽ����2�Ĵ����� */
#define    HI6551_FLASH_PERIOD_OFFSET                     (0xCC) /* DR��˸ģʽ���ڵ��ڼĴ����� */
#define    HI6551_FLASH_ON_OFFSET                         (0xCD) /* DR��˸ģʽ����ʱ����ڼĴ����� */
#define    HI6551_DR_MODE_SEL_OFFSET                      (0xCE) /* DR��ģʽѡ��Ĵ����� */
#define    HI6551_DR_BRE_CTRL_OFFSET                      (0xCF) /* DR1/2����ģʽ���ƼĴ����� */
#define    HI6551_DR1_TIM_CONF0_OFFSET                    (0xD0) /* DR1��������ʱ�����üĴ����� */
#define    HI6551_DR1_TIM_CONF1_OFFSET                    (0xD1) /* DR1��������ʱ�����üĴ����� */
#define    HI6551_DR1_ISET_OFFSET                         (0xD2) /* DR1����ѡ��Ĵ����� */
#define    HI6551_DR2_TIM_CONF0_OFFSET                    (0xD3) /* DR2��������ʱ�����üĴ����� */
#define    HI6551_DR2_TIM_CONF1_OFFSET                    (0xD4) /* DR2��������ʱ�����üĴ����� */
#define    HI6551_DR2_ISET_OFFSET                         (0xD5) /* DR2����ѡ��Ĵ����� */
#define    HI6551_DR_LED_CTRL_OFFSET                      (0xD6) /* DR3/4/5���ƼĴ����� */
#define    HI6551_DR_OUT_CTRL_OFFSET                      (0xD7) /* DR3/4/5������ƼĴ����� */
#define    HI6551_DR3_ISET_OFFSET                         (0xD8) /* DR3����ѡ��Ĵ����� */
#define    HI6551_DR3_START_DEL_OFFSET                    (0xD9) /* DR3������ʱ���üĴ����� */
#define    HI6551_DR3_TIM_CONF0_OFFSET                    (0xDA) /* DR3��������ʱ�����üĴ����� */
#define    HI6551_DR3_TIM_CONF1_OFFSET                    (0xDB) /* DR3��������ʱ�����üĴ����� */
#define    HI6551_DR4_ISET_OFFSET                         (0xDC) /* DR4����ѡ��Ĵ����� */
#define    HI6551_DR4_START_DEL_OFFSET                    (0xDD) /* DR4������ʱ���üĴ��� */
#define    HI6551_DR4_TIM_CONF0_OFFSET                    (0xDE) /* DR4��������ʱ�����üĴ����� */
#define    HI6551_DR4_TIM_CONF1_OFFSET                    (0xDF) /* DR4��������ʱ�����üĴ����� */
#define    HI6551_DR5_ISET_OFFSET                         (0xE0) /* DR5����ѡ��Ĵ����� */
#define    HI6551_DR5_START_DEL_OFFSET                    (0xE1) /* DR5������ʱ���üĴ����� */
#define    HI6551_DR5_TIM_CONF0_OFFSET                    (0xE2) /* DR5��������ʱ�����üĴ����� */
#define    HI6551_DR5_TIM_CONF1_OFFSET                    (0xE3) /* DR5��������ʱ�����üĴ����� */
#define    HI6551_OTP_CTRL1_OFFSET                        (0xE4) /* OTP����1�źżĴ����� */
#define    HI6551_OTP_CTRL2_OFFSET                        (0xE5) /* OTP����2�źżĴ����� */
#define    HI6551_OTP_PDIN_OFFSET                         (0xE6) /* OTPд��ֵ�Ĵ����� */
#define    HI6551_OTP_PDOB0_OFFSET                        (0xE7) /* OTP����ֵ0�Ĵ����� */
#define    HI6551_OTP_PDOB1_OFFSET                        (0xE8) /* OTP����ֵ1�Ĵ����� */
#define    HI6551_OTP_PDOB2_OFFSET                        (0xE9) /* OTP����ֵ2�Ĵ����� */
#define    HI6551_OTP_PDOB3_OFFSET                        (0xEA) /* OTP����ֵ3�Ĵ����� */
#define    HI6551_RTCCR_A0_OFFSET                         (0xEB) /* RTC_A����0�Ĵ����� */
#define    HI6551_RTCCR_A1_OFFSET                         (0xEC) /* RTC_A����1�Ĵ����� */
#define    HI6551_RTCCR_A2_OFFSET                         (0xED) /* RTC_A����2�Ĵ����� */
#define    HI6551_RTCCR_A3_OFFSET                         (0xEE) /* RTC_A����3�Ĵ����� */
#define    HI6551_RTCLR_A0_OFFSET                         (0xEF) /* RTCLR_A����0�Ĵ����� */
#define    HI6551_RTCLR_A1_OFFSET                         (0xF0) /* RTCLR_A����1�Ĵ����� */
#define    HI6551_RTCLR_A2_OFFSET                         (0xF1) /* RTCLR_A����2�Ĵ����� */
#define    HI6551_RTCLR_A3_OFFSET                         (0xF2) /* RTCLR_A����3�Ĵ����� */
#define    HI6551_RTCCTRL_A_OFFSET                        (0xF3) /* RTCCTRL_A���ƼĴ����� */
#define    HI6551_RTCMR_A_A0_OFFSET                       (0xF4) /* RTC_A_A�Ƚ�0�Ĵ����� */
#define    HI6551_RTCMR_A_A1_OFFSET                       (0xF5) /* RTC_A_A�Ƚ�1�Ĵ����� */
#define    HI6551_RTCMR_A_A2_OFFSET                       (0xF6) /* RTC_A_A�Ƚ�2�Ĵ����� */
#define    HI6551_RTCMR_A_A3_OFFSET                       (0xF7) /* RTC_A_A�Ƚ�3�Ĵ����� */
#define    HI6551_RTCMR_A_B0_OFFSET                       (0xF8) /* RTC_A_B�Ƚ�0�Ĵ����� */
#define    HI6551_RTCMR_A_B1_OFFSET                       (0xF9) /* RTC_A_B�Ƚ�1�Ĵ����� */
#define    HI6551_RTCMR_A_B2_OFFSET                       (0xFA) /* RTC_A_B�Ƚ�2�Ĵ����� */
#define    HI6551_RTCMR_A_B3_OFFSET                       (0xFB) /* RTC_A_B�Ƚ�3�Ĵ����� */
#define    HI6551_RTCMR_A_C0_OFFSET                       (0xFC) /* RTC_A_C�Ƚ�0�Ĵ����� */
#define    HI6551_RTCMR_A_C1_OFFSET                       (0xFD) /* RTC_A_C�Ƚ�1�Ĵ����� */
#define    HI6551_RTCMR_A_C2_OFFSET                       (0xFE) /* RTC_A_C�Ƚ�2�Ĵ����� */
#define    HI6551_RTCMR_A_C3_OFFSET                       (0xFF) /* RTC_A_C�Ƚ�3�Ĵ����� */
#define    HI6551_RTCMR_A_D0_OFFSET                       (0x100) /* RTC_A_D�Ƚ�0�Ĵ����� */
#define    HI6551_RTCMR_A_D1_OFFSET                       (0x101) /* RTC_A_D�Ƚ�1�Ĵ����� */
#define    HI6551_RTCMR_A_D2_OFFSET                       (0x102) /* RTC_A_D�Ƚ�2�Ĵ����� */
#define    HI6551_RTCMR_A_D3_OFFSET                       (0x103) /* RTC_A_D�Ƚ�3�Ĵ����� */
#define    HI6551_RTCMR_A_E0_OFFSET                       (0x104) /* RTC_A_E�Ƚ�0�Ĵ����� */
#define    HI6551_RTCMR_A_E1_OFFSET                       (0x105) /* RTC_A_E�Ƚ�1�Ĵ����� */
#define    HI6551_RTCMR_A_E2_OFFSET                       (0x106) /* RTC_A_E�Ƚ�2�Ĵ����� */
#define    HI6551_RTCMR_A_E3_OFFSET                       (0x107) /* RTC_A_E�Ƚ�3�Ĵ����� */
#define    HI6551_RTCMR_A_F0_OFFSET                       (0x108) /* RTC_A_F�Ƚ�0�Ĵ����� */
#define    HI6551_RTCMR_A_F1_OFFSET                       (0x109) /* RTC_A_F�Ƚ�1�Ĵ����� */
#define    HI6551_RTCMR_A_F2_OFFSET                       (0x10A) /* RTC_A_F�Ƚ�2�Ĵ����� */
#define    HI6551_RTCMR_A_F3_OFFSET                       (0x10B) /* RTC_A_F�Ƚ�3�Ĵ����� */
#define    HI6551_RTCCR_NA0_OFFSET                        (0x10C) /* RTC_NA����0�Ĵ����� */
#define    HI6551_RTCCR_NA1_OFFSET                        (0x10D) /* RTC_NA����1�Ĵ����� */
#define    HI6551_RTCCR_NA2_OFFSET                        (0x10E) /* RTC_NA����2�Ĵ����� */
#define    HI6551_RTCCR_NA3_OFFSET                        (0x10F) /* RTC_NA����3�Ĵ����� */
#define    HI6551_RTCLR_NA0_OFFSET                        (0x110) /* RTCLR_NA����0�Ĵ����� */
#define    HI6551_RTCLR_NA1_OFFSET                        (0x111) /* RTCLR_NA����1�Ĵ����� */
#define    HI6551_RTCLR_NA2_OFFSET                        (0x112) /* RTCLR_NA����2�Ĵ����� */
#define    HI6551_RTCLR_NA3_OFFSET                        (0x113) /* RTCLR_NA����3�Ĵ����� */
#define    HI6551_RTCCTRL_NA_OFFSET                       (0x114) /* RTCCTRL_NA���ƼĴ����� */
#define    HI6551_VERSION_OFFSET                          (0x115) /* �汾�Ĵ����� */
#define    HI6551_RESERVED0_OFFSET                        (0x116) /* ����0�Ĵ����� */
#define    HI6551_RESERVED1_OFFSET                        (0x117) /* ����1�Ĵ����� */
#define    HI6551_RESERVED2_OFFSET                        (0x118) /* ����2�Ĵ����� */
#define    HI6551_RESERVED3_OFFSET                        (0x119) /* ����3�Ĵ����� */
#define    HI6551_RESERVED4_OFFSET                        (0x11A) /* ����4�Ĵ����� */
#define    HI6551_HTOL_MODE_OFFSET                        (0x11B) /* �ϻ�����ģʽ���üĴ����� */
#define    HI6551_DAC_CTRL_OFFSET                         (0x11C) /* DAC���ƼĴ��� */
#define    HI6551_CHIP_SOFT_RST_OFFSET                    (0x11D) /* оƬģ����λ�Ĵ����� */
#define    HI6551_NP_REG_ADJ_OFFSET                       (0x11E) /* ���µ���ڼĴ����� */
#define    HI6551_NP_REG_CHG_OFFSET                       (0x11F) /* ���õ�ط��µ���ڼĴ����� */
#define    HI6551_NP_RSVED1_OFFSET                        (0x120) /* ���µ籣��1�Ĵ����� */
#define    HI6551_NP_RSVED2_OFFSET                        (0x121) /* ���µ籣��2�Ĵ����� */
#define    HI6551_NP_RSVED3_OFFSET                        (0x122) /* ���µ籣��3�Ĵ����� */
#define    HI6551_NP_RSVED4_OFFSET                        (0x123) /* ���µ籣��4�Ĵ����� */
#define    HI6551_RTC_ADJ1_OFFSET                         (0x124) /* rtc_adj[7:0]�Ĵ����� */
#define    HI6551_RTC_ADJ2_OFFSET                         (0x125) /* rtc_adj[15:8]�Ĵ����� */
#define    HI6551_CLJ_CTRL_REG_OFFSET                     (0x133) /* �Ĵ������ƼĴ����� */
#define    HI6551_ECO_REFALSH_TIME_OFFSET                 (0x134) /* ECO_REFLASH����ʱ��Ĵ����� */
#define    HI6551_CL_OUT0_OFFSET                          (0x135) /* cl_out[7:0]�Ĵ����� */
#define    HI6551_CL_OUT1_OFFSET                          (0x136) /* cl_out[15:8]�Ĵ����� */
#define    HI6551_CL_OUT2_OFFSET                          (0x137) /* cl_out[23:16]�Ĵ����� */
#define    HI6551_CL_OUT3_OFFSET                          (0x138) /* cl_out[31:24]�Ĵ����� */
#define    HI6551_CL_IN0_OFFSET                           (0x139) /* cl_in[7:0]�Ĵ����� */
#define    HI6551_CL_IN1_OFFSET                           (0x13A) /* cl_in[15:8]�Ĵ����� */
#define    HI6551_CL_IN2_OFFSET                           (0x13B) /* cl_in[23:16]�Ĵ����� */
#define    HI6551_CL_IN3_OFFSET                           (0x13C) /* cl_in[31:24]�Ĵ����� */
#define    HI6551_CHG_TIMER0_OFFSET                       (0x13D) /* chg_timer[7:0]�Ĵ����� */
#define    HI6551_CHG_TIMER1_OFFSET                       (0x13E) /* chg_timer[15:8]�Ĵ����� */
#define    HI6551_CHG_TIMER2_OFFSET                       (0x13F) /* chg_timer[23:16]�Ĵ����� */
#define    HI6551_CHG_TIMER3_OFFSET                       (0x140) /* chg_timer[31:24]�Ĵ����� */
#define    HI6551_LOAD_TIMER0_OFFSET                      (0x141) /* load_timer[7:0]�Ĵ����� */
#define    HI6551_LOAD_TIMER1_OFFSET                      (0x142) /* load_timer[15:8]�Ĵ����� */
#define    HI6551_LOAD_TIMER2_OFFSET                      (0x143) /* load_timer[23:16]�Ĵ����� */
#define    HI6551_LOAD_TIMER3_OFFSET                      (0x144) /* load_timer[31:24]�Ĵ����� */
#define    HI6551_OFF_TIMER0_OFFSET                       (0x145) /* off_timer[7:0]�Ĵ����� */
#define    HI6551_OFF_TIMER1_OFFSET                       (0x146) /* off_timer[15:8]�Ĵ����� */
#define    HI6551_OFF_TIMER2_OFFSET                       (0x147) /* off_timer[23:16]�Ĵ����� */
#define    HI6551_OFF_TIMER3_OFFSET                       (0x148) /* off_timer[31:24]�Ĵ����� */
#define    HI6551_CL_INT0_OFFSET                          (0x149) /* cl_int[7:0]�Ĵ����� */
#define    HI6551_CL_INT1_OFFSET                          (0x14A) /* cl_int[15:8]�Ĵ����� */
#define    HI6551_CL_INT2_OFFSET                          (0x14B) /* cl_int[23:16]�Ĵ����� */
#define    HI6551_CL_INT3_OFFSET                          (0x14C) /* cl_int[31:24]�Ĵ����� */
#define    HI6551_V_INT0_OFFSET                           (0x14D) /* v_int[7:0]�Ĵ����� */
#define    HI6551_V_INT1_OFFSET                           (0x14E) /* v_int[15:8]�Ĵ����� */
#define    HI6551_OFFSET_CURRENT0_OFFSET                  (0x14F) /* offset_current[7:0]�Ĵ����� */
#define    HI6551_OFFSET_CURRENT1_OFFSET                  (0x150) /* offset_current[15:8]�Ĵ����� */
#define    HI6551_OFFSET_VOLTAGE0_OFFSET                  (0x151) /* offset_voltage[7:0]�Ĵ����� */
#define    HI6551_OFFSET_VOLTAGE1_OFFSET                  (0x152) /* offset_voltage[15:8]�Ĵ����� */
#define    HI6551_OCV_DATA1_OFFSET                        (0x153) /* ocv_data[7:0]�Ĵ����� */
#define    HI6551_OCV_DATA2_OFFSET                        (0x154) /* ocv_data[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE0_OFFSET                      (0x155) /* v_out_pre0[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE0_OFFSET                      (0x156) /* v_out_pre0[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE1_OFFSET                      (0x157) /* v_out_pre1[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE1_OFFSET                      (0x158) /* v_out_pre1[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE2_OFFSET                      (0x159) /* v_out_pre2[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE2_OFFSET                      (0x15A) /* v_out_pre2[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE3_OFFSET                      (0x15B) /* v_out_pre3[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE3_OFFSET                      (0x15C) /* v_out_pre3[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE4_OFFSET                      (0x15D) /* v_out_pre4[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE4_OFFSET                      (0x15E) /* v_out_pre4[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE5_OFFSET                      (0x15F) /* v_out_pre5[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE5_OFFSET                      (0x160) /* v_out_pre5[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE6_OFFSET                      (0x161) /* v_out_pre6[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE6_OFFSET                      (0x162) /* v_out_pre6[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE7_OFFSET                      (0x163) /* v_out_pre7[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE7_OFFSET                      (0x164) /* v_out_pre7[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE8_OFFSET                      (0x165) /* v_out_pre8[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE8_OFFSET                      (0x166) /* v_out_pre8[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE9_OFFSET                      (0x167) /* v_out_pre9[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE9_OFFSET                      (0x168) /* v_out_pre9[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE10_OFFSET                     (0x169) /* v_out_pre10[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE10_OFFSET                     (0x16A) /* v_out_pre10[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE11_OFFSET                     (0x16B) /* v_out_pre11[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE11_OFFSET                     (0x16C) /* v_out_pre11[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE12_OFFSET                     (0x16D) /* v_out_pre12[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE12_OFFSET                     (0x16E) /* v_out_pre12[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE13_OFFSET                     (0x16F) /* v_out_pre13[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE13_OFFSET                     (0x170) /* v_out_pre13[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE14_OFFSET                     (0x171) /* v_out_pre14[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE14_OFFSET                     (0x172) /* v_out_pre14[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE15_OFFSET                     (0x173) /* v_out_pre15[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE15_OFFSET                     (0x174) /* v_out_pre15[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE16_OFFSET                     (0x175) /* v_out_pre16[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE16_OFFSET                     (0x176) /* v_out_pre16[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE17_OFFSET                     (0x177) /* v_out_pre17[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE17_OFFSET                     (0x178) /* v_out_pre17[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE18_OFFSET                     (0x179) /* v_out_pre18[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE18_OFFSET                     (0x17A) /* v_out_pre18[15:8]�Ĵ����� */
#define    HI6551_V_OUT0_PRE19_OFFSET                     (0x17B) /* v_out_pre19[7:0]�Ĵ����� */
#define    HI6551_V_OUT1_PRE19_OFFSET                     (0x17C) /* v_out_pre19[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE0_OFFSET                    (0x17D) /* current_pre0[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE0_OFFSET                    (0x17E) /* current_pre0[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE1_OFFSET                    (0x17F) /* current_pre1[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE1_OFFSET                    (0x180) /* current_pre1[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE2_OFFSET                    (0x181) /* current_pre2[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE2_OFFSET                    (0x182) /* current_pre2[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE3_OFFSET                    (0x183) /* current_pre3[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE3_OFFSET                    (0x184) /* current_pre3[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE4_OFFSET                    (0x185) /* current_pre4[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE4_OFFSET                    (0x186) /* current_pre4[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE5_OFFSET                    (0x187) /* current_pre5[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE5_OFFSET                    (0x188) /* current_pre5[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE6_OFFSET                    (0x189) /* current_pre6[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE6_OFFSET                    (0x18A) /* current_pre6[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE7_OFFSET                    (0x18B) /* current_pre7[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE7_OFFSET                    (0x18C) /* current_pre7[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE8_OFFSET                    (0x18D) /* current_pre8[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE8_OFFSET                    (0x18E) /* current_pre8[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE9_OFFSET                    (0x18F) /* current_pre9[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE9_OFFSET                    (0x190) /* current_pre9[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE10_OFFSET                   (0x191) /* current_pre10[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE10_OFFSET                   (0x192) /* current_pre10[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE11_OFFSET                   (0x193) /* current_pre11[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE11_OFFSET                   (0x194) /* current_pre11[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE12_OFFSET                   (0x195) /* current_pre12[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE12_OFFSET                   (0x196) /* current_pre12[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE13_OFFSET                   (0x197) /* current_pre13[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE13_OFFSET                   (0x198) /* current_pre13[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE14_OFFSET                   (0x199) /* current_pre14[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE14_OFFSET                   (0x19A) /* current_pre14[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE15_OFFSET                   (0x19B) /* current_pre15[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE15_OFFSET                   (0x19C) /* current_pre15[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE16_OFFSET                   (0x19D) /* current_pre16[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE16_OFFSET                   (0x19E) /* current_pre16[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE17_OFFSET                   (0x19F) /* current_pre17[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE17_OFFSET                   (0x1A0) /* current_pre17[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE18_OFFSET                   (0x1A1) /* current_pre18[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE18_OFFSET                   (0x1A2) /* current_pre18[15:8]�Ĵ����� */
#define    HI6551_CURRENT0_PRE19_OFFSET                   (0x1A3) /* current_pre19[7:0]�Ĵ����� */
#define    HI6551_CURRENT1_PRE19_OFFSET                   (0x1A4) /* current_pre19[15:8]�Ĵ����� */
#define    HI6551_CLJ_DEBUG_OFFSET                        (0x1A5) /* ���ؼ�DEBUGר��1�Ĵ����� */
#define    HI6551_STATE_TEST_OFFSET                       (0x1A6) /* ���ؼ�DEBUGר��2�Ĵ����� */
#define    HI6551_CLJ_RESERVED1_OFFSET                    (0x1A7) /* ���ؼƱ���1�Ĵ����� */
#define    HI6551_CLJ_RESERVED2_OFFSET                    (0x1A8) /* ���ؼƱ���2�Ĵ����� */
#define    HI6551_CLJ_RESERVED3_OFFSET                    (0x1A9) /* ���ؼƱ���3�Ĵ����� */
#define    HI6551_CLJ_RESERVED4_OFFSET                    (0x1AA) /* ���ؼƱ���4�Ĵ����� */
#define    HI6551_CLJ_RESERVED5_OFFSET                    (0x1AB) /* ���ؼƱ���5�Ĵ����� */
#define    HI6551_CLJ_RESERVED6_OFFSET                    (0x1AC) /* ���ؼƱ���6�Ĵ����� */
#define    HI6551_CLJ_RESERVED7_OFFSET                    (0x1AD) /* ���ؼƱ���7�Ĵ����� */
#define    HI6551_CLJ_RESERVED8_OFFSET                    (0x1AE) /* ���ؼƱ���8�Ĵ����� */

/********************************************************************************/
/*    hi6551 �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    otmp_d1r                   : 1; /* [0..0] 0�� ��ǰ�¶ȵ����趨��ֵ��Ĭ��125�棩��1�� ��ǰ�¶ȸ����趨��ֵ�� */
        unsigned int    otmp150_d1r                : 1; /* [1..1] 0�� ��ǰ�¶ȵ���150�棻1�� ��ǰ�¶ȸ���150�档 */
        unsigned int    osc_state                  : 1; /* [2..2] 0��OSC����ʱ���Ѿ�������ʱ���л����;1��OSC����ʱ��û�о����� */
        unsigned int    vsys_uv_d2f                : 1; /* [3..3] ��ǰvsys��ѹ��0��vsys<2.7V/3VV��1��vsys>2.7V/3.0V�� */
        unsigned int    vsys_6p0_d200ur            : 1; /* [4..4] ��ǰvsys��ѹ��0��vsys<6.0V��1��vsys>6.0V�� */
        unsigned int    pwron_d20r                 : 1; /* [5..5] 0��PWRON����ǰû�б����£�1:PWRON����ǰ������(pwronΪpwron_n�ķ���)�� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_STATUS1_T;    /* ״̬��־1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    alarm_on_a                 : 1; /* [0..0] ����A:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_b                 : 1; /* [1..1] ����B:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_c                 : 1; /* [2..2] ����C:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_d                 : 1; /* [3..3] ����D:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_e                 : 1; /* [4..4] ����E:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    vbus_det_0p9_d3r           : 1; /* [5..5] vbus_det_0p9��0: û�в��룻1�����롣 */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_STATUS2_T;    /* ״̬��־2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otmp_d1r                   : 1; /* [0..0] 0:�޴��жϣ�1��otmp ���¶ȳ����趨��ֵ��Ĭ��125�ȣ��жϡ� */
        unsigned int    vsys_2p5_f                 : 1; /* [1..1] 0:�޴��жϣ�1:vsys��ѹ����2.5V�жϡ� */
        unsigned int    vsys_uv_d2f                : 1; /* [2..2] 0:�޴��жϣ�1:vsys��ѹ����2.7V/3.0V 2ms�жϡ�(Ĭ��3V�����µ�Ĵ���vsys_uv_adj�ɵ�) */
        unsigned int    vsys_6p0_d200ur            : 1; /* [3..3] 0���޴��жϣ�1:vsys����ѹ����6.0V 200us�жϡ� */
        unsigned int    pwron_d4sr                 : 1; /* [4..4] 0:�޴��жϣ�1:PWRON��������4s�ж�(���ж�ֻ����������ʱ���²��ϱ�) �� */
        unsigned int    pwron_d20f                 : 1; /* [5..5] 0:�޴��жϣ�1:PWRON�����ͷ�20ms�ж� �� */
        unsigned int    pwron_d20r                 : 1; /* [6..6] 0:�޴��жϣ�1:PWRON��������20ms�жϡ� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_IRQ1_T;    /* �ж�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_scp_r                  : 1; /* [0..0] 0:�޴��жϣ�1:��ʾ������һ��BUCK/BOOST/CLASSD���������������߶�·����������LDO/LVS/������������������BOOST������ѹ/Ƿѹ������CPU��ѯ����Ҫȥ�鿴����Ĺ�������Ĵ����鿴����һ������������������д1����ж������� */
        unsigned int    vbus_det_1p375_d90ur       : 1; /* [1..1] 0:�޴��жϣ�1:vbus_det>1.375V 90us�ж� �� */
        unsigned int    vbus_det_0p9_d3f           : 1; /* [2..2] 0:�޴��жϣ�1:vbus_det<0.9 V 3ms�ж� �� */
        unsigned int    vbus_det_0p9_d3r           : 1; /* [3..3] 0:�޴��жϣ�1:vbus_det>0.9 V 3ms�ж� �� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_IRQ2_T;    /* �ж�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    alarm_on_a                 : 1; /* [0..0] ALARM_ON_A�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_b                 : 1; /* [1..1] ALARM_ON_B�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_c                 : 1; /* [2..2] ALARM_ON_C�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_d                 : 1; /* [3..3] ALARM_ON_D�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_e                 : 1; /* [4..4] ALARM_ON_E�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_f                 : 1; /* [5..5] ALARM_ON_F�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_IRQ3_T;    /* �ж�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sim0_hpd_out_f             : 1; /* [0..0] SIM0������λ����SIM0_HPD�жϣ�0�� �޴��ж� ��  1�� �����½�������  �� */
        unsigned int    sim0_hpd_out_r             : 1; /* [1..1] SIM0������λ����SIM0_HPD�жϣ�0�� �޴��ж� ��  1�� ��������������  �� */
        unsigned int    sim0_hpd_in_f              : 1; /* [2..2] SIM0����λ����SIM0_HPD�жϣ�0�� �޴��ж� ��  1�� �����½�������  �� */
        unsigned int    sim0_hpd_in_r              : 1; /* [3..3] SIM0����λ����SIM0_HPD�жϣ�0�� �޴��ж� ��  1�� ��������������  �� */
        unsigned int    sim1_hpd_out_f             : 1; /* [4..4] SIM1������λ����SIM1_HPD�жϣ���0�� �޴��ж� ��  1�� �����½�������  �� */
        unsigned int    sim1_hpd_out_r             : 1; /* [5..5] SIM1������λ����SIM1_HPD�жϣ�0�� �޴��ж� ��  1�� ��������������  �� */
        unsigned int    sim1_hpd_in_f              : 1; /* [6..6] SIM1����λ����SIM1_HPD�жϣ�0�� �޴��ж� ��  1�� �����½�������  �� */
        unsigned int    sim1_hpd_in_r              : 1; /* [7..7] SIM1����λ����SIM1_HPD�жϣ�0�� �޴��ж� ��  1�� ��������������  �� */
    } bits;
    unsigned int    u32;
}HI6551_IRQ4_T;    /* �ж�4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_int_i                   : 1; /* [0..0] cl_out>cl_intʱ�ϱ��ж� */
        unsigned int    cl_out_i                   : 1; /* [1..1] cl_out������81.25%�ϱ��ж� */
        unsigned int    cl_in_i                    : 1; /* [2..2] cl_in������81.25%�ϱ��ж� */
        unsigned int    chg_timer_i                : 1; /* [3..3] chg_timer������81.25%�ϱ��ж� */
        unsigned int    load_timer_i               : 1; /* [4..4] load_timer������81.25%�ϱ��ж� */
        unsigned int    vbat_int_i                 : 1; /* [5..5] vbat��ѹ<�趨��vbat_intֵ */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_COUL_IRQ_T;    /* ���ؼ��жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    otmp_d1r_mk                : 1; /* [0..0] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vsys_2p5_f_mk              : 1; /* [1..1] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vsys_uv_d2f_mk             : 1; /* [2..2] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vsys_6p0_d200ur_mk         : 1; /* [3..3] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    pwron_d4sr_mk              : 1; /* [4..4] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    pwron_d20f_mk              : 1; /* [5..5] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    pwron_d20r_mk              : 1; /* [6..6] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_IRQ1_MASK_T;    /* �ж�����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_scp_r_mk               : 1; /* [0..0] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vbus_det_1p375_mk          : 1; /* [1..1] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vbus_det_0p9_d3f_mk        : 1; /* [2..2] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vbus_det_0p9_d3r_mk        : 1; /* [3..3] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_IRQ2_MASK_T;    /* �ж�����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    alarm_on_a_mk              : 1; /* [0..0] ALARM_ON_A�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_b_mk              : 1; /* [1..1] ALARM_ON_B�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_c_mk              : 1; /* [2..2] ALARM_ON_C�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_d_mk              : 1; /* [3..3] ALARM_ON_D�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_e_mk              : 1; /* [4..4] ALARM_ON_E�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_f_mk              : 1; /* [5..5] ALARM_ON_F�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_IRQ3_MASK_T;    /* �ж�����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sim0_hpd_out_f_mk          : 1; /* [0..0] SIM0������λ����SIM0_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim0_hpd_out_r_mk          : 1; /* [1..1] SIM0������λ����SIM0_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim0_hpd_in_f_mk           : 1; /* [2..2] SIM0����λ����SIM0_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim0_hpd_in_r_mk           : 1; /* [3..3] SIM0����λ����SIM0_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim1_hpd_out_f_mk          : 1; /* [4..4] SIM1������λ����SIM1_HPD�жϣ���0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim1_hpd_out_r_mk          : 1; /* [5..5] SIM1������λ����SIM1_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim1_hpd_in_f_mk           : 1; /* [6..6] SIM1����λ����SIM1_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim1_in_hpd_r_mk           : 1; /* [7..7] SIM1����λ����SIM1_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
    } bits;
    unsigned int    u32;
}HI6551_IRQ4_MASK_T;    /* �ж�����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_int_i_mk                : 1; /* [0..0] cl_int_i�ж����� */
        unsigned int    cl_out_i_mk                : 1; /* [1..1] cl_out_i�ж����� */
        unsigned int    cl_in_i_mk                 : 1; /* [2..2] cl_in_i�ж����� */
        unsigned int    chg_timer_i_mk             : 1; /* [3..3] chg_timer_i�ж����� */
        unsigned int    load_timer_i_mk            : 1; /* [4..4] load_timer_i�ж����� */
        unsigned int    vbat_int_i_mk              : 1; /* [5..5] vbat_int_i�ж����� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_COUL_IRQ_MASK_T;    /* ���ؼ��жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    scp_buck0_1                : 1; /* [0..0] 0��BUCK0_1��������أ�1: BUCK0_1������ء�ע��BUCK0��BUCK1����1bits��·�����жϼ�¼�Ĵ����� */
        unsigned int    scp_buck2                  : 1; /* [1..1] 0��BUCK2�������·��1: BUCK2�����·�� */
        unsigned int    scp_buck3                  : 1; /* [2..2] 0��BUCK3�������·��1: BUCK3�����·�� */
        unsigned int    scp_buck4                  : 1; /* [3..3] 0��BUCK4�������·��1: BUCK4�����·�� */
        unsigned int    scp_buck5                  : 1; /* [4..4] 0��BUCK5�������·��1: BUCK5�����·�� */
        unsigned int    scp_buck6                  : 1; /* [5..5] 0��BUCK6�������·��1: BUCK6�����·�� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_SCP_RECORD1_T;    /* ��·������¼1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_buck0_1                : 1; /* [0..0] 0��BUCK0_1��������أ�1: BUCK0_1������ء�  ע:�����ϱ��жϣ������λ��������buck0_1�����жϡ���buck0��buck1ͬʱ����ʹ��ʱ��ֻ�ж�����������Żᴥ��������������������ʹ��ĳ��buckʱ��ֻҪ���������ʹ������������� */
        unsigned int    ocp_buck2                  : 1; /* [1..1] 0��BUCK2��������أ�1: BUCK2������ء� */
        unsigned int    ocp_buck3                  : 1; /* [2..2] 0��BUCK3��������أ�1: BUCK3������ء� */
        unsigned int    ocp_buck4                  : 1; /* [3..3] 0��BUCK4��������أ�1: BUCK4������ء� */
        unsigned int    ocp_buck5                  : 1; /* [4..4] 0��BUCK5��������أ�1: BUCK5������ء� */
        unsigned int    ocp_buck6                  : 1; /* [5..5] 0��BUCK6��������أ�1: BUCK6������ء� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_OCP_RECORD1_T;    /* ����������¼1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo1                   : 1; /* [0..0] 0��LDO1��������أ�1: LDO1������ء� */
        unsigned int    ocp_ldo2                   : 1; /* [1..1] 0��LDO2��������أ�1: LDO2������ء� */
        unsigned int    ocp_ldo3                   : 1; /* [2..2] 0��LDO3��������أ�1: LDO3������ء� */
        unsigned int    ocp_ldo4                   : 1; /* [3..3] 0��LDO4��������أ�1: LDO4������ء� */
        unsigned int    ocp_ldo5                   : 1; /* [4..4] 0��LDO5��������أ�1: LDO5������ء� */
        unsigned int    ocp_ldo6                   : 1; /* [5..5] 0��LDO6��������أ�1: LDO6������ء� */
        unsigned int    ocp_ldo7                   : 1; /* [6..6] 0��LDO7��������أ�1: LDO7������ء� */
        unsigned int    ocp_ldo8                   : 1; /* [7..7] 0��LDO8��������أ�1: LDO8������ء� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_RECORD2_T;    /* ����������¼2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo9                   : 1; /* [0..0] 0��LDO9��������أ�1: LDO9������ء� */
        unsigned int    ocp_ldo10                  : 1; /* [1..1] 0��LDO10��������أ�1: LDO10������ء� */
        unsigned int    ocp_ldo11                  : 1; /* [2..2] 0��LDO11��������أ�1: LDO11������ء� */
        unsigned int    ocp_ldo12                  : 1; /* [3..3] 0��LDO12��������أ�1: LDO12������ء� */
        unsigned int    ocp_ldo13                  : 1; /* [4..4] 0��LDO13��������أ�1: LDO13������ء� */
        unsigned int    ocp_ldo14                  : 1; /* [5..5] 0��LDO14��������أ�1: LDO14������ء� */
        unsigned int    ocp_ldo15                  : 1; /* [6..6] 0��LDO15��������أ�1: LDO15������ء� */
        unsigned int    ocp_ldo16                  : 1; /* [7..7] 0��LDO16��������أ�1: LDO16������ء� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_RECORD3_T;    /* ����������¼3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo17                  : 1; /* [0..0] 0��LDO17��������أ�1: LDO17������ء� */
        unsigned int    ocp_ldo18                  : 1; /* [1..1] 0��LDO18��������أ�1: LDO18������ء� */
        unsigned int    ocp_ldo19                  : 1; /* [2..2] 0��LDO19��������أ�1: LDO19������ء� */
        unsigned int    ocp_ldo20                  : 1; /* [3..3] 0��LDO20��������أ�1: LDO20������ء� */
        unsigned int    ocp_ldo21                  : 1; /* [4..4] 0��LDO21��������أ�1: LDO21������ء� */
        unsigned int    ocp_ldo22                  : 1; /* [5..5] 0��LDO22��������أ�1: LDO22������ء� */
        unsigned int    ocp_ldo23                  : 1; /* [6..6] 0��LDO23��������أ�1: LDO23������ء� */
        unsigned int    ocp_ldo24                  : 1; /* [7..7] 0��LDO24��������أ�1: LDO24������ء� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_RECORD4_T;    /* ����������¼4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_lvs2                   : 1; /* [0..0] 0��LVS2��������أ�1: LVS2������ء� */
        unsigned int    ocp_lvs3                   : 1; /* [1..1] 0��LVS3��������أ�1: LVS3������ء� */
        unsigned int    ocp_lvs4                   : 1; /* [2..2] 0��LVS4��������أ�1: LVS4������ء� */
        unsigned int    ocp_lvs5                   : 1; /* [3..3] 0��LVS5��������أ�1: LVS5������ء� */
        unsigned int    ocp_lvs7                   : 1; /* [4..4] 0��LVS7��������أ�1: LVS7������ء� */
        unsigned int    ocp_lvs6                   : 1; /* [5..5] 0��LVS6��������أ�1: LVS6������ء� */
        unsigned int    ocp_lvs8                   : 1; /* [6..6] 0��LVS8��������أ�1: LVS8������ء� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_OCP_RECORD5_T;    /* ����������¼5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_lvs9                   : 1; /* [0..0] 0��LVS9��������أ�1: LVS9������ء� */
        unsigned int    ocp_lvs10                  : 1; /* [1..1] 0��LVS10��������أ�1: LVS10������ء� */
        unsigned int    reserved                   : 6; /* [7..2] ������ */
    } bits;
    unsigned int    u32;
}HI6551_OCP_RECORD6_T;    /* ����������¼6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_boost                  : 1; /* [0..0] 0��BOOOST�����������1: BOOOST��������� */
        unsigned int    scp_boost                  : 1; /* [1..1] 0��BOOOST�������·��1: BOOOST�����·�� */
        unsigned int    ovp_boost                  : 1; /* [2..2] 0��BOOOST�������ѹ��1: BOOOST�����ѹ�� */
        unsigned int    uvp_boost                  : 1; /* [3..3] 0��BOOOST�����Ƿѹ��1: BOOOST���Ƿѹ�� */
        unsigned int    ocp_classd                 : 1; /* [4..4] 0��CLASSD�����������1: CLASSD��������� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6551_OCP_RECORD7_T;    /* ����������¼7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_otmp_d1r                : 1; /* [0..0] �¶ȱ���(Ĭ��125��)��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_hreset_n_f              : 1; /* [1..1] �ȸ�λ��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vsys_2p5_f              : 1; /* [2..2] vsys < 2.5V��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vsys_uv_d2f             : 1; /* [3..3] vsys < 2.7V/3.0V 2ms:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vsys_6p0_d200ur         : 1; /* [4..4] vsys> 6.0V 200us:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_d4sr              : 1; /* [5..5] ����������״̬��PWRON����4s:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_d20f              : 1; /* [6..6] PWRON�����ͷ�20ms��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_d20r              : 1; /* [7..7] PWRON��������20ms��0:û�з��������¼���1:�������¼��� */
    } bits;
    unsigned int    u32;
}HI6551_NP_IRQ1_RECORD_T;    /* �ж�1���µ��¼�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_vbus_det_0p9_d150r      : 1; /* [0..0] vbus_det> 0.9V 150ms��     0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vbus_det_1p375          : 1; /* [1..1] vbus_det>1.375V 90us��     0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vbus_det_0p9_d3f        : 1; /* [2..2] vbus_det< 0.9V 3ms�� 0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vbus_det_0p9_d3r        : 1; /* [3..3] vbus_det> 0.9V 3ms�� 0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_restart           : 1; /* [4..4] ͨ��pwron����N+5S����:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_dnsr              : 1; /* [5..5] ������������pwron����Ns�ػ�:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_d500r             : 1; /* [6..6] �ػ�״̬��PWRON����500ms:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_otmp150_d1r             : 1; /* [7..7] �¶� > 150�棺0:û�з��������¼���1:�������¼��� */
    } bits;
    unsigned int    u32;
}HI6551_NP_IRQ2_RECORD_T;    /* �ж�2���µ��¼�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_alarm_on_a              : 1; /* [0..0] ��������a��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_b              : 1; /* [1..1] ��������b��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_c              : 1; /* [2..2] ��������c��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_d              : 1; /* [3..3] ��������d��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_e              : 1; /* [4..4] ��������e��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_f              : 1; /* [5..5] ��������f��0:û�з��������¼���1:�������¼��� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_NP_IRQ3_RECORD_T;    /* �ж�3���µ��¼�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_scp_buck0_1             : 1; /* [0..0] 0������¼BUCK0_1�������·��1: ����¼BUCK0_1�����·��ע��BUCK0��BUCK1����1bits��·�����жϼ�¼�Ĵ����� */
        unsigned int    np_scp_buck2               : 1; /* [1..1] 0������¼BUCK2�������·��1: ����¼BUCK2�����·�� */
        unsigned int    np_scp_buck3               : 1; /* [2..2] 0������¼BUCK3�������·��1: ����¼BUCK3�����·�� */
        unsigned int    np_scp_buck4               : 1; /* [3..3] 0������¼BUCK4�������·��1: ����¼BUCK4�����·�� */
        unsigned int    np_scp_buck5               : 1; /* [4..4] 0������¼BUCK5�������·��1: ����¼BUCK5�����·�� */
        unsigned int    np_scp_buck6               : 1; /* [5..5] 0������¼BUCK6�������·��1: ����¼BUCK6�����·�� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_NP_SCP_RECORD1_T;    /* ��·�������µ��¼1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_buck0               : 1; /* [0..0] 0������¼BUCK0��������أ�1: ����¼BUCK0������ء�ע�������ڼ�¼���������á� */
        unsigned int    np_ocp_buck1               : 1; /* [1..1] 0������¼BUCK1��������أ�1: ����¼BUCK1������ء�ע�������ڼ�¼���������á� */
        unsigned int    np_ocp_buck0_1             : 1; /* [2..2] 0������¼BUCK0_1��������أ�1: ����¼BUCK0_1������ء� */
        unsigned int    np_ocp_buck2               : 1; /* [3..3] 0������¼BUCK2��������أ�1: ����¼BUCK2������ء� */
        unsigned int    np_ocp_buck3               : 1; /* [4..4] 0������¼BUCK3��������أ�1: ����¼BUCK3������ء� */
        unsigned int    np_ocp_buck4               : 1; /* [5..5] 0������¼BUCK4��������أ�1: ����¼BUCK4������ء� */
        unsigned int    np_ocp_buck5               : 1; /* [6..6] 0������¼BUCK5��������أ�1: ����¼BUCK5������ء� */
        unsigned int    np_ocp_buck6               : 1; /* [7..7] 0������¼BUCK6��������أ�1: ����¼BUCK6������ء� */
    } bits;
    unsigned int    u32;
}HI6551_NP_OCP_RECORD1_T;    /* �����������µ��¼1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_ldo1                : 1; /* [0..0] 0������¼LDO1��������أ�1: ����¼LDO1������ء� */
        unsigned int    np_ocp_ldo2                : 1; /* [1..1] 0������¼LDO2��������أ�1: ����¼LDO2������ء� */
        unsigned int    np_ocp_ldo3                : 1; /* [2..2] 0������¼LDO3��������أ�1: ����¼LDO3������� �� */
        unsigned int    np_ocp_ldo4                : 1; /* [3..3] 0������¼LDO4��������أ�1: ����¼LDO4������ء� */
        unsigned int    np_ocp_ldo5                : 1; /* [4..4] 0������¼LDO5��������أ�1: ����¼LDO5������ء� */
        unsigned int    np_ocp_ldo6                : 1; /* [5..5] 0������¼LDO6��������أ�1: ����¼LDO6������ء� */
        unsigned int    np_ocp_ldo7                : 1; /* [6..6] 0������¼LDO7��������أ�1: ����¼LDO7������ء� */
        unsigned int    np_ocp_ldo8                : 1; /* [7..7] 0������¼LDO8��������أ�1: ����¼LDO8������ء� */
    } bits;
    unsigned int    u32;
}HI6551_NP_OCP_RECORD2_T;    /* �����������µ��¼2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_ldo9                : 1; /* [0..0] 0������¼LDO9��������أ�1: ����¼LDO9������ء� */
        unsigned int    np_ocp_ldo10               : 1; /* [1..1] 0������¼LDO10��������أ�1: ����¼LDO10������ء� */
        unsigned int    np_ocp_ldo11               : 1; /* [2..2] 0������¼LDO11��������أ�1: ����¼LDO11������ء� */
        unsigned int    np_ocp_ldo12               : 1; /* [3..3] 0������¼LDO12��������أ�1: ����¼LDO12������ء� */
        unsigned int    np_ocp_ldo13               : 1; /* [4..4] 0������¼LDO13��������أ�1: ����¼LDO13������ء� */
        unsigned int    np_ocp_ldo14               : 1; /* [5..5] 0������¼LDO14��������أ�1: ����¼LDO14������ء� */
        unsigned int    np_ocp_ldo15               : 1; /* [6..6] 0������¼LDO15��������أ�1: ����¼LDO15������ء� */
        unsigned int    np_ocp_ldo16               : 1; /* [7..7] 0������¼LDO16��������أ�1: ����¼LDO16������ء� */
    } bits;
    unsigned int    u32;
}HI6551_NP_OCP_RECORD3_T;    /* �����������µ��¼3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_ldo17               : 1; /* [0..0] 0������¼LDO17��������أ�1: ����¼LDO17������ء� */
        unsigned int    np_ocp_ldo18               : 1; /* [1..1] 0������¼LDO18��������أ�1: ����¼LDO18������ء� */
        unsigned int    np_ocp_ldo19               : 1; /* [2..2] 0������¼LDO19��������أ�1: ����¼LDO19������ء� */
        unsigned int    np_ocp_ldo20               : 1; /* [3..3] 0������¼LDO20��������أ�1: ����¼LDO20������ء� */
        unsigned int    np_ocp_ldo21               : 1; /* [4..4] 0������¼LDO21��������أ�1: ����¼LDO21������ء� */
        unsigned int    np_ocp_ldo22               : 1; /* [5..5] 0������¼LDO22��������أ�1: ����¼LDO22������ء� */
        unsigned int    np_ocp_ldo23               : 1; /* [6..6] 0������¼LDO23��������أ�1: ����¼LDO23������ء� */
        unsigned int    np_ocp_ldo24               : 1; /* [7..7] 0������¼LDO24��������أ�1: ����¼LDO24������ء� */
    } bits;
    unsigned int    u32;
}HI6551_NP_OCP_RECORD4_T;    /* �����������µ��¼4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_lvs2                : 1; /* [0..0] 0������¼LVS2��������أ�1: ����¼LVS2������ء� */
        unsigned int    np_ocp_lvs3                : 1; /* [1..1] 0������¼LVS3��������أ�1: ����¼LVS3������ء� */
        unsigned int    np_ocp_lvs4                : 1; /* [2..2] 0������¼LVS4��������أ�1: ����¼LVS4������ء� */
        unsigned int    np_ocp_lvs5                : 1; /* [3..3] 0������¼LVS5��������أ�1: ����¼LVS5������ء� */
        unsigned int    np_ocp_lvs7                : 1; /* [4..4] 0������¼LVS7��������أ�1: ����¼LVS7������ء� */
        unsigned int    np_ocp_lvs6                : 1; /* [5..5] 0������¼LVS6��������أ�1: ����¼LVS6������ء� */
        unsigned int    np_ocp_lvs8                : 1; /* [6..6] 0������¼LVS8��������أ�1: ����¼LVS8������ء� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_NP_OCP_RECORD5_T;    /* �����������µ��¼5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_lvs9                : 1; /* [0..0] 0������¼LVS9��������أ�1: ����¼LVS9������ء� */
        unsigned int    np_ocp_lvs10               : 1; /* [1..1] 0������¼LVS10��������أ�1: ����¼LVS10������ء� */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI6551_NP_OCP_RECORD6_T;    /* �����������µ��¼6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_boost               : 1; /* [0..0] 0������¼BOOST�����������1: ����¼BOOST��������� */
        unsigned int    np_scp_boost               : 1; /* [1..1] 0������¼BOOST�������·��1: ����¼BOOST�����·�� */
        unsigned int    np_ovp_boost               : 1; /* [2..2] 0������¼BOOST�������ѹ��1: ����¼BOOST�����ѹ�� */
        unsigned int    np_uvp_boost               : 1; /* [3..3] 0������¼BOOST�����Ƿѹ��1: ����¼BOOST���Ƿѹ�� */
        unsigned int    np_ocp_classd              : 1; /* [4..4] 0������¼CLASSD�����������1: ����¼CLASSD��������� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6551_NP_OCP_RECORD7_T;    /* �����������µ��¼7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo_deb_sel            : 2; /* [1..0] ocpȥ��ʱ�䣺00��500us��01��1ms��10��2ms��11��4ms�� */
        unsigned int    en_ldo_ocp_deb             : 1; /* [2..2] 0��LDO OCP�����ز�ȥ����1��LDO OCP������ȥ����ע��LDO��LVS���á� */
        unsigned int    ocp_buck_deb_sel           : 2; /* [4..3] BUCK ��ocp��scpȥ��ʱ�䣺00��500us��01��1ms��10��2ms��11��4ms��ע��CLASSD��BOOST��BUCK���á� */
        unsigned int    en_buck_ocp_deb            : 1; /* [5..5] 0��BUCK OCP�����ز�ȥ����1��BUCK OCP������ȥ����ע��CLASSD��BUCK���á� */
        unsigned int    en_buck_scp_deb            : 1; /* [6..6] 0��BUCK SCP�����ز�ȥ����1��BUCK SCP������ȥ����ע��SCP��ʾ��·������ */
        unsigned int    en_bst_ocp_deb             : 1; /* [7..7] 0��BOOST ���������ز�ȥ����1��BOOST ����������ȥ����ע��BOOST ����������������·����ѹ��Ƿѹ����BUCK����ȥ��ʱ����� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_DEB_T;    /* OCPȥ�������ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vbus_det_0p9_ctrl          : 1; /* [0..0] 0������vbus_det<0.9V��⣻1:������vbus_det<0.9V��⡣ */
        unsigned int    vsys_2p5_ctrl              : 1; /* [1..1] 0������vsys< 2.5V��⣻1:������vsys<2.5V��⡣ */
        unsigned int    vsys_uv_ctrl               : 1; /* [2..2] 0������vsys< 2.7V/3.0V��⣻1:������vsys<2.7V/3.0V��⡣ */
        unsigned int    vsys_6p0_ctrl              : 1; /* [3..3] 0������vsys>6.0V��⣻1:������vsys>6.0��⡣ */
        unsigned int    otmp150_ctrl               : 1; /* [4..4] 0�����£�150�棩���ػ���1������(150��)�ػ��� */
        unsigned int    en_32kc                    : 1; /* [5..5] 0�� �ر�  CLK_32Cʱ�������1��  CLK_32C ʱ�����ʹ�ܡ� */
        unsigned int    en_32kb                    : 1; /* [6..6] 0�� �ر� CLK_32B ʱ�������1��  CLK_32B ʱ�����ʹ�ܡ� */
        unsigned int    en_32ka                    : 1; /* [7..7] 0�� �ر� CLK_32A ʱ�������1��  CLK_32A ʱ�����ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI6551_ONOFF8_T;    /* ���ؿ���8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_scp_ctrl_buck0_1       : 1; /* [0..0] ocp_scp_off_buck0_1����Ϊ1ʱ��ocp_scp_ctrl_buck0_1:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck0_1        : 1; /* [1..1] 0����������·��֧��BUCK1ģ���Զ��رգ�1���������·��֧��BUCK1ģ���Զ��ر� �� */
        unsigned int    ocp_scp_ctrl_buck2         : 1; /* [2..2] ocp_scp_off_buck2����Ϊ1ʱ��ocp_scp_ctrl_buck2:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck2          : 1; /* [3..3] 0���������·��֧��BUCK2ģ���Զ��رգ�1���������·��֧��BUCK2ģ���Զ��ر� �� */
        unsigned int    ocp_scp_ctrl_buck3         : 1; /* [4..4] ocp_scp_off_buck3����Ϊ1ʱ��ocp_scp_ctrl_buck3:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck3          : 1; /* [5..5] 0���������·��֧��BUCK3ģ���Զ��رգ�1���������·��֧��BUCK3ģ���Զ��ر� �� */
        unsigned int    ocp_scp_ctrl_buck4         : 1; /* [6..6] ocp_scp_off_buck4����Ϊ1ʱ��ocp_scp_ctrl_buck4:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck4          : 1; /* [7..7] 0���������·��֧��BUCK4ģ���Զ��رգ�1���������·��֧��BUCK4ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_SCP_MOD_CTRL1_T;    /* BUCK0-3�����Ͷ�·����ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_scp_ctrl_buck5         : 1; /* [0..0] ocp_scp_off_buck5����Ϊ1ʱ��ocp_scp_ctrl_buck5:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck5          : 1; /* [1..1] 0���������·��֧��BUCK5ģ���Զ��رգ�1���������·��֧��BUCK5ģ���Զ��ر� �� */
        unsigned int    ocp_scp_ctrl_buck6         : 1; /* [2..2] ocp_scp_off_buck6����Ϊ1ʱ��ocp_scp_ctrl_buck6:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck6          : 1; /* [3..3] 0���������·��֧��BUCK6ģ���Զ��رգ�1���������·��֧��BUCK6ģ���Զ��ر� �� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_OCP_SCP_MOD_CTRL2_T;    /* BUCK4-7�����Ͷ�·����ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo1              : 1; /* [0..0] ocp_off_ldo1����Ϊ1ʱ��ocp_ctrl_ldo1:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo1               : 1; /* [1..1] 0��������֧��LDO1ģ���Զ��رգ�1��������֧��LDO1ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo2              : 1; /* [2..2] ocp_off_ldo2����Ϊ1ʱ��ocp_ctrl_ldo2:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_ldo2               : 1; /* [3..3] 0��������֧��LDO2ģ���Զ��رգ�1��������֧��LDO2ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo3              : 1; /* [4..4] ocp_off_ldo3����Ϊ1ʱ��ocp_ctrl_ldo3:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_ldo3               : 1; /* [5..5] 0��������֧��LDO3ģ���Զ��رգ�1��������֧��LDO3ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo4              : 1; /* [6..6] ocp_off_ldo4����Ϊ1ʱ��ocp_ctrl_ldo4:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo4               : 1; /* [7..7] 0��������֧��LDO4ģ���Զ��رգ�1��������֧��LDO4ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL3_T;    /* LDO1-4��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo5              : 1; /* [0..0] ocp_off_ldo5����Ϊ1ʱ��ocp_ctrl_ldo5:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo5               : 1; /* [1..1] 0��������֧��LDO5ģ���Զ��رգ�1��������֧��LDO5ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo6              : 1; /* [2..2] ocp_off_ldo6����Ϊ1ʱ��ocp_ctrl_ldo6:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo6               : 1; /* [3..3] 0��������֧��LDO6ģ���Զ��رգ�1��������֧��LDO6ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo7              : 1; /* [4..4] ocp_off_ldo7����Ϊ1ʱ��ocp_ctrl_ldo7:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo7               : 1; /* [5..5] 0��������֧��LDO7ģ���Զ��رգ�1��������֧��LDO7ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo8              : 1; /* [6..6] ocp_off_ldo8����Ϊ1ʱ��ocp_ctrl_ldo8:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo8               : 1; /* [7..7] 0��������֧��LDO8ģ���Զ��رգ�1��������֧��LDO8ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL4_T;    /* LDO5-8��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo9              : 1; /* [0..0] ocp_off_ldo9����Ϊ1ʱ��ocp_ctrl_ldo9:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo9               : 1; /* [1..1] 0��������֧��LDO9ģ���Զ��رգ�1��������֧��LDO9ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo10             : 1; /* [2..2] ocp_off_ldo10����Ϊ1ʱ��ocp_ctrl_ldo10:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo10              : 1; /* [3..3] 0��������֧��LDO10ģ���Զ��رգ�1��������֧��LDO10ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo11             : 1; /* [4..4] ocp_off_ldo11����Ϊ1ʱ��ocp_ctrl_ldo11:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo11              : 1; /* [5..5] 0��������֧��LDO11ģ���Զ��رգ�1��������֧��LDO11ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo12             : 1; /* [6..6] ocp_off_ldo12����Ϊ1ʱ��ocp_ctrl_ldo12:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo12              : 1; /* [7..7] 0��������֧��LDO12ģ���Զ��رգ�1��������֧��LDO12ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL5_T;    /* LDO9-12��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo13             : 1; /* [0..0] ocp_off_ldo13����Ϊ1ʱ��ocp_ctrl_ldo13:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo13              : 1; /* [1..1] 0��������֧��LDO13ģ���Զ��رգ�1��������֧��LDO13ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo14             : 1; /* [2..2] ocp_off_ldo14����Ϊ1ʱ��ocp_ctrl_ldo14:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo14              : 1; /* [3..3] 0��������֧��LDO14ģ���Զ��رգ�1��������֧��LDO14ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo15             : 1; /* [4..4] ocp_off_ldo15����Ϊ1ʱ��ocp_ctrl_ldo15:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo15              : 1; /* [5..5] 0��������֧��LDO15ģ���Զ��رգ�1��������֧��LDO15ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo16             : 1; /* [6..6] ocp_off_ldo16����Ϊ1ʱ��ocp_ctrl_ldo16:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo16              : 1; /* [7..7] 0��������֧��LDO16ģ���Զ��رգ�1��������֧��LDO16ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL6_T;    /* LDO13-16��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo17             : 1; /* [0..0] ocp_off_ldo17����Ϊ1ʱ��ocp_ctrl_ldo17:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo17              : 1; /* [1..1] 0��������֧��LDO17ģ���Զ��رգ�1��������֧��LDO17ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo18             : 1; /* [2..2] ocp_off_ldo18����Ϊ1ʱ��ocp_ctrl_ldo18:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo18              : 1; /* [3..3] 0��������֧��LDO18ģ���Զ��رգ�1��������֧��LDO18ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo19             : 1; /* [4..4] ocp_off_ldo19����Ϊ1ʱ��ocp_ctrl_ldo19:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo19              : 1; /* [5..5] 0��������֧��LDO19ģ���Զ��رգ�1��������֧��LDO19ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo20             : 1; /* [6..6] ocp_off_ldo20����Ϊ1ʱ��ocp_ctrl_ldo20:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_ldo20              : 1; /* [7..7] 0��������֧��LDO20ģ���Զ��رգ�1��������֧��LDO20ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL7_T;    /* LDO17-20��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo21             : 1; /* [0..0] ocp_off_ldo21����Ϊ1ʱ��ocp_ctrl_ldo21:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_ldo21              : 1; /* [1..1] 0��������֧��LDO21ģ���Զ��رգ�1��������֧��LDO21ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo22             : 1; /* [2..2] ocp_off_ldo22����Ϊ1ʱ��ocp_ctrl_ldo22:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo22              : 1; /* [3..3] 0��������֧��LDO22ģ���Զ��رգ�1��������֧��LDO22ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo23             : 1; /* [4..4] ocp_off_ldo23����Ϊ1ʱ��ocp_ctrl_ldo23:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo23              : 1; /* [5..5] 0��������֧��LDO23ģ���Զ��رգ�1��������֧��LDO23ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo24             : 1; /* [6..6] ocp_off_ldo24����Ϊ1ʱ��ocp_ctrl_ldo24:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo24              : 1; /* [7..7] 0��������֧��LDO24ģ���Զ��رգ�1��������֧��LDO24ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL8_T;    /* LDO21-ldo23��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_lvs2              : 1; /* [0..0] ocp_off_lvs2����Ϊ1ʱ��ocp_ctrl_lvs2:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs2               : 1; /* [1..1] 0��������֧��LVS2ģ���Զ��رգ�1��������֧��LVS2ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_lvs3              : 1; /* [2..2] ocp_off_lvs3����Ϊ1ʱ��ocp_ctrl_lvs3:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs3               : 1; /* [3..3] 0��������֧��LVS3ģ���Զ��رգ�1��������֧��LVS3ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_lvs4              : 1; /* [4..4] ocp_off_lvs4����Ϊ1ʱ��ocp_ctrl_lvs4:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs4               : 1; /* [5..5] 0��������֧��LVS4ģ���Զ��رգ�1��������֧��LVS4ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_lvs5              : 1; /* [6..6] ocp_off_lvs5����Ϊ1ʱ��ocp_ctrl_lvs5:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs5               : 1; /* [7..7] 0��������֧��LVS5ģ���Զ��رգ�1��������֧��LVS5ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL9_T;    /* LVS2-5��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_lvs7              : 1; /* [0..0] ocp_off_lvs7����Ϊ1ʱ��ocp_ctrl_lvs7:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs7               : 1; /* [1..1] 0��������֧��lvs7ģ���Զ��رգ�1��������֧��lvs7ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_lvs6              : 1; /* [2..2] ocp_off_lvs6����Ϊ1ʱ��ocp_ctrl_lvs6:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs6               : 1; /* [3..3] 0��������֧��lvs6ģ���Զ��رգ�1��������֧��lvs6ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_lvs8              : 1; /* [4..4] ocp_off_lvs7����Ϊ1ʱ��ocp_ctrl_lvs7:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs8               : 1; /* [5..5] 0��������֧��LVS8ģ���Զ��رգ�1��������֧��LVS8ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_lvs9              : 1; /* [6..6] ocp_off_lvs9����Ϊ1ʱ��ocp_ctrl_lvs9:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs9               : 1; /* [7..7] 0��������֧��LVS9ģ���Զ��رգ�1��������֧��LVS9ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL10_T;    /* LVS2-5��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_lvs10             : 1; /* [0..0] ocp_off_lvs10����Ϊ1ʱ��ocp_ctrl_lvs10:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs10              : 1; /* [1..1] 0��������֧��LVS10ģ���Զ��رգ�1��������֧��LVS10ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_bst               : 1; /* [2..2] ocp_off_bst����Ϊ1ʱ��ocp_ctrl_bst:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_bst                : 1; /* [3..3] 0������/��·/��ѹ/Ƿѹ��֧��BOOSTģ���Զ��رգ�1������/��·/��ѹ/Ƿѹ��֧��BOOSTģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_classd            : 1; /* [4..4] ocp_off_classd����Ϊ1ʱ��ocp_ctrl_classd:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_classd             : 1; /* [5..5] 0��������֧��CLASSDģ���Զ��رգ�1��������֧��CLASSDģ���Զ��ر� �� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_OCP_MOD_CTRL11_T;    /* LVS9-10,BOOST��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    en_buck0_int               : 1; /* [0..0] BUCK0����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck1_int               : 1; /* [1..1] BUCK1����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck2_int               : 1; /* [2..2] BUCK2����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck3_int               : 1; /* [3..3] BUCK3����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck4_int               : 1; /* [4..4] BUCK4����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck5_int               : 1; /* [5..5] BUCK5����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck6_int               : 1; /* [6..6] BUCK6����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ENABLE1_T;    /* ��Դģ��ʹ��1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dis_buck0_int              : 1; /* [0..0] BUCK0���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck1_int              : 1; /* [1..1] BUCK1���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck2_int              : 1; /* [2..2] BUCK2���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck3_int              : 1; /* [3..3] BUCK3���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck4_int              : 1; /* [4..4] BUCK4���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck5_int              : 1; /* [5..5] BUCK5���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck6_int              : 1; /* [6..6] BUCK6���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DISABLE1_T;    /* ��Դģ��ر�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    st_buck0_int               : 1; /* [0..0] BUCK0����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ���������OTP_PWRSEL(OTP�ϵ�ʱ��ѡ��):00 ��1'b1 �ϵ�ʱ��1 ��01 ��1'b0 �ϵ�ʱ��2 ��10 ��1'b0 �ϵ�ʱ��3 ��11 : 1'b0 �ϵ�ʱ��4 �� */
        unsigned int    st_buck1_int               : 1; /* [1..1] BUCK1����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ���������OTP_PWRSEL(OTP�ϵ�ʱ��ѡ��):00 ��1'b1 �ϵ�ʱ��1 ��01 ��1'b0 �ϵ�ʱ��2 ��10 ��1'b0 �ϵ�ʱ��3 ��11 : 1'b0 �ϵ�ʱ��4 �� */
        unsigned int    st_buck2_int               : 1; /* [2..2] BUCK2����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_buck3_int               : 1; /* [3..3] BUCK3����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_buck4_int               : 1; /* [4..4] BUCK4����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_buck5_int               : 1; /* [5..5] BUCK5����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_buck6_int               : 1; /* [6..6] BUCK6����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ONOFF_STATUS1_T;    /* ��Դģ�鿪��״̬1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo1_int                : 1; /* [0..0] LDO1����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo2_int                : 1; /* [1..1] LDO2����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo3_buck_int           : 1; /* [2..2] BUCK��LDO3ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo4_int                : 1; /* [3..3] LDO4����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo5_int                : 1; /* [4..4] LDO5����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo6_int                : 1; /* [5..5] LDO6����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo7_int                : 1; /* [6..6] LDO7����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo8_int                : 1; /* [7..7] LDO8����ʹ�ܣ�д1�������Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6551_ENABLE2_T;    /* ��Դģ��ʹ��2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dis_ldo1_int               : 1; /* [0..0] LDO1���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo2_int               : 1; /* [1..1] LDO2���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo3_buck_int          : 1; /* [2..2] BUCK��LDO3��ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo4_int               : 1; /* [3..3] LDO4���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo5_int               : 1; /* [4..4] LDO5���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo6_int               : 1; /* [5..5] LDO6���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo7_int               : 1; /* [6..6] LDO7���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo8_int               : 1; /* [7..7] LDO8���ؽ�ֹ��д1�رգ��Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6551_DISABLE2_T;    /* ��Դģ��ر�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    st_ldo1_int                : 1; /* [0..0] LDO1����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo2_int                : 1; /* [1..1] LDO2����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo3_buck_int           : 1; /* [2..2] BUCK��LDO3ʱ�ܿ���״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo4_int                : 1; /* [3..3] LDO4����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo5_int                : 1; /* [4..4] LDO5����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ���������OTP_PWRSEL(OTP�ϵ�ʱ��ѡ��):00 ��1'b1 �ϵ�ʱ��1 ��01 ��1'b0 �ϵ�ʱ��2 ��10 ��1'b0 �ϵ�ʱ��3 ��11 : 1'b0 �ϵ�ʱ��4 �� */
        unsigned int    st_ldo6_int                : 1; /* [5..5] LDO6����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo7_int                : 1; /* [6..6] LDO7����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo8_int                : 1; /* [7..7] LDO8����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6551_ONOFF_STATUS2_T;    /* ��Դģ�鿪��״̬2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo10_int               : 1; /* [0..0] LDO10����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo12_int               : 1; /* [1..1] LDO12����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo13_int               : 1; /* [2..2] LDO13����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo14_int               : 1; /* [3..3] LDO14����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo15_int               : 1; /* [4..4] LDO15����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo16_int               : 1; /* [5..5] LDO16����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo17_int               : 1; /* [6..6] LDO17����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo18_int               : 1; /* [7..7] LDO18����ʹ�ܣ�д1�������Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6551_ENABLE3_T;    /* ��Դģ��ʹ��3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dis_ldo10_int              : 1; /* [0..0] LDO10���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo12_int              : 1; /* [1..1] LDO12���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo13_int              : 1; /* [2..2] LDO13���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo14_int              : 1; /* [3..3] LDO14���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo15_int              : 1; /* [4..4] LDO15���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo16_int              : 1; /* [5..5] LDO16���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo17_int              : 1; /* [6..6] LDO17���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo18_int              : 1; /* [7..7] LDO18���ؽ�ֹ��д1�رգ��Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6551_DISABLE3_T;    /* ��Դģ��ر�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    st_ldo10_int               : 1; /* [0..0] LDO10����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo12_int               : 1; /* [1..1] LDO12����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo13_int               : 1; /* [2..2] LDO13����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo14_int               : 1; /* [3..3] LDO14����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo15_int               : 1; /* [4..4] LDO15����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo16_int               : 1; /* [5..5] LDO16����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo17_int               : 1; /* [6..6] LDO17����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo18_int               : 1; /* [7..7] LDO18����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6551_ONOFF_STATUS3_T;    /* ��Դģ�鿪��״̬3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo19_int               : 1; /* [0..0] LDO19����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo20_int               : 1; /* [1..1] LDO20����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo21_int               : 1; /* [2..2] LDO21����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo22_int               : 1; /* [3..3] LDO22����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo23_int               : 1; /* [4..4] LDO23����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo24_int               : 1; /* [5..5] LDO24����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo3_batt_int           : 1; /* [6..6] BATT��LDO3ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ENABLE4_T;    /* ��Դģ��ʹ��4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dis_ldo19_int              : 1; /* [0..0] LDO19���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo20_int              : 1; /* [1..1] LDO20���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo21_int              : 1; /* [2..2] LDO21���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo22_int              : 1; /* [3..3] LDO22���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo23_int              : 1; /* [4..4] LDO23���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo24_int              : 1; /* [5..5] LDO24���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo3_batt_int          : 1; /* [6..6] BATT��LDO3��ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DISABLE4_T;    /* ��Դģ��ر�4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    st_ldo19_int               : 1; /* [0..0] LDO19����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ���������OTP_PWRSEL(OTP�ϵ�ʱ��ѡ��):00 ��1'b1 �ϵ�ʱ��1 ��01 ��1'b0 �ϵ�ʱ��2 ��10 ��1'b0 �ϵ�ʱ��3 ��11 : 1'b0 �ϵ�ʱ��4 �� */
        unsigned int    st_ldo20_int               : 1; /* [1..1] LDO20����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo21_int               : 1; /* [2..2] LDO21����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo22_int               : 1; /* [3..3] LDO22����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo23_int               : 1; /* [4..4] LDO23����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo24_int               : 1; /* [5..5] LDO24����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo3_batt_int           : 1; /* [6..6] BATT��LDO3����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ONOFF_STATUS4_T;    /* ��Դģ�鿪��״̬4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_lvs2_int                : 1; /* [0..0] LVS2����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_lvs3_int                : 1; /* [1..1] LVS3����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_lvs4_int                : 1; /* [2..2] LVS4����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_lvs5_int                : 1; /* [3..3] LVS5����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_lvs7_int                : 1; /* [4..4] LVS7����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_lvs6_int                : 1; /* [5..5] LVS6����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_lvs8_int                : 1; /* [6..6] LVS8����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_lvs9_int                : 1; /* [7..7] LVS9����ʹ�ܣ�д1�������Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6551_ENABLE5_T;    /* ��Դģ��ʹ��5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dis_lvs2_int               : 1; /* [0..0] LVS2���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_lvs3_int               : 1; /* [1..1] LVS3���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_lvs4_int               : 1; /* [2..2] LVS4���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_lvs5_int               : 1; /* [3..3] LVS5���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_lvs7_int               : 1; /* [4..4] LVS7���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_lvs6_int               : 1; /* [5..5] LVS6���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_lvs8_int               : 1; /* [6..6] LVS8���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_lvs9_int               : 1; /* [7..7] LVS9���ؽ�ֹ��д1�رգ��Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6551_DISABLE5_T;    /* ��Դģ��ر�5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    st_lvs2_int                : 1; /* [0..0] LVS2����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_lvs3_int                : 1; /* [1..1] LVS3����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_lvs4_int                : 1; /* [2..2] LVS4����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_lvs5_int                : 1; /* [3..3] LVS5����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_lvs7_int                : 1; /* [4..4] LVS7����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_lvs6_int                : 1; /* [5..5] LVS6����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ���������OTP_PWRSEL(OTP�ϵ�ʱ��ѡ��):00 ��1'b1 �ϵ�ʱ��1 ��01 ��1'b0 �ϵ�ʱ��2 ��10 ��1'b0 �ϵ�ʱ��3 ��11 : 1'b0 �ϵ�ʱ��4 �� */
        unsigned int    st_lvs8_int                : 1; /* [6..6] LVS8����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_lvs9_int                : 1; /* [7..7] LVS9����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6551_ONOFF_STATUS5_T;    /* ��Դģ�鿪��״̬5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_lvs10_int               : 1; /* [0..0] LVS10����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ENABLE6_T;    /* ��Դģ��ʹ��6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dis_lvs10_int              : 1; /* [0..0] LVS10���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DISABLE6_T;    /* ��Դģ��ر�6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    st_lvs10_int               : 1; /* [0..0] LVS10����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ONOFF_STATUS6_T;    /* ��Դģ�鿪��״̬6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_cp2_int                 : 1; /* [0..0] cp2_always_on_int = 1'b0 :usb_chg_pump �������ã�0���رգ�1��������PMU����USB PHY��ѹ������·����VBUS_DET>1.375Vʱ���ϱ��жϣ���ͨ���ر�en_cp2���ж�VBUS��USB PHy��ͨ·�� */
        unsigned int    cp2_always_on_int          : 1; /* [1..1] usb_chg_pump�������ã�������Ϊ1ʱ��usb_chg_pump�Ŀ���ֻ����λ�йأ���Ϊ0ʱ������en_cp2_int�򿪻��߹رգ�0��usb_chg_pump�رգ�1��usb_chg_pump�򿪡� */
        unsigned int    reserved                   : 6; /* [7..2] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ENABLE7_T;    /* ��Դģ��ʹ��7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo9_int                : 1; /* [0..0] 0���ر�LDO9 ��1������LDO9 �� */
        unsigned int    sim0_en_int                : 1; /* [1..1] simcard0ת����·��ʹ���źţ�0���ر�simcard0ת����· ��1������simcard0ת����· �� */
        unsigned int    en_ldo11_int               : 1; /* [2..2] 0���ر�LDO11 ��1������LDO11 �� */
        unsigned int    sim1_en_int                : 1; /* [3..3] simcard1ת����·��ʹ���źţ�0���ر�simcard1ת����· ��1������simcard1ת����· �� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_SIMCARD_EN_T;    /* SIM��ʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    simcard0_resv              : 2; /* [1..0] ����CLK�����������������simcard0_resv[1]����P�ܵ�����������simcard0_resv[0]����N�ܵ�����������0������������������1���������������� */
        unsigned int    simcard0_bbrp              : 1; /* [2..2] simcard0��DATAIO BB����������ʹ���źţ�0�������������裻1���ر��������� �� */
        unsigned int    simcard0_simrp             : 1; /* [3..3] simcard0��DATAIO SIM������������ʹ���źţ�0�������������裻1���ر��������� �� */
        unsigned int    simcard0_200ns_en          : 1; /* [4..4] simcard0 200ns��������ʱ���ʹ���źţ�0���رտ����������� ��1����ʼ������������ �� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6551_SIM0_CFG_T;    /* SIM��0���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    simcard1_resv              : 2; /* [1..0] ����CLK�����������������simcard1_resv[1]����P�ܵ�����������simcard1_resv[0]����N�ܵ�����������0������������������1���������������� */
        unsigned int    simcard1_bbrp              : 1; /* [2..2] simcard1��DATAIO BB����������ʹ���źţ�0�������������裻1���ر��������� �� */
        unsigned int    simcard1_simrp             : 1; /* [3..3] simcard1��DATAIO SIM������������ʹ���źţ�0�������������裻1���ر��������� �� */
        unsigned int    simcard1_200ns_en          : 1; /* [4..4] simcard1 200ns��������ʱ���ʹ���źţ�0���رտ����������� ��1����ʼ������������ �� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6551_SIM1_CFG_T;    /* SIM��1���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    simcard_deb_sel            : 5; /* [4..0] SIMCARD0��SIMCARD1������ȥ��ʱ��ɵ���0x3 : 120us0x4 : 150us0x5 : 180us0x6 : 210us0x7 : 240us0x8 : 270us0x9 : 300us0xa : 330us0xb : 360us0xc : 390us0xd : 420us0xe : 450us0xf : 480us0x10: 510us0x11: 540us0x12: 570us0x13: 600us */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6551_SIM_DEB_T;    /* SIM���ж�ȥ���ĵ��ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    en_eco_buck3_int           : 1; /* [0..0] ����BUCK3�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_buck4_int           : 1; /* [1..1] ����BUCK4�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_buck5_int           : 1; /* [2..2] ����BUCK5�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_buck6_int           : 1; /* [3..3] ����BUCK6�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ECO_MOD_CFG1_T;    /* ��Դģ���Ƿ����PMU����ECOģʽ����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_eco_ldo3_int            : 1; /* [0..0] ����LDO3�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo7_int            : 1; /* [1..1] ����LDO7�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo9_int            : 1; /* [2..2] ����LDO9�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo10_int           : 1; /* [3..3] ����LDO10�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo11_int           : 1; /* [4..4] ����LDO11�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo12_int           : 1; /* [5..5] ����LDO12�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo22_int           : 1; /* [6..6] ����LDO22�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo24_int           : 1; /* [7..7] ����LDO24�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
    } bits;
    unsigned int    u32;
}HI6551_ECO_MOD_CFG2_T;    /* ��Դģ���Ƿ����PMU����ECOģʽ����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    force_eco_buck3_int        : 1; /* [0..0] �����Ƿ�ǿ��ʹBUCK3����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_buck4_int        : 1; /* [1..1] �����Ƿ�ǿ��ʹBUCK4����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_buck5_int        : 1; /* [2..2] �����Ƿ�ǿ��ʹBUCK5����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_buck6_int        : 1; /* [3..3] �����Ƿ�ǿ��ʹBUCK6����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_ECO_MOD_CFG3_T;    /* ��Դ�Ƿ�ǿ����PMU����ECOģʽ����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    force_eco_ldo3_int         : 1; /* [0..0] �����Ƿ�ǿ��ʹLDO3����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo7_int         : 1; /* [1..1] �����Ƿ�ǿ��ʹLDO7����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo9_int         : 1; /* [2..2] �����Ƿ�ǿ��ʹLDO9����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo10_int        : 1; /* [3..3] �����Ƿ�ǿ��ʹLDO10����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo11_int        : 1; /* [4..4] �����Ƿ�ǿ��ʹLDO11����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo12_int        : 1; /* [5..5] �����Ƿ�ǿ��ʹLDO12����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo22_int        : 1; /* [6..6] �����Ƿ�ǿ��ʹLDO22����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo24_int        : 1; /* [7..7] �����Ƿ�ǿ��ʹLDO24����ECOģʽ��0:�����룻1�����롣 */
    } bits;
    unsigned int    u32;
}HI6551_ECO_MOD_CFG4_T;    /* ��Դ�Ƿ�ǿ����PMU����ECOģʽ����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    eco_pwrsel                 : 2; /* [1..0] PMU�����͹���ʱ��ѡ��00��PMU�����͹���ʱ��ͼ���1��01��PMU�����͹���ʱ��ͼ���2��10��PMU�����͹���ʱ��ͼ���1��11��PMU�����͹���ʱ��ͼ���1�� */
        unsigned int    peri_en_ctrl_ldo12         : 1; /* [2..2] LDO12�Ƿ���Peri_EN�������µ�:0�� ���ܿ� ��1�� �ܿ� �� */
        unsigned int    peri_en_ctrl_lvs9          : 1; /* [3..3] LVS9�Ƿ���Peri_EN�������µ�:0�� ���ܿ� ��1�� �ܿ� �� */
        unsigned int    peri_en_ctrl_ldo8          : 1; /* [4..4] LDO8�Ƿ���Peri_EN�������µ�:0�� ���ܿ� ��1�� �ܿ� �� */
        unsigned int    peri_en_ctrl_buck3         : 1; /* [5..5] BUCK3�Ƿ���Peri_EN�������µ�:0�� ���ܿ� ��1�� �ܿ� �� */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_ENB3_ECO_MARK_T;    /* ��ENB3Ӳ�ߺ�ECO������ص������źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_osc_d               : 4; /* [3..0] ����buck01Ƶ��,Ĭ��Ƶ��Ϊ1.2MHz��Ƶ�ʿɵ���ΧԼΪ300KHz~3MHz�� */
        unsigned int    buck0_pfm_vth_sel          : 1; /* [4..4] �����л�pfm�Ƿ�ѡ����NMOS��ֵ�Զ��л�PWM��0��PFMʱ�����Զ��л�ǿ��PWM ��1��PFMʱ�Զ��л�ǿ��PWM �� */
        unsigned int    buck0_sc_sel               : 2; /* [6..5] б�²������裬SENSE���裬б�²������ݵ��� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG1_ADJ_T;    /* BUCK0��BUCK1����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_mod_sel             : 2; /* [1..0] BUCK01��ģʽѡ��00�������л���X1��ǿ��PWM; */
        unsigned int    buck0_bt_sel               : 1; /* [2..2] ���ع�blanking time���ڣ�0:û����ʱ��1:����10ns��ʱ�� */
        unsigned int    buck0_pd_sel               : 1; /* [3..3] DMD״̬��������ȫ������ʹ��:0�����θù��� ��1�����øù��� �� */
        unsigned int    buck0_burst_drv_ctr        : 1; /* [4..4] ���������л�PFMʱ��ѡ��burst�Թ��ʹܵĿ��ƣ�0�����������л�PFMʱ��ѡ��burst����P/N���ʹ� ��1�����������л�PFMʱ��ѡ��burstֻ����P���ʹܡ� */
        unsigned int    buck01_ocp_mod_sel         : 1; /* [5..5] OCP ���ģʽѡ��Ŀ��أ�0���� ��1���� �� */
        unsigned int    buck01_ocp_clamp_sel       : 1; /* [6..6] OCP clamp���ܵĿ��أ�0���� ��1���� �� */
        unsigned int    buck01_ocp_shied_sel       : 1; /* [7..7] OCP�������ι��ܵĿ��أ�0���� ��1���� �� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG2_ADJ_T;    /* BUCK0��BUCK1����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_vc_sel               : 2; /* [1..0] buck01 �����л�pfm EA ��ֵ��ѹ���õ�����ڣ�00:45k��01:60k��10:75k��11:90k�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck01_auto_pfm_ctr        : 2; /* [5..4] buck01 �����л�pfm�������ƣ�00�������л�����PFM��·Ӱ�죻����������ԭ�������л�ģʽ�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG3_ADJ_T;    /* BUCK0��BUCK1����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_isc_sel              : 2; /* [1..0] buck01 �����л�pfmʱ��з�ֵ��������������(00~11����)�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck0_ipk_sel              : 2; /* [5..4] buck01 �����л�pfmʱ��з�ֵ�������Ƶ�����������00:21k��01:28k��10:35k��11:41k�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG4_ADJ_T;    /* BUCK0��BUCK1����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_dt_sel              : 2; /* [1..0] buck01����ʱ����ڣ�ÿbit�������ƣ�:0�������ӳ�5ns��1���������ӳ١� */
        unsigned int    buck01_pg_dt_sel           : 1; /* [2..2] buck01 N�ܵ�P������ģʽѡ��0������������������ģʽ ��1����������������ģʽ�� */
        unsigned int    buck01_ng_dt_sel           : 1; /* [3..3] buck01 P�ܵ�N������ģʽѡ��0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck01_sft_sel             : 1; /* [4..4] buck01��������ʽѡ�� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG5_ADJ_T;    /* BUCK0��BUCK1����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_pg_p_sel            : 2; /* [1..0] buck01 P power��������ӦPMOS�����������ڣ�00~11��С���������� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck01_pg_n_sel            : 2; /* [5..4] buck01 P power��������ӦNMOS�����������ڣ�00~11��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG6_ADJ_T;    /* BUCK0��BUCK1����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_ng_p_sel            : 2; /* [1..0] buck01 N power��������ӦPMOS�����������ڣ�00~11��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck01_ng_n_sel            : 2; /* [5..4] buck01 N power��������ӦNMOS�����������ڣ�00~11��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG7_ADJ_T;    /* BUCK0��BUCK1����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_ccm_sel              : 2; /* [1..0] buck0���ڲ�������������С��00~11����sens�������� */
        unsigned int    buck1_ccm_sel              : 2; /* [3..2] buck1���ڲ�������������С��00~11����sens�������� */
        unsigned int    buck0_ccc_sel              : 2; /* [5..4] ����isns�������������ĵ��ݣ�0�����ӵ��� ��1���ӵ��� �� */
        unsigned int    buck0_cs_sel               : 2; /* [7..6] ����sense�ܴ��ĵ��ݣ�00:0p��01:0.2p��10:0.4p��11:0.6p�� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG8_ADJ_T;    /* BUCK0��BUCK1����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_dmd_sel              : 2; /* [1..0] BUCK DMD������ �� */
        unsigned int    buck01_ton_off             : 1; /* [2..2] ��Сռ�ձȵ��ڿ���λ��0���رյ��ڹ��ܣ�1���������ڹ��ܡ� */
        unsigned int    buck01_pfm_sleep           : 1; /* [3..3] ����PFM����ʱ����SLEEPģʽ�ź�BUCK01����sleepģʽѡ��:0��BUCK�˳�sleepģʽ��1��BUCK����sleepģʽ��buck1_enp=buck1_en_ss=0 */
        unsigned int    buck01_ton_on              : 2; /* [5..4] ��Сռ�ձȵ���λ(00~11����)�� */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG9_ADJ_T;    /* BUCK0��BUCK1����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_new_dmd_sel         : 5; /* [4..0] ��dmd�ṹdmd�������� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG10_ADJ_T;    /* BUCK0��BUCK1����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_ocp_sel              : 4; /* [3..0] OCP ������ѡ��λ:0x3 :ϵͳ������ʼʱ����PVDD�½���3.15Vʱ��0xb :ϵͳ��������������ʱ �� */
        unsigned int    buck01_ocp_en              : 1; /* [4..4] ѡ��OCP���ܵĿ��أ�0���� ��1�������� */
        unsigned int    buck01_dmd_en              : 1; /* [5..5] ѡ��DMD��OCP���ܵĿ��� ��0���� ��1�������� */
        unsigned int    buck01_ea_sel              : 1; /* [6..6] ����ģʽ�����źţ�0���ֱ��ø���PWM�źţ�1������buck0 PWM�źš� */
        unsigned int    buck01_clk_sel             : 1; /* [7..7] ����ʱ��ѡ���źš�0����ͬclk;1����buck clk��λ��180deg�� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG11_ADJ_T;    /* BUCK0��BUCK1����11�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_sleep_depth_adj      : 2; /* [1..0] BUCK0 SLEEPģʽ���ڣ�bit[1]: ˯����ȿ��Ƶ���:0������˯�ߣ�1������˯�ߡ�Bit[0]:PFM�Ƚ���ƫ�õ�������:0���Ӵ������1����С������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck0_ea_comp_cap          : 2; /* [5..4] BUCK0 EA�ڲ���·�������ݵ���00��11�������ݴ�С���� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG12_ADJ_T;    /* BUCK0��BUCK1����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_slope_gen           : 3; /* [2..0] buck0б�²����仯����000-111�����ӣ� */
        unsigned int    buck01_pdn_lx_det          : 1; /* [3..3] ʹ��LX��������ʱ����Ƶ�·��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    buck01_sleep_dmd           : 1; /* [4..4] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck01_dmd_shield_n        : 1; /* [5..5] �������dmd�����źţ�0:���Σ�1�������Ρ� */
        unsigned int    buck01_ocp_delay_sel       : 1; /* [6..6] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck01_dmd_clamp           : 1; /* [7..7] ��dmdǶλʹ���ź�:0�����ϣ�1�������ϡ� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG13_ADJ_T;    /* BUCK0��BUCK1����13�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_slope_dc            : 2; /* [1..0] buck0 slope dcֵ�趨ѡ�� */
        unsigned int    buck01_unsleep             : 1; /* [2..2] buck01 ECO ����ѡ��0�� ����sleep��1��������sleep�� */
        unsigned int    buck01_dmd_float           : 1; /* [3..3] buck01 dmd�Ƚ���clampѡ��0��ʹ��clamp��·��1����ʹ��clamp��·�� */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG14_ADJ_T;    /* BUCK0��BUCK1����14�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_comp_adj1            : 8; /* [7..0] BUCK�ȶ��Ե��ڼĴ���1:bit[7]ѡ��ͬ��б�²�������0���Ӵ󲹳�����1����С��������bit[6]�����˷Ÿ�Ƶ�������Ƶ��ݵĴ�С��0���Ӵ󲹳�����1����С��������bit[6:3]���������صĲ��������ڵ���ѡ��λ��Bit[2:0] �����Ŵ����絼������ */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG15_ADJ_T;    /* BUCK0��BUCK1����15�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_reserved1           : 8; /* [7..0] Ԥ���Ĵ���1�� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG16_ADJ_T;    /* BUCK0��BUCK1����16�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck01_reserved0           : 8; /* [7..0] Ԥ���Ĵ���0�� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK01_REG17_ADJ_T;    /* BUCK0��BUCK1����17�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_adj_rlx              : 4; /* [3..0] buck2 LX�����˲�������ڣ�ÿbit�������ƣ�:0�����費���� ��1��������롣 */
        unsigned int    buck2_adj_clx              : 4; /* [7..4] buck2 LX�����˲����ݵ��ڣ�ÿbit�������ƣ�:0�����ݲ����� ��1�����ݽ��롣 */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG1_ADJ_T;    /* BUCK2����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_new_dmd_sel          : 5; /* [4..0] ��dmd�ṹdmd�������� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG2_ADJ_T;    /* BUCK2����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_shield_i             : 2; /* [1..0] dmd�����źŶ�Ӧ�������ڣ�00~11���� */
        unsigned int    buck2_en_regop_clamp       : 1; /* [2..2] regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܣ�0����ʹ�ܡ� */
        unsigned int    buck2_dmd_clamp            : 1; /* [3..3] ��dmdǶλʹ���źţ�0�����ϣ�1�������ϡ� */
        unsigned int    buck2_ocp_delay_sel        : 1; /* [4..4] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck2_dmd_shield_n         : 1; /* [5..5] �������dmd�����źţ�0:���Σ�1�������Ρ� */
        unsigned int    buck2_sleep_dmd            : 1; /* [6..6] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck2_pdn_lx_det           : 1; /* [7..7] ʹ��LX��������ʱ����Ƶ�·��0����ʹ�ܣ�1��ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG3_ADJ_T;    /* BUCK2����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_ocp_sel              : 2; /* [1..0] buck2 OCP�������0x0: 2.95A ��0x1: 3.74A ��0x2: 4.12A ��0x3: 4.72A �� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck2_dmd_sel              : 3; /* [6..4] buck2 dmd��ѡ��0x0~0x7���󣩡� */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG4_ADJ_T;    /* BUCK2����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_ng_dt_sel            : 1; /* [0..0] buck2 P�ܵ�N������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck2_pg_dt_sel            : 1; /* [1..1] buck2 N�ܵ�P������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck2_sft_sel              : 1; /* [2..2] buck2��������ʽѡ�� */
        unsigned int    buck2_sleep                : 1; /* [3..3] buck2 sleepģʽѡ��0������ ��1��sleep �� */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG5_ADJ_T;    /* BUCK2����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_pg_n_sel             : 2; /* [1..0] buck2 P power��������ӦNMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck2_pg_p_sel             : 2; /* [5..4] buck2 P power��������ӦPMOS�����������ڣ�0x0~0x3�������������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG6_ADJ_T;    /* BUCK2����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_ng_n_sel             : 2; /* [1..0] buck2 N power��������ӦNMOS�����������ڣ�0x0~0x3��С��������)�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck2_ng_p_sel             : 2; /* [5..4] buck2 N power��������ӦPMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG7_ADJ_T;    /* BUCK2����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_dbias                : 2; /* [1..0] buck2 �Ƚ���ƫ�õ������ڣ�0x0~0x3���󣩡� */
        unsigned int    buck2_ocp_d                : 1; /* [2..2] buck2 �ڲ�OCP��·�����źţ�0�������Σ�1������ �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck2_ton                  : 2; /* [5..4] buck2��С��ͨʱ�䡣 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG8_ADJ_T;    /* BUCK2����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_nmos_off             : 1; /* [0..0] buck2���ڹر�NMOS power�ܣ�0��ǿ�ƹرգ�1����ǿ�ƹر� �� */
        unsigned int    buck2_reg_c                : 1; /* [1..1] buck2�ڲ�regulator���ݣ����ڵ���regulator���� */
        unsigned int    buck2_short_pdp            : 1; /* [2..2] ��·�������μĴ�����0:ʹ�ܶ�·������1:��ʹ�ܶ�·������ */
        unsigned int    buck2_reg_ss_d             : 1; /* [3..3] buck2������ʱ�ڲ�regulator״̬��0������״̬��1����λ���淴���� */
        unsigned int    buck2_dt_sel               : 2; /* [5..4] buck2����ʱ����ڣ�ÿbit�������ƣ���1���������ӳ� ��0�������ӳ�5ns �� */
        unsigned int    buck2_regop_c              : 1; /* [6..6] buck2�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate�� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG9_ADJ_T;    /* BUCK2����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_reg_dr               : 3; /* [2..0] buck2�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    buck2_en_reg               : 1; /* [3..3] buck2�ڲ����ȵ�����ʹ���źţ�0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    buck2_ocp_clamp_sel        : 1; /* [4..4] OCP clamp���ܵĿ���:0:����1���ء� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG10_ADJ_T;    /* BUCK2����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_reg_idr              : 2; /* [1..0] buck2�ڲ�regulator���������ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck2_reg_r                : 2; /* [5..4] buck2�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG11_ADJ_T;    /* BUCK2����11�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_reserve              : 8; /* [7..0] buck2���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK2_REG12_ADJ_T;    /* BUCK2����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_adj_rlx              : 4; /* [3..0] buck3 LX�����˲�������ڣ�ÿbit�������ƣ�:0�����費���� ��1��������롣 */
        unsigned int    buck3_adj_clx              : 4; /* [7..4] buck3 LX�����˲����ݵ��ڣ�ÿbit�������ƣ�:0�����ݲ����� ��1�����ݽ��롣 */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG1_ADJ_T;    /* BUCK3����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_new_dmd_sel          : 5; /* [4..0] ��dmd�ṹdmd�������� */
        unsigned int    buck3_ocp_sel              : 2; /* [6..5] buck3 OCP�������0x0: 2.63A ��0x1: 3.08A ��0x2: 3.52A ��0x3: 3.92A �� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG2_ADJ_T;    /* BUCK3����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_dmd_sel              : 2; /* [1..0] buck3 dmd��ѡ��0x0~0x3���󣩡� */
        unsigned int    buck3_en_regop_clamp       : 1; /* [2..2] regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܣ�0����ʹ�ܡ� */
        unsigned int    buck3_dmd_clamp            : 1; /* [3..3] ��dmdǶλʹ���źţ�0�����ϣ�1�������ϡ� */
        unsigned int    buck3_ocp_delay_sel        : 1; /* [4..4] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck3_dmd_shield_n         : 1; /* [5..5] �������dmd�����źţ�0:���Σ�1�������Ρ� */
        unsigned int    buck3_sleep_dmd            : 1; /* [6..6] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck3_pdn_lx_det           : 1; /* [7..7] ʹ��LX��������ʱ����Ƶ�·��0����ʹ�ܣ�1��ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG3_ADJ_T;    /* BUCK3����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_ng_dt_sel            : 1; /* [0..0] buck3 P�ܵ�N������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck3_pg_dt_sel            : 1; /* [1..1] buck3 N�ܵ�P������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck3_sft_sel              : 1; /* [2..2] buck3��������ʽѡ�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck3_shield_i             : 2; /* [5..4] dmd�����źŶ�Ӧ�������ڣ�00~11���� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG4_ADJ_T;    /* BUCK3����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_pg_n_sel             : 2; /* [1..0] buck3 P power��������ӦNMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck3_pg_p_sel             : 2; /* [5..4] buck3 P power��������ӦPMOS�����������ڣ�0x0~0x3�������������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG5_ADJ_T;    /* BUCK3����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_ng_n_sel             : 2; /* [1..0] buck3 N power��������ӦNMOS�����������ڣ�0x0~0x3��С��������)�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck3_ng_p_sel             : 2; /* [5..4] buck3 N power��������ӦPMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG6_ADJ_T;    /* BUCK3����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_dbias                : 2; /* [1..0] buck3 �Ƚ���ƫ�õ������ڣ�0x0~0x3���󣩡� */
        unsigned int    buck3_ocp_d                : 1; /* [2..2] buck3 �ڲ�OCP��·�����źţ�0�������Σ�1������ �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck3_ton                  : 2; /* [5..4] buck3��С��ͨʱ�䡣 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG7_ADJ_T;    /* BUCK3����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_nmos_off             : 1; /* [0..0] buck3���ڹر�NMOS power�ܣ�0��ǿ�ƹرգ�1����ǿ�ƹر� �� */
        unsigned int    buck3_reg_c                : 1; /* [1..1] buck3�ڲ�regulator���ݣ����ڵ���regulator���� */
        unsigned int    buck3_short_pdp            : 1; /* [2..2] ��·�������μĴ�����0:ʹ�ܶ�·������1:��ʹ�ܶ�·������ */
        unsigned int    buck3_reg_ss_d             : 1; /* [3..3] buck3������ʱ�ڲ�regulator״̬��0������״̬��1����λ���淴���� */
        unsigned int    buck3_dt_sel               : 2; /* [5..4] buck3����ʱ����ڣ�ÿbit�������ƣ���1���������ӳ� ��0�������ӳ�5ns �� */
        unsigned int    buck3_regop_c              : 1; /* [6..6] buck3�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate�� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG8_ADJ_T;    /* BUCK3����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_reg_dr               : 3; /* [2..0] buck3�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    buck3_en_reg               : 1; /* [3..3] buck3�ڲ����ȵ�����ʹ���źţ�0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    buck3_ocp_clamp_sel        : 1; /* [4..4] OCP clamp���ܵĿ���:0:����1���ء� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG9_ADJ_T;    /* BUCK3����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_reg_idr              : 2; /* [1..0] buck3�ڲ�regulator���������ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck3_reg_r                : 2; /* [5..4] buck3�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG10_ADJ_T;    /* BUCK3����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_mos_sel              : 2; /* [1..0] buck3 power�ܴ�Сѡ��:11��ʾpower��ȫ����ͨ �� */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG11_ADJ_T;    /* BUCK3����11�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_reserve              : 8; /* [7..0] buck3���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK3_REG12_ADJ_T;    /* BUCK3����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_adj_rlx              : 4; /* [3..0] buck4 LX�����˲�������ڣ�ÿbit�������ƣ�:0�����費���� ��1��������롣 */
        unsigned int    buck4_adj_clx              : 4; /* [7..4] buck4 LX�����˲����ݵ��ڣ�ÿbit�������ƣ�:0�����ݲ����� ��1�����ݽ��롣 */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG1_ADJ_T;    /* BUCK4����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_new_dmd_sel          : 5; /* [4..0] ��dmd�ṹdmd�������� */
        unsigned int    buck4_ocp_sel              : 2; /* [6..5] buck4 OCP�������0x0: 1.03A ��0x1: 1.48A ��0x2: 1.92A ��0x3: 2.35A �� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG2_ADJ_T;    /* BUCK4����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_dmd_sel              : 2; /* [1..0] buck4 dmd��ѡ��0x0~0x3���󣩡� */
        unsigned int    buck4_en_regop_clamp       : 1; /* [2..2] regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܣ�0����ʹ�ܡ� */
        unsigned int    buck4_dmd_clamp            : 1; /* [3..3] ��dmdǶλʹ���źţ�0�����ϣ�1�������ϡ� */
        unsigned int    buck4_ocp_delay_sel        : 1; /* [4..4] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck4_dmd_shield_n         : 1; /* [5..5] �������dmd�����źţ�0:���Σ�1�������Ρ� */
        unsigned int    buck4_sleep_dmd            : 1; /* [6..6] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck4_pdn_lx_det           : 1; /* [7..7] ʹ��LX��������ʱ����Ƶ�·��0����ʹ�ܣ�1��ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG3_ADJ_T;    /* BUCK4����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_ng_dt_sel            : 1; /* [0..0] buck4 P�ܵ�N������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck4_pg_dt_sel            : 1; /* [1..1] buck4 N�ܵ�P������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck4_sft_sel              : 1; /* [2..2] buck4��������ʽѡ�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG4_ADJ_T;    /* BUCK4����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_pg_n_sel             : 2; /* [1..0] buck4 P power��������ӦNMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck4_pg_p_sel             : 2; /* [5..4] buck4 P power��������ӦPMOS�����������ڣ�0x0~0x3�������������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG5_ADJ_T;    /* BUCK4����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_ng_n_sel             : 2; /* [1..0] buck4 N power��������ӦNMOS�����������ڣ�0x0~0x3��С��������)�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck4_ng_p_sel             : 2; /* [5..4] buck4 N power��������ӦPMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG6_ADJ_T;    /* BUCK4����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_dbias                : 2; /* [1..0] buck4 �Ƚ���ƫ�õ������ڣ�0x0~0x3���󣩡� */
        unsigned int    buck4_ocp_d                : 1; /* [2..2] buck4 �ڲ�OCP��·�����źţ�0�������Σ�1������ �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck4_ton                  : 2; /* [5..4] buck4��С��ͨʱ�䡣 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG7_ADJ_T;    /* BUCK4����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_nmos_off             : 1; /* [0..0] buck4���ڹر�NMOS power�ܣ�0��ǿ�ƹرգ�1����ǿ�ƹر� �� */
        unsigned int    buck4_reg_c                : 1; /* [1..1] buck4�ڲ�regulator���ݣ����ڵ���regulator���� */
        unsigned int    buck4_short_pdp            : 1; /* [2..2] ��·�������μĴ�����0:ʹ�ܶ�·������1:��ʹ�ܶ�·������ */
        unsigned int    buck4_reg_ss_d             : 1; /* [3..3] buck4������ʱ�ڲ�regulator״̬��0������״̬��1����λ���淴���� */
        unsigned int    buck4_dt_sel               : 2; /* [5..4] buck4����ʱ����ڣ�ÿbit�������ƣ���1���������ӳ� ��0�������ӳ�5ns �� */
        unsigned int    buck4_regop_c              : 1; /* [6..6] buck4�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate�� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG8_ADJ_T;    /* BUCK4����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_reg_dr               : 3; /* [2..0] buck4�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    buck4_en_reg               : 1; /* [3..3] buck4�ڲ����ȵ�����ʹ���źţ�0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    buck4_ocp_clamp_sel        : 1; /* [4..4] OCP clamp���ܵĿ���:0:����1���ء� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG9_ADJ_T;    /* BUCK4����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_reg_idr              : 2; /* [1..0] buck4�ڲ�regulator���������ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck4_reg_r                : 2; /* [5..4] buck4�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG10_ADJ_T;    /* BUCK4����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_reserve              : 8; /* [7..0] buck4���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK4_REG12_ADJ_T;    /* BUCK4����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_adj_rlx              : 4; /* [3..0] buck5 LX�����˲�������ڣ�ÿbit�������ƣ�:0�����費���� ��1��������롣 */
        unsigned int    buck5_adj_clx              : 4; /* [7..4] buck5 LX�����˲����ݵ��ڣ�ÿbit�������ƣ�:0�����ݲ����� ��1�����ݽ��롣 */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG1_ADJ_T;    /* BUCK5����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_new_dmd_sel          : 5; /* [4..0] ��dmd�ṹdmd�������� */
        unsigned int    buck5_ocp_sel              : 2; /* [6..5] buck5 OCP�������0x0: 0.57A ��0x1: 0.79A ��0x2: 1.02A ��0x3: 1.22A �� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG2_ADJ_T;    /* BUCK5����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_dmd_sel              : 2; /* [1..0] buck5 dmd��ѡ��0x0~0x3���󣩡� */
        unsigned int    buck5_en_regop_clamp       : 1; /* [2..2] regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܣ�0����ʹ�ܡ� */
        unsigned int    buck5_dmd_clamp            : 1; /* [3..3] ��dmdǶλʹ���źţ�0�����ϣ�1�������ϡ� */
        unsigned int    buck5_ocp_delay_sel        : 1; /* [4..4] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck5_dmd_shield_n         : 1; /* [5..5] �������dmd�����źţ�0:���Σ�1�������Ρ� */
        unsigned int    buck5_sleep_dmd            : 1; /* [6..6] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck5_pdn_lx_det           : 1; /* [7..7] ʹ��LX��������ʱ����Ƶ�·��0����ʹ�ܣ�1��ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG3_ADJ_T;    /* BUCK5����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_ng_dt_sel            : 1; /* [0..0] buck5 P�ܵ�N������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck5_pg_dt_sel            : 1; /* [1..1] buck5 N�ܵ�P������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck5_sft_sel              : 1; /* [2..2] buck5��������ʽѡ�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG4_ADJ_T;    /* BUCK5����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_pg_n_sel             : 2; /* [1..0] buck5 P power��������ӦNMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck5_pg_p_sel             : 2; /* [5..4] buck5 P power��������ӦPMOS�����������ڣ�0x0~0x3�������������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG5_ADJ_T;    /* BUCK5����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_ng_n_sel             : 2; /* [1..0] buck5 N power��������ӦNMOS�����������ڣ�0x0~0x3��С��������)�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck5_ng_p_sel             : 2; /* [5..4] buck5 N power��������ӦPMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG6_ADJ_T;    /* BUCK5����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_dbias                : 2; /* [1..0] buck5 �Ƚ���ƫ�õ������ڣ�0x0~0x3���󣩡� */
        unsigned int    buck5_ocp_d                : 1; /* [2..2] buck5 �ڲ�OCP��·�����źţ�0�������Σ�1������ �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck5_ton                  : 2; /* [5..4] buck5��С��ͨʱ�䡣 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG7_ADJ_T;    /* BUCK5����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_nmos_off             : 1; /* [0..0] buck5���ڹر�NMOS power�ܣ�0��ǿ�ƹرգ�1����ǿ�ƹر� �� */
        unsigned int    buck5_reg_c                : 1; /* [1..1] buck5�ڲ�regulator���ݣ����ڵ���regulator���� */
        unsigned int    buck5_short_pdp            : 1; /* [2..2] ��·�������μĴ�����0:ʹ�ܶ�·������1:��ʹ�ܶ�·������ */
        unsigned int    buck5_reg_ss_d             : 1; /* [3..3] buck5������ʱ�ڲ�regulator״̬��0������״̬��1����λ���淴���� */
        unsigned int    buck5_dt_sel               : 2; /* [5..4] buck5����ʱ����ڣ�ÿbit�������ƣ���1���������ӳ� ��0�������ӳ�5ns �� */
        unsigned int    buck5_regop_c              : 1; /* [6..6] buck5�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate�� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG8_ADJ_T;    /* BUCK5����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_reg_dr               : 3; /* [2..0] buck5�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    buck5_en_reg               : 1; /* [3..3] buck5�ڲ����ȵ�����ʹ���źţ�0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    buck5_ocp_clamp_sel        : 1; /* [4..4] OCP clamp���ܵĿ���:0:����1���ء� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG9_ADJ_T;    /* BUCK5����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_reg_idr              : 2; /* [1..0] buck5�ڲ�regulator���������ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck5_reg_r                : 2; /* [5..4] buck5�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG10_ADJ_T;    /* BUCK5����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_reserve0             : 8; /* [7..0] buck5���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG12_ADJ_T;    /* BUCK5����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_reserve1             : 8; /* [7..0] buck5���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG13_ADJ_T;    /* BUCK5����13�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_reserve2             : 8; /* [7..0] buck5���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK5_REG14_ADJ_T;    /* BUCK5����14�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_adj_rlx              : 4; /* [3..0] buck6 LX�����˲�������ڣ�ÿbit�������ƣ�:0�����費���� ��1��������롣 */
        unsigned int    buck6_adj_clx              : 4; /* [7..4] buck6 LX�����˲����ݵ��ڣ�ÿbit�������ƣ�:0�����ݲ����� ��1�����ݽ��롣 */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG1_ADJ_T;    /* BUCK6����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_new_dmd_sel          : 5; /* [4..0] ��dmd�ṹdmd�������� */
        unsigned int    buck6_ocp_sel              : 2; /* [6..5] buck6 OCP�������0x0: 1.09A ��0x1: 1.58A ��0x2: 1.92A ��0x3: 2.40A �� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG2_ADJ_T;    /* BUCK6����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_dmd_sel              : 2; /* [1..0] buck6 dmd��ѡ��0x0~0x3���󣩡� */
        unsigned int    buck6_en_regop_clamp       : 1; /* [2..2] regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܣ�0����ʹ�ܡ� */
        unsigned int    buck6_dmd_clamp            : 1; /* [3..3] ��dmdǶλʹ���źţ�0�����ϣ�1�������ϡ� */
        unsigned int    buck6_ocp_delay_sel        : 1; /* [4..4] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck6_dmd_shield_n         : 1; /* [5..5] �������dmd�����źţ�0:���Σ�1�������Ρ� */
        unsigned int    buck6_sleep_dmd            : 1; /* [6..6] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck6_pdn_lx_det           : 1; /* [7..7] ʹ��LX��������ʱ����Ƶ�·��0����ʹ�ܣ�1��ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG3_ADJ_T;    /* BUCK6����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_ng_dt_sel            : 1; /* [0..0] buck6 P�ܵ�N������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck6_pg_dt_sel            : 1; /* [1..1] buck6 N�ܵ�P������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck6_sft_sel              : 1; /* [2..2] buck6��������ʽѡ�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG4_ADJ_T;    /* BUCK6����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_pg_n_sel             : 2; /* [1..0] buck6 P power��������ӦNMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck6_pg_p_sel             : 2; /* [5..4] buck6 P power��������ӦPMOS�����������ڣ�0x0~0x3�������������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG5_ADJ_T;    /* BUCK6����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_ng_n_sel             : 2; /* [1..0] buck6 N power��������ӦNMOS�����������ڣ�0x0~0x3��С��������)�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck6_ng_p_sel             : 2; /* [5..4] buck6 N power��������ӦPMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG6_ADJ_T;    /* BUCK6����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_dbias                : 2; /* [1..0] buck6 �Ƚ���ƫ�õ������ڣ�0x0~0x3���󣩡� */
        unsigned int    buck6_ocp_d                : 1; /* [2..2] buck6 �ڲ�OCP��·�����źţ�0�������Σ�1������ �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck6_ton                  : 2; /* [5..4] buck6��С��ͨʱ�䡣 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG7_ADJ_T;    /* BUCK6����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_nmos_off             : 1; /* [0..0] buck6���ڹر�NMOS power�ܣ�0��ǿ�ƹرգ�1����ǿ�ƹر� �� */
        unsigned int    buck6_reg_c                : 1; /* [1..1] buck6�ڲ�regulator���ݣ����ڵ���regulator���� */
        unsigned int    buck6_short_pdp            : 1; /* [2..2] ��·�������μĴ�����0:ʹ�ܶ�·������1:��ʹ�ܶ�·������ */
        unsigned int    buck6_reg_ss_d             : 1; /* [3..3] buck6������ʱ�ڲ�regulator״̬��0������״̬��1����λ���淴���� */
        unsigned int    buck6_dt_sel               : 2; /* [5..4] buck6����ʱ����ڣ�ÿbit�������ƣ���1���������ӳ� ��0�������ӳ�5ns �� */
        unsigned int    buck6_regop_c              : 1; /* [6..6] buck6�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate�� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG8_ADJ_T;    /* BUCK6����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_reg_dr               : 3; /* [2..0] buck6�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    buck6_en_reg               : 1; /* [3..3] buck6�ڲ����ȵ�����ʹ���źţ�0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    buck6_ocp_clamp_sel        : 1; /* [4..4] OCP clamp���ܵĿ���:0:����1���ء� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG9_ADJ_T;    /* BUCK6����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_reg_idr              : 2; /* [1..0] buck6�ڲ�regulator���������ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck6_reg_r                : 2; /* [5..4] buck6�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG10_ADJ_T;    /* BUCK6����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_mos_sel              : 2; /* [1..0] buck6 power�ܴ�Сѡ��:11��ʾpower��ȫ����ͨ �� */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG11_ADJ_T;    /* BUCK6����11�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_reserve              : 8; /* [7..0] buck6���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6551_BUCK6_REG12_ADJ_T;    /* BUCK6����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cp2_vout_sel               : 2; /* [1..0] CHARGE PUMP2�������ƽѡ���ź�0x0 : 7.00V ��0x1 ��6.82V ��0x2 ��6.66V ��0x3 ��6.350V �� */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI6551_CHG_PUMP2_ADJ_T;    /* CHG_PUMP2���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_vck                  : 6; /* [5..0] buck01�������Ĭ�����0.9V64Steps7.9365mV/stepҪ���ѹ���߱��뵥����0x19: 0.90V��0x26: 1.00V��OTP�ɱ��Ĭ�ϵ�ѹ��otp_vset:0x0 : 0.90V ��0x1 : 1.00V �� */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_VSET_BUCK01_ADJ_T;    /* BUCK01��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck2_dv                   : 8; /* [7..0] buck2�����ѹ����.0x00: 0.70V��0x3f: 1.20V��8mv/step��0x7f��1.6V ��0xff:1.8V ��0x19: 0.90V��0x26: 1.00V��OTP�ɱ��Ĭ�ϵ�ѹ��otp_vset:0x0 : 0.90V ��0x1 :1.00V �� */
    } bits;
    unsigned int    u32;
}HI6551_VSET_BUCK2_ADJ_T;    /* BUCK2��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_dv                   : 4; /* [3..0] BUCK3�����ѹ�����źţ�0x6: 0.90V��0xa: 1.00V��OTP�ɱ��Ĭ�ϵ�ѹ��otp_vset:0x0 : 0.90V ��0x1 : 1.00V �� */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6551_VSET_BUCK3_ADJ_T;    /* BUCK3��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_dv                   : 4; /* [3..0] buck4�����ѹ����:      0x0:1.20V;                   0xF:1.575V               25mv/step       Ĭ�������ѹ��1.225V */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6551_VSET_BUCK4_ADJ_T;    /* BUCK3��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_dv                   : 8; /* [7..0] buck5�����ѹ����: 0x0:0.7V;                   0x63:1.204V;0x127:1.65V; 0x255:1.8V8mv/stepĬ�������ѹ��0.9V */
    } bits;
    unsigned int    u32;
}HI6551_VSET_BUCK5_ADJ_T;    /* BUCK5��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_dv                   : 4; /* [3..0] buck6�����ѹ����:0x0:1.8V;0xF:2.175V;                        25mv/step Ĭ�������ѹ��1.825V */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6551_VSET_BUCK6_ADJ_T;    /* BUCK6��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo1                  : 3; /* [2..0] LDO1��ѹ���ڣ�0x0: 1.80V ��0x1: 2.50V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO1_REG_ADJ_T;    /* LDO1���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo2                  : 3; /* [2..0] LDO2��ѹ���ڣ�0x0: 2.50V ��0x1: 2.60V ��0x2: 2.80V ��0x3: 2.90V ��0x4: 3.00V ��0x5: 3.10V ��0x6: 3.20V ��0x7: 3.30V �� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO2_REG_ADJ_T;    /* LDO2���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo3                  : 3; /* [2..0] LDO3��ѹ���ڣ�0x0:0.80V ��0x1: 0.85V ��0x2: 0.90V ��0x3: 0.95V ��0x4: 1.00V ��OTP�ɱ��Ĭ�ϵ�ѹ��otp_vset:0x0 : 0.9V ��0x1 : 1.00V ��Pmu�ϵ�ʱldo3_battΪ0.85V����ldo3_buck�ϵ�ʱvset_ldo3 otpû��дΪ0.9V����д��Ϊ1.0V�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo3                 : 3; /* [6..4] LDO3���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO3_REG_ADJ_T;    /* LDO3���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo4                  : 3; /* [2..0] LDO4��ѹ���ڣ�0x0: 1.50V ��0x1: 1.80V ��0x2: 1.85V ��0x3: 2.20V ��0x4: 2.50V ��0x5: 2.80V �� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO4_REG_ADJ_T;    /* LDO4���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo5                  : 3; /* [2..0] LDO5��ѹ���ڣ�0x0: 2.85V ��0x1: 2.90V ��0x2: 2.95V ��0x3: 3.00V ��0x4: 3.05V ��0x5: 3.10V ��0x6: 3.15V ��0x7: 3.15V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo5                 : 3; /* [6..4] LDO3���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO5_REG_ADJ_T;    /* LDO5���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo6                  : 3; /* [2..0] LDO6��ѹ���ڣ�0x0: 1.50V ��0x1: 1.80V ��0x2: 1.85V ��0x3: 2.20V ��0x4: 2.50V ��0x5: 2.80V �� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO6_REG_ADJ_T;    /* LDO6���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo7                  : 3; /* [2..0] LDO7��ѹ���ڣ�0x0: 1.80V ��0x1: 1.85V ��0x2: 2.80V ��0x3: 2.85V ��0x4: 2.90V ��0x5: 2.95V ��0x6: 3.00V ��0x7: 3.05V �� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO7_REG_ADJ_T;    /* LDO7���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo8                  : 3; /* [2..0] LDO8��ѹ���ڣ�0x0: 1.10V ��0x1: 1.20V ��0x2: 1.25V ��0x3: 1.275V ��0x4: 1.30V ��0x5: 1.325V ��0x6: 1.35V ��0x7��1.375V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo8                 : 3; /* [6..4] LDO8���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO8_REG_ADJ_T;    /* LDO8���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo9                  : 3; /* [2..0] LDO9��ѹ���ڣ�0x0: 1.80V ��0x1: 1.85V ��0x2: 2.80V ��0x3: 2.85V ��0x4: 2.90V ��0x5: 2.95V ��0x6: 3.00V ��0x7: 3.05V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo9                 : 3; /* [6..4] LDO9���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO9_REG_ADJ_T;    /* LDO9���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo10                 : 3; /* [2..0] LDO10��ѹ���ڣ�0x0: 2.80V ��0x1: 2.85V ��0x2: 2.90V ��0x3: 2.95V ��0x4: 3.00V ��0x5: 3.05V ��0x6: 3.10V ��0x7: 3.15V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo10                : 3; /* [6..4] LDO10���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO10_REG_ADJ_T;    /* LDO10���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo11                 : 3; /* [2..0] LDO11��ѹ���ڣ�0x0: 1.80V ��0x1: 1.85V ��0x2: 2.80V ��0x3: 2.85V ��0x4: 2.90V ��0x5: 2.95V ��0x6: 3.00V ��0x7: 3.05V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo11                : 3; /* [6..4] LDO11���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO11_REG_ADJ_T;    /* LDO11���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo12                 : 3; /* [2..0] LDO12��ѹ���ڣ�0x0: 3.00V ��0x1: 3.05V ��0x2: 3.10V ��0x3: 3.15V ��0x4: 3.20V ��0x5: 3.25V ��0x6: 3.30V ��0x7: 3.35V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo12                : 3; /* [6..4] LDO12���ص����ʲ��������� */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO12_REG_ADJ_T;    /* LDO12���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo13                 : 3; /* [2..0] LDO13��ѹ���ڣ�0x0: 1.80V ��0x1: 2.50V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO13_REG_ADJ_T;    /* LDO13���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo14                 : 3; /* [2..0] LDO14��ѹ���ڣ�0x0: 1.80V ��0x1: 2.50V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo14                : 3; /* [6..4] LDO14���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO14_REG_ADJ_T;    /* LDO14���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo15                 : 3; /* [2..0] LDO15��ѹ���ڣ�0x0: 1.80V ��0x1: 2.50V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo15                : 3; /* [6..4] LDO15���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO15_REG_ADJ_T;    /* LDO15���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo16                 : 3; /* [2..0] LDO16��ѹ���ڣ�0x0: 1.80V ��0x1: 2.50V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo16                : 3; /* [6..4] LDO16���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO16_REG_ADJ_T;    /* LDO16���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo17                 : 3; /* [2..0] LDO17��ѹ���ڣ�0x0: 0.90V ��0x1: 0.95V ��0x2: 1.00V ��0x3: 1.05V ��0x4: 1.10V ��0x5: 1.15V �� 0x6: 1.20V ��0x7: 1.25V�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo17                : 3; /* [6..4] LDO17���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO17_REG_ADJ_T;    /* LDO17���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo18                 : 3; /* [2..0] LDO18��ѹ���ڣ�0x0: 1.80V ��0x1: 2.50V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo18                : 3; /* [6..4] LDO18���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO18_REG_ADJ_T;    /* LDO18���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo19                 : 3; /* [2..0] LDO19��ѹ���ڣ�0x0: 0.900V ��0x1: 0.925V ��0x2: 0.950V ��0x3: 0.975V ��0x4: 1.000V ��0x5: 1.025V ��0x6: 1.050V ��0x7: 1.075V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo19                : 3; /* [6..4] LDO19���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO19_REG_ADJ_T;    /* LDO19���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo20                 : 3; /* [2..0] LDO20��ѹ���ڣ�0x0: 2.50V ��0x1: 2.60V ��0x2: 2.70V ��0x3: 2.75V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 3.00V��0x7: 3.10V�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo20                : 3; /* [6..4] LDO20���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO20_REG_ADJ_T;    /* LDO20���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo21                 : 3; /* [2..0] LDO21��ѹ���ڣ�0x0: 1.20V ��0x1: 1.25V ��0x2: 1.275V ��0x3: 1.30V ��0x4: 1.325V ��0x5: 1.35V ��0x6: 1.50V ��0x7��1.80V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo21                : 3; /* [6..4] LDO21���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO21_REG_ADJ_T;    /* LDO21���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo22                 : 3; /* [2..0] LDO22��ѹ���ڣ�0x0: 1.40V ��0x1: 1.425V ��0x2: 1.45V ��0x3: 1.475V ��0x4: 1.50V �� 0x5: 1.525V�� */
        unsigned int    en_sink_ldo22              : 1; /* [3..3] ʹ��LDO22����������0:����û�е���������1�������е������� �� */
        unsigned int    rset_sink_ldo22            : 2; /* [5..4] ����LDO22�������裺00�������11������С��Ĭ��ֵ10�� */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO22_REG_ADJ_T;    /* LDO22���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo23                 : 3; /* [2..0] LDO23��ѹ���ڣ�0x0: 1.50V ��0x1: 1.80V ��0x2: 1.85V ��0x3: 1.90V ��0x4: 1.95V �� 0x5: 2.50V ��0x6: 2.80V ��0x7: 2.85V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo23                : 3; /* [6..4] LDO23���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO23_REG_ADJ_T;    /* LDO23���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo24                 : 3; /* [2..0] LDO24��ѹ���ڣ�0x0: 2.80V ��0x1: 2.85V ��0x2: 2.90V ��0x3: 2.95V ��0x4: 3.00V ��0x5: 3.05V ��0x6: 3.10V ��0x7: 3.15V �� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LDO24_REG_ADJ_T;    /* LDO24���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_pmua                  : 3; /* [2..0] PMUA��ѹ���ڣ�0x0: 2.90V ��0x1: 3.00V ��0x2: 3.05V ��0x3: 3.10V ��0x4: 3.15V �� 0x5: 3.20V ��0x6: 3.25V ��0x7: 3.30V�� */
        unsigned int    eco_pmua                   : 1; /* [3..3] PMUA����ECOģʽ�����ź�:0������normalģʽ��1������ecoģʽ�� */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6551_PMUA_REG_ADJ_T;    /* PMUA���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    sstset_lvs5                : 2; /* [1..0] LVS5�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    sstset_lvs4                : 2; /* [3..2] LVS4�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    sstset_lvs3                : 2; /* [5..4] LVS3�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    sstset_lvs2                : 2; /* [7..6] LVS2�����ٶȵ��ڣ�11��죬00���� */
    } bits;
    unsigned int    u32;
}HI6551_LVS_ADJ1_T;    /* LVS����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sstset_lvs9                : 2; /* [1..0] LVS9�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    sstset_lvs8                : 2; /* [3..2] LVS8�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    sstset_lvs7                : 2; /* [5..4] LVS7�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    sstset_lvs6                : 2; /* [7..6] LVS6�����ٶȵ��ڣ�11��죬00���� */
    } bits;
    unsigned int    u32;
}HI6551_LVS_ADJ2_T;    /* LVS����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sstset_lvs10               : 2; /* [1..0] LVS10�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI6551_LVS_ADJ3_T;    /* LVS����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_bst_int                 : 1; /* [0..0] 0: BOOST�ر� ��1: BOOST���� �� */
        unsigned int    bst_pm_th                  : 1; /* [1..1] 0: PMOS�����˼Ĵ������� ��1: PMOSǿ��ֱͨ�������ڲ���·�رա� */
        unsigned int    bst_pm_cut                 : 1; /* [2..2] 0: PMOS�����˼Ĵ������� ��1: PMOSǿ�йر� �� */
        unsigned int    bst_reserved0              : 5; /* [7..3] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ0_T;    /* BOOST����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_sel_scp                : 1; /* [0..0] 0: 1ms��VOUT����0.85BAT���ϱ���·��1: 2ms��VOUT����0.85BAT���ϱ���·�� */
        unsigned int    bst_sel_pd                 : 1; /* [1..1] 0: �ر��µ�PMOS���Ƶ�· ��1: ʹ���µ�PMOS���Ƶ�· �� */
        unsigned int    bst_en_uvp                 : 1; /* [2..2] 0: �ر�Ƿѹ��·�����ϱ�����1: ʹ��Ƿѹ��·�������ѹ�����趨20%���� */
        unsigned int    bst_en_scp                 : 1; /* [3..3] 0: �رն�·ϵͳ�Զ��رգ����ϱ�����1: ʹ�ܶ�·ϵͳ�Զ��رա� */
        unsigned int    bst_en_ovp                 : 1; /* [4..4] 0: �رչ�ѹ��·�����ϱ�����1: ʹ�ܹ�ѹ��·�������ѹ�����趨20%���� */
        unsigned int    bst_en_ocp                 : 1; /* [5..5] 0: �رչ�����·���ƣ���Ȼ�ϱ�����1: ʹ�ܹ�����·���ơ� */
        unsigned int    bst_reserved1              : 2; /* [7..6] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ1_T;    /* BOOST����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_drv_mode               : 1; /* [0..0] 0: ��С����ģʽ��1: ��ͳ�������ģʽ�� */
        unsigned int    bst_loop_mode              : 1; /* [1..1] 0:����ģʽ��1:��ѹģʽ�� */
        unsigned int    bst_en_pfm                 : 1; /* [2..2] 0: �ر������ѹ��ʽ��PFMģʽ��1: ʹ�������ѹ��ʽ��PFMģʽ�� */
        unsigned int    bst_en_nring               : 1; /* [3..3] 0: �رն����壻1: ʹ�ܷ����塣 */
        unsigned int    bst_en_clp_os              : 1; /* [4..4] 0: �ر�ǯλ��·ʧ����ѹ��1: ʹ��ǯλ��·ʧ����ѹ�� */
        unsigned int    bst_en_slop                : 1; /* [5..5] 0: �ر�б�²�����1: ʹ��б�²����� */
        unsigned int    bst_en_dmd                 : 1; /* [6..6] 0: �رչ����⣻1: ʹ�ܹ����⡣ */
        unsigned int    bst_reserved2              : 1; /* [7..7] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ2_T;    /* BOOST����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_clp                    : 3; /* [2..0] EA���ǯλֵ��VRAMPֱ����ƽֵ��ʧ��000: 8mV001: 12mV010: 16mV011: 20mV100: 24mV101: 28mV110: 32mV111: 36mV */
        unsigned int    bst_itail                  : 1; /* [3..3] EA�������̬��������0: 2.5uA ��1:  5.5uA �� */
        unsigned int    bst_gm                     : 3; /* [6..4] EA��gm�����趨(gm=2/R)000: 160k��001: 140k��010: 120k��011: 100k��100: 40k��101: 30k��110: 20k��111: 10k�� */
        unsigned int    bst_reserved3              : 1; /* [7..7] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ3_T;    /* BOOST����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_ccom2                  : 2; /* [1..0] EA����˲�����00: 0.8pF01: 1.1pF10: 1.4pF11: 1.7pF */
        unsigned int    bst_ccom1                  : 2; /* [3..2] ����·��������00: 20pF01: 40pF10: 50pF11: 60pF */
        unsigned int    bst_rcom                   : 2; /* [5..4] ����·��������00: 140k��01: 120k��10: 100k��11: 80k�� */
        unsigned int    bst_reserved4              : 2; /* [7..6] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ4_T;    /* BOOST����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_slop                   : 2; /* [1..0] б�²���б�ʵ��ڣ����ݵ��ڣ�00: 2.0pF01: 2.5pF10: 3.0pF11: 3.5pF */
        unsigned int    bst_ri                     : 2; /* [3..2] ��е���ת��ѹ�迹00: 0.75����ʵ��120k����01: 0.625����ʵ��100k����10: 0.5����ʵ��80k����11: 0.375����ʵ��60k���� */
        unsigned int    bst_reserved5              : 4; /* [7..4] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ5_T;    /* BOOST����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_nsn                    : 2; /* [1..0] NMOSդ�ص�ѹ�½�б��00: 67ns01: 35ns10: 25ns11: 11ns */
        unsigned int    bst_nsp                    : 2; /* [3..2] NMOSդ�ص�ѹ����б��00: 50ns01: 33ns10: 23ns11: 11ns */
        unsigned int    bst_psn                    : 2; /* [5..4] PMOSդ�ص�ѹ�½�б��00:10ns01: 6ns10: 4ns11:3ns */
        unsigned int    bst_psp                    : 2; /* [7..6] PMOSդ�ص�ѹ����б��00: 10ns01: 6ns10: 4ns11: 2ns */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ6_T;    /* BOOST����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_dt_nm                  : 2; /* [1..0] NMOS�رպ���PMOS����ʱ00: 001: 2ns10: 4ns11: 6ns */
        unsigned int    bst_dt_pm                  : 2; /* [3..2] PMOS�رպ���NMOS����ʱ00: 001: 2ns10: 4ns11: 6ns */
        unsigned int    bst_lxde                   : 2; /* [5..4] �ж�����PMOS��LX�жϵ�·�����Ĵ���LXDE<1>������LXDE<0>1������DMD�ض��߼�0���ر�DMD�ض��߼�����DMD֮����©�磩 */
        unsigned int    bst_reserved6              : 2; /* [7..6] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ7_T;    /* BOOST����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_ckmin                  : 2; /* [1..0] NMOS��С��ͨʱ��00: 160ns01: 120ns10: 80ns11: 40ns */
        unsigned int    bst_osc                    : 4; /* [5..2] ����Ƶ�ʣ�MHz��0000: 2.9910001: 2.8520010: 2.7120011: 2.5680100: 2.4230101: 2.2740110: 2.1220111: 1.9681000: 1.8131001: 1.6541010: 1.4921011: 1.3251100: 1.1551101: 0.9811110: 0.8021111: 0.617 */
        unsigned int    bst_reserved7              : 2; /* [7..6] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ8_T;    /* BOOST����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    vo                         : 3; /* [2..0] �����ѹ000: 5.5V001: 5.4V010: 5.2V011: 5.0V100: 4.2V101~111: 3.8V */
        unsigned int    sel_ocp                    : 2; /* [4..3] NMOS����ֵ00: 1.7A01: 2.0A10: 2.3A11: 2.6A */
        unsigned int    bst_start                  : 3; /* [7..5] PMOSֱͨʱդ�������ƣ�Ӱ������ʱ��Ͷ�·������000: 0.3uA001: 0.4uA010: 0.5uA011: 0.6uA100: 0.7uA101: 0.8uA110: 0.9uA111: 1.4uA */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ9_T;    /* BOOST����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_dmd_ofs                : 4; /* [3..0] DMDʧ��0000: 20mV (300mA)0001: 16mV (240mA)0010: 14mV (210mA)0011: 12mV (180mA)0100: 10mV (150mA)0101: 8mV (120mA)0110: 6mV (90mA)0111: 4mV (60mA)1000: 2mV (30mA)1001:01010: -16mV (-180mA).1011: -32mV (-360mA).1100: -48mV (-540mA).1101: -64mV (-720mA)..1110: -128mV (-900mA).1111: -256mV (-1080mA). */
        unsigned int    bst_reserved10             : 4; /* [7..4] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ10_T;    /* BOOST����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bst_v2clp                  : 2; /* [1..0] EA����߶�ǯλ�㣨��Ӧ�Ŵ����0.4�����00: 0.7*VOUT01: 0.6*VOUT10: 0.5*VOUT11: 0.4*VOUT */
        unsigned int    bst_v2div                  : 2; /* [3..2] ���ǲ�����С�ı���������ȡֵ����V2RAMP�Ĵ������ʹ�á���ȡͬ����ֵ���Ŵ����Ϊ0.400: 455k��01: 380k��10: 320k��11: 245k�� */
        unsigned int    bst_v2ramp                 : 2; /* [5..4] �������ǲ�RC������Rȡֵ00: 705k��01: 590k��10: 485k��11: 370k�� */
        unsigned int    bst_reserved11             : 2; /* [7..6] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_BOOST_ADJ11_T;    /* BOOST����11�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    classd_mute_sel            : 1; /* [0..0] classd_mute_sel���ơ�    0����ʱmuteģʽ��1������muteģʽ�� */
        unsigned int    classd_mute                : 1; /* [1..1] classd_mute���ơ�    0������������1��Mute�� */
        unsigned int    classd_gain                : 2; /* [3..2] classD������ơ�   00:12db01:15db10:18db11:21db������mute�� */
        unsigned int    en_classd_int              : 1; /* [4..4] classDʹ�ܿ��ơ�1��������0���رա� */
        unsigned int    classd_i_ocp               : 2; /* [6..5] classd ������ֵ���ڣ�00:1.5A01:2A10:2.5A11:3A */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_CLASSD_ADJ0_T;    /* CLASSD����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    classd_n_sel               : 2; /* [1..0] ������nmos���ơ�00����һ·nmos��01������·nmos��10������·nmos��11������·nmos�� */
        unsigned int    classd_p_sel               : 2; /* [3..2] ������pmos���ơ�00����һ·pmos��01������·pmos��10������·pmos��11������·pmos�� */
        unsigned int    classd_i_ramp              : 2; /* [5..4] Ramp���У��Ƚ����������ơ�00��1��A��01��3��A��10��4��A��11��5��A�� */
        unsigned int    classd_i_pump              : 2; /* [7..6] Ramp���У�pump�������ơ�00��6��A��01��7��A��10��7��A��11��8��A�� */
    } bits;
    unsigned int    u32;
}HI6551_CLASSD_ADJ1_T;    /* CLASSD����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    classd_ocp_bps             : 1; /* [0..0] �����������ơ�0����������������1��bypass����������·�� */
        unsigned int    classd_fx_bps              : 1; /* [1..1] ��Ƶģʽ���ơ�0��������Ƶģʽ��1��bypass��Ƶģʽ���̶�Ƶ�ʣ��� */
        unsigned int    classd_dt_sel              : 1; /* [2..2] dead time���ơ�0��2ns��1��7ns�� */
        unsigned int    classd_pls_byp             : 1; /* [3..3] ��С�������ޣ�0����������1��bypass��С�������� */
        unsigned int    classd_reserved            : 4; /* [7..4] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6551_CLASSD_ADJ2_T;    /* CLASSD����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bg_test                    : 4; /* [3..0] ��׼����ģʽԤ�� */
        unsigned int    bg_sleep                   : 1; /* [4..4] 0��ref_top�������� ��1��ref_top����sleepģʽ�� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BANDGAP_THSD_ADJ1_T;    /* BANDGAP��THSD����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_tmp_int                 : 2; /* [1..0] 0x:THSD���±���ģ��رգ�10:THSD���±���ģ�鿪����11:THSD�ĵ͹���ģʽ���ߵ�ƽΪ10ms,����Ϊ1s�������ź� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    thsd_set_tmp               : 2; /* [5..4] �¶ȱ���ģ�鱨���¶����á�00:  105�棻01:  115�棻10:  125�棻                      Ĭ������Ϊ125�档 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_BANDGAP_THSD_ADJ2_T;    /* BANDGAP��THSD����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_dr3_int                 : 1; /* [0..0] 0:  �ر�DR3��1: ����DR3�� */
        unsigned int    dr3_mode                   : 1; /* [1..1] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR3����ģʽ��    */
        unsigned int    en_dr4_int                 : 1; /* [2..2] 0:  �ر�DR4��1: ����DR4�� */
        unsigned int    dr4_mode                   : 1; /* [3..3] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR4����ģʽ��    */
        unsigned int    en_dr5_int                 : 1; /* [4..4] 0:  �ر�DR5��1: ����DR5�� */
        unsigned int    dr5_mode                   : 1; /* [5..5] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR5����ģʽ��    */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR_FLA_CTRL1_T;    /* DR��˸ģʽ����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_dr1_int                 : 1; /* [0..0] 0:  �ر�DR1��1: ����DR1  �� */
        unsigned int    dr1_mode                   : 1; /* [1..1] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR1����ģʽ�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    en_dr2_int                 : 1; /* [4..4] 0:  �ر�DR2��1: ����DR2�� */
        unsigned int    dr2_mode                   : 1; /* [5..5] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR2����ģʽ��    */
        unsigned int    reserved_0                 : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR_FLA_CTRL2_T;    /* DR��˸ģʽ����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    flash_period               : 8; /* [7..0] ��˸����T = ����ֵ *31.25ms�� */
    } bits;
    unsigned int    u32;
}HI6551_FLASH_PERIOD_T;    /* DR��˸ģʽ���ڵ��ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_on                   : 8; /* [7..0] ����ʱ��t =����ֵ *7.8125ms�� */
    } bits;
    unsigned int    u32;
}HI6551_FLASH_ON_T;    /* DR��˸ģʽ����ʱ����ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_mode_sel               : 1; /* [0..0] 0: DR1�����ں�������ģʽ��1��DR1��������˸ģʽ�� */
        unsigned int    dr2_mode_sel               : 1; /* [1..1] 0: DR2�����ں�������ģʽ��1��DR2��������˸ģʽ�� */
        unsigned int    dr3_mode_sel               : 1; /* [2..2] 0: DR3�����ں�������ģʽ��1��DR3��������˸ģʽ�� */
        unsigned int    dr4_mode_sel               : 1; /* [3..3] 0: DR4�����ں�������ģʽ��1��DR4��������˸ģʽ�� */
        unsigned int    dr5_mode_sel               : 1; /* [4..4] 0: DR5�����ں�������ģʽ��1��DR5��������˸ģʽ�� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR_MODE_SEL_T;    /* DR��ģʽѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_en                     : 1; /* [0..0] 0��dr1�ر� �� 1��dr1ʹ�ܣ�dr1_flash_en = 1,��˸ ��dr1_flash_en = 0,���� �� */
        unsigned int    dr1_flash_en               : 1; /* [1..1] 0��dr1����˸��1��dr1��˸ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    dr2_en                     : 1; /* [4..4] 0��dr2�ر� �� 1��dr2ʹ�ܣ�dr2_flash_en = 1,��˸ ��dr2_flash_en = 0,���� �� */
        unsigned int    dr2_flash_en               : 1; /* [5..5] 0��dr2����˸��1��dr2��˸ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_DR_BRE_CTRL_T;    /* DR1/2����ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_t_off                  : 3; /* [2..0] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr1_t_on                   : 3; /* [6..4] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_DR1_TIM_CONF0_T;    /* DR1��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_t_rise                 : 3; /* [2..0] 000��0s001��0.25s010��0.5s011��1s100��2s101��2.5s110��3s111��4s */
        unsigned int    reserved_1                 : 1; /* [3..3]  */
        unsigned int    dr1_t_fall                 : 3; /* [6..4] 000��0s001��0.25s010��0.5s011��1s100��2s101��2.5s110��3s111��4s */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_DR1_TIM_CONF1_T;    /* DR1��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr1                   : 3; /* [2..0] DR1�������ڡ�                                    000: 3  mA��001: 6  mA��010: 9  mA��011: 12 mA��100: 15 mA��101: 18 mA��110: 21 mA��111: 24 mA�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_DR1_ISET_T;    /* DR1����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr2_t_off                  : 3; /* [2..0] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr2_t_on                   : 3; /* [6..4] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_DR2_TIM_CONF0_T;    /* DR2��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr2_t_rise                 : 3; /* [2..0] 000��0s001��0.25s010��0.5s011��1s100��2s101��2.5s110��3s111��4s */
        unsigned int    reserved_1                 : 1; /* [3..3]  */
        unsigned int    dr2_t_fall                 : 3; /* [6..4] 000��0s001��0.25s010��0.5s011��1s100��2s101��2.5s110��3s111��4s */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6551_DR2_TIM_CONF1_T;    /* DR2��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr2                   : 3; /* [2..0] DR2�������ڡ�                                    000: 3  mA��001: 6  mA��010: 9  mA��011: 12 mA��100: 15 mA��101: 18 mA��110: 21 mA��111: 24 mA�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_DR2_ISET_T;    /* DR2����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_en                     : 1; /* [0..0] DR3ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    dr4_en                     : 1; /* [1..1] DR4ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    dr5_en                     : 1; /* [2..2] DR5ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    dr_eco_en                  : 1; /* [3..3] ���ƺ����Ƴ�������ʱ�Զ��ر�ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR_LED_CTRL_T;    /* DR3/4/5���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_out_ctrl               : 2; /* [1..0] DR3������ơ�00��DR3�������������DR3�ܽţ�01��DR3��DR4����������������DR3�ܽţ�10��DR3��DR4��DR5����������������DR3�ܽţ�11��DR4��DR5����������������DR3�ܽš� */
        unsigned int    dr4_out_ctrl               : 2; /* [3..2] DR4������ơ�00��DR4�������������DR4�ܽţ�01��DR3��DR4����������������DR4�ܽţ�10��DR3��DR4��DR5����������������DR4�ܽţ�11��DR4��DR5����������������DR4�ܽš� */
        unsigned int    dr5_out_ctrl               : 2; /* [5..4] DR5������ơ�00��DR5�������������DR5�ܽţ�01��DR3��DR4����������������DR5�ܽţ�10��DR3��DR4��DR5����������������DR5�ܽţ�11��DR4��DR5����������������DR5�ܽš� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR_OUT_CTRL_T;    /* DR3/4/5������ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr3                   : 3; /* [2..0] R3����������ڣ�mA����0x0 : 1.0��0x1 : 1.5��0x2 : 2.0��0x3 : 2.5��0x4 : 3.0��0x5 : 3.5��0x6 : 4.0��0x7 : 4.5�� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR3_ISET_T;    /* DR3����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_start_delay            : 8; /* [7..0] DR3������ʱ��Χ��0��32768 ms��step��256ms�� */
    } bits;
    unsigned int    u32;
}HI6551_DR3_START_DEL_T;    /* DR3������ʱ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_t_off                  : 4; /* [3..0] DR3����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    dr3_t_on                   : 4; /* [7..4] DR3����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
    } bits;
    unsigned int    u32;
}HI6551_DR3_TIM_CONF0_T;    /* DR3��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_t_rise                 : 3; /* [2..0] DR3����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    dr3_t_fall                 : 3; /* [6..4] DR3����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR3_TIM_CONF1_T;    /* DR3��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr4                   : 3; /* [2..0] DR4����������ڣ�mA����0x0 : 1.0��0x1 : 1.5��0x2 : 2.0��0x3 : 2.5��0x4 : 3.0��0x5 : 3.5��0x6 : 4.0��0x7 : 4.5�� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR4_ISET_T;    /* DR4����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr4_start_delay            : 8; /* [7..0] DR4������ʱ��Χ��0��32768 ms��step��256ms�� */
    } bits;
    unsigned int    u32;
}HI6551_DR4_START_DEL_T;    /* DR4������ʱ���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    dr4_t_off                  : 4; /* [3..0] DR4����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    dr4_t_on                   : 4; /* [7..4] DR4����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
    } bits;
    unsigned int    u32;
}HI6551_DR4_TIM_CONF0_T;    /* DR4��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr4_t_rise                 : 3; /* [2..0] DR4����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    dr4_t_fall                 : 3; /* [6..4] DR4����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR4_TIM_CONF1_T;    /* DR4��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr5                   : 3; /* [2..0] DR5����������ڣ�mA����0x0 : 1.0��0x1 : 1.5��0x2 : 2.0��0x3 : 2.5��0x4 : 3.0��0x5 : 3.5��0x6 : 4.0��0x7 : 4.5�� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR5_ISET_T;    /* DR5����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr5_start_delay            : 8; /* [7..0] DR5������ʱ��Χ��0��32768 ms��step��256ms�� */
    } bits;
    unsigned int    u32;
}HI6551_DR5_START_DEL_T;    /* DR5������ʱ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr5_t_off                  : 4; /* [3..0] DR5����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    dr5_t_on                   : 4; /* [7..4] DR5����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
    } bits;
    unsigned int    u32;
}HI6551_DR5_TIM_CONF0_T;    /* DR5��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr5_t_rise                 : 3; /* [2..0] DR5����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    dr5_t_fall                 : 3; /* [6..4] DR5����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6551_DR5_TIM_CONF1_T;    /* DR5��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pwe_int                : 1; /* [0..0] OTPд�����źš� */
        unsigned int    otp_pwe_pulse              : 1; /* [1..1] 0�����������壻1����otp_write_mask=1ʱ������һ��310us�ĸߵ�ƽ���塣 */
        unsigned int    otp_write_mask             : 1; /* [2..2] 0:��otp_pwe�źſ���OTP��д������1:��otp_pwe_pulse�źſ���OTP��д������ */
        unsigned int    otp_por_int                : 1; /* [3..3] OTP�������źš�0: otp������1���Զ���32bits otpֵ���ص����µ�Ĵ������档 */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_OTP_CTRL1_T;    /* OTP����1�źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pa                     : 2; /* [1..0] OTP�ĵ�ַ�źš� */
        unsigned int    otp_ptm                    : 2; /* [3..2] ����ģʽʹ���źš� */
        unsigned int    otp_pprog                  : 1; /* [4..4] ���ģʽʹ���źš� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6551_OTP_CTRL2_T;    /* OTP����2�źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdin                   : 8; /* [7..0] OTP������ֵ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI6551_OTP_PDIN_T;    /* OTPд��ֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob0                  : 8; /* [7..0] OTP_PDOB[7:0] */
    } bits;
    unsigned int    u32;
}HI6551_OTP_PDOB0_T;    /* OTP����ֵ0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob1                  : 8; /* [7..0] OTP_PDOB[15:8] */
    } bits;
    unsigned int    u32;
}HI6551_OTP_PDOB1_T;    /* OTP����ֵ1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob2                  : 8; /* [7..0] OTP_PDOB[23:16] */
    } bits;
    unsigned int    u32;
}HI6551_OTP_PDOB2_T;    /* OTP����ֵ2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob3                  : 8; /* [7..0] OTP_PDOB[31:24] */
    } bits;
    unsigned int    u32;
}HI6551_OTP_PDOB3_T;    /* OTP����ֵ3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a0                   : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCCR_A0_T;    /* RTC_A����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a1                   : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCCR_A1_T;    /* RTC_A����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a2                   : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCCR_A2_T;    /* RTC_A����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a3                   : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCCR_A3_T;    /* RTC_A����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_a0                   : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCLR_A0_T;    /* RTCLR_A����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_a1                   : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCLR_A1_T;    /* RTCLR_A����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_a2                   : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCLR_A2_T;    /* RTCLR_A����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_a3                   : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCLR_A3_T;    /* RTCLR_A����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a                    : 1; /* [0..0] ��RTC����λ0����RTC��ǰֵ������ֵȫ��Ϊ0��1����RTC��ǰֵ������ֵΪʵ�ʵ�ǰֵ�� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI6551_RTCCTRL_A_T;    /* RTCCTRL_A���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_a0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_A0_T;    /* RTC_A_A�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_a1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_A1_T;    /* RTC_A_A�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_a2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_A2_T;    /* RTC_A_A�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_a3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_A3_T;    /* RTC_A_A�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_b0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_B0_T;    /* RTC_A_B�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_b1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_B1_T;    /* RTC_A_B�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_b2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_B2_T;    /* RTC_A_B�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_b3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_B3_T;    /* RTC_A_B�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_c0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_C0_T;    /* RTC_A_C�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_c1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_C1_T;    /* RTC_A_C�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_c2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_C2_T;    /* RTC_A_C�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_c3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_C3_T;    /* RTC_A_C�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_d0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_D0_T;    /* RTC_A_D�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_d1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_D1_T;    /* RTC_A_D�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_d2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_D2_T;    /* RTC_A_D�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_d3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_D3_T;    /* RTC_A_D�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_e0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_E0_T;    /* RTC_A_E�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_e1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_E1_T;    /* RTC_A_E�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_e2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_E2_T;    /* RTC_A_E�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_e3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_E3_T;    /* RTC_A_E�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_f0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_F0_T;    /* RTC_A_F�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_f1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_F1_T;    /* RTC_A_F�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_f2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_F2_T;    /* RTC_A_F�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_f3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_RTCMR_A_F3_T;    /* RTC_A_F�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na0                  : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[7:0]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6551_RTCCR_NA0_T;    /* RTC_NA����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na1                  : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[15:8]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6551_RTCCR_NA1_T;    /* RTC_NA����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na2                  : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[23:16]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6551_RTCCR_NA2_T;    /* RTC_NA����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na3                  : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[31:24]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6551_RTCCR_NA3_T;    /* RTC_NA����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_na0                  : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[7:0]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6551_RTCLR_NA0_T;    /* RTCLR_NA����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_na1                  : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[15:8]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6551_RTCLR_NA1_T;    /* RTCLR_NA����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_na2                  : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[23:16]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6551_RTCLR_NA2_T;    /* RTCLR_NA����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_na3                  : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[31:24]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6551_RTCLR_NA3_T;    /* RTCLR_NA����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na                   : 1; /* [0..0] ��RTC����λ0����RTC��ǰֵ������ֵȫ��Ϊ0��1����RTC��ǰֵ������ֵΪʵ�ʵ�ǰֵ��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI6551_RTCCTRL_NA_T;    /* RTCCTRL_NA���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    version                    : 8; /* [7..0] �汾�Ĵ�������ʾ�汾ΪV220�� */
    } bits;
    unsigned int    u32;
}HI6551_VERSION_T;    /* �汾�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved0                  : 8; /* [7..0] bit[7:4]�������� ������δ����bit[3:0]: lvs��offset�����Ĵ����� */
    } bits;
    unsigned int    u32;
}HI6551_RESERVED0_T;    /* ����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved1                  : 8; /* [7..0] bit[7:2]:������ ������δ����bit[1:0]:����REF����ECOģʽ�� */
    } bits;
    unsigned int    u32;
}HI6551_RESERVED1_T;    /* ����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved2                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI6551_RESERVED2_T;    /* ����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved3                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI6551_RESERVED3_T;    /* ����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved4                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI6551_RESERVED4_T;    /* ����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    htol_mode                  : 4; /* [3..0] 0101���������ϻ�ģʽ ��1010�������ϻ�����ģʽ ����������Ч ��ע���ϻ�����ר�á� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6551_HTOL_MODE_T;    /* �ϻ�����ģʽ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dac_on_sel                 : 1; /* [0..0] 1: ����DAC�Ŀ�����dac_reg_onoff���ƣ�0������DAC�Ŀ��������pin�ſ��ơ� */
        unsigned int    aux_ibias_cfg              : 2; /* [2..1] AUXDACƫ�õ������ڣ�11���00��С */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_DAC_CTRL_T;    /* DAC���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    soft_rst                   : 8; /* [7..0] 0x11:��λ���ؼ�ģ�飻0x1f:������ؼ�ģ�鸴λ��д��������Ч�� */
    } bits;
    unsigned int    u32;
}HI6551_CHIP_SOFT_RST_T;    /* оƬģ����λ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pdns_sel                   : 3; /* [2..0] ������Ns�ػ�����Ĵ�����000:6s;001:7s;010:8s;011:9s;100:10s;101:11s;110:8s;111:9s�� */
        unsigned int    pdns_mk                    : 1; /* [3..3] �������ػ����μĴ�����0�������γ������ػ���1�����γ������ػ���ע�������������У�һֱ����pwron_n ����ʱ�ſ���ͨ��SSI���������ػ�����λ��һ����pwron_n�ɿ�20ms���λ�Զ������ */
        unsigned int    vsys_uv_adj                : 1; /* [4..4] 2.7V/3VǷѹ�������ڣ�0��vsys��ѹ������Ϊ3.0V��1��vsys��ѹ������Ϊ2.7V�� */
        unsigned int    nopwr_rc_off               : 1; /* [5..5] �ر��ڲ�256K RCʱ��:0:ʹ��;1:�رա� */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6551_NP_REG_ADJ_T;    /* ���µ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    nopwr_vcoinsl              : 2; /* [1..0] ���õ�س���ѹѡ��00��2.5V��01��3.0V��1X��3.3V�� */
        unsigned int    nopwr_en_backup_chg        : 1; /* [2..2] ���õ�س��ʹ�ܣ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6551_NP_REG_CHG_T;    /* ���õ�ط��µ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved1             : 8; /* [7..0] ģ��Ԥ���������ü�����δ�� */
    } bits;
    unsigned int    u32;
}HI6551_NP_RSVED1_T;    /* ���µ籣��1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved2             : 8; /* [7..0] ģ��Ԥ���������ü�����δ�� */
    } bits;
    unsigned int    u32;
}HI6551_NP_RSVED2_T;    /* ���µ籣��2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved3             : 8; /* [7..0] ��ƷԤ���������ü����ã�����PMU�ڲ�����״̬�����κ����ã������ڼ�¼��Ϣ�� */
    } bits;
    unsigned int    u32;
}HI6551_NP_RSVED3_T;    /* ���µ籣��3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved4             : 8; /* [7..0] ��ƷԤ���������ü����ã�����PMU�ڲ�����״̬�����κ����ã������ڼ�¼��Ϣ�� */
    } bits;
    unsigned int    u32;
}HI6551_NP_RSVED4_T;    /* ���µ籣��4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_clk_step_adj1          : 8; /* [7..0] ��ʱ���ȿ��Ե��ڣ����ڷ�Χ+/-192ppm��63��ʱ�ӣ������ڲ���3.05ppm��1��ʱ�ӣ���Ĭ��Ϊ0�� */
    } bits;
    unsigned int    u32;
}HI6551_RTC_ADJ1_T;    /* rtc_adj[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_clk_step_adj2          : 8; /* [7..0] ��ʱ���ȿ��Ե��ڣ����ڷ�Χ+/-192ppm��63��ʱ�ӣ������ڲ���3.05ppm��1��ʱ�ӣ���Ĭ��Ϊ0�� */
    } bits;
    unsigned int    u32;
}HI6551_RTC_ADJ2_T;    /* rtc_adj[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    eco_ctrl                   : 3; /* [2..0] bit[2]:0����ǿ�ƽ���ECOģʽ��1��ǿ�ƽ���ECOģʽ��bit[1]:0�����ؼƲ�����PMU����ECOģʽ��1�����ؼƸ���PMU����ECOģʽ����������bit[2] == 0 ʱ��Чbit[0]:0������ECOģʽʹ���źŲ�ȥ����1������ECOģʽʹ���ź�ȥ������������bit[1] ==1 ʱ��Ч */
        unsigned int    reflash_value_ctrl         : 1; /* [3..3] 0������״̬���������ݣ�1����ECOģʽ�������ݣ�Ĭ��Ϊ0�� */
        unsigned int    eco_filter_time            : 2; /* [5..4] 00��20ms��01��25ms��10��30ms��11��35ms����������en_eco_modeȥ��ʱ����Ĭ��Ϊ00�� */
        unsigned int    calibration_ctrl           : 1; /* [6..6] 1��ǿ�ƽ���У׼״̬��0����У׼��Ĭ��Ϊ0�� */
        unsigned int    coul_ctrl_onoff_reg        : 1; /* [7..7] 1�����ؼƿ�����0�����ؼƹرա�Ĭ��Ϊ1�� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_CTRL_REG_T;    /* �Ĵ������ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    eco_reflash_time           : 8; /* [7..0] �˹���ʱ����һ����λ����110ms��ΪECO_REFLASHʱ�䣻��Ч����ֵΪ1~255������ֵ����255ʱ��Ӳ��ֱ�ӱ��͵�255��Ĭ��Ϊ1�� */
    } bits;
    unsigned int    u32;
}HI6551_ECO_REFALSH_TIME_T;    /* ECO_REFLASH����ʱ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_out0                    : 8; /* [7..0] �������������[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CL_OUT0_T;    /* cl_out[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_out1                    : 8; /* [7..0] �������������[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CL_OUT1_T;    /* cl_out[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_out2                    : 8; /* [7..0] �������������[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_CL_OUT2_T;    /* cl_out[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_out3                    : 8; /* [7..0] �������������[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_CL_OUT3_T;    /* cl_out[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_in0                     : 8; /* [7..0] ��������������[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CL_IN0_T;    /* cl_in[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_in1                     : 8; /* [7..0] ��������������[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CL_IN1_T;    /* cl_in[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_in2                     : 8; /* [7..0] ��������������[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_CL_IN2_T;    /* cl_in[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_in3                     : 8; /* [7..0] ��������������[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_CL_IN3_T;    /* cl_in[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    chg_timer0                 : 8; /* [7..0] �ŵ�ʱ�������[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CHG_TIMER0_T;    /* chg_timer[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    chg_timer1                 : 8; /* [7..0] �ŵ�ʱ�������[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CHG_TIMER1_T;    /* chg_timer[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    chg_timer2                 : 8; /* [7..0] �ŵ�ʱ�������[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_CHG_TIMER2_T;    /* chg_timer[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    chg_timer3                 : 8; /* [7..0] �ŵ�ʱ�������[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_CHG_TIMER3_T;    /* chg_timer[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    load_timer0                : 8; /* [7..0] ���ʱ�������[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_LOAD_TIMER0_T;    /* load_timer[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    load_timer1                : 8; /* [7..0] ���ʱ�������[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_LOAD_TIMER1_T;    /* load_timer[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    load_timer2                : 8; /* [7..0] ���ʱ�������[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_LOAD_TIMER2_T;    /* load_timer[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    load_timer3                : 8; /* [7..0] ���ʱ�������[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_LOAD_TIMER3_T;    /* load_timer[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    off_timer0                 : 8; /* [7..0] �ػ�������[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_OFF_TIMER0_T;    /* off_timer[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    off_timer1                 : 8; /* [7..0] �ػ�������[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_OFF_TIMER1_T;    /* off_timer[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    off_timer2                 : 8; /* [7..0] �ػ�������[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6551_OFF_TIMER2_T;    /* off_timer[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    off_timer3                 : 8; /* [7..0] �ػ�������[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6551_OFF_TIMER3_T;    /* off_timer[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_int0                    : 8; /* [7..0] ��������ж����ã�����һ��ֵ����cl_out>cl_intʱ�ϱ��жϡ� */
    } bits;
    unsigned int    u32;
}HI6551_CL_INT0_T;    /* cl_int[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_int1                    : 8; /* [7..0] ��������ж����ã�����һ��ֵ����cl_out>cl_intʱ�ϱ��жϡ� */
    } bits;
    unsigned int    u32;
}HI6551_CL_INT1_T;    /* cl_int[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_int2                    : 8; /* [7..0] ��������ж����ã�����һ��ֵ����cl_out>cl_intʱ�ϱ��жϡ� */
    } bits;
    unsigned int    u32;
}HI6551_CL_INT2_T;    /* cl_int[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cl_int3                    : 8; /* [7..0] ��������ж����ã�����һ��ֵ����cl_out>cl_intʱ�ϱ��жϡ� */
    } bits;
    unsigned int    u32;
}HI6551_CL_INT3_T;    /* cl_int[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_int0                     : 8; /* [7..0] ��ѹ�жϱȽ�ֵ�Ĵ���[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_INT0_T;    /* v_int[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_int1                     : 8; /* [7..0] ��ѹ�жϱȽ�ֵ�Ĵ���[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_INT1_T;    /* v_int[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    offset_current0            : 8; /* [7..0] ����У׼[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_OFFSET_CURRENT0_T;    /* offset_current[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    offset_current1            : 8; /* [7..0] ����У׼[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_OFFSET_CURRENT1_T;    /* offset_current[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    offset_voltage0            : 8; /* [7..0] ��ѹУ׼[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_OFFSET_VOLTAGE0_T;    /* offset_voltage[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    offset_voltage1            : 8; /* [7..0] ��ѹУ׼[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_OFFSET_VOLTAGE1_T;    /* offset_voltage[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocv_data0                  : 8; /* [7..0] OCV��ѹ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_OCV_DATA1_T;    /* ocv_data[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocv_data1                  : 8; /* [7..0] OCV��ѹ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_OCV_DATA2_T;    /* ocv_data[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre0                : 8; /* [7..0] ��ǰ��ص�ѹָʾ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE0_T;    /* v_out_pre0[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre0                : 8; /* [7..0] ��ǰ��ص�ѹָʾ[15:8]�����λ�������λ]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE0_T;    /* v_out_pre0[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre1                : 8; /* [7..0] ��ǰ��ѹǰһ��ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE1_T;    /* v_out_pre1[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre1                : 8; /* [7..0] ��ǰ��ѹǰһ��ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE1_T;    /* v_out_pre1[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre2                : 8; /* [7..0] ��ǰ��ѹǰ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE2_T;    /* v_out_pre2[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre2                : 8; /* [7..0] ��ǰ��ѹǰ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE2_T;    /* v_out_pre2[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre3                : 8; /* [7..0] ��ǰ��ѹǰ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE3_T;    /* v_out_pre3[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre3                : 8; /* [7..0] ��ǰ��ѹǰ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE3_T;    /* v_out_pre3[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre4                : 8; /* [7..0] ��ǰ��ѹǰ�Ĵ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE4_T;    /* v_out_pre4[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre4                : 8; /* [7..0] ��ǰ��ѹǰ�Ĵ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE4_T;    /* v_out_pre4[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre5                : 8; /* [7..0] ��ǰ��ѹǰ���ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE5_T;    /* v_out_pre5[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre5                : 8; /* [7..0] ��ǰ��ѹǰ���ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE5_T;    /* v_out_pre5[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre6                : 8; /* [7..0] ��ǰ��ѹǰ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE6_T;    /* v_out_pre6[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre6                : 8; /* [7..0] ��ǰ��ѹǰ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE6_T;    /* v_out_pre6[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre7                : 8; /* [7..0] ��ǰ��ѹǰ�ߴ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE7_T;    /* v_out_pre7[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre7                : 8; /* [7..0] ��ǰ��ѹǰ�ߴ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE7_T;    /* v_out_pre7[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre8                : 8; /* [7..0] ��ǰ��ѹǰ�˴�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE8_T;    /* v_out_pre8[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre8                : 8; /* [7..0] ��ǰ��ѹǰ�˴�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE8_T;    /* v_out_pre8[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre9                : 8; /* [7..0] ��ǰ��ѹǰ�Ŵ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE9_T;    /* v_out_pre9[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre9                : 8; /* [7..0] ��ǰ��ѹǰ�Ŵ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE9_T;    /* v_out_pre9[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre10               : 8; /* [7..0] ��ǰ��ѹǰʮ��ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE10_T;    /* v_out_pre10[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre10               : 8; /* [7..0] ��ǰ��ѹǰʮ��ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE10_T;    /* v_out_pre10[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre11               : 8; /* [7..0] ��ǰ��ѹǰʮһ��ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE11_T;    /* v_out_pre11[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre11               : 8; /* [7..0] ��ǰ��ѹǰʮһ��ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE11_T;    /* v_out_pre11[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre12               : 8; /* [7..0] ��ǰ��ѹǰʮ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE12_T;    /* v_out_pre12[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre12               : 8; /* [7..0] ��ǰ��ѹǰʮ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE12_T;    /* v_out_pre12[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre13               : 8; /* [7..0] ��ǰ��ѹǰʮ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE13_T;    /* v_out_pre13[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre13               : 8; /* [7..0] ��ǰ��ѹǰʮ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE13_T;    /* v_out_pre13[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre14               : 8; /* [7..0] ��ǰ��ѹǰʮ�Ĵ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE14_T;    /* v_out_pre14[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre14               : 8; /* [7..0] ��ǰ��ѹǰʮ�Ĵ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE14_T;    /* v_out_pre14[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre15               : 8; /* [7..0] ��ǰ��ѹǰʮ���ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE15_T;    /* v_out_pre15[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre15               : 8; /* [7..0] ��ǰ��ѹǰʮ���ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE15_T;    /* v_out_pre15[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre16               : 8; /* [7..0] ��ǰ��ѹǰʮ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE16_T;    /* v_out_pre16[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre16               : 8; /* [7..0] ��ǰ��ѹǰʮ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE16_T;    /* v_out_pre16[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre17               : 8; /* [7..0] ��ǰ��ѹǰʮ�ߴ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE17_T;    /* v_out_pre17[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre17               : 8; /* [7..0] ��ǰ��ѹǰʮ�ߴ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE17_T;    /* v_out_pre17[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre18               : 8; /* [7..0] ��ǰ��ѹǰʮ�˴�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE18_T;    /* v_out_pre18[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre18               : 8; /* [7..0] ��ǰ��ѹǰʮ�˴�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE18_T;    /* v_out_pre18[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out0_pre19               : 8; /* [7..0] ��ǰ��ѹǰʮ�Ŵ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT0_PRE19_T;    /* v_out_pre19[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_out1_pre19               : 8; /* [7..0] ��ǰ��ѹǰʮ�Ŵ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_V_OUT1_PRE19_T;    /* v_out_pre19[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre0              : 8; /* [7..0] ��ǰ����ָʾ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE0_T;    /* current_pre0[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre0              : 8; /* [7..0] ��ǰ����ָʾ[15:8]�����λ�������λ��. */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE0_T;    /* current_pre0[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre1              : 8; /* [7..0] ��ǰ����ǰһ��ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE1_T;    /* current_pre1[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre1              : 8; /* [7..0] ��ǰ����ǰһ��ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE1_T;    /* current_pre1[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre2              : 8; /* [7..0] ��ǰ����ǰ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE2_T;    /* current_pre2[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre2              : 8; /* [7..0] ��ǰ����ǰ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE2_T;    /* current_pre2[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre3              : 8; /* [7..0] ��ǰ����ǰ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE3_T;    /* current_pre3[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre3              : 8; /* [7..0] ��ǰ����ǰ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE3_T;    /* current_pre3[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre4              : 8; /* [7..0] ��ǰ����ǰ�Ĵ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE4_T;    /* current_pre4[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre4              : 8; /* [7..0] ��ǰ����ǰ�Ĵ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE4_T;    /* current_pre4[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre5              : 8; /* [7..0] ��ǰ����ǰ���ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE5_T;    /* current_pre5[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre5              : 8; /* [7..0] ��ǰ����ǰ���ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE5_T;    /* current_pre5[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre6              : 8; /* [7..0] ��ǰ����ǰ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE6_T;    /* current_pre6[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre6              : 8; /* [7..0] ��ǰ����ǰ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE6_T;    /* current_pre6[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre7              : 8; /* [7..0] ��ǰ����ǰ�ߴ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE7_T;    /* current_pre7[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre7              : 8; /* [7..0] ��ǰ����ǰ�ߴ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE7_T;    /* current_pre7[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre8              : 8; /* [7..0] ��ǰ����ǰ�˴�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE8_T;    /* current_pre8[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre8              : 8; /* [7..0] ��ǰ����ǰ�˴�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE8_T;    /* current_pre8[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre9              : 8; /* [7..0] ��ǰ����ǰ�Ŵ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE9_T;    /* current_pre9[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre9              : 8; /* [7..0] ��ǰ����ǰ�Ŵ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE9_T;    /* current_pre9[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre10             : 8; /* [7..0] ��ǰ����ǰʮ��ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE10_T;    /* current_pre10[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre10             : 8; /* [7..0] ��ǰ����ǰʮ��ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE10_T;    /* current_pre10[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre11             : 8; /* [7..0] ��ǰ����ǰʮһ��ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE11_T;    /* current_pre11[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre11             : 8; /* [7..0] ��ǰ����ǰʮһ��ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE11_T;    /* current_pre11[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre12             : 8; /* [7..0] ��ǰ����ǰʮ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE12_T;    /* current_pre12[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre12             : 8; /* [7..0] ��ǰ����ǰʮ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE12_T;    /* current_pre12[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre13             : 8; /* [7..0] ��ǰ����ǰʮ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE13_T;    /* current_pre13[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre13             : 8; /* [7..0] ��ǰ����ǰʮ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE13_T;    /* current_pre13[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre14             : 8; /* [7..0] ��ǰ����ǰʮ�Ĵ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE14_T;    /* current_pre14[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre14             : 8; /* [7..0] ��ǰ����ǰʮ�Ĵ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE14_T;    /* current_pre14[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre15             : 8; /* [7..0] ��ǰ����ǰʮ���ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE15_T;    /* current_pre15[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre15             : 8; /* [7..0] ��ǰ����ǰʮ���ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE15_T;    /* current_pre15[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre16             : 8; /* [7..0] ��ǰ����ǰʮ����ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE16_T;    /* current_pre16[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre16             : 8; /* [7..0] ��ǰ����ǰʮ����ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE16_T;    /* current_pre16[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre17             : 8; /* [7..0] ��ǰ����ǰʮ�ߴ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE17_T;    /* current_pre17[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre17             : 8; /* [7..0] ��ǰ����ǰʮ�ߴ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE17_T;    /* current_pre17[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre18             : 8; /* [7..0] ��ǰ����ǰʮ�˴�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE18_T;    /* current_pre18[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre18             : 8; /* [7..0] ��ǰ����ǰʮ�˴�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE18_T;    /* current_pre18[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current0_pre19             : 8; /* [7..0] ��ǰ����ǰʮ�Ŵ�ֵ[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT0_PRE19_T;    /* current_pre19[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    current1_pre19             : 8; /* [7..0] ��ǰ����ǰʮ�Ŵ�ֵ[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6551_CURRENT1_PRE19_T;    /* current_pre19[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cic_clk_inv_i              : 1; /* [0..0] ���ƿ��ؼƵ����˲���·��һ��ȡ��ʱ�ӡ�0����Ч��1����Ч */
        unsigned int    cic_clk_inv_v              : 1; /* [1..1] ���ƿ��ؼƵ�ѹ�˲���·��һ��ȡ��ʱ�ӡ�0����Ч��1����Ч */
        unsigned int    adc_ana_v_output           : 1; /* [2..2] ����CK32BC�ܽţ���ѹADCģ����� */
        unsigned int    adc_ana_i_output           : 1; /* [3..3] ����CK32C�ܽţ�����ADCģ����� */
        unsigned int    cali_en_i                  : 1; /* [4..4] 0:����������1������ʼ�ղ����м��У׼��Ĭ��Ϊ0 */
        unsigned int    cali_en_i_force            : 1; /* [5..5] 1������ǿ��У׼��0��������ǿ��У׼��Ĭ�ϣ������Ϲ��ܾ���clj_debug[4]=0ʱ�����á� */
        unsigned int    cali_en_v_force            : 1; /* [6..6] 1����ѹǿ��У׼��0����ѹ��ǿ��У׼��Ĭ�ϣ������Ϲ��ܾ���clj_debug[7]=0ʱ�����á� */
        unsigned int    cali_en_v                  : 1; /* [7..7] 0:����������1����ѹ��ⲻ����У׼��Ĭ��Ϊ0 */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_DEBUG_T;    /* ���ؼ�DEBUGר��1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    state_test                 : 8; /* [7..0] �����͵�ѹ�����ת״̬��[7:4]��ʾ������ת״̬��[3:0]��ʾ��ѹ��ת״̬�� */
    } bits;
    unsigned int    u32;
}HI6551_STATE_TEST_T;    /* ���ؼ�DEBUGר��2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reg_data_clr               : 1; /* [0..0] 40��Ĵ�������������ѹ�����ֵ�ָ�ԭʼֵ��־��0�����ָ���ʼֵ��1���ָ���ʼֵ �� */
        unsigned int    clj_rw_inf1                : 7; /* [7..1] ��Ʒ���ר�ã��Կ��ؼƿ�ά�ɲ⣬�����ڼ�¼���ݣ����Կ��ؼ�״̬�����κ����á� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_RESERVED1_T;    /* ���ؼƱ���1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    clj_rw_inf2                : 8; /* [7..0] ��Ʒ���ר�ã��Կ��ؼƿ�ά�ɲ⣬�����ڼ�¼���ݣ����Կ��ؼ�״̬�����κ����á� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_RESERVED2_T;    /* ���ؼƱ���2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    clj_rw_inf3                : 8; /* [7..0] ��Ʒ���ר�ã��Կ��ؼƿ�ά�ɲ⣬�����ڼ�¼���ݣ����Կ��ؼ�״̬�����κ����á� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_RESERVED3_T;    /* ���ؼƱ���3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    clj_rw_inf4                : 8; /* [7..0] ��Ʒ���ר�ã��Կ��ؼƿ�ά�ɲ⣬�����ڼ�¼���ݣ����Կ��ؼ�״̬�����κ����á� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_RESERVED4_T;    /* ���ؼƱ���4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    i_reserve_1                : 8; /* [7..0] ���ؼ�ģ��Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_RESERVED5_T;    /* ���ؼƱ���5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    i_reserve_2                : 8; /* [7..0] ���ؼ�ģ��Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_RESERVED6_T;    /* ���ؼƱ���6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_reserve_1                : 8; /* [7..0] ���ؼ�ģ��Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_RESERVED7_T;    /* ���ؼƱ���7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    v_reserve_2                : 8; /* [7..0] ���ؼ�ģ��Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6551_CLJ_RESERVED8_T;    /* ���ؼƱ���8�Ĵ����� */


/********************************************************************************/
/*    hi6551 ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_hi6551_status1_otmp_d1r,otmp_d1r,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_otmp150_d1r,otmp150_d1r,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_osc_state,osc_state,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_vsys_uv_d2f,vsys_uv_d2f,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_vsys_6p0_d200ur,vsys_6p0_d200ur,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_pwron_d20r,pwron_d20r,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_reserved,reserved,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_a,alarm_on_a,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_b,alarm_on_b,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_c,alarm_on_c,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_d,alarm_on_d,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_e,alarm_on_e,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_vbus_det_0p9_d3r,vbus_det_0p9_d3r,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_reserved,reserved,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_irq1_otmp_d1r,otmp_d1r,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_vsys_2p5_f,vsys_2p5_f,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_vsys_uv_d2f,vsys_uv_d2f,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_vsys_6p0_d200ur,vsys_6p0_d200ur,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_pwron_d4sr,pwron_d4sr,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_pwron_d20f,pwron_d20f,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_pwron_d20r,pwron_d20r,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_reserved,reserved,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq2_ocp_scp_r,ocp_scp_r,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq2_vbus_det_1p375_d90ur,vbus_det_1p375_d90ur,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq2_vbus_det_0p9_d3f,vbus_det_0p9_d3f,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq2_vbus_det_0p9_d3r,vbus_det_0p9_d3r,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq2_reserved,reserved,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_a,alarm_on_a,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_b,alarm_on_b,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_c,alarm_on_c,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_d,alarm_on_d,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_e,alarm_on_e,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_f,alarm_on_f,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_reserved,reserved,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim0_hpd_out_f,sim0_hpd_out_f,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim0_hpd_out_r,sim0_hpd_out_r,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim0_hpd_in_f,sim0_hpd_in_f,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim0_hpd_in_r,sim0_hpd_in_r,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim1_hpd_out_f,sim1_hpd_out_f,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim1_hpd_out_r,sim1_hpd_out_r,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim1_hpd_in_f,sim1_hpd_in_f,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim1_hpd_in_r,sim1_hpd_in_r,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_cl_int_i,cl_int_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_cl_out_i,cl_out_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_cl_in_i,cl_in_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_chg_timer_i,chg_timer_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_load_timer_i,load_timer_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_vbat_int_i,vbat_int_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_reserved,reserved,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_otmp_d1r_mk,otmp_d1r_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_vsys_2p5_f_mk,vsys_2p5_f_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_vsys_uv_d2f_mk,vsys_uv_d2f_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_vsys_6p0_d200ur_mk,vsys_6p0_d200ur_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_pwron_d4sr_mk,pwron_d4sr_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_pwron_d20f_mk,pwron_d20f_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_pwron_d20r_mk,pwron_d20r_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_reserved,reserved,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_ocp_scp_r_mk,ocp_scp_r_mk,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_vbus_det_1p375_mk,vbus_det_1p375_mk,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_vbus_det_0p9_d3f_mk,vbus_det_0p9_d3f_mk,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_vbus_det_0p9_d3r_mk,vbus_det_0p9_d3r_mk,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_reserved,reserved,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_a_mk,alarm_on_a_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_b_mk,alarm_on_b_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_c_mk,alarm_on_c_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_d_mk,alarm_on_d_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_e_mk,alarm_on_e_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_f_mk,alarm_on_f_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_reserved,reserved,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim0_hpd_out_f_mk,sim0_hpd_out_f_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim0_hpd_out_r_mk,sim0_hpd_out_r_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim0_hpd_in_f_mk,sim0_hpd_in_f_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim0_hpd_in_r_mk,sim0_hpd_in_r_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim1_hpd_out_f_mk,sim1_hpd_out_f_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim1_hpd_out_r_mk,sim1_hpd_out_r_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim1_hpd_in_f_mk,sim1_hpd_in_f_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim1_in_hpd_r_mk,sim1_in_hpd_r_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_cl_int_i_mk,cl_int_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_cl_out_i_mk,cl_out_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_cl_in_i_mk,cl_in_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_chg_timer_i_mk,chg_timer_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_load_timer_i_mk,load_timer_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_vbat_int_i_mk,vbat_int_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_reserved,reserved,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck0_1,scp_buck0_1,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck2,scp_buck2,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck3,scp_buck3,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck4,scp_buck4,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck5,scp_buck5,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck6,scp_buck6,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_reserved,reserved,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck0_1,ocp_buck0_1,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck2,ocp_buck2,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck3,ocp_buck3,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck4,ocp_buck4,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck5,ocp_buck5,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck6,ocp_buck6,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_reserved,reserved,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo1,ocp_ldo1,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo2,ocp_ldo2,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo3,ocp_ldo3,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo4,ocp_ldo4,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo5,ocp_ldo5,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo6,ocp_ldo6,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo7,ocp_ldo7,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo8,ocp_ldo8,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo9,ocp_ldo9,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo10,ocp_ldo10,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo11,ocp_ldo11,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo12,ocp_ldo12,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo13,ocp_ldo13,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo14,ocp_ldo14,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo15,ocp_ldo15,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo16,ocp_ldo16,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo17,ocp_ldo17,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo18,ocp_ldo18,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo19,ocp_ldo19,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo20,ocp_ldo20,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo21,ocp_ldo21,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo22,ocp_ldo22,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo23,ocp_ldo23,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo24,ocp_ldo24,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs2,ocp_lvs2,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs3,ocp_lvs3,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs4,ocp_lvs4,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs5,ocp_lvs5,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs7,ocp_lvs7,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs6,ocp_lvs6,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs8,ocp_lvs8,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_reserved,reserved,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record6_ocp_lvs9,ocp_lvs9,HI6551_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record6_ocp_lvs10,ocp_lvs10,HI6551_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record6_reserved,reserved,HI6551_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_ocp_boost,ocp_boost,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_scp_boost,scp_boost,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_ovp_boost,ovp_boost,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_uvp_boost,uvp_boost,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_ocp_classd,ocp_classd,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_reserved,reserved,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_otmp_d1r,np_otmp_d1r,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_hreset_n_f,np_hreset_n_f,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_vsys_2p5_f,np_vsys_2p5_f,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_vsys_uv_d2f,np_vsys_uv_d2f,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_vsys_6p0_d200ur,np_vsys_6p0_d200ur,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_pwron_d4sr,np_pwron_d4sr,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_pwron_d20f,np_pwron_d20f,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_pwron_d20r,np_pwron_d20r,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_vbus_det_0p9_d150r,np_vbus_det_0p9_d150r,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_vbus_det_1p375,np_vbus_det_1p375,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_vbus_det_0p9_d3f,np_vbus_det_0p9_d3f,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_vbus_det_0p9_d3r,np_vbus_det_0p9_d3r,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_pwron_restart,np_pwron_restart,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_pwron_dnsr,np_pwron_dnsr,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_pwron_d500r,np_pwron_d500r,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_otmp150_d1r,np_otmp150_d1r,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_a,np_alarm_on_a,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_b,np_alarm_on_b,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_c,np_alarm_on_c,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_d,np_alarm_on_d,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_e,np_alarm_on_e,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_f,np_alarm_on_f,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_reserved,reserved,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck0_1,np_scp_buck0_1,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck2,np_scp_buck2,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck3,np_scp_buck3,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck4,np_scp_buck4,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck5,np_scp_buck5,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck6,np_scp_buck6,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_reserved,reserved,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck0,np_ocp_buck0,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck1,np_ocp_buck1,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck0_1,np_ocp_buck0_1,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck2,np_ocp_buck2,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck3,np_ocp_buck3,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck4,np_ocp_buck4,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck5,np_ocp_buck5,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck6,np_ocp_buck6,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo1,np_ocp_ldo1,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo2,np_ocp_ldo2,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo3,np_ocp_ldo3,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo4,np_ocp_ldo4,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo5,np_ocp_ldo5,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo6,np_ocp_ldo6,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo7,np_ocp_ldo7,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo8,np_ocp_ldo8,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo9,np_ocp_ldo9,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo10,np_ocp_ldo10,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo11,np_ocp_ldo11,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo12,np_ocp_ldo12,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo13,np_ocp_ldo13,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo14,np_ocp_ldo14,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo15,np_ocp_ldo15,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo16,np_ocp_ldo16,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo17,np_ocp_ldo17,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo18,np_ocp_ldo18,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo19,np_ocp_ldo19,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo20,np_ocp_ldo20,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo21,np_ocp_ldo21,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo22,np_ocp_ldo22,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo23,np_ocp_ldo23,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo24,np_ocp_ldo24,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs2,np_ocp_lvs2,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs3,np_ocp_lvs3,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs4,np_ocp_lvs4,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs5,np_ocp_lvs5,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs7,np_ocp_lvs7,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs6,np_ocp_lvs6,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs8,np_ocp_lvs8,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_reserved,reserved,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record6_np_ocp_lvs9,np_ocp_lvs9,HI6551_NP_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record6_np_ocp_lvs10,np_ocp_lvs10,HI6551_NP_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record6_reserved,reserved,HI6551_NP_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_ocp_boost,np_ocp_boost,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_scp_boost,np_scp_boost,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_ovp_boost,np_ovp_boost,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_uvp_boost,np_uvp_boost,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_ocp_classd,np_ocp_classd,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_reserved,reserved,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_ocp_ldo_deb_sel,ocp_ldo_deb_sel,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_en_ldo_ocp_deb,en_ldo_ocp_deb,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_ocp_buck_deb_sel,ocp_buck_deb_sel,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_en_buck_ocp_deb,en_buck_ocp_deb,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_en_buck_scp_deb,en_buck_scp_deb,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_en_bst_ocp_deb,en_bst_ocp_deb,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_vbus_det_0p9_ctrl,vbus_det_0p9_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_vsys_2p5_ctrl,vsys_2p5_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_vsys_uv_ctrl,vsys_uv_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_vsys_6p0_ctrl,vsys_6p0_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_otmp150_ctrl,otmp150_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_en_32kc,en_32kc,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_en_32kb,en_32kb,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_en_32ka,en_32ka,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_ctrl_buck0_1,ocp_scp_ctrl_buck0_1,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_off_buck0_1,ocp_scp_off_buck0_1,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_ctrl_buck2,ocp_scp_ctrl_buck2,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_off_buck2,ocp_scp_off_buck2,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_ctrl_buck3,ocp_scp_ctrl_buck3,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_off_buck3,ocp_scp_off_buck3,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_ctrl_buck4,ocp_scp_ctrl_buck4,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_off_buck4,ocp_scp_off_buck4,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_ocp_scp_ctrl_buck5,ocp_scp_ctrl_buck5,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_ocp_scp_off_buck5,ocp_scp_off_buck5,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_ocp_scp_ctrl_buck6,ocp_scp_ctrl_buck6,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_ocp_scp_off_buck6,ocp_scp_off_buck6,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_reserved,reserved,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_ctrl_ldo1,ocp_ctrl_ldo1,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_off_ldo1,ocp_off_ldo1,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_ctrl_ldo2,ocp_ctrl_ldo2,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_off_ldo2,ocp_off_ldo2,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_ctrl_ldo3,ocp_ctrl_ldo3,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_off_ldo3,ocp_off_ldo3,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_ctrl_ldo4,ocp_ctrl_ldo4,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_off_ldo4,ocp_off_ldo4,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_ctrl_ldo5,ocp_ctrl_ldo5,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_off_ldo5,ocp_off_ldo5,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_ctrl_ldo6,ocp_ctrl_ldo6,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_off_ldo6,ocp_off_ldo6,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_ctrl_ldo7,ocp_ctrl_ldo7,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_off_ldo7,ocp_off_ldo7,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_ctrl_ldo8,ocp_ctrl_ldo8,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_off_ldo8,ocp_off_ldo8,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_ctrl_ldo9,ocp_ctrl_ldo9,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_off_ldo9,ocp_off_ldo9,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_ctrl_ldo10,ocp_ctrl_ldo10,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_off_ldo10,ocp_off_ldo10,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_ctrl_ldo11,ocp_ctrl_ldo11,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_off_ldo11,ocp_off_ldo11,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_ctrl_ldo12,ocp_ctrl_ldo12,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_off_ldo12,ocp_off_ldo12,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_ctrl_ldo13,ocp_ctrl_ldo13,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_off_ldo13,ocp_off_ldo13,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_ctrl_ldo14,ocp_ctrl_ldo14,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_off_ldo14,ocp_off_ldo14,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_ctrl_ldo15,ocp_ctrl_ldo15,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_off_ldo15,ocp_off_ldo15,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_ctrl_ldo16,ocp_ctrl_ldo16,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_off_ldo16,ocp_off_ldo16,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_ctrl_ldo17,ocp_ctrl_ldo17,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_off_ldo17,ocp_off_ldo17,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_ctrl_ldo18,ocp_ctrl_ldo18,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_off_ldo18,ocp_off_ldo18,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_ctrl_ldo19,ocp_ctrl_ldo19,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_off_ldo19,ocp_off_ldo19,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_ctrl_ldo20,ocp_ctrl_ldo20,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_off_ldo20,ocp_off_ldo20,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_ctrl_ldo21,ocp_ctrl_ldo21,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_off_ldo21,ocp_off_ldo21,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_ctrl_ldo22,ocp_ctrl_ldo22,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_off_ldo22,ocp_off_ldo22,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_ctrl_ldo23,ocp_ctrl_ldo23,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_off_ldo23,ocp_off_ldo23,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_ctrl_ldo24,ocp_ctrl_ldo24,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_off_ldo24,ocp_off_ldo24,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_ctrl_lvs2,ocp_ctrl_lvs2,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_off_lvs2,ocp_off_lvs2,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_ctrl_lvs3,ocp_ctrl_lvs3,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_off_lvs3,ocp_off_lvs3,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_ctrl_lvs4,ocp_ctrl_lvs4,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_off_lvs4,ocp_off_lvs4,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_ctrl_lvs5,ocp_ctrl_lvs5,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_off_lvs5,ocp_off_lvs5,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_ctrl_lvs7,ocp_ctrl_lvs7,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_off_lvs7,ocp_off_lvs7,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_ctrl_lvs6,ocp_ctrl_lvs6,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_off_lvs6,ocp_off_lvs6,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_ctrl_lvs8,ocp_ctrl_lvs8,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_off_lvs8,ocp_off_lvs8,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_ctrl_lvs9,ocp_ctrl_lvs9,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_off_lvs9,ocp_off_lvs9,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_ctrl_lvs10,ocp_ctrl_lvs10,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_off_lvs10,ocp_off_lvs10,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_ctrl_bst,ocp_ctrl_bst,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_off_bst,ocp_off_bst,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_ctrl_classd,ocp_ctrl_classd,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_off_classd,ocp_off_classd,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_reserved,reserved,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck0_int,en_buck0_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck1_int,en_buck1_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck2_int,en_buck2_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck3_int,en_buck3_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck4_int,en_buck4_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck5_int,en_buck5_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck6_int,en_buck6_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_reserved,reserved,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck0_int,dis_buck0_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck1_int,dis_buck1_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck2_int,dis_buck2_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck3_int,dis_buck3_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck4_int,dis_buck4_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck5_int,dis_buck5_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck6_int,dis_buck6_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_reserved,reserved,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck0_int,st_buck0_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck1_int,st_buck1_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck2_int,st_buck2_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck3_int,st_buck3_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck4_int,st_buck4_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck5_int,st_buck5_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck6_int,st_buck6_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_reserved,reserved,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo1_int,en_ldo1_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo2_int,en_ldo2_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo3_buck_int,en_ldo3_buck_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo4_int,en_ldo4_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo5_int,en_ldo5_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo6_int,en_ldo6_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo7_int,en_ldo7_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo8_int,en_ldo8_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo1_int,dis_ldo1_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo2_int,dis_ldo2_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo3_buck_int,dis_ldo3_buck_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo4_int,dis_ldo4_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo5_int,dis_ldo5_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo6_int,dis_ldo6_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo7_int,dis_ldo7_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo8_int,dis_ldo8_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo1_int,st_ldo1_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo2_int,st_ldo2_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo3_buck_int,st_ldo3_buck_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo4_int,st_ldo4_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo5_int,st_ldo5_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo6_int,st_ldo6_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo7_int,st_ldo7_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo8_int,st_ldo8_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo10_int,en_ldo10_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo12_int,en_ldo12_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo13_int,en_ldo13_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo14_int,en_ldo14_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo15_int,en_ldo15_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo16_int,en_ldo16_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo17_int,en_ldo17_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo18_int,en_ldo18_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo10_int,dis_ldo10_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo12_int,dis_ldo12_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo13_int,dis_ldo13_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo14_int,dis_ldo14_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo15_int,dis_ldo15_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo16_int,dis_ldo16_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo17_int,dis_ldo17_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo18_int,dis_ldo18_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo10_int,st_ldo10_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo12_int,st_ldo12_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo13_int,st_ldo13_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo14_int,st_ldo14_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo15_int,st_ldo15_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo16_int,st_ldo16_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo17_int,st_ldo17_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo18_int,st_ldo18_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo19_int,en_ldo19_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo20_int,en_ldo20_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo21_int,en_ldo21_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo22_int,en_ldo22_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo23_int,en_ldo23_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo24_int,en_ldo24_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo3_batt_int,en_ldo3_batt_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_reserved,reserved,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo19_int,dis_ldo19_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo20_int,dis_ldo20_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo21_int,dis_ldo21_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo22_int,dis_ldo22_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo23_int,dis_ldo23_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo24_int,dis_ldo24_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo3_batt_int,dis_ldo3_batt_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_reserved,reserved,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo19_int,st_ldo19_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo20_int,st_ldo20_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo21_int,st_ldo21_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo22_int,st_ldo22_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo23_int,st_ldo23_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo24_int,st_ldo24_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo3_batt_int,st_ldo3_batt_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_reserved,reserved,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs2_int,en_lvs2_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs3_int,en_lvs3_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs4_int,en_lvs4_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs5_int,en_lvs5_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs7_int,en_lvs7_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs6_int,en_lvs6_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs8_int,en_lvs8_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs9_int,en_lvs9_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs2_int,dis_lvs2_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs3_int,dis_lvs3_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs4_int,dis_lvs4_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs5_int,dis_lvs5_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs7_int,dis_lvs7_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs6_int,dis_lvs6_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs8_int,dis_lvs8_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs9_int,dis_lvs9_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs2_int,st_lvs2_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs3_int,st_lvs3_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs4_int,st_lvs4_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs5_int,st_lvs5_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs7_int,st_lvs7_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs6_int,st_lvs6_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs8_int,st_lvs8_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs9_int,st_lvs9_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_enable6_en_lvs10_int,en_lvs10_int,HI6551_ENABLE6_T,HI6551_BASE_ADDR, HI6551_ENABLE6_OFFSET)
HI_SET_GET(hi_hi6551_enable6_reserved,reserved,HI6551_ENABLE6_T,HI6551_BASE_ADDR, HI6551_ENABLE6_OFFSET)
HI_SET_GET(hi_hi6551_disable6_dis_lvs10_int,dis_lvs10_int,HI6551_DISABLE6_T,HI6551_BASE_ADDR, HI6551_DISABLE6_OFFSET)
HI_SET_GET(hi_hi6551_disable6_reserved,reserved,HI6551_DISABLE6_T,HI6551_BASE_ADDR, HI6551_DISABLE6_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status6_st_lvs10_int,st_lvs10_int,HI6551_ONOFF_STATUS6_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS6_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status6_reserved,reserved,HI6551_ONOFF_STATUS6_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS6_OFFSET)
HI_SET_GET(hi_hi6551_enable7_en_cp2_int,en_cp2_int,HI6551_ENABLE7_T,HI6551_BASE_ADDR, HI6551_ENABLE7_OFFSET)
HI_SET_GET(hi_hi6551_enable7_cp2_always_on_int,cp2_always_on_int,HI6551_ENABLE7_T,HI6551_BASE_ADDR, HI6551_ENABLE7_OFFSET)
HI_SET_GET(hi_hi6551_enable7_reserved,reserved,HI6551_ENABLE7_T,HI6551_BASE_ADDR, HI6551_ENABLE7_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_en_ldo9_int,en_ldo9_int,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_sim0_en_int,sim0_en_int,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_en_ldo11_int,en_ldo11_int,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_sim1_en_int,sim1_en_int,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_reserved,reserved,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_simcard0_resv,simcard0_resv,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_simcard0_bbrp,simcard0_bbrp,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_simcard0_simrp,simcard0_simrp,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_simcard0_200ns_en,simcard0_200ns_en,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_reserved,reserved,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_simcard1_resv,simcard1_resv,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_simcard1_bbrp,simcard1_bbrp,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_simcard1_simrp,simcard1_simrp,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_simcard1_200ns_en,simcard1_200ns_en,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_reserved,reserved,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim_deb_simcard_deb_sel,simcard_deb_sel,HI6551_SIM_DEB_T,HI6551_BASE_ADDR, HI6551_SIM_DEB_OFFSET)
HI_SET_GET(hi_hi6551_sim_deb_reserved,reserved,HI6551_SIM_DEB_T,HI6551_BASE_ADDR, HI6551_SIM_DEB_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_en_eco_buck3_int,en_eco_buck3_int,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_en_eco_buck4_int,en_eco_buck4_int,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_en_eco_buck5_int,en_eco_buck5_int,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_en_eco_buck6_int,en_eco_buck6_int,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_reserved,reserved,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo3_int,en_eco_ldo3_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo7_int,en_eco_ldo7_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo9_int,en_eco_ldo9_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo10_int,en_eco_ldo10_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo11_int,en_eco_ldo11_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo12_int,en_eco_ldo12_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo22_int,en_eco_ldo22_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo24_int,en_eco_ldo24_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_force_eco_buck3_int,force_eco_buck3_int,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_force_eco_buck4_int,force_eco_buck4_int,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_force_eco_buck5_int,force_eco_buck5_int,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_force_eco_buck6_int,force_eco_buck6_int,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_reserved,reserved,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo3_int,force_eco_ldo3_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo7_int,force_eco_ldo7_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo9_int,force_eco_ldo9_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo10_int,force_eco_ldo10_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo11_int,force_eco_ldo11_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo12_int,force_eco_ldo12_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo22_int,force_eco_ldo22_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo24_int,force_eco_ldo24_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_eco_pwrsel,eco_pwrsel,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_peri_en_ctrl_ldo12,peri_en_ctrl_ldo12,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_peri_en_ctrl_lvs9,peri_en_ctrl_lvs9,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_peri_en_ctrl_ldo8,peri_en_ctrl_ldo8,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_peri_en_ctrl_buck3,peri_en_ctrl_buck3,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_reserved,reserved,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg1_adj_buck01_osc_d,buck01_osc_d,HI6551_BUCK01_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg1_adj_buck0_pfm_vth_sel,buck0_pfm_vth_sel,HI6551_BUCK01_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg1_adj_buck0_sc_sel,buck0_sc_sel,HI6551_BUCK01_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg1_adj_reserved,reserved,HI6551_BUCK01_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck01_mod_sel,buck01_mod_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck0_bt_sel,buck0_bt_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck0_pd_sel,buck0_pd_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck0_burst_drv_ctr,buck0_burst_drv_ctr,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck01_ocp_mod_sel,buck01_ocp_mod_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck01_ocp_clamp_sel,buck01_ocp_clamp_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck01_ocp_shied_sel,buck01_ocp_shied_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg3_adj_buck0_vc_sel,buck0_vc_sel,HI6551_BUCK01_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg3_adj_reserved_1,reserved_1,HI6551_BUCK01_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg3_adj_buck01_auto_pfm_ctr,buck01_auto_pfm_ctr,HI6551_BUCK01_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg3_adj_reserved_0,reserved_0,HI6551_BUCK01_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg4_adj_buck0_isc_sel,buck0_isc_sel,HI6551_BUCK01_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg4_adj_reserved_1,reserved_1,HI6551_BUCK01_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg4_adj_buck0_ipk_sel,buck0_ipk_sel,HI6551_BUCK01_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg4_adj_reserved_0,reserved_0,HI6551_BUCK01_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_buck01_dt_sel,buck01_dt_sel,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_buck01_pg_dt_sel,buck01_pg_dt_sel,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_buck01_ng_dt_sel,buck01_ng_dt_sel,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_buck01_sft_sel,buck01_sft_sel,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_reserved,reserved,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg6_adj_buck01_pg_p_sel,buck01_pg_p_sel,HI6551_BUCK01_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg6_adj_reserved_1,reserved_1,HI6551_BUCK01_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg6_adj_buck01_pg_n_sel,buck01_pg_n_sel,HI6551_BUCK01_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg6_adj_reserved_0,reserved_0,HI6551_BUCK01_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg7_adj_buck01_ng_p_sel,buck01_ng_p_sel,HI6551_BUCK01_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg7_adj_reserved_1,reserved_1,HI6551_BUCK01_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg7_adj_buck01_ng_n_sel,buck01_ng_n_sel,HI6551_BUCK01_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg7_adj_reserved_0,reserved_0,HI6551_BUCK01_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg8_adj_buck0_ccm_sel,buck0_ccm_sel,HI6551_BUCK01_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg8_adj_buck1_ccm_sel,buck1_ccm_sel,HI6551_BUCK01_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg8_adj_buck0_ccc_sel,buck0_ccc_sel,HI6551_BUCK01_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg8_adj_buck0_cs_sel,buck0_cs_sel,HI6551_BUCK01_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_buck0_dmd_sel,buck0_dmd_sel,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_buck01_ton_off,buck01_ton_off,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_buck01_pfm_sleep,buck01_pfm_sleep,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_buck01_ton_on,buck01_ton_on,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_reserved,reserved,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg10_adj_buck01_new_dmd_sel,buck01_new_dmd_sel,HI6551_BUCK01_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg10_adj_reserved,reserved,HI6551_BUCK01_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck0_ocp_sel,buck0_ocp_sel,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck01_ocp_en,buck01_ocp_en,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck01_dmd_en,buck01_dmd_en,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck01_ea_sel,buck01_ea_sel,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck01_clk_sel,buck01_clk_sel,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg12_adj_buck0_sleep_depth_adj,buck0_sleep_depth_adj,HI6551_BUCK01_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg12_adj_reserved_1,reserved_1,HI6551_BUCK01_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg12_adj_buck0_ea_comp_cap,buck0_ea_comp_cap,HI6551_BUCK01_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg12_adj_reserved_0,reserved_0,HI6551_BUCK01_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_slope_gen,buck01_slope_gen,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_pdn_lx_det,buck01_pdn_lx_det,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_sleep_dmd,buck01_sleep_dmd,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_dmd_shield_n,buck01_dmd_shield_n,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_ocp_delay_sel,buck01_ocp_delay_sel,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_dmd_clamp,buck01_dmd_clamp,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg14_adj_buck01_slope_dc,buck01_slope_dc,HI6551_BUCK01_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg14_adj_buck01_unsleep,buck01_unsleep,HI6551_BUCK01_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg14_adj_buck01_dmd_float,buck01_dmd_float,HI6551_BUCK01_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg14_adj_reserved,reserved,HI6551_BUCK01_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg15_adj_buck0_comp_adj1,buck0_comp_adj1,HI6551_BUCK01_REG15_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG15_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg16_adj_buck01_reserved1,buck01_reserved1,HI6551_BUCK01_REG16_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG16_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg17_adj_buck01_reserved0,buck01_reserved0,HI6551_BUCK01_REG17_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG17_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg1_adj_buck2_adj_rlx,buck2_adj_rlx,HI6551_BUCK2_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg1_adj_buck2_adj_clx,buck2_adj_clx,HI6551_BUCK2_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg2_adj_buck2_new_dmd_sel,buck2_new_dmd_sel,HI6551_BUCK2_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg2_adj_reserved,reserved,HI6551_BUCK2_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_shield_i,buck2_shield_i,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_en_regop_clamp,buck2_en_regop_clamp,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_dmd_clamp,buck2_dmd_clamp,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_ocp_delay_sel,buck2_ocp_delay_sel,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_dmd_shield_n,buck2_dmd_shield_n,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_sleep_dmd,buck2_sleep_dmd,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_pdn_lx_det,buck2_pdn_lx_det,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg4_adj_buck2_ocp_sel,buck2_ocp_sel,HI6551_BUCK2_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg4_adj_reserved_1,reserved_1,HI6551_BUCK2_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg4_adj_buck2_dmd_sel,buck2_dmd_sel,HI6551_BUCK2_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg4_adj_reserved_0,reserved_0,HI6551_BUCK2_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_buck2_ng_dt_sel,buck2_ng_dt_sel,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_buck2_pg_dt_sel,buck2_pg_dt_sel,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_buck2_sft_sel,buck2_sft_sel,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_buck2_sleep,buck2_sleep,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_reserved,reserved,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg6_adj_buck2_pg_n_sel,buck2_pg_n_sel,HI6551_BUCK2_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg6_adj_reserved_1,reserved_1,HI6551_BUCK2_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg6_adj_buck2_pg_p_sel,buck2_pg_p_sel,HI6551_BUCK2_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg6_adj_reserved_0,reserved_0,HI6551_BUCK2_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg7_adj_buck2_ng_n_sel,buck2_ng_n_sel,HI6551_BUCK2_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg7_adj_reserved_1,reserved_1,HI6551_BUCK2_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg7_adj_buck2_ng_p_sel,buck2_ng_p_sel,HI6551_BUCK2_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg7_adj_reserved_0,reserved_0,HI6551_BUCK2_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_buck2_dbias,buck2_dbias,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_buck2_ocp_d,buck2_ocp_d,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_reserved_1,reserved_1,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_buck2_ton,buck2_ton,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_reserved_0,reserved_0,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_nmos_off,buck2_nmos_off,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_reg_c,buck2_reg_c,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_short_pdp,buck2_short_pdp,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_reg_ss_d,buck2_reg_ss_d,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_dt_sel,buck2_dt_sel,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_regop_c,buck2_regop_c,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_reserved,reserved,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg10_adj_buck2_reg_dr,buck2_reg_dr,HI6551_BUCK2_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg10_adj_buck2_en_reg,buck2_en_reg,HI6551_BUCK2_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg10_adj_buck2_ocp_clamp_sel,buck2_ocp_clamp_sel,HI6551_BUCK2_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg10_adj_reserved,reserved,HI6551_BUCK2_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg11_adj_buck2_reg_idr,buck2_reg_idr,HI6551_BUCK2_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg11_adj_reserved_1,reserved_1,HI6551_BUCK2_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg11_adj_buck2_reg_r,buck2_reg_r,HI6551_BUCK2_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg11_adj_reserved_0,reserved_0,HI6551_BUCK2_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg12_adj_buck2_reserve,buck2_reserve,HI6551_BUCK2_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg1_adj_buck3_adj_rlx,buck3_adj_rlx,HI6551_BUCK3_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg1_adj_buck3_adj_clx,buck3_adj_clx,HI6551_BUCK3_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg2_adj_buck3_new_dmd_sel,buck3_new_dmd_sel,HI6551_BUCK3_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg2_adj_buck3_ocp_sel,buck3_ocp_sel,HI6551_BUCK3_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg2_adj_reserved,reserved,HI6551_BUCK3_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_dmd_sel,buck3_dmd_sel,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_en_regop_clamp,buck3_en_regop_clamp,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_dmd_clamp,buck3_dmd_clamp,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_ocp_delay_sel,buck3_ocp_delay_sel,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_dmd_shield_n,buck3_dmd_shield_n,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_sleep_dmd,buck3_sleep_dmd,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_pdn_lx_det,buck3_pdn_lx_det,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_buck3_ng_dt_sel,buck3_ng_dt_sel,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_buck3_pg_dt_sel,buck3_pg_dt_sel,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_buck3_sft_sel,buck3_sft_sel,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_reserved_1,reserved_1,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_buck3_shield_i,buck3_shield_i,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_reserved_0,reserved_0,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg5_adj_buck3_pg_n_sel,buck3_pg_n_sel,HI6551_BUCK3_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg5_adj_reserved_1,reserved_1,HI6551_BUCK3_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg5_adj_buck3_pg_p_sel,buck3_pg_p_sel,HI6551_BUCK3_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg5_adj_reserved_0,reserved_0,HI6551_BUCK3_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg6_adj_buck3_ng_n_sel,buck3_ng_n_sel,HI6551_BUCK3_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg6_adj_reserved_1,reserved_1,HI6551_BUCK3_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg6_adj_buck3_ng_p_sel,buck3_ng_p_sel,HI6551_BUCK3_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg6_adj_reserved_0,reserved_0,HI6551_BUCK3_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_buck3_dbias,buck3_dbias,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_buck3_ocp_d,buck3_ocp_d,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_reserved_1,reserved_1,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_buck3_ton,buck3_ton,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_reserved_0,reserved_0,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_nmos_off,buck3_nmos_off,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_reg_c,buck3_reg_c,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_short_pdp,buck3_short_pdp,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_reg_ss_d,buck3_reg_ss_d,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_dt_sel,buck3_dt_sel,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_regop_c,buck3_regop_c,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_reserved,reserved,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg9_adj_buck3_reg_dr,buck3_reg_dr,HI6551_BUCK3_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg9_adj_buck3_en_reg,buck3_en_reg,HI6551_BUCK3_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg9_adj_buck3_ocp_clamp_sel,buck3_ocp_clamp_sel,HI6551_BUCK3_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg9_adj_reserved,reserved,HI6551_BUCK3_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg10_adj_buck3_reg_idr,buck3_reg_idr,HI6551_BUCK3_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg10_adj_reserved_1,reserved_1,HI6551_BUCK3_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg10_adj_buck3_reg_r,buck3_reg_r,HI6551_BUCK3_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg10_adj_reserved_0,reserved_0,HI6551_BUCK3_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg11_adj_buck3_mos_sel,buck3_mos_sel,HI6551_BUCK3_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg11_adj_reserved,reserved,HI6551_BUCK3_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg12_adj_buck3_reserve,buck3_reserve,HI6551_BUCK3_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg1_adj_buck4_adj_rlx,buck4_adj_rlx,HI6551_BUCK4_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg1_adj_buck4_adj_clx,buck4_adj_clx,HI6551_BUCK4_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg2_adj_buck4_new_dmd_sel,buck4_new_dmd_sel,HI6551_BUCK4_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg2_adj_buck4_ocp_sel,buck4_ocp_sel,HI6551_BUCK4_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg2_adj_reserved,reserved,HI6551_BUCK4_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_dmd_sel,buck4_dmd_sel,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_en_regop_clamp,buck4_en_regop_clamp,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_dmd_clamp,buck4_dmd_clamp,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_ocp_delay_sel,buck4_ocp_delay_sel,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_dmd_shield_n,buck4_dmd_shield_n,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_sleep_dmd,buck4_sleep_dmd,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_pdn_lx_det,buck4_pdn_lx_det,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg4_adj_buck4_ng_dt_sel,buck4_ng_dt_sel,HI6551_BUCK4_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg4_adj_buck4_pg_dt_sel,buck4_pg_dt_sel,HI6551_BUCK4_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg4_adj_buck4_sft_sel,buck4_sft_sel,HI6551_BUCK4_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg4_adj_reserved,reserved,HI6551_BUCK4_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg5_adj_buck4_pg_n_sel,buck4_pg_n_sel,HI6551_BUCK4_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg5_adj_reserved_1,reserved_1,HI6551_BUCK4_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg5_adj_buck4_pg_p_sel,buck4_pg_p_sel,HI6551_BUCK4_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg5_adj_reserved_0,reserved_0,HI6551_BUCK4_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg6_adj_buck4_ng_n_sel,buck4_ng_n_sel,HI6551_BUCK4_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg6_adj_reserved_1,reserved_1,HI6551_BUCK4_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg6_adj_buck4_ng_p_sel,buck4_ng_p_sel,HI6551_BUCK4_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg6_adj_reserved_0,reserved_0,HI6551_BUCK4_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_buck4_dbias,buck4_dbias,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_buck4_ocp_d,buck4_ocp_d,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_reserved_1,reserved_1,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_buck4_ton,buck4_ton,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_reserved_0,reserved_0,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_nmos_off,buck4_nmos_off,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_reg_c,buck4_reg_c,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_short_pdp,buck4_short_pdp,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_reg_ss_d,buck4_reg_ss_d,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_dt_sel,buck4_dt_sel,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_regop_c,buck4_regop_c,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_reserved,reserved,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg9_adj_buck4_reg_dr,buck4_reg_dr,HI6551_BUCK4_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg9_adj_buck4_en_reg,buck4_en_reg,HI6551_BUCK4_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg9_adj_buck4_ocp_clamp_sel,buck4_ocp_clamp_sel,HI6551_BUCK4_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg9_adj_reserved,reserved,HI6551_BUCK4_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg10_adj_buck4_reg_idr,buck4_reg_idr,HI6551_BUCK4_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg10_adj_reserved_1,reserved_1,HI6551_BUCK4_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg10_adj_buck4_reg_r,buck4_reg_r,HI6551_BUCK4_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg10_adj_reserved_0,reserved_0,HI6551_BUCK4_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg12_adj_buck4_reserve,buck4_reserve,HI6551_BUCK4_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg1_adj_buck5_adj_rlx,buck5_adj_rlx,HI6551_BUCK5_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg1_adj_buck5_adj_clx,buck5_adj_clx,HI6551_BUCK5_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg2_adj_buck5_new_dmd_sel,buck5_new_dmd_sel,HI6551_BUCK5_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg2_adj_buck5_ocp_sel,buck5_ocp_sel,HI6551_BUCK5_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg2_adj_reserved,reserved,HI6551_BUCK5_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_dmd_sel,buck5_dmd_sel,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_en_regop_clamp,buck5_en_regop_clamp,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_dmd_clamp,buck5_dmd_clamp,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_ocp_delay_sel,buck5_ocp_delay_sel,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_dmd_shield_n,buck5_dmd_shield_n,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_sleep_dmd,buck5_sleep_dmd,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_pdn_lx_det,buck5_pdn_lx_det,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg4_adj_buck5_ng_dt_sel,buck5_ng_dt_sel,HI6551_BUCK5_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg4_adj_buck5_pg_dt_sel,buck5_pg_dt_sel,HI6551_BUCK5_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg4_adj_buck5_sft_sel,buck5_sft_sel,HI6551_BUCK5_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg4_adj_reserved,reserved,HI6551_BUCK5_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg5_adj_buck5_pg_n_sel,buck5_pg_n_sel,HI6551_BUCK5_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg5_adj_reserved_1,reserved_1,HI6551_BUCK5_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg5_adj_buck5_pg_p_sel,buck5_pg_p_sel,HI6551_BUCK5_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg5_adj_reserved_0,reserved_0,HI6551_BUCK5_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg6_adj_buck5_ng_n_sel,buck5_ng_n_sel,HI6551_BUCK5_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg6_adj_reserved_1,reserved_1,HI6551_BUCK5_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg6_adj_buck5_ng_p_sel,buck5_ng_p_sel,HI6551_BUCK5_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg6_adj_reserved_0,reserved_0,HI6551_BUCK5_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_buck5_dbias,buck5_dbias,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_buck5_ocp_d,buck5_ocp_d,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_reserved_1,reserved_1,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_buck5_ton,buck5_ton,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_reserved_0,reserved_0,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_nmos_off,buck5_nmos_off,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_reg_c,buck5_reg_c,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_short_pdp,buck5_short_pdp,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_reg_ss_d,buck5_reg_ss_d,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_dt_sel,buck5_dt_sel,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_regop_c,buck5_regop_c,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_reserved,reserved,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg9_adj_buck5_reg_dr,buck5_reg_dr,HI6551_BUCK5_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg9_adj_buck5_en_reg,buck5_en_reg,HI6551_BUCK5_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg9_adj_buck5_ocp_clamp_sel,buck5_ocp_clamp_sel,HI6551_BUCK5_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg9_adj_reserved,reserved,HI6551_BUCK5_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg10_adj_buck5_reg_idr,buck5_reg_idr,HI6551_BUCK5_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg10_adj_reserved_1,reserved_1,HI6551_BUCK5_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg10_adj_buck5_reg_r,buck5_reg_r,HI6551_BUCK5_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg10_adj_reserved_0,reserved_0,HI6551_BUCK5_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg12_adj_buck5_reserve0,buck5_reserve0,HI6551_BUCK5_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg13_adj_buck5_reserve1,buck5_reserve1,HI6551_BUCK5_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg14_adj_buck5_reserve2,buck5_reserve2,HI6551_BUCK5_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg1_adj_buck6_adj_rlx,buck6_adj_rlx,HI6551_BUCK6_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg1_adj_buck6_adj_clx,buck6_adj_clx,HI6551_BUCK6_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg2_adj_buck6_new_dmd_sel,buck6_new_dmd_sel,HI6551_BUCK6_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg2_adj_buck6_ocp_sel,buck6_ocp_sel,HI6551_BUCK6_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg2_adj_reserved,reserved,HI6551_BUCK6_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_dmd_sel,buck6_dmd_sel,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_en_regop_clamp,buck6_en_regop_clamp,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_dmd_clamp,buck6_dmd_clamp,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_ocp_delay_sel,buck6_ocp_delay_sel,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_dmd_shield_n,buck6_dmd_shield_n,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_sleep_dmd,buck6_sleep_dmd,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_pdn_lx_det,buck6_pdn_lx_det,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg4_adj_buck6_ng_dt_sel,buck6_ng_dt_sel,HI6551_BUCK6_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg4_adj_buck6_pg_dt_sel,buck6_pg_dt_sel,HI6551_BUCK6_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg4_adj_buck6_sft_sel,buck6_sft_sel,HI6551_BUCK6_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg4_adj_reserved,reserved,HI6551_BUCK6_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg5_adj_buck6_pg_n_sel,buck6_pg_n_sel,HI6551_BUCK6_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg5_adj_reserved_1,reserved_1,HI6551_BUCK6_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg5_adj_buck6_pg_p_sel,buck6_pg_p_sel,HI6551_BUCK6_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg5_adj_reserved_0,reserved_0,HI6551_BUCK6_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg6_adj_buck6_ng_n_sel,buck6_ng_n_sel,HI6551_BUCK6_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg6_adj_reserved_1,reserved_1,HI6551_BUCK6_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg6_adj_buck6_ng_p_sel,buck6_ng_p_sel,HI6551_BUCK6_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg6_adj_reserved_0,reserved_0,HI6551_BUCK6_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_buck6_dbias,buck6_dbias,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_buck6_ocp_d,buck6_ocp_d,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_reserved_1,reserved_1,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_buck6_ton,buck6_ton,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_reserved_0,reserved_0,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_nmos_off,buck6_nmos_off,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_reg_c,buck6_reg_c,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_short_pdp,buck6_short_pdp,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_reg_ss_d,buck6_reg_ss_d,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_dt_sel,buck6_dt_sel,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_regop_c,buck6_regop_c,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_reserved,reserved,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg9_adj_buck6_reg_dr,buck6_reg_dr,HI6551_BUCK6_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg9_adj_buck6_en_reg,buck6_en_reg,HI6551_BUCK6_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg9_adj_buck6_ocp_clamp_sel,buck6_ocp_clamp_sel,HI6551_BUCK6_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg9_adj_reserved,reserved,HI6551_BUCK6_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg10_adj_buck6_reg_idr,buck6_reg_idr,HI6551_BUCK6_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg10_adj_reserved_1,reserved_1,HI6551_BUCK6_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg10_adj_buck6_reg_r,buck6_reg_r,HI6551_BUCK6_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg10_adj_reserved_0,reserved_0,HI6551_BUCK6_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg11_adj_buck6_mos_sel,buck6_mos_sel,HI6551_BUCK6_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg11_adj_reserved,reserved,HI6551_BUCK6_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg12_adj_buck6_reserve,buck6_reserve,HI6551_BUCK6_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_chg_pump2_adj_cp2_vout_sel,cp2_vout_sel,HI6551_CHG_PUMP2_ADJ_T,HI6551_BASE_ADDR, HI6551_CHG_PUMP2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_chg_pump2_adj_reserved,reserved,HI6551_CHG_PUMP2_ADJ_T,HI6551_BASE_ADDR, HI6551_CHG_PUMP2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck01_adj_buck0_vck,buck0_vck,HI6551_VSET_BUCK01_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK01_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck01_adj_reserved,reserved,HI6551_VSET_BUCK01_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK01_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck2_adj_buck2_dv,buck2_dv,HI6551_VSET_BUCK2_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck3_adj_buck3_dv,buck3_dv,HI6551_VSET_BUCK3_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck3_adj_reserved,reserved,HI6551_VSET_BUCK3_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck4_adj_buck4_dv,buck4_dv,HI6551_VSET_BUCK4_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck4_adj_reserved,reserved,HI6551_VSET_BUCK4_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck5_adj_buck5_dv,buck5_dv,HI6551_VSET_BUCK5_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck6_adj_buck6_dv,buck6_dv,HI6551_VSET_BUCK6_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck6_adj_reserved,reserved,HI6551_VSET_BUCK6_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo1_reg_adj_vset_ldo1,vset_ldo1,HI6551_LDO1_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO1_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo1_reg_adj_reserved,reserved,HI6551_LDO1_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO1_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo2_reg_adj_vset_ldo2,vset_ldo2,HI6551_LDO2_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO2_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo2_reg_adj_reserved,reserved,HI6551_LDO2_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO2_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo3_reg_adj_vset_ldo3,vset_ldo3,HI6551_LDO3_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO3_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo3_reg_adj_reserved_1,reserved_1,HI6551_LDO3_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO3_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo3_reg_adj_vrset_ldo3,vrset_ldo3,HI6551_LDO3_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO3_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo3_reg_adj_reserved_0,reserved_0,HI6551_LDO3_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO3_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo4_reg_adj_vset_ldo4,vset_ldo4,HI6551_LDO4_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO4_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo4_reg_adj_reserved,reserved,HI6551_LDO4_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO4_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo5_reg_adj_vset_ldo5,vset_ldo5,HI6551_LDO5_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO5_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo5_reg_adj_reserved_1,reserved_1,HI6551_LDO5_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO5_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo5_reg_adj_vrset_ldo5,vrset_ldo5,HI6551_LDO5_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO5_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo5_reg_adj_reserved_0,reserved_0,HI6551_LDO5_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO5_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo6_reg_adj_vset_ldo6,vset_ldo6,HI6551_LDO6_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO6_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo6_reg_adj_reserved,reserved,HI6551_LDO6_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO6_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo7_reg_adj_vset_ldo7,vset_ldo7,HI6551_LDO7_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO7_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo7_reg_adj_reserved,reserved,HI6551_LDO7_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO7_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo8_reg_adj_vset_ldo8,vset_ldo8,HI6551_LDO8_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO8_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo8_reg_adj_reserved_1,reserved_1,HI6551_LDO8_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO8_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo8_reg_adj_vrset_ldo8,vrset_ldo8,HI6551_LDO8_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO8_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo8_reg_adj_reserved_0,reserved_0,HI6551_LDO8_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO8_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo9_reg_adj_vset_ldo9,vset_ldo9,HI6551_LDO9_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO9_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo9_reg_adj_reserved_1,reserved_1,HI6551_LDO9_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO9_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo9_reg_adj_vrset_ldo9,vrset_ldo9,HI6551_LDO9_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO9_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo9_reg_adj_reserved_0,reserved_0,HI6551_LDO9_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO9_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo10_reg_adj_vset_ldo10,vset_ldo10,HI6551_LDO10_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO10_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo10_reg_adj_reserved_1,reserved_1,HI6551_LDO10_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO10_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo10_reg_adj_vrset_ldo10,vrset_ldo10,HI6551_LDO10_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO10_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo10_reg_adj_reserved_0,reserved_0,HI6551_LDO10_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO10_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo11_reg_adj_vset_ldo11,vset_ldo11,HI6551_LDO11_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO11_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo11_reg_adj_reserved_1,reserved_1,HI6551_LDO11_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO11_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo11_reg_adj_vrset_ldo11,vrset_ldo11,HI6551_LDO11_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO11_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo11_reg_adj_reserved_0,reserved_0,HI6551_LDO11_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO11_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo12_reg_adj_vset_ldo12,vset_ldo12,HI6551_LDO12_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO12_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo12_reg_adj_reserved_1,reserved_1,HI6551_LDO12_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO12_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo12_reg_adj_vrset_ldo12,vrset_ldo12,HI6551_LDO12_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO12_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo12_reg_adj_reserved_0,reserved_0,HI6551_LDO12_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO12_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo13_reg_adj_vset_ldo13,vset_ldo13,HI6551_LDO13_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO13_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo13_reg_adj_reserved,reserved,HI6551_LDO13_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO13_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo14_reg_adj_vset_ldo14,vset_ldo14,HI6551_LDO14_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO14_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo14_reg_adj_reserved_1,reserved_1,HI6551_LDO14_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO14_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo14_reg_adj_vrset_ldo14,vrset_ldo14,HI6551_LDO14_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO14_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo14_reg_adj_reserved_0,reserved_0,HI6551_LDO14_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO14_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo15_reg_adj_vset_ldo15,vset_ldo15,HI6551_LDO15_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO15_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo15_reg_adj_reserved_1,reserved_1,HI6551_LDO15_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO15_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo15_reg_adj_vrset_ldo15,vrset_ldo15,HI6551_LDO15_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO15_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo15_reg_adj_reserved_0,reserved_0,HI6551_LDO15_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO15_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo16_reg_adj_vset_ldo16,vset_ldo16,HI6551_LDO16_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO16_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo16_reg_adj_reserved_1,reserved_1,HI6551_LDO16_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO16_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo16_reg_adj_vrset_ldo16,vrset_ldo16,HI6551_LDO16_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO16_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo16_reg_adj_reserved_0,reserved_0,HI6551_LDO16_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO16_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo17_reg_adj_vset_ldo17,vset_ldo17,HI6551_LDO17_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO17_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo17_reg_adj_reserved_1,reserved_1,HI6551_LDO17_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO17_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo17_reg_adj_vrset_ldo17,vrset_ldo17,HI6551_LDO17_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO17_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo17_reg_adj_reserved_0,reserved_0,HI6551_LDO17_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO17_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo18_reg_adj_vset_ldo18,vset_ldo18,HI6551_LDO18_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO18_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo18_reg_adj_reserved_1,reserved_1,HI6551_LDO18_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO18_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo18_reg_adj_vrset_ldo18,vrset_ldo18,HI6551_LDO18_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO18_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo18_reg_adj_reserved_0,reserved_0,HI6551_LDO18_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO18_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo19_reg_adj_vset_ldo19,vset_ldo19,HI6551_LDO19_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO19_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo19_reg_adj_reserved_1,reserved_1,HI6551_LDO19_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO19_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo19_reg_adj_vrset_ldo19,vrset_ldo19,HI6551_LDO19_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO19_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo19_reg_adj_reserved_0,reserved_0,HI6551_LDO19_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO19_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo20_reg_adj_vset_ldo20,vset_ldo20,HI6551_LDO20_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO20_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo20_reg_adj_reserved_1,reserved_1,HI6551_LDO20_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO20_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo20_reg_adj_vrset_ldo20,vrset_ldo20,HI6551_LDO20_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO20_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo20_reg_adj_reserved_0,reserved_0,HI6551_LDO20_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO20_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo21_reg_adj_vset_ldo21,vset_ldo21,HI6551_LDO21_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO21_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo21_reg_adj_reserved_1,reserved_1,HI6551_LDO21_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO21_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo21_reg_adj_vrset_ldo21,vrset_ldo21,HI6551_LDO21_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO21_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo21_reg_adj_reserved_0,reserved_0,HI6551_LDO21_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO21_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo22_reg_adj_vset_ldo22,vset_ldo22,HI6551_LDO22_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO22_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo22_reg_adj_en_sink_ldo22,en_sink_ldo22,HI6551_LDO22_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO22_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo22_reg_adj_rset_sink_ldo22,rset_sink_ldo22,HI6551_LDO22_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO22_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo22_reg_adj_reserved,reserved,HI6551_LDO22_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO22_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo23_reg_adj_vset_ldo23,vset_ldo23,HI6551_LDO23_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO23_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo23_reg_adj_reserved_1,reserved_1,HI6551_LDO23_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO23_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo23_reg_adj_vrset_ldo23,vrset_ldo23,HI6551_LDO23_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO23_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo23_reg_adj_reserved_0,reserved_0,HI6551_LDO23_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO23_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo24_reg_adj_vset_ldo24,vset_ldo24,HI6551_LDO24_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO24_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo24_reg_adj_reserved,reserved,HI6551_LDO24_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO24_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_pmua_reg_adj_vset_pmua,vset_pmua,HI6551_PMUA_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_PMUA_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_pmua_reg_adj_eco_pmua,eco_pmua,HI6551_PMUA_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_PMUA_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_pmua_reg_adj_reserved,reserved,HI6551_PMUA_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_PMUA_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj1_sstset_lvs5,sstset_lvs5,HI6551_LVS_ADJ1_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj1_sstset_lvs4,sstset_lvs4,HI6551_LVS_ADJ1_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj1_sstset_lvs3,sstset_lvs3,HI6551_LVS_ADJ1_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj1_sstset_lvs2,sstset_lvs2,HI6551_LVS_ADJ1_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj2_sstset_lvs9,sstset_lvs9,HI6551_LVS_ADJ2_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj2_sstset_lvs8,sstset_lvs8,HI6551_LVS_ADJ2_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj2_sstset_lvs7,sstset_lvs7,HI6551_LVS_ADJ2_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj2_sstset_lvs6,sstset_lvs6,HI6551_LVS_ADJ2_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj3_sstset_lvs10,sstset_lvs10,HI6551_LVS_ADJ3_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj3_reserved,reserved,HI6551_LVS_ADJ3_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj0_en_bst_int,en_bst_int,HI6551_BOOST_ADJ0_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj0_bst_pm_th,bst_pm_th,HI6551_BOOST_ADJ0_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj0_bst_pm_cut,bst_pm_cut,HI6551_BOOST_ADJ0_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj0_bst_reserved0,bst_reserved0,HI6551_BOOST_ADJ0_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_sel_scp,bst_sel_scp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_sel_pd,bst_sel_pd,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_en_uvp,bst_en_uvp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_en_scp,bst_en_scp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_en_ovp,bst_en_ovp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_en_ocp,bst_en_ocp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_reserved1,bst_reserved1,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_drv_mode,bst_drv_mode,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_loop_mode,bst_loop_mode,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_pfm,bst_en_pfm,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_nring,bst_en_nring,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_clp_os,bst_en_clp_os,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_slop,bst_en_slop,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_dmd,bst_en_dmd,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_reserved2,bst_reserved2,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj3_bst_clp,bst_clp,HI6551_BOOST_ADJ3_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj3_bst_itail,bst_itail,HI6551_BOOST_ADJ3_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj3_bst_gm,bst_gm,HI6551_BOOST_ADJ3_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj3_bst_reserved3,bst_reserved3,HI6551_BOOST_ADJ3_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj4_bst_ccom2,bst_ccom2,HI6551_BOOST_ADJ4_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ4_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj4_bst_ccom1,bst_ccom1,HI6551_BOOST_ADJ4_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ4_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj4_bst_rcom,bst_rcom,HI6551_BOOST_ADJ4_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ4_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj4_bst_reserved4,bst_reserved4,HI6551_BOOST_ADJ4_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ4_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj5_bst_slop,bst_slop,HI6551_BOOST_ADJ5_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ5_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj5_bst_ri,bst_ri,HI6551_BOOST_ADJ5_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ5_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj5_bst_reserved5,bst_reserved5,HI6551_BOOST_ADJ5_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ5_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj6_bst_nsn,bst_nsn,HI6551_BOOST_ADJ6_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ6_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj6_bst_nsp,bst_nsp,HI6551_BOOST_ADJ6_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ6_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj6_bst_psn,bst_psn,HI6551_BOOST_ADJ6_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ6_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj6_bst_psp,bst_psp,HI6551_BOOST_ADJ6_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ6_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj7_bst_dt_nm,bst_dt_nm,HI6551_BOOST_ADJ7_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ7_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj7_bst_dt_pm,bst_dt_pm,HI6551_BOOST_ADJ7_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ7_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj7_bst_lxde,bst_lxde,HI6551_BOOST_ADJ7_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ7_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj7_bst_reserved6,bst_reserved6,HI6551_BOOST_ADJ7_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ7_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj8_bst_ckmin,bst_ckmin,HI6551_BOOST_ADJ8_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ8_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj8_bst_osc,bst_osc,HI6551_BOOST_ADJ8_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ8_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj8_bst_reserved7,bst_reserved7,HI6551_BOOST_ADJ8_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ8_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj9_vo,vo,HI6551_BOOST_ADJ9_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ9_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj9_sel_ocp,sel_ocp,HI6551_BOOST_ADJ9_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ9_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj9_bst_start,bst_start,HI6551_BOOST_ADJ9_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ9_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj10_bst_dmd_ofs,bst_dmd_ofs,HI6551_BOOST_ADJ10_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ10_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj10_bst_reserved10,bst_reserved10,HI6551_BOOST_ADJ10_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ10_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj11_bst_v2clp,bst_v2clp,HI6551_BOOST_ADJ11_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ11_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj11_bst_v2div,bst_v2div,HI6551_BOOST_ADJ11_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ11_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj11_bst_v2ramp,bst_v2ramp,HI6551_BOOST_ADJ11_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ11_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj11_bst_reserved11,bst_reserved11,HI6551_BOOST_ADJ11_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ11_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_classd_mute_sel,classd_mute_sel,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_classd_mute,classd_mute,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_classd_gain,classd_gain,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_en_classd_int,en_classd_int,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_classd_i_ocp,classd_i_ocp,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_reserved,reserved,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj1_classd_n_sel,classd_n_sel,HI6551_CLASSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj1_classd_p_sel,classd_p_sel,HI6551_CLASSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj1_classd_i_ramp,classd_i_ramp,HI6551_CLASSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj1_classd_i_pump,classd_i_pump,HI6551_CLASSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_ocp_bps,classd_ocp_bps,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_fx_bps,classd_fx_bps,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_dt_sel,classd_dt_sel,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_pls_byp,classd_pls_byp,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_reserved,classd_reserved,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj1_bg_test,bg_test,HI6551_BANDGAP_THSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj1_bg_sleep,bg_sleep,HI6551_BANDGAP_THSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj1_reserved,reserved,HI6551_BANDGAP_THSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj2_en_tmp_int,en_tmp_int,HI6551_BANDGAP_THSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj2_reserved_1,reserved_1,HI6551_BANDGAP_THSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj2_thsd_set_tmp,thsd_set_tmp,HI6551_BANDGAP_THSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj2_reserved_0,reserved_0,HI6551_BANDGAP_THSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_en_dr3_int,en_dr3_int,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_dr3_mode,dr3_mode,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_en_dr4_int,en_dr4_int,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_dr4_mode,dr4_mode,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_en_dr5_int,en_dr5_int,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_dr5_mode,dr5_mode,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_reserved,reserved,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_en_dr1_int,en_dr1_int,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_dr1_mode,dr1_mode,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_reserved_1,reserved_1,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_en_dr2_int,en_dr2_int,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_dr2_mode,dr2_mode,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_reserved_0,reserved_0,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_flash_period_flash_period,flash_period,HI6551_FLASH_PERIOD_T,HI6551_BASE_ADDR, HI6551_FLASH_PERIOD_OFFSET)
HI_SET_GET(hi_hi6551_flash_on_flash_on,flash_on,HI6551_FLASH_ON_T,HI6551_BASE_ADDR, HI6551_FLASH_ON_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr1_mode_sel,dr1_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr2_mode_sel,dr2_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr3_mode_sel,dr3_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr4_mode_sel,dr4_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr5_mode_sel,dr5_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_reserved,reserved,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_dr1_en,dr1_en,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_dr1_flash_en,dr1_flash_en,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_reserved_1,reserved_1,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_dr2_en,dr2_en,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_dr2_flash_en,dr2_flash_en,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_reserved_0,reserved_0,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf0_dr1_t_off,dr1_t_off,HI6551_DR1_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf0_reserved_1,reserved_1,HI6551_DR1_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf0_dr1_t_on,dr1_t_on,HI6551_DR1_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf0_reserved_0,reserved_0,HI6551_DR1_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf1_dr1_t_rise,dr1_t_rise,HI6551_DR1_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf1_reserved_1,reserved_1,HI6551_DR1_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf1_dr1_t_fall,dr1_t_fall,HI6551_DR1_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf1_reserved_0,reserved_0,HI6551_DR1_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr1_iset_iset_dr1,iset_dr1,HI6551_DR1_ISET_T,HI6551_BASE_ADDR, HI6551_DR1_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr1_iset_reserved,reserved,HI6551_DR1_ISET_T,HI6551_BASE_ADDR, HI6551_DR1_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf0_dr2_t_off,dr2_t_off,HI6551_DR2_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf0_reserved_1,reserved_1,HI6551_DR2_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf0_dr2_t_on,dr2_t_on,HI6551_DR2_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf0_reserved_0,reserved_0,HI6551_DR2_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf1_dr2_t_rise,dr2_t_rise,HI6551_DR2_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf1_reserved_1,reserved_1,HI6551_DR2_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf1_dr2_t_fall,dr2_t_fall,HI6551_DR2_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf1_reserved_0,reserved_0,HI6551_DR2_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr2_iset_iset_dr2,iset_dr2,HI6551_DR2_ISET_T,HI6551_BASE_ADDR, HI6551_DR2_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr2_iset_reserved,reserved,HI6551_DR2_ISET_T,HI6551_BASE_ADDR, HI6551_DR2_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_dr3_en,dr3_en,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_dr4_en,dr4_en,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_dr5_en,dr5_en,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_dr_eco_en,dr_eco_en,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_reserved,reserved,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_out_ctrl_dr3_out_ctrl,dr3_out_ctrl,HI6551_DR_OUT_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_OUT_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_out_ctrl_dr4_out_ctrl,dr4_out_ctrl,HI6551_DR_OUT_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_OUT_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_out_ctrl_dr5_out_ctrl,dr5_out_ctrl,HI6551_DR_OUT_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_OUT_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_out_ctrl_reserved,reserved,HI6551_DR_OUT_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_OUT_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr3_iset_iset_dr3,iset_dr3,HI6551_DR3_ISET_T,HI6551_BASE_ADDR, HI6551_DR3_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr3_iset_reserved,reserved,HI6551_DR3_ISET_T,HI6551_BASE_ADDR, HI6551_DR3_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr3_start_del_dr3_start_delay,dr3_start_delay,HI6551_DR3_START_DEL_T,HI6551_BASE_ADDR, HI6551_DR3_START_DEL_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf0_dr3_t_off,dr3_t_off,HI6551_DR3_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf0_dr3_t_on,dr3_t_on,HI6551_DR3_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf1_dr3_t_rise,dr3_t_rise,HI6551_DR3_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf1_reserved_1,reserved_1,HI6551_DR3_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf1_dr3_t_fall,dr3_t_fall,HI6551_DR3_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf1_reserved_0,reserved_0,HI6551_DR3_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr4_iset_iset_dr4,iset_dr4,HI6551_DR4_ISET_T,HI6551_BASE_ADDR, HI6551_DR4_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr4_iset_reserved,reserved,HI6551_DR4_ISET_T,HI6551_BASE_ADDR, HI6551_DR4_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr4_start_del_dr4_start_delay,dr4_start_delay,HI6551_DR4_START_DEL_T,HI6551_BASE_ADDR, HI6551_DR4_START_DEL_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf0_dr4_t_off,dr4_t_off,HI6551_DR4_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf0_dr4_t_on,dr4_t_on,HI6551_DR4_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf1_dr4_t_rise,dr4_t_rise,HI6551_DR4_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf1_reserved_1,reserved_1,HI6551_DR4_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf1_dr4_t_fall,dr4_t_fall,HI6551_DR4_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf1_reserved_0,reserved_0,HI6551_DR4_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr5_iset_iset_dr5,iset_dr5,HI6551_DR5_ISET_T,HI6551_BASE_ADDR, HI6551_DR5_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr5_iset_reserved,reserved,HI6551_DR5_ISET_T,HI6551_BASE_ADDR, HI6551_DR5_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr5_start_del_dr5_start_delay,dr5_start_delay,HI6551_DR5_START_DEL_T,HI6551_BASE_ADDR, HI6551_DR5_START_DEL_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf0_dr5_t_off,dr5_t_off,HI6551_DR5_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf0_dr5_t_on,dr5_t_on,HI6551_DR5_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf1_dr5_t_rise,dr5_t_rise,HI6551_DR5_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf1_reserved_1,reserved_1,HI6551_DR5_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf1_dr5_t_fall,dr5_t_fall,HI6551_DR5_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf1_reserved_0,reserved_0,HI6551_DR5_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_otp_pwe_int,otp_pwe_int,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_otp_pwe_pulse,otp_pwe_pulse,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_otp_write_mask,otp_write_mask,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_otp_por_int,otp_por_int,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_reserved,reserved,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl2_otp_pa,otp_pa,HI6551_OTP_CTRL2_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl2_otp_ptm,otp_ptm,HI6551_OTP_CTRL2_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl2_otp_pprog,otp_pprog,HI6551_OTP_CTRL2_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl2_reserved,reserved,HI6551_OTP_CTRL2_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdin_otp_pdin,otp_pdin,HI6551_OTP_PDIN_T,HI6551_BASE_ADDR, HI6551_OTP_PDIN_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdob0_otp_pdob0,otp_pdob0,HI6551_OTP_PDOB0_T,HI6551_BASE_ADDR, HI6551_OTP_PDOB0_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdob1_otp_pdob1,otp_pdob1,HI6551_OTP_PDOB1_T,HI6551_BASE_ADDR, HI6551_OTP_PDOB1_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdob2_otp_pdob2,otp_pdob2,HI6551_OTP_PDOB2_T,HI6551_BASE_ADDR, HI6551_OTP_PDOB2_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdob3_otp_pdob3,otp_pdob3,HI6551_OTP_PDOB3_T,HI6551_BASE_ADDR, HI6551_OTP_PDOB3_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_a0_rtccr_a0,rtccr_a0,HI6551_RTCCR_A0_T,HI6551_BASE_ADDR, HI6551_RTCCR_A0_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_a1_rtccr_a1,rtccr_a1,HI6551_RTCCR_A1_T,HI6551_BASE_ADDR, HI6551_RTCCR_A1_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_a2_rtccr_a2,rtccr_a2,HI6551_RTCCR_A2_T,HI6551_BASE_ADDR, HI6551_RTCCR_A2_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_a3_rtccr_a3,rtccr_a3,HI6551_RTCCR_A3_T,HI6551_BASE_ADDR, HI6551_RTCCR_A3_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_a0_rtclr_a0,rtclr_a0,HI6551_RTCLR_A0_T,HI6551_BASE_ADDR, HI6551_RTCLR_A0_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_a1_rtclr_a1,rtclr_a1,HI6551_RTCLR_A1_T,HI6551_BASE_ADDR, HI6551_RTCLR_A1_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_a2_rtclr_a2,rtclr_a2,HI6551_RTCLR_A2_T,HI6551_BASE_ADDR, HI6551_RTCLR_A2_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_a3_rtclr_a3,rtclr_a3,HI6551_RTCLR_A3_T,HI6551_BASE_ADDR, HI6551_RTCLR_A3_OFFSET)
HI_SET_GET(hi_hi6551_rtcctrl_a_rtccr_a,rtccr_a,HI6551_RTCCTRL_A_T,HI6551_BASE_ADDR, HI6551_RTCCTRL_A_OFFSET)
HI_SET_GET(hi_hi6551_rtcctrl_a_reserved,reserved,HI6551_RTCCTRL_A_T,HI6551_BASE_ADDR, HI6551_RTCCTRL_A_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_a0_rtcmr_a_a0,rtcmr_a_a0,HI6551_RTCMR_A_A0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_A0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_a1_rtcmr_a_a1,rtcmr_a_a1,HI6551_RTCMR_A_A1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_A1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_a2_rtcmr_a_a2,rtcmr_a_a2,HI6551_RTCMR_A_A2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_A2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_a3_rtcmr_a_a3,rtcmr_a_a3,HI6551_RTCMR_A_A3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_A3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_b0_rtcmr_a_b0,rtcmr_a_b0,HI6551_RTCMR_A_B0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_B0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_b1_rtcmr_a_b1,rtcmr_a_b1,HI6551_RTCMR_A_B1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_B1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_b2_rtcmr_a_b2,rtcmr_a_b2,HI6551_RTCMR_A_B2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_B2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_b3_rtcmr_a_b3,rtcmr_a_b3,HI6551_RTCMR_A_B3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_B3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_c0_rtcmr_a_c0,rtcmr_a_c0,HI6551_RTCMR_A_C0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_C0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_c1_rtcmr_a_c1,rtcmr_a_c1,HI6551_RTCMR_A_C1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_C1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_c2_rtcmr_a_c2,rtcmr_a_c2,HI6551_RTCMR_A_C2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_C2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_c3_rtcmr_a_c3,rtcmr_a_c3,HI6551_RTCMR_A_C3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_C3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_d0_rtcmr_a_d0,rtcmr_a_d0,HI6551_RTCMR_A_D0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_D0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_d1_rtcmr_a_d1,rtcmr_a_d1,HI6551_RTCMR_A_D1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_D1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_d2_rtcmr_a_d2,rtcmr_a_d2,HI6551_RTCMR_A_D2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_D2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_d3_rtcmr_a_d3,rtcmr_a_d3,HI6551_RTCMR_A_D3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_D3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_e0_rtcmr_a_e0,rtcmr_a_e0,HI6551_RTCMR_A_E0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_E0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_e1_rtcmr_a_e1,rtcmr_a_e1,HI6551_RTCMR_A_E1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_E1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_e2_rtcmr_a_e2,rtcmr_a_e2,HI6551_RTCMR_A_E2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_E2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_e3_rtcmr_a_e3,rtcmr_a_e3,HI6551_RTCMR_A_E3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_E3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_f0_rtcmr_a_f0,rtcmr_a_f0,HI6551_RTCMR_A_F0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_F0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_f1_rtcmr_a_f1,rtcmr_a_f1,HI6551_RTCMR_A_F1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_F1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_f2_rtcmr_a_f2,rtcmr_a_f2,HI6551_RTCMR_A_F2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_F2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_f3_rtcmr_a_f3,rtcmr_a_f3,HI6551_RTCMR_A_F3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_F3_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_na0_rtccr_na0,rtccr_na0,HI6551_RTCCR_NA0_T,HI6551_BASE_ADDR, HI6551_RTCCR_NA0_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_na1_rtccr_na1,rtccr_na1,HI6551_RTCCR_NA1_T,HI6551_BASE_ADDR, HI6551_RTCCR_NA1_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_na2_rtccr_na2,rtccr_na2,HI6551_RTCCR_NA2_T,HI6551_BASE_ADDR, HI6551_RTCCR_NA2_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_na3_rtccr_na3,rtccr_na3,HI6551_RTCCR_NA3_T,HI6551_BASE_ADDR, HI6551_RTCCR_NA3_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_na0_rtclr_na0,rtclr_na0,HI6551_RTCLR_NA0_T,HI6551_BASE_ADDR, HI6551_RTCLR_NA0_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_na1_rtclr_na1,rtclr_na1,HI6551_RTCLR_NA1_T,HI6551_BASE_ADDR, HI6551_RTCLR_NA1_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_na2_rtclr_na2,rtclr_na2,HI6551_RTCLR_NA2_T,HI6551_BASE_ADDR, HI6551_RTCLR_NA2_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_na3_rtclr_na3,rtclr_na3,HI6551_RTCLR_NA3_T,HI6551_BASE_ADDR, HI6551_RTCLR_NA3_OFFSET)
HI_SET_GET(hi_hi6551_rtcctrl_na_rtccr_na,rtccr_na,HI6551_RTCCTRL_NA_T,HI6551_BASE_ADDR, HI6551_RTCCTRL_NA_OFFSET)
HI_SET_GET(hi_hi6551_rtcctrl_na_reserved,reserved,HI6551_RTCCTRL_NA_T,HI6551_BASE_ADDR, HI6551_RTCCTRL_NA_OFFSET)
HI_SET_GET(hi_hi6551_version_version,version,HI6551_VERSION_T,HI6551_BASE_ADDR, HI6551_VERSION_OFFSET)
HI_SET_GET(hi_hi6551_reserved0_reserved0,reserved0,HI6551_RESERVED0_T,HI6551_BASE_ADDR, HI6551_RESERVED0_OFFSET)
HI_SET_GET(hi_hi6551_reserved1_reserved1,reserved1,HI6551_RESERVED1_T,HI6551_BASE_ADDR, HI6551_RESERVED1_OFFSET)
HI_SET_GET(hi_hi6551_reserved2_reserved2,reserved2,HI6551_RESERVED2_T,HI6551_BASE_ADDR, HI6551_RESERVED2_OFFSET)
HI_SET_GET(hi_hi6551_reserved3_reserved3,reserved3,HI6551_RESERVED3_T,HI6551_BASE_ADDR, HI6551_RESERVED3_OFFSET)
HI_SET_GET(hi_hi6551_reserved4_reserved4,reserved4,HI6551_RESERVED4_T,HI6551_BASE_ADDR, HI6551_RESERVED4_OFFSET)
HI_SET_GET(hi_hi6551_htol_mode_htol_mode,htol_mode,HI6551_HTOL_MODE_T,HI6551_BASE_ADDR, HI6551_HTOL_MODE_OFFSET)
HI_SET_GET(hi_hi6551_htol_mode_reserved,reserved,HI6551_HTOL_MODE_T,HI6551_BASE_ADDR, HI6551_HTOL_MODE_OFFSET)
HI_SET_GET(hi_hi6551_dac_ctrl_dac_on_sel,dac_on_sel,HI6551_DAC_CTRL_T,HI6551_BASE_ADDR, HI6551_DAC_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dac_ctrl_aux_ibias_cfg,aux_ibias_cfg,HI6551_DAC_CTRL_T,HI6551_BASE_ADDR, HI6551_DAC_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dac_ctrl_reserved,reserved,HI6551_DAC_CTRL_T,HI6551_BASE_ADDR, HI6551_DAC_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_chip_soft_rst_soft_rst,soft_rst,HI6551_CHIP_SOFT_RST_T,HI6551_BASE_ADDR, HI6551_CHIP_SOFT_RST_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_pdns_sel,pdns_sel,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_pdns_mk,pdns_mk,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_vsys_uv_adj,vsys_uv_adj,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_nopwr_rc_off,nopwr_rc_off,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_reserved,reserved,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_chg_nopwr_vcoinsl,nopwr_vcoinsl,HI6551_NP_REG_CHG_T,HI6551_BASE_ADDR, HI6551_NP_REG_CHG_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_chg_nopwr_en_backup_chg,nopwr_en_backup_chg,HI6551_NP_REG_CHG_T,HI6551_BASE_ADDR, HI6551_NP_REG_CHG_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_chg_reserved,reserved,HI6551_NP_REG_CHG_T,HI6551_BASE_ADDR, HI6551_NP_REG_CHG_OFFSET)
HI_SET_GET(hi_hi6551_np_rsved1_no_pwr_resved1,no_pwr_resved1,HI6551_NP_RSVED1_T,HI6551_BASE_ADDR, HI6551_NP_RSVED1_OFFSET)
HI_SET_GET(hi_hi6551_np_rsved2_no_pwr_resved2,no_pwr_resved2,HI6551_NP_RSVED2_T,HI6551_BASE_ADDR, HI6551_NP_RSVED2_OFFSET)
HI_SET_GET(hi_hi6551_np_rsved3_no_pwr_resved3,no_pwr_resved3,HI6551_NP_RSVED3_T,HI6551_BASE_ADDR, HI6551_NP_RSVED3_OFFSET)
HI_SET_GET(hi_hi6551_np_rsved4_no_pwr_resved4,no_pwr_resved4,HI6551_NP_RSVED4_T,HI6551_BASE_ADDR, HI6551_NP_RSVED4_OFFSET)
HI_SET_GET(hi_hi6551_rtc_adj1_rtc_clk_step_adj1,rtc_clk_step_adj1,HI6551_RTC_ADJ1_T,HI6551_BASE_ADDR, HI6551_RTC_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_rtc_adj2_rtc_clk_step_adj2,rtc_clk_step_adj2,HI6551_RTC_ADJ2_T,HI6551_BASE_ADDR, HI6551_RTC_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_eco_ctrl,eco_ctrl,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_reflash_value_ctrl,reflash_value_ctrl,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_eco_filter_time,eco_filter_time,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_calibration_ctrl,calibration_ctrl,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_coul_ctrl_onoff_reg,coul_ctrl_onoff_reg,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_eco_refalsh_time_eco_reflash_time,eco_reflash_time,HI6551_ECO_REFALSH_TIME_T,HI6551_BASE_ADDR, HI6551_ECO_REFALSH_TIME_OFFSET)
HI_SET_GET(hi_hi6551_cl_out0_cl_out0,cl_out0,HI6551_CL_OUT0_T,HI6551_BASE_ADDR, HI6551_CL_OUT0_OFFSET)
HI_SET_GET(hi_hi6551_cl_out1_cl_out1,cl_out1,HI6551_CL_OUT1_T,HI6551_BASE_ADDR, HI6551_CL_OUT1_OFFSET)
HI_SET_GET(hi_hi6551_cl_out2_cl_out2,cl_out2,HI6551_CL_OUT2_T,HI6551_BASE_ADDR, HI6551_CL_OUT2_OFFSET)
HI_SET_GET(hi_hi6551_cl_out3_cl_out3,cl_out3,HI6551_CL_OUT3_T,HI6551_BASE_ADDR, HI6551_CL_OUT3_OFFSET)
HI_SET_GET(hi_hi6551_cl_in0_cl_in0,cl_in0,HI6551_CL_IN0_T,HI6551_BASE_ADDR, HI6551_CL_IN0_OFFSET)
HI_SET_GET(hi_hi6551_cl_in1_cl_in1,cl_in1,HI6551_CL_IN1_T,HI6551_BASE_ADDR, HI6551_CL_IN1_OFFSET)
HI_SET_GET(hi_hi6551_cl_in2_cl_in2,cl_in2,HI6551_CL_IN2_T,HI6551_BASE_ADDR, HI6551_CL_IN2_OFFSET)
HI_SET_GET(hi_hi6551_cl_in3_cl_in3,cl_in3,HI6551_CL_IN3_T,HI6551_BASE_ADDR, HI6551_CL_IN3_OFFSET)
HI_SET_GET(hi_hi6551_chg_timer0_chg_timer0,chg_timer0,HI6551_CHG_TIMER0_T,HI6551_BASE_ADDR, HI6551_CHG_TIMER0_OFFSET)
HI_SET_GET(hi_hi6551_chg_timer1_chg_timer1,chg_timer1,HI6551_CHG_TIMER1_T,HI6551_BASE_ADDR, HI6551_CHG_TIMER1_OFFSET)
HI_SET_GET(hi_hi6551_chg_timer2_chg_timer2,chg_timer2,HI6551_CHG_TIMER2_T,HI6551_BASE_ADDR, HI6551_CHG_TIMER2_OFFSET)
HI_SET_GET(hi_hi6551_chg_timer3_chg_timer3,chg_timer3,HI6551_CHG_TIMER3_T,HI6551_BASE_ADDR, HI6551_CHG_TIMER3_OFFSET)
HI_SET_GET(hi_hi6551_load_timer0_load_timer0,load_timer0,HI6551_LOAD_TIMER0_T,HI6551_BASE_ADDR, HI6551_LOAD_TIMER0_OFFSET)
HI_SET_GET(hi_hi6551_load_timer1_load_timer1,load_timer1,HI6551_LOAD_TIMER1_T,HI6551_BASE_ADDR, HI6551_LOAD_TIMER1_OFFSET)
HI_SET_GET(hi_hi6551_load_timer2_load_timer2,load_timer2,HI6551_LOAD_TIMER2_T,HI6551_BASE_ADDR, HI6551_LOAD_TIMER2_OFFSET)
HI_SET_GET(hi_hi6551_load_timer3_load_timer3,load_timer3,HI6551_LOAD_TIMER3_T,HI6551_BASE_ADDR, HI6551_LOAD_TIMER3_OFFSET)
HI_SET_GET(hi_hi6551_off_timer0_off_timer0,off_timer0,HI6551_OFF_TIMER0_T,HI6551_BASE_ADDR, HI6551_OFF_TIMER0_OFFSET)
HI_SET_GET(hi_hi6551_off_timer1_off_timer1,off_timer1,HI6551_OFF_TIMER1_T,HI6551_BASE_ADDR, HI6551_OFF_TIMER1_OFFSET)
HI_SET_GET(hi_hi6551_off_timer2_off_timer2,off_timer2,HI6551_OFF_TIMER2_T,HI6551_BASE_ADDR, HI6551_OFF_TIMER2_OFFSET)
HI_SET_GET(hi_hi6551_off_timer3_off_timer3,off_timer3,HI6551_OFF_TIMER3_T,HI6551_BASE_ADDR, HI6551_OFF_TIMER3_OFFSET)
HI_SET_GET(hi_hi6551_cl_int0_cl_int0,cl_int0,HI6551_CL_INT0_T,HI6551_BASE_ADDR, HI6551_CL_INT0_OFFSET)
HI_SET_GET(hi_hi6551_cl_int1_cl_int1,cl_int1,HI6551_CL_INT1_T,HI6551_BASE_ADDR, HI6551_CL_INT1_OFFSET)
HI_SET_GET(hi_hi6551_cl_int2_cl_int2,cl_int2,HI6551_CL_INT2_T,HI6551_BASE_ADDR, HI6551_CL_INT2_OFFSET)
HI_SET_GET(hi_hi6551_cl_int3_cl_int3,cl_int3,HI6551_CL_INT3_T,HI6551_BASE_ADDR, HI6551_CL_INT3_OFFSET)
HI_SET_GET(hi_hi6551_v_int0_v_int0,v_int0,HI6551_V_INT0_T,HI6551_BASE_ADDR, HI6551_V_INT0_OFFSET)
HI_SET_GET(hi_hi6551_v_int1_v_int1,v_int1,HI6551_V_INT1_T,HI6551_BASE_ADDR, HI6551_V_INT1_OFFSET)
HI_SET_GET(hi_hi6551_offset_current0_offset_current0,offset_current0,HI6551_OFFSET_CURRENT0_T,HI6551_BASE_ADDR, HI6551_OFFSET_CURRENT0_OFFSET)
HI_SET_GET(hi_hi6551_offset_current1_offset_current1,offset_current1,HI6551_OFFSET_CURRENT1_T,HI6551_BASE_ADDR, HI6551_OFFSET_CURRENT1_OFFSET)
HI_SET_GET(hi_hi6551_offset_voltage0_offset_voltage0,offset_voltage0,HI6551_OFFSET_VOLTAGE0_T,HI6551_BASE_ADDR, HI6551_OFFSET_VOLTAGE0_OFFSET)
HI_SET_GET(hi_hi6551_offset_voltage1_offset_voltage1,offset_voltage1,HI6551_OFFSET_VOLTAGE1_T,HI6551_BASE_ADDR, HI6551_OFFSET_VOLTAGE1_OFFSET)
HI_SET_GET(hi_hi6551_ocv_data1_ocv_data0,ocv_data0,HI6551_OCV_DATA1_T,HI6551_BASE_ADDR, HI6551_OCV_DATA1_OFFSET)
HI_SET_GET(hi_hi6551_ocv_data2_ocv_data1,ocv_data1,HI6551_OCV_DATA2_T,HI6551_BASE_ADDR, HI6551_OCV_DATA2_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre0_v_out0_pre0,v_out0_pre0,HI6551_V_OUT0_PRE0_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE0_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre0_v_out1_pre0,v_out1_pre0,HI6551_V_OUT1_PRE0_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE0_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre1_v_out0_pre1,v_out0_pre1,HI6551_V_OUT0_PRE1_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE1_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre1_v_out1_pre1,v_out1_pre1,HI6551_V_OUT1_PRE1_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE1_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre2_v_out0_pre2,v_out0_pre2,HI6551_V_OUT0_PRE2_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE2_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre2_v_out1_pre2,v_out1_pre2,HI6551_V_OUT1_PRE2_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE2_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre3_v_out0_pre3,v_out0_pre3,HI6551_V_OUT0_PRE3_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE3_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre3_v_out1_pre3,v_out1_pre3,HI6551_V_OUT1_PRE3_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE3_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre4_v_out0_pre4,v_out0_pre4,HI6551_V_OUT0_PRE4_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE4_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre4_v_out1_pre4,v_out1_pre4,HI6551_V_OUT1_PRE4_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE4_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre5_v_out0_pre5,v_out0_pre5,HI6551_V_OUT0_PRE5_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE5_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre5_v_out1_pre5,v_out1_pre5,HI6551_V_OUT1_PRE5_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE5_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre6_v_out0_pre6,v_out0_pre6,HI6551_V_OUT0_PRE6_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE6_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre6_v_out1_pre6,v_out1_pre6,HI6551_V_OUT1_PRE6_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE6_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre7_v_out0_pre7,v_out0_pre7,HI6551_V_OUT0_PRE7_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE7_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre7_v_out1_pre7,v_out1_pre7,HI6551_V_OUT1_PRE7_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE7_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre8_v_out0_pre8,v_out0_pre8,HI6551_V_OUT0_PRE8_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE8_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre8_v_out1_pre8,v_out1_pre8,HI6551_V_OUT1_PRE8_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE8_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre9_v_out0_pre9,v_out0_pre9,HI6551_V_OUT0_PRE9_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE9_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre9_v_out1_pre9,v_out1_pre9,HI6551_V_OUT1_PRE9_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE9_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre10_v_out0_pre10,v_out0_pre10,HI6551_V_OUT0_PRE10_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE10_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre10_v_out1_pre10,v_out1_pre10,HI6551_V_OUT1_PRE10_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE10_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre11_v_out0_pre11,v_out0_pre11,HI6551_V_OUT0_PRE11_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE11_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre11_v_out1_pre11,v_out1_pre11,HI6551_V_OUT1_PRE11_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE11_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre12_v_out0_pre12,v_out0_pre12,HI6551_V_OUT0_PRE12_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE12_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre12_v_out1_pre12,v_out1_pre12,HI6551_V_OUT1_PRE12_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE12_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre13_v_out0_pre13,v_out0_pre13,HI6551_V_OUT0_PRE13_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE13_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre13_v_out1_pre13,v_out1_pre13,HI6551_V_OUT1_PRE13_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE13_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre14_v_out0_pre14,v_out0_pre14,HI6551_V_OUT0_PRE14_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE14_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre14_v_out1_pre14,v_out1_pre14,HI6551_V_OUT1_PRE14_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE14_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre15_v_out0_pre15,v_out0_pre15,HI6551_V_OUT0_PRE15_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE15_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre15_v_out1_pre15,v_out1_pre15,HI6551_V_OUT1_PRE15_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE15_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre16_v_out0_pre16,v_out0_pre16,HI6551_V_OUT0_PRE16_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE16_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre16_v_out1_pre16,v_out1_pre16,HI6551_V_OUT1_PRE16_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE16_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre17_v_out0_pre17,v_out0_pre17,HI6551_V_OUT0_PRE17_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE17_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre17_v_out1_pre17,v_out1_pre17,HI6551_V_OUT1_PRE17_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE17_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre18_v_out0_pre18,v_out0_pre18,HI6551_V_OUT0_PRE18_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE18_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre18_v_out1_pre18,v_out1_pre18,HI6551_V_OUT1_PRE18_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE18_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre19_v_out0_pre19,v_out0_pre19,HI6551_V_OUT0_PRE19_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE19_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre19_v_out1_pre19,v_out1_pre19,HI6551_V_OUT1_PRE19_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE19_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre0_current0_pre0,current0_pre0,HI6551_CURRENT0_PRE0_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE0_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre0_current1_pre0,current1_pre0,HI6551_CURRENT1_PRE0_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE0_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre1_current0_pre1,current0_pre1,HI6551_CURRENT0_PRE1_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE1_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre1_current1_pre1,current1_pre1,HI6551_CURRENT1_PRE1_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE1_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre2_current0_pre2,current0_pre2,HI6551_CURRENT0_PRE2_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE2_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre2_current1_pre2,current1_pre2,HI6551_CURRENT1_PRE2_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE2_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre3_current0_pre3,current0_pre3,HI6551_CURRENT0_PRE3_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE3_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre3_current1_pre3,current1_pre3,HI6551_CURRENT1_PRE3_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE3_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre4_current0_pre4,current0_pre4,HI6551_CURRENT0_PRE4_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE4_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre4_current1_pre4,current1_pre4,HI6551_CURRENT1_PRE4_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE4_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre5_current0_pre5,current0_pre5,HI6551_CURRENT0_PRE5_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE5_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre5_current1_pre5,current1_pre5,HI6551_CURRENT1_PRE5_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE5_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre6_current0_pre6,current0_pre6,HI6551_CURRENT0_PRE6_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE6_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre6_current1_pre6,current1_pre6,HI6551_CURRENT1_PRE6_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE6_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre7_current0_pre7,current0_pre7,HI6551_CURRENT0_PRE7_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE7_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre7_current1_pre7,current1_pre7,HI6551_CURRENT1_PRE7_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE7_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre8_current0_pre8,current0_pre8,HI6551_CURRENT0_PRE8_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE8_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre8_current1_pre8,current1_pre8,HI6551_CURRENT1_PRE8_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE8_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre9_current0_pre9,current0_pre9,HI6551_CURRENT0_PRE9_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE9_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre9_current1_pre9,current1_pre9,HI6551_CURRENT1_PRE9_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE9_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre10_current0_pre10,current0_pre10,HI6551_CURRENT0_PRE10_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE10_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre10_current1_pre10,current1_pre10,HI6551_CURRENT1_PRE10_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE10_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre11_current0_pre11,current0_pre11,HI6551_CURRENT0_PRE11_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE11_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre11_current1_pre11,current1_pre11,HI6551_CURRENT1_PRE11_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE11_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre12_current0_pre12,current0_pre12,HI6551_CURRENT0_PRE12_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE12_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre12_current1_pre12,current1_pre12,HI6551_CURRENT1_PRE12_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE12_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre13_current0_pre13,current0_pre13,HI6551_CURRENT0_PRE13_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE13_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre13_current1_pre13,current1_pre13,HI6551_CURRENT1_PRE13_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE13_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre14_current0_pre14,current0_pre14,HI6551_CURRENT0_PRE14_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE14_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre14_current1_pre14,current1_pre14,HI6551_CURRENT1_PRE14_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE14_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre15_current0_pre15,current0_pre15,HI6551_CURRENT0_PRE15_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE15_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre15_current1_pre15,current1_pre15,HI6551_CURRENT1_PRE15_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE15_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre16_current0_pre16,current0_pre16,HI6551_CURRENT0_PRE16_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE16_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre16_current1_pre16,current1_pre16,HI6551_CURRENT1_PRE16_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE16_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre17_current0_pre17,current0_pre17,HI6551_CURRENT0_PRE17_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE17_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre17_current1_pre17,current1_pre17,HI6551_CURRENT1_PRE17_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE17_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre18_current0_pre18,current0_pre18,HI6551_CURRENT0_PRE18_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE18_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre18_current1_pre18,current1_pre18,HI6551_CURRENT1_PRE18_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE18_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre19_current0_pre19,current0_pre19,HI6551_CURRENT0_PRE19_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE19_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre19_current1_pre19,current1_pre19,HI6551_CURRENT1_PRE19_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE19_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cic_clk_inv_i,cic_clk_inv_i,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cic_clk_inv_v,cic_clk_inv_v,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_adc_ana_v_output,adc_ana_v_output,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_adc_ana_i_output,adc_ana_i_output,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cali_en_i,cali_en_i,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cali_en_i_force,cali_en_i_force,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cali_en_v_force,cali_en_v_force,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cali_en_v,cali_en_v,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_state_test_state_test,state_test,HI6551_STATE_TEST_T,HI6551_BASE_ADDR, HI6551_STATE_TEST_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved1_reg_data_clr,reg_data_clr,HI6551_CLJ_RESERVED1_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED1_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved1_clj_rw_inf1,clj_rw_inf1,HI6551_CLJ_RESERVED1_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED1_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved2_clj_rw_inf2,clj_rw_inf2,HI6551_CLJ_RESERVED2_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED2_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved3_clj_rw_inf3,clj_rw_inf3,HI6551_CLJ_RESERVED3_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED3_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved4_clj_rw_inf4,clj_rw_inf4,HI6551_CLJ_RESERVED4_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED4_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved5_i_reserve_1,i_reserve_1,HI6551_CLJ_RESERVED5_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED5_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved6_i_reserve_2,i_reserve_2,HI6551_CLJ_RESERVED6_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED6_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved7_v_reserve_1,v_reserve_1,HI6551_CLJ_RESERVED7_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED7_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved8_v_reserve_2,v_reserve_2,HI6551_CLJ_RESERVED8_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED8_OFFSET)

#endif // __HI6551_H__

