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
#include "Array.hpp"

extern "C" template class MGEDataArray<int>;
extern "C" template class MGEDataArray<short>;
extern "C" template class MGEDataArray<char>;
extern "C" template class MGEDataArray<unsigned int>;
extern "C" template class MGEDataArray<unsigned short>;
extern "C" template class MGEDataArray<unsigned char>;
extern "C" template class MGEDataArray<float>;
extern "C" template class MGEDataArray<double>;

extern "C" template class MGEDataArray<void*>;
extern "C" template class MGEDataArray<long long>;
extern "C" template class MGEDataArray<unsigned long long>;

