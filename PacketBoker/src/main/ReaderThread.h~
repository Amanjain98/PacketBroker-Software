#ifndef READERTHREAD_H
#define READERTHREAD_H
#include<iostream>
#include<string.h>
#include<pthread.h>
#include<queue>
#include "PacketReader.h"
using namespace std;
/*
class TheadCallBack{
	ThreadCallBack();
	~virtual ThreadCallBack();
	virtual void Run() = 0;
}*/
class ReaderThread
{
	
   	 public:
	    
	    	ReaderThread(int threadId) : mThreadId (threadId), mThreadListId (0), mIsFinalized(false), readerparser(0),mThreadCount(0){};
	    
	    	~ReaderThread(){delete readerparser;};
	    
	    	static void* Run(void *);
	    
	    	bool  Initialize();
        
        	void  Finalize();
        
        	void  addToQueue(char*, int);
        
        	void  setIsFinalized(bool val) { mIsFinalized = val;}
        
        	bool  getIsFinalized() { return mIsFinalized; }
        
        	char* getQueueFront()
        	{
        		return threadqueue.front();
        	}
        
        	void  pushInQueue(char* Packet){threadqueue.push(Packet);}
        
        	bool IsQueueEmpty(){return threadqueue.empty();}
        
        	void  popInQueue(){ threadqueue.pop(); }
        
        	int   getThreadId() { return mThreadId; }
		
			int  setMutexLock(){return pthread_mutex_lock(&thread_mutex);}
        
        	int  setMutexUnlock(){return pthread_mutex_unlock(&thread_mutex);}
	
			bool  setBufferLen(word32 bufferLen){ bufferlen = bufferLen; return true;};

			word32   getBufferLen(){ return bufferlen;};
	
		//Thread* getThread(int32_t i) { if (i str> 3) return NULL; return mWorkers[i]; }
                                                                                              
	private:	
		int bufferlen;		
		
		int  mThreadId;
			
		pthread_t mThreadListId;
		
		bool mIsFinalized;

		PacketReader* readerparser;
		
		int mThreadCount;	
		
		queue <char*> threadqueue;
		
		pthread_mutex_t thread_mutex;
		
		pthread_t& getThreadListId(){return mThreadListId;}
        
};

/*
typedef struct Queue
{
        int capacity;
        int size;
        int front;
        int rear;
        char **elements;
} mDQueue;

Queue * createQueue(int maxElements)
{
        Queue *Q;
        Q = (Queue *)malloc(sizeof(Queue));
        Q->elements = (char**)malloc(sizeof(char*)*maxElements);
        Q->size = 0;
        Q->capacity = maxElements;
        Q->front = 0;
        Q->rear = -1;
        return Q;
}
*/
#endif
