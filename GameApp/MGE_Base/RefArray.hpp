///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _REFARRAY_HPP_
#define _REFARRAY_HPP_

//template <typename T> _ARRAY_API TRefArray<T>::TRefArray<T>() {
template <typename T> MGERefArray<T>::MGERefArray() {
	references = NULL;
	length = 0;
	___this = this;
}

//template <typename T> _ARRAY_API TRefArray<T>::TRefArray<T>(unsigned int size) {
template <typename T> MGERefArray<T>::MGERefArray(unsigned int size) {
	references = new T*[size];
	length = size;
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		references[i1] = NULL;
	}
	___this = this;
}

//template <typename T> _ARRAY_API TRefArray<T>::~TRefArray<T>() {
template <typename T> MGERefArray<T>::~MGERefArray() {
	if ( ___this == this ) {
		if (references!=NULL) {
			delete []references;
			references = NULL;
		}
	} else {
	}
}

template <typename T> void MGERefArray<T>::Resize(unsigned int size) {
	CheckThisOut();
	if (size > 0) {
		T **newReferences = new T*[size];
		if (size < length) {
			memcpy(newReferences, references, sizeof(T*) * size);
		} else {
			if (references != NULL) {
				memcpy(newReferences, references, sizeof(T*) * length);
			}
			for ( unsigned int i1 = length ; i1 < size ; i1 ++ ) {
				newReferences[i1] = NULL;
			}
		}
		if (references != NULL) {
			delete []references;
			references = NULL;
		}
		references = newReferences;
		length = size;
	} else {
		if (references != NULL) {
			delete []references;
			references = NULL;
		}
		length = 0;
	}
}

template <typename T> T &MGERefArray<T>::operator[](unsigned int index) {
	if (index < length) {
		return *(references[index]);
	} else {
		return *(T*)NULL;
	}
}

template <typename T> MGERefArray<T> MGERefArray<T>::operator + (const MGERefArray<T> &src) {
	MGERefArray<T> desc(length + src.length);
	memcpy(desc.references, references, sizeof(T*) * length);
	memcpy(&(desc.references[length]), src.references, sizeof(T*) * src.length);
	desc.___this = 0;
	return desc;
}

template <typename T> MGERefArray<T> &MGERefArray<T>::operator = (const MGERefArray<T> &src) {
	if ( this != &src ) {
		if ( ___this == this ) {
			if (references != NULL) {
				delete []references;
				references = NULL;
			}
		}
		if (src.references != NULL) {
			if (src.___this == 0) {
				references = src.references;
				memset((void *)&(src.references), 0, sizeof(references));
			} else {
				references = new T*[src.length];
				memcpy (references, src.references, src.length * sizeof(T*));
			}
		}
		length = src.length;
	}
	___this = this;
	return *this;
}

template <typename T> MGERefArray<T> &MGERefArray<T>::operator += (const MGERefArray<T> &src) {
	if ( src.length > 0 ) {
		T **newReferences = new T*[length + src.length];
		memcpy( newReferences, references, sizeof(T*) * length );
		memcpy( &(newReferences[length]), src.references, sizeof(T*) * src.length);
		length += src.length;
		if ( ___this == this ) {
			if (references != NULL) {
				delete []references;
				references = NULL;
			}
		}
		references = newReferences;
	}
	___this = this;
	return *this;
}

template <typename T> MGERefArray<T> MGERefArray<T>::SubArray(const unsigned int begin, const unsigned int count) {
	MGERefArray des;
	if ((begin + count) <= length) {
		des.Resize(count);
		memcpy(des.references, &(references[begin]), sizeof(T*) * count);
	}
	des.___this = 0;
	return des;
}

template <typename T> unsigned int MGERefArray<T>::GetLength() {
	return length;
}

template <typename T> void MGERefArray<T>::Set(unsigned int index, T* ref) {
	CheckThisOut();
	if ( index < length ) {
		references[index] = ref;
	}
}

template <typename T> void MGERefArray<T>::Exchange(unsigned int i1, unsigned int i2) {
	CheckThisOut();
	if ( ( i1 < length ) && ( i2 < length ) ) {
		T *ref = references[i1];
		references[i1] = references[i2];
		references[i2] = ref;
	}
}

template <typename T> unsigned int MGERefArray<T>::Pack() {
	CheckThisOut();
	for ( unsigned int i0 = 0 , i1 = 0 , i2 = 0; i2 < length ; i0 ++ ) {
		if ( references[i1] == NULL ) {
			if ( i1 > i2 ) {
				i2 = i1 + 1;
			}
			if ( references[i2] != NULL ) {
				references[i1] = references[i2]; references[i2] = NULL;
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

template <typename T> void MGERefArray<T>::DeleteAll() {
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		if ( references[i1] != NULL ) {
			delete references[i1];
			references[i1] = NULL;
		}
	}
}

template <typename T> void MGERefArray<T>::Delete(const unsigned int begin, const unsigned int count) {
	CheckThisOut();
	if ( (begin + count) <= length) {
		unsigned int end = begin + count;
		for ( unsigned int i1 = begin ; i1 < end ; i1 ++ ) {
			if ( references[i1] != NULL ) {
				delete references[i1];
				references[i1] = NULL;
			}
		}
	} else {
		for ( unsigned int i1 = begin ; i1 < length ; i1 ++ ) {
			if ( references[i1] != NULL ) {
				delete references[i1];
				references[i1] = NULL;
			}
		}
	}
}

template <typename T> void MGERefArray<T>::CreateAll() {
	CheckThisOut();
	for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
		references[i1] = new T();
	}
}

template <typename T> void MGERefArray<T>::Create(const unsigned int begin, const unsigned int count) {
	CheckThisOut();
	if ( (begin + count) <= length) {
		unsigned int end = begin + count;
		for ( unsigned int i1 = begin ; i1 < end ; i1 ++ ) {
			references[i1] = new T();
		}
	} else {
		for ( unsigned int i1 = begin ; i1 < length ; i1 ++ ) {
			references[i1] = new T();
		}
	}
}

template <typename T> void MGERefArray<T>::CheckThisOut() {
	if ( ___this == 0 ) {
	} else
	if ( ___this != this ) {
		references = NULL;
		length = 0;
		references = new T*[___this->length];
		length = ___this->length;
		for ( unsigned int i1 = 0 ; i1 < length ; i1 ++ ) {
			references[i1] = ___this->references[i1];
		}
		___this = this;
	} else {
	}
}


template <typename T> const char *MGERefArray<T>::GetClassName() {
	return "MGERefArray";
}

template <typename T> BOOL32 MGERefArray<T>::IsInstanceof(const char* className) {
	if (strcmp("MGERefArray", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

#endif