///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _KEYFRAME_H_
#define _KEYFRAME_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

//extern "C" template class MGEDataArray<unsigned short>;
//extern "C" template class MGEDataArray<float>;
//extern "C" template class MGEDataArray<Triangle>;
//extern "C" template class MGEDataArray<TexCoord2f>;
//extern "C" template class MGEDataArray<Vector3f>;
//extern "C" template class MGEDataArray<Vector4f>;
//extern "C" template class MGEDataArray<Matrix22f>;
//extern "C" template class MGEDataArray<Matrix33f>;
//extern "C" template class MGEDataArray<Matrix44f>;
//extern "C" template class MGEDataArray<Matrix34f>;
//extern "C" template class MGEDataArray<Quaternion>;
//extern "C" template class MGEDataArray<Transform>;

extern "C" class MGEModelKeyFrame : public MGEObject {
protected:
protected:
	Vector3f translation;
	Quaternion rotation;
	float scale;
	unsigned char rotationType;
	unsigned char quatInterpolatType;
	unsigned char transInterpolatType;
	unsigned char scalesInterpolatType;
	unsigned int numFrames;
	unsigned int numQuaternion;
	MGEDataArray<float> timeLineQuat;
	MGEDataArray<Quaternion> quaternions;
	unsigned int numTrans;
	MGEDataArray<float> timeLineTrans;
	MGEDataArray<Vector3f> translations;
	unsigned int numScales;
	MGEDataArray<float> timeLineScales;
	MGEDataArray<float> scales;

	Quaternion temporaryRotation;
	Vector3f temporaryTranslation;
public:
	Vector3f &GetTranslation();
	Quaternion &GetRotation();
	float &GetScale();
	byte GetRotationType();
	void SetRotationType(byte rtype);
	byte GetQuatInterpolatType();
	void SetQuatInterpolatType(byte itype);
	byte GetTransInterpolatType();
	void SetTransInterpolatType(byte itype);
	byte GetScalesInterpolatType();
	void SetScalesInterpolatType(byte itype);
	MGEDataArray<float> &GetTimeLineQuat();
	MGEDataArray<Quaternion> &GetQuaternions();
	MGEDataArray<float> &GetTimeLineTrans();
	MGEDataArray<Vector3f> &GetTranslations();
	MGEDataArray<float> &GetTimeLineScales();
	MGEDataArray<float> &GetScales();

	unsigned int GetNumFrames();
	void SetNumFrames(unsigned int num);
	unsigned int GetNumQuaternions();
	void SetNumQuaternions(unsigned int num);
	unsigned int GetNumTranslations();
	void SetNumTranslations(unsigned int num);
	unsigned int GetNumScales();
	void SetNumScales(unsigned int num);

	Quaternion &GetTemporaryRotation();
	Vector3f &GetTemporaryTranslation();
public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	MGEModelKeyFrame();
	virtual ~MGEModelKeyFrame();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
