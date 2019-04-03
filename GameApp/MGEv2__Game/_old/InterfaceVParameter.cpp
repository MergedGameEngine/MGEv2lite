///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#include "string.h"
#undef GetClassName

#include "InterfaceVParameter.hpp"


MGE2Parameter::MGE2Parameter() {
}

MGE2Parameter::~MGE2Parameter() {
}

const char *MGE2Parameter::GetClassName() {
	return "MGE2Parameter";
}

BOOL32 MGE2Parameter::IsInstanceof(const char* className) {
	if (strcmp("MGE2Parameter", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

