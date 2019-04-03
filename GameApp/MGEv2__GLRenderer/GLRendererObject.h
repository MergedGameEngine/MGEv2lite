///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _GLRENDEREROBJECT_H_
#define _GLRENDEREROBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGEv2__Game/InterfaceVRendererObject.h"
//#include "../MGE__MathTool/MathTool.hpp"
#include "GL/glew.h"

extern "C" class MGE2GLRendererObject : public MGE2RendererObject {
public:
	MGE2GLRendererObject();
	virtual ~MGE2GLRendererObject();

public:
	void RenderUnit();

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
