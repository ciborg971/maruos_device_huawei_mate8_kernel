
#include <string.h>
#include <stdlib.h>
#include "securec.h"
#include <osl_sem.h>
#include <osl_malloc.h>
#include <mdrv_cipher.h>
#include <bsp_cipher.h>
#include <bsp_hardtimer.h>
#include <bsp_om.h>
#include "acc_balong.h"


#define ACC_TEST_PRINT(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_ACC, "[ACC API INFOR]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#ifndef RAND_MAX
#define RAND_MAX	32767
#endif

//#define ACC_CHN_NUM 0
#define CIPHER_CHN  1
static unsigned int ACC_APH_LEN = 0;
static osl_sem_id   g_UsrClkSendCountSem;
//static unsigned int g_AccInitCmp = 0;
static unsigned int g_ChnBusy    = 0;
static unsigned int g_acc_test_debug    = 0;
static unsigned int g_acc_test_time    = 0;
static int          g_bIsAcc     = 1;
static unsigned int g_keyRam[4]  = {0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c};

static int Acc_memcmp_ext(const void* mem1, const void* mem2, unsigned int size)
{
    unsigned int total = size;
	const unsigned char *p1 = mem1;
	const unsigned char *p2 = mem2;

	while(total && *p1 == *p2) {
		total--;
		if (g_acc_test_debug) {
		}
		p1++;
		p2++;
	}
	if (total) {
		ACC_TEST_PRINT("src:0x%x != dst:0x%x\n", *p1, *p2);
		return -1;
	}
	return 0;
}

static int AccDataCmp(void* pBlk1, void* pBlk2,unsigned int u32BlockLen)
{
    int s32CmpResult = -1;

    void* pTempBlk1 = pBlk1;
    void* pTempBlk2 = pBlk2;

    if ((pBlk1 == NULL) || (pBlk2 == NULL))
    {
        return -1;
    }

    s32CmpResult = Acc_memcmp_ext(pTempBlk1, pTempBlk2,u32BlockLen);
    if (s32CmpResult != OK)
    {
        return -1;
    }

    return OK;
}

