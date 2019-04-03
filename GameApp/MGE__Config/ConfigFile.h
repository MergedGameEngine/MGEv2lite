///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _CONFIGFILE_H_
#define _CONFIGFILE_H_

#include "../MGE_Base/Base.h"

extern "C" class MGEConfigFile : public MGEObject {
public:
	MGEConfigFile();
	virtual ~MGEConfigFile();
protected:
	MGERefArray<MGEString> names;
	MGERefArray<MGEConfig> values;
	MGEHashtable nameIndices;
protected:
	unsigned short errorLine;
	BOOL32 isError;
public:
	MGERefArray<MGEString> &GetNames();
	MGERefArray<MGEConfig> &GetValues();
	MGEConfig &GetValue(MGEString &name);
public:
	BOOL32 IsError(unsigned short &eline);
public:
	void Parse(MGEIOStream &iio);
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	void Serialize(MGEIOStream &iio);
};


#endif