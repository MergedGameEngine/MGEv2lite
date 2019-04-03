//#define _MATHTOOL_IMPORT
//#define _BASE_IMPORT
//#define _FILE_IMPORT
//#define _CORE_IMPORT
//#define _MODEL_IMPORT
//#define _RENDERER_IMPORT
//#define _THREAD_IMPORT
//#define _DLL_IMPORT_API __declspec(dllimport)
//#define _DLL_EXPORT_API __declspec(dllimport)

//#include "windows.h"
#include "string.h"
#include "stdlib.h"
#undef GetClassName

//#include "../Base/Type.h"
//#include "../Base/Base.h"
//#define _ARRAY_API _DLL_IMPORT_API
//#include "../Base/Array.h"
//#include "../Base/RefArray.h"
//#include "../Core/BaseImport.h"
//#include "../Core/MathToolImport.h"
//#include "../Core/ModelImport.h"
//#include "../Core/RendererImport.h"
//#include "../Core/FileImport.h"
//#include "../Thread/Thread.h"
//#include "../CoreV/CoreImport.h"

#include "TempModel.h"

MGERefArray<MGEModelPack> modelpacks;

GLchar *LoadShaderText(const char *fileName) {
    GLchar *shaderText = NULL;
    GLint shaderLength = 0;
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp != NULL)
    {
        while (fgetc(fp) != EOF)
        {
            shaderLength++;
        }
        rewind(fp);
        shaderText = (GLchar *)malloc(shaderLength+1);
        if (shaderText != NULL)
        {
            fread(shaderText, 1, shaderLength, fp);
        }
        shaderText[shaderLength] = '\0';
        fclose(fp);
    }

    return shaderText;
}

void LoadMesh(MGEModelPack &mobj) {
	char *fileName = "E:\\ZHH_SW2T.dat";
	MGEFile *file = new MGEFile();
	file->SetFilePathName(fileName);
	file->SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary );
	file->Open();
	MGEFileStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	mobj.Serialize(fio);
}

void LoadAni1(MGEModelPack &mani) {
	char *fileName = "E:\\Ani01.dat";
	MGEFile *file = new MGEFile();
	file->SetFilePathName(fileName);
	file->SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary );
	file->Open();
	MGEFileStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	mani.Serialize(fio);
}

void LoadAni2(MGEModelPack &mani) {
	char *fileName = "E:\\Ani02.dat";
	MGEFile *file = new MGEFile();
	file->SetFilePathName(fileName);
	file->SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary );
	file->Open();
	MGEFileStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	mani.Serialize(fio);
}

void LoadAni(MGEModelPack &mani, const char *fileName) {
	MGEFile *file = new MGEFile();
	file->SetFilePathName(fileName);
	file->SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary );
	file->Open();
	MGEFileStream fio;
	fio.SetFile(file);
	fio.SetLoadStore(MGEFileStream::load);
	fio.SetEndian(MGEFileStream::little_endian);
	mani.Serialize(fio);
	fio.Close();
	file->Close();
	delete file;
}

void DoAni(MGEModelPack &_mdl, MGEAnimationController &ac, MGEAnimationController &wac) {
	MGEModelData &mdl = _mdl.GetModels()[0];
	MGEModelBoneTreeNode &boneRoot = mdl.GetBoneController().GetBoneRoot();
	Transform _t0(Vector3f(), Matrix33f(), 1.0f);
	mdl.GetBoneController().ReloadMatrix();
	mdl.GetBoneController().BuildBoneMatrix(boneRoot, _t0);
	mdl.GetBoneController().ReloadInvertedMatrix(boneRoot);
	mdl.GetBoneController().ReloadMatrix(boneRoot);
	mdl.CopyAnimationController(ac.boneController);
	ac.boneController.GetBoneController().ReloadMatrix();
	ac.boneController.GetBoneController().BuildBoneMatrix();
	ac.boneController.GetBoneController().ReloadInvertedMatrix();
	ac.boneController.GetBoneController().ReloadMatrix();
	MGEString _strweapon("Weapon");
	MGEModelBoneTreeNode *weapon = (MGEModelBoneTreeNode*)ac.boneController.GetBoneController().GetBoneHashtable().Get(_strweapon);
	if ( weapon != NULL ) {
		weapon->GetInvertedTransform() = Transform();
	}

	wac.parentController = &ac;

///	MGEModelPack *mg = NULL;
	MGEModelSequence *sq = NULL;
	ac.animations.Resize(6);

	modelpacks.Resize(6);
	modelpacks.CreateAll();

	unsigned int _i1 = 0;

	LoadAni(modelpacks[_i1], "./_Ani/ANI01.dat");
	sq = &modelpacks[_i1].GetAnimations()[0];
	ac.animations.Set(_i1, sq);
	_i1 ++;

	LoadAni(modelpacks[_i1], "./_Ani/ANI02.dat");
	sq = &modelpacks[_i1].GetAnimations()[0];
	ac.animations.Set(_i1, sq);
	_i1 ++;

	LoadAni(modelpacks[_i1], "./_Ani/ANI20.dat");
	sq = &modelpacks[_i1].GetAnimations()[0];
	ac.animations.Set(_i1, sq);
	_i1 ++;

	LoadAni(modelpacks[_i1], "./_Ani/ANI21.dat");
	sq = &modelpacks[_i1].GetAnimations()[0];
	ac.animations.Set(_i1, sq);
	_i1 ++;

	LoadAni(modelpacks[_i1], "./_Ani/ANI22.dat");
	sq = &modelpacks[_i1].GetAnimations()[0];
	ac.animations.Set(_i1, sq);
	_i1 ++;

	LoadAni(modelpacks[_i1], "./_Ani/ANI23.dat");
	sq = &modelpacks[_i1].GetAnimations()[0];
	ac.animations.Set(_i1, sq);
	_i1 ++;

	ac.currentime = 0.0f;
	ac.boneController.GetBoneController().DoAnimation();
}
