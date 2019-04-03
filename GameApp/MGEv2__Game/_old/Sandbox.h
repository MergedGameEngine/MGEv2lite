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


#include "../MGE__ModelData/Skin.h"
#include "../MGE__ModelData/Skin.hpp"
#include "../MGE__ModelData/Mesh.h"
#include "../MGE__ModelData/Mesh.hpp"
#include "../MGE__ModelData/Model.h"
#include "../MGE__ModelData/Model.hpp"
#include "../MGE__ModelData/Texture.h"
#include "../MGE__ModelData/Texture.hpp"

#include "InterfaceVRendererObject.hpp"
#include "InterfaceVRendererContext.hpp"

#include "AnimationController.h"
#include "Core.hpp"
#include "GameObject.hpp"

extern "C" class MGE2Sandbox : public MGEObject {
public:
	MGE2Sandbox();
	virtual ~MGE2Sandbox();
public:
	unsigned short areaId;
public:
	MGERefArray<MGEModelData> prototypes;
//	MGERefArray<TMeshController> renderPrototypes;
//	MGERefArray<TTextureController> renderTextures;
	MGEHashtable prototypeIndices;
	MGEHashtable renderPrototypeIndices;
	MGEHashtable renderTextureIndices;

//	MGERefArray<TModelController> modelControllers;

	MGERefArray<MGEModelSequence> animationPrototypes;
	MGEHashtable animationPrototypeIndices;
public:
//	=================================================
//	MGE v2 field
	MGERefArray<MGEModelPack> modelPacks;

	MGERefArray<MGE2GameObject> gameObjects;
	MGEHashtable gameObjectIndex;

	MGE2Variant vParameter;

	MGEGameCore *refCore;
	void *pApp;

	// === Renderer Interface
	MGERefArray<MGE2TextureObject> rendererTextureObjects;
	MGEHashtable rendererTextureIndex;
	MGERefArray<MGE2MeshObject> rendererMeshObjects;
	MGEHashtable rendererMeshIndex;
	MGERefArray<MGE2ShaderObject> rendererShaderObjects;
	MGEHashtable rendererShaderIndex;
	MGERefArray<MGE2Parameter> rendererParameters;
	MGEHashtable rendererParameterIndex;

//	=================================================

public:
	void LoadModelPrototype(MGEString &filepathname);
	void LoadTexture(MGEString &filepathname);

public:
	void LoadSingleTexture(MGEString &fn, MGE2TextureObject *tar);
	void LoadShaderText(MGEString &fn, char *&shadertext);
	void LoadCollisionDetectingMatricesControllerData(MGEString &fn, MGEModelCollisionController *&cdmc, MGEModelPack &_tobj);
	void LoadModelData(MGEString &fn, MGEModelPack &model);
	void LoadAnimationData(MGEString &fn, MGEModelSequence *&ani);

	// Load RendererObject
	void LoadTextureController(MGEConfigFile &lfn, MGEConfigFile &mfn, MGE2RendererObject *_ro, unsigned int _renderertype);
	void LoadMeshController(MGEModelData &mdl, MGE2RendererObject *_ro, unsigned int _renderertype);

	void LoadConfigFile(MGEString &fn, MGEConfigFile &cf);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif