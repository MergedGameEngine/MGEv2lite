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

MGEModelBoneTreeNode::MGEModelBoneTreeNode() {
	boneId = 0;
	hasNextNode = FALSE;
	hasSubNode = FALSE;
	nextBoneId = 0;
	subBoneId = 0;
	nextNode = NULL;
	subNode = NULL;
}
MGEModelBoneTreeNode::MGEModelBoneTreeNode(MGEModelBoneTreeNode *p, MGEHashtable *table) {
	boneId = 0;
	hasNextNode = FALSE;
	hasSubNode = FALSE;
	nextBoneId = 0;
	subBoneId = 0;
	nextNode = NULL;
	subNode = NULL;
	parent = p;
	boneTable = table;
}

MGEModelBoneTreeNode::~MGEModelBoneTreeNode() {
}

const char *MGEModelBoneTreeNode::GetClassName() {
	return "MGEModelBoneTreeNode";
}

BOOL32 MGEModelBoneTreeNode::IsInstanceof(const char* className) {
	if (strcmp("MGEModelBoneTreeNode", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEModelBoneTreeNode::Serialize(MGEIOStream &iio) {
//	TModelObject::Serialize(iio);
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

			iio.Read(&boneId, sizeof(unsigned short));
			iio.Read(&_temp, sizeof(char));
			hasSubNode = (BOOL8)_temp;
			iio.Read(&_temp, sizeof(char));
			hasNextNode = (BOOL8)_temp;
			if (hasSubNode) {
				iio.Read(&subBoneId, sizeof(unsigned short));
			}
			if (hasNextNode) {
				iio.Read(&nextBoneId, sizeof(unsigned short));
			}

			if (hasSubNode) {
				MGETString btnClassName;//Unicode,UCS2
				btnClassName.Load(iio);
				subNode = new MGEModelBoneTreeNode(this, boneTable);
				subNode->version = version;
				subNode->subVersion = subVersion;
				subNode->Serialize(iio);
			}

			if (hasNextNode) {
				MGETString btnClassName;//Unicode,UCS2
				btnClassName.Load(iio);
				nextNode = new MGEModelBoneTreeNode(this, boneTable);
				nextNode->version = version;
				nextNode->subVersion = subVersion;
				nextNode->Serialize(iio);
			}

			if (boneTable != NULL) {
				boneTable->Add(name, this);
			}

			transform = Transform(translation, rotation, 1.0f);
			aTransform = Transform(Vector3f(), Matrix33f(), 1.0f);
			iTransform = transform.Inverse();
		}
	} else {
		////name.Store(iio);
		////iio.WriteBuffer(&translation, 3, sizeof(float));
		////iio.WriteBuffer(&rotation, 9, sizeof(float));
		////iio.Write(&scale, sizeof(float));

		////iio.Write(&boneId, sizeof(unsigned short));
		////iio.Write(&hasSubNode, sizeof(BOOL8));
		////iio.Write(&hasNextNode, sizeof(BOOL8));
		////if (hasSubNode) {
		////	iio.Write(&subBoneId, sizeof(unsigned short));
		////}
		////if (hasNextNode) {
		////	iio.Write(&nextBoneId, sizeof(unsigned short));
		////}

		////if (hasSubNode) {
		////	MGEString btnClassName(subNode->GetClassName());
		////	btnClassName.Store(iio);
		////	subNode->Serialize(iio);
		////}

		////if (hasNextNode) {
		////	MGEString btnClassName(nextNode->GetClassName());
		////	btnClassName.Store(iio);
		////	nextNode->Serialize(iio);
		////}

	}
}

Vector3f &MGEModelBoneTreeNode::GetTranslation() {
	return translation;
}

Matrix33f &MGEModelBoneTreeNode::GetRotation() {
	return rotation;
}

float &MGEModelBoneTreeNode::GetScale() {
	return scale;
}

unsigned short MGEModelBoneTreeNode::GetBoneId() {
	return boneId;
}

void MGEModelBoneTreeNode::SetBoneId(unsigned short id) {
	boneId = id;
}

BOOL8 MGEModelBoneTreeNode::HasNextNode() {
	return hasNextNode;
}

BOOL8 MGEModelBoneTreeNode::HasSubNode() {
	return hasSubNode;
}

MGEModelBoneTreeNode &MGEModelBoneTreeNode::GetNextNode() {
	return *nextNode;
}

MGEModelBoneTreeNode &MGEModelBoneTreeNode::GetSubNode() {
	return *subNode;
}

MGEModelBoneTreeNode &MGEModelBoneTreeNode::GetParentNode() {
	return *parent;
}

void MGEModelBoneTreeNode::SetNextNode(MGEModelBoneTreeNode *src) {
	if (src != NULL) {
		hasNextNode = TRUE;
		if ((nextNode != NULL) && (nextNode != src)) {
			delete nextNode;
			nextNode = NULL;
		}
		nextNode = src;
		nextBoneId = src->boneId;
	} else {
		hasNextNode = FALSE;
		if (nextNode != NULL) {
			delete nextNode;
			nextNode = NULL;
		}
	}
}

void MGEModelBoneTreeNode::SetSubNode(MGEModelBoneTreeNode *src) {
	if (src != NULL) {
		hasSubNode = TRUE;
		if ((subNode != NULL) && (subNode != src)) {
			delete subNode;
			subNode = NULL;
		}
		subNode = src;
		subBoneId = src->boneId;
	} else {
		hasSubNode = FALSE;
		if (subNode != NULL) {
			delete subNode;
			subNode = NULL;
		}
	}
}

void MGEModelBoneTreeNode::SetParentNode(MGEModelBoneTreeNode *src) {
	parent = src;
}

MGEHashtable &MGEModelBoneTreeNode::GetBoneHashtable() {
	return *boneTable;
}

Transform &MGEModelBoneTreeNode::GetInvertedTransform() {
	return iTransform;
}

Transform &MGEModelBoneTreeNode::GetAnimationTransform() {
	return aTransform;
}

Transform &MGEModelBoneTreeNode::GetTransform() {
	return transform;
}

Transform &MGEModelBoneTreeNode::GetFastTransform() {
	return fast;
}

void MGEModelBoneTreeNode::CopyInstance(MGEModelBoneTreeNode &btn) {
	btn.name = name;

	btn.translation = translation;
	btn.rotation = rotation;
	btn.scale = scale;

	btn.boneId = boneId;
	btn.hasNextNode = hasNextNode;
	btn.hasSubNode = hasSubNode;
	btn.nextBoneId = nextBoneId;
	btn.subBoneId = subBoneId;
	if (hasSubNode) {
		btn.subNode = new MGEModelBoneTreeNode(&btn, btn.boneTable);
		btn.subNode->version = subNode->version;
		btn.subNode->subVersion = subNode->subVersion;
		subNode->CopyInstance(*btn.subNode);
	}

	if (hasNextNode) {
		btn.nextNode = new MGEModelBoneTreeNode(&btn, btn.boneTable);
		btn.nextNode->version = nextNode->version;
		btn.nextNode->subVersion = nextNode->subVersion;
		nextNode->CopyInstance(*btn.nextNode);
	}

	if (btn.boneTable != NULL) {
		btn.boneTable->Add(name, &btn);
	}
}
