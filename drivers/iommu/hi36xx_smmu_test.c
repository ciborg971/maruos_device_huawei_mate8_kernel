/*
 * Copyright (C) 2013-2013 ...
 * ...
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/iommu.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/hisi/ion-iommu.h>
#include <linux/hisi/hisi-iommu.h>

#ifdef IOMMU_DEBUG
#define D(format, arg...) \
	do {\
		printk(KERN_INFO "[iommutest] " format, ##arg);\
	} while(0)
#else
#define D(format, arg...)
#endif

static struct sg_table * table;
struct smmu_tester{
	struct ion_handle *  ion_handle;
	struct ion_client *  ion_client;
	struct iommu_domain* domain;
};

struct iommu_page_info {
	struct page *page;
	unsigned int order;
	struct list_head list;
};

struct test_case{
	int id;
	const char* name;
	int (*test_func)(void);
};


#define __CALL_TEST_FUNC(func)  func
#define __BUILD_TEST_CASE(_id,_name,_func)  { \
	.id = _id, \
	.name = __stringify(_name),	\
	.test_func	= _func,\
}
struct smmu_tester *smmu_tester = NULL;
int smmu_test_result = 0;
static struct iommu_domain_data* info;
/**
 * str1: options
 * str2: option to find
 */
static unsigned int my_getopt(const char *str1, const char *str2)
{
	char *p = NULL;
	unsigned int value = 0;

	p = strstr(str1, str2);
	if (!p)
		return 0;

	for (; *p; p++) {
		if (*p == '=') {
			if ((value = simple_strtol(p + 1, NULL, 16)) == 0)
				value = 0;

			break;
		}
	}

	return value;
}
/*
 *iova:the start io virtual address.
 *size:the size of io virtual memory.
 *this function unmap a section io virtual memory
 */
static int do_unmap(unsigned int iova, unsigned int size)
{
	int ret;
	struct scatterlist* sg;
	unsigned int i=0;
	unsigned int mem_size=0;
	if(!smmu_tester->domain){
		D("domain is null");
		return -EINVAL;
	}
	/* iommu unmap */
	ret = iommu_unmap(smmu_tester->domain,iova,size);
	if (!ret) {
		D("hisi iommu unmap domain failed!\n");
	}
	/*free physical memory*/
	if(table){
		for_each_sg(table->sgl, sg, table->nents, i){
			__free_pages(sg_page(sg),get_order(sg->length));
			mem_size += sg->length;
		}
		D("%s:free total memory 0x%x \n",__func__,mem_size);
		sg_free_table(table);
		kfree(table);
	}
	table = NULL;
	D("test result: %s\n"
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",
			ret ? "pass" : "failed");
	return ret;
}

/* the usage of map operation*/
static ssize_t map_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
        char temp_buf[] = "usage: echo m=? id=?,iova=0x?,phy=0x? size=0x? > map\n";
	return snprintf(buf,sizeof(temp_buf),temp_buf) ;
}
/*this function do iommu map*/
static ssize_t map_store(struct device *pdev,struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned int iova_start = 0;
	unsigned int map_size = 0;
	unsigned int i;
	struct scatterlist* sg=NULL ;
	ktime_t time_start, time_end;
	unsigned long diff;
	int ret = 0;

	/*get parameter from buffer*/
	iova_start = my_getopt(buf, "iova");
	map_size  = my_getopt(buf,  "size");

	D("%s: iova_start: 0x%x, size: 0x%x ",__func__,iova_start, map_size);
	/* DO TEST */
	time_start = ktime_get();
	if( smmu_tester->domain && table ){
		for_each_sg( table->sgl, sg, table->nents, i ){
			ret = iommu_map(smmu_tester->domain,iova_start,page_to_phys(sg_page(sg)),sg->length,IOMMU_READ|IOMMU_WRITE|IOMMU_CACHE);
			if (ret) {
				D(dev, "failed to map devmem: %d\n", ret);
				goto out;
			}
			iova_start += sg->length;
		}
	}
	time_end = ktime_get();
	diff = ktime_to_us(ktime_sub(time_end, time_start));
	D("%s: mapping time is 0x%lx \n",__func__,diff);
	return size;
out:
	return -ENOSPC ;
}

static DEVICE_ATTR(map, (S_IRUGO | S_IWUSR), map_show, map_store);

/* ------------------------------------------------------------------------- */
/*display the usage of unmap*/
static ssize_t unmap_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
        char temp_buf[] = "usage: echo id=?, a=0xXXXX, l=0xXXXX > dump_pgtbl!\n";
	return snprintf(buf,sizeof(temp_buf),temp_buf);
}

/*this function do unmap operation*/
static ssize_t unmap_store(struct device *pdev,struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned int iova_start = 0x10;
	unsigned int map_size = 0;

	iova_start = my_getopt(buf, "iova");
	map_size  = my_getopt(buf,  "size");
	D("%s:iova_start: 0x%x, size: 0x%x ",__func__,iova_start, map_size);
	do_unmap(iova_start,map_size);
	return size;
}
static DEVICE_ATTR(unmap, (S_IRUGO | S_IWUSR), unmap_show, unmap_store);

