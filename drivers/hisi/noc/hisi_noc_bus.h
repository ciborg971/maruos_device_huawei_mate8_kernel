#ifndef __HISI_NOC_BUS_H
#define __HISI_NOC_BUS_H

#include "hisi_noc.h"

#define CFG_INITFLOW_ARRAY_SIZE		22
#define CFG_TARGETFLOW_ARRAY_SIZE	33
#define VIVO_INITFLOW_ARRAY_SIZE		9
#define VIVO_TARGETFLOW_ARRAY_SIZE	    8
#define VCODEC_INITFLOW_ARRAY_SIZE		3
#define VCODEC_TARGETFLOW_ARRAY_SIZE	    7

#define HI3XXX_MAX_NOC_BUSES_NR	3

/* keep target route id, initiator flow id etc*/
struct noc_bus_info {
	char *name;
	unsigned int initflow_mask;
	unsigned int initflow_shift;

	unsigned int targetflow_mask;
	unsigned int targetflow_shift;

	unsigned int targ_subrange_mask;
	unsigned int seq_id_mask;

	char **initflow_array;
	unsigned int initflow_array_size;

	char **targetflow_array;
	unsigned int targetflow_array_size;
};

struct noc_mid_info
{
	unsigned int idx; //Bus Id: 0
	int init_flow;
	int mid_val;
	char *mid_name;
};

/*used by k3*/

/*
Function: noc_set_bus_info
Description: set noc_bus_info from platform_id
input: unsigned int platform_id -> platform_id input
output: none
return: 0 -> success
*/
int noc_set_buses_info(unsigned int platform_id);

/*
Function: noc_get_mid_info
Description: noc get mid_info
input: none
output: none
return: noc_mid_info pointer
*/
struct noc_mid_info* noc_get_mid_info(void);

/*
Function: noc_get_buses_info
Description: get noc_bus_info
input: none
output: none
return: noc_arr_info pointer
*/
struct noc_arr_info* noc_get_buses_info(void);

/*
Function: noc_get_bus_info
Description: get noc_bus_info from bus_id
input: int bus_id -> bus id input
output: none
return: noc_bus_info
*/
extern const struct noc_bus_info* noc_get_bus_info(int bus_id);

#endif
