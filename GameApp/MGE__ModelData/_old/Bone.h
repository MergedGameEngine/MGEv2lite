///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _BONE_H_
#define _BONE_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

#include "BoneTreeNode.h"

//extern "C" template class MGEDataArray<unsigned short>;
//extern "C" template class MGEDataArray<float>;

extern "C" class MGEModelBone : public MGEObject {
protected:
protected:
	Vector3f translation;
	Matrix33f rotation;
	float scale;
	Vector3f boundingSphereOffset;
	float boundingSphereRadius;

	unsigned short numVertices;
	MGEDataArray<unsigned short> vertexIndices;
	MGEDataArray<float> weights;

	MGEModelBoneTreeNode *shortCut;

public:
	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();
	Vector3f &GetBoundingSphereOffset();
	float &GetBoundingSphereRadius();
	MGEDataArray<unsigned short> &GetVertexIndices();
	MGEDataArray<float> &GetWeights();
	MGEModelBoneTreeNode &GetBoneNode();

	void SetNumVertices(unsigned short num);
	unsigned short GetNumVertices();

public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	MGEModelBone();
	MGEModelBone(MGEModelBoneTreeNode *sc);
	virtual ~MGEModelBone();

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
