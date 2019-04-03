///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _RENDERER_EXPORT

#include "string.h"
//#include "GLee.h"
#undef GetClassName
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "GLMeshObject.hpp"

MGE2GLMeshObject::MGE2GLMeshObject() {
	verticesBufferIndex = 0xFFFFFFFF;
	normalsBufferIndex = 0xFFFFFFFF;
	tangentsBufferIndex = 0xFFFFFFFF;
	binormalsBufferIndex = 0xFFFFFFFF;
	texCoordsBufferIndex = 0xFFFFFFFF;
	indicesBufferIndex = 0xFFFFFFFF;

	verticesTarget = 0;
	normalsTarget = 0;
	tangentsTarget = 0;
	binormalsTarget = 0;
	texCoordsTarget = 0;
	indicesTarget = 0;

	//isVBO = TRUE;
	numVertices = 0;
	drawMode = 0;
	numIndices = 0;

	verticesBuffer = NULL;
	normalsBuffer = NULL;
	tangentsBuffer = NULL;
	binormalsBuffer = NULL;
	texCoordsBuffer = NULL;
	boneIndicesBuffer = NULL;
	vertexWeightsBuffer = NULL;
	indicesBuffer = NULL;

	hasTangents = FALSE;
	hasBinormals = FALSE;
	hasWeights = FALSE;
	hasBoneIndices = FALSE;

	hasTransforms = FALSE;
}

MGE2GLMeshObject::~MGE2GLMeshObject() {
}

const char *MGE2GLMeshObject::GetClassName() {
	return "MGE2GLMeshObject";
}

BOOL32 MGE2GLMeshObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2GLMeshObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGE2GLMeshObject::SetMode(GLenum mode) {
	drawMode = mode;
}


void MGE2GLMeshObject::CreateBuffers(GLenum vu, GLenum nu, GLenum tu, GLenum bu, GLenum uu, GLenum iu) {
	glGenBuffers(1, &verticesBufferIndex);
	glBindBuffer(verticesTarget, verticesBufferIndex);
	glBufferData(verticesTarget, numVertices * 3 * sizeof(float), verticesBuffer, vu);
	verticesBuffer = NULL;

	glGenBuffers(1, &normalsBufferIndex);
	glBindBuffer(normalsTarget, normalsBufferIndex);
	glBufferData(normalsTarget, numVertices * 3 * sizeof(float), normalsBuffer, nu);
	normalsBuffer = NULL;

	if ( tangentsBuffer != NULL ) {
		glGenBuffers(1, &tangentsBufferIndex);
		glBindBuffer(tangentsTarget, tangentsBufferIndex);
		glBufferData(tangentsTarget, numVertices * 3 * sizeof(float), tangentsBuffer, tu);
		tangentsBuffer = NULL;
		hasTangents = TRUE;
	}

	if ( binormalsBuffer != NULL ) {
		glGenBuffers(1, &binormalsBufferIndex);
		glBindBuffer(binormalsTarget, binormalsBufferIndex);
		glBufferData(binormalsTarget, numVertices * 3 * sizeof(float), binormalsBuffer, bu);
		binormalsBuffer = NULL;
		hasBinormals = TRUE;
	}

	glGenBuffers(1, &texCoordsBufferIndex);
	glBindBuffer(texCoordsTarget, texCoordsBufferIndex);
	glBufferData(texCoordsTarget, numVertices * 2 * sizeof(float), texCoordsBuffer, uu);
	texCoordsBuffer = NULL;

	glGenBuffers(1, &indicesBufferIndex);
	glBindBuffer(indicesTarget, indicesBufferIndex);
	glBufferData(indicesTarget, numIndices * sizeof(unsigned short), indicesBuffer, iu);
	indicesBuffer = NULL;
}


void MGE2GLMeshObject::GenVerticesBuffer() {
	glGenBuffers(1, &verticesBufferIndex);
}

void MGE2GLMeshObject::GenNormalsBuffer() {
	glGenBuffers(1, &normalsBufferIndex);
}

void MGE2GLMeshObject::GenTangentsBuffer() {
	glGenBuffers(1, &tangentsBufferIndex);
}

void MGE2GLMeshObject::GenBinormalsBuffer() {
	glGenBuffers(1, &binormalsBufferIndex);
}

void MGE2GLMeshObject::GenTexCoordsBuffer() {
	glGenBuffers(1, &texCoordsBufferIndex);
}

void MGE2GLMeshObject::GenIndicesBuffer() {
	glGenBuffers(1, &indicesBufferIndex);
}

void MGE2GLMeshObject::GenBoneIndicesBuffer() {
	glGenBuffers(1, &boneIndicesBufferIndex);
}
void MGE2GLMeshObject::GenVertexWeightsBuffer() {
	glGenBuffers(1, &vertexWeightsBufferIndex);
}



void MGE2GLMeshObject::BindVerticesBuffer() {
	glBindBuffer(verticesTarget, verticesBufferIndex);
}

void MGE2GLMeshObject::BindNormalsBuffer() {
	glBindBuffer(normalsTarget, normalsBufferIndex);
}

void MGE2GLMeshObject::BindTangentsBuffer() {
	glBindBuffer(tangentsTarget, tangentsBufferIndex);
}

void MGE2GLMeshObject::BindBinormalsBuffer() {
	glBindBuffer(binormalsTarget, binormalsBufferIndex);
}

