/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0063

#include "csn1clib.h"
#include "CSN1DataTypes_cs0063.h"
#include "ed_c_known_ie_cs0063.h"
#include "ed_tlv.h"
#include "UserDefinedDataTypes_cs0063.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


#ifdef CURPOS
#undef CURPOS
#endif
#define CURPOS (Context->CurrOfs)

#ifdef BUFFER
#undef BUFFER
#endif
#define BUFFER ((unsigned char*)(Context->Buffer))

#ifdef CSN1_BACKTRACK
#undef CSN1_BACKTRACK
#endif
#define CSN1_BACKTRACK CSN1C_Backtrack(Context)

#ifdef PUSH_TAG
#undef PUSH_TAG
#endif
#define PUSH_TAG(Tag,Value) CSN1C_PushValue (Context, Tag, Value)

#ifdef EXISTS_TAG
#undef EXISTS_TAG
#endif
#define EXISTS_TAG(Tag) CSN1C_ExistsValue (Context, Tag)

#ifdef POP_TAGS
#undef POP_TAGS
#endif
#define POP_TAGS(Tag) CSN1C_PopValues (Context, Tag)

#ifdef TAG
#undef TAG
#endif
#define TAG(Tag) CSN1C_GetValue (Context, Tag)

#ifdef TAGZ
#undef TAGZ
#endif
#define TAGZ(Tag) CSN1C_GetValueOrZero (Context, Tag)

#ifdef SET_TAG
#undef SET_TAG
#endif
#define SET_TAG(Tag,Value) CSN1C_SetValue (Context, Tag, Value)


/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents* Source = (const c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 200: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 201: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'AttributeLength' */
			case 202: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AttributeLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AttributeRecord' */
			case 203: {
				FieldCallbackParam->Length = ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), (&(Source->data01.data[(Field)->Parent->Index]->AttributeRecord)), pCSN1CContextSet);
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents* Source = (const c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 206: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 207: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'AttributeLength' */
			case 208: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AttributeLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AttributeRecord' */
			case 209: {
				FieldCallbackParam->Length = ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), (&(Source->data01.data[(Field)->Parent->Index]->AttributeRecord)), pCSN1CContextSet);
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RSP_INUSE_RouteSelect_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RSP_INUSE_RouteSelect_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RSP_INUSE_RouteSelect_contents* Source = (const c_EMFPKA_RSP_INUSE_RouteSelect_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 212: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'Route' */
			case 213: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 214: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 7);
				FieldCallbackParam->Length = 7;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RSP_INUSE_RouteSelectAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RSP_INUSE_RouteSelectAck_contents* Source = (const c_EMFPKA_RSP_INUSE_RouteSelectAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 215: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RSP_INUSE_ActivateRoute_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RSP_INUSE_ActivateRoute_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RSP_INUSE_ActivateRoute_contents* Source = (const c_EMFPKA_RSP_INUSE_ActivateRoute_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 216: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'Route' */
			case 217: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 218: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 7);
				FieldCallbackParam->Length = 7;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RSP_INUSE_ActivateRouteAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents* Source = (const c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 219: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetTxIndication_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ResetTxIndication_contents* Source = (const c_EMFPKA_RLP_INUSE_ResetTxIndication_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 220: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 221: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 222: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetRxIndication_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ResetRxIndication_contents* Source = (const c_EMFPKA_RLP_INUSE_ResetRxIndication_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 223: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 224: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 225: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents* Source = (const c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 226: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 227: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 228: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetTxComplete_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ResetTxComplete_contents* Source = (const c_EMFPKA_RLP_INUSE_ResetTxComplete_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 229: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 230: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 231: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetRxComplete_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ResetRxComplete_contents* Source = (const c_EMFPKA_RLP_INUSE_ResetRxComplete_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 232: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 233: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 234: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_Nak_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_Nak_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_Nak_contents* Source = (const c_EMFPKA_RLP_INUSE_Nak_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 235: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 236: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved1' */
			case 237: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved1), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			/* Field 'SequenceLength' */
			case 238: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->SequenceLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReportCount' */
			case 239: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReportCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 240: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'FirstErasedDataUnit' */
			case 241: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->FirstErasedDataUnit.value, 0, Source->data01.data[(Field)->Parent->Index]->FirstErasedDataUnit.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->FirstErasedDataUnit.usedBits;
				break;
			}
			/* Field 'WindowLen' */
			case 242: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->WindowLen.value, 0, Source->data01.data[(Field)->Parent->Index]->WindowLen.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->WindowLen.usedBits;
				break;
			}
			/* Field 'VR' */
			case 243: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->VR.value, 0, Source->data01.data[(Field)->Parent->Index]->VR.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->VR.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ReservationOnRequest_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents* Source = (const c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 247: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 248: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 249: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'Link' */
			case 250: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->Link != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'ReservationLabel' */
			case 251: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'EmergencyIndication' */
			case 252: {
				/* The field 'EmergencyIndication' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication (&((*(Source->data01.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->EmergencyIndication != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'ReservationQueuingReq' */
			case 253: {
				/* The field 'ReservationQueuingReq' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq (&((*(Source->data01.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationQueuingReq != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ReservationOffRequest_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents* Source = (const c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 258: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 259: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 260: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'Link' */
			case 261: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->Link != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'ReservationLabel' */
			case 262: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ReservationAccept_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ReservationAccept_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ReservationAccept_contents* Source = (const c_EMFPKA_RLP_INUSE_ReservationAccept_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 265: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_ReservationReject_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ReservationReject_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_ReservationReject_contents* Source = (const c_EMFPKA_RLP_INUSE_ReservationReject_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 266: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 267: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 268: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'AllowableLink' */
			case 269: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AllowableLink != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'AllowableReservationLabel' */
			case 270: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AllowableReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 271: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'RejectCode' */
			case 272: {
				/* The field 'RejectCode' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode (&((*(Source->data01.data[Field->Parent->Parent->Index]->data02.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->RejectCode), 4);
				FieldCallbackParam->Length = 4;
				break;
			}
			/* Field 'PendingDuration' */
			case 273: {
				/* The field 'PendingDuration' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration (&((*(Source->data01.data[Field->Parent->Parent->Index]->data02.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->PendingDuration), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_RevReservationOn_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_RevReservationOn_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_RevReservationOn_contents* Source = (const c_EMFPKA_RLP_INUSE_RevReservationOn_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 279: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 280: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 281: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 282: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_RevReservationOff_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_RevReservationOff_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_RevReservationOff_contents* Source = (const c_EMFPKA_RLP_INUSE_RevReservationOff_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 284: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 285: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 286: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 287: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_FwdReservationOff_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_FwdReservationOff_contents* Source = (const c_EMFPKA_RLP_INUSE_FwdReservationOff_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 289: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 290: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 291: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 292: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_FwdReservationOn_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_FwdReservationOn_contents* Source = (const c_EMFPKA_RLP_INUSE_FwdReservationOn_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 294: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 295: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 296: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 297: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_FwdReservationAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_FwdReservationAck_contents* Source = (const c_EMFPKA_RLP_INUSE_FwdReservationAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 299: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents* Source = (const c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 300: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 301: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'AttributeLength' */
			case 302: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AttributeLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AttributeRecord' */
			case 303: {
				FieldCallbackParam->Length = ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), (&(Source->data01.data[(Field)->Parent->Index]->AttributeRecord)), pCSN1CContextSet);
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents* Source = (const c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 306: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents* Source = (const c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 307: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_DOSP_INUSE_DataOverSignaling_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents* Source = (const c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 308: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 309: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'AckRequired' */
			case 310: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->AckRequired != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reset' */
			case 311: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reset != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 312: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			/* Field 'MessageSequence' */
			case 313: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->MessageSequence), 6);
				FieldCallbackParam->Length = 6;
				break;
			}
			/* Field 'HigherLayerPacket' */
			case 314: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->HigherLayerPacket.value, 0, Source->HigherLayerPacket.usedBits);
				FieldCallbackParam->Length = Source->HigherLayerPacket.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents* Source = (const c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'Route' */
			case 315: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'AckSequence' */
			case 316: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->AckSequence), 6);
				FieldCallbackParam->Length = 6;
				break;
			}
			/* Field 'Reserved' */
			case 317: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_LUP_INUSE_LocationNotification_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_LocationNotification_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_LUP_INUSE_LocationNotification_contents* Source = (const c_EMFPKA_LUP_INUSE_LocationNotification_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LocationType' */
			case 318: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LocationType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationLength' */
			case 319: {
				/* The field 'LocationLength' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationLength (&((*Source)))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LocationLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationValue' */
			case 320: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->LocationValue.value, 0, Source->LocationValue.usedBits);
				FieldCallbackParam->Length = Source->LocationValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_LUP_INUSE_LocationAssignment_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_LocationAssignment_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_LUP_INUSE_LocationAssignment_contents* Source = (const c_EMFPKA_LUP_INUSE_LocationAssignment_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 321: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationType' */
			case 322: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LocationType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationLength' */
			case 323: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LocationLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationValue' */
			case 324: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->LocationValue.value, 0, Source->LocationValue.usedBits);
				FieldCallbackParam->Length = Source->LocationValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_LUP_INUSE_LocationComplete_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_LocationComplete_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_LUP_INUSE_LocationComplete_contents* Source = (const c_EMFPKA_LUP_INUSE_LocationComplete_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 325: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents* Source = (const c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'StorageBLOBType' */
			case 326: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->StorageBLOBType), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'StorageBLOBLength' */
			case 327: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->StorageBLOBLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'StorageBLOB' */
			case 328: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->StorageBLOB.value, 0, Source->StorageBLOB.usedBits);
				FieldCallbackParam->Length = Source->StorageBLOB.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents* Source = (const c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 329: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'StorageBLOBType' */
			case 330: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->StorageBLOBType), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'StorageBLOBLength' */
			case 331: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->StorageBLOBLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'StorageBLOB' */
			case 332: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->StorageBLOB.value, 0, Source->StorageBLOB.usedBits);
				FieldCallbackParam->Length = Source->StorageBLOB.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents* Source = (const c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 333: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_FCP_INUSE_DataReady_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_FCP_INUSE_DataReady_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_FCP_INUSE_DataReady_contents* Source = (const c_EMFPKA_FCP_INUSE_DataReady_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 334: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_FCP_INUSE_DataReadyAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_FCP_INUSE_DataReadyAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_FCP_INUSE_DataReadyAck_contents* Source = (const c_EMFPKA_FCP_INUSE_DataReadyAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 335: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents* Source = (const c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 336: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents* Source = (const c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 337: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents* Source = (const c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 338: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 339: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'AttributeLength' */
			case 340: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AttributeLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AttributeRecord' */
			case 341: {
				FieldCallbackParam->Length = ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), (&(Source->data01.data[(Field)->Parent->Index]->AttributeRecord)), pCSN1CContextSet);
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents* Source = (const c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 344: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 345: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'AttributeLength' */
			case 346: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AttributeLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AttributeRecord' */
			case 347: {
				FieldCallbackParam->Length = ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), (&(Source->data01.data[(Field)->Parent->Index]->AttributeRecord)), pCSN1CContextSet);
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_RSP_INUSE_RouteSelect_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_RSP_INUSE_RouteSelect_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_RSP_INUSE_RouteSelect_contents* Source = (const c_MLMFPA_RSP_INUSE_RouteSelect_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 350: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'Route' */
			case 351: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 352: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 7);
				FieldCallbackParam->Length = 7;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_RSP_INUSE_RouteSelectAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_RSP_INUSE_RouteSelectAck_contents* Source = (const c_MLMFPA_RSP_INUSE_RouteSelectAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 353: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_RSP_INUSE_ActivateRoute_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_RSP_INUSE_ActivateRoute_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_RSP_INUSE_ActivateRoute_contents* Source = (const c_MLMFPA_RSP_INUSE_ActivateRoute_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 354: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'Route' */
			case 355: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 356: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 7);
				FieldCallbackParam->Length = 7;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_RSP_INUSE_ActivateRouteAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents* Source = (const c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 357: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetTxIndication_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ResetTxIndication_contents* Source = (const c_MLMFPA_SRP_INUSE_ResetTxIndication_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 358: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 359: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 360: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetRxIndication_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ResetRxIndication_contents* Source = (const c_MLMFPA_SRP_INUSE_ResetRxIndication_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 361: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 362: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 363: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents* Source = (const c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 364: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 365: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 366: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetTxComplete_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ResetTxComplete_contents* Source = (const c_MLMFPA_SRP_INUSE_ResetTxComplete_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 367: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 368: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 369: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetRxComplete_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ResetRxComplete_contents* Source = (const c_MLMFPA_SRP_INUSE_ResetRxComplete_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 370: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 371: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 372: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_MultiLinkNak_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_MultiLinkNak_contents* Source = (const c_MLMFPA_SRP_INUSE_MultiLinkNak_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 373: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 374: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved1' */
			case 375: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved1), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			/* Field 'SARSequenceLength' */
			case 376: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->SARSequenceLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReportCount' */
			case 377: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReportCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 378: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'DelayedNak' */
			case 382: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->DelayedNak != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'LeadingEdgeIncluded' */
			case 383: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->LeadingEdgeIncluded != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'LeadingEdge' */
			case 384: {
				/* The field 'LeadingEdge' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge (&((*(Source->data01.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), (*(Source->data01.data[(Field)->Parent->Index]->LeadingEdge)).value, 0, (*(Source->data01.data[(Field)->Parent->Index]->LeadingEdge)).usedBits);
				FieldCallbackParam->Length = (*(Source->data01.data[(Field)->Parent->Index]->LeadingEdge)).usedBits;
				break;
			}
			/* Field 'TrailingEdge' */
			case 385: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->TrailingEdge.value, 0, Source->data01.data[(Field)->Parent->Index]->TrailingEdge.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->TrailingEdge.usedBits;
				break;
			}
			/* Field 'OtherQNCount' */
			case 379: {
				/* The field 'OtherQNCount' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_OtherQNCount (&((*Source)))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->OtherQNCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 380: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*Source).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'LargestSAR' */
			case 386: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data02.data[(Field)->Parent->Index]->LargestSAR.value, 0, Source->data02.data[(Field)->Parent->Index]->LargestSAR.usedBits);
				FieldCallbackParam->Length = Source->data02.data[(Field)->Parent->Index]->LargestSAR.usedBits;
				break;
			}
			/* Field 'VR' */
			case 381: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->VR.value, 0, Source->VR.usedBits);
				FieldCallbackParam->Length = Source->VR.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ReservationOnRequest_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents* Source = (const c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 392: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 393: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 394: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'Link' */
			case 395: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->Link != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'ReservationLabel' */
			case 396: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'EmergencyIndication' */
			case 397: {
				/* The field 'EmergencyIndication' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication (&((*(Source->data01.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->EmergencyIndication != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'ReservationQueuingReq' */
			case 398: {
				/* The field 'ReservationQueuingReq' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq (&((*(Source->data01.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationQueuingReq != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ReservationOffRequest_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents* Source = (const c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 403: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 404: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 405: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'Link' */
			case 406: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->Link != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'ReservationLabel' */
			case 407: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ReservationAccept_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ReservationAccept_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ReservationAccept_contents* Source = (const c_MLMFPA_SRP_INUSE_ReservationAccept_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 410: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_ReservationReject_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ReservationReject_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_ReservationReject_contents* Source = (const c_MLMFPA_SRP_INUSE_ReservationReject_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 411: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 412: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 413: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'AllowableLink' */
			case 414: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AllowableLink != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'AllowableReservationLabel' */
			case 415: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AllowableReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 416: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'RejectCode' */
			case 417: {
				/* The field 'RejectCode' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode (&((*(Source->data01.data[Field->Parent->Parent->Index]->data02.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->RejectCode), 4);
				FieldCallbackParam->Length = 4;
				break;
			}
			/* Field 'PendingDuration' */
			case 418: {
				/* The field 'PendingDuration' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration (&((*(Source->data01.data[Field->Parent->Parent->Index]->data02.data[Field->Parent->Index]))))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->PendingDuration), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_RevReservationOn_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_RevReservationOn_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_RevReservationOn_contents* Source = (const c_MLMFPA_SRP_INUSE_RevReservationOn_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 424: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 425: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 426: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 427: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_RevReservationOff_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_RevReservationOff_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_RevReservationOff_contents* Source = (const c_MLMFPA_SRP_INUSE_RevReservationOff_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 429: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 430: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 431: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 432: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_FwdReservationOff_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_FwdReservationOff_contents* Source = (const c_MLMFPA_SRP_INUSE_FwdReservationOff_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 434: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 435: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 436: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 437: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_FwdReservationOn_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_FwdReservationOn_contents* Source = (const c_MLMFPA_SRP_INUSE_FwdReservationOn_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 439: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 440: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 441: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 442: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_FwdReservationAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_FwdReservationAck_contents* Source = (const c_MLMFPA_SRP_INUSE_FwdReservationAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 444: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents* Source = (const c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 445: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 446: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'AttributeLength' */
			case 447: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AttributeLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AttributeRecord' */
			case 448: {
				FieldCallbackParam->Length = ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), (&(Source->data01.data[(Field)->Parent->Index]->AttributeRecord)), pCSN1CContextSet);
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents* Source = (const c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 451: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents* Source = (const c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 452: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_Flush_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_Flush_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_Flush_contents* Source = (const c_MLMFPA_SRP_INUSE_Flush_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 453: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 454: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'SARSequenceLength' */
			case 455: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->SARSequenceLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LastSARSequence' */
			case 456: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->LastSARSequence.value, 0, Source->LastSARSequence.usedBits);
				FieldCallbackParam->Length = Source->LastSARSequence.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_SRP_INUSE_Nak_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_Nak_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_SRP_INUSE_Nak_contents* Source = (const c_MLMFPA_SRP_INUSE_Nak_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 457: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 458: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved1' */
			case 459: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved1), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			/* Field 'SARSequenceLength' */
			case 460: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->SARSequenceLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReportCount' */
			case 461: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ReportCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 462: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'FirstErasedDataUnit' */
			case 463: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->FirstErasedDataUnit.value, 0, Source->data01.data[(Field)->Parent->Index]->FirstErasedDataUnit.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->FirstErasedDataUnit.usedBits;
				break;
			}
			/* Field 'WindowLen' */
			case 464: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->WindowLen.value, 0, Source->data01.data[(Field)->Parent->Index]->WindowLen.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->WindowLen.usedBits;
				break;
			}
			/* Field 'VR' */
			case 465: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->VR.value, 0, Source->data01.data[(Field)->Parent->Index]->VR.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->VR.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_DOSP_INUSE_DataOverSignaling_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents* Source = (const c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LinkFlowNumber' */
			case 469: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LinkFlowNumber), 5);
				FieldCallbackParam->Length = 5;
				break;
			}
			/* Field 'Route' */
			case 470: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'AckRequired' */
			case 471: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->AckRequired != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reset' */
			case 472: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reset != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'Reserved' */
			case 473: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved), 2);
				FieldCallbackParam->Length = 2;
				break;
			}
			/* Field 'MessageSequence' */
			case 474: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->MessageSequence), 6);
				FieldCallbackParam->Length = 6;
				break;
			}
			/* Field 'HigherLayerPacket' */
			case 475: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->HigherLayerPacket.value, 0, Source->HigherLayerPacket.usedBits);
				FieldCallbackParam->Length = Source->HigherLayerPacket.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents* Source = (const c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'Route' */
			case 476: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Route != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			/* Field 'AckSequence' */
			case 477: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->AckSequence), 6);
				FieldCallbackParam->Length = 6;
				break;
			}
			/* Field 'Reserved' */
			case 478: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->Reserved != 0 ? 1 : 0), 1);FieldCallbackParam->Length = 1;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_LUP_INUSE_LocationNotification_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_LocationNotification_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_LUP_INUSE_LocationNotification_contents* Source = (const c_MLMFPA_LUP_INUSE_LocationNotification_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'LocationType' */
			case 479: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LocationType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationLength' */
			case 480: {
				/* The field 'LocationLength' is optional. If missing, generate nothing. */
				if (!GETPRESENT_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationLength (&((*Source)))) return CSN1C_CB_BACKTRACK;
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LocationLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationValue' */
			case 481: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->LocationValue.value, 0, Source->LocationValue.usedBits);
				FieldCallbackParam->Length = Source->LocationValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_LUP_INUSE_LocationAssignment_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_LocationAssignment_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_LUP_INUSE_LocationAssignment_contents* Source = (const c_MLMFPA_LUP_INUSE_LocationAssignment_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 482: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationType' */
			case 483: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LocationType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationLength' */
			case 484: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->LocationLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'LocationValue' */
			case 485: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->LocationValue.value, 0, Source->LocationValue.usedBits);
				FieldCallbackParam->Length = Source->LocationValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_LUP_INUSE_LocationComplete_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_LocationComplete_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_LUP_INUSE_LocationComplete_contents* Source = (const c_MLMFPA_LUP_INUSE_LocationComplete_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 486: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents* Source = (const c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'StorageBLOBType' */
			case 487: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->StorageBLOBType), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'StorageBLOBLength' */
			case 488: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->StorageBLOBLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'StorageBLOB' */
			case 489: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->StorageBLOB.value, 0, Source->StorageBLOB.usedBits);
				FieldCallbackParam->Length = Source->StorageBLOB.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents* Source = (const c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 490: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'StorageBLOBType' */
			case 491: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->StorageBLOBType), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'StorageBLOBLength' */
			case 492: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->StorageBLOBLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'StorageBLOB' */
			case 493: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->StorageBLOB.value, 0, Source->StorageBLOB.usedBits);
				FieldCallbackParam->Length = Source->StorageBLOB.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents* Source = (const c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 494: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_FCP_INUSE_DataReady_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_FCP_INUSE_DataReady_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_FCP_INUSE_DataReady_contents* Source = (const c_MLMFPA_FCP_INUSE_DataReady_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 495: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_FCP_INUSE_DataReadyAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_FCP_INUSE_DataReadyAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_FCP_INUSE_DataReadyAck_contents* Source = (const c_MLMFPA_FCP_INUSE_DataReadyAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 496: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents* Source = (const c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 497: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents* Source = (const c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'TransactionID' */
			case 498: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->TransactionID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'ValueID' */
			case 499: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'QoSProfileCount' */
			case 500: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->QoSProfileCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 501: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ProfileType' */
			case 502: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 503: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileValue' */
			case 504: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'ValueID' */
			case 508: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'QoSProfileCount' */
			case 509: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->QoSProfileCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 510: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ProfileType' */
			case 511: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 512: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileValue' */
			case 513: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 517: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 518: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumLinkFlowsFwd' */
			case 519: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumLinkFlowsFwd), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumLinkFlowsRev' */
			case 520: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumLinkFlowsRev), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxActivatedLinkFlowsFwd' */
			case 521: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxActivatedLinkFlowsFwd), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxActivatedLinkFlowsRev' */
			case 522: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxActivatedLinkFlowsRev), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 528: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 529: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumReservationsFwd' */
			case 530: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumReservationsFwd), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumReservationsRev' */
			case 531: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumReservationsRev), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumOpenReservationsFwd' */
			case 532: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumOpenReservationsFwd), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumOpenReservationsRev' */
			case 533: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumOpenReservationsRev), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 539: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 540: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AbortTimer' */
			case 541: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AbortTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'FlushTimer' */
			case 542: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->FlushTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 546: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 547: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AbortTimer' */
			case 548: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AbortTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'FlushTimer' */
			case 549: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->FlushTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 553: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 554: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 555: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 556: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 557: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 562: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 563: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 564: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 565: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 566: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 571: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 572: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileType' */
			case 573: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 574: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'ProfileValue' */
			case 575: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 580: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 581: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileType' */
			case 582: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 583: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'ProfileValue' */
			case 584: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 589: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 590: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileType' */
			case 591: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 592: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'ProfileValue' */
			case 593: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 598: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 599: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileType' */
			case 600: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 601: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'ProfileValue' */
			case 602: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 607: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 608: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolID' */
			case 609: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParametersLength' */
			case 610: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolParametersLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParameters' */
			case 611: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.value, 0, Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 616: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 617: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolID' */
			case 618: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParametersLength' */
			case 619: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolParametersLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParameters' */
			case 620: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.value, 0, Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 625: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 626: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolID' */
			case 627: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParametersLength' */
			case 628: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolParametersLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParameters' */
			case 629: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.value, 0, Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 634: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 635: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolID' */
			case 636: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParametersLength' */
			case 637: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolParametersLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParameters' */
			case 638: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.value, 0, Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'ValueID' */
			case 643: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolSupported' */
			case 644: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ProtocolSupported), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SupportedProtocolParametersValuesLength' */
			case 645: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->SupportedProtocolParametersValuesLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SupportedProtocolParametersValues' */
			case 646: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->SupportedProtocolParametersValues.value, 0, Source->SupportedProtocolParametersValues.usedBits);
				FieldCallbackParam->Length = Source->SupportedProtocolParametersValues.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'ValueID' */
			case 647: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolSupported' */
			case 648: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ProtocolSupported), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SupportedProtocolParametersValuesLength' */
			case 649: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->SupportedProtocolParametersValuesLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SupportedProtocolParametersValues' */
			case 650: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->SupportedProtocolParametersValues.value, 0, Source->SupportedProtocolParametersValues.usedBits);
				FieldCallbackParam->Length = Source->SupportedProtocolParametersValues.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 651: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 652: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'BCMCSFlowCount' */
			case 653: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->BCMCSFlowCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 654: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'BCMCSFlowID' */
			case 655: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->BCMCSFlowID), 32);
				FieldCallbackParam->Length = 32;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* Source = (const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 660: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 661: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProgramCount' */
			case 662: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProgramCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 663: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ProgramIDLSBLength' */
			case 664: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->ProgramIDLSBLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProgramIDLSBs' */
			case 665: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->ProgramIDLSBs), 32);
				FieldCallbackParam->Length = 32;
				break;
			}
			/* Field 'FlowDiscriminatorCount' */
			case 666: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->FlowDiscriminatorCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data03' */
			case 667: {
				/* The field 'data03' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Parent->Index]->data02.data[Field->Parent->Index])).data03.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'FlowDiscriminator' */
			case 668: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Parent->Index]->data02.data[(Field)->Parent->Parent->Index]->data03.data[(Field)->Parent->Index]->FlowDiscriminator), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'ValueID' */
			case 677: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'QoSProfileCount' */
			case 678: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->QoSProfileCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 679: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ProfileType' */
			case 680: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 681: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileValue' */
			case 682: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'ValueID' */
			case 686: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'QoSProfileCount' */
			case 687: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->QoSProfileCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data01' */
			case 688: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ProfileType' */
			case 689: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 690: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileValue' */
			case 691: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 695: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 696: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumLinkFlowsFwd' */
			case 697: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumLinkFlowsFwd), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumLinkFlowsRev' */
			case 698: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumLinkFlowsRev), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxActivatedLinkFlowsFwd' */
			case 699: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxActivatedLinkFlowsFwd), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxActivatedLinkFlowsRev' */
			case 700: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxActivatedLinkFlowsRev), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 706: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 707: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumReservationsFwd' */
			case 708: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumReservationsFwd), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumReservationsRev' */
			case 709: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumReservationsRev), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumOpenReservationsFwd' */
			case 710: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumOpenReservationsFwd), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'MaxNumOpenReservationsRev' */
			case 711: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->MaxNumOpenReservationsRev), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 717: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 718: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SARSequenceLength' */
			case 719: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->SARSequenceLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SARSequenceLengthShort' */
			case 720: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->SARSequenceLengthShort), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 724: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 725: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AbortTimer' */
			case 726: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AbortTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'FlushTimer' */
			case 727: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->FlushTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'NakDelayTimer' */
			case 728: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->NakDelayTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 733: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 734: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'AbortTimer' */
			case 735: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->AbortTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'FlushTimer' */
			case 736: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->FlushTimer), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 740: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 741: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 742: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 743: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 744: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 749: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 750: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ReservationCount' */
			case 751: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ReservationCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 752: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ReservationLabel' */
			case 753: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->ReservationLabel), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 758: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 759: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileType' */
			case 760: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 761: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'ProfileValue' */
			case 762: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 767: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 768: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileType' */
			case 769: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 770: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'ProfileValue' */
			case 771: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 776: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 777: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileType' */
			case 778: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 779: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'ProfileValue' */
			case 780: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 785: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 786: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileType' */
			case 787: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileType), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProfileLength' */
			case 788: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProfileLength), 16);
				FieldCallbackParam->Length = 16;
				break;
			}
			/* Field 'ProfileValue' */
			case 789: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProfileValue.value, 0, Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProfileValue.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 794: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 795: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolID' */
			case 796: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParametersLength' */
			case 797: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolParametersLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParameters' */
			case 798: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.value, 0, Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 803: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 804: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolID' */
			case 805: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParametersLength' */
			case 806: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolParametersLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParameters' */
			case 807: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.value, 0, Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 812: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 813: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolID' */
			case 814: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParametersLength' */
			case 815: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolParametersLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParameters' */
			case 816: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.value, 0, Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 821: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 822: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolID' */
			case 823: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParametersLength' */
			case 824: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProtocolParametersLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolParameters' */
			case 825: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.value, 0, Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits);
				FieldCallbackParam->Length = Source->data01.data[(Field)->Parent->Index]->ProtocolParameters.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'ValueID' */
			case 830: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolSupported' */
			case 831: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ProtocolSupported), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SupportedProtocolParametersValuesLength' */
			case 832: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->SupportedProtocolParametersValuesLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'ValueID' */
			case 833: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProtocolSupported' */
			case 834: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->ProtocolSupported), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SupportedProtocolParametersValuesLength' */
			case 835: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->SupportedProtocolParametersValuesLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'SupportedProtocolParametersValues' */
			case 836: {
				EDCopyBits (FieldCallbackParam->Context->Buffer, (int)(FieldCallbackParam->Context->CurrOfs), Source->SupportedProtocolParametersValues.value, 0, Source->SupportedProtocolParametersValues.usedBits);
				FieldCallbackParam->Length = Source->SupportedProtocolParametersValues.usedBits;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 837: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 838: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'BCMCSFlowCount' */
			case 839: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->BCMCSFlowCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 840: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'BCMCSFlowID' */
			case 841: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->BCMCSFlowID), 32);
				FieldCallbackParam->Length = 32;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
