///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _RENDERER_EXPORT

#include "string.h"
#undef GetClassName
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "GLShaderObject.hpp"

MGE2GLShaderObject::MGE2GLShaderObject() {
	currentParam = 0;
	vertexProgramText = NULL;
	fragmentProgramText = NULL;
	geometryProgramText = NULL;
	fragmentShaderIndex = 0xFFFFFFFF;
	vertexShaderIndex = 0xFFFFFFFF; 
	programIndex = 0xFFFFFFFF; 
	validated = FALSE;
	parameters.Resize(0);
}

MGE2GLShaderObject::~MGE2GLShaderObject() {
	parameters.DeleteAll();
	parameters.Resize(0);
}

const char *MGE2GLShaderObject::GetClassName() {
	return "MGE2GLShaderObject";
}

BOOL32 MGE2GLShaderObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2GLShaderObject", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}


void MGE2GLShaderObject::SetVertexShaderText(GLchar *text) {
	vertexProgramText = text;
}
void MGE2GLShaderObject::CreateVertexShader() {
	vertexShaderIndex = glCreateShader(GL_VERTEX_SHADER);
}
void MGE2GLShaderObject::VertexShaderSource() {
	glShaderSource(vertexShaderIndex, 1, (const GLchar**)&vertexProgramText, NULL);
}
void MGE2GLShaderObject::CompileVertexShader() {
	glCompileShader(vertexShaderIndex);
}
GLint MGE2GLShaderObject::GetVertexShaderStatus() {
	GLint success;
	glGetShaderiv(vertexShaderIndex, GL_COMPILE_STATUS, &success);
	return success;
}


void MGE2GLShaderObject::SetFragmentShaderText(GLchar *text) {
	fragmentProgramText = text;
}
void MGE2GLShaderObject::CreateFragmentShader() {
	fragmentShaderIndex = glCreateShader(GL_FRAGMENT_SHADER);
}
void MGE2GLShaderObject::FragmentShaderSource() {
	glShaderSource(fragmentShaderIndex, 1, (const GLchar**)&fragmentProgramText, NULL);
}
void MGE2GLShaderObject::CompileFragmentShader() {
	glCompileShader(fragmentShaderIndex);
}
GLint MGE2GLShaderObject::GetFragmentShaderStatus() {
	GLint success;
	glGetShaderiv(fragmentShaderIndex, GL_COMPILE_STATUS, &success);
	return success;
}

void MGE2GLShaderObject::DeleteProgram() {
	glDeleteProgram(programIndex);
}
void MGE2GLShaderObject::DeleteVertexShader() {
	glDeleteShader(vertexShaderIndex);
}
void MGE2GLShaderObject::DeleteFragmentShader() {
	glDeleteShader(fragmentShaderIndex);
}


void MGE2GLShaderObject::CreateProgram() {
	programIndex = glCreateProgram();
}
void MGE2GLShaderObject::AttachVertexShader() {
	glAttachShader(programIndex, vertexShaderIndex);
}
void MGE2GLShaderObject::AttachFragmentShader() {
	glAttachShader(programIndex, fragmentShaderIndex);
}
void MGE2GLShaderObject::LinkProgram() {
	glLinkProgram(programIndex);
}
GLint MGE2GLShaderObject::GetProgramStatus(GLenum pname) {
	GLint success;
	glGetProgramiv(programIndex, pname, &success);
	return success;
}
void MGE2GLShaderObject::ValidateProgram() {
	glValidateProgram(programIndex);
}


BOOL32 MGE2GLShaderObject::PrepareShader(GLuint *_erri) {

	vertexShaderIndex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderIndex, 1, (const GLchar**)&vertexProgramText, NULL);
    glCompileShader(vertexShaderIndex);
    glGetShaderiv(vertexShaderIndex, GL_COMPILE_STATUS, &vertexShaderStatus);
	if (!vertexShaderStatus) {
		if ( _erri != NULL ) {
			*_erri = vertexShaderIndex;
		}
		return FALSE;
	}

	fragmentShaderIndex = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderIndex, 1, (const GLchar**)&fragmentProgramText, NULL);
    glCompileShader(fragmentShaderIndex);
    glGetShaderiv(fragmentShaderIndex, GL_COMPILE_STATUS, &fragmentShaderStatus);
	if (!fragmentShaderStatus) {
		if ( _erri != NULL ) {
			*_erri = fragmentShaderIndex;
		}
		return FALSE;
	}

	programIndex = glCreateProgram();
	glAttachShader(programIndex, vertexShaderIndex);
	glAttachShader(programIndex, fragmentShaderIndex);

