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
#include "Mesh.hpp"

MGEModelMesh::MGEModelMesh() {
	numVertices = 0;
	hasVertices = FALSE;
	hasNormals = FALSE;
	hasBinormals = FALSE;
	hasTangents = FALSE;
	vertices.Resize(0);
	normals.Resize(0);
	binormals.Resize(0);
	tangents.Resize(0);
	hasUV = FALSE;
	uvMap.Resize(0);

	numTriangles = 0;
	numStrips = 0;
	hasTriangles = FALSE;
	hasStrips = FALSE;
	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.Resize(0);

	boneBlockIndices.Resize(0);
	boneMatrices.Resize(0);
	skins.Resize(0);
	bones.Resize(0);
	numSkins = 0;
	numBones = 0;
}

MGEModelMesh::~MGEModelMesh() {
	vertices.Resize(0);
	normals.Resize(0);
	binormals.Resize(0);
	tangents.Resize(0);
	hasUV = FALSE;
	uvMap.Resize(0);

	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.DeleteAll();
	strips.Resize(0);

	boneBlockIndices.Resize(0);
	boneMatrices.Resize(0);
	skins.Resize(0);
	bones.Resize(0);
}

const char *MGEModelMesh::GetClassName() {
	return "MGEModelMesh";
}

BOOL32 MGEModelMesh::IsInstanceof(const char* className) {
	if (strcmp("MGEModelMesh", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelMesh::Serialize(MGEIOStream &iio) {
///	TModelObject::Serialize(iio);
	char _temp = 0;
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
			iio.Read(&numVertices, sizeof(unsigned short));
			iio.Read(&_temp, sizeof(char));
			hasVertices = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasNormals = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasBinormals = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasTangents = (BOOL8)_temp;
			if (hasVertices) {
				vertices.Resize(numVertices);
				iio.ReadBuffer(vertices.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if (hasNormals) {
				normals.Resize(numVertices);
				iio.ReadBuffer(normals.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if (hasBinormals) {
				binormals.Resize(numVertices);
				iio.ReadBuffer(binormals.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if (hasTangents) {
				tangents.Resize(numVertices);
				iio.ReadBuffer(tangents.GetBuffer(), numVertices * 3, sizeof(float));
			}
			iio.ReadBuffer(&center, 3, sizeof(float));
			iio.Read(&radius, sizeof(float));
			iio.Read(&_temp, sizeof(char));
			hasUV = (BOOL8)_temp;
			if (hasUV) {
				uvMap.Resize(numVertices);
				iio.ReadBuffer(uvMap.GetBuffer(), numVertices * 2, sizeof(float));
			}

			iio.Read(&numTriangles, sizeof(unsigned int));
			iio.Read(&numStrips, sizeof(unsigned short));
			iio.Read(&_temp, sizeof(char));
			hasTriangles = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasStrips = (BOOL8)_temp;
			if (hasTriangles) {
				triangles.Resize(numTriangles);
				iio.ReadBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
			}
			if (hasStrips) {
				strips.Resize(numStrips);
				strips.CreateAll();
				stripLengths.Resize(numStrips);
				iio.ReadBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
				for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
					strips[i1].Resize(stripLengths[i1]);
					iio.ReadBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
				}
			}

			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.Read(&numSkins, sizeof(unsigned short));
			skins.Resize(numSkins);
			skins.CreateAll();
			for (unsigned int i1 = 0 ; i1 < numSkins ; i1 ++ ) {
				MGETString sClassName;//Unicode,UCS2
				sClassName.Load(iio);
				skins[i1].version = version;
				skins[i1].subVersion = subVersion;
				skins[i1].Serialize(iio);
			}
			iio.ReadBuffer(&boneTranslation, 3, sizeof(float));
			iio.ReadBuffer(&boneRotation, 9, sizeof(float));
			iio.Read(&boneScale, sizeof(float));
			iio.Read(&numBones, sizeof(unsigned short));
			bones.Resize(numBones);
			bones.CreateAll();
			for (unsigned int i2 = 0 ; i2 < numBones ; i2 ++ ) {
				MGETString bClassName;//Unicode,UCS2
				bClassName.Load(iio);
				bones[i2].version = version;
				bones[i2].subVersion = subVersion;
				bones[i2].Serialize(iio);
			}
			if (numBones > 0) {
				boneBlockIndices.Resize(numBones);
				boneBlockIndices.CreateAll();
				for (unsigned int i3 = 0 ; i3 < numBones ; i3 ++ ) {
					MGETString _boneName;//Unicode,UCS2
					_boneName.Load(iio);
					if ( _boneName.GetBuffer() ) {
#ifdef WIN32
						boneBlockIndices[i3] = MGEString("%ls",_boneName.GetBuffer());
#else
						MGEWString __wstr(_boneName.GetBuffer());
						boneBlockIndices[i3] = MGEString("%ls",__wstr.GetBuffer());
#endif				
					}
				}
			}
		}
	} else {
		////hasVertices = ((numVertices != 0) && (vertices.GetLength() >= numVertices));
		////hasNormals = ((numVertices != 0) && (normals.GetLength() >= numVertices));
		////hasBinormals = ((numVertices != 0) && (binormals.GetLength() >= numVertices));
		////hasTangents = ((numVertices != 0) && (tangents.GetLength() >= numVertices));

		////hasUV = ((numVertices != 0) && (uvMap.GetLength() >= numVertices));

		////hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
		////hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));

		////name.Store(iio);
		////iio.Write(&numVertices, sizeof(unsigned short));
		////iio.Write(&hasVertices, sizeof(BOOL8));
		////iio.Write(&hasNormals, sizeof(BOOL8));
		////iio.Write(&hasBinormals, sizeof(BOOL8));
		////iio.Write(&hasTangents, sizeof(BOOL8));
		////if (hasVertices) {
		////	iio.WriteBuffer(vertices.GetBuffer(), numVertices * 3, sizeof(float));
		////}
		////if (hasNormals) {
		////	iio.WriteBuffer(normals.GetBuffer(), numVertices * 3, sizeof(float));
		////}
		////if (hasBinormals) {
		////	iio.WriteBuffer(binormals.GetBuffer(), numVertices * 3, sizeof(float));
		////}
		////if (hasTangents) {
		////	iio.WriteBuffer(tangents.GetBuffer(), numVertices * 3, sizeof(float));
		////}
		////iio.WriteBuffer(&center, 3, sizeof(float));
		////iio.Write(&radius, sizeof(float));
		////iio.Write(&hasUV, sizeof(BOOL8));
		////if (hasUV) {
		////	iio.WriteBuffer(uvMap.GetBuffer(), numVertices * 2, sizeof(float));
		////}

		////iio.Write(&numTriangles, sizeof(unsigned int));
		////iio.Write(&numStrips, sizeof(unsigned short));
		////iio.Write(&hasTriangles, sizeof(BOOL8));
		////iio.Write(&hasStrips, sizeof(BOOL8));
		////if (hasTriangles) {
		////	iio.WriteBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
		////}
		////if (hasStrips) {
		////	iio.WriteBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
		////	for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
		////		iio.WriteBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
		////	}
		////}

		////iio.WriteBuffer(&translation, 3, sizeof(float));
		////iio.WriteBuffer(&rotation, 9, sizeof(float));
		////iio.Write(&scale, sizeof(float));
		////numSkins = (unsigned short)skins.GetLength();
		////iio.Write(&numSkins, sizeof(unsigned short));
		////for (unsigned int i1 = 0 ; i1 < numSkins ; i1 ++ ) {
		////	MGEString sClassName(skins[i1].GetClassName());
		////	sClassName.Store(iio);
		////	skins[i1].Serialize(iio);
		////}
		////iio.WriteBuffer(&boneTranslation, 3, sizeof(float));
		////iio.WriteBuffer(&boneRotation, 9, sizeof(float));
		////iio.Write(&boneScale, sizeof(float));
		////numBones = (unsigned short)bones.GetLength();
		////iio.Write(&numBones, sizeof(unsigned short));
		////for (unsigned int i1 = 0 ; i1 < numBones ; i1 ++ ) {
		////	MGEString bClassName(bones[i1].GetClassName());
		////	bClassName.Store(iio);
		////	bones[i1].Serialize(iio);
		////}
		////for (unsigned int i2 = 0 ; i2 < numBones ; i2 ++ ) {
		////	boneBlockIndices[i2].Store(iio);
		////}
	}
}

BOOL8 MGEModelMesh::HasVertices() {
	return hasVertices = ((numVertices != 0) && (vertices.GetLength() >= numVertices));
}

BOOL8 MGEModelMesh::HasNormals() {
	return hasNormals = ((numVertices != 0) && (normals.GetLength() >= numVertices));
}

BOOL8 MGEModelMesh::HasBinormals() {
	return hasBinormals = ((numVertices != 0) && (binormals.GetLength() >= numVertices));
}

BOOL8 MGEModelMesh::HasTangents() {
	return hasTangents = ((numVertices != 0) && (tangents.GetLength() >= numVertices));
}

MGEDataArray<Vector3f> &MGEModelMesh::GetVertices() {
	return vertices;
}

MGEDataArray<Vector3f> &MGEModelMesh::GetNormals() {
	return normals;
}

MGEDataArray<Vector3f> &MGEModelMesh::GetBinormals() {
	return binormals;
}

MGEDataArray<Vector3f> &MGEModelMesh::GetTangents() {
	return tangents;
}

Vector3f &MGEModelMesh::GetCenter() {
	return center;
}

float &MGEModelMesh::GetRadius() {
	return radius;
}

BOOL8 MGEModelMesh::HasUV() {
	return hasUV = ((numVertices != 0) && (uvMap.GetLength() >= numVertices));
}

MGEDataArray<TexCoord2f> &MGEModelMesh::GetUVMap() {
	return uvMap;
}

BOOL8 MGEModelMesh::HasTriangles() {
	return hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
}

BOOL8 MGEModelMesh::HasStrips() {
	return hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));
}

MGEDataArray<Triangle> &MGEModelMesh::GetTriangles() {
	return triangles;
}

MGEDataArray<unsigned short> &MGEModelMesh::GetStripLengths() {
	return stripLengths;
}

MGERefArray<TUShortArray> &MGEModelMesh::GetStrips() {
	return strips;
}

Vector3f &MGEModelMesh::GetTranslation() {
	return translation;
}

Matrix33f &MGEModelMesh::GetRotation() {
	return rotation;
}

float &MGEModelMesh::GetScale() {
	return scale;
}

Vector3f &MGEModelMesh::GetBoneTranslation() {
	return boneTranslation;
}

Matrix33f &MGEModelMesh::GetBoneRotation() {
	return boneRotation;
}

float &MGEModelMesh::GetBoneScale() {
	return boneScale;
}

MGERefArray<MGEModelSkin> &MGEModelMesh::GetSkins() {
	return skins;
}

MGERefArray<MGEModelBone> &MGEModelMesh::GetBones() {
	return bones;
}

MGERefArray<MGEString> &MGEModelMesh::GetBoneBlockIndices() {
	return boneBlockIndices;
}

MGERefArray<MGEModelBoneTreeNode> &MGEModelMesh::GetBoneNodes() {
	return boneNodes;
}

unsigned short MGEModelMesh::GetNumVertices() {
	return numVertices;
}

void MGEModelMesh::SetNumVertices(unsigned short num) {
	numVertices = num;
}

unsigned int MGEModelMesh::GetNumTriangles() {
	return numTriangles;
}

void MGEModelMesh::SetNumTriangles(unsigned short num) {
	numTriangles = num;
	triangles.Resize(num);
}

unsigned short MGEModelMesh::GetNumStrips() {
	return numStrips;
}

void MGEModelMesh::SetNumStrips(unsigned short num) {
	numStrips = num;
}

void MGEModelMesh::BuildTangentsBinormals() {
	if ( hasTriangles ) {
		if ( ( !hasNormals ) || ( !hasBinormals ) ) {
			tangents.Resize(numVertices);
			binormals.Resize(numVertices);
			for (unsigned int i1 = 0 ; i1 < numTriangles ; i1 ++ ) {
				Vector3f tangent1(vertices[triangles[i1].c].x - vertices[triangles[i1].a].x, vertices[triangles[i1].c].y - vertices[triangles[i1].a].y, vertices[triangles[i1].c].z - vertices[triangles[i1].a].z);
				tangent1 = tangent1.Normalized();
				Vector3f binormal1 = (tangent1^normals[triangles[i1].a]).Normalized();
				tangents[triangles[i1].a] = tangent1;
				binormals[triangles[i1].a] = binormal1;

				Vector3f tangent2(vertices[triangles[i1].a].x - vertices[triangles[i1].b].x, vertices[triangles[i1].a].y - vertices[triangles[i1].b].y, vertices[triangles[i1].a].z - vertices[triangles[i1].b].z);
				tangent2 = tangent2.Normalized();
				Vector3f binormal2 = (tangent2^normals[triangles[i1].b]).Normalized();
				tangents[triangles[i1].b] = tangent2;
				binormals[triangles[i1].b] = binormal2;

				Vector3f tangent3(vertices[triangles[i1].b].x - vertices[triangles[i1].c].x, vertices[triangles[i1].b].y - vertices[triangles[i1].c].y, vertices[triangles[i1].b].z - vertices[triangles[i1].c].z);
				tangent3 = tangent3.Normalized();
				Vector3f binormal3 = (tangent3^normals[triangles[i1].c]).Normalized();
				tangents[triangles[i1].c] = tangent3;
				binormals[triangles[i1].c] = binormal3;
			}
			hasNormals = TRUE;
			hasBinormals = TRUE;
		}
	} else if ( hasStrips ) {
		if ( ( !hasNormals ) || ( !hasBinormals ) ) {
			if ( stripLengths.GetLength() < 1 ) {
				return;
			}
			if ( strips.GetLength() < 1 ) {
				return;
			}
			tangents.Resize(numVertices);
			binormals.Resize(numVertices);
			unsigned int sl = stripLengths[0] - 1;
			MGEDataArray<unsigned short> &strip = strips[0];
			for (unsigned int i1 = 0 ; i1 < sl ; i1 ++ ) {
				Vector3f tangent1(vertices[strip[i1 + 1]].x - vertices[strip[i1]].x, vertices[strip[i1 + 1]].y - vertices[strip[i1]].y, vertices[strip[i1 + 1]].z - vertices[strip[i1]].z);
				tangent1 = tangent1.Normalized();
				Vector3f binormal1 = (tangent1^normals[strip[i1]]).Normalized();
				tangents[strip[i1]] = tangent1;
				binormals[strip[i1]] = binormal1;
			}
			hasNormals = TRUE;
			hasBinormals = TRUE;
		}
	}
}

void MGEModelMesh::CopyBoneBlockIndices(MGEModelMesh &tar) {
	tar.name = name;
	unsigned int length = boneBlockIndices.GetLength();
	tar.boneBlockIndices.Resize(length);
	tar.boneBlockIndices.CreateAll();
	for ( unsigned int i2 = 0 ; i2 < length ; i2 ++ ) {
		tar.boneBlockIndices[i2] = boneBlockIndices[i2];
	}
	tar.numBones = length;
}

MGEDataArray<Matrix44f> &MGEModelMesh::GetBoneMatrices() {
	return boneMatrices;
}