/* ------------------------------------------------------------------------- */
/*get physical address according to io vritual address*/
static ssize_t iova_to_phy_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	unsigned int iova_addr;
	unsigned int phys_addr;

	iova_addr = my_getopt(buf, "addr");
	phys_addr = iommu_iova_to_phys(smmu_tester->domain,iova_addr);
	D("iova_addr=0x%x and phys_addr=0x%x\n",iova_addr, phys_addr);
	return 0;
}
static DEVICE_ATTR(iova_to_phy, S_IWUSR, NULL, iova_to_phy_store);

/* ------------------------------------------------------------------------- */
/*display the available io virtual memory*/
static ssize_t alloc_memory_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	int ret = 0;
	unsigned int size, available;
        char temp_buf[] = "iova pool info: size: 0x12345678, available: 0x12345678\n";
	size = hisi_iommu_iova_size();
	available = hisi_iommu_iova_available();
	printk(KERN_INFO "iova pool info: size: 0x%x, available: 0x%x\n",
			size, available);


	ret += snprintf(buf,sizeof(temp_buf),"iova pool info: size: 0x%x, available: 0x%x\n",
			size, available);
	return ret;
}
static struct iommu_page_info* create_node(void)
{
	struct iommu_page_info* info = NULL;
	struct page* page = NULL ;
	info = kmalloc(sizeof(struct iommu_page_info), GFP_KERNEL);
	if (!info) {
		D("%s: kmalloc info failed!\n", __func__);
		return NULL;
	}
	page = alloc_pages(GFP_KERNEL,1); /*alloc 8kb each time*/
	if (!page) {
		D("alloc page error \n");
		kfree(info);
		return NULL;
	}
	info->page = page;
	info->order = 0;
	INIT_LIST_HEAD(&info->list);
	return info ;
}
/*
 *this function allocate physical memory,
 *and make them to scatter lista.
 *table is global .
 */
static ssize_t alloc_memory_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	int map_size = 0;
	unsigned int sum = 0;
	struct list_head pages;
	struct iommu_page_info *info,*tmp_info;
	unsigned int i = 0, ret=0;
	struct scatterlist* sg=NULL;

	INIT_LIST_HEAD(&pages);
	map_size  = my_getopt(buf,"size");

	if ( map_size < 0 ) return -EINVAL;
	D("%s: map_size=0x%x \n",__func__, map_size);
	do{
		info = create_node();
		if(!info) goto error;
		list_add_tail(&info->list, &pages);
		sum += (1 << info->order) * PAGE_SIZE;
		i++;
	}while(sum < map_size);

	table = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table){
           goto error;
	}
	ret = sg_alloc_table(table, i, GFP_KERNEL);
	if (ret){
	   kfree(table);
	   goto error;
	}
	sg = table->sgl;
	list_for_each_entry_safe(info, tmp_info, &pages, list) {
		struct page *page = info->page;
		sg_set_page(sg, page, (1 << info->order) * PAGE_SIZE, 0);
		sg = sg_next(sg);
		list_del(&info->list);
		kfree(info);
	}
	D("sg list is ok \n");
	return map_size;
error:
	list_for_each_entry_safe(info, tmp_info, &pages, list) {
		list_del(&info->list);
		kfree(info);
	}
	return 0;

}
static DEVICE_ATTR(alloc_memory, (S_IRUGO|S_IWUSR), alloc_memory_show, alloc_memory_store);

/*
   test mapping address from ion device
 */
static int test_smmu_ion_tile_map(void)
{
	int ret;
	/*total physical memory :0xF0000
	 *physical line :60KB
	 *virtual line :64KB
	 *tile flag: 1
	 *page property:0xff
	 */
	struct iommu_map_format format = {0,0xF0000,0,0,0,60,64,0x01,0xff};

	printk(KERN_ERR"%s start\n",__func__);

	smmu_tester->ion_handle = ion_alloc(smmu_tester->ion_client,0xF0000,0x1000,ION_HEAP(ION_SYSTEM_HEAP_ID),0x0);
	if (IS_ERR(smmu_tester->ion_handle)) {
		pr_err("alloc is fail\n");
		return 0;
	}

	ret = ion_map_iommu(smmu_tester->ion_client,smmu_tester->ion_handle,&format);
	if (ret) {
		pr_err("ion map iommu is failed\n");
		return 0;
	}

	printk(KERN_ERR"%s end\n",__func__);
	return 1;
}

/*
   test unmapping address from ion device
 */
static int test_smmu_ion_tile_unmap(void)
{

	printk(KERN_ERR"%s start\n",__func__);

	ion_unmap_iommu(smmu_tester->ion_client,smmu_tester->ion_handle);

	printk(KERN_ERR"%s end\n",__func__);

	return 0 ;
}

/*
 *map a section space from ion device layer
 */
