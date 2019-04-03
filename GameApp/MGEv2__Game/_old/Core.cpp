///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//
//		MGE Game Core
//		
//		Total Control Unit
//
///////////////////////////////////////////////////////////////////


#include "string.h"

#undef GetClassName
#undef PostMessage

//#include "string.h"
#include "../MGE_File/File.h"
#include "../MGE_File/FileStream.h"
#include "MessageProc.hpp"
#include "Core.hpp"


MGEGameCore::MGEGameCore() {
	messageQueue.Resize(128);
	queueHead = 0;
	queueTail = 0;
	queueLength = messageQueue.GetLength();
	queueRWLock.AttribInit();
	queueRWLock.Init();
}
MGEGameCore::~MGEGameCore() {
	queueRWLock.Unlock();
	queueRWLock.Destroy();
	queueRWLock.AttribDestroy();
	messageQueue.Resize(0);
}
const char *MGEGameCore::GetClassName() {
	return "MGEGameCore";
}

BOOL32 MGEGameCore::IsInstanceof(const char* className) {
	if (strcmp("MGEGameCore", className)) {
		return TRUE;
	}
	return FALSE;
}

void MGEGameCore::Run() {
	MGEMessage msg;
	while(TRUE) {
		if ( queueHead != queueTail ) {
			queueRWLock.ReadLock();
			msg = messageQueue[queueTail];
			queueTail ++;
			queueTail = queueTail % queueLength;
			queueRWLock.Unlock();
			MessageHandler(msg);
		}
		Delay(0, interval);
	}
}
void MGEGameCore::PostMessage(MGEMessage &msg) {
	if ( queueTail == ( ( queueHead + 1 ) % queueLength ) ) {
		Delay(0, interval);
	} else {
		queueRWLock.WriteLock();
		messageQueue[queueHead] = msg;
		queueHead ++;
		queueHead = queueHead % queueLength;
		queueRWLock.Unlock();
	}
}
void MGEGameCore::MessageHandler(MGEMessage &msg) {
	MGE2MessageProcessor::MessageHandler(msg);
}


void MGEGameCore::LoadConfigFile(MGEString &fn, MGEConfigFile &cf) {
	char fileName[256];
	fn.GetStringASC(fileName);
	MGEFile fd;
	fd.SetFilePathName(fileName);
	fd.SetOpenMode(MGEFile::modeRead | MGEFile::typeBinary);
	fd.Open();
	MGEFileStream fdio;
	fdio.SetFile(&fd);
	fdio.SetEndian(MGEFileStream::little_endian);
	fdio.SetLoadStore(MGEFileStream::load);
	cf.Serialize(fdio);
	fdio.Close();
	fd.Close();
}
void MGEGameCore::LoadShader(MGEConfigFile &cf) {
}
