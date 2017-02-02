

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafMtaComm.h"
#include "TafMtaAgps.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_AGPS_XML_FILL_MSG_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_AGPS)


VOS_UINT32 TAF_MTA_AGPS_FillLatitude(
    XML_COMM_NODE_STRU                 *pstXmlLatitude,
    AGPS_LATITUDE_STRU                 *pstLatitude
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
        <!ELEMENT latitude (north,degrees)>
           <!ELEMENT north (#PCDATA)>
           <!ELEMENT degrees (#PCDATA)>
    */

    /* ��ȡnorth */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlLatitude, MTA_AGPS_LABEL_NORTH);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillLatitude: WARNING: Get north node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��north�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstLatitude->enNorth))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillLatitude: WARNING: transfer north fail!");
        return VOS_ERR;
    }

    /* ��ȡdegrees */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlLatitude, MTA_AGPS_LABEL_DEGREES);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillLatitude: WARNING: Get degrees node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��degrees�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2ul(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstLatitude->ulDegrees))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillLatitude: WARNING: transfer degrees fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillCoordinate(
    XML_COMM_NODE_STRU                 *pstXmlCoordinate,
    AGPS_COORDINATE_STRU               *pstCoordinate
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
    <!ELEMENT coordinate (latitude,longitude)>
            <!ELEMENT latitude (north,degrees)>
               <!ELEMENT north (#PCDATA)>
               <!ELEMENT degrees (#PCDATA)>
            <!ELEMENT longitude (#PCDATA)>
    */

    /* ��ȡlatitude */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlCoordinate, MTA_AGPS_LABEL_LATITUDE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillCoordinate: WARNING: Get latitude node fail!");
        return VOS_ERR;
    }

    /* ���latitude */
    if (VOS_OK != TAF_MTA_AGPS_FillLatitude(pstTmpXmlNode, &pstCoordinate->stLatitude))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillCoordinate: WARNING: TAF_MTA_AGPS_FillLatitude fail!");
        return VOS_ERR;
    }

    /* ��ȡlongitude */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlCoordinate, MTA_AGPS_LABEL_LONGITUDE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillCoordinate: WARNING: Get latitude node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��longitude�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2sl(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstCoordinate->lLongitude))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillCoordinate: WARNING: transfer longitude fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillUncertEllipse(
    XML_COMM_NODE_STRU                 *pstXmlUncertEllipse,
    AGPS_UNCERT_ELLIPSE_STRU           *pstUncertEllipse
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
         <!ELEMENT uncert_ellipse (uncert_semi_major,uncert_semi_minor,orient_major,confidence)>
            <!ELEMENT uncert_semi_major (#PCDATA)>
            <!ELEMENT uncert_semi_minor (#PCDATA)>
            <!ELEMENT orient_major (#PCDATA)>
            <!ELEMENT confidence (#PCDATA)>
    */

    /* ��ȡuncert_semi_major */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlUncertEllipse, MTA_AGPS_LABEL_UNCERT_SEMI_MAJOR);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillUncertEllipse: WARNING: Get uncert_semi_major node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��uncert_semi_major�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstUncertEllipse->ucUncertnSemiMajor))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillUncertEllipse: WARNING: transfer uncert_semi_major fail!");
        return VOS_ERR;
    }

    /* ��ȡuncert_semi_minor */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlUncertEllipse, MTA_AGPS_LABEL_UNCERT_SEMI_MINOR);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillUncertEllipse: WARNING: Get uncert_semi_minor node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��uncert_semi_minor�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstUncertEllipse->ucUncertnSemiMin))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillUncertEllipse: WARNING: transfer uncert_semi_minor fail!");
        return VOS_ERR;
    }

    /* ��ȡorient_major */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlUncertEllipse, MTA_AGPS_LABEL_ORIENT_MAJOR);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillUncertEllipse: WARNING: Get orient_major node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��orient_major�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstUncertEllipse->ucOrientMajorAxis))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillUncertEllipse: WARNING: transfer orient_major fail!");
        return VOS_ERR;
    }

    /* ��ȡconfidence */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlUncertEllipse, MTA_AGPS_LABEL_CONFIDENCE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillUncertEllipse: WARNING: Get confidence node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��confidence�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstUncertEllipse->ucConfidence))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillUncertEllipse: WARNING: transfer confidence fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillAltitude(
    XML_COMM_NODE_STRU                 *pstXmlpstAltitude,
    AGPS_ALTITUDE_STRU                 *pstAltitude
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
         <!ELEMENT altitude (height_above_surface,height)>
            <!ELEMENT height_above_surface (#PCDATA)>
            <!ELEMENT height (#PCDATA)>
    */

    /* ��ȡheight_above_surface */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlpstAltitude, MTA_AGPS_LABEL_HEIGHT_ABOVE_SURFACE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAltitude: WARNING: Get height_above_surface node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��height_above_surface�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstAltitude->enAltiDirect))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAltitude: WARNING: transfer height_above_surface fail!");
        return VOS_ERR;
    }

    /* ��ȡheight */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlpstAltitude, MTA_AGPS_LABEL_HEIGHT);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAltitude: WARNING: Get height node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��height�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2us(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstAltitude->usHeight))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAltitude: WARNING: transfer height fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillEllipPoint(
    XML_COMM_NODE_STRU                 *pstXmlElliPoint,
    AGPS_ELLIP_POINT_STRU              *pstElliPoint
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
    <!ELEMENT ellipsoid_point (coordinate)>
         <!ELEMENT coordinate (latitude,longitude)>
            <!ELEMENT latitude (north,degrees)>
               <!ELEMENT north (#PCDATA)>
               <!ELEMENT degrees (#PCDATA)>
            <!ELEMENT longitude (#PCDATA)>
    */

    /* ��ȡcoordinate�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPoint, MTA_AGPS_LABEL_COORDINATE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPoint: WARNING: Get coordinate node fail!");
        return VOS_ERR;
    }

    /* ���coordinate�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillCoordinate(pstTmpXmlNode, &pstElliPoint->stCoordinate))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPoint: WARNING: TAF_MTA_AGPS_FillCoordinate fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillEllipPointUncertCircle(
    XML_COMM_NODE_STRU                                    *pstXmlElliPointUncertCircle,
    AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU                   *pstElliPointUncertCircle
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
    <!ELEMENT ellipsoid_point_uncert_circle (coordinate,uncert_circle)>
         <!ELEMENT uncert_circle (#PCDATA)>
    */

    /* ��ȡcoordinate�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointUncertCircle, MTA_AGPS_LABEL_COORDINATE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: Get coordinate node fail!");
        return VOS_ERR;
    }

    /* ���coordinate�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillCoordinate(pstTmpXmlNode, &pstElliPointUncertCircle->stCoordinate))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: TAF_MTA_AGPS_FillCoordinate fail!");
        return VOS_ERR;
    }

    /* ��ȡuncert_circle�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointUncertCircle, MTA_AGPS_LABEL_UNCERT_CIRCLE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: Get uncert_circle node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��uncert_circle�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPointUncertCircle->ucUncertnCode))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: transfer uncert_circle fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillEllipPointUncertEllipse(
    XML_COMM_NODE_STRU                 *pstXmlElliPointUncertEllip,
    AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU *pstElliPointUncertEllip
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
      <!ELEMENT ellipsoid_point_uncert_ellipse (coordinate,uncert_ellipse)>
         <!ELEMENT uncert_ellipse (uncert_semi_major,uncert_semi_minor,orient_major,confidence)>
            <!ELEMENT uncert_semi_major (#PCDATA)>
            <!ELEMENT uncert_semi_minor (#PCDATA)>
            <!ELEMENT orient_major (#PCDATA)>
            <!ELEMENT confidence (#PCDATA)>
    */

    /* ��ȡcoordinate�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointUncertEllip, MTA_AGPS_LABEL_COORDINATE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertEllipse: WARNING: Get coordinate node fail!");
        return VOS_ERR;
    }

    /* ���coordinate�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillCoordinate(pstTmpXmlNode, &pstElliPointUncertEllip->stCoordinate))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertEllipse: WARNING: TAF_MTA_AGPS_FillCoordinate fail!");
        return VOS_ERR;
    }

    /* ��ȡuncert_ellipse�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointUncertEllip, MTA_AGPS_LABEL_UNCERT_ELLIPSE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertEllipse: WARNING: Get uncert_ellipse node fail!");
        return VOS_ERR;
    }

    /* ���uncert_ellipse�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillUncertEllipse(pstTmpXmlNode, &pstElliPointUncertEllip->stUncertEllipse))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertEllipse: WARNING: TAF_MTA_AGPS_FillUncertEllipse fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillEllipPointAlt(
    XML_COMM_NODE_STRU                 *pstXmlElliPointAlti,
    AGPS_ELLIP_POINT_ALTI_STRU         *pstElliPointAlti
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
      <!ELEMENT ellipsoid_point_alt (coordinate,altitude)>
         <!ELEMENT altitude (height_above_surface,height)>
            <!ELEMENT height_above_surface (#PCDATA)>
            <!ELEMENT height (#PCDATA)>
    */

    /* ��ȡcoordinate�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAlti, MTA_AGPS_LABEL_COORDINATE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAlt: WARNING: Get coordinate node fail!");
        return VOS_ERR;
    }

    /* ���coordinate�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillCoordinate(pstTmpXmlNode, &pstElliPointAlti->stCoordinate))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAlt: WARNING: TAF_MTA_AGPS_FillCoordinate fail!");
        return VOS_ERR;
    }

    /* ��ȡaltitude�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAlti, MTA_AGPS_LABEL_ALTITUDE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAlt: WARNING: Get altitude node fail!");
        return VOS_ERR;
    }

    /* ���altitude�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillAltitude(pstTmpXmlNode, &pstElliPointAlti->stAltitude))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAlt: WARNING: TAF_MTA_AGPS_FillAltitude fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillEllipPointAltUncertellipse(
    XML_COMM_NODE_STRU                 *pstXmlElliPointAltiEllip,
    AGPS_ELLIP_POINT_ALTI_ELLIP_STRU   *pstElliPointAltiEllip
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
      <!ELEMENT ellipsoid_point_alt_uncertellipse (coordinate,altitude,uncert_semi_major,uncert_semi_minor,orient_major,confidence,uncert_alt)>
         <!ELEMENT uncert_alt (#PCDATA)>
    */

    /* ��ȡcoordinate�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAltiEllip, MTA_AGPS_LABEL_COORDINATE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: Get coordinate node fail!");
        return VOS_ERR;
    }

    /* ���coordinate�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillCoordinate(pstTmpXmlNode, &pstElliPointAltiEllip->stCoordinate))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: TAF_MTA_AGPS_FillCoordinate fail!");
        return VOS_ERR;
    }

    /* ��ȡaltitude�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAltiEllip, MTA_AGPS_LABEL_ALTITUDE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: Get altitude node fail!");
        return VOS_ERR;
    }

    /* ���altitude�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillAltitude(pstTmpXmlNode, &pstElliPointAltiEllip->stAltitude))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: TAF_MTA_AGPS_FillCoordinate altitude fail!");
        return VOS_ERR;
    }

    /* ��ȡuncert_semi_major */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAltiEllip, MTA_AGPS_LABEL_UNCERT_SEMI_MAJOR);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: Get uncert_semi_major node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��uncert_semi_major�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPointAltiEllip->ucUncertnSemiMajor))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: transfer uncert_semi_major fail!");
        return VOS_ERR;
    }

    /* ��ȡuncert_semi_minor */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAltiEllip, MTA_AGPS_LABEL_UNCERT_SEMI_MINOR);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: Get uncert_semi_minor node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��uncert_semi_minor�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPointAltiEllip->ucUncertnSemiMin))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: transfer uncert_semi_minor fail!");
        return VOS_ERR;
    }

    /* ��ȡorient_major */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAltiEllip, MTA_AGPS_LABEL_ORIENT_MAJOR);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: Get orient_major node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��orient_major�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPointAltiEllip->ucOrientMajorAxis))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: transfer orient_major fail!");
        return VOS_ERR;
    }

    /* ��ȡconfidence */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAltiEllip, MTA_AGPS_LABEL_CONFIDENCE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: Get confidence node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��confidence�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPointAltiEllip->ucConfidence))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: transfer confidence fail!");
        return VOS_ERR;
    }

    /* ��ȡuncert_alt */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPointAltiEllip, MTA_AGPS_LABEL_UNCERT_ALT);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: Get uncert_alt node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��uncert_alt�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPointAltiEllip->ucUncertnAlti))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointAltUncertellipse: WARNING: transfer uncert_alt fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillEllipsArc(
    XML_COMM_NODE_STRU                 *pstXmlElliPArc,
    AGPS_ELLIP_ARC_STRU                *pstElliPArc
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
      <!ELEMENT ellips_arc (coordinate,inner_rad,uncert_rad,offset_angle,included_angle,confidence)>
         <!ELEMENT inner_rad (#PCDATA)>
         <!ELEMENT uncert_rad (#PCDATA)>
         <!ELEMENT offset_angle (#PCDATA)>
         <!ELEMENT included_angle (#PCDATA)>
    */

    /* ��ȡcoordinate�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPArc, MTA_AGPS_LABEL_COORDINATE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipsArc: WARNING: Get coordinate node fail!");
        return VOS_ERR;
    }

    /* ���coordinate�ӽڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillCoordinate(pstTmpXmlNode, &pstElliPArc->stCoordinate))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipsArc: WARNING: TAF_MTA_AGPS_FillCoordinate fail!");
        return VOS_ERR;
    }

    /* ��ȡinner_rad�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPArc, MTA_AGPS_LABEL_INNER_RAD);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: Get inner_rad node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��inner_rad�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2us(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPArc->usInnerRad))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: transfer inner_rad fail!");
        return VOS_ERR;
    }

    /* ��ȡuncert_rad�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPArc, MTA_AGPS_LABEL_UNCERT_RAD);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: Get uncert_rad node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��uncert_rad�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPArc->ucUncertRad))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: transfer uncert_rad fail!");
        return VOS_ERR;
    }

    /* ��ȡoffset_angle�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPArc, MTA_AGPS_LABEL_OFFSET_ANGLE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: Get offset_angle node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��offset_angle�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPArc->ucOffsetAngle))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: transfer offset_angle fail!");
        return VOS_ERR;
    }

    /* ��ȡincluded_angle�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPArc, MTA_AGPS_LABEL_INCLUDED_ANGLE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: Get included_angle node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��included_angle�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPArc->ucIncludedAngle))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: transfer included_angle fail!");
        return VOS_ERR;
    }

    /* ��ȡconfidence�ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlElliPArc, MTA_AGPS_LABEL_CONFIDENCE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: Get confidence node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��confidence�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstElliPArc->ucConfidence))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillEllipPointUncertCircle: WARNING: transfer confidence fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillShapData(
    XML_COMM_NODE_STRU                 *pstXmlShapeData,
    AGPS_SHAPE_DATA_STRU               *pstShapeData
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;
    VOS_UINT32                          ulResult;

    /*
           <!ELEMENT shape_data (ellipsoid_point|ellipsoid_point_uncert_circle|ellipsoid_point_uncert_ellipse|polygon|ellipsoid_point_alt|ellipsoid_point_alt_uncertellipse|ellips_arc)>
              <!ELEMENT ellipsoid_point (coordinate)>
                 <!ELEMENT coordinate (latitude,longitude)>
                    <!ELEMENT latitude (north,degrees)>
                       <!ELEMENT north (#PCDATA)>
                       <!ELEMENT degrees (#PCDATA)>
                    <!ELEMENT longitude (#PCDATA)>
              <!ELEMENT ellipsoid_point_uncert_circle (coordinate,uncert_circle)>
                 <!ELEMENT uncert_circle (#PCDATA)>
              <!ELEMENT ellipsoid_point_uncert_ellipse (coordinate,uncert_ellipse)>
                 <!ELEMENT uncert_ellipse (uncert_semi_major,uncert_semi_minor,orient_major,confidence)>
                    <!ELEMENT uncert_semi_major (#PCDATA)>
                    <!ELEMENT uncert_semi_minor (#PCDATA)>
                    <!ELEMENT orient_major (#PCDATA)>
                    <!ELEMENT confidence (#PCDATA)>
              <!ELEMENT polygon (coordinate+)>
              <!ELEMENT ellipsoid_point_alt (coordinate,altitude)>
                 <!ELEMENT altitude (height_above_surface,height)>
                    <!ELEMENT height_above_surface (#PCDATA)>
                    <!ELEMENT height (#PCDATA)>
              <!ELEMENT ellipsoid_point_alt_uncertellipse (coordinate,altitude,uncert_semi_major,uncert_semi_minor,orient_major,confidence,uncert_alt)>
                 <!ELEMENT uncert_alt (#PCDATA)>
              <!ELEMENT ellips_arc (coordinate,inner_rad,uncert_rad,offset_angle,included_angle,confidence)>
                 <!ELEMENT inner_rad (#PCDATA)>
                 <!ELEMENT uncert_rad (#PCDATA)>
                 <!ELEMENT offset_angle (#PCDATA)>
                 <!ELEMENT included_angle (#PCDATA)>
     */

    /* ��ȡ�ӽڵ�ĸ���������ֻ����һ�� */
    if (MTA_AGPS_XML_NODE_COUNT_1 != XML_COMM_GetChildCount(pstXmlShapeData))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillShapData: WARNING: Number of ChildNodes error!");
        return VOS_ERR;
    }

    /* ȡ�õ�һ���ӽڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByIndex(pstXmlShapeData, MTA_AGPS_XML_NODE_INDEX_0);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillShapData: WARNING: Get first node fail!");
        return VOS_ERR;
    }

    /* �жϵ�һ���ڵ�Ϊ�������͵Ľڵ� */
    if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_ELLIPSOID_POINT))
    {
        ulResult = TAF_MTA_AGPS_FillEllipPoint(pstTmpXmlNode, &pstShapeData->u.stEllipPoint);
    }
    else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_ELLIPSOID_POINT_UNCERT_CIRCLE))
    {
        ulResult = TAF_MTA_AGPS_FillEllipPointUncertCircle(pstTmpXmlNode, &pstShapeData->u.stEllipPointUncertCircle);
    }
    else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_ELLIPSOID_POINT_UNCERT_ELLIPSE))
    {
        ulResult = TAF_MTA_AGPS_FillEllipPointUncertEllipse(pstTmpXmlNode, &pstShapeData->u.stEllipPointUncertEllip);
    }
    else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_ELLIPSOID_POINT_ALT))
    {
        ulResult = TAF_MTA_AGPS_FillEllipPointAlt(pstTmpXmlNode, &pstShapeData->u.stEllipPointAlti);
    }
    else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_ELLIPSOID_POINT_ALT_UNCERTELLIPSE))
    {
        ulResult = TAF_MTA_AGPS_FillEllipPointAltUncertellipse(pstTmpXmlNode, &pstShapeData->u.stEllipPointAltiEllip);
    }
    else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_ELLIPS_ARC))
    {
        ulResult = TAF_MTA_AGPS_FillEllipsArc(pstTmpXmlNode, &pstShapeData->u.stEllipArc);
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillShapData: WARNING: FInd first ChildNode fail!");
        ulResult = VOS_ERR;
    }

    return ulResult;
}
VOS_UINT32 TAF_MTA_AGPS_FillLocationPara(
    XML_COMM_NODE_STRU                 *pstXmlLocationPara,
    AGPS_LOCATION_PARA_STRU            *pstLocationPara
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*XML DTD for <location_parameters>:
    <?xml version="1.0" ?>
    <!DOCTYPE location_parameters [
    <!ELEMENT location_parameters (time?,direction?,shape_data,velocity_data?)>
       <!ELEMENT time (#PCDATA)>
       <!ELEMENT direction (#PCDATA)>
       <!ELEMENT shape_data (ellipsoid_point|ellipsoid_point_uncert_circle|ellipsoid_point_uncert_ellipse|polygon|ellipsoid_point_alt|ellipsoid_point_alt_uncertellipse|ellips_arc)>
          <!ELEMENT ellipsoid_point (coordinate)>
             <!ELEMENT coordinate (latitude,longitude)>
                <!ELEMENT latitude (north,degrees)>
                   <!ELEMENT north (#PCDATA)>
                   <!ELEMENT degrees (#PCDATA)>
                <!ELEMENT longitude (#PCDATA)>
          <!ELEMENT ellipsoid_point_uncert_circle (coordinate,uncert_circle)>
             <!ELEMENT uncert_circle (#PCDATA)>
          <!ELEMENT ellipsoid_point_uncert_ellipse (coordinate,uncert_ellipse)>
             <!ELEMENT uncert_ellipse (uncert_semi_major,uncert_semi_minor,orient_major,confidence)>
                <!ELEMENT uncert_semi_major (#PCDATA)>
                <!ELEMENT uncert_semi_minor (#PCDATA)>
                <!ELEMENT orient_major (#PCDATA)>
                <!ELEMENT confidence (#PCDATA)>
          <!ELEMENT polygon (coordinate+)>
          <!ELEMENT ellipsoid_point_alt (coordinate,altitude)>
             <!ELEMENT altitude (height_above_surface,height)>
                <!ELEMENT height_above_surface (#PCDATA)>
                <!ELEMENT height (#PCDATA)>
          <!ELEMENT ellipsoid_point_alt_uncertellipse (coordinate,altitude,uncert_semi_major,uncert_semi_minor,orient_major,confidence,uncert_alt)>
             <!ELEMENT uncert_alt (#PCDATA)>
          <!ELEMENT ellips_arc (coordinate,inner_rad,uncert_rad,offset_angle,included_angle,confidence)>
             <!ELEMENT inner_rad (#PCDATA)>
             <!ELEMENT uncert_rad (#PCDATA)>
             <!ELEMENT offset_angle (#PCDATA)>
             <!ELEMENT included_angle (#PCDATA)>
       <!ELEMENT velocity_data
    (hor_velocity?,vert_velocity?,vert_velocity_direction?,hor_uncert?,vert_uncert?)>
          <!ELEMENT hor_velocity (#PCDATA)>
          <!ELEMENT vert_velocity (#PCDATA)>
          <!ELEMENT vert_velocity_direction (#PCDATA)>
          <!ELEMENT hor_uncert (#PCDATA)>
          <!ELEMENT vert_uncert (#PCDATA)>
    ]>
    */

    /* ��ѡԪ�ص�bitλ��ʼ��ΪFalse */
    pstLocationPara->bitOpTime      = VOS_FALSE;
    pstLocationPara->bitOpDirection = VOS_FALSE;

    /* ��ȡtime�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlLocationPara, MTA_AGPS_LABEL_TIME);
    if (VOS_NULL_PTR != pstTmpXmlNode)
    {
        /* ���ַ�����ʽ��time�ڵ�ֵת��Ϊ��ֵ */
        if (VOS_OK == TAF_MTA_Ac2ul(pstTmpXmlNode->pcNodeValue,
                                    pstTmpXmlNode->ulValueLength,
                                    &pstLocationPara->ulTime))
        {
            pstLocationPara->bitOpTime = VOS_TRUE;
        }
        else
        {
            /* ����time�ǿ�ѡ�ڵ㣬���Լ������ʧ�ܣ�Ҳ������VOS_ERR�����Ǽ�����������㣬��־λ����ΪVOS_FALSE */
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillLocationPara: WARNING: Transfer time fail!");
        }
    }

    /* ��ȡdirection�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlLocationPara, MTA_AGPS_LABEL_DIRECTION);
    if (VOS_NULL_PTR != pstTmpXmlNode)
    {
        /* ���ַ�����ʽ��direction�ڵ�ֵת��Ϊ��ֵ */
        if (VOS_OK == TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                    pstTmpXmlNode->ulValueLength,
                                    &pstLocationPara->ucDirection))
        {
            pstLocationPara->bitOpDirection = VOS_TRUE;
        }
        else
        {
            /* ����direction�ǿ�ѡ�ڵ㣬���Լ������ʧ�ܣ�Ҳ������VOS_ERR�����Ǽ�����������㣬��־λ����ΪVOS_FALSE */
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillLocationPara: WARNING: Transfer direction fail!");
        }
    }

    /* ��ȡshape_data�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlLocationPara, MTA_AGPS_LABEL_SHAPE_DATA);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillLocationPara: WARNING: get shape_data node fail!");
        return VOS_ERR;
    }

    if (VOS_OK != TAF_MTA_AGPS_FillShapData(pstTmpXmlNode, &pstLocationPara->stShapeData))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillLocationPara: WARNING: TAF_MTA_AGPS_FillShapData fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillLocationInfo(
    XML_COMM_NODE_STRU                 *pstXmlLocationInfo,
    AGPS_LOCATION_INFO_STRU            *pstLocationInfo
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
        <!ELEMENT location (location_parameters,time_of_fix?)>
            <!ELEMENT time_of_fix (#PCDATA)>
    */

    /* ��ѡԪ�ص�bitλ��ʼ��ΪFalse */
    pstLocationInfo->bitOpTimeOfFix = VOS_FALSE;

    /* ��ȡlocation_parameters�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlLocationInfo, MTA_AGPS_LABEL_LOCATION_PARAMENTERS);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillLocationInfo: WARNING: get location_parameters node fail!");
        return VOS_ERR;
    }

    /* ���location_parameters�ڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillLocationPara(pstTmpXmlNode, &pstLocationInfo->stLocationPara))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillLocationInfo: WARNING: TAF_MTA_AGPS_FillLocationPara fail!");
        return VOS_ERR;
    }

    /* ��ȡtime_of_fix�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlLocationInfo, MTA_AGPS_LABEL_TIME_OF_FIX);
    if (VOS_NULL_PTR != pstTmpXmlNode)
    {
        /* ���ַ�����ʽ��time_of_fix�ڵ�ֵת��Ϊ��ֵ */
        if (VOS_OK == TAF_MTA_Ac2ul(pstTmpXmlNode->pcNodeValue,
                                    pstTmpXmlNode->ulValueLength,
                                    &pstLocationInfo->ulTimeOfFix))
        {
            pstLocationInfo->bitOpTimeOfFix = VOS_TRUE;
        }
        else
        {
            /* ����time_of_fix�ǿ�ѡ�ڵ㣬���Լ������ʧ�ܣ�Ҳ������VOS_ERR�����Ǽ�����������㣬��־λ����ΪVOS_FALSE */
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillLocationInfo: WARNING: Transfer time_of_fix fail!");
        }
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillRefTimeOnly(
    XML_COMM_NODE_STRU                 *pstXmlRefTimeOnly,
    AGPS_REF_TIME_ONLY_STRU            *pstRefTimeOnly
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
       <!ELEMENT ref_time_only (tow_msec)>
          <!ELEMENT tow_msec (#PCDATA)>
    */

    /* ��ȡtow_msec�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlRefTimeOnly, MTA_AGPS_LABEL_TOW_MSEC);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillRefTimeOnly: WARNING: Get node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ�Ľڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2ul(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstRefTimeOnly->ulTow))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillRefTimeOnly: WARNING: transfer ulTow fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillMultiPathOfMeasParams(
    XML_COMM_NODE_STRU                 *pstXmlGpsMeasurePara,
    AGPS_MULTI_PATH_INDIC_ENUM_UINT8   *penMultipathIndic
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡmulti_path�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlGpsMeasurePara, MTA_AGPS_LABEL_MULTI_PATH);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMultiPathOfMeasParams: WARNING: Get multi_path node fail!");
        return VOS_ERR;
    }

    /* ��ȡmulti_path�ڵ��literal���Խڵ�ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstTmpXmlNode, MTA_AGPS_ATTRIB_LITERAL);
    if (VOS_NULL_PTR == pstTmpXmlNodeAttrib)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMultiPathOfMeasParams: WARNING: Get literal attribute of multi_path node fail!");
        return VOS_ERR;
    }

    /* ��ȡmulti_path�ڵ��literal����ֵ */
    if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstTmpXmlNodeAttrib, MTA_AGPS_ATTRIB_VALUE_NOT_MEASURED))
    {
        *penMultipathIndic = AGPS_MULTI_PATH_INDIC_NOT_MEAS;
    }
    else if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstTmpXmlNodeAttrib, MTA_AGPS_ATTRIB_VALUE_NOT_LOW))
    {
        *penMultipathIndic = AGPS_MULTI_PATH_INDIC_LOW;
    }
    else if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstTmpXmlNodeAttrib, MTA_AGPS_ATTRIB_VALUE_NOT_MEDIA))
    {
        *penMultipathIndic = AGPS_MULTI_PATH_INDIC_MEDIUM;
    }
    else if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstTmpXmlNodeAttrib, MTA_AGPS_ATTRIB_VALUE_NOT_HIGH))
    {
        *penMultipathIndic = AGPS_MULTI_PATH_INDIC_HIGH;
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMultiPathOfMeasParams: WARNING: literal attribute of multi_path node is abnormal!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillMeasParams(
    XML_COMM_NODE_STRU                 *pstXmlGpsMeasurePara,
    AGPS_GPS_MEASURE_PARA_STRU         *pstGpsMeasurePara
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
       <!ELEMENT meas_params (sat_id,carr2_noise,dopl,whole_chips,fract_chips,multi_path,psr_rms_err)>
          <!ELEMENT carr2_noise (#PCDATA)>
          <!ELEMENT dopl (#PCDATA)>
          <!ELEMENT whole_chips (#PCDATA)>
          <!ELEMENT fract_chips (#PCDATA)>
          <!ELEMENT multi_path EMPTY>
          <!ATTLIST multi_path literal (not_measured|low|medium|high) #REQUIRED>
          <!ELEMENT psr_rms_err (#PCDATA)>
    */

    /* ��ȡsat_id�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlGpsMeasurePara, MTA_AGPS_LABEL_SAT_ID);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Get sat_id node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��sat_id�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstGpsMeasurePara->ucSatId))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Transfer sat_id fail!");
        return VOS_ERR;
    }

    /* ��ȡcarr2_noise�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlGpsMeasurePara, MTA_AGPS_LABEL_CARR2_NOISE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Get carr2_noise node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��carr2_noise�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstGpsMeasurePara->ucCarr2Noise))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Transfer carr2_noise fail!");
        return VOS_ERR;
    }

    /* ��ȡdopl�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlGpsMeasurePara, MTA_AGPS_LABEL_DOP1);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Get dopl node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��dopl�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2sl(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstGpsMeasurePara->lDoppler))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Transfer dopl fail!");
        return VOS_ERR;
    }

    /* ��ȡwhole_chips�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlGpsMeasurePara, MTA_AGPS_LABEL_WHOLE_CHIPS);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Get whole_chips node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��whole_chips�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2us(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstGpsMeasurePara->usWholeChips))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Transfer whole_chips fail!");
        return VOS_ERR;
    }

    /* ��ȡfract_chips�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlGpsMeasurePara, MTA_AGPS_LABEL_FRACT_CHIPS);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Get fract_chips node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��fract_chips�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2us(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstGpsMeasurePara->usFracChips))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Transfer fract_chips fail!");
        return VOS_ERR;
    }

    /* ��� multi_path �ڵ� */
    if (VOS_OK != TAF_MTA_AGPS_FillMultiPathOfMeasParams(pstXmlGpsMeasurePara, &pstGpsMeasurePara->enMultipathIndic))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: TAF_MTA_AGPS_FillMultiPathOfMeasParams fail!");
        return VOS_ERR;
    }

    /* ��ȡpsr_rms_err�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlGpsMeasurePara, MTA_AGPS_LABEL_PSR_RMS_ERR);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Get psr_rms_err node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��psr_rms_err�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                pstTmpXmlNode->ulValueLength,
                                &pstGpsMeasurePara->ucPseuRangeRmsErr))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillMeasParams: WARNING: Transfer psr_rms_err fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillGpsMeas(
    XML_COMM_NODE_STRU                 *pstXmlGpsMeasureInfo,
    AGPS_GPS_MEASURE_INFO_STRU         *pstGpsMeasureInfo
)
{
    VOS_INT32                           lCount;
    VOS_INT32                           lLoop;
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;
    VOS_UINT8                           ucRefTimeOnlyCnt;

    /*
    <!ELEMENT GPS_meas (ref_time_only,meas_params*)>
       <!ELEMENT ref_time_only (tow_msec)>
          <!ELEMENT tow_msec (#PCDATA)>
       <!ELEMENT meas_params (sat_id,carr2_noise,dopl,whole_chips,fract_chips,multi_path,psr_rms_err)>
          <!ELEMENT carr2_noise (#PCDATA)>
          <!ELEMENT dopl (#PCDATA)>
          <!ELEMENT whole_chips (#PCDATA)>
          <!ELEMENT fract_chips (#PCDATA)>
          <!ELEMENT multi_path EMPTY>
          <!ATTLIST multi_path literal (not_measured|low|medium|high) #REQUIRED>
          <!ELEMENT psr_rms_err (#PCDATA)>
    */

    lCount = XML_COMM_GetChildCount(pstXmlGpsMeasureInfo);

    if (lCount < MTA_AGPS_XML_NODE_COUNT_1)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillGpsMeas: WARNING: lCount < 1");
        return VOS_ERR;
    }

    /* �ڵ������ʼ��Ϊ0 */
    pstGpsMeasureInfo->ulGpsMeasNum = 0;
    ucRefTimeOnlyCnt                = 0;

    /* �������нڵ� */
    for (lLoop = 0; lLoop < lCount; lLoop++)
    {
        /* ��������ȡ�ڵ� */
        pstTmpXmlNode = XML_COMM_GetChildNodeByIndex(pstXmlGpsMeasureInfo, lLoop);

        /* �жϽڵ����� */
        if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_REF_TIME_ONLY))
        {
            /* ��� ref_time_only �ڵ� */
            if (VOS_OK != TAF_MTA_AGPS_FillRefTimeOnly(pstTmpXmlNode, &pstGpsMeasureInfo->stRefTimeOnly))
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_FillGpsMeas: WARNING: TAF_MTA_AGPS_FillRefTimeOnly fail!");
                return VOS_ERR;
            }

            ucRefTimeOnlyCnt++;
        }
        else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_MEAS_PARAMS))
        {
            /* ��� meas_params �ڵ� */
            if (VOS_OK != TAF_MTA_AGPS_FillMeasParams(pstTmpXmlNode, &pstGpsMeasureInfo->astGpsMeasParaList[pstGpsMeasureInfo->ulGpsMeasNum]))
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_FillGpsMeas: WARNING: TAF_MTA_AGPS_FillMeasParams fail!");
                return VOS_ERR;
            }

            /* �ڵ������1 */
            pstGpsMeasureInfo->ulGpsMeasNum++;
        }
        else
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillGpsMeas: WARNING: invalid label name!");
            return VOS_ERR;
        }
    }

    /* �ж�ref_time_only�ڵ�����Ƿ�Ϊ1 */
    if (MTA_AGPS_XML_NODE_COUNT_1 != ucRefTimeOnlyCnt)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillGpsMeas: WARNING: Count of ref_time_only is abnormal!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillAttributeTrueOrFalse(
    XML_COMM_NODE_ATTRIBUTE_STRU        *pstXmlAttrib,
    VOS_UINT8                           *pucElement
)
{
    if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstXmlAttrib, MTA_AGPS_ATTRIB_VALUE_TRUE))
    {
        *pucElement = VOS_TRUE;
    }
    else if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstXmlAttrib, MTA_AGPS_ATTRIB_VALUE_FALSE))
    {
        *pucElement = VOS_FALSE;
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAttributeTrueOrFalse: WARNING: Attribute is abnormal!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillAlmReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucAlmReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��alm_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_ALM_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucAlmReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillAlmReqOfGpsAssistReq: WARNING: alm_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillUtcModelReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucUtcModelReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��UTC_model_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_UTC_MODEM_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucUtcModelReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillUtcModelReqOfGpsAssistReq: WARNING: UTC_model_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillIonReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucIonReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��ion_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_ION_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucIonReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillIonReqOfGpsAssistReq: WARNING: ion_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillNavModelReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucNavModelReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��nav_model_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_NAV_MODEL_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucNavModelReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillNavModelReqOfGpsAssistReq: WARNING: nav_model_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillDgpsCorrReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucDgpsCorrReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��DGPS_corr_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_DGPS_CORR_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucDgpsCorrReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillDgpsCorrReqOfGpsAssistReq: WARNING: DGPS_corr_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillRefLocReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucRefLocReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��ref_loc_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_REF_LOC_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucRefLocReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillRefLocReqOfGpsAssistReq: WARNING: ref_loc_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillRefTimeReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucRefTimeReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��ref_time_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_REF_TIME_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucRefTimeReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillRefTimeReqOfGpsAssistReq: WARNING: ref_time_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillAquAssistReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucAquAssistReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��aqu_assist_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_AQU_ASSIST_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucAquAssistReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillAquAssistReqOfGpsAssistReq: WARNING: aqu_assist_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillRtIntegrReqOfGpsAssistReq(
    XML_COMM_NODE_STRU                 *pstXmlAssistReq,
    VOS_UINT8                          *pucRtIntegrReq
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /* ��ȡGPS_assist_req�ڵ��rt_integr_req����ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstXmlAssistReq, MTA_AGPS_ATTRIB_RT_INTEGR_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNodeAttrib)
    {
        if (VOS_OK != TAF_MTA_AGPS_FillAttributeTrueOrFalse(pstTmpXmlNodeAttrib, pucRtIntegrReq))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillRtIntegrReqOfGpsAssistReq: WARNING: rt_integr_req attribute of GPS_assist_req node is abnormal!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_AGPS_FillGpsAssistReq(
    XML_COMM_NODE_STRU                                     *pstXmlAssistReq,
    AGPS_POSITION_GPS_ADDITION_ASSIST_REQ_STRU             *pstAgpsAssistReq
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
    <!ELEMENT GPS_assist_req  (nav_addl_data?)>
       <!ATTLIST GPS_assist_req
          alm_req        (true|false) "false"
          UTC_model_req  (true|false) "false"
          ion_req        (true|false) "false"
          nav_model_req  (true|false) "false"
          DGPS_corr_req  (true|false) "false"
          ref_loc_req    (true|false) "false"
          ref_time_req   (true|false) "false"
          aqu_assist_req (true|false) "false"
          rt_integr_req  (true|false) "false"
          >
       <!ELEMENT nav_addl_data (GPS_week,GPS_toe,ttoe_limit,addl_req_sat*)>
          <!ELEMENT GPS_week (#PCDATA)>
          <!ELEMENT GPS_toe (#PCDATA)>
          <!ELEMENT ttoe_limit (#PCDATA)>
          <!ELEMENT addl_req_sat (sat_id,iode)>
             <!ELEMENT iode (#PCDATA)>
    */

    /* ��GPS_assist_req������ֵ��ΪĬ��ֵfalse */
    pstAgpsAssistReq->ucAlmReq          = VOS_FALSE;
    pstAgpsAssistReq->ucUtcModelReq     = VOS_FALSE;
    pstAgpsAssistReq->ucIonReq          = VOS_FALSE;
    pstAgpsAssistReq->ucNavModelReq     = VOS_FALSE;
    pstAgpsAssistReq->ucDgpsCorrReq     = VOS_FALSE;
    pstAgpsAssistReq->ucRefLocReq       = VOS_FALSE;
    pstAgpsAssistReq->ucRefTimeReq      = VOS_FALSE;
    pstAgpsAssistReq->ucAquAssistReq    = VOS_FALSE;
    pstAgpsAssistReq->ucRtIntegrReq     = VOS_FALSE;

    /* ��ѡԪ�ص�bitλ��ʼ��ΪFalse */
    pstAgpsAssistReq->bitOpNavAddData   = VOS_FALSE;


    /* ��ȡGPS_assist_req�ڵ��alm_req����ָ�� */
    if(VOS_OK != TAF_MTA_AGPS_FillAlmReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucAlmReq))
    {
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ��UTC_model_req���Խڵ�ָ�� */
    if (VOS_OK != TAF_MTA_AGPS_FillUtcModelReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucUtcModelReq))
    {
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ��ion_req���Խڵ�ָ�� */
    if (VOS_OK != TAF_MTA_AGPS_FillIonReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucIonReq))
    {
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ��nav_model_req���Խڵ�ָ�� */
    if (VOS_OK != TAF_MTA_AGPS_FillNavModelReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucNavModelReq))
    {
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ��DGPS_corr_req���Խڵ�ָ�� */
    if (VOS_OK != TAF_MTA_AGPS_FillDgpsCorrReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucDgpsCorrReq))
    {
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ��ref_loc_req���Խڵ�ָ�� */
    if (VOS_OK != TAF_MTA_AGPS_FillRefLocReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucRefLocReq))
    {
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ��ref_time_req���Խڵ�ָ�� */
    if (VOS_OK != TAF_MTA_AGPS_FillRefTimeReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucRefTimeReq))
    {
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ��aqu_assist_req���Խڵ�ָ�� */
    if (VOS_OK != TAF_MTA_AGPS_FillAquAssistReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucAquAssistReq))
    {
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ��rt_integr_req���Խڵ�ָ�� */
    if (VOS_OK != TAF_MTA_AGPS_FillRtIntegrReqOfGpsAssistReq(pstXmlAssistReq, &pstAgpsAssistReq->ucRtIntegrReq))
    {
        return VOS_ERR;
    }

    /* ��ȡnav_addl_data�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlAssistReq, MTA_AGPS_LABEL_NAV_ADDL_DATA);
    if (VOS_NULL_PTR != pstTmpXmlNode)
    {
        /* ���nav_addl_data�ڵ� */
        if (VOS_OK == TAF_MTA_AGPS_FillNavAddlData(pstTmpXmlNode, &pstAgpsAssistReq->stNavAddData))
        {
            pstAgpsAssistReq->bitOpNavAddData = VOS_TRUE;
        }
        else
        {
            /* ����nav_addl_data�ǿ�ѡ�ڵ㣬���Լ������ʧ�ܣ�Ҳ������VOS_ERR�����Ǽ�����������㣬��־λ����ΪVOS_FALSE */
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillGpsAssistReq: WARNING: TAF_MTA_AGPS_FillNavAddlData fail!");
        }
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillAddlReqSat(
    XML_COMM_NODE_STRU                 *pstXmlAdditionReqSat,
    AGPS_ADDITION_REQ_SAT_STRU         *pstAdditionReqSat
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;

    /*
       <!ELEMENT addl_req_sat (sat_id,iode)>
         <!ELEMENT iode (#PCDATA)>

    */

    /* ��ȡsat_id�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlAdditionReqSat, MTA_AGPS_LABEL_SAT_ID);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAddlReqSat: WARNING: Get sat_id node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��sat_id�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                               pstTmpXmlNode->ulValueLength,
                               &pstAdditionReqSat->ucSatId))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAddlReqSat: WARNING: transfer ucSatId fail!");
        return VOS_ERR;
    }

    /* ��ȡiode�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlAdditionReqSat, MTA_AGPS_LABEL_IODE_LOWER_CASE);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAddlReqSat: WARNING: Get iode node fail!");
        return VOS_ERR;
    }

    /* ���ַ�����ʽ��iode�ڵ�ֵת��Ϊ��ֵ */
    if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                               pstTmpXmlNode->ulValueLength,
                               &pstAdditionReqSat->ucIode))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillAddlReqSat: WARNING: transfer ucIode fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillNavAddlData(
    XML_COMM_NODE_STRU                 *pstXmlNavAddData,
    AGPS_NAV_ADD_DATA_STRU             *pstNavAddData
)
{
    VOS_INT32                           lCount;
    VOS_INT32                           lLoop;
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;
    VOS_UINT8                           ucGpsWeekCnt;
    VOS_UINT8                           ucGpsToeCnt;
    VOS_UINT8                           ucTtoeLimitCnt;

    /*
       <!ELEMENT nav_addl_data (GPS_week,GPS_toe,ttoe_limit,addl_req_sat*)>
          <!ELEMENT GPS_week (#PCDATA)>
          <!ELEMENT GPS_toe (#PCDATA)>
          <!ELEMENT ttoe_limit (#PCDATA)>
          <!ELEMENT addl_req_sat (sat_id,iode)>
             <!ELEMENT iode (#PCDATA)>
    */

    lCount = XML_COMM_GetChildCount(pstXmlNavAddData);

    if (lCount < MTA_AGPS_XML_NODE_COUNT_3)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillNavAddlData: WARNING: lCount < 3");
        return VOS_ERR;
    }

    /* �ڵ������ʼ��Ϊ0 */
    pstNavAddData->usAddlReqSatNum = 0;
    ucGpsWeekCnt                   = 0;
    ucGpsToeCnt                    = 0;
    ucTtoeLimitCnt                 = 0;

    /* �������нڵ� */
    for (lLoop = 0; lLoop < lCount; lLoop++)
    {
        /* ��������ȡ�ڵ� */
        pstTmpXmlNode = XML_COMM_GetChildNodeByIndex(pstXmlNavAddData, lLoop);

        /* �жϽڵ����� */
        if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_GPS_WEEK))
        {
            /* ת��GPS_weekΪ��ֵ */
            if (VOS_OK != TAF_MTA_Ac2us(pstTmpXmlNode->pcNodeValue,
                                          pstTmpXmlNode->ulValueLength,
                                          &pstNavAddData->usGpsWeek))
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_FillNavAddlData: WARNING: fill GPS_week fail!");
                return VOS_ERR;
            }

            ucGpsWeekCnt++;
        }
        else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_GPS_TOE))
        {
            /* ת�� GPS_toe Ϊ��ֵ */
            if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                          pstTmpXmlNode->ulValueLength,
                                          &pstNavAddData->ucGpsToe))
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_FillNavAddlData: WARNING: fill GPS_toe fail!");
                return VOS_ERR;
            }

            ucGpsToeCnt++;
        }
        else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_TTOE_LIMIT))
        {
            /* ת�� ttoe_limit Ϊ��ֵ */
            if (VOS_OK != TAF_MTA_Ac2uc(pstTmpXmlNode->pcNodeValue,
                                          pstTmpXmlNode->ulValueLength,
                                          &pstNavAddData->ucTtoeLimit))
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_FillNavAddlData: WARNING: fill ttoe_limit fail!");
                return VOS_ERR;
            }

            ucTtoeLimitCnt++;
        }
        else if (VOS_TRUE == XML_COMM_CheckLabelName(pstTmpXmlNode, MTA_AGPS_LABEL_ADDL_REQ_SAT))
        {
            if (VOS_OK != TAF_MTA_AGPS_FillAddlReqSat(pstTmpXmlNode, &pstNavAddData->astAddlReqSat[pstNavAddData->usAddlReqSatNum]))
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_FillNavAddlData: WARNING: TAF_MTA_AGPS_FillAddlReqSat fail!");
                return VOS_ERR;
            }

            /* �ڵ������1 */
            pstNavAddData->usAddlReqSatNum++;
        }
        else
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillNavAddlData: WARNING: Invalid label!");
            return VOS_ERR;
        }
    }

    if ((MTA_AGPS_XML_NODE_COUNT_1 != ucGpsWeekCnt)
        || (MTA_AGPS_XML_NODE_COUNT_1 != ucGpsToeCnt)
        || (MTA_AGPS_XML_NODE_COUNT_1 != ucTtoeLimitCnt))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillNavAddlData: WARNING: Count of mandatory lable is abnormal!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_AGPS_FillPosErr(
    XML_COMM_NODE_STRU                 *pstXmlPositionErr,
    AGPS_POSITION_ERR_STRU             *pstPositionErr
)
{
    XML_COMM_NODE_STRU                 *pstTmpXmlNode;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpXmlNodeAttrib;

    /*
    <!ELEMENT pos_err (err_reason, GPS_assist_req?)>
       <!ELEMENT err_reason_EMPTY>
       <!ATTLIST err_reason literal (undefined_error|not_enough_gps_satellites|gps_assist_data_missing) #REQUIRED>
    */

    /* ��ѡԪ�ص�bitλ��ʼ��ΪFalse */
    pstPositionErr->bitOpAssistDataReq = VOS_FALSE;

    /* ��ȡerr_reason�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlPositionErr, MTA_AGPS_LABEL_ERR_REASON);
    if (VOS_NULL_PTR == pstTmpXmlNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillPosErr: WARNING: Get err_reason node fail!");
        return VOS_ERR;
    }

    /* ��ȡerr_reason�ڵ��literal���Խڵ�ָ�� */
    pstTmpXmlNodeAttrib = XML_COMM_GetAttributeByAttributeName(pstTmpXmlNode, MTA_AGPS_ATTRIB_LITERAL);
    if (VOS_NULL_PTR == pstTmpXmlNodeAttrib)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillPosErr: WARNING: Get literal attribute of err_reason node fail!");
        return VOS_ERR;
    }

    /* ��ȡerr_reason�ڵ��literal����ֵ */
    if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstTmpXmlNodeAttrib, MTA_AGPS_ATTRIB_VALUE_UNDEFINED_ERROR))
    {
        pstPositionErr->enLocErrReason = AGPS_POSITION_ERROR_REASON_UNDEFINED;
    }
    else if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstTmpXmlNodeAttrib, MTA_AGPS_ATTRIB_VALUE_NOT_ENOUGH_GPS_SATELLITES))
    {
        pstPositionErr->enLocErrReason = AGPS_POSITION_ERROR_REASON_NOT_ENOUGH_GPS_SATS;
    }
    else if (VOS_TRUE == XML_COMM_CheckAttributeValue(pstTmpXmlNodeAttrib, MTA_AGPS_ATTRIB_VALUE_GPS_ASSIST_DATA_MISSING))
    {
        pstPositionErr->enLocErrReason = AGPS_POSITION_ERROR_REASON_GPS_ASS_DATA_MISSING;
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_FillPosErr: WARNING: literal attribute of err_reason node is abnormal!");
        return VOS_ERR;
    }

    /* ��ȡGPS_assist_req�ڵ� */
    pstTmpXmlNode = XML_COMM_GetChildNodeByLabel(pstXmlPositionErr, MTA_AGPS_LABEL_GPS_ASSIST_REQ);
    if (VOS_NULL_PTR != pstTmpXmlNode)
    {
        if (VOS_OK == TAF_MTA_AGPS_FillGpsAssistReq(pstTmpXmlNode, &pstPositionErr->stAssistDataReq))
        {
            pstPositionErr->bitOpAssistDataReq = VOS_TRUE;
        }
        else
        {
            /* ����GPS_assist_req�ǿ�ѡ�ڵ㣬���Լ������ʧ�ܣ�Ҳ������VOS_ERR�����Ǽ�����������㣬��־λ����ΪVOS_FALSE */
            MTA_WARNING_LOG("TAF_MTA_AGPS_FillPosErr: WARNING: TAF_MTA_AGPS_FillGpsAssistReq fail!");
        }
    }

    return VOS_OK;
}



#endif /* FEATURE_AGPS */

#ifdef __cplusplus
    #if __cplusplus
       }
    #endif
#endif


