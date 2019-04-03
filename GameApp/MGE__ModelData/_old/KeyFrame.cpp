///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _MODEL_EXPORT

#include "string.h"
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "KeyFrame.hpp"

MGEModelKeyFrame::MGEModelKeyFrame() {
	rotationType = 0;
	quatInterpolatType = 0;
	transInterpolatType = 0;
	scalesInterpolatType = 0;
	numFrames = 0;
	numQuaternion = 0;
	timeLineQuat.Resize(0);
	quaternions.Resize(0);
	numTrans = 0;
	timeLineTrans.Resize(0);
	translations.Resize(0);
	numScales = 0;
	timeLineScales.Resize(0);
	scales.Resize(0);
}

MGEModelKeyFrame::~MGEModelKeyFrame() {
	timeLineQuat.Resize(0);
	quaternions.Resize(0);
	numTrans = 0;
	timeLineTrans.Resize(0);
	translations.Resize(0);
	numScales = 0;
	timeLineScales.Resize(0);
	scales.Resize(0);
}

const char *MGEModelKeyFrame::GetClassName() {
	return "MGEModelKeyFrame";
}

BOOL32 MGEModelKeyFrame::IsInstanceof(const char* className) {
	if (strcmp("MGEModelKeyFrame", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelKeyFrame::Serialize(MGEIOStream &iio) {
//	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == MGEIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			_name.Load(iio);//Unicode,UCS2
			name = MGEString("%ls",_name.GetBuffer());
			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 4, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.Read(&rotationType, sizeof(byte));
			iio.Read(&quatInterpolatType, sizeof(byte));
			iio.Read(&transInterpolatType, sizeof(byte));
			iio.Read(&scalesInterpolatType, sizeof(byte));
			iio.Read(&numFrames, sizeof(unsigned int));
			iio.Read(&numQuaternion, sizeof(unsigned int));
			iio.Read(&numTrans, sizeof(unsigned int));
			iio.Read(&numScales, sizeof(unsigned int));
			if ( numQuaternion > 0 ) {
				timeLineQuat.Resize(numQuaternion);
				quaternions.Resize(numQuaternion);
				iio.ReadBuffer(timeLineQuat.GetBuffer(), numQuaternion, sizeof(float));
				iio.ReadBuffer(quaternions.GetBuffer(), numQuaternion * 4, sizeof(float));
			}
			if ( numTrans > 0 ) {
				timeLineTrans.Resize(numTrans);
				translations.Resize(numTrans);
				iio.ReadBuffer(timeLineTrans.GetBuffer(), numTrans, sizeof(float));
				iio.ReadBuffer(translations.GetBuffer(), numTrans * 3, sizeof(float));
			}
			if ( numScales > 0 ) {
				timeLineScales.Resize(numScales);
				scales.Resize(numScales);
				iio.ReadBuffer(timeLineScales.GetBuffer(), numScales, sizeof(float));
				iio.ReadBuffer(scales.GetBuffer(), numScales, sizeof(float));
			}
		}
	} else {
		name.Store(iio);
		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 4, sizeof(float));
		iio.Write(&scale, sizeof(float));
		iio.Write(&rotationType, sizeof(byte));
		iio.Write(&quatInterpolatType, sizeof(byte));
		iio.Write(&transInterpolatType, sizeof(byte));
		iio.Write(&scalesInterpolatType, sizeof(byte));
		iio.Write(&numFrames, sizeof(unsigned int));
		iio.Write(&numQuaternion, sizeof(unsigned int));
		iio.Write(&numTrans, sizeof(unsigned int));
		iio.Write(&numScales, sizeof(unsigned int));
		if ( numQuaternion > 0 ) {
			iio.WriteBuffer(timeLineQuat.GetBuffer(), numQuaternion, sizeof(float));
			iio.WriteBuffer(quaternions.GetBuffer(), numQuaternion * 4, sizeof(float));
		}
		if ( numTrans > 0 ) {
			iio.WriteBuffer(timeLineTrans.GetBuffer(), numTrans, sizeof(float));
			iio.WriteBuffer(translations.GetBuffer(), numTrans * 3, sizeof(float));
		}
		if ( numScales > 0 ) {
			iio.WriteBuffer(timeLineScales.GetBuffer(), numScales, sizeof(float));
			iio.WriteBuffer(scales.GetBuffer(), numScales, sizeof(float));
		}
	}
}

Vector3f &MGEModelKeyFrame::GetTranslation() {
	return translation;
}

Quaternion &MGEModelKeyFrame::GetRotation() {
	return rotation;
}

float &MGEModelKeyFrame::GetScale() {
	return scale;
}

byte MGEModelKeyFrame::GetRotationType() {
	return rotationType;
}

void MGEModelKeyFrame::SetRotationType(byte rtype) {
	rotationType = rtype;
}

byte MGEModelKeyFrame::GetQuatInterpolatType() {
	return quatInterpolatType;
}

void MGEModelKeyFrame::SetQuatInterpolatType(byte itype) {
	quatInterpolatType = itype;
}

byte MGEModelKeyFrame::GetTransInterpolatType() {
	return transInterpolatType;
}

void MGEModelKeyFrame::SetTransInterpolatType(byte itype) {
	transInterpolatType = itype;
}

byte MGEModelKeyFrame::GetScalesInterpolatType() {
	return scalesInterpolatType;
}

void MGEModelKeyFrame::SetScalesInterpolatType(byte itype) {
	scalesInterpolatType = itype;
}

MGEDataArray<float> &MGEModelKeyFrame::GetTimeLineQuat() {
	return timeLineQuat;
}

MGEDataArray<Quaternion> &MGEModelKeyFrame::GetQuaternions() {
	return quaternions;
}

MGEDataArray<float> &MGEModelKeyFrame::GetTimeLineTrans() {
	return timeLineTrans;
}

MGEDataArray<Vector3f> &MGEModelKeyFrame::GetTranslations() {
	return translations;
}

MGEDataArray<float> &MGEModelKeyFrame::GetTimeLineScales() {
	return timeLineScales;
}

MGEDataArray<float> &MGEModelKeyFrame::GetScales() {
	return scales;
}

unsigned int MGEModelKeyFrame::GetNumFrames() {
	return numFrames;
}

void MGEModelKeyFrame::SetNumFrames(unsigned int num) {
	numFrames = num;
}

unsigned int MGEModelKeyFrame::GetNumQuaternions() {
	return numQuaternion;
}

void MGEModelKeyFrame::SetNumQuaternions(unsigned int num) {
	numQuaternion = num;
	timeLineQuat.Resize(num);
	quaternions.Resize(num);
}

unsigned int MGEModelKeyFrame::GetNumTranslations() {
	return numTrans;
}

void MGEModelKeyFrame::SetNumTranslations(unsigned int num) {
	numTrans = num;
	timeLineTrans.Resize(num);
	translations.Resize(num);
}

unsigned int MGEModelKeyFrame::GetNumScales() {
	return numScales;
}

void MGEModelKeyFrame::SetNumScales(unsigned int num) {
	numScales = num;
	timeLineScales.Resize(num);
	scales.Resize(num);
}

Quaternion &MGEModelKeyFrame::GetTemporaryRotation() {
	return temporaryRotation;
}
Vector3f &MGEModelKeyFrame::GetTemporaryTranslation() {
	return temporaryTranslation;
}
