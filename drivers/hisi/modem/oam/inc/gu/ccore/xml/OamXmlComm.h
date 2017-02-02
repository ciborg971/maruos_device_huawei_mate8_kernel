

#ifndef _OAM_XML_COMM_H_
#define _OAM_XML_COMM_H_

/*****************************************************************************
1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "pamom.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
2 �궨��
*****************************************************************************/
#define OAM_XML_MAX_LEVEL                      (10)                /* ֧�ֵ�XML������    */
#define OAM_XML_BUFF_SIZE                      (8000)              /* XML�������ڴ泤��    */
#define OAM_XML_MAX_STACK_DEPTH                (100)               /* Ŀǰ����ջ���Ϊ100  */
#define OAM_XML_MAX_NUM_LEN                    (11)                /* �з�����������󳤶� */
#define OAM_XML_INDENTATION_SPACE_NUM          (4)                 /* �����ո����         */
#define OAM_XML_ATTRIB_PUNCTUATION_LEN         (4)                 /* ����ֵ�а������ַ��� */
#define OAM_XML_CRLF_LEN                       (2)                 /* �س����з��ĳ���     */
#define OAM_XML_LABEL_START_LEN                (1)                 /* ��ǩ��ʼ��"<"����    */
#define OAM_XML_LABEL_END_LEN                  (1)                 /* ��ǩ������">"����    */
#define OAM_XML_SINGLE_LABLE_END_LEN           (2)                 /* ����ǩ������"/>"���� */
#define OAM_XML_END_LABEL_START_LEN            (2)                 /* �ұ�ǩ��ʼ��"</"���� */
#define OAM_XML_MAX_STR_LEN                    (10240)             /* ����XML������󳤶�  */
/* XML�����汾��Ϣ�ַ��� */
#define OAM_XML_VERSION_STR                     "<?xml version=\"1.0\" encoding=\"utf-8\"?>"

#if (VOS_WIN32 == VOS_OS_VER)
#define XML_WARNING_LOG(string)                 vos_printf("%s \r\n", string)
#define XML_WARNING1_LOG(string, para1)         vos_printf("%s %d.\r\n", string, para1)
#define XML_WARNING2_LOG(string, para1, para2)  vos_printf("%s %d, %d.\r\n", string, para1, para2)
#define XML_ERROR_LOG(string)                   vos_printf("%s \r\n", string)
#define XML_ERROR1_LOG(string, para1)           vos_printf("%s %d.\r\n", string, para1)
#define XML_ERROR2_LOG(string, para1, para2)    vos_printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define XML_WARNING_LOG(string)                 PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_WARNING,  string)
#define XML_WARNING1_LOG(string, para1)         PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_WARNING,  string, (VOS_INT32)para1)
#define XML_WARNING2_LOG(string, para1, para2)  PS_LOG2(WUEPS_PID_USIM, 0, PS_PRINT_WARNING,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#define XML_ERROR_LOG(string)                   PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,  string)
#define XML_ERROR1_LOG(string, para1)           PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,  string, (VOS_INT32)para1)
#define XML_ERROR2_LOG(string, para1, para2)    PS_LOG2(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#endif

/*****************************************************************************
3 ö�ٶ���
*****************************************************************************/


enum OAM_XML_RESULT_ENUM
{
    OAM_XML_RESULT_SUCCEED                         = 0 ,   /* �ɹ�                 */

    /* XML��ʽ�������������еĽ���� */
    OAM_XML_RESULT_SUCCEED_ALL_ENDS                    ,   /* ��������             */
    OAM_XML_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT        ,   /* ���ڵ�����ڷǷ��ַ� */
    OAM_XML_RESULT_FALIED_DECLARATION_NO_END           ,   /* XML����δ��ȷ����    */
    OAM_XML_RESULT_FALIED_COMMENT_NO_END               ,   /* ע��δ��ȷ����       */
    OAM_XML_RESULT_FALIED_COMMENT_SYNTAX_ERROR         ,   /* ע���﷨����         */
    OAM_XML_RESULT_FALIED_LABEL_NAMES_NOT_SAME         ,   /* ���ұ�ǩ����ƥ��     */
    OAM_XML_RESULT_FALIED_BAD_LABEL_NAME               ,   /* ��ǩ���Ƿ�           */
    OAM_XML_RESULT_FALIED_BAD_END_LABEL                ,   /* �������β��ǩ       */
    OAM_XML_RESULT_FALIED_BAD_ATTRIB_NAME              ,   /* �������Ƿ�           */
    OAM_XML_RESULT_FALIED_CREATE_NODE_ERROR            ,   /* �����ڵ����         */
    OAM_XML_RESULT_FALIED_CREATE_ATTRIB_ERROR          ,   /* �������Դ���         */
    OAM_XML_RESULT_FALIED_EXPECT_EQUAL_SIGN            ,   /* ���������Ҳ����Ⱥ�   */
    OAM_XML_RESULT_FALIED_NO_QUOTATION_MARK            ,   /* ȱ������ֵ������     */
    OAM_XML_RESULT_FALIED_CHAR_UNEXPECT                ,   /* �����Ƿ��ַ�         */
    OAM_XML_RESULT_FALIED_ANALYSE_STATUS_ERROR         ,   /* �Ƿ��Ľ���״̬       */

