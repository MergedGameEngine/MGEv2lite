#define _MATHTOOL_IMPORT
#define _BASE_IMPORT
#define _FILE_IMPORT
#define _CORE_IMPORT
#define _MODEL_IMPORT
#define _RENDERER_IMPORT
#define _THREAD_IMPORT
#define _DLL_IMPORT_API __declspec(dllimport)
#define _DLL_EXPORT_API __declspec(dllimport)

#include "string.h"

#include "GL/glew.h"

#include "../MGEv2__Game/InterfaceVRendererContext.hpp"
#include "../MGEv2__Game/Core.hpp"
#include "../MGEv2__Game/Sandbox.hpp"

#include "RendererOutput.h"


int		windowWidth = 1440;                // window size
int		windowHeight = 900;
double	cameraZoom = 0.4;


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



MGE2GLFrameObject _view; 
MGE2GLFrameObject _viewfb; 

MGE2Parameter _vlight;


bool isOneFrameFinished = true;
bool isShutDown = false;

float __interval; 
float __numCycles;
MGEString __anisel("SLEEP");

CoreSync::CoreSync() {_x = 0; _y = 0; _dx = 0; _dy = 0; _oha = 0.0f; _ova = 0.0f; _dist = 5.0f; objpos = Vector3f();};
CoreSync::~CoreSync() {};
void CoreSync::OnMouseMove(short x, short y) {
	_dx = x - _x; _x = x;
	_dy = y - _y; _y = y;
	float _ha = - _dx / 180.0f;
	float _va = _dy / 180.0f;
	_oha += _ha;
	_ova += _va;
	////float _distance = 1.0f;
	////Vector3f cam(10.0f, 0.0f, 0.0f);

//	view.CameraCentered(Vector3f(10.0f, 0.0f, 0.0f) , _dist, _oha, _ova);
	//view->ObjectCentered(objpos, _dist, _oha, _ova);
	_view.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
	_view.GenViewCoordinate();
	_viewfb.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
	_viewfb.GenViewCoordinate();
}
void CoreSync::OnKeyDown(unsigned char key) {
	switch(key) {
		case 'W':
			{
				gameSandbox.gameObjects[0].innerstate = 1;
			}
			break;
		case 'S':
			{
				gameSandbox.gameObjects[0].innerstate = 2;
			}
			break;
		case 'A':
			{
				gameSandbox.gameObjects[0].RotationAxisZ(0.05f);
			}
			break;
		case 'D':
			{
				gameSandbox.gameObjects[0].RotationAxisZ(-0.05f);
			}
			break;
		case 'C':
			{
			}
			break;
		case 'Z':
			{
			}
			break;
		case '1':
			{
				__anisel = "SLEEP";
			}
			break;
		case '2':
			{
				__anisel = "WALK";
			}
			break;
		case '3':
			{
				__anisel = "ANI20";
			}
			break;
		case '4':
			{
				__anisel = "ANI21";
			}
			break;
		case '5':
			{
				__anisel = "ANI22";
			}
			break;
		case '6':
			{
				__anisel = "ANI23";
			}
			break;
		case 'I':
			{
				_dist -= 0.1f;
			//	view.CameraCentered(Vector3f(10.0f, 0.0f, 0.0f) , _dist, _oha, _ova);
				_view.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
				_view.GenViewCoordinate();
				_viewfb.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
				_viewfb.GenViewCoordinate();
			}
			break;
		case 'O':
			{
				_dist += 0.1f;
			//	view.CameraCentered(Vector3f(10.0f, 0.0f, 0.0f) , _dist, _oha, _ova);
				_view.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
				_view.GenViewCoordinate();
				_viewfb.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
				_viewfb.GenViewCoordinate();
			}
			break;
		default:
			break;
	}
	_view.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
	_view.GenViewCoordinate();
	_viewfb.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
	_viewfb.GenViewCoordinate();
}
void CoreSync::OnMouseWheel(short zdelta) {
	_dist += zdelta * 0.005f;
//	view.CameraCentered(Vector3f(10.0f, 0.0f, 0.0f) , _dist, _oha, _ova);
	_view.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
	_view.GenViewCoordinate();
	_viewfb.ObjectCentered(gameSandbox.gameObjects[0].positionCurrent, _dist, _oha, _ova);
	_viewfb.GenViewCoordinate();
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

	gameSandbox.gameObjects[0].Flush(__anisel, __interval * __numCycles);
	gameSandbox.gameObjects[1].Flush(__anisel, __interval * __numCycles);

	gameSandbox.gameObjects[2].Flush(__interval * __numCycles);
	gameSandbox.gameObjects[3].Flush(__interval * __numCycles);
	gameSandbox.gameObjects[4].Flush(__interval * __numCycles);
	gameSandbox.gameObjects[5].Flush(__interval * __numCycles);
	gameSandbox.gameObjects[6].Flush(__interval * __numCycles);
	gameSandbox.gameObjects[7].Flush(__interval * __numCycles);

	gameSandbox.gameObjects[0].numBoneMatrices = 70;
	gameSandbox.gameObjects[0].LinkBoneMatrices();

	gameSandbox.gameObjects[1].numBoneMatrices = 1;
	gameSandbox.gameObjects[1].LinkBoneMatrices();

	gameSandbox.gameObjects[2].numBoneMatrices = 70;
	gameSandbox.gameObjects[2].LinkBoneMatrices();

	gameSandbox.gameObjects[3].numBoneMatrices = 70;
	gameSandbox.gameObjects[3].LinkBoneMatrices();

	gameSandbox.gameObjects[4].numBoneMatrices = 70;
	gameSandbox.gameObjects[4].LinkBoneMatrices();

	gameSandbox.gameObjects[5].numBoneMatrices = 70;
	gameSandbox.gameObjects[5].LinkBoneMatrices();

	gameSandbox.gameObjects[6].numBoneMatrices = 70;
	gameSandbox.gameObjects[6].LinkBoneMatrices();

	gameSandbox.gameObjects[7].numBoneMatrices = 70;
	gameSandbox.gameObjects[7].LinkBoneMatrices();

}

Matrix33f __lmat;
float light_rotation = 0;

void ___SetVarParam() {
	//if (!isOneFrameFinished) {
	//	return;
	//}

	if ( light_rotation >= ( PI * 2.0 ) ) {
		light_rotation = 0.0f;
	} else {
		light_rotation += 0.05f;
	}

	Vector3f l(1.0f , 1.0f , -1.0f);

	__lmat.fromEuler(0,0, light_rotation );

	l = l.Normalized();
	////Quaternion q(Vector3f(0,0,1), light_rotation);
	//////q.mult_vec(*(vec3f*)&l); 

	l = __lmat * l;

	Vector3f eye(0.0f , 0.0f , 1.0f);
	Vector3f h = l + eye;
	h = h.Normalized();

	_vlight.vParameter["params"][_0]["value"][_0] = l.x;
	_vlight.vParameter["params"][_0]["value"][1] = l.y;
	_vlight.vParameter["params"][_0]["value"][2] = l.z;
	_vlight.vParameter["params"][1]["value"][_0] = h.x;
	_vlight.vParameter["params"][1]["value"][1] = h.y;
	_vlight.vParameter["params"][1]["value"][2] = h.z;
}

void ___RenderScene() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_viewfb.BindFrameBuffer();

//		glDisable(GL_FRAGMENT_PROGRAM_ARB);
//		glDisable(GL_FRAGMENT_PROGRAM_ARB);
//		glEnable(GL_LIGHTING);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_viewfb.viewPortHeight = (float)windowHeight;
		_viewfb.viewPortWidth = (float)windowWidth;
		_viewfb.cameraZoom = cameraZoom;
		_viewfb.SetProjection();
		_viewfb.SetViewPort();

		_view.RenderFrame();

//		glDisable(GL_LIGHTING);
//		glEnable(GL_FRAGMENT_PROGRAM_ARB);

	_viewfb.UnbindFrameBuffer();

		//_viewfb.cameraZoom = cameraZoom;
		//_viewfb.SetProjection();
		//_viewfb.SetViewPort();
	_view.viewPortHeight = (float)windowHeight;
	_view.viewPortWidth = (float)windowWidth;
	_view.cameraZoom = cameraZoom;
	_view.SetProjection();
	_view.SetViewPort();

	_view.RenderFrame();

	_viewfb.DrawFrameBufferTexture(0.0f, 0.01f, 0.0f, 0.01f);

}






void LoadAnimation() {

	MGEString __fn;

	__fn = "./_Ani/ANI01.dat";

	gameSandbox.LoadModelData(__fn, gameSandbox.modelPacks[3]);
	gameSandbox.modelIndex.Add("SLEEP", &gameSandbox.modelPacks[3]);
	gameSandbox.animationIndex.Add("SLEEP", &gameSandbox.modelPacks[3].GetAnimations()[0]);

	__fn = "./_Ani/ANI02.dat";

	gameSandbox.LoadModelData(__fn, gameSandbox.modelPacks[4]);
	gameSandbox.modelIndex.Add("WALK", &gameSandbox.modelPacks[4]);
	gameSandbox.animationIndex.Add("WALK", &gameSandbox.modelPacks[4].GetAnimations()[0]);

	__fn = "./_Ani/ANI20.dat";

	gameSandbox.LoadModelData(__fn, gameSandbox.modelPacks[5]);
	gameSandbox.modelIndex.Add("ANI20", &gameSandbox.modelPacks[5]);
	gameSandbox.animationIndex.Add("ANI20", &gameSandbox.modelPacks[5].GetAnimations()[0]);

	__fn = "./_Ani/ANI21.dat";

	gameSandbox.LoadModelData(__fn, gameSandbox.modelPacks[6]);
	gameSandbox.modelIndex.Add("ANI21", &gameSandbox.modelPacks[6]);
	gameSandbox.animationIndex.Add("ANI21", &gameSandbox.modelPacks[6].GetAnimations()[0]);

	__fn = "./_Ani/ANI22.dat";

	gameSandbox.LoadModelData(__fn, gameSandbox.modelPacks[7]);
	gameSandbox.modelIndex.Add("ANI22", &gameSandbox.modelPacks[7]);
	gameSandbox.animationIndex.Add("ANI22", &gameSandbox.modelPacks[7].GetAnimations()[0]);

	__fn = "./_Ani/ANI23.dat";

	gameSandbox.LoadModelData(__fn, gameSandbox.modelPacks[8]);
	gameSandbox.modelIndex.Add("ANI23", &gameSandbox.modelPacks[8]);
	gameSandbox.animationIndex.Add("ANI23", &gameSandbox.modelPacks[8].GetAnimations()[0]);



	gameSandbox.gameObjects[0].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.gameObjects[0].InitializeAnimation(__anisel, &gameSandbox.animationIndex, &_view.rendererReferences[0].meshIndex);

	MGEString _aniidx;
	_aniidx = "SLEEP";
	gameSandbox.gameObjects[2].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.gameObjects[2].InitializeAnimation(_aniidx, &gameSandbox.animationIndex, &_view.rendererReferences[2].meshIndex);
	_aniidx = "WALK";
	gameSandbox.gameObjects[3].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.gameObjects[3].InitializeAnimation(_aniidx, &gameSandbox.animationIndex, &_view.rendererReferences[3].meshIndex);
	_aniidx = "ANI20";
	gameSandbox.gameObjects[4].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.gameObjects[4].InitializeAnimation(_aniidx, &gameSandbox.animationIndex, &_view.rendererReferences[4].meshIndex);
	_aniidx = "ANI21";
	gameSandbox.gameObjects[5].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.gameObjects[5].InitializeAnimation(_aniidx, &gameSandbox.animationIndex, &_view.rendererReferences[5].meshIndex);
	_aniidx = "ANI22";
	gameSandbox.gameObjects[6].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.gameObjects[6].InitializeAnimation(_aniidx, &gameSandbox.animationIndex, &_view.rendererReferences[6].meshIndex);
	_aniidx = "ANI23";
	gameSandbox.gameObjects[7].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.gameObjects[7].InitializeAnimation(_aniidx, &gameSandbox.animationIndex, &_view.rendererReferences[7].meshIndex);

	MGEModelBoneTreeNode *weapon = NULL;
	weapon = (MGEModelBoneTreeNode*)gameSandbox.gameObjects[0].animator->GetBoneController().GetBoneHashtable().Get("Weapon");
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}
	weapon = (MGEModelBoneTreeNode*)gameSandbox.gameObjects[2].animator->GetBoneController().GetBoneHashtable().Get("Weapon");
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}
	weapon = (MGEModelBoneTreeNode*)gameSandbox.gameObjects[3].animator->GetBoneController().GetBoneHashtable().Get("Weapon");
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}
	weapon = (MGEModelBoneTreeNode*)gameSandbox.gameObjects[4].animator->GetBoneController().GetBoneHashtable().Get("Weapon");
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}
	weapon = (MGEModelBoneTreeNode*)gameSandbox.gameObjects[5].animator->GetBoneController().GetBoneHashtable().Get("Weapon");
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}
	weapon = (MGEModelBoneTreeNode*)gameSandbox.gameObjects[6].animator->GetBoneController().GetBoneHashtable().Get("Weapon");
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}
	weapon = (MGEModelBoneTreeNode*)gameSandbox.gameObjects[7].animator->GetBoneController().GetBoneHashtable().Get("Weapon");
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}

	gameSandbox.gameObjects[1].parentController = &gameSandbox.gameObjects[0];
	gameSandbox.gameObjects[1].modelPrototype = &gameSandbox.modelPacks[1];
	gameSandbox.gameObjects[1].InitializeAnimation(__anisel, &gameSandbox.animationIndex, &_view.rendererReferences[1].meshIndex);


	gameSandbox.gameObjects[0].animator->GetBoneController().DoAnimation();
	gameSandbox.gameObjects[2].animator->GetBoneController().DoAnimation();
	gameSandbox.gameObjects[3].animator->GetBoneController().DoAnimation();
	gameSandbox.gameObjects[4].animator->GetBoneController().DoAnimation();
	gameSandbox.gameObjects[5].animator->GetBoneController().DoAnimation();
	gameSandbox.gameObjects[6].animator->GetBoneController().DoAnimation();
	gameSandbox.gameObjects[7].animator->GetBoneController().DoAnimation();

	gameSandbox.gameObjects[2].position = Vector3f(7.0f, 0.0f, 7.0f);
	gameSandbox.gameObjects[3].position = Vector3f(3.5f, -6.062177826f, 7.0f);
	gameSandbox.gameObjects[4].position = Vector3f(3.5f, 6.062177826f, 7.0f);
	gameSandbox.gameObjects[5].position = Vector3f(-7.0f, 0.0f, 13.0f);
	gameSandbox.gameObjects[6].position = Vector3f(-3.5f, -6.062177826f, 13.0f);
	gameSandbox.gameObjects[7].position = Vector3f(-3.5f, 6.062177826f, 2.0f);

	gameSandbox.gameObjects[2].RotationAxisZ(0.0f);//.direction = Vector3f(1.0f, 0.0f, 0.0f);
	gameSandbox.gameObjects[3].RotationAxisZ(-3.1415926f / 3.0f);//.position = Vector3f(0.5f, -0.866f, 0.0f);
	gameSandbox.gameObjects[4].RotationAxisZ(3.1415926f / 3.0f);//.position = Vector3f(0.5f, 0.866f, 0.0f);
	gameSandbox.gameObjects[5].RotationAxisZ(3.1415926f);//.position = Vector3f(-1.0f, 0.0f, 0.0f);
	gameSandbox.gameObjects[6].RotationAxisZ(-3.1415926f / 1.5f);//.position = Vector3f(-0.5f, -0.866f, 0.0f);
	gameSandbox.gameObjects[7].RotationAxisZ(3.1415926f / 1.5f);//.position = Vector3f(-0.5f, 0.866f, 0.0f);

	
