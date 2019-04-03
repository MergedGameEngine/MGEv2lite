///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_EXPORT


#include "Type.h"
#include "Base.h"
#include "stdio.h"
#include "string.h"
#include "CRC32.h"
#define _ARRAY_API _BASE_API
#include "Array.h"
#include "RefArray.h"
#include "RefArray.hpp"

typedef MGEDataArray<unsigned short> MGEUShortArray;
extern "C" template class MGERefArray<MGEUShortArray>;
//extern "C" template class MGERefArray<MGEString>;
//extern "C" template class MGERefArray<MGETString>;
//extern "C" template class MGERefArray<MGEWString>;

