///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _BONECONTROLLER_H_
#define _BONECONTROLLER_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

extern "C" class MGEModelBoneController : public MGEObject {
protected:
protected:
	MGEModelBoneTreeNode *boneRoot;

	Vector3f translation;
	Matrix33f rotation;
	float scale;
	
	MGERefArray<MGEModelBoneTreeNode> boneTable;
	MGEHashtable boneHashtable;
	unsigned short numBones;
	unsigned short indexCount;
public:
	MGEModelBoneTreeNode &GetBoneRoot();
	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();
	MGERefArray<MGEModelBoneTreeNode> &GetBoneTable();
	MGEHashtable &GetBoneHashtable();
	void SetBoneRoot(MGEModelBoneTreeNode *src);
public:
	void BuildBoneMatrix(MGEModelBoneTreeNode &btn, Transform &src);
	void ReloadMatrix(MGEModelBoneTreeNode &btn);
	void ReloadInvertedMatrix(MGEModelBoneTreeNode &btn);
	void DoAnimation(MGEModelBoneTreeNode &btn, Transform &src);
	void BuildBoneMatrix();
	void ReloadMatrix();
	void ReloadInvertedMatrix();
	void DoAnimation();
public:
	void CopyInstance(MGEModelBoneController &bc);
	void CopyBoneTransform(MGEModelBoneTreeNode &btn);

public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	MGEModelBoneController();
	virtual ~MGEModelBoneController();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
