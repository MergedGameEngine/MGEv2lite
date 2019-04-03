///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SKIN_H_
#define _SKIN_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE__MathTool/MathTool.hpp"

extern "C" class MGEModelSkin : public MGEObject {
protected:
protected:
	unsigned short numVertices;
	unsigned int numTriangles;
	unsigned short numStrips;
	unsigned short numBones;
	unsigned short numWeightPerVertex;
	BOOL8 hasVertexMaps;
	BOOL8 hasTriangles;
	BOOL8 hasStrips;
	BOOL8 hasBones;
	BOOL8 hasVertexWeights;
	BOOL8 hasBoneIndices;
	MGEDataArray<unsigned short> vertexMap;
	MGEDataArray<Triangle> triangles;
	MGEDataArray<unsigned short> stripLengths;
	MGERefArray<TUShortArray> strips;
	MGEDataArray<unsigned short> bones;
	MGEDataArray<float> vertexWeights;
	MGEDataArray<unsigned short> boneIndices;

	BOOL8 isExternalMaterial;
	MGEString fileLinkMtl;
	BOOL8 isExternalPhysical;
	MGEString fileLinkPhy;
public:
	BOOL8 HasVertexMaps();
	BOOL8 HasTriangles();
	BOOL8 HasStrips();
	BOOL8 HasBones();
	BOOL8 HasVertexWeights();
	BOOL8 HasBoneIndices();
	MGEDataArray<unsigned short> &GetVertexMap();
	MGEDataArray<Triangle> &GetTriangles();
	MGEDataArray<unsigned short> &GetStripLengths();
	MGERefArray<TUShortArray> &GetStrips();
	MGEDataArray<unsigned short> &GetBones();
	MGEDataArray<float> &GetVertexWeights();
	MGEDataArray<unsigned short> &GetBoneIndices();

	unsigned short GetNumVertices();
	void SetNumVertices(unsigned short num);
	unsigned int GetNumTriangles();
	void SetNumTriangles(unsigned int num);
	unsigned short GetNumStrips();
	void SetNumStrips(unsigned short num);
	unsigned short GetNumBones();
	void SetNumBones(unsigned short num);
	unsigned short GetNumWeightPerVertex();
	void SetNumWeightPerVertex(unsigned short num);

	void SetFileLinkMtl(MGEString &fl);
	void SetFileLinkPhy(MGEString &fl);
	MGEString &GetFileLinkMtl();
	MGEString &GetFileLinkPhy();
	BOOL8 IsExternalMaterial();
	BOOL8 IsExternalPhysical();

public:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	MGEString name;
	MGETString _name;


public:
	MGEModelSkin();
	virtual ~MGEModelSkin();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
