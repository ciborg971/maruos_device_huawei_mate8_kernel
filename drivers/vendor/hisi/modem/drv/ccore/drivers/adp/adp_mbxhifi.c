
#include <mdrv.h>

#ifdef __cplusplus
extern "C"
{
#endif


#ifndef CONFIG_HIFI_MAILBOX   /* ´ò×® */
unsigned int DRV_MAILBOX_READMAILDATA(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned int          *pSize)

{
        return 0;
}

unsigned int DRV_MAILBOX_SENDMAIL(
                unsigned int           MailCode,
                void                   *pData,
                unsigned int           Length)
{
        return 0;
}

unsigned int DRV_MAILBOX_REGISTERRECVFUNC(
                unsigned int           MailCode,
                mb_msg_cb               pFun,
                void                   *UserHandle)
{
        return 0;
}
#endif

#ifdef __cplusplus
}
#endif
