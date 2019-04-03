///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////


#ifndef _GLPARAMETER_H_
#define _GLPARAMETER_H_

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGEv2__Game/InterfaceVParameter.h"
#include "../MGE__MathTool/MathTool.h"
#include "GL/glew.h"

extern "C" class MGE2GLParameter : public MGE2Parameter {
protected:
protected:
	unsigned short	parameterCode;
	char			parameterName[128];
	GLint			location;
//	GLvoid*			parameter;
public:
	MGE2GLParameter();
	virtual ~MGE2GLParameter();
public:
	enum {
		sp_attribute_vertex = 0x0001,
		sp_attribute_normal = 0x0002,
		sp_attribute_tangent = 0x0003,
		sp_attribute_binormal = 0x0004,
		sp_attribute_texcoord = 0x0005,

		sp_attribute_custom_int = 0x0020,
		sp_attribute_custom_float = 0x0021,
		sp_attribute_custom_vector2 = 0x0022,
		sp_attribute_custom_vector3 = 0x0023,
		sp_attribute_custom_vector4 = 0x0024,

		sp_uniform_diffuse_map = 0x0100,
		sp_uniform_normal_map = 0x0101,
		sp_uniform_height_map = 0x0102,

		sp_uniform_cube_map = 0x01F0,

		sp_uniform_camera_position = 0x0200,
		sp_uniform_model_position = 0x0201,
		sp_uniform_view_matrix44 = 0x0202,
		sp_uniform_view_invmatrix44 = 0x0203,
		sp_uniform_project_matrix44 = 0x0204,
		sp_uniform_project_invmatrix44 = 0x0205,
		sp_uniform_world_matrix44 = 0x0206,
		sp_uniform_world_invmatrix44 = 0x0207,
		sp_uniform_model_matrix44 = 0x0208,
		sp_uniform_model_invmatrix44 = 0x0209,

		sp_uniform_light_position = 0x0300,
		sp_uniform_light_positions = 0x0301,

		sp_uniform_custom_int = 0xF000,
		sp_uniform_custom_float = 0xF100,
		sp_uniform_custom_vector2 = 0xF200,
		sp_uniform_custom_vector3 = 0xF300,
		sp_uniform_custom_vector4 = 0xF400,
		sp_uniform_custom_matrix22 = 0xF500,
		sp_uniform_custom_matrix33 = 0xF600,
		sp_uniform_custom_matrix44 = 0xF700,

		sp_uniform_custom_unknown = 0xFFFF
	};
public:
	void SetCode(unsigned short code);
	void SetName(GLchar *name);
	void SetLocation(GLuint program);
	unsigned short GetCode();
	GLchar *GetName();
	GLint GetLocation();

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif
