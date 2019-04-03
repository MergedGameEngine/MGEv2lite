#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _CORE_IMPORT
#define _MODEL_IMPORT
#define _RENDERER_IMPORT
#define _THREAD_IMPORT
#define _DLL_IMPORT_API __declspec(dllimport)
#define _DLL_EXPORT_API __declspec(dllimport)

///#include "stdafx.h"
///#include "windows.h"
#include "string.h"
#undef GetClassName
#undef PostMessage

#include "GL/glew.h"
#include "../MGEv2__Game/AnimationController.hpp"
#include "../MGEv2__Game/InterfaceVRendererContext.hpp"
#include "../MGEv2__Game/Core.hpp"
#include "../MGEv2__Game/Sandbox.hpp"
#include "TempModel.h"
#include "RendererOutput.h"


GLint		windowWidth = 1440;                // window size
GLint		windowHeight = 900;
GLdouble	cameraZoom = 0.4;
float light_rotation = 0;


char _debug_str[256];
char sInfoLog[1024];
char sFinalMessage[1536];
int iLogLength;


Matrix44f _wmat;
Matrix44f _archmat;

///MGE2Sandbox *area = NULL;
MGE2Sandbox gameSandbox;

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


MGERefArray<MGE2GLShaderObject> gameShaders;
MGEHashtable gameShaderIndex;
////MGERefArray<MGE2GLTextureObject> gameTextures;
////MGEHashtable gameTextureIndex;


MGERefArray<MGE2GLRendererObject> gameRendererObjects;

MGE2GLFrameObject _view; 

MGE2Parameter _vlight;

MGEModelPack _mdlch;
MGEModelPack _mdlsw;
MGEModelPack _mdlar;

MGEModelPack _cmdl;
MGEModelPack _mcdm1;
MGEModelPack _mcdm2;
MGEModelCollisionController *_cdm1;
MGEModelCollisionController *_cdm2;

bool isOneFrameFinished = true;
bool isShutDown = false;

Sync::Sync() {
	selector = 0;dselector = 0;dratio = 0.0f;
	frameCounter = 0;
	_actCounter = 0;
};
Sync::~Sync() {

};
void Sync::Run() {
	while (TRUE) {
		if ( currentime > 1.66f ) {
			currentime = 0.0f;
			count ++;
		} else {
			currentime = currentime + 0.01f;
		}
		rwLock.WriteLock();
		animations[0].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), currentime);
		boneController.GetBoneController().GetBoneRoot().GetTransform() = Transform();
		boneController.GetBoneController().DoAnimation();
		rwLock.Unlock();
		if ( !isOneFrameFinished ) {
			isOneFrameFinished = true;
		} else {
			while (isOneFrameFinished) {
				Delay(0, 1000);
			}
		}
	}
}

