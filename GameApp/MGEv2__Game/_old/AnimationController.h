///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _ANIMATIONCONTROLLER_H_
#define _ANIMATIONCONTROLLER_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
//#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE_Thread/Thread.h"

//#include "../MGE__ModelData/Skin.h"

//#include "../MGE__ModelData/Sequence.h"
#include "../MGE__ModelData/Sequence.hpp"
//#include "../MGE__ModelData/Model.h"
#include "../MGE__ModelData/Model.hpp"

extern "C" class MGEAnimationController : public MGEThread {
public:
	MGEAnimationController();
	virtual ~MGEAnimationController();
public:
	Vector3f positionCurrent;
	Vector3f position;
	Matrix33f direction;
	float directionAngle;
	Vector3f velocityCurrent;
	Vector3f velocity;
	Vector3f accelerationCurrent;
	Vector3f acceleration;
public:
	unsigned int innerstate;
public:
	void RotationAxisZ(float angle);
	void Velocity(float delta);
	void CommitVelocity();
	void Gravity(float delta);
	void CommitGravity();
	void Commit();
public:
	float currentime;
	MGERWLock rwLock;
	MGERefArray<MGEModelSequence> animations;
	MGEModelData boneController;
	MGEAnimationController *parentController;
	int count;
public:
	virtual void Run();
	virtual void Flush(float delta);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif