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
#include "AnimationController.hpp"
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
	Vector3f velocity;
	Vector3f acceleration;
public:
	void RotationAxisZ(float angle);
	void Velocity(float delta);
	void Commit();
public:
	MGERefArray<MGE2MeshObject> meshes;
	MGEHashtable meshIndices;
public:
	MGEModelPack *modelPrototype;
	MGE2RendererObject *rendererReference;
//	TTextureController *renderTextureUnit;
	MGEAnimationController *animationController;
	unsigned short numBoneMatrices;
public:
	MGERefArray<MGE2GameObject> subModelControllers;
public:
	void LinkBoneMatrices();
public:
//	virtual void EventHandler(TEvent &e);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif