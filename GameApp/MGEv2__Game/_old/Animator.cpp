///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _CORE_EXPORT

#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _MODEL_IMPORT
#define _THREAD_IMPORT
#define _RENDERER_IMPORT

#include "string.h"
#ifdef WIN32
#include "windows.h"
#else
#include <sys/time.h>
#endif
#undef GetClassName
#undef AddParameter

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE_Thread/Thread.h"

#include "../MGE__ModelData/Skin.h"
//#include "../MGE__ModelData/Skin.hpp"

#include "../MGE__ModelData/Sequence.h"
#include "../MGE__ModelData/Sequence.hpp"
#include "../MGE__ModelData/Model.h"
#include "../MGE__ModelData/Model.hpp"
#include "AnimationController.hpp"
#include "Animator.hpp"

//inline unsigned __int64 GetTimeStamp() {
//	_asm {
//		RDTSC;//0x0F,0x31
//	};
//}


MGEAnimator::MGEAnimator() {
	arrayRWLock.AttribInit();
	arrayRWLock.Init();
	numCycles = 1.0f;
}
MGEAnimator::~MGEAnimator() {
	arrayRWLock.Unlock();
	arrayRWLock.Destroy();
	arrayRWLock.AttribDestroy();
	controllers.Resize(0);
}

void MGEAnimator::AddController(MGEAnimationController &controller) {
	arrayRWLock.WriteLock();
	unsigned int l = controllers.GetLength() + 1;
	controllers.Resize(l);
	controllers.Set(l - 1, &controller);
	arrayRWLock.Unlock();
}

void MGEAnimator::Run() {
#ifdef WIN32
	LARGE_INTEGER fq;
	LARGE_INTEGER startc,endc;
	double dfq = 0;
#else
    timeval startCount;                         //
    timeval endCount;                           //
	double startd,endd;
#endif
	double delta = 0;
	while (TRUE) {
#ifdef WIN32
		QueryPerformanceFrequency(&fq);
		dfq = (double)fq.QuadPart;

		QueryPerformanceCounter(&startc);
#else
        gettimeofday(&startCount, NULL);
#endif
		arrayRWLock.ReadLock();
		unsigned int length = controllers.GetLength();
		for ( unsigned int i2 = 0 ; i2 < length ; i2 ++ ) {
			MGEAnimationController *ac = &controllers[i2];
			if ( ac != NULL ) {
				ac->Flush(interval * numCycles);
			}
		}
		arrayRWLock.Unlock();
		RendererHandler();
#ifdef WIN32
		QueryPerformanceCounter(&endc);
		delta = (double)(endc.QuadPart - startc.QuadPart) / dfq / 0.001;
#else
        gettimeofday(&endCount, NULL);
		startd = ((double)(startCount.tv_sec) * 1000000.0) + (double)startCount.tv_usec;
		endd = ((double)(endCount.tv_sec) * 1000000.0) + (double)endCount.tv_usec;
		delta = ( endd - startd ) / 0.001;
#endif

		if ( delta <= interval ) {
			Delay(0, (int)((interval - delta) * 1000000.0));
			numCycles = 1.0f;
		} else {
			unsigned int udelta = (unsigned int)delta;
			unsigned int uinterval = (unsigned int)interval;
			numCycles = (float)(udelta / uinterval + 1);
			Delay(0, (int)(uinterval - udelta / uinterval) * 1000000);
		}
	}
}

void MGEAnimator::RendererHandler() {
}

void MGEAnimator::AnimatorHandler() {
	arrayRWLock.ReadLock();
	unsigned int length = controllers.GetLength();
	for ( unsigned int i2 = 0 ; i2 < length ; i2 ++ ) {
		MGEAnimationController *ac = &controllers[i2];
		if ( ac != NULL ) {
			ac->Flush(interval * numCycles);
		}
	}
	arrayRWLock.Unlock();
}


const char *MGEAnimator::GetClassName() {
	return "MGEAnimator";
}
BOOL32 MGEAnimator::IsInstanceof(const char* className) {
	if (strcmp("MGEAnimator", className)) {
		return TRUE;
	}
	return FALSE;
}

