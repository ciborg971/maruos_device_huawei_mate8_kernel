

/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/

#include "Taf_Common.h"
#include "XmlComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*lint -e958*/

#if (FEATURE_ON == FEATRUE_XML_PARSER)

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_XML_COMM_C

/*****************************************************************************
2 ȫ�ֱ�������
*****************************************************************************/
typedef VOS_UINT32 (*XML_COMM_ANALYSE_FUNC)(XML_COMM_CTX_INNER_STRU *pstXmlCtxInner);

/*****************************************************************************
3 ��������
*****************************************************************************/


VOS_INT32 XML_COMM_GetChildCount(XML_COMM_NODE_STRU *pstNode)
{
    XML_COMM_NODE_STRU                 *pstTmpNode;
    VOS_INT32                           lCounter;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_GetChildCount: pstNode is VOS_NULL_PTR!");
        return VOS_ERROR;
    }

    lCounter = 0;

    /* �ӳ�������ͷ��ʼ, ���������ӽڵ� */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        lCounter++;
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return lCounter;
}


XML_COMM_NODE_STRU* XML_COMM_GetChildNodeByIndex(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lChildIndex)
{
    XML_COMM_NODE_STRU                 *pstTmpNode;
    VOS_INT32                           lCounter;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_GetChildNodeByIndex: pstNode is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    lCounter = 0;

    /* �ӳ�������ͷ��ʼ,���������ӽڵ� */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        if (lCounter == lChildIndex)
        {
            return pstTmpNode;
        }
        lCounter++;
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return VOS_NULL_PTR;
}


XML_COMM_NODE_STRU* XML_COMM_GetChildNodeByLabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabel)
{
    XML_COMM_NODE_STRU                 *pstTmpNode;
    VOS_UINT32                          ulLabelLength;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcLabel))
    {
        XML_WARNING_LOG("XML_COMM_GetChildNodeByLabel: pstNode or pcLabel is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* �ӳ�������ͷ��ʼ,���������ӽڵ� */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        ulLabelLength   = pstTmpNode->ulLabelLength;
        if (VOS_StrLen(pcLabel) == ulLabelLength)
        {
            if (0 == PS_MEM_CMP(pstTmpNode->pcNodeLabel, pcLabel, ulLabelLength))
            {
                return pstTmpNode;
            }
        }
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return VOS_NULL_PTR;
}


VOS_UINT32 XML_COMM_CheckLabelName(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabelName)
{
    VOS_UINT32                          ulLabelLength;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcLabelName))
    {
        XML_WARNING_LOG("XML_COMM_CheckLabelName: pstNode or pcLabelName is VOS_NULL_PTR!");
        return VOS_FALSE;
    }

    /* �ֱ�Աȱ�ǩ�����ȼ���ǩ����ֵ */
    ulLabelLength = VOS_StrLen(pcLabelName);
    if (ulLabelLength == pstNode->ulLabelLength)
    {
        if (0 == PS_MEM_CMP(pstNode->pcNodeLabel, pcLabelName, ulLabelLength))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_INT32 XML_COMM_GetAttributeCount(XML_COMM_NODE_STRU *pstNode)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_INT32                           lCounter;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_GetAttributeCount: pstNode is VOS_NULL_PTR!");
        return VOS_ERROR;
    }

    lCounter = 0;

    /* �ӳ�������ͷ��ʼ,���������ӽڵ� */
    pstTmpAttribute = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttribute)
    {
        lCounter++;
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return lCounter;
}


XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_GetAttributeByIndex(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lAttribIndex)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_INT32                           lCounter;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_GetAttributeByIndex: pstNode is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    lCounter = 0;

    /* ������ͷ��ʼ,���������ӽڵ� */
    pstTmpAttribute = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttribute)
    {
        if (lCounter == lAttribIndex)
        {
            return pstTmpAttribute;
        }
        lCounter++;
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return VOS_NULL_PTR;
}


XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_GetAttributeByAttributeName(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribName)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;
    VOS_UINT32                          ulNameLength;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcAttribName))
    {
        XML_WARNING_LOG("XML_COMM_GetAttributeByAttributeName: pstNode or pcAttribName is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* ������ͷ��ʼ,������������ */
    pstTmpAttrib = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttrib)
    {
        ulNameLength = pstTmpAttrib->ulNameLength;
        if (VOS_StrLen(pcAttribName) == ulNameLength)
        {
            if (0 == PS_MEM_CMP(pstTmpAttrib->pcAttribName, pcAttribName, ulNameLength))
            {
                return pstTmpAttrib;
            }
        }
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    XML_WARNING_LOG("XML_COMM_GetAttributeByAttributeName: Can't find the Attribute!");
    return VOS_NULL_PTR;
}


LOCAL XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_GetLastAttribute(
    XML_COMM_NODE_STRU                 *pstNode)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;

    pstTmpAttribute = pstNode->pstFirstAttrib;

    /* �ڵ���������ֱ�ӷ��ؿ�ָ�� */
    if (VOS_NULL_PTR == pstTmpAttribute)
    {
        return VOS_NULL_PTR;
    }

    /* ������ͷ��ʼ, ���������ӽڵ�, ֱ�����һ������ */
    while (VOS_NULL_PTR != pstTmpAttribute->pstNexBrother)
    {
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return pstTmpAttribute;
}


VOS_UINT32 XML_COMM_CheckAttributeValue(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttributeValue)
{
    VOS_UINT32                          ulValueLength;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstAttribute) || (VOS_NULL_PTR == pcAttributeValue))
    {
        XML_WARNING_LOG("XML_COMM_CheckAttributeValue: pstAttribute or pcAttributeValue is VOS_NULL_PTR!");
        return VOS_FALSE;
    }

    /* �ֱ�Ա�����ֵ���ȼ�����ֵ���� */
    ulValueLength = VOS_StrLen(pcAttributeValue);
    if (ulValueLength == pstAttribute->ulValueLength)
    {
        if (0 == PS_MEM_CMP(pstAttribute->pcAttribValue, pcAttributeValue, ulValueLength))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BreakAnAttribute(
    XML_COMM_NODE_STRU                 *pstNode,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstAttribute))
    {
        XML_WARNING_LOG("XML_COMM_BreakAnAttribute: pstNode or pstAttribute is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �����������,��λ��Ҫ��������� */
    pstTmpAttrib = pstNode->pstFirstAttrib;
    while ((VOS_NULL_PTR != pstTmpAttrib) && (pstAttribute != pstTmpAttrib))
    {
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    /* û�ҵ�ָ��������,ʧ�ܷ��� */
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return XML_COMM_RESULT_FAILED_ATTRIB_NOT_FOUND;
    }

    /* ���Ҫ��ж���ǽڵ��һ�����ԣ�������ڵ�������ָ�� */
    if (pstTmpAttrib == pstNode->pstFirstAttrib)
    {
        pstNode->pstFirstAttrib = pstTmpAttrib->pstNexBrother;
    }

    /* ����ǰ���ֵܽڵ��ָ�� */
    if (VOS_NULL_PTR != pstTmpAttrib->pstPreBrother)
    {
        pstTmpAttrib->pstPreBrother->pstNexBrother = pstTmpAttrib->pstNexBrother;
    }
    if (VOS_NULL_PTR != pstTmpAttrib->pstNexBrother)
    {
        pstTmpAttrib->pstNexBrother->pstPreBrother = pstTmpAttrib->pstPreBrother;
    }

    /* ��ԭ�������Ͼ���ϵ */
    pstTmpAttrib->pstPreBrother = VOS_NULL_PTR;
    pstTmpAttrib->pstNexBrother = VOS_NULL_PTR;

    return XML_COMM_RESULT_SUCCEED;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BreakANode(XML_COMM_NODE_STRU *pstNode)
{
    XML_COMM_NODE_STRU                 *pstFatherNode;
    XML_COMM_NODE_STRU                 *pstTmpNode;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_BreakANode: pstNode is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* ȡ�ø��ڵ� */
    pstFatherNode = pstNode->pstFather;

    /* ���ڵ㲻���� */
    if (VOS_NULL_PTR == pstFatherNode)
    {
        return XML_COMM_RESULT_FAILED_CANT_UNLOAD_ROOT_NODE;
    }

    /* �����ӽڵ�������ң�ȷ��ָ���ĸ��ӹ�ϵ */
    pstTmpNode = pstFatherNode->pstFirstChild;
    while ((VOS_NULL_PTR != pstTmpNode) && (pstTmpNode != pstNode))
    {
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    /* û���ҵ� */
    if (VOS_NULL_PTR == pstTmpNode)
    {
        return XML_COMM_RESULT_FAILED_NODE_NOT_FOUND;
    }

    /* ����Ǹ��ڵ㳤�ӣ���������ڵ㳤�� */
    if (pstNode == pstFatherNode->pstFirstChild)
    {
        pstFatherNode->pstFirstChild = pstNode->pstNexBrother;
    }

    /* ���븸�ӹ�ϵ */
    pstNode->pstFather = VOS_NULL_PTR;

    /* �����ֵ����� */
    if (VOS_NULL_PTR != pstNode->pstPreBrother)
    {
        pstNode->pstPreBrother->pstNexBrother = pstNode->pstNexBrother;
    }
    if (VOS_NULL_PTR != pstNode->pstNexBrother)
    {
        pstNode->pstNexBrother->pstPreBrother = pstNode->pstPreBrother;
    }
    pstNode->pstPreBrother = VOS_NULL_PTR;
    pstNode->pstNexBrother = VOS_NULL_PTR;

    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_InitMemory(XML_COMM_CTX_STRU *pstXmlCtx)
{
    /* ���������ڴ��ַΪ��, ������ڴ沢��ʼ�� */
    if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffer)
    {
        pstXmlCtx->ulXMLBuffSize    = XML_COMM_BUFF_SIZE;
        pstXmlCtx->pucXMLBuffer     = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, pstXmlCtx->ulXMLBuffSize);
        pstXmlCtx->pucXMLBuffCur    = pstXmlCtx->pucXMLBuffer;

        /* �����ڴ�ʧ�� */
        if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffer)
        {
            XML_ERROR_LOG("XML_COMM_InitMemory: Malloc Failure!");
            return XML_COMM_RESULT_FALIED_MALLOC;
        }
    }
    /* �������ѷ����ڴ�ռ�, ��ֻ���ʼ�� */
    else
    {
        pstXmlCtx->ulXMLBuffSize    = XML_COMM_BUFF_SIZE;
        pstXmlCtx->pucXMLBuffCur    = pstXmlCtx->pucXMLBuffer;
    }

    PS_MEM_SET(pstXmlCtx->pucXMLBuffer, 0x00, pstXmlCtx->ulXMLBuffSize);

    return XML_COMM_RESULT_SUCCEED;
}
LOCAL VOS_VOID* XML_COMM_Malloc(
    XML_COMM_CTX_STRU                  *pstXmlCtx,
    VOS_UINT32                          ulSize)
{
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;
    VOS_INT32                           iRemainMemSize;
    VOS_VOID                           *pReturn;

    pReturn     = VOS_NULL_PTR;
    ulReturnVal = XML_COMM_RESULT_SUCCEED;

    /* �ж��������еĵ�ǰ�ڴ�ָ���Ƿ����, ����������ó�ʼ���ڴ溯�� */
    if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffCur)
    {
        ulReturnVal = XML_COMM_InitMemory(pstXmlCtx);
    }

    if (XML_COMM_RESULT_SUCCEED == ulReturnVal)
    {
        /* �ж����������ڴ��Ƿ��� */
        iRemainMemSize = (pstXmlCtx->pucXMLBuffer
                       + pstXmlCtx->ulXMLBuffSize)
                       - pstXmlCtx->pucXMLBuffCur;
        if ((VOS_INT32)ulSize > iRemainMemSize)
        {
            pReturn = VOS_NULL_PTR;
        }
        else
        {
            pReturn = (VOS_VOID*)pstXmlCtx->pucXMLBuffCur;
            pstXmlCtx->pucXMLBuffCur += ulSize;
        }
    }

    return pReturn;
}


XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_CreateAnAttribute(XML_COMM_CTX_STRU *pstXmlCtx)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute;
    VOS_UINT32                          ulAttribStruSize;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("XML_COMM_CreateAnAttribute: pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    pstAttribute        = VOS_NULL_PTR;
    ulAttribStruSize    = sizeof(XML_COMM_NODE_ATTRIBUTE_STRU);

    /* ����XMLģ���ڴ���亯��������һ��ڵ��ڴ� */
    pstAttribute = (XML_COMM_NODE_ATTRIBUTE_STRU*)XML_COMM_Malloc(pstXmlCtx, ulAttribStruSize);

    return pstAttribute;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetAttributeName(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttribName)
{
    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstAttribute) || (VOS_NULL_PTR == pcAttribName))
    {
        XML_WARNING_LOG("XML_COMM_SetAttributeName: pstAttribute or pcAttribName is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �����Խṹ���и�ֵ */
    pstAttribute->pcAttribName = pcAttribName;
    pstAttribute->ulNameLength = VOS_StrLen(pcAttribName);

    return XML_COMM_RESULT_SUCCEED;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetAttributeValue(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttribValue)
{
    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstAttribute) || (VOS_NULL_PTR == pcAttribValue))
    {
        XML_WARNING_LOG("XML_COMM_SetAttributeValue: pstAttribute or pcAttribValue is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �����Խṹ���и�ֵ */
    pstAttribute->pcAttribValue = pcAttribValue;
    pstAttribute->ulValueLength = VOS_StrLen(pcAttribValue);

    return XML_COMM_RESULT_SUCCEED;
}


XML_COMM_NODE_STRU* XML_COMM_CreateANode(XML_COMM_CTX_STRU *pstXmlCtx)
{
    XML_COMM_NODE_STRU                 *pstNode;
    VOS_UINT32                          ulNodeStruSize;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("XML_COMM_CreateANode: pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    pstNode         = VOS_NULL_PTR;
    ulNodeStruSize  = sizeof(XML_COMM_NODE_STRU);

    /* ����XMLģ���ڴ���亯��������һ��ڵ��ڴ� */
    pstNode = (XML_COMM_NODE_STRU*)XML_COMM_Malloc(pstXmlCtx, ulNodeStruSize);

    return pstNode;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeLabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcNodeLabel)
{
    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcNodeLabel))
    {
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �Խڵ�ṹ���и�ֵ */
    pstNode->pcNodeLabel        = pcNodeLabel;
    pstNode->pcNodeLabelEnd     = pcNodeLabel;
    pstNode->ulLabelLength      = VOS_StrLen(pcNodeLabel);
    pstNode->ulLabelEndLength   = VOS_StrLen(pcNodeLabel);

    return XML_COMM_RESULT_SUCCEED;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueStr(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcNodeValue)
{
    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcNodeValue))
    {
        XML_WARNING_LOG("XML_COMM_SetNodeValueStr: pstNode or pcNodeValue is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �Խڵ�ṹ���и�ֵ */
    pstNode->pcNodeValue    = pcNodeValue;
    pstNode->ulValueLength  = VOS_StrLen(pcNodeValue);

    return XML_COMM_RESULT_SUCCEED;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueInt(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lNodeValue,
    XML_COMM_CTX_STRU                  *pstXmlCtx)
{
    VOS_CHAR                            acTmpStr[XML_COMM_MAX_NUM_LEN + 1];

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstXmlCtx))
    {
        XML_WARNING_LOG("XML_COMM_SetNodeValueInt: pstNode or pstXmlCtx is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    PS_MEM_SET(acTmpStr, 0x00, XML_COMM_MAX_NUM_LEN + 1);

    /* �Խڵ�ṹ���и�ֵ */
    /* ������ֵת��Ϊ�ַ�������ȡ���� */
    pstNode->ulValueLength  = (VOS_UINT32)VOS_sprintf(acTmpStr, "%d", lNodeValue);

    /* ����ֵ�ڴ棬����ֵ */
    pstNode->pcNodeValue    = (VOS_CHAR*)XML_COMM_Malloc(pstXmlCtx, pstNode->ulValueLength);
    if (VOS_NULL_PTR == pstNode->pcNodeValue)
    {
        XML_ERROR_LOG("XML_COMM_SetNodeValueInt: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MALLOC;
    }

    PS_MEM_CPY(pstNode->pcNodeValue, acTmpStr, pstNode->ulValueLength);

    return XML_COMM_RESULT_SUCCEED;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueUInt(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_UINT32                          ulNodeValue,
    XML_COMM_CTX_STRU                  *pstXmlCtx)
{
    VOS_CHAR                            acTmpStr[XML_COMM_MAX_NUM_LEN];

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstXmlCtx))
    {
        XML_WARNING_LOG("XML_COMM_SetNodeValueUInt: pstNode or pstXmlCtx is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    PS_MEM_SET(acTmpStr, 0x00, XML_COMM_MAX_NUM_LEN);

    /* �Խڵ�ṹ���и�ֵ */
    /* ������ֵת��Ϊ�ַ�������ȡ���� */
    pstNode->ulValueLength  = (VOS_UINT32)VOS_sprintf(acTmpStr, "%u", ulNodeValue);

    /* ����ֵ�ڴ棬����ֵ */
    pstNode->pcNodeValue    = (VOS_CHAR*)XML_COMM_Malloc(pstXmlCtx, pstNode->ulValueLength);
    if (VOS_NULL_PTR == pstNode->pcNodeValue)
    {
        XML_ERROR_LOG("XML_COMM_SetNodeValueUInt: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MALLOC;
    }

    PS_MEM_CPY(pstNode->pcNodeValue, acTmpStr, pstNode->ulValueLength);

    return XML_COMM_RESULT_SUCCEED;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_AddAChildNode(
    XML_COMM_NODE_STRU                 *pstFather,
    XML_COMM_NODE_STRU                 *pstChild,
    XML_COMM_NODE_STRU                 *pstYoungBrother)
{
    XML_COMM_NODE_STRU                 *pstTmpChild;
    XML_COMM_NODE_STRU                 *pstLastChild;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstFather) || (VOS_NULL_PTR == pstChild))
    {
        XML_WARNING_LOG("XML_COMM_AddAChildNode: pstFather or pstChild is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �趨���� */
    pstChild->pstFather = pstFather;

    /* �趨���� */
    /* ����ýڵ㻹û�к��ӣ���Ѳ���Ľڵ���Ϊ�׽ڵ� */
    if (VOS_NULL_PTR == pstFather->pstFirstChild)
    {
        pstFather->pstFirstChild    = pstChild;

        /* ������ӵ�������ӵ������ϵ */
        pstChild->pstPreBrother     = VOS_NULL_PTR;
        pstChild->pstNexBrother     = VOS_NULL_PTR;

        return XML_COMM_RESULT_SUCCEED;
    }

    /* ����ʱ����pstTmpChild�����ӽڵ�����, ֱ���ҵ�����ָ�����ӽڵ�ĵܵ� */
    pstTmpChild     = pstFather->pstFirstChild; /* �ӳ��ӿ�ʼ */
    pstLastChild    = VOS_NULL_PTR;
    while (VOS_NULL_PTR != pstTmpChild)
    {
        pstLastChild = pstTmpChild;
        if (pstTmpChild == pstYoungBrother)
        {
            break;
        }
        pstTmpChild = pstTmpChild->pstNexBrother;
    }

    /* û���ҵ�ָ���ĵܵܣ�����㣩 */
    if (VOS_NULL_PTR == pstTmpChild )
    {
        if ( (VOS_NULL_PTR != pstYoungBrother)
          || (VOS_NULL_PTR == pstLastChild) )
        {
            return XML_COMM_RESULT_FAILED_NODE_NOT_FOUND;
        }
        else
        {
            pstLastChild->pstNexBrother = pstChild;
            pstChild->pstPreBrother     = pstLastChild;
            pstChild->pstNexBrother     = VOS_NULL_PTR;
            return XML_COMM_RESULT_SUCCEED;
        }
    }

    if (pstFather->pstFirstChild == pstTmpChild)
    {
        /* �ܵ�Ϊԭ���� */
        pstFather->pstFirstChild    = pstChild;
        pstChild ->pstPreBrother    = VOS_NULL_PTR;
        pstChild ->pstNexBrother    = pstTmpChild;
        pstTmpChild->pstPreBrother  = pstChild;
    }
    else
    {
        pstChild ->pstPreBrother    = pstTmpChild->pstPreBrother;
        pstChild ->pstNexBrother    = pstTmpChild;
        pstTmpChild->pstPreBrother  = pstChild;
        pstChild->pstPreBrother->pstNexBrother = pstChild;
    }

    return XML_COMM_RESULT_SUCCEED;
}
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_AddAnAttribute(
    XML_COMM_NODE_STRU                 *pstNode,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstYoungBrother)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstAttribute))
    {
        XML_WARNING_LOG("XML_COMM_AddAnAttribute: pstNode or pstAttribute is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* ����ýڵ㻹û�����ԣ����׸����Լ�ΪpstYoungBrother����Ѳ�������Ե����׸����� */
    if ( (VOS_NULL_PTR == pstNode->pstFirstAttrib)
      || (pstYoungBrother == pstNode->pstFirstAttrib) )
    {
        /* ������ӵ�������Ե������ϵ */
        pstAttribute->pstPreBrother         = VOS_NULL_PTR;
        pstAttribute->pstNexBrother         = pstNode->pstFirstAttrib;
        if (VOS_NULL_PTR != pstYoungBrother)
        {
            pstYoungBrother->pstPreBrother  = pstAttribute;
        }

        pstNode->pstFirstAttrib             = pstAttribute;

        return XML_COMM_RESULT_SUCCEED;
    }

    /* ����ʱ����pstAttribute������������,ֱ���ҵ�����ָ�������Ե�ǰһ�� */
    pstTmpAttrib = pstNode->pstFirstAttrib; /* �ӵ�һ�����Կ�ʼ */
    while ( (VOS_NULL_PTR != pstTmpAttrib)
         && (pstTmpAttrib->pstNexBrother != pstYoungBrother) )
    {
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    /* û���ҵ�ָ���Ĳ���� */
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return XML_COMM_RESULT_FAILED_ATTRIB_NOT_FOUND;
    }

    /* ��pstAttribute����pstTmpAttrib��pstYoungBrother֮�� */
    pstTmpAttrib->pstNexBrother     = pstAttribute;
    pstAttribute->pstPreBrother     = pstTmpAttrib;
    pstAttribute->pstNexBrother     = pstYoungBrother;
    if (VOS_NULL_PTR != pstYoungBrother)
    {
        pstYoungBrother->pstPreBrother = pstAttribute;
    }

    return XML_COMM_RESULT_SUCCEED;
}
VOS_UINT32 XML_COMM_IsSeparator(VOS_CHAR cCharacter)
{
    if ( ('\r' == cCharacter)       /* �ָ��������س�   */
      || ('\n' == cCharacter)       /* �ָ�����������   */
      || ('\t' == cCharacter)       /* �ָ��������Ʊ�� */
      || (' '  == cCharacter) )     /* �ָ��������ո�   */
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}


LOCAL VOS_UINT32 XML_COMM_IsLetter(VOS_CHAR cCharacter)
{
    /* �ж��ַ��Ƿ���a~z֮�� */
    if ( ('a' <= cCharacter)
      && ('z' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* �ж��ַ��Ƿ���A~Z֮�� */
    else if ( ('A' <= cCharacter)
           && ('Z' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    else
    {
        if ('_' == cCharacter)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


LOCAL VOS_UINT32 XML_COMM_IsKeySymbol(VOS_CHAR cCharacter)
{
    /* XML��׼Լ���Ĺؼ����Ű���": . - _" */
    if ( (':' == cCharacter)
      || ('.' == cCharacter)
      || ('-' == cCharacter)
      || ('_' == cCharacter) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
LOCAL VOS_UINT32 XML_COMM_IsPunctuation(VOS_CHAR cCharacter)
{
    /* ����ASCII���, �����ж��Ƿ�Ϊ���±�����
       (�ո�) ! " # $ % & ' ( ) * + , - . / */
    if ( (' ' <= cCharacter)
      && ('/' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* �ж��Ƿ�Ϊ���±����� : ; < = > @ */
    else if ( (':' <= cCharacter)
           && ('@' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* �ж��Ƿ�Ϊ���±����� [ \ ] ^ _ ` */
    else if ( ('[' <= cCharacter)
           && ('`' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* �ж��Ƿ�Ϊ���±����� { | } ~ */
    else if ( ('{' <= cCharacter)
           && ('~' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    else
    {
    }

    return VOS_FALSE;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlOriginal(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ����<�����״̬ */
    if ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ENTER_LABEL;
    }
    /* ��ǰ�ڵ�ָ��Ϊ��, ��Ϊû�н���ڵ�, ���Ը��ַ� */
    else if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode)
    {
        /* ��ʱ���û�и��ڵ㣬���ַ����ܺ�����Ҫ�����쳣 */
        if ( (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
          && (VOS_NULL_PTR == pstXmlCtxInner->pstXMLRootNode) )
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlOriginal: Unexpect charactor out of Root!");
            return XML_COMM_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT;
        }
    }
    /* ��ǰ�ڵ��ֵ��Ϊ��, ����Ϊ�ýڵ����ӽڵ�, ��ǰ�ַ����ڽڵ�ֵ */
    else if (VOS_NULL_PTR != pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue)
    {
        /* ��ǰ�ڵ��ֵ����+1 */
        pstXmlCtxInner->pstXMLCurrentNode->ulValueLength++;
    }
    else
    {
    }

    pstXmlCtxInner->pcXMLStrCurChar++;
    return XML_COMM_RESULT_SUCCEED;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlEnterLabel(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* �������а汾��Ϣ */
    if ('?' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_DECLARATION;
    }
    /* ����ע�� */
    else if ('!' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_COMMENT;
    }
    /* ����β�ڵ��ǩ */
    else if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_SINGLE_ENDS_LABEL;
    }
    /* ����һ���½ڵ� */
    else
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_NODE_LABEL_START;
    }

    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlDeclaration(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ��ָ���Ƶ�"<?"�� */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* Ŀǰ�޽����汾��Ϣ�������ݲ�������, ֱ������"?>"���� */
    while ('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        /*lint -e961*/
        if ( ('?' == *(pstXmlCtxInner->pcXMLStrCurChar++))
          && ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ORIGINAL;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return XML_COMM_RESULT_SUCCEED;
        }
        /*lint +e961*/
    }

    XML_WARNING_LOG("XML_COMM_ProcXmlDeclaration: The declaration has no end!");
    return XML_COMM_RESULT_FALIED_DECLARATION_NO_END;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlComment(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ��ָ���Ƶ�"<!"�� */
    pstXmlCtxInner->pcXMLStrCurChar++;
    /*lint -e961*/
    /* ��֧��DOCTYPE, ע�ͱ�����"<!--"��ͷ, �����﷨���� */
    if ( ('-' == *(pstXmlCtxInner->pcXMLStrCurChar++))
      && ('-' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
    {
        pstXmlCtxInner->pcXMLStrCurChar++;

        /* ֱ������������"-->"ǰ, �������е��ַ� */
        while (0 != *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            if ( ('-' == *(pstXmlCtxInner->pcXMLStrCurChar++))
              && ('-' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
            {
                pstXmlCtxInner->pcXMLStrCurChar++;
                if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar++))
                {
                    pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ORIGINAL;
                    return XML_COMM_RESULT_SUCCEED;
                }
                else
                {
                    XML_WARNING_LOG("XML_COMM_ProcXmlComment: The comment has syntax error!");
                    return XML_COMM_RESULT_FALIED_COMMENT_SYNTAX_ERROR;
                }
            }
        }

        XML_WARNING_LOG("XML_COMM_ProcXmlComment: The comment has no end!");
        return XML_COMM_RESULT_FALIED_COMMENT_NO_END;
    }
    /*lint +e961*/
    XML_WARNING_LOG("XML_COMM_ProcXmlComment: The comment has syntax error!");
    return XML_COMM_RESULT_FALIED_COMMENT_SYNTAX_ERROR;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlSingleEndLabel(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ��ָ���Ƶ�"</"�� */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* ��ǩ������ĸ����Ϊ���ֻ������ */
    /* ��֧��˫�ֽڱ����ַ�, ��֧�������ռ�, �����Բ������� */
    if (VOS_TRUE != XML_COMM_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlSingleEndLabel: Illegal label name!");
        return XML_COMM_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* ���ڵ��ұ�ǩ����ֵ */
    /*lint -e961*/
    pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabelEnd = pstXmlCtxInner->pcXMLStrCurChar++;
    /*lint +e961*/
    pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == XML_COMM_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == XML_COMM_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength++;
    }

    /* �Ƚ��ұ�ǩ���Ƿ�����ǩ��һ�� */
    if (pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength == pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength)
    {
        if (0 != PS_MEM_CMP(pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabel,
                            pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabelEnd,
                            pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength))
        {
            return XML_COMM_RESULT_FALIED_LABEL_NAMES_NOT_SAME;
        }
    }
    else
    {
        return XML_COMM_RESULT_FALIED_BAD_END_LABEL;
    }

    /* �ұ�ǩ�����ǩ������֮�������ָ��� */
    /* һֱ������>����������β��ǩ */
    while (0 != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode->pstFather)
            {
                /* ���ڵ�Ľ�β��ǩ, �������ڵ���������� */
                pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_AFTER_ROOT_NODE;
                pstXmlCtxInner->pcXMLStrCurChar++;
                return XML_COMM_RESULT_SUCCEED_ALL_ENDS;
            }
            break;
        }
        else if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlSingleEndLabel: Illegal label!");
            return XML_COMM_RESULT_FALIED_BAD_END_LABEL;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
        }
    }

    /* �սڵ㴦�� */
    if (0 == pstXmlCtxInner->pstXMLCurrentNode->ulValueLength)
    {
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = VOS_NULL_PTR;
    }

    /* ��ǰ�ڵ��˵����ڵ� */
    pstXmlCtxInner->pstXMLCurrentNode   = pstXmlCtxInner->pstXMLCurrentNode->pstFather;
    pstXmlCtxInner->enXMLAnalyseStatus  = XML_COMM_PARSE_ORIGINAL;
    pstXmlCtxInner->pcXMLStrCurChar++;
    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlLabelStart(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_NODE_STRU                 *pstNewNode;
    XML_COMM_RESULT_ENUM_UINT32         enXmlRslt;

    /* ��ǩ������ĸ����Ϊ���ֻ������ */
    /* ��֧��˫�ֽڱ����ַ�, ��֧�������ռ�, �����Բ������� */
    if (VOS_TRUE != XML_COMM_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlLabelStart: Illegal label name!");
        return XML_COMM_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* ����һ���½ڵ� */
    pstNewNode  = XML_COMM_CreateANode(pstXmlCtxInner->pstXMLCtx);
    if (VOS_NULL_PTR == pstNewNode)
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlLabelStart: Create Node Error!");
        return XML_COMM_RESULT_FALIED_CREATE_NODE_ERROR;
    }

    /* ���ڵ�Ϊ��, ��ζ�ŵ�ǰ�ڵ㼴���ڵ� */
    if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLRootNode)
    {
        pstXmlCtxInner->pstXMLRootNode = pstNewNode;
    }

    /* �����뵽��ǰ�ڵ���ӽڵ�����ĩ�ˣ�������ǰ�ڵ�ָ��ָ������½ڵ� */
    if (VOS_NULL_PTR != pstXmlCtxInner->pstXMLCurrentNode)
    {
        enXmlRslt = XML_COMM_AddAChildNode(pstXmlCtxInner->pstXMLCurrentNode,
                               pstNewNode,
                               VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != enXmlRslt)
        {
            XML_WARNING_LOG("XML_COMM_AddAChildNode: Error!");
        }
        /* ��������ӽڵ�, ����սڵ�ֵ */
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue      = VOS_NULL_PTR;
        pstXmlCtxInner->pstXMLCurrentNode->ulValueLength    = 0;
    }
    pstXmlCtxInner->pstXMLCurrentNode = pstNewNode;
    /*lint -e961*/
    /* ���ڵ�Label��ֵ */
    pstNewNode->pcNodeLabel = pstXmlCtxInner->pcXMLStrCurChar++;
    /*lint +e961*/
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == XML_COMM_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == XML_COMM_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstNewNode->ulLabelLength++;
    }

    /* ����/����>���߷ָ���˵��Node�����ֽ����� */
    /* ����/��������β�����ڵ�, �¸��ֽ�һ����> */
    if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_LABEL_END_MUST_RIGHT;
    }
    /* ����>���ǩ���� */
    else if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ORIGINAL;
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = pstXmlCtxInner->pcXMLStrCurChar + 1;
    }
    /* ��ǩ���ֽ���, �������Խ���״̬ */
    else if (VOS_TRUE == XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_START;
    }
    else
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlLabelStart: Illegal label name!");
        return XML_COMM_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
    pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength++;
    pstXmlCtxInner->pcXMLStrCurChar++;
    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlEndMustBeRight(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /*lint -e961*/
    /* ������>������Ϊ�����ʽ */
    if ('>' != *(pstXmlCtxInner->pcXMLStrCurChar++))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlEndMustBeRight: Illegal end label!");
        return XML_COMM_RESULT_FALIED_BAD_END_LABEL;
    }
    /*lint +e961*/
    /* ����Ǹ��ڵ�Ľ�β��ǩ, �����������Խ����� */
    if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode->pstFather)
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_AFTER_ROOT_NODE;
        return XML_COMM_RESULT_SUCCEED_ALL_ENDS;
    }

    /* ��ǰ�ڵ��˵����ڵ� */
    pstXmlCtxInner->pstXMLCurrentNode   = pstXmlCtxInner->pstXMLCurrentNode->pstFather;
    /* ���״̬ */
    pstXmlCtxInner->enXMLAnalyseStatus  = XML_COMM_PARSE_ORIGINAL;

    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribStart(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ����Lable�еķָ��� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* ����β�ڵ��ǩ */
    if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_LABEL_END_MUST_RIGHT;
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /* ���ǩ����, �ص���ʼ״̬ */
    else if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ORIGINAL;
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /* �����ǩ������ */
    else
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_NAME_START;
    }

    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribNameStart(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNewAttrib;

    /* ����������ĸ����Ϊ���ֻ������, ��֧��˫�ֽڱ����ַ� */
    if (VOS_TRUE != XML_COMM_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlAttribNameStart: Illegal attribute name!");
        return XML_COMM_RESULT_FALIED_BAD_ATTRIB_NAME;
    }

    /* ����һ���½ڵ�, �����뵽��ǰ�ڵ����������ĩ�� */
    pstNewAttrib = XML_COMM_CreateAnAttribute(pstXmlCtxInner->pstXMLCtx);
    if (XML_COMM_RESULT_SUCCEED != XML_COMM_AddAnAttribute(pstXmlCtxInner->pstXMLCurrentNode,
                                                           pstNewAttrib,
                                                           VOS_NULL_PTR))
    {
        return XML_COMM_RESULT_FALIED_CREATE_ATTRIB_ERROR;
    }
    /*lint -e961*/
    /* ����������ֵ */
    pstNewAttrib->pcAttribName = pstXmlCtxInner->pcXMLStrCurChar++;
    /*lint +e961*/
    pstNewAttrib->ulNameLength++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == XML_COMM_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == XML_COMM_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstNewAttrib->ulNameLength++;
    }

    /* ����=���߷ָ���˵�������������� */
    if ('=' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_NAME_END;
    }
    else if (VOS_TRUE == XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_NAME_END;
    }
    else
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlAttribNameStart: Illegal attribute name!");
        return XML_COMM_RESULT_FALIED_BAD_ATTRIB_NAME;
    }

    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribNameEnd(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ������������, ������ڶ���ָ��� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /*lint -e961*/
    /* ȥ���ָ�����, һ����'=' */
    if ('=' != *(pstXmlCtxInner->pcXMLStrCurChar++))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlAttribNameEnd: Lake of equal sign!");
        return XML_COMM_RESULT_FALIED_EXPECT_EQUAL_SIGN;
    }
    /*lint +e961*/
    /* �Ⱥ�������ֵ֮���������ָ��� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* ȥ���ָ�����, һ���ǵ����Ż�˫���� */
    if ('\'' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_VALUE_SINGLE;
    }
    else if ('"' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_VALUE_DOUBLE;
    }
    else
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlAttribNameEnd: Lake of quotation mark!");
        return XML_COMM_RESULT_FALIED_NO_QUOTATION_MARK;
    }

    pstXmlCtxInner->pcXMLStrCurChar++;
    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribValueSingle(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* ����ǰ�ڵ����һ�����Ե�����ֵ�� */
    pstTmpAttrib = XML_COMM_GetLastAttribute(pstXmlCtxInner->pstXMLCurrentNode);
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return XML_COMM_RESULT_FALIED_UNKOWN_ERROR;
    }
    pstTmpAttrib->pcAttribValue = pstXmlCtxInner->pcXMLStrCurChar;

    /* �ȴ������� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('\'' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            /* ����ֵ����, ���ؿ�ʼ�������Ե�״̬ */
            pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_START;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return XML_COMM_RESULT_SUCCEED;
        }
        else if ( ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
               || ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlAttribValueSingle: Unexpect Char!");
            return XML_COMM_RESULT_FALIED_CHAR_UNEXPECT;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
            pstTmpAttrib->ulValueLength++;
        }
    }

    XML_WARNING_LOG("XML_COMM_ProcXmlAttribValueSingle: Lake of end quotation mark!");
    return XML_COMM_RESULT_FALIED_NO_QUOTATION_MARK;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribValueDouble(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* ����ǰ�ڵ����һ�����Ե�����ֵ�� */
    pstTmpAttrib = XML_COMM_GetLastAttribute(pstXmlCtxInner->pstXMLCurrentNode);
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return XML_COMM_RESULT_FALIED_UNKOWN_ERROR;
    }
    pstTmpAttrib->pcAttribValue = pstXmlCtxInner->pcXMLStrCurChar;

    /* �ȴ�˫���� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('"' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            /* ����ֵ����, ���ؿ�ʼ�������Ե�״̬ */
            pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_START;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return XML_COMM_RESULT_SUCCEED;
        }
        else if ( ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
               || ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlAttribValueDouble: Unexpect Char!");
            return XML_COMM_RESULT_FALIED_CHAR_UNEXPECT;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
            pstTmpAttrib->ulValueLength++;
        }
    }

    XML_WARNING_LOG("XML_COMM_ProcXmlAttribValueDouble: Lake of end quotation mark!");
    return XML_COMM_RESULT_FALIED_NO_QUOTATION_MARK;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAfterRootNode(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ֱ������ĩβ����������ַָ��� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlAfterRootNode: Unexpect charactor out of Root!");
            return XML_COMM_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    return XML_COMM_RESULT_SUCCEED_ALL_ENDS;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_Analyse(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;
    XML_COMM_ANALYSE_FUNC               afucXmlAnalyseFucs[] =
    {
        XML_COMM_ProcXmlOriginal,
        XML_COMM_ProcXmlEnterLabel,
        XML_COMM_ProcXmlDeclaration,
        XML_COMM_ProcXmlComment,
        XML_COMM_ProcXmlLabelStart,
        XML_COMM_ProcXmlSingleEndLabel,
        XML_COMM_ProcXmlEndMustBeRight,
        XML_COMM_ProcXmlAttribStart,
        XML_COMM_ProcXmlAttribNameStart,
        XML_COMM_ProcXmlAttribNameEnd,
        XML_COMM_ProcXmlAttribValueSingle,
        XML_COMM_ProcXmlAttribValueDouble,
        XML_COMM_ProcXmlAfterRootNode
    };

    /* �жϽ���״̬�ĺϷ��� */
    if (pstXmlCtxInner->enXMLAnalyseStatus >= XML_COMM_PARSE_BUTT)
    {
        XML_WARNING_LOG("XML_COMM_Analyse: Invalid Analyse Status!");
        return XML_COMM_RESULT_FALIED_ANALYSE_STATUS_ERROR;
    }

    /* ͨ����������״̬�������� */
    ulReturnVal = afucXmlAnalyseFucs[pstXmlCtxInner->enXMLAnalyseStatus](pstXmlCtxInner);

    return ulReturnVal;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_InitXMLCtx(XML_COMM_CTX_STRU *pstXmlCtx)
{
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("XML_COMM_InitXMLCtx: pstXmlCtx is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* ��ʼ���ڴ�ռ� */
    PS_MEM_SET(pstXmlCtx, 0x00, sizeof(XML_COMM_CTX_STRU));
    ulReturnVal = XML_COMM_InitMemory(pstXmlCtx);

    return ulReturnVal;
}


XML_COMM_NODE_STRU* XML_COMM_BuildXMLTree(
    VOS_CHAR                           *pcXmlStr,
    XML_COMM_CTX_STRU                  *pstXmlCtx)
{
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;
    XML_COMM_CTX_INNER_STRU             stXmlCtxInner;
    VOS_UINT32                          ulStrLen;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pcXmlStr) || (VOS_NULL_PTR == pstXmlCtx))
    {
        XML_WARNING_LOG("XML_COMM_BuildXMLTree: pcXmlStr or pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* �Խ�����XML�����ĳ��Ƚ���Լ�� */
    ulStrLen = VOS_StrLen(pcXmlStr);
    if ( (0 == ulStrLen)
      || (ulStrLen > XML_COMM_MAX_STR_LEN) )
    {
        XML_WARNING_LOG("XML_COMM_BuildXMLTree: pcXmlStr Length Error!");
        return VOS_NULL_PTR;
    }

    /* ��ʼ���ڴ���� */
    ulReturnVal = XML_COMM_InitMemory(pstXmlCtx);
    if (XML_COMM_RESULT_SUCCEED != ulReturnVal)
    {
        return VOS_NULL_PTR;
    }

    stXmlCtxInner.pstXMLCtx             = pstXmlCtx;
    stXmlCtxInner.pstXMLRootNode        = VOS_NULL_PTR;
    stXmlCtxInner.pstXMLCurrentNode     = VOS_NULL_PTR;
    stXmlCtxInner.pcXMLStrCurChar       = pcXmlStr;
    stXmlCtxInner.enXMLAnalyseStatus    = XML_COMM_PARSE_ORIGINAL;

    /* ����XML��ʽ����������ΪXML���ṹ */
    while ('\0' != *(stXmlCtxInner.pcXMLStrCurChar))
    {
        ulReturnVal = XML_COMM_Analyse(&stXmlCtxInner);

        /* ����ʧ��ֱ���ж�ѭ������ */
        if ( (XML_COMM_RESULT_SUCCEED != ulReturnVal)
          && (XML_COMM_RESULT_SUCCEED_ALL_ENDS != ulReturnVal) )
        {
            break;
        }
    }

    /* ����������ɣ�����XML���ṹ���ڵ� */
    if (XML_COMM_RESULT_SUCCEED_ALL_ENDS == ulReturnVal)
    {
        return stXmlCtxInner.pstXMLRootNode;
    }

    /* �����쳣, �ͷ��������з�����ڴ�, ���ؿ�ָ�� */
    XML_WARNING1_LOG("XML_COMM_BuildXMLTree: Xml Analyse Failure, Error Code: ", ulReturnVal);
    (VOS_VOID)XML_COMM_ClearXMLCtx(pstXmlCtx);
    return VOS_NULL_PTR;
}
VOS_VOID XML_COMM_StackPushNode(
    XML_COMM_TRAVERSE_STACK_STRU       *pstTraverseStack,
    XML_COMM_TRAVERSE_STACK_NODE_STRU  *pstStackNode)
{
    /*lint -e961*/
    if (XML_COMM_MAX_STACK_DEPTH > pstTraverseStack->ulStackDepth)
    {
        pstTraverseStack->astStackNode[pstTraverseStack->ulStackDepth++] = *pstStackNode;
    }
    /*lint +e961*/
    return;
}


VOS_VOID XML_COMM_StackPopNode(
    XML_COMM_TRAVERSE_STACK_STRU       *pstTraverseStack,
    XML_COMM_TRAVERSE_STACK_NODE_STRU  *pstStackNode)
{
    /*lint -e961*/
    if (0 < pstTraverseStack->ulStackDepth)
    {
        *pstStackNode = pstTraverseStack->astStackNode[--pstTraverseStack->ulStackDepth];
    }
    /*lint +e961*/
    return;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintIndentation(
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    VOS_UINT32                          ulLevel,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLen;

    /* ���ݸ�ʽ�ж��Ƿ���Ҫ���� */
    if (XML_FORMATTING_INDENTED == enFormatting)
    {
        /* �ж��ڴ�ռ��Ƿ���� */
        ulLen = ulLevel * XML_COMM_INDENTATION_SPACE_NUM;
        if (ulLen >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintIndentation: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }
        /*lint -e961*/
        /* ���ݲ���������� */
        for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
        {
            *((*ppcXmlStr)++) = ' ';
        }
        /*lint +e961*/
        (*pulLenRemain) -= ulLen;
    }

    return XML_COMM_RESULT_SUCCEED;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintAttribs(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain)
{
    VOS_UINT32                          ulLen;

    /* ѭ����ӡ�������� */
    while (VOS_NULL_PTR != pstAttribute)
    {
        /* �ж��ڴ�ռ��Ƿ���� */
        ulLen = XML_COMM_ATTRIB_PUNCTUATION_LEN
              + pstAttribute->ulNameLength
              + pstAttribute->ulValueLength;
        if (ulLen >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintAttribs: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }
        /*lint -e961*/
        /* ��д���Լ�Ŀո� */
        *((*ppcXmlStr)++) = ' ';

        /* ��д������ */
        PS_MEM_CPY((*ppcXmlStr), pstAttribute->pcAttribName, pstAttribute->ulNameLength);
        (*ppcXmlStr) += pstAttribute->ulNameLength;

        /* ��д=" (�ݲ����ǵ����ŵ����) */
        *((*ppcXmlStr)++) = '=';
        *((*ppcXmlStr)++) = '\"';

        /* ��д����ֵ */
        PS_MEM_CPY((*ppcXmlStr), pstAttribute->pcAttribValue, pstAttribute->ulValueLength);
        (*ppcXmlStr) += pstAttribute->ulValueLength;

        /* ��д" (�ݲ����ǵ����ŵ����) */
        *((*ppcXmlStr)++) = '\"';
        /*lint +e961*/
        (*pulLenRemain) -= ulLen;
        pstAttribute = pstAttribute->pstNexBrother;
    }

    return XML_COMM_RESULT_SUCCEED;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintCRLF(
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    if (XML_FORMATTING_INDENTED == enFormatting)
    {
        if (XML_COMM_CRLF_LEN >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintCRLF: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }
        /*lint -e961*/
        /* ��д�س����з� */
        *((*ppcXmlStr)++) = '\r';
        *((*ppcXmlStr)++) = '\n';
        /*lint +e961*/
        (*pulLenRemain)  -= XML_COMM_CRLF_LEN;
    }

    return XML_COMM_RESULT_SUCCEED;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintStartLabelEnd(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    VOS_UINT32                          ulHasValue;
    XML_COMM_RESULT_ENUM_UINT32         ulResult;

    /* �жϸýڵ��Ƿ���Value */
    ulHasValue  = VOS_TRUE;
    if ( (VOS_NULL_PTR == pstNode->pcNodeValue)
      || (0 == pstNode->ulValueLength) )
    {
        ulHasValue  = VOS_FALSE;
    }

    /* ���ӽڵ����Value�����ǩ��">"����, ������"/>"���� */
    if ((VOS_NULL_PTR != pstNode->pstFirstChild) || (VOS_TRUE == ulHasValue))
    {
        if (XML_COMM_LABEL_END_LEN >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintStartLabelEnd: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }
        /*lint -e961*/
        *((*ppcXmlStr)++) = '>';
        /*lint +e961*/
        (*pulLenRemain)   -= XML_COMM_LABEL_END_LEN;
    }
    else
    {
        if (XML_COMM_SINGLE_LABLE_END_LEN >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintStartLabelEnd: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }

        /*lint -e961*/
        *((*ppcXmlStr)++) = '/';
        *((*ppcXmlStr)++) = '>';
        /*lint +e961*/
        (*pulLenRemain)   -= XML_COMM_SINGLE_LABLE_END_LEN;
    }

    /* �ڵ����, ��д�س����� */
    if (VOS_FALSE == ulHasValue)
    {
        ulResult = XML_COMM_PrintCRLF(ppcXmlStr, pulLenRemain, enFormatting);
        if (XML_COMM_RESULT_SUCCEED != ulResult)
        {
            return ulResult;
        }
    }

    return XML_COMM_RESULT_SUCCEED;
}
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintStartLabelAndAttribs(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    VOS_UINT32                          ulLevel,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    VOS_UINT32                          ulLen;
    XML_COMM_RESULT_ENUM_UINT32         ulResult;

    /* ������� */
    ulResult = XML_COMM_PrintIndentation(ppcXmlStr, pulLenRemain, ulLevel, enFormatting);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    /* �������ǩ�ĳ���, ���ж��ڴ��Ƿ��� */
    ulLen = XML_COMM_LABEL_START_LEN + pstNode->ulLabelLength;
    if (ulLen >= *pulLenRemain)
    {
        XML_WARNING_LOG("XML_COMM_PrintStartLabelAndAttribs: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
    }

    /*lint -e961*/
    /* дǰ��ǩ */
    *((*ppcXmlStr)++) = '<';
    /*lint +e961*/

    /* ��д��ǩ�� */
    PS_MEM_CPY((*ppcXmlStr), pstNode->pcNodeLabel, pstNode->ulLabelLength);
    (*ppcXmlStr)      += pstNode->ulLabelLength;
    (*pulLenRemain)   -= ulLen;

    /* ������������ */
    ulResult = XML_COMM_PrintAttribs(pstNode->pstFirstAttrib, ppcXmlStr, pulLenRemain);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    /* д���ǩ */
    ulResult = XML_COMM_PrintStartLabelEnd(pstNode,
                                           ppcXmlStr,
                                           pulLenRemain,
                                           enFormatting);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintEndLabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain)
{
    VOS_UINT32                          ulLen;

    /* �����ұ�ǩ�ĳ���, ���ж��ڴ��Ƿ��� */
    ulLen = XML_COMM_END_LABEL_START_LEN + pstNode->ulLabelLength + XML_COMM_LABEL_END_LEN;
    if (ulLen >= *pulLenRemain)
    {
        XML_WARNING_LOG("XML_COMM_PrintEndLabel: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
    }
    /*lint -e961*/
    /* ��д�ұ�ǩ��ʼ��"</" */
    *((*ppcXmlStr)++) = '<';
    *((*ppcXmlStr)++) = '/';

    /* ��д��ǩ�� */
    PS_MEM_CPY((*ppcXmlStr), pstNode->pcNodeLabel, pstNode->ulLabelLength);
    (*ppcXmlStr)      += pstNode->ulLabelLength;

    /* ��д�ұ�ǩ������">" */
    *((*ppcXmlStr)++) = '>';
    (*pulLenRemain)   -= ulLen;
    /*lint +e961*/
    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintValueAndELabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    VOS_UINT32                          ulLevel,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    VOS_UINT32                          ulHasValue;
    XML_COMM_RESULT_ENUM_UINT32         ulResult;

    /* �жϸýڵ��Ƿ���Value */
    ulHasValue  = VOS_TRUE;
    if ( (VOS_NULL_PTR == pstNode->pcNodeValue)
      || (0 == pstNode->ulValueLength) )
    {
        ulHasValue  = VOS_FALSE;
    }

    /* ����ڵ�����ӽڵ�Ҳ�޽ڵ�ֵ, ��ֱ�ӷ��� */
    if ((VOS_NULL_PTR == pstNode->pstFirstChild) && (VOS_FALSE == ulHasValue))
    {
        return XML_COMM_RESULT_SUCCEED;
    }

    /* ����ýڵ���ֵ��������ڵ�ֵ, ����������� */
    if (VOS_TRUE == ulHasValue)
    {
        /* ����ڵ�ֵ�ĳ���, ���ж��ڴ��Ƿ��� */
        if (pstNode->ulValueLength >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintValueAndELabel: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }

        /* ��д�ڵ�ֵ */
        PS_MEM_CPY((*ppcXmlStr), pstNode->pcNodeValue, pstNode->ulValueLength);
        (*ppcXmlStr)      += pstNode->ulValueLength;
        (*pulLenRemain)   -= pstNode->ulValueLength;
    }
    else
    {
        /* ������� */
        ulResult = XML_COMM_PrintIndentation(ppcXmlStr, pulLenRemain, ulLevel, enFormatting);
        if (XML_COMM_RESULT_SUCCEED != ulResult)
        {
            return ulResult;
        }
    }

    /* ����ұ�ǩ */
    ulResult = XML_COMM_PrintEndLabel(pstNode, ppcXmlStr, pulLenRemain);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    /* �ڵ����, ��д�س����� */
    ulResult = XML_COMM_PrintCRLF(ppcXmlStr, pulLenRemain, enFormatting);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    return XML_COMM_RESULT_SUCCEED;
}


LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_GenerateXMLStr(
    XML_COMM_NODE_STRU                 *pstXMLRootNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    XML_COMM_TRAVERSE_STACK_STRU       *pstTraverseStack;
    XML_COMM_NODE_STRU                 *pstTmpNode;
    XML_COMM_NODE_STRU                  stXmlRootNode;
    XML_COMM_TRAVERSE_STACK_NODE_STRU   stTmpStackNode;
    XML_COMM_RESULT_ENUM_UINT32         ulResult;

    /* ��ʼ��ջ�ռ� */
    pstTraverseStack = (XML_COMM_TRAVERSE_STACK_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                   sizeof(XML_COMM_TRAVERSE_STACK_STRU));
    if (VOS_NULL_PTR == pstTraverseStack)
    {
        XML_ERROR_LOG("XML_COMM_GenerateXMLStr: Malloc Failure!");
        return XML_COMM_RESULT_FALIED_MALLOC;
    }
    PS_MEM_SET(pstTraverseStack, 0, sizeof(XML_COMM_TRAVERSE_STACK_STRU));

    /* ��ʼ������ */
    PS_MEM_SET(&stXmlRootNode, 0, sizeof(XML_COMM_NODE_STRU));
    ulResult = XML_COMM_AddAChildNode(&stXmlRootNode, pstXMLRootNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
        return ulResult;
    }
    pstTmpNode = VOS_NULL_PTR;

    /* ��¼��ǰ�Ľڵ� */
    stTmpStackNode.pstXmlNode = &stXmlRootNode;
    stTmpStackNode.ulVisited  = VOS_FALSE;
    XML_COMM_StackPushNode(pstTraverseStack, &stTmpStackNode);

    /* ���Ϊ0ʱ���˳�ѭ�� */
    do
    {
        /* ���ں��ӽڵ� ���һ�û�����ʹ� */
        pstTmpNode = stTmpStackNode.pstXmlNode->pstFirstChild;
        while ( (VOS_NULL_PTR != pstTmpNode)
             && (VOS_FALSE == stTmpStackNode.ulVisited) )
        {
            /* ������ǩ����ǩ�������� */
            ulResult = XML_COMM_PrintStartLabelAndAttribs(pstTmpNode,
                                                          ppcXmlStr,
                                                          pulLenRemain,
                                                          pstTraverseStack->ulStackDepth - 1,
                                                          enFormatting);
            if (XML_COMM_RESULT_SUCCEED != ulResult)
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
                return ulResult;
            }

            /* �ڵ����ó��Ѿ������� */
            stTmpStackNode.pstXmlNode    = pstTmpNode;
            stTmpStackNode.ulVisited     = VOS_TRUE;

            /* ������ӽڵ㣬��ѹջ */
            if (VOS_NULL_PTR != pstTmpNode->pstFirstChild)
            {
                XML_COMM_StackPushNode(pstTraverseStack, &stTmpStackNode);
                stTmpStackNode.ulVisited = VOS_FALSE;
                pstTmpNode               = pstTmpNode->pstFirstChild;
            }
        }

        /* stTmpStackNode�Ľڵ��ӡValue, �ұ�ǩֵ */
        ulResult = XML_COMM_PrintValueAndELabel(stTmpStackNode.pstXmlNode,
                                                ppcXmlStr,
                                                pulLenRemain,
                                                pstTraverseStack->ulStackDepth - 1,
                                                enFormatting);
        if (XML_COMM_RESULT_SUCCEED != ulResult)
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
            return ulResult;
        }

        /*�����ֵܽڵ�*/
        pstTmpNode = stTmpStackNode.pstXmlNode->pstNexBrother;
        while (VOS_NULL_PTR != pstTmpNode)
        {
            /* ������ǩ����ǩ��������ֵ */
            ulResult = XML_COMM_PrintStartLabelAndAttribs(pstTmpNode,
                                                          ppcXmlStr,
                                                          pulLenRemain,
                                                          pstTraverseStack->ulStackDepth - 1,
                                                          enFormatting);
            if (XML_COMM_RESULT_SUCCEED != ulResult)
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
                return ulResult;
            }

            /* �ֵܽڵ���ں��ӽڵ� */
            if  (VOS_NULL_PTR != pstTmpNode->pstFirstChild)
            {
                /*�ֵܽڵ�ѹջ*/
                stTmpStackNode.pstXmlNode = pstTmpNode;
                stTmpStackNode.ulVisited  = VOS_TRUE;
                XML_COMM_StackPushNode(pstTraverseStack, &stTmpStackNode);
                stTmpStackNode.ulVisited  = VOS_FALSE;
                break;
            }
            else
            {
                /*��ӡValue, �ұ�ǩֵ*/
                ulResult = XML_COMM_PrintValueAndELabel(pstTmpNode,
                                                        ppcXmlStr,
                                                        pulLenRemain,
                                                        pstTraverseStack->ulStackDepth - 1,
                                                        enFormatting);
                if (XML_COMM_RESULT_SUCCEED != ulResult)
                {
                    PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
                    return ulResult;
                }

                /*ָ����һ���ֵܽڵ�*/
                pstTmpNode = pstTmpNode->pstNexBrother;
            }
        }

        /*�����ں��ӽڵ㣬���ߵ�ǰ�ڵ��Ѿ����ʹ���,����Ե���ջ*/
        if ( (VOS_NULL_PTR == stTmpStackNode.pstXmlNode->pstFirstChild)
          || (VOS_TRUE == stTmpStackNode.ulVisited) )
        {
            /* ��ջ */
            XML_COMM_StackPopNode(pstTraverseStack, &stTmpStackNode);
        }

    }while (0 != pstTraverseStack->ulStackDepth);

    PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
    return ulResult;
}
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BuildXMLStr(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcXmlStr,
    VOS_UINT32                         *pulLength,
    XML_COMM_FORMATTING_ENUM_UINT8      enXmlFormat)
{
    VOS_UINT32                          ulLenRemain;
    VOS_UINT32                          ulLen;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;

    /* �����Ϸ��Լ�� */
    if ( (VOS_NULL_PTR == pstNode)
      || (VOS_NULL_PTR == pcXmlStr)
      || (VOS_NULL_PTR == pulLength) )
    {
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* ��ӡ�汾��Ϣ */
    ulLen     = VOS_StrLen(XML_COMM_VERSION_STR);
    if (ulLen >= (*pulLength))
    {
        XML_WARNING_LOG("XML_COMM_BuildXMLStr: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
    }

    PS_MEM_CPY(pcXmlStr, XML_COMM_VERSION_STR, ulLen);
    pcXmlStr    += ulLen;
    ulLenRemain = *pulLength - ulLen;

    /* ��ӡ�س����� */
    ulReturnVal = XML_COMM_PrintCRLF(&pcXmlStr, &ulLenRemain, enXmlFormat);
    if (XML_COMM_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* ����XML��ʽ�������ɺ��� */
    ulReturnVal = XML_COMM_GenerateXMLStr(pstNode, &pcXmlStr, &ulLenRemain, enXmlFormat);
    if (XML_COMM_RESULT_SUCCEED == ulReturnVal)
    {
        *pulLength -= ulLenRemain;
        *pcXmlStr = '\0';
    }

    return ulReturnVal;
}


XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ClearXMLCtx(XML_COMM_CTX_STRU *pstXmlCtx)
{
    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �ͷ���������ռ�õ��ڴ� */
    if (VOS_NULL_PTR != pstXmlCtx->pucXMLBuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstXmlCtx->pucXMLBuffer);
    }

    PS_MEM_SET(pstXmlCtx, 0x00, sizeof(XML_COMM_CTX_STRU));
    return XML_COMM_RESULT_SUCCEED;
}

#endif

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

