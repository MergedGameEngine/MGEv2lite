///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _INTERFACE_MESHOBJECT_HPP_
#define _INTERFACE_MESHOBJECT_HPP_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "InterfaceVMeshObject.h"
extern "C" template class MGERefArray<MGE2MeshObject>;
typedef MGERefArray<MGE2MeshObject> MGE2MeshObjectArray;
extern "C" template class MGERefArray<MGE2MeshObjectArray>;

#endif

