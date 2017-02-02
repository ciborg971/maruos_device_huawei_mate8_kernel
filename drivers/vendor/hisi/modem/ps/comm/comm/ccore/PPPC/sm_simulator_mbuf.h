
#ifndef _SM_SIMULATOR_MBUF_H_
#define _SM_SIMULATOR_MBUF_H_

/* ĿǰUE����Ҫ�õ�500��4K���ڴ棬Ϊ�˲�Ӱ��ԭ���߼��ͽ�ʡ�ڴ濪�������޸�Ϊ10�� */
#if 0
#define SM_PGPADAPT_MBUF_MAX_NUM                   500
#endif
#define SM_PGPADAPT_MBUF_MAX_NUM                   10

#define     SM_PGPADAPT_DATABLOCK_MAX_LENGTH            4096
#define MBUF_TOO_SMALL_LENGTH 500
#define PMBUF_DATA_SIZE 2048         /* ����Ϊת����Ԥ����512�ֽ� */
#define MBUF_TRANSMIT_RESERVED_SIZE 512 /* Ϊת����Ԥ����512�ֽ� */

#define PMBUF_TRANSMIT_RESERVED_SIZE   MBUF_TRANSMIT_RESERVED_SIZE

#define SM_PGPADAPT_MBUF_CORR_PKTID_MAX_NUM      5000

#define     SM_PGP_MBUF_DATABLOCK_OFFSET                512
#define     SM_PGP_MBUF_DATABLOCK_MAX_LEN               3232

#define SOFT_PMBUF_MAX_NUM_SHIFT_NUM 10 /*1024�����PMbuf*/
#define SOFT_PMBUF_MAX_NUM (1<<SOFT_PMBUF_MAX_NUM_SHIFT_NUM)
#define SOFT_PMBUF_HIGH_THRESHOLD (SOFT_PMBUF_MAX_NUM - 1)


#define SM_MBUF_USERTAGDATA_S  MBUF_USERTAGDATA_S

#define SM_MBUF_ADD_HEAD(pstMBufM, ulLengthM)\
do{\
    if( (pstMBufM) != VOS_NULL_PTR )\
    {\
        (pstMBufM)->stDataBlockDescriptor.pucData -= (ulLengthM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataLength += (ulLengthM);\
        (pstMBufM)->ulTotalDataLength += (ulLengthM);\
    }\
}while(0)


/*-------------------------- BEGIN: Mbuf ------------------------------------*/
#define PMBUF_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PMBUF_MTOD(pstMBufM, DataTypeM) ( (DataTypeM)(pstMBufM)->stDataBlockDescriptor.pucData)

/* VOS�����������ڴ�Ϊ2k,����MBUFͷ�����ֽڳ���Ϊ256,�����һ���ܴ��Ϊ2000-256�ֽ� */
#define PMBUF_MAX_AVAILABLE_MEM_SIZE    (1744)


#define PMBUF_TAILING_SPACE(pstMBufM) \
    ((pstMBufM)->stDataBlockDescriptor.pucDataBlock + (pstMBufM)->stDataBlockDescriptor.ulDataBlockLength \
        - (pstMBufM)->stDataBlockDescriptor.pucData - (pstMBufM)->stDataBlockDescriptor.ulDataLength)

typedef struct tagMBUF_USERTAGDATA_S
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
} MBUF_USERTAGDATA_S;


#define PMBUF_S_RES_SIZE 4

typedef struct tagMBUF_DataBlockDescriptor
{
    ULONG ulDataLength;         /* ���ݿ������ݵĳ��ȣ�ȡֵ��Χ[0, ulDataBlockLength]*/
    UCHAR * pucData;            /* ���ݿ������ݵ���ʼ��ַ, [pucDataBlock + 512, pucDataBlock + ulDataBlockLength]*/
    ULONG ulDataBlockLength;    /* ���ݿ���ܳ���,*/
    UCHAR * pucDataBlock;       /* ���ݿ����ʼ��ַ�� NULL��ʾ��Ч��������ʾ��Ч */
    ULONG ulType;               /* MBUF_TYPE_XXX */
    struct tagMBUF_DataBlockDescriptor * pstNextDataBlockDescriptor;/* ��һ�����ݿ��������� Always NULL*/
}MBUF_DATABLOCKDESCRIPTOR_S,SM_MBUF_DATABLOCKDESCRIPTOR_S;    /* ���ݿ����������ݽṹ */