static void Acc_CipherCfg(ACC_SINGLE_CFG_S *pstCfg, unsigned int CfgType)
{
    /*����pstCfg��Ϣ*/
    switch(CfgType)
    {
        case 0:
            mdrv_cipher_set_key(g_keyRam , 0, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                 /* ���ܲ�������Ҫkey����� */
            pstCfg->u32AppdHeaderLen            = 0;                 /* ���Ӱ�ͷ�ĳ���          */
            pstCfg->u32HeaderLen                = 0;                 /* ��ͷpacker head�ĳ���   */
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_SNOW3G; /* ���ܲ�������SNOW3G      */
            pstCfg->stAlgKeyInfo.enAlgIntegrity = 0;
            pstCfg->u32BearId                   = 12;
            pstCfg->u32Aph                      = 0x512;
            pstCfg->u32Count                    = 0x512;
            break;
            
        case 1:
            mdrv_cipher_set_key(g_keyRam , 0, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                  /* ���ܲ�������Ҫkey����� */
            pstCfg->u32AppdHeaderLen            = 0;                  /* ���Ӱ�ͷ�ĳ���          */
            pstCfg->u32HeaderLen                = 0;                  /* ��ͷpacker head�ĳ���   */
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128; /* ���ܲ�������AES192      */
            pstCfg->stAlgKeyInfo.enAlgIntegrity = 0;
            pstCfg->u32BearId                   = 12;
            pstCfg->u32Aph                      = 0x56432F;  
            pstCfg->u32Count                    = 0x56432F;
            break;
            
        case 2:
            mdrv_cipher_set_key(g_keyRam , 0, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                  /* ���ܲ�������Ҫkey����� */
            pstCfg->u32AppdHeaderLen            = 1;                  /* ���Ӱ�ͷ�ĳ���          */
            pstCfg->u32HeaderLen                = 0;                  /* ��ͷpacker head�ĳ���   */
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128; /* ���ܲ�������AES128      */
            pstCfg->stAlgKeyInfo.enAlgIntegrity = 0;
            pstCfg->u32BearId                   = 12;
            pstCfg->u32Aph                      = 0x56432F;
            pstCfg->u32Count                    = 0x56432F;
            break;
            
        case 3:
            mdrv_cipher_set_key(g_keyRam , 0, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                  /* ���ܲ�������Ҫkey����� */
            pstCfg->u32AppdHeaderLen            = 2;                  /* ���Ӱ�ͷ�ĳ���          */
            pstCfg->u32HeaderLen                = 0;                  /* ��ͷpacker head�ĳ���   */
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128; /* ���ܲ�������AES256      */
            pstCfg->stAlgKeyInfo.enAlgIntegrity = 0; 
            pstCfg->u32BearId                   = 3;    
            pstCfg->u32Aph                      = 256;  
            pstCfg->u32Count                    = 256;
            break;
        case 4:
            mdrv_cipher_set_key(g_keyRam , 0, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                  /* ���ܲ�������Ҫkey����� */
            pstCfg->u32AppdHeaderLen            = 2;                  /* ���Ӱ�ͷ�ĳ���          */
            pstCfg->u32HeaderLen                = 2;                  /* ��ͷpacker head�ĳ���   */
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_128; /* ���ܲ�������NULL        */
            pstCfg->stAlgKeyInfo.enAlgIntegrity = 0;
            pstCfg->u32BearId                   = 3;
            pstCfg->u32Aph                      = 256;
            pstCfg->u32Count                    = 256;
            break;   
        case 5:
            mdrv_cipher_set_key(g_keyRam , 2, 0);
            pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;                  /* ���ܲ�������Ҫkey����� */
            pstCfg->u32AppdHeaderLen            = 2;                  /* ���Ӱ�ͷ�ĳ���          */
            pstCfg->u32HeaderLen                = 0;                  /* ��ͷpacker head�ĳ���   */
            pstCfg->stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_AES_256; /* ���ܲ�������NULL        */
            pstCfg->stAlgKeyInfo.enAlgIntegrity = 0;
            pstCfg->u32BearId                   = 3;
            pstCfg->u32Aph                      = 256;
            pstCfg->u32Count                    = 256;
            break;            

    }
    return;
}

static int ACC_ST_Init(unsigned int u32BlockLen, unsigned int u32PakNums, void **pInAddr, void **pOutAddr,
	ACC_SINGLE_CFG_S ** pstCfg,CIPHER_SINGLE_CFG_S **pstCipherCfg)
{
    int i;
    char * ptempIn;

    *pstCipherCfg = (CIPHER_SINGLE_CFG_S *) osl_cachedma_malloc(sizeof(CIPHER_SINGLE_CFG_S));
    if(!*pstCipherCfg)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail, malloc failed !\n", (int)__LINE__, (int)__FUNCTION__);
        return -1;
    }

    *pstCfg = (ACC_SINGLE_CFG_S *)osl_cachedma_malloc(sizeof(ACC_SINGLE_CFG_S));
    if(!*pstCfg)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail, malloc failed !\n", (int)__LINE__, (int)__FUNCTION__);
		goto clean0;

    }
    
    *pInAddr = (void *)osl_cachedma_malloc(u32BlockLen * u32PakNums + ACC_APH_LEN* u32PakNums);
    if(NULL == *pInAddr)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail, malloc failed !\n", (int)__LINE__, (int)__FUNCTION__);
		goto clean1;
    }
    
    *pOutAddr = (void *)osl_cachedma_malloc(u32BlockLen * u32PakNums + ACC_APH_LEN* u32PakNums);
    if(NULL == *pInAddr)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail, malloc failed !\n", (int)__LINE__, (int)__FUNCTION__);
		goto clean2;

	}
	memset_s(*pstCipherCfg,sizeof(CIPHER_SINGLE_CFG_S), 0, sizeof(CIPHER_SINGLE_CFG_S));
	memset_s(*pstCfg,sizeof(ACC_SINGLE_CFG_S),   0, sizeof(ACC_SINGLE_CFG_S));
    memset_s(*pOutAddr,((u32BlockLen + ACC_APH_LEN) * u32PakNums), 0, ((u32BlockLen + ACC_APH_LEN) * u32PakNums));
    ptempIn = *pInAddr;
    for(i = 0; i < (int)(u32BlockLen * u32PakNums + ACC_APH_LEN* u32PakNums) ; i ++)
    {
        *ptempIn = i%256;
        ptempIn ++;
    }
    memset_s(*pOutAddr,u32BlockLen * u32PakNums + ACC_APH_LEN* u32PakNums, 0, u32BlockLen * u32PakNums + ACC_APH_LEN* u32PakNums);

	return 0;
clean2:
    osl_cachedma_free(*pstCipherCfg);
clean1:
    osl_cachedma_free(*pstCfg);
clean0:
    osl_cachedma_free(*pInAddr);
	
    return -1;
}

#if 0
int ACC_ST_STOP()
{
    g_bIsAcc = FALSE;
    BSP_USRCLK_Disable(g_UsrClkID);
    BSP_USRCLK_Free(g_UsrClkID);

    osl_cachedma_free((void*)g_CipherCfgAddr);
    osl_cachedma_free((void*)g_CfgAddr);
    osl_cachedma_free((void*)g_InDataAddr);
    osl_cachedma_free((void*)g_OutDataAddr);

    
}
#endif

int ACC_ST_DMA(unsigned int u32BlockLen, unsigned int u32PakNums)
{
    int ret;
    unsigned int i;
    unsigned int u32BdFifoAddr;
    ACC_SINGLE_CFG_S *pstCfg   = NULL;
    CIPHER_SINGLE_CFG_S *pstCipherCfg = NULL;
    void *pInAddr      = NULL;
    void *pOutAddr     = NULL;
    void *pTempInAddr  = NULL;
    void *pTempOutAddr = NULL;
	/*���ܲ�����*/
    unsigned int timeStart = 0;
    unsigned int timeEnd   = 0;

    ret = ACC_ST_Init(u32BlockLen, u32PakNums, &pInAddr, &pOutAddr,&pstCfg,&pstCipherCfg);
    if(ret)
    {
        return ret;
    }

    pstCfg->u32BlockLen = u32BlockLen;
    pTempInAddr         = pInAddr;
    pTempOutAddr        = pOutAddr;

    /*��ȡ����FIFO�׵�ַ*/
    u32BdFifoAddr = mdrv_acc_get_bdq_addr();
    if((unsigned int)CIPHER_UNKNOWN_ERROR == u32BdFifoAddr)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��result = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, u32BdFifoAddr);
        goto free;
    }

    /*����DMA��ʽ*/
    for(i = 0; i < u32PakNums; i++)
    {
    	pstCfg->pInMemMgr  = pTempInAddr;
		pstCfg->pOutMemMgr = pTempOutAddr;
        ret = mdrv_acc_dma(u32BdFifoAddr, pstCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen);
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen);
    }

    /*��ȡ��ǰͨ��״̬��������ʹ���������*/
    while(mdrv_acc_get_status(CIPHER_SECURITY_CHANNEL_0) != CHN_FREE)
    {
        g_ChnBusy ++;
    }

    timeStart = bsp_get_slice_value();

    ret = mdrv_acc_enable(CIPHER_SECURITY_CHANNEL_0, u32BdFifoAddr);
    if(CIPHER_UNKNOWN_ERROR == ret)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
        goto free;
    }

    /*�ȴ��������*/
    do{
        /*taskDelay(10);*//*Ϊ�˵�һʱ��֪��ͨ���Ѿ�ֹͣ����ʹ����ʱ������*/
    }while(mdrv_acc_get_status(CIPHER_SECURITY_CHANNEL_0) != CHN_FREE);

	/*���ܲ���*/
    timeEnd = bsp_get_slice_value();
	g_acc_test_time += timeEnd - timeStart;
    
    /*�Ƚ����ǰ�����Ƿ���ͬ*/
    ret = AccDataCmp(pInAddr, pOutAddr,u32BlockLen * u32PakNums);

