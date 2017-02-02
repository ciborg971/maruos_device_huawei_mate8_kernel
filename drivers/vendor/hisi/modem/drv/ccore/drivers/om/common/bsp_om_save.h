

#ifndef	__BSP_OM_SAVE_H__
#define __BSP_OM_SAVE_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**************************************************************************
  �궨��
**************************************************************************/
#define OM_ROOT_DIR             "/modem_log/"
#define OM_LOG_PATH             "/modem_log/log/"
#define OM_DUMP_PATH            "/modem_log/dump/"
#define OM_RESET_LOG            "/modem_log/dump/reset.log"
#define OM_RESET_LOG_MAX        2048
#define OM_ERROR_LOG_MAX        4096
#define OM_PRINT_LOG_MAX        (4096*24)

#define OM_DUMP_FILE_MAX_NUM        3
#define OM_DUMP_FILE_NAME_LENGTH    50
/**************************************************************************
  STRUCT����
**************************************************************************/

/**************************************************************************
  UNION����
**************************************************************************/

/**************************************************************************
  OTHERS����
**************************************************************************/


/**************************************************************************
  ��������
**************************************************************************/
#ifdef ENABLE_BUILD_OM
int  bsp_om_save_loop_file(char * dirName, char *fileHeader, void * address, u32 length);
int  bsp_om_save_file(char *filename, void * address, u32 length, u32 mode);
int  bsp_om_append_file(char *filename, void * address, u32 length, u32 max_size);
bool bsp_om_fs_check(void);
void bsp_om_record_resetlog(u8 * dump_addr);
void bsp_om_save_resetlog(void);
#else
static inline int  bsp_om_save_loop_file(char * dirName, char *fileHeader, void * address, u32 length){return 0;}
static inline int  bsp_om_save_file(char *filename, void * address, u32 length, u32 mode){return 0;}
static inline int  bsp_om_append_file(char *filename, void * address, u32 length, u32 max_size){return 0;}
static inline bool bsp_om_fs_check(){return 0;}
static inline void bsp_om_record_resetlog(u8 * dump_addr){return ;}
static inline void bsp_om_save_resetlog(){return ;}


#endif
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define __BSP_OM_SAVE_H__ */





