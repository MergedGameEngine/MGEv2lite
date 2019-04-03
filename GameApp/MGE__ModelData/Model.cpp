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
#include "Model.hpp"

MGEModelData::MGEModelData() {
	boneController = NULL;
	numMeshes = 0;
	hasBoneController = FALSE;

	flags = 0;

	meshes.Resize(0);
}

MGEModelData::~MGEModelData() {
	meshes.DeleteAll();
	meshes.Resize(0);
}

const char *MGEModelData::GetClassName() {
	return "MGEModelData";
}

BOOL32 MGEModelData::IsInstanceof(const char* className) {
	if (strcmp("MGEModelData", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelData::Serialize(MGEIOStream &iio) {
//	MGEModelDataObject::Serialize(iio);
	char _temp = 0;
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
			iio.Read(&numMeshes, sizeof(unsigned short));
			meshes.Resize(numMeshes);
			meshes.CreateAll();
			for (unsigned int i1 = 0 ; i1 < numMeshes ; i1 ++ ) {
				MGETString mClassName;//Unicode,UCS2
				mClassName.Load(iio);
				meshes[i1].version = version;
				meshes[i1].subVersion = subVersion;
				meshes[i1].Serialize(iio);
			}
			iio.Read(&_temp, sizeof(char));
			hasBoneController = ( _temp != 0 );
			if ( hasBoneController ) {
				MGETString bcClassName;//Unicode,UCS2
				bcClassName.Load(iio);
				boneController = new MGEModelBoneController();
				boneController->version = version;
				boneController->subVersion = subVersion;
				boneController->Serialize(iio);

				for (unsigned int i2 = 0 ; i2 < numMeshes ; i2 ++ ) {
					MGERefArray<MGEModelBoneTreeNode> &boneNodes = meshes[i2].GetBoneNodes();
					boneNodes.Resize(meshes[i2].GetBones().GetLength());
					MGERefArray<MGEString> &boneBlockIndices = meshes[i2].GetBoneBlockIndices();
					for (unsigned int i3 = 0 ; i3 < boneNodes.GetLength() ; i3 ++ ) {
						boneNodes.Set(i3, (MGEModelBoneTreeNode*)(boneController->GetBoneHashtable().Get(boneBlockIndices[i3])));
					}
				}
			}
		} else
		if ( ( version == 0x00000001 ) && ( subVersion == 0x00000001 ) ) {
			name.Load(iio);//MBCS or UTF8

			iio.Read(&flags, sizeof(unsigned int));

			iio.ReadBuffer(&translation, 3, sizeof(float));
			iio.ReadBuffer(&rotation, 9, sizeof(float));
			iio.Read(&scale, sizeof(float));
			iio.Read(&numMeshes, sizeof(unsigned short));
			meshes.Resize(numMeshes);
			meshes.CreateAll();
			for (unsigned int i1 = 0 ; i1 < numMeshes ; i1 ++ ) {
				MGEString mClassName;//MBCS or UTF8
				mClassName.Load(iio);
				meshes[i1].version = version;
				meshes[i1].subVersion = subVersion;
				meshes[i1].Serialize(iio);
			}

			////iio.Read(&_temp, sizeof(char));
			////hasBoneController = ( _temp != 0 );

			if ( flags & _MODEL_CONTAIN_BONE_CONTROL_ ) {
				MGEString bcClassName;//MBCS or UTF8
				bcClassName.Load(iio);
				boneController = new MGEModelBoneController();
				boneController->version = version;
				boneController->subVersion = subVersion;
				boneController->Serialize(iio);

				for (unsigned int i2 = 0 ; i2 < numMeshes ; i2 ++ ) {
					MGERefArray<MGEModelBoneTreeNode> &boneNodes = meshes[i2].GetBoneNodes();
					boneNodes.Resize(meshes[i2].GetBones().GetLength());
					MGERefArray<MGEString> &boneBlockIndices = meshes[i2].GetBoneBlockIndices();
					for (unsigned int i3 = 0 ; i3 < boneNodes.GetLength() ; i3 ++ ) {
						boneNodes.Set(i3, (MGEModelBoneTreeNode*)(boneController->GetBoneHashtable().Get(boneBlockIndices[i3])));
					}
				}
			}
		} else
		{
		}
	} else {
		name.Store(iio);

		flags = 0;

		if ( boneController != NULL ) {
			flags |= _MODEL_CONTAIN_BONE_CONTROL_;
			hasBoneController = TRUE;
		}

		iio.Write(&flags, sizeof(unsigned int));

		iio.WriteBuffer(&translation, 3, sizeof(float));
		iio.WriteBuffer(&rotation, 9, sizeof(float));
		iio.Write(&scale, sizeof(float));
		numMeshes = (unsigned short)meshes.GetLength();
		iio.Write(&numMeshes, sizeof(unsigned short));
		for (unsigned int i1 = 0 ; i1 < numMeshes ; i1 ++ ) {
			MGEString mClassName(meshes[i1].GetClassName());
			mClassName.Store(iio);
			meshes[i1].version = version;
			meshes[i1].subVersion = subVersion;
			meshes[i1].Serialize(iio);
		}

		if ( hasBoneController ) {
			MGEString bcClassName(boneController->GetClassName());
			bcClassName.Store(iio);
			boneController->version = version;
			boneController->subVersion = subVersion;
			boneController->Serialize(iio);
		}
	}
}

Vector3f &MGEModelData::GetTranslation() {
	return translation;
}

Matrix33f &MGEModelData::GetRotation() {
	return rotation;
}

float &MGEModelData::GetScale() {
	return scale;
}

MGERefArray<MGEModelMesh> &MGEModelData::GetMeshes() {
	return meshes;
}

BOOL8 MGEModelData::HasBoneController() {
	return hasBoneController = (boneController != NULL);
}

MGEModelBoneController &MGEModelData::GetBoneController() {
	return *boneController;
}

void MGEModelData::SetBoneController(MGEModelBoneController *src) {
	if (boneController != NULL) {
		delete boneController;
		boneController = NULL;
		hasBoneController = FALSE;
	}
	if (src != NULL) {
		hasBoneController = TRUE;
		boneController = src;
	} else {
		hasBoneController = FALSE;
		boneController = NULL;
	}
}

unsigned short MGEModelData::GetNumMeshes() {
	return numMeshes;
}

void MGEModelData::SetNumMeshes(unsigned short num) {
	numMeshes = num;
}

void MGEModelData::CopyBoneBlockIndices(MGEModelData &tar) {
	unsigned int length = meshes.GetLength();
	tar.meshes.Resize(length);
	tar.meshes.CreateAll();
	for (unsigned int i2 = 0 ; i2 < length ; i2 ++ ) {
		meshes[i2].CopyBoneBlockIndices(tar.meshes[i2]);
	}
	tar.numMeshes = length;
}

void MGEModelData::LinkBoneNodes() {
	for (unsigned int i2 = 0 ; i2 < numMeshes ; i2 ++ ) {
		MGERefArray<MGEString> &boneBlockIndices = meshes[i2].GetBoneBlockIndices();
		MGERefArray<MGEModelBoneTreeNode> &boneNodes = meshes[i2].GetBoneNodes();
		boneNodes.Resize(boneBlockIndices.GetLength());
		for (unsigned int i3 = 0 ; i3 < boneNodes.GetLength() ; i3 ++ ) {
			boneNodes.Set(i3, (MGEModelBoneTreeNode*)(boneController->GetBoneHashtable().Get(boneBlockIndices[i3])));
		}
	}
}

void MGEModelData::CopyAnimationController(MGEModelData &tar) {
	CopyBoneBlockIndices(tar);
	if ( tar.boneController == NULL ) {
		tar.boneController = new MGEModelBoneController();
	}
	boneController->CopyInstance(*tar.boneController);
	tar.LinkBoneNodes();
}

void MGEModelData::BuildAnimationController(MGEModelData &tar, MGEString &rootbonename, Transform &trans, Transform &itrans) {
	CopyBoneBlockIndices(tar);
	if ( tar.boneController == NULL ) {
		tar.boneController = new MGEModelBoneController();
		tar.boneController->SetBoneRoot(new MGEModelBoneTreeNode());
	} else if ( NULL == &tar.boneController->GetBoneRoot() ) {
		tar.boneController->SetBoneRoot(new MGEModelBoneTreeNode());
	} else {
	}
	tar.boneController->GetBoneRoot().name = rootbonename;
	tar.boneController->GetBoneRoot().GetTransform() = trans;
	tar.boneController->GetBoneRoot().GetInvertedTransform() = itrans;
	tar.numMeshes = tar.meshes.GetLength();
	for ( unsigned int i3 = 0 ; i3 < tar.numMeshes ; i3 ++ ) {
		tar.meshes[i3].GetBoneNodes().Resize(1);
		tar.meshes[i3].GetBoneNodes().Set(0, &tar.boneController->GetBoneRoot());
	}
}

void MGEModelData::SetAnimationControllerBoneRoot(MGEString &newname, Transform &trans, Transform &itrans) {
	boneController->GetBoneRoot().name = newname;
	boneController->GetBoneRoot().GetTransform() = trans;
	boneController->GetBoneRoot().GetInvertedTransform() = itrans;
}