static int test_smmu_ion_dai_map(void)
{
	int ret;
	struct iommu_map_format format = {0,0x100000,0,0,0,0,0,0x0,0xff};

	printk(KERN_ERR"%s start\n",__func__);

	smmu_tester->ion_handle = ion_alloc(smmu_tester->ion_client,0x100000,0x1000,ION_HEAP(ION_SYSTEM_HEAP_ID),0x0);
	if (IS_ERR(smmu_tester->ion_handle)) {
		pr_err("alloc is fail\n");
		return 0;
	}

	ret = ion_map_iommu(smmu_tester->ion_client,smmu_tester->ion_handle,&format);
	if (ret) {
		pr_err("ion_map_iommu is failed\n");
		return 0;
	}

	return 1;
}

/*
 *unmap a section space from ion device layer
 */
static int test_smmu_ion_dai_unmap(void)
{

	printk(KERN_ERR"%s start\n",__func__);
	ion_unmap_iommu(smmu_tester->ion_client,smmu_tester->ion_handle);
	printk(KERN_ERR"%s end\n",__func__);

	return 1;
}

static struct test_case smmu_test_array[] = {
	__BUILD_TEST_CASE(1,TEST-SMMU-ION-FIX-MAP,test_smmu_ion_tile_map),
	__BUILD_TEST_CASE(2,TEST-SMMU-ION-FIX-UNMAP,test_smmu_ion_tile_unmap),
	__BUILD_TEST_CASE(3,TEST-SMMU-ION-DAI-MAP,test_smmu_ion_dai_map),
	__BUILD_TEST_CASE(4,TEST-SMMU-ION-DAI-UNMAP,test_smmu_ion_dai_unmap),
};

static ssize_t smmu_test_show(struct device *dev,
		struct device_attribute *attr,char *buf)
{
        char temp_buf[] = "0x%x12345678 \n";
	return snprintf(buf, sizeof(temp_buf), "0x%x\n", smmu_test_result);;
}

static ssize_t smmu_test_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int i, ret;
	pr_err("smmu_test test case: %s",buf);

	for (i = 0;i < ARRAY_SIZE(smmu_test_array); i++){
		if (!strncmp(smmu_test_array[i].name,buf,strlen(smmu_test_array[i].name))){
			ret = __CALL_TEST_FUNC(smmu_test_array[i].test_func)();
			smmu_test_result |= ret<<i;
			break;
		}
	}
	if (i == ARRAY_SIZE(smmu_test_array)){
		pr_err("there is no case:%s",buf);
		return -ENODEV;
	}

	pr_err("smmu_test test case: %s",buf);
	return count;
}



/*device attribute for test*/
static struct device_attribute smmu_tester_attrs[] = {
	__ATTR(smmu_tester_case, 0644, smmu_test_show, smmu_test_store),
};



static int create_attr_file(struct device *dev)
{
	int ret = 0;
	ret |= device_create_file(dev, &dev_attr_map);
	ret |= device_create_file(dev, &dev_attr_unmap);
	ret |= device_create_file(dev, &dev_attr_iova_to_phy);
	ret |= device_create_file(dev, &dev_attr_alloc_memory);
	ret |= device_create_file(dev, &smmu_tester_attrs[0]);

	if (ret) {
		D("create attr file error!\n");
	}
	return ret;
}

static int hi36xx_iommutest_probe(struct platform_device *pdev)
{
	unsigned int i=0;
	struct device* dev = &pdev->dev;

	smmu_tester = devm_kzalloc(&pdev->dev, sizeof(struct smmu_tester), GFP_KERNEL);
	if (!smmu_tester){
		pr_err("in %s devm_kzalloc is failed\n",__func__);
		return -ENOMEM;
	}

	smmu_tester->ion_client = hisi_ion_client_create("smmu_test");
	if(IS_ERR(smmu_tester->ion_client)) {
		pr_err("hisi ion client create failed \n");
		return -ENODEV;
	}
	smmu_tester->domain = iommu_domain_alloc(dev->bus);
	if (!smmu_tester->domain) {
		D("create domain fail \n");
		return -ENOMEM;
	}else{
		iommu_attach_device(smmu_tester->domain,dev);
		info = (struct iommu_domain_data*)smmu_tester->domain->priv;
		for(i=0;i<3;i++){
			D("%s,iova_start=0x%lx,iova_size=0x%lx \n", __func__,
					info->iova_start,
					info->iova_size );
		}
	}
	create_attr_file(&pdev->dev);
	return 0;
}


/*the platform device for iommu test*/
struct platform_device iommutest_dev = {
	.name = "hi36xx-iommu-test",
	.id = -1,
	.dev = {
		.platform_data = "fix",
	},
};

/*the platform driver for iommu test*/
struct platform_driver hisi_iommutest_drv = {
	.probe = hi36xx_iommutest_probe,
	.driver = {
		.name = "hi36xx-iommu-test",
	},
};

/*the inital function for iommu test module*/
static int __init init_iommu_test(void)
{
	int err = -EBUSY;
	err = platform_device_register(&iommutest_dev);
	if (err)
		return err;
	err = platform_driver_register(&hisi_iommutest_drv);
	if (err)
		goto out_remove_drivers;

	return 0;
out_remove_drivers:
	platform_device_unregister(&iommutest_dev);
	return err;
}
module_init(init_iommu_test);

