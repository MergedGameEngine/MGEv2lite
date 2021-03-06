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
	surfaces.Resize(0);
	bones.Resize(0);
	numSkins = 0;
	numBones = 0;

	numUVWkeys = 0;
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
	surfaces.Resize(0);
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
			hasVertices = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasNormals = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasBinormals = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasTangents = ( _temp != 0 );
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
			hasUV = ( _temp != 0 );
			if (hasUV) {
				uvMap.Resize(numVertices);
				iio.ReadBuffer(uvMap.GetBuffer(), numVertices * 2, sizeof(float));
			}

			iio.Read(&numTriangles, sizeof(unsigned int));
			iio.Read(&numStrips, sizeof(unsigned short));
			iio.Read(&_temp, sizeof(char));
			hasTriangles = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasStrips = ( _temp != 0 );
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
			surfaces.Resize(numSkins);
			surfaces.CreateAll();
			for (unsigned int i1 = 0 ; i1 < numSkins ; i1 ++ ) {
				MGETString sClassName;//Unicode,UCS2
				sClassName.Load(iio);
				surfaces[i1].version = version;
				surfaces[i1].subVersion = subVersion;
				surfaces[i1].Serialize(iio);
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
		} else
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000001 ) ) {
			name.Load(iio);	//MBCS or UTF8

			iio.Read(&flags, sizeof(unsigned int));

			iio.Read(&numVertices, sizeof(unsigned short));

			if ( flags & _MODEL_MESH_CONTAIN_VERTICES_ ) {
				vertices.Resize(numVertices);
				iio.ReadBuffer(vertices.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if ( flags & _MODEL_MESH_CONTAIN_NORMALS_ ) {
				normals.Resize(numVertices);
				iio.ReadBuffer(normals.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if ( flags & _MODEL_MESH_CONTAIN_BINORMALS_ ) {
				binormals.Resize(numVertices);
				iio.ReadBuffer(binormals.GetBuffer(), numVertices * 3, sizeof(float));
			}
			if ( flags & _MODEL_MESH_CONTAIN_TANGENTS_ ) {
				tangents.Resize(numVertices);
				iio.ReadBuffer(tangents.GetBuffer(), numVertices * 3, sizeof(float));
			}

			iio.ReadBuffer(&center, 3, sizeof(float));
			iio.Read(&radius, sizeof(float));

			if ( flags & _MODEL_MESH_CONTAIN_TEXCOORDS_ ) {
				uvMap.Resize(numVertices);
				iio.ReadBuffer(uvMap.GetBuffer(), numVertices * 2, sizeof(float));
			}

			if ( flags & _MODEL_MESH_CONTAIN_UVWCOORDS_ ) {
				uvwMap.Resize(numVertices);
				iio.ReadBuffer(uvwMap.GetBuffer(), numVertices * 3, sizeof(float));
			}

			if ( flags & _MODEL_MESH_CONTAIN_UVWKEYS_ ) {
				iio.Read(&numUVWkeys, sizeof(unsigned short));
				uvwIndices.Resize(numUVWkeys);
				uvwIndices.CreateAll();
				for (unsigned int i3 = 0 ; i3 < numUVWkeys ; i3 ++ ) {
					uvwIndices[i3].Load(iio);	//MBCS or UTF8
				}
			}

			iio.Read(&numTriangles, sizeof(unsigned int));
			iio.Read(&numStrips, sizeof(unsigned short));

			if ( flags & _MODEL_MESH_CONTAIN_TRIANGLES_ ) {
				triangles.Resize(numTriangles);
				iio.ReadBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
			}
			if ( flags & _MODEL_MESH_CONTAIN_STRIPS_ ) {
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
			surfaces.Resize(numSkins);
			surfaces.CreateAll();
			for (unsigned int i1 = 0 ; i1 < numSkins ; i1 ++ ) {
				MGEString sClassName;	//MBCS or UTF8
				sClassName.Load(iio);
				surfaces[i1].version = version;
				surfaces[i1].subVersion = subVersion;
				surfaces[i1].Serialize(iio);
			}
			iio.ReadBuffer(&boneTranslation, 3, sizeof(float));
			iio.ReadBuffer(&boneRotation, 9, sizeof(float));
			iio.Read(&boneScale, sizeof(float));
			iio.Read(&numBones, sizeof(unsigned short));
			bones.Resize(numBones);
			bones.CreateAll();
			for (unsigned int i2 = 0 ; i2 < numBones ; i2 ++ ) {
				MGEString bClassName;	//MBCS or UTF8
				bClassName.Load(iio);
				bones[i2].version = version;
				bones[i2].subVersion = subVersion;
				bones[i2].Serialize(iio);
			}
			if (numBones > 0) {
				boneBlockIndices.Resize(numBones);
				boneBlockIndices.CreateAll();
				for (unsigned int i3 = 0 ; i3 < numBones ; i3 ++ ) {
					boneBlockIndices[i3].Load(iio);	//MBCS or UTF8
				}
			}
		} else
		{
		}
	} else {
		flags = 0;
		//version = 0x00000001;
		//subVersion = 0x00000001;

		if ( (numVertices != 0) && (normals.GetLength() >= numVertices) ) {
			hasNormals = TRUE;
			flags |= _MODEL_MESH_CONTAIN_NORMALS_;
		}
		if ( (numTriangles != 0) && (triangles.GetLength() >= numTriangles) ) {
			hasTriangles = TRUE;
			flags |= _MODEL_MESH_CONTAIN_TRIANGLES_;
		}
		if ( (numVertices != 0) && (uvMap.GetLength() >= numVertices) ) {
			hasUV = TRUE;
			flags |= _MODEL_MESH_CONTAIN_TEXCOORDS_;
		}
		if ( (numVertices != 0) && (vertices.GetLength() >= numVertices) ) {
			hasVertices = TRUE;
			flags |= _MODEL_MESH_CONTAIN_VERTICES_;
		}

		if ( (numVertices != 0) && (binormals.GetLength() >= numVertices) ) {
			hasBinormals = TRUE;
			flags |= _MODEL_MESH_CONTAIN_BINORMALS_;
		}
		if ( (numStrips != 0) && (strips.GetLength() == numStrips) ) {
			hasStrips = TRUE;
			flags |= _MODEL_MESH_CONTAIN_STRIPS_;
		}

		if ( (numVertices != 0) && (tangents.GetLength() >= numVertices) ) {
			hasTangents = TRUE;
			flags |= _MODEL_MESH_CONTAIN_TANGENTS_;
		}

		if ( (numVertices != 0) && (uvwMap.GetLength() >= numVertices) ) {
			flags |= _MODEL_MESH_CONTAIN_UVWCOORDS_;
		}

		if ( ( numUVWkeys != 0 ) && (numVertices != 0) && (uvwMap.GetLength() >= numVertices) ) {
			flags |= _MODEL_MESH_CONTAIN_UVWKEYS_;
		}

		name.Store(iio);
		iio.Write(&flags, sizeof(unsigned int));

		iio.Write(&numVertices, sizeof(unsigned short));

		if (hasVertices) {
			iio.WriteBuffer(vertices.GetBuffer(), numVertices * 3, sizeof(float));
		}
		if (hasNormals) {
			iio.WriteBuffer(normals.GetBuffer(), numVertices * 3, sizeof(float));
		}
		if (hasBinormals) {
			iio.WriteBuffer(binormals.GetBuffer(), numVertices * 3, sizeof(float));
		}
		if (hasTangents) {
			iio.WriteBuffer(tangents.GetBuffer(), numVertices * 3, sizeof(float));
		}
		iio.WriteBuffer(&center, 3, sizeof(float));
		iio.Write(&radius, sizeof(float));

		if (hasUV) {
			iio.WriteBuffer(uvMap.GetBuffer(), numVertices * 2, sizeof(float));
		}

		if ( flags & _MODEL_MESH_CONTAIN_UVWCOORDS_ ) {
			iio.WriteBuffer(uvwMap.GetBuffer(), numVertices * 3, sizeof(float));
		}

		if ( flags & _MODEL_MESH_CONTAIN_UVWKEYS_ ) {
			iio.Write(&numUVWkeys, sizeof(unsigned short));
			for (unsigned int i3 = 0 ; i3 < numUVWkeys ; i3 ++ ) {
				uvwIndices[i3].Store(iio);	//MBCS or UTF8
			}
		}

		iio.Write(&numTriangles, sizeof(unsigned int));
		iio.Write(&numStrips, sizeof(unsigned short));

		if (hasTriangles) {
			iio.WriteBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
		}
		if (hasStrips) {
			iio.WriteBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
			for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
				iio.WriteBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
			}
		}

		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));
		numSkins = (unsigned short)surfaces.GetLength();
		iio.Write(&numSkins, sizeof(unsigned short));
		for (unsigned int i1 = 0 ; i1 < numSkins ; i1 ++ ) {
			MGEString sClassName(surfaces[i1].GetClassName());
			sClassName.Store(iio);
			surfaces[i1].version = version;
			surfaces[i1].subVersion = subVersion;

			surfaces[i1].Serialize(iio);
		}
		iio.WriteBuffer(&boneTranslation, 3, sizeof(float));
		iio.WriteBuffer(&boneRotation, 9, sizeof(float));
		iio.Write(&boneScale, sizeof(float));
		numBones = (unsigned short)bones.GetLength();
		iio.Write(&numBones, sizeof(unsigned short));
		for (unsigned int i1 = 0 ; i1 < numBones ; i1 ++ ) {
			MGEString bClassName(bones[i1].GetClassName());
			bClassName.Store(iio);
			bones[i1].version = version;
			bones[i1].subVersion = subVersion;

			bones[i1].Serialize(iio);
		}
		for (unsigned int i2 = 0 ; i2 < numBones ; i2 ++ ) {
			boneBlockIndices[i2].Store(iio);
		}
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

BOOL8 MGEModelMesh::HasUVW() {
	return ((numVertices != 0) && (uvwMap.GetLength() >= numVertices));
}

MGEDataArray<Vector3f> &MGEModelMesh::GetUVWMap() {
	return uvwMap;
}

BOOL8 MGEModelMesh::HasUVWKeys() {
	return ( numUVWkeys != 0 );
}
MGERefArray<MGEString> &MGEModelMesh::GetUVWKeys() {
	return uvwIndices;
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

MGERefArray<MGEModelSurface> &MGEModelMesh::GetSurfaces() {
	return surfaces;
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
