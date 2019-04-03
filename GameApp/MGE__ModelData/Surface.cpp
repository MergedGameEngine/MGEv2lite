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
#include "Surface.hpp"

MGEModelSurface::MGEModelSurface() {
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

MGEModelSurface::~MGEModelSurface() {
	vertexMap.Resize(0);
	triangles.Resize(0);
	stripLengths.Resize(0);
	strips.DeleteAll();
	strips.Resize(0);
	bones.Resize(0);
	vertexWeights.Resize(0);
	boneIndices.Resize(0);
}

const char *MGEModelSurface::GetClassName() {
	return "MGEModelSurface";
}

BOOL32 MGEModelSurface::IsInstanceof(const char* className) {
	if (strcmp("MGEModelSurface", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelSurface::Serialize(MGEIOStream &iio) {
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
			hasVertexMaps = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasTriangles = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasStrips = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasBones = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasVertexWeights = ( _temp != 0 );
			iio.Read(&_temp, sizeof(char));
			hasBoneIndices = ( _temp != 0 );

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
			isExternalMaterial = ( _temp != 0 );
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
			isExternalPhysical = ( _temp != 0 );
			_strtemp.Load(iio);
			if ( _strtemp.GetBuffer() ) {
#ifdef WIN32
				fileLinkPhy = MGEString("%ls",_strtemp.GetBuffer());
#else
				MGEWString __wstr(_strtemp.GetBuffer());
				fileLinkPhy = MGEString("%ls",__wstr.GetBuffer());
#endif				
			}
		} else 
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000001 ) ) {

			iio.Read(&flags, sizeof(unsigned int));

			iio.Read(&numVertices, sizeof(unsigned short));
			iio.Read(&numTriangles, sizeof(unsigned int));
			iio.Read(&numStrips, sizeof(unsigned short));
			iio.Read(&numBones, sizeof(unsigned short));
			iio.Read(&numWeightPerVertex, sizeof(unsigned short));

			////iio.Read(&_temp, sizeof(char));
			////hasVertexMaps = ( _temp != 0 );
			////iio.Read(&_temp, sizeof(char));
			////hasTriangles = ( _temp != 0 );
			////iio.Read(&_temp, sizeof(char));
			////hasStrips = ( _temp != 0 );
			////iio.Read(&_temp, sizeof(char));
			////hasBones = ( _temp != 0 );
			////iio.Read(&_temp, sizeof(char));
			////hasVertexWeights = ( _temp != 0 );
			////iio.Read(&_temp, sizeof(char));
			////hasBoneIndices = ( _temp != 0 );

			if ( flags & _MODEL_SURFACE_CONTAIN_VERTEXMAPS_ ) {
				vertexMap.Resize(numVertices);
				iio.ReadBuffer(vertexMap.GetBuffer(), numVertices, sizeof(unsigned short));
			}

			if ( flags & _MODEL_SURFACE_CONTAIN_TRIANGLES_ ) {
				triangles.Resize(numTriangles);
				iio.ReadBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
			}

			if ( flags & _MODEL_SURFACE_CONTAIN_STRIPS_ ) {
				strips.Resize(numStrips);
				strips.CreateAll();
				stripLengths.Resize(numStrips);
				iio.ReadBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
				for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
					strips[i1].Resize(stripLengths[i1]);
					iio.ReadBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
				}
			}

			if ( flags & _MODEL_SURFACE_CONTAIN_BONES_ ) {
				bones.Resize(numBones);
				iio.ReadBuffer(bones.GetBuffer(), numBones, sizeof(unsigned short));
			}

			if ( flags & _MODEL_SURFACE_CONTAIN_WEIGHTS_ ) {
				vertexWeights.Resize(numVertices * numWeightPerVertex);
				iio.ReadBuffer(vertexWeights.GetBuffer(), numVertices * numWeightPerVertex, sizeof(float));
			}

			if ( flags & _MODEL_SURFACE_CONTAIN_BONEINDICES_ ) {
				boneIndices.Resize(numVertices * numWeightPerVertex);
				iio.ReadBuffer(boneIndices.GetBuffer(), numVertices * numWeightPerVertex, sizeof(unsigned short));
			}

			if ( flags & _MODEL_SURFACE_CONTAIN_EXT_MAT_ ) {
			}
			if ( flags & _MODEL_SURFACE_CONTAIN_EXT_PHY_ ) {
			}
		} else 
		{
		}
	} else {
		flags = 0;
		//version = 0x00000001;
		//subVersion = 0x00000001;

		if ((numVertices != 0) && (vertexMap.GetLength() >= numVertices)) {
			hasVertexMaps = TRUE;
			flags |= _MODEL_SURFACE_CONTAIN_VERTEXMAPS_ ;
		}
		if ((numTriangles != 0) && (triangles.GetLength() >= numTriangles)) {
			hasTriangles = TRUE;
			flags |= _MODEL_SURFACE_CONTAIN_TRIANGLES_ ;
		}
		if ((numStrips != 0) && (strips.GetLength() == numStrips)) {
			hasStrips = TRUE;
			flags |= _MODEL_SURFACE_CONTAIN_STRIPS_ ;
		}
		if ((numBones != 0) && (bones.GetLength() >= numBones)) {
			hasBones = TRUE;
			flags |= _MODEL_SURFACE_CONTAIN_BONES_ ;
		}
		if (((numVertices * numWeightPerVertex) != 0) && (vertexWeights.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex))) {
			hasVertexWeights = TRUE;
			flags |= _MODEL_SURFACE_CONTAIN_WEIGHTS_ ;
		}
		if (((numVertices * numWeightPerVertex) != 0) && (boneIndices.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex))) {
			hasBoneIndices = TRUE;
			flags |= _MODEL_SURFACE_CONTAIN_BONEINDICES_ ;
		}

		iio.Write(&numVertices, sizeof(unsigned short));
		iio.Write(&numTriangles, sizeof(unsigned int));
		iio.Write(&numStrips, sizeof(unsigned short));
		iio.Write(&numBones, sizeof(unsigned short));
		iio.Write(&numWeightPerVertex, sizeof(unsigned short));
		////iio.Write(&hasVertexMaps, sizeof(BOOL8));
		////iio.Write(&hasTriangles, sizeof(BOOL8));
		////iio.Write(&hasStrips, sizeof(BOOL8));
		////iio.Write(&hasBones, sizeof(BOOL8));
		////iio.Write(&hasVertexWeights, sizeof(BOOL8));
		////iio.Write(&hasBoneIndices, sizeof(BOOL8));
		if (flags & _MODEL_SURFACE_CONTAIN_VERTEXMAPS_) {
			iio.WriteBuffer(vertexMap.GetBuffer(), numVertices, sizeof(unsigned short));
		}
		if (flags & _MODEL_SURFACE_CONTAIN_TRIANGLES_) {
			iio.WriteBuffer(triangles.GetBuffer(), numTriangles * 3, sizeof(unsigned short));
		}
		if (flags & _MODEL_SURFACE_CONTAIN_STRIPS_) {
			iio.WriteBuffer(stripLengths.GetBuffer(), numStrips, sizeof(unsigned short));
			for (int i1 = 0 ; i1 < numStrips ; i1 ++ ) {
				iio.WriteBuffer(strips[i1].GetBuffer(), stripLengths[i1], sizeof(unsigned short));
			}
		}
		if (flags & _MODEL_SURFACE_CONTAIN_BONES_) {
			iio.WriteBuffer(bones.GetBuffer(), numBones, sizeof(unsigned short));
		}
		if (flags & _MODEL_SURFACE_CONTAIN_WEIGHTS_) {
			iio.WriteBuffer(vertexWeights.GetBuffer(), numVertices * numWeightPerVertex, sizeof(float));
		}
		if (flags & _MODEL_SURFACE_CONTAIN_BONEINDICES_) {
			iio.WriteBuffer(boneIndices.GetBuffer(), numVertices * numWeightPerVertex, sizeof(unsigned short));
		}

	}
}