void Sync::Flush(float delta) {
	//if ( _actCounter < 10 ) {
	//	_actCounter ++;
	//	return;
	//} else {
	//	_actCounter = 0;
	//}
	if ( selector == dselector ) {
		if ( &animations[selector] != NULL ) {
			numKeyFrames = animations[selector].GetKeyFrames().GetLength();
		} else {
			numKeyFrames = 0;
		}
		if ( parentController == NULL ) {
			if ( currentime > animations[selector].GetStopTime() - 0.01 ) {
				currentime = 0.0f;
				count ++;
			} else {
				currentime = currentime + delta / 1000.0f;
			}
			if ( frameCounter < numKeyFrames ) {
				frameCounter ++ ;
			} else {
				frameCounter = 0;
			}

		}
		rwLock.WriteLock();

		if ( parentController != NULL ) {

			parentController->boneController.GetBoneController().CopyBoneTransform(boneController.GetBoneController().GetBoneRoot());
			boneController.GetBoneController().DoAnimation();

		} else {
			// animation[time]
			animations[selector].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), currentime);
			// animation[frameCounter]
			////animations[selector].LoadAnimationMatrix(boneController.GetBoneController().GetBoneRoot(), frameCounter);

			if ( innerstate != 0 ) {
				if ( innerstate == 1 ) {
					Velocity(0.1f);
				} else if ( innerstate == 2 ) {
					Velocity(-0.1f);
				} else {
					Velocity(0.0f);
				}
				innerstate = 0;
			}
			if ( _cdm1->IsCollision(position, position) ) {
				//Gravity(0.0f);
				Commit();
				//if ( innerstate == 1 ) {
				//	Velocity(0.1f);
				//}
				//if ( innerstate == 2 ) {
				//	Velocity(-0.1f);
				//}
				//Commit();
			} else {
				Commit();
				Gravity(0.001f);
			}
			if ( innerstate != 0 ) {
				innerstate = 0;
			}
			Vector3f spos = positionCurrent / 0.015f;
			Transform rt(spos, direction, 1.0f);
			boneController.GetBoneController().GetBoneRoot().GetTransform() = rt;
			boneController.GetBoneController().DoAnimation();
		}
		rwLock.Unlock();
	} else {
		if ( parentController == NULL ) {
			if ( dratio > 1.0f ) {
				selector = dselector;
				currentime = 0.0f;
			} else {
				dratio = dratio + delta / 1000.0f;
			}
		}
		rwLock.WriteLock();
		//TBoneTreeNode *weapon = (TBoneTreeNode*)boneController.GetBoneController().GetBoneHashtable().Get(TString("Weapon"));
		//if ( weapon != NULL ) {
		//	weapon->GetInvertedTransform() = Transform();
		//}
		if ( parentController != NULL ) {
		//	_wmat = Matrix44f(weapon->GetFastTransform().translation, weapon->GetFastTransform().rotation);
			parentController->boneController.GetBoneController().CopyBoneTransform(boneController.GetBoneController().GetBoneRoot());
			boneController.GetBoneController().DoAnimation();
		} else {
			animations[selector].BuildTemporaryAnimation(currentime);
			animations[selector].LoadAnimationMatrix(animations[dselector], boneController.GetBoneController().GetBoneRoot(), dratio);
			if ( innerstate != 0 ) {
				if ( innerstate == 1 ) {
					Velocity(0.1f);
				} else if ( innerstate == 2 ) {
					Velocity(-0.1f);
				} else {
					Velocity(0.0f);
				}
				innerstate = 0;
			}
			if ( _cdm1->IsCollision(position, position) ) {
				//Gravity(0.0f);
				Commit();
				//if ( innerstate == 1 ) {
				//	Velocity(0.1f);
				//}
				//if ( innerstate == 2 ) {
				//	Velocity(-0.1f);
				//}
				//Commit();
			} else {
				Commit();
				Gravity(0.001f);
			}
			if ( innerstate != 0 ) {
				innerstate = 0;
			}
			Vector3f spos = positionCurrent / 0.015f;
			Transform rt(spos, direction, 1.0f);
			boneController.GetBoneController().GetBoneRoot().GetTransform() = rt;
			boneController.GetBoneController().DoAnimation();
		}
		//if ( weapon != NULL ) {
		//	_wmat = Matrix44f(weapon->GetFastTransform().translation, weapon->GetFastTransform().rotation);
		//}
		rwLock.Unlock();
	}
}
Sync ac;
Sync wac;

ANCSync::ANCSync() {};
ANCSync::~ANCSync() {};
void ANCSync::RendererHandler() {
	if ( !isOneFrameFinished ) {
		isOneFrameFinished = true;
	} else {
		while (isOneFrameFinished) {
			Delay(0, 1000);
		}
	}
}

ANCSync ant;

