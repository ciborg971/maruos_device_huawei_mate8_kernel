

#ifndef __OAL_HCC_COMM_H
#define __OAL_HCC_COMM_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

//#define CONFIG_HCC_DEBUG
#undef CONFIG_HCC_DEBUG
#undef CONFIG_HCC_TX_MULTI_BUF_CHECK
#define CONFIG_HCC_HEADER_CHECK_SUM

typedef enum _hcc_action_type__
{
    HCC_ACTION_TYPE_WIFI = 0,/*data from wifi*/
    HCC_ACTION_TYPE_OAM = 1, /*data from oam,sdt etc.*/
    HCC_ACTION_TYPE_TEST= 2, /*used for hcc transfer test*/
    HCC_ACTION_TYPE_BUTT
}hcc_action_type;

/* hcc protocol header
|-------hcc total(64B)-----|-----------package mem--------------|
|hcc hdr|pad hdr|hcc extend|pad_payload|--------payload---------|
*/
#pragma pack(push,1)
/*6bytes*/
struct hcc_header
{
#define HCC_SUB_TYPE_BUTT   (16)          /*4 bits bound [0~15]*/
    oal_uint8      sub_type:4;            /* sub type to hcc type,refer to hcc_action_type */
    oal_uint8      main_type:4;           /* main type to hcc type,refer to hcc_action_type*/

    oal_uint8      seq;                 /*seq num for debug*/
	oal_uint8      pad_hdr;             /*pad_hdr only need 6 bits, the 2bits reserved,
	                                   pad_hdr used to algin hcc tcm hdr(64B)*/
    oal_uint16     more   :1;           /*for hcc aggregation*/
    oal_uint16     option :1;           /*reserved*/
    oal_uint16     pad_payload   :2;    /*the pad to algin the payload addr*/
    oal_uint16     pay_len:12;          /*the payload length,
                                        did't contain the extend hcc hdr area*/
}__OAL_DECLARE_PACKED;
#pragma pack(pop)
#define HCC_HDR_TOTAL_LEN   (64)
#define HCC_HDR_LEN         (OAL_SIZEOF(struct hcc_header))
#define HCC_HDR_RESERVED_MAX_LEN    (HCC_HDR_TOTAL_LEN - HCC_HDR_LEN)

typedef enum _hcc_test_case_{
    HCC_TEST_CASE_TX = 0,
    HCC_TEST_CASE_RX = 1,
    HCC_TEST_CASE_LOOP = 2,
    HCC_TEST_CASE_COUNT
}hcc_test_case;

/*less than 16,4bits for sub_type*/
typedef enum _hcc_test_subtype_
{
    HCC_TEST_SUBTYPE_CMD = 0,/*command mode*/
    HCC_TEST_SUBTYPE_DATA = 1,
    HCC_TEST_SUBTYPE_BUTT
}hcc_test_subtype;

#define   HCC_TEST_CMD_START_TX          (0)
#define   HCC_TEST_CMD_START_RX          (1)
#define   HCC_TEST_CMD_START_LOOP        (2)
#define   HCC_TEST_CMD_STOP_TEST         (3)

typedef struct _hcc_test_cmd_stru_
{
    oal_uint16 cmd_type;
    oal_uint16 cmd_len;
}hcc_test_cmd_stru;
#define hcc_get_test_cmd_data(base) (((oal_uint8*)(base)) + OAL_SIZEOF(hcc_test_cmd_stru))

typedef struct _hsdio_trans_test_info_
{
    oal_uint32 actual_tx_pkts;
    oal_uint64 total_h2d_trans_bytes;/*total bytes trans by from host to device*/
    oal_uint64 total_d2h_trans_bytes;/*total bytes trans by from device to host*/
}hsdio_trans_test_info;

typedef struct _hsdio_trans_test_rx_info_
{
    oal_uint32 total_trans_pkts;
    oal_uint32 pkt_len;
    oal_uint8 pkt_value;
}hsdio_trans_test_rx_info;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
