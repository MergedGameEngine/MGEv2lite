///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)	v2	Copyright 2018
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//
//		Variant container
//		 versatile container
//		 
//
///////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		widen direction
//        int ->  long(64) -> double -> string -> object array -> hashtable -> error
//       uint -> ulong(64) -> double -> string -> object array -> hashtable -> error
//                   float -> double -> string -> object array -> hashtable -> error
//                           wstring -> string -> object array -> hashtable -> error
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include "stdio.h"
#include "string.h"
#include "Type.h"
#include "Base.h"
#include "CRC32.h"

MGE2Variant::MGE2Variant() {
	status = _VAR_NULL_;
	memset(&VarPrimeType, 0, sizeof(_VAR_PRIME_TYPE_));
	___this = this;
}



MGE2Variant::MGE2Variant(const int _ivalue) {
	status = _VAR_PRIME_INT_;
	VarPrimeType._iValue = _ivalue;
	___this = this;
}


MGE2Variant::MGE2Variant(const unsigned int _ivalue) {
	status = _VAR_PRIME_UINT_;
	VarPrimeType._uiValue = _ivalue;
	___this = this;
}


MGE2Variant::MGE2Variant(const float _fvalue) {
	status = _VAR_PRIME_FLOAT_;
	VarPrimeType._fValue = _fvalue;
	___this = this;
}


MGE2Variant::MGE2Variant(const double _dvalue) {
	status = _VAR_PRIME_DOUBLE_;
	VarPrimeType._dValue = _dvalue;
	___this = this;
}




MGE2Variant::MGE2Variant(const _var_long _lvalue) {
	status = _VAR_PRIME_LONG_;
	VarPrimeType._lValue = _lvalue;
	___this = this;
}


MGE2Variant::MGE2Variant(const _var_ulong _lvalue) {
	status = _VAR_PRIME_ULONG_;
	VarPrimeType._ulValue = _lvalue;
	___this = this;
}


MGE2Variant::MGE2Variant(const wchar_t* wstr) {
#ifdef WIN32
	status = _VAR_TSTRING_;
	VarPrimeType._VarObject = new MGETString(wstr);
#else
	status = _VAR_WSTRING_;
	VarPrimeType._VarObject = new MGEWString(wstr);
#endif
	___this = this;
}


MGE2Variant::MGE2Variant(const MGEWString &src) {
	status = _VAR_WSTRING_;
	MGEWString *desc = new MGEWString();
	*desc = src;
	VarPrimeType._VarObject = desc;
	___this = this;
}

MGE2Variant::MGE2Variant(const MGETString &src) {
	status = _VAR_TSTRING_;
	MGETString *desc = new MGETString();
	*desc = src;
	VarPrimeType._VarObject = desc;
	___this = this;
}


MGE2Variant::MGE2Variant(const char* str) {
	status = _VAR_STRING_;
	VarPrimeType._VarObject = new MGEString(str);
	___this = this;
}


MGE2Variant::MGE2Variant(const MGEString &src) {
	status = _VAR_STRING_;
	MGEString *desc = new MGEString();
	*desc = src;
	VarPrimeType._VarObject = desc;
	___this = this;
}

//unsafe
MGE2Variant::MGE2Variant(const MGE2Variant *_ref) {
	status = _VAR_REFERENCE_;
	VarPrimeType._VarObject = (MGEObject*)_ref;
	___this = this;
}


