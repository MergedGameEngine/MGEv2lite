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


MGEHashtable::MGEHashtable() {
	for (int i = 0 ; i < ONE_BLOCK_SIZE ; i ++ ) {
		items[i].keyHash = 0;
		items[i].obj = NULL;
	}
	itemCount = 0;
	nextTable = NULL;
}

MGEHashtable::~MGEHashtable() {
	if ( nextTable != NULL ) {
		delete nextTable;
	}
}


BOOL32 MGEHashtable::Add(MGEString &key, const MGEObject *obj) {
	if (key.GetHashCode() == 0) {
		return FALSE;
	}
	if (obj == NULL) {
		return FALSE;
	}
	const MGEObject *object = Get(key);
	if (object == NULL) {
		if (itemCount == ONE_BLOCK_SIZE) {
			if (nextTable == NULL) {
				nextTable = new MGEHashtable();
			}
			return nextTable->Add(key, obj);
		}
	} else {
		return FALSE;	//	Already has
	}
	unsigned int i = 0;
	for (i = 0 ; i < ONE_BLOCK_SIZE ; i ++ ) {
		if(items[i].keyHash == 0) {
			break;
		}
	}
	items[i].key = key;
	items[i].keyHash = key.GetHashCode();
	items[i].obj = (MGEObject*)obj;
	itemCount ++;
	return TRUE;
}


const MGEObject *MGEHashtable::Get(MGEString &key) {
	int keyHash = key.GetHashCode();
	if ( keyHash == 0 ) {
		return NULL;
	}
	for (unsigned int i = 0 ; i < ONE_BLOCK_SIZE ; i ++) {
		if ( keyHash == items[i].keyHash ) {
			if (items[i].key.Equals(key)) {
				return items[i].obj;
			}
		}
	}
	if (nextTable != NULL) {
		return nextTable->Get(key);
	}
	return NULL;
}



BOOL32 MGEHashtable::Set(MGEString &key, const MGEObject *obj) {
	if (obj == NULL) {
		return FALSE;
	}
	int keyHash = key.GetHashCode();
	if ( keyHash == 0 ) {
		return FALSE;
	}
	for (unsigned int i = 0 ; i < ONE_BLOCK_SIZE ; i++) {
		if ( keyHash == items[i].keyHash ) {
			if (items[i].key.Equals(key)) {
				items[i].obj = (MGEObject*)obj;
				return TRUE;
			}
		}
	}
	if (nextTable != NULL) {
		return nextTable->Set(key, obj);
	}
	return FALSE;
}

BOOL32 MGEHashtable::Add(const char *_str, const MGEObject *obj) {
	MGEString _key(_str);
	return Add(_key, obj);
}

const MGEObject *MGEHashtable::Get(const char *_str) {
	MGEString _key(_str);
	return Get(_key);
}

BOOL32 MGEHashtable::Set(const char *_str, const MGEObject *obj) {
	MGEString _key(_str);
	return Set(_key, obj);
}

BOOL32 MGEHashtable::Del(MGEString &key) {
	int keyHash = key.GetHashCode();
	if ( keyHash == 0 ) {
		return FALSE;
	}
	for (unsigned int i = 0 ; i < ONE_BLOCK_SIZE ; i++) {
		if ( keyHash == items[i].keyHash ) {
			if (items[i].key.Equals(key)) {
				items[i].key = "";	//	Empty String
				items[i].keyHash = 0;
				items[i].obj = NULL;
				itemCount --;
				return TRUE;
			}
		}
	}
	if (nextTable != NULL) {
		return nextTable->Del(key);
	}
	return FALSE;
}

BOOL32 MGEHashtable::Del(const char *_str) {
	MGEString _key(_str);
	return Del(_key);
}

unsigned int MGEHashtable::GetCount() {
	unsigned int sum = itemCount ;
	if (nextTable != NULL) {
		return sum + nextTable->GetCount();
	}
	return sum;
}

MGEObject *&MGEHashtable::operator[](MGEString &key) {
	int keyHash = key.GetHashCode();
	if ( keyHash == 0 ) {
		return *(MGEObject**)NULL;
	}
	for (unsigned int i = 0 ; i < ONE_BLOCK_SIZE ; i ++) {
		if ( keyHash == items[i].keyHash ) {
			if (items[i].key.Equals(key)) {
				return items[i].obj;
			}
		}
	}
	if (nextTable != NULL) {
		return (*nextTable)[key];
	}
	return *(MGEObject**)NULL;
}

