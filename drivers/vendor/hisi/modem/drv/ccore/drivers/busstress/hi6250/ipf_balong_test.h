#ifndef C_IPF_BALONG_TEST_H
#define C_IPF_BALONG_TEST_H

#include <string.h>
#include <osl_thread.h>
#include <osl_cache.h>
#include "osal.h"
#include "osl_malloc.h"
#include "osl_sem.h"
#include "securec.h"
#include <bsp_ipf.h>
#include <bsp_hardtimer.h>
#include "ipf_balong.h"

#define T_DL_VALUE		0x5a
#define T_UL_VALUE		0x5b

typedef struct tagStreamIPv4Header
{
    unsigned int TOL:16;
    unsigned int TOS:8;
    unsigned int HeaderLen:4;
    unsigned int Vers:4; 
    unsigned int offset:13;
    unsigned int MF:1;
    unsigned int DF:1;
    unsigned int ReservFlag:1;
    unsigned int ID:16;
    unsigned int Checksum:16;
    unsigned int Prot:8;
    unsigned int TTL:8;    
    unsigned int SourceAddr;
    unsigned int DestAddr;
}StreamIPv4Header;

typedef struct tagStreamUDP
{
    unsigned int DstPort:16;
    unsigned int SrcPort:16;
    unsigned int Checksum:16;
    unsigned int Length:16;    
}StreamUDP;


//-psam test file needs ttf struct
#define TTF_OFFSET_OF_T(s, m) ((unsigned int)&(((s *)0)->m))
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                  usAllocFileId;      /* File ID when alloc or free */
    unsigned short                  usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                  usTraceFileId;      /* File ID when traced */
    unsigned short                  usTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct _TTF_NODE_ST
{
    struct _TTF_NODE_ST    *pNext;
    struct _TTF_NODE_ST    *pPrev;
} TTF_NODE_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned char                   ucPoolId;       /*���ڴ�������һ���ڴ�� */
    unsigned char                   ucClusterId;    /*���ڴ���������һ������*/
    unsigned char                   ucReserve[2];
    struct _TTF_MEM_ST             *pNext;          /* �����ݵ���һ�� */
    unsigned short                  usType;         /* �ڴ����ͣ�DYN��BLK��EXT���� */
    unsigned short                  usLen;          /* �������ݵ��ܳ��ȣ�����һ��ȫ����ʹ�� */
    unsigned short                  usUsed;         /* �Ѿ�ʹ�õ����ݳ���   */
    unsigned short                  usApp;          /* ʹ���߿���ʹ�õ����� */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;      /* ��¼���ݵ�ԭʼָ�� */
    unsigned char                  *pData;          /* ������ݵ�ָ�룬������ָ��ṹ��������ڴ� */
    void                           *pExtBuffAddr;   /* ����extern���͵��ڴ��ַ�����ͷ� */
    unsigned long                   ulForCds[1];    /*Ԥ����CDSʹ�ã�GUģ���ó�ʼ��*/

#if( FEATURE_LTE == FEATURE_ON )
    unsigned long                   ulForLte[6];    /*Ԥ����LTEʹ�ã�GUģ���ó�ʼ��*/
#endif
} TTF_MEM_ST;
//+psam test file needs ttf struct


void ipf_set_ccore_reset_flag(unsigned int flag);


#endif
