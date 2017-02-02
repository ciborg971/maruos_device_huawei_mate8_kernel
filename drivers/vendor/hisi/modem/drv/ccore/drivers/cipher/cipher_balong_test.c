#include <string.h>
#include "securec.h"
#include <osl_sem.h>
#include <osl_malloc.h>
#include <osl_thread.h>
#include <mdrv_cipher.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>
#include <bsp_cipher.h>
#include "cipher_balong.h"

/*
static unsigned char ph_len_in_pkt [CIPHER_HDR_BIT_TYPE_BUTT] = {    0,     1,     1,     2,     1,     1,     2};
 */
static unsigned char aph_len_in_bd [CIPHER_HDR_BIT_TYPE_BUTT] = {   
					0,		1,     1,     2,     1,     1,     2};
/*
static unsigned char aph_attr      [CIPHER_HDR_BIT_TYPE_BUTT] = {    0,     1,     1,     1,     0,     0,     0};
static unsigned int  aph_mast      [CIPHER_HDR_BIT_TYPE_BUTT] = {0x000, 0x01F, 0x07F, 0xFFF, 0x01F, 0x07F, 0xFFF};
 */
unsigned int fifo_cfg_cnt[7][3] =
{  /*  bd    cd    rd */
	{ 200,    0,    0},/* chn-0 */
	{  32,  320,   32},/* chn-1 */
	{  32,  320,   32},/* chn-2 */
	{ 1024, 4096,1024},/* chn-3 */
	{   0,    0,    0},/* chn-4 */
	{ 1024, 4096,   0},/* chn-5 */
	{ 200,    0,    0} /* chn-6 */
};

typedef struct tag_cipher_data_block
{
    unsigned int u32DataAddr;
    unsigned int u32DataLen;
    unsigned int pNextBlock;
}CIPHER_DATA_BLOCK;
typedef struct targ_cipher_ass_op_pdcp_arg
{
    CIPHER_RELA_CFG_S    stRelaCfg;
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int         blk_num;
    unsigned int *       blk_len;
    unsigned int         dataTestLen;
    CIPHER_KEY_LEN_E     keyLen;
    CIPHER_HDR_E         enHeaderLength; 
}CIPHER_ASS_OP_PDCP_ARG;

struct cipher_stress_tsk_para
{
	unsigned int         chnid;
	unsigned int         loops;
	int                  bDone;
	CIPHER_SUBMIT_TYPE_E enSubmit;
};

struct lup_mem_st {
	struct lup_mem_st 	*pnext;
	unsigned int 		size;
	unsigned char		*data_ptr;
	unsigned int		*r_mem;
	unsigned char		reserve[24]	;
};

struct cipher_test_global {
	void *data_ptr;
	void *ps_cfg_head;
	void *input_mem;
	void *encrypt_output;
	struct lup_mem_st *cdlist_output;
	void *decrypt_output;
	unsigned int init_flag;
	CIPHER_RD_INFO_S *ps_rd;
};

struct cipher_test_global g_cipher_test;

void *cipher_test_data_ptr;
void *cipher_test_ps_cfg_head;

void *cipher_test_input_mem;
void *cipher_test_encrypt_output_mem;
void *cipher_test_cdlist_output;
void *cipher_test_decrypt_output_mem;
CIPHER_RD_INFO_S *cipher_test_ps_rd;

unsigned int cipher_test_init_flag = 0;

#define	CIPHER_TEST_CD_NUM_CHN1		 (320 + 80)
#define	CIPHER_TEST_PS_NUM_CHN1		 (32 + 8)
#define CIPHER_TEST_BD_FIFO_ID		 0
#define CIPHER_TEST_CD_FIFO_ID		 1
#define CIPHER_TEST_RD_FIFO_ID		 2
#define BLOCK_MAX_SIZE               (64 * 1024 + 4 + 20)
#define MAC_SIZE_LONG                (4)
#define MAC_SIZE_SHORT               (2)
#define UP_LINK                      (0)
#define DOWN_LINK                    (1)
#define PDCP_SIGNAL_CHN              (1)
#define MAC_SIZE                     (4)
#define SEQNUM_SIZE                  (1)
#define PDCP_DATA_TASK_NUM           (2)
#define PDCP_DATA_CHN_1              (2)
#define PDCP_DATA_CHN_2              (3)
#define TEST_TASK_PRIORITY           (50)
#define TEST_TASK_STACK_SIZE         (10000)

#define CIPHER_TEST_PRINT(fmt, ...)  bsp_trace(BSP_LOG_LEVEL_ERROR, \
					BSP_MODU_CIPHER, "[CIPHER]: <%s> <%d>"fmt, 		\
					__FUNCTION__, __LINE__, ##__VA_ARGS__)
					
#define cipher_test_print(fmt, ...)	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER,"[Cipher test]"fmt, ##__VA_ARGS__);

static int   g_cipher_test_inited = 0;
static CIPHER_DATA_BLOCK    cipherInBlock [CIPHER_CHN_NUM];
static CIPHER_DATA_BLOCK    cipherTmpBlock[CIPHER_CHN_NUM];
static CIPHER_DATA_BLOCK    cipherOutBlock[CIPHER_CHN_NUM];
static osl_sem_id           cipherChnCbSem[CIPHER_CHN_NUM];
static CIPHER_SINGLE_CFG_S  g_cipher_uplink_cfg  [CIPHER_CHN_NUM];
static CIPHER_SINGLE_CFG_S  g_cipher_downlink_cfg[CIPHER_CHN_NUM];
static CIPHER_NOTIFY_STAT_E g_notify_stat[CIPHER_CHN_NUM] = {0};
static unsigned int         g_check_err  [CIPHER_CHN_NUM] = {0};
static unsigned int         g_FreeInMem_Num  = 0;
static unsigned int         g_FreeOutMem_Num = 0;
static unsigned char        g_key[32] =
{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
	0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
	0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f
};
static int s32LoopforMulti = 0;


int cipher_memcmp_ext(const void* mem1,const void* mem2,int size)
{
	int i = 0;

	for(i = 0; i < size; i++)
	{
		if(*((char*)mem1+i) != *((char*)mem2+i))
		{
			CIPHER_TEST_PRINT("diff_pos:%d,addr1(0x%x):%x,addr2(0x%x):%x\n",i,
								(int)((char*)mem1+i),(int)*((char*)mem1+i),
								(int)((char*)mem2+i),(int)*((char*)mem2+i),0);
			return -1;
		}
	}
	return 0;
}

static int cipherDataCmp(CIPHER_DATA_BLOCK* pBlk1,CIPHER_DATA_BLOCK* pBlk2)
{
    int s32CmpResult = -1;

    CIPHER_DATA_BLOCK* pTempBlk1 = pBlk1;
    CIPHER_DATA_BLOCK* pTempBlk2 = pBlk2;

    if((pBlk1 == NULL)||(pBlk2 == NULL))
    {
        return -1;
    }
    
    do
    {
        s32CmpResult = cipher_memcmp_ext((void*)pTempBlk1->u32DataAddr,
						(void*)pTempBlk2->u32DataAddr,pTempBlk1->u32DataLen);
        if(s32CmpResult != 0)
        {
            return -1;
        }
        else
        {
            pTempBlk1 = (CIPHER_DATA_BLOCK*)pTempBlk1->pNextBlock;
            pTempBlk2 = (CIPHER_DATA_BLOCK*)pTempBlk2->pNextBlock;
        }
    }while((pTempBlk1 != NULL) && (pTempBlk2 != NULL));
    
    return 0;
}

void cipherCbFunc_forMulti(unsigned int u32ChNum, unsigned int u32SourAddr,
						unsigned int u32DestAddr, CIPHER_NOTIFY_STAT_E enStatus,
						unsigned int u32Private)
{
     g_notify_stat[u32ChNum] = enStatus;
       
     if(enStatus == CIPHER_STAT_CHECK_ERR)
     {
		g_check_err[u32ChNum]++;
     }

     if((s32LoopforMulti >= 0x11)||(s32LoopforMulti == 0))
     {
         osl_sem_up(&cipherChnCbSem[u32ChNum]);
     }
     s32LoopforMulti++;
}

void cipherCbFunc(unsigned int u32ChNum, unsigned int u32SourAddr, 
					unsigned int u32DestAddr,CIPHER_NOTIFY_STAT_E enStatus, 
					unsigned int u32Private)
{
	g_notify_stat[u32ChNum] = enStatus;
	g_check_err[u32ChNum]   += (CIPHER_STAT_CHECK_ERR == enStatus) ? 1 : 0;
	osl_sem_up(&cipherChnCbSem[u32ChNum]);
}

void cipherInBufFree(void* pMemAddr)
{
	g_FreeInMem_Num++;
}

void cipherOutBufFree(void* pMemAddr)
{
	g_FreeOutMem_Num++;
}

void cipherTestInit()
{
	int i = 0;
	int s32Ret = 0;

	if(g_cipher_test_inited)
		return;

	for(i = 0; i < CIPHER_CHN_NUM; i++)
	{
		memset_s((void*)&cipherInBlock[i], sizeof(cipherInBlock[i]), 0, sizeof(CIPHER_DATA_BLOCK));
		memset_s((void*)&cipherTmpBlock[i],sizeof(cipherTmpBlock[i]),0, sizeof(CIPHER_DATA_BLOCK));
		memset_s((void*)&cipherOutBlock[i],sizeof(cipherOutBlock[i]),0, sizeof(CIPHER_DATA_BLOCK));
		memset_s((void*)&(g_cipher_uplink_cfg[i]),  sizeof(g_cipher_uplink_cfg[i]),   0, sizeof(CIPHER_SINGLE_CFG_S));
		memset_s((void*)&(g_cipher_downlink_cfg[i]),sizeof(g_cipher_downlink_cfg[i]), 0, sizeof(CIPHER_SINGLE_CFG_S));

		cipherInBlock[i].pNextBlock   = 0;
		cipherInBlock[i].u32DataLen   = BLOCK_MAX_SIZE;
		cipherInBlock[i].u32DataAddr  = (unsigned int)osl_cachedma_malloc(BLOCK_MAX_SIZE);
		cipherTmpBlock[i].pNextBlock  = 0;
		cipherTmpBlock[i].u32DataLen  = BLOCK_MAX_SIZE;
		cipherTmpBlock[i].u32DataAddr = (unsigned int)osl_cachedma_malloc(BLOCK_MAX_SIZE);
		cipherOutBlock[i].pNextBlock  = 0;
		cipherOutBlock[i].u32DataLen  = BLOCK_MAX_SIZE;
		cipherOutBlock[i].u32DataAddr = (unsigned int)osl_cachedma_malloc(BLOCK_MAX_SIZE);
		if(!cipherInBlock[i].u32DataAddr ||
			!cipherTmpBlock[i].u32DataAddr ||
			!cipherOutBlock[i].u32DataAddr)
		{
			CIPHER_TEST_PRINT("%s: cipherInBlock[%d].u32DataAddr osl_malloc fail, addr:0x%x\n",(int)__FUNCTION__,i,cipherInBlock[i].u32DataAddr,0,0);
			return;
		}

		s32Ret = osl_sem_bcreate(&cipherChnCbSem[i], OSL_SEM_Q_FIFO, OSL_SEM_Q_PRIORITY);
		if(s32Ret)
		{
			CIPHER_TEST_PRINT("Sem create faile,ret\n",0,0,0,0,0);
			return;
		}

		(void)mdrv_cipher_register_notify_cb((CIPHER_NOTIFY_CB_T)cipherCbFunc);
		(void)mdrv_cipher_register_memfree_cb((unsigned int)i, 0, (CIPHER_FREEMEM_CB_T)cipherInBufFree);
		(void)mdrv_cipher_register_memfree_cb((unsigned int)i, 1, (CIPHER_FREEMEM_CB_T)cipherOutBufFree);
		(void)mdrv_cipher_set_dbuf_para((unsigned int)i, 0x0, 0x0, 0x4, 0x8);
		(void)mdrv_cipher_set_dbuf_para((unsigned int)i, 0x1, 0x0, 0x4, 0x8);
	}
	g_cipher_test_inited = 1;
}

int build_blk_chain(CIPHER_DATA_BLOCK * pCipherInBlock, CIPHER_DATA_BLOCK CipherBlkChain[], unsigned int u32TestLen,
	unsigned int blk_num, unsigned int blk_len[])
{
	unsigned int total_len = 0;
	int i;
	unsigned int tmpAddr = 0;

	for(i = 0; i < (int)blk_num; i++)
		total_len += blk_len[i];

	if(u32TestLen != total_len)
	{
		CIPHER_TEST_PRINT("chain total len(%d) not equal to test len(%d).\n", total_len, u32TestLen, 0, 0,0);
		return -1;
	}
    tmpAddr = pCipherInBlock->u32DataAddr;
    for(i = 0; i < (int)blk_num; i++)
    {
		CipherBlkChain[i].u32DataAddr = tmpAddr;
		CipherBlkChain[i].u32DataLen  = blk_len[i];
		if(i == (int)(blk_num - 1))
			CipherBlkChain[i].pNextBlock = 0;
		else
		{
			CipherBlkChain[i].pNextBlock  = (unsigned int)&CipherBlkChain[i + 1];
			tmpAddr += blk_len[i];
		}
	}
	return 0;
}

int chain_protect_check_pdcp_longmac(unsigned char* caseName, unsigned int chnid,
	unsigned int dataTestLen, unsigned int blk_num, unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen, CIPHER_HDR_E enHeaderlen)
{
    int s32TestStatus = 0;
    int s32Ret = 0;
    int i = 0;
    CIPHER_DATA_BLOCK * blkChain = NULL;
    unsigned char u8Key[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    unsigned int u32KeyIndex = 0x1;
    unsigned int u32Private = 0x0;
    unsigned int ip_size = 0;
    CIPHER_SUBMIT_TYPE_E enSubmit = CIPHER_SUBM_CALLBACK;

	cipherTestInit();

	ip_size = aph_len_in_bd[enHeaderlen];
    cipherInBlock[chnid].u32DataLen = ip_size + dataTestLen;
    blk_len[0] += ip_size;
    blkChain = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num * sizeof(CIPHER_DATA_BLOCK));
	if(!blkChain)
		return -1;

    s32Ret = build_blk_chain(&cipherInBlock[chnid], blkChain, dataTestLen + ip_size, blk_num, blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }

    cipherTmpBlock[chnid].u32DataLen = MAC_SIZE_LONG;
    cipherTmpBlock[chnid].pNextBlock = 0;

    memset_s((void*)cipherInBlock[chnid].u32DataAddr, BLOCK_MAX_SIZE, 0,dataTestLen + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);

    for(i = 0; i <(int)cipherInBlock[chnid].u32DataLen; i++)
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr + i)) = (unsigned char)i;

    s32Ret = mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);
    if(s32Ret != 0)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",s32Ret,0,0,0,0);
        s32TestStatus = -1;
        goto clearup;
    }

	/*�������ҵ��*/
	g_cipher_uplink_cfg[chnid].enOpt           = CIPHER_OPT_PROTECT_LMAC;
	g_cipher_uplink_cfg[chnid].u8BearId        = 0;
	g_cipher_uplink_cfg[chnid].u8Direction     = 0;
	g_cipher_uplink_cfg[chnid].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].enHeaderLen     = enHeaderlen;
	g_cipher_uplink_cfg[chnid].u32Count        = 0;
	g_cipher_uplink_cfg[chnid].bMemBlock       = 0;
	g_cipher_uplink_cfg[chnid].u32BlockLen     = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndex;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = alg;
	g_cipher_uplink_cfg[chnid].enSubmAttr      = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private      = u32Private;
	g_cipher_uplink_cfg[chnid].pInMemMgr       = blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr      = (void*)&cipherTmpBlock[chnid];

	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));
	if(s32Ret != 0)
	{
		CIPHER_TEST_PRINT("mdrv_cipher_set_bdinfoTask fail,ret:0x%x\n",s32Ret,0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    /*��������У��ֵ����������ĩβ*/
/*    memcpy((void*)(cipherInBlock[chnid].u32DataAddr + dataTestLen),(void*)(cipherTmpBlock[chnid].u32DataAddr),MAC_SIZE);*/

	/*�������ҵ��*/
	g_cipher_downlink_cfg[chnid].enOpt            = CIPHER_OPT_CHECK_POST_LMAC;
	g_cipher_downlink_cfg[chnid].u8BearId         = 0;
	g_cipher_downlink_cfg[chnid].u8Direction      = 0;
	g_cipher_downlink_cfg[chnid].enAppdHeaderLen  = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].enHeaderLen      = enHeaderlen;
	g_cipher_downlink_cfg[chnid].u32Count         = 0;
	g_cipher_downlink_cfg[chnid].bMemBlock        = 0;
	g_cipher_downlink_cfg[chnid].u32BlockLen      = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec  = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt  = u32KeyIndex;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity   = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity  = alg;
	g_cipher_downlink_cfg[chnid].enSubmAttr       = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private       = u32Private;
	g_cipher_downlink_cfg[chnid].pInMemMgr        = blkChain;
	g_cipher_downlink_cfg[chnid].pOutMemMgr       = NULL;

	/*������Ϊ����ʱ�����������Լ��*/
	memcpy_s((void*)(blkChain[blk_num - 1].u32DataAddr + blkChain[blk_num - 1].u32DataLen), MAC_SIZE_LONG,
		(void*)cipherTmpBlock[chnid].u32DataAddr, MAC_SIZE_LONG);
	blkChain[blk_num - 1].u32DataLen = blkChain[blk_num - 1].u32DataLen + MAC_SIZE_LONG;
	g_notify_stat[chnid] = CIPHER_STAT_OK;

	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != 0)
	{
		CIPHER_TEST_PRINT("mdrv_cipher_set_bdinfoTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

	blkChain[blk_num - 1].u32DataLen = blkChain[blk_num - 1].u32DataLen - MAC_SIZE_LONG;

	if(g_notify_stat[chnid] != CIPHER_STAT_OK)
	{
		CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid]);
		s32TestStatus = -1;
		goto clearup;
	}

clearup:
	osl_free(blkChain);
	if(s32TestStatus == 0)
		CIPHER_TEST_PRINT("test pass.\n");
	else
		CIPHER_TEST_PRINT("test fail.\n"); 
	return s32TestStatus;
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��
* ʹ��CIPHER_ALG_AES_128���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200
*/
int BSP_CIPHER_001_001()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__, \
   	LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128, CIPHER_KEY_L128, CIPHER_HDR_BIT_TYPE_5); 
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_128���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_002()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);  
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_128���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_003()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128, CIPHER_KEY_L128, CIPHER_HDR_BIT_TYPE_12); 
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_128���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_004()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);  
}


/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_SNOW3G���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_005()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);                    
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_SNOW3G���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_001_006()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);  
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_SNOW3G���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_007()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);                    
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_SNOW3G���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_008()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);  
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_192���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_009()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192, CIPHER_KEY_L192, CIPHER_HDR_BIT_TYPE_5); 
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_KEY_L192���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_010()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192,CIPHER_KEY_L192,CIPHER_HDR_BIT_TYPE_5);  
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_192���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_011()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192, CIPHER_KEY_L192, CIPHER_HDR_BIT_TYPE_12); 
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_192���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_012()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192,CIPHER_KEY_L192,CIPHER_HDR_BIT_TYPE_12);  
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_256���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_013()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256, CIPHER_KEY_L256, CIPHER_HDR_BIT_TYPE_5); 
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_256���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_014()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256,CIPHER_KEY_L256,CIPHER_HDR_BIT_TYPE_5);  
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_256���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_015()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256, CIPHER_KEY_L256, CIPHER_HDR_BIT_TYPE_12); 
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_256���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_016()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256,CIPHER_KEY_L256,CIPHER_HDR_BIT_TYPE_12);  
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_NULL���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_017()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL, CIPHER_KEY_L128, CIPHER_HDR_BIT_TYPE_5); 
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_NULL���������Ա�������ͷ����Ϊ1Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_018()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);  
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_NULL���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ������������Ϊ���飬��������СΪ200��
*/
int BSP_CIPHER_001_019()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL, CIPHER_KEY_L128, CIPHER_HDR_BIT_TYPE_12); 
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_NULL���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_001_020()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);  
}