MGEHashitem *MGEHashtable::NextEmptyItem(unsigned int &index, MGEHashtable *&loc) {
	MGEHashtable *curtab = this;
	while (curtab != NULL) {
		for (unsigned int i1 = index ; i1 <  ONE_BLOCK_SIZE ; i1 ++) {
			if ( curtab->items[i1].keyHash == 0 ) {
				loc = curtab;
				index = i1;
				return &curtab->items[i1];
			}
		}
		curtab = curtab->nextTable;
	}
	return NULL;
}
MGEHashitem *MGEHashtable::NextNonEmptyItem(unsigned int &index, MGEHashtable *&loc) {
	MGEHashtable *curtab = this;
	while (curtab != NULL) {
		for (unsigned int i1 = index ; i1 <  ONE_BLOCK_SIZE ; i1 ++) {
			if ( curtab->items[i1].keyHash != 0 ) {
				loc = curtab;
				index = i1;
				return &curtab->items[i1];
			}
		}
		curtab = curtab->nextTable;
	}
	return NULL;
}

unsigned int MGEHashtable::Pack() {
	MGEHashitem *packhead = NULL;
	MGEHashitem *packtail = NULL;
	MGEHashtable *lpackhead = this;
	MGEHashtable *lpacktail = this;
	for ( unsigned int i0 = 0, i1 = 0, i2 = 0 ; i0 < ONE_BLOCK_SIZE ; i0 ++ ) {
		lpackhead = this;
		if ( lpackhead->itemCount == ONE_BLOCK_SIZE ) {
			break;
		}
		packhead = NextEmptyItem(i1, lpackhead);
		i2 = i1;
		lpacktail = lpackhead;
		packtail = lpacktail->NextNonEmptyItem(i2, lpacktail);
		if ( ( packhead != NULL ) && ( packtail != NULL ) ) {
			packhead->key = packtail->key; packtail->key = MGEString();
			packhead->keyHash = packtail->keyHash; packtail->keyHash = 0;
			packhead->obj = packtail->obj; packtail->obj = NULL;
			packhead->objHash = packtail->objHash; packtail->objHash = 0;
			lpackhead->itemCount ++;
			lpacktail->itemCount --;
		}
	}
	if ( nextTable != NULL ) {
		nextTable->Pack();
	}
	MGEHashtable *nt = this;
	while ( nt->nextTable != NULL ) {
		if ( nt->nextTable->itemCount == 0 ) {
			delete nt->nextTable;
			nt->nextTable = NULL;
		} else {
			nt = nt->nextTable;
		}
	}
	return GetCount();
}

const char *MGEHashtable::GetClassName() {
	return "MGEHashtable";
}

int MGEHashtable::GetHashCode() {
	int hashCode = (int)CRC32::GetCRC32(items, sizeof(MGEHashitem)*ONE_BLOCK_SIZE);
	if (nextTable != NULL) {
		hashCode = hashCode ^ nextTable->GetHashCode();
	}
	return hashCode;
}

BOOL32 MGEHashtable::IsInstanceof(const char* className) {
	if ( strcmp(className, "MGEHashtable") == 0 ) {
		return TRUE;
	}
	return FALSE;
}
	
unsigned int MGEHashtable::GetKeyValuePair(MGEObjectArray &__keys, MGEObjectArray &__objs) {
	unsigned int _count = 0; 
	for ( unsigned int i0 = 0 ; i0 < ONE_BLOCK_SIZE ; i0 ++ ) {
		if ( items[i0].obj != NULL ) {
			MGEString *__str = new MGEString();
			*__str = items[i0].key;
			__keys.Append(__str);
			__objs.Append(items[i0].obj);
			_count ++;
		}
	}
	unsigned int _sum = _count;
	if ( nextTable != NULL ) {
		_sum += nextTable->GetKeyValuePair(__keys, __objs);
	}
	return _sum;
}

void MGEHashtable::DeleteAll() {
	unsigned int _count = 0; 
	for ( unsigned int i0 = 0 ; i0 < ONE_BLOCK_SIZE ; i0 ++ ) {
		if ( items[i0].obj != NULL ) {
			items[i0].key = "";
			delete items[i0].obj;
			items[i0].obj = NULL;
		}
	}
	if ( nextTable != NULL ) {
		nextTable->DeleteAll();
		delete nextTable;
		nextTable = NULL;
	}
}

void MGEHashtable::CopyHashtable(MGEHashtable &_ht) {
	unsigned int _count = 0; 
	for ( unsigned int i0 = 0 ; i0 < ONE_BLOCK_SIZE ; i0 ++ ) {
		if ( items[i0].obj != NULL ) {
			_ht.Add(items[i0].key, items[i0].obj);
			///_ht.items[i0].key = items[i0].key;
			///_ht.items[i0].obj = items[i0].obj;
			///_ht.itemCount ++;
		}
	}
	if ( nextTable != NULL ) {
		_ht.nextTable = new MGEHashtable();
		nextTable->CopyHashtable(*(_ht.nextTable));
	} else {
		_ht.nextTable = NULL;
	}
}
