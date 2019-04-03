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
//extern "C" template class MGERefArray<MGEConfig>;
#include "ConfigFile.h"

MGEConfigFile::MGEConfigFile() {
	errorLine = 0;
	isError = FALSE;
	names.Resize(0);
	values.Resize(0);
}
MGEConfigFile::~MGEConfigFile() {
	names.DeleteAll();
	names.Resize(0);
	values.DeleteAll();
	values.Resize(0);
}
const char *MGEConfigFile::GetClassName() {
	return "MGEConfigFile";
}
BOOL32 MGEConfigFile::IsInstanceof(const char* className) {
	if ( strcmp("MGEConfigFile", className) == 0 ) {
		return TRUE;
	}
	return FALSE;
}

void MGEConfigFile::Serialize(MGEIOStream &iio) {
	if ( iio.GetLoadStore() == MGEIOStream::load ) {
		//unsigned short nonwidthspace = 0;
		//iio.Read(&nonwidthspace, sizeof(unsigned short));
		//if ( nonwidthspace == 0xFEFF ) {
		//} else if ( nonwidthspace == 0xFFFE ) {
		//	iio.SetEndian(MGEIOStream::big_endian);
		//}
		Parse(iio);
	} else {
		MGEString se(" = ");
		MGEString enter(";\r\n");
		MGEString oneline;
		MGEString l("[");
		MGEString r("]");
		unsigned short f = 0xFEFF;
		iio.Write(&f, sizeof(unsigned short));
		unsigned int cl = names.GetLength();
		for ( unsigned int i2 = 0 ; i2 < cl ; i2 ++ ) {
			oneline = l + names[i2] + r + enter;
			oneline.Write(iio, oneline.GetLength());
			MGEConfig *cv = &values[i2];
			unsigned int vl = cv->GetValues().GetLength();
			MGERefArray<MGEString> &cnames = cv->GetNames();
			MGERefArray<MGEString> &cvalues = cv->GetValues();
			for ( unsigned int i3 = 0 ; i3 < vl ; i3 ++ ) {
				oneline = cnames[i3] + se + cvalues[i3] + enter;
				oneline.Write(iio, oneline.GetLength());
			}			
		}
	}
}

MGERefArray<MGEString> &MGEConfigFile::GetNames() {
	return names;
}
MGERefArray<MGEConfig> &MGEConfigFile::GetValues() {
	return values;
}
MGEConfig &MGEConfigFile::GetValue(MGEString &name) {
	return *(MGEConfig*)nameIndices.Get(name);
}
BOOL32 MGEConfigFile::IsError(unsigned short &eline) {
	eline = errorLine;
	return isError;
}