typedef struct tagMBuf
{
    struct tagMBuf * pstNextMBuf;                       /* ��һ��mbuf�� NULL��ʾ��Ч��������ʾ��Ч */
    ULONG ulTotalDataLength;                            /* mbuf �����ݵ��ܳ��ȣ�ͬһ��MBUF�е��������ݵĳ��Ⱥ� */
    MBUF_DATABLOCKDESCRIPTOR_S stDataBlockDescriptor;   /* Mbuf ����������Ϣ */
    ULONG ulDataBlockNumber;                            /* mbuf �����ݿ�ĸ��� */
    MBUF_USERTAGDATA_S stUserTagData;                   /* Mbuf ������Ϣ */
    ULONG ulResv[PMBUF_S_RES_SIZE-1];                   /* �ճ�4���ֽڴ�����ģʽ */
    VOS_UINT8 ucRatMode;                                /* ����ģʽ */
    VOS_UINT8 aucResv[3];
    ULONG ulMagicWord;
}MBUF_S, PMBUF_S, SM_MBUF_S, TP_PMBUF_S;  /* mbuf��ͷ��ǩ���ݽṹ */


#define MBUF_TRANSMIT_USED_SIZE 128  /* Ϊת����ʹ�õ�128�ֽ� */
#define MBUF_FAIL ((ULONG)1)
#define MBUF_OK ((ULONG)0)
#define PMBUF_OK    MBUF_OK
#define PMBUF_FAIL  MBUF_FAIL
#define PMBUF_MBUF_SIZE             ((sizeof(PMBUF_S)+(32-1))&~(32-1))
#define MBUF_INDEX_MAGIC_SIZE       32 /*mbuf������magic��С����4���ֽ�*/
#define MBUF_TOTAL_SIZE         (3*1024+512-64)//BSP_GetMakeFileMbufTotalLen()
#define MBUF_DATA_MAXLEN    (MBUF_TOTAL_SIZE - PMBUF_MBUF_SIZE - MBUF_TRANSMIT_RESERVED_SIZE - MBUF_INDEX_MAGIC_SIZE)    /* MBUF���ݶγ������� 0xaa0*/
#define PMBUF_DATA_MAXLEN                         MBUF_DATA_MAXLEN

#define PMBUF_GET_TOTAL_DATA_LENGTH(pstMBufM) ( (pstMBufM)->ulTotalDataLength )
#define PMBUF_GET_DATA_BLOCK_DESC(pstMBufM) ( & ( (pstMBufM)->stDataBlockDescriptor) )
#define PMBUF_DBD_OFFSET ((ULONG)(&((PMBUF_S*)(0))->stDataBlockDescriptor))
#define PMBUF_GET_PMBUF_FROM_DBD(_DataBlockDescriptor) ((PMBUF_S*)((DULONG)(_DataBlockDescriptor) - PMBUF_DBD_OFFSET))
#define FWD_GET_PMBUF_FROM_DBD(pDataBlockDescriptor) \
    ((PMBUF_S *)(((PF_UCHAR*)pDataBlockDescriptor) - offsetof(PMBUF_S, stDataBlockDescriptor)))



#define PMBUF_PREPEND_MEMORY_SPACE(pstMBufM, ulLengthM, ulModuleIDM, ulResultM) \
do{ \
    PMBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor; \
\
    if ( (pstMBufM) != NULL) \
    { \
        pstDataBlockDescriptor = &( (pstMBufM)->stDataBlockDescriptor ); \
        if ((ulLengthM) > ((ULONG)(pstDataBlockDescriptor->pucData) -\
            (ULONG)(pstDataBlockDescriptor->pucDataBlock) - \
             MBUF_TRANSMIT_USED_SIZE)) \
        { \
            (ulResultM) = MBUF_FAIL; \
        }\
        else \
        { \
            pstDataBlockDescriptor->pucData -= (ulLengthM); \
            pstDataBlockDescriptor->ulDataLength += (ulLengthM); \
            (pstMBufM)->ulTotalDataLength += (ulLengthM); \
            (ulResultM) = MBUF_OK; \
        }  \
    }else \
    { \
        (ulResultM) = MBUF_FAIL; \
    } \
}while(0)