int MGE2Variant::DivOpr(MGE2Variant& desc, MGE2Variant& op1, MGE2Variant& op2) {
	switch ( op1.status & _VAR_TYPE_STATUS_MASK_ ) {
		case _VAR_PRIME_INT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((int)(op1.VarPrimeType._iValue / op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._iValue / (_var_long)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue / (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue / op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._iValue / op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue / op2.VarPrimeType._dValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_UINT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._uiValue / (_var_long)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((unsigned int)(op1.VarPrimeType._uiValue / op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue / (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue / op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._uiValue / op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue / op2.VarPrimeType._dValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_FLOAT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue / (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue / (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((float)(op1.VarPrimeType._fValue / op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue / op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue / (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue / (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;

		case _VAR_PRIME_DOUBLE_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue / (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue / (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue / (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue / (double)op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue / (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue / (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_LONG_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue / (_var_long)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue / (_var_long)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue / (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue / op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue / op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue / (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_ULONG_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue / (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue / (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue / (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue / op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue / (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((_var_ulong)(op1.VarPrimeType._ulValue / op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		default :
			{
				// error
				desc.Error();
				return -1;
			}
			break;
	}
	return 0;
}

int MGE2Variant::MulOpr(MGE2Variant& desc, MGE2Variant& op1, MGE2Variant& op2) {
	switch ( op1.status & _VAR_TYPE_STATUS_MASK_ ) {
		case _VAR_PRIME_INT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((int)(op1.VarPrimeType._iValue * op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._iValue * (_var_long)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue * (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue * op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._iValue * op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue * op2.VarPrimeType._dValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_UINT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._uiValue * (_var_long)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((unsigned int)(op1.VarPrimeType._uiValue * op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue * (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue * op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._uiValue * op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue * op2.VarPrimeType._dValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_FLOAT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue * (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue * (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((float)(op1.VarPrimeType._fValue * op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue * op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue * (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue * (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;

		case _VAR_PRIME_DOUBLE_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue * (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue * (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue * (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue * (double)op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue * (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue * (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_LONG_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue * (_var_long)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue * (_var_long)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue * (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue * op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue * op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue * (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_ULONG_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue * (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue * (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue * (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue * op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue * (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((_var_ulong)(op1.VarPrimeType._ulValue * op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		default :
			{
				// error
				desc.Error();
				return -1;
			}
			break;
	}
	return 0;
}

int MGE2Variant::SubOpr(MGE2Variant& desc, MGE2Variant& op1, MGE2Variant& op2) {
	switch ( op1.status & _VAR_TYPE_STATUS_MASK_ ) {
		case _VAR_PRIME_INT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((int)(op1.VarPrimeType._iValue - op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._iValue - (_var_long)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue - (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue - op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._iValue - op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue - op2.VarPrimeType._dValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_UINT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._uiValue - (_var_long)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((unsigned int)(op1.VarPrimeType._uiValue - op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue - (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue - op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._uiValue - op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue - op2.VarPrimeType._dValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_FLOAT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue - (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue - (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((float)(op1.VarPrimeType._fValue - op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue - op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue - (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue - (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;

		case _VAR_PRIME_DOUBLE_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue - (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue - (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue - (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue - (double)op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue - (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue - (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_LONG_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue - (_var_long)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue - (_var_long)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue - (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue - op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue - op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue - (double)op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_ULONG_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue - (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue - (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue - (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue - op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue - (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((_var_ulong)(op1.VarPrimeType._ulValue - op2.VarPrimeType._ulValue));
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		default :
			{
				// error
				desc.Error();
				return -1;
			}
			break;
	}
	return 0;
}

int MGE2Variant::AddOpr(MGE2Variant& desc, MGE2Variant& op1, MGE2Variant& op2) {
	switch ( op1.status & _VAR_TYPE_STATUS_MASK_ ) {
		case _VAR_NULL_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant();
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant(op2.VarPrimeType._iValue);
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant(op2.VarPrimeType._uiValue);
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant(op2.VarPrimeType._fValue);
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant(op2.VarPrimeType._dValue);
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant(op2.VarPrimeType._lValue);
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant(op2.VarPrimeType._ulValue);
						}
						break;
					case _VAR_WSTRING_ :
						{
							desc = MGE2Variant(*(MGEWString*)(op2.VarPrimeType._VarObject));
						}
						break;

					case _VAR_TSTRING_ :
						{
							desc = MGE2Variant(*(MGETString*)(op2.VarPrimeType._VarObject));
						}
						break;
					case _VAR_STRING_ :
						{
							desc = MGE2Variant(*(MGEString*)(op2.VarPrimeType._VarObject));
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							desc.CreateHashtable();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_INT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant(op1.VarPrimeType._iValue);
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((int)(op1.VarPrimeType._iValue + op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._iValue + (_var_long)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue + (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue + op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._iValue + op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._iValue + op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_WSTRING_ :
						{
							MGEWString _wstr0 = MGEWString("%d", op1.VarPrimeType._iValue) + (*(MGEWString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_wstr0);
						}
						break;

					case _VAR_TSTRING_ :
						{
							MGETString _wstr0 = MGETString("%d", op1.VarPrimeType._iValue) + (*(MGETString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _str0 = MGEString("%d", op1.VarPrimeType._iValue) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op1.VarPrimeType._iValue);

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str(op1.VarPrimeType._iValue);
							desc.CreateHashtable();
							desc[_str] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_UINT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant(op1.VarPrimeType._uiValue);
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._uiValue + (_var_long)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((unsigned int)(op1.VarPrimeType._uiValue + op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue + (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue + op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)((_var_long)op1.VarPrimeType._uiValue + op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._uiValue + op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_WSTRING_ :
						{
							MGEWString _wstr0 = MGEWString("%u", op1.VarPrimeType._uiValue) + (*(MGEWString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_wstr0);
						}
						break;

					case _VAR_TSTRING_ :
						{
							MGETString _wstr0 = MGETString("%u", op1.VarPrimeType._uiValue) + (*(MGETString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _str0 = MGEString("%u", op1.VarPrimeType._uiValue) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op1.VarPrimeType._uiValue);

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str(op1.VarPrimeType._uiValue);
							desc.CreateHashtable();
							desc[_str] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_FLOAT_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant(op1.VarPrimeType._fValue);
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue + (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue + (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((float)(op1.VarPrimeType._fValue + op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue + op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue + (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._fValue + (double)op2.VarPrimeType._ulValue));
						}
						break;
					case _VAR_WSTRING_ :
						{
							MGEWString _str0 = MGEWString("%f", op1.VarPrimeType._fValue) + (*(MGEWString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;

					case _VAR_TSTRING_ :
						{
							MGETString _str0 = MGETString("%f", op1.VarPrimeType._fValue) + (*(MGETString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _str0 = MGEString("%f", op1.VarPrimeType._fValue) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op1.VarPrimeType._fValue);

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str(op1.VarPrimeType._fValue);
							desc.CreateHashtable();
							desc[_str] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;

		case _VAR_PRIME_DOUBLE_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant(op1.VarPrimeType._fValue);
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue + (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue + (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue + (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue + (double)op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue + (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)(op1.VarPrimeType._dValue + (double)op2.VarPrimeType._ulValue));
						}
						break;
					case _VAR_WSTRING_ :
						{
							MGEWString _str0 = MGEWString("%f", op1.VarPrimeType._dValue) + (*(MGEWString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;

					case _VAR_TSTRING_ :
						{
							MGETString _str0 = MGETString("%f", op1.VarPrimeType._dValue) + (*(MGETString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _str0 = MGEString("%f", op1.VarPrimeType._dValue) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op1.VarPrimeType._dValue);

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str(op1.VarPrimeType._dValue);
							desc.CreateHashtable();
							desc[_str] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_LONG_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant(op1.VarPrimeType._lValue);
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue + (_var_long)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue + (_var_long)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue + (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue + op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((_var_long)(op1.VarPrimeType._lValue + op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._lValue + (double)op2.VarPrimeType._ulValue));
						}
						break;
					case _VAR_WSTRING_ :
						{
							MGEWString _str0 = MGEWString("%ld", op1.VarPrimeType._lValue) + (*(MGEWString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;

					case _VAR_TSTRING_ :
						{
							MGETString _str0 = MGETString("%ld", op1.VarPrimeType._lValue) + (*(MGETString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _str0 = MGEString("%ld", op1.VarPrimeType._lValue) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op1.VarPrimeType._lValue);

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str(op1.VarPrimeType._lValue);
							desc.CreateHashtable();
							desc[_str] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_PRIME_ULONG_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant(op1.VarPrimeType._ulValue);
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue + (double)op2.VarPrimeType._iValue));
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue + (double)op2.VarPrimeType._uiValue));
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue + (double)op2.VarPrimeType._fValue));
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue + op2.VarPrimeType._dValue));
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc = MGE2Variant((double)((double)op1.VarPrimeType._ulValue + (double)op2.VarPrimeType._lValue));
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc = MGE2Variant((_var_ulong)(op1.VarPrimeType._ulValue + op2.VarPrimeType._ulValue));
						}
						break;
					case _VAR_WSTRING_ :
						{
							MGEWString _str0 = MGEWString("%lu", op1.VarPrimeType._ulValue) + (*(MGEWString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;

					case _VAR_TSTRING_ :
						{
							MGETString _str0 = MGETString("%lu", op1.VarPrimeType._ulValue) + (*(MGETString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _str0 = MGEString("%lu", op1.VarPrimeType._ulValue) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op1.VarPrimeType._ulValue);

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str(op1.VarPrimeType._ulValue);
							desc.CreateHashtable();
							desc[_str] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_WSTRING_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant((*(MGEWString*)(op2.VarPrimeType._VarObject)));
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							MGEWString _wstr0 = (*(MGEWString*)(op1.VarPrimeType._VarObject)) + MGEWString("%d", op2.VarPrimeType._iValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							MGEWString _wstr0 = (*(MGEWString*)(op1.VarPrimeType._VarObject)) + MGEWString("%u", op2.VarPrimeType._uiValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							MGEWString _wstr0 = (*(MGEWString*)(op1.VarPrimeType._VarObject)) + MGEWString("%f", op2.VarPrimeType._fValue);
							desc.CopyfromString(_wstr0);
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							MGEWString _wstr0 = (*(MGEWString*)(op1.VarPrimeType._VarObject)) + MGEWString("%f", op2.VarPrimeType._dValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							MGEWString _wstr0 = (*(MGEWString*)(op1.VarPrimeType._VarObject)) + MGEWString("%ld", op2.VarPrimeType._lValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							MGEWString _wstr0 = (*(MGEWString*)(op1.VarPrimeType._VarObject)) + MGEWString("%lu", op2.VarPrimeType._ulValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_WSTRING_ :
						{
							MGEWString _wstr0 = (*(MGEWString*)(op1.VarPrimeType._VarObject)) + (*(MGEWString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_wstr0);
						}
						break;

					case _VAR_TSTRING_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _str0 = MGEString("%ls", (*(MGEWString*)(op1.VarPrimeType._VarObject)).GetBuffer()) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant((*(MGEWString*)(op1.VarPrimeType._VarObject)));

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str0 = MGEString("%ls", (*(MGEWString*)(op1.VarPrimeType._VarObject)).GetBuffer());
							desc.CreateHashtable();
							desc[_str0] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;

		case _VAR_TSTRING_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant((*(MGETString*)(op2.VarPrimeType._VarObject)));
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							MGETString _wstr0 = (*(MGETString*)(op1.VarPrimeType._VarObject)) + MGETString("%d", op2.VarPrimeType._iValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							MGETString _wstr0 = (*(MGETString*)(op1.VarPrimeType._VarObject)) + MGETString("%u", op2.VarPrimeType._uiValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							MGETString _wstr0 = (*(MGETString*)(op1.VarPrimeType._VarObject)) + MGETString("%f", op2.VarPrimeType._fValue);
							desc.CopyfromString(_wstr0);
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							MGETString _wstr0 = (*(MGETString*)(op1.VarPrimeType._VarObject)) + MGETString("%f", op2.VarPrimeType._dValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							MGETString _wstr0 = (*(MGETString*)(op1.VarPrimeType._VarObject)) + MGETString("%ld", op2.VarPrimeType._lValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							MGETString _wstr0 = (*(MGETString*)(op1.VarPrimeType._VarObject)) + MGETString("%lu", op2.VarPrimeType._ulValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_WSTRING_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;

					case _VAR_TSTRING_ :
						{
							MGETString _wstr0 = (*(MGETString*)(op1.VarPrimeType._VarObject)) + (*(MGETString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _str0 = MGEString("%ls", (*(MGETString*)(op1.VarPrimeType._VarObject)).GetBuffer()) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_str0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant((*(MGETString*)(op1.VarPrimeType._VarObject)));

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str0 = MGEString("%ls", (*(MGETString*)(op1.VarPrimeType._VarObject)).GetBuffer());
							desc.CreateHashtable();
							desc[_str0] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_STRING_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc = MGE2Variant((*(MGEString*)(op1.VarPrimeType._VarObject)));
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + MGEString("%d", op2.VarPrimeType._iValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + MGEString("%u", op2.VarPrimeType._uiValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + MGEString("%f", op2.VarPrimeType._fValue);
							desc.CopyfromString(_wstr0);
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + MGEString("%f", op2.VarPrimeType._dValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + MGEString("%ld", op2.VarPrimeType._lValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + MGEString("%lu", op2.VarPrimeType._ulValue);
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_WSTRING_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + MGEString("%ls", (*(MGEWString*)(op2.VarPrimeType._VarObject)).GetBuffer());
							desc.CopyfromString(_wstr0);
						}
						break;

					case _VAR_TSTRING_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + MGEString("%ls", (*(MGETString*)(op2.VarPrimeType._VarObject)).GetBuffer());
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_STRING_ :
						{
							MGEString _wstr0 = (*(MGEString*)(op1.VarPrimeType._VarObject)) + (*(MGEString*)(op2.VarPrimeType._VarObject));
							desc.CopyfromString(_wstr0);
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							desc.CreateArray();

							MGEObjectArray *___array = (MGEObjectArray *)op2.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant((*(MGEString*)(op1.VarPrimeType._VarObject)));

							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							MGEString _str0 = (*(MGEString*)(op1.VarPrimeType._VarObject));
							desc.CreateHashtable();
							desc[_str0] = MGE2Variant();
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_REFERENCE_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_WSTRING_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;

					case _VAR_TSTRING_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_STRING_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		case _VAR_OBJECT_ARRAY_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op2.VarPrimeType._iValue);
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op2.VarPrimeType._uiValue);
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op2.VarPrimeType._fValue);
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op2.VarPrimeType._dValue);
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op2.VarPrimeType._lValue);
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant(op2.VarPrimeType._ulValue);
						}
						break;
					case _VAR_WSTRING_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant((*(MGEWString*)(op2.VarPrimeType._VarObject)));
						}
						break;

					case _VAR_TSTRING_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant((*(MGETString*)(op2.VarPrimeType._VarObject)));
						}
						break;
					case _VAR_STRING_ :
						{
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							MGEObjectArray *___array = (MGEObjectArray *)desc.VarPrimeType._VarObject;
							unsigned int _len = ___array->GetLength();
							___array->Resize(_len + 1);
							(*___array)[_len] = new MGE2Variant((*(MGEString*)(op2.VarPrimeType._VarObject)));
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							// Merge 2 array objects
							desc.CreateArray();
							desc.CopyObjectArrayfromObjectArray(op1);
							desc.CopyObjectArrayfromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							// Merge 2 objects
							desc.CreateHashtable();
							desc.CopyHashtablefromObjectArray(op1);
							desc.CopyHashtablefromHashtable(op2);
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;

		case _VAR_HASHTABLE_ :
			{
				switch ( op2.status & _VAR_TYPE_STATUS_MASK_ ) {
					case _VAR_NULL_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
						}
						break;
					case _VAR_PRIME_INT_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							MGEString _str(op2.VarPrimeType._iValue);
							desc[_str] = MGE2Variant();
						}
						break;
					case _VAR_PRIME_UINT_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							MGEString _str(op2.VarPrimeType._uiValue);
							desc[_str] = MGE2Variant();
						}
						break;
					case _VAR_PRIME_FLOAT_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							MGEString _str(op2.VarPrimeType._fValue);
							desc[_str] = MGE2Variant();
						}
						break;

					case _VAR_PRIME_DOUBLE_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							MGEString _str(op2.VarPrimeType._dValue);
							desc[_str] = MGE2Variant();
						}
						break;
					case _VAR_PRIME_LONG_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							MGEString _str(op2.VarPrimeType._lValue);
							desc[_str] = MGE2Variant();
						}
						break;
					case _VAR_PRIME_ULONG_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							MGEString _str(op2.VarPrimeType._ulValue);
							desc[_str] = MGE2Variant();
						}
						break;
					case _VAR_WSTRING_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							MGEString _str("%ls",(*(MGEWString*)(op2.VarPrimeType._VarObject)).GetBuffer());
							desc[_str] = MGE2Variant();
						}
						break;

					case _VAR_TSTRING_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							MGEString _str("%ls",(*(MGETString*)(op2.VarPrimeType._VarObject)).GetBuffer());
							desc[_str] = MGE2Variant();
						}
						break;
					case _VAR_STRING_ :
						{
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							desc[(*(MGEString*)(op2.VarPrimeType._VarObject))] = MGE2Variant();
						}
						break;
					case _VAR_REFERENCE_ :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
					case _VAR_OBJECT_ARRAY_ :
						{
							// Merge 2 objects
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							desc.CopyHashtablefromObjectArray(op2);
						}
						break;

					case _VAR_HASHTABLE_ :
						{
							// Merge 2 objects
							desc.CreateHashtable();
							desc.CopyHashtablefromHashtable(op1);
							desc.CopyHashtablefromHashtable(op2);
						}
						break;
					default :
						{
							// error
							desc.Error();
							return -1;
						}
						break;
				}
			}
			break;
		default :
			{
				// error
				desc.Error();
				return -1;
			}
			break;
	}
	return 0;
}



MGE2Variant::~MGE2Variant() {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( ___this == this ) {
		if ( _s == _VAR_HASHTABLE_ ) {
			MGEHashtable &___array = *(MGEHashtable*)VarPrimeType._VarObject;
			___array.DeleteAll();
			delete VarPrimeType._VarObject;
			VarPrimeType._VarObject = 0;
			status = _VAR_NULL_;
		} else if ( _s == _VAR_OBJECT_ARRAY_ ) {
			MGEObjectArray &___array = *(MGEObjectArray*)VarPrimeType._VarObject;
			___array.DeleteAll();
			delete VarPrimeType._VarObject;
			VarPrimeType._VarObject = 0;
			status = _VAR_NULL_;
		} else if ( ( _s >= _VAR_WSTRING_ ) && ( _s <= _VAR_STRING_ ) ) {
			delete VarPrimeType._VarObject;
			VarPrimeType._VarObject = 0;
			status = _VAR_NULL_;
		} else {
		}
	} else if ( ___this == 0 ) {
	} else {
	}
	status = 0;
}

void MGE2Variant::DelObj() {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _s == _VAR_HASHTABLE_ ) {
		MGEHashtable &___array = *(MGEHashtable*)VarPrimeType._VarObject;
		___array.DeleteAll();
		delete VarPrimeType._VarObject;
		VarPrimeType._VarObject = 0;
		status = 0;
	} else if ( _s == _VAR_OBJECT_ARRAY_ ) {
		MGEObjectArray &___array = *(MGEObjectArray*)VarPrimeType._VarObject;
		___array.DeleteAll();
		delete VarPrimeType._VarObject;
		VarPrimeType._VarObject = 0;
		status = 0;
	} else if ( ( _s >= _VAR_WSTRING_ ) && ( _s <= _VAR_STRING_ ) ) {
		delete VarPrimeType._VarObject;
		VarPrimeType._VarObject = 0;
		status = 0;
	} else {
	}
	status = 0;
}

void MGE2Variant::Error() {
	DelObj();
	status = _VAR_ERROR_;
}


MGE2Variant MGE2Variant::operator + (const MGE2Variant &src) {
	MGE2Variant desc;
	AddOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	if ( src.___this == 0 ) {
		((MGE2Variant &)src).DelObj();
	}
	return desc;
}


MGE2Variant& MGE2Variant::operator = (const MGE2Variant &src) {
//	CheckThisOut();
	if ( &src != this ) {
		if ( ___this == this ) {
			DelObj();
		} else {
			___this = this;
		}
		Assign(*this, (MGE2Variant &)src);
		if ( src.___this == 0 ) {
			((MGE2Variant &)src).DelObj();
		}
	}
	___this = this;
	return *this;
}

MGE2Variant& MGE2Variant::operator /= (const MGE2Variant &src) {
	CheckThisOut();
	MGE2Variant desc;
	DivOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	if ( src.___this == 0 ) {
		((MGE2Variant&)src).DelObj();
	}
	return *this;
}


MGE2Variant& MGE2Variant::operator *= (const MGE2Variant &src) {
	CheckThisOut();
	MGE2Variant desc;
	MulOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	if ( src.___this == 0 ) {
		((MGE2Variant&)src).DelObj();
	}
	return *this;
}



MGE2Variant& MGE2Variant::operator -= (const MGE2Variant &src) {
	CheckThisOut();
	MGE2Variant desc;
	SubOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	if ( src.___this == 0 ) {
		((MGE2Variant&)src).DelObj();
	}
	return *this;
}




MGE2Variant& MGE2Variant::operator += (const MGE2Variant &src) {
	CheckThisOut();
	MGE2Variant desc;
	AddOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	if ( src.___this == 0 ) {
		((MGE2Variant&)src).DelObj();
	}
	return *this;
}


BOOL32 MGE2Variant::operator == (const MGE2Variant &src) {
	return Equals(src);
}

MGE2Variant MGE2Variant::operator / (const MGE2Variant &src) {
	MGE2Variant desc;
	DivOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}

MGE2Variant MGE2Variant::operator * (const MGE2Variant &src) {
	MGE2Variant desc;
	MulOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}

MGE2Variant MGE2Variant::operator - (const MGE2Variant &src) {
	MGE2Variant desc;
	SubOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}



BOOL32 MGE2Variant::Equals(const MGE2Variant &src) {
	return 0;
}



MGE2Variant MGE2Variant::operator + (const int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator + (const unsigned int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator + (const float _fvalue) {
	MGE2Variant desc;
	MGE2Variant src(_fvalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator + (const double _dvalue) {
	MGE2Variant desc;
	MGE2Variant src(_dvalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}



MGE2Variant MGE2Variant::operator + (const _var_long _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator + (const _var_ulong _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator + (const wchar_t* wstr) {
#ifdef WIN32
	MGETString _wstr0(wstr);
#else
	MGEWString _wstr0(wstr);
#endif

	MGE2Variant desc;
	MGE2Variant src(_wstr0);
	AddOpr(desc, *this, src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator + (const MGEWString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	AddOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}

MGE2Variant MGE2Variant::operator + (const MGETString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	AddOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator + (const char* str) {
	MGEString _str0(str);

	MGE2Variant desc;
	MGE2Variant src(_str0);
	AddOpr(desc, *this, src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator + (const MGEString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	AddOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}



MGE2Variant& MGE2Variant::operator = (const int _ivalue) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	MGE2Variant desc(_ivalue);
	*this = desc;
	return *this;
}


MGE2Variant& MGE2Variant::operator = (const unsigned int _ivalue) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	MGE2Variant desc(_ivalue);
	*this = desc;
	return *this;
}


MGE2Variant& MGE2Variant::operator = (const float _fvalue) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	MGE2Variant desc(_fvalue);
	*this = desc;
	return *this;
}


MGE2Variant& MGE2Variant::operator = (const double _dvalue) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	MGE2Variant desc(_dvalue);
	*this = desc;
	return *this;
}



MGE2Variant& MGE2Variant::operator = (const _var_long _lvalue) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	MGE2Variant desc(_lvalue);
	*this = desc;
	return *this;
}


MGE2Variant& MGE2Variant::operator = (const _var_ulong _lvalue) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	MGE2Variant desc(_lvalue);
	*this = desc;
	return *this;
}


MGE2Variant& MGE2Variant::operator = (const wchar_t* wstr) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
#ifdef WIN32
	status = _VAR_TSTRING_;
	VarPrimeType._VarObject = new MGETString(wstr);
#else
	status = _VAR_WSTRING_;
	VarPrimeType._VarObject = new MGEWString(wstr);
#endif
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator = (const MGEWString &src) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	status = _VAR_WSTRING_;
	MGEWString *desc = new MGEWString();
	*desc = src;
	VarPrimeType._VarObject = desc;
	return *this;
}

MGE2Variant& MGE2Variant::operator = (const MGETString &src) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	status = _VAR_TSTRING_;
	MGETString *desc = new MGETString();
	*desc = src;
	VarPrimeType._VarObject = desc;
	return *this;
}


MGE2Variant& MGE2Variant::operator = (const char* str) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	status = _VAR_STRING_;
	MGEString *desc = new MGEString(str);
	VarPrimeType._VarObject = desc;
	return *this;
}


MGE2Variant& MGE2Variant::operator = (const MGEString &src) {
	if ( ___this == this ) {
		DelObj();
	} else {
		___this = this;
	}
	status = _VAR_STRING_;
	MGEString *desc = new MGEString();
	*desc = src;
	VarPrimeType._VarObject = desc;
	return *this;
}



MGE2Variant& MGE2Variant::operator += (const int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator += (const unsigned int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator += (const float _fvalue) {
	MGE2Variant desc;
	MGE2Variant src(_fvalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator += (const double _dvalue) {
	MGE2Variant desc;
	MGE2Variant src(_dvalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}



MGE2Variant& MGE2Variant::operator += (const _var_long _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator += (const _var_ulong _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	AddOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator += (const wchar_t* wstr) {
	MGE2Variant desc;
	MGE2Variant src(wstr);
	AddOpr(desc, *this, (MGE2Variant &)src);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator += (const MGEWString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	AddOpr(desc, *this, (MGE2Variant &)src0);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}

MGE2Variant& MGE2Variant::operator += (const MGETString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	AddOpr(desc, *this, (MGE2Variant &)src0);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator += (const char* str) {
	MGE2Variant desc;
	MGE2Variant src0(str);
	AddOpr(desc, *this, (MGE2Variant &)src0);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}


MGE2Variant& MGE2Variant::operator += (const MGEString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	AddOpr(desc, *this, (MGE2Variant &)src0);
	DelObj();
	status = desc.status;
	VarPrimeType = desc.VarPrimeType;
	desc.status = 0;
	desc.VarPrimeType._VarObject = 0;
	___this = this;
	return *this;
}



BOOL32 MGE2Variant::operator == (const int _ivalue) {
	MGE2Variant src0(_ivalue);
	return Equals(src0);
}


BOOL32 MGE2Variant::operator == (const unsigned int _ivalue) {
	MGE2Variant src0(_ivalue);
	return Equals(src0);
}


BOOL32 MGE2Variant::operator == (const float _fvalue) {
	MGE2Variant src0(_fvalue);
	return Equals(src0);
}


BOOL32 MGE2Variant::operator == (const double _dvalue) {
	MGE2Variant src0(_dvalue);
	return Equals(src0);
}



BOOL32 MGE2Variant::operator == (const _var_long _lvalue) {
	MGE2Variant src0(_lvalue);
	return Equals(src0);
}


BOOL32 MGE2Variant::operator == (const _var_ulong _lvalue) {
	MGE2Variant src0(_lvalue);
	return Equals(src0);
}


BOOL32 MGE2Variant::operator == (const wchar_t* wstr) {
	MGE2Variant src0(wstr);
	return Equals(src0);
}


BOOL32 MGE2Variant::operator == (const MGEWString &src) {
	MGE2Variant src0(src);
	return Equals(src0);
}

BOOL32 MGE2Variant::operator == (const MGETString &src) {
	MGE2Variant src0(src);
	return Equals(src0);
}


BOOL32 MGE2Variant::operator == (const char* str) {
	MGE2Variant src0(str);
	return Equals(src0);
}


BOOL32 MGE2Variant::operator == (const MGEString &src) {
	MGE2Variant src0(src);
	return Equals(src0);
}




MGE2Variant MGE2Variant::operator - (const int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	SubOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator - (const unsigned int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	SubOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator - (const float _fvalue) {
	MGE2Variant desc;
	MGE2Variant src(_fvalue);
	SubOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator - (const double _dvalue) {
	MGE2Variant desc;
	MGE2Variant src(_dvalue);
	SubOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}



MGE2Variant MGE2Variant::operator - (const _var_long _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	SubOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator - (const _var_ulong _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	SubOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator - (const wchar_t* wstr) {
#ifdef WIN32
	MGETString _wstr0(wstr);
#else
	MGEWString _wstr0(wstr);
#endif

	MGE2Variant desc;
	MGE2Variant src(_wstr0);
	SubOpr(desc, *this, src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator - (const MGEWString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	SubOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}

MGE2Variant MGE2Variant::operator - (const MGETString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	SubOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator - (const char* str) {
	MGEString _str0(str);

	MGE2Variant desc;
	MGE2Variant src(_str0);
	SubOpr(desc, *this, src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator - (const MGEString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	SubOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	MulOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const unsigned int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	MulOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const float _fvalue) {
	MGE2Variant desc;
	MGE2Variant src(_fvalue);
	MulOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const double _dvalue) {
	MGE2Variant desc;
	MGE2Variant src(_dvalue);
	MulOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}



MGE2Variant MGE2Variant::operator * (const _var_long _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	MulOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const _var_ulong _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	MulOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const wchar_t* wstr) {
#ifdef WIN32
	MGETString _wstr0(wstr);
#else
	MGEWString _wstr0(wstr);
#endif

	MGE2Variant desc;
	MGE2Variant src(_wstr0);
	MulOpr(desc, *this, src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const MGEWString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	MulOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}

MGE2Variant MGE2Variant::operator * (const MGETString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	MulOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const char* str) {
	MGEString _str0(str);

	MGE2Variant desc;
	MGE2Variant src(_str0);
	MulOpr(desc, *this, src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator * (const MGEString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	MulOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}



MGE2Variant MGE2Variant::operator / (const int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	DivOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator / (const unsigned int _ivalue) {
	MGE2Variant desc;
	MGE2Variant src(_ivalue);
	DivOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator / (const float _fvalue) {
	MGE2Variant desc;
	MGE2Variant src(_fvalue);
	DivOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator / (const double _dvalue) {
	MGE2Variant desc;
	MGE2Variant src(_dvalue);
	DivOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}



MGE2Variant MGE2Variant::operator / (const _var_long _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	DivOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator / (const _var_ulong _lvalue) {
	MGE2Variant desc;
	MGE2Variant src(_lvalue);
	DivOpr(desc, *this, (MGE2Variant &)src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator / (const wchar_t* wstr) {
#ifdef WIN32
	MGETString _wstr0(wstr);
#else
	MGEWString _wstr0(wstr);
#endif

	MGE2Variant desc;
	MGE2Variant src(_wstr0);
	DivOpr(desc, *this, src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator / (const MGEWString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	DivOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}

MGE2Variant MGE2Variant::operator / (const MGETString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	DivOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator / (const char* str) {
	MGEString _str0(str);

	MGE2Variant desc;
	MGE2Variant src(_str0);
	DivOpr(desc, *this, src);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}


MGE2Variant MGE2Variant::operator / (const MGEString &src) {
	MGE2Variant desc;
	MGE2Variant src0(src);
	DivOpr(desc, *this, src0);
	desc.___this = 0;
	if ( ___this == 0 ) {
		DelObj();
	}
	return desc;
}

//MGE2Variant &MGE2Variant::operator () (const MGE2Variant &src) {
//	((MGE2Variant *)&src)->___this = 0;
//	return *((MGE2Variant *)&src);
//}


void MGE2Variant::CreateArray() {
	DelObj();
	VarPrimeType._VarObject = new MGEObjectArray();
	status = _VAR_OBJECT_ARRAY_;
	___this = this;
}

void MGE2Variant::CreateHashtable() {
	DelObj();
	VarPrimeType._VarObject = new MGEHashtable();
	status = _VAR_HASHTABLE_;
	___this = this;
}

void MGE2Variant::CreateGenericObject() {
	DelObj();
	VarPrimeType._VarObject = new MGEHashtable();
	status = _VAR_HASHTABLE_;
	___this = this;
}



BOOL32 MGE2Variant::Del(MGEString &key) {
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_HASHTABLE_ ) {
		MGEHashtable &___ht = *(MGEHashtable*)VarPrimeType._VarObject;
		MGE2Variant *_obj = (MGE2Variant*)___ht.Get(key);
		if ( _obj != NULL ) {
			delete _obj;
		}
		return ___ht.Del(key);
	}
	return FALSE;
}


unsigned int MGE2Variant::GetCount() {
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_HASHTABLE_ ) {
		MGEHashtable &___ht = *(MGEHashtable*)VarPrimeType._VarObject;
		return ___ht.GetCount();
	}
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_OBJECT_ARRAY_ ) {
		MGEObjectArray &___array = *(MGEObjectArray*)VarPrimeType._VarObject;
		return ___array.GetLength();
	}
	return 0;
}


MGE2Variant& MGE2Variant::operator[](MGEString &key) {
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_HASHTABLE_ ) {
		MGEHashtable &___ht = *(MGEHashtable*)VarPrimeType._VarObject;
		MGE2Variant* __pvar = NULL;
		if ( key.GetLength() > 0 ) {
			__pvar = (MGE2Variant*)(___ht.Get(key));
			if ( __pvar == NULL ) {
				__pvar = new MGE2Variant();
				___ht.Add(key, __pvar);
			}
		} else {
			MGEString _epsilon(" ");//<<=== replace "" with _epsilon 
			__pvar = (MGE2Variant*)(___ht.Get(key));
			if ( __pvar == NULL ) {
				__pvar = new MGE2Variant();
				___ht.Add(_epsilon, __pvar);
			}
		}
		return *__pvar;
	} else 
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_OBJECT_ARRAY_ ) {
		ObjectArray2Hashtable();
		return (*this)[key];
	}
	return *this;
}

MGE2Variant& MGE2Variant::operator[](const char *__str) {
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_HASHTABLE_ ) {
		MGEString _key(__str);
		MGEHashtable &___ht = *(MGEHashtable*)VarPrimeType._VarObject;
		MGE2Variant* __pvar = (MGE2Variant*)(___ht.Get(_key));
		if ( __pvar == NULL ) {
			__pvar = new MGE2Variant();
			___ht.Add(_key, __pvar);
		}
		return *__pvar;
	} else 
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_OBJECT_ARRAY_ ) {
		ObjectArray2Hashtable();
		return (*this)[__str];
	}
	return *this;
}


unsigned int MGE2Variant::Pack() {
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_HASHTABLE_ ) {
		MGEHashtable &___ht = *(MGEHashtable*)VarPrimeType._VarObject;
		return ___ht.Pack();
	}
	return 0;
}



MGE2Variant& MGE2Variant::operator[](unsigned int index) {
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_OBJECT_ARRAY_ ) {
		MGEObjectArray &___array = *(MGEObjectArray*)VarPrimeType._VarObject;
		if ( index >= ___array.GetLength() ) {
			___array.Resize(index + 1);
		}
		MGE2Variant* __pvar = (MGE2Variant*)(___array[index]);
		if ( __pvar == NULL ) {
			__pvar = new MGE2Variant();
			___array[index] = __pvar;
		}
		return *__pvar;
	} else 
	if ( ( status & _VAR_TYPE_STATUS_MASK_ ) == _VAR_HASHTABLE_ ) {
		MGEString _key(index);
		MGEHashtable &___ht = *(MGEHashtable*)VarPrimeType._VarObject;
		MGE2Variant* __pvar = (MGE2Variant*)(___ht.Get(_key));
		if ( __pvar == NULL ) {
			__pvar = new MGE2Variant();
			___ht.Add(_key, __pvar);
		}
		return *__pvar;
	}
	return *this;
}



void MGE2Variant::DeleteAll() {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _s == _VAR_HASHTABLE_ ) {
		MGEHashtable &___array = *(MGEHashtable*)VarPrimeType._VarObject;
		___array.DeleteAll();
		delete VarPrimeType._VarObject;
		VarPrimeType._VarObject = 0;
		status = _VAR_NULL_;
	} else if ( _s == _VAR_OBJECT_ARRAY_ ) {
		MGEObjectArray &___array = *(MGEObjectArray*)VarPrimeType._VarObject;
		___array.DeleteAll();
		delete VarPrimeType._VarObject;
		VarPrimeType._VarObject = 0;
		status = _VAR_NULL_;
	} else if ( ( _s >= _VAR_WSTRING_ ) && ( _s <= _VAR_STRING_ ) ) {
		delete VarPrimeType._VarObject;
		VarPrimeType._VarObject = 0;
		status = _VAR_NULL_;
	} else {
	}
	status = _VAR_NULL_;
}


void MGE2Variant::CopyfromString(const MGEString &src) {
	DelObj();
	status = _VAR_STRING_;
	MGEString *desc = new MGEString();
	*desc = src;
	VarPrimeType._VarObject = desc;
}

void MGE2Variant::CopyfromString(const MGETString &src) {
	DelObj();
	status = _VAR_TSTRING_;
	MGETString *desc = new MGETString();
	*desc = src;
	VarPrimeType._VarObject = desc;
}

void MGE2Variant::CopyfromString(const MGEWString &src) {
	DelObj();
	status = _VAR_WSTRING_;
	MGEWString *desc = new MGEWString();
	*desc = src;
	VarPrimeType._VarObject = desc;
}

unsigned int MGE2Variant::GetKeyValuePair(MGEObjectArray &__keys, MGEObjectArray &__vars) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _s == _VAR_HASHTABLE_ ) {
		unsigned int _count, _i;
		MGEHashtable &___array = *(MGEHashtable*)VarPrimeType._VarObject;
		_count = ___array.GetKeyValuePair(__keys, __vars);
		for ( _i = 0 ; _i < _count ; _i ++ ) {
			MGE2Variant* __pvar = new MGE2Variant();
			(*__pvar) = *(MGE2Variant*)(__vars[_i]);
			__vars[_i] = __pvar;
		}
		return _count;
	} else {
	}
	return 0;
}

void MGE2Variant::CheckThisOut() {
	if ( ___this == 0 ) {
	} else if ( ___this != this ) {
		unsigned long _s = ___this->status & _VAR_TYPE_STATUS_MASK_;
		if ( _s == _VAR_STRING_ ) {
			status = _VAR_STRING_;
			MGEString *desc = new MGEString();
			MGEString *_src = (MGEString *)(___this->VarPrimeType._VarObject);
			*desc = *_src;
			VarPrimeType._VarObject = desc;
			___this = this;
		} else
		if ( _s == _VAR_TSTRING_ ) {
			status = _VAR_TSTRING_;
			MGETString *desc = new MGETString();
			MGETString *_src = (MGETString *)(___this->VarPrimeType._VarObject);
			*desc = *_src;
			VarPrimeType._VarObject = desc;
			___this = this;
		} else 
		if ( _s == _VAR_WSTRING_ ) {
			status = _VAR_WSTRING_;
			MGEWString *desc = new MGEWString();
			MGEWString *_src = (MGEWString *)(___this->VarPrimeType._VarObject);
			*desc = *_src;
			VarPrimeType._VarObject = desc;
			___this = this;
		} else
		if ( _s == _VAR_OBJECT_ARRAY_ ) {
			status = _VAR_OBJECT_ARRAY_;
			MGEObjectArray *desc = new MGEObjectArray();
			MGEObjectArray *_src = (MGEObjectArray *)(___this->VarPrimeType._VarObject);
			*desc = *_src;
			VarPrimeType._VarObject = desc;
			___this = this;
		} else
		if ( _s == _VAR_HASHTABLE_ ) {
			status = _VAR_HASHTABLE_;
			MGEHashtable *desc = new MGEHashtable();
			MGEHashtable *_src = (MGEHashtable *)(___this->VarPrimeType._VarObject);
			(*desc).CopyHashtable(*_src);
			VarPrimeType._VarObject = desc;
			___this = this;
		} else
		if ( _s == _VAR_REFERENCE_ ) {
			status = _VAR_REFERENCE_;
			VarPrimeType._VarObject = (MGEObject *)(___this->VarPrimeType._VarObject);
			___this = this;
		} else 
		{
			___this = this;
		}
	} else {
	}
}

void MGE2Variant::ObjectArray2Hashtable() {
	unsigned int _i = 0;
	unsigned int _l = 0;
	MGEObjectArray &___array = *(MGEObjectArray*)VarPrimeType._VarObject;
	MGEHashtable *desc = new MGEHashtable();

	_l = ___array.GetLength();
	for ( _i = 0 ; _i < _l ; _i ++ ) {
		MGEObject *_obj = (MGEObject *)___array[_i];
		if ( _obj != NULL ) {
			MGEString _str(_i);
			desc->Add(_str, _obj);
		}
	}
	delete VarPrimeType._VarObject;

	VarPrimeType._VarObject = desc;
	status = _VAR_HASHTABLE_;
}

void MGE2Variant::CopyHashtablefromHashtable(MGE2Variant& src) {
	MGEObjectArray _keys;
	MGEObjectArray _vars;
	MGEHashtable &___ht = *(MGEHashtable*)src.VarPrimeType._VarObject;
	unsigned int _srccount = src.GetKeyValuePair(_keys, _vars);
	unsigned int _i;

	for ( _i = 0 ; _i < _srccount ; _i ++ ) {
		MGEString &_key = *(MGEString*)_keys[_i];
		(*this)[_key] = *(MGE2Variant*)_vars[_i];
	}

	_keys.DeleteAll();
	_vars.DeleteAll();
}

void MGE2Variant::CopyHashtablefromObjectArray(MGE2Variant& src) {
	MGEObjectArray &___array = *(MGEObjectArray*)src.VarPrimeType._VarObject;
	unsigned int _count = ___array.GetLength();
	unsigned int _i;

	for ( _i = 0 ; _i < _count ; _i ++ ) {
		MGEString _key(_i);
		MGE2Variant *___var = (MGE2Variant*)___array[_i];
		if ( ___var != NULL ) {
			(*this)[_key] = *___var;
		}
	}
}

void MGE2Variant::CopyObjectArrayfromObjectArray(MGE2Variant& src) {
	MGEObjectArray &___srcarray = *(MGEObjectArray*)src.VarPrimeType._VarObject;
	MGEObjectArray &___array = *(MGEObjectArray*)VarPrimeType._VarObject;
	unsigned int _count = ___srcarray.GetLength();
	unsigned int _i;

	for ( _i = 0 ; _i < _count ; _i ++ ) {
		MGE2Variant *___svar = (MGE2Variant*)___srcarray[_i];
		if ( ___svar != NULL ) {
			MGE2Variant *___var = new MGE2Variant();
			(*___var) = *___svar;
			___array.Append(___var);
		}
	}
}

void MGE2Variant::Assign(MGE2Variant& __vdesc, MGE2Variant& __vsrc) {
	unsigned long _s = __vsrc.status & _VAR_TYPE_STATUS_MASK_;
	if ( _s == _VAR_STRING_ ) {
		__vdesc.status = _VAR_STRING_;
		MGEString *desc = new MGEString();
		MGEString *_src = (MGEString *)(__vsrc.VarPrimeType._VarObject);
		*desc = *_src;
		__vdesc.VarPrimeType._VarObject = desc;
	} else
	if ( _s == _VAR_TSTRING_ ) {
		__vdesc.status = _VAR_TSTRING_;
		MGETString *desc = new MGETString();
		MGETString *_src = (MGETString *)(__vsrc.VarPrimeType._VarObject);
		*desc = *_src;
		__vdesc.VarPrimeType._VarObject = desc;
	} else 
	if ( _s == _VAR_WSTRING_ ) {
		__vdesc.status = _VAR_WSTRING_;
		MGEWString *desc = new MGEWString();
		MGEWString *_src = (MGEWString *)(__vsrc.VarPrimeType._VarObject);
		*desc = *_src;
		__vdesc.VarPrimeType._VarObject = desc;
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		__vdesc.CreateArray();
		__vdesc.CopyObjectArrayfromObjectArray(__vsrc);
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		__vdesc.CreateHashtable();
		__vdesc.CopyHashtablefromHashtable(__vsrc);
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		__vdesc.status = _s;
		__vdesc.VarPrimeType = __vsrc.VarPrimeType;
	} else 
	if ( _s < _VAR_WSTRING_ ) {
		__vdesc.status = _s;
		__vdesc.VarPrimeType = __vsrc.VarPrimeType;
	} else 
	{
	}
}

int MGE2Variant::GetInt(unsigned int *_result) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _result != NULL ) {
		*_result = _s;
	}

	if ( _s == _VAR_STRING_ ) {
		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
		int _ret = 0;
		if ( _src->GetBuffer() ) {
			sscanf(_src->GetBuffer(), "%d", &_ret);
		}
		return _ret;
	} else
	if ( _s == _VAR_TSTRING_ ) {
//		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_WSTRING_ ) {
//		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return (int)GetCount();
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return (int)GetCount();
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return (int)VarPrimeType._ulValue;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return (int)VarPrimeType._lValue;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return (int)VarPrimeType._dValue;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return (int)VarPrimeType._fValue;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return (int)VarPrimeType._uiValue;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return (int)VarPrimeType._iValue;
	} else 
	{
	}
	return 0;
}

unsigned int MGE2Variant::GetUInt(unsigned int *_result) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _result != NULL ) {
		*_result = _s;
	}

	if ( _s == _VAR_STRING_ ) {
		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
		unsigned int _ret = 0;
		if ( _src->GetBuffer() ) {
			sscanf(_src->GetBuffer(), "%u", &_ret);
		}
		return _ret;
//		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_TSTRING_ ) {
//		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_WSTRING_ ) {
//		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return (unsigned int)GetCount();
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return (unsigned int)GetCount();
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return (unsigned int)VarPrimeType._ulValue;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return (unsigned int)VarPrimeType._lValue;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return (unsigned int)VarPrimeType._dValue;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return (unsigned int)VarPrimeType._fValue;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return (unsigned int)VarPrimeType._uiValue;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return (unsigned int)VarPrimeType._iValue;
	} else 
	{
	}
	return 0;
}

_var_long MGE2Variant::GetLong(unsigned int *_result) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _result != NULL ) {
		*_result = _s;
	}

	if ( _s == _VAR_STRING_ ) {
		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
		_var_long _ret = 0;
		if ( _src->GetBuffer() ) {
			sscanf(_src->GetBuffer(), "%ld", &_ret);
		}
		return _ret;
//		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_TSTRING_ ) {
//		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_WSTRING_ ) {
//		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return (_var_long)GetCount();
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return (_var_long)GetCount();
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return (_var_long)VarPrimeType._ulValue;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return (_var_long)VarPrimeType._lValue;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return (_var_long)VarPrimeType._dValue;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return (_var_long)VarPrimeType._fValue;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return (_var_long)VarPrimeType._uiValue;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return (_var_long)VarPrimeType._iValue;
	} else 
	{
	}
	return 0;
}

_var_ulong MGE2Variant::GetULong(unsigned int *_result) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _result != NULL ) {
		*_result = _s;
	}

	if ( _s == _VAR_STRING_ ) {
		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
		_var_ulong _ret = 0;
		if ( _src->GetBuffer() ) {
			sscanf(_src->GetBuffer(), "%lu", &_ret);
		}
		return _ret;
//		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_TSTRING_ ) {
//		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_WSTRING_ ) {
//		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return (_var_ulong)GetCount();
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return (_var_ulong)GetCount();
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return (_var_ulong)VarPrimeType._ulValue;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return (_var_ulong)VarPrimeType._lValue;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return (_var_ulong)VarPrimeType._dValue;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return (_var_ulong)VarPrimeType._fValue;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return (_var_ulong)VarPrimeType._uiValue;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return (_var_ulong)VarPrimeType._iValue;
	} else 
	{
	}
	return 0;
}

//unsafe
const void *MGE2Variant::GetBuffer(unsigned int *_result) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _result != NULL ) {
		*_result = _s;
	}

	if ( _s == _VAR_STRING_ ) {
		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
		return _src->GetBuffer();
	} else
	if ( _s == _VAR_TSTRING_ ) {
		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
		return _src->GetBuffer();
	} else 
	if ( _s == _VAR_WSTRING_ ) {
		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
		return _src->GetBuffer();
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
	} else 
	{
	}
	return NULL;
}

//unsafe
const MGE2Variant *MGE2Variant::GetReference(unsigned int *_result) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _result != NULL ) {
		*_result = _s;
	}

	if ( _s == _VAR_STRING_ ) {
		return this;
	} else
	if ( _s == _VAR_TSTRING_ ) {
		return this;
	} else 
	if ( _s == _VAR_WSTRING_ ) {
		return this;
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return this;
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return this;
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		return (MGE2Variant *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return this;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return this;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return this;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return this;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return this;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return this;
	} else 
	{
	}
	return NULL;
}

float MGE2Variant::GetFloat(unsigned int *_result) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _result != NULL ) {
		*_result = _s;
	}

	if ( _s == _VAR_STRING_ ) {
//		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_TSTRING_ ) {
//		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_WSTRING_ ) {
//		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return (float)GetCount();
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return (float)GetCount();
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return (float)VarPrimeType._ulValue;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return (float)VarPrimeType._lValue;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return (float)VarPrimeType._dValue;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return (float)VarPrimeType._fValue;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return (float)VarPrimeType._uiValue;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return (float)VarPrimeType._iValue;
	} else 
	{
	}
	return 0;
}

double MGE2Variant::GetDouble(unsigned int *_result) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;
	if ( _result != NULL ) {
		*_result = _s;
	}

	if ( _s == _VAR_STRING_ ) {
//		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_TSTRING_ ) {
//		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_WSTRING_ ) {
//		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return (double)GetCount();
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return (double)GetCount();
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return (double)VarPrimeType._ulValue;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return (double)VarPrimeType._lValue;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return (double)VarPrimeType._dValue;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return (double)VarPrimeType._fValue;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return (double)VarPrimeType._uiValue;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return (double)VarPrimeType._iValue;
	} else 
	{
	}
	return 0;
}


unsigned int MGE2Variant::Copy2String(MGEString &desc) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;

	if ( _s == _VAR_STRING_ ) {
		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
		desc = *_src;
	} else
	if ( _s == _VAR_TSTRING_ ) {
//		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_WSTRING_ ) {
//		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return _s;//<===output string stream?
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return _s;//<===output string stream?
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return _s;
	} else 
	{
	}
	return _s;
}

unsigned int MGE2Variant::Copy2String(MGETString &desc) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;

	if ( _s == _VAR_STRING_ ) {
//		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_TSTRING_ ) {
		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
		desc = *_src;
	} else 
	if ( _s == _VAR_WSTRING_ ) {
//		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return _s;//<===output string stream?
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return _s;//<===output string stream?
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return _s;
	} else 
	{
	}
	return _s;
}

unsigned int MGE2Variant::Copy2String(MGEWString &desc) {
	unsigned long _s = status & _VAR_TYPE_STATUS_MASK_;

	if ( _s == _VAR_STRING_ ) {
//		MGEString *_src = (MGEString *)(VarPrimeType._VarObject);
	} else
	if ( _s == _VAR_TSTRING_ ) {
//		MGETString *_src = (MGETString *)(VarPrimeType._VarObject);
	} else 
	if ( _s == _VAR_WSTRING_ ) {
		MGEWString *_src = (MGEWString *)(VarPrimeType._VarObject);
		desc = *_src;
	} else
	if ( _s == _VAR_OBJECT_ARRAY_ ) {
		return _s;//<===output string stream?
	} else
	if ( _s == _VAR_HASHTABLE_ ) {
		return _s;//<===output string stream?
	} else
	if ( _s == _VAR_REFERENCE_ ) {
		// Error
	} else 
	if ( _s == _VAR_PRIME_ULONG_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_LONG_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_DOUBLE_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_FLOAT_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_UINT_ ) {
		return _s;
	} else 
	if ( _s == _VAR_PRIME_INT_ ) {
		return _s;
	} else 
	{
	}
	return _s;
}


MGE2Variant& MGE2Variant::SetReturn() {
	___this = 0;
	return *this;
}


const char* MGE2Variant::GetClassName() {
	return "MGE2Variant";
}


int MGE2Variant::GetHashCode() {
	return 0;
}


BOOL32 MGE2Variant::IsInstanceof(const char* className) {
	if (strcmp("MGE2Variant", className) == 0) {
		return TRUE;
	}
	return FALSE;
}


BOOL32 MGE2Variant::IsEqualto(MGEObject &obj) {
	return 0;
}


void MGE2Variant::Serialize(MGEIOStream &iio) {
}


