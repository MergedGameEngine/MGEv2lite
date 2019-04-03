///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _FILE_EXPORT

#include "stdio.h"
#include "string.h"
#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#undef _ARRAY_API
#define _ARRAY_API _FILE_API
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "Config.hpp"

MGEConfig::MGEConfig() {
	names.Resize(0);
	values.Resize(0);
}
MGEConfig::~MGEConfig() {
	names.DeleteAll();
	names.Resize(0);
	values.DeleteAll();
	values.Resize(0);
}
const char *MGEConfig::GetClassName() {
	return "MGEConfig";
}

BOOL32 MGEConfig::IsInstanceof(const char* className) {
	if ( strcmp("MGEConfig", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}
void MGEConfig::Serialize(MGEIOStream &iio) {
}

MGERefArray<MGEString> &MGEConfig::GetNames() {
	return names;
}
MGERefArray<MGEString> &MGEConfig::GetValues() {
	return values;
}
MGEHashtable &MGEConfig::GetNameIndices() {
	return nameIndices;
}

inline int _IsSpace(unsigned short chr) {
	if ( chr == 0x0020 ) {
		return TRUE;
	}
	if ( chr == 0x000B ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsAZaz(unsigned short chr) {
	if ( ( chr >= 0x0041 ) && ( chr <= 0x005A ) ) {
		return TRUE;
	}
	if ( ( chr >= 0x0061 ) && ( chr <= 0x007A ) ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsAZaz_(unsigned short chr) {
	if ( ( chr >= 0x0041 ) && ( chr <= 0x005A ) ) {
		return TRUE;
	}
	if ( ( chr >= 0x0061 ) && ( chr <= 0x007A ) ) {
		return TRUE;
	}
	if ( chr == '_' ) {
		return TRUE;
	}
	return FALSE;
}

inline int _Is09(unsigned short chr) {
	if ( ( chr >= 0x0030 ) && ( chr <= 0x0039 ) ) {
		return TRUE;
	}
	return FALSE;
}

inline int _Is_(unsigned short chr) {
	if ( chr == '_' ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsEnter(unsigned short chr) {
	if ( chr == 0x000D ) {
		return TRUE;
	}
	if ( chr == 0x000A ) {
		return TRUE;
	}
	return FALSE;
}

double MGEConfig::StringtoDouble(MGEString &src) {
	const char *stream = src.GetBuffer();
	char achar = 0;
	unsigned short i = 0;
	unsigned short innerstate = 0;
	double sum = 0.0;
	double rank = 0.0;
	BOOL32 isNeg = FALSE;
	while(stream[i] != 0) {
		achar = stream[i]; i++;
		if ( achar == '-' ) {
			isNeg = TRUE;
			innerstate = 3;
		} else if ( achar == '.' ) {
			innerstate = 1;
		} else if ( _Is09(achar) ) {
		} else {
			return sum;
		}
		switch ( innerstate ) {
			case 0:
				{
					innerstate = 0;
					sum = sum * 10 + (double)(achar - 0x0030);
				}
				break;
			case 1:
				{
					innerstate = 2;
					rank = 0.1;
				}
				break;
			case 2:
				{
					innerstate = 2;
					sum = sum + rank * (double)(achar - 0x0030);
					rank = rank / 10.0;
				}
				break;
			case 3:
				{
					innerstate = 0;
				}
				break;
		}
	}
	if ( isNeg ) {
		return sum / -1.0;
	}
	return sum;
}

BOOL32 MGEConfig::ParseInt(MGEString &key, int &des) {
	MGEString *result = (MGEString*)nameIndices.Get(key);
	if ( result != NULL ) {
		const char *stream = result->GetBuffer();
		unsigned int i = 0;
		char achar = 0;
		unsigned short innerstate = 1;
		unsigned short linecount = 0;
		char oneline[256];
		while (TRUE) {
			achar = stream[i]; i++;
			switch (innerstate) {
				case 1:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 1;
						} else if ( _Is09(achar) ) {
							innerstate = 2;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 6;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 2:
					{
						if ( _Is09(achar) ) {
							innerstate = 2;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( _IsSpace(achar) ) {
							innerstate = 4;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == 0 ) {
							innerstate = 5;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == '.' ) {
							innerstate = 3;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 3:
					{
						if ( _Is09(achar) ) {
							innerstate = 3;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == 0 ) {
							innerstate = 5;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _IsSpace(achar) ) {
							innerstate = 4;
							oneline[linecount] = 0;
							linecount = 0;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 4:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 4;
						} else if ( achar == 0 ) {
							innerstate = 5;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 5:
					{
						MGEString val(oneline);
						double v = StringtoDouble(val);
						des = (int)v;
						return TRUE;
					}
					break;
				case 6:
					{
						if ( _Is09(achar) ) {
							innerstate = 2;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 0xFFFF:
					{
						return FALSE;
					}
					break;
				default:
					{
					}
					break;
			}

		}
	}
	return FALSE;
}
BOOL32 MGEConfig::ParseDouble(MGEString &key, double &des) {
	MGEString *result = (MGEString*)nameIndices.Get(key);
	if ( result != NULL ) {
		const char *stream = result->GetBuffer();
		unsigned int i = 0;
		char achar = 0;
		unsigned short innerstate = 1;
		unsigned short linecount = 0;
		char oneline[256];
		while (TRUE) {
			achar = stream[i]; i++;
			switch (innerstate) {
				case 1:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 1;
						} else if ( _Is09(achar) ) {
							innerstate = 2;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 6;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 2:
					{
						if ( _Is09(achar) ) {
							innerstate = 2;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( _IsSpace(achar) ) {
							innerstate = 4;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == 0 ) {
							innerstate = 5;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == '.' ) {
							innerstate = 3;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 3:
					{
						if ( _Is09(achar) ) {
							innerstate = 3;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == 0 ) {
							innerstate = 5;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _IsSpace(achar) ) {
							innerstate = 4;
							oneline[linecount] = 0;
							linecount = 0;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 4:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 4;
						} else if ( achar == 0 ) {
							innerstate = 5;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 5:
					{
						MGEString val(oneline);
						des = StringtoDouble(val);
						return TRUE;
					}
					break;
				case 6:
					{
						if ( _Is09(achar) ) {
							innerstate = 2;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 0xFFFF:
					{
						return FALSE;
					}
					break;
				default:
					{
					}
					break;
			}

		}
	}
	return FALSE;
}
BOOL32 MGEConfig::ParseVector3f(MGEString &key, Vector3f &des) {
	MGEString *result = (MGEString*)nameIndices.Get(key);
	if ( result != NULL ) {
		Vector3f desc;
		const char *stream = result->GetBuffer();
		unsigned int i = 0;
		char achar = 0;
		unsigned short innerstate = 1;
		unsigned short linecount = 0;
		char oneline[256];
		while (TRUE) {
			achar = stream[i]; i++;
			switch (innerstate) {
				case 1:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 1;
						} else if ( achar == 'v' ) {
							innerstate = 2;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 2:
					{
						if ( achar == 'e' ) {
							innerstate = 3;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 3:
					{
						if ( achar == 'c' ) {
							innerstate = 4;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 4:
					{
						if ( achar == '3' ) {
							innerstate = 5;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 5:
					{
						if ( achar == 'f' ) {
							innerstate = 6;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 6:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 6;
						} else if ( achar == '(' ) {
							innerstate = 7;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 7:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 7;
						} else if ( _Is09(achar) ) {
							innerstate = 8;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 12;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 8:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 11;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 8;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 9;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 9:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 11;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 9;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 10:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
						} else if ( achar == ',' ) {
							innerstate = 11;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 11:
					{
						MGEString val(oneline);
						desc.x = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 17;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 22;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 12:
					{
						if ( _Is09(achar) ) {
							innerstate = 8;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 17:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 17;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 22;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 18:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 21;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 19;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 19:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 21;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 19;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 20:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
						} else if ( achar == ',' ) {
							innerstate = 21;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 21:
					{
						MGEString val(oneline);
						desc.y = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 27;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 32;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 22:
					{
						if ( _Is09(achar) ) {
							innerstate = 18;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


					
				case 27:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 27;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 32;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 28:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ')' ) {
							innerstate = 31;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 29;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 29:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ')' ) {
							innerstate = 31;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 29;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 30:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
						} else if ( achar == ')' ) {
							innerstate = 31;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 31:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 31;
						} else if ( achar == 0 ) {
							MGEString val(oneline);
							desc.z = (float)StringtoDouble(val);
							innerstate = 33;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 32:
					{
						if ( _Is09(achar) ) {
							innerstate = 28;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;

				case 33:
					{
						des = desc;
						return TRUE;
					}
					break;
				case 0xFFFF:
					{
						return FALSE;
					}
					break;
				default:
					{
					}
					break;
			}
		}
	}
	return FALSE;
}
BOOL32 MGEConfig::ParseVector4f(MGEString &key, Vector4f &des) {
	MGEString *result = (MGEString*)nameIndices.Get(key);
	if ( result != NULL ) {
		Vector4f desc;
		const char *stream = result->GetBuffer();
		unsigned int i = 0;
		char achar = 0;
		unsigned short innerstate = 1;
		unsigned short linecount = 0;
		char oneline[256];
		while (TRUE) {
			achar = stream[i]; i++;
			switch (innerstate) {
				case 1:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 1;
						} else if ( achar == 'v' ) {
							innerstate = 2;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 2:
					{
						if ( achar == 'e' ) {
							innerstate = 3;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 3:
					{
						if ( achar == 'c' ) {
							innerstate = 4;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 4:
					{
						if ( achar == '4' ) {
							innerstate = 5;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 5:
					{
						if ( achar == 'f' ) {
							innerstate = 6;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 6:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 6;
						} else if ( achar == '(' ) {
							innerstate = 7;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 7:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 7;
						} else if ( _Is09(achar) ) {
							innerstate = 8;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 12;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 8:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 11;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 8;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 9;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 9:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 11;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 9;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 10:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
						} else if ( achar == ',' ) {
							innerstate = 11;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 11:
					{
						MGEString val(oneline);
						desc.x = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 17;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 22;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 12:
					{
						if ( _Is09(achar) ) {
							innerstate = 8;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 17:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 17;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 22;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 18:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 21;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 19;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 19:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 21;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 19;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 20:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
						} else if ( achar == ',' ) {
							innerstate = 21;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 21:
					{
						MGEString val(oneline);
						desc.y = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 27;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 32;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 22:
					{
						if ( _Is09(achar) ) {
							innerstate = 18;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 27:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 27;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 32;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 28:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 31;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 29;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 29:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 31;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 29;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 30:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
						} else if ( achar == ',' ) {
							innerstate = 31;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 31:
					{
						MGEString val(oneline);
						desc.z = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 37;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 42;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 32:
					{
						if ( _Is09(achar) ) {
							innerstate = 28;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;

					
				case 37:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 37;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 42;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 38:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ')' ) {
							innerstate = 41;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 39;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 39:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ')' ) {
							innerstate = 41;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 39;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 40:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
						} else if ( achar == ')' ) {
							innerstate = 41;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 41:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 41;
						} else if ( achar == 0 ) {
							MGEString val(oneline);
							desc.w = (float)StringtoDouble(val);
							innerstate = 43;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 42:
					{
						if ( _Is09(achar) ) {
							innerstate = 38;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;

				case 43:
					{
						des = desc;
						return TRUE;
					}
					break;
				case 0xFFFF:
					{
						return FALSE;
					}
					break;
				default:
					{
					}
					break;
			}
		}
	}
	return FALSE;
}
BOOL32 MGEConfig::ParseMatrix33f(MGEString &key, Matrix33f &des) {
	MGEString *result = (MGEString*)nameIndices.Get(key);
	if ( result != NULL ) {
		Matrix33f desc;
		const char *stream = result->GetBuffer();
		unsigned int i = 0;
		char achar = 0;
		unsigned short innerstate = 1;
		unsigned short linecount = 0;
		char oneline[256];
		while (TRUE) {
			achar = stream[i]; i++;
			switch (innerstate) {
				case 1:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 1;
						} else if ( achar == 'm' ) {
							innerstate = 2;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 2:
					{
						if ( achar == 'a' ) {
							innerstate = 3;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 3:
					{
						if ( achar == 't' ) {
							innerstate = 4;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 4:
					{
						if ( achar == '3' ) {
							innerstate = 5;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 5:
					{
						if ( achar == 'f' ) {
							innerstate = 6;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 6:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 6;
						} else if ( achar == '(' ) {
							innerstate = 7;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 7:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 7;
						} else if ( _Is09(achar) ) {
							innerstate = 8;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 12;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 8:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 11;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 8;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 9;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 9:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 11;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 9;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 10:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
						} else if ( achar == ',' ) {
							innerstate = 11;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 11:
					{
						MGEString val(oneline);
						desc.m[0][0] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 17;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 22;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 12:
					{
						if ( _Is09(achar) ) {
							innerstate = 8;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 17:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 17;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 22;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 18:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 21;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 19;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 19:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 21;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 19;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 20:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
						} else if ( achar == ',' ) {
							innerstate = 21;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 21:
					{
						MGEString val(oneline);
						desc.m[0][1] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 27;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 32;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 22:
					{
						if ( _Is09(achar) ) {
							innerstate = 18;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 27:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 27;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 32;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 28:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 31;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 29;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 29:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 31;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 29;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 30:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
						} else if ( achar == ',' ) {
							innerstate = 31;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 31:
					{
						MGEString val(oneline);
						desc.m[0][2] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 37;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 42;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 32:
					{
						if ( _Is09(achar) ) {
							innerstate = 28;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 37:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 37;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 42;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 38:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 41;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 39;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 39:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 41;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 39;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 40:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
						} else if ( achar == ',' ) {
							innerstate = 41;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 41:
					{
						MGEString val(oneline);
						desc.m[1][0] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 47;
						} else if ( _Is09(achar) ) {
							innerstate = 48;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 52;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 42:
					{
						if ( _Is09(achar) ) {
							innerstate = 38;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 47:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 47;
						} else if ( _Is09(achar) ) {
							innerstate = 48;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 52;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 48:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 50;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 51;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 48;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 49;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 49:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 50;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 51;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 49;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 50:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 50;
						} else if ( achar == ',' ) {
							innerstate = 51;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 51:
					{
						MGEString val(oneline);
						desc.m[1][1] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 57;
						} else if ( _Is09(achar) ) {
							innerstate = 58;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 62;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 52:
					{
						if ( _Is09(achar) ) {
							innerstate = 48;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 57:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 57;
						} else if ( _Is09(achar) ) {
							innerstate = 58;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 62;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 58:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 60;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 61;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 58;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 59;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 59:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 60;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 61;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 59;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 60:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 60;
						} else if ( achar == ',' ) {
							innerstate = 61;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 61:
					{
						MGEString val(oneline);
						desc.m[1][2] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 67;
						} else if ( _Is09(achar) ) {
							innerstate = 68;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 72;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 62:
					{
						if ( _Is09(achar) ) {
							innerstate = 58;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 67:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 67;
						} else if ( _Is09(achar) ) {
							innerstate = 68;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 72;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 68:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 70;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 71;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 68;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 69;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 69:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 70;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 71;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 69;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 70:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 70;
						} else if ( achar == ',' ) {
							innerstate = 71;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 71:
					{
						MGEString val(oneline);
						desc.m[2][0] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 77;
						} else if ( _Is09(achar) ) {
							innerstate = 78;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 82;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 72:
					{
						if ( _Is09(achar) ) {
							innerstate = 68;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 77:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 77;
						} else if ( _Is09(achar) ) {
							innerstate = 78;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 82;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 78:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 80;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 81;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 78;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 79;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 79:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 80;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 81;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 79;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 80:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 80;
						} else if ( achar == ',' ) {
							innerstate = 81;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 81:
					{
						MGEString val(oneline);
						desc.m[2][1] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 87;
						} else if ( _Is09(achar) ) {
							innerstate = 88;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 92;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 82:
					{
						if ( _Is09(achar) ) {
							innerstate = 78;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 87:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 87;
						} else if ( _Is09(achar) ) {
							innerstate = 88;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 92;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 88:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 90;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ')' ) {
							innerstate = 91;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 88;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 89;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 89:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 90;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ')' ) {
							innerstate = 91;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 89;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 90:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 90;
						} else if ( achar == ')' ) {
							innerstate = 91;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 91:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 91;
						} else if ( achar == 0 ) {
							MGEString val(oneline);
							desc.m[2][2] = (float)StringtoDouble(val);
							innerstate = 93;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 92:
					{
						if ( _Is09(achar) ) {
							innerstate = 88;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;

				case 93:
					{
						des = desc;
						return TRUE;
					}
					break;
				case 0xFFFF:
					{
						return FALSE;
					}
					break;
				default:
					{
					}
					break;
			}
		}
	}
	return FALSE;
}
BOOL32 MGEConfig::ParseMatrix44f(MGEString &key, Matrix44f &des) {
	MGEString *result = (MGEString*)nameIndices.Get(key);
	if ( result != NULL ) {
		Matrix44f desc;
		const char *stream = result->GetBuffer();
		unsigned int i = 0;
		char achar = 0;
		unsigned short innerstate = 1;
		unsigned short linecount = 0;
		char oneline[256];
		while (TRUE) {
			achar = stream[i]; i++;
			switch (innerstate) {
				case 1:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 1;
						} else if ( achar == 'm' ) {
							innerstate = 2;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 2:
					{
						if ( achar == 'a' ) {
							innerstate = 3;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 3:
					{
						if ( achar == 't' ) {
							innerstate = 4;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 4:
					{
						if ( achar == '4' ) {
							innerstate = 5;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 5:
					{
						if ( achar == 'f' ) {
							innerstate = 6;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 6:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 6;
						} else if ( achar == '(' ) {
							innerstate = 7;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 7:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 7;
						} else if ( _Is09(achar) ) {
							innerstate = 8;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 12;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 8:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 11;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 8;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 9;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 9:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 11;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 9;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 10:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 10;
						} else if ( achar == ',' ) {
							innerstate = 11;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 11:
					{
						MGEString val(oneline);
						desc.m[0][0] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 17;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 22;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 12:
					{
						if ( _Is09(achar) ) {
							innerstate = 8;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 17:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 17;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 22;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 18:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 21;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 18;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 19;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 19:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 21;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 19;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 20:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 20;
						} else if ( achar == ',' ) {
							innerstate = 21;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 21:
					{
						MGEString val(oneline);
						desc.m[0][1] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 27;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 32;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 22:
					{
						if ( _Is09(achar) ) {
							innerstate = 18;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 27:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 27;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 32;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 28:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 31;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 28;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 29;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 29:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 31;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 29;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 30:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 30;
						} else if ( achar == ',' ) {
							innerstate = 31;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 31:
					{
						MGEString val(oneline);
						desc.m[0][2] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 37;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 42;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 32:
					{
						if ( _Is09(achar) ) {
							innerstate = 28;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 37:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 37;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 42;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 38:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 41;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 38;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 39;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 39:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 41;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 39;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 40:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 40;
						} else if ( achar == ',' ) {
							innerstate = 41;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 41:
					{
						MGEString val(oneline);
						desc.m[0][3] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 47;
						} else if ( _Is09(achar) ) {
							innerstate = 48;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 52;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 42:
					{
						if ( _Is09(achar) ) {
							innerstate = 38;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 47:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 47;
						} else if ( _Is09(achar) ) {
							innerstate = 48;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 52;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 48:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 50;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 51;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 48;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 49;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 49:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 50;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 51;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 49;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 50:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 50;
						} else if ( achar == ',' ) {
							innerstate = 51;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 51:
					{
						MGEString val(oneline);
						desc.m[1][0] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 57;
						} else if ( _Is09(achar) ) {
							innerstate = 58;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 62;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 52:
					{
						if ( _Is09(achar) ) {
							innerstate = 48;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 57:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 57;
						} else if ( _Is09(achar) ) {
							innerstate = 58;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 62;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 58:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 60;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 61;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 58;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 59;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 59:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 60;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 61;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 59;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 60:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 60;
						} else if ( achar == ',' ) {
							innerstate = 61;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 61:
					{
						MGEString val(oneline);
						desc.m[1][1] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 67;
						} else if ( _Is09(achar) ) {
							innerstate = 68;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 72;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 62:
					{
						if ( _Is09(achar) ) {
							innerstate = 58;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 67:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 67;
						} else if ( _Is09(achar) ) {
							innerstate = 68;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 72;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 68:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 70;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 71;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 68;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 69;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 69:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 70;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 71;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 69;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 70:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 70;
						} else if ( achar == ',' ) {
							innerstate = 71;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 71:
					{
						MGEString val(oneline);
						desc.m[1][2] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 77;
						} else if ( _Is09(achar) ) {
							innerstate = 78;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 82;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 72:
					{
						if ( _Is09(achar) ) {
							innerstate = 68;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;


				case 77:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 77;
						} else if ( _Is09(achar) ) {
							innerstate = 78;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 82;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 78:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 80;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 81;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 78;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 79;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 79:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 80;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 81;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 79;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 80:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 80;
						} else if ( achar == ',' ) {
							innerstate = 81;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 81:
					{
						MGEString val(oneline);
						desc.m[1][3] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 87;
						} else if ( _Is09(achar) ) {
							innerstate = 88;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 92;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 82:
					{
						if ( _Is09(achar) ) {
							innerstate = 78;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 87:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 87;
						} else if ( _Is09(achar) ) {
							innerstate = 88;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 92;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 88:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 90;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 91;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 88;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 89;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 89:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 90;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 91;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 89;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 90:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 90;
						} else if ( achar == ',' ) {
							innerstate = 91;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 91:
					{
						MGEString val(oneline);
						desc.m[2][0] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 97;
						} else if ( _Is09(achar) ) {
							innerstate = 98;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 102;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 92:
					{
						if ( _Is09(achar) ) {
							innerstate = 88;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 97:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 97;
						} else if ( _Is09(achar) ) {
							innerstate = 98;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 102;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 98:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 100;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 101;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 98;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 99;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 99:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 100;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 101;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 99;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 100:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 100;
						} else if ( achar == ',' ) {
							innerstate = 101;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 101:
					{
						MGEString val(oneline);
						desc.m[2][1] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 107;
						} else if ( _Is09(achar) ) {
							innerstate = 108;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 112;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 102:
					{
						if ( _Is09(achar) ) {
							innerstate = 98;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 107:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 107;
						} else if ( _Is09(achar) ) {
							innerstate = 108;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 112;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 108:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 110;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 111;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 108;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 109;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 109:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 110;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 111;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 109;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 110:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 110;
						} else if ( achar == ',' ) {
							innerstate = 111;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 111:
					{
						MGEString val(oneline);
						desc.m[2][2] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 117;
						} else if ( _Is09(achar) ) {
							innerstate = 118;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 122;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 112:
					{
						if ( _Is09(achar) ) {
							innerstate = 108;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 117:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 117;
						} else if ( _Is09(achar) ) {
							innerstate = 118;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 122;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 118:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 120;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 121;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 118;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 119;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 119:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 120;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 121;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 119;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 120:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 120;
						} else if ( achar == ',' ) {
							innerstate = 121;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 121:
					{
						MGEString val(oneline);
						desc.m[2][3] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 127;
						} else if ( _Is09(achar) ) {
							innerstate = 128;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 132;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 122:
					{
						if ( _Is09(achar) ) {
							innerstate = 118;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 127:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 127;
						} else if ( _Is09(achar) ) {
							innerstate = 128;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 132;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 128:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 130;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 131;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 128;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 129;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 129:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 130;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 131;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 129;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 130:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 130;
						} else if ( achar == ',' ) {
							innerstate = 131;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 131:
					{
						MGEString val(oneline);
						desc.m[3][0] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 137;
						} else if ( _Is09(achar) ) {
							innerstate = 138;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 142;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 132:
					{
						if ( _Is09(achar) ) {
							innerstate = 128;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 137:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 137;
						} else if ( _Is09(achar) ) {
							innerstate = 138;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 142;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 138:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 140;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 141;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 138;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 139;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 139:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 140;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 141;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 139;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 140:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 140;
						} else if ( achar == ',' ) {
							innerstate = 141;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 141:
					{
						MGEString val(oneline);
						desc.m[3][1] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 147;
						} else if ( _Is09(achar) ) {
							innerstate = 148;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 152;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 142:
					{
						if ( _Is09(achar) ) {
							innerstate = 138;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 147:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 147;
						} else if ( _Is09(achar) ) {
							innerstate = 148;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 152;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 148:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 150;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 151;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 148;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 149;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 149:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 150;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ',' ) {
							innerstate = 151;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 149;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 150:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 150;
						} else if ( achar == ',' ) {
							innerstate = 151;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 151:
					{
						MGEString val(oneline);
						desc.m[3][2] = (float)StringtoDouble(val);
						if ( _IsSpace(achar) ) {
							innerstate = 157;
						} else if ( _Is09(achar) ) {
							innerstate = 158;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 162;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 152:
					{
						if ( _Is09(achar) ) {
							innerstate = 148;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;



				case 157:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 157;
						} else if ( _Is09(achar) ) {
							innerstate = 158;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '-' ) {
							innerstate = 162;
							linecount = 0;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 158:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 160;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ')' ) {
							innerstate = 161;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 158;
							oneline[linecount] = achar;
							linecount ++;
						} else if ( achar == '.' ) {
							innerstate = 159;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 159:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 160;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( achar == ')' ) {
							innerstate = 161;
							oneline[linecount] = 0;
							linecount = 0;
						} else if ( _Is09(achar) ) {
							innerstate = 159;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 160:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 160;
						} else if ( achar == ')' ) {
							innerstate = 161;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 161:
					{
						if ( _IsSpace(achar) ) {
							innerstate = 161;
						} else if ( achar == 0 ) {
							MGEString val(oneline);
							desc.m[3][3] = (float)StringtoDouble(val);
							innerstate = 163;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;
				case 162:
					{
						if ( _Is09(achar) ) {
							innerstate = 158;
							oneline[linecount] = achar;
							linecount ++;
						} else {
							innerstate = 0xFFFF;
						}
					}
					break;

				case 163:
					{
						des = desc;
						return TRUE;
					}
					break;
				case 0xFFFF:
					{
						return FALSE;
					}
					break;
				default:
					{
					}
					break;
			}
		}
	}
	return FALSE;
}
BOOL32 MGEConfig::GetString(MGEString &key, MGEString &des) {
	MGEString *result = (MGEString*)nameIndices.Get(key);
	if ( result != NULL ) {
		des = *result;
		return TRUE;
	}
	return FALSE;
}

