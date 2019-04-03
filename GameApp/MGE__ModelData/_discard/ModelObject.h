///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MODELOBJECT_H_
#define _MODELOBJECT_H_

#include "..\Base\Type.h"
#include "..\Base\Base.h"
#include "..\MathTool\MathTool.h"

extern "C" class _MODEL_API TModelObject : public IObject {
protected:
protected:
	unsigned int version;
	unsigned int subVersion;
	unsigned int filePos;
	TString name;
public:
	TModelObject();
	virtual ~TModelObject();
public:
	void SetVersion(unsigned int ver);
	void SetSubVersion(unsigned int subver);
	void SetName(TString &src);
	unsigned int GetVersion();
	unsigned int GetSubVersion();
	TString &GetName();
	unsigned int GetFilePosition();
public:
	virtual char* GetClassName();
	virtual int GetClassCode();
	virtual int GetHashCode();
	virtual BOOL32 IsInstanceof(const char* className);
	virtual BOOL32 IsEqualto(IObject &obj);
	virtual void Serialize(IIOStream &iio);
	virtual void Wait();
	virtual void Notify();
};

#endif
