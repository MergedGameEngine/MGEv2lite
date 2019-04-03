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
#undef GetClassName
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "GLParameter.hpp"
//#include "ShaderParameter.hpp"

MGE2GLParameter::MGE2GLParameter() {
}

MGE2GLParameter::~MGE2GLParameter() {
}

const char *MGE2GLParameter::GetClassName() {
	return "MGE2GLParameter";
}

BOOL32 MGE2GLParameter::IsInstanceof(const char* className) {
	if (strcmp("MGE2GLParameter", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGE2GLParameter::SetCode(unsigned short code) {
	parameterCode = code;
}
void MGE2GLParameter::SetName(GLchar *name) {
	if ( strlen (name) < 127 ) {
		strcpy(parameterName, name);
	}
}
void MGE2GLParameter::SetLocation(GLuint program) {
	if ( ( parameterCode & 0xFF00 ) == 0x0000 ) {
		location = glGetAttribLocation(program, parameterName);
	} else {
		location = glGetUniformLocation(program, parameterName);
	}
}
unsigned short MGE2GLParameter::GetCode() {
	return parameterCode;
}
GLchar *MGE2GLParameter::GetName() {
	return parameterName;
}
GLint MGE2GLParameter::GetLocation() {
	return location;
}
