///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MESSAGEPROC_HPP_
#define _MESSAGEPROC_HPP_


#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "MessageProc.h"

extern "C" template class MGERefArray<MGE2MessageProcessor>;
extern "C" template class MGEDataArray<MGEMessage>;

#endif