CoreSync::CoreSync() {_x = 0; _y = 0; _dx = 0; _dy = 0; _oha = 0.0f; _ova = 0.0f; _dist = 5.0f; objpos = Vector3f();};
CoreSync::~CoreSync() {};
void CoreSync::OnMouseMove(short x, short y) {
	_dx = x - _x; _x = x;
	_dy = y - _y; _y = y;
	float _ha = - _dx / 360.0f;
	float _va = _dy / 360.0f;
	_oha += _ha;
	_ova += _va;
	float _distance = 1.0f;
	Vector3f cam(10.0f, 0.0f, 0.0f);

//	view.CameraCentered(Vector3f(10.0f, 0.0f, 0.0f) , _dist, _oha, _ova);
	//view->ObjectCentered(objpos, _dist, _oha, _ova);
	_view.ObjectCentered(ac.positionCurrent, _dist, _oha, _ova);
	_view.GenViewCoordinate();
}
void CoreSync::OnKeyDown(unsigned char key) {
	switch(key) {
		case 'W':
			{
				//bak = objpos;
				//bak.x += 0.1f;
				ac.innerstate = 1;
				//if ( _cdm1->IsCollision(ac->position, Vector3f()) ) {
				//} else {
				//	ac->Commit();
				//}
			}
			break;
		case 'S':
			{
				//bak = objpos;
				//bak.x -= 0.1f;
				ac.innerstate = 2;
				//if ( _cdm1->IsCollision(ac->position, Vector3f()) ) {
				//} else {
				//	ac->Commit();
				//}
			}
			break;
		case 'A':
			{
				//bak = objpos;
				//bak.y += 0.1f;
				ac.RotationAxisZ(0.05f);
				//if ( _cdm1->IsCollision(bak, Vector3f()) ) {
				//} else {
				//	objpos = bak;
				//}
			}
			break;
		case 'D':
			{
				//bak = objpos;
				//bak.y -= 0.1f;
				ac.RotationAxisZ(-0.05f);
				//if ( _cdm1->IsCollision(bak, Vector3f()) ) {
				//} else {
				//	objpos = bak;
				//}
			}
			break;
		case 'C':
			{
				//bak = objpos;
				//bak.z += 0.1f;
				Vector3f _v0;
				if ( _cdm1->IsCollision(bak, _v0) ) {
				} else {
					objpos = bak;
				}
			}
			break;
		case 'Z':
			{
				//bak = objpos;
				//bak.z -= 0.1f;
				Vector3f _v0;
				if ( _cdm1->IsCollision(bak, _v0) ) {
				} else {
					objpos = bak;
				}
			}
			break;
		case '1':
			{
				ac.dselector = 0;
				ac.dratio = 0.0f;
			}
			break;
		case '2':
			{
				ac.dselector = 1;
				ac.dratio = 0.0f;
			}
			break;
		case '3':
			{
				ac.dselector = 2;
				ac.dratio = 0.0f;
			}
			break;
		case '4':
			{
				ac.dselector = 3;
				ac.dratio = 0.0f;
			}
			break;
		case '5':
			{
				ac.dselector = 4;
				ac.dratio = 0.0f;
			}
			break;
		case '6':
			{
				ac.dselector = 5;
				ac.dratio = 0.0f;
			}
			break;
		default:
			break;
	}
	_view.ObjectCentered(ac.positionCurrent, _dist, _oha, _ova);
	_view.GenViewCoordinate();
}
void CoreSync::OnMouseWheel(short zdelta) {
	_dist += zdelta * 0.005f;
//	view.CameraCentered(Vector3f(10.0f, 0.0f, 0.0f) , _dist, _oha, _ova);
	_view.ObjectCentered(ac.positionCurrent, _dist, _oha, _ova);
	_view.GenViewCoordinate();
}
void CoreSync::OnTimer(unsigned int _tid) {
}

CoreSync cs;

void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat nRange = 100.0f;
	GLfloat fAspect;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	fAspect = (GLfloat)w/(GLfloat)h;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	// Reset coordinate system
	glLoadIdentity();

	// Setup perspective for viewing
	gluPerspective(17.5f,fAspect,1,300);

	// Viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ___DoAnimation() {
	ant.AnimatorHandler();
}