/*callback���޳�������*/
int BSP_CIPHER_001_021()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {1};
   unsigned int dataTestLen = 1;
   int s32Ret = 0;
   s32Ret = chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);                   
   return s32Ret;                    
}

/*
* PDCP�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_NULL���������Ա�������ͷ����Ϊ2Byte��
* һ�����ݰ�������Ϊ17�飬���С�ֱ�Ϊ23��45��132,17,46,80,1,101...���Ϊ����
*/
int BSP_CIPHER_001_022()
{
   unsigned int blk_num = 17;
   unsigned int blk_len[] = {23, 45, 132, 17, 46, 80, 1, 100, 101, 10, 20, 30, 40, 6, 1023, 1024, 23};
   unsigned int dataTestLen = 2721;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);  
}

int BSP_CIPHER_001_023()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);                    
}

int BSP_CIPHER_001_024()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);  
}

int BSP_CIPHER_001_025()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);                    
}

int BSP_CIPHER_001_026()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_pdcp_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC,CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);  
}

/* ��MACӦ�ó���*/
int chain_protect_check_nas_shortmac(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen)
{
    int s32TestStatus = 0;
    int s32Ret = 0;
    int i = 0;
    CIPHER_DATA_BLOCK* blkChain = NULL;
    unsigned char u8Key[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    unsigned int u32KeyIndex = 0x1;
    unsigned int u32Private = 0x0;
    CIPHER_SUBMIT_TYPE_E enSubmit = CIPHER_SUBM_CALLBACK;

    cipherTestInit();

    /*�������ݼӽ��ܻ�����*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;

    blkChain = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num * sizeof(CIPHER_DATA_BLOCK));
    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }    

    cipherTmpBlock[chnid].u32DataLen = MAC_SIZE_SHORT;

    memset_s((void*)cipherInBlock[chnid].u32DataAddr, BLOCK_MAX_SIZE,0,dataTestLen  + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);

    for(i = 0; i < (int)cipherInBlock[chnid].u32DataLen; i++)
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr + i)) = (unsigned char)i;

    s32Ret = mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);
    if(s32Ret != 0)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",s32Ret,0,0,0,0);
        s32TestStatus = -1;
        goto clearup;
    }
    
	/*�������ҵ��*/
	g_cipher_uplink_cfg[chnid].enOpt           = CIPHER_OPT_PROTECT_SMAC;
	g_cipher_uplink_cfg[chnid].u8BearId        = 0;
	g_cipher_uplink_cfg[chnid].u8Direction     = 0;
	g_cipher_uplink_cfg[chnid].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].enHeaderLen     = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].u32Count        = 0;
	g_cipher_uplink_cfg[chnid].bMemBlock       = 0;
	g_cipher_uplink_cfg[chnid].u32BlockLen     = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndex;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = alg;
	g_cipher_uplink_cfg[chnid].enSubmAttr      = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private      = u32Private;
	g_cipher_uplink_cfg[chnid].pInMemMgr       = blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr      = (void*)&cipherTmpBlock[chnid];

	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));
	if(s32Ret != 0)
	{
		CIPHER_TEST_PRINT("mdrv_cipher_set_bdinfoTask fail,ret:0x%x\n",s32Ret,0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}

    if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    /*��������У��ֵ����������ĩβ*/
/*    memcpy((void*)(cipherInBlock[chnid].u32DataAddr + dataTestLen),(void*)(cipherTmpBlock[chnid].u32DataAddr),MAC_SIZE);*/

	/*�������ҵ��*/
	g_cipher_downlink_cfg[chnid].enOpt             = CIPHER_OPT_CHECK_POST_SMAC;
	g_cipher_downlink_cfg[chnid].u8BearId          = 0;
	g_cipher_downlink_cfg[chnid].u8Direction       = 0;
	g_cipher_downlink_cfg[chnid].enAppdHeaderLen   = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].enHeaderLen       = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].u32Count          = 0;
	g_cipher_downlink_cfg[chnid].bMemBlock         = 0;
	g_cipher_downlink_cfg[chnid].u32BlockLen       = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec   = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt   = u32KeyIndex;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity    = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity   = alg;
	g_cipher_downlink_cfg[chnid].enSubmAttr        = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private        = u32Private;
	g_cipher_downlink_cfg[chnid].pInMemMgr         = blkChain;
	g_cipher_downlink_cfg[chnid].pOutMemMgr        = NULL;

	/*������Ϊ����ʱ�����������Լ��*/
	memcpy_s((void*)(blkChain[blk_num - 1].u32DataAddr + blkChain[blk_num - 1].u32DataLen), MAC_SIZE_SHORT,
		(void*)cipherTmpBlock[chnid].u32DataAddr,MAC_SIZE_SHORT);
	blkChain[blk_num - 1].u32DataLen = blkChain[blk_num - 1].u32DataLen + MAC_SIZE_SHORT;

    g_notify_stat[chnid] = CIPHER_STAT_OK;

    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != 0)
	{
		CIPHER_TEST_PRINT("mdrv_cipher_set_bdinfoTask fail,ret:0x%x\n",s32Ret,0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}    

	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    blkChain[blk_num - 1].u32DataLen = blkChain[blk_num - 1].u32DataLen - MAC_SIZE_SHORT;
    
    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid],0,0,0,0);
        s32TestStatus = -1;
        goto clearup;        
    } 

clearup:
    osl_free(blkChain);
    if(s32TestStatus == 0)
        CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
    else
        CIPHER_TEST_PRINT("test fail.\n",0,0,0,0,0);
    return s32TestStatus;
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_AES_128���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_002_001()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128, CIPHER_KEY_L128); 
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_AES_128���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_002_002()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128,CIPHER_KEY_L128);  
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_SNOW3G���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_002_003()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G,CIPHER_KEY_L128);                    
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_AES_128���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_002_004()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G,CIPHER_KEY_L128);  
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_AES_192���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_002_005()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192, CIPHER_KEY_L192); 
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_AES_192���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_002_006()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192,CIPHER_KEY_L192);  
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_AES_256���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_002_007()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256, CIPHER_KEY_L256); 
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_AES_256���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_002_008()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256,CIPHER_KEY_L256);  
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_NULL���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_002_009()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL, CIPHER_KEY_L256); 
}

/*
* NAS�����������ͳ��������MAC����Ϊ2Byte��ʹ��CIPHER_ALG_NULL���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_002_010()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL,CIPHER_KEY_L256);  
}

int BSP_CIPHER_002_011()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC,CIPHER_KEY_L128);                    
}

int BSP_CIPHER_002_012()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_shortmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC,CIPHER_KEY_L128);  
}

/* Nas��Mac*/
int chain_protect_check_nas_longmac(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen)
{
    int s32TestStatus = 0;
    int s32Ret        = 0;
    int i             = 0;
    CIPHER_DATA_BLOCK*   blkChain    = NULL;
    CIPHER_DATA_BLOCK*   blkChain2   = NULL;
    unsigned char        u8Key[32]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    unsigned int         u32KeyIndex = 0x1;
    unsigned int         u32Private  = 0x0;
    CIPHER_SUBMIT_TYPE_E enSubmit    = CIPHER_SUBM_CALLBACK;

	cipherTestInit();

    /*�������ݼӽ��ܻ�����*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;
    cipherInBlock[chnid].pNextBlock = 0;

    blkChain   = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    blkChain2  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));

    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }    

    cipherTmpBlock[chnid].u32DataLen = MAC_SIZE_LONG;
    cipherTmpBlock[chnid].pNextBlock = 0;

    memset_s((void*)cipherInBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE, 0,dataTestLen  + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);

    for(i = 0; i <(int) cipherInBlock[chnid].u32DataLen; i++)
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;

    s32Ret = mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);
    if(s32Ret != CIPHER_SUCCESS)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",s32Ret);
        s32TestStatus = -1;
        goto clearup;
    }
    
	/*�������ҵ��*/
	g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_PROTECT_LMAC;
	g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
	g_cipher_uplink_cfg[chnid].u8Direction                 = 1;
	g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].u32Count                    = 0;
	g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
	g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndex;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = alg;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;

	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}

	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    /*��������У��ֵ����������ĩβ*/
/*    memcpy((void*)(cipherInBlock[chnid].u32DataAddr + dataTestLen),(void*)(cipherTmpBlock[chnid].u32DataAddr),MAC_SIZE);*/

	/*�������ҵ��*/
	g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_CHECK_PRE_LMAC;
	g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
	g_cipher_downlink_cfg[chnid].u8Direction                 = 1;
	g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].u32Count                    = 0;
	g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
	g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndex;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = alg;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = NULL;
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;

	memcpy_s((void*)(cipherTmpBlock[chnid].u32DataAddr + MAC_SIZE_LONG), BLOCK_MAX_SIZE,
		(void*)(cipherInBlock[chnid].u32DataAddr), dataTestLen);

    blk_len[0] += MAC_SIZE_LONG;

    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,(MAC_SIZE_LONG + dataTestLen),blk_num,blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }
    g_notify_stat[chnid] = CIPHER_STAT_OK;

	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));   
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}

	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid]);
        s32TestStatus = -1;
        goto clearup;        
    } 

clearup:
    osl_free(blkChain);
    osl_free(blkChain2);
    if(s32TestStatus == 0)
        CIPHER_TEST_PRINT("test pass.\n");
    else
        CIPHER_TEST_PRINT("test fail.\n"); 

    return s32TestStatus;
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_128���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_003_001()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128, CIPHER_KEY_L128); 
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_128���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_003_002()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128,CIPHER_KEY_L128);  
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_SNOW3G���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_003_003()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G,CIPHER_KEY_L128);                    
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_SNOW3G���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_003_004()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G,CIPHER_KEY_L128);  
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_192���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_003_005()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192,CIPHER_KEY_L192);                    
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_192���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_003_006()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192,CIPHER_KEY_L192);  
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_256���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_003_007()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256,CIPHER_KEY_L256);                    
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_AES_256���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_003_008()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256,CIPHER_KEY_L256);  
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_NULL���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ����������Ϊ����
*/
int BSP_CIPHER_003_009()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL,CIPHER_KEY_L256);                    
}

/*
* NAS�����������ͳ��������MAC����Ϊ4Byte��ʹ��CIPHER_ALG_NULL���������Ա�����û�а�ͷ��û�и��Ӱ�ͷ
* һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_003_010()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   return chain_protect_check_nas_longmac((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS,dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL,CIPHER_KEY_L256);  
}

/* ���ܲ���*/
int chain_encrypt_decrypt(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen)
{
    int s32TestStatus = 0;
    int s32Ret        = 0;
    int i             = 0;
    CIPHER_DATA_BLOCK*   blkChain    = NULL;
    CIPHER_DATA_BLOCK*   blkChain2   = NULL;
    unsigned char        u8Key[32]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    unsigned int         u32KeyIndex = 0x1;
    unsigned int         u32Private  = 0x0;
    CIPHER_SUBMIT_TYPE_E enSubmit    = CIPHER_SUBM_CALLBACK;

	cipherTestInit();

    /*�������ݼӽ��ܻ�����*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;
    cipherInBlock[chnid].pNextBlock = 0;

    blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    
    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret)
    {
        s32TestStatus = -1;
        goto clearup;
    }    

    cipherTmpBlock[chnid].u32DataLen = dataTestLen;
    cipherOutBlock[chnid].u32DataLen = dataTestLen;
    cipherTmpBlock[chnid].pNextBlock = 0;
    cipherOutBlock[chnid].pNextBlock = 0;
#if 1
    memset_s((void*)cipherInBlock[chnid].u32DataAddr, BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
#endif
    for(i = 0; i <(int) cipherInBlock[chnid].u32DataLen; i++)
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;

    s32Ret = mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);
    if(s32Ret != CIPHER_SUCCESS)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",s32Ret);
        s32TestStatus = -1;
        goto clearup;
    }

	/*�������ҵ��*/
	g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
	g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
	g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
	g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].u32Count                    = 0;
	g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
	g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;
     
	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));             
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

	/*�������ҵ��*/
	g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
	g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
	g_cipher_downlink_cfg[chnid].u8Direction                 = 0;
	g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].u32Count                    = 0;
	g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
	g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;
    
    /*������ܺ����������*/
    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen,blk_num,blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }
    g_notify_stat[chnid] = CIPHER_STAT_OK;

    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid],0,0,0,0);
        s32TestStatus = -1;
        goto clearup;        
    } 
    
    s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
    if(s32Ret != 0)
    {
        CIPHER_TEST_PRINT("data cmp fail.\n",0,0,0,0,0);
        s32TestStatus = -1;
        goto clearup;
    }

clearup:
    osl_free(blkChain);
    osl_free(blkChain2);
    if(s32TestStatus == 0)
        CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
    else
		CIPHER_TEST_PRINT("test fail.\n",0,0,0,0,0);

    return s32TestStatus;
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128��û�а�ͷ��û�и��Ӱ�ͷ��
* һ�����ݰ������������Ϊ���飬��������СΪ200
*/
int BSP_CIPHER_004_001()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128, CIPHER_KEY_L128);
}

struct cipher_test {
	struct cipher_test_para* para;	
	CIPHER_SINGLE_CFG_S* bd;
	unsigned int blocks;

};

struct cipher_test_para {
	void* src;
	void* dst;
	int* src_len;
	int* dst_len;
	int blocks;
	CIPHER_SINGLE_CFG_S cfg;
	CIPHER_SINGLE_CFG_S* bd;
	int bd_cnt;
	int key_len;
	int channel;
	int use_chain;
	int use_cd;
	int total;
	int out_total;
};


int cipher_test_init(int channel)
{
	int ret;
	
	ret = osl_sem_bcreate(&cipherChnCbSem[channel], OSL_SEM_Q_FIFO, OSL_SEM_Q_PRIORITY);
	if(ret) {
		CIPHER_TEST_PRINT("Sem create failed\n");
		return ret;
	}
	(void)mdrv_cipher_register_notify_cb((CIPHER_NOTIFY_CB_T)cipherCbFunc);
	(void)mdrv_cipher_register_memfree_cb((unsigned int)channel, 0, (CIPHER_FREEMEM_CB_T)cipherInBufFree);
	(void)mdrv_cipher_register_memfree_cb((unsigned int)channel, 1, (CIPHER_FREEMEM_CB_T)cipherOutBufFree);
	(void)mdrv_cipher_set_dbuf_para((unsigned int)channel, 0x0, 0x0, 0x4, 0x8);
	(void)mdrv_cipher_set_dbuf_para((unsigned int)channel, 0x1, 0x0, 0x4, 0x8);

	return 0;
}


/*we design for 3 cases
*case 1: one bd <----> one buff
*case 2: one bd <----> one cd <----> one buff 
*exp 3 buffers, we use 3 cds ,also 3 bds. 
*case 3: one bd <----> a cd chain <---> a buff chain
*exp 3 buffers, we use 3 cds ,but 1 bd.
*/
static void cipher_test_set_para(struct cipher_test_para* para,
	int dl, int alg, int key_len, int channel,
	int use_chain, int use_cd, int aph_len, int operater, int submit)
{
	para->cfg.enOpt = operater;
	para->cfg.enSubmAttr = submit;
	para->cfg.u8Direction = (unsigned char)dl;
	para->cfg.enAppdHeaderLen = aph_len;
	para->cfg.stAlgKeyInfo.enAlgIntegrity = alg;
	para->cfg.stAlgKeyInfo.enAlgSecurity = alg;
	para->cfg.stAlgKeyInfo.u32KeyIndexInt = 0;
	para->cfg.stAlgKeyInfo.u32KeyIndexSec = 0;
	//para->cfg.bMemBlock = use_chain;
	para->key_len = key_len;
	para->channel = channel;
	para->use_chain = use_chain;
	para->use_cd = use_cd;
}
int cipher_test_dl(void)
{
	return 0;
}


int cipher_test_prepare_buff(struct cipher_test_para* para, 
	void** buff, int* len, int src)
{
	int i;
	int num;
	int value;
	CIPHER_DATA_BLOCK* next = NULL;
	CIPHER_DATA_BLOCK* prev = NULL;
	void* ttf;



	value = src ? 0x5a : 0x0;
	num = src ? para->blocks : para->bd_cnt;
	
	/*one bd one out ttf buffer */
	ttf = osl_malloc(sizeof(CIPHER_DATA_BLOCK) * num);
	
	if (!ttf) {
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "ttf blk alloc failed\n");
		return -1;
	}
	memset_s(ttf, sizeof(CIPHER_DATA_BLOCK) * num,
		0, sizeof(CIPHER_DATA_BLOCK) * num);
	
	next = (CIPHER_DATA_BLOCK*)ttf; 
	prev = (CIPHER_DATA_BLOCK*)ttf; 

	/*for one bd ,we alloc a big buffer*/
	if (!src && num == 1) {
		len[0] = para->out_total;
	}
	for (i = 0; i < num; i++) {
		next->u32DataAddr = (unsigned int)osl_cachedma_malloc(len[i]);
		if (!next->u32DataAddr) {
			next = (CIPHER_DATA_BLOCK*)ttf; 
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "data buff alloc failed\n");
			goto free; 
		}
		next->u32DataLen = len[i];
		memset_s((void*)next->u32DataAddr, len[i], 
			value, len[i]);
		
		/*if use chain, we should make buffers as a chain list*/
		/*data add append header len*/

		prev = next;
		if (para->use_chain) {
			prev->pNextBlock = (unsigned int)prev + sizeof(CIPHER_DATA_BLOCK);
		}
		next = (CIPHER_DATA_BLOCK*)((unsigned int)prev + sizeof(CIPHER_DATA_BLOCK));

	}
	prev->pNextBlock = 0;
	*buff = ttf;
	return 0;
free:
	for (i = 0; i < num && next; i++) {
		osl_cachedma_free((void*)next->u32DataAddr);
		next = (CIPHER_DATA_BLOCK*)((unsigned int)next + sizeof(CIPHER_DATA_BLOCK));
	}
	osl_free(ttf);

	return -1;
}


/*prepare ttf*/
int cipher_test_prepare_src_data(struct cipher_test_para* para)
{
	int ret;
	
	ret = cipher_test_prepare_buff(para, &para->src, para->src_len, 1);

	return ret;

}

int cipher_test_prepare_dst_buff(struct cipher_test_para* para)
{
	int ret;

	ret = cipher_test_prepare_buff(para, &para->dst, para->dst_len, 0);
	return ret;
}

int cipher_test_alloc_bd(struct cipher_test_para* para)
{

	para->bd_cnt = para->use_chain ? 1: para->blocks;
	
	para->bd = (CIPHER_SINGLE_CFG_S*)osl_malloc(
		para->bd_cnt * sizeof(CIPHER_SINGLE_CFG_S));
	
	if (!para->bd) {
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "bd alloc failed\n");
		return -1;
	}
	
	return 0;
	
}

int cipher_test_prepare_bd(struct cipher_test_para* para)
{
	int i;
	CIPHER_SINGLE_CFG_S* bd = para->bd;
	CIPHER_DATA_BLOCK* src = NULL;
	CIPHER_DATA_BLOCK* dst = NULL;
	
	for (i = 0; i < para->bd_cnt; i++) {
		memcpy_s(bd, sizeof(*bd), &para->cfg, sizeof(*bd));
		src = (CIPHER_DATA_BLOCK*)((unsigned int)para->src 
			+ i * sizeof(CIPHER_DATA_BLOCK));
		dst = (CIPHER_DATA_BLOCK*)((unsigned int)para->dst 
			+ i * sizeof(CIPHER_DATA_BLOCK));
		
		if (!para->use_cd) {
			bd->pInMemMgr = (void*)src->u32DataAddr;
			bd->bMemBlock = 1;
			bd->u32BlockLen = src->u32DataLen;
			bd->pOutMemMgr = (void*)dst->u32DataAddr;
		} else {
			bd->pInMemMgr = src;
			bd->pOutMemMgr = dst;
		}
		bd++;
	}

	return 0;
}


