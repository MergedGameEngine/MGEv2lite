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
#include "../MGE__MathTool/MathTool.hpp"
#include "Skin.hpp"

MGEModelSkin::MGEModelSkin() {
	numVertices = 0;
	numTriangles = 0;
	numStrips = 0;
	numBones = 0;
	numWeightPerVertex = 0;
	hasVertexMaps = FALSE;
	hasTriangles = FALSE;
	hasStrips = FALSE;
	hasBones = FALSE;
	hasVertexWeights = FALSE;
	hasBoneIndices = FALSE;
	vertexMap.Resize(0);
	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.Resize(0);
	bones.Resize(0);
	vertexWeights.Resize(0);
	boneIndices.Resize(0);

	isExternalMaterial = FALSE;
	isExternalPhysical = FALSE;
}

MGEModelSkin::~MGEModelSkin() {
	vertexMap.Resize(0);
	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.DeleteAll();
	strips.Resize(0);
	bones.Resize(0);
	vertexWeights.Resize(0);
	boneIndices.Resize(0);
}

const char *MGEModelSkin::GetClassName() {
	return "MGEModelSkin";
}

BOOL32 MGEModelSkin::IsInstanceof(const char* className) {
	if (strcmp("MGEModelSkin", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelSkin::Serialize(MGEIOStream &iio) {
///	TModelObject::Serialize(iio);
	char _temp = 0;
	if ( iio.GetLoadStore() == MGEIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {

			iio.Read(&numVertices, sizeof(unsigned short));
			iio.Read(&numTriangles, sizeof(unsigned int));
			iio.Read(&numStrips, sizeof(unsigned short));
			iio.Read(&numBones, sizeof(unsigned short));
			iio.Read(&numWeightPerVertex, sizeof(unsigned short));
			iio.Read(&_temp, sizeof(char));
			hasVertexMaps = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasTriangles = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasStrips = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasBones = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasVertexWeights = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasBoneIndices = (BOOL8)_temp;

			if (hasVertexMaps) {
				vertexMap.Resize(numVertices);
				iio.ReadBuffer(vertexMap.GetBuffer(), numVertices, sizeof(unsigned short));
			}

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

			if (hasBones) {
				bones.Resize(numBones);
				iio.ReadBuffer(bones.GetBuffer(), numBones, sizeof(unsigned short));
			}

			if (hasVertexWeights) {
				vertexWeights.Resize(numVertices * numWeightPerVertex);
				iio.ReadBuffer(vertexWeights.GetBuffer(), numVertices * numWeightPerVertex, sizeof(float));
			}

			if (hasBoneIndices) {
				boneIndices.Resize(numVertices * numWeightPerVertex);
				iio.ReadBuffer(boneIndices.GetBuffer(), numVertices * numWeightPerVertex, sizeof(unsigned short));
			}

			MGETString _strtemp;
			iio.Read(&_temp, sizeof(char));
			isExternalMaterial = (BOOL8)_temp;
			_strtemp.Load(iio);
			if ( _strtemp.GetBuffer() ) {
#ifdef WIN32
				fileLinkMtl = MGEString("%ls",_strtemp.GetBuffer());
#else
				MGEWString __wstr(_strtemp.GetBuffer());
				fileLinkMtl = MGEString("%ls",__wstr.GetBuffer());
#endif				
			}
			iio.Read(&_temp, sizeof(char));
			isExternalPhysical = (BOOL8)_temp;
			_strtemp.Load(iio);
			if ( _strtemp.GetBuffer() ) {
#ifdef WIN32
				fileLinkPhy = MGEString("%ls",_strtemp.GetBuffer());
#else
				MGEWString __wstr(_strtemp.GetBuffer());
				fileLinkPhy = MGEString("%ls",__wstr.GetBuffer());
#endif				
			}
		}
	} else {
		hasVertexMaps = ((numVertices != 0) && (vertexMap.GetLength() >= numVertices));
		hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
		hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));
		hasBones = ((numBones != 0) && (bones.GetLength() >= numBones));
		hasVertexWeights = (((numVertices * numWeightPerVertex) != 0) && (vertexWeights.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));
		hasBoneIndices = (((numVertices * numWeightPerVertex) != 0) && (boneIndices.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));

		iio.Write(&numVertices, sizeof(unsigned short));
		iio.Write(&numTriangles, sizeof(unsigned int));
		iio.Write(&numStrips, sizeof(unsigned short));
		iio.Write(&numBones, sizeof(unsigned short));
		iio.Write(&numWeightPerVertex, sizeof(unsigned short));
		iio.Write(&hasVertexMaps, sizeof(BOOL8));
		iio.Write(&hasTriangles, sizeof(BOOL8));
		iio.Write(&hasStrips, sizeof(BOOL8));
		iio.Write(&hasBones, sizeof(BOOL8));
		iio.Write(&hasVertexWeights, sizeof(BOOL8));
		iio.Write(&hasBoneIndices, sizeof(BOOL8));
		if (hasVertexMaps) {
			iio.WriteBuffer(vertexMap.GetBuffer(), numVertices, sizeof(unsigned short));
		}
		if (hasTriangles) {
			iio.WriteBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
		}
		if (hasStrips) {
			iio.WriteBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
			for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
				iio.WriteBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
			}
		}
		if (hasBones) {
			iio.WriteBuffer(bones.GetBuffer(), numBones, sizeof(unsigned short));
		}
		if (hasVertexWeights) {
			iio.WriteBuffer(vertexWeights.GetBuffer(), numVertices * numWeightPerVertex, sizeof(float));
		}
		if (hasBoneIndices) {
			iio.WriteBuffer(boneIndices.GetBuffer(), numVertices * numWeightPerVertex, sizeof(unsigned short));
		}

		isExternalMaterial = TRUE;
		isExternalPhysical = TRUE;
		iio.Write(&isExternalMaterial, sizeof(BOOL8));
		fileLinkMtl.Store(iio);
		iio.Write(&isExternalPhysical, sizeof(BOOL8));
		fileLinkPhy.Store(iio);
	}
}

