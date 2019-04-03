///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _BONETREENODE_H_
#define _BONETREENODE_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

extern "C" class MGEModelBoneTreeNode : public MGEObject {
protected:
protected:
	Vector3f translation;
	Matrix33f rotation;
	float scale;

	unsigned short boneId;
	BOOL8 hasNextNode;
	BOOL8 hasSubNode;
	unsigned short nextBoneId;
	unsigned short subBoneId;

	MGEModelBoneTreeNode *nextNode;
	MGEModelBoneTreeNode *subNode;
	MGEModelBoneTreeNode *parent;
	MGEHashtable *boneTable;
	unsigned short *indexCount;

	Transform iTransform;
	Transform aTransform;
	Transform transform;

	Transform fast;
public:
	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();

	unsigned short GetBoneId();
	void SetBoneId(unsigned short id);
	BOOL8 HasNextNode();
	BOOL8 HasSubNode();
	MGEModelBoneTreeNode &GetNextNode();
	MGEModelBoneTreeNode &GetSubNode();
	MGEModelBoneTreeNode &GetParentNode();
	void SetNextNode(MGEModelBoneTreeNode *src);
	void SetSubNode(MGEModelBoneTreeNode *src);
	void SetParentNode(MGEModelBoneTreeNode *src);
	MGEHashtable &GetBoneHashtable();

	Transform &GetInvertedTransform();
	Transform &GetAnimationTransform();
	Transform &GetTransform();

	Transform &GetFastTransform();
public:
	void CopyInstance(MGEModelBoneTreeNode &bc);
public:
	MGEModelBoneTreeNode();
	MGEModelBoneTreeNode(MGEModelBoneTreeNode *p, MGEHashtable *table);
	virtual ~MGEModelBoneTreeNode();
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
