///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

#include "KeyFrame.h"
#include "BoneTreeNode.h"

#define MAX_KEYFRAMENUM 256

extern "C" class MGEModelSequence : public MGEObject {
protected:
protected:
	float weight;
	byte cycleType;
	float frequency;
	float startTime;
	float stopTime;
	MGEString targetName;

	unsigned short numControlledBlocks;
	MGERefArray<MGEModelKeyFrame> keyFrames;
	MGEHashtable controlledNodes;

public:
	float &GetWeight();
	byte GetCycleType();
	void SetCycleType(byte ctype);
	float &GetFrequency();
	float &GetStartTime();
	float &GetStopTime();
	MGEString &GetTargetName();

	MGERefArray<MGEModelKeyFrame> &GetKeyFrames();
	MGEHashtable &GetControlledNodes();
public:
	void GetInterpolate(MGEModelKeyFrame &kf, Quaternion &q, Vector3f &t, float time);
	void GetTransform(MGEModelKeyFrame &kf, Quaternion &q, Vector3f &t, unsigned int _index);
	void GetInterpolate(MGEModelKeyFrame &kfa, MGEModelKeyFrame &kfb, Quaternion &q, Vector3f &t, float ratio);
	void LoadAnimationMatrix(MGEModelBoneTreeNode &btn, float time);
	void LoadAnimationMatrix(MGEModelBoneTreeNode &btn, unsigned int _index);
	void LoadAnimationMatrix(MGEModelSequence &sqb, MGEModelBoneTreeNode &btn, float ratio);
	void BuildTemporaryAnimation(float time);

	void RotInterpolate(Quaternion &_out, Quaternion &_q0, Quaternion &_q1, float ratio);
public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	MGEModelSequence();
	virtual ~MGEModelSequence();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
