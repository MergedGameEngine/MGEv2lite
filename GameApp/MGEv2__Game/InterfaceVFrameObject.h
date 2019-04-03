///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _INTERFACE_FRAMEOBJECT_H_
#define _INTERFACE_FRAMEOBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "InterfaceVMeshObject.hpp"
#include "InterfaceVParameter.hpp"
#include "InterfaceVShaderObject.hpp"
#include "InterfaceVTextureObject.hpp"

#include "InterfaceVRendererObject.hpp"

extern "C" class MGE2FrameObject : public MGEObject {
public:
	MGE2FrameObject();
	virtual ~MGE2FrameObject();

protected:
	Vector3f camera;
	Vector3f center;
	Vector3f cameraUp;
	Matrix44f viewCoord;
protected:
	unsigned int renderMode;

public:
	enum {
		_FRAMEBUFFER_RENDERBUFFER_ = 0x0001,
		_FRAMEBUFFER_STENCIL_ = 0x0002,
		_FRAMEBUFFER_DEPTH_	= 0x0003,
	};
public:
	int frameBufferHeight;//<<=== 4 FrameBufferObject
	int frameBufferWidth;//<<=== 4 FrameBufferObject

public:
	MGERefArray<MGE2RendererObject> rendererReferences;
	MGEDataArray<unsigned int> renderSequence;

public:
	float viewPortHeight;
	float viewPortWidth;
	double cameraZoom;

	//int iPortHeight;
	//int iPortWidth;
public:
	void Set(Vector3f &cam, Vector3f &cen, Vector3f &up);
	void GetCamera(Vector3f &cam);
	void GetCenter(Vector3f &cen);
	void GetCameraUp(Vector3f &up);
public:
	void CameraCentered(Vector3f &cam, float _distance, float _ha, float _va);
	void ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va);
	void CameraCentered(Vector3f &cam, float _distance, float _ha, float _va, float _aa);
	void ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va, float _aa);
	void CameraCenteredOrbit(Vector3f &cam, float _distance, float _ha, float _va, float _aa);
	void ObjectCenteredOrbit(Vector3f &obj, float _distance, float _ha, float _va, float _aa);
public:
	void GenViewCoordinate();

	void TranslateViewPort(Vector3f &trans);

	void MoveForward(float scale);
	void MoveBackward(float scale);
	void MoveLeft(float scale);
	void MoveRight(float scale);
	void MoveUp(float scale);
	void MoveDown(float scale);

	void RotateViewPort(float x, float y, float z);// Deprecated
	void RotateHorizontal(float angle);// Deprecated
	void RotateVertical(float angle);// Deprecated
	void RotateAxis(float angle);// Deprecated

public:
	virtual void SetViewPort();
	virtual void SetProjection();
	virtual void RenderFrame();
	
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
