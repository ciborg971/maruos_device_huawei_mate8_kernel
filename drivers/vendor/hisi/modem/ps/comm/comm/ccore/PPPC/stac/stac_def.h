/************************************************************************
 *                                                                      *
 *                             stac_def.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/20                                      *
 *  Author:             Shi  Yong                                       *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           STAC���ֵ�˽�к�			                    *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *												                        *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_STAC == VRP_YES )

#ifndef		_STAC_DEF_H_
#define		_STAC_DEF_H_

#ifdef	__cplusplus
extern "C"{
#endif

/***************************************************************************/
/*hash��ֲ��ĺ�*/
#define STAC_NULL_HASH_NODE 0x0FFFF       /*          hash���еĿսڵ�         */
#define STAC_HASH_SIZE 256			          /*          hash�����Ĵ�С           */
#define STAC_HASH_KEY(a)  *(a)
/***************************************************************************/

#define STAC_APPLY_MEMORY_LENGTH  2048
#define STAC_MAXRESERVE_SPACE	  100
#define STAC_MBUF_LEN			  2048
#define STAC_MAX_PACKET_LENGTH	  1820   
#define STAC_MIN_BECOMPRESSED_LENGTH 2       /* ��С��ѹ�����ַ����ĳ��� */    
#define STAC_HISTORY_BUFFSIZE 2048			 /* should not less than 2 */

#define STAC_SENDRSTREQTIMEOUT       2000
/****************************************************************************
* CREATE DATE	: 2000-6-21
* CREATED BY	: SHI YONG
* MACRO  		: STAC_INC_MOD
*Input:
* 	DSTVALUE ȡģ��ķ���ֵ
* 	ORGVALUE ��ȡģ��ֵ
*	MODVALUE ģ�Ĵ�С
* Output
*   DSTVALUE=(ORGVALUE+1)%MODVALUE
****************************************************************************/
#define	STAC_INC_MOD( DSTVALUE,ORGVALUE, MODVALUE)  \
{													\
    (DSTVALUE) = 1 + (ORGVALUE);			    	\
    if ((DSTVALUE)==(MODVALUE))		                \
	{											    \
	    (DSTVALUE)=0;							    \
	}												\
}
/* end of the STAC_INC_MOD define */

/***************************************************************************/

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif

#endif /*end of the *.h file*/
