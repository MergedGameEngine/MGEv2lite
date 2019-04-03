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
#include "GLFrameObject.hpp"

#include "GLTextureObject.hpp"
#include "GLMeshObject.hpp"
#include "GLShaderObject.hpp"
#include "GLParameter.hpp"

#include "GLRendererObject.hpp"
//#include "ShaderParameter.hpp"

MGE2GLFrameObject::MGE2GLFrameObject() {
	__fb = 0xFFFFFFFF;	// color render target
	__rb = 0xFFFFFFFF;	// depth render target
	__to = 0xFFFFFFFF;	// texture


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
	unsigned int _i4 = renderSequence.GetLength();
	unsigned int _i2 = rendererReferences.GetLength();
	unsigned int _i3 = 0;
	unsigned int _i1 = 0;

	for ( _i3 = 0 ; _i3 < _i4 ; _i3 ++ ) {
		_i1 = renderSequence[_i3];
		if ( _i1 < _i2 ) {
			MGE2GLRendererObject &_ro = *(MGE2GLRendererObject*)&rendererReferences[_i1];
			_ro.RenderUnit();
		}
	}
}

void MGE2GLFrameObject::LookAt() {
	glMultMatrixf((GLfloat*)&viewCoord);
	glTranslated (-camera.x, -camera.y, -camera.z);
}

void MGE2GLFrameObject::SetViewPort() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((GLfloat*)&viewCoord);
	glTranslated (-camera.x, -camera.y, -camera.z);
}

