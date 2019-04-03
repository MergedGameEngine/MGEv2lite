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
#include "math.h"
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#define _ARRAY_API _MODEL_API
#include "Sequence.hpp"

MGEModelSequence::MGEModelSequence() {
	keyFrames.Resize(0);
	weight = 0;
	cycleType = 0;
	frequency = 0;
	startTime = 0;
	stopTime = 0;

	numControlledBlocks = 0;
}

MGEModelSequence::~MGEModelSequence() {
	keyFrames.DeleteAll();
	keyFrames.Resize(0);
}

const char *MGEModelSequence::GetClassName() {
	return "MGEModelSequence";
}

BOOL32 MGEModelSequence::IsInstanceof(const char* className) {
	if (strcmp("MGEModelSequence", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelSequence::Serialize(MGEIOStream &iio) {
//	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == MGEIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			_name.Load(iio);//Unicode,UCS2
			if ( _name.GetBuffer() ) {
#ifdef WIN32
				name = MGEString("%ls",_name.GetBuffer());
#else
				MGEWString __wstr(_name.GetBuffer());
				name = MGEString("%ls",__wstr.GetBuffer());
#endif				
			}
			iio.Read(&weight, sizeof(float));
			iio.Read(&cycleType, sizeof(byte)); 
			iio.Read(&frequency, sizeof(float));
			iio.Read(&startTime, sizeof(float));
			iio.Read(&stopTime, sizeof(float));
			_name.Load(iio);
			if ( _name.GetBuffer() ) {
#ifdef WIN32
				targetName = MGEString("%ls",_name.GetBuffer());
#else
				MGEWString __wstr(_name.GetBuffer());
				targetName = MGEString("%ls",__wstr.GetBuffer());
#endif				
			}
			/////if ( _name.GetBuffer() ) {
			/////	targetName = MGEString("%ls",_name.GetBuffer());
			/////}
			///targetName.Load(iio);

			iio.Read(&numControlledBlocks, sizeof(unsigned int));
			keyFrames.Resize(numControlledBlocks);
			keyFrames.CreateAll();
			for (int i1 = 0 ; i1 < numControlledBlocks ; i1 ++ ) {
				MGETString kClassName;
				kClassName.Load(iio);
				keyFrames[i1].version = version;
				keyFrames[i1].subVersion = subVersion;
				keyFrames[i1].Serialize(iio);
			}
			for (int i2 = 0 ; i2 < numControlledBlocks ; i2 ++ ) {
				controlledNodes.Add(keyFrames[i2].name, &keyFrames[i2]);
			}
		} else
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000001 ) ) {
			name.Load(iio);//MBCS or UTF8

			iio.Read(&weight, sizeof(float));
			iio.Read(&cycleType, sizeof(unsigned char)); 
			iio.Read(&frequency, sizeof(float));
			iio.Read(&startTime, sizeof(float));
			iio.Read(&stopTime, sizeof(float));

			targetName.Load(iio);

			iio.Read(&numControlledBlocks, sizeof(unsigned int));
			keyFrames.Resize(numControlledBlocks);
			keyFrames.CreateAll();
			for (int i1 = 0 ; i1 < numControlledBlocks ; i1 ++ ) {
				MGEString kClassName;//MBCS or UTF8
				kClassName.Load(iio);
				keyFrames[i1].version = version;
				keyFrames[i1].subVersion = subVersion;
				keyFrames[i1].Serialize(iio);
			}
			for (int i2 = 0 ; i2 < numControlledBlocks ; i2 ++ ) {
				controlledNodes.Add(keyFrames[i2].name, &keyFrames[i2]);
			}
		} else
		{
		}

	} else {
		name.Store(iio);

		iio.Write(&weight, sizeof(float));
		iio.Write(&cycleType, sizeof(byte)); 
		iio.Write(&frequency, sizeof(float));
		iio.Write(&startTime, sizeof(float));
		iio.Write(&stopTime, sizeof(float));

		targetName.Store(iio);

		numControlledBlocks = keyFrames.GetLength();
		iio.Write(&numControlledBlocks, sizeof(unsigned int));
		for (int i1 = 0 ; i1 < numControlledBlocks ; i1 ++ ) {
			MGEString kClassName(keyFrames[i1].GetClassName());
			kClassName.Store(iio);
			keyFrames[i1].version = version;
			keyFrames[i1].subVersion = subVersion;
			keyFrames[i1].Serialize(iio);
		}
	}
}

float &MGEModelSequence::GetWeight() {
	return weight;
}

byte MGEModelSequence::GetCycleType() {
	return cycleType;
}

void MGEModelSequence::SetCycleType(byte ctype) {
	cycleType = ctype;
}

float &MGEModelSequence::GetFrequency() {
	return frequency;
}

float &MGEModelSequence::GetStartTime() {
	return startTime;
}

float &MGEModelSequence::GetStopTime() {
	return stopTime;
}

MGEString &MGEModelSequence::GetTargetName() {
	return targetName;
}

MGERefArray<MGEModelKeyFrame> &MGEModelSequence::GetKeyFrames() {
	return keyFrames;
}

MGEHashtable &MGEModelSequence::GetControlledNodes() {
	return controlledNodes;
}

void MGEModelSequence::GetTransform(MGEModelKeyFrame &kf, Quaternion &q, Vector3f &t, unsigned int _index) {
	if ( kf.GetNumQuaternions() == 0 ) {
		Matrix33f mat;
		q = mat.toQuat();
	} else if ( kf.GetNumQuaternions() == 1 ) {
		q = kf.GetQuaternions()[0];
	} else {
		unsigned int i = 0;
		if ( _index < kf.GetNumQuaternions() ) {
			q = kf.GetQuaternions()[_index];
		}
	}
	if ( kf.GetNumTranslations() == 0 ) {
		t = kf.GetTranslation();
	} else if ( kf.GetNumTranslations() == 1 ) {
		t = kf.GetTranslations()[0];
	} else {
		if ( _index < kf.GetNumTranslations() ) {
			t = kf.GetTranslations()[_index];
		}
	}
}

void MGEModelSequence::RotInterpolate(Quaternion &_out, Quaternion &_q0, Quaternion &_q1, float ratio) {
	Matrix33f _rot0;
	Matrix33f _rot1;

	_rot0.fromQuat(_q0);
	_rot1.fromQuat(_q1);

	float _rs00, _rs01, _rs02;
	float _rs10, _rs11, _rs12;

	_rot0.toEuler(_rs00, _rs01, _rs02);
	_rot1.toEuler(_rs10, _rs11, _rs12);

	_rs10 = _rs10 * ratio + _rs00 * ( 1.0f - ratio );
	_rs11 = _rs11 * ratio + _rs01 * ( 1.0f - ratio );
	_rs12 = _rs12 * ratio + _rs02 * ( 1.0f - ratio );

	_rot1.fromEuler(_rs10, _rs11, _rs12);
	_out = _rot1.toQuat();
}


void MGEModelSequence::GetInterpolate(MGEModelKeyFrame &kf, Quaternion &q, Vector3f &t, float time) {
	if ( time < 0.0f ) {
		return;
	}
	if ( kf.GetNumQuaternions() == 0 ) {
		Matrix33f mat;
		q = mat.toQuat();
	} else if ( kf.GetNumQuaternions() == 1 ) {
		q = kf.GetQuaternions()[0];
	} else {
		unsigned int i = 0;
		for ( i = 0 ; i < kf.GetNumQuaternions() ; i ++ ) {
			if ( kf.GetTimeLineQuat()[i] > time ) {
				Quaternion prev = kf.GetQuaternions()[i - 1];
				Quaternion next = kf.GetQuaternions()[i];
				float prevtime = kf.GetTimeLineQuat()[i - 1];
				float nexttime = kf.GetTimeLineQuat()[i];
				float ratio = ( time - prevtime ) / ( nexttime - prevtime );
///				q = kf.GetQuaternions()[i];
				q = prev.Slerp(ratio, next);
				///RotInterpolate(q, prev, next, ratio);
				break;
			} else if ( fabsf(kf.GetTimeLineQuat()[i] - time) == 0.00001 ) {
				q = kf.GetQuaternions()[i];
				break;
			}
		}
		if ( i >= kf.GetNumQuaternions()) {
			i = kf.GetNumQuaternions() - 1;
		}
	}
	if ( kf.GetNumTranslations() == 0 ) {
		t = kf.GetTranslation();
	} else if ( kf.GetNumTranslations() == 1 ) {
		t = kf.GetTranslations()[0];
	} else {
		unsigned int i = 0;
		for ( i = 0 ; i < kf.GetNumTranslations() ; i ++ ) {
			if ( kf.GetTimeLineTrans()[i] > time ) {
				Vector3f prev = kf.GetTranslations()[i - 1];
				Vector3f next = kf.GetTranslations()[i];
				float prevtime = kf.GetTimeLineTrans()[i - 1];
				float nexttime = kf.GetTimeLineTrans()[i];
				float ratio = ( time - prevtime ) / ( nexttime - prevtime );
				t = prev + ( next - prev ) * ratio;
				break;
			} else if ( fabsf(kf.GetTimeLineTrans()[i] - time) == 0.00001 ) {
				t = kf.GetTranslations()[i];
				break;
			}
		}
		if ( i >= kf.GetNumTranslations()) {
			i = kf.GetNumTranslations() - 1;
		}
	}
}

void MGEModelSequence::GetInterpolate(MGEModelKeyFrame &kfa, MGEModelKeyFrame &kfb, Quaternion &q, Vector3f &t, float ratio) {
	if ( ratio < 0.0f ) {
		return;
	}
	////q = kfb.GetTemporaryRotation();
	q = kfa.GetTemporaryRotation().Slerp(ratio, kfb.GetTemporaryRotation());
///	RotInterpolate(q, kfa.GetTemporaryRotation(), kfb.GetTemporaryRotation(), ratio);
	t = kfa.GetTemporaryTranslation() + ( kfb.GetTemporaryTranslation() - kfa.GetTemporaryTranslation() ) * ratio;
}

void MGEModelSequence::LoadAnimationMatrix(MGEModelBoneTreeNode &btn, float time) {
	MGEModelKeyFrame *kf = (MGEModelKeyFrame*)(controlledNodes.Get(btn.name));
	if (kf != NULL) {
		Vector3f t;
		Quaternion q;
		Matrix33f m;
		GetInterpolate(*kf, q, t, time);
		m.fromQuat(q);
		btn.GetTransform() = Transform(t, m, 1.0f);
	}
	if (btn.HasSubNode()) {
		LoadAnimationMatrix(btn.GetSubNode(), time);
	}
	if (btn.HasNextNode()) {
		LoadAnimationMatrix(btn.GetNextNode(), time);
	}
}

void MGEModelSequence::LoadAnimationMatrix(MGEModelBoneTreeNode &btn, unsigned int _index) {
	MGEModelKeyFrame *kf = (MGEModelKeyFrame*)(controlledNodes.Get(btn.name));
	if (kf != NULL) {
		Vector3f t;
		Quaternion q;
		Matrix33f m;

		GetTransform(*kf, q, t, _index);

		m.fromQuat(q);
		btn.GetTransform() = Transform(t, m, 1.0f);
	}
	if (btn.HasSubNode()) {
		LoadAnimationMatrix(btn.GetSubNode(), _index);
	}
	if (btn.HasNextNode()) {
		LoadAnimationMatrix(btn.GetNextNode(), _index);
	}
}

void MGEModelSequence::LoadAnimationMatrix(MGEModelSequence &sqb, MGEModelBoneTreeNode &btn, float ratio) {
	MGEModelKeyFrame *kfa = (MGEModelKeyFrame*)(controlledNodes.Get(btn.name));
	MGEModelKeyFrame *kfb = (MGEModelKeyFrame*)(sqb.controlledNodes.Get(btn.name));
	if ( ( kfa != NULL ) && ( kfb != NULL ) ) {
		Vector3f t;
		Quaternion q;
		Matrix33f m;
		GetInterpolate(*kfa, *kfb, q, t, ratio);
		m.fromQuat(q);
		btn.GetTransform() = Transform(t, m, 1.0f);
	}
	if (btn.HasSubNode()) {
		LoadAnimationMatrix(sqb, btn.GetSubNode(), ratio);
	}
	if (btn.HasNextNode()) {
		LoadAnimationMatrix(sqb, btn.GetNextNode(), ratio);
	}
}

void MGEModelSequence::BuildTemporaryAnimation(float time) {
	unsigned int numKFs = keyFrames.GetLength();
	for ( unsigned int i1 = 0 ; i1 < numKFs ; i1 ++ ) {
		MGEModelKeyFrame *kf = &(keyFrames[i1]);
		if (kf != NULL) {
			GetInterpolate(*kf, kf->GetTemporaryRotation(), kf->GetTemporaryTranslation(), time);
		}
	}
}

