///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _INTERFACE_SHADEROBJECT_H_
#define _INTERFACE_SHADEROBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
//#include "../MGE__MathTool/MathTool.hpp"

extern "C" class MGE2ShaderObject : public MGEObject {
public:
	MGE2ShaderObject();
	virtual ~MGE2ShaderObject();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
