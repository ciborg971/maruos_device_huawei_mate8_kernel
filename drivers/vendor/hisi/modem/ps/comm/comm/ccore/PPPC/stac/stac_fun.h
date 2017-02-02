/************************************************************************
 *                                                                      *
 *                             stac_fun.h                               *
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

#ifndef		_STAC_FUN_H_
#define		_STAC_FUN_H_

#ifdef	__cplusplus
extern "C"{
#endif

/***************************************************************************/
ULONG       STAC_OutputRawByte( STAC_COMPRESSINFO_S * );
ULONG	    STAC_OutputToken( STAC_COMPRESSINFO_S *, STAC_HASH_MATCH_S * );
ULONG       STAC_OutputEndMarker( STAC_COMPRESSINFO_S * );
UCHAR	    STAC_ReadBit( STAC_DECOMPRESSINFO_S * );
ULONG	    STAC_WriteBit( STAC_COMPRESSINFO_S *, USHORT  );
ULONG		STAC_StacCompressStream( STAC_COMPRESSINFO_S * );
USHORT		STAC_StacDecompressStream( STAC_DECOMPRESSINFO_S * );	
VOID        STAC_ResetHistorybuffer(STAC_COMPRESSINFO_S *);
/***************************************************************************/
/*hash�ĺ���*/
VOID STAC_HASH_NewList( STAC_HASH_MINLIST_S *  );
VOID STAC_HASH_AddHead( STAC_HASH_MINLIST_S * , struct tagStacHashMinNode *  );
struct tagStacHashTable * STAC_HASH_AllocHashTable( ULONG  );

VOID STAC_HASH_FreeHashTable( struct tagStacHashTable *  );
struct tagStacHashNode * STAC_HASH_GetNextHashNode( struct tagStacHashTable * ,USHORT );

/***************************************************************************/

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif

#endif	/*end of the *.h file*/