inline int _IsSpace(char chr) {
	if ( chr == 0x0020 ) {
		return TRUE;
	}
	if ( chr == 0x000B ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsAZaz(char chr) {
	if ( ( chr >= 0x0041 ) && ( chr <= 0x005A ) ) {
		return TRUE;
	}
	if ( ( chr >= 0x0061 ) && ( chr <= 0x007A ) ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsAZaz_(char chr) {
	if ( ( chr >= 0x0041 ) && ( chr <= 0x005A ) ) {
		return TRUE;
	}
	if ( ( chr >= 0x0061 ) && ( chr <= 0x007A ) ) {
		return TRUE;
	}
	if ( chr == '_' ) {
		return TRUE;
	} else
	if ( chr == '/' ) {
		return TRUE;
	} else
	if ( chr == '\\' ) {
		return TRUE;
	} 
	return FALSE;
}

inline int _Is09(char chr) {
	if ( ( chr >= 0x0030 ) && ( chr <= 0x0039 ) ) {
		return TRUE;
	}
	return FALSE;
}

inline int _Is_(char chr) {
	if ( chr == '_' ) {
		return TRUE;
	}
	return FALSE;
}

inline int _IsEnter(char chr) {
	if ( chr == 0x000D ) {
		return TRUE;
	}
	if ( chr == 0x000A ) {
		return TRUE;
	}
	return FALSE;
}

void MGEConfigFile::Parse(MGEIOStream &iio) {
	char achar = 0;
	char oneline[256];
	unsigned short linecount = 0;
	unsigned short innerstate = 1;
	MGEConfig *current = NULL;
	MGEString *name = NULL;
	MGEString *value = NULL;
	oneline[linecount] = 0;
	while(!iio.IsEoF()){
		iio.Read(&achar, sizeof(char));
		if ( iio.IsEoF() ) {
			achar = '\n';
		}
		if ( achar == '\r' ) {
			continue;
		}	//	Filter '\r'
		if ( achar == '\n' ) {
			errorLine ++;
		}
		switch (innerstate) {
			case 1:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 1;
					} else if ( _IsEnter(achar) ) {
						innerstate = 1;
					} else if ( achar == '[' ) {
						innerstate = 2;
					} else if ( achar == ';' ) {
						innerstate = 18;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 2:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 2;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
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
					if ( _IsAZaz_(achar) ) {
						innerstate = 3;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _Is09(achar) ) {
						innerstate = 3;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _IsSpace(achar) ) {
						innerstate = 4;
						oneline[linecount] = 0;
						linecount = 0;
					} else if ( achar == ']' ) {
						innerstate = 5;
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
					} else if ( achar == ']' ) {
						innerstate = 5;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 5:
				{
					current = new MGEConfig;
					values.Resize(values.GetLength() + 1);
					values.Set(values.GetLength() - 1, current);
					name = new MGEString(oneline);
					names.Resize(values.GetLength());
					names.Set(values.GetLength() - 1, name);
					nameIndices.Add(*name, current);
					if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( _IsSpace(achar) ) {
						innerstate = 17;
					} else if ( achar == ';' ) {
						innerstate = 14;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 6:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 6;
					} else if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ';') {
						innerstate = 14;
					} else if ( achar == '[') {
						innerstate = 2;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 7:
				{
					if ( _IsAZaz_(achar) ) {
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _Is09(achar) ) {
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _IsSpace(achar) ) {
						innerstate = 8;
					} else if ( achar == '=' ) {
						innerstate = 9;
						oneline[linecount] = 0;
						current->GetNames().Resize(current->GetNames().GetLength() + 1);
						current->GetValues().Resize(current->GetValues().GetLength() + 1);
						name = new MGEString(oneline);
						linecount = 0;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 8:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 8;
					} else if ( achar == '=' ) {
						innerstate = 9;
						oneline[linecount] = 0;
						current->GetNames().Resize(current->GetNames().GetLength() + 1);
						current->GetValues().Resize(current->GetValues().GetLength() + 1);
						name = new MGEString(oneline);
						linecount = 0;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 9:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 9;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _Is09(achar) ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '(' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ')' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ',' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '.' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '\\' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ':' ) {
						linecount = 0;
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '-' ) {
						linecount = 0;
						innerstate = 10;
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
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _IsAZaz_(achar) ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _Is09(achar) ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '(' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ')' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ',' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '.' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '\\' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ':' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '-' ) {
						innerstate = 10;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( _IsEnter(achar) ) {
						innerstate = 11;
						oneline[linecount] = 0;
						value = new MGEString(oneline);
						current->GetNames().Set(current->GetNames().GetLength() - 1, name);
						current->GetValues().Set(current->GetValues().GetLength() - 1, value);
						current->GetNameIndices().Add(*name, value);
						linecount = 0;
					} else if ( achar == ';' ) {
						innerstate = 12;
						oneline[linecount] = 0;
						value = new MGEString(oneline);
						current->GetNames().Set(current->GetNames().GetLength() - 1, name);
						current->GetValues().Set(current->GetValues().GetLength() - 1, value);
						current->GetNameIndices().Add(*name, value);
						linecount = 0;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 11:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 6;
					} else if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == ';' ) {
						innerstate = 14;
					} else if ( achar == '[' ) {
						innerstate = 2;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 12:
				{
					if ( _IsEnter(achar) ) {
						innerstate = 16;
					} else {
						innerstate = 15;
					}
				}
				break;
			case 14:
				{
					if ( _IsEnter(achar) ) {
						innerstate = 16;
					} else {
						innerstate = 15;
					}
				}
				break;
			case 15:
				{
					if ( _IsEnter(achar) ) {
						innerstate = 16;
					} else {
						innerstate = 15;
					}
				}
				break;
			case 16:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 6;
					} else if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( _IsAZaz_(achar) ) {
						linecount = 0;
						innerstate = 7;
						oneline[linecount] = achar;
						linecount ++;
					} else if ( achar == '[' ) {
						innerstate = 2;
					} else if ( achar == ';' ) {
						innerstate = 14;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 17:
				{
					if ( _IsSpace(achar) ) {
						innerstate = 17;
					} else if ( _IsEnter(achar) ) {
						innerstate = 6;
					} else if ( achar == ';' ) {
						innerstate = 14;
					} else {
						innerstate = 0xFFFF;
					}
				}
				break;
			case 18:
				{
					if ( _IsEnter(achar) ) {
						innerstate = 1;
					} else {
						innerstate = 18;
					}
				}
				break;
			case 0xFFFF:
				{
					isError = TRUE;
				}
				break;
			default:
				{
				}
				break;
		}
	}
}
