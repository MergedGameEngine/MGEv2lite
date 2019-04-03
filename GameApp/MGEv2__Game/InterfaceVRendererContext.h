///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _INTERFACE_RENDERERCONTEXT_H_
#define _INTERFACE_RENDERERCONTEXT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
//#include "../MGE__MathTool/MathTool.hpp"

extern "C" class MGE2RendererContext : public MGEObject {
public:
	MGE2RendererContext();
	virtual ~MGE2RendererContext();
public:
	enum {
		_RENDERER_OPENGLES_ = 1,
		_RENDERER_OPENGL_ = 2,
		_RENDERER_VULKAN_ = 3,
	};

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
