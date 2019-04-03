///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _INTERFACE_RENDEREROBJECT_H_
#define _INTERFACE_RENDEREROBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE__MathTool/MathTool.h"
#include "InterfaceVMeshObject.hpp"
#include "InterfaceVParameter.hpp"
#include "InterfaceVShaderObject.hpp"
#include "InterfaceVTextureObject.hpp"

extern "C" class MGE2RendererObject : public MGEObject {
public:
	MGE2RendererObject();
	virtual ~MGE2RendererObject();
public:
//private:
	MGERefArray<MGE2TextureObject> textures;
	MGEHashtable textureIndex;
	MGERefArray<MGE2MeshObject> meshes;
	MGEHashtable meshIndex;
	MGERefArray<MGE2ShaderObject> shaders;
	MGEHashtable shaderIndex;
	MGERefArray<MGE2Parameter> parameters;
	MGEHashtable parameterIndex;
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
