///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)	v2	Copyright 2018
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _MATHTOOL_HPP_
#define _MATHTOOL_HPP_

#include "math.h"

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

extern "C" template class MGEDataArray<unsigned short>;
extern "C" template class MGEDataArray<float>;
typedef MGEDataArray<unsigned short> TUShortArray;
extern "C" template class MGERefArray<TUShortArray>;
extern "C" template class MGEDataArray<Triangle>;
extern "C" template class MGEDataArray<TexCoord2f>;
extern "C" template class MGEDataArray<Vector3f>;
extern "C" template class MGEDataArray<Vector4f>;
extern "C" template class MGEDataArray<Matrix22f>;
extern "C" template class MGEDataArray<Matrix33f>;
extern "C" template class MGEDataArray<Matrix44f>;
extern "C" template class MGEDataArray<Matrix34f>;
extern "C" template class MGEDataArray<Quaternion>;
extern "C" template class MGEDataArray<Transform>;

#endif



