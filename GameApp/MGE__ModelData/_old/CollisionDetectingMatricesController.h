///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _COLLISIONDETECTINGMATRICESCONTROLLER_H_
#define _COLLISIONDETECTINGMATRICESCONTROLLER_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

extern "C" class MGEModelCollisionController : public MGEObject {
protected:
protected:
	MGERefArray<MGEModelCollision> cdmos;
	MGEHashtable cdmoIndices;
public:
	MGEModelCollisionController();
	virtual ~MGEModelCollisionController();
public:
	MGERefArray<MGEModelCollision> &GetCDMObjects();
	MGEHashtable &GetCDMIndices();
	MGEModelCollision &GetCDMObject(MGEString &key);
	BOOL32 IsCollision(Vector3f &src, Vector3f &varify);
	BOOL32 IsCollision(Vector4f &src, Vector4f &varify);
	void Scale(float ratio);

public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