//	glBindAttribLocationARB(rShaders[0].programIndex, 0, "position");

	glLinkProgram(programIndex);
	glGetProgramiv(programIndex, GL_LINK_STATUS, &linkShaderStatus);
	if (!linkShaderStatus) {
		if ( _erri != NULL ) {
			*_erri = programIndex;
		}
		return FALSE;
	}

	validated = FALSE;
    glValidateProgram(programIndex);
 	glGetProgramiv(programIndex, GL_VALIDATE_STATUS, &validateShaderStatus);
	if (!validateShaderStatus) {
		return FALSE;
    }
	validated = TRUE;

	vertexProgramText = NULL;
	fragmentProgramText = NULL;
	return TRUE;
}

//	Deprecated
void MGE2GLShaderObject::CreateParameters(unsigned int num) {
	//parameters.Resize(num);
	//parameters.CreateAll();
}
void MGE2GLShaderObject::AddParameter(MGEString &key, GLchar *pname, unsigned short pcode) {
	unsigned int lastnum = parameters.GetLength();
	parameters.Resize(lastnum + 1);
	parameters.Create(lastnum, 1);
	parameters[lastnum].SetName(pname);
	parameters[lastnum].SetCode(pcode);
	parameters[lastnum].SetLocation(programIndex);
	paramIndices.Add(key, &parameters[lastnum]);
	//currentParam ++;
	//currentParam = currentParam % (parameters.GetLength());
}
void MGE2GLShaderObject::SetParameter(MGEString &key, GLint value) {
	MGE2GLParameter *pParam = (MGE2GLParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		MGE2GLParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case MGE2GLParameter::sp_uniform_diffuse_map :
			case MGE2GLParameter::sp_uniform_normal_map :
			case MGE2GLParameter::sp_uniform_height_map :
			case MGE2GLParameter::sp_uniform_cube_map :
				glUniform1i(param.GetLocation(), value);
				break;
			case MGE2GLParameter::sp_uniform_custom_int :
				glUniform1iv(param.GetLocation(), 1, &value);
				break;
			default :
				break;
		}
	}
}
void MGE2GLShaderObject::SetParameter(MGEString &key, MGE2Variant &value) {
	switch ( value["type"].GetUInt(NULL) ) {
		case 0:
			break;
		case MGE2Parameter::_VAR_PARAMETER_INT_ :
			{
				int _v = value["value"].GetInt(NULL);
				SetParameter(key, &_v);
			}
			break;
		case MGE2Parameter::_VAR_PARAMETER_FLOAT_ :
			{
				float _v = value["value"].GetFloat(NULL);
				SetParameter(key, &_v);
			}
			break;
		case MGE2Parameter::_VAR_PARAMETER_FVEC2_ :
			{
				TexCoord2f _v;
				MGE2Variant &_vv = value["value"];
				_v.u = _vv[(unsigned int)0].GetFloat(NULL);
				_v.v = _vv[1].GetFloat(NULL);
				SetParameter(key, &_v);
			}
			break;
		case MGE2Parameter::_VAR_PARAMETER_FVEC3_ :
			{
				Vector3f _v;
				MGE2Variant &_vv = value["value"];
				_v.x = _vv[(unsigned int)0].GetFloat(NULL);
				_v.y = _vv[1].GetFloat(NULL);
				_v.z = _vv[2].GetFloat(NULL);
				SetParameter(key, &_v);
			}
			break;
		case MGE2Parameter::_VAR_PARAMETER_FVEC4_ :
			{
				Vector4f _v;
				MGE2Variant &_vv = value["value"];
				_v.x = _vv[(unsigned int)0].GetFloat(NULL);
				_v.y = _vv[1].GetFloat(NULL);
				_v.z = _vv[2].GetFloat(NULL);
				_v.w = _vv[3].GetFloat(NULL);
				SetParameter(key, &_v);
			}
			break;
		case MGE2Parameter::_VAR_PARAMETER_FMAT2_ :
			break;
		case MGE2Parameter::_VAR_PARAMETER_FMAT3_ :
			break;
		case MGE2Parameter::_VAR_PARAMETER_FMAT4_ :
			break;
		default:
			break;
	}
}

void MGE2GLShaderObject::SetParameter(MGEString &key, void *value) {
	MGE2GLParameter *pParam = (MGE2GLParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		MGE2GLParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case MGE2GLParameter::sp_uniform_diffuse_map :
			case MGE2GLParameter::sp_uniform_normal_map :
			case MGE2GLParameter::sp_uniform_height_map :
			case MGE2GLParameter::sp_uniform_cube_map :
				{
					GLint ivalue = *(GLint*)value;
					glUniform1i(param.GetLocation(), ivalue);
				}
				break;
			case MGE2GLParameter::sp_uniform_camera_position :
			case MGE2GLParameter::sp_uniform_model_position :
				glUniform4fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_view_matrix44 :
			case MGE2GLParameter::sp_uniform_view_invmatrix44 :
			case MGE2GLParameter::sp_uniform_project_matrix44 :
			case MGE2GLParameter::sp_uniform_project_invmatrix44 :
			case MGE2GLParameter::sp_uniform_world_matrix44 :
			case MGE2GLParameter::sp_uniform_world_invmatrix44 :
			case MGE2GLParameter::sp_uniform_model_matrix44 :
			case MGE2GLParameter::sp_uniform_model_invmatrix44 :
				glUniformMatrix4fv(param.GetLocation(), 1, GL_FALSE, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_light_position :
				glUniform3fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_int :
				glUniform1iv(param.GetLocation(), 1, (GLint*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_float :
				glUniform1fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_vector2 :
				glUniform2fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_vector3 :
				glUniform3fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_vector4 :
				glUniform4fv(param.GetLocation(), 1, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_matrix22 :
				glUniformMatrix2fv(param.GetLocation(), 1, FALSE, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_matrix33 :
				glUniformMatrix3fv(param.GetLocation(), 1, FALSE, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_matrix44 :
				glUniformMatrix4fv(param.GetLocation(), 1, FALSE, (GLfloat*)value);
				break;
			default :
				break;
		}
	}
}
void MGE2GLShaderObject::SetParameter(MGEString &key, GLsizei num, GLboolean transpose, void *value) {
	MGE2GLParameter *pParam = (MGE2GLParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		MGE2GLParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case MGE2GLParameter::sp_uniform_light_positions :
				glUniform3fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_int :
				glUniform1iv(param.GetLocation(), num, (GLint*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_float :
				glUniform1fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_vector2 :
				glUniform2fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_vector3 :
				glUniform3fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_vector4 :
				glUniform4fv(param.GetLocation(), num, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_matrix22 :
				glUniformMatrix2fv(param.GetLocation(), num, transpose, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_matrix33 :
				glUniformMatrix3fv(param.GetLocation(), num, transpose, (GLfloat*)value);
				break;
			case MGE2GLParameter::sp_uniform_custom_matrix44 :
				glUniformMatrix4fv(param.GetLocation(), num, transpose, (GLfloat*)value);
				break;
			default :
				break;
		}
	}
}
void MGE2GLShaderObject::SetParameter(MGEString &key, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) {
	MGE2GLParameter *pParam = (MGE2GLParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		MGE2GLParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case MGE2GLParameter::sp_attribute_vertex :
			case MGE2GLParameter::sp_attribute_normal :
			case MGE2GLParameter::sp_attribute_tangent :
			case MGE2GLParameter::sp_attribute_binormal :
				glVertexAttribPointer(param.GetLocation(), 3, type, normalized, stride, pointer);
				break;
			case MGE2GLParameter::sp_attribute_texcoord :
				glVertexAttribPointer(param.GetLocation(), 2, type, normalized, stride, pointer);
				break;
			case MGE2GLParameter::sp_attribute_custom_int :
				glVertexAttribPointer(param.GetLocation(), 1, type, normalized, stride, pointer);
				break;
			case MGE2GLParameter::sp_attribute_custom_float :
				glVertexAttribPointer(param.GetLocation(), 1, type, normalized, stride, pointer);
				break;
			case MGE2GLParameter::sp_attribute_custom_vector2 :
				glVertexAttribPointer(param.GetLocation(), 2, type, normalized, stride, pointer);
				break;
			case MGE2GLParameter::sp_attribute_custom_vector3 :
				glVertexAttribPointer(param.GetLocation(), 3, type, normalized, stride, pointer);
				break;
			case MGE2GLParameter::sp_attribute_custom_vector4 :
				glVertexAttribPointer(param.GetLocation(), 4, type, normalized, stride, pointer);
				break;
			default :
				break;
		}
	}
}
void MGE2GLShaderObject::SetParameter(GLchar *pname, GLsizei num, float *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform1fv(location, num, (GLfloat*)value);
}
void MGE2GLShaderObject::SetParameter(GLchar *pname, GLsizei num, TexCoord2f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform2fv(location, num, (GLfloat*)value);
}
void MGE2GLShaderObject::SetParameter(GLchar *pname, GLsizei num, Vector3f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform3fv(location, num, (GLfloat*)value);
}
void MGE2GLShaderObject::SetParameter(GLchar *pname, GLsizei num, Vector4f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform4fv(location, num, (GLfloat*)value);
}
void MGE2GLShaderObject::SetParameter(GLchar *pname, GLint value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniform1i(location, value);
}
void MGE2GLShaderObject::SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix22f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniformMatrix2fv(location, num, transpose, (GLfloat*)value);
}
void MGE2GLShaderObject::SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix33f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniformMatrix3fv(location, num, transpose, (GLfloat*)value);
}
void MGE2GLShaderObject::SetParameter(GLchar *pname, GLsizei num, GLboolean transpose, Matrix44f *value) {
	GLint location = glGetUniformLocation(programIndex, pname);
	glUniformMatrix4fv(location, num, transpose, (GLfloat*)value);
}

void MGE2GLShaderObject::EnableVertexAttribArray(MGEString &key) {
	MGE2GLParameter *pParam = (MGE2GLParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		MGE2GLParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case MGE2GLParameter::sp_attribute_vertex :
			case MGE2GLParameter::sp_attribute_normal :
			case MGE2GLParameter::sp_attribute_tangent :
			case MGE2GLParameter::sp_attribute_binormal :
			case MGE2GLParameter::sp_attribute_texcoord :
			case MGE2GLParameter::sp_attribute_custom_int :
			case MGE2GLParameter::sp_attribute_custom_float :
			case MGE2GLParameter::sp_attribute_custom_vector2 :
			case MGE2GLParameter::sp_attribute_custom_vector3 :
			case MGE2GLParameter::sp_attribute_custom_vector4 :
				glEnableVertexAttribArray(param.GetLocation());
				break;
			default :
				break;
		}
	}
}
void MGE2GLShaderObject::DisableVertexAttribArray(MGEString &key) {
	MGE2GLParameter *pParam = (MGE2GLParameter*)paramIndices.Get(key);
	if ( pParam != NULL ) {
		MGE2GLParameter &param = *pParam;
		switch ( param.GetCode() ) {
			case MGE2GLParameter::sp_attribute_vertex :
			case MGE2GLParameter::sp_attribute_normal :
			case MGE2GLParameter::sp_attribute_tangent :
			case MGE2GLParameter::sp_attribute_binormal :
			case MGE2GLParameter::sp_attribute_texcoord :
			case MGE2GLParameter::sp_attribute_custom_int :
			case MGE2GLParameter::sp_attribute_custom_float :
			case MGE2GLParameter::sp_attribute_custom_vector2 :
			case MGE2GLParameter::sp_attribute_custom_vector3 :
			case MGE2GLParameter::sp_attribute_custom_vector4 :
				glDisableVertexAttribArray(param.GetLocation());
				break;
			default :
				break;
		}
	}
}



void MGE2GLShaderObject::UseProgram() {
	glUseProgram(programIndex);
}
void MGE2GLShaderObject::UnuseProgram() {
	glUseProgram(0);
}


MGERefArray<MGE2GLParameter> &MGE2GLShaderObject::GetParameters() {
	return parameters;
}
