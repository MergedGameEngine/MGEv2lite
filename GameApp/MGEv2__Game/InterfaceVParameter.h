///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _INTERFACE_PARAMETER_H_
#define _INTERFACE_PARAMETER_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
//#include "../MGE__MathTool/MathTool.hpp"

extern "C" class MGE2Parameter : public MGEObject {
public:
	MGE2Parameter();
	virtual ~MGE2Parameter();
public:
//private:
	MGE2Variant vParameter;
public:
	enum {
		_VAR_PARAMETER_INT_ = 0x3020,
		_VAR_PARAMETER_FLOAT_ = 0x3021,
		_VAR_PARAMETER_FVEC2_ = 0x3022,
		_VAR_PARAMETER_FVEC3_ = 0x3023,
		_VAR_PARAMETER_FVEC4_ = 0x3024,
		_VAR_PARAMETER_FMAT2_ = 0x3042,
		_VAR_PARAMETER_FMAT3_ = 0x3043,
		_VAR_PARAMETER_FMAT4_ = 0x3044,
	};
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
