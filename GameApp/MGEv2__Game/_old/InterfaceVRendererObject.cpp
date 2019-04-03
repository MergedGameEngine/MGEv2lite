///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#include "string.h"
#undef GetClassName

#include "InterfaceVRendererObject.hpp"


MGE2RendererObject::MGE2RendererObject() {
}

MGE2RendererObject::~MGE2RendererObject() {
}

const char *MGE2RendererObject::GetClassName() {
	return "MGE2RendererObject";
}

BOOL32 MGE2RendererObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2RendererObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

