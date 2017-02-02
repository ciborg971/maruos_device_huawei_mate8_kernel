

/*****************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
*****************************************************************************/




#ifndef __DIAG_PS_TRANS_CMD_ID_H__
#define __DIAG_PS_TRANS_CMD_ID_H__

/*****************************************************************************
 PS Э��ջ ͸��ָ�� BEGIN
*****************************************************************************/


/*****************************************************************************
     NAS ͸��ָ�� BEGIN
*****************************************************************************/

/* DIAG_CMD_MM_SET_HPLMN*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.1 APP_MM_SET_HPLMN_REQ*/
/*                        APP_MM_SET_HPLMN_CNF*/
/* Ӧ��ͨ������ԭ������HPLMN��Э��ջͨ��APP_MM_SET_HPLMN_CNF_STRUԭ��ظ�Ӧ�ý��*/
/*#define DIAG_CMD_MM_SET_HPLMN                        (0x1000)*/

/* DIAG_CMD_MM_SET_UEID*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.2 APP_MM_SET_UEID_REQ_STRU*/
/*                        APP_MM_SET_UEID_CNF_STRU*/
/* Ӧ��ͨ������ԭ������UEID��Э��ջͨ��APP_MM_SET_UEID_CNF_STRUԭ��ظ�Ӧ�ý��*/
#define DIAG_CMD_MM_SET_UEID                         (0x1001)

/* DIAG_CMD_MM_SET_PH_RA_MODE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.3 APP_MM_SET_PH_RA_MODE_REQ_STRU*/
/*                        APP_MM_SET_PH_RA_MODE_CNF_STRU*/
/* ����LTE��������ģʽѡ��FDD��TDD*/
#define DIAG_CMD_MM_SET_PH_RA_MODE                   (0x1002)

/* DIAG_CMD_MM_SET_MS_CLASSMARK*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.4 APP_MM_SET_MS_CLASSMARK_REQ_STRU*/
/*                        APP_MM_SET_MS_CLASSMARK_CNF_STRU*/
/* ����CLASSMARK*/
#define DIAG_CMD_MM_SET_MS_CLASSMARK               (0x1003)

/* DIAG_CMD_MM_SET_UE_NET_CAP*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.5 APP_MM_SET_UE_NET_CAP_REQ_STRU*/
/*                        APP_MM_SET_UE_NET_CAP_CNF_STRU*/
/* ����UE NET CAP*/
#define DIAG_CMD_MM_SET_UE_NET_CAP                  (0x1004)

/* DIAG_CMD_MM_SET_MS_NET_CAP*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.6 APP_MM_SET_MS_NET_CAP_REQ_STRU*/
/*                        APP_MM_SET_MS_NET_CAP_CNF_STRU*/
/* ����MS NET CAP*/
#define DIAG_CMD_MM_SET_MS_NET_CAP                  (0x1005)

/* DIAG_CMD_MM_SET_PLMN*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_SET_PLMN_REQ_STRU*/
/*                  APP_MM_SET_PLMN_CNF_STRU*/

#define DIAG_CMD_MM_SET_PLMN                        (0x1006)

/* DIAG_CMD_MM_SET_LOCK_PLMN*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_SET_LOCK_PLMN_REQ_STRU*/
/*                  APP_MM_SET_LOCK_PLMN_CNF_STRU*/

#define DIAG_CMD_MM_SET_LOCK_PLMN                    (0x1007)

/* DIAG_CMD_MM_SET_LAC*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_SET_LAC_REQ*/
/*                  APP_MM_SET_LAC_CNF*/

/*#define DIAG_CMD_MM_SET_LAC                          (0x1008)*/

/* DIAG_CMD_MM_SET_RAC*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_SET_RAC_REQ*/
/*                  APP_MM_SET_RAC_CNF*/

/*#define DIAG_CMD_MM_SET_RAC                          (0x1009)*/

/* DIAG_CMD_MM_SET_TAC*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_SET_TAC_REQ*/
/*                  APP_MM_SET_TAC_CNF*/

#define DIAG_CMD_MM_SET_TAC                          (0x100a)

/* DIAG_CMD_MM_SET_CELL_ID*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_SET_CELL_ID_REQ*/
/*                  APP_MM_SET_CELL_ID_CNF*/

/*#define DIAG_CMD_MM_SET_CELL_ID                      (0x100b)*/

/* DIAG_CMD_MM_SET_DRX*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_SET_DRX_REQ_STRU*/
/*                  APP_MM_SET_DRX_CNF_STRU*/

#define DIAG_CMD_MM_SET_DRX                          (0x100c)

/* DIAG_CMD_MM_INQ_UEID*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_INQ_UEID_REQ_STRU*/
/*                  APP_MM_INQ_UEID_CNF_STRU*/

#define DIAG_CMD_MM_INQ_UEID                         (0x100d)

/* DIAG_CMD_MM_INQ_PLMN*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_INQ_PLMN_REQ_STRU*/
/*                  APP_MM_INQ_PLMN_CNF_STRU*/

#define DIAG_CMD_MM_INQ_PLMN                         (0x100e)

/* DIAG_CMD_MM_INQ_PH_RA_MODE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_INQ_PH_RA_MODE_REQ_STRU*/
/*                  APP_MM_INQ_PH_RA_MODE_CNF_STRU*/

#define DIAG_CMD_MM_INQ_PH_RA_MODE                   (0x100f)

/* DIAG_CMD_MM_INQ_UE_NET_CAP*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_INQ_UE_NET_CAP_REQ_STRU*/
/*                  APP_MM_INQ_UE_NET_CAP_CNF_STRU*/

#define DIAG_CMD_MM_INQ_UE_NET_CAP                     (0x1010)

/* DIAG_CMD_MM_INQ_RAC*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_INQ_RAC_REQ*/
/*                  APP_MM_INQ_RAC_CNF*/

/*#define DIAG_CMD_MM_INQ_RAC                          (0x1011)*/

/* DIAG_CMD_MM_INQ_TAC*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_INQ_TAC_REQ*/
/*                  APP_MM_INQ_TAC_CNF*/

