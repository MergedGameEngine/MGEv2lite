///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "Type.h"
#include "Base.h"

class MGEObject;

template <typename T>
class MGEDataArray : public MGEObject {
protected:
	T* buffer;
	unsigned int length;
	MGEDataArray *___this;
public:
	MGEDataArray();
	MGEDataArray(unsigned int size);
	virtual ~MGEDataArray();
public:
	void Resize(unsigned int size);
	T &operator[](unsigned int index);
	MGEDataArray operator + (const MGEDataArray &src);
	MGEDataArray &operator = (const MGEDataArray &src);
	MGEDataArray &operator += (const MGEDataArray &src);
	MGEDataArray SubArray(const unsigned int begin, const unsigned int count);
	unsigned int GetLength();
	const void *GetBuffer();
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	int GetHashCode();
	BOOL32 IsEqualto(MGEObject &obj);
	void Serialize(MGEIOStream &iio);
};

#endif