    /* �ṩ�������ýӿڷ��صĴ����� */
    OAM_XML_RESULT_FAILED_ATTRIB_NOT_FOUND             ,   /* û�ҵ�ָ��������     */
    OAM_XML_RESULT_FAILED_NODE_NOT_FOUND               ,   /* û�ҵ�ָ���Ľڵ�     */
    OAM_XML_RESULT_FAILED_CANT_UNLOAD_ROOT_NODE        ,   /* ���ڵ㲻����       */
    OAM_XML_RESULT_FALIED_PARA_NULL_POINTER            ,   /* ������ָ��           */
    OAM_XML_RESULT_FALIED_MEM_NOT_ENOUGH               ,   /* �ڴ治��             */
    OAM_XML_RESULT_FALIED_MALLOC                       ,   /* �ڴ�����ʧ��         */

    OAM_XML_RESULT_BUTT
};
typedef VOS_UINT32 OAM_XML_RESULT_ENUM_UINT32;



enum OAM_XML_ANALYSE_STATUS_ENUM
{
    OAM_XML_PARSE_ORIGINAL                     = 0 , /* ��ʼ״̬               */
    OAM_XML_PARSE_ENTER_LABEL                      , /* �����ǩ               */
    OAM_XML_PARSE_DECLARATION                      , /* XML����                */
    OAM_XML_PARSE_COMMENT                          , /* ע��״̬               */
    OAM_XML_PARSE_NODE_LABEL_START                 , /* ������ǩ��             */
    OAM_XML_PARSE_SINGLE_ENDS_LABEL                , /* ������β��ǩ           */
    OAM_XML_PARSE_LABEL_END_MUST_RIGHT             , /* ��ǩ��ʼ����β         */
    OAM_XML_PARSE_ATTRIB_START                     , /* ��ʼ��������           */
    OAM_XML_PARSE_ATTRIB_NAME_START                , /* ��ʼ������������       */
    OAM_XML_PARSE_ATTRIB_NAME_END                  , /* �������ƽ������ȴ����� */
    OAM_XML_PARSE_ATTRIB_VALUE_SINGLE              , /* �Ե����Ž���������ֵ   */
    OAM_XML_PARSE_ATTRIB_VALUE_DOUBLE              , /* ��˫���Ž���������ֵ   */
    OAM_XML_PARSE_AFTER_ROOT_NODE                  , /* ���ڵ������           */
    OAM_XML_RESULT_FALIED_UNKOWN_ERROR             , /* δ֪���� */
    OAM_XML_PARSE_BUTT
};
typedef VOS_UINT32 OAM_XML_ANALYSE_STATUS_ENUM_UINT32;


enum OAM_XML_FORMATTING_ENUM
{
    XML_FORMATTING_NONE                 = 0 , /* �޸�ʽ, �����ո�ʽ  */
    XML_FORMATTING_INDENTED                 , /* ����������ʽ        */
    XML_FORMATTING_BUTT
};
typedef VOS_UINT8 OAM_XML_FORMATTING_ENUM_UINT8;


/*****************************************************************************
4 UNION����
*****************************************************************************/


/*****************************************************************************
5 OTHERS����
*****************************************************************************/


/*****************************************************************************
6 STRUCT����
*****************************************************************************/


typedef struct OAM_XML_NODE_ATTRIBUTE
{
    /* ����˫������ */
    struct OAM_XML_NODE_ATTRIBUTE     *pstPreBrother;              /* �������                 */
    struct OAM_XML_NODE_ATTRIBUTE     *pstNexBrother;              /* �ܵ�����                 */

    /* �������� */
    VOS_CHAR                           *pcAttribName;               /* ��������                 */
    VOS_CHAR                           *pcAttribValue;              /* ����ֵ                   */

    VOS_UINT32                          ulNameLength;               /* pcAttribName  ���������� */
    VOS_UINT32                          ulValueLength;              /* pcAttribValue ���������� */

}OAM_XML_NODE_ATTRIBUTE_STRU;


