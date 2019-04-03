#ifndef _TEMPMODEL_H_
#define _TEMPMODEL_H_

#include "GL/glew.h"

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"

#include "../MGEv2__GLRenderer/GLShaderObject.hpp"
#include "../MGEv2__GLRenderer/GLFrameObject.hpp"
#include "../MGEv2__GLRenderer/GLTextureObject.hpp"

#include "../MGEv2__GLRenderer/GLRendererObject.hpp"

#include "../MGE__ModelData/Texture.hpp"
#include "../MGE__ModelData/CollisionDetectingMatricesController.hpp"
#include "../MGE__ModelData/ModelPack.hpp"
#include "../MGE__ModelData/Model.hpp"

#include "../MGEv2__Game/AnimationController.hpp"
#include "../MGEv2__Game/Animator.hpp"
#include "../MGEv2__Game/Core.hpp"
#include "../MGEv2__Game/Sandbox.hpp"

#include "../MGEv2__Game/GameObject.hpp"

#include "../MGE__ModelData/DDSTexture.hpp"

extern MGERefArray<MGEModelPack> modelpacks;

GLchar *LoadShaderText(const char *fileName);
void LoadMesh(MGEModelPack &mobj);
void LoadAni1(MGEModelPack &mani);
void LoadAni2(MGEModelPack &mani);
void DoAni(MGEModelPack &_mdl, MGEAnimationController &ac, MGEAnimationController &wac);

#endif