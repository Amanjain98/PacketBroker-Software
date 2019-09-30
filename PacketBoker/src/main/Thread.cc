#include<iostream>
#include<stdio.h>
#include<queue>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include "Thread.h"
#include "PcapFileManager.h"
#include "PacketParser.h"

using namespace std;

//Thread::thread_mutex = PTHREAD_MUTEX_INITIALIZER;

/*Worker::Worker() : mIsFinalized (false)
{
	cout<<"Worker Constructor"<<endl;
	sleep(1);
	for (int i = 0; i < 4; ++i)
	{
		mWorkers[i] = new Worker(i);
	}
}
*/

bool 
Thread::Initialize()
{	
	
	pthread_create(&getThreadListId(),NULL,&Thread::Run,(void*)this);
		
	mIsFinalized = false;
			
	pthread_mutex_init(&thread_mutex, NULL);
	
	parser = new PacketParser();
	
	return true;		
}
/*
ThreadCallBack::Run(void* args)
{
	(Thread*)args->Run();
}*/

void Thread::addToQueue(string FileName)
{	
	
	setMutexLock();
	
	cout<<"Inside addToQueue"<<endl;
	
	setFileName(FileName);
	
	string FileLocation = getPath() + "/" + getFileName();
	
	cout<< "FileLocation" <<FileLocation << endl; 
	
	pushInQueue(FileLocation);
	
	setMutexUnlock();
	
}

void* Thread::Run(void* threadPtr)
{
    Thread* thread = (Thread*)threadPtr;
	
	cout<< "Inside Thread Run Function " << endl;
	while (!thread->getIsFinalized())
	{	
					
		thread->setMutexLock();
		
		if(!thread->IsQueueEmpty())
		{		
			cout<< "Thread Run Function If loop "<< endl;
				
			thread->parser->Initialize(thread->getFileName(),thread->getQueueFront());
		
			thread->parser->Finalize(thread->getPath(), thread->getFileName());
	
			thread->popInQueue();
			
			thread->setMutexUnlock();
				
		}
		
		else 
			thread->setMutexUnlock();		
	}
		return NULL;
	
}

void Thread::Finalize()
{	
		mIsFinalized = true;
		pthread_cancel(getThreadListId());
		pthread_join(getThreadListId(), NULL);
}

