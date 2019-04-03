///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

#include "CRC32.h"
#include "Array.h"

#undef GetClassName

//template <typename T> _ARRAY_API TArray<T>::TArray<T>() {
template <typename T> MGEDataArray<T>::MGEDataArray() {
	buffer = NULL;
	length = 0;
	___this = this;
}

//template <typename T> _ARRAY_API TArray<T>::TArray<T>(unsigned int size) {
template <typename T> MGEDataArray<T>::MGEDataArray(unsigned int size) {
	buffer = new T[size];
	length = size;
	___this = this;
}

//template <typename T> _ARRAY_API TArray<T>::~TArray<T>() {
template <typename T> MGEDataArray<T>::~MGEDataArray() {
	if ( ___this == this ) {
		if (buffer!=NULL) {
			delete []buffer;
			buffer = NULL;
			___this = NULL;
		}
	}
}

template <typename T> void MGEDataArray<T>::Resize(unsigned int size) {
	if (size > 0) {
		T *newBuffer = new T[size];
		if (size < length) {
			memcpy(newBuffer, buffer, sizeof(T) * size);
		} else {
			memcpy(newBuffer, buffer, sizeof(T) * length);
		}
		if (buffer!=NULL) {
			delete []buffer;
			buffer = NULL;
		}
		buffer = newBuffer;
		length = size;
	} else {
		if (buffer!=NULL) {
			delete []buffer;
			buffer = NULL;
		}
		length = 0;
	}
}

template <typename T> T &MGEDataArray<T>::operator[](unsigned int index) {
	if (index < length) {
		return buffer[index];
	} else {
		return *(T*)NULL;
	}
}

template <typename T> MGEDataArray<T> MGEDataArray<T>::operator + (const MGEDataArray<T> &src) {
	MGEDataArray<T> desc(length + src.length);
	memcpy(desc.buffer, buffer, sizeof(T) * length);
	memcpy(&(desc.buffer[length]), src.buffer, sizeof(T) * src.length);
	desc.___this = 0;
	return desc;
}

template <typename T> MGEDataArray<T> &MGEDataArray<T>::operator = (const MGEDataArray<T> &src) {
	if ( this != &src ) {
		if (buffer != NULL) {
			delete []buffer;
			buffer = NULL;
		}
		if (src.buffer != NULL) {
			if (src.___this == 0) {
				buffer = src.buffer;
			} else {
				buffer = new T[src.length];
				memcpy (buffer, src.buffer, src.length * sizeof(T));
			}
		}
		length = src.length;
	}
	___this = this;
	return *this;
}

template <typename T> MGEDataArray<T> &MGEDataArray<T>::operator += (const MGEDataArray<T> &src) {
	if ( src.length > 0 ) {
		T *newBuffer = new T[length + src.length];
		memcpy( newBuffer, buffer, sizeof(T) * length );
		memcpy( &(newBuffer[length]), src.buffer, sizeof(T) * src.length);
		length += src.length;
		if (buffer!=NULL) {
			delete []buffer;
		}
		buffer = newBuffer;
	}
	___this = this;
	return *this;
}

template <typename T> MGEDataArray<T> MGEDataArray<T>::SubArray(const unsigned int begin, const unsigned int count) {
	MGEDataArray des;
	if ((begin + count) <= length) {
		des.Resize(count);
		memcpy(des.buffer, &(buffer[begin]), sizeof(T) * count);
	}
	des.___this = 0;
	return des;
}

template <typename T> unsigned int MGEDataArray<T>::GetLength() {
	return length;
}

template <typename T> const void *MGEDataArray<T>::GetBuffer() {
	return buffer;
}

template <typename T> const char *MGEDataArray<T>::GetClassName() {
	return "MGEDataArray";
}

template <typename T> int MGEDataArray<T>::GetHashCode() {
	return CRC32::GetCRC32(buffer, sizeof(T) * length);
}

template <typename T> BOOL32 MGEDataArray<T>::IsInstanceof(const char* className) {
	if (strcmp("MGEDataArray", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

template <typename T> BOOL32 MGEDataArray<T>::IsEqualto(MGEObject &obj) {
	return FALSE;
}

template <typename T> void MGEDataArray<T>::Serialize(MGEIOStream &iio) {
}

#endif