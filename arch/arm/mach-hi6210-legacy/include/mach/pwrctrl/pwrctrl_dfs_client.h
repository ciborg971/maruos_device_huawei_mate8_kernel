

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl_multi_dfs.h>
#include "drv_mailbox_interface.h" // FIXME: arch file call driver function!...

#ifndef __PWRCTRL_DFS_CLIENT_H__
#define __PWRCTRL_DFS_CLIENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifndef DFS_CMD_CLIENT_CPU_ID
    #define DFS_CMD_CLIENT_CPU_ID    MAILBOX_TARGET_CPU_ACPU
#else
    ## ERROR: DFS_CMD_CLIENT_CPU_ID Redefinition!
#endif
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
struct dfs_prof_pli
{
    s32_t asc_threshold;
    s32_t des_threshold;
    u32_t asc_step;
    u32_t des_step;
};

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern int pwrctrl_dfs_cmd_dis(s32_t dev_id);
extern int pwrctrl_dfs_cmd_en(s32_t dev_id);
extern int pwrctrl_dfs_cmd_pflock(s32_t dev_id, u32_t prof_id);
extern int pwrctrl_dfs_cmd_pfunlock(s32_t dev_id);
extern int pwrctrl_dfs_cmd_rdevid(char_t* dev_name, s32_t* dev_id);
extern int pwrctrl_dfs_cmd_rlqos(s32_t qos_id, s32_t req_id);
extern int pwrctrl_dfs_cmd_rpfctn(s32_t dev_id, u32_t prof_id, void* prof_buf, u32_t prof_buf_size);
extern int pwrctrl_dfs_cmd_rpfcur(s32_t dev_id, u32_t* prof_id);
extern int pwrctrl_dfs_cmd_wpfcur(s32_t pol_id, u32_t prof_id);
extern int pwrctrl_dfs_cmd_rpfnum(s32_t dev_id, u32_t* num);
extern int pwrctrl_dfs_cmd_rpfpli(s32_t poli_id, u32_t prof_id, struct dfs_prof_pli* prof_pli);
extern int pwrctrl_dfs_cmd_rpolid(char_t* poli_name, s32_t* poli_id);
extern int pwrctrl_dfs_cmd_rqosid(char_t* qos_name, s32_t* qos_id);
extern int pwrctrl_dfs_cmd_rqqos(s32_t qos_id, u32_t req_value, s32_t* req_id);
extern int pwrctrl_dfs_cmd_rstate(s32_t dev_id, u32_t* state);
extern int pwrctrl_dfs_cmd_wpfpli(s32_t poli_id, u32_t prof_id, struct dfs_prof_pli prof_pli);











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pwrctrl_dfs_client.h */
