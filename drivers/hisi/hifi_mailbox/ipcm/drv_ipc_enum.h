
#ifndef __DRV_IPC_ENUM_H__
#define __DRV_IPC_ENUM_H__
/* ����������*/
typedef enum tagIPC_INT_CORE_E
{
    IPC_CORE_ARM11 = 0x0,   /* P500�ϵ�IPC */
    IPC_CORE_A9,
    IPC_CORE_CEVA,
    IPC_CORE_TENS0,
    IPC_CORE_TENS1,
    IPC_CORE_DSP,

    IPC_CORE_APPARM = 0x0,  /* V7R1/V3R2�ϵ�IPC */
    IPC_CORE_COMARM,
    IPC_CORE_LTEDSP,
    IPC_CORE_VDSP,
    IPC_CORE_ZSP,
    IPC_CORE_DSP_GU,

    IPC_CORE_ACPU = 0x0,/* V9R1 SFT�ϵ�IPC */
    IPC_CORE_CCPU,
    IPC_CORE_MCU,
    IPC_CORE_HIFI,
    IPC_CORE_BBE16,

    IPC_CORE_ACORE=0x0,   /*P531,V7R2*/
    IPC_CORE_CCORE,
    IPC_CORE_MCORE,
    IPC_CORE_LDSP,
    IPC_CORE_HiFi,
    IPC_CORE_BBE,          /*����5����P531\V7R2�����ڣ�����������ֻ��P531����*/
    IPC_CORE0_A15,
    IPC_CORE1_A15,

    /* !!!!����Ԫ������ӵ����  */
    IPC_CORE_BUTTOM
}IPC_INT_CORE_E;