void MGE2GLMeshObject::BindTexCoordsBuffer() {
	glBindBuffer(texCoordsTarget, texCoordsBufferIndex);
}

void MGE2GLMeshObject::BindIndicesBuffer() {
	glBindBuffer(indicesTarget, indicesBufferIndex);
}

void MGE2GLMeshObject::BindBoneIndicesBuffer() {
	glBindBuffer(boneIndicesTarget, boneIndicesBufferIndex);
}

void MGE2GLMeshObject::BindVertexWeightsBuffer() {
	glBindBuffer(vertexWeightsTarget, vertexWeightsBufferIndex);
}



void MGE2GLMeshObject::VerticesBufferData(GLenum usage) {
	glBufferData(verticesTarget, numVertices * 3 * sizeof(float), verticesBuffer, usage);
	verticesBuffer = NULL;
}

void MGE2GLMeshObject::NormalsBufferData(GLenum usage) {
	glBufferData(normalsTarget, numVertices * 3 * sizeof(float), normalsBuffer, usage);
	normalsBuffer = NULL;
}

void MGE2GLMeshObject::TangentsBufferData(GLenum usage) {
	if ( tangentsBuffer != NULL ) {
		glBufferData(tangentsTarget, numVertices * 3 * sizeof(float), tangentsBuffer, usage);
		tangentsBuffer = NULL;
		hasTangents = TRUE;
	}
}

void MGE2GLMeshObject::BinormalsBufferData(GLenum usage) {
	if ( binormalsBuffer != NULL ) {
		glBufferData(binormalsTarget, numVertices * 3 * sizeof(float), binormalsBuffer, usage);
		binormalsBuffer = NULL;
		hasBinormals = TRUE;
	}
}

void MGE2GLMeshObject::TexCoordsBufferData(GLenum usage) {
	glBufferData(texCoordsTarget, numVertices * 2 * sizeof(float), texCoordsBuffer, usage);
	texCoordsBuffer = NULL;
}

void MGE2GLMeshObject::IndicesBufferData(GLenum usage) {
	glBufferData(indicesTarget, numIndices * sizeof(unsigned short), indicesBuffer, usage);
	indicesBuffer = NULL;
}

void MGE2GLMeshObject::BoneIndicesBufferData(GLenum usage) {
	if ( boneIndicesBuffer != NULL ) {
		glBufferData(boneIndicesTarget, numVertices * 4 * sizeof(unsigned short), boneIndicesBuffer, usage);
		boneIndicesBuffer = NULL;
		hasBoneIndices = TRUE;
	}
}

void MGE2GLMeshObject::VertexWeightsBufferData(GLenum usage) {
	if ( vertexWeightsBuffer != NULL ) {
		glBufferData(vertexWeightsTarget, numVertices * 4 * sizeof(float), vertexWeightsBuffer, usage);
		vertexWeightsBuffer = NULL;
		hasWeights = TRUE;
	}
}

GLuint MGE2GLMeshObject::GetVerticesBufferIndex() {
	return verticesBufferIndex;
}
GLuint MGE2GLMeshObject::GetNormalsBufferIndex() {
	return normalsBufferIndex;
}
GLuint MGE2GLMeshObject::GetTangentsBufferIndex() {
	return tangentsBufferIndex;
}
GLuint MGE2GLMeshObject::GetBinormalsBufferIndex() {
	return binormalsBufferIndex;
}
GLuint MGE2GLMeshObject::GetTexCoordsBufferIndex() {
	return texCoordsBufferIndex;
}
GLuint MGE2GLMeshObject::GetIndicesBufferIndex() {
	return indicesBufferIndex;
}
GLuint MGE2GLMeshObject::GetBoneIndicesBufferIndex() {
	return boneIndicesBufferIndex;
}
GLuint MGE2GLMeshObject::GetVertexWeightsBufferIndex() {
	return vertexWeightsBufferIndex;
}


void MGE2GLMeshObject::SetVerticesBuffer(Vector3f *vertices, GLenum target) {
	verticesBuffer = vertices;
	verticesTarget = target;
}
void MGE2GLMeshObject::SetNormalsBuffer(Vector3f *normals, GLenum target) {
	normalsBuffer = normals;
	normalsTarget = target;
}
void MGE2GLMeshObject::SetTangentsBuffer(Vector3f *tangents, GLenum target) {
	tangentsBuffer = tangents;
	tangentsTarget = target;
}
void MGE2GLMeshObject::SetBinormalsBuffer(Vector3f *binormals, GLenum target) {
	binormalsBuffer = binormals;
	binormalsTarget = target;
}
void MGE2GLMeshObject::SetTexCoordsBuffer(TexCoord2f *texcoords, GLenum target) {
	texCoordsBuffer = texcoords;
	texCoordsTarget = target;
}
void MGE2GLMeshObject::SetIndicesBuffer(unsigned short *indices, GLenum target) {
	indicesBuffer = indices;
	indicesTarget = target;
}
void MGE2GLMeshObject::SetBoneIndicesBuffer(unsigned short *boneindices, GLenum target) {
	boneIndicesBuffer = boneindices;
	boneIndicesTarget = target;
}
void MGE2GLMeshObject::SetVertexWeightsBuffer(float *vertexweights, GLenum target) {
	vertexWeightsBuffer = vertexweights;
	vertexWeightsTarget = target;
}