//	gameSandbox.gameObjects[2].offset = Vector3f(7.0f, 0.0f, 7.0f);
//	gameSandbox.gameObjects[3].offset = Vector3f(7.0f, -7.0f, 7.0f);
	gameSandbox.gameObjects[4].offset = Vector3f(0.0f, 0.0f, 1.0f);
	gameSandbox.gameObjects[5].offset = Vector3f(0.0f, 0.0f, 1.0f);
	gameSandbox.gameObjects[6].offset = Vector3f(0.0f, 0.0f, 1.0f);
//	gameSandbox.gameObjects[7].offset = Vector3f(0.0f, 0.0f, 0.8f);
}


void Initialization() {

	GLenum err;
	printf("Hardware Skinning ZNW\n\n");

	err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
	}

	MGEString __scfn("./shaderfiles.ini");
	MGEString __spcfn("./shaderparams.ini");
	MGEString __sptcfn("./shaderparamtypes.ini");

	_viewfb.frameBufferHeight = 1024;
	_viewfb.frameBufferWidth = 1024;

	_viewfb.CreateFrameBuffer(MGE2FrameObject::_FRAMEBUFFER_RENDERBUFFER_);


	gameSandbox.LoadShaders(__scfn, __spcfn, __sptcfn, MGE2RendererContext::_RENDERER_OPENGL_);

	err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("ERROR0013: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
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
	
	
	///test
//	unsigned int _i2 = 0;
//	MGEString _tstrmz("./_Model/ZNW_SW2T.dat");													//	LoadMesh(mobj);
//	MGERefArray<MGEModelPack> _packs;
//	_packs.Resize(512);
//	_packs.CreateAll();
//	for ( _i2 = 0 ; _i2 < 512 ; _i2 ++ ) {
//		gameSandbox.LoadModelData(_tstrmz, _packs[_i2]);
//	}
//	unsigned int _i2 = 0;
//	MGERefArray<MGEString> ___strarray;
//	___strarray.Resize(1024*1024);
//	___strarray.CreateAll();
//	for ( _i2 = 0 ; _i2 < 1024 * 1024 ; _i2 ++ ) {
//		___strarray[_i2] = "Hello World !";
//	}
//	printf("\nLast Object addr=[0x%016lX]\n", (unsigned long)&___strarray[1024 * 1024 - 1]);
//															//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	MGEString __str;
	unsigned int _i2;

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

	_view.rendererReferences.Resize(9);
	for ( _i2 = 0 ; _i2 < 9 ; _i2 ++ ) {
		_view.rendererReferences.Set(_i2, new MGE2GLRendererObject());
	}
	_view.renderSequence.Resize(9);
	_view.renderSequence[0] = 8;
	_view.renderSequence[1] = 0;
	_view.renderSequence[2] = 1;
	_view.renderSequence[3] = 2;
	_view.renderSequence[4] = 3;
	_view.renderSequence[5] = 4;
	_view.renderSequence[6] = 5;
	_view.renderSequence[7] = 6;
	_view.renderSequence[8] = 7;


	gameSandbox.CopyShaderIndex(&_view);


	gameSandbox.gameObjects.Resize(9);
	gameSandbox.gameObjects.CreateAll();


	gameSandbox.modelPacks.Resize(12);
	gameSandbox.modelPacks.CreateAll();

	MGEConfigFile znwtf;
	MGEConfigFile znwmt;
	MGEString _strztf("./ZNWTF.ini");
	MGEString _strzmt("./ZNWMT.ini");
	gameSandbox.LoadConfigFile(_strztf, znwtf);
	gameSandbox.LoadConfigFile(_strzmt, znwmt);
	gameSandbox.LoadTextureController(znwtf, znwmt, &_view.rendererReferences[0], MGE2RendererContext::_RENDERER_OPENGL_);

	gameSandbox.gameObjects[0].rendererReference = &_view.rendererReferences[0];

	

	MGEConfigFile hstf;
	MGEConfigFile hsmt;
	MGEString _strhstf("./HSTF.ini");
	MGEString _strhsmt("./HSMT.ini");
	gameSandbox.LoadConfigFile(_strhstf, hstf);
	gameSandbox.LoadConfigFile(_strhsmt, hsmt);
	gameSandbox.LoadTextureController(hstf, hsmt, &_view.rendererReferences[1], MGE2RendererContext::_RENDERER_OPENGL_);

	gameSandbox.gameObjects[1].rendererReference = &_view.rendererReferences[1];



	
	
	err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("ERROR0014: OpenGL error: 0x%X, %s \n" , err, gluErrorString(err));
	}

	
	MGEString _strmz("./_Model/ZNW_SW2T.dat");													
	gameSandbox.LoadModelData(_strmz, gameSandbox.modelPacks[0]);
	gameSandbox.modelIndex.Add("ZNW", &gameSandbox.modelPacks[0]);
	gameSandbox.gameObjects[0].modelPrototype = &gameSandbox.modelPacks[0];
															
	MGEConfigFile znwmc;
	MGEString _strznwmc("./ZNWMC.ini");
	gameSandbox.LoadConfigFile(_strznwmc, znwmc);
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[0].modelPrototype->GetModels()[0], znwmc, &_view.rendererReferences[0], MGE2RendererContext::_RENDERER_OPENGL_);


	gameSandbox.gameObjects[2].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[2].modelPrototype->GetModels()[0], znwmc, &_view.rendererReferences[2], MGE2RendererContext::_RENDERER_OPENGL_);
	gameSandbox.gameObjects[3].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[3].modelPrototype->GetModels()[0], znwmc, &_view.rendererReferences[3], MGE2RendererContext::_RENDERER_OPENGL_);
	gameSandbox.gameObjects[4].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[4].modelPrototype->GetModels()[0], znwmc, &_view.rendererReferences[4], MGE2RendererContext::_RENDERER_OPENGL_);
	gameSandbox.gameObjects[5].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[5].modelPrototype->GetModels()[0], znwmc, &_view.rendererReferences[5], MGE2RendererContext::_RENDERER_OPENGL_);
	gameSandbox.gameObjects[6].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[6].modelPrototype->GetModels()[0], znwmc, &_view.rendererReferences[6], MGE2RendererContext::_RENDERER_OPENGL_);
	gameSandbox.gameObjects[7].modelPrototype = &gameSandbox.modelPacks[0];
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[7].modelPrototype->GetModels()[0], znwmc, &_view.rendererReferences[7], MGE2RendererContext::_RENDERER_OPENGL_);


	gameSandbox.gameObjects[0].modelPrototype = &gameSandbox.modelPacks[0];
