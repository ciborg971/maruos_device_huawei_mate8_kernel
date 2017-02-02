

#ifndef _XML_COMM_H_
#define _XML_COMM_H_

/*****************************************************************************
1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */

#ifdef __cplusplus
    #if __cplusplus
        extern "C"{
    #endif
#endif

#pragma pack(4)

#if (FEATURE_ON == FEATRUE_XML_PARSER)
/*****************************************************************************
2 �궨��
*****************************************************************************/
#define XML_COMM_MAX_LEVEL                      (10)                /* ֧�ֵ�XML������    */
#define XML_COMM_BUFF_SIZE                      (16000)             /* XML�������ڴ泤��    */
#define XML_COMM_MAX_STACK_DEPTH                (100)               /* Ŀǰ����ջ���Ϊ100  */
#define XML_COMM_MAX_NUM_LEN                    (11)                /* �з�����������󳤶� */
#define XML_COMM_INDENTATION_SPACE_NUM          (4)                 /* �����ո����         */
#define XML_COMM_ATTRIB_PUNCTUATION_LEN         (4)                 /* ����ֵ�а������ַ��� */
#define XML_COMM_CRLF_LEN                       (2)                 /* �س����з��ĳ���     */
#define XML_COMM_LABEL_START_LEN                (1)                 /* ��ǩ��ʼ��"<"����    */
#define XML_COMM_LABEL_END_LEN                  (1)                 /* ��ǩ������">"����    */
#define XML_COMM_SINGLE_LABLE_END_LEN           (2)                 /* ����ǩ������"/>"���� */
#define XML_COMM_END_LABEL_START_LEN            (2)                 /* �ұ�ǩ��ʼ��"</"���� */
#define XML_COMM_MAX_STR_LEN                    (10240)             /* ����XML������󳤶�  */
/* XML�����汾��Ϣ�ַ��� */
#define XML_COMM_VERSION_STR                     "<?xml version=\"1.0\" encoding=\"utf-8\"?>"

#if (VOS_WIN32 == VOS_OS_VER)
#define XML_WARNING_LOG(string)                 vos_printf("%s \r\n", string)
#define XML_WARNING1_LOG(string, para1)         vos_printf("%s %d.\r\n", string, para1)
#define XML_WARNING2_LOG(string, para1, para2)  vos_printf("%s %d, %d.\r\n", string, para1, para2)
#define XML_ERROR_LOG(string)                   vos_printf("%s \r\n", string)
#define XML_ERROR1_LOG(string, para1)           vos_printf("%s %d.\r\n", string, para1)
#define XML_ERROR2_LOG(string, para1, para2)    vos_printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define XML_WARNING_LOG(string)                 TAF_LOG(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_WARNING,  string)
#define XML_WARNING1_LOG(string, para1)         TAF_LOG1(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1)
#define XML_WARNING2_LOG(string, para1, para2)  TAF_LOG2(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#define XML_ERROR_LOG(string)                   TAF_LOG(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_ERROR,  string)
#define XML_ERROR1_LOG(string, para1)           TAF_LOG1(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1)
#define XML_ERROR2_LOG(string, para1, para2)    TAF_LOG2(WUEPS_PID_TAF, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#endif

/*****************************************************************************
3 ö�ٶ���
*****************************************************************************/


enum XML_COMM_RESULT_ENUM
{
    XML_COMM_RESULT_SUCCEED                         = 0 ,   /* �ɹ�                 */

    /* XML��ʽ�������������еĽ���� */
    XML_COMM_RESULT_SUCCEED_ALL_ENDS                    ,   /* ��������             */
    XML_COMM_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT        ,   /* ���ڵ�����ڷǷ��ַ� */
    XML_COMM_RESULT_FALIED_DECLARATION_NO_END           ,   /* XML����δ��ȷ����    */
    XML_COMM_RESULT_FALIED_COMMENT_NO_END               ,   /* ע��δ��ȷ����       */
    XML_COMM_RESULT_FALIED_COMMENT_SYNTAX_ERROR         ,   /* ע���﷨����         */
    XML_COMM_RESULT_FALIED_LABEL_NAMES_NOT_SAME         ,   /* ���ұ�ǩ����ƥ��     */
    XML_COMM_RESULT_FALIED_BAD_LABEL_NAME               ,   /* ��ǩ���Ƿ�           */
    XML_COMM_RESULT_FALIED_BAD_END_LABEL                ,   /* �������β��ǩ       */
    XML_COMM_RESULT_FALIED_BAD_ATTRIB_NAME              ,   /* �������Ƿ�           */
    XML_COMM_RESULT_FALIED_CREATE_NODE_ERROR            ,   /* �����ڵ����         */
    XML_COMM_RESULT_FALIED_CREATE_ATTRIB_ERROR          ,   /* �������Դ���         */
    XML_COMM_RESULT_FALIED_EXPECT_EQUAL_SIGN            ,   /* ���������Ҳ����Ⱥ�   */
    XML_COMM_RESULT_FALIED_NO_QUOTATION_MARK            ,   /* ȱ������ֵ������     */
    XML_COMM_RESULT_FALIED_CHAR_UNEXPECT                ,   /* �����Ƿ��ַ�         */
    XML_COMM_RESULT_FALIED_ANALYSE_STATUS_ERROR         ,   /* �Ƿ��Ľ���״̬       */

    /* �ṩ�������ýӿڷ��صĴ����� */
    XML_COMM_RESULT_FAILED_ATTRIB_NOT_FOUND             ,   /* û�ҵ�ָ��������     */
    XML_COMM_RESULT_FAILED_NODE_NOT_FOUND               ,   /* û�ҵ�ָ���Ľڵ�     */
    XML_COMM_RESULT_FAILED_CANT_UNLOAD_ROOT_NODE        ,   /* ���ڵ㲻����       */
    XML_COMM_RESULT_FALIED_PARA_NULL_POINTER            ,   /* ������ָ��           */
    XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH               ,   /* �ڴ治��             */
    XML_COMM_RESULT_FALIED_MALLOC                       ,   /* �ڴ�����ʧ��         */
    XML_COMM_RESULT_FALIED_UNKOWN_ERROR                 ,   /* δ֪���� */

    XML_COMM_RESULT_BUTT
};
typedef VOS_UINT32 XML_COMM_RESULT_ENUM_UINT32;
enum XML_COMM_ANALYSE_STATUS_ENUM
{
    XML_COMM_PARSE_ORIGINAL                     = 0 , /* ��ʼ״̬               */
    XML_COMM_PARSE_ENTER_LABEL                      , /* �����ǩ               */
    XML_COMM_PARSE_DECLARATION                      , /* XML����                */
    XML_COMM_PARSE_COMMENT                          , /* ע��״̬               */
    XML_COMM_PARSE_NODE_LABEL_START                 , /* ������ǩ��             */
    XML_COMM_PARSE_SINGLE_ENDS_LABEL                , /* ������β��ǩ           */
    XML_COMM_PARSE_LABEL_END_MUST_RIGHT             , /* ��ǩ��ʼ����β         */
    XML_COMM_PARSE_ATTRIB_START                     , /* ��ʼ��������           */
    XML_COMM_PARSE_ATTRIB_NAME_START                , /* ��ʼ������������       */
    XML_COMM_PARSE_ATTRIB_NAME_END                  , /* �������ƽ������ȴ����� */
    XML_COMM_PARSE_ATTRIB_VALUE_SINGLE              , /* �Ե����Ž���������ֵ   */
    XML_COMM_PARSE_ATTRIB_VALUE_DOUBLE              , /* ��˫���Ž���������ֵ   */
    XML_COMM_PARSE_AFTER_ROOT_NODE                  , /* ���ڵ������           */
    XML_COMM_PARSE_BUTT
};
typedef VOS_UINT32 XML_COMM_ANALYSE_STATUS_ENUM_UINT32;
enum XML_COMM_FORMATTING_ENUM
{
    XML_FORMATTING_NONE                 = 0 , /* �޸�ʽ, �����ո�ʽ  */
    XML_FORMATTING_INDENTED                 , /* ����������ʽ        */
    XML_FORMATTING_BUTT
};
typedef VOS_UINT8 XML_COMM_FORMATTING_ENUM_UINT8;


/*****************************************************************************
4 UNION����
*****************************************************************************/


/*****************************************************************************
5 OTHERS����
*****************************************************************************/


/*****************************************************************************
6 STRUCT����
*****************************************************************************/


typedef struct XML_COMM_NODE_ATTRIBUTE
{
    /* ����˫������ */
    struct XML_COMM_NODE_ATTRIBUTE     *pstPreBrother;              /* �������                 */
    struct XML_COMM_NODE_ATTRIBUTE     *pstNexBrother;              /* �ܵ�����                 */

    /* �������� */
    VOS_CHAR                           *pcAttribName;               /* ��������                 */
    VOS_CHAR                           *pcAttribValue;              /* ����ֵ                   */

    VOS_UINT32                          ulNameLength;               /* pcAttribName  ���������� */
    VOS_UINT32                          ulValueLength;              /* pcAttribValue ���������� */

}XML_COMM_NODE_ATTRIBUTE_STRU;


typedef struct XML_COMM_NODE
{
    /* ���νṹ���ӵ� */
    struct XML_COMM_NODE               *pstFather;                  /* ���ڵ�                    */
    struct XML_COMM_NODE               *pstPreBrother;              /* ���ڵ�                  */
    struct XML_COMM_NODE               *pstNexBrother;              /* �ܵܽڵ�                  */
    struct XML_COMM_NODE               *pstFirstChild;              /* ����ӽڵ�                */

    /* ���ڵ��������� */
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstFirstAttrib;             /* ��һ������                */

    /* �ڵ����� */
    VOS_CHAR                           *pcNodeLabel;                /* �ڵ��ǩ                  */
    VOS_CHAR                           *pcNodeLabelEnd;             /* ��β������ǩ              */
    VOS_CHAR                           *pcNodeValue;                /* �ڵ�ֵ                    */

    VOS_UINT32                          ulLabelLength;              /* pcNodeLabel    ���������� */
    VOS_UINT32                          ulLabelEndLength;           /* pcNodeLabelEnd ���������� */
    VOS_UINT32                          ulValueLength;              /* pcNodeValue    ���������� */

}XML_COMM_NODE_STRU;


typedef struct XML_COMM_CTX
{
    VOS_UINT8                          *pucXMLBuffer;               /* �ڵ㡢�����ڴ����׵�ַ    */
    VOS_UINT8                          *pucXMLBuffCur;              /* �ڴ�����ǰ�����ַ        */
    VOS_UINT32                          ulXMLBuffSize;              /* �ڴ�����С                */
}XML_COMM_CTX_STRU;
typedef struct XML_COMM_CTX_INNER
{
    XML_COMM_CTX_STRU                  *pstXMLCtx;                  /* �������ṩ��������        */
    XML_COMM_NODE_STRU                 *pstXMLRootNode;             /* ���ڵ�                    */
    XML_COMM_NODE_STRU                 *pstXMLCurrentNode;          /* ��ǰ�ڵ�                  */
    VOS_CHAR                           *pcXMLStrCurChar;            /* ��ǰ�����ַ�              */
    XML_COMM_ANALYSE_STATUS_ENUM_UINT32 enXMLAnalyseStatus;         /* ��ǰ����״̬              */
}XML_COMM_CTX_INNER_STRU;
typedef struct XML_COMM_TRAVERSE_STACK_NODE
{
    XML_COMM_NODE_STRU                 *pstXmlNode;
    VOS_UINT32                          ulVisited;                              /* �ýڵ��Ƿ��Ѿ������� */
}XML_COMM_TRAVERSE_STACK_NODE_STRU;
typedef struct XML_COMM_TRAVERSE_STACK
{
    XML_COMM_TRAVERSE_STACK_NODE_STRU   astStackNode[XML_COMM_MAX_STACK_DEPTH]; /* ����XML������Ҫ��ջ */
    VOS_UINT32                          ulStackDepth;
}XML_COMM_TRAVERSE_STACK_STRU;

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
VOS_INT32 XML_COMM_GetChildCount(XML_COMM_NODE_STRU *pstNode);

/* ��������ȡ��ĳ�ڵ��ӽڵ�, ������0��ʼ */
XML_COMM_NODE_STRU* XML_COMM_GetChildNodeByIndex(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lChildIndex);

/* ���ձ�ǩ����ȡ��ĳ�ڵ��ӽڵ� */
XML_COMM_NODE_STRU* XML_COMM_GetChildNodeByLabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabel);

/* ���ڵ��ǩ���Ƿ���Ŀ��ֵ��ͬ */
VOS_UINT32 XML_COMM_CheckLabelName(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabelName);

/* ȡ��ĳ�ڵ��������� */
VOS_INT32 XML_COMM_GetAttributeCount(XML_COMM_NODE_STRU *pstNode);

/* ��������ȡ��ĳ�ڵ�����ֵ, ������0�� */
XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_GetAttributeByIndex(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lAttribIndex);

/* ����������ȡ��ĳ�ڵ����� */
XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_GetAttributeByAttributeName(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribName);

/* �������ֵ�Ƿ���Ŀ��ֵ��ͬ */
VOS_UINT32 XML_COMM_CheckAttributeValue(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttributeValue);

/* ����һ������ */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BreakAnAttribute(
    XML_COMM_NODE_STRU                 *pstNode,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute);

/* ����һ����֦��������Ҫ�������Ľڵ� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BreakANode(XML_COMM_NODE_STRU *pstNode);

/* ���ڴ��д���һ�����Բ���ʼ�� */
XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_CreateAnAttribute(XML_COMM_CTX_STRU *pstXmlCtx);

/* �������Ե������� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetAttributeName(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttribName);

/* �������Ե�����ֵ */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetAttributeValue(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttribValue);

