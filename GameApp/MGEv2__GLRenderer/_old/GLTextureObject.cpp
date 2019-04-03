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
//#include "GLee.h"
#undef GetClassName
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "GLTextureObject.hpp"

MGE2GLTextureObject::MGE2GLTextureObject() {
	textureIndex = 0xFFFFFFFF;
	typesize = 0;
	textureBuffer = NULL;
	height = 0;
	width = 0;
	colordeepth = 0;
	index = 0;
	target = GL_TEXTURE_2D;
}

MGE2GLTextureObject::~MGE2GLTextureObject() {
}

const char *MGE2GLTextureObject::GetClassName() {
	return "MGE2GLTextureObject";
}

BOOL32 MGE2GLTextureObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2GLTextureObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGE2GLTextureObject::SetTextureBuffer(
	unsigned int h, unsigned int w, unsigned char cd, unsigned char ts, const void *src)
{
	height = h;
	width = w;
	colordeepth = cd;
	typesize = ts;
	if ( src != NULL ) {
		memcpy ( textureBuffer, src, h * w * cd * ts );
	} else {
		textureBuffer = 0;
	}
}

void MGE2GLTextureObject::SetTarget(GLenum tar) {
	target = tar;
}


void MGE2GLTextureObject::GenTexture() {
	glGenTextures(1, &textureIndex);
}

void MGE2GLTextureObject::TextureParameter(GLenum pname, GLenum param) {
	glTexParameteri(target, pname, param);
}

void MGE2GLTextureObject::TextureParameter(unsigned int swarp, unsigned int twarp, unsigned int minl, unsigned int magl, unsigned int isgm) {
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minl);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magl);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, swarp);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, twarp);
	glTexParameteri(target, GL_GENERATE_MIPMAP, isgm);
}

void MGE2GLTextureObject::TextureParameter() {
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_GENERATE_MIPMAP, GL_TRUE);
}

void MGE2GLTextureObject::TextureImage2D(GLint level, GLint internalformat, GLint border, GLenum format, GLenum type) {
	glTexImage2D(target, level, internalformat, width, height, border, format, type, textureBuffer);
}

void MGE2GLTextureObject::CompressedTexImage2D(GLint level, GLenum internalformat, GLint border, GLsizei imageSize) {
	glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, textureBuffer);
}

void MGE2GLTextureObject::ReadPixels(GLenum format, GLenum type) {
	glReadPixels(0, 0, width, height, format, type, NULL);
}

void MGE2GLTextureObject::ReadPixels(GLint x, GLint y, GLsizei w, GLsizei h, GLenum format, GLenum type, GLvoid *buf) {
	glReadPixels(x, y, w, h, format, type, buf);
}

void MGE2GLTextureObject::GenerateMipmap() {
	glGenerateMipmapEXT(target);
}

void MGE2GLTextureObject::BindTexture() {
	glBindTexture(target, textureIndex);
}

void MGE2GLTextureObject::ActiveTexture() {
	glActiveTexture(GL_TEXTURE0 + index);
}

void MGE2GLTextureObject::UnbindTexture() {
}
void MGE2GLTextureObject::DeleteTexture() {
	glDeleteTextures(1, &textureIndex);
}

GLuint MGE2GLTextureObject::GetTextureIndex() {
	return textureIndex;
}

void MGE2GLTextureObject::SetIndex(unsigned char i) {
	index = i % 32;
}

unsigned char MGE2GLTextureObject::GetIndex() {
	return index;
}

void MGE2GLTextureObject::TextureImage2D(unsigned char _colordeepth) {
	if ( _colordeepth == 1 ) {
		TextureImage2D(0, GL_LUMINANCE, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE);
	}
	if ( _colordeepth == 3 ) {
		TextureImage2D(0, GL_RGB, 0, GL_BGR, GL_UNSIGNED_BYTE);
	}
	if ( _colordeepth == 4 ) {
		TextureImage2D(0, GL_RGBA, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	}
}