BOOL8 MGEModelSurface::HasVertexMaps() {
	return hasVertexMaps = ((numVertices != 0) && (vertexMap.GetLength() >= numVertices));
}

BOOL8 MGEModelSurface::HasTriangles() {
	return hasTriangles = ((numTriangles != 0) && (triangles.GetLength() >= numTriangles));
}

BOOL8 MGEModelSurface::HasStrips() {
	return hasStrips = ((numStrips != 0) && (strips.GetLength() == numStrips));
}

BOOL8 MGEModelSurface::HasBones() {
	return hasBones = ((numBones != 0) && (bones.GetLength() >= numBones));
}

BOOL8 MGEModelSurface::HasVertexWeights() {
	return hasVertexWeights = (((numVertices * numWeightPerVertex) != 0) 
		&& (vertexWeights.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));
}

BOOL8 MGEModelSurface::HasBoneIndices() {
	return hasBoneIndices = (((numVertices * numWeightPerVertex) != 0) 
		&& (boneIndices.GetLength() >= (unsigned int)(numVertices * numWeightPerVertex)));
}

MGEDataArray<unsigned short> &MGEModelSurface::GetVertexMap() {
	return vertexMap;
}

MGEDataArray<Triangle> &MGEModelSurface::GetTriangles() {
	return triangles;
}

