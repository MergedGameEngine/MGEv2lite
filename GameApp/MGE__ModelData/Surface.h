///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE__MathTool/MathTool.hpp"

extern "C" class MGEModelSurface : public MGEObject {
protected:

	unsigned int flags;

	enum {
		_MODEL_SURFACE_CONTAIN_VERTEXMAPS_	=	0x00000001,

		_MODEL_SURFACE_CONTAIN_TRIANGLES_	=	0x00000008,

		_MODEL_SURFACE_CONTAIN_STRIPS_		=	0x00000200,

		_MODEL_SURFACE_CONTAIN_BONES_		=	0x00010000,

		_MODEL_SURFACE_CONTAIN_EXT_MAT_		=	0x00000010,

		_MODEL_SURFACE_CONTAIN_EXT_PHY_		=	0x00000020,

		_MODEL_SURFACE_CONTAIN_WEIGHTS_		=	0x00020000,
		_MODEL_SURFACE_CONTAIN_BONEINDICES_	=	0x00040000,
	};
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
	MGEModelSurface();
	virtual ~MGEModelSurface();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif
