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
	//rwLock.AttribInit();
	//rwLock.Init();

	/// 4 Animation
	animator = NULL;
	parentController = NULL;
	animationIndex = NULL;
	meshObjectIndex = NULL;

	collisions = NULL;

	directionAngle = 0.0f;

	selector = NULL;
	dselector = NULL;

	currentime = 0.0f;
	dratio = 0.0f;

	innerstate = 0;

	/// ============================
	//positionCurrent;
	//position;
	//direction;
	//directionAngle;
	//velocity;
	//acceleration;
}
MGE2GameObject::~MGE2GameObject() {
	//rwLock.Unlock();
	//rwLock.Destroy();
	//rwLock.AttribDestroy();
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

	if ( animator == NULL ) {
		return;
	}
	if ( meshObjectIndex == NULL ) {
		return;
	}

	MGEModelData *mdlink = animator;// Load Animator

	unsigned int numeshes = mdlink->GetNumMeshes();
	for ( unsigned int i2 = 0 ; i2 < numeshes ; i2 ++ ) {
		MGEHashtable &_meshIndex = *meshObjectIndex;
		MGE2MeshObject *mo = (MGE2MeshObject*)_meshIndex.Get(mdlink->GetMeshes()[i2].name);
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
	float vz = velocity.z;
	velocity = direction * dir * delta;
	velocity.z = vz;
	position = positionCurrent + velocity;
	velocity = Vector3f();
}

void MGE2GameObject::CommitVelocity() {
}

void MGE2GameObject::Commit() {
	positionCurrent = position;
}

void MGE2GameObject::Gravity(float delta) {
	if ( delta == 0.0f ) {
		acceleration = Vector3f();
		velocity.z = 0.0f;
		position = positionCurrent;
	} else {
		acceleration = Vector3f(0.0f, 0.0f, -delta);
		velocity += acceleration;
		position = positionCurrent + velocity;
	}
}
	
void MGE2GameObject::CommitGravity() {
}

void MGE2GameObject::Flush(MGEString _akey, float _delta) {

	if ( animator == NULL ) {
		return;
	}
	if ( animationIndex == NULL ) {
		return;
	}
	dselector = (MGEModelSequence *)animationIndex->Get(_akey);
	if ( dselector == NULL ) {
		return;
	}
	if ( selector == dselector ) {
		dratio = 0.0f;
		numKeyFrames = selector->GetKeyFrames().GetLength();
		if ( parentController == NULL ) {
			if ( currentime > selector->GetStopTime() - 0.01 ) {
				currentime = 0.0f;
				////count ++;
			} else {
				currentime = currentime + _delta / 1000.0f;
			}
			if ( frameCounter < numKeyFrames ) {
				frameCounter ++ ;
			} else {
				frameCounter = 0;
			}

		}

		if ( parentController != NULL ) {

			parentController->animator->GetBoneController().CopyBoneTransform(animator->GetBoneController().GetBoneRoot());
			animator->GetBoneController().DoAnimation();

		} else {
			// animation[time]
			selector->LoadAnimationMatrix(animator->GetBoneController().GetBoneRoot(), currentime);
			// animation[frameCounter]

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
			if ( collisions != NULL ) {
				MGERefArray<MGEModelCollisionController> &_collisions = *collisions;
				Vector3f __position;
				BOOL32 _isc = FALSE;
				unsigned int _numc = _collisions.GetLength();
				unsigned int _i5 = 0;
				for ( _i5 = 0 ; _i5 < _numc ; _i5 ++ ) {
					_isc |= _collisions[_i5].IsCollision(position, __position);
				}
				if ( _isc ) {
					position.z = __position.z;
					Commit();
				} else {
					Commit();
					Gravity(0.001f);
				}
			}
			if ( innerstate != 0 ) {
				innerstate = 0;
			}
			Vector3f spos = ( positionCurrent + offset ) / 0.015f;
			Transform rt(spos, direction, 1.0f);
			animator->GetBoneController().GetBoneRoot().GetTransform() = rt;
			animator->GetBoneController().DoAnimation();
		}
	} else {
		if ( parentController == NULL ) {
			if ( dratio > 1.0f ) {
				selector = dselector;
				currentime = 0.0f;
			} else {
				dratio = dratio + _delta / 1000.0f;
			}
		}
		if ( selector == NULL ) {
			selector = dselector;
			return;
		}
		if ( parentController != NULL ) {
			parentController->animator->GetBoneController().CopyBoneTransform(animator->GetBoneController().GetBoneRoot());
			animator->GetBoneController().DoAnimation();
		} else {
			selector->BuildTemporaryAnimation(currentime);
			selector->LoadAnimationMatrix(*dselector, animator->GetBoneController().GetBoneRoot(), dratio);
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
			if ( collisions != NULL ) {
				MGERefArray<MGEModelCollisionController> &_collisions = *collisions;
				Vector3f __position;
				BOOL32 _isc = FALSE;
				unsigned int _numc = _collisions.GetLength();
				unsigned int _i5 = 0;
				for ( _i5 = 0 ; _i5 < _numc ; _i5 ++ ) {
					_isc |= _collisions[_i5].IsCollision(position, __position);
				}
				if ( _isc ) {
					position.z = __position.z;
					Commit();
				} else {
					Commit();
					Gravity(0.001f);
				}
			}
			if ( innerstate != 0 ) {
				innerstate = 0;
			}
			Vector3f spos = ( positionCurrent + offset ) / 0.015f;
			Transform rt(spos, direction, 1.0f);
			animator->GetBoneController().GetBoneRoot().GetTransform() = rt;
			animator->GetBoneController().DoAnimation();
		}
	}
}

void MGE2GameObject::Flush(float _delta) {

	if ( animator == NULL ) {
		return;
	}
	if ( animationIndex == NULL ) {
		return;
	}
	if ( dselector == NULL ) {
		return;
	}
	if ( selector == dselector ) {
		dratio = 0.0f;
		numKeyFrames = selector->GetKeyFrames().GetLength();
		if ( parentController == NULL ) {
			if ( currentime > selector->GetStopTime() - 0.01 ) {
				currentime = 0.0f;
				////count ++;
			} else {
				currentime = currentime + _delta / 1000.0f;
			}
			if ( frameCounter < numKeyFrames ) {
				frameCounter ++ ;
			} else {
				frameCounter = 0;
			}

		}

		if ( parentController != NULL ) {

			parentController->animator->GetBoneController().CopyBoneTransform(animator->GetBoneController().GetBoneRoot());
			animator->GetBoneController().DoAnimation();

		} else {
			// animation[time]
			selector->LoadAnimationMatrix(animator->GetBoneController().GetBoneRoot(), currentime);
			// animation[frameCounter]

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
			if ( collisions != NULL ) {
				MGERefArray<MGEModelCollisionController> &_collisions = *collisions;
				Vector3f __position;
				BOOL32 _isc = FALSE;
				unsigned int _numc = _collisions.GetLength();
				unsigned int _i5 = 0;
				for ( _i5 = 0 ; _i5 < _numc ; _i5 ++ ) {
					_isc |= _collisions[_i5].IsCollision(position, __position);
				}
				if ( _isc ) {
					position.z = __position.z;
					Commit();
				} else {
					Commit();
					Gravity(0.001f);
				}
			}
			if ( innerstate != 0 ) {
				innerstate = 0;
			}
			Vector3f spos = ( positionCurrent + offset ) / 0.015f;
			Transform rt(spos, direction, 1.0f);
			animator->GetBoneController().GetBoneRoot().GetTransform() = rt;
			animator->GetBoneController().DoAnimation();
		}
	} else {
		if ( parentController == NULL ) {
			if ( dratio > 1.0f ) {
				selector = dselector;
				currentime = 0.0f;
			} else {
				dratio = dratio + _delta / 1000.0f;
			}
		}
		if ( selector == NULL ) {
			selector = dselector;
			return;
		}
		if ( parentController != NULL ) {
			parentController->animator->GetBoneController().CopyBoneTransform(animator->GetBoneController().GetBoneRoot());
			animator->GetBoneController().DoAnimation();
		} else {
			selector->BuildTemporaryAnimation(currentime);
			selector->LoadAnimationMatrix(*dselector, animator->GetBoneController().GetBoneRoot(), dratio);
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
			if ( collisions != NULL ) {
				MGERefArray<MGEModelCollisionController> &_collisions = *collisions;
				Vector3f __position;
				BOOL32 _isc = FALSE;
				unsigned int _numc = _collisions.GetLength();
				unsigned int _i5 = 0;
				for ( _i5 = 0 ; _i5 < _numc ; _i5 ++ ) {
					_isc |= _collisions[_i5].IsCollision(position, __position);
				}
				if ( _isc ) {
					position.z = __position.z;
					Commit();
				} else {
					Commit();
					Gravity(0.001f);
				}
			}
			if ( innerstate != 0 ) {
				innerstate = 0;
			}
			Vector3f spos = ( positionCurrent + offset ) / 0.015f;
			Transform rt(spos, direction, 1.0f);
			animator->GetBoneController().GetBoneRoot().GetTransform() = rt;
			animator->GetBoneController().DoAnimation();
		}
	}
}

void MGE2GameObject::InitializeAnimation(MGEString _akey, MGEHashtable *_animationIndex, MGEHashtable *_meshObjectIndex) {
	if ( modelPrototype == NULL ) {
		return;
	}
	if ( modelPrototype->GetModels().GetLength() < 1 ) {
		return;
	}

	if ( ( _animationIndex != NULL ) && ( _meshObjectIndex != NULL ) ) {
		animationIndex = _animationIndex;
		meshObjectIndex = _meshObjectIndex;
		dselector = (MGEModelSequence *)animationIndex->Get(_akey);
		selector = dselector;

		animator = new MGEModelData();
		if ( modelPrototype->GetModels().GetLength() < 1 ) {
			return;
		}
		MGEModelData &mdl = modelPrototype->GetModels()[0];
		if ( !mdl.HasBoneController() ) {
			return;
		}
		MGEModelBoneTreeNode &boneRoot = mdl.GetBoneController().GetBoneRoot();
		Transform _t0(Vector3f(), Matrix33f(), 1.0f);
		mdl.GetBoneController().ReloadMatrix();
		mdl.GetBoneController().BuildBoneMatrix(boneRoot, _t0);
		mdl.GetBoneController().ReloadInvertedMatrix(boneRoot);
		mdl.GetBoneController().ReloadMatrix(boneRoot);
		mdl.CopyAnimationController(*animator);
		animator->GetBoneController().ReloadMatrix();
		animator->GetBoneController().BuildBoneMatrix();
		animator->GetBoneController().ReloadInvertedMatrix();
		animator->GetBoneController().ReloadMatrix();
		///collisions = new MGERefArray<MGEModelCollisionController>;

	}
}