typedef enum tagIPC_INT_LEV_E
{
   /* ����CCPU IPC�����Ϣ�ж�Դbitλ�� */
   IPC_CCPU_INT_SRC_HIFI_MSG                        = 1,      /*bit1,  ������Ϣ��HIFI ����CCPU ��IPC�ж�                                 */
   IPC_INT_DSP_MBX_RSD                              = 3,      /*bit3,  Ԥ����DSP�����ж�                                                 */
   IPC_INT_DSP_PS_PUB_MBX                           = 4,      /*bit4,  v7r2������Ϣ��PS���������ж�,DSP����CCPU��IPC�ж�                 */
   IPC_CCPU_INT_SRC_MCU_MSG                         = 5,      /*bit5,  ������Ϣ��MCU����CCPU ��IPC�ж�                                   */
   IPC_INT_DICC_UsRDATA                             = 6,      /*bit6,  V7R2 Ϊcsdҵ������ACPU���͸�CCPU��IPC�ж�                       */
   IPC_INT_DSP_PS_MAC_MBX                           = 7,      /*bit7,  v7r2 mac phy data ind�ж�                                         */
   IPC_INT_DSP_HALT                                 = 8,      /*bit8,  v7r2������DSP֪ͨARM˯�ߣ�DSP����CCPU��IPC�ж�                    */
   IPC_INT_DSP_RESUME                               = 9,      /*bit9,  v7r2������DSP֪ͨARM��ɻ��Ѻ�Ļָ�����,DSP����CCPU��IPC�ж�     */
   IPC_INT_WAKE_GU                                  =11,      /*bit11, v7r2��������ģ���Ѵ�ģ�жϣ�DSP����CCPU��IPC�ж�                  */
   IPC_INT_SLEEP_GU                                 =12,      /*bit12, v7r2��������ģ˯���жϣ�DSP����CCPU��IPC�ж�                      */
   IPC_CCPU_INT_SRC_ICC                             =13,      /*bit13, v7r2 ICCͨ�ţ�ACPU ����CCPU ��IPC�ж� ,ACPU���͸�CCPU��IPC�ж�    */
   IPC_CCPU_INT_SRC_ICC_PRIVATE                     =14,      /*bit14, v7r2 ICCͨ�ţ�iccר�÷�����Ϣʹ��  ,ACPU���͸�CCPU��IPC�ж�       */
   IPC_CCPU_SRC_ACPU_DUMP                           =15,      /*bit15, v7r2 ��ά�ɲ⣬ACPU ���͸�CCPU ��IPC�ж�                          */
   IPC_INT_DICC_RELDATA                             =16,      /*ԭΪ7�ţ�gu ��ȷ��ɾ������JB��֧����ʹ�ã�7�ű�dspռ�ã����Ϊ����ͨ��   */
   IPC_CCPU_INT_SRC_MCPU                            =17,      /*bit17,   ICC��Ϣ, MCU���͸�CCPU��  IPC�ж�                               */
   IPC_CCPU_INT_SRC_MCPU_WDT						=18,    /*����traceʱͣwdt */

   IPC_INT_WAKE_GSM                                 = 19,   /* bit16, BBE16֪ͨCCPU,����GSM��ģ */
   IPC_INT_WAKE_WCDMA                               = 20,   /* bit17, BBE16֪ͨCCPU,����WCDMA��ģ */
   IPC_CCPU_INT_SRC_DSP_MNTN                        = 21,   /* bit21��BBE16��ά�ɲ��ж�֪ͨmailbox���޾�ǿ */
   IPC_CCPU_INT_SRC_ACPU_RESET                      = 22,   /* bit22, A/C����C�˵�����λ�ڼ�˼�ͨ��(����C��),Ҧ���� */

   IPC_CCPU_INT_SRC_MCPU_FOR_TEST                   =29,      /*BIT29, FOR TEST interact with m3                                         */
   IPC_CCPU_INT_SRC_ACPU_TEST_ENABLE                =31,      /*bit31, IPC�Զ��������ж�ʹ��ʱʹ�ã�����IPC�жϲ���ʹ��ʱ����ɾ��        */
   IPC_CCPU_INT_SRC_BUTT                            =32,

   /* ����MCU IPC�����Ϣ�ж�Դbitλ�� */
    IPC_MCU_INT_SRC_ACPU_DRX                        = 0,      /*ACPU��CCPU����IPC�ж�ʱ����Ҫͬʱ��֪��M3                                */
    IPC_MCU_INT_SRC_CCPU_DRX                        = 1,      /*CCPU��ACPU����IPC�ж�ʱ����Ҫͬʱ��֪��M3                                */
    IPC_MCU_INT_SRC_ACPU_MSG                        = 4,      /* bit4,  ������Ϣ��    ACPU���͸�MCU��IPC�ж�                             */
    IPC_MCU_INT_SRC_CCPU_MSG                        = 5,      /* bit5,  ������Ϣ��    CCPU���͸�MCU��IPC�ж�                             */
    IPC_MCU_INT_SRC_HIFI_MSG                        = 6,      /* bit6,  ������Ϣ��    HIFI���͸�MCU�� IPC�ж�                            */
    IPC_MCU_INT_SRC_CCPU_IPF                        = 7,      /*bit7,   IPF�ָ�ר�ã�CCPU���͸�MCU��IPC�ж�                              */
    IPC_MCU_INT_SRC_ACPU_PD                         =16,      /*bit16,  POWERDOWN,   ACPU���͸�MCU��IPC�ж�                              */
    IPC_MCU_INT_SRC_CCPU_PD                         =17,      /*bit17,  POWERDOWN,   CCPU���͸�MCU��IPC�ж�                              */
    IPC_MCU_INT_SRC_HIFI_PD                         =18,      /*bit18,   POWERDOWN,  HIFI���͸�MCU��IPC�ж�                              */
    IPC_MCU_INT_SRC_ICC                             =19,      /*bit19,   m3 icc���õ�ipc�ж�                                             */
    IPC_MCU_INT_SRC_ICC_PRIVATE                     =20,      /*bit20,    m3 icc˽�е�ipc�жϣ�������ͨ����������������                  */
    IPC_MCU_INT_SRC_DUMP                            =21,      /* bit21 m3 dump�жϣ�ACORE���͸�MCU��IPC�ж�*/
    IPC_MCU_INT_SRC_HIFI_PU                         =22,      /* bit22,   POWERUP,  HIFI���͸�MCU��IPC�ж�                              */
    IPC_MCU_INT_SRC_HIFI_DDR_DFS_QOS                =23,      /*BIT23, HIFI��DDR��ƵͶƱ*/
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLOW            =24,      /*bit24, notify mcu into slow state*/
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP           =25,      /*bit25, notify mcu into sleep state*/
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID         =26,      /*bit26, ֪ͨMCUȫϵͳ�µ� */
    IPC_MCU_INT_SRC_CCPU_START                      =27,      /*bit27, ֪ͨMCU����CCPU */
	IPC_MCU_INT_SRC_HIFI_DDR_VOTE          			=28,      /*HIFI DDR��ˢ��*/
    IPC_MCU_INT_SRC_TEST                            =31,      /*BIT31, for test a\c interact with m3                                     */

    IPC_MCU_INT_SRC_BUTT = 32,

    /* ����ACPU IPC�����Ϣ�ж�Դbitλ�� */
    IPC_ACPU_INT_SRC_CCPU_MSG                       = 1,        /* bit1,  ������Ϣ��    CCPU���͸�ACPU��IPC�ж�                          */
    IPC_ACPU_INT_SRC_HIFI_MSG                       = 2,        /* bit2,  ������Ϣ��    HIFI���͸�ACPU��IPC�ж�                          */
    IPC_ACPU_INT_SRC_MCU_MSG                        = 3,        /* bit3,  ������Ϣ��    MCU���͸�ACPU��IPC�ж�                           */
    IPC_ACPU_INT_SRC_CCPU_NVIM                      = 4,        /* bit4,  NVIM��        CCPU���͸�ACPU��IPC�ж�                          */
    IPC_INT_DICC_USRDATA                            = 6,        /* bit6,  V7R2 Ϊcsdҵ������CCPU���͸�ACPU��IPC�ж�                    */
    IPC_ACPU_INT_SRC_ICC                            = 9,        /* bit9,   v7r2 icc    ���ã�CCPU���͸�ACPU��IPC�ж�                     */
    IPC_ACPU_INT_SRC_ICC_PRIVATE                    =10,        /* bit10,   v7r2 icc    ˽�ã�CCPU���͸�ACPU��IPC�ж�                    */
    IPC_ACPU_SRC_CCPU_DUMP                          =15,        /* bit15, v7r2 ��ά�ɲ⣬CCPU ���͸�ACPU ��IPC�ж�                       */
    IPC_INT_DICC_RELDATA_ACPU                       =16,        /* ԭΪ7�ţ�gu ��ȷ��ɾ������JB��֧����ʹ�ã�7�ű�dspռ�ã����Ϊ����ͨ��*/
    IPC_ACPU_INT_SRC_MCPU                           =17,        /*bit17,   ICC��Ϣ, MCU���͸�ACPU��  IPC�ж�                             */
	IPC_ACPU_INT_SRC_MCPU_WDT                       =18,        /*����traceʱͣwdt */
    IPC_ACPU_INT_MCU_SRC_DUMP                       = 19,       /* bin19   dump�жϣmMCU���͸�ACPU��IPC�ж�*/
    IPC_ACPU_INT_SRC_CCPU_RESET_IDLE                = 20,       /* bit20��A/C����C�˵�����λ�ڼ�˼�ͨ��(master in idle)��Ҧ���� */
    IPC_ACPU_INT_SRC_CCPU_RESET_SUCC                = 21,       /* bit21��A/C����C�˵�����λ�ڼ�˼�ͨ��(ccore reset ok)��Ҧ���� */
    IPC_ACPU_INT_SRC_MCU_FOR_TEST                   =29,        /*BIT29, test, m core to acore                                           */
    IPC_ACPU_INT_SRC_CCPU_TEST_ENABLE               =31,        /*bit31, IPC�Զ��������ж�ʹ��ʱʹ�ã�����IPC�жϲ���ʹ��ʱ����ɾ��      */
    IPC_ACPU_INT_SRC_BUTT = 32,

    /* ����HIFI IPC�����Ϣ�ж�Դbitλ�� */
    IPC_HIFI_INT_SRC_ACPU_MSG                       =0,        /* bit0, ������Ϣ��ACPU���͸�HIFI��IPC�ж�                                */
    IPC_HIFI_INT_SRC_CCPU_MSG                       =1,        /* bit1, ������Ϣ��CCPU���͸�HIFI��IPC�ж�                                */
    IPC_HIFI_INT_SRC_BBE_MSG                        =4,        /* bit4,  ������Ϣ��BBE16���͸�HIFI��IPC�ж�                              */
    IPC_HIFI_INT_SRC_MCU_MSG                        =6,        /* bit6,   ������Ϣ��MCU���͸�HIFI��IPC�ж�                               */
    IPC_HIFI_INT_SRC_BUTT=32,

   /* ����DSP IPC�����Ϣ�ж�Դbitλ�� */
   IPC_INT_MSP_DSP_OM_MBX                           = 0,       /*bit0, V7R2ʹ�ã�������Ϣ��CCPU���͸�DSP��IPC�ж�                        */
   IPC_INT_PS_DSP_PUB_MBX                           = 1,       /*bit1, v7r2ʹ�ã�  ������Ϣ��CCPU���͸�DSP��IPC�ж�                      */
   IPC_INT_PS_DSP_MAC_MBX                           = 2,       /*bit2,v7r2������Ϣ��ר�������ж�Ԥ��, DSP����CCPU��IPC�ж�               */
   IPC_INT_HIFI_DSP_MBX                             = 3,
   IPC_DSP_INT_SRC_CCPU_RESET                       = 4,       /*bit4,k3v3������Ϣ��C�˵�����λ����BBE16�����idle��IPC�ж�              */
   IPC_DSP_INT_SRC_BUTT                             =32,

    /* ����BBE IPC�����Ϣ�ж�Դbitλ�� */
    IPC_BBE_INT_SRC_HIFI_MSG                        =0,        /* bit0,  ������Ϣ��HIFI���͸�BBE16��IPC�ж�                              */
    IPC_BBE_INT_SRC_BUTT=32,

    IPC_INT_BUTTOM=32
}IPC_INT_LEV_E;