/*#define DIAG_CMD_MM_INQ_TAC                          (0x1012)*/

/* DIAG_CMD_MM_INQ_CELL_ID*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_INQ_CELL_ID_REQ*/
/*                  APP_MM_INQ_CELL_ID_CNF*/

/*#define DIAG_CMD_MM_INQ_CELL_ID                      (0x1013)*/

/* DIAG_CMD_MM_START*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.8 APP_MM_START_REQ_STRU*/
/*                  2.5.9 APP_MM_START_CNF_STRU*/
/* Ӧ��ͨ������ԭ������Э��ջ��Э��ջͨ��APP_MM_START_CNFԭ��ظ�Ӧ�ÿ��������*/
/* ������Ϣ��������������ע����̣�*/
/* ��APP�Ѿ���Э��ջ�����˸���Ϣ������APP��Э��ջ����APP_MM_STOP_REQ��Ϣ֮ǰ��*/
/* APP��Ӧ���ٴ���Э��ջ���ʹ���Ϣ*/
#define DIAG_CMD_MM_START                            (0x1014)

/* DIAG_CMD_MM_STOP*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.10 APP_MM_STOP_REQ_STRU*/
/*                  2.5.11 APP_MM_STOP_CNF_STRU*/
/* Ӧ��ͨ������ԭ��֪ͨЭ��ջ�ػ���Э��ջͨ��APP_MM_STOP_CNFԭ��ظ�Ӧ�ùػ����*/
#define DIAG_CMD_MM_STOP                             (0x1015)

/* DIAG_CMD_MM_PLMN_SEL*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.12 APP_MM_PLMN_SEL_REQ_STRU*/
/*                  2.5.13 APP_MM_PLMN_SEL_CNF_STRU*/
/* APPͨ������ԭ�֪ͨMM����ָ��PLMN ѡ�񣬲��ڸ�PLMN�Ͻ���ע�ᣨ��27007 COPS˵����*/
#define DIAG_CMD_MM_PLMN_SEL                         (0x1016)

/* DIAG_CMD_MM_PLMN_LIST*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.14 APP_MM_PLMN_LIST_REQ_STRU*/
/*                  2.5.15 APP_MM_PLMN_LIST_CNF_STRU*/
/* Ӧ��ͨ����ԭ���ѯ��ǰ����PLMN ��Ϣ���б�MM�յ���ԭ�����PLMN List����,*/
/* �������ͨ��APP_MM_PLMN_LIST_CNF�ϱ���Ӧ�á�*/
/* ����ϱ���Ҫһ��ʱ�䣬����ʱ��������ϸ��(FFS)��*/
/* ��PLMN List�������̣�Ӧ�ÿ���ͨ��APP_MM_ABORT_PLMN_LIST_REQԭ���ʱ��ֹ����*/
#define DIAG_CMD_MM_PLMN_LIST                        (0x1017)

/* DIAG_CMD_MM_PLMN_LIST_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.5.16 APP_MM_PLMN_LIST_IND_STRU*/
/* Ӧ��ͨ����ԭ���ֹPLMN�������̣�MM�յ���ԭ�ֹͣPLMN ����*/
#define DIAG_CMD_MM_PLMN_LIST_IND                    (0x1018)

/* DIAG_CMD_MM_ABORT_PLMN_SEL*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.17 APP_MM_ABORT_PLMN_SEL_REQ_STRU*/
/*                  2.5.18 APP_MM_ABORT_PLMN_SEL_CNF_STRU*/
/* Ӧ��ͨ����ԭ���ֹPLMN�������̣�MM�յ���ԭ�ֹͣPLMN ����*/
#define DIAG_CMD_MM_ABORT_PLMN_SEL                   (0x1019)

/* DIAG_CMD_MM_PLMN_RESEL*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.19 APP_MM_PLMN_RESEL_REQ_STRU*/
/*                  2.5.20 APP_MM_PLMN_RESEL_CNF_STRU*/
/* Ӧ��ͨ������ԭ�֪ͨMM����������ѡ�����а����Զ�ѡ������ֹ�ѡ��*/
/* Э��ջ�ᰴ�����õ���ѡ��ʽִ��һ��������ѡ��*/
/* MMͨ��APP_MM_PLMN_RESEL_CNF�ظ�Ӧ�����ý��*/
#define DIAG_CMD_MM_PLMN_RESEL                       (0x101a)

/* DIAG_CMD_MM_ATTACH*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.21 APP_MM_ATTACH_REQ_STRU*/
/*                  2.5.22 APP_MM_ATTACH_CNF_STRU*/
/* Ӧ��ͨ������ԭ�֪ͨMM����ATTACH����*/
/* �ϵ��APP����APP_MM_START_REQ֮ǰ������Ϣ��Ч��*/
/* �ǹػ�DETACH��ɺ�APP���ʹ���Ϣ��Э��ջ��������Э��ջע�ᣬ����������������*/
/* ��Э��ջ����ע������У��յ�APP�����Ĵ���Ϣ��Э��ջ��������Ϣ��*/
/* ��Э��ջ�Ѿ�ע��ɹ����յ�APP�����Ĵ���Ϣ��Э��ջֱ�ӷ���ע��ɹ���*/
#define DIAG_CMD_MM_ATTACH                           (0x101b)

/* DIAG_CMD_MM_ATTACH_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.5.23 APP_MM_ATTACH_IND*/
/* ���緢��re-attach��DETACH����UE��DETACH���ٴη���ATTACH����*/
/* ���̽�����MM�ϱ�����ԭ��֪ͨӦ��ATTACH���*/
#define DIAG_CMD_MM_ATTACH_IND                       (0x101c)

/* DIAG_CMD_MM_DETACH*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.24 APP_MM_DETACH_REQ_STRU*/
/*                  2.5.25 APP_MM_DETACH_CNF_STRU*/
/* Ӧ��ͨ������ԭ�֪ͨMM����Detach*/
#define DIAG_CMD_MM_DETACH                           (0x101d)

