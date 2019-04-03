

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

//#include "../MGEv2__Game/AnimationController.hpp"
//#include "../MGEv2__Game/Animator.hpp"
#include "../MGEv2__Game/Core.hpp"
#include "../MGEv2__Game/Sandbox.hpp"

#include "../MGEv2__Game/GameObject.hpp"

#include "../MGE__ModelData/DDSTexture.hpp"

void ChangeSize(GLsizei w, GLsizei h);
void ___RenderScene();
void ___SetVarParam();
void ___DoAnimation();
void Initialization();
void LoadSingleTexture(const char * filepathname, MGE2GLTextureObject &tar);


extern bool isOneFrameFinished;
extern bool isShutDown;

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

extern class CoreSync cs;


extern float __interval; 
extern float __numCycles;

extern int		windowWidth;                // window size
extern int		windowHeight;

#endif