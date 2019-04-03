///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _INTERFACE_MESHOBJECT_H_
#define _INTERFACE_MESHOBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
//#include "../MGE__MathTool/MathTool.hpp"

extern "C" class MGE2MeshObject : public MGEObject {
public:
	MGE2MeshObject();
	virtual ~MGE2MeshObject();

public:
	unsigned short	numVertices;
	unsigned int	numIndices;

	Vector3f		*verticesBuffer;
	Vector3f		*normalsBuffer;
	Vector3f		*tangentsBuffer;
	Vector3f		*binormalsBuffer;
	TexCoord2f		*texCoordsBuffer;
	unsigned short	*indicesBuffer;

	unsigned short	*boneIndicesBuffer;
	float			*vertexWeightsBuffer;

	Matrix44f		*boneMatricesBuffer;
	unsigned short	numBoneMatrices;
protected:
	BOOL32	hasTangents;
	BOOL32	hasBinormals;
	BOOL32	hasWeights;
	BOOL32	hasBoneIndices;

	BOOL32	hasTransforms;
public:
	MGERefArray<MGEString> textureNames;
	MGEString shaderName;
public:
	MGEString vertexParamName;
	MGEString normalParamName;
	MGEString tangentParamName;
	MGEString binormalParamName;
	MGEString texCoordParamName;
	MGEString boneIndexParamName;
	MGEString vertexWeightParamName;

	MGEString boneMatrixParamName;

public:
	void SetNumVertices(unsigned short num);
	void SetNumIndices(unsigned int num);

	//	Deprecated
	Vector3f *GetVerticesBuffer();
	Vector3f *GetNormalsBuffer();
	Vector3f *GetTangentsBuffer();
	Vector3f *GetBinormalsBuffer();
	TexCoord2f *GetTexCoordsBuffer();
	unsigned short *GetBoneIndicesBuffer();
	float *GetVertexWeightsBuffer();
	unsigned short *GetIndicesBuffer();
	//

	Matrix44f *GetBoneMatricesBuffer();
	unsigned short GetNumBoneMatrices();

	unsigned short GetNumVertices();
	unsigned int GetNumIndices();

public:
	BOOL32	HasTangents();
	BOOL32	HasBinormals();
	BOOL32	HasWeights();
	BOOL32	HasBoneIndices();

	void	SetBoneMatrices(Matrix44f *bm, unsigned short bmsize);
	BOOL32	HasTransforms();

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