/* DIAG_CMD_MM_DETACH_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.5.26 APP_MM_DETACH_IND*/
/* ���緢��Detach����UE�յ�������ϱ�����ԭ��֪ͨӦ��*/
#define DIAG_CMD_MM_DETACH_IND                       (0x101e)

/* DIAG_CMD_MM_AREA_LOST_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  APP_MM_AREA_LOST_IND_STRU*/

#define DIAG_CMD_MM_AREA_LOST_IND                    (0x101f)


/* DIAG_CMD_MM_TRANSPARENT_CMD*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.1.8.1 APP_MM_TRANSPARENT_CMD_REQ_STRU*/
/*                  2.1.8.2 APP_MM_TRANSPARENT_CMD_CNF_STRU*/
/* ���͸�MM��Transparent����*/
#define DIAG_CMD_MM_TRANSPARENT_CMD                  (0x1020)

/* DIAG_CMD_MM_TRANSPARENT_CMD_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.1.8.3	OM_MM_TRANSPARENT_CMD_IND*/
/* MM�յ�Transparent����󣬿��ܻ��Զ��ϱ�һЩ���ݣ�*/
/* ��Щ���ݿ���ͨ��OM_PS_TRANSPARENT_CMD_IND_STRU�ϱ�*/
/*#define DIAG_CMD_MM_TRANSPARENT_CMD_IND              (0x1021)*/

/* DIAG_CMD_ESM_SET_PCO*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.27 APP_ESM_SET_PCO_REQ_STRU*/
/*                  2.5.28 APP_ESM_SET_PCO_CNF_STRU*/
/* Ӧ��ͨ������ԭ������ָ�����������ĵ�PCO��Ϣ��*/
/* ���ڴ�����һ�������PDP��������ص��ⲿ����Э�飬*/
/* �Լ��������ⲿ����Э����صĸ�������*/
#define DIAG_CMD_ESM_SET_PCO                         (0x1022)

/* DIAG_CMD_ESM_SET_BEARER_TYPE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.29 APP_ESM_SET_BEARER_TYPE_REQ_STRU*/
/*                  2.5.30 APP_ESM_SET_BEARER_TYPE_CNF_STRU*/
/* Ӧ��ͨ������ԭ�����ó������ͣ�����ר�ó��أ��������������ȱʡ���ص�CID*/
#define DIAG_CMD_ESM_SET_BEARER_TYPE                 (0x1023)

/* DIAG_CMD_ESM_SET_PDN_TYPE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.31 APP_ESM_SET_PDN_TYPE_REQ_STRU*/
/*                  2.5.32 APP_ESM_SET_PDN_TYPE_CNF_STRU*/
/* Ӧ��ͨ������ԭ������UE����PDN���ӵ�IP��ַ�汾��Ϣ*/
#define DIAG_CMD_ESM_SET_PDN_TYPE                    (0x1024)

/* DIAG_CMD_ESM_SET_APN*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.33 APP_ESM_SET_APN_REQ_STRU*/
/*                  2.5.34 APP_ESM_SET_APN_CNF_STRU*/
/* Ӧ��ͨ������ԭ������APN������APN��������ȷ��GPRS�û�ϣ�����ӵ���packet data network*/
/* ��ͨ��ϣ������MS��packet data network�Ľ����*/
#define DIAG_CMD_ESM_SET_APN                         (0x1025)

/* DIAG_CMD_ESM_SET_EPS_QOS_TYPE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.35 APP_ESM_SET_EPS_QOS_TYPE_REQ_STRU*/
/*                  2.5.36 APP_ESM_SET_EPS_QOS_TYPE_CNF*/
/* Ӧ��ͨ������ԭ������EPS_QOS�������ڳ�����Դ����������Ϣ��*/
/* ����������ҵ��������SDF��Qos����*/
/*#define DIAG_CMD_ESM_SET_EPS_QOS_TYPE                (0x1026)*/

/* DIAG_CMD_ESM_SET_TFT*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.37 APP_ESM_SET_TFT_REQ_STRU*/
/*                  2.5.38 APP_ESM_SET_TFT_CNF_STRU*/
/* Ӧ��ͨ������ԭ������ָ�����������ĵ�TFT��Ϣ��*/
/* �����ĳ������������ʹ��TFT ��������ֻ���������TFT ����Ҫ������ݰ���*/
/* ���ó��������ĵ�TFT����ʱ����������TFT �Ĳ������Ҫ��*/
/* Э��涨��Ҫ����������TFT�����ӿ����Ƿ�ֻ���������У���SM������TFT����ȡ����TFT������FFS��*/
#define DIAG_CMD_ESM_SET_TFT                         (0x1027)

/* DIAG_CMD_ESM_SET_EPS_QOS*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.39 APP_ESM_SET_EPS_QOS_REQ_STRU*/
/*                  2.5.40 APP_ESM_SET_EPS_QOS_CNF_STRU*/
/* Ӧ��ͨ������ԭ������ָ�����������ĵ�QoS��Ϣ��*/
/* �÷����������ն˷��������Դ����ʱ�ϱ������磬�������ʵ�������*/
/* ֪ͨ�ն��Ƿ�ʹ�ø÷���������ʵ�ʵķ����������ܱ��޸ġ�*/
/* ʵ�ʵķ����������ڳ��������ļ���ɹ����ϱ��¼��б���Ӧ�ã�*/
/* ʹ�ò�����ѯ���ܲ�ѯ�������ô�ԭ�����õķ������������ܲ���ʵ�ʵķ�������*/
#define DIAG_CMD_ESM_SET_EPS_QOS                     (0x1028)

/* ESM_SET_BEARER_MANAGER_TYPE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.41 APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU*/
/*                  2.5.42 APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU*/
/* Ӧ��ͨ������ԭ������ָ��BEARER_MANAGER_TYPE��Ϣ��*/
/* ��������UE�Գ��ؽ��������Ӧ��ģʽ����Ĭ�ϵ�Ӧ����*/
#define DIAG_CMD_ESM_SET_PDP_MANAGER_TYPE            (0x1029)

