#ifndef _HISILICON_UDP_BOARD_ID_H_
#define _HISILICON_UDP_BOARD_ID_H_

#define	D2_TYPE_LCD	01
#define	JDI_TYPE_LCD	02

/******************************************************************************
Function:	    read_lcd_type
Description:	    ��ȡMMU�۰��Ӧ��LCD����
Input:		    none
Output:		    none
Return:		    01: D2_TYPE_LCD  02: JDI_TYPE_LCD ����: ERROR
******************************************************************************/
extern int read_lcd_type(void);

#endif