typedef enum tagIPC_SEM_ID_E
{
    IPC_SEM_SPI0               =0,
    IPC_SEM_NV                 =1,
    IPC_SEM_DICC               =3,
    IPC_SEM_RFILE_LOG          =4,
    IPC_SEM_EMMC               =5,
    IPC_SEM_GPIO               =6,
    IPC_SEM_CLK                =7,
    IPC_SEM_PMU_HI6451         =8,
    IPC_SEM_PMU_HI6551         =9,
    IPC_SEM_MTCMOS             =10,
    IPC_SEM_MEM                =11,
#if (defined(BSP_CONFIG_HI3630))
    IPC_SEM_IPF_PWCTRL         =12,
#endif
    IPC_SEM_PMU_HI6559         =13,
    IPC_SEM_I2C_SWITHC         =23,
    IPC_SEM_SYNC               =25,    
    IPC_SEM_BBP                =26,
    IPC_SEM1_IPC_TEST          =28,/*IPC�Զ�������ʹ��*/
	IPC_SEM2_IPC_TEST          =29,/*IPC�Զ�������ʹ��*/
    IPC_SEM_SYSCTRL            =30,
    IPC_SEM_ZSP_HALT           =31,
    IPC_SEM_BUTTOM
}IPC_SEM_ID_E;
#endif

