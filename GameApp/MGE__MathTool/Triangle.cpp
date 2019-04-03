///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _MATHTOOL_EXPORT

#include "../MGE_Base/Type.h"
#include "MathTool.h"
#include "string.h"


Triangle::Triangle() {
	a = b = c = 0;
}

Triangle::Triangle(unsigned short pa, unsigned short pb, unsigned short pc) {
	a = pa;
	b = pb;
	c = pc;
}

