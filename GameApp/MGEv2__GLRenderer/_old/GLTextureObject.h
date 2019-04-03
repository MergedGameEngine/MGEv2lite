///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _GLTEXTUREOBJECT_H_
#define _GLTEXTUREOBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGEv2__Game/InterfaceVTextureObject.h"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "GL/glew.h"

extern "C" class MGE2GLTextureObject : public MGE2TextureObject {
protected:
protected:
	GLuint			textureIndex;
	unsigned char	typesize;
	unsigned char	index;
	GLenum			target;
public:
	MGEString typeName;
public:
	enum {
		_wrap_uv_clamp = 0x2900,//GL_CLAMP,
		_wrap_uv_repeat = 0x2901//GL_REPEAT
	};
	enum {
		_min_filter_mipmap = 0x2703//GL_LINEAR_MIPMAP_LINEAR
	};
	enum {
		_mag_filter_linear = 0x2601//GL_LINEAR
	};
	enum {
		_mipmap_true = 0x1,//GL_TRUE,
		_mipmap_false = 0x0//GL_FALSE
	};
public:
	MGE2GLTextureObject();
	virtual ~MGE2GLTextureObject();
public:
	void SetTextureBuffer(unsigned int height, unsigned int width, unsigned char colordeepth, unsigned char typesize, const void *src);
	void SetTarget(GLenum tar);

	void GenTexture();
	void TextureParameter(GLenum pname, GLenum param);
	void TextureImage2D(GLint level, GLint internalformat, GLint border, GLenum format, GLenum type);
	void CompressedTexImage2D(GLint level, GLenum internalformat, GLint border, GLsizei imageSize);
	void ReadPixels(GLenum format, GLenum type);
	void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *buffer);
	void GenerateMipmap();
	void BindTexture();
	void ActiveTexture();

	void TextureParameter(unsigned int swarp, unsigned int twarp, unsigned int minl, unsigned int magl, unsigned int isgm);
	void TextureParameter();

	void UnbindTexture();
	void DeleteTexture();

	GLuint GetTextureIndex();

	void SetIndex(unsigned char index);
	unsigned char GetIndex();

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
