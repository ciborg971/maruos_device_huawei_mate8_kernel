#ifndef _PARTITION_H_
#define _PARTITION_H_

struct partition {
	const char *name;
	unsigned size_kb;
};

#if defined(CONFIG_HISI_PARTITION_HI3650)
static struct partition partitions[] = {
	{"-",				512},			/* ptable			512K */
	{"vrl",				256},			/* VRL				256K p1*/
	{"vrl_backup",			256},			/* VRL backup			256K p2*/
	{"fw_lpm3",			256},			/* mcuimage			256K p3*/
	{"frp",				768},			/* reserved0			768K p4*/
	{"fastboot",			4*1024},		/* fastboot			4M   p5*/
	{"modemnvm_factory",		4*1024},		/* modemnvm factory		4M   p6*/
	{"nvme",			6*1024},		/* nvme				6M   p7*/
	{"oeminfo",			64*1024},		/* oeminfo			64M  p8*/
	{"splash",			8*1024},		/* splash			8M   p9*/
	{"modemnvm_backup",  		4*1024},		/* modemnvm backup		4M   p10*/
	{"modemnvm_img",	    	8*1024},		/* modemnvm img 		8M   p11*/
	{"modemnvm_system",		4*1024},		/* modemnvm system 		4M   p12*/
	{"secure_storage",		32*1024},		/* secure storage		32M  p13*/
	{"3rdmodemnvm",			16*1024},		/* 3rdmodemnvm			16M  p14*/
	{"3rdmodemnvmbkp",	    	16*1024},		/* 3rdmodemnvmback		16M  p15*/
	{"persist",                     2*1024},                /* persist                       2M  p16*/
	{"reserved1",			14*1024},		/* reserved1			14M  p17*/
	{"modem_om",			32*1024},		/* modem om			32M  p18*/
	{"splash2",			64*1024},		/* splash2			64M  p19*/
	{"misc",			2*1024},		/* misc             		2M   p20*/
	{"modemnvm_update",		24*1024},		/* modemnvm update		24M  p21*/
	{"recovery2",			64*1024},		/* recovery2			64M  p22*/
	{"reserved2",			64*1024},		/* reserved2			64M  p23*/
	{"teeos",			4*1024},		/* teeos			4M   p24*/
	{"trustfirmware",		2*1024},		/* trustfirmware		2M   p25*/
	{"sensorhub",			16*1024},		/* sensorhub			16M  p26*/
	{"fw_hifi",             	12*1024},   		/* hifi            		12M  p27*/
	{"boot",			32*1024},		/* boot				32M  p28*/
	{"recovery",			64*1024},		/* recovery			64M  p29*/
	{"dts",				64*1024},		/* dtimage			64M  p30*/
	{"modem",			64*1024},		/* modem			64M  p31*/
	{"modem_dsp",			16*1024},		/* modem_dsp			16M  p32*/
	{"modem_dtb",			8*1024},		/* modem_dtb			8M   p33*/
	{"dfx",				16*1024},		/* dfx				16M  p34*/
	{"3rdmodem",			64*1024},		/* 3rdmodem         		64M  p35*/
	{"cache",			256*1024},		/* cache			256M p36*/
	{"hisitest0",			2*1024},		/* hisitest0         		2M   p37*/
	{"hisitest1",			2*1024},		/* hisitest1         		2M   p38*/
	{"system",			2560*1024},		/* system			2560M p40*/
	{"cust",			512*1024},		/* cust				512M  p41*/
	{"hisitest2",			4*1024},		/* hisitest2         		4M   p39*/
	{"userdata",			4096*1024},		/* userdata			4096M p42*/
	{ 0, 0 },						/* total 8204M*/

};
#elif defined CONFIG_HISI_PARTITION_HI6250
static struct partition partitions[] = {
	{"-",				512},			/* ptable			512K */
	{"vrl",				256},			/* VRL				256K p1*/
	{"vrl_backup",			256},			/* VRL backup			256K p2*/
	{"fw_lpm3",			256},			/* mcuimage			256K p3*/
	{"reserved0",			768},			/* reserved0			768K p4*/
	{"fastboot",			4*1024},		/* fastboot			4M   p5*/
	{"modemnvm_factory",		4*1024},		/* modemnvm factory		4M   p6*/
	{"nvme",			6*1024},		/* nvme				6M   p7*/
	{"oeminfo",			64*1024},		/* oeminfo			64M  p8*/
	{"reserved3",			4*1024},		/* reserved			4M   p9*/
	{"modemnvm_backup",  		4*1024},		/* modemnvm backup		4M   p10*/
	{"modemnvm_img",	    	8*1024},		/* modemnvm img 		8M   p11*/
	{"modemnvm_system",		4*1024},		/* modemnvm system 		4M   p12*/
	{"secure_storage",		32*1024},		/* secure storage		32M  p13*/
	{"reserved4",			2*1024},		/* reserved4			2M  p14*/
	{"reserved5",		    	2*1024},		/* reserved5			2M  p15*/
	{"persist",                     2*1024},                /* persist                       2M  p16*/
	{"reserved1",			14*1024},		/* reserved1			14M  p17*/
	{"modem_om",			32*1024},		/* modem om			32M  p18*/
	{"splash2",			64*1024},		/* splash2			64M  p19*/
	{"misc",			2*1024},		/* misc             		2M   p20*/
	{"modemnvm_update",		24*1024},		/* modemnvm update		24M  p21*/
	{"recovery2",			64*1024},		/* recovery2			64M  p22*/
	{"reserved2",			60*1024},		/* reserved2			60M  p23*/
	{"teeos",			4*1024},		/* teeos			4M   p24*/
	{"trustfirmware",		2*1024},		/* trustfirmware		2M   p25*/
	{"sensorhub",			16*1024},		/* sensorhub			16M  p26*/
	{"fw_hifi",             	12*1024},   		/* hifi            		12M  p27*/
	{"boot",			32*1024},		/* boot				32M  p28*/
	{"recovery",			64*1024},		/* recovery			64M  p29*/
	{"dts",				32*1024},		/* dtimage			32M  p30*/
	{"modem",			64*1024},		/* modem			64M  p31*/
	{"modem_dsp",			24*1024},		/* modem_dsp			24M  p32*/
	{"modem_dtb",			8*1024},		/* modem_dtb			8M   p33*/
	{"dfx",				16*1024},		/* dfx				16M  p34*/
	{"reserved6",			8*1024},		/* reserved6         		8M  p35*/
	{"cache",			256*1024},		/* cache			256M p36*/
	{"hisitest0",			2*1024},		/* hisitest0         		2M   p37*/
	{"hisitest1",			2*1024},		/* hisitest1         		2M   p38*/
	{"hisitest2",			4*1024},		/* hisitest2         		4M   p39*/
	{"system",			2560*1024},		/* system			2560M p40*/
	{"cust",			512*1024},		/* cust				512M  p41*/
	{"userdata",			4096*1024},		/* userdata			4096M p42*/
	{ 0, 0 },						/* total 8112M*/

};
#endif

#endif

