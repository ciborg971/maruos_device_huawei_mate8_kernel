/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __RPDCON_IRATQISP_INUSE_cs0087_h
#define __RPDCON_IRATQISP_INUSE_cs0087_h
#include "ed_lib.h"
#include "ed_c_cs0087.h"
#include "ed_user.h"
#include "endec_configs_cs0087.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATQISP_INUSE_Page".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATQISP_INUSE_Page (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_Page* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATQISP_INUSE_Page (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_Page* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATQISP_INUSE_Page".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATQISP_INUSE_Page (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_Page* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATQISP_INUSE_Page (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_Page* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATQISP_INUSE_ConnectionRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_ConnectionRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_ConnectionRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATQISP_INUSE_ConnectionRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_ConnectionRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_ConnectionRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATQISP_INUSE_ConnectionDeny".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_ConnectionDeny* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_ConnectionDeny* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATQISP_INUSE_ConnectionDeny".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_ConnectionDeny* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_ConnectionDeny* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATQISP_INUSE_QuickPage".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATQISP_INUSE_QuickPage (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_QuickPage* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATQISP_INUSE_QuickPage (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_QuickPage* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATQISP_INUSE_QuickPage".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATQISP_INUSE_QuickPage (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_QuickPage* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATQISP_INUSE_QuickPage (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_QuickPage* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATQISP_INUSE_AttributeUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATQISP_INUSE_AttributeUpdateRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATQISP_INUSE_AttributeUpdateAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATQISP_INUSE_AttributeUpdateAccept".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RPDCON_IRATQISP_INUSE_AttributeUpdateReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RPDCON_IRATQISP_INUSE_AttributeUpdateReject".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet));

int Match_c_RPDCON_IRATQISP_INUSE_Page (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATQISP_INUSE_QuickPage (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif

