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

#include "stdio.h"

#include "string.h"
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "Bone.hpp"

MGEModelBone::MGEModelBone() {
	numVertices = 0;
	vertexIndices.Resize(0);
	weights.Resize(0);
}

MGEModelBone::MGEModelBone(MGEModelBoneTreeNode *sc) {
	numVertices = 0;
	vertexIndices.Resize(0);
	weights.Resize(0);

	shortCut = sc;
}

MGEModelBone::~MGEModelBone() {
	vertexIndices.Resize(0);
	weights.Resize(0);
}

const char *MGEModelBone::GetClassName() {
	return "MGEModelBone";
}

BOOL32 MGEModelBone::IsInstanceof(const char* className) {
	if (strcmp("MGEModelBone", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelBone::Serialize(MGEIOStream &iio) {
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
			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.ReadBuffer(&boundingSphereOffset, 3, sizeof(float));
			iio.Read(&boundingSphereRadius, sizeof(float));

			
			iio.Read(&numVertices, sizeof(unsigned short));
			if (numVertices > 0) {
				vertexIndices.Resize(numVertices);
				iio.ReadBuffer(vertexIndices.GetBuffer(), numVertices, sizeof(unsigned short));
				weights.Resize(numVertices);
				iio.ReadBuffer(weights.GetBuffer(), numVertices, sizeof(float));
			}

		}
	} else {
		name.Store(iio);
		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));
		iio.WriteBuffer(&boundingSphereOffset, 3, sizeof(float));
		iio.Write(&boundingSphereRadius, sizeof(float));

		iio.Write(&numVertices, sizeof(unsigned short));
		if (numVertices > 0) {
			iio.WriteBuffer(vertexIndices.GetBuffer(), numVertices, sizeof(unsigned short));
			iio.WriteBuffer(weights.GetBuffer(), numVertices, sizeof(float));
		}
	}
}

Vector3f &MGEModelBone::GetTranslation() {
	return translation;
}

Matrix33f &MGEModelBone::GetRotation() {
	return rotation;
}

float &MGEModelBone::GetScale() {
	return scale;
}

Vector3f &MGEModelBone::GetBoundingSphereOffset() {
	return boundingSphereOffset;
}

float &MGEModelBone::GetBoundingSphereRadius() {
	return boundingSphereRadius;
}

MGEDataArray<unsigned short> &MGEModelBone::GetVertexIndices() {
	return vertexIndices;
}

MGEDataArray<float> &MGEModelBone::GetWeights() {
	return weights;
}

MGEModelBoneTreeNode &MGEModelBone::GetBoneNode() {
	return *shortCut;
}

void MGEModelBone::SetNumVertices(unsigned short num) {
	numVertices = num;
	weights.Resize(num);
	vertexIndices.Resize(num);
}

unsigned short MGEModelBone::GetNumVertices() {
	return numVertices;
}
