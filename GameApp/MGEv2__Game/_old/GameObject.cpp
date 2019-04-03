///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//#define _CORE_EXPORT
//
//#define _MATHTOOL_IMPORT
//#define _BASE_IMPORT
//#define _FILE_IMPORT
//#define _MODEL_IMPORT
//#define _THREAD_IMPORT
//#define _RENDERER_IMPORT

#include "string.h"
//#include "../Base/Type.h"
//#include "../Base/Base.h"
//#define _ARRAY_API _CORE_API
//#include "ModelController.hpp"
//
//#include "BaseImport.h"
//#include "MathToolImport.h"
//#include "FileImport.h"
//#include "ModelImport.h"
//#include "RendererImport.h"

#include "GameObject.hpp"

MGE2GameObject::MGE2GameObject() {
	animationController = NULL;
	modelPrototype = NULL;
	//renderMeshUnit = NULL;
	//renderTextureUnit = NULL;
	subModelControllers.Resize(0);
	numBoneMatrices = 0;

	directionAngle = 0;
}
MGE2GameObject::~MGE2GameObject() {
	animationController = NULL;
	modelPrototype = NULL;
	//renderMeshUnit = NULL;
	//renderTextureUnit = NULL;
	subModelControllers.Resize(0);
}
const char *MGE2GameObject::GetClassName() {
	return "MGE2GameObject";
}

BOOL32 MGE2GameObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2GameObject", className)) {
		return TRUE;
	}
	return FALSE;
}

void MGE2GameObject::LinkBoneMatrices() {
	MGEModelData *mdlink = &animationController->boneController;
///	TMeshController *mc = renderMeshUnit;
	unsigned int numeshes = mdlink->GetNumMeshes();
	for ( unsigned int i2 = 0 ; i2 < numeshes ; i2 ++ ) {
		MGE2MeshObject *mo = (MGE2MeshObject*)meshIndices.Get(mdlink->GetMeshes()[i2].name);
		MGEModelMesh *m = &mdlink->GetMeshes()[i2];
		if ( mo != NULL ) {
			MGEDataArray<Matrix44f> &bm = m->GetBoneMatrices();
			if ( bm.GetLength() != numBoneMatrices ) {
				bm.Resize(numBoneMatrices);
			}
			MGERefArray<MGEModelBoneTreeNode> &btns = m->GetBoneNodes();
			unsigned int unumbones = btns.GetLength();
			for ( unsigned int i7 = 0 ; i7 < unumbones ; i7 ++ ) {
				Transform &trat = btns[i7].GetFastTransform();
				bm[i7] = Matrix44f(trat.translation, trat.rotation);
			}
			//TSkin *s = &modelPrototype->GetMeshes()[i2].GetSkins()[0];
			//if ( s != NULL ) {
			//	unsigned short unumbones = s->GetNumBones();
			//	unsigned short *bmap = (unsigned short *)(s->GetBones().GetBuffer());
			//	TRefArray<TBoneTreeNode> &btns = m->GetBoneNodes();
			//	for ( unsigned int i7 = 0 ; i7 < unumbones ; i7 ++ ) {
			//		Transform &trat = btns[bmap[i7]].GetFastTransform();
			//		Matrix44f mat(trat.translation, trat.rotation);
			//		bm[i7] = mat;
			//	}
			//}
			if ( numBoneMatrices > 0 ) {
				mo->SetBoneMatrices((Matrix44f*)bm.GetBuffer(), numBoneMatrices);
			}
		}
	}
}

//
//void MGE2GameObject::EventHandler(TEvent &e) {
//	if ( e.subject != NULL ) {
//		if ( e.subject->IsInstanceof("MGE2GameObject") ) {
//			MGE2GameObject *subject = (MGE2GameObject*)e.subject;
//			if (subject->uid == uid) {
//				return;
//			}
//			switch (e.actionCode) {
//				case 1://attack
//					{
//						Vector3f attackvec = position - subject->position;
//						if ( attackvec.Magnitude() < 3 ) {
//							position = position + attackvec.Normalized();
//							printf( " The uid = %d Charactor has been attacked by the uid = %d Charactor.\n" , uid , subject->uid );
//						} else {
//							position = position - attackvec.Normalized() * 0.3f;
//							printf( " The uid = %d Charactor wanna beat the uid = %d Charactor.\n" , uid , subject->uid );
//						}
//					}
//					break;
//				default:
//					{
//					}
//					break;
//			}
//		}
//	}
//}

void MGE2GameObject::RotationAxisZ(float angle) {
	directionAngle += angle;
	direction.fromEuler(0.0f, 0.0f, directionAngle);
}

void MGE2GameObject::Velocity(float delta) {
	Vector3f dir(1.0f, 0.0f, 0.0f);
	velocity = direction * dir * delta;
	position = positionCurrent + velocity;
}

void MGE2GameObject::Commit() {
	positionCurrent = position;
}

