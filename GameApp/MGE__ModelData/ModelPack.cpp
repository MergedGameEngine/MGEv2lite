///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _MODEL_EXPORT

#include "string.h"
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#define _ARRAY_API _MODEL_API
#include "ModelPack.hpp"

MGEModelPack::MGEModelPack() {
	models.Resize(0);
	animations.Resize(0);
	fileType = MGEModelPack::type_model;
	numModels = 0;
	numAnimations = 0;
}

MGEModelPack::~MGEModelPack() {
//	models.DeleteAll();
	models.Resize(0);
//	animations.DeleteAll();
	animations.Resize(0);
}

const char *MGEModelPack::GetClassName() {
	return "MGEModelPack";
}

BOOL32 MGEModelPack::IsInstanceof(const char* className) {
	if (strcmp("MGEModelPack", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelPack::Serialize(MGEIOStream &iio) {
	char _magic[10];
	if ( iio.GetLoadStore() == MGEIOStream::load ) {
		iio.ReadBuffer(_magic, 8, sizeof(char));
		_magic[8] = 0;

		if ( strcmp("MGEMDL\n", _magic) == 0 ) {
			unsigned char endiantype = 0;
			iio.Read(&endiantype, sizeof(unsigned char));
			iio.Read(&version, sizeof(unsigned int));
			iio.Read(&subVersion, sizeof(unsigned int));
			if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
				iio.Read(&fileType, sizeof(unsigned char));
				if ( ( fileType == MGEModelPack::type_model ) || ( fileType == MGEModelPack::type_animation ) ) {
					iio.Read(&numModels, sizeof(unsigned short));
					models.Resize(numModels);
					models.CreateAll();
					for (unsigned int i1 = 0 ; i1 < numModels ; i1 ++ ) {
						MGETString className;//Unicode,UCS2
						className.Load(iio);
						models[i1].version = version;
						models[i1].subVersion = subVersion;
						models[i1].Serialize(iio);
					}
					iio.Read(&numAnimations, sizeof(unsigned short));
					animations.Resize(numAnimations);
					animations.CreateAll();
					for (unsigned int i2 = 0 ; i2 < numAnimations ; i2 ++ ) {
						MGETString aClassName;//Unicode,UCS2
						aClassName.Load(iio);
						animations[i2].version = version;
						animations[i2].subVersion = subVersion;
						animations[i2].Serialize(iio);
					}
				}
				if (fileType == MGEModelPack::type_collision) {
					unsigned int numcdmcs = 0;
					iio.Read(&numcdmcs, sizeof(unsigned int));
					cdmcs.Resize(numcdmcs);
					cdmcs.CreateAll();
					for (unsigned int i2 = 0 ; i2 < numcdmcs ; i2 ++ ) {
						cdmcs[i2].version = version;
						cdmcs[i2].subVersion = subVersion;
						cdmcs[i2].Serialize(iio);
					}
				}
			} else 
			if ( ( version == 0x00000001 ) && ( subVersion == 0x00000001 ) ) {
				iio.Read(&fileType, sizeof(unsigned char));
				if ( ( fileType == MGEModelPack::type_model ) || ( fileType == MGEModelPack::type_animation ) ) {
					iio.Read(&numModels, sizeof(unsigned short));
					models.Resize(numModels);
					models.CreateAll();
					for (unsigned int i1 = 0 ; i1 < numModels ; i1 ++ ) {
						MGEString className;//MBCS or UTF8
						className.Load(iio);
						models[i1].version = version;
						models[i1].subVersion = subVersion;
						models[i1].Serialize(iio);
					}
					iio.Read(&numAnimations, sizeof(unsigned short));
					animations.Resize(numAnimations);
					animations.CreateAll();
					for (unsigned int i2 = 0 ; i2 < numAnimations ; i2 ++ ) {
						MGEString aClassName;//MBCS or UTF8
						aClassName.Load(iio);
						animations[i2].version = version;
						animations[i2].subVersion = subVersion;
						animations[i2].Serialize(iio);
					}
				}
				//if (fileType == MGEModelPack::type_collision) {
				//	unsigned int numcdmcs = 0;
				//	iio.Read(&numcdmcs, sizeof(unsigned int));
				//	cdmcs.Resize(numcdmcs);
				//	cdmcs.CreateAll();
				//	for (unsigned int i2 = 0 ; i2 < numcdmcs ; i2 ++ ) {
				//		cdmcs[i2].version = version;
				//		cdmcs[i2].subVersion = subVersion;
				//		cdmcs[i2].Serialize(iio);
				//	}
				//}
			} else 
			{
			}
		}
	} else {
		version = 0x00000001;
		subVersion = 0x00000001;
		unsigned char endiantype = MGEIOStream::little_endian;
		iio.WriteBuffer("MGEMDL\n\0", 8, sizeof(char));
		iio.Write(&endiantype, sizeof(unsigned char));
		iio.Write(&version, sizeof(unsigned int));
		iio.Write(&subVersion, sizeof(unsigned int));
		iio.Write(&fileType, sizeof(unsigned char));
		if (fileType == MGEModelPack::type_model) {
			numModels = (unsigned short)models.GetLength();
			iio.Write(&numModels, sizeof(unsigned short));
			for (unsigned int i1 = 0 ; i1 < numModels ; i1 ++ ) {
				if ( &models[i1] != NULL ) {
					MGEString className(models[i1].GetClassName());
					className.Store(iio);
					models[i1].version = version;
					models[i1].subVersion = subVersion;
					models[i1].Serialize(iio);
				}
			}
			numAnimations = (unsigned short)animations.GetLength();
			iio.Write(&numAnimations, sizeof(unsigned short));
			for (unsigned int i2 = 0 ; i2 < numAnimations ; i2 ++ ) {
				if ( &animations[i2] != NULL ) {
					MGEString aClassName(animations[i2].GetClassName());
					aClassName.Store(iio);
					animations[i2].version = version;
					animations[i2].subVersion = subVersion;
					animations[i2].Serialize(iio);
				}
			}
		}
		if (fileType == MGEModelPack::type_animation) {
			numModels = 0;
			iio.Write(&numModels, sizeof(unsigned short));
			numAnimations = (unsigned short)animations.GetLength();
			iio.Write(&numAnimations, sizeof(unsigned short));
			for (unsigned int i2 = 0 ; i2 < numAnimations ; i2 ++ ) {
				if ( &animations[i2] != NULL ) {
					MGEString aClassName(animations[i2].GetClassName());
					aClassName.Store(iio);
					animations[i2].version = version;
					animations[i2].subVersion = subVersion;
					animations[i2].Serialize(iio);
				}
			}
		}
		//if (fileType == MGEModelPack::type_collision) {
		//	unsigned int numcdmcs = cdmcs.GetLength();
		//	iio.Write(&numcdmcs, sizeof(unsigned int));
		//	for (unsigned int i2 = 0 ; i2 < numcdmcs ; i2 ++ ) {
		//		cdmcs[i2].Serialize(iio);
		//	}
		//}
	}
}

MGERefArray<MGEModelData> &MGEModelPack::GetModels() {
	return models;
}

MGERefArray<MGEModelSequence> &MGEModelPack::GetAnimations() {
	return animations;
}

MGERefArray<MGEModelCollisionController> &MGEModelPack::GetCollisionDetectingMatricesControllers() {
	return cdmcs;
}

byte MGEModelPack::GetFileType() {
	return fileType;
}

void MGEModelPack::SetFileType(byte ftype) {
	fileType = ftype;
}