/* ���ڴ��д���һ���ڵ㲢��ʼ�� */
XML_COMM_NODE_STRU* XML_COMM_CreateANode(XML_COMM_CTX_STRU *pstXmlCtx);

/* ���ýڵ�ı�ǩ�� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeLabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcNodeLabel);

/* ���ýڵ��ֵ, �ַ������� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueStr(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcNodeValue);

/* ���ýڵ��ֵ, �з��������� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueInt(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lNodeValue,
    XML_COMM_CTX_STRU                  *pstXmlCtx);

/* ���ýڵ��ֵ, �޷��������� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueUInt(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_UINT32                          ulNodeValue,
    XML_COMM_CTX_STRU                  *pstXmlCtx);

/* Ϊһ���ڵ������ӽڵ㣬��һ���ڵ��һ�������ҵ���һ������ĳ���ڵ��� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_AddAChildNode(
    XML_COMM_NODE_STRU                 *pstFather,
    XML_COMM_NODE_STRU                 *pstChild,
    XML_COMM_NODE_STRU                 *pstYoungBrother);

/* Ϊһ���ڵ��������� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_AddAnAttribute(
    XML_COMM_NODE_STRU                 *pstNode,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstYoungBrother);

/* ��ʼ��XML API������ */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_InitXMLCtx(XML_COMM_CTX_STRU *pstXmlCtx);

/* �����������XML��ʽ�����׵�ַ��XML�����ģ����XML���ĸ��ڵ� */
XML_COMM_NODE_STRU* XML_COMM_BuildXMLTree(
    VOS_CHAR                           *pcXmlStr,
    XML_COMM_CTX_STRU                  *pstXmlCtx);

/* ������XML�������ڴ�ռ�, �ڴ�ռ�ĳ���, ���ڵ� */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BuildXMLStr(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcXmlStr,
    VOS_UINT32                         *pulLength,
    XML_COMM_FORMATTING_ENUM_UINT8      enXmlFormat);

/* ����XML������ */
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ClearXMLCtx(XML_COMM_CTX_STRU *pstXmlCtx);

/* �ж��ַ��Ƿ�Ϊ�ָ��� */
VOS_UINT32 XML_COMM_IsSeparator(VOS_CHAR cCharacter);

#endif

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


#endif /* _XML_COMM_H_ */