free: 
    osl_cachedma_free(pstCipherCfg);
    osl_cachedma_free(pstCfg);
    osl_cachedma_free(pInAddr);
    osl_cachedma_free(pOutAddr);
    return ret;
}

/*****************************************************************************
* �� �� ��  : ACC_ST_Cipher
*
* ��������  :��������������٣�����Cipher���ܷ�ʽ
*
* �������  : unsigned int u32BlockLen : ������
                            unsigned int u32PakNums : һ������İ�����
                            unsigned int CfgType : cipher��������
                            int bAph :�Ƿ��APHͷ��0��ʾ������1��ʾ��
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
int ACC_ST_Cipher(unsigned int u32BlockLen, unsigned int u32PakNums, unsigned int CfgType)
{
    int ret,i;
    unsigned int u32BdFifoAddr;
    ACC_SINGLE_CFG_S *pstCfg   = NULL;
    CIPHER_SINGLE_CFG_S *pstCipherCfg = NULL;
    void *pInAddr      = NULL;
    void *pOutAddr     = NULL;
    void *pTempInAddr  = NULL;
    void *pTempOutAddr = NULL;
   /* void *pTempOutAddrCip = 0xc3f00000;*/

    ret = ACC_ST_Init(u32BlockLen, u32PakNums, &pInAddr, &pOutAddr,&pstCfg,&pstCipherCfg);
    if(ret)
    {
        return ret;
    }

    /*����pstCfg��Ϣ*/
    Acc_CipherCfg(pstCfg,CfgType);
    pstCfg->u32BlockLen = u32BlockLen;
    pstCfg->u32Offset   = 0;
    pstCfg->u32OutLen   = u32BlockLen + ACC_APH_LEN;

    pTempInAddr  = (char *)((unsigned int)pInAddr + ACC_APH_LEN);
    pTempOutAddr = (char *)((unsigned int)pOutAddr);

    /*��ȡ����FIFO�׵�ַ*/
    u32BdFifoAddr = mdrv_acc_get_bdq_addr();
    if((unsigned int)CIPHER_UNKNOWN_ERROR == u32BdFifoAddr )
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��result = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, u32BdFifoAddr);
        goto free;
    }

    /*����Cipher���ܷ�ʽ*/ 
    for(i = 0; i < (int)u32PakNums; i++)
    {
    	pstCfg->pInMemMgr  = pTempInAddr;
		pstCfg->pOutMemMgr = pTempOutAddr;
        ret = mdrv_acc_cipher(u32BdFifoAddr, pstCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen + ACC_APH_LEN) ;
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen + ACC_APH_LEN);
    }

    /*��ȡ��ǰͨ��״̬��������ʹ���������*/
    while(mdrv_acc_get_status(CIPHER_SECURITY_CHANNEL_0) != CHN_FREE)
    {
        g_ChnBusy ++;
    }
    ret = mdrv_acc_enable(CIPHER_SECURITY_CHANNEL_0, u32BdFifoAddr);
    if(CIPHER_UNKNOWN_ERROR == ret)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
        goto free;
    }   

    /*����Cipher���ܺ��������ܼ���֮�������****************************************/
    pstCipherCfg->bMemBlock       = 1;
    pstCipherCfg->enOpt           = 1;
    pstCipherCfg->u8Direction     = 0;
    pstCipherCfg->stAlgKeyInfo    = pstCfg->stAlgKeyInfo;
    pstCipherCfg->u32Count        = pstCfg->u32Count;
    pstCipherCfg->enAppdHeaderLen = 0;
    pstCipherCfg->u8BearId        = (unsigned char)pstCfg->u32BearId;
    pstCipherCfg->enHeaderLen     = 0;
    pstCipherCfg->u32BlockLen     = pstCfg->u32BlockLen;
        
    pTempOutAddr = (char *)((unsigned int)pOutAddr + ACC_APH_LEN);
    for(i = 0; i <(int)u32PakNums; i++)
    {
    	pstCipherCfg->pInMemMgr  = pTempOutAddr;
		pstCipherCfg->pOutMemMgr = pTempOutAddr;
		pstCipherCfg->enSubmAttr = 1;
		pstCipherCfg->u32Private = 0;
        ret = mdrv_cipher_set_bdinfo(CIPHER_CHN, 1, pstCipherCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempOutAddr = (char*)((unsigned int)pTempOutAddr + u32BlockLen + ACC_APH_LEN);
       /* (char*)pTempOutAddrCip = (char*)pTempOutAddrCip + u32BlockLen + ACC_APH_LEN;*/
    }
        
    /*�Ƚ����ǰ�����Ƿ���ͬ*/
   /* pTempOutAddrCip = 0xc3f00000;*/
    for(i = 0; i < (int)u32PakNums; i++)
    {
        pTempInAddr  = (char *)((unsigned int)pInAddr  + ACC_APH_LEN);
        pTempOutAddr = (char *)((unsigned int)pOutAddr + ACC_APH_LEN);
        ret = AccDataCmp(pTempInAddr, pTempOutAddr,u32BlockLen);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen + ACC_APH_LEN) ;
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen + ACC_APH_LEN);
    }

free: 
    osl_cachedma_free(pstCipherCfg);
    osl_cachedma_free(pstCfg);
    osl_cachedma_free(pInAddr);
    osl_cachedma_free(pOutAddr);
    return ret;
       
}

