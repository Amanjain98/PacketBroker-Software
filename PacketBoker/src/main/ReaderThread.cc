#include "CommonIncludes.h"
#include "ReaderThread.h"
#include<queue>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include "PacketReader.h"

using namespace std;

bool 
ReaderThread::Initialize()
{	
	
	pthread_create(&getThreadListId(),NULL,&ReaderThread::Run,(void*)this);
		
	mIsFinalized = false;
			
	pthread_mutex_init(&thread_mutex, NULL);
	
	readerparser = new PacketReader();
	
	readerparser->Initialize();
	
	return true;		
}

void ReaderThread::addToQueue(char* packet, int bufferlen)
{	
	
	setMutexLock();
		
	setBufferLen(bufferlen);

	pushInQueue(packet);
	
	setMutexUnlock();
	
}

void* ReaderThread::Run(void* threadPtr)
{
    ReaderThread* readerThread = (ReaderThread*)threadPtr;
	
	while (!readerThread->getIsFinalized())
	{						
		readerThread->setMutexLock();
		
		if(!readerThread->IsQueueEmpty())
		{				
			readerThread->readerparser->Run(readerThread->getQueueFront(), readerThread->getBufferLen());
	
			readerThread->popInQueue();
			
			readerThread->setMutexUnlock();
		}
		else 
			readerThread->setMutexUnlock();		
	}
		return NULL;
}
	
void ReaderThread::Finalize()
{	
		mIsFinalized = true;
		pthread_cancel(getThreadListId());
		pthread_join(getThreadListId(), NULL);
		readerparser->Finalize();
}
