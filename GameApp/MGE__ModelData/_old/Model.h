///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MODEL_H_
#define _MODEL_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

#include "Mesh.h"
#include "BoneController.h"

#define MAX_MESHNUM 256

extern "C" class MGEModelData : public MGEObject {
protected:
protected:
	Vector3f translation;
	Matrix33f rotation;
	float scale;

	unsigned short numMeshes;
	MGERefArray<MGEModelMesh> meshes;
	BOOL8 hasBoneController;
	MGEModelBoneController *boneController;
public:
	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();

	MGERefArray<MGEModelMesh> &GetMeshes();
	BOOL8 HasBoneController();
	MGEModelBoneController &GetBoneController();
	void SetBoneController(MGEModelBoneController *src);
	unsigned short GetNumMeshes();
	void SetNumMeshes(unsigned short num);
public:
	void CopyBoneBlockIndices(MGEModelData &tar);
	void LinkBoneNodes();
	void CopyAnimationController(MGEModelData &tar);
	void BuildAnimationController(MGEModelData &tar, MGEString &rootbonename, Transform &trans, Transform &itrans);
	void SetAnimationControllerBoneRoot(MGEString &newname, Transform &trans, Transform &itrans);

public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	MGEModelData();
	virtual ~MGEModelData();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