/* DIAG_CMD_ESM_QUERY_TFT*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.43 APP_ESM_INQ_TFT_REQ_STRU*/
/*                  2.5.44 APP_ESM_INQ_TFT_CNF_STRU*/
/* Ӧ��ͨ������ԭ���ѯָ�����������ĵ�TFT��Ϣ*/
#define DIAG_CMD_ESM_INQ_TFT                       (0x102a)

/* DIAG_CMD_ESM_QUERY_QOS*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.45 APP_ESM_QUERY_QOS_REQ*/
/*                  2.5.46 APP_ESM_QUERY_QOS_CNF*/
/* Ӧ��ͨ������ԭ���ѯָ�����������ĵ�QoS��Ϣ*/
#define DIAG_CMD_ESM_QUERY_QOS                       (0x102b)

/* DIAG_CMD_ESM_QUERY_PCO*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.47 APP_ESM_QUERY_PCO_REQ*/
/*                  2.5.48 APP_ESM_QUERY_PCO_CNF*/
/* Ӧ��ͨ������ԭ���ѯָ�����������ĵ�PCO��Ϣ*/
#define DIAG_CMD_ESM_INQ_PCO                         (0x102c)

/* DIAG_CMD_ESM_QUERY_BEARER_TYPE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.49 APP_ESM_QUERY_BEARER_TYPE_REQ*/
/*                  2.5.50 APP_ESM_QUERY_BEARER_TYPE_CNF*/
/* Ӧ��ͨ������ԭ���ѯָ�����������ĵĳ������ͣ�*/
/* ��Ϊר�г��أ�Ӧ�����������ȱʡ����CID*/
#define DIAG_CMD_ESM_INQ_BEARER_TYPE                 (0x102d)

/* DIAG_CMD_ESM_QUERY_PDN_TYPE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.51 APP_ESM_QUERY_PDN_TYPE_REQ*/
/*                  2.5.52 APP_ESM_QUERY_PDN_TYPE_CNF*/
/* Ӧ��ͨ������ԭ���ѯָ�����������ĵ�PDN_CONN_TYPE��Ϣ*/
#define DIAG_CMD_ESM_INQ_PDN_TYPE                    (0x102e)

/* DIAG_CMD_ESM_QUERY_EPS_QOS*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.53 APP_ESM_QUERY_EPS_QOS_REQ*/
/*                  2.5.54 APP_ESM_QUERY_EPS_QOS_CNF*/
/* Ӧ��ͨ������ԭ���ѯָ�����������ĵ�EPS QOS��Ϣ*/
#define DIAG_CMD_ESM_INQ_EPS_QOS                     (0x102f)

/* DIAG_CMD_ESM_QUERY_APN*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.55 APP_ESM_QUERY_APN_REQ*/
/*                  2.5.56 APP_ESM_QUERY_APN_CNF*/
/* Ӧ��ͨ������ԭ���ѯָ�����������ĵ�APN����*/
#define DIAG_CMD_ESM_INQ_APN                         (0x1030)

/* DIAG_CMD_ESM_SET_BEARER_MANAGER_TYPE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.57 APP_ESM_QUERY_BEARER_MANAGER_TYPE_REQ*/
/*                  2.5.58 APP_ESM_QUERY_BEARER_MANAGER_TYPE_CNF*/
/* Ӧ��ͨ������ԭ������ն˶Գ��ؼ�����޸Ľ����Զ����˹�Ӧ��*/
#define DIAG_CMD_ESM_INQ_PDP_MANAGER_TYPE            (0x1031)

/* DIAG_CMD_ESM_PDP_SETUP*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.59 APP_ESM_PDP_SETUP_REQ_STRU*/
/*                  2.5.60 APP_ESM_PDP_SETUP_CNF_STRU*/
/* Ӧ��ͨ������ԭ�֪ͨSM���������Դ������*/
/* �����յ�������Դ������Ϣ�󣬷���ר�г��ؼ��������޸�����*/
#define DIAG_CMD_ESM_PDP_SETUP                       (0x1032)

/* DIAG_CMD_ESM_PDP_SETUP_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.5.61 APP_ESM_PDP_SETUP_IND_STRU*/
/* ��������������ؼ������̣�SM������ϱ���Ӧ�á������緢��ĳ��ؼ��������У�*/
/* SM��ռ����ȥ������ص�CID���δ��ʹ�õ�CID�������ϱ���Ϣ�н�CID����Ӧ��*/
#define DIAG_CMD_ESM_PDP_SETUP_IND                   (0x1033)

/* DIAG_CMD_ESM_PDP_MODIFY*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.62 APP_ESM_PDP_MODIFY_REQ_STRU*/
/*                  2.5.63 APP_ESM_PDP_MODIFY_CNF_STRU*/
/* FFS*/
#define DIAG_CMD_ESM_PDP_MODIFY                      (0x1034)

/* DIAG_CMD_ESM_PDP_MODIFY_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.5.64 APP_ESM_PDP_MODIFY_IND_STRU*/
/* ���緢������޸����̣����̽�����SMͨ������ԭ�ｫ���֪ͨAPP*/
#define DIAG_CMD_ESM_PDP_MODIFY_IND                  (0x1035)

/* DIAG_CMD_ESM_PDP_RELEASE*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.5.65 APP_ESM_PDP_RELEASE_REQ_STRU*/
/*                  2.5.66 APP_ESM_PDP_RELEASE_CNF_STRU*/
/* Ӧ��ͨ������ԭ�֪ͨSM�ͷų�����Դ*/
#define DIAG_CMD_ESM_PDP_RELEASE                     (0x1036)

/* DIAG_CMD_ESM_PDP_RELEASE_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.5.67 APP_ESM_PDP_RELEASE_IND_STRU*/
/* �����������������Դ�ͷ����̣����̽�����*/
/* SMͨ������ԭ�֪ͨӦ�ö�ӦCID�ĳ�����Դ���ͷ�*/
#define DIAG_CMD_ESM_PDP_RELEASE_IND                 (0x1037)

