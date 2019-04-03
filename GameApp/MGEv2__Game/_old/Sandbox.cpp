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
#include "../MGE__ModelData/Skin.h"
#include "../MGE__ModelData/Skin.hpp"
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

#include "Sandbox.hpp"
//#include "BaseImport.h"
//#include "MathToolImport.h"
//#include "FileImport.h"
//#include "ModelImport.h"
//#include "RendererImport.h"

MGE2Sandbox::MGE2Sandbox() {
}
MGE2Sandbox::~MGE2Sandbox() {
	prototypes.DeleteAll();
	prototypes.Resize(0);
//	renderPrototypes.DeleteAll();
//	renderPrototypes.Resize(0);
//	renderTextures.DeleteAll();
//	renderTextures.Resize(0);

//	modelControllers.DeleteAll();
//	modelControllers.Resize(0);

	animationPrototypes.DeleteAll();
	animationPrototypes.Resize(0);

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
		printf ("  Can't open inputfile \n");
	}
	MGEFileStream fio;
	fio.SetFile(&file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	MGEDDSTexture dds;
	dds.Serialize(fio);
	unsigned short _w = 0,_h = 0;
	unsigned char _cd = 0;
	void *_buf = NULL;
	dds.Get(_w, _h, _cd, _buf);
	if ( _cd == 4 ) {
		dds.ConvertARGBtoRGBA(TRUE);
	}
	tar->SetBuffer(_buf);
	tar->SetHeight(_h);
	tar->SetWidth(_w);
	tar->TextureImage2D(_cd);//<<<===virtual
	fio.Close();
	file.Close();
}

void MGE2Sandbox::LoadShaderText(MGEString &fn, char *&shadertext) {
	char fileName[256];
	fn.GetStringASC(fileName);
    GLint shaderLength = 0;
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp != NULL)
    {
        while (fgetc(fp) != EOF)
        {
            shaderLength ++;
        }
        rewind(fp);
        shadertext = new char[shaderLength + 1];
        if (shadertext != NULL)
        {
            fread(shadertext, 1, shaderLength, fp);
        }
        shadertext[shaderLength] = '\0';
        fclose(fp);
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
	////if ( tobj.GetModels().GetLength() > 0 ) {
	////	model = tobj;
	////} else {
	////	model = NULL;
	////}
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

void MGE2Sandbox::LoadMeshController(MGEModelData &mdl, MGE2RendererObject *_ro, unsigned int _renderertype) {

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
			bodyData = &mdl.GetMeshes()[i7];//17=leg;7=stocking;14=body
			bodyData->BuildTangentsBinormals();
			bodyData->GetBoneMatrices().Resize(70);
			bodyU = (TexCoord2f*)(bodyData->GetUVMap().GetBuffer());
			bodyV = (Vector3f*)(bodyData->GetVertices().GetBuffer());
			bodyN = (Vector3f*)(bodyData->GetNormals().GetBuffer());
			bodyT = (Vector3f*)(bodyData->GetTangents().GetBuffer());
			bodyB = (Vector3f*)(bodyData->GetBinormals().GetBuffer());
			bodyTri = (Triangle*)(bodyData->GetTriangles().GetBuffer());

			if ( bodyData->GetSkins().GetLength() > 0 ) {
				MGEModelSkin *s = &(bodyData->GetSkins()[0]);
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
			if ( bodyData->GetSkins().GetLength() > 0 ) {
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
			mo->lightNames.Resize(1);
			mo->lightNames.CreateAll();
			mo->lightNames[0] = MGEString("SIMPLELIGHT");
			mo->shaderName = MGEString("SKINNING");
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
	fd.Open();
	MGEFileStream fdio;
	fdio.SetFile(&fd);
	fdio.SetEndian(MGEFileStream::little_endian);
	fdio.SetLoadStore(MGEFileStream::load);
	cf.Serialize(fdio);
	fdio.Close();
	fd.Close();
}
