///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)	v2	Copyright 2018
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//
//		base container
//		 string, array, hashtable, variant 
//		 
//
///////////////////////////////////////////////////////////////////


#ifndef _BASE_H_
#define _BASE_H_


#include "Type.h"

//#define LITTLE_ENDIAN 0
//#define BIG_ENDIAN 1

//#define IO_STORE 0
//#define IO_LOAD 1

class MGEIOStream;

extern "C" class MGEObject {
public:
	virtual ~MGEObject();
public:
	virtual const char* GetClassName() = 0;
	virtual BOOL32 IsInstanceof(const char* className) = 0;
};

extern "C" class MGEIOStream : public MGEObject {
public:
	virtual ~MGEIOStream();
public:
	virtual BOOL32 Open() = 0;
	virtual void Close() = 0;
	virtual void SetEndian(unsigned int endian) = 0;
	virtual unsigned int GetEndian() = 0;
	virtual void SetLoadStore(unsigned int loadstore) = 0;
	virtual unsigned int GetLoadStore() = 0;
	virtual unsigned int Read(const void* buf, const unsigned int length) = 0;
	virtual unsigned int Write(const void* buf, const unsigned int length) = 0;
	virtual unsigned int ReadBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) = 0;
	virtual unsigned int WriteBuffer(const void* buf, const unsigned int cells, const unsigned int celllength) = 0;
	virtual unsigned int Seek(unsigned int length) = 0;
	virtual unsigned int Seek(unsigned int begin, unsigned int length) = 0;
	virtual unsigned int GetPosition() = 0;
	virtual BOOL32 IsEoF() = 0;
	enum {
		big_endian = 0,
		little_endian = 1
	};

	enum {
		load = 10,
		store = 11
	};
};

///////////////////////////////////////////////////////////////////
//
//		 string 16bit --- java String(UCS2) 
//		 
//
///////////////////////////////////////////////////////////////////
extern "C" class MGETString : public MGEObject {

private:
	unsigned short* buffer;
	unsigned int length;
	MGETString *___this;
protected:

public:

public:
	MGETString();
	virtual ~MGETString();
	MGETString(const wchar_t* str);
	MGETString(char* fmt, ...);
public:
	MGETString(const unsigned long* wstr);
	MGETString(const unsigned short* wstr);
	MGETString(const char* asciiStr);

public:
	MGETString operator + (const MGETString &src);
	MGETString& operator = (const MGETString &src);
	MGETString& operator += (const MGETString &src);
	BOOL32 operator == (const MGETString &src);

	BOOL32 Equals(const MGETString &src);

	MGETString operator + (const wchar_t *src);
	MGETString& operator = (const wchar_t *src);
	MGETString& operator += (const wchar_t *src);
	BOOL32 operator == (const wchar_t *src);

	const unsigned short *GetBuffer();//unsafe
	unsigned int GetLength();
	unsigned int GetWString(wchar_t *desc);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	int GetHashCode();
	BOOL32 IsEqualto(MGEObject &obj);
	void Serialize(MGEIOStream &iio);

public:
	int Read(MGEIOStream &iio, unsigned int count);
	int Write(MGEIOStream &iio, unsigned int count);
	void Load(MGEIOStream &iio);
	void Store(MGEIOStream &iio);

public:
};


///////////////////////////////////////////////////////////////////
//
//		 string 8bit
//		 
//
///////////////////////////////////////////////////////////////////
extern "C" class MGEString : public MGEObject {

private:
	char* buffer;
	unsigned int length;
	MGEString *___this;
protected:

public:

public:
	MGEString();
	virtual ~MGEString();
	MGEString(const char* str);
	MGEString(char* fmt, ...);
	MGEString(int value);
	MGEString(unsigned int value);
	MGEString(long long value);
	MGEString(unsigned long long value);
	MGEString(float value);
	MGEString(double value);

public:

public:
	MGEString operator + (const MGEString &src);
	MGEString& operator = (const MGEString &src);
	MGEString& operator += (const MGEString &src);
	BOOL32 operator == (const MGEString &src);

	BOOL32 Equals(const MGEString &src);

	MGEString operator + (const char *src);
	MGEString& operator = (const char *src);
	MGEString& operator += (const char *src);
	BOOL32 operator == (const char *src);

	const char *GetBuffer();//unsafe
	unsigned int GetLength();
	char* GetStringASC();
	unsigned int GetStringASC(char *desc);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	int GetHashCode();
	BOOL32 IsEqualto(MGEObject &obj);
	void Serialize(MGEIOStream &iio);

public:
	int Read(MGEIOStream &iio, unsigned int count);
	int Write(MGEIOStream &iio, unsigned int count);
	void Load(MGEIOStream &iio);
	void Store(MGEIOStream &iio);

public:
	int Format(MGEString formats, ...);

};


