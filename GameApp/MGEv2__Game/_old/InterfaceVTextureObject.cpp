///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#include "string.h"
#undef GetClassName

#include "InterfaceVTextureObject.hpp"


MGE2TextureObject::MGE2TextureObject() {
}

MGE2TextureObject::~MGE2TextureObject() {
}

const char *MGE2TextureObject::GetClassName() {
	return "MGE2TextureObject";
}

BOOL32 MGE2TextureObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2TextureObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGE2TextureObject::SetHeight(unsigned int h) {
	height = h;
}
void MGE2TextureObject::SetWidth(unsigned int w) {
	width = w;
}
void MGE2TextureObject::SetBuffer(void *buf) {
	textureBuffer = buf;
}
unsigned int MGE2TextureObject::GetHeight() {
	return height;
}
unsigned int MGE2TextureObject::GetWidth() {
	return width;
}
void *MGE2TextureObject::GetBuffer() {
	return textureBuffer;
}

void MGE2TextureObject::TextureImage2D(unsigned char _colordeepth) {
}

