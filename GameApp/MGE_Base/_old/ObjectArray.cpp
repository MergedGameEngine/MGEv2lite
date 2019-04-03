///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_EXPORT


#include "Type.h"
#include "Base.h"
#include "stdio.h"
#include "string.h"
#include "CRC32.h"

MGEObjectArray::MGEObjectArray() {
	objects = NULL;
	length = 0;
	___this = this;
}

MGEObjectArray::MGEObjectArray(unsigned int size) {
	objects = new MGEObject*[size];
	length = size;
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		objects[i1] = NULL;
	}
	___this = this;
}

MGEObjectArray::~MGEObjectArray() {
	if ( ___this == this ) {
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
			___this = NULL;
		}
	} else if ( ___this == 0 ) {
	} else {
	}
}

void MGEObjectArray::Resize(unsigned int size) {
	CheckThisOut();
	if (size > 0) {
		MGEObject **newObjects = new MGEObject*[size];
		if (size < length) {
			memcpy(newObjects, objects, sizeof(MGEObject*) * size);
			for ( unsigned int i1 = size ; i1 < length ; i1 ++ ) {
				if ( objects[i1] != NULL ) {
					delete objects[i1];
					objects[i1] = NULL;
				}
			}
		} else {
			memcpy(newObjects, objects, sizeof(MGEObject*) * length);
			for ( unsigned int i1 = length ; i1 < size ; i1 ++ ) {
				newObjects[i1] = NULL;
			}
		}
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		objects = newObjects;
		length = size;
	} else {
		for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
			if ( objects[i1] != NULL ) {
				delete objects[i1];
				objects[i1] = NULL;
			}
		}
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		length = 0;
	}
}

MGEObject *&MGEObjectArray::operator[](unsigned int index) {
	if (index < length) {
		return objects[index];
	} else {
		return *(MGEObject**)NULL;
	}
}
	
MGEObjectArray MGEObjectArray::operator + (const MGEObjectArray &src) {
	MGEObjectArray desc(length + src.length);
	memcpy(desc.objects, objects, sizeof(MGEObject*) * length);
	memcpy(&(desc.objects[length]), src.objects, sizeof(MGEObject*) * src.length);	
	desc.___this = 0;
	return desc;
}

MGEObjectArray &MGEObjectArray::operator = (const MGEObjectArray &src) {
	CheckThisOut();
	if ( this != &src ) {
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		if (src.objects != NULL) {
			if (src.___this == 0) {
				objects = src.objects;
			} else {
				objects = new MGEObject*[src.length];
				memcpy (objects, src.objects, src.length * sizeof(MGEObject*));
			}
		}
	}
	length = src.length;
	___this = this;
	return *this;
}

MGEObjectArray &MGEObjectArray::operator += (const MGEObjectArray &src) {
	CheckThisOut();
	if ( src.length > 0 ) {
		MGEObject **newObjects = new MGEObject*[length + src.length];
		memcpy( newObjects, objects, sizeof(MGEObject*) * length );
		memcpy( &(newObjects[length]), src.objects, sizeof(MGEObject*) * src.length);
		length += src.length;
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		objects = newObjects;
	}
	___this = this;
	return *this;
}

MGEObjectArray MGEObjectArray::SubArray(const unsigned int begin, const unsigned int count) {
	CheckThisOut();
	MGEObjectArray des;
	if ((begin + count) <= length) {
		des.Resize(count);
		memcpy(des.objects, &(objects[begin]), sizeof(MGEObject*) * count);
	}
	des.___this = 0;
	return des;
}


unsigned int MGEObjectArray::GetLength() {
	return length;
}

void MGEObjectArray::DeleteAll() {
	CheckThisOut();
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		if ( objects[i1] != NULL ) {
			delete objects[i1];
			objects[i1] = NULL;
		}
	}
}

unsigned int MGEObjectArray::Pack() {
	CheckThisOut();
	for ( unsigned int i0 = 0 , i1 = 0 , i2 = 0; i2 < length ; i0 ++ ) {
		if ( objects[i1] == NULL ) {
			if ( i1 > i2 ) {
				i2 = i1 + 1;
			}
			if ( objects[i2] != NULL ) {
				objects[i1] = objects[i2]; objects[i2] = NULL;
			} else {
				i2 ++ ;
				if ( i2 >= length ) {
					Resize(i1);
					return length;
				}
			}
		} else {
			i1 ++ ;
			if ( i1 >= length ) {
				break;
			}
		}
	}
	return length;
}

void MGEObjectArray::Exchange(unsigned int i1, unsigned int i2) {
	if ( ( i1 < length ) && ( i2 < length ) ) {
		MGEObject *obj = objects[i1];
		objects[i1] = objects[i2];
		objects[i2] = obj;
	}
}

void MGEObjectArray::Delete(const unsigned int begin, const unsigned int count) {
	CheckThisOut();
	if ( (begin + count) <= length) {
		unsigned int end = begin + count;
		for ( unsigned int i1 = begin ; i1 < end ; i1 ++ ) {
			if ( objects[i1] != NULL ) {
				delete objects[i1];
				objects[i1] = NULL;
			}
		}
	} else {
		for ( unsigned int i1 = begin ; i1 < length ; i1 ++ ) {
			if ( objects[i1] != NULL ) {
				delete objects[i1];
				objects[i1] = NULL;
			}
		}
	}
}

const char *MGEObjectArray::GetClassName() {
	return "MGEObjectArray";
}

BOOL32 MGEObjectArray::IsInstanceof(const char* className) {
	if (strcmp("MGEObjectArray", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGEObjectArray::CheckThisOut() {
	if ( ___this != this ) {
		objects = NULL;
		length = 0;
		objects = new MGEObject*[___this->length];
		length = ___this->length;
		for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
			objects[i1] = ___this->objects[i1];
		}
		___this = this;
	}
}

void MGEObjectArray::Append(const MGEObject *__obj) {
	CheckThisOut();
	if ( length > 0 ) {
		MGEObject **newObjects = new MGEObject*[length + 1];
		memcpy( newObjects, objects, sizeof(MGEObject*) * length );
		newObjects[length] = (MGEObject *)__obj;
		length += 1;
		if (objects!=NULL) {
			delete []objects;
			objects = NULL;
		}
		objects = newObjects;
	} else {
		MGEObject **newObjects = new MGEObject*[1];
		newObjects[0] = (MGEObject *)__obj;
		length = 1;
		objects = newObjects;
	}
	___this = this;
}
