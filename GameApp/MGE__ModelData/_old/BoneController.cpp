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
#include "BoneTreeNode.hpp"
#include "BoneController.h"

MGEModelBoneController::MGEModelBoneController() {
	boneRoot = NULL;
	boneTable.Resize(0);
	numBones = 0;
	indexCount = 0;
}

MGEModelBoneController::~MGEModelBoneController() {
	boneTable.Resize(0);
}

const char *MGEModelBoneController::GetClassName() {
	return "MGEModelBoneController";
}

BOOL32 MGEModelBoneController::IsInstanceof(const char* className) {
	if (strcmp("MGEModelBoneController", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelBoneController::Serialize(MGEIOStream &iio) {
//	TModelObject::Serialize(iio);
	if ( iio.GetLoadStore() == MGEIOStream::load ) {
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000000 ) ) {
			_name.Load(iio);//Unicode,UCS2
			if ( _name.GetBuffer() ) {
#ifdef WIN32
				name = MGEString("%ls",_name.GetBuffer());
#else
				MGEWString __wstr(_name.GetBuffer());
				name = MGEString("%ls",__wstr.GetBuffer());
#endif				
			}
			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.Read(&numBones, sizeof(unsigned short));
			MGETString btnClassName;//Unicode,UCS2
			btnClassName.Load(iio);
			boneRoot = new MGEModelBoneTreeNode(NULL, &boneHashtable);
			boneRoot->version = version;
			boneRoot->subVersion = subVersion;
			boneRoot->Serialize(iio);
		}
	} else {
		name.Store(iio);
		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));
		iio.Write(&numBones, sizeof(unsigned short));
		MGEString btnClassName(boneRoot->GetClassName());
		btnClassName.Store(iio);
		boneRoot->Serialize(iio);
	}
}

MGEModelBoneTreeNode &MGEModelBoneController::GetBoneRoot() {
	return *boneRoot;
}

Vector3f &MGEModelBoneController::GetTranslation() {
	return translation;
}

Matrix33f &MGEModelBoneController::GetRotation() {
	return rotation;
}

float &MGEModelBoneController::GetScale() {
	return scale;
}

MGERefArray<MGEModelBoneTreeNode> &MGEModelBoneController::GetBoneTable() {
	return boneTable;
}

MGEHashtable &MGEModelBoneController::GetBoneHashtable() {
	return boneHashtable;
}

void MGEModelBoneController::SetBoneRoot(MGEModelBoneTreeNode *src) {
	if (boneRoot!= NULL) {
		delete boneRoot;
		boneRoot = NULL;
	}
	boneRoot = src;
}

void MGEModelBoneController::BuildBoneMatrix(MGEModelBoneTreeNode &btn, Transform &src) {
	btn.GetTransform() = src * btn.GetTransform();
	if (btn.HasSubNode()) {
		BuildBoneMatrix(btn.GetSubNode(), btn.GetTransform());
	}
	if (btn.HasNextNode()) {
		BuildBoneMatrix(btn.GetNextNode(), src);
	}
}

void MGEModelBoneController::ReloadMatrix(MGEModelBoneTreeNode &btn) {
	btn.GetTransform() = Transform(btn.GetTranslation(), btn.GetRotation(), 1.0f);
	if (btn.HasSubNode()) {
		ReloadMatrix(btn.GetSubNode());
	}
	if (btn.HasNextNode()) {
		ReloadMatrix(btn.GetNextNode());
	}
}

void MGEModelBoneController::ReloadInvertedMatrix(MGEModelBoneTreeNode &btn) {
	btn.GetInvertedTransform() = btn.GetTransform().Inverse();
	if (btn.HasSubNode()) {
		ReloadInvertedMatrix(btn.GetSubNode());
	}
	if (btn.HasNextNode()) {
		ReloadInvertedMatrix(btn.GetNextNode());
	}
}

void MGEModelBoneController::DoAnimation(MGEModelBoneTreeNode &btn, Transform &src) {
//	btn.GetFastTransform() = src * btn.GetTransform() * btn.GetAnimationTransform();
	btn.GetFastTransform() = src * btn.GetTransform();
	if (btn.HasSubNode()) {
		DoAnimation(btn.GetSubNode(), btn.GetFastTransform());
	}
	if (btn.HasNextNode()) {
		DoAnimation(btn.GetNextNode(), src);
	}
	btn.GetFastTransform() = btn.GetFastTransform() * btn.GetInvertedTransform();
}

void MGEModelBoneController::BuildBoneMatrix() {
	Transform _trs = Transform(Vector3f(), Matrix33f(), 1.0f);
	BuildBoneMatrix(*boneRoot, _trs);
}

void MGEModelBoneController::ReloadMatrix() {
	ReloadMatrix(*boneRoot);
}

void MGEModelBoneController::ReloadInvertedMatrix() {
	ReloadInvertedMatrix(*boneRoot);
}

void MGEModelBoneController::DoAnimation() {
	Transform _trs = Transform(Vector3f(), Matrix33f(), 1.0f);
	DoAnimation(*boneRoot, _trs);
}

void MGEModelBoneController::CopyInstance(MGEModelBoneController &bc) {
	bc.name = name;

	bc.translation = translation;
	bc.rotation = rotation;
	bc.scale = scale;
	
	bc.numBones = numBones;

	bc.boneRoot = new MGEModelBoneTreeNode(NULL, &bc.boneHashtable);
	bc.boneRoot->version = version;
	bc.boneRoot->subVersion = subVersion;
	boneRoot->CopyInstance(*bc.boneRoot);

	bc.boneTable.Resize(boneTable.GetLength());
	unsigned int i3 = boneTable.GetLength();
	for ( unsigned int i2 = 0 ; i2 < i3 ; i2 ++ ) {
		bc.boneTable.Set(i2, (MGEModelBoneTreeNode*)(bc.boneHashtable.Get(boneTable[i2].name)));
	}
}

void MGEModelBoneController::CopyBoneTransform(MGEModelBoneTreeNode &btn) {
	MGEModelBoneTreeNode *lbtn = (MGEModelBoneTreeNode*)boneHashtable.Get(btn.name);
	if ( lbtn != NULL ) {
		btn.GetTransform() = lbtn->GetFastTransform();
	}
}
