///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//
//		MGE Game Core
//		
//		Total Container Unit
//
///////////////////////////////////////////////////////////////////


//#include "../Renderer/GLee.h"
#undef GetClassName
#undef PostMessage
#include "string.h"
#include "stdlib.h"
//#include "../Base/Type.h"
//#include "../Base/Base.h"

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"
#include "../MGE_Base/Array.h"
#include "../MGE_Base/Array.hpp"
#include "../MGE_Base/RefArray.h"
#include "../MGE_Base/RefArray.hpp"
#include "../MGE__MathTool/MathTool.h"
#include "../MGE__MathTool/MathTool.hpp"

#include "../MGE_Thread/Thread.h"

#include "../MGE__ModelData/KeyFrame.h"
#include "../MGE__ModelData/KeyFrame.hpp"
#include "../MGE__ModelData/Sequence.h"
#include "../MGE__ModelData/Sequence.hpp"
#include "../MGE__ModelData/Bone.h"
#include "../MGE__ModelData/Bone.hpp"
#include "../MGE__ModelData/BoneController.h"
#include "../MGE__ModelData/BoneTreeNode.h"
#include "../MGE__ModelData/BoneTreeNode.hpp"
#include "../MGE__ModelData/Mesh.h"
#include "../MGE__ModelData/Mesh.hpp"
#include "../MGE__ModelData/Model.h"
#include "../MGE__ModelData/Model.hpp"
#include "../MGE__ModelData/Surface.h"
#include "../MGE__ModelData/Surface.hpp"
#include "../MGE__ModelData/DDSTexture.h"
#include "../MGE__ModelData/DDSTexture.hpp"
#include "../MGE__ModelData/Texture.h"
#include "../MGE__ModelData/Texture.hpp"
#include "../MGE__ModelData/TGATexture.h"
#include "../MGE__ModelData/TGATexture.hpp"
#include "../MGE__ModelData/ModelPack.h"
#include "../MGE__ModelData/ModelPack.hpp"
#include "../MGE__ModelData/CollisionDetectingMatrices.h"
#include "../MGE__ModelData/CollisionDetectingMatrices.hpp"
#include "../MGE__ModelData/CollisionDetectingMatricesController.h"
#include "../MGE__ModelData/CollisionDetectingMatricesController.hpp"

#include "../MGEv2__GLRenderer/GLTextureObject.hpp"
#include "../MGEv2__GLRenderer/GLMeshObject.hpp"
#include "../MGEv2__GLRenderer/GLShaderObject.hpp"

#include "Sandbox.hpp"
//#include "BaseImport.h"
//#include "MathToolImport.h"
//#include "FileImport.h"
//#include "ModelImport.h"
//#include "RendererImport.h"

MGE2Sandbox::MGE2Sandbox() {
	interval = 16.0f;
	numCycles = 1.0f;

}
MGE2Sandbox::~MGE2Sandbox() {

}
const char *MGE2Sandbox::GetClassName() {
	return "MGE2Sandbox";
}
BOOL32 MGE2Sandbox::IsInstanceof(const char* className) {
	if (strcmp("MGE2Sandbox", className)) {
		return TRUE;
	}
	return FALSE;
}

void MGE2Sandbox::LoadModelPrototype(MGEString &filepathname) {
}
void MGE2Sandbox::LoadTexture(MGEString &filepathname) {
}


void MGE2Sandbox::LoadSingleTexture(MGEString &fn, MGE2TextureObject *tar) {
	char filepathname[256];
	fn.GetStringASC(filepathname);
	MGEFile file;
	file.SetFilePathName(filepathname);
	file.SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary );
	if(!(file.Open())) {
		printf ("Texture :   Can't open inputfile [%s]\n", filepathname);
		file.Close();
		return;
	}
	MGEFileStream fio;
	fio.SetFile(&file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	MGEDDSTexture dds;
	
	printf("Texture : Begin Load : [%s]\n",filepathname);
	
	dds.Serialize(fio);
	fio.Close();
	file.Close();
	unsigned short _w = 0,_h = 0;
	unsigned char _cd = 0;
	void *_buf = NULL;
	dds.Get(_w, _h, _cd, _buf);
	if ( _cd == 4 ) {
		dds.ConvertARGBtoRGBA(TRUE);
	}
	printf("Texture : Bind : [%s]\n",filepathname);
	
	tar->SetBuffer(_buf);
	tar->SetHeight(_h);
	tar->SetWidth(_w);
	tar->TextureImage2D(_cd);//<<<===virtual
	
	printf("Texture : End Load : [%s]\n",filepathname);
	
}

