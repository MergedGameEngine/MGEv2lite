///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#include "string.h"
#undef GetClassName

#include "InterfaceVFrameObject.hpp"


MGE2FrameObject::MGE2FrameObject() {
}

MGE2FrameObject::~MGE2FrameObject() {
}

const char *MGE2FrameObject::GetClassName() {
	return "MGE2FrameObject";
}

BOOL32 MGE2FrameObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2FrameObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGE2FrameObject::Set(Vector3f &cam, Vector3f &cen, Vector3f &up) {
	camera = cam;
	center = cen;
	cameraUp = up;
	Vector3f f = center - camera;
	f = f.Normalized();
	Vector3f UP = cameraUp.Normalized();
	Vector3f s = f ^ UP;
	Vector3f u = s ^ f;
	viewCoord = Matrix44f(	s.x,	u.x,	-f.x,	0.0f, 
							s.y,	u.y,	-f.y,	0.0f,
							s.z,	u.z,	-f.z,	0.0f,
							0.0f,	0.0f,	0.0f,	1.0f);
}
void MGE2FrameObject::GetCamera(Vector3f &cam) {
	cam = camera;
}
void MGE2FrameObject::GetCenter(Vector3f &cen) {
	cen = center;
}
void MGE2FrameObject::GetCameraUp(Vector3f &up) {
	up = cameraUp;
}

void MGE2FrameObject::GenViewCoordinate() {
	Vector3f f = center - camera;
	f = f.Normalized();
	Vector3f UP = cameraUp.Normalized();
	Vector3f s = f ^ UP;
	Vector3f u = s ^ f;
	viewCoord = Matrix44f(	s.x,	u.x,	-f.x,	0.0f, 
							s.y,	u.y,	-f.y,	0.0f,
							s.z,	u.z,	-f.z,	0.0f,
							0.0f,	0.0f,	0.0f,	1.0f);
}

void MGE2FrameObject::TranslateViewPort(Vector3f &trans) {
	Vector3f delta = viewCoord * trans;
	camera = camera + delta;
}

void MGE2FrameObject::MoveForward(float scale) {
	Vector3f _v0(0.0f, 0.0f, -scale);
	TranslateViewPort(_v0);
}
void MGE2FrameObject::MoveBackward(float scale) {
	Vector3f _v0(0.0f, 0.0f, scale);
	TranslateViewPort(_v0);
}
void MGE2FrameObject::MoveLeft(float scale) {
	Vector3f _v0(-scale, 0.0f, 0.0f);
	TranslateViewPort(_v0);
}
void MGE2FrameObject::MoveRight(float scale) {
	Vector3f _v0(scale, 0.0f, 0.0f);
	TranslateViewPort(_v0);
}
void MGE2FrameObject::MoveUp(float scale) {
	Vector3f _v0(0.0f, scale, 0.0f);
	TranslateViewPort(_v0);
}
void MGE2FrameObject::MoveDown(float scale) {
	Vector3f _v0(0.0f, -scale, 0.0f);
	TranslateViewPort(_v0);
}

//	Deprecated ===== Begin
void MGE2FrameObject::RotateViewPort(float x, float y, float z) {
	Matrix33f mat;
	mat.fromEuler(x, y, z);
	Vector3f _v0;
	Matrix44f mat4(_v0, mat);
	viewCoord = mat4 * viewCoord;
}
void MGE2FrameObject::RotateHorizontal(float angle) {
	//float sine = sinf(angle);
	//float cosine = cosf(angle);

	//up.y = cosine * up.Magnitude();
	//up.z = sine * up.Magnitude();

	//forward.y = -sine * forward.Magnitude();
	//forward.z = cosine * forward.Magnitude();
	//			x   y      z       p
	//		|   1  0       0       0 |
	//	M = |   0  cos(A) -sin(A)  0 |
	//		|   0  sin(A)  cos(A)  0 |
	//		|   0  0       0       1 |
	RotateViewPort(0.0f, 0.0f, angle);//+L,-R
}
void MGE2FrameObject::RotateVertical(float angle) {
	//float sine = sinf(angle);
	//float cosine = cosf(angle);
	//
	//right.x = cosine * right.Magnitude();
	//right.z = sine * right.Magnitude();

	//forward.x = -sine * forward.Magnitude();
	//forward.z = cosine * forward.Magnitude();
	//	   x      y    z      p
    //     |  cos(A)  0  -sin(A)  0 |
    // M = |  0       1   0       0 |
    //     |  sin(A)  0   cos(A)  0 |
    //     |  0       0   0       1 |
	RotateViewPort(0.0f, angle, 0.0f);//+U,-D
}
void MGE2FrameObject::RotateAxis(float angle) {
	//float sine = sinf(angle);
	//float cosine = cosf(angle);
	//
	//right.x = cosine * right.Magnitude();
	//right.y = sine * right.Magnitude();

	//up.x = -sine * forward.Magnitude();
	//up.y = cosine * forward.Magnitude();
	//
    //     |  cos(A)  -sin(A)   0   0 |
    // M = |  sin(A)   cos(A)   0   0 |
    //     |  0        0        1   0 |
    //     |  0        0        0   1 |
	RotateViewPort(angle, 0.0f, 0.0f);//+C,-CC
}
//	Deprecated ===== End

void MGE2FrameObject::CameraCentered(Vector3f &cam, float _distance, float _ha, float _va) {
	float _cos_ha = cosf(_ha);
	float _sin_ha = sinf(_ha);
	float _cos_va = cosf(_va);
	float _sin_va = sinf(_va);
	camera = cam;
	center = Vector3f(_distance * _cos_ha * _cos_va, _distance * _sin_ha * _cos_va, _distance * _sin_va ) + camera;
	cameraUp = Vector3f(- _cos_ha * _sin_va, - _sin_ha * _sin_va, _cos_va );
}
void MGE2FrameObject::ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va) {
	float _cos_ha = cosf(_ha);
	float _sin_ha = sinf(_ha);
	float _cos_va = cosf(_va);
	float _sin_va = sinf(_va);
	center = obj;
	camera = Vector3f(_distance * _cos_ha * _cos_va, _distance * _sin_ha * _cos_va, _distance * _sin_va ) + center;
	cameraUp = Vector3f(- _cos_ha * _sin_va, - _sin_ha * _sin_va, _cos_va );
}
void MGE2FrameObject::CameraCentered(Vector3f &cam, float _distance, float _ha, float _va, float _aa) {
	CameraCentered(cam, _distance, _ha, _va);
	Vector3f _cx = (center - camera).Normalized();
	Vector3f _cz = cameraUp.Normalized();
	Vector3f _cy = _cz ^ _cx;
	Matrix33f mat(_cx, _cy, _cz);
	Matrix33f rot;rot.fromEuler(_aa, 0.0f, 0.0f);
	Matrix33f trans3 = mat * rot;
	_cx = *(Vector3f*)&(trans3.m[0][0]);
	_cy = *(Vector3f*)&(trans3.m[1][0]);
	_cz = *(Vector3f*)&(trans3.m[2][0]);
	center = _cx * _distance + camera;
	cameraUp = _cz;
}
void MGE2FrameObject::ObjectCentered(Vector3f &obj, float _distance, float _ha, float _va, float _aa) {
	ObjectCentered(obj, _distance, _ha, _va);
	Vector3f _cx = (center - camera).Normalized();
	Vector3f _cz = cameraUp.Normalized();
	Vector3f _cy = _cz ^ _cx;
	Matrix33f mat(_cx, _cy, _cz);
	Matrix33f rot;rot.fromEuler(_aa, 0.0f, 0.0f);
	Matrix33f trans3 = rot * mat;
	_cx = *(Vector3f*)&(trans3.m[0][0]);
	_cy = *(Vector3f*)&(trans3.m[1][0]);
	_cz = *(Vector3f*)&(trans3.m[2][0]);
	camera = center - _cx * _distance;
	cameraUp = _cz;
}
void MGE2FrameObject::CameraCenteredOrbit(Vector3f &cam, float _distance, float _ha, float _va, float _aa) {
	CameraCentered(cam, _distance, _ha, _va);
	Vector3f _cx = (center - camera).Normalized();
	Vector3f _cz = cameraUp.Normalized();
	Vector3f _cy = _cz ^ _cx;
	Matrix33f mat(_cx, _cy, _cz);
	Matrix33f rot;rot.fromEuler(_aa, 0.0f, 0.0f);
	Matrix33f trans3 = rot * mat;
	_cx = *(Vector3f*)&(trans3.m[0][0]);
	_cy = *(Vector3f*)&(trans3.m[1][0]);
	_cz = *(Vector3f*)&(trans3.m[2][0]);
	center = _cx * _distance + camera;
	cameraUp = _cz;
}
void MGE2FrameObject::ObjectCenteredOrbit(Vector3f &obj, float _distance, float _ha, float _va, float _aa) {
	ObjectCentered(obj, _distance, _ha, _va);
	Vector3f _cx = (center - camera).Normalized();
	Vector3f _cz = cameraUp.Normalized();
	Vector3f _cy = _cz ^ _cx;
	Matrix33f mat(_cx, _cy, _cz);
	Matrix33f rot;rot.fromEuler(_aa, 0.0f, 0.0f);
	Matrix33f trans3 = mat * rot;
	_cx = *(Vector3f*)&(trans3.m[0][0]);
	_cy = *(Vector3f*)&(trans3.m[1][0]);
	_cz = *(Vector3f*)&(trans3.m[2][0]);
	camera = center - _cx * _distance;
	cameraUp = _cz;
}

void MGE2FrameObject::SetViewPort() {
}