/*----------------------------------------------------------------------------
	Callback function used to encode Encodix ADTs
----------------------------------------------------------------------------*/
int XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL)
{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	
	int Ret = CSN1C_CB_OK;
	
	const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* Source = (const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation*)(FieldCallbackParam->Context->Data);
	const TCSN1CFieldElement* Field;
	ED_EXTRAPARAMS_CODE
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Field);
	
	/* No fields detected? There is nothing we can do! */
	if (FieldCallbackParam->Context->FieldState.FieldsTop <= 0) {
		ED_ASSERT_FORCE_FAIL
		return CSN1C_CB_FAIL;
	}
	
	Field = &(FieldCallbackParam->Context->Fields[FieldCallbackParam->Context->FieldState.FieldsTop-1]);
	
	if (Field->Index >= 0) {
		switch (Field->FieldId) {
			/* Field 'data01' */
			case 846: {
				/* The field 'data01' is optional. If missing, generate nothing. */
				if ((*Source).data01.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ValueID' */
			case 847: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ValueID), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProgramCount' */
			case 848: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Index]->ProgramCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data02' */
			case 849: {
				/* The field 'data02' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Index])).data02.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'ProgramIDLSBLength' */
			case 850: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->ProgramIDLSBLength), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'ProgramIDLSBs' */
			case 851: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->ProgramIDLSBs), 32);
				FieldCallbackParam->Length = 32;
				break;
			}
			/* Field 'FlowDiscriminatorCount' */
			case 852: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Index]->data02.data[(Field)->Parent->Index]->FlowDiscriminatorCount), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			/* Field 'data03' */
			case 853: {
				/* The field 'data03' is optional. If missing, generate nothing. */
				if ((*(Source->data01.data[Field->Parent->Parent->Index]->data02.data[Field->Parent->Index])).data03.items <= Field->Index) return CSN1C_CB_BACKTRACK;
				break;
			}
			/* Field 'FlowDiscriminator' */
			case 854: {
				EDIntToBits (FieldCallbackParam->Context->Buffer, ((int)(FieldCallbackParam->Context->CurrOfs)), (int)(Source->data01.data[(Field)->Parent->Parent->Parent->Index]->data02.data[(Field)->Parent->Parent->Index]->data03.data[(Field)->Parent->Index]->FlowDiscriminator), 8);
				FieldCallbackParam->Length = 8;
				break;
			}
			default:;
		}
	}
	return Ret;