///////////////////////////////////////////////////////////////////
//
//		 string 32bit --- Linux wstring(UCS4) 
//		 
//
///////////////////////////////////////////////////////////////////
extern "C" class MGEWString : public MGEObject {

private:
	unsigned int* buffer;
	unsigned int length;
	MGEWString *___this;
protected:

public:

public:
	MGEWString();
	virtual ~MGEWString();
	MGEWString(const wchar_t* str);
	MGEWString(char* fmt, ...);
public:
	MGEWString(const unsigned int* wstr);
	MGEWString(const unsigned short* wstr);
	MGEWString(const char* asciiStr);

public:
	MGEWString operator + (const MGEWString &src);
	MGEWString& operator = (const MGEWString &src);
	MGEWString& operator += (const MGEWString &src);
	BOOL32 operator == (const MGEWString &src);

	BOOL32 Equals(const MGEWString &src);

	MGEWString operator + (const wchar_t *src);
	MGEWString& operator = (const wchar_t *src);
	MGEWString& operator += (const wchar_t *src);
	BOOL32 operator == (const wchar_t *src);

	const unsigned int *GetBuffer();//unsafe
	unsigned int GetLength();
	unsigned int GetWString(wchar_t *desc);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	int GetHashCode();
	BOOL32 IsEqualto(MGEObject &obj);
	void Serialize(MGEIOStream &iio);

public:
	int Read(MGEIOStream &iio, unsigned int count);
	int Write(MGEIOStream &iio, unsigned int count);
	void Load(MGEIOStream &iio);
	void Store(MGEIOStream &iio);

public:
};

extern "C" struct MGEHashitem {
	MGEString key;
	int keyHash;
	MGEObject *obj;
	int objHash;
};

extern "C" class MGEObjectArray : public MGEObject {
protected:
	MGEObject** objects;
	unsigned int length;
	MGEObjectArray *___this;
public:
	MGEObjectArray();
	MGEObjectArray(unsigned int size);
	virtual ~MGEObjectArray();
public:
	void Resize(unsigned int size);
	MGEObject *&operator[](unsigned int index);
	MGEObjectArray operator + (const MGEObjectArray &src);
	MGEObjectArray &operator = (const MGEObjectArray &src);
	MGEObjectArray &operator += (const MGEObjectArray &src);
	MGEObjectArray SubArray(const unsigned int begin, const unsigned int count);
	unsigned int GetLength();
	void DeleteAll();
	void Delete(const unsigned int begin, const unsigned int count);
	void Exchange(unsigned int i1, unsigned int i2);
	unsigned int Pack();
	void Append(const MGEObject *__obj);

public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
        
private:
	void CheckThisOut();
};


#define ONE_BLOCK_SIZE 128

extern "C" class MGEHashtable : public MGEObject {
	
private:
	MGEHashitem items[ONE_BLOCK_SIZE];
	MGEHashtable* nextTable;
	unsigned int itemCount;
private:
	MGEHashitem *NextEmptyItem(unsigned int &index, MGEHashtable *&loc);
	MGEHashitem *NextNonEmptyItem(unsigned int &index, MGEHashtable *&loc);
public:
	MGEHashtable();
	virtual ~MGEHashtable();
public:
	BOOL32 Add(MGEString &key, const MGEObject *obj);
	const MGEObject *Get(MGEString &key);
	BOOL32 Set(MGEString &key, const MGEObject *obj);
	BOOL32 Del(MGEString &key);
	unsigned int GetCount();
	MGEObject *&operator[](MGEString &key);
	unsigned int Pack();
	unsigned int GetKeyValuePair(MGEObjectArray &__keys, MGEObjectArray &__objs);

	void DeleteAll();
	void CopyHashtable(MGEHashtable &_ht);
	
public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	int GetHashCode();
};


typedef long long _var_long;
typedef unsigned long long _var_ulong;

