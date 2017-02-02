/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_apiadp_stru02.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF ����ģ�鶨��Ľṹ(Query �ṹ)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/

#ifndef OSPF_APIADP_STRU02_H
#define OSPF_APIADP_STRU02_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*�����ݽṹ�а���AMB_OSPF_PM_LSDB�е�ȫ��not-accessible��*/
typedef struct tagOSPF_LSDB_KEY
{
    UCHAR ucAreaId[4];
    ULONG ulType;
    UCHAR ucLsId[4];
    UCHAR ucRouterId[4];
    ULONG ulProcessId;
}OSPF_LSDB_KEY_S;

typedef struct tagOSPF_CFG_GRHELPER
{
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    /*Add for BC3D02908*/
    ULONG ulAccNum;
    /*end BC3D02908*/
}OSPF_CFG_GRHELPER_S;

/*Note:�����ݽṹ����MIB�е�ȫ��not-accessiable��*/
typedef struct tagOSPF_SHOWIF_KEY
{
    UCHAR ucIpAddr[4];
    ULONG ulAddr_less_if;
    ULONG ulProcessId;
}OSPF_SHOWIF_KEY_S;

/*�����ݽṹ����AMB_OSPF_PM_NBR�е�����not-accessiable��*/
typedef struct tagOSPF_NBR_KEY
{
    UCHAR ucIpAddr[4];
    ULONG ulAddr_Less_If;
    ULONG ulProcessId;
}OSPF_NBR_KEY_S;

/*�����ݽṹ����ospf routing���key*/
typedef struct tagOSPF_ROUTING_KEY
{
    ULONG ulProcessId;
    UCHAR ucDstIp[4];
    UCHAR ucDstIpMask[4];
    ULONG ulAssiciated_Area_Id;
    UCHAR ucDestType;
    UCHAR ucPadding[3];
}OSPF_ROUTING_KEY_S;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagOSPF_SHOWNETWORK_INFO
{
    USHORT usProcessId;
    /*Added for BC3D03465, 2010/8/5 */
    USHORT   usIsAllVRF;
    /*End Added for BC3D03465, 2010/8/5 */
    ULONG  ulVrfIndex;
}OSPF_SHOWNETWORK_INFO_S;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef struct tagOSPF_NETWORK_KEY
{
    ULONG ulNotFirst;
    ULONG ulProcessId;
    ULONG ulArea;
    ULONG ulNetworkAddr;
    ULONG ulNetworkLen;
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_NETWORK_KEY_S;


/*�����ݽ�ݰ���AMB_OSPF_PM_VIRT_IFȫ����not-accessiable��*/
typedef struct tagOSPF_VIRTUAL_IF_KEY
{
    UCHAR ucAreaId[4];
    UCHAR ucNeighbor[4];
    ULONG ulProcessId;
}OSPF_VIRTUAL_IF_KEY_S;

/*�����ݽṹ����AMB_OSPF_PM_VIRT_LOCAL_LSDB���е�not-accessiable��*/
typedef struct tagOSPF_VIRTUAL_LSDB_KEY
{
    UCHAR uctransit_area_id[4];
    UCHAR ucneighbor[4];
    ULONG ultype;
    UCHAR ucls_id[4];
    UCHAR ucrouter_id[4];
    ULONG ulappl_index;
}OSPF_VIRTUAL_LSDB_KEY_S;

typedef struct tagOSPF_VIRTUAL_NBR_KEY
{
    UCHAR ucarea_id[4];
    UCHAR ucrtr_id[4];
    ULONG ulappl_index;    
}OSPF_VIRTUAL_NBR_KEY_S;

/*�����ݽṹ����ospf entity mib�е�����not-accessiable��*/
typedef struct tagOSPF_ENTITY_KEY
{
    ULONG ulProcessId;             /*OSPFʵ����*/
}OSPF_ENTITY_KEY_S;

/*�����ݽṹ����ospf area mib�е�����not-accessiable��*/
typedef struct tagOSPF_AREA_KEY
{
    UCHAR ucAreaId[4];
    ULONG ulProcessId;    
    ULONG ulGetAreaFlag;
}OSPF_AREA_KEY_S;

/*�����ݽṹ����ospf if metric mib�е�����not-accessiable��*/
typedef struct tagOSPF_IF_METRIC_KEY
{
    UCHAR ucIPAddr[4];             /*address*/
    ULONG ulAddr_Less_If;          /*address less if*/
    ULONG ulTos;                   /*The type of service metric being referenced*/
    ULONG ulProcess_Id;            /*Process Id*/
}OSPF_IF_METRIC_KEY_S;

/*�����ݽṹ����ospf area agg�е�����not-accessible��*/
typedef struct tagOSPF_AREA_AGG_KEY
{
    UCHAR ucAreaId[4];             /*area id*/
    ULONG ulLsdb_Type;             /*Lsdb type*/
    UCHAR ucIpAddr[4];             /*address*/
    UCHAR ucIpMask[4];             /*ip mask*/
    ULONG ulProcessId;             /*process id*/
}OSPF_AREA_AGG_KEY_S;

typedef struct tagOSPF_CFGAREA_LOG
{
    ULONG  ulAreaId;                    /*����ID*/ 
    USHORT bNoFlag;                     /*�������û���ɾ������,1���ã�0ɾ��*/
    USHORT usProcessId;                 /*����id*/
    ULONG  ulAreaStatus;                /*row_status|admin_status|oper_status|ambl_state*/
}OSPF_CFGAREA_LOG_S;


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