int cipher_test_cleanup(struct cipher_test_para* para)
{
	int i;
	int blocks;
	CIPHER_DATA_BLOCK* next;

	next= (CIPHER_DATA_BLOCK*)para->src;
	blocks = para->blocks;
	for (i = 0; i < blocks && next; i++) {
		osl_cachedma_free((void*)next->u32DataAddr);
		next = (CIPHER_DATA_BLOCK*)((unsigned int)next + sizeof(CIPHER_DATA_BLOCK));
	}
	next= (CIPHER_DATA_BLOCK*)para->dst;
	for (i = 0; i < para->bd_cnt && next; i++) {
		osl_cachedma_free((void*)next->u32DataAddr);
		next = (CIPHER_DATA_BLOCK*)((unsigned int)next + sizeof(CIPHER_DATA_BLOCK));
	}

	osl_free(para->bd);
	osl_free(para->src);
	osl_free(para->dst);
	para->src = NULL;
	para->dst = NULL;
	para->src_len = NULL;
	para->dst_len = NULL;
	para->blocks = 0;
	return 0;
	
}


int cipher_test_set_key_len(struct cipher_test_para* para)
{
	int ret;
	unsigned int key[16];


	memset_s(key, 16 * sizeof(*key), 0x5a, 16 * sizeof(*key));

	/*for test we use first key ram*/
	ret = mdrv_cipher_set_key(key, para->key_len, 0);
	
	return ret;
}

int cipher_test_start(struct cipher_test_para* para)
{
	int ret;

	/*only one bd, use cd chain*/
	ret = mdrv_cipher_set_bdinfo(para->channel, para->bd_cnt, para->bd);
	if (ret) {
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "set bd failed\n");
	}		

	return ret;
	
}
int cipher_test_perf(struct cipher_test_para* para, unsigned int loop)
{
	int ret;
	int total;
	unsigned int start;
	unsigned int end;
	unsigned int speed;

	ret = cipher_test_alloc_bd(para);
	if (ret)
		goto clean;	
	
	ret = cipher_test_prepare_src_data(para);
	if (ret)
		goto clean;

	ret = cipher_test_prepare_dst_buff(para);
	if (ret)
		goto clean;
	ret = cipher_test_prepare_bd(para);
	if (ret) {
		goto clean;
	}

	ret = cipher_test_init(para->channel);
	if (ret) {
		return ret;
	}

	total = loop * para->total;
	start = bsp_get_slice_value();

	while (loop--) 
		ret = cipher_test_start(para);
	
	end = bsp_get_slice_value();
	speed = total * 32 / (end - start);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "speed: %ukb/s\n", speed);
	
clean:
	cipher_test_cleanup(para);
	return ret;

}


int cipher_test_dl_perf(struct cipher_test_para* para)
{
	int ret;
	
	ret = cipher_test_prepare_src_data(para);
	if (ret)
		goto clean;
	ret = cipher_test_prepare_bd(para);
	if (ret) {
		goto clean;
	}

	ret = cipher_test_start(para);
	
clean:
	cipher_test_cleanup(para);
	return ret;

}

int cipher_test_ul_aes256(struct cipher_test_para* para, int loop)
{
	int ret;

	ret = cipher_test_set_key_len(para);
	if (ret)
		return ret;
	
	ret = cipher_test_perf(para, loop);
	return ret;
}

int cipher_test_ul_aes256_channel_srb(int loop, int by_pass)
{
	int blksz = 750;
	int src_len[25];
	int dst_len[25];

	int i;
	int ret;
	struct cipher_test_para para;

	if (by_pass) {
		cipher_disable_aes_opt_bypass(LTE_SECURITY_CHANNEL_UL_SRB);
	} else {
		cipher_enable_aes_opt_bypass(LTE_SECURITY_CHANNEL_UL_SRB);
	}
	memset_s(&para, sizeof(para), 0x0, sizeof(para));
	cipher_test_set_para(&para, 0, CIPHER_ALG_AES_256,
		CIPHER_KEY_L256, LTE_SECURITY_CHANNEL_UL_SRB,
		1, 1, CIPHER_APPEND_HDR_BIT_TYPE_12, 
		CIPHER_OPT_ENCRYPT, CIPHER_SUBM_BLK_HOLD);

	para.src_len = src_len;
	para.dst_len = dst_len;
	para.blocks = 25;
	for (i = 24; i > -1; i--) {
		src_len[i] = blksz;
		para.total += src_len[i];
		dst_len[i] = blksz + aph_len_in_bd[para.cfg.enAppdHeaderLen];
		para.out_total += dst_len[i];
	}

	ret = cipher_test_ul_aes256(&para, loop);
	
	return ret;
}


/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128��û�а�ͷ��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_004_002()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_128, CIPHER_KEY_L128);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_192���ܣ���Կ����192��û�а�ͷ��û�и��Ӱ�ͷ��
* һ�����ݰ������������Ϊ���飬��������СΪ200
*/
int BSP_CIPHER_004_003()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192, CIPHER_KEY_L192);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_192���ܣ���Կ����192��û�а�ͷ��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_004_004()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_192,CIPHER_KEY_L192);

}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_256���ܣ���Կ����256��û�а�ͷ��û�и��Ӱ�ͷ��
* һ�����ݰ������������Ϊ���飬��������СΪ200
*/
int BSP_CIPHER_004_005()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256, CIPHER_KEY_L256);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_256���ܣ���Կ����256��û�а�ͷ��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_004_006()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_AES_256, CIPHER_KEY_L256);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_SNOW3G���ܣ���Կ����128��û�а�ͷ��û�и��Ӱ�ͷ��
* һ�����ݰ������������Ϊ���飬��������СΪ200
*/
int BSP_CIPHER_004_007()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G, CIPHER_KEY_L128);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_SNOW3G���ܣ���Կ����128��û�а�ͷ��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_004_008()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G, CIPHER_KEY_L128);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_NULL���ܣ���Կ����128��û�а�ͷ��û�и��Ӱ�ͷ��
* һ�����ݰ������������Ϊ���飬��������СΪ200
*/
int BSP_CIPHER_004_009()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL, CIPHER_KEY_L128);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_NULL���ܣ���Կ����128��û�а�ͷ��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/

int BSP_CIPHER_004_010()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL, CIPHER_KEY_L128);
}

/*
* PDCP������Ƶ�������л����в�����ʹ��AES���мӽ��ܣ���Կ����Ϊ192��һ�����ݰ���������Ϊ200�ֽڡ�
* ʵ�ַ�ʽ���м��ܺ����ݣ���Ϊ���н�����������
*/
int BSP_CIPHER_004_011()
{
   int i = 0;
   int test_times = 100;
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;

   for(i = 0; i < test_times; i++)
   {
        chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                            CIPHER_ALG_AES_192, CIPHER_KEY_L192);                    
   }
   return 0;
}

int BSP_CIPHER_004_012()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC, CIPHER_KEY_L128);
}

int BSP_CIPHER_004_013()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC, CIPHER_KEY_L128);
}

/*PDCP_SIGNAL*/
int associate_operate_pdcp(unsigned char* caseName,unsigned int chnid,
 	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
 	CIPHER_RELA_CFG_S cfg[],CIPHER_SUBMIT_TYPE_E submAttr[])
 {
	int s32TestStatus = 0;
	int s32Ret        = 0;
	int i             = 0;
	CIPHER_DATA_BLOCK* blkChain1  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
	CIPHER_DATA_BLOCK* blkChain2  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
	unsigned int ip_size          = 0;
	unsigned int u32Private       = 0;
	unsigned int u32ChangedHead   = BSP_FALSE;
	unsigned int u32ChangedTail   = BSP_FALSE;

	cipherTestInit();

	cipherInBlock[chnid].pNextBlock  = 0;
	cipherTmpBlock[chnid].pNextBlock = 0;
	cipherOutBlock[chnid].pNextBlock = 0;
       
	switch(cfg[0].enOpt)
	{
	/*�漰IPͷ�Ĵ���*/
	case CIPHER_PDCP_PRTCT_ENCY:
	case CIPHER_PDCP_DECY_CHCK:
		ip_size = (cfg[0].enHeaderLen >> 20) & 0xF;
	break;
	default:
		CIPHER_TEST_PRINT("enOpt fail\n",0,0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}

	cipherInBlock[chnid].u32DataLen = ip_size + dataTestLen;
	blk_len[0]    += ip_size;
	u32ChangedHead = BSP_TRUE;

	s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain1,ip_size + dataTestLen,blk_num,blk_len);
	if(s32Ret != 0)
	{
		s32TestStatus = -1;
		goto clearup;
	}

	cipherTmpBlock[chnid].u32DataLen = ip_size + dataTestLen + MAC_SIZE;

	memset_s((void*)cipherInBlock[chnid].u32DataAddr, BLOCK_MAX_SIZE,0,cipherInBlock[chnid].u32DataLen + 20);
	memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,cipherTmpBlock[chnid].u32DataLen + 20);
	memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,cipherOutBlock[chnid].u32DataLen + 20);
 
	for(i = 0; i <(int) cipherInBlock[chnid].u32DataLen; i++)
		*((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;

	cfg[0].pInMemMgr  = (void*)blkChain1;
	cfg[0].pOutMemMgr = (void*)&cipherTmpBlock[chnid];
	cfg[0].enSubmAttr = submAttr[0];
	cfg[0].u32Private = u32Private;

	s32Ret = mdrv_cipher_rela_submit_task(chnid, &(cfg[0]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(submAttr[0] == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

	/*�������ҵ��*/
	switch(cfg[1].enOpt)
	{
	/*�漰IPͷ�Ĵ���*/
	case CIPHER_PDCP_PRTCT_ENCY:
	case CIPHER_PDCP_DECY_CHCK:
		ip_size = (cfg[1].enHeaderLen >> 20) & 0xF;
	break;
	default:
		s32TestStatus = -1;
		goto clearup;
	}

	blk_len[blk_num - 1] += MAC_SIZE;
	u32ChangedTail        = BSP_TRUE;

	s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,(ip_size + dataTestLen + MAC_SIZE),blk_num,blk_len);
	if(s32Ret != 0)
	{
		s32TestStatus = -1;
		goto clearup;
	}

	cipherOutBlock[chnid].u32DataLen = ip_size + dataTestLen;
	g_notify_stat[chnid] = CIPHER_STAT_OK;

	cfg[1].pInMemMgr  = (void*)blkChain2;
	cfg[1].pOutMemMgr = (void*)&cipherOutBlock[chnid];
	cfg[1].enSubmAttr = submAttr[1];
	cfg[1].u32Private = u32Private;

	s32Ret = mdrv_cipher_rela_submit_task(chnid, &(cfg[1]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(submAttr[1] == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

	if(g_notify_stat[chnid] != CIPHER_STAT_OK)
	{
		CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid],0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}

	s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
	if(s32Ret != 0)
	{
		CIPHER_TEST_PRINT("data cmp fail.\n",0,0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}   
clearup:
	/*��ԭblk_len[0]*/
	if(u32ChangedHead)
		blk_len[0] -= ip_size;
 
	/*��ԭblk_len[blk_num -1]*/
	if(u32ChangedTail)
		blk_len[blk_num -1] -= MAC_SIZE;

	osl_free(blkChain1);
	osl_free(blkChain2);
	if(s32TestStatus == 0)
		CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
	else
		CIPHER_TEST_PRINT("test fail.\n",0,0,0,0,0); 
     return s32TestStatus;   
}

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
 */
 int BSP_CIPHER_005_001()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }
 
 /*
  * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
  * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte��
  */
 int BSP_CIPHER_005_002()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i], sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i], sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

  /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
 */
 int BSP_CIPHER_005_003()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
 /*    unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
 */
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {132,45,23};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_004()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
 */
int BSP_CIPHER_005_005()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte.
 */
int BSP_CIPHER_005_006()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
* ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
*/
int BSP_CIPHER_005_007()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
* ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
*/
int BSP_CIPHER_005_008()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
* ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
*/
int BSP_CIPHER_005_009()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_010()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

  /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
 */
 int BSP_CIPHER_005_011()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {132,45,23};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_012()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

 /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
 */
 int BSP_CIPHER_005_013()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }
 
 /*
  * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
  * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte��
  */
 int BSP_CIPHER_005_014()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

  /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
 */
 int BSP_CIPHER_005_015()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {132,45,23};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_016()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

 /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
 */
 int BSP_CIPHER_005_017()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }
 
 /*
  * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
  * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte��
  */
 int BSP_CIPHER_005_018()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

  /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
 */
 int BSP_CIPHER_005_019()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {132,45,23};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_020()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
 */
 int BSP_CIPHER_005_021()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }
 
 /*
  * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
  * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte��
  */
 int BSP_CIPHER_005_022()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

  /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
 */
 int BSP_CIPHER_005_023()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {132,45,23};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
         memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_024()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
 */
 int BSP_CIPHER_005_025()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }
 
 /*
  * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
  * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte��
  */
 int BSP_CIPHER_005_026()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

  /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
 */
 int BSP_CIPHER_005_027()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {132,45,23};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_028()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
 */
int BSP_CIPHER_005_029()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }
 
 /*
  * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
  * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte��
  */
 int BSP_CIPHER_005_030()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

  /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
 */
 int BSP_CIPHER_005_031()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {132,45,23};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_032()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
 * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ1Byte.
 */
int BSP_CIPHER_005_033()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }
 
 /*
  * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
  * ��Կ����128��һ�����ݰ������������Ϊ���飬��������СΪ200, ��ͷ��Ϊ2Byte��
  */
 int BSP_CIPHER_005_034()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

  /*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ1Byte��
 */
 int BSP_CIPHER_005_035()
 {
     int i = 0;
     int s32Ret;
     CIPHER_RELA_CFG_S cfg[2];
     CIPHER_SUBMIT_TYPE_E submAttr[2];
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {132,45,23};
     unsigned int dataTestLen = 200;
     
     unsigned int u32KeyIndexInt = 0x0;
     unsigned int u32KeyIndexSec = 0x1;
     CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
     CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
     CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
     CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
 
     for(i=0; i<2; i++)
     {
		 memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
         memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
     }
     
     cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
     cfg[UP_LINK].u8BearId = 0;
     cfg[UP_LINK].u8Direction = 0;
     cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[UP_LINK].enHeaderLen = enHeaderLength;
     cfg[UP_LINK].u32Count = 0;
     cfg[UP_LINK].bMemBlock = 0;
     cfg[UP_LINK].u32BlockLen = 0;
     cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
     cfg[DOWN_LINK].u8BearId = 0;
     cfg[DOWN_LINK].u8Direction = 0;
     cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
     cfg[DOWN_LINK].u32Count = 0;
     cfg[DOWN_LINK].bMemBlock = 0;
     cfg[DOWN_LINK].u32BlockLen = 0;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
     cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
     cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;
 
     submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
     submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;
 
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }
     s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
     if(CIPHER_SUCCESS != s32Ret)
     {
         CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
         return -1;
     }    
 
     return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
 }

/*
 * PDCP�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ�
 * ��Կ����128��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����, ��ͷ��Ϊ2Byte��
 */
int BSP_CIPHER_005_036()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��AES�����Ա�����ʹ��AES���ܣ���Կ����192��һ�����ݰ������������Ϊ���飬
* ��������СΪ200
*/
int BSP_CIPHER_005_037()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L192;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_192;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_192;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��AES�����Ա�����ʹ��AES���ܣ���Կ����192��
*  һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����
*/
int BSP_CIPHER_005_038()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L192;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_192;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_192;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��AES�����Ա�����ʹ��AES���ܣ���Կ����256��һ�����ݰ������������Ϊ���飬
* ��������СΪ200
*/
int BSP_CIPHER_005_039()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L256;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_256;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_256;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��AES�����Ա�����ʹ��AES���ܣ���Կ����256��һ�����ݰ������������Ϊ���飬
* ��������СΪ200
*/
int BSP_CIPHER_005_040()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L256;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_256;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_256;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��SNOW3G�����Ա�����ʹ��AES���ܣ���Կ����192��һ�����ݰ������������Ϊ���飬
* ��������СΪ200
*/
int BSP_CIPHER_005_041()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L192;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_192;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��SNOW3G�����Ա�����ʹ��AES���ܣ���Կ����192��
*  һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����
*/
int BSP_CIPHER_005_042()
{
    int i = 0;
    int s32Ret;
    
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L192;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_192;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��SNOW3G�����Ա�����ʹ��AES���ܣ���Կ����256��һ�����ݰ������������Ϊ���飬
* ��������СΪ200
*/
int BSP_CIPHER_005_043()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L256;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_256;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��SNOW3G�����Ա�����ʹ��AES���ܣ���Կ����256��
*  һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ132��45��23�����Ϊ����
*/
int BSP_CIPHER_005_044()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L256;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_256;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��SNOW3G�����Ա�����ʹ��SNOW3G���ܣ���Կ����128��һ�����ݰ������������Ϊ���飬
* ��������СΪ200
*/

/*
* PDCP����������ͳ�����ʹ��AES�����Ա�����ʹ��AES���ܣ���Կ����128��һ�����ݰ������������Ϊ���飬
* ��������СΪ2048
*/
int BSP_CIPHER_005_045()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {2048};
    unsigned int dataTestLen = 2048;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* PDCP����������ͳ�����ʹ��AES�����Ա�����ʹ��AES���ܣ���Կ����128��
*  һ�����ݰ�����СΪ2048������Ϊ3�飬���С�ֱ�Ϊ1023��999��26�����Ϊ����
*/
int BSP_CIPHER_005_046()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {1023,999,26};
    unsigned int dataTestLen = 2048;
    
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    for(i=0; i<2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }
    
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]  = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK]= CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

int bsp_cipher_ass_op_pdcp(CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg)
{
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2]={{0},{0}};
	
    cfg[UP_LINK].enOpt = CIPHER_PDCP_PRTCT_ENCY;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = stCipherAssOpPdcpArg.enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_PDCP_DECY_CHCK;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = stCipherAssOpPdcpArg.enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec;

    s32Ret = mdrv_cipher_set_key(g_key, stCipherAssOpPdcpArg.keyLen, stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, stCipherAssOpPdcpArg.keyLen, stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_pdcp((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,stCipherAssOpPdcpArg.dataTestLen,\
        stCipherAssOpPdcpArg.blk_num,stCipherAssOpPdcpArg.blk_len,cfg,stCipherAssOpPdcpArg.submAttr);
}

int BSP_CIPHER_005_047()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_048()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_049()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_050()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_051()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_052()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_053()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_054()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_055()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_056()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_057()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_058()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}
 
int BSP_CIPHER_005_059()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_060()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_061()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_062()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_063()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_064()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_065()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_SNOW3G;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_066()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_SNOW3G;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_067()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_SNOW3G;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_005_068()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_CALLBACK;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0x0;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0x1;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_SNOW3G;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_pdcp(stCipherAssOpPdcpArg);
}

