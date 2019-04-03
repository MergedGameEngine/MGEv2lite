///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _GLSHADEROBJECT_H_
#define _GLSHADEROBJECT_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGEv2__Game/InterfaceVShaderObject.h"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "GLParameter.hpp"
#include "GL/glew.h"

extern "C" class MGE2GLShaderObject : public MGE2ShaderObject {
protected:
private:
	MGERefArray<MGE2GLParameter> parameters;
	MGEHashtable	paramIndices;
	unsigned int currentParam;
	GLchar*		vertexProgramText;
	GLchar*		fragmentProgramText;
	GLchar*		geometryProgramText;
	GLuint		fragmentShaderIndex;
	GLuint		vertexShaderIndex; 
	GLuint		programIndex; 
	GLboolean	validated;
public:
	GLint		vertexShaderStatus;
	GLint		fragmentShaderStatus;
	GLint		linkShaderStatus;
	GLint		validateShaderStatus;
public:
	MGE2GLShaderObject();
	virtual ~MGE2GLShaderObject();
public:
	void SetVertexShaderText(GLchar *text);
	void CreateVertexShader();
	void VertexShaderSource();
	void CompileVertexShader();
	GLint GetVertexShaderStatus();

	void SetFragmentShaderText(GLchar *text);
	void CreateFragmentShader();
	void FragmentShaderSource();
	void CompileFragmentShader();
	GLint GetFragmentShaderStatus();

	void CreateProgram();
	void AttachVertexShader();
	void AttachFragmentShader();
	void LinkProgram();
	GLint GetProgramStatus(GLenum pname);
	void ValidateProgram();

	BOOL32 PrepareShader(GLuint *_erri);

	void DeleteProgram();
	void DeleteVertexShader();
	void DeleteFragmentShader();

	void CreateParameters(unsigned int num);
	void AddParameter(MGEString &key, GLchar *pname, unsigned short pcode);
	void SetParameter(MGEString &key, MGE2Variant &value);
	void SetParameter(MGEString &key, GLint value);
	void SetParameter(MGEString &key, void *value);
	void SetParameter(MGEString &key, GLsizei num, GLboolean transpose, void *value);
	void SetParameter(MGEString &key, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
	void SetParameter(GLchar *pname, GLsizei num, float *value);
	void SetParameter(GLchar *pname, GLsizei num, TexCoord2f *value);
	void SetParameter(GLchar *pname, GLsizei num, Vector3f *value);
	void SetParameter(GLchar *pname, GLsizei num, Vector4f *value);
	void SetParameter(GLchar *pname, GLint value);
	void SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix22f *value);
	void SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix33f *value);
	void SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix44f *value);

	void EnableVertexAttribArray(MGEString &key);
	void DisableVertexAttribArray(MGEString &key);

	void UseProgram();
	static void UnuseProgram();

	MGERefArray<MGE2GLParameter> &GetParameters();

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