/* DIAG_CMD_ESM_PDP_MANAGER_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.5.68 APP_ESM_PDP_MANAGER_IND_STRU*/
/* �ڳ�����Դ�����ֶ�ģʽ�£�SMͨ������ԭ�֪ͨӦ���������ڼ�����޸ĳ�����Դ,*/
/* Ӧ����ظ�APP_ESM_PDP_MANAGER_RSPԭ���֪SM�Ƿ��������*/
#define DIAG_CMD_ESM_PDP_MANAGER_IND                 (0x1038)

/* DIAG_CMD_ESM_PDP_MANAGER_RSP*/
/* RSP*/
/* ���PS�ṩ�ӿ�:  2.5.69 APP_ESM_PDP_MANAGER_RSP_STRU*/
/* ����ԭ���Ƕ�APP_ESM_BEARER_MANAGER_INDԭ�����Ӧ��*/
/* ����Դ�����ֶ�ģʽ�£�Ӧ��ͨ������ԭ�֪ͨSM�Ƿ���ճ�����Դ�ļ�����޸�����*/
/* �����һ��ʱ���ڣ�ʱ��FFS����û���յ�Ӧ�õĻظ���SM��ΪӦ�ò����ճ�����Դ�ķ�����޸�����*/
#define DIAG_CMD_ESM_PDP_MANAGER_RSP                 (0x1039)

/* DIAG_CMD_ESM_TRANSPARENT_CMD*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  2.1.8.4	OM_ESM_TRANSPARENT_CMD_REQ*/
/*                  2.1.8.5	OM_ESM_TRANSPARENT_CMD_CNF*/
/* ���͸�ESM��Transparent����*/
/*#define DIAG_CMD_ESM_TRANSPARENT_CMD                 (0x103a)*/

/* DIAG_CMD_ESM_TRANSPARENT_CMD_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  2.1.8.6 OM_ESM_TRANSPARENT_CMD_IND*/
/* ESM�յ�Transparent����󣬿��ܻ��Զ��ϱ�һЩ���ݣ�*/
/* ��Щ���ݿ���ͨ��OM_PS_TRANSPARENT_CMD_IND_STRU�ϱ�*/
/*#define DIAG_CMD_ESM_TRANSPARENT_CMD_IND             (0x103b)*/

/* DIAG_CMD_ESM_INQ_DYNAMIC_ESP_QOS*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ_STRU*/
/*                  APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU*/
#define DIAG_CMD_ESM_INQ_DYNAMIC_ESP_QOS             (0x103c)

/* DIAG_CMD_ESM_INQ_DYNAMIC_TFT*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_ESM_INQ_DYNAMIC_TFT_REQ_STRU*/
/*                  APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU*/
#define DIAG_CMD_ESM_INQ_DYNAMIC_TFT                 (0x103d)

/* DIAG_CMD_MM_SET_SMC*/
/* REQ/CNF*/
/* ���PS�ṩ�ӿ�:  APP_MM_SET_SMC_REQ_STRU*/
/*                  APP_MM_SET_SMC_CNF_STRU*/
#define DIAG_CMD_MM_SET_SMC                          (0x103e)

/* DIAG_CMD_MM_REG_STAT_IND*/
/* IND*/
/* ���PS�ṩ�ӿ�:  APP_MM_REG_STAT_IND*/

#define DIAG_CMD_MM_REG_STAT_IND                     (0x103f)

#define DIAG_CMD_MM_INQ_MS_CLASSMARK                 (0x1061)

#define DIAG_CMD_MM_INQ_MS_NET_CAP                   (0x1063)
#define DIAG_CMD_MM_INQ_DRX                          (0x1064)

#define DIAG_CMD_MM_INQ_MM_INFO                      (0x1066)
#define DIAG_CMD_MM_INQ_MM_INFO_IND                  (0x1067)
/*****************************************************************************
     NAS ͸��ָ�� END
*****************************************************************************/

/*****************************************************************************
 PS �������Ϣ BEGIN
*****************************************************************************/




#define DIAG_CMD_APP_RRC_TRANSPARENT_CMD      (0x106b)
#define DIAG_CMD_APP_RRC_TRANSPARENT_CMD_IND  (0x106c)
#define DIAG_CMD_RRC_CELL_MEAS_RPT            (0x106d)
#define DIAG_CMD_RRC_CELL_MEAS_RPT_IND        (0x106e)
#define DIAG_CMD_RRC_TIME_DELAY_RPT           (0x106f)
#define DIAG_CMD_RRC_TIME_DELAY_RPT_IND       (0x1070)
#define DIAG_CMD_RRC_INQ_CAMP_CELL_INFO       (0x1071)
#define DIAG_CMD_RRC_INQ_CAMP_CELL_INFO_IND   (0x1072)
#define DIAG_CMD_APP_RRC_LOCK_WORK_INFO       (0x1073)

/*****************************************************************************
 PS �������Ϣ END
*****************************************************************************/

/*****************************************************************************
 L2 �����͸��ָ�����L2���������
 ���ⵥ�ţ�BJ9D01040
 ͬ����ţ�BJ9TB00026
*****************************************************************************/

#define DIAG_CMD_MAC_TRANSPARENT_CMD          (0x1074)
#define DIAG_CMD_MAC_TRANSPARENT_CMD_IND      (0x1075)
#define DIAG_CMD_RLC_TRANSPARENT_CMD          (0x1076)
#define DIAG_CMD_RLC_TRANSPARENT_CMD_IND      (0x1077)
#define DIAG_CMD_PDCP_TRANSPARENT_CMD         (0x1078)
#define DIAG_CMD_PDCP_TRANSPARENT_CMD_IND     (0x1079)
/*#define DIAG_CMD_L2_THROUGHPUT_CMD_REQ        (0x107a)*/
/*#define DIAG_CMD_L2_THROUGHPUT_CMD_IND        (0x107b)*/
/*Added for ������ά�ɲ�*/
#define DIAG_CMD_OM_L2_THROUGHPUT_CMD_REQ     (0x107c)