BOOL8 MGEModelSkin::HasVertexMaps() {
	return hasVertexMaps = ((numVertices != 0) && (vertexMap.GetLength() >= numVertices));
}

BOOL8 MGEModelSkin::HasTriangles() {
	return hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
}

BOOL8 MGEModelSkin::HasStrips() {
	return hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));
}

BOOL8 MGEModelSkin::HasBones() {
	return hasBones = ((numBones != 0) && (bones.GetLength() >= numBones));
}

BOOL8 MGEModelSkin::HasVertexWeights() {
	return hasVertexWeights = (((numVertices * numWeightPerVertex) != 0) 
		&& (vertexWeights.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));
}

BOOL8 MGEModelSkin::HasBoneIndices() {
	return hasBoneIndices = (((numVertices * numWeightPerVertex) != 0) 
		&& (boneIndices.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));
}

MGEDataArray<unsigned short> &MGEModelSkin::GetVertexMap() {
	return vertexMap;
}

MGEDataArray<Triangle> &MGEModelSkin::GetTriangles() {
	return triangles;
}

MGEDataArray<unsigned short> &MGEModelSkin::GetStripLengths() {
	return stripLengths;
}

MGERefArray<TUShortArray> &MGEModelSkin::GetStrips() {
	return strips;
}

MGEDataArray<unsigned short> &MGEModelSkin::GetBones() {
	return bones;
}

MGEDataArray<float> &MGEModelSkin::GetVertexWeights() {
	return vertexWeights;
}

MGEDataArray<unsigned short> &MGEModelSkin::GetBoneIndices() {
	return boneIndices;
}

unsigned short MGEModelSkin::GetNumVertices() {
	return numVertices;
}

void MGEModelSkin::SetNumVertices(unsigned short num) {
	numVertices = num;
}

unsigned int MGEModelSkin::GetNumTriangles() {
	return numTriangles;
}

void MGEModelSkin::SetNumTriangles(unsigned int num) {
	numTriangles = num;
}

unsigned short MGEModelSkin::GetNumStrips() {
	return numStrips;
}

void MGEModelSkin::SetNumStrips(unsigned short num) {
	numStrips = num;
}

unsigned short MGEModelSkin::GetNumBones() {
	return numBones;
}

void MGEModelSkin::SetNumBones(unsigned short num) {
	numBones = num;
}

unsigned short MGEModelSkin::GetNumWeightPerVertex() {
	return numWeightPerVertex;
}

void MGEModelSkin::SetNumWeightPerVertex(unsigned short num) {
	numWeightPerVertex = num;
}

void MGEModelSkin::SetFileLinkMtl(MGEString &fl) {
	fileLinkMtl = fl;
	if (fl.GetLength() == 0) {
		isExternalMaterial = FALSE;
	} else {
		isExternalMaterial = TRUE;
	}
}

void MGEModelSkin::SetFileLinkPhy(MGEString &fl) {
	fileLinkPhy = fl;
	if (fl.GetLength() == 0) {
		isExternalPhysical = FALSE;
	} else {
		isExternalPhysical = TRUE;
	}
}

MGEString &MGEModelSkin::GetFileLinkMtl() {
	return fileLinkMtl;
}

MGEString &MGEModelSkin::GetFileLinkPhy() {
	return fileLinkPhy;
}

BOOL8 MGEModelSkin::IsExternalMaterial() {
	return isExternalMaterial;
}

BOOL8 MGEModelSkin::IsExternalPhysical() {
	return isExternalPhysical;
}