int acc_test_aes_cipher_only(unsigned int u32BlockLen, 
	unsigned int u32PakNums, unsigned int CfgType)
{
    int ret,i;
    unsigned int u32BdFifoAddr;
    ACC_SINGLE_CFG_S *pstCfg   = NULL;
    CIPHER_SINGLE_CFG_S *pstCipherCfg = NULL;
    void *pInAddr      = NULL;
    void *pOutAddr     = NULL;
    void *pTempInAddr  = NULL;
    void *pTempOutAddr = NULL;
	int start;
	int end;



	
    ret = ACC_ST_Init(u32BlockLen, u32PakNums, &pInAddr, &pOutAddr,&pstCfg,&pstCipherCfg);
    if(ret) {
        return ret;
    }

    /*����pstCfg��Ϣ*/
    Acc_CipherCfg(pstCfg,CfgType);
    pstCfg->u32BlockLen = u32BlockLen;
    pstCfg->u32Offset   = 0;
    pstCfg->u32OutLen   = u32BlockLen + pstCfg->u32AppdHeaderLen;
    pTempInAddr  = (char *)((unsigned int)pInAddr + pstCfg->u32AppdHeaderLen);
    pTempOutAddr = (char *)((unsigned int)pOutAddr);

    /*��ȡ����FIFO�׵�ַ*/
    u32BdFifoAddr = mdrv_acc_get_bdq_addr();
    if((unsigned int)CIPHER_UNKNOWN_ERROR == u32BdFifoAddr )
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��result = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, u32BdFifoAddr);
        goto free;
    }

    /*����Cipher���ܷ�ʽ*/ 
    for(i = 0; i < (int)u32PakNums; i++)
    {
    	pstCfg->pInMemMgr  = pTempInAddr;
		pstCfg->pOutMemMgr = pTempOutAddr;
        ret = mdrv_acc_cipher(u32BdFifoAddr, pstCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen + pstCfg->u32AppdHeaderLen) ;
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen + pstCfg->u32AppdHeaderLen);
    }

    /*��ȡ��ǰͨ��״̬��������ʹ���������*/
    while(mdrv_acc_get_status(CIPHER_SECURITY_CHANNEL_0) != CHN_FREE)
    {
        g_ChnBusy ++;
    }
    start = bsp_get_slice_value();

    ret = mdrv_acc_enable(CIPHER_SECURITY_CHANNEL_0, u32BdFifoAddr);
    if(CIPHER_UNKNOWN_ERROR == ret)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
        goto free;
    }

    /*�ȴ��������*/
    do{
        /*taskDelay(10);*//*Ϊ�˵�һʱ��֪��ͨ���Ѿ�ֹͣ����ʹ����ʱ������*/
    }while(mdrv_acc_get_status(CIPHER_SECURITY_CHANNEL_0) != CHN_FREE);

	/*���ܲ���*/
    end = bsp_get_slice_value();
	g_acc_test_time = end - start;
	
free: 
    osl_cachedma_free(pstCipherCfg);
    osl_cachedma_free(pstCfg);
    osl_cachedma_free(pInAddr);
    osl_cachedma_free(pOutAddr);
    return ret;
       
}

int acc_test_dma(int loop, unsigned int blksz, unsigned int blocks)
{
    int ret = 0;
	unsigned int total;
	int remain = loop;
	int speed;
	g_acc_test_time = 0;
    while(remain) {
        ret = ACC_ST_DMA(blksz, blocks);
        if(ret) {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto out;
        }
        remain--;
    }
out:	
	total = (loop - remain) * blksz * blocks;
	speed = total * 32  / g_acc_test_time;
	ACC_TEST_PRINT("speed: %ukb/s\n", speed);

    return ret;
    
}

int acc_test_aes_cipher(int loop, int blksz, int blocks)
{
	int ret = 0;
	unsigned int total;
	int remain = loop;
	int speed;

	
	g_acc_test_time = 0;
    while(--remain) {
        ret = acc_test_aes_cipher_only(blksz, blocks, 5);
        if(ret) {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto out;
        }
    }

out:
	total = (loop - remain) * blksz * blocks;
	speed = total * 32  / g_acc_test_time;

	ACC_TEST_PRINT("speed: %ukb/s\n", speed);
	
	return ret;
}

int acc_test_aes_cipher_opt(int loop, int bypass)
{
	int ret;
    unsigned int blksz = 40;
    unsigned int blocks = 50;	
	
	if (bypass) {
		acc_disable_aes_opt_bypass();
	} else {
		acc_enable_aes_opt_bypass();
	}
	ret = acc_test_aes_cipher(loop, blksz, blocks);

	
	return ret;
}

int acc_test_dma_opt(int loop, int bypass)
{
    int ret;
    unsigned int blksz = 30;
    unsigned int blocks = 6;
	if (bypass) {
		acc_disable_aes_opt_bypass();
	} else {
		acc_enable_aes_opt_bypass();
	}
	ret = acc_test_dma(loop, blksz, blocks);
	
	return ret;
    
}

