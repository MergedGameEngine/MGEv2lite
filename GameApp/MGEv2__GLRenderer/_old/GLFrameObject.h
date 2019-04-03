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

//public:
//	void Set(Vector3f &cam, Vector3f &cen, Vector3f &up);
//	void GetCamera(Vector3f &cam);
//	void GetCenter(Vector3f &cen);
//	void GetCameraUp(Vector3f &up);
//public:
//	void CameraCentered(Vector3f &cam, float _distance, float _ha, float _va);
//	void ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va);
//	void CameraCentered(Vector3f &cam, float _distance, float _ha, float _va, float _aa);
//	void ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va, float _aa);
//	void CameraCenteredOrbit(Vector3f &cam, float _distance, float _ha, float _va, float _aa);
//	void ObjectCenteredOrbit(Vector3f &obj, float _distance, float _ha, float _va, float _aa);
//public:
//	void GenViewCoordinate();
//	void LookAt();
//	void TranslateViewPort(Vector3f &trans);
//
//	void MoveForward(float scale);
//	void MoveBackward(float scale);
//	void MoveLeft(float scale);
//	void MoveRight(float scale);
//	void MoveUp(float scale);
//	void MoveDown(float scale);
//
//	void RotateViewPort(float x, float y, float z);// Deprecated
//	void RotateHorizontal(float angle);// Deprecated
//	void RotateVertical(float angle);// Deprecated
//	void RotateAxis(float angle);// Deprecated

public:
	void LookAt();// Deprecated
	virtual void SetViewPort();
public:
	void Ortho();
	void Ortho(double znear, double zfar);
	void Ortho(double left, double right, double buttom, double top, double znear, double zfar);

	void DrawRect();
	void DrawRect(float left, float right, float buttom, float top);

public:
	void RenderFrame();

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