/* Nas��������*/
int associate_operate_nas(unsigned char* caseName,unsigned int chnid,
                    unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
                    CIPHER_RELA_CFG_S cfg[],CIPHER_SUBMIT_TYPE_E submAttr[])
{
    int s32TestStatus = 0;
    int s32Ret        = 0;
    int i             = 0;
    CIPHER_DATA_BLOCK* blkChain1 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    CIPHER_DATA_BLOCK* blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    unsigned int ip_size         = 0;
    unsigned int u32Private      = 0;
    unsigned int u32ChangedHead  = BSP_FALSE;
    unsigned int u32ChangedMac   = BSP_FALSE;

	cipherTestInit();
    
    cipherInBlock[chnid].pNextBlock  = 0;
    cipherTmpBlock[chnid].pNextBlock = 0;
    cipherOutBlock[chnid].pNextBlock = 0;

    /* NAS������������ǰ��Ҫ��Sequence Number����СΪ1Byte, ���Nuber���ǰ�ͷ*/
    switch(cfg[0].enOpt)
    {
        case CIPHER_NAS_ENCY_PRTCT:
        case CIPHER_NAS_CHCK_DECY:
              ip_size = SEQNUM_SIZE;
        break;
        default:
            CIPHER_TEST_PRINT("enOpt fail\n",0,0,0,0,0);
            s32TestStatus = -1;
            goto clearup;
    }

    cipherInBlock[chnid].u32DataLen = ip_size + dataTestLen;
    blk_len[0] += ip_size;
    u32ChangedHead = BSP_TRUE;

    /* ����PDCP�ṹ������*/
    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain1,ip_size + dataTestLen,blk_num,blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }

    /* �����������ΪMAC_SIZE + Seq Num + Nas Data*/
    cipherTmpBlock[chnid].u32DataLen = MAC_SIZE + ip_size + dataTestLen;
 
    memset_s((void*)cipherInBlock[chnid].u32DataAddr, BLOCK_MAX_SIZE, 0,cipherInBlock[chnid].u32DataLen  + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,cipherTmpBlock[chnid].u32DataLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,cipherOutBlock[chnid].u32DataLen + 20);

    /* �����������ݣ�����Sequnce Number �� NAS Meg*/
    for(i = 0; i <(int) cipherInBlock[chnid].u32DataLen; i++)
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;

	cfg[0].pInMemMgr  = (void*)blkChain1;
	cfg[0].pOutMemMgr = (void*)&cipherTmpBlock[chnid];
	cfg[0].enSubmAttr = submAttr[0];
	cfg[0].u32Private = u32Private;
    /* �ύ����*/
    s32Ret = mdrv_cipher_rela_submit_task(chnid, &(cfg[0]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(submAttr[0] == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    /*�������ҵ��*/
    switch(cfg[0].enOpt)
    {
    case CIPHER_NAS_ENCY_PRTCT:
    case CIPHER_NAS_CHCK_DECY:
		ip_size = SEQNUM_SIZE;
        break;
    default:
        CIPHER_TEST_PRINT("enOpt fail\n",0,0,0,0,0);
        break;
    }
    
    blk_len[0]   += MAC_SIZE;
    u32ChangedMac = BSP_TRUE;

    /* ����PDCP�ṹ������*/
    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,(MAC_SIZE + ip_size + dataTestLen),blk_num,blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }

    /* ������������������ȣ�ΪSeq Number + NAS Meg*/
    cipherOutBlock[chnid].u32DataLen = ip_size + dataTestLen;
    g_notify_stat[chnid]             = CIPHER_STAT_OK;

	cfg[1].pInMemMgr  = (void*)blkChain2;
	cfg[1].pOutMemMgr = (void*)&cipherOutBlock[chnid];
	cfg[1].enSubmAttr = submAttr[1];
	cfg[1].u32Private = u32Private;
    s32Ret = mdrv_cipher_rela_submit_task(chnid, &(cfg[1]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(submAttr[1] == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid]);
        s32TestStatus = -1;
        goto clearup;        
    }  

    s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
    if(s32Ret != 0)
    {
        CIPHER_TEST_PRINT("data cmp fail.\n");
        s32TestStatus = -1;
        goto clearup;
    }   
clearup:   
    /*��ԭblk_len[0]*/
    if(u32ChangedHead)
        blk_len[0] -= ip_size;
    /*��ԭblk_len[0]*/
    if(u32ChangedMac)
        blk_len[0] -= MAC_SIZE;
   
    osl_free(blkChain1);
    osl_free(blkChain2);
    if(s32TestStatus == 0)
        CIPHER_TEST_PRINT("test pass.\n");
    else
        CIPHER_TEST_PRINT("test fail.\n"); 
    return s32TestStatus;   
}
/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_001()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,
												sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_002()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_003()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_004()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_005()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_006()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_007()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_008()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_009()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
		memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}


/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_010()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_011()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_012()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_013()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}


/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_014()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_015()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_016()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_017()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}


/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_018()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_019()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_NULL�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_020()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_NULL;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_021()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_022()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_023()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_024()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_025()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_026()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_027()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_128�����Ա�����ʹ��CIPHER_ALG_SNOW3G���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_028()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_128;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_SNOW3G;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_029()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}


/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_030()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_031()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_032()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_033()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}


/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_034()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_035()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_128���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_036()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_128;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}


/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_192�����Ա�����ʹ��CIPHER_ALG_AES_192���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ����,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_037()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L192;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_192;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_192;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5;
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexInt;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_192�����Ա�����ʹ��CIPHER_ALG_AES_192���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_038()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0xe;
    unsigned int u32KeyIndexSec = 0xf;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L192;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_192;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_192;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5;
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_256�����Ա�����ʹ��CIPHER_ALG_AES_256���ܣ���Կ����128��һ�����ݰ���
* ����Ϊһ�飬���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_039()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0xe;
    unsigned int u32KeyIndexSec = 0xf;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L256;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_256;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_256;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5;
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}


/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_256�����Ա�����ʹ��CIPHER_ALG_AES_256���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_040()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0xe;
    unsigned int u32KeyIndexSec = 0xf;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L256;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_AES_256;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_256;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5;
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_192���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_041()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L192;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_192;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5;
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexInt;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_256�����Ա�����ʹ��CIPHER_ALG_AES_256���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��2Byte
*/
int BSP_CIPHER_006_042()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0xe;
    unsigned int u32KeyIndexSec = 0xf;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L192;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_192;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5;
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_AES_256���ܣ���Կ����128��
* һ�����ݰ�������Ϊ1�飬���СΪ200�����Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_043()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
/*
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
*/
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0xe;
    unsigned int u32KeyIndexSec = 0xf;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L256;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_256;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5;
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK] = CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_AES_256�����Ա�����ʹ��CIPHER_ALG_AES_256���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_044()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {132,45,23};
    unsigned int dataTestLen = 200;
    unsigned int u32KeyIndexInt = 0xe;
    unsigned int u32KeyIndexSec = 0xf;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L256;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_AES_256;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5;
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    submAttr[UP_LINK]   = CIPHER_SUBM_CALLBACK;
    submAttr[DOWN_LINK] = CIPHER_SUBM_CALLBACK;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

/*
* NAS�����������ͳ�����ʹ��CIPHER_ALG_SNOW3G�����Ա�����ʹ��CIPHER_ALG_NULL���ܣ���Կ����128��һ�����ݰ���
* ����Ϊ3�飬���С�ֱ�Ϊ132��45��23,���Ϊ����,�ύ����ΪCIPHER_SUBM_BLK_HOLDģʽ,��ͷ��1Byte
*/
int BSP_CIPHER_006_045()
{
    int i = 0;
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2];
    CIPHER_SUBMIT_TYPE_E submAttr[2];
    unsigned int blk_num = 18;
    unsigned int blk_len[] = {23, 45, 132, 17, 46, 80, 1, 100, 101, 10, 20, 30, 40, 6, 1023, 1024, 23, 9};
    unsigned int dataTestLen = 2730;
    unsigned int u32KeyIndexInt = 0x0;
    unsigned int u32KeyIndexSec = 0x1;
    CIPHER_KEY_LEN_E keyLen = CIPHER_KEY_L128;
    CIPHER_ALGORITHM_E enAlgIntegrity = CIPHER_ALG_SNOW3G;
    CIPHER_ALGORITHM_E enAlgSecurity = CIPHER_ALG_NULL;
    CIPHER_HDR_E enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 
    
    for(i = 0; i < 2; i++)
    {
        memset_s((void*)&cfg[i],sizeof(cfg[i]),0,sizeof(CIPHER_RELA_CFG_S));
        memset_s((void*)&submAttr[i],sizeof(submAttr[i]),0,sizeof(CIPHER_SUBMIT_TYPE_E));
    }

    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndexSec;


    submAttr[UP_LINK]   = CIPHER_SUBM_BLK_HOLD;
    submAttr[DOWN_LINK] = CIPHER_SUBM_BLK_HOLD;

    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, keyLen, u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,dataTestLen,blk_num,blk_len,cfg,submAttr);
}

extern struct cipher_ctl     cipher_module_ctl;
int bsp_cipher_test_bd_num(void)
{	
	int ret;
	unsigned int chn, bd_type;
	char *type_name;
	
	for (bd_type = 0; bd_type <= BD_TYPE_TOTAL; bd_type++) {
		
		switch(bd_type) {
			case BD_TYPE_FREE:
				type_name = "BD_TYPE_FREE";
				break;

			case BD_TYPE_CFG:
				type_name = "BD_TYPE_CFG";
				break;

			case BD_TYPE_TOTAL:
				type_name = "BD_TYPE_TOTAL";
				break;
		}
			
		for (chn = 0; chn < cipher_module_ctl.chn_cnt; chn++) {
			ret = mdrv_cipher_get_bd_num(chn, bd_type);
			
			switch(chn){
				case LTE_KEY_OPT_CHANNEL_KDF:
				case LTE_SECURITY_CHANNEL_UL_ACC_0: 
				case LTE_SECURITY_CHANNEL_UL_ACC_1:
					
					/*Wrong input, ret should be negative.*/
					if (ret >= 0) {
						CIPHER_TEST_PRINT("chn:%d, bd_type:%s,err!\n", chn, type_name);
						return CIPHER_CHECK_ERROR; 
					}
					break;
					
				default:
					if (ret < 0) {
						CIPHER_TEST_PRINT("chn:%d, bd_type:%s,err!\n", chn, type_name);
						return CIPHER_CHECK_ERROR;
					}
					break;
			}
		}
	}
	return CIPHER_SUCCESS;
}
int bsp_cipher_ass_op_nas(CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg)
{
    int s32Ret;
    CIPHER_RELA_CFG_S cfg[2]={{0},{0}};

    /*memset_s((void*)&cfg[i],0,sizeof(CIPHER_CFG_S) * 2);*/
    
    cfg[UP_LINK].enOpt = CIPHER_NAS_ENCY_PRTCT;
    cfg[UP_LINK].u8BearId = 0;
    cfg[UP_LINK].u8Direction = 0;
    cfg[UP_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[UP_LINK].enHeaderLen = stCipherAssOpPdcpArg.enHeaderLength;
    cfg[UP_LINK].u32Count = 0;
    cfg[UP_LINK].bMemBlock = 0;
    cfg[UP_LINK].u32BlockLen = 0;
    cfg[UP_LINK].stAlgKeyInfo.enAlgIntegrity = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity;
    cfg[UP_LINK].stAlgKeyInfo.enAlgSecurity = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexInt = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt;
    cfg[UP_LINK].stAlgKeyInfo.u32KeyIndexSec = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec;

    cfg[DOWN_LINK].enOpt = CIPHER_NAS_CHCK_DECY;
    cfg[DOWN_LINK].u8BearId = 0;
    cfg[DOWN_LINK].u8Direction = 0;
    cfg[DOWN_LINK].enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    cfg[DOWN_LINK].enHeaderLen = stCipherAssOpPdcpArg.enHeaderLength;
    cfg[DOWN_LINK].u32Count = 0;
    cfg[DOWN_LINK].bMemBlock = 0;
    cfg[DOWN_LINK].u32BlockLen = 0;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgIntegrity = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity;
    cfg[DOWN_LINK].stAlgKeyInfo.enAlgSecurity = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexInt = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt;
    cfg[DOWN_LINK].stAlgKeyInfo.u32KeyIndexSec = stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec;

    s32Ret = mdrv_cipher_set_key(g_key, stCipherAssOpPdcpArg.keyLen, stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }
    s32Ret = mdrv_cipher_set_key(g_key, stCipherAssOpPdcpArg.keyLen, stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_SetKey2 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return -1;
    }    

    return associate_operate_nas((unsigned char*)__FUNCTION__,PDCP_SIGNAL_CHN,stCipherAssOpPdcpArg.dataTestLen,\
        stCipherAssOpPdcpArg.blk_num,stCipherAssOpPdcpArg.blk_len,cfg,stCipherAssOpPdcpArg.submAttr);
}

int BSP_CIPHER_006_046()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_SNOW3G;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_047()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_SNOW3G;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_048()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_SNOW3G;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_049()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_SNOW3G;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_050()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_051()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_052()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_053()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_054()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_055()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_056()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_057()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_058()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_059()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_060()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_061()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_062()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_063()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_064()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_065()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_NULL;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_066()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_067()
{
    unsigned int blk_len[] = {200};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 1;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_068()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_5; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int BSP_CIPHER_006_069()
{
    unsigned int blk_len[] = {132,45,23};
    CIPHER_ASS_OP_PDCP_ARG stCipherAssOpPdcpArg;
    stCipherAssOpPdcpArg.blk_num = 3;
    stCipherAssOpPdcpArg.blk_len = blk_len;
    stCipherAssOpPdcpArg.submAttr[0]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.submAttr[1]=CIPHER_SUBM_BLK_HOLD;
    stCipherAssOpPdcpArg.dataTestLen = 200;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexInt = 0xe;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.u32KeyIndexSec = 0xf;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_ZUC;
    stCipherAssOpPdcpArg.stRelaCfg.stAlgKeyInfo.enAlgSecurity = CIPHER_ALG_AES_128;
    stCipherAssOpPdcpArg.keyLen = CIPHER_KEY_L128;
    stCipherAssOpPdcpArg.enHeaderLength = CIPHER_HDR_BIT_TYPE_12; 

    return bsp_cipher_ass_op_nas(stCipherAssOpPdcpArg);
}

int chain_encrypt_decrypt_header(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen, CIPHER_HDR_E enHeaderlen)
{
	int s32TestStatus = BSP_OK;
	int s32Ret        = BSP_OK;
	int i             = 0;
	unsigned int ip_size;
	CIPHER_DATA_BLOCK* blkChain   = NULL;
	CIPHER_DATA_BLOCK* blkChain2  = NULL;
	unsigned char u8Key[32]       = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
	unsigned int u32KeyIndex      = 0x1;
	unsigned int u32Private       = 0x0;
	CIPHER_SUBMIT_TYPE_E enSubmit = CIPHER_SUBM_CALLBACK;

	cipherTestInit();

	cipherInBlock[chnid].pNextBlock  = 0;
	cipherTmpBlock[chnid].pNextBlock = 0;
	cipherOutBlock[chnid].pNextBlock = 0;

	ip_size = aph_len_in_bd[enHeaderlen];

	/*�������ݼӽ��ܻ�����*/
	cipherInBlock[chnid].u32DataLen = ip_size + dataTestLen;
	blk_len[0] += ip_size;

	blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
	blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
 
	s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen+ip_size,blk_num,blk_len);
	if(s32Ret != BSP_OK)
	{
		s32TestStatus = BSP_ERROR;
		goto clearup;
	}

	cipherTmpBlock[chnid].u32DataLen = dataTestLen + ip_size;
	cipherOutBlock[chnid].u32DataLen = dataTestLen + ip_size;

#if 1   
	memset_s((void*)cipherInBlock[chnid].u32DataAddr, BLOCK_MAX_SIZE, 0,dataTestLen + 20);
	memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
	memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
#endif
	for(i = 0; i <(int) cipherInBlock[chnid].u32DataLen; i++)
		*((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;

	s32Ret = mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",s32Ret);
		s32TestStatus = BSP_ERROR;
		goto clearup;
	}

	/*�������ҵ��*/
	g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
	g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
	g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
	g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].enHeaderLen                 = enHeaderlen;
	g_cipher_uplink_cfg[chnid].u32Count                    = 0;
	g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
	g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;
  
	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret,0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

	/*�������ҵ��*/
	g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
	g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
	g_cipher_downlink_cfg[chnid].u8Direction                 = 0;
	g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].enHeaderLen                 = enHeaderlen;
	g_cipher_downlink_cfg[chnid].u32Count                    = 0;
	g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
	g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;

	/*������ܺ����������*/
	s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen + ip_size,blk_num,blk_len);
	if(s32Ret)
	{
		s32TestStatus = -1;
		goto clearup;
	}

	g_notify_stat[chnid] = CIPHER_STAT_OK;

	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret,0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

	if(g_notify_stat[chnid] != CIPHER_STAT_OK)
	{
		CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid],0,0,0,0);
		s32TestStatus = -1;
		goto clearup;        
	}

 	osl_task_delay(1);
	s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
	if(s32Ret != BSP_OK)
	{
		CIPHER_TEST_PRINT("data cmp fail.\n");
		s32TestStatus = -1;
		goto clearup;
	}

clearup:

	osl_free(blkChain);
	osl_free(blkChain2);
	cipherInBlock[chnid].u32DataLen -= ip_size;
	blk_len[0] -= ip_size;

	if(s32TestStatus == BSP_OK)
		CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
	else
		CIPHER_TEST_PRINT("test fail.\n",0,0,0,0,0); 

	return s32TestStatus;
}

 /*
 * PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128����ͷ����Ϊ1Byte��û�и��Ӱ�ͷ��
 * һ�����ݰ������������Ϊ���飬��������СΪ200
 */
 int BSP_CIPHER_007_001()
 {
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                     CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);
 }
 
 /*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128����ͷ����Ϊ1Byte��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
 int BSP_CIPHER_007_002()
 {
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {23,45,132};
    unsigned int dataTestLen = 200;
    
    return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                     CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);
 }

 /*
 * PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128����ͷ����Ϊ2Byte��û�и��Ӱ�ͷ��
 * һ�����ݰ������������Ϊ���飬��������СΪ200
 */
  int BSP_CIPHER_007_003()
 {
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    
    return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                     CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);
 }
 
 /*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128����ͷ����Ϊ2Byte��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
 int BSP_CIPHER_007_004()
 {
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {23,45,132};
    unsigned int dataTestLen = 200;
    
    return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                     CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);
 }

 /*
 * PDCP���м��ܵ��ͳ�����CIPHER_ALG_SNOW3G���ܣ���Կ����128����ͷ����Ϊ1Byte��û�и��Ӱ�ͷ��
 * һ�����ݰ������������Ϊ���飬��������СΪ200
 */
 int BSP_CIPHER_007_005()
  {
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                      CIPHER_ALG_SNOW3G, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);
  }
  
 /*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_SNOW3G���ܣ���Կ����128����ͷ����Ϊ1Byte��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
  int BSP_CIPHER_007_006()
  {
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {23,45,132};
     unsigned int dataTestLen = 200;
     
     return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                      CIPHER_ALG_SNOW3G, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);
  }

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_SNOW3G���ܣ���Կ����128����ͷ����Ϊ2Byte��û�и��Ӱ�ͷ��
* һ�����ݰ������������Ϊ���飬��������СΪ200
*/
int BSP_CIPHER_007_007()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_SNOW3G���ܣ���Կ����128����ͷ����Ϊ2Byte��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_007_008()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_SNOW3G, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_NULL���ܣ���Կ����128����ͷ����Ϊ1Byte��û�и��Ӱ�ͷ��
* һ�����ݰ������������Ϊ���飬��������СΪ200
*/
int BSP_CIPHER_007_009()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_NULL���ܣ���Կ����128����ͷ����Ϊ1Byte��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
int BSP_CIPHER_007_010()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_NULL, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);
}

