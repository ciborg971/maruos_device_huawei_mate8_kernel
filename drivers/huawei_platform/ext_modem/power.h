/*
 * power.h
 *
 */
#ifndef EXT_MODEM_POWER_H
#define EXT_MODEM_POWER_H


int is_via_modem_state_ready(void);
void modem_err_indication_usr_form_module(void *rst_buf, char *rst_mod_name, enum cbp_except_modid_e rst_modid);


#endif
