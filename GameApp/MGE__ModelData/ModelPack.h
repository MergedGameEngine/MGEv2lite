///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MODELGLOBAL_H_
#define _MODELGLOBAL_H_


#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

#include "Model.h"
#include "Sequence.h"
#include "CollisionDetectingMatrices.hpp"
#include "CollisionDetectingMatricesController.hpp"

extern "C" class MGEModelPack : public MGEObject {
protected:
protected:
	MGERefArray<MGEModelData> models;
	unsigned short numModels;
	byte fileType;
	unsigned short numAnimations;
	MGERefArray<MGEModelSequence> animations;
	MGERefArray<MGEModelCollisionController> cdmcs;
public:
	MGERefArray<MGEModelData> &GetModels();
	MGERefArray<MGEModelSequence> &GetAnimations();
	MGERefArray<MGEModelCollisionController> &GetCollisionDetectingMatricesControllers();
	byte GetFileType();
	void SetFileType(byte ftype);
public:
	enum {
		type_model = 0,
		type_skeleton = 1,
		type_animation = 2,
		type_collision = 3
	};

public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	MGEModelPack();
	virtual ~MGEModelPack();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
