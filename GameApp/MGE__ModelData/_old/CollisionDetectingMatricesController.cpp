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
#undef _ARRAY_API
#define _ARRAY_API _MODEL_API
#include "CollisionDetectingMatricesController.hpp"

MGEModelCollisionController::MGEModelCollisionController() {
}

MGEModelCollisionController::~MGEModelCollisionController() {
}

const char *MGEModelCollisionController::GetClassName() {
	return "MGEModelCollisionController";
}

BOOL32 MGEModelCollisionController::IsInstanceof(const char* className) {
	if (strcmp("MGEModelCollisionController", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelCollisionController::Serialize(MGEIOStream &iio) {
	if ( iio.GetLoadStore() == MGEIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			unsigned int numcdms = 0;
			iio.Read(&numcdms, sizeof(unsigned int));
			cdmos.Resize(numcdms);
			cdmos.CreateAll();
			for ( unsigned int i2 = 0 ; i2 < numcdms ; i2 ++ ) {
				cdmos[i2].version = version;
				cdmos[i2].subVersion = subVersion;
				cdmos[i2].Serialize(iio);
			}
		}
	} else {
		unsigned int numcdms = cdmos.GetLength();
		iio.Write(&numcdms, sizeof(unsigned int));
		for ( unsigned int i2 = 0 ; i2 < numcdms ; i2 ++ ) {
			cdmos[i2].Serialize(iio);
		}
	}
}

MGERefArray<MGEModelCollision> &MGEModelCollisionController::GetCDMObjects() {
	return cdmos;
}
MGEHashtable &MGEModelCollisionController::GetCDMIndices() {
	return cdmoIndices;
}
MGEModelCollision &MGEModelCollisionController::GetCDMObject(MGEString &key) {
	return *(MGEModelCollision*)cdmoIndices.Get(key);
}

BOOL32 MGEModelCollisionController::IsCollision(Vector4f &src, Vector4f &varify) {
	unsigned int numcdmos = cdmos.GetLength();
	for ( unsigned int i2 = 0 ; i2 < numcdmos ; i2 ++ ) {
		if ( cdmos[i2].IsCollision(src, varify) ) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL32 MGEModelCollisionController::IsCollision(Vector3f &src, Vector3f &varify) {
	unsigned int numcdmos = cdmos.GetLength();
	for ( unsigned int i2 = 0 ; i2 < numcdmos ; i2 ++ ) {
		if ( cdmos[i2].IsCollision(src, varify) ) {
			return TRUE;
		}
	}
	return FALSE;
}

void MGEModelCollisionController::Scale(float ratio) {
	unsigned int numcdmos = cdmos.GetLength();
	for ( unsigned int i2 = 0 ; i2 < numcdmos ; i2 ++ ) {
		cdmos[i2].Scale(ratio);
	}
}
