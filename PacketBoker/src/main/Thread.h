#ifndef THREAD_H
#define THREAD_H
#include<iostream>
#include<string.h>
#include<pthread.h>
#include<queue>
#include "PacketParser.h"
using namespace std;
/*
class TheadCallBack{
	ThreadCallBack();
	~virtual ThreadCallBack();
	virtual void Run() = 0;
}*/
class Thread
{
	
   	 public:
				    
	    	Thread(int threadId) : mThreadId (threadId), mThreadListId (0), mIsFinalized(false), mThreadCount(0), parser(NULL){};
	    
	    	~Thread(){delete parser;};		    
	    	
			static void* Run(void *);
	    
	    	bool  Initialize();
        
        	void  Finalize();
        
        	void  addToQueue(string);
        
        	void  setIsFinalized(bool val) { mIsFinalized = val;}
        
        	bool  getIsFinalized() { return mIsFinalized; }
        
        	std::string getQueueFront()
        	{
        		return threadqueue.front();
        	}
        	string Path, FileName;
        
        	void  pushInQueue(string FileLocation){threadqueue.push(FileLocation);}
        
        	bool IsQueueEmpty(){return threadqueue.empty();}
        
        	void  popInQueue(){ threadqueue.pop(); }
        
        	int   getThreadId() { return mThreadId; }
		
		int  setMutexLock(){return pthread_mutex_lock(&thread_mutex);}
        
        	int  setMutexUnlock(){return pthread_mutex_unlock(&thread_mutex);}
        
		string getPath(){return Path;};
		
		void setPath(string val){Path = val;};
		
		string getFileName(){return FileName;};
		
		void setFileName(string val){FileName = val;};

		//Thread* getThread(int32_t i) { if (i str> 3) return NULL; return mWorkers[i]; }
                                                                                              
	private:	
		int  mThreadId;
			
		pthread_t mThreadListId;
		
		bool mIsFinalized;
		
		int mThreadCount;	
				
		PacketParser* parser;
		
		queue <string> threadqueue;
		
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
