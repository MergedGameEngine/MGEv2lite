///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
//#include "../MGE__MathTool/MathTool.h"
//#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE_Thread/Thread.h"

#include "../MGE__Config/Config.hpp"
#include "../MGE__Config/ConfigFile.h"

//#include "EventListener.h"

#include "../MGE__ModelData/ModelPack.hpp"
//#include "AnimationController.hpp"
//#include "InterfaceVMeshObject.hpp"
#include "InterfaceVRendererObject.hpp"

extern "C" class MGE2GameObject : public MGEObject {
public:
	MGE2GameObject();
	virtual ~MGE2GameObject();
public:
	Vector3f positionCurrent;
	Vector3f position;
	Matrix33f direction;
	float directionAngle;
	Vector3f offset;
	Vector3f velocity;
	Vector3f acceleration;
public:
public:
public:
	MGEModelPack *modelPrototype;
	MGE2RendererObject *rendererReference;

	unsigned short numBoneMatrices;
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

public:
//	=================================================
//	MGE v2 field
	/// 4 Animation
public:
	MGEModelData *animator;
	MGE2GameObject *parentController;
	MGEHashtable *animationIndex;/// combine with animator
	MGEHashtable *meshObjectIndex;///Mat44 Data Sent to shader

	/// 4 Phyx
public:
	MGERefArray<MGEModelCollisionController> *collisions;

private:
	MGEModelSequence *selector;
	MGEModelSequence *dselector;
	float dratio;
	unsigned int numKeyFrames;
	unsigned int frameCounter;
	unsigned int _actCounter;
public:
	unsigned int innerstate;

//	=================================================
public:
	void LinkBoneMatrices();
	virtual void Flush(MGEString _akey, float delta);
	virtual void Flush(float delta);
	void InitializeAnimation(MGEString _akey, MGEHashtable *_animationIndex, MGEHashtable *_meshObjectIndex);
public:
//	virtual void EventHandler(TEvent &e);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif