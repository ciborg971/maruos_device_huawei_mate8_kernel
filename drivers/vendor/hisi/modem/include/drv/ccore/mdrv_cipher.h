#ifndef __MDRV_CCORE_CIPHER_H__
#define __MDRV_CCORE_CIPHER_H__
#ifdef __cplusplus
extern "C"
{
#endif


/* ������ */
#define CIPHER_SUCCESS                  0

#define CHN_BUSY                    0
#define CHN_FREE                    1

typedef enum tagCIPHER_ALGORITHM_E
{
    CIPHER_ALG_NULL = 0,        /* ���㷨 */
    CIPHER_ALG_SNOW3G  = 1,     /* SNOW3G�㷨 */
    CIPHER_ALG_AES_128 = 2,     /* AES128�㷨 */
    CIPHER_ALG_AES_192 = 3,     /* AES192�㷨 */
    CIPHER_ALG_AES_256 = 4,     /* AES256�㷨 */
    CIPHER_ALG_ZUC = 5,	        /* ZUC�㷨 */
    CIPHER_ALG_BUTTOM,
}CIPHER_ALGORITHM_E;


typedef enum tagKDF_SHA_KEY_SOURCE_E
{
    SHA_KEY_SOURCE_DDR,             /*sha_key��Դ��input pointָ���ĵ�ַ�ռ� */
    SHA_KEY_SOURCE_KEYRAM,       /*  sha_key��Դ���ڲ�KeyRam */
    SHA_KEY_SOURCE_FOLLOW,       /*  sha_key��Դ���ϴ�KDF������sha_key */ 
    SHA_KEY_SOURCE_RESULT,        /*  sha_key��Դ����һ��KDF�����Ľ��*/
    SHA_KEY_SOURCE_MAX
}KDF_SHA_KEY_SOURCE_E;

typedef enum tagKDF_SHA_S_SOURCE_E
{
    SHA_S_SOURCE_DDR,              /*  sha_s��Դ��input pointָ���ĵ�ַ�ռ�*/
    SHA_S_SOURCE_KEYRAM,        /*  sha_s��Դ���ڲ�KeyRam */
    SHA_S_SOURCE_MAX
}KDF_SHA_S_SOURCE_E;

enum CIPHER_SECURITY_CHANNEL_ENUM
{
    CIPHER_SECURITY_CHANNEL_0            = 0,                /*ͨ��0*/
    CIPHER_SECURITY_CHANNEL_1            = 1,                /*ͨ��1*/
    CIPHER_SECURITY_CHANNEL_2            = 2,                /*ͨ��2*/
    CIPHER_SECURITY_CHANNEL_3            = 3,                /*ͨ��3*/
    CIPHER_SECURITY_CHANNEL_4            = 4,                /*ͨ��4*/
    CIPHER_SECURITY_CHANNEL_5            = 5,                /*ͨ��5*/
    CIPHER_SECURITY_CHANNEL_6            = 6,                /*ͨ��5*/

    CIPHER_SECURITY_CHANNEL_BUTT
};

/* ͨ����*/
#define LTE_SECURITY_CHANNEL_NAS          CIPHER_SECURITY_CHANNEL_2
#define LTE_SECURITY_CHANNEL_RRC          CIPHER_SECURITY_CHANNEL_2
#define LTE_SECURITY_CHANNEL_UL_SRB       CIPHER_SECURITY_CHANNEL_1
#define LTE_SECURITY_CHANNEL_DL_SRB       CIPHER_SECURITY_CHANNEL_1
#define LTE_SECURITY_CHANNEL_DL_DRB_CCORE CIPHER_SECURITY_CHANNEL_3 /* ��ֱͨ */
#define LTE_SECURITY_CHANNEL_DL_DRB_ACORE CIPHER_SECURITY_CHANNEL_5 /* ֱͨ */
#define LTE_SECURITY_CHANNEL_UL_ACC_0     CIPHER_SECURITY_CHANNEL_0
#define LTE_SECURITY_CHANNEL_UL_ACC_1     CIPHER_SECURITY_CHANNEL_6

typedef enum tagCIPHER_SINGLE_OPT_E
{
    CIPHER_OPT_ENCRYPT = 0x0,
    CIPHER_OPT_DECRYPT = 0x1,
    CIPHER_OPT_PROTECT_SMAC = 0x2,
    CIPHER_OPT_PROTECT_LMAC = 0x3,
    CIPHER_OPT_CHECK_PRE_SMAC  = 0x4,
    CIPHER_OPT_CHECK_POST_SMAC = 0x5,
    CIPHER_OPT_CHECK_PRE_LMAC  = 0x6,
    CIPHER_OPT_CHECK_POST_LMAC = 0x7,
    CIPHER_SINGLE_OPT_BUTTOM
}CIPHER_SINGLE_OPT_E;

typedef enum tagCIPHER_RELA_OPT_E
{
    CIPHER_PDCP_PRTCT_ENCY,
    CIPHER_PDCP_DECY_CHCK,
    CIPHER_NAS_ENCY_PRTCT,
    CIPHER_NAS_CHCK_DECY,
    CIPHER_RELA_OPT_BUTTOM

}CIPHER_RELA_OPT_E;


typedef enum tagCIPHER_KEY_LEN_E
{
    CIPHER_KEY_L128 = 0,        /* ��Կ����128 bit */
    CIPHER_KEY_L192 = 1,        /* ��Կ����192 bit */
    CIPHER_KEY_L256 = 2,        /* ��Կ����256 bit */
    CIPHER_KEY_LEN_BUTTOM
}CIPHER_KEY_LEN_E;

typedef enum tagCIPHER_SUBMIT_TYPE_E
{
    CIPHER_SUBM_NONE = 0,           /* �����κ�֪ͨ */
    CIPHER_SUBM_BLK_HOLD = 1,       /* ѭ����ѯ�ȴ���� */
    CIPHER_SUBM_CALLBACK = 2,       /* �ص�����֪ͨ */
    CIPHER_SUBM_BUTTOM
}CIPHER_SUBMIT_TYPE_E;

typedef enum tagCIPHER_NOTIFY_STAT_E
{
    CIPHER_STAT_OK = 0,           /* �ɹ���� */
    CIPHER_STAT_CHECK_ERR = 1,    /* �����Լ����� */
    CIPHER_STAT_BUTTOM
}CIPHER_NOTIFY_STAT_E;


typedef enum tagCIPHER_HDR_E
{
    CIPHER_HDR_BIT_TYPE_0              = 0,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ0�����������˹���*/
    CIPHER_HDR_BIT_TYPE_5              = 1,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�5λ�����뱣��*/
    CIPHER_HDR_BIT_TYPE_7              = 2,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�7λ�����뱣��*/
    CIPHER_HDR_BIT_TYPE_12             = 3,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ2���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�12λ�����뱣��*/
    CIPHER_APPEND_HDR_BIT_TYPE_5       = 4,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�5λ�������뱣����ֻ����*/
    CIPHER_APPEND_HDR_BIT_TYPE_7       = 5,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�7λ�������뱣����ֻ����*/
    CIPHER_APPEND_HDR_BIT_TYPE_12      = 6,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ2���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�12λ�������뱣����ֻ����*/
    CIPHER_HDR_BIT_TYPE_BUTT
}CIPHER_HDR_E;

typedef enum tagCIPHER_KEY_OUTPUT_E
{
    CIPHER_KEY_NOT_OUTPUT,    /*�������Կ*/
    CIPHER_KEY_OUTPUT,        /*�����Կ*/
    CIPHER_KEY_OUTPUT_BUTTOM
}CIPHER_KEY_OUTPUT_E;

typedef unsigned int CIPHER_KEY_LEN_E_U32;
typedef unsigned int CIPHER_KEY_OUTPUT_E_U32;

typedef struct tagCIPHER_ALGKEY_INFO_S
{
    unsigned int u32KeyIndexSec;
    unsigned int u32KeyIndexInt;
    CIPHER_ALGORITHM_E enAlgSecurity;          /* ��ȫ�����㷨ѡ��AEC�㷨����SNOW3G�㷨 */
    CIPHER_ALGORITHM_E enAlgIntegrity;         /* �����Բ����㷨ѡ��AEC�㷨����SNOW3G�㷨 */
}CIPHER_ALGKEY_INFO_S;

typedef struct tagACC_SINGLE_CFG_S
{
    unsigned int u32BearId;
    unsigned int u32AppdHeaderLen;
    unsigned int u32HeaderLen;
    unsigned int u32Count;
    int bMemBlock;                 /* �Ƿ��ǵ��ڴ�� */
    unsigned int u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/
    unsigned int u32Offset;                  /* ʹ�����ݾ������ݰ���ʼ��ַƫ��*/
    unsigned int u32OutLen;                  /* ʹ�õ������ݳ���*/
    unsigned int u32Aph;                      /*���Ӱ�ͷ��*/
    CIPHER_ALGKEY_INFO_S stAlgKeyInfo;  /* �����������㷨��Կ������Ϣ */
    void* pInMemMgr;
    void* pOutMemMgr;
} ACC_SINGLE_CFG_S;


typedef struct tagCIPHER_RELA_CFG_S
{
    CIPHER_RELA_OPT_E enOpt;          /* ��������(��DMA��������������㷨����) */
    unsigned char u8BearId;
    unsigned char u8Direction;
    CIPHER_HDR_E enAppdHeaderLen;
    CIPHER_HDR_E enHeaderLen;
    unsigned int u32Count;
    int bMemBlock;                 /* �Ƿ��ǵ��ڴ�飬����Ϊ������Ϊ������ */
    unsigned int u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/
    CIPHER_ALGKEY_INFO_S stAlgKeyInfo;  /* �����������㷨��Կ������Ϣ */
    void* pInMemMgr ;
    void* pOutMemMgr ;
    CIPHER_SUBMIT_TYPE_E enSubmAttr;
    unsigned int u32Private;
} CIPHER_RELA_CFG_S;

typedef struct tagCIPHER_SINGLE_CFG_S
{
    CIPHER_SINGLE_OPT_E enOpt;       /* ��������(��DMA��������������㷨����) */
    unsigned char u8BearId;
    unsigned char u8Direction;
    CIPHER_HDR_E enAppdHeaderLen;
    CIPHER_HDR_E enHeaderLen;
    unsigned int u32Count;
    int bMemBlock;                 /* �Ƿ��ǵ��ڴ�飬����Ϊ������Ϊ������ */
    unsigned int u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/ 
    CIPHER_ALGKEY_INFO_S stAlgKeyInfo;  /* �����������㷨��Կ������Ϣ */
    void* pInMemMgr ;
    void* pOutMemMgr ;
    CIPHER_SUBMIT_TYPE_E enSubmAttr;
    unsigned int u32Private;
	unsigned int usr_field1;
	unsigned int usr_field2;
	unsigned int usr_field3;
} CIPHER_SINGLE_CFG_S;


typedef struct tagS_CONFIG_INFO_S
{
    KDF_SHA_S_SOURCE_E   enShaSSource;      /* sha_s��Դ*/
    unsigned int              u32ShaSIndex;                /* sha_s��Դ��KeyRamʱ������keyRam�е�����*/
    unsigned int              u32ShaSLength;              /* sha_s�ĳ���*/
    void             *pSAddr;           
}S_CONFIG_INFO_S;


typedef struct
{
    CIPHER_KEY_LEN_E    enKeyLen; /* Ҫ��ȡ��Key�ĳ��ȣ����ϲ㴫��*/
    void                *pKeyAddr; /*Keyֵ��ŵ�ַ */
    CIPHER_KEY_LEN_E    *penOutKeyLen;/*�õ�ַ���ڴ��ʵ�ʷ��ص�Key�ĳ���*/
}KEY_GET_S;


typedef struct
{
    CIPHER_KEY_OUTPUT_E  enKeyOutput; /*ָʾ�Ƿ����Key��stKeyGet��*/
    KEY_GET_S stKeyGet;
}KEY_MAKE_S;


typedef struct tagKEY_CONFIG_INFO_S
{
    KDF_SHA_KEY_SOURCE_E enShaKeySource;    /* sha_key��Դ*/
    unsigned int              u32ShaKeyIndex;       /* sha_key��Դ��KeyRamʱ������keyRam�е����� */
    void             *pKeySourceAddr;   /* */
}KEY_CONFIG_INFO_S;


typedef enum tagBD_TYPE_E
{
	BD_TYPE_FREE,
	BD_TYPE_CFG,	
	BD_TYPE_TOTAL
}BD_TYPE_E;



typedef struct tagCIPHER_RD_INFO_STRU
{
	CIPHER_NOTIFY_STAT_E enstat;
	unsigned int  usr_field1;
	unsigned int  usr_field2;
	unsigned int  usr_field3;
}CIPHER_RD_INFO_S;

/*****************************************************************************
* �� �� ��  : mdrv_acc_dma
*
* ��������  : ��DMA��ʽ�������
*
* �������  : unsigned int u32BdFifoAddr  ACC����FIFO�׵�ַ
*             		pstCfg   ACC������Ϣ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_acc_dma (unsigned int u32BdFifoAddr, ACC_SINGLE_CFG_S *pstCfg);

/*****************************************************************************
* �� �� ��  : mdrv_acc_cipher
*
* ��������  : ���мӽ��ܹ��ܵ��������
*
* �������  : unsigned int u32BdFifoAddr
*             const void* pInMemMgr
*             const void* pOutMemMgr
*             ACC_SINGLE_CFG_S *pstCfg
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_acc_cipher(unsigned int u32BdFifoAddr, ACC_SINGLE_CFG_S *pstCfg);

/*****************************************************************************
* �� �� ��  : mdrv_acc_get_bdq_addr
*
* ��������  : ��ȡ����BDQ�����׵�ַ
*
* �������  : void
* �������  :
*
* �� �� ֵ  : 0��ʧ�ܣ���������Ч��ֵַ��
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_acc_get_bdq_addr(void);

/*****************************************************************************
* �� �� ��  : mdrv_acc_get_status
*
* ��������  : ��ȡ��ǰACCͨ��״̬
*
* �������  : Chn  ͨ����
* �������  :
*
* �� �� ֵ  : 0��ͨ��æ��1��ͨ������
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_acc_get_status(unsigned int chn);

/*****************************************************************************
* �� �� ��  : mdrv_acc_enable
*
* ��������  : ����BDQ�׵�ַ���Ĵ�������ʹ��ACC
*
* �������  :chn   ͨ����
				unsigned int u32BdFifoAddr  FIFO���������׵�ַ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_acc_enable(unsigned int chn, unsigned int u32BdFifoAddr);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_register_memfree_cb
*
* ��������  : ע���ϲ��ڴ��ͷź���
*
* �������  : unsigned int u32Chn ͨ����
*             int bSrc  0:����Buffer / 1:���Bufffer
*             CIPHER_FREEMEM_CB_T pFunFreeMemCb
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
/* Memory�ͷŻص�����*/
typedef void (*CIPHER_FREEMEM_CB_T)(void* pMemAddr);
int mdrv_cipher_register_memfree_cb(unsigned int u32Chn, int bSrc, CIPHER_FREEMEM_CB_T pFunFreeMemCb);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_register_notify_cb
*
* ��������  : ע���ϲ�֪ͨ�ص�����
*
* �������  : CIPHER_NOTIFY_CB_T pFunNotifyCb
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
/* ֪ͨ�ص�����ָ������*/
typedef void (*CIPHER_NOTIFY_CB_T)(unsigned int u32ChNum, unsigned int u32SourAddr,unsigned int u32DestAddr, CIPHER_NOTIFY_STAT_E enStatus, unsigned int u32Private);

int mdrv_cipher_register_notify_cb(CIPHER_NOTIFY_CB_T pFunNotifyCb);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_purge_chan
*
* ��������  : ���ָ��ͨ��
*
* �������  : unsigned int u32Chn
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*       1.�ýӿڲ������ж��������е��á�������ȫ���ڲ��л������������3��ͨ����
*       2.�ýӿڻ�ѭ���ȴ�ָ��ͨ�����У�Ȼ��λͨ����
*
*****************************************************************************/
int mdrv_cipher_purge_chan(unsigned int u32Chn);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_single_submit_task
*
* ��������  : ���������ύ
*
* �������  : unsigned int u32Chn               ͨ����
*                          	 CIPHER_SINGLE_CFG_S   pstCfg   ��������������Ϣ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_single_submit_task(unsigned int u32Chn, CIPHER_SINGLE_CFG_S *pstCfg);


/*****************************************************************************
* �� �� ��  : mdrv_cipher_rela_submit_task
*
* ��������  : ���������ύ
*
* �������  : unsigned int u32Chn               ͨ����
*                          	 CIPHER_RELA_CFG_S   pstCfg    ��������������Ϣ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_rela_submit_task(unsigned int u32Chn, CIPHER_RELA_CFG_S * pstCfg);


/*****************************************************************************
* �� �� ��  : mdrv_cipher_set_key
*
* ��������  : ����key��ָ����������λ��
*
* �������  : const void* pKeyAddr  Դ�����׵�ַ
*             CIPHER_KEY_LEN_E enKeyLen Key����
*             unsigned int u32KeyIndex       Ŀ������λ��
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_set_key(const void* pKeyAddr,CIPHER_KEY_LEN_E enKeyLen,unsigned int u32KeyIndex);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_get_key
*
* ��������  : ��ȡָ������λ�õ�Key
*
* �������  : unsigned int u32KeyIndex   ������
*             KEY_GET_S *pstKeyGet  ������key���ȡ�����key���ڴ��ַ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_get_key(unsigned int u32KeyIndex, KEY_GET_S *pstKeyGet);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_set_dbuf_para
*
* ��������  : ����Դ���ݸ�ʽ��Ϣ
*
* �������  : unsigned int u32Chn      ͨ����
*             int bSrc       TRUE,Դ��ַ����������;FALSE,Ŀ�ĵ�ַ��������
*             unsigned int u32BufOft   ����bufferָ��ƫ��
*             unsigned int u32LenOft   Buffer����ƫ��
*             unsigned int u32NextOft  ��һ�ڵ�ƫ��
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_set_dbuf_para(unsigned int u32Chn, int bSrc, unsigned int u32BufOft,unsigned int u32LenOft, unsigned int u32NextOft);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_get_cmplt_data
*
* ��������  : ��ȡ����ɵ�����
*
* �������  : unsigned int u32Chn                   ͨ����
*             unsigned int *pu32SourAddr            Դ��ַ
*             unsigned int *pu32DestAddr            Ŀ�ĵ�ַ
*             CIPHER_NOTIFY_STAT_E *penStatus  ״̬
*             unsigned int *pu32Private             ���ص�˽������
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_get_cmplt_data(unsigned int u32Chn, unsigned int *pu32SourAddr,unsigned int *pu32DestAddr, CIPHER_NOTIFY_STAT_E *penStatus, unsigned int *pu32Private);


/*****************************************************************************
* �� �� ��  : mdrv_cipher_read_key
*
* ��������  : ��ȡkey
*
* �������  : pDestAddr    ��ȡkey���ŵĵ�ַ
*             		 u32KeyIndex       Ҫ��ȡkey������
*             		u32ReadLength     Ҫ��ȡkey�ĳ���

* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_read_key (void *pDestAddr, unsigned int u32KeyIndex ,unsigned int u32ReadLength);


/*****************************************************************************
* �� �� ��  : mdrv_cipher_write_key
*
* ��������  : ��keyд��keyram��
*
* �������  : u32KeyIndex    Keyд��keyram�е�����
*             		 pSourAddr        Key���ڴ��е�ַ
*             		u32Length         key����

* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_write_key(unsigned int u32KeyIndex, void *pSourAddr, unsigned int u32Length);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_gen_key
*
* ��������  : �����µ�key
*
* �������  : KEY_CONFIG_INFO_S *pstKeyCfgInfo  KDF����ʱ����sha_key����������Ϣ
*             S_CONFIG_INFO_S *pstSCfgInfo      KDF����ʱ����sha_s��������
*             unsigned int u32DestIndex              KDF���������Key������KeyRam�е�λ��
*             KEY_MAKE_S *pstKeyMake            ����ָʾ���ɵ�KEY�Ƿ���������ʱ���ܵĵ�ַ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*            1 u32DestIndex��ȡֵ��Χ��[0~15]
*            2 �ýӿڲ������ж��������е��á�������ȫ���ڲ��л������
*
*****************************************************************************/
int mdrv_cipher_gen_key(KEY_CONFIG_INFO_S *pstKeyCfgInfo, S_CONFIG_INFO_S *pstSCfgInfo,unsigned int u32DestIndex, KEY_MAKE_S *pstKeyMake);



/*****************************************************************************
* �� �� ��  : mdrv_cipher_enable
*
* ��������  : Cipher����
*
* �������  : ��

* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_enable(void);


/*****************************************************************************
* �� �� ��  : mdrv_cipher_disable
*
* ��������  : Cipher����
*
* �������  : ��

* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int  mdrv_cipher_disable(void);

/*****************************************************************************
* �� �� ��  : mdrv_cipher_get_rdinfo
*
* ��������  : Cipher������ȡRD��Ϣ
*
* �������  : u32Chn  ͨ����
				 pstRd RD��Ϣ�ṹ��
				 pstRdNum   ��ȡ����RD����
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_get_rdinfo(unsigned int u32Chn, CIPHER_RD_INFO_S * pstRd, unsigned int* pstRdNum);


/*****************************************************************************
* �� �� ��  : mdrv_cipher_set_bdinfo
*
* ��������  : Cipher��������BD��Ϣ
*
* �������  : u32Chn  ͨ����
				 num  pstCfg���鳤��
				 pstCfg  BD������Ϣ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_set_bdinfo(unsigned int u32Chn, unsigned int num, CIPHER_SINGLE_CFG_S *pstCfg);


/*****************************************************************************
* �� �� ��  : mdrv_cipher_get_bd_num
*
* ��������  : Cipher��������BD��Ϣ
*
* �������  : u32Chn  ͨ����
				 bd_type  Bd����
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_get_bd_num(unsigned int u32Chn, BD_TYPE_E  bd_type);


/*****************************************************************************
* �� �� ��  : mdrv_cipher_get_chn_status
*
* ��������  : ��ȡCipher �ض�ͨ��״̬
*
* �������  : chn_id  ͨ����

* �������  :
*
* �� �� ֵ  : CIPHER_CHN_STATUS_Eö�����ͻ��ߴ�����롣
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_cipher_get_chn_status(int chn_id);


typedef enum tagCIPHER_CHN_STATUS_E
{
	CIPHER_CHN_BDEMPTY_RDEMPTY,	//BD queue and  RD queue are empty , the channel is idle.
	CIPHER_CHN_BDINUSE_RDEMPTY,	//BD queue in using, RD queue is empty, the channel in using.
	CIPHER_CHN_BDEMPTY_RDINUSE,	//BD queue is empty, RD queue in using , the channel in using.
	CIPHER_CHN_BDINUSE_RDINUSE	//Either BD queue and RD queue in using, the channel in using. 
} CIPHER_CHN_STATUS_E;

/* ע��CIPHER������ҪΪ��ֵ */
#define CIPHER_ERROR_BASE               0x80000800

typedef enum tagCIPHER_ERR_CODE_E
{
    CIPHER_ERR_CODE_NULL_PTR = 1,
    CIPHER_ERR_CODE_NO_MEM ,
    CIPHER_ERR_CODE_NOT_INIT ,
    CIPHER_ERR_CODE_FIFO_FULL ,
    CIPHER_ERR_CODE_INVALID_CHN ,
    CIPHER_ERR_CODE_INVALID_OPT ,
    CIPHER_ERR_CODE_ALIGN_ERROR ,
    CIPHER_ERR_CODE_PURGING ,
    CIPHER_ERR_CODE_TIME_OUT,
    CIPHER_ERR_CODE_INVALID_ENUM,
    CIPHER_ERR_CODE_INVALID_RD,
    CIPHER_ERR_CODE_RD_NULL,
    CIPHER_ERR_CODE_INVALID_KEY,
    CIPHER_ERR_CODE_CHECK_ERROR,
    CIPHER_ERR_CODE_BDLEN_ERROR,
    CIPHER_ERR_CODE_INVALID_NUM,
    CIPHER_ERR_CODE_NO_KEY,
    CIPHER_ERR_CODE_KEYLEN_ERROR,
    ACC_FIFOS_WORK,
    CIPHER_ENABLE_FAIL
}CIPHER_ERR_CODE_E;

#define CIPHER_NULL_PTR      ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NULL_PTR))
#define CIPHER_NO_MEM        ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_MEM))
#define CIPHER_NOT_INIT      ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NOT_INIT))
#define CIPHER_FIFO_FULL     ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_FIFO_FULL))
#define CIPHER_INVALID_CHN   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_CHN))
#define CIPHER_INVALID_OPT   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_OPT))
#define CIPHER_ALIGN_ERROR   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_ALIGN_ERROR))
#define CIPHER_PURGING       ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_PURGING))
#define CIPHER_TIME_OUT      ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_TIME_OUT))
#define CIPHER_INVALID_ENUM  ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_ENUM))
#define CIPHER_INVALID_RD    ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_RD))
#define CIPHER_RDQ_NULL      ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_RD_NULL))
#define CIPHER_INVALID_KEY   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_KEY))
#define CIPHER_CHECK_ERROR   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_CHECK_ERROR))
#define CIPHER_BDLEN_ERROR   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_BDLEN_ERROR))
#define CIPHER_INVALID_NUM   ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_NUM))
#define CIPHER_NO_KEY        ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_KEY))
#define CIPHER_KEYLEN_ERROR  ((int)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_KEYLEN_ERROR))
#define ACC_ALL_FIFO_WORK    ((int)(CIPHER_ERROR_BASE|ACC_FIFOS_WORK))
#define CIPHER_ENABLE_FAILED ((int)(CIPHER_ERROR_BASE|CIPHER_ENABLE_FAIL))
#define CIPHER_UNKNOWN_ERROR ((int)(CIPHER_ERROR_BASE|0xff))


#ifdef __cplusplus
}
#endif
#endif