#define MBUF_MBUF_SIZE ((sizeof(MBUF_S)+(32-1))&~(32-1))
#define MBUF_TYPE_DATA  1


#define MBUF_CREATE_BY_DATA_BLOCK(pstMBufM, pucDataBlockM, ulDataBlockLengthM,  pucDataM, \
    ulDataLengthM, ulReceiveIfnetIndexM, ulModuleIDM)\
do{\
    (pstMBufM) = PPP_Malloc(MBUF_MBUF_SIZE);\
    if( (pstMBufM) != NULL)\
    {\
        (pstMBufM)->stDataBlockDescriptor.pstNextDataBlockDescriptor = NULL;\
        (pstMBufM)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
        (pstMBufM)->stDataBlockDescriptor.pucData = (pucDataM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
        (pstMBufM)->stDataBlockDescriptor.ulType = MBUF_TYPE_DATA;/*???*/\
        PPP_MemSet( (VOID *) (& pstMBufM->stUserTagData), 0 , sizeof(MBUF_USERTAGDATA_S));\
        (pstMBufM)->ulTotalDataLength = (ulDataLengthM);\
        (pstMBufM)->ulDataBlockNumber = 1;\
        (pstMBufM)->pstNextMBuf = NULL;\
    }\
}while(0)

#define PMBUF_MAKE_MEMORY_CONTINUOUS(pstMBufM, ulLengthM, ulModuleIDM, ulResultM) \
do{\
    if( (pstMBufM) != NULL )\
    {\
        if( (pstMBufM)->stDataBlockDescriptor.ulDataLength < (ulLengthM) )\
        {\
            (ulResultM) = PMBUF_PullUp( (pstMBufM), (ulLengthM), (ulModuleIDM) );\
        }\
        else\
        {\
            (ulResultM) = MBUF_OK;\
        }\
    }\
    else\
    {\
        (ulResultM) = MBUF_FAIL;\
    }\
}while(0)


#define PMBUF_GET_DATA_BLOCK_DESC_INFO(pstDataBlockDescriptorM, pucDataM, ulDataLengthM, pstNextDataBlockDescriptorM)\
do{\
    (pucDataM) = (pstDataBlockDescriptorM)->pucData;\
    (ulDataLengthM) = (pstDataBlockDescriptorM)->ulDataLength;\
    (pstNextDataBlockDescriptorM) = (pstDataBlockDescriptorM)->pstNextDataBlockDescriptor;\
}while(0)

/* Mbuf���롢�ͷż������Ϣbegin */
typedef struct tagSmPgpAdaptPacketInfo
{
    MBUF_S*  pstMbuf;
    SM_ULONG ulPacketId;
}SM_PGPADAPT_PACKET_INFO_S;

#define FWD_COMMCHANNEL_SIZE    sizeof(FWD_COMCHANNEL_S)

enum
{
    PMBUF_ERR = 1,
    PMBUF_REFREE,
    PMBUF_REUSED,
#ifndef __VXWORKS_PLATFORM__
    PMBUF_BDQ_FULL,
    PMBUF_POOL_FULL,
    PMBUF_PKT_ERR,
#endif
};

typedef struct tagSmPgpAdaptMbuf
{
    MBUF_S    stMbuf;
    SM_UCHAR  aucDataBlock[SM_PGPADAPT_DATABLOCK_MAX_LENGTH];
    SM_ULONG  ulUsed;
    SM_ULONG  ulMID;
    SM_ULONG  ulDataBlockMallocNum;
    SM_ULONG  ulDataBlockFreeNum;
}SM_PGPADAPT_MBUF_S;


typedef struct tagSmPgpAdaptMbufInfo
{
    SM_PGPADAPT_MBUF_S   astPgpAdaptMbuf[SM_PGPADAPT_MBUF_MAX_NUM];
    SM_ULONG ulMbufMallocNum;
    SM_ULONG ulMbufFreeNum;
}SM_PGPADAPT_MBUF_INFO_S;

typedef struct tagSmPgpAdaptMbufCheckResult
{
    SM_BOOL  bIfMbufMallocEqualFree;
    SM_ULONG ulMbufMallocNum;
    SM_ULONG ulMbufFreeNum;
    SM_ULONG ulMbufUsedNum;
    SM_ULONG ulMbufErrNum;  /* �����DataBlock�����ͷŵ���Ŀ���� */
    SM_ULONG ulMbufExistRelationNum;  /*Mbuf��Packet Id�Ķ�Ӧ��ϵû�б���� */
}SM_PGPADAPT_MBUF_CHECK_RESULT_S;

extern SM_ULONG sm_plt_concatenateMbuf(SM_MBUF_S * pstDestinationMBuf, SM_MBUF_S * pstSourceMBuf, SM_ULONG ulModuleID);

extern SM_MBUF_S* sm_plt_createForControlPacket(SM_ULONG ulReserveHeadSpace, SM_ULONG ulLength,
                                                SM_ULONG ulType, SM_ULONG ulModuleID);

extern SM_UCHAR *sm_plt_AppendMemorySpace(SM_MBUF_S * pstMBuf, SM_ULONG ulLength, SM_ULONG ulModuleID);


SM_VOID _pgpAdapt_clearMbufInfo
(
    IN      SM_PGPADAPT_MBUF_CHECK_RESULT_S*  pstMbufCheckResult
);

SM_VOID _pgpAdapt_reportMbufFailureInfo
(
    IN      SM_PGPADAPT_MBUF_CHECK_RESULT_S* pstResult,
    IN      SM_VOID* pFile
);

SM_BOOL _pgpAdapt_checkMbufInfo
(
    OUT  SM_PGPADAPT_MBUF_CHECK_RESULT_S* pstResult
);

SM_VOID sm_pgpAdapt_releaseMbuf
(
    IN  MBUF_S*     pstMBuf
);

MBUF_S* sm_pgpAdapt_getMbuf
(
    IN      SM_ULONG ulMID
);

ULONG PMBUF_CopyDataFromBufferToPMBuf(SM_MBUF_S * pstMBuf, ULONG ulOffset,
                              ULONG ulLength, UCHAR * pucBuffer, ULONG ulModuleID);

ULONG sm_plt_neatConcatenateMbuf(SM_MBUF_S * pstDestinationMBuf, SM_MBUF_S * pstSourceMBuf,
                                 SM_MBUF_DATABLOCKDESCRIPTOR_S ** ppstLastDataBlockDescriptor,
                                 SM_ULONG ulModuleID);

ULONG PMBUF_CopyDataFromPMBufToBuffer(SM_MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer);

PMBUF_S *PMBUF_GetPMbuf(ULONG ulSubMod, ULONG ulLen);

ULONG PMBUF_Destroy(PMBUF_S * pstMbuf);

MBUF_DATABLOCKDESCRIPTOR_S *PMBUF_GetNextDataBlock
(
    ULONG                               ulSubMod,
    ULONG                               ulDataBlockLen,
    ULONG                              *pulBlockNum
);

ULONG PMBUF_DataBlockDestroy(MBUF_DATABLOCKDESCRIPTOR_S *pstHeadDataBlock);

PF_VOID MBUF_UPDATE_BY_LEN(PMBUF_S* pstMBuf,PF_LONG lLen);

PF_VOID MBUF_UPDATE_BY_LEN_TAIL(PMBUF_S* pstMBuf,PF_LONG lLen);

PF_VOID MBUF_UPDATE_LENGTH(PMBUF_S* pstMBuf,PF_LONG lLen);

extern ULONG PMBUF_PullUp(SM_MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);

#endif /* _SM_SIMULATOR_MBUF_H_ */
