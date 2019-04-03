///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _SANDBOX_H_
#define _SANDBOX_H_


#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE_File/File.h"
#include "../MGE_File/FileStream.h"


#include "../MGE__Config/Config.h"
#include "../MGE__Config/ConfigFile.h"


#include "../MGE__ModelData/Surface.h"
#include "../MGE__ModelData/Surface.hpp"
#include "../MGE__ModelData/Mesh.h"
#include "../MGE__ModelData/Mesh.hpp"
#include "../MGE__ModelData/Model.h"
#include "../MGE__ModelData/Model.hpp"
#include "../MGE__ModelData/Texture.h"
#include "../MGE__ModelData/Texture.hpp"

#include "InterfaceVFrameObject.hpp"
#include "InterfaceVRendererObject.hpp"
#include "InterfaceVRendererContext.hpp"

//#include "AnimationController.h"
#include "Core.hpp"
#include "GameObject.hpp"

extern "C" class MGE2Sandbox : public MGEObject {
public:
	MGE2Sandbox();
	virtual ~MGE2Sandbox();
public:
	unsigned short areaId;
public:

	MGEHashtable renderPrototypeIndices;
	MGEHashtable renderTextureIndices;


	MGERefArray<MGEModelSequence> animationPrototypes;
	MGEHashtable animationPrototypeIndices;
public:
//	=================================================
//	MGE v2 field
	MGERefArray<MGEModelPack> modelPacks;
	MGEHashtable modelIndex;

	MGERefArray<MGE2GameObject> gameObjects;
	MGE2Variant vParameter;

	MGEHashtable gameObjectIndex;

	MGEGameCore *refCore;
	///void *pApp;

	// === Renderer Interface
	MGERefArray<MGE2TextureObject> rendererTextureObjects;
	MGEHashtable rendererTextureIndex;
	MGERefArray<MGE2MeshObject> rendererMeshObjects;
	MGEHashtable rendererMeshIndex;///<=== Index of MGE2MeshObjectArray , not MGE2MeshObject
	MGERefArray<MGE2ShaderObject> rendererShaderObjects;
	MGEHashtable rendererShaderIndex;
	MGERefArray<MGE2Parameter> rendererParameters;
	MGEHashtable rendererParameterIndex;

	MGERefArray<MGE2Parameter> rendererObjects;
	MGEHashtable rendererIndex;

	MGERefArray<MGE2Parameter> frameObjects;
	MGEHashtable frameIndex;

	MGEHashtable animationIndex;

	// === Phyx
	MGERefArray<MGEModelCollisionController> collisionObjects;
	MGEHashtable collisionIndex;
//	=================================================
public:
	MGERWLock arrayRWLock;
	float interval;//Unit millisec
	float numCycles;

public:
	void AnimationHandler();

public:
	void LoadModelPrototype(MGEString &filepathname);
	void LoadTexture(MGEString &filepathname);

public:
	void LoadSingleTexture(MGEString &fn, MGE2TextureObject *tar);
	void LoadCollisionDetectingMatricesControllerData(MGEString &fn, MGEModelCollisionController *&cdmc, MGEModelPack &_tobj);
	void LoadModelData(MGEString &fn, MGEModelPack &model);
	void LoadAnimationData(MGEString &fn, MGEModelSequence *&ani);

	void LoadShaderText(MGEString &fn, MGEString &shadertext);
	void LoadSingleShader(MGE2Variant &fn, MGE2ShaderObject *tar);
	BOOL32 LoadShaders(MGEString &_sc, MGEString &_spc, MGEString &_sptc, unsigned int _renderertype);
	void CopyShaderIndex(MGE2FrameObject *_fo);

	// Load RendererObject
	void LoadTextureController(MGEConfigFile &lfn, MGEConfigFile &mfn, MGE2RendererObject *_ro, unsigned int _renderertype);
	void LoadMeshController(MGEModelData &mdl, MGEConfigFile &mfn, MGE2RendererObject *_ro, unsigned int _renderertype);

	void LoadConfigFile(MGEString &fn, MGEConfigFile &cf);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif