/* hisi_mailbox_debugfs.h */

#ifndef __HISI_MAILBOX_DEBUGFS_H__
#define __HISI_MAILBOX_DEBUGFS_H__

extern void mbox_debugfs_register(struct hisi_mbox_device **list);
extern void mbox_debugfs_unregister(struct hisi_mbox_device **list);

#endif /* __HISI_MAILBOX_DEBUGFS_H__ */
