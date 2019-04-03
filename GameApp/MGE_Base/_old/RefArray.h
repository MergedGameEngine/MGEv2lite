///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _REFARRAY_H_
#define _REFARRAY_H_

class MGEObject;

template <typename T>
class MGERefArray : public MGEObject {
protected:
	T** references;
	unsigned int length;
	MGERefArray *___this;
public:
	MGERefArray();
	MGERefArray(unsigned int size);
	virtual ~MGERefArray();
public:
	void Resize(unsigned int size);
	T &operator[](unsigned int index);
	MGERefArray operator + (const MGERefArray &src);
	MGERefArray &operator = (const MGERefArray &src);
	MGERefArray &operator += (const MGERefArray &src);
	MGERefArray SubArray(const unsigned int begin, const unsigned int count);
	unsigned int GetLength();
	void Set(unsigned int index, T* ref);
	void DeleteAll();
	void Delete(const unsigned int begin, const unsigned int count);
	void CreateAll();
	void Create(const unsigned int begin, const unsigned int count);
	void Exchange(unsigned int i1, unsigned int i2);
	unsigned int Pack();

private:
	void CheckThisOut();

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
};

#endif