#else
ED_ASSERT_FORCE_FAIL
return ED_SYNTAX_ERROR;
#endif
}
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2711, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 1;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2711, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 1;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 200 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 201: {
				if (SETITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 202 /* AttributeLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 203 /* AttributeRecord */: {
					(void)DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeRecord)), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos, pCSN1CContextSet);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2750, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 3;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2750, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 3;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 206 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 207: {
				if (SETITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 208 /* AttributeLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 209 /* AttributeRecord */: {
					(void)DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeRecord)), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos, pCSN1CContextSet);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RSP_INUSE_RouteSelect_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_RouteSelect_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RSP_INUSE_RouteSelect_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 332, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 5;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RSP_INUSE_RouteSelect_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RSP_INUSE_RouteSelect_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_RouteSelect_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RSP_INUSE_RouteSelect_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 332, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 5;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 212 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 213 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 214 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 7);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_RouteSelectAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RSP_INUSE_RouteSelectAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 345, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 6;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_RouteSelectAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RSP_INUSE_RouteSelectAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 345, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 6;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 215 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RSP_INUSE_ActivateRoute_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_ActivateRoute_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RSP_INUSE_ActivateRoute_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 350, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 7;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RSP_INUSE_ActivateRoute_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RSP_INUSE_ActivateRoute_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_ActivateRoute_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RSP_INUSE_ActivateRoute_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 350, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 7;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 216 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 217 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 218 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 7);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RSP_INUSE_ActivateRouteAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 363, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 8;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RSP_INUSE_ActivateRouteAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 363, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 8;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 219 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxIndication_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetTxIndication_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 368, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 9;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxIndication_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ResetTxIndication_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 368, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 9;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 220 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 221 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 222 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetRxIndication_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetRxIndication_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 381, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 10;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetRxIndication_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ResetRxIndication_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 381, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 10;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 223 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 224 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 225 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 394, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 11;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 394, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 11;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 226 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 227 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 228 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetTxComplete_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetTxComplete_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 407, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 12;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetTxComplete_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ResetTxComplete_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 407, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 12;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 229 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 230 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 231 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ResetRxComplete_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ResetRxComplete_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 420, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 13;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ResetRxComplete_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ResetRxComplete_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 420, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 13;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 232 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 233 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 234 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_Nak_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_Nak_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_Nak_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2789, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 14;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_Nak_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_Nak_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_Nak_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_Nak_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2789, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 14;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 235 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 236 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 237 /* Reserved1 */: {
					Destin->Reserved1 = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}
			case 238 /* SequenceLength */: {
					Destin->SequenceLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 239 /* ReportCount */: {
					Destin->ReportCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 240: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_Nak_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 241 /* FirstErasedDataUnit */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FirstErasedDataUnit), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FirstErasedDataUnit.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FirstErasedDataUnit.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}
			case 242 /* WindowLen */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_WindowLen (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->WindowLen), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->WindowLen.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->WindowLen.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}
			case 243 /* VR */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_VR (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->VR), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->VR.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->VR.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ReservationOnRequest_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2882, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 16;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ReservationOnRequest_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2882, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 16;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 247 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 248 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 249: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 250 /* Link */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->Link = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 251 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 252 /* EmergencyIndication */: {
					SETPRESENT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->EmergencyIndication = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 253 /* ReservationQueuingReq */: {
					SETPRESENT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationQueuingReq = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ReservationOffRequest_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2949, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 18;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ReservationOffRequest_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2949, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 18;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 258 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 259 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 260: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 261 /* Link */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->Link = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 262 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ReservationAccept_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationAccept_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ReservationAccept_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 433, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 20;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ReservationAccept_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ReservationAccept_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationAccept_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ReservationAccept_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 433, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 20;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 265 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_ReservationReject_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_ReservationReject_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_ReservationReject_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3400, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 21;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_ReservationReject_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_ReservationReject_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_ReservationReject_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_ReservationReject_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3400, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 21;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 266 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 267 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 268: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 269 /* AllowableLink */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AllowableLink = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 270 /* AllowableReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AllowableReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 271: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 272 /* RejectCode */: {
					SETPRESENT_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->RejectCode = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 4);
					break;
				}
			case 273 /* PendingDuration */: {
					SETPRESENT_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->PendingDuration = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_RevReservationOn_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_RevReservationOn_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_RevReservationOn_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1971, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 24;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_RevReservationOn_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_RevReservationOn_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_RevReservationOn_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_RevReservationOn_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1971, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 24;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 279 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 280 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 281: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 282 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_RevReservationOff_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_RevReservationOff_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_RevReservationOff_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2001, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 26;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_RevReservationOff_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_RevReservationOff_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_RevReservationOff_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_RevReservationOff_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2001, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 26;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 284 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 285 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 286: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 287 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationOff_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_FwdReservationOff_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2031, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 28;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationOff_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_FwdReservationOff_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2031, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 28;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 289 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 290 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 291: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 292 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationOn_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_FwdReservationOn_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2061, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 30;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationOn_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_FwdReservationOn_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2061, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 30;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 294 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 295 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 296: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 297 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_FwdReservationAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_FwdReservationAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 438, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 32;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_FwdReservationAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_FwdReservationAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 438, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 32;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 299 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2992, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 33;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2992, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 33;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 300 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 301: {
				if (SETITEMS_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 302 /* AttributeLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 303 /* AttributeRecord */: {
					(void)DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeRecord)), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos, pCSN1CContextSet);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 443, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 35;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 443, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 35;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 306 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 448, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 36;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 448, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 36;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 307 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_DOSP_INUSE_DataOverSignaling_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 453, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 37;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_DOSP_INUSE_DataOverSignaling_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 453, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 37;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 308 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 309 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 310 /* AckRequired */: {
					Destin->AckRequired = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 311 /* Reset */: {
					Destin->Reset = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 312 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}
			case 313 /* MessageSequence */: {
					Destin->MessageSequence = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 6);
					break;
				}
			case 314 /* HigherLayerPacket */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket (&(Destin->HigherLayerPacket), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->HigherLayerPacket.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->HigherLayerPacket.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 491, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 38;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 491, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 38;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 315 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 316 /* AckSequence */: {
					Destin->AckSequence = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 6);
					break;
				}
			case 317 /* Reserved */: {
					Destin->Reserved = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_LUP_INUSE_LocationNotification_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_LUP_INUSE_LocationNotification_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_LocationNotification_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 504, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 39;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_LUP_INUSE_LocationNotification_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_LUP_INUSE_LocationNotification_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_LUP_INUSE_LocationNotification_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_LUP_INUSE_LocationNotification_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 504, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 39;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 318 /* LocationType */: {
					Destin->LocationType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 319 /* LocationLength */: {
					SETPRESENT_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationLength (&((*Destin)), ED_TRUE);
					Destin->LocationLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 320 /* LocationValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue (&(Destin->LocationValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->LocationValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->LocationValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_LUP_INUSE_LocationAssignment_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_LUP_INUSE_LocationAssignment_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_LocationAssignment_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 539, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 40;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_LUP_INUSE_LocationAssignment_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_LUP_INUSE_LocationAssignment_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_LUP_INUSE_LocationAssignment_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_LUP_INUSE_LocationAssignment_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 539, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 40;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 321 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 322 /* LocationType */: {
					Destin->LocationType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 323 /* LocationLength */: {
					Destin->LocationLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 324 /* LocationValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue (&(Destin->LocationValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->LocationValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->LocationValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_LUP_INUSE_LocationComplete_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_LUP_INUSE_LocationComplete_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_LocationComplete_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 570, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 41;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_LUP_INUSE_LocationComplete_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_LUP_INUSE_LocationComplete_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_LUP_INUSE_LocationComplete_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_LUP_INUSE_LocationComplete_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 570, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 41;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 325 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 575, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 42;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 575, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 42;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 326 /* StorageBLOBType */: {
					Destin->StorageBLOBType = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 327 /* StorageBLOBLength */: {
					Destin->StorageBLOBLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 328 /* StorageBLOB */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB (&(Destin->StorageBLOB), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->StorageBLOB.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->StorageBLOB.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 602, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 43;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 602, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 43;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 329 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 330 /* StorageBLOBType */: {
					Destin->StorageBLOBType = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 331 /* StorageBLOBLength */: {
					Destin->StorageBLOBLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 332 /* StorageBLOB */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB (&(Destin->StorageBLOB), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->StorageBLOB.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->StorageBLOB.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 633, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 44;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 633, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 44;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 333 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_FCP_INUSE_DataReady_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_FCP_INUSE_DataReady_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_FCP_INUSE_DataReady_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 638, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 45;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_FCP_INUSE_DataReady_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_FCP_INUSE_DataReady_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_FCP_INUSE_DataReady_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_FCP_INUSE_DataReady_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 638, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 45;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 334 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_FCP_INUSE_DataReadyAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_FCP_INUSE_DataReadyAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_FCP_INUSE_DataReadyAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 643, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 46;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_FCP_INUSE_DataReadyAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_FCP_INUSE_DataReadyAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_FCP_INUSE_DataReadyAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_FCP_INUSE_DataReadyAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 643, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 46;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 335 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 648, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 47;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 648, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 47;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 336 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 653, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 48;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 653, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 48;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 337 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3031, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 49;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3031, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 49;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 338 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 339: {
				if (SETITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 340 /* AttributeLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 341 /* AttributeRecord */: {
					(void)DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeRecord)), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos, pCSN1CContextSet);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3070, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 51;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3070, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 51;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 344 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 345: {
				if (SETITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 346 /* AttributeLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 347 /* AttributeRecord */: {
					(void)DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeRecord)), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos, pCSN1CContextSet);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_RSP_INUSE_RouteSelect_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_RSP_INUSE_RouteSelect_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_RSP_INUSE_RouteSelect_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 658, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 53;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_RSP_INUSE_RouteSelect_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_RSP_INUSE_RouteSelect_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_RSP_INUSE_RouteSelect_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_RSP_INUSE_RouteSelect_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 658, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 53;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 350 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 351 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 352 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 7);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_RSP_INUSE_RouteSelectAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_RSP_INUSE_RouteSelectAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 671, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 54;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_RSP_INUSE_RouteSelectAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_RSP_INUSE_RouteSelectAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 671, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 54;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 353 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_RSP_INUSE_ActivateRoute_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_RSP_INUSE_ActivateRoute_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_RSP_INUSE_ActivateRoute_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 676, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 55;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_RSP_INUSE_ActivateRoute_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_RSP_INUSE_ActivateRoute_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_RSP_INUSE_ActivateRoute_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_RSP_INUSE_ActivateRoute_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 676, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 55;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 354 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 355 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 356 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 7);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_RSP_INUSE_ActivateRouteAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 689, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 56;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_RSP_INUSE_ActivateRouteAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 689, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 56;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 357 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ResetTxIndication_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetTxIndication_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 694, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 57;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ResetTxIndication_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ResetTxIndication_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 694, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 57;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 358 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 359 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 360 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ResetRxIndication_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetRxIndication_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 707, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 58;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ResetRxIndication_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ResetRxIndication_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 707, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 58;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 361 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 362 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 363 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 720, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 59;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 720, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 59;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 364 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 365 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 366 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ResetTxComplete_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetTxComplete_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 733, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 60;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ResetTxComplete_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ResetTxComplete_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 733, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 60;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 367 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 368 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 369 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ResetRxComplete_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ResetRxComplete_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 746, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 61;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ResetRxComplete_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ResetRxComplete_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 746, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 61;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 370 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 371 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 372 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_MultiLinkNak_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_MultiLinkNak_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2091, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 62;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_MultiLinkNak_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_MultiLinkNak_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2091, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 62;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 373 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 374 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 375 /* Reserved1 */: {
					Destin->Reserved1 = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}
			case 376 /* SARSequenceLength */: {
					Destin->SARSequenceLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 377 /* ReportCount */: {
					Destin->ReportCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 378: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 382 /* DelayedNak */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->DelayedNak = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 383 /* LeadingEdgeIncluded */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->LeadingEdgeIncluded = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 384 /* LeadingEdge */: {
					SETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->LeadingEdge, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->LeadingEdge->value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->LeadingEdge->usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}
			case 385 /* TrailingEdge */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_TrailingEdge (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->TrailingEdge), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->TrailingEdge.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->TrailingEdge.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}
			case 379 /* OtherQNCount */: {
					SETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_OtherQNCount (&((*Destin)), ED_TRUE);
					Destin->OtherQNCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 380: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 (&((*Destin).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 386 /* LargestSAR */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data_LargestSAR (&(Destin->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->LargestSAR), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->LargestSAR.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->LargestSAR.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}
			case 381 /* VR */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR (&(Destin->VR), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->VR.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->VR.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ReservationOnRequest_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3109, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 65;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ReservationOnRequest_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3109, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 65;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 392 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 393 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 394: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 395 /* Link */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->Link = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 396 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 397 /* EmergencyIndication */: {
					SETPRESENT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->EmergencyIndication = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 398 /* ReservationQueuingReq */: {
					SETPRESENT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationQueuingReq = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ReservationOffRequest_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3176, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 67;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ReservationOffRequest_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3176, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 67;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 403 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 404 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 405: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 406 /* Link */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->Link = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 407 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ReservationAccept_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ReservationAccept_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ReservationAccept_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 759, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 69;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ReservationAccept_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ReservationAccept_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ReservationAccept_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ReservationAccept_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 759, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 69;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 410 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_ReservationReject_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_ReservationReject_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_ReservationReject_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3483, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 70;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_ReservationReject_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_ReservationReject_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_ReservationReject_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_ReservationReject_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3483, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 70;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 411 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 412 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 413: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 414 /* AllowableLink */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AllowableLink = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 415 /* AllowableReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AllowableReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 416: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 417 /* RejectCode */: {
					SETPRESENT_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->RejectCode = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 4);
					break;
				}
			case 418 /* PendingDuration */: {
					SETPRESENT_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]))), ED_TRUE);
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->PendingDuration = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_RevReservationOn_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_RevReservationOn_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_RevReservationOn_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2246, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 73;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_RevReservationOn_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_RevReservationOn_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_RevReservationOn_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_RevReservationOn_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2246, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 73;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 424 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 425 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 426: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 427 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_RevReservationOff_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_RevReservationOff_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_RevReservationOff_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2276, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 75;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_RevReservationOff_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_RevReservationOff_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_RevReservationOff_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_RevReservationOff_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2276, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 75;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 429 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 430 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 431: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 432 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_FwdReservationOff_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_FwdReservationOff_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2306, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 77;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_FwdReservationOff_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_FwdReservationOff_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2306, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 77;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 434 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 435 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 436: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 437 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_FwdReservationOn_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_FwdReservationOn_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2336, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 79;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_FwdReservationOn_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_FwdReservationOn_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2336, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 79;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 439 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 440 /* ReservationCount */: {
					Destin->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 441: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 442 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_FwdReservationAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_FwdReservationAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 764, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 81;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_FwdReservationAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_FwdReservationAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 764, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 81;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 444 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3219, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 82;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3219, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 82;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 445 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 446: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 447 /* AttributeLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 448 /* AttributeRecord */: {
					(void)DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AttributeRecord)), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos, pCSN1CContextSet);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 769, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 84;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 769, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 84;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 451 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 20, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 85;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 20, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 85;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 452 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_Flush_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_Flush_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_Flush_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 774, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 86;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_Flush_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_Flush_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_Flush_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_Flush_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 774, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 86;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 453 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 454 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 455 /* SARSequenceLength */: {
					Destin->SARSequenceLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 456 /* LastSARSequence */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence (&(Destin->LastSARSequence), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->LastSARSequence.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->LastSARSequence.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_SRP_INUSE_Nak_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_SRP_INUSE_Nak_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_SRP_INUSE_Nak_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2366, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 87;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_SRP_INUSE_Nak_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_SRP_INUSE_Nak_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_SRP_INUSE_Nak_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_SRP_INUSE_Nak_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2366, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 87;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 457 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 458 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 459 /* Reserved1 */: {
					Destin->Reserved1 = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}
			case 460 /* SARSequenceLength */: {
					Destin->SARSequenceLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 461 /* ReportCount */: {
					Destin->ReportCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 462: {
				if (SETITEMS_c_MLMFPA_SRP_INUSE_Nak_contents_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 463 /* FirstErasedDataUnit */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FirstErasedDataUnit), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FirstErasedDataUnit.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FirstErasedDataUnit.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}
			case 464 /* WindowLen */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_WindowLen (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->WindowLen), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->WindowLen.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->WindowLen.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}
			case 465 /* VR */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_VR (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->VR), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->VR.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->VR.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_DOSP_INUSE_DataOverSignaling_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 24, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 89;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_DOSP_INUSE_DataOverSignaling_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 24, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 89;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 469 /* LinkFlowNumber */: {
					Destin->LinkFlowNumber = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 5);
					break;
				}
			case 470 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 471 /* AckRequired */: {
					Destin->AckRequired = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 472 /* Reset */: {
					Destin->Reset = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 473 /* Reserved */: {
					Destin->Reserved = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 2);
					break;
				}
			case 474 /* MessageSequence */: {
					Destin->MessageSequence = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 6);
					break;
				}
			case 475 /* HigherLayerPacket */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket (&(Destin->HigherLayerPacket), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->HigherLayerPacket.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->HigherLayerPacket.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 54, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 90;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 54, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 90;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 476 /* Route */: {
					Destin->Route = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}
			case 477 /* AckSequence */: {
					Destin->AckSequence = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 6);
					break;
				}
			case 478 /* Reserved */: {
					Destin->Reserved = (EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 1) != 0 ? ED_TRUE : ED_FALSE);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_LUP_INUSE_LocationNotification_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_LUP_INUSE_LocationNotification_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_LocationNotification_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 64, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 91;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_LUP_INUSE_LocationNotification_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_LUP_INUSE_LocationNotification_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_LUP_INUSE_LocationNotification_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_LUP_INUSE_LocationNotification_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 64, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 91;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 479 /* LocationType */: {
					Destin->LocationType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 480 /* LocationLength */: {
					SETPRESENT_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationLength (&((*Destin)), ED_TRUE);
					Destin->LocationLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 481 /* LocationValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue (&(Destin->LocationValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->LocationValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->LocationValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_LUP_INUSE_LocationAssignment_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_LUP_INUSE_LocationAssignment_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_LocationAssignment_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 94, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 92;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_LUP_INUSE_LocationAssignment_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_LUP_INUSE_LocationAssignment_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_LUP_INUSE_LocationAssignment_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_LUP_INUSE_LocationAssignment_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 94, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 92;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 482 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 483 /* LocationType */: {
					Destin->LocationType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 484 /* LocationLength */: {
					Destin->LocationLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 485 /* LocationValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue (&(Destin->LocationValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->LocationValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->LocationValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_LUP_INUSE_LocationComplete_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_LUP_INUSE_LocationComplete_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_LocationComplete_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 119, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 93;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_LUP_INUSE_LocationComplete_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_LUP_INUSE_LocationComplete_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_LUP_INUSE_LocationComplete_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_LUP_INUSE_LocationComplete_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 119, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 93;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 486 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 123, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 94;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 123, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 94;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 487 /* StorageBLOBType */: {
					Destin->StorageBLOBType = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 488 /* StorageBLOBLength */: {
					Destin->StorageBLOBLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 489 /* StorageBLOB */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB (&(Destin->StorageBLOB), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->StorageBLOB.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->StorageBLOB.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 147, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 95;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 147, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 95;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 490 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 491 /* StorageBLOBType */: {
					Destin->StorageBLOBType = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 492 /* StorageBLOBLength */: {
					Destin->StorageBLOBLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 493 /* StorageBLOB */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB (&(Destin->StorageBLOB), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->StorageBLOB.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->StorageBLOB.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 176, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 96;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 176, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 96;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 494 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_DataReady_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_DataReady_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_FCP_INUSE_DataReady_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 180, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 97;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_FCP_INUSE_DataReady_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_DataReady_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_DataReady_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_FCP_INUSE_DataReady_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 180, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 97;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 495 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_DataReadyAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_DataReadyAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_FCP_INUSE_DataReadyAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 184, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 98;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_FCP_INUSE_DataReadyAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_DataReadyAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_DataReadyAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_FCP_INUSE_DataReadyAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 184, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 98;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 496 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 188, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 99;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 188, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 99;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 497 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 192, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 100;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 192, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 100;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 498 /* TransactionID */: {
					Destin->TransactionID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 814, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 101;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 814, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 101;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 499 /* ValueID */: {
					Destin->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 500 /* QoSProfileCount */: {
					Destin->QoSProfileCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 501: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 502 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 503 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 504 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 866, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 103;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 866, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 103;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 508 /* ValueID */: {
					Destin->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 509 /* QoSProfileCount */: {
					Destin->QoSProfileCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 510: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 511 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 512 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 513 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 918, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 105;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 918, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 105;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 517: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 518 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 519 /* MaxNumLinkFlowsFwd */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumLinkFlowsFwd = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 520 /* MaxNumLinkFlowsRev */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumLinkFlowsRev = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 521 /* MaxActivatedLinkFlowsFwd */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxActivatedLinkFlowsFwd = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 522 /* MaxActivatedLinkFlowsRev */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxActivatedLinkFlowsRev = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 951, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 107;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 951, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 107;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 528: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 529 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 530 /* MaxNumReservationsFwd */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumReservationsFwd = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 531 /* MaxNumReservationsRev */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumReservationsRev = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 532 /* MaxNumOpenReservationsFwd */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumOpenReservationsFwd = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 533 /* MaxNumOpenReservationsRev */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumOpenReservationsRev = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 984, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 109;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 984, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 109;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 539: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 540 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 541 /* AbortTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AbortTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 542 /* FlushTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FlushTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1009, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 111;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1009, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 111;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 546: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 547 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 548 /* AbortTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AbortTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 549 /* FlushTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FlushTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2459, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 113;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2459, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 113;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 553: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 554 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 555 /* ReservationCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 556: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 557 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2501, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 116;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2501, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 116;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 562: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 563 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 564 /* ReservationCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 565: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 566 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1034, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 119;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1034, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 119;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 571: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 572 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 573 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 574 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 575 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1077, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 121;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1077, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 121;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 580: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 581 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 582 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 583 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 584 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1120, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 123;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1120, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 123;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 589: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 590 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 591 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 592 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 593 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1163, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 125;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1163, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 125;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 598: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 599 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 600 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 601 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 602 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1206, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 127;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1206, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 127;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 607: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 608 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 609 /* ProtocolID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 610 /* ProtocolParametersLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParametersLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 611 /* ProtocolParameters */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1249, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 129;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1249, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 129;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 616: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 617 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 618 /* ProtocolID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 619 /* ProtocolParametersLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParametersLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 620 /* ProtocolParameters */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1292, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 131;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1292, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 131;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 625: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 626 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 627 /* ProtocolID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 628 /* ProtocolParametersLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParametersLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 629 /* ProtocolParameters */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1335, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 133;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1335, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 133;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 634: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 635 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 636 /* ProtocolID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 637 /* ProtocolParametersLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParametersLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 638 /* ProtocolParameters */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 196, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 135;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 196, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 135;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 643 /* ValueID */: {
					Destin->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 644 /* ProtocolSupported */: {
					Destin->ProtocolSupported = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 645 /* SupportedProtocolParametersValuesLength */: {
					Destin->SupportedProtocolParametersValuesLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 646 /* SupportedProtocolParametersValues */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues (&(Destin->SupportedProtocolParametersValues), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->SupportedProtocolParametersValues.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->SupportedProtocolParametersValues.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 225, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 136;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 225, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 136;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 647 /* ValueID */: {
					Destin->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 648 /* ProtocolSupported */: {
					Destin->ProtocolSupported = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 649 /* SupportedProtocolParametersValuesLength */: {
					Destin->SupportedProtocolParametersValuesLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 650 /* SupportedProtocolParametersValues */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues (&(Destin->SupportedProtocolParametersValues), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->SupportedProtocolParametersValues.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->SupportedProtocolParametersValues.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2543, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 137;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2543, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 137;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 651: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 652 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 653 /* BCMCSFlowCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->BCMCSFlowCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 654: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 655 /* BCMCSFlowID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->BCMCSFlowID = (ED_LONG)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 32);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3258, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 140;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3258, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 140;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 660: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 661 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 662 /* ProgramCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProgramCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 663: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 664 /* ProgramIDLSBLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProgramIDLSBLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 665 /* ProgramIDLSBs */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProgramIDLSBs = (ED_LONG)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 32);
					break;
				}
			case 666 /* FlowDiscriminatorCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FlowDiscriminatorCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 667: {
				if (SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data03), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 668 /* FlowDiscriminator */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data03.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FlowDiscriminator = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1378, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 144;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1378, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 144;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 677 /* ValueID */: {
					Destin->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 678 /* QoSProfileCount */: {
					Destin->QoSProfileCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 679: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 680 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 681 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 682 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1430, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 146;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1430, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 146;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 686 /* ValueID */: {
					Destin->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 687 /* QoSProfileCount */: {
					Destin->QoSProfileCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 688: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 689 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 690 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 691 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1482, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 148;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1482, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 148;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 695: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 696 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 697 /* MaxNumLinkFlowsFwd */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumLinkFlowsFwd = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 698 /* MaxNumLinkFlowsRev */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumLinkFlowsRev = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 699 /* MaxActivatedLinkFlowsFwd */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxActivatedLinkFlowsFwd = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 700 /* MaxActivatedLinkFlowsRev */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxActivatedLinkFlowsRev = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1515, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 150;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1515, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 150;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 706: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 707 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 708 /* MaxNumReservationsFwd */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumReservationsFwd = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 709 /* MaxNumReservationsRev */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumReservationsRev = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 710 /* MaxNumOpenReservationsFwd */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumOpenReservationsFwd = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 711 /* MaxNumOpenReservationsRev */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->MaxNumOpenReservationsRev = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1548, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 152;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1548, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 152;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 717: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 718 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 719 /* SARSequenceLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->SARSequenceLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 720 /* SARSequenceLengthShort */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->SARSequenceLengthShort = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1573, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 154;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1573, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 154;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 724: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 725 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 726 /* AbortTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AbortTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 727 /* FlushTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FlushTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 728 /* NakDelayTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->NakDelayTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1602, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 156;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1602, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 156;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 733: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 734 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 735 /* AbortTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->AbortTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 736 /* FlushTimer */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FlushTimer = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2585, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 158;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2585, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 158;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 740: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 741 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 742 /* ReservationCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 743: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 744 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2627, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 161;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2627, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 161;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 749: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 750 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 751 /* ReservationCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 752: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 753 /* ReservationLabel */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ReservationLabel = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1627, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 164;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1627, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 164;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 758: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 759 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 760 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 761 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 762 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1670, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 166;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1670, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 166;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 767: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 768 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 769 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 770 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 771 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1713, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 168;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1713, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 168;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 776: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 777 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 778 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 779 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 780 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1756, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 170;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1756, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 170;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 785: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 786 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 787 /* ProfileType */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileType = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 788 /* ProfileLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileLength = (ED_SHORT)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 16);
					break;
				}
			case 789 /* ProfileValue */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProfileValue.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1799, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 172;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1799, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 172;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 794: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 795 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 796 /* ProtocolID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 797 /* ProtocolParametersLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParametersLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 798 /* ProtocolParameters */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1842, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 174;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1842, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 174;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 803: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 804 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 805 /* ProtocolID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 806 /* ProtocolParametersLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParametersLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 807 /* ProtocolParameters */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1885, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 176;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1885, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 176;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 812: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 813 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 814 /* ProtocolID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 815 /* ProtocolParametersLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParametersLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 816 /* ProtocolParameters */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1928, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 178;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 1928, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 178;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 821: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 822 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 823 /* ProtocolID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 824 /* ProtocolParametersLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParametersLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 825 /* ProtocolParameters */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters (&(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProtocolParameters.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 254, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 180;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 254, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 180;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 830 /* ValueID */: {
					Destin->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 831 /* ProtocolSupported */: {
					Destin->ProtocolSupported = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 832 /* SupportedProtocolParametersValuesLength */: {
					Destin->SupportedProtocolParametersValuesLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 264, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 181;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 264, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 181;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 833 /* ValueID */: {
					Destin->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 834 /* ProtocolSupported */: {
					Destin->ProtocolSupported = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 835 /* SupportedProtocolParametersValuesLength */: {
					Destin->SupportedProtocolParametersValuesLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 836 /* SupportedProtocolParametersValues */: {
					if (CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos > 0) {
						/* BINDEC02 */
						ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues (&(Destin->SupportedProtocolParametersValues), CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
					
						EDCopyBits (Destin->SupportedProtocolParametersValues.value, 0, Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos);
						Destin->SupportedProtocolParametersValues.usedBits = CSN1C_CONTEXT_PTR->Fields[i+1].Pos - CSN1C_CONTEXT_PTR->Fields[i].Pos;
					}
					
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2669, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 182;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 2669, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 182;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 837: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 838 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 839 /* BCMCSFlowCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->BCMCSFlowCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 840: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 841 /* BCMCSFlowID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->BCMCSFlowID = (ED_LONG)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 32);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Source

ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* ED_CONST Source, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_ENCODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation
	int Ret;

#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT

	/* Initialize the stack */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3329, Buffer, BitOffset, 0, 1);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 185;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Source;

#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_ENCODE
#endif

	/* Run the encoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, XENCODE_DATA_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation ED_EXTRAPARAMS_CALL);

	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#define THIS Destin

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* ED_CONST Destin, ED_EXLONG Length, struct SCSN1CContextSet* pCSN1CContextSet))

{
#ifndef CSN1C_DISABLE_DECODE_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation
	int Ret, i;
	
#ifdef CSN1C_DISABLE_ADT
#error "CSN.1 ADT DISABLED. ENCODE/DECODE FUNCTIONS MUST BE DISABLED WITH ED_CSN1_DISABLE_ADT TCL VARIABLE"
#endif
	CSN1C_DECLARE_CONTEXT
	
	/* Initialize the context */
	CSN1C_Init (CSN1C_CONTEXT_PTR, &Program_cs0063_Program, 3329, (void*)Buffer, BitOffset, Length, 0);
	
	/* Prepare the stack host field id */
	CSN1C_CONTEXT_PTR->HostFieldId = 185;
	
	/* Set the data object */
	CSN1C_CONTEXT_PTR->Data = (void*)Destin;
	
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT
	CSN1C_USER_DEFINED_SETUP_CONTEXT
#endif
#ifdef CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
	CSN1C_USER_DEFINED_SETUP_CONTEXT_DECODE
#endif

	/* Run the decoder */
	Ret = CSN1C_Process (CSN1C_CONTEXT_PTR, NULL ED_EXTRAPARAMS_CALL);

	for (i=0; i<CSN1C_CONTEXT_PTR->FieldState.FieldsTop; i++) {
		if (CSN1C_CONTEXT_PTR->Fields[i].Index >= 0) {
			switch (CSN1C_CONTEXT_PTR->Fields[i].FieldId) {
				case 846: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (&((*Destin).data01), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 847 /* ValueID */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ValueID = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 848 /* ProgramCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProgramCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 849: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data02), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 850 /* ProgramIDLSBLength */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProgramIDLSBLength = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 851 /* ProgramIDLSBs */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->ProgramIDLSBs = (ED_LONG)EDBitsToInt (Buffer, (CSN1C_CONTEXT_PTR->Fields[i].Pos), 32);
					break;
				}
			case 852 /* FlowDiscriminatorCount */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FlowDiscriminatorCount = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}
			case 853: {
				if (SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (&((*(Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index])).data03), CSN1C_CONTEXT_PTR->Fields[i].Index+1) != ED_NO_ERRORS) {CSN1C_CONTEXT_PTR->Failed = -1; return ED_ARRAY_OVERFLOW;}
				break;
			}
			case 854 /* FlowDiscriminator */: {
					Destin->data01.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Parent->Index]->data02.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Parent->Index]->data03.data[(&(CSN1C_CONTEXT_PTR->Fields[i]))->Parent->Index]->FlowDiscriminator = (unsigned char)EDBitsToInt (Buffer, CSN1C_CONTEXT_PTR->Fields[i].Pos, 8);
					break;
				}

				default:;
			}
		}
	}
	
	CSN1C_UNDECLARE_CONTEXT
	
	return Ret;
#else
	ED_ASSERT_FORCE_FAIL
	return ED_SYNTAX_ERROR;
#endif
}
#undef THIS
#ifdef CSN1C_LABEL_NAMES
/* List of label names */
const char* const Program_cs0063_Labels [] = {

	/*     0 */ "CSN1_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents_TransactionID",
	/*     1 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_LinkFlowNumber",
	/*     2 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Route",
	/*     3 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_AckRequired",
	/*     4 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Reset",
	/*     5 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Reserved",
	/*     6 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_MessageSequence",
	/*     7 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket",
	/*     8 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_Route",
	/*     9 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_AckSequence",
	/*    10 */ "CSN1_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_Reserved",
	/*    11 */ "CSN1_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationType",
	/*    12 */ "CSN1_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationLength",
	/*    13 */ "CSN1_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue",
	/*    14 */ "CSN1_MLMFPA_LUP_INUSE_LocationAssignment_contents_TransactionID",
	/*    15 */ "CSN1_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationType",
	/*    16 */ "CSN1_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationLength",
	/*    17 */ "CSN1_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue",
	/*    18 */ "CSN1_MLMFPA_LUP_INUSE_LocationComplete_contents_TransactionID",
	/*    19 */ "CSN1_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBType",
	/*    20 */ "CSN1_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBLength",
	/*    21 */ "CSN1_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB",
	/*    22 */ "CSN1_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_TransactionID",
	/*    23 */ "CSN1_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBType",
	/*    24 */ "CSN1_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBLength",
	/*    25 */ "CSN1_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB",
	/*    26 */ "CSN1_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents_TransactionID",
	/*    27 */ "CSN1_MLMFPA_FCP_INUSE_DataReady_contents_TransactionID",
	/*    28 */ "CSN1_MLMFPA_FCP_INUSE_DataReadyAck_contents_TransactionID",
	/*    29 */ "CSN1_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents_TransactionID",
	/*    30 */ "CSN1_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents_TransactionID",
	/*    31 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ValueID",
	/*    32 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ProtocolSupported",
	/*    33 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValuesLength",
	/*    34 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues",
	/*    35 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ValueID",
	/*    36 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ProtocolSupported",
	/*    37 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValuesLength",
	/*    38 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues",
	/*    39 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ValueID",
	/*    40 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ProtocolSupported",
	/*    41 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValuesLength",
	/*    42 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ValueID",
	/*    43 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ProtocolSupported",
	/*    44 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValuesLength",
	/*    45 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues",
	/*    46 */ "CSN1_EMFPKA_RSP_INUSE_RouteSelect_contents_TransactionID",
	/*    47 */ "CSN1_EMFPKA_RSP_INUSE_RouteSelect_contents_Route",
	/*    48 */ "CSN1_EMFPKA_RSP_INUSE_RouteSelect_contents_Reserved",
	/*    49 */ "CSN1_EMFPKA_RSP_INUSE_RouteSelectAck_contents_TransactionID",
	/*    50 */ "CSN1_EMFPKA_RSP_INUSE_ActivateRoute_contents_TransactionID",
	/*    51 */ "CSN1_EMFPKA_RSP_INUSE_ActivateRoute_contents_Route",
	/*    52 */ "CSN1_EMFPKA_RSP_INUSE_ActivateRoute_contents_Reserved",
	/*    53 */ "CSN1_EMFPKA_RSP_INUSE_ActivateRouteAck_contents_TransactionID",
	/*    54 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxIndication_contents_LinkFlowNumber",
	/*    55 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxIndication_contents_Route",
	/*    56 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxIndication_contents_Reserved",
	/*    57 */ "CSN1_EMFPKA_RLP_INUSE_ResetRxIndication_contents_LinkFlowNumber",
	/*    58 */ "CSN1_EMFPKA_RLP_INUSE_ResetRxIndication_contents_Route",
	/*    59 */ "CSN1_EMFPKA_RLP_INUSE_ResetRxIndication_contents_Reserved",
	/*    60 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_LinkFlowNumber",
	/*    61 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_Route",
	/*    62 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_Reserved",
	/*    63 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxComplete_contents_LinkFlowNumber",
	/*    64 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxComplete_contents_Route",
	/*    65 */ "CSN1_EMFPKA_RLP_INUSE_ResetTxComplete_contents_Reserved",
	/*    66 */ "CSN1_EMFPKA_RLP_INUSE_ResetRxComplete_contents_LinkFlowNumber",
	/*    67 */ "CSN1_EMFPKA_RLP_INUSE_ResetRxComplete_contents_Route",
	/*    68 */ "CSN1_EMFPKA_RLP_INUSE_ResetRxComplete_contents_Reserved",
	/*    69 */ "CSN1_EMFPKA_RLP_INUSE_ReservationAccept_contents_TransactionID",
	/*    70 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationAck_contents_TransactionID",
	/*    71 */ "CSN1_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents_TransactionID",
	/*    72 */ "CSN1_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents_TransactionID",
	/*    73 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_LinkFlowNumber",
	/*    74 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Route",
	/*    75 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_AckRequired",
	/*    76 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Reset",
	/*    77 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Reserved",
	/*    78 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_MessageSequence",
	/*    79 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket",
	/*    80 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_Route",
	/*    81 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_AckSequence",
	/*    82 */ "CSN1_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_Reserved",
	/*    83 */ "CSN1_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationType",
	/*    84 */ "CSN1_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationLength",
	/*    85 */ "CSN1_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue",
	/*    86 */ "CSN1_EMFPKA_LUP_INUSE_LocationAssignment_contents_TransactionID",
	/*    87 */ "CSN1_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationType",
	/*    88 */ "CSN1_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationLength",
	/*    89 */ "CSN1_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue",
	/*    90 */ "CSN1_EMFPKA_LUP_INUSE_LocationComplete_contents_TransactionID",
	/*    91 */ "CSN1_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBType",
	/*    92 */ "CSN1_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBLength",
	/*    93 */ "CSN1_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB",
	/*    94 */ "CSN1_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_TransactionID",
	/*    95 */ "CSN1_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBType",
	/*    96 */ "CSN1_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBLength",
	/*    97 */ "CSN1_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB",
	/*    98 */ "CSN1_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents_TransactionID",
	/*    99 */ "CSN1_EMFPKA_FCP_INUSE_DataReady_contents_TransactionID",
	/*   100 */ "CSN1_EMFPKA_FCP_INUSE_DataReadyAck_contents_TransactionID",
	/*   101 */ "CSN1_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents_TransactionID",
	/*   102 */ "CSN1_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents_TransactionID",
	/*   103 */ "CSN1_MLMFPA_RSP_INUSE_RouteSelect_contents_TransactionID",
	/*   104 */ "CSN1_MLMFPA_RSP_INUSE_RouteSelect_contents_Route",
	/*   105 */ "CSN1_MLMFPA_RSP_INUSE_RouteSelect_contents_Reserved",
	/*   106 */ "CSN1_MLMFPA_RSP_INUSE_RouteSelectAck_contents_TransactionID",
	/*   107 */ "CSN1_MLMFPA_RSP_INUSE_ActivateRoute_contents_TransactionID",
	/*   108 */ "CSN1_MLMFPA_RSP_INUSE_ActivateRoute_contents_Route",
	/*   109 */ "CSN1_MLMFPA_RSP_INUSE_ActivateRoute_contents_Reserved",
	/*   110 */ "CSN1_MLMFPA_RSP_INUSE_ActivateRouteAck_contents_TransactionID",
	/*   111 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxIndication_contents_LinkFlowNumber",
	/*   112 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxIndication_contents_Route",
	/*   113 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxIndication_contents_Reserved",
	/*   114 */ "CSN1_MLMFPA_SRP_INUSE_ResetRxIndication_contents_LinkFlowNumber",
	/*   115 */ "CSN1_MLMFPA_SRP_INUSE_ResetRxIndication_contents_Route",
	/*   116 */ "CSN1_MLMFPA_SRP_INUSE_ResetRxIndication_contents_Reserved",
	/*   117 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_LinkFlowNumber",
	/*   118 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_Route",
	/*   119 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_Reserved",
	/*   120 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxComplete_contents_LinkFlowNumber",
	/*   121 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxComplete_contents_Route",
	/*   122 */ "CSN1_MLMFPA_SRP_INUSE_ResetTxComplete_contents_Reserved",
	/*   123 */ "CSN1_MLMFPA_SRP_INUSE_ResetRxComplete_contents_LinkFlowNumber",
	/*   124 */ "CSN1_MLMFPA_SRP_INUSE_ResetRxComplete_contents_Route",
	/*   125 */ "CSN1_MLMFPA_SRP_INUSE_ResetRxComplete_contents_Reserved",
	/*   126 */ "CSN1_MLMFPA_SRP_INUSE_ReservationAccept_contents_TransactionID",
	/*   127 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationAck_contents_TransactionID",
	/*   128 */ "CSN1_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents_TransactionID",
	/*   129 */ "CSN1_MLMFPA_SRP_INUSE_Flush_contents_LinkFlowNumber",
	/*   130 */ "CSN1_MLMFPA_SRP_INUSE_Flush_contents_Route",
	/*   131 */ "CSN1_MLMFPA_SRP_INUSE_Flush_contents_SARSequenceLength",
	/*   132 */ "CSN1_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence",
	/*   133 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_ValueID",
	/*   134 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_QoSProfileCount",
	/*   135 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01",
	/*   136 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileType",
	/*   137 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileLength",
	/*   138 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileValue",
	/*   139 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_ValueID",
	/*   140 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_QoSProfileCount",
	/*   141 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01",
	/*   142 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileType",
	/*   143 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileLength",
	/*   144 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileValue",
	/*   145 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01",
	/*   146 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_ValueID",
	/*   147 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxNumLinkFlowsFwd",
	/*   148 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxNumLinkFlowsRev",
	/*   149 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxActivatedLinkFlowsFwd",
	/*   150 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxActivatedLinkFlowsRev",
	/*   151 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01",
	/*   152 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_ValueID",
	/*   153 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumReservationsFwd",
	/*   154 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumReservationsRev",
	/*   155 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumOpenReservationsFwd",
	/*   156 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumOpenReservationsRev",
	/*   157 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01",
	/*   158 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_ValueID",
	/*   159 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_AbortTimer",
	/*   160 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_FlushTimer",
	/*   161 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01",
	/*   162 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_ValueID",
	/*   163 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_AbortTimer",
	/*   164 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_FlushTimer",
	/*   165 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01",
	/*   166 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ValueID",
	/*   167 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileType",
	/*   168 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileLength",
	/*   169 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileValue",
	/*   170 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01",
	/*   171 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ValueID",
	/*   172 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileType",
	/*   173 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileLength",
	/*   174 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileValue",
	/*   175 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01",
	/*   176 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ValueID",
	/*   177 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileType",
	/*   178 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileLength",
	/*   179 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileValue",
	/*   180 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01",
	/*   181 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ValueID",
	/*   182 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileType",
	/*   183 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileLength",
	/*   184 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileValue",
	/*   185 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01",
	/*   186 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ValueID",
	/*   187 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolID",
	/*   188 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolParametersLength",
	/*   189 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolParameters",
	/*   190 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01",
	/*   191 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ValueID",
	/*   192 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolID",
	/*   193 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolParametersLength",
	/*   194 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolParameters",
	/*   195 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01",
	/*   196 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ValueID",
	/*   197 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolID",
	/*   198 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolParametersLength",
	/*   199 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolParameters",
	/*   200 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01",
	/*   201 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ValueID",
	/*   202 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolID",
	/*   203 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolParametersLength",
	/*   204 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolParameters",
	/*   205 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_ValueID",
	/*   206 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_QoSProfileCount",
	/*   207 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01",
	/*   208 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileType",
	/*   209 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileLength",
	/*   210 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileValue",
	/*   211 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_ValueID",
	/*   212 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_QoSProfileCount",
	/*   213 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01",
	/*   214 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileType",
	/*   215 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileLength",
	/*   216 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileValue",
	/*   217 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01",
	/*   218 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_ValueID",
	/*   219 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxNumLinkFlowsFwd",
	/*   220 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxNumLinkFlowsRev",
	/*   221 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxActivatedLinkFlowsFwd",
	/*   222 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxActivatedLinkFlowsRev",
	/*   223 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01",
	/*   224 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_ValueID",
	/*   225 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumReservationsFwd",
	/*   226 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumReservationsRev",
	/*   227 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumOpenReservationsFwd",
	/*   228 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumOpenReservationsRev",
	/*   229 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01",
	/*   230 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_ValueID",
	/*   231 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_SARSequenceLength",
	/*   232 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_SARSequenceLengthShort",
	/*   233 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01",
	/*   234 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_ValueID",
	/*   235 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_AbortTimer",
	/*   236 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_FlushTimer",
	/*   237 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_NakDelayTimer",
	/*   238 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01",
	/*   239 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_ValueID",
	/*   240 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_AbortTimer",
	/*   241 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_FlushTimer",
	/*   242 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01",
	/*   243 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ValueID",
	/*   244 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileType",
	/*   245 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileLength",
	/*   246 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileValue",
	/*   247 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01",
	/*   248 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ValueID",
	/*   249 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileType",
	/*   250 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileLength",
	/*   251 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileValue",
	/*   252 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01",
	/*   253 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ValueID",
	/*   254 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileType",
	/*   255 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileLength",
	/*   256 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileValue",
	/*   257 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01",
	/*   258 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ValueID",
	/*   259 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileType",
	/*   260 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileLength",
	/*   261 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileValue",
	/*   262 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01",
	/*   263 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ValueID",
	/*   264 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolID",
	/*   265 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolParametersLength",
	/*   266 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolParameters",
	/*   267 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01",
	/*   268 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ValueID",
	/*   269 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolID",
	/*   270 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolParametersLength",
	/*   271 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolParameters",
	/*   272 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01",
	/*   273 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ValueID",
	/*   274 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolID",
	/*   275 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolParametersLength",
	/*   276 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolParameters",
	/*   277 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01",
	/*   278 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ValueID",
	/*   279 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolID",
	/*   280 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolParametersLength",
	/*   281 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolParameters",
	/*   282 */ "CSN1_EMFPKA_RLP_INUSE_RevReservationOn_contents_TransactionID",
	/*   283 */ "CSN1_EMFPKA_RLP_INUSE_RevReservationOn_contents_ReservationCount",
	/*   284 */ "CSN1_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01",
	/*   285 */ "CSN1_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_ReservationLabel",
	/*   286 */ "CSN1_EMFPKA_RLP_INUSE_RevReservationOff_contents_TransactionID",
	/*   287 */ "CSN1_EMFPKA_RLP_INUSE_RevReservationOff_contents_ReservationCount",
	/*   288 */ "CSN1_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01",
	/*   289 */ "CSN1_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_ReservationLabel",
	/*   290 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationOff_contents_TransactionID",
	/*   291 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationOff_contents_ReservationCount",
	/*   292 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01",
	/*   293 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_ReservationLabel",
	/*   294 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationOn_contents_TransactionID",
	/*   295 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationOn_contents_ReservationCount",
	/*   296 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01",
	/*   297 */ "CSN1_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_ReservationLabel",
	/*   298 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_LinkFlowNumber",
	/*   299 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_Route",
	/*   300 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_Reserved1",
	/*   301 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_SARSequenceLength",
	/*   302 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_ReportCount",
	/*   303 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01",
	/*   304 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_DelayedNak",
	/*   305 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_LeadingEdgeIncluded",
	/*   306 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_LeadingEdge",
	/*   307 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_TrailingEdge",
	/*   308 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_OtherQNCount",
	/*   309 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02",
	/*   310 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_LargestSAR",
	/*   311 */ "CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR",
	/*   312 */ "CSN1_MLMFPA_SRP_INUSE_RevReservationOn_contents_TransactionID",
	/*   313 */ "CSN1_MLMFPA_SRP_INUSE_RevReservationOn_contents_ReservationCount",
	/*   314 */ "CSN1_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01",
	/*   315 */ "CSN1_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_ReservationLabel",
	/*   316 */ "CSN1_MLMFPA_SRP_INUSE_RevReservationOff_contents_TransactionID",
	/*   317 */ "CSN1_MLMFPA_SRP_INUSE_RevReservationOff_contents_ReservationCount",
	/*   318 */ "CSN1_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01",
	/*   319 */ "CSN1_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_ReservationLabel",
	/*   320 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationOff_contents_TransactionID",
	/*   321 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationOff_contents_ReservationCount",
	/*   322 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01",
	/*   323 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_ReservationLabel",
	/*   324 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationOn_contents_TransactionID",
	/*   325 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationOn_contents_ReservationCount",
	/*   326 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01",
	/*   327 */ "CSN1_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_ReservationLabel",
	/*   328 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_LinkFlowNumber",
	/*   329 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_Route",
	/*   330 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_Reserved1",
	/*   331 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_SARSequenceLength",
	/*   332 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_ReportCount",
	/*   333 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_data01",
	/*   334 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_data01_FirstErasedDataUnit",
	/*   335 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_data01_WindowLen",
	/*   336 */ "CSN1_MLMFPA_SRP_INUSE_Nak_contents_data01_VR",
	/*   337 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01",
	/*   338 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_ValueID",
	/*   339 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_ReservationCount",
	/*   340 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data02",
	/*   341 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data02_ReservationLabel",
	/*   342 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01",
	/*   343 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_ValueID",
	/*   344 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_ReservationCount",
	/*   345 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data02",
	/*   346 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data02_ReservationLabel",
	/*   347 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01",
	/*   348 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_ValueID",
	/*   349 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_BCMCSFlowCount",
	/*   350 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data02",
	/*   351 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data02_BCMCSFlowID",
	/*   352 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01",
	/*   353 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_ValueID",
	/*   354 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_ReservationCount",
	/*   355 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data02",
	/*   356 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data02_ReservationLabel",
	/*   357 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01",
	/*   358 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_ValueID",
	/*   359 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_ReservationCount",
	/*   360 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data02",
	/*   361 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data02_ReservationLabel",
	/*   362 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01",
	/*   363 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_ValueID",
	/*   364 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_BCMCSFlowCount",
	/*   365 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data02",
	/*   366 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data02_BCMCSFlowID",
	/*   367 */ "CSN1_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_TransactionID",
	/*   368 */ "CSN1_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01",
	/*   369 */ "CSN1_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_AttributeLength",
	/*   370 */ "CSN1_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_AttributeRecord",
	/*   371 */ "CSN1_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_TransactionID",
	/*   372 */ "CSN1_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01",
	/*   373 */ "CSN1_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_AttributeLength",
	/*   374 */ "CSN1_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_AttributeRecord",
	/*   375 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_LinkFlowNumber",
	/*   376 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_Route",
	/*   377 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_Reserved1",
	/*   378 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_SequenceLength",
	/*   379 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_ReportCount",
	/*   380 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_data01",
	/*   381 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_data01_FirstErasedDataUnit",
	/*   382 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_data01_WindowLen",
	/*   383 */ "CSN1_EMFPKA_RLP_INUSE_Nak_contents_data01_VR",
	/*   384 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_TransactionID",
	/*   385 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_ReservationCount",
	/*   386 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01",
	/*   387 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_Link",
	/*   388 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_ReservationLabel",
	/*   389 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_EmergencyIndication",
	/*   390 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_ReservationQueuingReq",
	/*   391 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_TransactionID",
	/*   392 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_ReservationCount",
	/*   393 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01",
	/*   394 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_Link",
	/*   395 */ "CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_ReservationLabel",
	/*   396 */ "CSN1_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_TransactionID",
	/*   397 */ "CSN1_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01",
	/*   398 */ "CSN1_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_AttributeLength",
	/*   399 */ "CSN1_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_AttributeRecord",
	/*   400 */ "CSN1_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_TransactionID",
	/*   401 */ "CSN1_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01",
	/*   402 */ "CSN1_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_AttributeLength",
	/*   403 */ "CSN1_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_AttributeRecord",
	/*   404 */ "CSN1_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_TransactionID",
	/*   405 */ "CSN1_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01",
	/*   406 */ "CSN1_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_AttributeLength",
	/*   407 */ "CSN1_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_AttributeRecord",
	/*   408 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_TransactionID",
	/*   409 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_ReservationCount",
	/*   410 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01",
	/*   411 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_Link",
	/*   412 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_ReservationLabel",
	/*   413 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_EmergencyIndication",
	/*   414 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_ReservationQueuingReq",
	/*   415 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_TransactionID",
	/*   416 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_ReservationCount",
	/*   417 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01",
	/*   418 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_Link",
	/*   419 */ "CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_ReservationLabel",
	/*   420 */ "CSN1_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_TransactionID",
	/*   421 */ "CSN1_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01",
	/*   422 */ "CSN1_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_AttributeLength",
	/*   423 */ "CSN1_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_AttributeRecord",
	/*   424 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01",
	/*   425 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_ValueID",
	/*   426 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_ProgramCount",
	/*   427 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02",
	/*   428 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_ProgramIDLSBLength",
	/*   429 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_ProgramIDLSBs",
	/*   430 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_FlowDiscriminatorCount",
	/*   431 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_data03",
	/*   432 */ "CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_data03_FlowDiscriminator",
	/*   433 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01",
	/*   434 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_ValueID",
	/*   435 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_ProgramCount",
	/*   436 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02",
	/*   437 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_ProgramIDLSBLength",
	/*   438 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_ProgramIDLSBs",
	/*   439 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_FlowDiscriminatorCount",
	/*   440 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_data03",
	/*   441 */ "CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_data03_FlowDiscriminator",
	/*   442 */ "CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_TransactionID",
	/*   443 */ "CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_ReservationCount",
	/*   444 */ "CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01",
	/*   445 */ "CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_AllowableLink",
	/*   446 */ "CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_AllowableReservationLabel",
	/*   447 */ "CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data02",
	/*   448 */ "CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data02_RejectCode",
	/*   449 */ "CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data02_PendingDuration",
	/*   450 */ "CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_TransactionID",
	/*   451 */ "CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_ReservationCount",
	/*   452 */ "CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01",
	/*   453 */ "CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_AllowableLink",
	/*   454 */ "CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_AllowableReservationLabel",
	/*   455 */ "CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data02",
	/*   456 */ "CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data02_RejectCode",
	/*   457 */ "CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data02_PendingDuration",
	NULL
};
#endif

#ifdef CSN1C_ENABLE_LABEL_SIZE
/* For each label id, there is an entry describing its size */
const unsigned char Program_cs0063_LabelSize [] = {

	/*     0 */ 8, /* CSN1_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents_TransactionID */
	/*     1 */ 5, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_LinkFlowNumber */
	/*     2 */ 1, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Route */
	/*     3 */ 1, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_AckRequired */
	/*     4 */ 1, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Reset */
	/*     5 */ 2, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Reserved */
	/*     6 */ 6, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_MessageSequence */
	/*     7 */ 0, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket */
	/*     8 */ 1, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_Route */
	/*     9 */ 6, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_AckSequence */
	/*    10 */ 1, /* CSN1_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_Reserved */
	/*    11 */ 8, /* CSN1_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationType */
	/*    12 */ 8, /* CSN1_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationLength */
	/*    13 */ 0, /* CSN1_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue */
	/*    14 */ 8, /* CSN1_MLMFPA_LUP_INUSE_LocationAssignment_contents_TransactionID */
	/*    15 */ 8, /* CSN1_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationType */
	/*    16 */ 8, /* CSN1_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationLength */
	/*    17 */ 0, /* CSN1_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue */
	/*    18 */ 8, /* CSN1_MLMFPA_LUP_INUSE_LocationComplete_contents_TransactionID */
	/*    19 */ 16, /* CSN1_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBType */
	/*    20 */ 8, /* CSN1_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBLength */
	/*    21 */ 0, /* CSN1_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB */
	/*    22 */ 8, /* CSN1_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_TransactionID */
	/*    23 */ 16, /* CSN1_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBType */
	/*    24 */ 8, /* CSN1_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBLength */
	/*    25 */ 0, /* CSN1_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB */
	/*    26 */ 8, /* CSN1_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents_TransactionID */
	/*    27 */ 8, /* CSN1_MLMFPA_FCP_INUSE_DataReady_contents_TransactionID */
	/*    28 */ 8, /* CSN1_MLMFPA_FCP_INUSE_DataReadyAck_contents_TransactionID */
	/*    29 */ 8, /* CSN1_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents_TransactionID */
	/*    30 */ 8, /* CSN1_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents_TransactionID */
	/*    31 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ValueID */
	/*    32 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ProtocolSupported */
	/*    33 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValuesLength */
	/*    34 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues */
	/*    35 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ValueID */
	/*    36 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ProtocolSupported */
	/*    37 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValuesLength */
	/*    38 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues */
	/*    39 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ValueID */
	/*    40 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ProtocolSupported */
	/*    41 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValuesLength */
	/*    42 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ValueID */
	/*    43 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ProtocolSupported */
	/*    44 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValuesLength */
	/*    45 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues */
	/*    46 */ 8, /* CSN1_EMFPKA_RSP_INUSE_RouteSelect_contents_TransactionID */
	/*    47 */ 1, /* CSN1_EMFPKA_RSP_INUSE_RouteSelect_contents_Route */
	/*    48 */ 7, /* CSN1_EMFPKA_RSP_INUSE_RouteSelect_contents_Reserved */
	/*    49 */ 8, /* CSN1_EMFPKA_RSP_INUSE_RouteSelectAck_contents_TransactionID */
	/*    50 */ 8, /* CSN1_EMFPKA_RSP_INUSE_ActivateRoute_contents_TransactionID */
	/*    51 */ 1, /* CSN1_EMFPKA_RSP_INUSE_ActivateRoute_contents_Route */
	/*    52 */ 7, /* CSN1_EMFPKA_RSP_INUSE_ActivateRoute_contents_Reserved */
	/*    53 */ 8, /* CSN1_EMFPKA_RSP_INUSE_ActivateRouteAck_contents_TransactionID */
	/*    54 */ 5, /* CSN1_EMFPKA_RLP_INUSE_ResetTxIndication_contents_LinkFlowNumber */
	/*    55 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ResetTxIndication_contents_Route */
	/*    56 */ 2, /* CSN1_EMFPKA_RLP_INUSE_ResetTxIndication_contents_Reserved */
	/*    57 */ 5, /* CSN1_EMFPKA_RLP_INUSE_ResetRxIndication_contents_LinkFlowNumber */
	/*    58 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ResetRxIndication_contents_Route */
	/*    59 */ 2, /* CSN1_EMFPKA_RLP_INUSE_ResetRxIndication_contents_Reserved */
	/*    60 */ 5, /* CSN1_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_LinkFlowNumber */
	/*    61 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_Route */
	/*    62 */ 2, /* CSN1_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_Reserved */
	/*    63 */ 5, /* CSN1_EMFPKA_RLP_INUSE_ResetTxComplete_contents_LinkFlowNumber */
	/*    64 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ResetTxComplete_contents_Route */
	/*    65 */ 2, /* CSN1_EMFPKA_RLP_INUSE_ResetTxComplete_contents_Reserved */
	/*    66 */ 5, /* CSN1_EMFPKA_RLP_INUSE_ResetRxComplete_contents_LinkFlowNumber */
	/*    67 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ResetRxComplete_contents_Route */
	/*    68 */ 2, /* CSN1_EMFPKA_RLP_INUSE_ResetRxComplete_contents_Reserved */
	/*    69 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationAccept_contents_TransactionID */
	/*    70 */ 8, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationAck_contents_TransactionID */
	/*    71 */ 8, /* CSN1_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents_TransactionID */
	/*    72 */ 8, /* CSN1_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents_TransactionID */
	/*    73 */ 5, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_LinkFlowNumber */
	/*    74 */ 1, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Route */
	/*    75 */ 1, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_AckRequired */
	/*    76 */ 1, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Reset */
	/*    77 */ 2, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Reserved */
	/*    78 */ 6, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_MessageSequence */
	/*    79 */ 0, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket */
	/*    80 */ 1, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_Route */
	/*    81 */ 6, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_AckSequence */
	/*    82 */ 1, /* CSN1_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_Reserved */
	/*    83 */ 8, /* CSN1_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationType */
	/*    84 */ 8, /* CSN1_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationLength */
	/*    85 */ 0, /* CSN1_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue */
	/*    86 */ 8, /* CSN1_EMFPKA_LUP_INUSE_LocationAssignment_contents_TransactionID */
	/*    87 */ 8, /* CSN1_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationType */
	/*    88 */ 8, /* CSN1_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationLength */
	/*    89 */ 0, /* CSN1_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue */
	/*    90 */ 8, /* CSN1_EMFPKA_LUP_INUSE_LocationComplete_contents_TransactionID */
	/*    91 */ 16, /* CSN1_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBType */
	/*    92 */ 8, /* CSN1_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBLength */
	/*    93 */ 0, /* CSN1_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB */
	/*    94 */ 8, /* CSN1_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_TransactionID */
	/*    95 */ 16, /* CSN1_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBType */
	/*    96 */ 8, /* CSN1_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBLength */
	/*    97 */ 0, /* CSN1_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB */
	/*    98 */ 8, /* CSN1_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents_TransactionID */
	/*    99 */ 8, /* CSN1_EMFPKA_FCP_INUSE_DataReady_contents_TransactionID */
	/*   100 */ 8, /* CSN1_EMFPKA_FCP_INUSE_DataReadyAck_contents_TransactionID */
	/*   101 */ 8, /* CSN1_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents_TransactionID */
	/*   102 */ 8, /* CSN1_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents_TransactionID */
	/*   103 */ 8, /* CSN1_MLMFPA_RSP_INUSE_RouteSelect_contents_TransactionID */
	/*   104 */ 1, /* CSN1_MLMFPA_RSP_INUSE_RouteSelect_contents_Route */
	/*   105 */ 7, /* CSN1_MLMFPA_RSP_INUSE_RouteSelect_contents_Reserved */
	/*   106 */ 8, /* CSN1_MLMFPA_RSP_INUSE_RouteSelectAck_contents_TransactionID */
	/*   107 */ 8, /* CSN1_MLMFPA_RSP_INUSE_ActivateRoute_contents_TransactionID */
	/*   108 */ 1, /* CSN1_MLMFPA_RSP_INUSE_ActivateRoute_contents_Route */
	/*   109 */ 7, /* CSN1_MLMFPA_RSP_INUSE_ActivateRoute_contents_Reserved */
	/*   110 */ 8, /* CSN1_MLMFPA_RSP_INUSE_ActivateRouteAck_contents_TransactionID */
	/*   111 */ 5, /* CSN1_MLMFPA_SRP_INUSE_ResetTxIndication_contents_LinkFlowNumber */
	/*   112 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ResetTxIndication_contents_Route */
	/*   113 */ 2, /* CSN1_MLMFPA_SRP_INUSE_ResetTxIndication_contents_Reserved */
	/*   114 */ 5, /* CSN1_MLMFPA_SRP_INUSE_ResetRxIndication_contents_LinkFlowNumber */
	/*   115 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ResetRxIndication_contents_Route */
	/*   116 */ 2, /* CSN1_MLMFPA_SRP_INUSE_ResetRxIndication_contents_Reserved */
	/*   117 */ 5, /* CSN1_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_LinkFlowNumber */
	/*   118 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_Route */
	/*   119 */ 2, /* CSN1_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_Reserved */
	/*   120 */ 5, /* CSN1_MLMFPA_SRP_INUSE_ResetTxComplete_contents_LinkFlowNumber */
	/*   121 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ResetTxComplete_contents_Route */
	/*   122 */ 2, /* CSN1_MLMFPA_SRP_INUSE_ResetTxComplete_contents_Reserved */
	/*   123 */ 5, /* CSN1_MLMFPA_SRP_INUSE_ResetRxComplete_contents_LinkFlowNumber */
	/*   124 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ResetRxComplete_contents_Route */
	/*   125 */ 2, /* CSN1_MLMFPA_SRP_INUSE_ResetRxComplete_contents_Reserved */
	/*   126 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationAccept_contents_TransactionID */
	/*   127 */ 8, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationAck_contents_TransactionID */
	/*   128 */ 8, /* CSN1_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents_TransactionID */
	/*   129 */ 5, /* CSN1_MLMFPA_SRP_INUSE_Flush_contents_LinkFlowNumber */
	/*   130 */ 1, /* CSN1_MLMFPA_SRP_INUSE_Flush_contents_Route */
	/*   131 */ 8, /* CSN1_MLMFPA_SRP_INUSE_Flush_contents_SARSequenceLength */
	/*   132 */ 0, /* CSN1_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence */
	/*   133 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_ValueID */
	/*   134 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_QoSProfileCount */
	/*   135 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 */
	/*   136 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileType */
	/*   137 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileLength */
	/*   138 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileValue */
	/*   139 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_ValueID */
	/*   140 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_QoSProfileCount */
	/*   141 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 */
	/*   142 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileType */
	/*   143 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileLength */
	/*   144 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileValue */
	/*   145 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 */
	/*   146 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_ValueID */
	/*   147 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxNumLinkFlowsFwd */
	/*   148 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxNumLinkFlowsRev */
	/*   149 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxActivatedLinkFlowsFwd */
	/*   150 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxActivatedLinkFlowsRev */
	/*   151 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 */
	/*   152 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_ValueID */
	/*   153 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumReservationsFwd */
	/*   154 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumReservationsRev */
	/*   155 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumOpenReservationsFwd */
	/*   156 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumOpenReservationsRev */
	/*   157 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 */
	/*   158 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_ValueID */
	/*   159 */ 16, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_AbortTimer */
	/*   160 */ 16, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_FlushTimer */
	/*   161 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 */
	/*   162 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_ValueID */
	/*   163 */ 16, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_AbortTimer */
	/*   164 */ 16, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_FlushTimer */
	/*   165 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 */
	/*   166 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ValueID */
	/*   167 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileType */
	/*   168 */ 16, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileLength */
	/*   169 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileValue */
	/*   170 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 */
	/*   171 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ValueID */
	/*   172 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileType */
	/*   173 */ 16, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileLength */
	/*   174 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileValue */
	/*   175 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 */
	/*   176 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ValueID */
	/*   177 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileType */
	/*   178 */ 16, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileLength */
	/*   179 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileValue */
	/*   180 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 */
	/*   181 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ValueID */
	/*   182 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileType */
	/*   183 */ 16, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileLength */
	/*   184 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileValue */
	/*   185 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 */
	/*   186 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ValueID */
	/*   187 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolID */
	/*   188 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolParametersLength */
	/*   189 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolParameters */
	/*   190 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 */
	/*   191 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ValueID */
	/*   192 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolID */
	/*   193 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolParametersLength */
	/*   194 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolParameters */
	/*   195 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 */
	/*   196 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ValueID */
	/*   197 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolID */
	/*   198 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolParametersLength */
	/*   199 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolParameters */
	/*   200 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 */
	/*   201 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ValueID */
	/*   202 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolID */
	/*   203 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolParametersLength */
	/*   204 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolParameters */
	/*   205 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_ValueID */
	/*   206 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_QoSProfileCount */
	/*   207 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 */
	/*   208 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileType */
	/*   209 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileLength */
	/*   210 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_ProfileValue */
	/*   211 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_ValueID */
	/*   212 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_QoSProfileCount */
	/*   213 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 */
	/*   214 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileType */
	/*   215 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileLength */
	/*   216 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_ProfileValue */
	/*   217 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 */
	/*   218 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_ValueID */
	/*   219 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxNumLinkFlowsFwd */
	/*   220 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxNumLinkFlowsRev */
	/*   221 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxActivatedLinkFlowsFwd */
	/*   222 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_MaxActivatedLinkFlowsRev */
	/*   223 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 */
	/*   224 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_ValueID */
	/*   225 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumReservationsFwd */
	/*   226 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumReservationsRev */
	/*   227 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumOpenReservationsFwd */
	/*   228 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_MaxNumOpenReservationsRev */
	/*   229 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 */
	/*   230 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_ValueID */
	/*   231 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_SARSequenceLength */
	/*   232 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_SARSequenceLengthShort */
	/*   233 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 */
	/*   234 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_ValueID */
	/*   235 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_AbortTimer */
	/*   236 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_FlushTimer */
	/*   237 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_NakDelayTimer */
	/*   238 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 */
	/*   239 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_ValueID */
	/*   240 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_AbortTimer */
	/*   241 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_FlushTimer */
	/*   242 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 */
	/*   243 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ValueID */
	/*   244 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileType */
	/*   245 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileLength */
	/*   246 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_ProfileValue */
	/*   247 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 */
	/*   248 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ValueID */
	/*   249 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileType */
	/*   250 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileLength */
	/*   251 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_ProfileValue */
	/*   252 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 */
	/*   253 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ValueID */
	/*   254 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileType */
	/*   255 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileLength */
	/*   256 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_ProfileValue */
	/*   257 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 */
	/*   258 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ValueID */
	/*   259 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileType */
	/*   260 */ 16, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileLength */
	/*   261 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_ProfileValue */
	/*   262 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 */
	/*   263 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ValueID */
	/*   264 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolID */
	/*   265 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolParametersLength */
	/*   266 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_ProtocolParameters */
	/*   267 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 */
	/*   268 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ValueID */
	/*   269 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolID */
	/*   270 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolParametersLength */
	/*   271 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_ProtocolParameters */
	/*   272 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 */
	/*   273 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ValueID */
	/*   274 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolID */
	/*   275 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolParametersLength */
	/*   276 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_ProtocolParameters */
	/*   277 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 */
	/*   278 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ValueID */
	/*   279 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolID */
	/*   280 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolParametersLength */
	/*   281 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_ProtocolParameters */
	/*   282 */ 8, /* CSN1_EMFPKA_RLP_INUSE_RevReservationOn_contents_TransactionID */
	/*   283 */ 8, /* CSN1_EMFPKA_RLP_INUSE_RevReservationOn_contents_ReservationCount */
	/*   284 */ 0, /* CSN1_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 */
	/*   285 */ 8, /* CSN1_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_ReservationLabel */
	/*   286 */ 8, /* CSN1_EMFPKA_RLP_INUSE_RevReservationOff_contents_TransactionID */
	/*   287 */ 8, /* CSN1_EMFPKA_RLP_INUSE_RevReservationOff_contents_ReservationCount */
	/*   288 */ 0, /* CSN1_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 */
	/*   289 */ 8, /* CSN1_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_ReservationLabel */
	/*   290 */ 8, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationOff_contents_TransactionID */
	/*   291 */ 8, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationOff_contents_ReservationCount */
	/*   292 */ 0, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 */
	/*   293 */ 8, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_ReservationLabel */
	/*   294 */ 8, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationOn_contents_TransactionID */
	/*   295 */ 8, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationOn_contents_ReservationCount */
	/*   296 */ 0, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 */
	/*   297 */ 8, /* CSN1_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_ReservationLabel */
	/*   298 */ 5, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_LinkFlowNumber */
	/*   299 */ 1, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_Route */
	/*   300 */ 2, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_Reserved1 */
	/*   301 */ 8, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_SARSequenceLength */
	/*   302 */ 8, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_ReportCount */
	/*   303 */ 0, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 */
	/*   304 */ 1, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_DelayedNak */
	/*   305 */ 1, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_LeadingEdgeIncluded */
	/*   306 */ 0, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_LeadingEdge */
	/*   307 */ 0, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_TrailingEdge */
	/*   308 */ 8, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_OtherQNCount */
	/*   309 */ 0, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 */
	/*   310 */ 0, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_LargestSAR */
	/*   311 */ 0, /* CSN1_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR */
	/*   312 */ 8, /* CSN1_MLMFPA_SRP_INUSE_RevReservationOn_contents_TransactionID */
	/*   313 */ 8, /* CSN1_MLMFPA_SRP_INUSE_RevReservationOn_contents_ReservationCount */
	/*   314 */ 0, /* CSN1_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 */
	/*   315 */ 8, /* CSN1_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_ReservationLabel */
	/*   316 */ 8, /* CSN1_MLMFPA_SRP_INUSE_RevReservationOff_contents_TransactionID */
	/*   317 */ 8, /* CSN1_MLMFPA_SRP_INUSE_RevReservationOff_contents_ReservationCount */
	/*   318 */ 0, /* CSN1_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 */
	/*   319 */ 8, /* CSN1_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_ReservationLabel */
	/*   320 */ 8, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationOff_contents_TransactionID */
	/*   321 */ 8, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationOff_contents_ReservationCount */
	/*   322 */ 0, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 */
	/*   323 */ 8, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_ReservationLabel */
	/*   324 */ 8, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationOn_contents_TransactionID */
	/*   325 */ 8, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationOn_contents_ReservationCount */
	/*   326 */ 0, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 */
	/*   327 */ 8, /* CSN1_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_ReservationLabel */
	/*   328 */ 5, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_LinkFlowNumber */
	/*   329 */ 1, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_Route */
	/*   330 */ 2, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_Reserved1 */
	/*   331 */ 8, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_SARSequenceLength */
	/*   332 */ 8, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_ReportCount */
	/*   333 */ 0, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_data01 */
	/*   334 */ 0, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_data01_FirstErasedDataUnit */
	/*   335 */ 0, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_data01_WindowLen */
	/*   336 */ 0, /* CSN1_MLMFPA_SRP_INUSE_Nak_contents_data01_VR */
	/*   337 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 */
	/*   338 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_ValueID */
	/*   339 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_ReservationCount */
	/*   340 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data02 */
	/*   341 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data02_ReservationLabel */
	/*   342 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 */
	/*   343 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_ValueID */
	/*   344 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_ReservationCount */
	/*   345 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data02 */
	/*   346 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data02_ReservationLabel */
	/*   347 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 */
	/*   348 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_ValueID */
	/*   349 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_BCMCSFlowCount */
	/*   350 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data02 */
	/*   351 */ 32, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data02_BCMCSFlowID */
	/*   352 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 */
	/*   353 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_ValueID */
	/*   354 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_ReservationCount */
	/*   355 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data02 */
	/*   356 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data02_ReservationLabel */
	/*   357 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 */
	/*   358 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_ValueID */
	/*   359 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_ReservationCount */
	/*   360 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data02 */
	/*   361 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data02_ReservationLabel */
	/*   362 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 */
	/*   363 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_ValueID */
	/*   364 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_BCMCSFlowCount */
	/*   365 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data02 */
	/*   366 */ 32, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data02_BCMCSFlowID */
	/*   367 */ 8, /* CSN1_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_TransactionID */
	/*   368 */ 0, /* CSN1_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 */
	/*   369 */ 8, /* CSN1_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_AttributeLength */
	/*   370 */ 0, /* CSN1_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_AttributeRecord */
	/*   371 */ 8, /* CSN1_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_TransactionID */
	/*   372 */ 0, /* CSN1_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 */
	/*   373 */ 8, /* CSN1_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_AttributeLength */
	/*   374 */ 0, /* CSN1_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_AttributeRecord */
	/*   375 */ 5, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_LinkFlowNumber */
	/*   376 */ 1, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_Route */
	/*   377 */ 2, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_Reserved1 */
	/*   378 */ 8, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_SequenceLength */
	/*   379 */ 8, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_ReportCount */
	/*   380 */ 0, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_data01 */
	/*   381 */ 0, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_data01_FirstErasedDataUnit */
	/*   382 */ 0, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_data01_WindowLen */
	/*   383 */ 0, /* CSN1_EMFPKA_RLP_INUSE_Nak_contents_data01_VR */
	/*   384 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_TransactionID */
	/*   385 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_ReservationCount */
	/*   386 */ 0, /* CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 */
	/*   387 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_Link */
	/*   388 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_ReservationLabel */
	/*   389 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_EmergencyIndication */
	/*   390 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_ReservationQueuingReq */
	/*   391 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_TransactionID */
	/*   392 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_ReservationCount */
	/*   393 */ 0, /* CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 */
	/*   394 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_Link */
	/*   395 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_ReservationLabel */
	/*   396 */ 8, /* CSN1_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_TransactionID */
	/*   397 */ 0, /* CSN1_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 */
	/*   398 */ 8, /* CSN1_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_AttributeLength */
	/*   399 */ 0, /* CSN1_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_AttributeRecord */
	/*   400 */ 8, /* CSN1_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_TransactionID */
	/*   401 */ 0, /* CSN1_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 */
	/*   402 */ 8, /* CSN1_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_AttributeLength */
	/*   403 */ 0, /* CSN1_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_AttributeRecord */
	/*   404 */ 8, /* CSN1_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_TransactionID */
	/*   405 */ 0, /* CSN1_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 */
	/*   406 */ 8, /* CSN1_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_AttributeLength */
	/*   407 */ 0, /* CSN1_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_AttributeRecord */
	/*   408 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_TransactionID */
	/*   409 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_ReservationCount */
	/*   410 */ 0, /* CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 */
	/*   411 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_Link */
	/*   412 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_ReservationLabel */
	/*   413 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_EmergencyIndication */
	/*   414 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_ReservationQueuingReq */
	/*   415 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_TransactionID */
	/*   416 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_ReservationCount */
	/*   417 */ 0, /* CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 */
	/*   418 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_Link */
	/*   419 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_ReservationLabel */
	/*   420 */ 8, /* CSN1_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_TransactionID */
	/*   421 */ 0, /* CSN1_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 */
	/*   422 */ 8, /* CSN1_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_AttributeLength */
	/*   423 */ 0, /* CSN1_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_AttributeRecord */
	/*   424 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 */
	/*   425 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_ValueID */
	/*   426 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_ProgramCount */
	/*   427 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02 */
	/*   428 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_ProgramIDLSBLength */
	/*   429 */ 32, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_ProgramIDLSBs */
	/*   430 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_FlowDiscriminatorCount */
	/*   431 */ 0, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_data03 */
	/*   432 */ 8, /* CSN1_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_data03_FlowDiscriminator */
	/*   433 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 */
	/*   434 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_ValueID */
	/*   435 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_ProgramCount */
	/*   436 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02 */
	/*   437 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_ProgramIDLSBLength */
	/*   438 */ 32, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_ProgramIDLSBs */
	/*   439 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_FlowDiscriminatorCount */
	/*   440 */ 0, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_data03 */
	/*   441 */ 8, /* CSN1_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data02_data03_FlowDiscriminator */
	/*   442 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_TransactionID */
	/*   443 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_ReservationCount */
	/*   444 */ 0, /* CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 */
	/*   445 */ 1, /* CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_AllowableLink */
	/*   446 */ 8, /* CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_AllowableReservationLabel */
	/*   447 */ 0, /* CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data02 */
	/*   448 */ 4, /* CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data02_RejectCode */
	/*   449 */ 0, /* CSN1_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data02_PendingDuration */
	/*   450 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_TransactionID */
	/*   451 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_ReservationCount */
	/*   452 */ 0, /* CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 */
	/*   453 */ 1, /* CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_AllowableLink */
	/*   454 */ 8, /* CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_AllowableReservationLabel */
	/*   455 */ 0, /* CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data02 */
	/*   456 */ 4, /* CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data02_RejectCode */
	/*   457 */ 0  /* CSN1_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data02_PendingDuration */
};
#endif

/* FieldId Pair Set */
static const CSN1C_PAIRSET_TYPE Program_cs0063_FieldIdPairSet [] = {
	/* 0000 (ID:1018:51849:51875) <TransactionID> */ 0,85,452,
	/* 0003 (ID:1084:54319:54347) <LinkFlowNumber> */ 1,89,469,
	/* 0006 (ID:1088:54347:54362) <Route> */ 2,89,470,
	/* 0009 (ID:1092:54362:54383) <AckRequired> */ 3,89,471,
	/* 0012 (ID:1096:54383:54398) <Reset> */ 4,89,472,
	/* 0015 (ID:1100:54398:54420) <Reserved> */ 5,89,473,
	/* 0018 (ID:1104:54420:54449) <MessageSequence> */ 6,89,474,
	/* 0021 (ID:1108:54449:54477) <HigherLayerPacket> */ 7,89,475,
	/* 0024 (ID:1114:55114:55129) <Route> */ 8,90,476,
	/* 0027 (ID:1118:55129:55154) <AckSequence> */ 9,90,477,
	/* 0030 (ID:1122:55154:55171) <Reserved> */ 10,90,478,
	/* 0033 (ID:1128:56243:56269) <LocationType> */ 11,91,479,
	/* 0036 (ID:1134:56270:56304) <LocationLength> */ 12,91,480,
	/* 0039 (ID:1140:56314:56390) <LocationValue> */ 13,91,481,
	/* 0042 (ID:1146:57008:57035) <TransactionID> */ 14,92,482,
	/* 0045 (ID:1150:57035:57061) <LocationType> */ 15,92,483,
	/* 0048 (ID:1154:57061:57097) <LocationLength> */ 16,92,484,
	/* 0051 (ID:1158:57097:57173) <LocationValue> */ 17,92,485,
	/* 0054 (ID:1164:57781:57807) <TransactionID> */ 18,93,486,
	/* 0057 (ID:1170:58903:58933) <StorageBLOBType> */ 19,94,487,
	/* 0060 (ID:1174:58933:58972) <StorageBLOBLength> */ 20,94,488,
	/* 0063 (ID:1178:58972:59049) <StorageBLOB> */ 21,94,489,
	/* 0066 (ID:1184:59682:59709) <TransactionID> */ 22,95,490,
	/* 0069 (ID:1188:59709:59739) <StorageBLOBType> */ 23,95,491,
	/* 0072 (ID:1192:59739:59778) <StorageBLOBLength> */ 24,95,492,
	/* 0075 (ID:1196:59778:59855) <StorageBLOB> */ 25,95,493,
	/* 0078 (ID:1202:60478:60504) <TransactionID> */ 26,96,494,
	/* 0081 (ID:1208:62790:62816) <TransactionID> */ 27,97,495,
	/* 0084 (ID:1214:63401:63427) <TransactionID> */ 28,98,496,
	/* 0087 (ID:1220:64067:64093) <TransactionID> */ 29,99,497,
	/* 0090 (ID:1226:64748:64774) <TransactionID> */ 30,100,498,
	/* 0093 (ID:1628:88540:88561) <ValueID> */ 31,135,643,
	/* 0096 (ID:1632:88561:88592) <ProtocolSupported> */ 32,135,644,
	/* 0099 (ID:1636:88592:88653) <SupportedProtocolParametersValuesLength> */ 33,135,645,
	/* 0102 (ID:1640:88653:88774) <SupportedProtocolParametersValues> */ 34,135,646,
	/* 0105 (ID:1646:89356:89377) <ValueID> */ 35,136,647,
	/* 0108 (ID:1650:89377:89408) <ProtocolSupported> */ 36,136,648,
	/* 0111 (ID:1654:89408:89469) <SupportedProtocolParametersValuesLength> */ 37,136,649,
	/* 0114 (ID:1658:89469:89590) <SupportedProtocolParametersValues> */ 38,136,650,
	/* 0141 (ID:0046:4178:4193) <Route> */ 47,5,213,
	/* 0144 (ID:0050:4193:4214) <Reserved> */ 48,5,214,
	/* 0147 (ID:0056:4812:4838) <TransactionID> */ 49,6,215,
	/* 0150 (ID:0062:5431:5458) <TransactionID> */ 50,7,216,
	/* 0153 (ID:0066:5458:5473) <Route> */ 51,7,217,
	/* 0156 (ID:0070:5473:5494) <Reserved> */ 52,7,218,
	/* 0159 (ID:0076:6102:6128) <TransactionID> */ 53,8,219,
	/* 0162 (ID:0082:6736:6764) <LinkFlowNumber> */ 54,9,220,
	/* 0165 (ID:0086:6764:6779) <Route> */ 55,9,221,
	/* 0168 (ID:0090:6779:6800) <Reserved> */ 56,9,222,
	/* 0171 (ID:0096:7408:7436) <LinkFlowNumber> */ 57,10,223,
	/* 0174 (ID:0100:7436:7451) <Route> */ 58,10,224,
	/* 0177 (ID:0104:7451:7472) <Reserved> */ 59,10,225,
	/* 0180 (ID:0110:8095:8123) <LinkFlowNumber> */ 60,11,226,
	/* 0183 (ID:0114:8123:8138) <Route> */ 61,11,227,
	/* 0186 (ID:0118:8138:8159) <Reserved> */ 62,11,228,
	/* 0189 (ID:0124:8757:8785) <LinkFlowNumber> */ 63,12,229,
	/* 0192 (ID:0128:8785:8800) <Route> */ 64,12,230,
	/* 0195 (ID:0132:8800:8821) <Reserved> */ 65,12,231,
	/* 0198 (ID:0138:9419:9447) <LinkFlowNumber> */ 66,13,232,
	/* 0201 (ID:0142:9447:9462) <Route> */ 67,13,233,
	/* 0204 (ID:0146:9462:9483) <Reserved> */ 68,13,234,
	/* 0207 (ID:0259:13102:13128) <TransactionID> */ 69,20,265,
	/* 0210 (ID:0388:18529:18555) <TransactionID> */ 70,32,299,
	/* 0213 (ID:0414:20129:20155) <TransactionID> */ 71,35,306,
	/* 0216 (ID:0420:20784:20810) <TransactionID> */ 72,36,307,
	/* 0219 (ID:0426:21432:21460) <LinkFlowNumber> */ 73,37,308,
	/* 0222 (ID:0430:21460:21475) <Route> */ 74,37,309,
	/* 0225 (ID:0434:21475:21496) <AckRequired> */ 75,37,310,
	/* 0228 (ID:0438:21496:21511) <Reset> */ 76,37,311,
	/* 0231 (ID:0442:21511:21533) <Reserved> */ 77,37,312,
	/* 0234 (ID:0446:21533:21562) <MessageSequence> */ 78,37,313,
	/* 0237 (ID:0450:21562:21590) <HigherLayerPacket> */ 79,37,314,
	/* 0240 (ID:0456:22227:22242) <Route> */ 80,38,315,
	/* 0243 (ID:0460:22242:22267) <AckSequence> */ 81,38,316,
	/* 0246 (ID:0464:22267:22284) <Reserved> */ 82,38,317,
	/* 0249 (ID:0470:23356:23382) <LocationType> */ 83,39,318,
	/* 0252 (ID:0476:23383:23417) <LocationLength> */ 84,39,319,
	/* 0255 (ID:0482:23427:23503) <LocationValue> */ 85,39,320,
	/* 0258 (ID:0488:24121:24148) <TransactionID> */ 86,40,321,
	/* 0261 (ID:0492:24148:24174) <LocationType> */ 87,40,322,
	/* 0264 (ID:0496:24174:24210) <LocationLength> */ 88,40,323,
	/* 0267 (ID:0500:24210:24286) <LocationValue> */ 89,40,324,
	/* 0270 (ID:0506:24894:24920) <TransactionID> */ 90,41,325,
	/* 0273 (ID:0512:26016:26046) <StorageBLOBType> */ 91,42,326,
	/* 0276 (ID:0516:26046:26085) <StorageBLOBLength> */ 92,42,327,
	/* 0279 (ID:0520:26085:26162) <StorageBLOB> */ 93,42,328,
	/* 0282 (ID:0526:26795:26822) <TransactionID> */ 94,43,329,
	/* 0285 (ID:0530:26822:26852) <StorageBLOBType> */ 95,43,330,
	/* 0288 (ID:0534:26852:26891) <StorageBLOBLength> */ 96,43,331,
	/* 0291 (ID:0538:26891:26968) <StorageBLOB> */ 97,43,332,
	/* 0294 (ID:0544:27591:27617) <TransactionID> */ 98,44,333,
	/* 0297 (ID:0550:29903:29929) <TransactionID> */ 99,45,334,
	/* 0300 (ID:0556:30514:30540) <TransactionID> */ 100,46,335,
	/* 0303 (ID:0562:31180:31206) <TransactionID> */ 101,47,336,
	/* 0306 (ID:0568:31861:31887) <TransactionID> */ 102,48,337,
	/* 0309 (ID:0614:34430:34457) <TransactionID> */ 103,53,350,
	/* 0312 (ID:0618:34457:34472) <Route> */ 104,53,351,
	/* 0315 (ID:0622:34472:34493) <Reserved> */ 105,53,352,
	/* 0318 (ID:0628:35091:35117) <TransactionID> */ 106,54,353,
	/* 0321 (ID:0634:35710:35737) <TransactionID> */ 107,55,354,
	/* 0324 (ID:0638:35737:35752) <Route> */ 108,55,355,
	/* 0327 (ID:0642:35752:35773) <Reserved> */ 109,55,356,
	/* 0330 (ID:0648:36381:36407) <TransactionID> */ 110,56,357,
	/* 0333 (ID:0654:37032:37060) <LinkFlowNumber> */ 111,57,358,
	/* 0336 (ID:0658:37060:37075) <Route> */ 112,57,359,
	/* 0339 (ID:0662:37075:37096) <Reserved> */ 113,57,360,
	/* 0342 (ID:0668:37721:37749) <LinkFlowNumber> */ 114,58,361,
	/* 0345 (ID:0672:37749:37764) <Route> */ 115,58,362,
	/* 0348 (ID:0676:37764:37785) <Reserved> */ 116,58,363,
	/* 0351 (ID:0682:38425:38453) <LinkFlowNumber> */ 117,59,364,
	/* 0354 (ID:0686:38453:38468) <Route> */ 118,59,365,
	/* 0357 (ID:0690:38468:38489) <Reserved> */ 119,59,366,
	/* 0360 (ID:0696:39104:39132) <LinkFlowNumber> */ 120,60,367,
	/* 0363 (ID:0700:39132:39147) <Route> */ 121,60,368,
	/* 0366 (ID:0704:39147:39168) <Reserved> */ 122,60,369,
	/* 0369 (ID:0710:39783:39811) <LinkFlowNumber> */ 123,61,370,
	/* 0372 (ID:0714:39811:39826) <Route> */ 124,61,371,
	/* 0375 (ID:0718:39826:39847) <Reserved> */ 125,61,372,
	/* 0378 (ID:0857:44012:44038) <TransactionID> */ 126,69,410,
	/* 0381 (ID:0986:49541:49567) <TransactionID> */ 127,81,444,
	/* 0384 (ID:1012:51177:51203) <TransactionID> */ 128,84,451,
	/* 0387 (ID:1024:52441:52469) <LinkFlowNumber> */ 129,86,453,
	/* 0390 (ID:1028:52469:52484) <Route> */ 130,86,454,
	/* 0393 (ID:1032:52484:52523) <SARSequenceLength> */ 131,86,455,
	/* 0396 (ID:1036:52523:52601) <LastSARSequence> */ 132,86,456,
	/* 0399 (ID:1232:73777:73798) <ValueID> */ 133,101,499,
	/* 0402 (ID:1236:73798:73835) <QoSProfileCount> */ 134,101,500,
	/* 0405 (ID:1240:73835:73929) <data01> */ 135,101,501,
	/* 0408 (ID:1246:74083:74108) <ProfileType> */ 136,102,505,501,502,
	/* 0413 (ID:1250:74108:74143) <ProfileLength> */ 137,102,506,501,503,
	/* 0418 (ID:1254:74143:74217) <ProfileValue> */ 138,102,507,501,504,
	/* 0423 (ID:1260:74744:74765) <ValueID> */ 139,103,508,
	/* 0426 (ID:1264:74765:74802) <QoSProfileCount> */ 140,103,509,
	/* 0429 (ID:1268:74802:74896) <data01> */ 141,103,510,
	/* 0432 (ID:1274:75050:75075) <ProfileType> */ 142,104,514,510,511,
	/* 0437 (ID:1278:75075:75110) <ProfileLength> */ 143,104,515,510,512,
	/* 0442 (ID:1282:75110:75184) <ProfileValue> */ 144,104,516,510,513,
	/* 0447 (ID:1288:75681:75764) <data01> */ 145,105,517,
	/* 0450 (ID:1294:75859:75880) <ValueID> */ 146,106,523,517,518,
	/* 0455 (ID:1298:75880:75912) <MaxNumLinkFlowsFwd> */ 147,106,524,517,519,
	/* 0460 (ID:1302:75912:75944) <MaxNumLinkFlowsRev> */ 148,106,525,517,520,
	/* 0465 (ID:1306:75944:75982) <MaxActivatedLinkFlowsFwd> */ 149,106,526,517,521,
	/* 0470 (ID:1310:75982:76019) <MaxActivatedLinkFlowsRev> */ 150,106,527,517,522,
	/* 0475 (ID:1316:76515:76601) <data01> */ 151,107,528,
	/* 0478 (ID:1322:76699:76720) <ValueID> */ 152,108,534,528,529,
	/* 0483 (ID:1326:76720:76755) <MaxNumReservationsFwd> */ 153,108,535,528,530,
	/* 0488 (ID:1330:76755:76790) <MaxNumReservationsRev> */ 154,108,536,528,531,
	/* 0493 (ID:1334:76790:76829) <MaxNumOpenReservationsFwd> */ 155,108,537,528,532,
	/* 0498 (ID:1338:76829:76867) <MaxNumOpenReservationsRev> */ 156,108,538,528,533,
	/* 0503 (ID:1344:77366:77452) <data01> */ 157,109,539,
	/* 0506 (ID:1350:77550:77571) <ValueID> */ 158,110,543,539,540,
	/* 0511 (ID:1354:77571:77596) <AbortTimer> */ 159,110,544,539,541,
	/* 0516 (ID:1358:77596:77620) <FlushTimer> */ 160,110,545,539,542,
	/* 0521 (ID:1364:78119:78205) <data01> */ 161,111,546,
	/* 0524 (ID:1370:78303:78324) <ValueID> */ 162,112,550,546,547,
	/* 0529 (ID:1374:78324:78349) <AbortTimer> */ 163,112,551,546,548,
	/* 0534 (ID:1378:78349:78373) <FlushTimer> */ 164,112,552,546,549,
	/* 0539 (ID:1436:81025:81122) <data01> */ 165,119,571,
	/* 0542 (ID:1442:81231:81252) <ValueID> */ 166,120,576,571,572,
	/* 0547 (ID:1446:81252:81277) <ProfileType> */ 167,120,577,571,573,
	/* 0552 (ID:1450:81277:81313) <ProfileLength> */ 168,120,578,571,574,
	/* 0557 (ID:1454:81313:81387) <ProfileValue> */ 169,120,579,571,575,
	/* 0562 (ID:1460:81930:82027) <data01> */ 170,121,580,
	/* 0565 (ID:1466:82136:82157) <ValueID> */ 171,122,585,580,581,
	/* 0570 (ID:1470:82157:82182) <ProfileType> */ 172,122,586,580,582,
	/* 0575 (ID:1474:82182:82218) <ProfileLength> */ 173,122,587,580,583,
	/* 0580 (ID:1478:82218:82292) <ProfileValue> */ 174,122,588,580,584,
	/* 0585 (ID:1484:82838:82936) <data01> */ 175,123,589,
	/* 0588 (ID:1490:83046:83067) <ValueID> */ 176,124,594,589,590,
	/* 0593 (ID:1494:83067:83092) <ProfileType> */ 177,124,595,589,591,
	/* 0598 (ID:1498:83092:83128) <ProfileLength> */ 178,124,596,589,592,
	/* 0603 (ID:1502:83128:83202) <ProfileValue> */ 179,124,597,589,593,
	/* 0608 (ID:1508:83749:83847) <data01> */ 180,125,598,
	/* 0611 (ID:1514:83957:83978) <ValueID> */ 181,126,603,598,599,
	/* 0616 (ID:1518:83978:84003) <ProfileType> */ 182,126,604,598,600,
	/* 0621 (ID:1522:84003:84039) <ProfileLength> */ 183,126,605,598,601,
	/* 0626 (ID:1526:84039:84113) <ProfileValue> */ 184,126,606,598,602,
	/* 0631 (ID:1532:84672:84774) <data01> */ 185,127,607,
	/* 0634 (ID:1538:84888:84909) <ValueID> */ 186,128,612,607,608,
	/* 0639 (ID:1542:84909:84933) <ProtocolID> */ 187,128,613,607,609,
	/* 0644 (ID:1546:84933:84979) <ProtocolParametersLength> */ 188,128,614,607,610,
	/* 0649 (ID:1550:84979:85070) <ProtocolParameters> */ 189,128,615,607,611,
	/* 0654 (ID:1556:85633:85735) <data01> */ 190,129,616,
	/* 0657 (ID:1562:85849:85870) <ValueID> */ 191,130,621,616,617,
	/* 0662 (ID:1566:85870:85894) <ProtocolID> */ 192,130,622,616,618,
	/* 0667 (ID:1570:85894:85940) <ProtocolParametersLength> */ 193,130,623,616,619,
	/* 0672 (ID:1574:85940:86031) <ProtocolParameters> */ 194,130,624,616,620,
	/* 0677 (ID:1580:86597:86700) <data01> */ 195,131,625,
	/* 0680 (ID:1586:86815:86836) <ValueID> */ 196,132,630,625,626,
	/* 0685 (ID:1590:86836:86860) <ProtocolID> */ 197,132,631,625,627,
	/* 0690 (ID:1594:86860:86906) <ProtocolParametersLength> */ 198,132,632,625,628,
	/* 0695 (ID:1598:86906:86997) <ProtocolParameters> */ 199,132,633,625,629,
	/* 0700 (ID:1604:87564:87667) <data01> */ 200,133,634,
	/* 0703 (ID:1610:87782:87803) <ValueID> */ 201,134,639,634,635,
	/* 0708 (ID:1614:87803:87827) <ProtocolID> */ 202,134,640,634,636,
	/* 0713 (ID:1618:87827:87873) <ProtocolParametersLength> */ 203,134,641,634,637,
	/* 0718 (ID:1622:87873:87964) <ProtocolParameters> */ 204,134,642,634,638,
	/* 1073 (ID:0312:15017:15055) <ReservationCount> */ 283,24,280,
	/* 1076 (ID:0316:15055:15115) <data01> */ 284,24,281,
	/* 1079 (ID:0322:15237:15266) <ReservationLabel> */ 285,25,283,281,282,
	/* 1084 (ID:0328:15875:15902) <TransactionID> */ 286,26,284,
	/* 1087 (ID:0332:15902:15940) <ReservationCount> */ 287,26,285,
	/* 1090 (ID:0336:15940:16001) <data01> */ 288,26,286,
	/* 1093 (ID:0342:16124:16153) <ReservationLabel> */ 289,27,288,286,287,
	/* 1098 (ID:0348:16762:16789) <TransactionID> */ 290,28,289,
	/* 1101 (ID:0352:16789:16827) <ReservationCount> */ 291,28,290,
	/* 1104 (ID:0356:16827:16888) <data01> */ 292,28,291,
	/* 1107 (ID:0362:17011:17040) <ReservationLabel> */ 293,29,293,291,292,
	/* 1112 (ID:0368:17644:17671) <TransactionID> */ 294,30,294,
	/* 1115 (ID:0372:17671:17709) <ReservationCount> */ 295,30,295,
	/* 1118 (ID:0376:17709:17769) <data01> */ 296,30,296,
	/* 1121 (ID:0382:17891:17920) <ReservationLabel> */ 297,31,298,296,297,
	/* 1126 (ID:0724:40447:40475) <LinkFlowNumber> */ 298,62,373,
	/* 1129 (ID:0728:40475:40490) <Route> */ 299,62,374,
	/* 1132 (ID:0732:40490:40513) <Reserved1> */ 300,62,375,
	/* 1135 (ID:0736:40513:40552) <SARSequenceLength> */ 301,62,376,
	/* 1138 (ID:0740:40552:40585) <ReportCount> */ 302,62,377,
	/* 1141 (ID:0744:40585:40641) <data01> */ 303,62,378,
	/* 1144 (ID:0767:40986:41006) <DelayedNak> */ 304,63,387,378,382,
	/* 1149 (ID:0771:41006:41043) <LeadingEdgeIncluded> */ 305,63,388,378,383,
	/* 1154 (ID:0775:41043:41115) <LeadingEdge> */ 306,63,389,378,384,
	/* 1159 (ID:0779:41182:41256) <TrailingEdge> */ 307,63,390,378,385,
	/* 1164 (ID:0750:40692:40724) <OtherQNCount> */ 308,62,379,
	/* 1167 (ID:0756:40734:40790) <data02> */ 309,62,380,
	/* 1170 (ID:0785:41320:41392) <LargestSAR> */ 310,64,391,380,386,
	/* 1175 (ID:0760:40841:40906) <VR> */ 311,62,381,
	/* 1178 (ID:0906:45934:45961) <TransactionID> */ 312,73,424,
	/* 1181 (ID:0910:45961:45999) <ReservationCount> */ 313,73,425,
	/* 1184 (ID:0914:45999:46059) <data01> */ 314,73,426,
	/* 1187 (ID:0920:46181:46210) <ReservationLabel> */ 315,74,428,426,427,
	/* 1192 (ID:0926:46836:46863) <TransactionID> */ 316,75,429,
	/* 1195 (ID:0930:46863:46901) <ReservationCount> */ 317,75,430,
	/* 1198 (ID:0934:46901:46962) <data01> */ 318,75,431,
	/* 1201 (ID:0940:47085:47114) <ReservationLabel> */ 319,76,433,431,432,
	/* 1206 (ID:0946:47740:47767) <TransactionID> */ 320,77,434,
	/* 1209 (ID:0950:47767:47805) <ReservationCount> */ 321,77,435,
	/* 1212 (ID:0954:47805:47866) <data01> */ 322,77,436,
	/* 1215 (ID:0960:47989:48018) <ReservationLabel> */ 323,78,438,436,437,
	/* 1220 (ID:0966:48639:48666) <TransactionID> */ 324,79,439,
	/* 1223 (ID:0970:48666:48704) <ReservationCount> */ 325,79,440,
	/* 1226 (ID:0974:48704:48764) <data01> */ 326,79,441,
	/* 1229 (ID:0980:48886:48915) <ReservationLabel> */ 327,80,443,441,442,
	/* 1234 (ID:1043:53173:53201) <LinkFlowNumber> */ 328,87,457,
	/* 1237 (ID:1047:53201:53216) <Route> */ 329,87,458,
	/* 1240 (ID:1051:53216:53239) <Reserved1> */ 330,87,459,
	/* 1243 (ID:1055:53239:53278) <SARSequenceLength> */ 331,87,460,
	/* 1246 (ID:1059:53278:53311) <ReportCount> */ 332,87,461,
	/* 1249 (ID:1063:53311:53358) <data01> */ 333,87,462,
	/* 1252 (ID:1069:53462:53544) <FirstErasedDataUnit> */ 334,88,466,462,463,
	/* 1257 (ID:1073:53544:53616) <WindowLen> */ 335,88,467,462,464,
	/* 1262 (ID:1077:53616:53681) <VR> */ 336,88,468,462,465,
	/* 1267 (ID:1384:78887:78978) <data01> */ 337,113,553,
	/* 1270 (ID:1390:79081:79102) <ValueID> */ 338,114,558,553,554,
	/* 1275 (ID:1394:79102:79140) <ReservationCount> */ 339,114,559,553,555,
	/* 1280 (ID:1398:79140:79239) <data02> */ 340,114,560,553,556,
	/* 1285 (ID:1404:79399:79428) <ReservationLabel> */ 341,115,561,556,557,
	/* 1290 (ID:1410:79947:80038) <data01> */ 342,116,562,
	/* 1293 (ID:1416:80141:80162) <ValueID> */ 343,117,567,562,563,
	/* 1298 (ID:1420:80162:80200) <ReservationCount> */ 344,117,568,562,564,
	/* 1303 (ID:1424:80200:80299) <data02> */ 345,117,569,562,565,
	/* 1308 (ID:1430:80459:80488) <ReservationLabel> */ 346,118,570,565,566,
	/* 1313 (ID:1664:90170:90276) <data01> */ 347,137,651,
	/* 1316 (ID:1670:90394:90415) <ValueID> */ 348,138,656,651,652,
	/* 1321 (ID:1674:90415:90451) <BCMCSFlowCount> */ 349,138,657,651,653,
	/* 1326 (ID:1678:90451:90565) <data02> */ 350,138,658,651,654,
	/* 1331 (ID:1684:90738:90763) <BCMCSFlowID> */ 351,139,659,654,655,
	/* 1408 (ID:0006:2297:2362) <data01> */ 368,1,201,
	/* 1411 (ID:0012:2440:2467) <AttributeLength> */ 369,2,204,201,202,
	/* 1416 (ID:0016:2467:2581) <AttributeRecord> */ 370,2,205,201,203,
	/* 1421 (ID:0022:3246:3273) <TransactionID> */ 371,3,206,
	/* 1424 (ID:0026:3273:3339) <data01> */ 372,3,207,
	/* 1427 (ID:0032:3418:3445) <AttributeLength> */ 373,4,210,207,208,
	/* 1432 (ID:0036:3445:3568) <AttributeRecord> */ 374,4,211,207,209,
	/* 1437 (ID:0152:10021:10049) <LinkFlowNumber> */ 375,14,235,
	/* 1440 (ID:0156:10049:10064) <Route> */ 376,14,236,
	/* 1443 (ID:0160:10064:10087) <Reserved1> */ 377,14,237,
	/* 1446 (ID:0164:10087:10123) <SequenceLength> */ 378,14,238,
	/* 1449 (ID:0168:10123:10156) <ReportCount> */ 379,14,239,
	/* 1452 (ID:0172:10156:10203) <data01> */ 380,14,240,
	/* 1455 (ID:0178:10307:10386) <FirstErasedDataUnit> */ 381,15,244,240,241,
	/* 1460 (ID:0182:10386:10455) <WindowLen> */ 382,15,245,240,242,
	/* 1465 (ID:0186:10455:10517) <VR> */ 383,15,246,240,243,
	/* 1470 (ID:0193:11156:11183) <TransactionID> */ 384,16,247,
	/* 1473 (ID:0197:11183:11221) <ReservationCount> */ 385,16,248,
	/* 1476 (ID:0201:11221:11285) <data01> */ 386,16,249,
	/* 1479 (ID:0207:11411:11425) <Link> */ 387,17,254,249,250,
	/* 1484 (ID:0211:11425:11455) <ReservationLabel> */ 388,17,255,249,251,
	/* 1489 (ID:0217:11456:11483) <EmergencyIndication> */ 389,17,256,249,252,
	/* 1494 (ID:0225:11494:11523) <ReservationQueuingReq> */ 390,17,257,249,253,
	/* 1499 (ID:0234:12177:12204) <TransactionID> */ 391,18,258,
	/* 1502 (ID:0238:12204:12242) <ReservationCount> */ 392,18,259,
	/* 1505 (ID:0242:12242:12307) <data01> */ 393,18,260,
	/* 1508 (ID:0248:12434:12448) <Link> */ 394,19,263,260,261,
	/* 1513 (ID:0252:12448:12478) <ReservationLabel> */ 395,19,264,260,262,
	/* 1518 (ID:0394:19189:19216) <TransactionID> */ 396,33,300,
	/* 1521 (ID:0398:19216:19281) <data01> */ 397,33,301,
	/* 1524 (ID:0404:19359:19386) <AttributeLength> */ 398,34,304,301,302,
	/* 1529 (ID:0408:19386:19500) <AttributeRecord> */ 399,34,305,301,303,
	/* 1534 (ID:0574:32549:32576) <TransactionID> */ 400,49,338,
	/* 1537 (ID:0578:32576:32641) <data01> */ 401,49,339,
	/* 1540 (ID:0584:32719:32746) <AttributeLength> */ 402,50,342,339,340,
	/* 1545 (ID:0588:32746:32862) <AttributeRecord> */ 403,50,343,339,341,
	/* 1550 (ID:0594:33529:33556) <TransactionID> */ 404,51,344,
	/* 1553 (ID:0598:33556:33622) <data01> */ 405,51,345,
	/* 1556 (ID:0604:33701:33728) <AttributeLength> */ 406,52,348,345,346,
	/* 1561 (ID:0608:33728:33847) <AttributeRecord> */ 407,52,349,345,347,
	/* 1566 (ID:0791:42032:42059) <TransactionID> */ 408,65,392,
	/* 1569 (ID:0795:42059:42097) <ReservationCount> */ 409,65,393,
	/* 1572 (ID:0799:42097:42161) <data01> */ 410,65,394,
	/* 1575 (ID:0805:42287:42301) <Link> */ 411,66,399,394,395,
	/* 1580 (ID:0809:42301:42331) <ReservationLabel> */ 412,66,400,394,396,
	/* 1585 (ID:0815:42332:42359) <EmergencyIndication> */ 413,66,401,394,397,
	/* 1590 (ID:0823:42370:42399) <ReservationQueuingReq> */ 414,66,402,394,398,
	/* 1595 (ID:0832:43070:43097) <TransactionID> */ 415,67,403,
	/* 1598 (ID:0836:43097:43135) <ReservationCount> */ 416,67,404,
	/* 1601 (ID:0840:43135:43200) <data01> */ 417,67,405,
	/* 1604 (ID:0846:43327:43341) <Link> */ 418,68,408,405,406,
	/* 1609 (ID:0850:43341:43371) <ReservationLabel> */ 419,68,409,405,407,
	/* 1614 (ID:0992:50218:50245) <TransactionID> */ 420,82,445,
	/* 1617 (ID:0996:50245:50310) <data01> */ 421,82,446,
	/* 1620 (ID:1002:50388:50415) <AttributeLength> */ 422,83,449,446,447,
	/* 1625 (ID:1006:50415:50531) <AttributeRecord> */ 423,83,450,446,448,
	/* 1630 (ID:1690:91351:91460) <data01> */ 424,140,660,
	/* 1633 (ID:1696:91581:91602) <ValueID> */ 425,141,669,660,661,
	/* 1638 (ID:1700:91602:91636) <ProgramCount> */ 426,141,670,660,662,
	/* 1643 (ID:1704:91636:91753) <data02> */ 427,141,671,660,663,
	/* 1648 (ID:1710:91927:91959) <ProgramIDLSBLength> */ 428,142,672,663,664,
	/* 1653 (ID:1714:91959:91987) <ProgramIDLSBs> */ 429,142,673,663,665,
	/* 1658 (ID:1718:91987:92031) <FlowDiscriminatorCount> */ 430,142,674,663,666,
	/* 1663 (ID:1722:92031:92155) <data03> */ 431,142,675,663,667,
	/* 1668 (ID:1728:92346:92376) <FlowDiscriminator> */ 432,143,676,667,668,
	/* 1719 (ID:0269:13764:13802) <ReservationCount> */ 443,21,267,
	/* 1722 (ID:0273:13802:13863) <data01> */ 444,21,268,
	/* 1725 (ID:0279:13986:14009) <AllowableLink> */ 445,22,274,268,269,
	/* 1730 (ID:0283:14009:14048) <AllowableReservationLabel> */ 446,22,275,268,270,
	/* 1735 (ID:0287:14048:14116) <data02> */ 447,22,276,268,271,
	/* 1740 (ID:0295:14247:14277) <RejectCode> */ 448,23,277,271,272,
	/* 1745 (ID:0301:14287:14314) <PendingDuration> */ 449,23,278,271,273,
	/* 1750 (ID:0863:44664:44691) <TransactionID> */ 450,70,411,
	/* 1753 (ID:0867:44691:44729) <ReservationCount> */ 451,70,412,
	/* 1756 (ID:0871:44729:44790) <data01> */ 452,70,413,
	/* 1759 (ID:0877:44913:44936) <AllowableLink> */ 453,71,419,413,414,
	/* 1764 (ID:0881:44936:44975) <AllowableReservationLabel> */ 454,71,420,413,415,
	/* 1769 (ID:0885:44975:45043) <data02> */ 455,71,421,413,416,
	/* 1774 (ID:0893:45174:45204) <RejectCode> */ 456,72,422,416,417,
	/* 1779 (ID:0899:45214:45241) <PendingDuration> */ 457,72,423,416,418

#ifndef NDEBUG
	, -1, -1 /* Used in conjunction with an assert */
#endif
};

/* CUSTOM EXPRESSION 0 (ID:0485:23443:23447, ID:0503:24226:24230, ID:1143:56330:56334, ID:1161:57113:57117) */
unsigned ED_EXLONG Program_cs0063_expr0000 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* LocationLength */) * 8);
}
/* CUSTOM EXPRESSION 1 (ID:0523:26099:26103, ID:0541:26905:26909, ID:1181:58986:58990, ID:1199:59792:59796) */
unsigned ED_EXLONG Program_cs0063_expr0001 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* StorageBLOBLength */) * 8);
}
unsigned ED_EXLONG Program_cs0063_expr0002 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* SupportedProtocolParametersValuesLength */) * 8);
}
unsigned ED_EXLONG Program_cs0063_expr0003 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)((8 - (CURPOS & 7)) & 7);
}
unsigned ED_EXLONG Program_cs0063_expr0004 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(((8 - ((CURPOS - 0x00) & 7)) & 7));
}
unsigned ED_EXLONG Program_cs0063_expr0005 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(
			((8 - ((CURPOS - 0x00) & 7)) & 7) < (Context->FinalOffset - CURPOS)
			?
			((8 - ((CURPOS - 0x00) & 7)) & 7)
			:
			(Context->FinalOffset - CURPOS)
		);
}
/* CUSTOM EXPRESSION 6 (ID:1039:52541:52545) */
unsigned ED_EXLONG Program_cs0063_expr0006 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* SARSequenceLength */));
}
unsigned ED_EXLONG Program_cs0063_expr0007 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* QoSProfileCount */));
}
unsigned ED_EXLONG Program_cs0063_expr0008 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (2 /* ProfileLength */) * 8);
}
unsigned ED_EXLONG Program_cs0063_expr0009 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* ProfileLength */) * 8);
}
unsigned ED_EXLONG Program_cs0063_expr0010 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* ProtocolParametersLength */) * 8);
}
unsigned ED_EXLONG Program_cs0063_expr0011 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* ReservationCount */));
}
/* CUSTOM EXPRESSION 12 (ID:0172:10156:10203, ID:0744:40585:40641, ID:1063:53311:53358) */
unsigned ED_EXLONG Program_cs0063_expr0012 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* ReportCount */));
}
/* CUSTOM EXPRESSION 13 (ID:0775:41043:41115) */
unsigned ED_EXLONG Program_cs0063_expr0013 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)((TAGZ (4 /* LeadingEdgeIncluded */) != 0 ? 1 : 0));
}
/* CUSTOM EXPRESSION 14 (ID:0763:40846:40850, ID:0778:41057:41061, ID:0782:41197:41201, ID:0788:41333:41337, ID:1072:53484:53488, ID:1076:53556:53560, ID:1080:53621:53625) */
unsigned ED_EXLONG Program_cs0063_expr0014 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (2 /* SARSequenceLength */));
}
/* CUSTOM EXPRESSION 15 (ID:0756:40734:40790) */
unsigned ED_EXLONG Program_cs0063_expr0015 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (3 /* OtherQNCount */));
}
unsigned ED_EXLONG Program_cs0063_expr0016 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* BCMCSFlowCount */));
}
/* CUSTOM EXPRESSION 17 (ID:0019:2541:2545) */
unsigned ED_EXLONG Program_cs0063_expr0017 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAG(100)*8);
}
/* CUSTOM EXPRESSION 18 (ID:0039:3528:3532) */
unsigned ED_EXLONG Program_cs0063_expr0018 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAG(101)*8);
}
/* CUSTOM EXPRESSION 19 (ID:0181:10329:10333, ID:0185:10398:10402, ID:0189:10460:10464) */
unsigned ED_EXLONG Program_cs0063_expr0019 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (2 /* SequenceLength */));
}
/* CUSTOM EXPRESSION 20 (ID:0411:19460:19464) */
unsigned ED_EXLONG Program_cs0063_expr0020 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAG(102)*8);
}
/* CUSTOM EXPRESSION 21 (ID:0591:32822:32826) */
unsigned ED_EXLONG Program_cs0063_expr0021 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAG(103)*8);
}
/* CUSTOM EXPRESSION 22 (ID:0611:33813:33817) */
unsigned ED_EXLONG Program_cs0063_expr0022 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAG(104)*8);
}
/* CUSTOM EXPRESSION 23 (ID:1009:50491:50495) */
unsigned ED_EXLONG Program_cs0063_expr0023 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAG(105)*8);
}
unsigned ED_EXLONG Program_cs0063_expr0024 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (1 /* ProgramCount */));
}
unsigned ED_EXLONG Program_cs0063_expr0025 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)(TAGZ (2 /* FlowDiscriminatorCount */));
}
/* CUSTOM EXPRESSION 26 (ID:0301:14287:14314, ID:0899:45214:45241) */
unsigned ED_EXLONG Program_cs0063_expr0026 (TCSN1CContext* Context) {
	ED_WARNING_REMOVER(Context);
	return (unsigned ED_EXLONG)((TAGZ (2 /* RejectCode */)==1 ? 1 : 0));
}
static const unsigned ED_EXLONG (*const Program_cs0063_ExpressionMap[]) (TCSN1CContext*) = {
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0000,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0001,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0002,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0003,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0004,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0005,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0006,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0007,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0008,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0009,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0010,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0011,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0012,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0013,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0014,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0015,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0016,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0017,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0018,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0019,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0020,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0021,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0022,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0023,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0024,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0025,
	(const unsigned ED_EXLONG (*const) (TCSN1CContext*))Program_cs0063_expr0026};