/*
 * PDCP���м��ܵ��ͳ�����CIPHER_ALG_NULL���ܣ���Կ����128����ͷ����Ϊ2Byte��û�и��Ӱ�ͷ��
 * һ�����ݰ������������Ϊ���飬��������СΪ200
 */
 int BSP_CIPHER_007_011()
  {
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                      CIPHER_ALG_NULL, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);
  }
  
 /*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_NULL���ܣ���Կ����128����ͷ����Ϊ2Byte��û�и��Ӱ�ͷ��
* ���С�ֱ�Ϊ23��45��132�����Ϊ����
*/
  int BSP_CIPHER_007_012()
  {
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {23,45,132};
     unsigned int dataTestLen = 200;
     
     return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                      CIPHER_ALG_NULL, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);
  }

int BSP_CIPHER_007_013()
  {
     unsigned int blk_num = 1;
     unsigned int blk_len[] = {200};
     unsigned int dataTestLen = 200;
     
     return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                      CIPHER_ALG_ZUC, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);
  }
  
int BSP_CIPHER_007_014()
  {
     unsigned int blk_num = 3;
     unsigned int blk_len[] = {23,45,132};
     unsigned int dataTestLen = 200;
     
     return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                      CIPHER_ALG_ZUC, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_5);
  }

int BSP_CIPHER_007_015()
{
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {200};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);
}

int BSP_CIPHER_007_016()
{
   unsigned int blk_num = 3;
   unsigned int blk_len[] = {23,45,132};
   unsigned int dataTestLen = 200;
   
   return  chain_encrypt_decrypt_header((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                    CIPHER_ALG_ZUC, CIPHER_KEY_L128,CIPHER_HDR_BIT_TYPE_12);
}

int chain_encrypt_decrypt_aph(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen,CIPHER_HDR_E aphlen,unsigned int u32Count)
{
	int s32TestStatus = 0;
	int s32Ret        = 0;
	int i             = 0;
	unsigned int         ip_size     = 0;
	CIPHER_DATA_BLOCK*   blkChain    = NULL;
	CIPHER_DATA_BLOCK*   blkChain2   = NULL;
	unsigned char        u8Key[32]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
	unsigned int         u32KeyIndex = 0x1;
	unsigned int         u32Private  = 0x0;
	CIPHER_SUBMIT_TYPE_E enSubmit    = CIPHER_SUBM_CALLBACK;

	cipherTestInit();
      
	cipherInBlock[chnid].pNextBlock = 0;
	cipherInBlock[chnid].u32DataLen = dataTestLen;
  
	blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
	blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));

	s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
	if(s32Ret)
	{
		s32TestStatus = 1;
		goto clearup;
	}

	ip_size = aph_len_in_bd[aphlen];

	cipherTmpBlock[chnid].u32DataLen = dataTestLen + ip_size;
	cipherTmpBlock[chnid].pNextBlock = 0;
	cipherOutBlock[chnid].u32DataLen = dataTestLen;
	cipherOutBlock[chnid].pNextBlock = 0;
  
#if 1   
	memset_s((void*)cipherInBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE, 0,dataTestLen + 20);
	memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
	memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
#endif
	for(i = 0; i <(int) cipherInBlock[chnid].u32DataLen; i++)
		*((unsigned char*)(cipherInBlock[chnid].u32DataAddr + i)) = (unsigned char)i;
  
	s32Ret = mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",s32Ret,0,0,0,0);
		s32TestStatus = -1;
		goto clearup;
	}
  
	/*�������ҵ��*/
	g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
	g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
	g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
	g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = aphlen;
	g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_uplink_cfg[chnid].u32Count                    = u32Count;
	g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
	g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;    
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;   
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;   
	g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = CIPHER_SUBM_CALLBACK;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;

	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));             
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);
  
	/*�������ҵ��*/
	g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
	g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
	g_cipher_downlink_cfg[chnid].u8Direction                 = 0;
	g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
	g_cipher_downlink_cfg[chnid].u32Count                    = u32Count;
	g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
	g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;    
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;   
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;   
	g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = CIPHER_SUBM_CALLBACK;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;

	cipherTmpBlock[chnid].u32DataAddr += ip_size;

	/*������ܺ����������*/
	s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen,blk_num,blk_len);
	if(s32Ret != BSP_OK)
	{
		s32TestStatus = -1;
		goto clearup;
	}

	g_notify_stat[chnid] = CIPHER_STAT_OK;

	s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}

	osl_sem_down(&cipherChnCbSem[chnid]);

	if(g_notify_stat[chnid] != CIPHER_STAT_OK)
	{
		CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid]);
		s32TestStatus = -1;
		goto clearup;
	}

	osl_task_delay(1);
	s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
	if(s32Ret)
	{
		CIPHER_TEST_PRINT("data cmp fail.\n");
		s32TestStatus = -1;
		goto clearup;
	}

clearup:
	osl_free(blkChain);
	osl_free(blkChain2);
	cipherInBlock[chnid].u32DataLen -= ip_size;
	blk_len[0] -= ip_size;

	if(s32TestStatus == BSP_OK)
		CIPHER_TEST_PRINT("test pass.\n");
	else
		CIPHER_TEST_PRINT("test fail.\n");
	return s32TestStatus;
}

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128�����Ӱ�ͷ����Ϊ1Byte����Ӧ����ͷ��
* ������Countֵ�ĵ�5λ�������뱣����û�а�ͷ��һ�����ݰ������������Ϊ���飬��������СΪ200
*/
 int BSP_CIPHER_008_001()
 {
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32count = 0x353526;
    
    return  chain_encrypt_decrypt_aph((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_APPEND_HDR_BIT_TYPE_5, u32count);
 }
 
/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128�����Ӱ�ͷ����Ϊ1Byte����Ӧ����ͷ��
* ������Countֵ�ĵ�5λ, �����뱣����û�а�ͷ��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132��
* ���Ϊ����
*/
 int BSP_CIPHER_008_002()
 {
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {23,45,132};
    unsigned int dataTestLen = 200;
    unsigned int u32count = 0x353526;
    
    return  chain_encrypt_decrypt_aph((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_APPEND_HDR_BIT_TYPE_5, u32count);
 }

/*
* PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128�����Ӱ�ͷ����Ϊ1Byte����Ӧ����ͷ��
* ������Countֵ�ĵ�7λ�������뱣����û�а�ͷ��һ�����ݰ������������Ϊ���飬��������СΪ200
*/
  int BSP_CIPHER_008_003()
 {
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32count = 0x353526;
    
    return  chain_encrypt_decrypt_aph((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_APPEND_HDR_BIT_TYPE_7,u32count);
 }
 
 /*
 * PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128�����Ӱ�ͷ����Ϊ1Byte����Ӧ����ͷ��
 * ������Countֵ�ĵ�7λ, �����뱣����û�а�ͷ��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132��
 * ���Ϊ����
 */
 int BSP_CIPHER_008_004()
 {
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {23,45,132};
    unsigned int dataTestLen = 200;
    unsigned int u32count = 0x353526;
    
    return  chain_encrypt_decrypt_aph((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_APPEND_HDR_BIT_TYPE_7, u32count);
 }

 /*
 * PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128�����Ӱ�ͷ����Ϊ2Byte����Ӧ����ͷ��
 * ������Countֵ�ĵ�12λ�������뱣����û�а�ͷ��һ�����ݰ������������Ϊ���飬��������СΪ200
 */
 int BSP_CIPHER_008_005()
 {
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;
    unsigned int u32count = 0x353526;
    
    return  chain_encrypt_decrypt_aph((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_APPEND_HDR_BIT_TYPE_12,u32count);
 }
 
 /*
 * PDCP���м��ܵ��ͳ�����CIPHER_ALG_AES_128���ܣ���Կ����128�����Ӱ�ͷ����Ϊ2Byte����Ӧ����ͷ��
 * ������Countֵ�ĵ�12λ, �����뱣����û�а�ͷ��һ�����ݰ�������Ϊ3�飬���С�ֱ�Ϊ23��45��132��
 * ���Ϊ����
 */
 int BSP_CIPHER_008_006()
 {
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {23,45,132};
    unsigned int dataTestLen = 200;
    unsigned int u32count = 0x353526;
    
    return  chain_encrypt_decrypt_aph((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len,
                CIPHER_ALG_AES_128, CIPHER_KEY_L128,CIPHER_APPEND_HDR_BIT_TYPE_12, u32count);
 }

/* Purge��������*/
int chain_purge_prepare(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],CIPHER_ALGORITHM_E alg,
	CIPHER_KEY_LEN_E keyLen, CIPHER_SUBMIT_TYPE_E enSubmit)
{
	int s32TestStatus = BSP_OK;
    int s32Ret        = BSP_OK;
    int i             = 0;
    CIPHER_DATA_BLOCK* blkChain    = NULL;
    CIPHER_DATA_BLOCK* blkChain2   = NULL;
    unsigned char      u8Key[32]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    unsigned int       u32KeyIndex = 0x1;
    unsigned int       u32Private  = 0x0;

	cipherTestInit();

    /*�������ݼӽ��ܻ�����*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;
    cipherInBlock[chnid].pNextBlock = 0;

    blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    
    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret)
    {
        s32TestStatus = -1;
        goto clearup;
    }    

    cipherTmpBlock[chnid].u32DataLen = dataTestLen;
    cipherOutBlock[chnid].u32DataLen = dataTestLen;
  
    cipherTmpBlock[chnid].pNextBlock = 0;
    cipherOutBlock[chnid].pNextBlock = 0;
#if 1   
    memset_s((void*)cipherInBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE, 0,dataTestLen + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
#endif
    for(i = 0; i <(int) cipherInBlock[chnid].u32DataLen; i++)
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;

    s32Ret = mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);
    if(s32Ret != CIPHER_SUCCESS)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",s32Ret);
        s32TestStatus = -1;
        goto clearup;
    }

    /*�������ҵ��*/
    g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
    g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
    g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
    g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].u32Count                    = 0;
    g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;    
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;   
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;   
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;

    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));
    if(enSubmit == CIPHER_SUBM_CALLBACK)
    {        
        if(s32Ret != CIPHER_SUCCESS)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
            s32TestStatus = -1;
            goto clearup;
        }
/*        semTake(cipherChnCbSem[chnid],WAIT_FOREVER);*/
    }
    else
    {
        if(s32Ret != CIPHER_SUCCESS)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
            s32TestStatus = -1;
            goto clearup;
        }    
    }

    /*�������ҵ��*/
    g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
    g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
    g_cipher_downlink_cfg[chnid].u8Direction                 = 1;
    g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].u32Count                    = 0;
    g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;    
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;   
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;   
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;
    
    /*������ܺ����������*/
    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen,blk_num,blk_len);
    if(s32Ret != BSP_OK)
    {
        s32TestStatus = BSP_ERROR;
        goto clearup;
    }    

    g_notify_stat[chnid] = CIPHER_STAT_OK;
        
    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
    if(enSubmit == CIPHER_SUBM_CALLBACK)
    {        
        if(s32Ret != CIPHER_SUCCESS)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
            s32TestStatus = BSP_ERROR;
            goto clearup;
        }
/*        semTake(cipherChnCbSem[chnid],WAIT_FOREVER);*/
    }
    else
    {
        if(s32Ret != CIPHER_SUCCESS)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
            s32TestStatus = BSP_ERROR;
            goto clearup;
        }  
    }

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid]);
        s32TestStatus = -1;
        goto clearup;
    }
#if 0
    s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
    if(s32Ret != BSP_OK)
    {
        CIPHER_TEST_PRINT("data cmp fail.\n",0,0,0,0,0);
        s32TestStatus = BSP_ERROR;
        goto clearup;
    }
#endif
clearup:
    osl_free(blkChain);
    osl_free(blkChain2);
    if(s32TestStatus == BSP_OK)
    {
        CIPHER_TEST_PRINT("test pass.\n");
    }
    else
    {
        CIPHER_TEST_PRINT("test fail.\n"); 
    }
    return s32TestStatus;
}

/* �ύ�Ĳ�������ΪNONEʱ������Purge����*/
int BSP_CIPHER_009_001()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {10240};
    unsigned int dataTestLen = 10240; 
    int test_times = 0xa;

	cipherTestInit();

    submAttr = CIPHER_SUBM_NONE;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_purge_prepare((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("mdrv_cipher_purge_chan Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    s32Ret = mdrv_cipher_purge_chan(LTE_SECURITY_CHANNEL_NAS);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_purge_chan Test 1 fail,ret:0x%x\n",s32Ret);
        return s32Ret;
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return 0;
}

/* �ύ�Ĳ�������ΪNONEʱ������Purge����*/
int BSP_CIPHER_009_002()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {4096};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {3200, 800, 6240};
    unsigned int dataTestLen = 10240; 
    int test_times = 0xa;
    
	cipherTestInit();

    submAttr = CIPHER_SUBM_NONE;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_purge_prepare((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_192, CIPHER_KEY_L192, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("mdrv_cipher_purge_chan Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
            return s32Ret;
        }
    }

    s32Ret = mdrv_cipher_purge_chan(LTE_SECURITY_CHANNEL_NAS);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_purge_chan Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return s32Ret;
    }

    CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
    return BSP_OK;
}

/* �ύ�Ĳ�������ΪCallBackʱ������Purge����*/
int BSP_CIPHER_009_003()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {10*1024};
    unsigned int dataTestLen = 10240; 
    int test_times = 0xa;

    if(!g_cipher_test_inited)
    {
        cipherTestInit();
    }

    submAttr = CIPHER_SUBM_CALLBACK;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_purge_prepare((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("mdrv_cipher_purge_chan Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
            return s32Ret;
        }
    }

    s32Ret = mdrv_cipher_purge_chan(LTE_SECURITY_CHANNEL_NAS);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_purge_chan Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
        return s32Ret;
    }

    CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
    return BSP_OK;
}

/* �ύ�Ĳ�������ΪCallBackʱ������Purge����*/
int BSP_CIPHER_009_004()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {4096};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {240, 5000, 5000};
    unsigned int dataTestLen = 10240; 
    int test_times = 0x8;

    if(!g_cipher_test_inited)
    {
        cipherTestInit();
    }

    submAttr = CIPHER_SUBM_CALLBACK;

    for(i=0; i < test_times; i++)
    {
        s32Ret = chain_purge_prepare((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_192, CIPHER_KEY_L192, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("mdrv_cipher_purge_chan Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    s32Ret = mdrv_cipher_purge_chan(LTE_SECURITY_CHANNEL_NAS);
    if(CIPHER_SUCCESS != s32Ret)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_purge_chan Test 1 fail,ret:0x%x\n",s32Ret);
        return s32Ret;
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

int chain_encrypt_decrypt_multitype(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],CIPHER_ALGORITHM_E alg,
	CIPHER_KEY_LEN_E keyLen, CIPHER_SUBMIT_TYPE_E enSubmit)
{
    int s32TestStatus = BSP_OK;
    int s32Ret = BSP_OK;
    int i = 0;

    CIPHER_DATA_BLOCK* blkChain  = NULL;
    CIPHER_DATA_BLOCK* blkChain2 = NULL;
    unsigned char u8Key[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
                        18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    unsigned int u32KeyIndex = 0x1;
    unsigned int u32Private = 0x0;

	cipherTestInit();

    /*�������ݼӽ��ܻ�����*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;
    cipherInBlock[chnid].pNextBlock = 0;

    blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    
    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret)
    {
        s32TestStatus = -1;
        goto clearup;
    }    

    cipherTmpBlock[chnid].u32DataLen = dataTestLen;
    cipherOutBlock[chnid].u32DataLen = dataTestLen;
  
    cipherTmpBlock[chnid].pNextBlock = 0;
    cipherOutBlock[chnid].pNextBlock = 0;
#if 1   
    memset_s((void*)cipherInBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE, 0,dataTestLen + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
#endif
    for(i = 0; i <(int) cipherInBlock[chnid].u32DataLen; i++)
    {
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;
    }

    s32Ret = mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);
    if(s32Ret != CIPHER_SUCCESS)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",s32Ret);
        s32TestStatus = -1;
        goto clearup;
    }

    /*�������ҵ��*/
    g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
    g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
    g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
    g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].u32Count                    = 0;
    g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;    
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;   
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;

    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    /*�������ҵ��*/
    g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
    g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
    g_cipher_downlink_cfg[chnid].u8Direction                 = 0;
    g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].u32Count                    = 0;
    g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;    
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;   
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;   
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;

    /*������ܺ����������*/
    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen,blk_num,blk_len);
    if(s32Ret != BSP_OK)
    {
        s32TestStatus = BSP_ERROR;
        goto clearup;
    }    

    g_notify_stat[chnid] = CIPHER_STAT_OK;
        
    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid],0,0,0,0);
        s32TestStatus = -1;
        goto clearup;
    }
#if 1
    if((enSubmit == CIPHER_SUBM_CALLBACK) || (enSubmit == CIPHER_SUBM_BLK_HOLD))
    {
    	osl_task_delay(1);
        s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
        if(s32Ret)
        {
            CIPHER_TEST_PRINT("data cmp fail.\n",0,0,0,0,0);
            s32TestStatus = -1;
            goto clearup;
        }
    }
#endif
clearup:

    osl_free(blkChain);
    osl_free(blkChain2);
    if(s32TestStatus == BSP_OK)
    {
        CIPHER_TEST_PRINT("test pass.\n");
    }
    else
    {
        CIPHER_TEST_PRINT("test fail.\n"); 
    }
    return s32TestStatus;
}

/* �ύ����������͵Ĳ�����ʹ��CIPHER_ALG_AES_128����*/
int BSP_CIPHER_010_001()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    submAttr = CIPHER_SUBM_BLK_HOLD;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

/* �ύ����������͵Ĳ���*/
int BSP_CIPHER_010_002()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {120, 20, 60};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    submAttr = CIPHER_SUBM_BLK_HOLD;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

/* �ύ����������͵Ĳ�����ʹ��CIPHER_ALG_AES_192����*/
int BSP_CIPHER_010_003()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    submAttr = CIPHER_SUBM_BLK_HOLD;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_192, CIPHER_KEY_L192, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

int BSP_CIPHER_010_004()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {120, 20, 60};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    submAttr = CIPHER_SUBM_BLK_HOLD;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_192, CIPHER_KEY_L192, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

/* �ύ����������͵Ĳ�����ʹ��CIPHER_ALG_AES_256����*/
int BSP_CIPHER_010_005()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    submAttr = CIPHER_SUBM_BLK_HOLD;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_256, CIPHER_KEY_L256, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

int BSP_CIPHER_010_006()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {120, 20, 60};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    submAttr = CIPHER_SUBM_BLK_HOLD;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_256, CIPHER_KEY_L256, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}


/* �ύ���CIPHER_SUBM_NONE���͵Ĳ���*/
int BSP_CIPHER_010_007()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;
    unsigned int u32BDNumber = 0;
    unsigned int u32SourAddr = 0;
    unsigned int u32DestAddr = 0;
    CIPHER_NOTIFY_STAT_E enStatus = 0;
    unsigned int u32Private = 0;

    submAttr = CIPHER_SUBM_NONE;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    for(i=0; ;i++)
    {
        s32Ret = mdrv_cipher_get_cmplt_data(LTE_SECURITY_CHANNEL_NAS, &u32SourAddr, &u32DestAddr, 
                                             &enStatus, &u32Private);
        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("InValid RD\n");
        }
        else
        {
            u32BDNumber++;
            if(enStatus != CIPHER_STAT_OK)
            {
                CIPHER_TEST_PRINT("state Error 0x%x\n",enStatus);    
            }
        }
        
        if(0x10 == u32BDNumber)
        {
             break;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

/* �ύ���CIPHER_SUBM_NONE���͵Ĳ���*/
int BSP_CIPHER_010_008()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {120, 20, 60};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;
    unsigned int u32BDNumber = 0;
    unsigned int u32SourAddr = 0;
    unsigned int u32DestAddr = 0;
    CIPHER_NOTIFY_STAT_E enStatus = 0;
    unsigned int u32Private = 0;

    submAttr = CIPHER_SUBM_NONE;

    
    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
            return s32Ret;
        }
    }
    
    for(i=0; ;i++)
    {
        s32Ret = mdrv_cipher_get_cmplt_data(LTE_SECURITY_CHANNEL_NAS, &u32SourAddr, &u32DestAddr, 
                                             &enStatus, &u32Private);
        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("InValid RD\n",0,0,0,0,0);
        }
        else
        {
            u32BDNumber++;
            if(enStatus != CIPHER_STAT_OK)
            {
                CIPHER_TEST_PRINT("state Error 0x%x\n",enStatus,0,0,0,0);    
            }
        }
        
        if(0x10 == u32BDNumber)
        {
             break;
        }
    }
    
    CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
    return BSP_OK;
}

