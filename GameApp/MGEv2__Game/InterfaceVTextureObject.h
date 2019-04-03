///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _INTERFACE_TEXTUREOBJECT_H_
#define _INTERFACE_TEXTUREOBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
//#include "../MGE__MathTool/MathTool.hpp"

extern "C" class MGE2TextureObject : public MGEObject {
public:
	MGE2TextureObject();
	virtual ~MGE2TextureObject();
protected:
	void			*textureBuffer;
	unsigned int	height;
	unsigned int	width;
	unsigned char	colordeepth;

public:
	void SetHeight(unsigned int height);
	void SetWidth(unsigned int width);
	void SetBuffer(void *buf);
	unsigned int GetHeight();
	unsigned int GetWidth();
	void *GetBuffer();

public:
//	=================================================
//	MGE v2 field
	virtual void TextureImage2D(unsigned char _colordeepth);

//	=================================================

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
