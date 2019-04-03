///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)	v2	Copyright 2018
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _BASE_HPP_
#define _BASE_HPP_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"


extern "C" template class MGERefArray<MGEString>;
extern "C" template class MGERefArray<MGETString>;
extern "C" template class MGERefArray<MGEWString>;

extern "C" template class MGERefArray<MGE2Variant>;


#endif

