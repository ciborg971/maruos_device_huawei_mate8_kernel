#ifndef _HSO_DRX_INTERFACE_CMD__
#define _HSO_DRX_INTERFACE_CMD__
/*
  ע��:
	ʹ���ַ����ϱ�ʱ:ֻ֧��CHAR_T ���������,��֧��char[] string ������
*/

typedef char                   CHAR_T;
typedef u32                    VOS_UINT32;

//˯��״̬�ṹ
#define MAX_LOCK_LEN 32


//�ӿ�ID
#define DIAG_CMD_DRX_BSP_SLEEP_IND                        	(0x5220)					//�͹��Ŀ�ά�ɲ��ϱ�IND
#define DIAG_CMD_DRX_CHIP_TEMP_IND                        	(0x5221)					//�͹��Ŀ�άоƬ�¶��ϱ�IND
#define DIAG_CMD_DRX_BATTERIES_TEMP_IND                     (0x5222)					//�͹��Ŀ�ά����¶��ϱ�IND



//

typedef struct 
{
    CHAR_T name[MAX_LOCK_LEN]; 
    VOS_UINT32	status;
} LOCK_STATUS;

typedef struct 
{
    LOCK_STATUS lock_lookup[MAX_LOCK_LEN];
} DIAG_CMD_DRX_SLEEP_STRU;

// DIAG_CMD_DRX_CHIP_TEMP_IND �͹��Ŀ�άоƬ�¶��ϱ��ṹ��
typedef struct 
{
    s16 tem;
	s16 reserved;
}DIAG_CMD_DRX_CHIP_TEMP_STRU;

// DIAG_CMD_DRX_BATTERIES_TEMP_IND �͹��Ŀ�ά����¶��ϱ��ṹ��
typedef struct 
{
    s16 tem;
	s16 reserved;
}DIAG_CMD_DRX_BATTERIES_TEMP_STRU;

#endif