typedef struct OAM_XML_NODE
{
    /* ���νṹ���ӵ� */
    struct OAM_XML_NODE               *pstFather;                  /* ���ڵ�                    */
    struct OAM_XML_NODE               *pstPreBrother;              /* ���ڵ�                  */
    struct OAM_XML_NODE               *pstNexBrother;              /* �ܵܽڵ�                  */
    struct OAM_XML_NODE               *pstFirstChild;              /* ����ӽڵ�                */

    /* ���ڵ��������� */
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstFirstAttrib;             /* ��һ������                */

    /* �ڵ����� */
    VOS_CHAR                           *pcNodeLabel;                /* �ڵ��ǩ                  */
    VOS_CHAR                           *pcNodeLabelEnd;             /* ��β������ǩ              */
    VOS_CHAR                           *pcNodeValue;                /* �ڵ�ֵ                    */

    VOS_UINT32                          ulLabelLength;              /* pcNodeLabel    ���������� */
    VOS_UINT32                          ulLabelEndLength;           /* pcNodeLabelEnd ���������� */
    VOS_UINT32                          ulValueLength;              /* pcNodeValue    ���������� */

}OAM_XML_NODE_STRU;


typedef struct OAM_XML_CTX
{
    VOS_UINT8                          *pucXMLBuffer;               /* �ڵ㡢�����ڴ����׵�ַ    */
    VOS_UINT8                          *pucXMLBuffCur;              /* �ڴ�����ǰ�����ַ        */
    VOS_UINT32                          ulXMLBuffSize;              /* �ڴ�����С                */
}OAM_XML_CTX_STRU;
typedef struct OAM_XML_CTX_INNER
{
    OAM_XML_CTX_STRU                  *pstXMLCtx;                  /* �������ṩ��������        */
    OAM_XML_NODE_STRU                 *pstXMLRootNode;             /* ���ڵ�                    */
    OAM_XML_NODE_STRU                 *pstXMLCurrentNode;          /* ��ǰ�ڵ�                  */
    VOS_CHAR                           *pcXMLStrCurChar;            /* ��ǰ�����ַ�              */
    OAM_XML_ANALYSE_STATUS_ENUM_UINT32 enXMLAnalyseStatus;         /* ��ǰ����״̬              */
}OAM_XML_CTX_INNER_STRU;

/*****************************************************************************
7 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
8 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
10 ��������
*****************************************************************************/

/* ȡ��ĳ�ڵ��ӽڵ����� */
VOS_INT32 OAM_XML_GetChildCount(OAM_XML_NODE_STRU *pstNode);

/* ��������ȡ��ĳ�ڵ��ӽڵ�, ������0��ʼ */
OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByIndex(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_INT32                           lChildIndex);

/* ���ձ�ǩ����ȡ��ĳ�ڵ��ӽڵ� */
OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByLabel(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabel);

/* ��������ֵȡ��ĳ�ڵ��ӽڵ� */
OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByAttributeValue(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribValue);

/* ȡ��ĳ�ڵ��������� */
VOS_INT32 OAM_XML_GetAttributeCount(OAM_XML_NODE_STRU *pstNode);

/* ��������ȡ��ĳ�ڵ�����ֵ, ������0�� */
OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetAttributeByIndex(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_INT32                           lAttribIndex);

/* ����������ȡ��ĳ�ڵ����� */
OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetAttributeByAttributeName(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribName);

/* ��ʼ��XML API������ */
OAM_XML_RESULT_ENUM_UINT32 OAM_XML_InitXMLCtx(OAM_XML_CTX_STRU *pstXmlCtx);

/* �����������XML��ʽ�����׵�ַ��XML�����ģ����XML���ĸ��ڵ� */
OAM_XML_NODE_STRU* OAM_XML_BuildXMLTree(
    VOS_CHAR                           *pcXmlStr,
    OAM_XML_CTX_STRU                  *pstXmlCtx);

/* ����XML������ */
OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ClearXMLCtx(OAM_XML_CTX_STRU *pstXmlCtx);

/* ��ȡ�ַ������� */
VOS_VOID OAM_XML_GetStrContent(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pcDst, VOS_UINT32 *pulDstLen);

VOS_VOID OAM_XML_FilterStrInvalidChar(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pcDst, VOS_UINT32 *pulDstLen);

/* ת���ַ���ΪAscii */
VOS_UINT32 OAM_XML_GetIntArray(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_UINT8 *pucDst, VOS_UINT32 *pulDstLen);

OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_SearchAttNodeByName(
                                    OAM_XML_NODE_ATTRIBUTE_STRU *pstFirstAttrNode,
                                    VOS_CHAR                    *pcAttribName);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
    #pragma pack()
#else
    #pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* _OAM_XML_COMM_H_ */