void ___RenderScene() {
	//if (!isOneFrameFinished) {
	//	return;
	//}
//	ac.Run();
//	GLenum err;
	Vector3f l(1.0f , 1.0f , -1.0f);

	l = l.Normalized();
	//quaternionf q(vec3f(0,0,1), light_rotation);
	//q.mult_vec(*(vec3f*)&l); 
	Vector3f eye(0.0f , 0.0f , 1.0f);
	Vector3f h = l + eye;
	h = h.Normalized();

	//////TLightObject *lo = &_lc->lights[0];
	//////lo->direction = l;
	//////lo->halfAngle = h;
	_vlight.vParameter["params"][_0]["value"][_0] = l.x;
	_vlight.vParameter["params"][_0]["value"][1] = l.y;
	_vlight.vParameter["params"][_0]["value"][2] = l.z;
	_vlight.vParameter["params"][1]["value"][_0] = h.x;
	_vlight.vParameter["params"][1]["value"][1] = h.y;
	_vlight.vParameter["params"][1]["value"][2] = h.z;

	// set vertex program inputs

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (windowWidth > windowHeight)	{
		GLdouble ar = (GLdouble)windowWidth / (GLdouble)windowHeight;
		glFrustum(-ar * cameraZoom, ar * cameraZoom, -cameraZoom, cameraZoom, 1.0, 1000.0);
	} else {
		GLdouble ar = (GLdouble)windowHeight / (GLdouble)windowWidth;
		glFrustum(-cameraZoom, cameraZoom, -ar * cameraZoom, ar * cameraZoom, 1.0, 1000.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(0.0f , 0.0f , -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	_view.LookAt();


	ac.rwLock.ReadLock();
	gameSandbox.gameObjects[0].numBoneMatrices = 70;
	gameSandbox.gameObjects[0].LinkBoneMatrices();
	ac.rwLock.Unlock();
	wac.rwLock.ReadLock();
	gameSandbox.gameObjects[1].numBoneMatrices = 1;
	gameSandbox.gameObjects[1].LinkBoneMatrices();
	wac.rwLock.Unlock();

	Matrix44f mat;
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&mat);
//	view->invertModelView = mat.Inverse();

	gameRendererObjects[2].RenderUnit();
	gameRendererObjects[0].RenderUnit();
	gameRendererObjects[1].RenderUnit();

	
//	glFlush();
	//isOneFrameFinished = false;
}

void Initialization() {
}

void Init_SC(MGE2Sandbox &sandbox) {
	GLenum err;
	char *vfilename;
	char *ffilename;
	GLuint uiShader;

	MGEString _stri;

	vfilename = "./shaders/skinning.vs";
	ffilename = "./shaders/skinning.fs";

	gameShaders.Resize(3);
	gameShaders.CreateAll();

	sandbox.rendererShaderObjects.Resize(3);

	sandbox.rendererShaderObjects.Set(0, &gameShaders[0]);

	gameShaders[0].SetVertexShaderText(LoadShaderText(vfilename));
	gameShaders[0].SetFragmentShaderText(LoadShaderText(ffilename));

	gameShaders[0].PrepareShader(&uiShader);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		sprintf(_debug_str, "ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
		glGetShaderInfoLog(uiShader, 1024, &iLogLength, sInfoLog);
	}

	gameShaders[0].CreateParameters(15);

	gameShaders[0].AddParameter(tangent, "tangent", MGE2GLParameter::sp_attribute_tangent);
	gameShaders[0].AddParameter(binormal, "binormal", MGE2GLParameter::sp_attribute_binormal);
	gameShaders[0].AddParameter(boneindex, "boneindex", MGE2GLParameter::sp_attribute_custom_vector4);
	gameShaders[0].AddParameter(weight, "weight", MGE2GLParameter::sp_attribute_custom_vector4);
	gameShaders[0].AddParameter(texcoord, "texcoord", MGE2GLParameter::sp_attribute_texcoord);
	gameShaders[0].AddParameter(transforms, "transforms", MGE2GLParameter::sp_uniform_custom_matrix44);
	gameShaders[0].AddParameter(modelview, "modelViewI", MGE2GLParameter::sp_uniform_model_matrix44);
	gameShaders[0].AddParameter(light, "light", MGE2GLParameter::sp_uniform_light_position);
	gameShaders[0].AddParameter(halfangle, "halfAngle", MGE2GLParameter::sp_uniform_custom_vector3);
	gameShaders[0].AddParameter(isparallax, "parallaxMapping", MGE2GLParameter::sp_uniform_custom_int);
	gameShaders[0].AddParameter(decalmap, "decalMap", MGE2GLParameter::sp_uniform_diffuse_map);
	gameShaders[0].AddParameter(heightmap, "heightMap", MGE2GLParameter::sp_uniform_height_map);
	gameShaders[0].AddParameter(normalmap, "normalMap", MGE2GLParameter::sp_uniform_normal_map);
	gameShaders[0].AddParameter(vertex, "vertexAttrib", MGE2GLParameter::sp_attribute_vertex);
	gameShaders[0].AddParameter(normal, "normalAttrib", MGE2GLParameter::sp_attribute_normal);

	_stri = "SKINNING";
	gameShaderIndex.Add(_stri, &gameShaders[0]);

	sandbox.rendererShaderIndex.Add(_stri, &gameShaders[0]);

	vfilename = "./shaders/norm.vs";
	ffilename = "./shaders/norm.fs";

	sandbox.rendererShaderObjects.Set(1, &gameShaders[1]);

	gameShaders[1].SetVertexShaderText(LoadShaderText(vfilename));
	gameShaders[1].SetFragmentShaderText(LoadShaderText(ffilename));

	gameShaders[1].PrepareShader(&uiShader);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		sprintf(_debug_str, "ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
		glGetShaderInfoLog(uiShader, 1024, &iLogLength, sInfoLog);
	}

	gameShaders[1].CreateParameters(15);

	gameShaders[1].AddParameter(tangent, "tangent", MGE2GLParameter::sp_attribute_tangent);
	gameShaders[1].AddParameter(binormal, "binormal", MGE2GLParameter::sp_attribute_binormal);
	gameShaders[1].AddParameter(boneindex, "boneindex", MGE2GLParameter::sp_attribute_custom_vector4);
	gameShaders[1].AddParameter(weight, "weight", MGE2GLParameter::sp_attribute_custom_vector4);
	gameShaders[1].AddParameter(texcoord, "texcoord", MGE2GLParameter::sp_attribute_texcoord);
	gameShaders[1].AddParameter(transforms, "transforms", MGE2GLParameter::sp_uniform_custom_matrix44);
	gameShaders[1].AddParameter(modelview, "modelViewI", MGE2GLParameter::sp_uniform_model_matrix44);
	gameShaders[1].AddParameter(light, "light", MGE2GLParameter::sp_uniform_light_position);
	gameShaders[1].AddParameter(halfangle, "halfAngle", MGE2GLParameter::sp_uniform_custom_vector3);
	gameShaders[1].AddParameter(isparallax, "parallaxMapping", MGE2GLParameter::sp_uniform_custom_int);
	gameShaders[1].AddParameter(decalmap, "decalMap", MGE2GLParameter::sp_uniform_diffuse_map);
	gameShaders[1].AddParameter(heightmap, "heightMap", MGE2GLParameter::sp_uniform_height_map);
	gameShaders[1].AddParameter(normalmap, "normalMap", MGE2GLParameter::sp_uniform_normal_map);
	gameShaders[1].AddParameter(vertex, "vertexAttrib", MGE2GLParameter::sp_attribute_vertex);
	gameShaders[1].AddParameter(normal, "normalAttrib", MGE2GLParameter::sp_attribute_normal);

	_stri = "NORM";
	gameShaderIndex.Add(_stri, &gameShaders[1]);

	sandbox.rendererShaderIndex.Add(_stri, &gameShaders[1]);

	vfilename = "./shaders/stransform.vs";
	ffilename = "./shaders/stransform.fs";

	sandbox.rendererShaderObjects.Set(2, &gameShaders[2]);

	gameShaders[2].SetVertexShaderText(LoadShaderText(vfilename));
	gameShaders[2].SetFragmentShaderText(LoadShaderText(ffilename));

	gameShaders[2].PrepareShader(&uiShader);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		sprintf(_debug_str, "ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
		glGetShaderInfoLog(uiShader, 1024, &iLogLength, sInfoLog);
		
	}

	gameShaders[2].CreateParameters(15);

	gameShaders[2].AddParameter(tangent, "tangent", MGE2GLParameter::sp_attribute_tangent);
	gameShaders[2].AddParameter(binormal, "binormal", MGE2GLParameter::sp_attribute_binormal);
	gameShaders[2].AddParameter(boneindex, "boneindex", MGE2GLParameter::sp_attribute_custom_vector4);
	gameShaders[2].AddParameter(weight, "weight", MGE2GLParameter::sp_attribute_custom_vector4);
	gameShaders[2].AddParameter(texcoord, "texcoord", MGE2GLParameter::sp_attribute_texcoord);
	gameShaders[2].AddParameter(transforms, "transform", MGE2GLParameter::sp_uniform_custom_matrix44);
	gameShaders[2].AddParameter(modelview, "modelViewI", MGE2GLParameter::sp_uniform_model_matrix44);
	gameShaders[2].AddParameter(light, "light", MGE2GLParameter::sp_uniform_light_position);
	gameShaders[2].AddParameter(halfangle, "halfAngle", MGE2GLParameter::sp_uniform_custom_vector3);
	gameShaders[2].AddParameter(isparallax, "parallaxMapping", MGE2GLParameter::sp_uniform_custom_int);
	gameShaders[2].AddParameter(decalmap, "decalMap", MGE2GLParameter::sp_uniform_diffuse_map);
	gameShaders[2].AddParameter(heightmap, "heightMap", MGE2GLParameter::sp_uniform_height_map);
	gameShaders[2].AddParameter(normalmap, "normalMap", MGE2GLParameter::sp_uniform_normal_map);
	gameShaders[2].AddParameter(vertex, "vertexAttrib", MGE2GLParameter::sp_attribute_vertex);
	gameShaders[2].AddParameter(normal, "normalAttrib", MGE2GLParameter::sp_attribute_normal);

	_stri = "STRANS";
	gameShaderIndex.Add(_stri, &gameShaders[2]);

	sandbox.rendererShaderIndex.Add(_stri, &gameShaders[2]);


}

void Init_ALL() {

	GLenum err;
	printf("Hardware Skinning ZNW\n\n");

	err = glGetError();
	if (err != GL_NO_ERROR) {
		sprintf(_debug_str, "ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
	}

	Init_SC(gameSandbox);

	err = glGetError();
	if (err != GL_NO_ERROR) {
		sprintf(_debug_str, "ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
	}

															//	glDepthMask(FALSE);
															//	glDisable(GL_LIGHTING);
	glClearColor(0.2f, 0.8f, 0.2f, 0.0f);
	glAlphaFunc(GL_GREATER, 0.1f);   
	glEnable(GL_ALPHA_TEST);   
	glEnable(GL_DEPTH_TEST);
															//GL_TEXTURE_RECTANGLE_NV
															//GL_REGISTER_COMBINERS_NV
	glEnable(GL_BLEND);
															//glDisable(GL_DEPTH_TEST);
															//	4. set additive blending
															//glColor4f(1.0f,1.0f,1.0f,0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
															//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	MGEString __str;

	_vlight.vParameter.CreateHashtable();
	_vlight.vParameter["numparam"] = (unsigned int)2;
	_vlight.vParameter["params"].CreateArray();
	_vlight.vParameter["params"][_0].CreateHashtable();
	_vlight.vParameter["params"][_0]["key"] = light;
	_vlight.vParameter["params"][_0]["type"] = (unsigned int)MGE2Parameter::_VAR_PARAMETER_FVEC3_;
	_vlight.vParameter["params"][_0]["value"].CreateArray();
	_vlight.vParameter["params"][_0]["value"][_0] = 0.0f;
	_vlight.vParameter["params"][_0]["value"][1] = 0.0f;
	_vlight.vParameter["params"][_0]["value"][2] = 0.0f;
	_vlight.vParameter["params"][1].CreateHashtable();
	_vlight.vParameter["params"][1]["key"] = halfangle;
	_vlight.vParameter["params"][1]["type"] = (unsigned int)MGE2Parameter::_VAR_PARAMETER_FVEC3_;
	_vlight.vParameter["params"][1]["value"].CreateArray();
	_vlight.vParameter["params"][1]["value"][_0] = 0.0f;
	_vlight.vParameter["params"][1]["value"][1] = 0.0f;
	_vlight.vParameter["params"][1]["value"][2] = 0.0f;

	gameRendererObjects.Resize(3);
	gameRendererObjects.CreateAll();

	MGEHashtable &_ht0 = gameRendererObjects[0].shaderIndex;
	gameShaderIndex.CopyHashtable(_ht0);
	MGEHashtable &_ht1 = gameRendererObjects[1].shaderIndex;
	gameShaderIndex.CopyHashtable(_ht1);
	MGEHashtable &_ht2 = gameRendererObjects[2].shaderIndex;
	gameShaderIndex.CopyHashtable(_ht2);

	gameSandbox.gameObjects.Resize(3);
	gameSandbox.gameObjects.CreateAll();

	MGEConfigFile znwtf;
	MGEConfigFile znwmt;
	///area = new MGE2Sandbox();
	MGEString _strztf("./ZNWTF.ini");
	MGEString _strzmt("./ZNWMT.ini");
	gameSandbox.LoadConfigFile(_strztf, znwtf);
	gameSandbox.LoadConfigFile(_strzmt, znwmt);
	gameSandbox.LoadTextureController(znwtf, znwmt, &gameRendererObjects[0], MGE2RendererContext::_RENDERER_OPENGL_);

	gameSandbox.gameObjects[0].rendererReference = &gameRendererObjects[0];
	gameShaderIndex.CopyHashtable(gameRendererObjects[0].shaderIndex);
	__str = "SKINNING";
	gameRendererObjects[0].parameterIndex.Add(__str, &_vlight);
	__str = "NORM";
	gameRendererObjects[0].parameterIndex.Add(__str, &_vlight);
	__str = "STRANS";
	gameRendererObjects[0].parameterIndex.Add(__str, &_vlight);

	
	//Init_TC(_tc);
	MGEConfigFile hstf;
	MGEConfigFile hsmt;
	MGEString _strhstf("./HSTF.ini");
	MGEString _strhsmt("./HSMT.ini");
	gameSandbox.LoadConfigFile(_strhstf, hstf);
	gameSandbox.LoadConfigFile(_strhsmt, hsmt);
	gameSandbox.LoadTextureController(hstf, hsmt, &gameRendererObjects[1], MGE2RendererContext::_RENDERER_OPENGL_);

	gameSandbox.gameObjects[1].rendererReference = &gameRendererObjects[1];
	gameShaderIndex.CopyHashtable(gameRendererObjects[1].shaderIndex);
	__str = "SKINNING";
	gameRendererObjects[1].parameterIndex.Add(__str, &_vlight);
	__str = "NORM";
	gameRendererObjects[1].parameterIndex.Add(__str, &_vlight);
	__str = "STRANS";
	gameRendererObjects[1].parameterIndex.Add(__str, &_vlight);

	gameShaders[0].UseProgram();
	gameShaders[0].SetParameter(isparallax, 0);

	///Init_LC(*_lc);
	
	err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("ERROR0014: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
	}

	///_mdlsw = new MGEModelPack();
	MGEString _strmz("./_Model/ZNW_SW2T.dat");													//	LoadMesh(mobj);
	gameSandbox.LoadModelData(_strmz, _mdlch);
															//	LoadAni1(mani1);
															//	LoadAni2(mani2);
	DoAni(_mdlch, ac, wac);

	//Init_MC(_mc);
	gameSandbox.LoadMeshController(_mdlch.GetModels()[0], &gameRendererObjects[0], MGE2RendererContext::_RENDERER_OPENGL_);
	gameRendererObjects[0].meshIndex.CopyHashtable(gameSandbox.gameObjects[0].meshIndices);

	gameSandbox.gameObjects[0].modelPrototype = &_mdlch;
	gameSandbox.gameObjects[0].animationController = &ac;
	///Init_MDLC(*_mdlc, *_mdl);

	MGEString _strmhs("./_Model/HeavenlySword.dat");
	gameSandbox.LoadModelData(_strmhs, _mdlsw);
	gameSandbox.LoadMeshController(_mdlsw.GetModels()[0], &gameRendererObjects[1], MGE2RendererContext::_RENDERER_OPENGL_);
	gameRendererObjects[1].meshIndex.CopyHashtable(gameSandbox.gameObjects[1].meshIndices);
	MGEString __strweapon("Weapon");
	Transform _t0 = Transform();
	_mdlsw.GetModels()[0].BuildAnimationController(wac.boneController, __strweapon, _t0, _t0);

	unsigned int nummeshobjects = gameRendererObjects[1].meshes.GetLength();
	for (unsigned int i2 = 0 ; i2 < nummeshobjects ; i2 ++ ) {
		if ( &gameRendererObjects[1].meshes[i2] != NULL ) {
			gameRendererObjects[1].meshes[i2].shaderName = "STRANS";
			gameRendererObjects[1].meshes[i2].SetBoneMatrices(&_wmat, 1);
		}
	}
	gameSandbox.gameObjects[1].modelPrototype = &_mdlsw;
	gameSandbox.gameObjects[1].animationController = &wac;
	///gameSandbox.gameObjects[0].renderMeshUnit = _wmc;

	MGEConfigFile archtf;
	MGEConfigFile archmt;
	MGEString _strstf("./SCTF.ini");
	MGEString _strsmt("./SCMT.ini");
	gameSandbox.LoadConfigFile(_strstf, archtf);
	gameSandbox.LoadConfigFile(_strsmt, archmt);
	gameSandbox.LoadTextureController(archtf, archmt, &gameRendererObjects[2], MGE2RendererContext::_RENDERER_OPENGL_);


	///TModel *_archmdl = NULL;
	MGEString _strmarch("./_Model/Arch.dat");
	gameSandbox.LoadModelData(_strmarch, _mdlar);
	gameSandbox.LoadMeshController(_mdlar.GetModels()[0], &gameRendererObjects[2], MGE2RendererContext::_RENDERER_OPENGL_);
															//	_archmdl->BuildAnimationController(*_archmdl, TString("Location"), Transform(), Transform());
	gameSandbox.gameObjects[2].rendererReference = &gameRendererObjects[2];
	gameShaderIndex.CopyHashtable(gameRendererObjects[2].shaderIndex);
	__str = "SKINNING";
	gameRendererObjects[2].parameterIndex.Add(__str, &_vlight);
	__str = "NORM";
	gameRendererObjects[2].parameterIndex.Add(__str, &_vlight);
	__str = "STRANS";
	gameRendererObjects[2].parameterIndex.Add(__str, &_vlight);

	nummeshobjects = gameRendererObjects[2].meshes.GetLength();
	for (unsigned int i3 = 0 ; i3 < nummeshobjects ; i3 ++ ) {
		if ( &gameRendererObjects[2].meshes[i3] != NULL ) {
			gameRendererObjects[2].meshes[i3].shaderName = "STRANS";
			gameRendererObjects[2].meshes[i3].SetBoneMatrices(&_archmat, 1);
		}
	}

	////gameSandbox.rendererShaderIndex.CopyHashtable(gameRendererObjects[0].shaderIndex);
	////gameSandbox.rendererShaderIndex.CopyHashtable(gameRendererObjects[1].shaderIndex);
	////gameSandbox.rendererShaderIndex.CopyHashtable(gameRendererObjects[2].shaderIndex);

	///TModel *_cmdl = NULL;
	__str = "./BOX.cdm";
	gameSandbox.LoadModelData(__str, _cmdl);
															//	TCollisionDetectingMatrices _cdm;
	__str = "./_Model/CDM1.cdm";														//	TestCDM(_cdm, _cmdl->GetMeshes()[0]);
	gameSandbox.LoadCollisionDetectingMatricesControllerData(__str, _cdm1, _mcdm1);
	__str = "./_Model/CDM2.cdm";
	gameSandbox.LoadCollisionDetectingMatricesControllerData(__str, _cdm2, _mcdm2);
	unsigned int numcdmos = _cdm1->GetCDMObjects().GetLength();
	for (unsigned int i5 = 0 ; i5 < numcdmos ; i5 ++ ) {
		_cdm1->GetCDMObjects()[i5].SetOuterFlag(TRUE);
	}
	_cdm1->Scale(0.015f);
	Transform ttr1(_cdm1->GetCDMObjects()[numcdmos - 1].GetCDMs()[0].GetTranslation(), 
		_cdm1->GetCDMObjects()[numcdmos - 1].GetCDMs()[0].GetRotation(), 1.0f);
	ttr1 = ttr1.Inverse();
	_cdm1->GetCDMObjects()[numcdmos - 1].GetRecommendation() = ttr1.toMatrix4();

	numcdmos = _cdm2->GetCDMObjects().GetLength();
	for (unsigned int i6 = 0 ; i6 < numcdmos ; i6 ++ ) {
		_cdm2->GetCDMObjects()[i6].SetOuterFlag(TRUE);
	}
	_cdm2->Scale(0.015f);

	Vector3f eye(3.0f , 0.0f , 0.0f);                           // infinite viewer
	Vector3f _v0;
	Vector3f _v1(0.0f, 0.0f, 1.0f);
	_view.Set(eye, _v0, _v1);
	_view.GenViewCoordinate();

															//	view->imvParamName = modelview;


}


