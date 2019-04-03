

#ifndef _RENEREROUTPUT_H_
#define _RENEREROUTPUT_H_

#include "GL/glew.h"

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"

#include "../MGEv2__GLRenderer/GLShaderObject.hpp"
#include "../MGEv2__GLRenderer/GLFrameObject.hpp"
#include "../MGEv2__GLRenderer/GLTextureObject.hpp"

#include "../MGEv2__GLRenderer/GLRendererObject.hpp"

#include "../MGE__ModelData/Texture.hpp"
#include "../MGE__ModelData/CollisionDetectingMatricesController.hpp"

#include "../MGEv2__Game/AnimationController.hpp"
#include "../MGEv2__Game/Animator.hpp"
#include "../MGEv2__Game/Core.hpp"
#include "../MGEv2__Game/Sandbox.hpp"

#include "../MGEv2__Game/GameObject.hpp"

#include "../MGE__ModelData/DDSTexture.hpp"

void ChangeSize(GLsizei w, GLsizei h);
void ___RenderScene();
void ___DoAnimation();
void Initialization();
void Init_SC(MGE2Sandbox &sandbox);
void LoadSingleTexture(const char * filepathname, MGE2GLTextureObject &tar);
//void Init_TC(MGE2Sandbox &sandbox);
///void Init_LC(MGE2GLFrameObject &lc);
///void Init_MC(MGE2GLFrameObject &mc);
void Init_MDLC(MGE2GameObject &mdlc, MGEModelPack &mdl);
void Init_ALL();

extern bool isOneFrameFinished;
extern bool isShutDown;

class Sync : public MGEAnimationController {
public:
	Sync();
	virtual ~Sync();
public:
	virtual void Run();
	virtual void Flush(float delta);
public:
	unsigned int selector;
	unsigned int dselector;
	float dratio;
	unsigned int numKeyFrames;
	unsigned int frameCounter;
	unsigned int _actCounter;
public:
};

class ANCSync : public MGEAnimator {
public:
///	MSG		msg;
///	HWND	hWnd;
///	HDC		hDC;
///	PAINTSTRUCT ps;
public:
	ANCSync();
	virtual ~ANCSync();
public:
	virtual void RendererHandler();
};

class CoreSync : public MGEGameCore {
public:
public:
	short _x;
	short _y;
	short _dx;
	short _dy;
	float _oha;
	float _ova;
	float _dist;
	Vector3f objpos;
	Vector3f bak;
public:
	CoreSync();
	virtual ~CoreSync();
public:
	virtual void OnMouseMove(short x, short y);
	virtual void OnKeyDown(unsigned char key);
	virtual void OnMouseWheel(short zdelta);
	virtual void OnTimer(unsigned int _tid);
};

extern class Sync ac;
extern class Sync wac;
extern class ANCSync ant;
extern class CoreSync cs;
//extern class MGE2GameObject *_mdlc;

#endif