#define DIAG_CMD_L2_OM_THROUGHPUT_CMD_IND     (0x107d)

#define DIAG_CMD_L2_OM_KEYEVENT_CMD_IND       (0x107e)

#define DIAG_CMD_L2_OM_SDUCOUNT_CMD_REQ       (0x107f)
#define DIAG_CMD_L2_OM_SDUCOUNT_CMD_IND       (0x1080)

#define DIAG_CMD_PS_OM_CAMPEDCELL_CMD_REQ     (0x1081)
#define DIAG_CMD_PS_OM_CAMPEDCELL_CMD_IND     (0x1082)

#define DIAG_CMD_PS_OM_HANDOVER_CMD_REQ       (0x1083)
#define DIAG_CMD_PS_OM_HANDOVER_CMD_IND       (0x1084)

#define DIAG_CMD_PS_OM_PRACH_SR_CMD_REQ       (0x1085)
#define DIAG_CMD_PS_OM_PRACH_SR_CMD_IND       (0x1086)

#define DIAG_CMD_PS_OM_BSR_CMD_REQ            (0x1087)
#define DIAG_CMD_PS_OM_BSR_CMD_IND            (0x1088)

/*LTE L2 ·������*/
#define DIAG_CMD_OM_L2_DT_RA_INFO_CMD_REQ       (0x1089)
#define DIAG_CMD_L2_OM_DT_RA_INFO_CMD_IND       (0x108A)
#define DIAG_CMD_OM_L2_DT_RB_INFO_CMD_REQ       (0x108B)
#define DIAG_CMD_L2_OM_DT_RB_INFO_CMD_IND       (0x108C)
#define DIAG_CMD_OM_L2_DT_HO_LATENCY_CMD_REQ    (0x108D)
#define DIAG_CMD_L2_OM_DT_HO_LATENCY_CMD_IND    (0x108F)

#define DIAG_CMD_RRC_APP_PTL_STATE_QUERY_CNF    (0x1090)
#define DIAG_CMD_OM_L2_DT_CONTENT_TMR_CMD_REQ   (0x1091)
#define DIAG_CMD_L2_OM_DT_CONTENT_TMR_CMD_IND   (0x1092)
#define DIAG_CMD_OM_L2_DT_SR_STATUS_CMD_REQ     (0x1093)
#define DIAG_CMD_L2_OM_DT_SR_STATUS_CMD_IND     (0x1094)

/*LTE RRC·������ */
/* niuxiufan DT begin */
#define DIAG_CMD_APP_RRC_SERVING_CELL_INFO_REQ (0x1095)
#define DIAG_CMD_RRC_APP_SERVING_CELL_INFO_IND (0x1096)

#define DIAG_CMD_APP_RRC_CSEL_INFO_REQ         (0x1097)
#define DIAG_CMD_RRC_APP_LTE_CSEL_INFO_IND     (0x1098)
#define DIAG_CMD_RRC_APP_UTRA_CSEL_INFO_IND    (0x1099)
#define DIAG_CMD_RRC_APP_GERAN_CSEL_INFO_IND   (0x109a)

#define DIAG_CMD_APP_RRC_UE_CAP_INFO_REQ       (0x109b)
#define DIAG_CMD_RRC_APP_UE_CAP_INFO_IND       (0x109c)

#define DIAG_CMD_APP_RRC_AC_BARRING_INFO_REQ   (0x109d)
#define DIAG_CMD_RRC_APP_AC_BARRING_INFO_IND   (0x109e)

#define DIAG_CMD_APP_RRC_UE_DRX_INFO_REQ       (0x109f)
#define DIAG_CMD_RRC_APP_UE_DRX_INFO_IND       (0x10a0)

#define DIAG_CMD_APP_RRC_PTL_STATE_REQ         (0x10a1)
#define DIAG_CMD_RRC_APP_PTL_STATE_IND         (0x10a2)


#define DIAG_CMD_APP_EMM_GUTI_INFO_REQ         (0x10a3)
#define DIAG_CMD_EMM_APP_GUTI_INFO_IND         (0x10a4)

#define DIAG_CMD_APP_EMM_IMSI_INFO_REQ         (0x10a5)
#define DIAG_CMD_EMM_APP_IMSI_INFO_IND         (0x10a6)

#define DIAG_CMD_APP_EMM_EMM_STATE_REQ         (0x10a7)
#define DIAG_CMD_EMM_APP_EMM_STATE_IND         (0x10a8)

#define DIAG_CMD_APP_ESM_PDP_INFO_REQ          (0x10a9)
#define DIAG_CMD_EMM_APP_PDP_INFO_IND          (0x10aa)

#define DIAG_CMD_APP_RRC_LOCK_NET_REQ          (0x10ab)

#define DIAG_CMD_EMM_APP_EMM_INFO_IND           (0x10ac)
#define DIAG_CMD_ESM_APP_ESM_INFO_IND           (0x10ad)
#define DIAG_CMD_EMM_INFO_REPORT                (0x10ae)
#define DIAG_CMD_ESM_INFO_REPORT                (0x10af)


/* niuxiufan DT end */

#define DIAG_CMD_TLPS_PRINT2LAYER_IND           (0x10b0)


#define DIAG_CMD_RRC_APP_END                    (0x109F)


/*TDS BEGIN*/
#define DIAG_CMD_TDS_L2_THROUGHPUT_REQ          (0x1100)
#define DIAG_CMD_TDS_L2_THROUGHPUT_IND          (0x1101)

#define DIAG_CMD_TDS_RRC_BASICINFO_REQ          (0x1102)
#define DIAG_CMD_TDS_RRC_BASICINFO_IND          (0x1103)

#define DIAG_CMD_TDS_MAC_CELL_MEAS_REQ          (0x1104)
#define DIAG_CMD_TDS_MAC_CELL_MEAS_IND          (0x1105)

#define DIAG_CMD_TDS_L2_THROUGHPUT_SG_REQ       (0x1106)
#define DIAG_CMD_TDS_L2_THROUGHPUT_SG_IND       (0x1107)

