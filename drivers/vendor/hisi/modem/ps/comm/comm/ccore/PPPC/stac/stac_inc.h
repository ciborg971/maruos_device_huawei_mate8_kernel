/************************************************************************
 *                                                                      *
 *                             stac_inc.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/20                                      *
 *  Author:             Shi  Yong                                       *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           STAC�����������õĽӿ�	                    *
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

#ifndef		_STAC_INC_H_
#define		_STAC_INC_H_

#ifdef	__cplusplus
extern "C"{
#endif

/***************************************************************************/

/*ѹ��ʹ�õĺ���*/
VOID             STAC_ExitStacCompress( STAC_COMPRESSINFO_S * );
LONG		     STAC_InitStacCompress(STAC_COMPRESSINFO_S * );
//MBUF_S*           STAC_StacCompress  (MBUF_S * , STAC_COMPRESSINFO_S *,USHORT );
USHORT STAC_CompressPacket( UCHAR *,ULONG,UCHAR ** ,ULONG *,STAC_COMPRESSINFO_S* ,USHORT);

/*��ѹʹ�õĺ���*/
LONG             STAC_InitStacDecompress( STAC_DECOMPRESSINFO_S * );
VOID             STAC_ExitStacDecompress( STAC_DECOMPRESSINFO_S * );
//MBUF_S *         STAC_StacDecompress( MBUF_S *, STAC_DECOMPRESSINFO_S *,USHORT );
USHORT  STAC_DecompressPacket( UCHAR * ,ULONG,UCHAR ** ,ULONG *,STAC_DECOMPRESSINFO_S * , USHORT);



/***************************************************************************/

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif

#endif	/*end of the *.h file*/
