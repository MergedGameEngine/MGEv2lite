///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#include "string.h"
#undef GetClassName

#include "InterfaceVShaderObject.hpp"


MGE2ShaderObject::MGE2ShaderObject() {
}

MGE2ShaderObject::~MGE2ShaderObject() {
}

const char *MGE2ShaderObject::GetClassName() {
	return "MGE2ShaderObject";
}

BOOL32 MGE2ShaderObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2ShaderObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