/* �ύ���CIPHER_SUBM_CALLBACK���͵Ĳ���*/
int BSP_CIPHER_010_009()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    submAttr = CIPHER_SUBM_CALLBACK;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("CALLBACK Test 1 fail,ret:0x%x i:%d\n",s32Ret, i);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

/* �ύ���CIPHER_SUBM_CALLBACK���͵Ĳ���*/
int BSP_CIPHER_010_010()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {120, 20, 60};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    submAttr = CIPHER_SUBM_CALLBACK;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x i:%d\n",s32Ret,i);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

/* NONE���ͺ�CallBack���ͻ���ύ*/
int BSP_CIPHER_010_011()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;

    if(!g_cipher_test_inited)
    {
        cipherTestInit();
    }

    s32LoopforMulti = 0;

    s32Ret = mdrv_cipher_register_notify_cb(cipherCbFunc_forMulti);
    if(s32Ret != BSP_OK)
    {
        CIPHER_TEST_PRINT("BSP_CIPHER_RegistNotifyCB faile,ret:0x%x\n",s32Ret,0,0,0,0);
    }

    submAttr = CIPHER_SUBM_NONE;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
            mdrv_cipher_register_notify_cb(cipherCbFunc);
            
            return s32Ret;
        }
    }

    submAttr = CIPHER_SUBM_CALLBACK;
    
    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
            mdrv_cipher_register_notify_cb(cipherCbFunc);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    mdrv_cipher_register_notify_cb(cipherCbFunc);
    return BSP_OK;

}

/* NONE���ͺ�CallBack���ͻ���ύ*/
int BSP_CIPHER_010_012()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200; 
    int test_times = 0x8;
    unsigned int u32BDNumber = 0;
    unsigned int u32SourAddr = 0;
    unsigned int u32DestAddr = 0;
    CIPHER_NOTIFY_STAT_E enStatus = 0;
    unsigned int u32Private = 0;

    submAttr = CIPHER_SUBM_CALLBACK;

    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
            return s32Ret;
        }
    }

    submAttr = CIPHER_SUBM_NONE;
    
    for(i=0; i<test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
            return s32Ret;
        }
    }

    for(i=0; ;i++)
    {
        s32Ret = mdrv_cipher_get_cmplt_data(LTE_SECURITY_CHANNEL_NAS, &u32SourAddr, &u32DestAddr, 
                                             &enStatus, &u32Private);
        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("InValid RD\n",0,0,0,0,0);
        }
        else
        {
            u32BDNumber++;
        }
        
        if(0x10 == u32BDNumber)
        {
             break;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
    return BSP_OK;
}

/* �ύ���CIPHER_SUBM_NONE���͵Ĳ���, һ�����ݰ����ֳ�18�飬���Ϊ����*/
int BSP_CIPHER_010_013()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num     = 18;
    unsigned int blk_len[]   = {23, 45, 132, 17, 46, 80, 1, 100, 101, 10, 20, 30, 40, 6, 1023, 1024, 23, 9};
    unsigned int dataTestLen = 2730;
    int test_times           = 0x8;
    unsigned int u32BDNumber = 0;
    unsigned int u32SourAddr = 0;
    unsigned int u32DestAddr = 0;
    CIPHER_NOTIFY_STAT_E enStatus = 0;
    unsigned int u32Private       = 0;

    submAttr = CIPHER_SUBM_NONE;
    
    for(i=0; i< test_times; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,
			LTE_SECURITY_CHANNEL_NAS, dataTestLen,blk_num,blk_len, 
			CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret,0,0,0,0);
            return s32Ret;
        }
    }
    
    for(i=0; ;i++)
    {
        s32Ret = mdrv_cipher_get_cmplt_data(LTE_SECURITY_CHANNEL_NAS, &u32SourAddr, &u32DestAddr, 
                                             &enStatus, &u32Private);
        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("InValid RD\n",0,0,0,0,0);
        }
        else
        {
            u32BDNumber++;
            if(enStatus != CIPHER_STAT_OK)
            {
                CIPHER_TEST_PRINT("state Error 0x%x\n",enStatus,0,0,0,0);    
            }
        }
        
        if(0x10 == u32BDNumber)
        {
             break;
        }
    }
    
    CIPHER_TEST_PRINT("test pass.\n",0,0,0,0,0);
    return BSP_OK;
}

int chain_encrypt_decrypt_multiTask(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen, CIPHER_SUBMIT_TYPE_E enSubmit)
{
    int s32TestStatus = BSP_OK;
    int s32Ret        = BSP_OK;
    int i             = 0;

    CIPHER_DATA_BLOCK* blkChain  = NULL;
    CIPHER_DATA_BLOCK* blkChain2 = NULL;
    unsigned int u32KeyIndex = 0x1;
    unsigned int u32Private = 0x0;

    cipherTestInit();

    /*�������ݼӽ��ܻ�����*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;
    cipherInBlock[chnid].pNextBlock = 0;

    blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    
    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret)
    {
        s32TestStatus = -1;
        goto clearup;
    }

    cipherTmpBlock[chnid].u32DataLen = dataTestLen;
    cipherOutBlock[chnid].u32DataLen = dataTestLen;

    cipherTmpBlock[chnid].pNextBlock = 0;
    cipherOutBlock[chnid].pNextBlock = 0;
#if 1
    memset_s((void*)cipherInBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE, 0,dataTestLen + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
#endif
    for(i = 0; i < (int)cipherInBlock[chnid].u32DataLen; i++)
    {
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;
    }

    /*�������ҵ��*/
    g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
    g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
    g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
    g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].u32Count                    = 0;
    g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;
     
    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));             
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    /*�������ҵ��*/
    g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
    g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
    g_cipher_downlink_cfg[chnid].u8Direction                 = 0;
    g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].u32Count                    = 0;
    g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;
    
    /*������ܺ����������*/
    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen,blk_num,blk_len);
    if(s32Ret)
    {
        s32TestStatus = -1;
        goto clearup;
    }    

    g_notify_stat[chnid] = CIPHER_STAT_OK;
        
    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid]);
        s32TestStatus = -1;
        goto clearup;        
    }

	udelay(100);
    s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
    if(s32Ret)
    {
        CIPHER_TEST_PRINT("data cmp fail.\n");
        s32TestStatus = -1;
        goto clearup;
    }

clearup:
    osl_free(blkChain);
    osl_free(blkChain2);
    if(s32TestStatus == BSP_OK)
		CIPHER_TEST_PRINT("test pass.\n");
    else
        CIPHER_TEST_PRINT("test fail.\n");
    return s32TestStatus;
}

int chain_encrypt_decrypt_multiTask_onechn(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen, CIPHER_SUBMIT_TYPE_E enSubmit)
{
    int s32TestStatus = 0;
    int s32Ret        = 0;
    int i             = 0;
    CIPHER_DATA_BLOCK* blkChain    = NULL;
    CIPHER_DATA_BLOCK* blkChain2   = NULL;
    unsigned int       u32KeyIndex = 0x1;
    unsigned int       u32Private  = 0x0;

    cipherTestInit();

    /*�������ݼӽ��ܻ�����*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;
    cipherInBlock[chnid].pNextBlock = 0;

    blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    
    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret != BSP_OK)
    {
        s32TestStatus = BSP_ERROR;
        goto clearup;
    }    

    cipherTmpBlock[chnid].u32DataLen = dataTestLen;
    cipherOutBlock[chnid].u32DataLen = dataTestLen;
    cipherTmpBlock[chnid].pNextBlock = 0;
    cipherOutBlock[chnid].pNextBlock = 0;

    memset_s((void*)cipherInBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE, 0,dataTestLen + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE,0,dataTestLen + 20);

    for(i = 0; i < (int)cipherInBlock[chnid].u32DataLen; i++)
    {
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;
    }

    /*�������ҵ��*/
    g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
    g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
    g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
    g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].u32Count                    = 0;
    g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;
     
    s32Ret = mdrv_cipher_set_bdinfo(PDCP_SIGNAL_CHN, 1, &(g_cipher_uplink_cfg[chnid]));             
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    /*�������ҵ��*/
    g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
    g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
    g_cipher_downlink_cfg[chnid].u8Direction                 = 0;
    g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].u32Count                    = 0;
    g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;

    /*������ܺ����������*/
    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen,blk_num,blk_len);
    if(s32Ret != BSP_OK)
    {
        s32TestStatus = BSP_ERROR;
        goto clearup;
    }

    g_notify_stat[chnid] = CIPHER_STAT_OK;

    s32Ret = mdrv_cipher_set_bdinfo(PDCP_SIGNAL_CHN, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid],0,0,0,0);
        s32TestStatus = -1;
        goto clearup;
    }

	udelay(100);
    if((enSubmit == CIPHER_SUBM_CALLBACK) || (enSubmit == CIPHER_SUBM_BLK_HOLD))
    {
        s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
        if(s32Ret != BSP_OK)
        {
            CIPHER_TEST_PRINT("data cmp fail.\n");
            s32TestStatus = -1;
            goto clearup;
        }
    }

clearup:

    osl_free(blkChain);
    osl_free(blkChain2);
    if(s32TestStatus == BSP_OK)
    {
        CIPHER_TEST_PRINT("test pass.\n");
    }
    else
    {
        CIPHER_TEST_PRINT("test fail.\n");
    }
    return s32TestStatus;
}

void pdcp_data_taskEntry(void * para)
{
   int i = 0;
   unsigned int blk_num     = 1;
   unsigned int blk_len[]   = {1500};
   unsigned int dataTestLen = 1500;
   struct cipher_stress_tsk_para * tsk_pa = (struct cipher_stress_tsk_para *)para;

   for(i = 0; i < (int)tsk_pa->loops; i++)
   {
		chain_encrypt_decrypt_multiTask((unsigned char*)__FUNCTION__,tsk_pa->chnid, dataTestLen,blk_num,blk_len,
			CIPHER_ALG_AES_128, CIPHER_KEY_L128, tsk_pa->enSubmit);
   }
   tsk_pa->bDone = 1;
}

void pdcp_data_taskEntry_onechn(void * para)
{
   int i = 0;
   unsigned int blk_num     = 1;
   unsigned int blk_len[]   = {1500};
   unsigned int dataTestLen = 1500;
   int s32Ret;
   struct cipher_stress_tsk_para * tsk_pa = (struct cipher_stress_tsk_para *)para;

   for(i = 0; i < (int)tsk_pa->loops; i++)
   {
		s32Ret = chain_encrypt_decrypt_multiTask_onechn((unsigned char*)__FUNCTION__,tsk_pa->chnid, dataTestLen,blk_num,blk_len,
			CIPHER_ALG_AES_128, CIPHER_KEY_L128, tsk_pa->enSubmit);

		if(BSP_OK != s32Ret)
		{
			CIPHER_TEST_PRINT("test fail.s32Ret = 0x%x\n",s32Ret);
			break;
		}
	}
	tsk_pa->bDone = 1;
}

void pdcp_data_taskEntry2(void * para)
{
   int i = 0;
   unsigned int blk_num = 1500;/*CD��������512�����ⶼ�趨����ô��!!!!!*/
   unsigned int blk_len[1500] = {0};
   unsigned int dataTestLen = 1500;
   unsigned int chnid      = (unsigned int)*((int*)para + 0);
   unsigned int test_times = (unsigned int)*((int*)para + 1);
   int* pbDone = (int*)*((int*)para + 2);
   CIPHER_SUBMIT_TYPE_E enSubmit = (CIPHER_SUBMIT_TYPE_E)*((int*)para + 3);

   for(i = 0; i < (int)blk_num; i++)
   {
       blk_len[i] = 1;
   }

   for(i = 0; i < (int)test_times; i++)
   {
       chain_encrypt_decrypt_multiTask((unsigned char*)__FUNCTION__,chnid, dataTestLen,blk_num,blk_len,
                        CIPHER_ALG_AES_128, CIPHER_KEY_L128, enSubmit);
   }
   if(pbDone != NULL)
   {
       *pbDone = BSP_TRUE;
   }
}

/*
* PDCP����˫ͨ��˫���񲢷���ÿ��ͨ��������мӽ��ܲ���
*/
static struct cipher_stress_tsk_para tsk_in_para[PDCP_DATA_TASK_NUM] =
{
	{.chnid    = PDCP_DATA_CHN_1,
	 .loops    = 1000,
	 .bDone    = 0,
	 .enSubmit = CIPHER_SUBM_CALLBACK
	},
	{.chnid    = PDCP_DATA_CHN_2,
	 .loops    = 1000,
	 .bDone    = 0,
	 .enSubmit = CIPHER_SUBM_CALLBACK
	}
};
int BSP_CIPHER_011_001()
{
	int ret = 0;
	int i = 0,j = 0;
	OSL_TASK_ID taskId[PDCP_DATA_TASK_NUM];
	int testStatus = 0;
	unsigned char* taskName[] = {(unsigned char*)"pdcp_data_task1",(unsigned char*)"pdcp_data_task2"};

	cipherTestInit();
	tsk_in_para[0].bDone = 0;
	tsk_in_para[1].bDone = 0;

	for(i = 0; i < PDCP_DATA_TASK_NUM; i++)
	{
		ret = osl_task_init((char*)taskName[i], TEST_TASK_PRIORITY, TEST_TASK_STACK_SIZE,
			(OSL_TASK_FUNC)pdcp_data_taskEntry, &tsk_in_para[i], &taskId[i]);
		if(ret)
		{
			testStatus = -1;
			for(j = 0; j < i; j++)
				osl_task_delete(&taskId[j]);
		}
	}

	while(1)
	{
		osl_task_delay(10);
		if((tsk_in_para[0].bDone == BSP_TRUE) && (tsk_in_para[1].bDone == BSP_TRUE))
		{
			break;
		}
	}

	for(i = 0; i < PDCP_DATA_TASK_NUM; i++)
		osl_task_delete(&taskId[i]);

	return testStatus;
}

/*
 * PDCP����˫ͨ��˫���񲢷���ÿ��ͨ��������мӽ��ܲ���
 * CD���趨Ϊ1500�������ض�����
 */
int BSP_CIPHER_012_001()
{
   int i = 0,j = 0;
   OSL_TASK_ID    taskId[PDCP_DATA_TASK_NUM];
   int    test_times = 1000;
   int testStatus = BSP_OK;
   int bDone[] = {BSP_FALSE,BSP_FALSE};
   unsigned int chnid[] = {PDCP_DATA_CHN_1,PDCP_DATA_CHN_2};
   unsigned char* taskName[] = {(unsigned char*)"pdcp_data_task1",(unsigned char*)"pdcp_data_task2"};
   CIPHER_SUBMIT_TYPE_E enSubmit = CIPHER_SUBM_CALLBACK;
   int tsk_param[4] = {0};
   int ret = 0;

   cipherTestInit();

   for(i = 0; i < PDCP_DATA_TASK_NUM; i++)
   {
		tsk_param[0] = chnid[i];
		tsk_param[1] = test_times;
		tsk_param[2] = (int)&bDone[i];
		tsk_param[3] = (int)enSubmit;
		ret = osl_task_init((char*)taskName[i], TEST_TASK_PRIORITY, TEST_TASK_STACK_SIZE,
			(OSL_TASK_FUNC)pdcp_data_taskEntry2, tsk_param, &taskId[i]);
		if(ret)
		{
			testStatus = -1;
			for(j = 0; j < i; j++)
				osl_task_delete(&taskId[j]);
		}
   }

   while(1)
   {
       osl_task_delay(10);
       if((bDone[0] == BSP_TRUE)||(bDone[1] == BSP_TRUE))
            break;
   }
   
   for(i = 0; i < PDCP_DATA_TASK_NUM; i++)
       osl_task_delete(&taskId[i]);

   return testStatus;
}

/*
* PDCP���ݵ�ͨ�������񲢷���ͨ�����мӽ��ܲ���
*/
static struct cipher_stress_tsk_para tsk_in_para_013_001[PDCP_DATA_TASK_NUM] =
{
	{.chnid    = PDCP_SIGNAL_CHN,
	 .loops    = 1000,
	 .bDone    = 0,
	 .enSubmit = CIPHER_SUBM_CALLBACK
	},
	{.chnid    = PDCP_DATA_CHN_1,
	 .loops    = 1000,
	 .bDone    = 0,
	 .enSubmit = CIPHER_SUBM_CALLBACK
	}
};
int BSP_CIPHER_013_001()
{
   int i = 0,j = 0;
   OSL_TASK_ID    taskId[PDCP_DATA_TASK_NUM];
   int testStatus = BSP_OK;
   unsigned char* taskName[] = {(unsigned char*)"pdcp_data_task1",(unsigned char*)"pdcp_data_task2"};
   int ret = 0;

   cipherTestInit();

   for(i = 0; i < PDCP_DATA_TASK_NUM; i++)
   {
		ret = osl_task_init((char*)taskName[i], TEST_TASK_PRIORITY, TEST_TASK_STACK_SIZE,
			(OSL_TASK_FUNC)pdcp_data_taskEntry_onechn, &tsk_in_para_013_001[i], &taskId[i]);
		if(ret)
		{
			CIPHER_TEST_PRINT("fail to create tsk %s\n", taskName[i]);
			testStatus = -1;
			for(j = 0; j < i; j++)
				osl_task_delete(&taskId[j]);
		}
   }

   while(1)
   {
		osl_task_delay(10);
		if(0 == tsk_in_para_013_001[0].bDone)
			CIPHER_TEST_PRINT("tsk running : %s\n", taskName[0]);
		if(0 == tsk_in_para_013_001[1].bDone)
			CIPHER_TEST_PRINT("tsk running : %s\n", taskName[1]);
		if((1 == tsk_in_para_013_001[0].bDone) && (1 == tsk_in_para_013_001[1].bDone))
			break;
   }

   for(i = 0; i < PDCP_DATA_TASK_NUM; i++)
       osl_task_delete(&taskId[i]);

   return testStatus;
}

void cipher_hold_taskEntry_longtime(int* pbDone)
{
   int i = 0;
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {1500};
   unsigned int dataTestLen = 1500;
   int s32Ret;

   for(i = 0; ; i++)
   {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, CIPHER_SUBM_BLK_HOLD);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("cipher_hold_taskEntry_longtime fail,ret:0x%x\n",s32Ret,0,0,0,0);
            break;
        }

        if(0x0 == (i % 0x10))
        {
            osl_task_delay(0);
        }
   }
   *pbDone = BSP_TRUE;   
}

void cipher_callback_taskEntry_longtime(void * para)
{
   int i = 0;
   unsigned int blk_num = 1;
   unsigned int blk_len[] = {1500};
   unsigned int dataTestLen = 1500;
   int s32Ret;
   unsigned int chnid      = (unsigned int)*((int*)para + 0);
   //unsigned int test_times = (unsigned int)*((int*)para + 1);
   int* pbDone = (int*)*((int*)para + 2);
   CIPHER_SUBMIT_TYPE_E enSubmit = (CIPHER_SUBMIT_TYPE_E)*((int*)para + 3);

   for(i = 0; ; i++)
   {
        s32Ret = chain_encrypt_decrypt_multiTask((unsigned char*)__FUNCTION__, chnid, dataTestLen,blk_num,blk_len,
                        CIPHER_ALG_AES_128, CIPHER_KEY_L128, enSubmit);
        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("cipher_callback_taskEntry_longtime fail,ret:0x%x\n",s32Ret,0,0,0,0);
            break;
        }

        if(0x0 == (i % 0x10))
        {
            osl_task_delay(0);
        }
        
   }
   *pbDone = BSP_TRUE;
}

