///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _RENDERER_EXPORT

#include "string.h"
#include "stdio.h"
#undef GetClassName
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "GLRendererContext.h"
#include "GLFrameObject.hpp"

#include "GLTextureObject.hpp"
#include "GLMeshObject.hpp"
#include "GLShaderObject.hpp"
#include "GLParameter.hpp"

#include "GLRendererObject.hpp"
//#include "ShaderParameter.hpp"

MGE2GLRendererContext::MGE2GLRendererContext() {
}

MGE2GLRendererContext::~MGE2GLRendererContext() {
}

const char *MGE2GLRendererContext::GetClassName() {
	return "MGE2GLRendererContext";
}

BOOL32 MGE2GLRendererContext::IsInstanceof(const char* className) {
	if (strcmp("MGE2GLRendererContext", className) == 0) {
		return TRUE;
	}
	return FALSE;
}