/*DCM logger*/
#define DIAG_CMD_LTE_DCM_MAC_PDU_INFO_REQ       (0x1108)
#define DIAG_CMD_LTE_DCM_MAC_BSR_INFO_REQ       (0x1109)
#define DIAG_CMD_LTE_DCM_MAC_BSR_INFO_IND       (0x110A)
/*end DCM*/

#define DIAG_CMD_TDS_HSDPA_INFO_IND             (0x110B)
#define DIAG_CMD_TDS_L2_RB_INFO_IND             (0x110C)

/* TDS CMCC Begin */
#define DIAG_CMD_TDS_RRC_MEAS_GSM_REQ           (0x110D)
#define DIAG_CMD_TDS_RRC_MEAS_GSM_IND           (0x110E)

#define DIAG_CMD_TDS_RRC_3A_INFO_REQ            (0x110F)
#define DIAG_CMD_TDS_RRC_3A_INFO_IND            (0x1110)
/* TDS CMCC End */

#define DIAG_CMD_RRC_APP_SERVING_CELL_INFO_CA_IND (0x1202)

#define DIAG_CMD_L2_OM_SWITCH_CONTROL_REQ       (0x1203)

#define DIAG_CMD_RRC_SERV_IDLE_INFO_IND        (0x1204)
#define DIAG_CMD_RRC_INTRA_IDLE_INFO_IND       (0x1205)
#define DIAG_CMD_RRC_INTER_IDLE_INFO_IND       (0x1206)
#define DIAG_CMD_RRC_WCDMA_IDLE_INFO_IND       (0x1207)
#define DIAG_CMD_RRC_TDS_IDLE_INFO_IND         (0x1208)
#define DIAG_CMD_RRC_GERAN_IDLE_INFO_IND       (0x1209)

#define DIAG_CMD_RRC_SERV_MEAS_RSLT_IND   (0x120A)
#define DIAG_CMD_RRC_INTRA_MEAS_RSLT_IND  (0x120B)
#define DIAG_CMD_RRC_INTER_MEAS_RSLT_IND  (0x120C)
#define DIAG_CMD_RRC_SCELL_MEAS_RSLT_IND  (0x120D)
#define DIAG_CMD_RRC_UTRAN_MEAS_RSLT_IND  (0x120E)
#define DIAG_CMD_RRC_GERAN_MEAS_RSLT_IND  (0x120F)

/* begin: add for ·���ں� */
#define DIAG_CMD_LRRC_MEAS_RPT_REQ              (0x1210)
#define DIAG_CMD_LRRC_MEAS_INFO_IND             (0x1211)
#define DIAG_CMD_LRRC_SYNC_RPT_REQ              (0x1212)
#define DIAG_CMD_LRRC_SYNC_INFO_IND             (0x1213)
#define DIAG_CMD_LRRC_OUT_OF_SYNC_INFO_IND      (0x1214)
/* end: add for ·���ں� */

/*****************************************************************************
 L2 �����͸��ָ�����L2��������� END
*****************************************************************************/

/*----------------------------------------------------------------------------*/
/*TL�û�������͸������: 0x2000-0x2FFF, added by hujianbo, 20140108, begin     */
/*----------------------------------------------------------------------------*/

/*TL�û����¼��ϱ�*/
#define DIAG_CMD_L2_OM_UP_EVENT_REQ             (0x2000)
#define DIAG_CMD_L2_OM_UP_EVENT_CNF             (0x2001)

#define DIAG_CMD_L2_OM_SINGLE_UP_EVENT_IND      (0x2002)
#define DIAG_CMD_L2_OM_ALL_UP_EVENT_ACCUL_IND   (0x2003)    /*�ۼ���*/
#define DIAG_CMD_L2_OM_ALL_UP_EVENT_DELTA_IND   (0x2004)    /*����*/

/*TL�û������ͳ�����ϱ�*/
#define DIAG_CMD_TL_STAT_REQ                    (0x2100)
#define DIAG_CMD_TL_STAT_CNF                    (0x2101)

#define DIAG_CMD_CDS_STAT_IND_BASE              (0x2102)
/*More CDS stat ind can added here*/
#define DIAG_CMD_CDS_IPF_PROC_STAT_IND          (0x2103)
#define DIAG_CMD_CDS_UL_IP_PKT_STAT_IND         (0x2104)
#define DIAG_CMD_CDS_DL_SDU_STAT_IND            (0x2105)
#define DIAG_CMD_CDS_LOOP_BACK_STAT_IND         (0x2106)
#define DIAG_CMD_CDS_IMS_PROC_STAT_IND          (0x2107)
/*Added by l00304941 for LTE PDU Report, 2015-03-12, Begin*/
#define DIAG_CMD_CDS_UL_IP_PKT_INFO_IND         (0x2108)
#define DIAG_CMD_CDS_DL_IP_PKT_INFO_IND         (0x2109)
/*Added by l00304941 for LTE PDU Report, 2015-03-12, End*/

#define DIAG_CMD_TDS_PDCP_STAT_SINGLE_RB_IND    (0x2120)
#define DIAG_CMD_TDS_PDCP_STAT_ALL_RB_IND       (0x2121)
/*More TDS PDCP stat ind can added here*/

#define DIAG_CMD_TDS_RLC_STAT_SINGLE_RB_IND     (0x2140)
#define DIAG_CMD_TDS_RLC_STAT_ALL_RB_IND        (0x2141)
/*More TDS RLC stat ind can added here*/

#define DIAG_CMD_TDS_MAC_STAT_IND               (0x2160)
/*More TDS MAC stat ind can added here*/

