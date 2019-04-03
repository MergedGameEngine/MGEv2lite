///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CORE_H_
#define _CORE_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
//#include "../MGE__MathTool/MathTool.h"
//#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE_Thread/Thread.h"

#include "../MGE__Config/Config.hpp"
#include "../MGE__Config/ConfigFile.h"

#include "MessageProc.hpp"

#include "InterfaceVShaderObject.hpp"

extern "C" class MGEGameCore : public MGE2MessageProcessor {
public:
	MGEGameCore();
	virtual ~MGEGameCore();
public:

public:
	MGEDataArray<MGEMessage> messageQueue;
	MGERWLock queueRWLock;
	unsigned int queueHead;
	unsigned int queueTail;
	unsigned int queueLength;
public:
	MGERefArray<MGE2ShaderObject> shaderController;
	MGERefArray<MGE2ShaderObject> HDRShader;
public:
	unsigned int interval;

public:
	virtual void Run();
	void PostMessage(MGEMessage &msg);
	virtual void MessageHandler(MGEMessage &msg);

public:
	void LoadConfigFile(MGEString &fn, MGEConfigFile &cf);
	void LoadShader(MGEConfigFile &cf);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};


#endif