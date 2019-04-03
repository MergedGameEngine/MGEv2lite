///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _CORE_EXPORT

#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _MODEL_IMPORT
#define _THREAD_IMPORT
#define _RENDERER_IMPORT

#include "string.h"
//#include "../Base/Type.h"
//#include "../Base/Base.h"
//#define _ARRAY_API _CORE_API

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE_Thread/Thread.h"

#include "../MGE__ModelData/Skin.h"
//#include "../MGE__ModelData/Skin.hpp"

#include "../MGE__ModelData/Sequence.h"
#include "../MGE__ModelData/Sequence.hpp"
#include "../MGE__ModelData/Model.h"
#include "../MGE__ModelData/Model.hpp"
#include "AnimationController.hpp"

//#include "../Model/ModelObject.h"
//#include "../Model/Mesh.h"
//#include "../Model/Skin.h"
//#include "../Model/Bone.h"
//#include "../Model/BoneController.h"
//#include "../Model/BoneTreeNode.h"
//#include "../Model/Sequence.h"
//#include "../Model/KeyFrame.h"
//#include "../Model/Model.h"
//#include "../Model/ModelGlobal.h"
//
////extern "C" template class _MODEL_API TRefArray<TModel>;
////extern "C" template class _MODEL_API TRefArray<TSequence>;
////extern "C" template class _MODEL_API TRefArray<TSkin>;
////extern "C" template class _MODEL_API TRefArray<TBone>;
////extern "C" template class _MODEL_API TRefArray<TMesh>;
////extern "C" template class _MODEL_API TRefArray<TKeyFrame>;
//
//#include "../Renderer/TextureObject.h"
//#include "../Renderer/TextureController.h"
//#include "../Renderer/MeshObject.h"
//#include "../Renderer/MeshController.h"

//extern "C" template class _RENDERER_API TRefArray<TMeshObject>;

MGEAnimationController::MGEAnimationController() {
	rwLock.AttribInit();
	rwLock.Init();
	count = 0;
	parentController = NULL;

	directionAngle = 0.0f;

	innerstate = 0;
}
MGEAnimationController::~MGEAnimationController() {
	rwLock.Unlock();
	rwLock.Destroy();
	rwLock.AttribDestroy();
	animations.Resize(0);
}
const char *MGEAnimationController::GetClassName() {
	return "MGEAnimationController";
}

BOOL32 MGEAnimationController::IsInstanceof(const char* className) {
	if (strcmp("MGEAnimationController", className)) {
		return TRUE;
	}
	return FALSE;
}

void MGEAnimationController::Run() {
	if ( currentime > 1.33f ) {
		currentime = 0.0f;
		count ++;
	} else {
		currentime = currentime + 0.01f;
	}
	rwLock.WriteLock();
	animations[0].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), currentime);
	boneController.GetBoneController().DoAnimation();
	rwLock.Unlock();
}

void MGEAnimationController::Flush(float delta) {
	if ( currentime > 1.33f ) {
		currentime = 0.0f;
		count ++;
	} else {
		currentime = currentime + delta;
	}
	rwLock.WriteLock();
	animations[0].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), currentime);
	boneController.GetBoneController().DoAnimation();
	rwLock.Unlock();
}

void MGEAnimationController::RotationAxisZ(float angle) {
	directionAngle += angle;
	direction.fromEuler(0.0f, 0.0f, directionAngle);
}

void MGEAnimationController::Velocity(float delta) {
	Vector3f dir(1.0f, 0.0f, 0.0f);
	float vz = velocity.z;
	velocity = direction * dir * delta;
	velocity.z = vz;
	position = positionCurrent + velocity;
	velocity = Vector3f();
}

void MGEAnimationController::CommitVelocity() {
}

void MGEAnimationController::Commit() {
	positionCurrent = position;
}

void MGEAnimationController::Gravity(float delta) {
	if ( delta == 0.0f ) {
		acceleration = Vector3f();
		velocity.z = 0.0f;
		position = positionCurrent;
	} else {
		acceleration = Vector3f(0.0f, 0.0f, -delta);
		velocity += acceleration;
		position = positionCurrent + velocity;
	}
}
	
void MGEAnimationController::CommitGravity() {
}