MGEDataArray<unsigned short> &MGEModelSurface::GetStripLengths() {
	return stripLengths;
}

MGERefArray<TUShortArray> &MGEModelSurface::GetStrips() {
	return strips;
}

MGEDataArray<unsigned short> &MGEModelSurface::GetBones() {
	return bones;
}

MGEDataArray<float> &MGEModelSurface::GetVertexWeights() {
	return vertexWeights;
}

MGEDataArray<unsigned short> &MGEModelSurface::GetBoneIndices() {
	return boneIndices;
}

unsigned short MGEModelSurface::GetNumVertices() {
	return numVertices;
}

void MGEModelSurface::SetNumVertices(unsigned short num) {
	numVertices = num;
}

unsigned int MGEModelSurface::GetNumTriangles() {
	return numTriangles;
}

void MGEModelSurface::SetNumTriangles(unsigned int num) {
	numTriangles = num;
}

unsigned short MGEModelSurface::GetNumStrips() {
	return numStrips;
}

void MGEModelSurface::SetNumStrips(unsigned short num) {
	numStrips = num;
}

unsigned short MGEModelSurface::GetNumBones() {
	return numBones;
}

void MGEModelSurface::SetNumBones(unsigned short num) {
	numBones = num;
}

unsigned short MGEModelSurface::GetNumWeightPerVertex() {
	return numWeightPerVertex;
}

void MGEModelSurface::SetNumWeightPerVertex(unsigned short num) {
	numWeightPerVertex = num;
}

void MGEModelSurface::SetFileLinkMtl(MGEString &fl) {
	fileLinkMtl = fl;
	if (fl.GetLength() == 0) {
		isExternalMaterial = FALSE;
	} else {
		isExternalMaterial = TRUE;
	}
}

void MGEModelSurface::SetFileLinkPhy(MGEString &fl) {
	fileLinkPhy = fl;
	if (fl.GetLength() == 0) {
		isExternalPhysical = FALSE;
	} else {
		isExternalPhysical = TRUE;
	}
}

MGEString &MGEModelSurface::GetFileLinkMtl() {
	return fileLinkMtl;
}

MGEString &MGEModelSurface::GetFileLinkPhy() {
	return fileLinkPhy;
}

BOOL8 MGEModelSurface::IsExternalMaterial() {
	return isExternalMaterial;
}

BOOL8 MGEModelSurface::IsExternalPhysical() {
	return isExternalPhysical;
}