///	gameSandbox.rendererMeshIndex.CopyHashtable(gameSandbox.gameObjects[0].rendererReference->meshIndex);

	////_view.rendererReferences[0].meshIndex.CopyHashtable(_view.rendererReferences[2].meshIndex);
	////_view.rendererReferences[0].meshIndex.CopyHashtable(_view.rendererReferences[3].meshIndex);
	////_view.rendererReferences[0].meshIndex.CopyHashtable(_view.rendererReferences[4].meshIndex);
	////_view.rendererReferences[0].meshIndex.CopyHashtable(_view.rendererReferences[5].meshIndex);
	////_view.rendererReferences[0].meshIndex.CopyHashtable(_view.rendererReferences[6].meshIndex);
	////_view.rendererReferences[0].meshIndex.CopyHashtable(_view.rendererReferences[7].meshIndex);

	////_view.rendererReferences[2].meshes = _view.rendererReferences[0].meshes;
	////_view.rendererReferences[3].meshes = _view.rendererReferences[0].meshes;
	////_view.rendererReferences[4].meshes = _view.rendererReferences[0].meshes;
	////_view.rendererReferences[5].meshes = _view.rendererReferences[0].meshes;
	////_view.rendererReferences[6].meshes = _view.rendererReferences[0].meshes;
	////_view.rendererReferences[7].meshes = _view.rendererReferences[0].meshes;

	_view.rendererReferences[0].textureIndex.CopyHashtable(_view.rendererReferences[2].textureIndex);
	_view.rendererReferences[0].textureIndex.CopyHashtable(_view.rendererReferences[3].textureIndex);
	_view.rendererReferences[0].textureIndex.CopyHashtable(_view.rendererReferences[4].textureIndex);
	_view.rendererReferences[0].textureIndex.CopyHashtable(_view.rendererReferences[5].textureIndex);
	_view.rendererReferences[0].textureIndex.CopyHashtable(_view.rendererReferences[6].textureIndex);
	_view.rendererReferences[0].textureIndex.CopyHashtable(_view.rendererReferences[7].textureIndex);


	MGEString _strmhs("./_Model/HeavenlySword.dat");
	gameSandbox.LoadModelData(_strmhs, gameSandbox.modelPacks[1]);
	gameSandbox.modelIndex.Add("SWORD", &gameSandbox.modelPacks[1]);
	gameSandbox.gameObjects[1].modelPrototype = &gameSandbox.modelPacks[1];
	MGEConfigFile hsmc;
	MGEString _strhsmc("./HSMC.ini");
	gameSandbox.LoadConfigFile(_strhsmc, hsmc);
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[1].modelPrototype->GetModels()[0], hsmc, &_view.rendererReferences[1], MGE2RendererContext::_RENDERER_OPENGL_);


	LoadAnimation();

	MGEString __strweapon("Weapon");
	Transform _t0 = Transform();
	gameSandbox.gameObjects[1].modelPrototype->GetModels()[0].BuildAnimationController(*(gameSandbox.gameObjects[1].animator), __strweapon, _t0, _t0);

	unsigned int nummeshobjects = _view.rendererReferences[1].meshes.GetLength();
	for (unsigned int i2 = 0 ; i2 < nummeshobjects ; i2 ++ ) {
		if ( &_view.rendererReferences[1].meshes[i2] != NULL ) {

			_view.rendererReferences[1].meshes[i2].SetBoneMatrices(&_wmat, 1);
		}
	}
	gameSandbox.gameObjects[1].modelPrototype = &gameSandbox.modelPacks[1];




	MGEConfigFile archtf;
	MGEConfigFile archmt;
	MGEString _strstf("./SCTF.ini");
	MGEString _strsmt("./SCMT.ini");
	gameSandbox.LoadConfigFile(_strstf, archtf);
	gameSandbox.LoadConfigFile(_strsmt, archmt);
	gameSandbox.LoadTextureController(archtf, archmt, &_view.rendererReferences[8], MGE2RendererContext::_RENDERER_OPENGL_);



	MGEString _strmarch("./_Model/Arch.dat");
	gameSandbox.LoadModelData(_strmarch, gameSandbox.modelPacks[2]);
	gameSandbox.modelIndex.Add("ARCH", &gameSandbox.modelPacks[2]);
	gameSandbox.gameObjects[8].modelPrototype = &gameSandbox.modelPacks[2];
	MGEConfigFile armc;
	MGEString _strarmc("./SCMC.ini");
	gameSandbox.LoadConfigFile(_strarmc, armc);
	gameSandbox.LoadMeshController(gameSandbox.gameObjects[8].modelPrototype->GetModels()[0], armc, &_view.rendererReferences[8], MGE2RendererContext::_RENDERER_OPENGL_);

	gameSandbox.gameObjects[8].rendererReference = &_view.rendererReferences[8];


	nummeshobjects = _view.rendererReferences[8].meshes.GetLength();
	for (unsigned int i3 = 0 ; i3 < nummeshobjects ; i3 ++ ) {
		if ( &_view.rendererReferences[8].meshes[i3] != NULL ) {

			_view.rendererReferences[8].meshes[i3].SetBoneMatrices(&_archmat, 1);
		}
	}
	for ( _i2 = 0 ; _i2 < 9 ; _i2 ++ ) {
		__str = "SKINNING";
		_view.rendererReferences[_i2].parameterIndex.Add(__str, &_vlight);
		__str = "NORM";
		_view.rendererReferences[_i2].parameterIndex.Add(__str, &_vlight);
		__str = "STRANS";
		_view.rendererReferences[_i2].parameterIndex.Add(__str, &_vlight);
	}


	MGEModelCollisionController *_cdm1;
	MGEModelCollisionController *_cdm2;

	__str = "./BOX.cdm";
	gameSandbox.LoadModelData(__str, gameSandbox.modelPacks[9]);
	gameSandbox.modelIndex.Add("BASE", &gameSandbox.modelPacks[9]);

	MGERefArray<MGEModelCollisionController> &_collisions = gameSandbox.collisionObjects;
	__str = "./_Model/CDM1.cdm";														
	gameSandbox.LoadCollisionDetectingMatricesControllerData(__str, _cdm1, gameSandbox.modelPacks[11]);
	_collisions.Resize(1);
	_collisions.Set(0, _cdm1);

	gameSandbox.gameObjects[0].collisions = &_collisions;

	gameSandbox.gameObjects[2].collisions = &_collisions;
	gameSandbox.gameObjects[3].collisions = &_collisions;
	gameSandbox.gameObjects[4].collisions = &_collisions;
	gameSandbox.gameObjects[5].collisions = &_collisions;
	gameSandbox.gameObjects[6].collisions = &_collisions;
	gameSandbox.gameObjects[7].collisions = &_collisions;

	__str = "./_Model/CDM2.cdm";
	gameSandbox.LoadCollisionDetectingMatricesControllerData(__str, _cdm2, gameSandbox.modelPacks[10]);
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

	_viewfb.Set(eye, _v0, _v1);
	_viewfb.GenViewCoordinate();

															//	view->imvParamName = modelview;


}