extern "C" class MGE2Variant : public MGEObject {

private:
	unsigned long status;
	MGE2Variant *___this;

	union _VAR_PRIME_TYPE_ {
		int _iValue;
		unsigned int _uiValue;
		float _fValue;
		double _dValue;
		void *_lpointer;
		unsigned char *_bufpointer;
		MGEObject *_VarObject;
		_var_long _lValue;
		_var_ulong _ulValue;
	} VarPrimeType;


protected:
public:

	enum {
		_VAR_NULL_ = 0,
		_VAR_PRIME_INT_ = 1,
		_VAR_PRIME_UINT_ = 2,
		_VAR_PRIME_FLOAT_ = 3,
		_VAR_PRIME_DOUBLE_ = 4,
		_VAR_PRIME_LPOINTER_ = 5,//<==unused
		_VAR_PRIME_BPOINTER_ = 6,//<==unused
		_VAR_PRIME_LONG_ = 7,
		_VAR_PRIME_ULONG_ = 8,
		_VAR_WSTRING_ = 9,
		_VAR_TSTRING_ = 10,
		_VAR_STRING_ = 11,
		_VAR_OBJECT_ARRAY_ = 12,
		_VAR_REFERENCE_ = 13,//<==unused
		_VAR_HASHTABLE_ = 14,
		_VAR_ERROR_ = 15,
		_VAR_TYPE_STATUS_MASK_ = 0x000F,
	};


public:

public:
	MGE2Variant();
	virtual ~MGE2Variant();
public:
	MGE2Variant(const int _ivalue);
	MGE2Variant(const unsigned int _ivalue);
	MGE2Variant(const float _fvalue);
	MGE2Variant(const double _dvalue);


	MGE2Variant(const _var_long _lvalue);
	MGE2Variant(const _var_ulong _lvalue);
	MGE2Variant(const wchar_t* wstr);
	MGE2Variant(const MGEWString &src);
	MGE2Variant(const MGETString &src);
	MGE2Variant(const char* str);
	MGE2Variant(const MGEString &src);

	MGE2Variant(const MGE2Variant *_ref);//unsafe

public:
	MGE2Variant& operator = (const MGE2Variant &src);
	BOOL32 operator == (const MGE2Variant &src);
	MGE2Variant& operator[](MGEString &key);
	MGE2Variant& operator[](unsigned int index);

//	MGEObject *GetObject();
	void DeleteAll();

	MGE2Variant& operator[](const char *__str);

	MGE2Variant operator / (const MGE2Variant &src);
	MGE2Variant operator * (const MGE2Variant &src);
	MGE2Variant operator - (const MGE2Variant &src);
	MGE2Variant operator + (const MGE2Variant &src);

	MGE2Variant& operator /= (const MGE2Variant &src);
	MGE2Variant& operator *= (const MGE2Variant &src);
	MGE2Variant& operator -= (const MGE2Variant &src);
	MGE2Variant& operator += (const MGE2Variant &src);

	BOOL32 Equals(const MGE2Variant &src);

	MGE2Variant operator + (const int _ivalue);
	MGE2Variant operator + (const unsigned int _ivalue);
	MGE2Variant operator + (const float _fvalue);
	MGE2Variant operator + (const double _dvalue);

	MGE2Variant operator + (const MGEWString &src);
	MGE2Variant operator + (const MGETString &src);

	MGE2Variant operator + (const _var_long _lvalue);
	MGE2Variant operator + (const _var_ulong _lvalue);
	MGE2Variant operator + (const wchar_t* wstr);
	MGE2Variant operator + (const char* str);
	MGE2Variant operator + (const MGEString &src);

	MGE2Variant& operator = (const int _ivalue);
	MGE2Variant& operator = (const unsigned int _ivalue);
	MGE2Variant& operator = (const float _fvalue);
	MGE2Variant& operator = (const double _dvalue);

	MGE2Variant& operator = (const MGEWString &src);
	MGE2Variant& operator = (const MGETString &src);

	MGE2Variant& operator = (const _var_long _lvalue);
	MGE2Variant& operator = (const _var_ulong _lvalue);
	MGE2Variant& operator = (const wchar_t* wstr);
	MGE2Variant& operator = (const char* str);
	MGE2Variant& operator = (const MGEString &src);

	MGE2Variant& operator += (const int _ivalue);
	MGE2Variant& operator += (const unsigned int _ivalue);
	MGE2Variant& operator += (const float _fvalue);
	MGE2Variant& operator += (const double _dvalue);

	MGE2Variant& operator += (const MGEWString &src);
	MGE2Variant& operator += (const MGETString &src);

	MGE2Variant& operator += (const _var_long _lvalue);
	MGE2Variant& operator += (const _var_ulong _lvalue);
	MGE2Variant& operator += (const wchar_t* wstr);
	MGE2Variant& operator += (const char* str);
	MGE2Variant& operator += (const MGEString &src);

	BOOL32 operator == (const int _ivalue);
	BOOL32 operator == (const unsigned int _ivalue);
	BOOL32 operator == (const float _fvalue);
	BOOL32 operator == (const double _dvalue);

	BOOL32 operator == (const MGEWString &src);
	BOOL32 operator == (const MGETString &src);

	BOOL32 operator == (const _var_long _lvalue);
	BOOL32 operator == (const _var_ulong _lvalue);
	BOOL32 operator == (const wchar_t* wstr);
	BOOL32 operator == (const char* str);
	BOOL32 operator == (const MGEString &src);

	MGE2Variant operator - (const int _ivalue);
	MGE2Variant operator - (const unsigned int _ivalue);
	MGE2Variant operator - (const float _fvalue);
	MGE2Variant operator - (const double _dvalue);

	MGE2Variant operator - (const MGEWString &src);
	MGE2Variant operator - (const MGETString &src);

	MGE2Variant operator - (const _var_long _lvalue);
	MGE2Variant operator - (const _var_ulong _lvalue);
	MGE2Variant operator - (const wchar_t* wstr);
	MGE2Variant operator - (const char* str);
	MGE2Variant operator - (const MGEString &src);

	MGE2Variant operator / (const int _ivalue);
	MGE2Variant operator / (const unsigned int _ivalue);
	MGE2Variant operator / (const float _fvalue);
	MGE2Variant operator / (const double _dvalue);

	MGE2Variant operator / (const MGEWString &src);
	MGE2Variant operator / (const MGETString &src);

	MGE2Variant operator / (const _var_long _lvalue);
	MGE2Variant operator / (const _var_ulong _lvalue);
	MGE2Variant operator / (const wchar_t* wstr);
	MGE2Variant operator / (const char* str);
	MGE2Variant operator / (const MGEString &src);

	MGE2Variant operator * (const int _ivalue);
	MGE2Variant operator * (const unsigned int _ivalue);
	MGE2Variant operator * (const float _fvalue);
	MGE2Variant operator * (const double _dvalue);

	MGE2Variant operator * (const MGEWString &src);
	MGE2Variant operator * (const MGETString &src);

	MGE2Variant operator * (const _var_long _lvalue);
	MGE2Variant operator * (const _var_ulong _lvalue);
	MGE2Variant operator * (const wchar_t* wstr);
	MGE2Variant operator * (const char* str);
	MGE2Variant operator * (const MGEString &src);

	//MGE2Variant& operator () (const MGE2Variant &src);

public:
	void CreateArray();
	void CreateHashtable();//Deprecated
	void CreateGenericObject();

public:
	unsigned int GetCount();
	BOOL32 Del(MGEString &key);
	unsigned int Pack();

public:

	int GetInt(unsigned int *_result);
	unsigned int GetUInt(unsigned int *_result);
	long long GetLong(unsigned int *_result);
	unsigned long long GetULong(unsigned int *_result);

	const void *GetBuffer(unsigned int *_result);//unsafe
	const MGE2Variant *GetReference(unsigned int *_result);//unsafe

	float GetFloat(unsigned int *_result);
	double GetDouble(unsigned int *_result);

	unsigned int Copy2String(MGEString &desc);
	unsigned int Copy2String(MGETString &desc);
	unsigned int Copy2String(MGEWString &desc);


private:
	int DivOpr(MGE2Variant& desc, MGE2Variant& op1, MGE2Variant& op2); 
	int MulOpr(MGE2Variant& desc, MGE2Variant& op1, MGE2Variant& op2); 
	int SubOpr(MGE2Variant& desc, MGE2Variant& op1, MGE2Variant& op2); 
	int AddOpr(MGE2Variant& desc, MGE2Variant& op1, MGE2Variant& op2); 

	void DelObj();
	void Error();

	void CheckThisOut();
	void ObjectArray2Hashtable();

	void CopyfromString(const MGEString &src);
	void CopyfromString(const MGETString &src);
	void CopyfromString(const MGEWString &src);

	void CopyHashtablefromHashtable(MGE2Variant& src);
	void CopyHashtablefromObjectArray(MGE2Variant& src);
	void CopyObjectArrayfromObjectArray(MGE2Variant& src);
	void Assign(MGE2Variant& desc, MGE2Variant& src);

public:
	unsigned int GetKeyValuePair(MGEObjectArray &__keys, MGEObjectArray &__vars);

public:
	MGE2Variant& SetReturn();


public:
	virtual const char* GetClassName();
	virtual BOOL32 IsInstanceof(const char* className);
	int GetHashCode();
	BOOL32 IsEqualto(MGEObject &obj);
	void Serialize(MGEIOStream &iio);

public:

public:

};




#endif