void MGE2Sandbox::LoadShaderText(MGEString &fn, MGEString &shadertext) {
	char *fileName = (char *)malloc(256);
	char *_textbuf = (char *)malloc(65536);
	memset(_textbuf, 0, 65536);
	fn.GetStringASC(fileName);
    int shaderLength = 0;

	MGEFile _f;
	_f.SetFilePathName(fileName);
	_f.SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary);
	if ( _f.Open() != TRUE ) {
		_f.Close();
		printf("Shader Text : file=[%s] error\n", fileName);
		free ( fileName ) ;
		free ( _textbuf ) ;
		return;
	}

	while (!_f.IsEof()) {
		_f.Read(&_textbuf[shaderLength],1,1);
        shaderLength ++;
    }
	_textbuf[shaderLength] = 0;
	_f.Close();
	shadertext = _textbuf;
	free ( fileName ) ;
	free ( _textbuf ) ;
}

void MGE2Sandbox::LoadSingleShader(MGE2Variant &_fn, MGE2ShaderObject *tar) {
	GLenum err;
	MGEString vfilename;
	MGEString ffilename;
	MGEString vshader;
	MGEString fshader;
	GLuint uiShader;

	_fn["vertex"].Copy2String(vfilename);
	_fn["fragment"].Copy2String(ffilename);

	if ( tar->IsInstanceof("MGE2GLShaderObject") ) {
		char *sInfoLog = (char*)malloc(65536);
		sInfoLog[0] = 0;
		int iLogLength;

		MGE2GLShaderObject &_glshader = *(MGE2GLShaderObject*)tar;
		LoadShaderText(vfilename, vshader);
		LoadShaderText(ffilename, fshader);
		_glshader.SetVertexShaderText((GLchar*)vshader.GetBuffer());
		_glshader.SetFragmentShaderText((GLchar*)fshader.GetBuffer());

		_glshader.PrepareShader(&uiShader);
		err = glGetError();
		if (err != GL_NO_ERROR) {
			printf("ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
			glGetShaderInfoLog(uiShader, 1024, &iLogLength, sInfoLog);
			printf("\n===Detail:[[%s]]\n",sInfoLog);
		}

		free(sInfoLog);
	}
}

BOOL32 MGE2Sandbox::LoadShaders(MGEString &_scf, MGEString &_spcf, MGEString &_sptcf, unsigned int _renderertype) {

	if ( ( _renderertype < MGE2RendererContext::_RENDERER_OPENGLES_ ) || ( _renderertype > MGE2RendererContext::_RENDERER_VULKAN_ ) ) {
		return FALSE;//Invalid Renderer
	}

	MGEHashtable linktable;

	MGEConfig *_scfg = NULL;
	MGEConfig *_spcfg = NULL;
	MGEConfig *_sptcfg = NULL;
	MGEConfigFile _sc;
	MGEConfigFile _spc;
	MGEConfigFile _sptc;

	LoadConfigFile(_scf, _sc);
	LoadConfigFile(_spcf, _spc);
	LoadConfigFile(_sptcf, _sptc);

	MGE2Variant _vfn;

	_vfn.CreateGenericObject();

	if ( _sc.GetNames().GetLength() != _spc.GetNames().GetLength() ) {
		printf("Shaders : num of shaders \n");
		return FALSE;
	}
	if ( _spc.GetNames().GetLength() != _sptc.GetNames().GetLength() ) {
		printf("Shaders : num of shaders \n");
		return FALSE;
	}
	unsigned int _i2;
	unsigned int _l3;
	unsigned int _i3;
	unsigned int numshaderfile = _sc.GetNames().GetLength();

	MGERefArray<MGE2ShaderObject> _shaders;

	_shaders.Resize(numshaderfile);
	for ( _i2 = 0 ; _i2 < numshaderfile ; _i2 ++ ) {
		if ( _renderertype == MGE2RendererContext::_RENDERER_OPENGL_ ) {
			_shaders.Set(_i2, new MGE2GLShaderObject());
		}
	}

	if ( _renderertype == MGE2RendererContext::_RENDERER_OPENGL_ ) {
		MGE2GLShaderObject *_glshader;
		MGEString _value;
		int _ivalue = 0;
		MGERefArray<MGEString> &__namearray = _sc.GetNames();

		for ( _i2 = 0 ; _i2 < numshaderfile ; _i2 ++ ) {
			_glshader = (MGE2GLShaderObject*)&_shaders[_i2];
			_scfg = &_sc.GetValue(__namearray[_i2]);
			if ( _scfg != NULL ) {
				MGERefArray<MGEString> &__fnamearray = _scfg->GetNames();

				_l3 = __fnamearray.GetLength();

				for ( _i3 = 0 ; _i3 < _l3 ; _i3 ++ ) {
					_scfg->GetString(__fnamearray[_i3], _value);
					_vfn[__fnamearray[_i3]] = _value;
				}

				LoadSingleShader(_vfn, _glshader);
			} else {
				//error;
			}
			_spcfg = &_spc.GetValue(__namearray[_i2]);
			_sptcfg = &_sptc.GetValue(__namearray[_i2]);
			if ( ( _spcfg != NULL ) && ( _sptcfg != NULL ) ) {
				if ( _spcfg->GetNames().GetLength() != _sptcfg->GetNames().GetLength() ) {
					//error
				}
				MGERefArray<MGEString> &__pnamearray = _spcfg->GetNames();

				_l3 = __pnamearray.GetLength();

				_glshader->CreateParameters(_l3);

				for ( _i3 = 0 ; _i3 < _l3 ; _i3 ++ ) {
					_spcfg->GetString(__pnamearray[_i3], _value);
					_sptcfg->ParseInt(__pnamearray[_i3], _ivalue);
					_glshader->AddParameter(__pnamearray[_i3], (GLchar*)_value.GetBuffer(), (unsigned short)_ivalue);
				}
			} else {
				//error;
			}
			linktable.Add(__namearray[_i2], _glshader);
		}
		rendererShaderObjects += _shaders;///<=== container objects
		linktable.CopyHashtable(rendererShaderIndex);
	}
	return TRUE;
}

void MGE2Sandbox::CopyShaderIndex(MGE2FrameObject *_fo) {
	if ( _fo != NULL ) {
		MGE2FrameObject &_view = *_fo;
		unsigned int _length = _view.rendererReferences.GetLength();
		unsigned int _i1 = 0;
		for ( _i1 = 0 ; _i1 < _length ; _i1 ++ ) {
			MGEHashtable &_ht0 = _view.rendererReferences[_i1].shaderIndex;
			rendererShaderIndex.CopyHashtable(_ht0);
		}
	}
}

void MGE2Sandbox::LoadModelData(MGEString &fn, MGEModelPack &model) {
	char fileName[256];
	fn.GetStringASC(fileName);
	MGEFile *file = new MGEFile();
	file->SetFilePathName(fileName);
	file->SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary );
	file->Open();
	MGEFileStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	///MGEModelPack tobj;
	model.Serialize(fio);
	fio.Close();
	file->Close();
	delete file;
}

