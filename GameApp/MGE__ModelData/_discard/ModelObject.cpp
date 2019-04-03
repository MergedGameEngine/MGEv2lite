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

#include "ModelObject.h"
#include "string.h"

_MODEL_API TModelObject::TModelObject() {
	version = 0;
	subVersion = 0;
	filePos = 0;
}

_MODEL_API TModelObject::~TModelObject() {
}

char _MODEL_API *TModelObject::GetClassName() {
	return "TModelObject";
}

int _MODEL_API TModelObject::GetClassCode() {
	return CLSID_TModelObject;
}

int _MODEL_API TModelObject::GetHashCode() {
	return 1;
}

BOOL32 _MODEL_API TModelObject::IsInstanceof(const char* className) {
	if (strcmp("TModelObject", className) == 0) {
		return TRUE;
	} else if (strcmp("IObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL32 _MODEL_API TModelObject::IsEqualto(IObject &obj) {
	return FALSE;
}

void _MODEL_API TModelObject::Serialize(IIOStream &iio) {
}

void _MODEL_API TModelObject::Wait() {
}

void _MODEL_API TModelObject::Notify() {
}

void _MODEL_API TModelObject::SetVersion(unsigned int ver) {
	version = ver;
}

void _MODEL_API TModelObject::SetSubVersion(unsigned int subver) {
	subVersion = subver;
}

void _MODEL_API TModelObject::SetName(TString &src) {
	name = src;
}

unsigned int _MODEL_API TModelObject::GetVersion() {
	return version;
}

unsigned int _MODEL_API TModelObject::GetSubVersion() {
	return subVersion;
}

TString _MODEL_API &TModelObject::GetName() {
	return name;
}

unsigned int _MODEL_API TModelObject::GetFilePosition() {
	return filePos;
}

