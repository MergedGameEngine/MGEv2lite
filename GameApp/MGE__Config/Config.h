///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "../MGE_Base/Base.h"
#include "../MGE_Base/Base.hpp"
#include "../MGE__MathTool/MathTool.h"

extern "C" class MGEConfig : public MGEObject {
public:
	MGEConfig();
	virtual ~MGEConfig();
protected:
	MGERefArray<MGEString> names;
	MGERefArray<MGEString> values;
	MGEHashtable nameIndices;
public:
	MGERefArray<MGEString> &GetNames();
	MGERefArray<MGEString> &GetValues();
	MGEHashtable &GetNameIndices();
public:
	double	StringtoDouble(MGEString &src);
	BOOL32	ParseInt(MGEString &key, int &des);
	BOOL32	ParseDouble(MGEString &key, double &des);
	BOOL32	ParseVector3f(MGEString &key, Vector3f &des);
	BOOL32	ParseVector4f(MGEString &key, Vector4f &des);
	BOOL32	ParseMatrix33f(MGEString &key, Matrix33f &des);
	BOOL32	ParseMatrix44f(MGEString &key, Matrix44f &des);
	BOOL32	GetString(MGEString &key, MGEString &des);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};

#endif