#define DIAG_CMD_LTE_PDCP_STAT_IND              (0x2180)
/*More LTE PDCP stat ind can added here*/
#define DIAG_CMD_LTE_PDCP_UL_RB_STAT_IND        (0x2181)
#define DIAG_CMD_LTE_PDCP_DL_RB_STAT_IND        (0x2182)
#define DIAG_CMD_LTE_PDCP_ALL_RB_STAT_IND       (0x2183)
/*Added by l00304941 for LTE PDU Report, 2015-03-12, Begin*/
#define DIAG_CMD_LTE_PDCP_UL_PDU_INFO_IND       (0x2184)
#define DIAG_CMD_LTE_PDCP_DL_PDU_INFO_IND       (0x2185)
#define DIAG_CMD_LTE_PDCP_DL_SDU_INFO_IND       (0x2186)
#define DIAG_CMD_LTE_PDCP_UL_PKT_COMPRESS_IND   (0x2187)
#define DIAG_CMD_LTE_PDCP_DL_SDU_DECOMP_IND     (0x2188)
/*Added by l00304941 for LTE PDU Report, 2015-03-12, End*/
#define DIAG_CMD_LTE_PDCP_CIPHER_CH_STAT_IND    (0x2189)

#define DIAG_CMD_LTE_RLC_STAT_IND               (0x21A0)
/*More LTE RLC stat ind can added here*/
#define DIAG_CMD_LTE_RLC_UL_RB_STAT_IND         (0x21A1)
#define DIAG_CMD_LTE_RLC_DL_RB_STAT_IND         (0x21A2)
#define DIAG_CMD_LTE_RLC_UL_ALL_STAT_IND        (0x21A3)
#define DIAG_CMD_LTE_RLC_DL_ALL_STAT_IND        (0x21A4)
/*Added by l00304941 for LTE PDU Report, 2015-03-12, Begin*/
#define DIAG_CMD_LTE_RLC_UL_PDU_INFO_IND        (0x21A5)
#define DIAG_CMD_LTE_RLC_DL_PDU_INFO_IND        (0x21A6)
#define DIAG_CMD_LTE_RLC_AM_CTRL_PDU_INFO_IND   (0x21A7)
/*Added by l00304941 for LTE PDU Report, 2015-03-12, End*/

#define DIAG_CMD_LTE_MAC_STAT_IND_BASE          (0x21C0)
/*More LTE MAC stat ind can added here*/
#define DIAG_CMD_LTE_MAC_RA_STAT_IND            (0x21C1)
#define DIAG_CMD_LTE_MAC_UL_STAT_IND            (0x21C2)
#define DIAG_CMD_LTE_MAC_DL_STAT_IND            (0x21C3)
#define DIAG_CMD_LTE_MAC_CA_STAT_IND            (0x21C4)
#define DIAG_CMD_LTE_MAC_MBMS_STAT_IND          (0x21C5)
/*Added by l00304941 for LTE PDU Report, 2015-03-12, Begin*/
#define DIAG_CMD_LTE_MAC_UL_PDU_INFO_IND        (0x21C6)
#define DIAG_CMD_LTE_MAC_DL_PDU_INFO_IND        (0x21C7)
#define DIAG_CMD_LTE_MAC_REG_BSR_SR_INFO_IND    (0x21C8)
#define DIAG_CMD_LTE_MAC_BUFFER_STATUS_IND      (0x21CA)
/*Added by l00304941 for LTE PDU Report, 2015-03-12, End*/

#define DIAG_CMD_LTE_ROHC_COMP_STAT_IND         (0x21CB)
#define DIAG_CMD_LTE_ROHC_DECOMP_STAT_IND       (0x21CC)

#define DIAG_CMD_LTE_MAC_PHR_TRIGGER_INFO       (0x21CD)
#define DIAG_CMD_LTE_MAC_UL_GRANT_IND           (0x21CE)
#define DIAG_CMD_LTE_MAC_DL_ASSIGN_IND          (0x21CF)


#define DIAG_CMD_TDS_L2_OVERVIEW_STAT_IND       (0x21E0)
#define DIAG_CMD_LTE_L2_OVERVIEW_STAT_IND       (0x2200)
#define DIAG_CMD_LTE_UP_LATENCY_RPT_IND         (0x2201)

/*TL�û��������������ϱ�*/
#define DIAG_CMD_LT_CFG_REQ                     (0x2300)
#define DIAG_CMD_LT_CFG_CNF

#define DIAG_CMD_CDS_CFG_IND
#define DIAG_CMD_TDS_PDCP_CFG_IND
#define DIAG_CMD_TDS_RLC_CFG_IND
#define DIAG_CMD_TDS_MAC_CFG_IND
#define DIAG_CMD_LTE_PDCP_CFG_IND
#define DIAG_CMD_LTE_RLC_CFG_IND
#define DIAG_CMD_LTE_MAC_CFG_IND


/*TL�û������PDUͷ�ϱ�*/
#define DIAG_CMD_LTE_PDCP_HEAD_REQ              (0x2400)
#define DIAG_CMD_LTE_PDCP_HEAD_IND

#define DIAG_CMD_LTE_RLC_HEAD_REQ
#define DIAG_CMD_LTE_RLC_HEAD_IND

#define DIAG_CMD_LTE_MAC_HEAD_REQ
#define DIAG_CMD_LTE_MAC_HEAD_IND

#define DIAG_CMD_TDS_PDCP_HEAD_REQ
#define DIAG_CMD_TDS_PDCP_HEAD_IND

#define DIAG_CMD_TDS_RLC_HEAD_REQ
#define DIAG_CMD_TDS_RLC_HEAD_IND

#define DIAG_CMD_TDS_MAC_HEAD_REQ
#define DIAG_CMD_TDS_MAC_HEAD_IND

/*TL�û���TCP�����ϱ�*/
#define DIAG_CMD_LT_TCP_CAP_REQ                 (0x2500)
#define DIAG_CMD_LT_TCP_IND_REQ

#define DIAG_CMD_LT_L2_END                      (0x2FFF)

#define DIAG_CMD_CA_L2_OM_THROUGHPUT_CMD_IND      (0x1500)

/*----------------------------------------------------------------------------*/
/*TL�û�������͸������: 0x2000-0x2FFF, added by hujianbo, 20140108, end       */
/*----------------------------------------------------------------------------*/



/*****************************************************************************
 PS Э��ջ ͸��ָ��END
*****************************************************************************/



#endif /*__DIAG_PS_TRANS_CMD_ID_H__*/




