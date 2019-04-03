///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//		MathTool Templates
//

#define _BASE_IMPORT
#define _MATHTOOL_EXPORT

#include "string.h"
#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE__MathTool/MathTool.h"
#undef _ARRAY_API
#define _ARRAY_API _MATHTOOL_API
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"




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
typedef MGEDataArray<Matrix44f> Matrix44fArray;
extern "C" template class MGERefArray<Matrix44fArray>;
