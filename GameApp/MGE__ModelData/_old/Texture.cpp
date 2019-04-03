///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MODEL_EXPORT

#include "string.h"
//#include "..\Base\CRC32.h"
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "Texture.hpp"

MGETextureData::MGETextureData() {
}

MGETextureData::~MGETextureData() {
}


const char *MGETextureData::GetClassName() {
	return "MGETextureData";
}

BOOL32 MGETextureData::IsInstanceof(const char* className) {
	if (strcmp("MGETextureData", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGETextureData::Set(unsigned short w, unsigned short h, unsigned char cd, void *buf) {
	width = w;
	height = h;
	colordeepth = cd;
	buffer = buf;
}
void MGETextureData::Get(unsigned short &w, unsigned short &h, unsigned char &cd, void *&buf) {
	w = width;
	h = height;
	cd = colordeepth;
	buf = buffer;
}

