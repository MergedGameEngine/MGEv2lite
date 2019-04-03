///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _GLRENDERERCONTEXT_H_
#define _GLRENDERERCONTEXT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGEv2__Game/InterfaceVRendererContext.h"
#include "GLFrameObject.hpp"

//#include "../MGE__MathTool/MathTool.hpp"
#include "GL/glew.h"

extern "C" class MGE2GLRendererContext : public MGE2RendererContext {
public:
	MGE2GLRendererContext();
	virtual ~MGE2GLRendererContext();
protected:
private:

public:

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