/* ѹ������*/
int BSP_CIPHER_014_001()
{
   int i = 0,j = 0;
   OSL_TASK_ID    taskId[3];
   int    test_times = 1000;
   int testStatus = BSP_OK;
   int bDone[] = {BSP_FALSE,BSP_FALSE,BSP_FALSE};
   unsigned int chnid[] = {PDCP_SIGNAL_CHN, PDCP_DATA_CHN_1, PDCP_DATA_CHN_2};
   unsigned char* taskName[] = {(unsigned char*)"ltask1",(unsigned char*)"ltask2",(unsigned char*)"ltask3"};
   CIPHER_SUBMIT_TYPE_E enSubmit = CIPHER_SUBM_CALLBACK;
   int tsk_param[3][4];

   cipherTestInit();

   for(i = 0; i < 0x3; i++)
   {
		if(0x0 == i)
		{
	   		testStatus = osl_task_init((char*)taskName[i], TEST_TASK_PRIORITY, TEST_TASK_STACK_SIZE,
				(OSL_TASK_FUNC)cipher_hold_taskEntry_longtime, &bDone[i], &taskId[i]);
		}
		if((1 == i) || (2 == i))
		{
			tsk_param[i][0] = chnid[i];
			tsk_param[i][1] = test_times;
			tsk_param[i][2] = (int)&bDone[i];
			tsk_param[i][3] = enSubmit;
	   		testStatus = osl_task_init((char*)taskName[i], TEST_TASK_PRIORITY, TEST_TASK_STACK_SIZE,
				(OSL_TASK_FUNC)cipher_callback_taskEntry_longtime, &tsk_param[i], &taskId[i]);
		}

       if(taskId[i] == 0)
       {
          testStatus = BSP_ERROR;
          for(j = 0; j < i; j++)
              osl_task_delete(&taskId[j]);
       }
   }

   while(1)
   {
       osl_task_delay(10);
       if((bDone[0] == BSP_TRUE) || (bDone[1] == BSP_TRUE) || (bDone[2] == BSP_TRUE))
       {
            CIPHER_TEST_PRINT("long time Test fail,ret:0x%x\n",0,0,0,0,0);
            break;
       }
   }

#if 0
   for(i = 0; i < PDCP_DATA_TASK_NUM; i++)
   {
       osl_task_delete(taskId[i]);
   }
/*
   printf("g_curOptId[PDCP_DATA_CHN_1]:%d\n",g_curOptId[PDCP_DATA_CHN_1]);
   printf("g_curOptId[PDCP_DATA_CHN_2]:%d\n",g_curOptId[PDCP_DATA_CHN_2]);
*/
#endif

   return testStatus;
}

/* �ύ���CIPHER_SUBM_CALLBACK���͵Ĳ���*/
int BSP_CIPHER_014_002()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr = CIPHER_SUBM_CALLBACK;
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
    unsigned int dataTestLen = 200;

    cipherTestInit();

    for(i=0; ; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("CALLBACK Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

}

/* �ύ����������͵Ĳ���*/
int BSP_CIPHER_014_003()
{
    int i = 0;
    int s32Ret;
    CIPHER_SUBMIT_TYPE_E submAttr = CIPHER_SUBM_BLK_HOLD;
/*
    unsigned int blk_num = 1;
    unsigned int blk_len[] = {200};
*/
    unsigned int blk_num = 3;
    unsigned int blk_len[] = {120, 20, 60};
    unsigned int dataTestLen = 200;

    cipherTestInit();

    for(i=0; ; i++)
    {
        s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,LTE_SECURITY_CHANNEL_NAS, 
                dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, submAttr);

        if(BSP_OK != s32Ret)
        {
            CIPHER_TEST_PRINT("BSP_CIPHER_Purge Test 1 fail,ret:0x%x\n",s32Ret);
            return s32Ret;
        }
    }

    CIPHER_TEST_PRINT("test pass.\n");
    return BSP_OK;
}

/*cipher aes test*/
int BSP_CIPHER_015_001(void)
{
	int loop = 1000;
	int by_pass;
	int ret;

	/*enable aes accelerate*/
	by_pass = 0;
	ret = cipher_test_ul_aes256_channel_srb(loop, by_pass);
	if (ret)
		return CIPHER_CHECK_ERROR;

	/*disable aes accelerate*/
	by_pass = 1;
	ret = cipher_test_ul_aes256_channel_srb(loop, by_pass);
	if (ret)
		return CIPHER_CHECK_ERROR;

	return CIPHER_SUCCESS;	
}


void cipher_test_build_pscfg_basic(CIPHER_SINGLE_CFG_S *ps_cfg)
{
	//ps_cfg->enOpt			=	CIPHER_OPT_ENCRYPT;
	ps_cfg->u8BearId		=	0;	
	ps_cfg->u8Direction		=	1;
	ps_cfg->enAppdHeaderLen = 	CIPHER_HDR_BIT_TYPE_0;
	ps_cfg->enHeaderLen     = 	CIPHER_HDR_BIT_TYPE_0;
	ps_cfg->u32Count        = 	0;	
	ps_cfg->bMemBlock       = 	0;
	ps_cfg->u32BlockLen     = 	0;
	//ps_cfg->stAlgKeyInfo.u32KeyIndexSec = 1;
	ps_cfg->stAlgKeyInfo.u32KeyIndexInt = 0;
	//ps_cfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128;	
	ps_cfg->stAlgKeyInfo.enAlgIntegrity = 0;	
	//ps_cfg->enSubmAttr      = 	CIPHER_SUBM_NONE;
	ps_cfg->u32Private      = 	0;		
	//ps_cfg->pInMemMgr       = 	cipher_test_input_mem;
	//ps_cfg->pOutMemMgr      = 	cipher_test_encrypt_output_mem;
	ps_cfg->usr_field1		= 	0;
	ps_cfg->usr_field2		= 	0;
	ps_cfg->usr_field3		=	0;
}

void cipher_test_set_pscfg_opt(CIPHER_SINGLE_CFG_S *ps_cfg, 
			CIPHER_SINGLE_OPT_E en_opt, int key_idx, CIPHER_ALGORITHM_E alg_sec,
			CIPHER_SUBMIT_TYPE_E en_sub)
{
	int ret;
	void *real_key;
	char key[32]   = {1,  2, 3, 4, 5, 6, 7, 8, 9,10,
					  11,12,13,14,15,16,17,18,19,20,
					  21,22,23,24,25,26,27,28,29,30,
					  31,32};

	
	ps_cfg->enOpt			=	en_opt;
	ps_cfg->stAlgKeyInfo.u32KeyIndexSec = key_idx;
	ps_cfg->stAlgKeyInfo.enAlgSecurity  = alg_sec;
	ps_cfg->enSubmAttr      = 	en_sub;
	
	if (key_idx == 0) {
		real_key = key;
	} else {
		real_key = (key + 16);
	}
	
	ret = mdrv_cipher_set_key(real_key, CIPHER_KEY_L128, key_idx);
    if(ret != CIPHER_SUCCESS)
    {
        CIPHER_TEST_PRINT("mdrv_cipher_set_key fail,ret:0x%x\n",ret);
    }

}

void cipher_test_set_cd_end(struct lup_mem_st *cd_head, int cd_gap)
{
	int i;
	struct lup_mem_st *cd = cd_head;

	for (i = 0; i < cd_gap - 1; i++) {
		cd = cd->pnext;
	}

	cd->pnext = NULL;
}

void cipher_test_set_single_block(CIPHER_SINGLE_CFG_S *ps_cfg, int blk_len, void* in_mem, void* out_mem)
{
	ps_cfg->bMemBlock       = 	1;
	ps_cfg->u32BlockLen     = 	blk_len;
	ps_cfg->pInMemMgr		=	in_mem;
	ps_cfg->pOutMemMgr		=	out_mem;
}

void cipher_test_set_cd_list(CIPHER_SINGLE_CFG_S *ps_cfg, void* in_mem, 
				void* out_mem, int cd_gap)
{
	ps_cfg->bMemBlock       = 	0;
	ps_cfg->u32BlockLen     = 	0;
	ps_cfg->pInMemMgr		=	in_mem;
	ps_cfg->pOutMemMgr		=	out_mem;
	cipher_test_set_cd_end((struct lup_mem_st *)in_mem, cd_gap);
}

//only for channel 1
int cipher_test_bd_init(void)
{
	unsigned int dp_offset,dl_offset,pn_offset;
	CIPHER_SINGLE_CFG_S *ps_cfg;
	unsigned char *input_data;
	unsigned char *output_data;
	unsigned int i;
	struct lup_mem_st *cdlist_input;
	struct lup_mem_st *cdlist_input_head;
	struct lup_mem_st *cdlist_output;
	struct lup_mem_st *cdlist_output_head;
	unsigned int data_len = sizeof(unsigned int);
	unsigned int output_size;
	
	if (cipher_test_init_flag) {
		return cipher_test_init_flag;
	}
	
	dp_offset = offsetof(struct lup_mem_st, data_ptr);
	dl_offset = offsetof(struct lup_mem_st, size);
	pn_offset = offsetof(struct lup_mem_st, pnext);

	cipher_test_data_ptr = osl_cachedma_malloc(CIPHER_TEST_CD_NUM_CHN1* sizeof(unsigned int));
	cipher_test_ps_cfg_head	= osl_cachedma_malloc(CIPHER_TEST_PS_NUM_CHN1* sizeof(CIPHER_SINGLE_CFG_S));
	cipher_test_decrypt_output_mem = osl_cachedma_malloc(CIPHER_TEST_CD_NUM_CHN1 * sizeof(unsigned int));
	cipher_test_encrypt_output_mem = osl_cachedma_malloc(CIPHER_TEST_PS_NUM_CHN1 * CIPHER_TEST_CD_NUM_CHN1 * sizeof(unsigned int));
	cipher_test_cdlist_output = osl_cachedma_malloc(CIPHER_TEST_PS_NUM_CHN1 * sizeof(struct lup_mem_st));
	cipher_test_input_mem = osl_cachedma_malloc(CIPHER_TEST_CD_NUM_CHN1 * sizeof(struct lup_mem_st));
	cipher_test_ps_rd	=	(CIPHER_RD_INFO_S *)osl_cachedma_malloc(CIPHER_TEST_PS_NUM_CHN1 * sizeof(CIPHER_RD_INFO_S));

	cdlist_output_head = (struct lup_mem_st *)cipher_test_cdlist_output;
	cdlist_output = cdlist_output_head;
	output_data = (unsigned char *)cipher_test_encrypt_output_mem;
	output_size = CIPHER_TEST_CD_NUM_CHN1 * sizeof(unsigned int);
	for (i = 0; i < CIPHER_TEST_PS_NUM_CHN1 - 1; i++) {
		cdlist_output->pnext = cdlist_output_head + i + 1;
		cdlist_output->size = output_size;
		cdlist_output->data_ptr = output_data + i * output_size;
		cdlist_output = cdlist_output->pnext;
	}
	
	/* The last cdlist output chain pointed to the head */
	cdlist_output->pnext = cdlist_output_head;
	cdlist_output->size = output_size;
	cdlist_output->data_ptr = output_data + (CIPHER_TEST_PS_NUM_CHN1 - 1) * output_size;
	

	memset_s(cipher_test_data_ptr,CIPHER_TEST_CD_NUM_CHN1 * sizeof(unsigned int),5,CIPHER_TEST_CD_NUM_CHN1 * sizeof(unsigned int) + 20);
	cdlist_input_head  = (struct lup_mem_st *)cipher_test_input_mem;
	cdlist_input = cdlist_input_head;
	input_data	= (unsigned char *)cipher_test_data_ptr;
	for (i = 0; i < CIPHER_TEST_CD_NUM_CHN1 - 1; i++) {
		cdlist_input->pnext = cdlist_input_head + i + 1;
		cdlist_input->size = data_len;
		cdlist_input->data_ptr = input_data + (i * data_len);
		cdlist_input = cdlist_input->pnext;
	}

	/* The last cdlist input chain pointed to the head */
	cdlist_input->pnext = cdlist_input_head;
	cdlist_input->size = data_len;
	cdlist_input->data_ptr = input_data + ((CIPHER_TEST_CD_NUM_CHN1 - 1) * data_len);
	
	ps_cfg 	= (CIPHER_SINGLE_CFG_S *)cipher_test_ps_cfg_head;
	for (i = 0; i < CIPHER_TEST_PS_NUM_CHN1; i++, ps_cfg++) {
		cipher_test_build_pscfg_basic(ps_cfg);
	}

	(void)mdrv_cipher_set_dbuf_para(CIPHER_SECURITY_CHANNEL_1, 0x0, dp_offset, dl_offset, pn_offset);
	(void)mdrv_cipher_set_dbuf_para(CIPHER_SECURITY_CHANNEL_1, 0x1, dp_offset, dl_offset, pn_offset);

#ifdef CIPHER_DEBUG_BD_CD_QUEUE
	cipher_module_ctl.idx_dbg_chn = CIPHER_SECURITY_CHANNEL_1;
#endif

	cipher_test_init_flag = 1;

	return cipher_test_init_flag;
}

void cipher_test_cd_recover(void)
{
	struct lup_mem_st *cd;
	struct lup_mem_st *cd_head;
	unsigned int *cdq;
	int i;
	unsigned int data_len;
	
	data_len = sizeof(unsigned int);
	cd_head  = (struct lup_mem_st *)cipher_test_input_mem;
	cd = cd_head;
	cdq	= (unsigned int *)cipher_test_data_ptr;
	for (i = 0; i < CIPHER_TEST_CD_NUM_CHN1 - 1; i++) {
		cd->pnext = cd_head + i + 1;
		cd->size = data_len;
		cd->data_ptr = (unsigned char *)(cdq + i);
		cd = cd->pnext;
	}

	cd->pnext = cd_head;
	cd->size = data_len;
	cd->data_ptr = (unsigned char *)(cdq + CIPHER_TEST_CD_NUM_CHN1 - 1);
}

int cipher_test_bd_cdlist(int bd_num, int cd_num)
{	
	int ret;
	int i;
	int chn_id;
	struct lup_mem_st *cd_input;
	struct lup_mem_st *cd_output;
	CIPHER_SINGLE_CFG_S *ps_cfg_head;
	CIPHER_SINGLE_CFG_S *ps_cfg;

	(void)cipher_test_bd_init();
	
	cd_input = (struct lup_mem_st *)cipher_test_input_mem;
	cd_output = (struct lup_mem_st *)cipher_test_cdlist_output;
	ps_cfg_head = (CIPHER_SINGLE_CFG_S *)cipher_test_ps_cfg_head;
	ps_cfg = ps_cfg_head;
	chn_id = CIPHER_SECURITY_CHANNEL_1;

	cipher_test_cd_recover();
	for (i = 0; i < bd_num; i++) {
		cipher_test_set_cd_list(ps_cfg, (void *)cd_input, (void *)cd_output, cd_num);			//cd list
		cipher_test_set_pscfg_opt(ps_cfg, CIPHER_OPT_ENCRYPT, 1, CIPHER_ALG_AES_128, CIPHER_SUBM_NONE);
		cd_input += cd_num;
		cd_output++;
		ps_cfg++;
	}
	
	ret = mdrv_cipher_set_bdinfo(chn_id, bd_num, ps_cfg_head);
	cipher_test_cd_recover();
	
	return ret;
}

int cipher_test_bd_single_block(int bd_num, int blk_len)
{	
	int ret;
	int i;
	int chn_id;
	void *input;
	void *output;
	CIPHER_SINGLE_CFG_S *ps_cfg_head;
	CIPHER_SINGLE_CFG_S *ps_cfg;

	(void)cipher_test_bd_init();

	input = cipher_test_data_ptr;
	output = cipher_test_encrypt_output_mem;
	ps_cfg_head = (CIPHER_SINGLE_CFG_S *)cipher_test_ps_cfg_head;
	ps_cfg = ps_cfg_head;
	chn_id = CIPHER_SECURITY_CHANNEL_1;	

	//max bd_num = 320*4/32 = 40
	for (i = 0; i < bd_num; i++) {
		cipher_test_set_single_block(ps_cfg,blk_len, input, output);	//single block
		cipher_test_set_pscfg_opt(ps_cfg, CIPHER_OPT_ENCRYPT, 1, CIPHER_ALG_AES_128, CIPHER_SUBM_NONE);
		input += blk_len;
		output += blk_len;
		ps_cfg++;
	}
	
	ret = mdrv_cipher_set_bdinfo(chn_id, bd_num, ps_cfg_head);
	
	return ret;
}

int cipher_test_rd_handler(unsigned int rd_num, int chn_id)
{	
	CIPHER_RD_INFO_S *ps_rd = cipher_test_ps_rd;
	int ret;

	(void)osl_task_delay(1);
	ret = mdrv_cipher_get_rdinfo(chn_id, ps_rd, &rd_num);

	return ret;
}

/* BD queue */
int cipher_test_bd_queue(void)
{	
	int ret;
	int i;
	int bd_num;

	(void)cipher_test_bd_init();
	
	ret = cipher_test_rd_handler(CIPHER_TEST_PS_NUM_CHN1, CIPHER_SECURITY_CHANNEL_1);
	if ((ret != CIPHER_RDQ_NULL) && (ret != CIPHER_SUCCESS)) {
		cipher_test_print("[Clear RD]error code:0x%x\n", ret);
		return ret;
	}
	
	/* BD mode*/	
	ret = cipher_test_bd_cdlist(32,1);
	if (ret != CIPHER_FIFO_FULL) {
		cipher_test_print("[BD mode]error code:0x%x\n", ret);
		return ret;
	} else if (ret == CIPHER_FIFO_FULL) {
		cipher_test_print("cipher test bd full succeed!\n");
	}
	
	/* CD mode */
	ret = cipher_test_bd_cdlist(31,11);
	if (ret != CIPHER_FIFO_FULL) {
		cipher_test_print("[CD mode]error code:0x%x\n", ret);
		return ret;
	} else if (ret == CIPHER_FIFO_FULL) {
		cipher_test_print("cipher test cd full succeed!\n");
	}

	/* Single BD mode */
	ret = cipher_test_bd_single_block(32,8);
	if (ret != CIPHER_FIFO_FULL) {
		cipher_test_print("[Single BD mode]error code:0x%x\n", ret);
		return ret;
	} else if (ret == CIPHER_FIFO_FULL) {
		cipher_test_print("cipher test single block BD full succeed!\n");
	}

	/* Hybrid mode */
	for (i = 0; i < 30; i++) {
		bd_num = mdrv_cipher_get_bd_num(CIPHER_SECURITY_CHANNEL_1,BD_TYPE_FREE);
	    if (bd_num <= 0 )
	    {
	        cipher_test_print("[Hybrid mode]Get BD num for CD list error!bd num:0x%x\n", bd_num);
	        return CIPHER_FIFO_FULL;
	    }
		
		ret = cipher_test_bd_cdlist(bd_num,5);
		if (ret) {
			cipher_test_print("[Hybrid mode]CD list error code:0x%x, bd num:%d\n", ret, bd_num);
			return ret;
		}

		ret = cipher_test_rd_handler(CIPHER_TEST_PS_NUM_CHN1, CIPHER_SECURITY_CHANNEL_1);
		if (ret) {
			cipher_test_print("[Get RD]For CD list,error code:0x%x, bd num:%d\n", ret, bd_num);
			return ret;
		}

		bd_num = mdrv_cipher_get_bd_num(CIPHER_SECURITY_CHANNEL_1,BD_TYPE_FREE);
	    if (bd_num <= 0 )
	    {
	        cipher_test_print("[Hybrid mode]Get BD num for single mem error!bd num:0x%x\n", bd_num);
	        return CIPHER_FIFO_FULL;
	    }
		
		ret = cipher_test_bd_single_block(bd_num,32);
		if (ret) {
			cipher_test_print("[Hybrid mode]single mem error code:0x%x, bd num:%d\n", ret, bd_num);
			return ret;
		}

		ret = cipher_test_rd_handler(CIPHER_TEST_PS_NUM_CHN1, CIPHER_SECURITY_CHANNEL_1);
		if (ret) {
			cipher_test_print("[Get RD]single mem, error code:0x%x, bd num:%d\n", ret, bd_num);
			return ret;
		}
	}
	
	return ret;
}

