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
#include "GLFrameObject.hpp"

#include "GLTextureObject.hpp"
#include "GLMeshObject.hpp"
#include "GLShaderObject.hpp"
#include "GLParameter.hpp"
//#include "ShaderParameter.hpp"

MGE2GLFrameObject::MGE2GLFrameObject() {
	Vector3f _v0;
	Vector3f _v1(1.0f, 0.0f, 0.0f);
	Vector3f _v2(0.0f, 0.0f, 1.0f);
	Set(_v0, _v1, _v2);
}

MGE2GLFrameObject::~MGE2GLFrameObject() {
}

const char *MGE2GLFrameObject::GetClassName() {
	return "MGE2GLFrameObject";
}

BOOL32 MGE2GLFrameObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2GLFrameObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGE2GLFrameObject::RenderFrame() {
}

void MGE2GLFrameObject::LookAt() {
	glMultMatrixf((GLfloat*)&viewCoord);
	glTranslated (-camera.x, -camera.y, -camera.z);
}

void MGE2GLFrameObject::SetViewPort() {
	glMultMatrixf((GLfloat*)&viewCoord);
	glTranslated (-camera.x, -camera.y, -camera.z);
}



void MGE2GLFrameObject::Ortho() {
	glOrtho(0.0, viewPortWidth, 0.0, viewPortHeight, 1.0, 20.0);
}
void MGE2GLFrameObject::Ortho(double znear, double zfar) {
	glOrtho(0.0, viewPortWidth, 0.0, viewPortHeight, znear, zfar);
}
void MGE2GLFrameObject::Ortho(double left, double right, double buttom, double top, double znear, double zfar) {
	glOrtho(left, right, buttom, top, znear, zfar);
}

void MGE2GLFrameObject::DrawRect() {
	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2d(1.0,0.0);glVertex3f(viewPortWidth, 0.0f, 0.0f);
		glTexCoord2d(1.0,1.0);glVertex3f(viewPortWidth, viewPortHeight, 0.0f);
		glTexCoord2d(0.0,1.0);glVertex3f(0.0f, viewPortHeight, 0.0f);
	glEnd();
}
void MGE2GLFrameObject::DrawRect(float left, float right, float buttom, float top) {
	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(left, buttom, 0.0f);
		glTexCoord2d(1.0,0.0);glVertex3f(right, buttom, 0.0f);
		glTexCoord2d(1.0,1.0);glVertex3f(right, top, 0.0f);
		glTexCoord2d(0.0,1.0);glVertex3f(left, top, 0.0f);
	glEnd();
}