void MGE2GLFrameObject::SetProjection() {
	if ( renderMode != 0 ) {
		////viewPortWidth = (float)frameBufferWidth;
		////viewPortHeight = (float)frameBufferHeight;
		glViewport(0, 0, frameBufferWidth, frameBufferHeight);
	} else {
		glViewport(0, 0, (int)viewPortWidth, (int)viewPortHeight);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (viewPortWidth >= viewPortHeight)	{
		GLdouble ar = (GLdouble)viewPortWidth / (GLdouble)viewPortHeight;
		glFrustum(-ar * cameraZoom, ar * cameraZoom, -cameraZoom, cameraZoom, 1.0, 1000.0);
	} else {
		GLdouble ar = (GLdouble)viewPortHeight / (GLdouble)viewPortWidth;
		glFrustum(-cameraZoom, cameraZoom, -ar * cameraZoom, ar * cameraZoom, 1.0, 1000.0);
	}
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

void MGE2GLFrameObject::FillViewPort() {
	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2d(1.0,0.0);glVertex3f(viewPortWidth, 0.0f, 0.0f);
		glTexCoord2d(1.0,1.0);glVertex3f(viewPortWidth, viewPortHeight, 0.0f);
		glTexCoord2d(0.0,1.0);glVertex3f(0.0f, viewPortHeight, 0.0f);
	glEnd();
}
void MGE2GLFrameObject::FillViewPort(float left, float right, float buttom, float top) {
	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);glVertex3f(left, buttom, 0.0f);
		glTexCoord2d(1.0,0.0);glVertex3f(right, buttom, 0.0f);
		glTexCoord2d(1.0,1.0);glVertex3f(right, top, 0.0f);
		glTexCoord2d(0.0,1.0);glVertex3f(left, top, 0.0f);
	glEnd();
}

void MGE2GLFrameObject::CheckFrameBufferStatus() {
	GLenum status;
	status = (GLenum) glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch(status) {
		case GL_FRAMEBUFFER_COMPLETE:
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			printf("Unsupported framebuffer format\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			printf("Framebuffer incomplete, missing attachment\n");
			break;
		//case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT:
		//	printf("Framebuffer incomplete, duplicate attachment\n");
		//	break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			printf("Framebuffer incomplete, attached images must have same dimensions\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			printf("Framebuffer incomplete, attached images must have same format\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			printf("Framebuffer incomplete, missing draw buffer\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			printf("Framebuffer incomplete, missing read buffer\n");
			break;
		default:
			break;
	}
}


void MGE2GLFrameObject::CreateFrameBuffer(unsigned int _mode) {
	renderMode = _mode;
	if ( __fb != 0xFFFFFFFF ) {
		return;
	}
	if ( renderMode == _FRAMEBUFFER_RENDERBUFFER_ ) {
		glGenFramebuffers(1, &__fb);
		glGenTextures(1, &__to);
		glGenRenderbuffers(1, &__rb);

		glBindFramebuffer(GL_FRAMEBUFFER, __fb);    

		// init texture
		glBindTexture(GL_TEXTURE_2D, __to);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, frameBufferWidth, frameBufferHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		///GET_GLERROR(NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, __to, 0);

		///GET_GLERROR(0);

		// initialize depth renderbuffer
		glBindRenderbuffer(GL_RENDERBUFFER, __rb);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, frameBufferWidth, frameBufferHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, __rb);

		///GET_GLERROR(0);

		CheckFrameBufferStatus();
    
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	} else {
		__depth = 2048;

		glGenFramebuffers(1, &__fb);
		glBindFramebuffer(GL_FRAMEBUFFER, __fb);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE); 
		CheckFrameBufferStatus();
    
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glGenTextures(1, &__to);

		glFramebufferTexture2D(	GL_FRAMEBUFFER,
								GL_DEPTH_ATTACHMENT,
								GL_TEXTURE_2D, 
								__to,
								0);
		glBindTexture(GL_TEXTURE_2D, __to);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24_ARB, frameBufferWidth, frameBufferHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

		glBindTexture(GL_TEXTURE_2D, 0);


		//glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, __to);

		//glTexImage3D(GL_TEXTURE_2D_ARRAY_EXT, 0, GL_DEPTH_COMPONENT24, __depth, __depth, 4, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		//glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}
}

void MGE2GLFrameObject::DeleteFrameBuffer() {
	glDeleteRenderbuffers(1, &__rb);
	glDeleteTextures(1, &__to);
	glDeleteFramebuffers(1, &__fb);

	__fb = 0xFFFFFFFF;
	__rb = 0xFFFFFFFF;
	__to = 0xFFFFFFFF;
}

void MGE2GLFrameObject::BindFrameBuffer() {
	if ( renderMode == _FRAMEBUFFER_RENDERBUFFER_ ) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, __fb);
			glPushAttrib(GL_VIEWPORT_BIT); 
	//        glViewport(0, 0, viewPortWidth, viewPortHeight);
	} else {
		glDisable(GL_TEXTURE_2D);
		// redirect rendering to the depth texture
		glBindFramebufferEXT(GL_FRAMEBUFFER, __fb);
			// store the screen viewport
			glPushAttrib(GL_VIEWPORT_BIT);
			// and render only to the shadowmap
			glViewport(0, 0, __depth, __depth);
			// offset the geometry slightly to prevent z-fighting
			// note that this introduces some light-leakage artifacts
			glPolygonOffset( 1.0f, 4096.0f);
			glEnable(GL_POLYGON_OFFSET_FILL);

			// draw all faces since our terrain is not closed.
			glDisable(GL_CULL_FACE);
	}
}

void MGE2GLFrameObject::UnbindFrameBuffer() {
	if ( renderMode == _FRAMEBUFFER_RENDERBUFFER_ ) {
			glPopAttrib();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	} else {
			// revert to normal back face culling as used for rendering
			glEnable(GL_CULL_FACE);

			glDisable(GL_POLYGON_OFFSET_FILL);
			glPopAttrib(); 
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);

		glEnable(GL_TEXTURE_2D);
	}
}

void MGE2GLFrameObject::DrawFrameBufferTexture(float left, float right, float buttom, float top) {
 
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


	glTranslatef(-1.0,-0.5,-2.0);


	glBindTexture(GL_TEXTURE_2D, __to);
	glEnable(GL_TEXTURE_2D);  

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0);         glVertex2f(-0.25, -0.25);
        glTexCoord2f(1, 0);         glVertex2f( 0.25, -0.25);
        glTexCoord2f(1, 1);         glVertex2f( 0.25,  0.25);
        glTexCoord2f(0, 1);         glVertex2f(-0.25,  0.25);
    }
    glEnd();


	glPopMatrix();

 }


