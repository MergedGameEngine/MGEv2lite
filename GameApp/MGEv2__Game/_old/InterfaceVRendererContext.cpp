///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#include "string.h"
#undef GetClassName

#include "InterfaceVRendererContext.hpp"


MGE2RendererContext::MGE2RendererContext() {
}

MGE2RendererContext::~MGE2RendererContext() {
}

const char *MGE2RendererContext::GetClassName() {
	return "MGE2RendererContext";
}

BOOL32 MGE2RendererContext::IsInstanceof(const char* className) {
	if (strcmp("MGE2RendererContext", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

