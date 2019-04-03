///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MESH_H_
#define _MESH_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"

#include "Skin.h"
#include "Bone.h"

//extern "C" template class MGEDataArray<unsigned short>;
//typedef MGEDataArray<unsigned short> TUShortArray;
//extern "C" template class MGERefArray<TUShortArray>;
//extern "C" template class MGERefArray<MGEString>;
//extern "C" template class MGEDataArray<Triangle>;
//extern "C" template class MGEDataArray<TexCoord2f>;
//extern "C" template class MGEDataArray<Vector3f>;
//extern "C" template class MGEDataArray<Vector4f>;
//extern "C" template class MGEDataArray<Matrix22f>;
//extern "C" template class MGEDataArray<Matrix33f>;
//extern "C" template class MGEDataArray<Matrix44f>;
//extern "C" template class MGEDataArray<Matrix34f>;
//extern "C" template class MGEDataArray<Quaternion>;
//extern "C" template class MGEDataArray<Transform>;


extern "C" class MGEModelMesh : public MGEObject {
protected:
protected:
	unsigned short numVertices;
	BOOL8 hasVertices;
	BOOL8 hasNormals;
	BOOL8 hasBinormals;
	BOOL8 hasTangents;
	MGEDataArray<Vector3f> vertices;
	MGEDataArray<Vector3f> normals;
	MGEDataArray<Vector3f> binormals;
	MGEDataArray<Vector3f> tangents;
	Vector3f center;
	float radius;
	BOOL8 hasUV;
	MGEDataArray<TexCoord2f> uvMap;

	unsigned int numTriangles;
	unsigned short numStrips;
	BOOL8 hasTriangles;
	BOOL8 hasStrips;
	MGEDataArray<Triangle> triangles;
	MGEDataArray<unsigned short> stripLengths;
	MGERefArray<TUShortArray> strips;

	Vector3f translation;
	Matrix33f rotation;
	float scale;
	Vector3f boneTranslation;
	Matrix33f boneRotation;
	float boneScale;
	unsigned short numSkins;
	MGERefArray<MGEModelSkin> skins;
	unsigned short numBones;
	MGERefArray<MGEModelBone> bones;
	MGERefArray<MGEString> boneBlockIndices;
	MGEDataArray<Matrix44f> boneMatrices;

	MGERefArray<MGEModelBoneTreeNode> boneNodes;
public:
	BOOL8 HasVertices();
	BOOL8 HasNormals();
	BOOL8 HasBinormals();
	BOOL8 HasTangents();
	MGEDataArray<Vector3f> &GetVertices();
	MGEDataArray<Vector3f> &GetNormals();
	MGEDataArray<Vector3f> &GetBinormals();
	MGEDataArray<Vector3f> &GetTangents();
	Vector3f &GetCenter();
	float &GetRadius();
	BOOL8 HasUV();
	MGEDataArray<TexCoord2f> &GetUVMap();

	BOOL8 HasTriangles();
	BOOL8 HasStrips();
	MGEDataArray<Triangle> &GetTriangles();
	MGEDataArray<unsigned short> &GetStripLengths();
	MGERefArray<TUShortArray> &GetStrips();

	Vector3f &GetTranslation();
	Matrix33f &GetRotation();
	float &GetScale();
	Vector3f &GetBoneTranslation();
	Matrix33f &GetBoneRotation();
	float &GetBoneScale();
	MGERefArray<MGEModelSkin> &GetSkins();
	MGERefArray<MGEModelBone> &GetBones();
	MGERefArray<MGEString> &GetBoneBlockIndices();
	MGEDataArray<Matrix44f> &GetBoneMatrices();

	MGERefArray<MGEModelBoneTreeNode> &GetBoneNodes();

	unsigned short GetNumVertices();
	void SetNumVertices(unsigned short num);
	unsigned int GetNumTriangles();
	void SetNumTriangles(unsigned short num);
	unsigned short GetNumStrips();
	void SetNumStrips(unsigned short num);
public:
	void BuildTangentsBinormals();
	void CopyBoneBlockIndices(MGEModelMesh &tar);
public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;

public:
	MGEModelMesh();
	virtual ~MGEModelMesh();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