void MGE2Sandbox::LoadCollisionDetectingMatricesControllerData(MGEString &fn, MGEModelCollisionController *&cdmc, MGEModelPack &_tobj) {
	char fileName[256];
	fn.GetStringASC(fileName);
	MGEFile *file = new MGEFile();
	file->SetFilePathName(fileName);
	file->SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary );
	file->Open();
	MGEFileStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	_tobj.Serialize(fio);
	fio.Close();
	file->Close();
	delete file;
	if ( _tobj.GetCollisionDetectingMatricesControllers().GetLength() > 0 ) {
		cdmc = &(_tobj.GetCollisionDetectingMatricesControllers()[0]);
	} else {
		cdmc = NULL;
	}
}

void MGE2Sandbox::LoadAnimationData(MGEString &fn, MGEModelSequence *&ani) {
	char fileName[256];
	fn.GetStringASC(fileName);
	MGEFile *file = new MGEFile();
	file->SetFilePathName(fileName);
	file->SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary );
	file->Open();
	MGEFileStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	MGEModelPack tobj;
	tobj.Serialize(fio);
	fio.Close();
	file->Close();
	delete file;
	if ( tobj.GetAnimations().GetLength() > 0 ) {
		ani = &tobj.GetAnimations()[0];
	} else {
		ani = NULL;
	}
}

void MGE2Sandbox::LoadTextureController(MGEConfigFile &lfn, MGEConfigFile &mfn, MGE2RendererObject *_ro, unsigned int _renderertype) {

	if ( ( _renderertype < MGE2RendererContext::_RENDERER_OPENGLES_ ) || ( _renderertype > MGE2RendererContext::_RENDERER_VULKAN_ ) ) {
		return;//Invalid Renderer
	}

	MGEHashtable linktable;
	MGEConfig *cfg;
	MGEString filepathname("FilePathName");
	MGEString texturetype("TextureType");
	MGEString strindex("Index");
	MGEString fndest;
	int index = 0;
	unsigned int _i2 = 0;
	unsigned int numtexturefile = lfn.GetNames().GetLength();

	MGERefArray<MGE2TextureObject> _textures;

	_textures.Resize(numtexturefile);
	for ( _i2 = 0 ; _i2 < numtexturefile ; _i2 ++ ) {
		if ( _renderertype == MGE2RendererContext::_RENDERER_OPENGL_ ) {
			_textures.Set(_i2, new MGE2GLTextureObject());
		}
	}

	//tc.textures.CreateAll();
	if ( _renderertype == MGE2RendererContext::_RENDERER_OPENGL_ ) {
		MGE2GLTextureObject *_gltexture;
		for ( _i2 = 0 ; _i2 < numtexturefile ; _i2 ++ ) {
			cfg = &lfn.GetValues()[_i2];
			if ( cfg != NULL ) {
				if ( cfg->ParseInt(strindex, index) ) {
				}
				_gltexture = (MGE2GLTextureObject *)&_textures[_i2];
				_gltexture->GenTexture();
				_gltexture->SetIndex(index);
				_gltexture->SetTarget(GL_TEXTURE_2D);
				_gltexture->ActiveTexture();
				_gltexture->BindTexture();
				_gltexture->TextureParameter();
				if ( cfg->GetString(filepathname, fndest) ) {
					LoadSingleTexture(fndest, _gltexture);
				}
				if ( cfg->GetString(texturetype, _gltexture->typeName) ) {
				}
			}
			linktable.Add(lfn.GetNames()[_i2], _gltexture);
		}
		///tc.ActiveTexture0();

		MGEString tarname;
		unsigned int numparts = mfn.GetNames().GetLength();
		for (unsigned int i3 = 0 ; i3 < numparts ; i3 ++ ) {
			cfg = &mfn.GetValues()[i3];
			if ( cfg != NULL ) {
				unsigned int nl = cfg->GetNames().GetLength();
				for ( unsigned int i7 = 0 ; i7 < nl ; i7 ++ ) {
					cfg->GetString(cfg->GetNames()[i7], tarname);
					MGE2GLTextureObject *to = (MGE2GLTextureObject*)linktable.Get(tarname);
					rendererTextureIndex.Add(cfg->GetNames()[i7], to);
					if ( _ro != NULL ) {
						_ro->textureIndex.Add(cfg->GetNames()[i7], to);
					}
				}
			}
		}
		rendererTextureObjects += _textures;///<=== container objects
		if ( _ro != NULL ) {
			_ro->textures += _textures;///<=== renderer reference
		}
	}
}

