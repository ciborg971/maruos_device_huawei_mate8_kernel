/*
 *
 *
 */
#include <module.h>
#include <linux/debugfs.h>

static struct dentry *g_balong_bus_perf_dir_dentry = NULL;


static int __init balong_bus_perf_init(void)
{
    g_balong_bus_perf_dir_dentry = debugfs_create_dir("balong_bus_perf", NULL);

    //debugfs_test_file_dentry = debugfs_create_file("bus_fops", S_IRWXUGO, g_balong_bus_perf_dir_dentry, NULL, &debugfs_test_file_fops);
}