/*****************************************************************************
* �� �� ��  : ACC_ST_DMA_Cipher_001
*
* ��������  :��������������٣�����DMA ��Cipher���ܽ���ķ�ʽ
*
* �������  : unsigned int u32BlockLen : ������
                            unsigned int u32PakNums : һ������İ�����(���ܴ���64)
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
int ACC_ST_DMA_Cipher_001(unsigned int u32BlockLen, unsigned int u32PakNums, 
	unsigned int u32Offset, unsigned int CfgType)
{
    int ret = 0;
	int i;
    unsigned int u32BdFifoAddr;
    ACC_SINGLE_CFG_S * pstCfg       = NULL;
    CIPHER_SINGLE_CFG_S *     pstCipherCfg = NULL;
    void *pInAddr      = NULL ;
    void *pOutAddr     = NULL;
    void *pTempInAddr  = NULL;
    void *pTempOutAddr = NULL;

    ret = ACC_ST_Init(u32BlockLen, 2 * u32PakNums, &pInAddr, &pOutAddr, &pstCfg, &pstCipherCfg);
    if(ret) { 
        return ret;
    }

    /*����pstCfg��Ϣ*/
    pstCfg->u32BlockLen = u32BlockLen;
    pstCfg->u32Offset   = u32Offset;
    pstCfg->u32OutLen   = u32BlockLen - u32Offset;

    pTempInAddr  = pInAddr;
    pTempOutAddr = pOutAddr;

    /*��ȡ����FIFO�׵�ַ*/
    u32BdFifoAddr = mdrv_acc_get_bdq_addr();
    if((unsigned int)CIPHER_UNKNOWN_ERROR == u32BdFifoAddr )
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��result = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, u32BdFifoAddr);
        goto free;
    }

    /*����Cipher���ܷ�ʽ*/
    for(i = 0; i < (int)u32PakNums; i++)
    {
    	pstCfg->bMemBlock  = 1;
		pstCfg->stAlgKeyInfo.enAlgIntegrity = 0;
		pstCfg->stAlgKeyInfo.enAlgSecurity  = 0;
		pstCfg->stAlgKeyInfo.u32KeyIndexInt = 0;
		pstCfg->stAlgKeyInfo.u32KeyIndexSec = 0;
		pstCfg->u32Aph     = 0;
		pstCfg->u32AppdHeaderLen = 0;
		pstCfg->u32BearId  = 0;
		pstCfg->u32Count   = 0;
		pstCfg->u32HeaderLen = 0;
    	pstCfg->pInMemMgr  = pTempInAddr;
		pstCfg->pOutMemMgr = pTempOutAddr;
        ret = mdrv_acc_dma(u32BdFifoAddr, pstCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen);
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen);

        Acc_CipherCfg(pstCfg,CfgType);
		pstCfg->pInMemMgr  = pTempInAddr;
		pstCfg->pOutMemMgr = pTempOutAddr;
        ret = mdrv_acc_cipher(u32BdFifoAddr, pstCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen);
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen);
    }

    /*��ȡ��ǰͨ��״̬��������ʹ���������*/
    while(mdrv_acc_get_status(CIPHER_SECURITY_CHANNEL_0) != CHN_FREE)
    {
        g_ChnBusy ++;
    }
    ret = mdrv_acc_enable(CIPHER_SECURITY_CHANNEL_0, u32BdFifoAddr);
    if(CIPHER_UNKNOWN_ERROR == ret)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
        goto free;
    }   

    /*����Cipher���ܺ��������ܼ���֮�������****************************************/
    pstCipherCfg->bMemBlock       = 1;
    pstCipherCfg->enOpt           = 1;
    pstCipherCfg->u8Direction     = 0;
    pstCipherCfg->stAlgKeyInfo    = pstCfg->stAlgKeyInfo;
    pstCipherCfg->u32Count        = pstCfg->u32Count;
    pstCipherCfg->enAppdHeaderLen = 0;
    pstCipherCfg->u8BearId        = (unsigned char)pstCfg->u32BearId;
    pstCipherCfg->enHeaderLen     = 0;
    pstCipherCfg->u32BlockLen     = pstCfg->u32BlockLen;
	pstCipherCfg->enSubmAttr      = 1;
	pstCipherCfg->u32Private      = 0;

    pTempOutAddr = (char *)((unsigned int)pOutAddr + u32BlockLen);
    for(i = 0; i < (int)u32PakNums; i++)
    {
    	pstCipherCfg->pInMemMgr  = pTempOutAddr;
		pstCipherCfg->pOutMemMgr = pTempOutAddr;

        ret = mdrv_cipher_set_bdinfo(CIPHER_CHN, 1, pstCipherCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen * 2);
    }
	while(!mdrv_cipher_chn_idle(CIPHER_CHN));
    /*�Ƚ����ǰ�����Ƿ���ͬ*/
    ret = AccDataCmp(pInAddr, pOutAddr, 2 * u32BlockLen * u32PakNums);
    if(ret)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
    }

free: 
    osl_cachedma_free(pstCipherCfg);
    osl_cachedma_free(pstCfg);
    osl_cachedma_free(pInAddr);
    osl_cachedma_free(pOutAddr);
    return ret;
}

int ACC_UsrClkSendIsr()
{
    osl_sem_up(&g_UsrClkSendCountSem);
    return OK;
}