static const void (*const Program_cs0063_FunctionMap[]) (TCSN1CContext* ED_EXTRAPARAMS_DECL) = {
	NULL
};
/* PROGRAM CODE FOR PROGRAM 'Program_cs0063' */
static const unsigned char Program_cs0063_ProgramCode [] = {

	/*-----------------------------------------------------------------
		DEFINITION 'bit'
		DEFINITION FIELD-ID: 189  COMPLEXITY: 5
		SOURCE: ./csn1lib.src, 5
	-----------------------------------------------------------------*/
};

/* DEFINITION FOR PROGRAM 'Program_cs0063' */
TCSN1CProgram Program_cs0063_Program = {
	/* ProgramCode.......*/ Program_cs0063_ProgramCode,
	/* ProgramLength.....*/ 3566,
	/* FieldIdPairSet....*/ Program_cs0063_FieldIdPairSet,
#ifdef CSN1C_LABEL_NAMES
	/* LabelNames........*/ Program_cs0063_Labels,
#endif
	/* FunctionMap.......*/ (void (*const *) (void* ED_EXTRAPARAMS_DECL))Program_cs0063_FunctionMap,
	/* ExpressionMap.....*/ (unsigned ED_EXLONG (*const *) (void*))Program_cs0063_ExpressionMap,
#ifdef CSN1C_ENABLE_LABEL_SIZE
	/* LabelSizes........*/ Program_cs0063_LabelSize,
#endif
	/* FirstErrorLabelId.*/ 462
};

