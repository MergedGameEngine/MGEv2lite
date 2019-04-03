///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _GLFRAMEOBJECT_H_
#define _GLFRAMEOBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGEv2__Game/InterfaceVFrameObject.h"
//#include "../MGE__MathTool/MathTool.hpp"
#include "GL/glew.h"

extern "C" class MGE2GLFrameObject : public MGE2FrameObject {
public:
	MGE2GLFrameObject();
	virtual ~MGE2GLFrameObject();
protected:

public:
	MGEString imvParamName;

public:	

private:
	GLuint __fb;	// color render target
	GLuint __rb;	// depth render target
	GLuint __to;	// texture

	int __depth;
public:
	void CreateFrameBuffer(unsigned int _mode);
	void DeleteFrameBuffer();
	void BindFrameBuffer();
	void UnbindFrameBuffer();

public:
	void LookAt();// Deprecated
	virtual void SetViewPort();
	virtual void SetProjection();
public:
	void Ortho();
	void Ortho(double znear, double zfar);
	void Ortho(double left, double right, double buttom, double top, double znear, double zfar);

	void FillViewPort();
	void FillViewPort(float left, float right, float buttom, float top);

	void DrawFrameBufferTexture(float left, float right, float buttom, float top);

	void CheckFrameBufferStatus();


public:
	virtual void RenderFrame();


public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