/*****************************************************************************
* �� �� ��  : ACC_UsrClk_Send
*
* ��������  :�ҽӺ����ж�
*
* �������  : SendRate: �жϼ��
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
#if 0
int ACC_UsrClk_Send(int SendRate)
{
    int * ps32UsrClkId;

    ps32UsrClkId = (int *)osl_cachedma_malloc(sizeof(int));
    BSP_USRCLK_Alloc(ps32UsrClkId);
    g_UsrClkID = *ps32UsrClkId;

    if (OK != BSP_USRCLK_RateSet(SendRate, g_UsrClkID))
    {
    	ACC_TEST_PRINT(">>>line %d FUNC %s fail!\n", (int)__LINE__, (int)__FUNCTION__, 0, 0, 0, 0);
    	return -1;
    }

    if (OK != BSP_USRCLK_Connect((FUNCPTR)ACC_UsrClkSendIsr, 0, g_UsrClkID))
    {
    	ACC_TEST_PRINT(">>>line %d FUNC %s fail!\n", (int)__LINE__, (int)__FUNCTION__, 0, 0, 0, 0);
    	return -1;
    }

    if (OK != BSP_USRCLK_Enable(g_UsrClkID))
    {
    	ACC_TEST_PRINT(">>>line %d FUNC %s fail!\n", (int)__LINE__, (int)__FUNCTION__, 0, 0, 0, 0);
    	return -1;
    }

    return OK;
}
#endif

int ACC_EnableFunc(unsigned int u32BlockLen, unsigned int u32PakNums, void *pInAddr, void *pOutAddr,
	ACC_SINGLE_CFG_S *pstCfg, CIPHER_SINGLE_CFG_S *pstCipherCfg)
{
    int ret;
    unsigned int u32BdFifoAddr;
    void *pTempInAddr = NULL;
    void *pTempOutAddr = NULL;
    int i = 0;
    
    while (g_bIsAcc)
    {
        pTempInAddr  = pInAddr;
        pTempOutAddr = pOutAddr;
        osl_sem_down(&g_UsrClkSendCountSem);
       
        /*��ȡ����FIFO�׵�ַ*/
        u32BdFifoAddr = mdrv_acc_get_bdq_addr();
        if((unsigned int)CIPHER_UNKNOWN_ERROR == u32BdFifoAddr )
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��result = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, u32BdFifoAddr);
            goto free;
        }

        /*����Cipher���ܷ�ʽ*/ 
        for(i = 0; i <(int)u32PakNums; i++)
        {
        	pstCfg->pInMemMgr  = pTempInAddr;
			pstCfg->pOutMemMgr = pTempOutAddr;
            ret = mdrv_acc_dma(u32BdFifoAddr, pstCfg);
            if(ret)
            {
                ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
                goto free;
            }
            pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen);
            pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen);

			pstCfg->pInMemMgr  = pTempInAddr;
			pstCfg->pOutMemMgr = pTempOutAddr;
            ret = mdrv_acc_cipher(u32BdFifoAddr, pstCfg);
            if(ret)
            {
                ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
                goto free;
            }
            pTempInAddr  = (char *)((unsigned int)pTempInAddr  + u32BlockLen);
            pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen);
        }

        /*��ȡ��ǰͨ��״̬��������ʹ���������*/
        while(mdrv_acc_get_status(CIPHER_SECURITY_CHANNEL_0) != CHN_FREE)
        {
            osl_sem_down(&g_UsrClkSendCountSem);
            g_ChnBusy ++;
        }
        ret = mdrv_acc_enable(CIPHER_SECURITY_CHANNEL_0, u32BdFifoAddr);
        if(CIPHER_UNKNOWN_ERROR == ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }   

        /*����Cipher���ܺ��������ܼ���֮�������****************************************/
        pstCipherCfg->bMemBlock       = 1;
        pstCipherCfg->enOpt           = 1;
        pstCipherCfg->u8Direction     = 0;
        pstCipherCfg->stAlgKeyInfo    = pstCfg->stAlgKeyInfo;
        pstCipherCfg->u32Count        = pstCfg->u32Count;
        pstCipherCfg->enAppdHeaderLen = 0;
        pstCipherCfg->u8BearId        = (unsigned char)pstCfg->u32BearId;
        pstCipherCfg->enHeaderLen     = 0;
        pstCipherCfg->u32BlockLen     = pstCfg->u32BlockLen;

        pTempOutAddr = (char *)pOutAddr + u32BlockLen;
        for(i = 0; i <(int)u32PakNums; i++)
        {
        	pstCipherCfg->pInMemMgr  = pTempOutAddr;
			pstCipherCfg->pOutMemMgr = pTempOutAddr;
			pstCipherCfg->enSubmAttr = 1;
			pstCipherCfg->u32Private = 0;
            ret = mdrv_cipher_set_bdinfo(CIPHER_CHN, 1, pstCipherCfg);
            if(ret)
            {
               ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
               goto free;
            }
            pTempOutAddr = (char *)((unsigned int)pTempOutAddr + u32BlockLen*2);
        }

        /*�Ƚ����ǰ�����Ƿ���ͬ*/
        ret = AccDataCmp(pInAddr, pOutAddr,2 * u32BlockLen * u32PakNums);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            break;
        }

    }
  
free: 
    osl_cachedma_free(pstCipherCfg);
    osl_cachedma_free(pstCfg);
    osl_cachedma_free(pInAddr);
    osl_cachedma_free(pOutAddr);
    return ret;
}

/*****************************************************************************
* �� �� ��  : ACC_ST_DMA_Cipher_002
*
* ��������  :�ҽӺ����жϣ�ģ����ʵ����
*
* �������  : unsigned int u32BlockLen : ������
                            unsigned int u32PakNums : һ������İ�����(���ܴ���64)
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
#if 0
int ACC_ST_DMA_Cipher_002(unsigned int u32BlockLen, unsigned int u32PakNums, unsigned int u32Offset, unsigned int CfgType)
{
    int ret;
    ACC_SINGLE_CFG_S *pstCfg = NULL;
    CIPHER_SINGLE_CFG_S *pstCipherCfg = NULL;
    void *pInAddr = NULL;
    void *pOutAddr = NULL;
    void *pTempInAddr = NULL;
    void *pTempOutAddr = NULL;

    if(cipher_init())
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail, Cipher Init Failed! return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret, 0, 0, 0);
        return -1;
    }
    if(BSP_USRCLK_Init())
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail, Cipher Init Failed! return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret, 0, 0, 0);
        return -1;
    }
   
    ret = ACC_ST_Init(u32BlockLen, 2*u32PakNums, &pInAddr, &pOutAddr,&pstCfg,&pstCipherCfg);
    if(-1 == ret)
    {
        return -1;
    }

    g_CipherCfgAddr = (unsigned int)pstCipherCfg;
    g_CfgAddr = (unsigned int)pstCfg;
    g_InDataAddr = (unsigned int)pInAddr;
    g_OutDataAddr = (unsigned int)pOutAddr;

    /*����pstCfg��Ϣ*/
    Acc_CipherCfg(pstCfg,CfgType);
    pstCfg->u32BlockLen = u32BlockLen;
    pstCfg->u32Offset = u32Offset;
    pstCfg->u32OutLen = u32BlockLen - u32Offset;

    g_UsrClkSendCountSem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    if (g_UsrClkSendCountSem == NULL)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail\n", (int)__LINE__, (int)__FUNCTION__, 0, 0, 0, 0);
         goto free;
    }
    
    

    /*��ʼ���������*/
    if(FALSE == g_AccInitCmp)
    {
        ret = bsp_acc_init();
        if(CIPHER_NO_MEM == ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail, malloc failed !\n", (int)__LINE__, (int)__FUNCTION__, 0, 0, 0, 0);
            goto free;
        }
         g_AccInitCmp = TRUE;
    }

    if (OK != ACC_UsrClk_Send(1000))
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail\n", (int)__LINE__, (int)__FUNCTION__, 0, 0, 0, 0);
         goto free;
    }
    ret = taskSpawn ("tmAccEnableFunc", 132, 0, 20000, (FUNCPTR)ACC_EnableFunc, (int)u32BlockLen,
                                                (int)u32PakNums, (int)pInAddr, (int)pOutAddr,(int)pstCfg, (int)pstCipherCfg, 0, 0, 0, 0);
        
    if (-1 == ret)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��ret = %d\n", (int)__LINE__, (int)__FUNCTION__, ret, 0, 0, 0);
         goto free;
    }
    
    return OK;
    free: 
        osl_cachedma_free(pstCipherCfg);
        osl_cachedma_free(pstCfg);
        osl_cachedma_free(pInAddr);
        osl_cachedma_free(pOutAddr);
        return -1;
    
}
#endif

