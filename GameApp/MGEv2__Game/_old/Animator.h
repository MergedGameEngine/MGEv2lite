///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE__ModelData/Skin.h"
#include "../MGE__ModelData/Skin.hpp"
#include "../MGE__ModelData/Mesh.h"
#include "../MGE__ModelData/Mesh.hpp"
#include "AnimationController.h"


//#include "MGEImport.h"


extern "C" class MGEAnimator : public MGEThread {
public:
	MGEAnimator();
	virtual ~MGEAnimator();
public:
public:
	MGERWLock arrayRWLock;
	float interval;//Unit millisec
	float numCycles;
public:
public:
	MGERefArray<MGEAnimationController> controllers;
public:
public:
	void AddController(MGEAnimationController &controller);
public:
	virtual void Run();
	virtual void RendererHandler();

public:
	void AnimatorHandler();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif