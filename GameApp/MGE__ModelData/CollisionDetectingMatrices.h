///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _COLLISIONDETECTINGMATRICES_H_
#define _COLLISIONDETECTINGMATRICES_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

//extern "C" template class MGEDataArray<Matrix44f>;

extern "C" class MGEModelCollision : public MGEObject {
protected:
protected:
	MGEDataArray<Matrix44f> cdms;
	Vector3f position;
	BOOL32 isOuter;
	Matrix44f recommendation;
public:
	MGEModelCollision();
	virtual ~MGEModelCollision();
public:
	BOOL32 IsCollision(Vector3f &src, Vector3f &varify);
	BOOL32 IsCollision(Vector4f &src, Vector4f &varify);
public:
	BOOL32 IsMatricesZEqual(Matrix44f &src1, Matrix44f &src2, float delta);
	unsigned int BuildCollisionDetectingMatrices(MGEModelMesh &msh);
	void Scale(float ratio);
public:
	Vector3f &GetPosition();
	Matrix44f &GetRecommendation();
	MGEDataArray<Matrix44f> &GetCDMs();
	void SetOuterFlag(BOOL32 flag);
	BOOL32 IsOuter();
public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual void Serialize(MGEIOStream &iio);
};

#endif