/*****************************************************************************
* �� �� ��  : ACC_ST_DMA_001
*
* ��������  :�������е�������������٣�����DMA���Ʒ�ʽ��ÿ��������Ϊ23
*
* �������  :unsigned int u32LoopTimes : ѭ������
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
int ACC_ST_DMA_001(unsigned int u32BlockLen, unsigned int u32PakNums,unsigned int u32LoopTimes)
{
    int ret;
    
    while(u32LoopTimes > 0)
    {
        ret = ACC_ST_DMA(u32BlockLen,u32PakNums);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            return ret;
        }
        u32LoopTimes--;
    }
    return OK;
}

/*****************************************************************************
* �� �� ��  : ACC_ST_DMA_002
*
* ��������  :��������������������������������٣�����DMA���Ʒ�ʽ
*
* �������  :unsigned int u32LoopTimes : ѭ������
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
int ACC_ST_DMA_002(unsigned int u32LoopTimes)
{
    int ret;
    unsigned int u32randLen = 0;
    unsigned int u32randPak = 0;

	srand(bsp_get_slice_value_hrt());

    while(u32LoopTimes > 0)
    {
        //u32randLen = (unsigned int)(rand() * (65536 - 1) / (RAND_MAX + 1) + 1);
        //u32randPak = (unsigned int)(rand() * (128   - 1) / (RAND_MAX + 1) + 1);
        u32randLen = rand() % RAND_MAX;
		u32randPak = rand() % RAND_MAX;
        ret = ACC_ST_DMA(u32randLen, u32randPak);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            return ret;
        }
        u32LoopTimes--;
    }
    return OK;
    
}

/*****************************************************************************
* �� �� ��  : ACC_ST_Cipher_001
*
* ��������  :�������е�������������٣�����Cipher���ܷ�ʽ��ÿ��������Ϊ23
*
* �������  :unsigned int u32LoopTimes : ѭ������
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
int ACC_ST_Cipher_001(unsigned int u32BlockLen, unsigned int u32PakNums,unsigned int u32LoopTimes, unsigned int CfgType)
{
    int ret;
    
    while(u32LoopTimes > 0)
    {
        ret = ACC_ST_Cipher(u32BlockLen,u32PakNums, CfgType);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            return ret;
        }
        u32LoopTimes--;
    }
    return OK;
    
}

/*****************************************************************************
* �� �� ��  : ACC_ST_Cipher_002
*
* ��������  :���������������������������������,����Cipher���ܷ�ʽ
*
* �������  :unsigned int u32LoopTimes : ѭ������
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
int ACC_ST_Cipher_002(unsigned int u32LoopTimes, unsigned int CfgType)
{
    int ret = -1;
    unsigned int u32randLen = 0;
    unsigned int u32randPak = 0;

	srand(bsp_get_slice_value_hrt());

    while(u32LoopTimes > 0)
    {
        //u32randLen = (unsigned int)(rand() * (65536 - 10) / (RAND_MAX + 1) + 10);
        //u32randPak = (unsigned int)(rand() * (128   -  1) / (RAND_MAX + 1) +  1);
        u32randLen = rand() % RAND_MAX;
		u32randPak = rand() % RAND_MAX;
        ret = ACC_ST_Cipher(u32randLen,u32randPak,CfgType);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            return ret;
        }
        u32LoopTimes--;
    }
    return OK;
    
}

/*****************************************************************************
* �� �� ��  : ACC_ST_Cipher_003
*
* ��������  :�������в��ֿ����,����Cipher���ܷ�ʽ
*
* �������  :unsigned int u32LoopTimes : ѭ������
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
int ACC_ST_Cipher_003(unsigned int u32BlockLen, unsigned int u32PakNums, unsigned int u32Offset,
	unsigned int u32LoopTimes, unsigned int CfgType)
{
    int ret = 0;
    unsigned int u32BdFifoAddr,i;
    ACC_SINGLE_CFG_S * pstCfg       = NULL;
    CIPHER_SINGLE_CFG_S *     pstCipherCfg = NULL;
    void * pInAddr      = NULL;
    void * pOutAddr     = NULL;
    void * pTempInAddr  = NULL;
    void * pTempOutAddr = NULL;

    ret = ACC_ST_Init(u32BlockLen, u32PakNums, &pInAddr, &pOutAddr,&pstCfg,&pstCipherCfg);
    if(ret)
    {
        return ret;
    }

    /*����pstCfg��Ϣ*/
    Acc_CipherCfg(pstCfg,CfgType);
    
    pTempInAddr  = (void*)((unsigned int)pInAddr + ACC_APH_LEN);
    pTempOutAddr = pOutAddr;

    /*��ȡ����FIFO�׵�ַ*/
    u32BdFifoAddr = mdrv_acc_get_bdq_addr();
    if((unsigned int)CIPHER_UNKNOWN_ERROR == u32BdFifoAddr )
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��result = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, u32BdFifoAddr);
        goto free;
    }

    /*����Cipher���ܷ�ʽ*/ 
    for(i = 0; i < u32PakNums; i++)
    {
        pstCfg->u32BlockLen = u32BlockLen;
        pstCfg->u32Offset   = 0;
        pstCfg->u32OutLen   = u32Offset;
		pstCfg->pInMemMgr   = pTempInAddr;
		pstCfg->pOutMemMgr  = pTempOutAddr;
        ret = mdrv_acc_cipher(u32BdFifoAddr, pstCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempOutAddr = (char *)pTempOutAddr + u32Offset;
        pstCfg->u32BlockLen = u32BlockLen;
        pstCfg->u32Offset   = u32Offset;
        pstCfg->u32OutLen   = u32BlockLen - u32Offset + ACC_APH_LEN;
		pstCfg->pInMemMgr   = pTempInAddr;
		pstCfg->pOutMemMgr  = pTempOutAddr;
        ret = mdrv_acc_cipher(u32BdFifoAddr, pstCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempInAddr  = (char *)pTempInAddr  + u32BlockLen  + ACC_APH_LEN;
        pTempOutAddr = (char *)pTempOutAddr + (u32BlockLen - u32Offset) + ACC_APH_LEN;
    }

    /*��ȡ��ǰͨ��״̬��������ʹ���������*/
    while(mdrv_acc_get_status(CIPHER_SECURITY_CHANNEL_0) != CHN_FREE)
    {
        g_ChnBusy ++;
    }
    ret = mdrv_acc_enable(CIPHER_SECURITY_CHANNEL_0, u32BdFifoAddr);
    if(CIPHER_UNKNOWN_ERROR == ret)
    {
        ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
        goto free;
    }   

    /*����Cipher���ܺ��������ܼ���֮�������****************************************/
    pstCipherCfg->bMemBlock       = 1;
    pstCipherCfg->enOpt           = 1;
    pstCipherCfg->u8Direction     = 0;
    pstCipherCfg->stAlgKeyInfo    = pstCfg->stAlgKeyInfo;
    pstCipherCfg->u32Count        = pstCfg->u32Count;
    pstCipherCfg->enAppdHeaderLen = 0;
    pstCipherCfg->u8BearId        = (unsigned char)pstCfg->u32BearId;
    pstCipherCfg->enHeaderLen     = 0;
    pstCipherCfg->u32BlockLen     = pstCfg->u32BlockLen;
	pstCipherCfg->enSubmAttr      = 1;
	pstCipherCfg->u32Private      = 0;

    pTempOutAddr = (void *)((unsigned int)pOutAddr + ACC_APH_LEN);
    for(i = 0; i <u32PakNums; i++)
    {
    	pstCipherCfg->pInMemMgr  = pTempOutAddr;
		pstCipherCfg->pOutMemMgr = pTempOutAddr;

        ret = mdrv_cipher_set_bdinfo(CIPHER_CHN, 1, pstCipherCfg);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempOutAddr = (char *)pTempOutAddr + u32BlockLen + ACC_APH_LEN;
    }

    /* �Ƚ����ǰ�����Ƿ���ͬ */
    for(i = 0; i <u32PakNums; i++)
    {
        pTempInAddr  = (void *)((unsigned int)pInAddr  + ACC_APH_LEN);
        pTempOutAddr = (void *)((unsigned int)pOutAddr + ACC_APH_LEN);
        ret = AccDataCmp(pTempInAddr, pTempOutAddr,u32BlockLen);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret);
            goto free;
        }
        pTempInAddr  = (void *)((unsigned int)pTempInAddr  + u32BlockLen + ACC_APH_LEN) ;
        pTempOutAddr = (void *)((unsigned int)pTempOutAddr + u32BlockLen + ACC_APH_LEN);
    }


free: 
    osl_cachedma_free(pstCipherCfg);
    osl_cachedma_free(pstCfg);
    osl_cachedma_free(pInAddr);
    osl_cachedma_free(pOutAddr);
    return ret;
       
}

/*****************************************************************************
* �� �� ��  : ACC_ST_Cipher_004
*
* ��������  :����ͷ�ļ���
* �������  :unsigned int u32LoopTimes : ѭ������
* �������  : ��
*
* �� �� ֵ  : OK&-1
*
* ����˵��  :
*
*****************************************************************************/
int ACC_ST_Cipher_004(unsigned int u32BlockLen, unsigned int u32PakNums,unsigned int u32LoopTimes,
	unsigned int CfgType)
{
    int ret;
    
    while(u32LoopTimes > 0)
    {
        ret = ACC_ST_Cipher(u32BlockLen,u32PakNums, CfgType);
        if(ret)
        {
            ACC_TEST_PRINT(">>>line %d FUNC %s fail��return = 0x%x\n", (int)__LINE__, (int)__FUNCTION__, ret, 0, 0, 0);
            return ret;
        }
        u32LoopTimes--;
    }
    return OK;
    
}

int ACC_ST_DMA_01()
{
    return ACC_ST_DMA_001(1500, 127, 10);
}

int ACC_ST_Cipher_01()
{
    ACC_APH_LEN = 1;
    return ACC_ST_Cipher_001(1500, 127, 10, 2);
}

int ACC_ST_Cipher_02()
{
    ACC_APH_LEN = 0;
    return ACC_ST_Cipher_003(1500, 60,500,10,1 );
}

int ACC_ST_DMA_Cipher_01()
{
    return ACC_ST_DMA_Cipher_001(1500, 60, 0 ,1 );
}