static int cipher_special_channel(unsigned int chn)
{
	if(LTE_KEY_OPT_CHANNEL_KDF		 == chn 
	|| LTE_SECURITY_CHANNEL_UL_ACC_0 == chn 
	|| LTE_SECURITY_CHANNEL_UL_ACC_1 == chn)
		return 1;
	return 0;
}


int cipher_test_chn_status(void) 
{
	int ret;
	int chn_id;
	struct fifo_ctl *rd_fifo;
	struct cipher_chn_ctl *cur_chn;

	/* Test wrong chn id */
	ret = mdrv_cipher_get_chn_status(cipher_module_ctl.chn_cnt);
	if (ret != CIPHER_CHECK_ERROR) {			//error input check
		cipher_test_print("[Test error chn0]error code:%d\n", ret);
		return CIPHER_UNKNOWN_ERROR;
	}

	for (chn_id = 0; chn_id < cipher_module_ctl.chn_cnt; chn_id++) {
		if (cipher_special_channel(chn_id)) {
			ret = mdrv_cipher_get_chn_status(chn_id);
			if (ret != CIPHER_NULL_PTR) {		//error input check
				cipher_test_print("[Test error chn1]error code:%d\n", ret);
				return CIPHER_UNKNOWN_ERROR;
			}
			continue;
		}

		cur_chn = &(cipher_module_ctl.cipher_chn[chn_id]);
		if (cur_chn->straight) {
			ret = mdrv_cipher_get_chn_status(chn_id);
			if (ret != CIPHER_INVALID_CHN) {	//error input check
				cipher_test_print("[Test error chn2]error code:%d\n", ret);
				return CIPHER_UNKNOWN_ERROR;
			}
			continue;
		}

		rd_fifo = &(cipher_module_ctl.cipher_chn[chn_id].rd_fifo);

		/* clear all rd twice to ensure all of the BD and RD are handled */
		(void)cipher_test_rd_handler(rd_fifo->elem_cnt, chn_id);
		(void)cipher_test_rd_handler(rd_fifo->elem_cnt, chn_id);

		/* Test bd and rd empty */
		ret = mdrv_cipher_get_chn_status(chn_id);
		if ((ret != CIPHER_CHN_BDEMPTY_RDEMPTY)) {
			cipher_test_print("[Test chn idle]error code:%d\n", ret);
			return ret;
		}
	}

	/* Test bd empty, RD in using */
	rd_fifo = &(cipher_module_ctl.cipher_chn[CIPHER_SECURITY_CHANNEL_1].rd_fifo);
	cipher_test_bd_single_block(rd_fifo->elem_cnt - 2, 32);
	(void)osl_task_delay(1);	//waiting for task completed.
	ret = mdrv_cipher_get_chn_status(CIPHER_SECURITY_CHANNEL_1);
	if (ret != CIPHER_CHN_BDEMPTY_RDINUSE) {
		cipher_test_print("[Test bd empty]error code:%d\n", ret);
		return -CIPHER_CHN_BDEMPTY_RDINUSE;
	}
	(void)cipher_test_rd_handler(rd_fifo->elem_cnt, chn_id);

	/* Test bd in using, RD in using */
	cipher_test_bd_single_block(rd_fifo->elem_cnt - 2, 4);	//make RD in using
	cipher_test_bd_single_block(rd_fifo->elem_cnt - 2, 4);	//make BD in using
	ret = mdrv_cipher_get_chn_status(CIPHER_SECURITY_CHANNEL_1);
	if (ret != CIPHER_CHN_BDINUSE_RDINUSE) {
		cipher_test_print("[Test bd in using]error code:%d\n", ret);
		return -CIPHER_CHN_BDINUSE_RDINUSE;
	}

	/* clear all rd twice to ensure all of the BD and RD are handled */
	(void)cipher_test_rd_handler(rd_fifo->elem_cnt, chn_id);
	(void)cipher_test_rd_handler(rd_fifo->elem_cnt, chn_id);

	return CIPHER_SUCCESS;		//if normal, ret should be zero.
}

#if 0
static unsigned int ACC_APH_LEN = 0;
static unsigned int g_keyRam[4] = {0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c};

static int ACC_ST_Init(unsigned int u32BlockLen, unsigned int u32PakNums, void **pInAddr, void **pOutAddr,
	CIPHER_CFG_S ** pstCfg,CIPHER_CFG_S **pstCipherCfg)
{
    int i;
    char * ptempIn;

    *pstCipherCfg = (CIPHER_CFG_S *)osl_cachedma_malloc(sizeof(CIPHER_CFG_S));
    *pstCfg       = (CIPHER_CFG_S *)osl_cachedma_malloc(sizeof(CIPHER_CFG_S));
    *pInAddr      = (void *)osl_cachedma_malloc((u32BlockLen + ACC_APH_LEN) * u32PakNums);
    *pOutAddr     = (void *)osl_cachedma_malloc((u32BlockLen + ACC_APH_LEN) * u32PakNums);
    if(!*pstCipherCfg || !*pstCfg || !*pInAddr || !*pOutAddr)
    {
        osl_free(*pstCipherCfg);
        osl_free(*pstCfg);
        osl_free(*pInAddr);
		osl_free(*pOutAddr);
        CIPHER_TEST_PRINT(">>>line %d FUNC %s fail, osl_malloc failed !\n", (int)__LINE__, (int)__FUNCTION__, 0, 0, 0, 0);
        return -1;
    }
    ptempIn = *pInAddr;
    for(i = 0; i < (int)((u32BlockLen + ACC_APH_LEN) * u32PakNums) ; i ++)
    {
        *ptempIn = i%256;
        ptempIn ++;
    }
	memset_s(*pstCipherCfg,sizeof(*pstCipherCfg), 0, sizeof(CIPHER_CFG_S));
	memset_s(*pstCfg,sizeof(*pstCfg),       0, sizeof(CIPHER_CFG_S));
    memset_s(*pOutAddr,sizeof(*pOutAddr),     0, ((u32BlockLen + ACC_APH_LEN) * u32PakNums));

    return 0;
}

static int ACC_ST_DMA(unsigned int u32BlockLen, unsigned int u32PakNums)
{
    int s32ret;
    int i;
    CIPHER_CFG_S *pstCfg       = NULL;
    CIPHER_CFG_S *pstCipherCfg = NULL;
    void *pInAddr      = NULL;
    void *pOutAddr     = NULL;
    void *pTempInAddr  = NULL;
    void *pTempOutAddr = NULL;
	/*���ܲ�����*/
    unsigned int timeStart = 0;
    unsigned int timeEnd   = 0;

    s32ret = ACC_ST_Init(u32BlockLen, u32PakNums, &pInAddr, &pOutAddr,&pstCfg,&pstCipherCfg);
    if(s32ret)
    {
    	CIPHER_TEST_PRINT("ACC_ST_Init err\n");
        return -1;
    }
	
    pTempInAddr = pInAddr;
    pTempOutAddr = pOutAddr;

	timeStart = bsp_get_slice_value_hrt();
	/*����DMA��ʽ*/ 
	for(i = 0; i <(int)u32PakNums; i++)
	{
		pstCfg->enOpt       = CIPHER_OPT_DMA;
		pstCfg->u8Direction = 0;
		pstCfg->bMemBlock   = 1;
    	pstCfg->u32BlockLen = u32BlockLen;
		pstCfg->pInMemMgr   = pTempInAddr;
		pstCfg->pOutMemMgr  = pTempOutAddr;
		pstCfg->enSubmAttr  = CIPHER_SUBM_NONE;

		s32ret = mdrv_cipher_set_bdinfo(LTE_SECURITY_CHANNEL_UL_ACC_0, 1, pstCfg);
		if(OK != s32ret)
		{
			CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
			goto ERRFREE;
		}
		pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen);
		pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen);
	}
	timeEnd = bsp_get_slice_value_hrt();
	CIPHER_TEST_PRINT("cfg bdnum:%d time:%d\n",i, timeEnd - timeStart);

	do{
		s32ret = cipher_start_channel(LTE_SECURITY_CHANNEL_UL_ACC_0, CIPHER_SUBM_NONE);
	}while(-1000 == s32ret);
    if(s32ret)
    {
        CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
        goto ERRFREE;
    }

    timeStart = bsp_get_slice_value_hrt();
    /*�ȴ��������*/
    do{
        /*osl_task_delay(10);*//*Ϊ�˵�һʱ��֪��ͨ���Ѿ�ֹͣ����ʹ����ʱ������*/
    }while(!mdrv_cipher_chn_idle(LTE_SECURITY_CHANNEL_UL_ACC_0));

	/*���ܲ���*/
    timeEnd = bsp_get_slice_value_hrt();
	CIPHER_TEST_PRINT("acc process time:%d\n", timeEnd - timeStart);
    
    /*�Ƚ����ǰ�����Ƿ���ͬ*/
    s32ret = cipher_memcmp_ext(pInAddr, pOutAddr,u32BlockLen * u32PakNums);
    if(s32ret)
    {
        CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
        goto ERRFREE;
    }

    osl_cachedma_free(pstCipherCfg);
    osl_cachedma_free(pstCfg);
    osl_cachedma_free(pInAddr);
    osl_cachedma_free(pOutAddr);

    return 0;
ERRFREE: 
	osl_cachedma_free(pstCipherCfg);
	osl_cachedma_free(pstCfg);
	osl_cachedma_free(pInAddr);
	osl_cachedma_free(pOutAddr);
	return -1;
}

int ACC_ST_DMA_0001(void)
{
    int s32ret = -1;
	int u32LoopTimes = 10;
    
    while(u32LoopTimes > 0)
    {
        s32ret = ACC_ST_DMA(1500, 1);
        if(s32ret)
        {
            CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
            return -1;
        }
        u32LoopTimes--;
    }
    return 0;
    
}

static void Acc_CipherCfg(CIPHER_CFG_S *pstCfg, unsigned int CfgType)
{
    /*����pstCfg��Ϣ*/
    switch(CfgType)
    {
        case 0:
            mdrv_cipher_set_key(g_keyRam , CIPHER_KEY_L128, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                     /*���ܲ�������Ҫkey�����*/
            pstCfg->enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0; /*���Ӱ�ͷ�ĳ���*/
            pstCfg->enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0; /*��ͷpacker head�ĳ���*/
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_SNOW3G;     /*���ܲ�������SNOW3G*/
            pstCfg->stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
            pstCfg->u8BearId                    = 12;
//            pstCfg->u32Aph                      = 0x512;
            pstCfg->u32Count                    = 0x512;
            break;
        case 1:
            mdrv_cipher_set_key(g_keyRam , CIPHER_KEY_L128, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                     /*���ܲ�������Ҫkey�����*/
            pstCfg->enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0; /*���Ӱ�ͷ�ĳ���*/
            pstCfg->enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0; /*��ͷpacker head�ĳ���*/
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128;    /*���ܲ�������AES192*/
            pstCfg->stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
            pstCfg->u8BearId                   = 12;
//            pstCfg->u32Aph                      = 0x56432F;
            pstCfg->u32Count                    = 0x56432F;
            break;
        case 2:
            mdrv_cipher_set_key(g_keyRam , CIPHER_KEY_L128, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                     /*���ܲ�������Ҫkey�����*/
            pstCfg->enAppdHeaderLen             = CIPHER_ACC_HDR_1; /*���Ӱ�ͷ�ĳ���*/
            pstCfg->enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0; /*��ͷpacker head�ĳ���*/
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128;    /*���ܲ�������AES128*/
            pstCfg->stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
            pstCfg->u8BearId                    = 12;
//            pstCfg->u32Aph                      = 0x56432F;
            pstCfg->u32Count                    = 0x56432F;
            break;
        case 3:
            mdrv_cipher_set_key(g_keyRam , CIPHER_KEY_L128, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                     /*���ܲ�������Ҫkey�����*/
            pstCfg->enAppdHeaderLen             = CIPHER_ACC_HDR_2; /*���Ӱ�ͷ�ĳ���*/
            pstCfg->enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0; /*��ͷpacker head�ĳ���*/
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128;    /*���ܲ�������AES256*/
            pstCfg->stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
            pstCfg->u8BearId                   = 3;
//            pstCfg->u32Aph                      = 256;
            pstCfg->u32Count                    = 256;
            break;
        case 4:
            mdrv_cipher_set_key(g_keyRam , CIPHER_KEY_L128, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                     /*���ܲ�������Ҫkey�����*/
            pstCfg->enAppdHeaderLen             = CIPHER_ACC_HDR_2; /*���Ӱ�ͷ�ĳ���*/
            pstCfg->enHeaderLen                 = CIPHER_ACC_HDR_2; /*��ͷpacker head�ĳ���*/
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128;    /*���ܲ�������NULL*/
            pstCfg->stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL; 
            pstCfg->u8BearId                   = 3;
//            pstCfg->u32Aph                      = 256;
            pstCfg->u32Count                    = 256;
            break;            
    }
    return;
}

static int ACC_ST_Cipher(unsigned int u32BlockLen, unsigned int u32PakNums, unsigned int CfgType, unsigned int offset)
{
    int s32ret,i;
    CIPHER_CFG_S *pstCfg       = NULL;
    CIPHER_CFG_S *pstCipherCfg = NULL;
    void *pInAddr      = NULL;
    void *pOutAddr     = NULL;
    void *pTempInAddr  = NULL;
    void *pTempOutAddr = NULL;
	/*���ܲ�����*/
    unsigned int timeStart = 0;
    unsigned int timeEnd   = 0;

    s32ret = ACC_ST_Init(u32BlockLen, u32PakNums, &pInAddr, &pOutAddr,&pstCfg,&pstCipherCfg);
	if(ERROR == s32ret)
    {
    	CIPHER_TEST_PRINT("ACC_ST_Init err\n");
        return -1;
    }
	/*����pstCfg��Ϣ*/
	Acc_CipherCfg(pstCfg,CfgType);
	pstCfg->enOpt       = CIPHER_OPT_ENCRYPT;
	pstCfg->u8Direction = 0;
	pstCfg->bMemBlock   = 1;
    pstCfg->u32BlockLen = u32BlockLen;
	pstCfg->enSubmAttr  = CIPHER_SUBM_NONE;
	pstCfg->u32Offset   = 0;
	pstCfg->u32OutLen   = offset ? offset : (u32BlockLen + ACC_APH_LEN);

    pTempInAddr  = (char *)((unsigned int)pInAddr + ACC_APH_LEN);
    pTempOutAddr = (char *)((unsigned int)pOutAddr);

	/*����Cipher���ܷ�ʽ*/
	for(i = 0; i <(int)u32PakNums; i++)
	{
		pstCfg->pInMemMgr   = pTempInAddr;
		pstCfg->pOutMemMgr  = pTempOutAddr;
		s32ret = mdrv_cipher_set_bdinfo(LTE_SECURITY_CHANNEL_UL_ACC_0, 1, pstCfg);
        if(s32ret)
        {
            CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
            goto ERRFREE;
        }
		if(offset)
		{
			pstCfg->pOutMemMgr  = pTempOutAddr + offset;
			pstCfg->u32Offset   = offset;
			pstCfg->u32OutLen   = (u32BlockLen - offset + ACC_APH_LEN);
			s32ret = mdrv_cipher_set_bdinfo(LTE_SECURITY_CHANNEL_UL_ACC_0, 1, pstCfg);
        	if(s32ret)
        	{
            	CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
            	goto ERRFREE;
        	}
		}
        pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen + ACC_APH_LEN) ;
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen + ACC_APH_LEN);
	}
	do{
		s32ret = cipher_start_channel(LTE_SECURITY_CHANNEL_UL_ACC_0, CIPHER_SUBM_CALLBACK);
	}while(-1000 == s32ret);
    if(s32ret)
    {
        CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
        goto ERRFREE;
    }
	timeStart = bsp_get_slice_value_hrt();
    /*�ȴ��������*/
	while(!mdrv_cipher_chn_idle(LTE_SECURITY_CHANNEL_UL_ACC_0));
	/*���ܲ���*/
    timeEnd = bsp_get_slice_value_hrt();
	CIPHER_TEST_PRINT("acc process time:%d\n", timeEnd - timeStart);

    /*����Cipher���ܺ��������ܼ���֮�������****************************************/
	pstCipherCfg->bMemBlock       = 1;
	pstCipherCfg->enOpt           = CIPHER_OPT_DECRYPT;
	pstCipherCfg->u8Direction     = 1;
	pstCipherCfg->stAlgKeyInfo    = pstCfg->stAlgKeyInfo;
	pstCipherCfg->u32Count        = pstCfg->u32Count;
	pstCipherCfg->enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
	pstCipherCfg->u8BearId        = pstCfg->u8BearId;
	pstCipherCfg->enHeaderLen     = CIPHER_HDR_BIT_TYPE_0;
	pstCipherCfg->u32BlockLen     = pstCfg->u32BlockLen;
	pstCipherCfg->u32Private      = 0;
	pstCipherCfg->enSubmAttr      = CIPHER_SUBM_BLK_HOLD;
	
    pTempOutAddr = (char *)((unsigned int)pOutAddr + ACC_APH_LEN);
    for(i = 0; i <(int)u32PakNums; i++)
    {
		pstCipherCfg->pInMemMgr       = pTempOutAddr;
		pstCipherCfg->pOutMemMgr      = pTempOutAddr;

        s32ret = mdrv_cipher_set_bdinfo(LTE_SECURITY_CHANNEL_DL_DRB_CCORE, 1, pstCipherCfg);
        if(s32ret)
        {
            CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
            goto ERRFREE;
        }
        pTempOutAddr = (char*)((unsigned int)pTempOutAddr + u32BlockLen + ACC_APH_LEN);
    }

    /*�Ƚ����ǰ�����Ƿ���ͬ*/
    for(i = 0; i <(int)u32PakNums; i++)
    {
        pTempInAddr  = (char *)((unsigned int)pInAddr  + ACC_APH_LEN);
        pTempOutAddr = (char *)((unsigned int)pOutAddr + ACC_APH_LEN);
        s32ret = cipher_memcmp_ext(pTempInAddr, pTempOutAddr,u32BlockLen);
        if(s32ret)
        {
            CIPHER_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, s32ret, 0, 0, 0);
            goto ERRFREE;
        }
        pTempInAddr =  (char *)((unsigned int)pTempInAddr  + u32BlockLen   + ACC_APH_LEN) ;
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen + ACC_APH_LEN);
    }

    osl_cachedma_free(pstCipherCfg);
    osl_cachedma_free(pstCfg);
    osl_cachedma_free(pInAddr);
    osl_cachedma_free(pOutAddr);

    return 0;
ERRFREE: 
	osl_cachedma_free(pstCipherCfg);
	osl_cachedma_free(pstCfg);
	osl_cachedma_free(pInAddr);
	osl_cachedma_free(pOutAddr);
	return -1;
}

int ACC_ST_Cipher_0001(void)
{
    ACC_APH_LEN = 1;
    return ACC_ST_Cipher(1500, 127, 2, 0);
}

int ACC_ST_Cipher_0002(void)
{
    ACC_APH_LEN = 0;
    return ACC_ST_Cipher(1500, 60, 1, 500);
}
#endif
