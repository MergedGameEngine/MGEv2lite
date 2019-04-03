///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#include "string.h"
#undef GetClassName

#include "InterfaceVMeshObject.hpp"


MGE2MeshObject::MGE2MeshObject() {
	verticesBuffer = 0;
	normalsBuffer = 0;
	tangentsBuffer = 0;
	binormalsBuffer = 0;
	texCoordsBuffer = 0;
	indicesBuffer = 0;

	boneIndicesBuffer = 0;
	vertexWeightsBuffer = 0;

	boneMatricesBuffer = 0;
}

MGE2MeshObject::~MGE2MeshObject() {
}

const char *MGE2MeshObject::GetClassName() {
	return "MGE2MeshObject";
}

BOOL32 MGE2MeshObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2MeshObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGE2MeshObject::SetNumVertices(unsigned short num) {
	numVertices = num;
}
void MGE2MeshObject::SetNumIndices(unsigned int num) {
	numIndices = num;
}
unsigned short MGE2MeshObject::GetNumVertices() {
	return numVertices;
}
unsigned int MGE2MeshObject::GetNumIndices() {
	return numIndices;
}

//	Deprecated
Vector3f *MGE2MeshObject::GetVerticesBuffer() {
	return verticesBuffer;
}
Vector3f *MGE2MeshObject::GetNormalsBuffer() {
	return normalsBuffer;
}
Vector3f *MGE2MeshObject::GetTangentsBuffer() {
	return tangentsBuffer;
}
Vector3f *MGE2MeshObject::GetBinormalsBuffer() {
	return binormalsBuffer;
}
TexCoord2f *MGE2MeshObject::GetTexCoordsBuffer() {
	return texCoordsBuffer;
}
unsigned short *MGE2MeshObject::GetIndicesBuffer() {
	return indicesBuffer;
}
unsigned short *MGE2MeshObject::GetBoneIndicesBuffer() {
	return boneIndicesBuffer;
}
float *MGE2MeshObject::GetVertexWeightsBuffer() {
	return vertexWeightsBuffer;
}
//

Matrix44f *MGE2MeshObject::GetBoneMatricesBuffer() {
	return boneMatricesBuffer;
}

BOOL32 MGE2MeshObject::HasTangents() {
	return hasTangents;
}
BOOL32 MGE2MeshObject::HasBinormals() {
	return hasBinormals;
}
BOOL32 MGE2MeshObject::HasWeights() {
	return hasWeights;
}
BOOL32 MGE2MeshObject::HasBoneIndices() {
	return hasBoneIndices;
}

void MGE2MeshObject::SetBoneMatrices(Matrix44f *bm, unsigned short bmsize) {
	if ( bm != NULL ) {
		boneMatricesBuffer = bm;
		numBoneMatrices = bmsize;
		hasTransforms = TRUE;
	} else {
		boneMatricesBuffer = NULL;
		numBoneMatrices = 0;
		hasTransforms = FALSE;
	}
}
unsigned short MGE2MeshObject::GetNumBoneMatrices() {
	return numBoneMatrices;
}
BOOL32 MGE2MeshObject::HasTransforms() {
	return hasTransforms;
}
