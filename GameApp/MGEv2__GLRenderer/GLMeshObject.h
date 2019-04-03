///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _GLMESHOBJECT_H_
#define _GLMESHOBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE__MathTool/MathTool.h"
#include "../MGEv2__Game/InterfaceVMeshObject.h"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "GLParameter.hpp"
#include "GL/glew.h"

//extern "C" template class MGERefArray<MGEString>;

extern "C" class MGE2GLMeshObject : public MGE2MeshObject {
protected:
protected:
	GLuint			verticesBufferIndex;
	GLuint			normalsBufferIndex;
	GLuint			tangentsBufferIndex;
	GLuint			binormalsBufferIndex;
	GLuint			texCoordsBufferIndex;
	GLuint			indicesBufferIndex;

	GLuint			boneIndicesBufferIndex;
	GLuint			vertexWeightsBufferIndex;

	GLenum			verticesTarget;
	GLenum			normalsTarget;
	GLenum			tangentsTarget;
	GLenum			binormalsTarget;
	GLenum			texCoordsTarget;
	GLenum			indicesTarget;

	GLenum			boneIndicesTarget;
	GLenum			vertexWeightsTarget;

	GLenum			drawMode;

public:
	MGE2GLMeshObject();
	virtual ~MGE2GLMeshObject();
public:
	void SetMode(GLenum mode);
	void CreateBuffers(GLenum vu, GLenum nu, GLenum tu, GLenum bu, GLenum uu, GLenum iu);

	void GenVerticesBuffer();
	void GenNormalsBuffer();
	void GenTangentsBuffer();
	void GenBinormalsBuffer();
	void GenTexCoordsBuffer();
	void GenIndicesBuffer();

	void GenBoneIndicesBuffer();
	void GenVertexWeightsBuffer();

	void BindVerticesBuffer();
	void BindNormalsBuffer();
	void BindTangentsBuffer();
	void BindBinormalsBuffer();
	void BindTexCoordsBuffer();
	void BindIndicesBuffer();

	void BindBoneIndicesBuffer();
	void BindVertexWeightsBuffer();

	void VerticesBufferData(GLenum usage);
	void NormalsBufferData(GLenum usage);
	void TangentsBufferData(GLenum usage);
	void BinormalsBufferData(GLenum usage);
	void TexCoordsBufferData(GLenum usage);
	void IndicesBufferData(GLenum usage);

	void BoneIndicesBufferData(GLenum usage);
	void VertexWeightsBufferData(GLenum usage);

	GLuint GetVerticesBufferIndex();
	GLuint GetNormalsBufferIndex();
	GLuint GetTangentsBufferIndex();
	GLuint GetBinormalsBufferIndex();
	GLuint GetTexCoordsBufferIndex();
	GLuint GetIndicesBufferIndex();

	GLuint GetBoneIndicesBufferIndex();
	GLuint GetVertexWeightsBufferIndex();

	void SetVerticesBuffer(Vector3f *vertices, GLenum target);
	void SetNormalsBuffer(Vector3f *normals, GLenum target);
	void SetTangentsBuffer(Vector3f *tangents, GLenum target);
	void SetBinormalsBuffer(Vector3f *binormals, GLenum target);
	void SetTexCoordsBuffer(TexCoord2f *texcoords, GLenum target);
	void SetBoneIndicesBuffer(unsigned short *boneindices, GLenum target);
	void SetVertexWeightsBuffer(float *vertexweights, GLenum target);
	void SetIndicesBuffer(unsigned short *indices, GLenum target);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