void MGE2Sandbox::LoadMeshController(MGEModelData &mdl, MGEConfigFile &_mfn, MGE2RendererObject *_ro, unsigned int _renderertype) {

	if ( ( _renderertype < MGE2RendererContext::_RENDERER_OPENGLES_ ) || ( _renderertype > MGE2RendererContext::_RENDERER_VULKAN_ ) ) {
		return;//Invalid Renderer
	}

	Vector3f *bodyV = NULL;
	Vector3f *bodyN = NULL;
	Vector3f *bodyT = NULL;
	Vector3f *bodyB = NULL;
	unsigned short *bodyBone = NULL;
	float *bodyWeight = NULL;
	TexCoord2f *bodyU = NULL;
	Triangle *bodyTri = NULL;

	MGEModelMesh *bodyData = NULL;

	MGEConfig *_cfg;

	unsigned int _i2 = 0;
	unsigned int numMeshes = mdl.GetMeshes().GetLength();

	MGERefArray<MGE2MeshObject> _meshes;

	_meshes.Resize(numMeshes);
	for ( _i2 = 0 ; _i2 < numMeshes ; _i2 ++ ) {
		if ( _renderertype == MGE2RendererContext::_RENDERER_OPENGL_ ) {
			_meshes.Set(_i2, new MGE2GLMeshObject());
		}
	}

	///_meshes.CreateAll();

	if ( _renderertype == MGE2RendererContext::_RENDERER_OPENGL_ ) {

		/// System Strings (DEFAULT)
		MGEString tangent("TANGENT");
		MGEString binormal("BINORMAL");
		MGEString boneindex("BONEINDEX");
		MGEString weight("WEIGHT");
		MGEString texcoord("TEXCOORD");
		MGEString transforms("TRANSFORMS");
		MGEString modelview("MODELVIEW");
		MGEString light("LIGHT");
		MGEString halfangle("HALFANGLE");
		MGEString isparallax("ISP");
		MGEString decalmap("DECAL");
		MGEString heightmap("HEIGHT");
		MGEString normalmap("NORMAL");
		MGEString vertex("VERTEX");
		MGEString normal("NORMALVV");

		MGEString _d("_d");
		MGEString _h("_h");
		MGEString _n("_n");


		for ( unsigned int i7 = 0 ; i7 < numMeshes ; i7 ++ ) {
			bodyData = &mdl.GetMeshes()[i7];
			bodyData->BuildTangentsBinormals();
			bodyData->GetBoneMatrices().Resize(70);
			bodyU = (TexCoord2f*)(bodyData->GetUVMap().GetBuffer());
			bodyV = (Vector3f*)(bodyData->GetVertices().GetBuffer());
			bodyN = (Vector3f*)(bodyData->GetNormals().GetBuffer());
			bodyT = (Vector3f*)(bodyData->GetTangents().GetBuffer());
			bodyB = (Vector3f*)(bodyData->GetBinormals().GetBuffer());
			bodyTri = (Triangle*)(bodyData->GetTriangles().GetBuffer());

			if ( bodyData->GetSurfaces().GetLength() > 0 ) {
				MGEModelSurface *s = &(bodyData->GetSurfaces()[0]);
				bodyBone = (unsigned short*)(s->GetBoneIndices().GetBuffer());
				bodyWeight = (float*)(s->GetVertexWeights().GetBuffer());
			} else {
				bodyBone = NULL;
				bodyWeight = NULL;
			}


			//i7 = 0;
			MGE2GLMeshObject *mo = (MGE2GLMeshObject *)&_meshes[i7];

			mo->SetNumVertices(bodyData->GetNumVertices());

			mo->SetVerticesBuffer(bodyV, GL_ARRAY_BUFFER);
			mo->GenVerticesBuffer();
			mo->BindVerticesBuffer();
			mo->VerticesBufferData(GL_STATIC_DRAW);

			mo->SetNormalsBuffer(bodyN, GL_ARRAY_BUFFER);
			mo->GenNormalsBuffer();
			mo->BindNormalsBuffer();
			mo->NormalsBufferData(GL_STATIC_DRAW);

			//
			if ( bodyData->HasTangents() ) {
				mo->SetTangentsBuffer(bodyT, GL_ARRAY_BUFFER);
				mo->GenTangentsBuffer();
				mo->BindTangentsBuffer();
				mo->TangentsBufferData(GL_STATIC_DRAW);
			}

			if ( bodyData->HasBinormals() ) {
				mo->SetBinormalsBuffer(bodyB, GL_ARRAY_BUFFER);
				mo->GenBinormalsBuffer();
				mo->BindBinormalsBuffer();
				mo->BinormalsBufferData(GL_STATIC_DRAW);
			}
			//

			mo->SetTexCoordsBuffer(bodyU, GL_ARRAY_BUFFER);
			mo->GenTexCoordsBuffer();
			mo->BindTexCoordsBuffer();
			mo->TexCoordsBufferData(GL_STATIC_DRAW);

			mo->SetIndicesBuffer((unsigned short*)bodyTri, GL_ELEMENT_ARRAY_BUFFER);
			mo->SetNumIndices(bodyData->GetNumTriangles() * 3);
			mo->GenIndicesBuffer();
			mo->BindIndicesBuffer();
			mo->IndicesBufferData(GL_STATIC_DRAW);

			//
			if ( bodyData->GetSurfaces().GetLength() > 0 ) {
				mo->SetBoneIndicesBuffer(bodyBone, GL_ARRAY_BUFFER);
				mo->GenBoneIndicesBuffer();
				mo->BindBoneIndicesBuffer();
				mo->BoneIndicesBufferData(GL_STATIC_DRAW);

				mo->SetVertexWeightsBuffer(bodyWeight, GL_ARRAY_BUFFER);
				mo->GenVertexWeightsBuffer();
				mo->BindVertexWeightsBuffer();
				mo->VertexWeightsBufferData(GL_STATIC_DRAW);
			}
			//

			BOOL32 isok = rendererMeshIndex.Add(bodyData->name, mo);
			if ( _ro != NULL ) {
				_ro->meshIndex.Add(bodyData->name, mo);
			}

			/// shader link KEYs
			MGEString __key("DEFAULT");
			_cfg = &_mfn.GetValue(__key);

			if ( _cfg != NULL ) {
				MGEString _svalue;
				MGEString _key;

				_key = "binormal";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->binormalParamName = _svalue;

				_key = "boneindex";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->boneIndexParamName = _svalue;

				_key = "normal";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->normalParamName = _svalue;

				_key = "tangent";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->tangentParamName = _svalue;

				_key = "vertex";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->vertexParamName = vertex;

				_key = "texcoord";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->texCoordParamName = _svalue;

				_key = "weight";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->vertexWeightParamName = _svalue;

				_key = "transforms";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->boneMatrixParamName = _svalue;

				mo->textureNames.Resize(3);
				mo->textureNames.CreateAll();
				mo->textureNames[0] = bodyData->name + _d;
				mo->textureNames[1] = bodyData->name + _h;
				mo->textureNames[2] = bodyData->name + _n;
				////mo->lightNames.Resize(1);
				////mo->lightNames.CreateAll();
				////mo->lightNames[0] = MGEString("SIMPLELIGHT");
				_key = "shader";
				_svalue = "";
				_cfg->GetString(_key, _svalue);
				mo->shaderName = _svalue;
			} else {
				_cfg = &_mfn.GetValue(bodyData->name);

				if ( _cfg != NULL ) {
					MGEString _svalue;
					MGEString _key;

					_key = "binormal";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->binormalParamName = _svalue;

					_key = "boneindex";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->boneIndexParamName = _svalue;

					_key = "normal";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->normalParamName = _svalue;

					_key = "tangent";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->tangentParamName = _svalue;

					_key = "vertex";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->vertexParamName = vertex;

					_key = "texcoord";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->texCoordParamName = _svalue;

					_key = "weight";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->vertexWeightParamName = _svalue;

					_key = "transforms";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->boneMatrixParamName = _svalue;

					mo->textureNames.Resize(3);
					mo->textureNames.CreateAll();
					mo->textureNames[0] = bodyData->name + _d;
					mo->textureNames[1] = bodyData->name + _h;
					mo->textureNames[2] = bodyData->name + _n;
					////mo->lightNames.Resize(1);
					////mo->lightNames.CreateAll();
					////mo->lightNames[0] = MGEString("SIMPLELIGHT");
					_key = "shader";
					_svalue = "";
					_cfg->GetString(_key, _svalue);
					mo->shaderName = _svalue;
				} else {
					mo->binormalParamName = binormal;
					mo->boneIndexParamName = boneindex;
					mo->normalParamName = normal;
					mo->tangentParamName = tangent;
					mo->vertexParamName = vertex;
					mo->texCoordParamName = texcoord;
					mo->vertexWeightParamName = weight;
					mo->boneMatrixParamName = transforms;

					mo->textureNames.Resize(3);
					mo->textureNames.CreateAll();
					mo->textureNames[0] = bodyData->name + _d;
					mo->textureNames[1] = bodyData->name + _h;
					mo->textureNames[2] = bodyData->name + _n;
					////mo->lightNames.Resize(1);
					////mo->lightNames.CreateAll();
					////mo->lightNames[0] = MGEString("SIMPLELIGHT");
					mo->shaderName = MGEString("SKINNING");
				}

			}

			///
		}
		rendererMeshObjects += _meshes;///<=== container objects
		if ( _ro != NULL ) {
			_ro->meshes += _meshes;///<=== renderer reference
		}
	}
}

void MGE2Sandbox::LoadConfigFile(MGEString &fn, MGEConfigFile &cf) {
	char fileName[256];
	fn.GetStringASC(fileName);
	MGEFile fd;
	fd.SetFilePathName(fileName);
	fd.SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary);
	if ( fd.Open() != TRUE ) {
		printf (" cannot load file %s \n", fileName);
		fd.Close();
		return;
	}
	MGEFileStream fdio;
	fdio.SetFile(&fd);
	fdio.SetEndian(MGEFileStream::little_endian);
	fdio.SetLoadStore(MGEFileStream::load);
	cf.Serialize(fdio);
	fdio.Close();
	fd.Close();
}


void MGE2Sandbox::AnimationHandler() {
}
