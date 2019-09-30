#include "CommonIncludes.h"
#include "PcapFileManager.h"
#include "Thread.h"

using namespace std;

PcapFileManager *PcapFileManager::mpInstance = NULL;


PcapFileManager::PcapFileManager() : mIsFinalized (false), mThreadCount(0)
{
	for (int i = 0; i < 4; ++i)
	{
		mThread[i] = new Thread(i);
	}
}

void signal_callback_handler(int signo)
{
	PcapFileManager *pcapfilemanager = pcapfilemanager->GetInstance();
	if (signo == SIGINT)
    	{
			cout<<"Received SIGINT"<<endl;;
			pcapfilemanager->Finalize();		
		}
	else
		if(signo == SIGQUIT)
			{
				cout<<"Terminal Exit"<<endl;
				pcapfilemanager->Finalize();		
		}
	else
		if(signo == SIGSTOP)
			{
				cout<<"Execution Stopped"<<endl;
				pcapfilemanager->Finalize();		
		}
}

void PcapFileManager::ReadDir(char** argv)
{
	FilesList.clear();
	while(!mIsFinalized)
	{										
		struct dirent *entry;
		if((dir = opendir(argv[1])) != NULL)
		{	
			while((entry = readdir(dir)) != NULL)
			{
				if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
					{
						cout<<entry->d_name<<endl;
						FilesList.push_back(entry->d_name);
					}
			
			} 
		}
		
		vector <string>::iterator iter = FilesList.begin();

		for(iter = FilesList.begin(); iter != FilesList.end(); iter++)
		{	
			addTask(*iter);	
		}
			
		if(signal(SIGINT, signal_callback_handler) == SIG_ERR)		
			Finalize();
		sleep(5);
	}
}

bool
PcapFileManager::Initialize(char** argv)
{	
	for(int i=0;i<4;i++)
		{	
			getThread(i)->setPath(argv[1]);
			getThread(i)->Initialize();			
		}
		
	ReadDir(argv);		
	return true;
}

PcapFileManager*
PcapFileManager::GetInstance()
{	
	if(!mpInstance)
	{
		mpInstance = new PcapFileManager();
	}
	return mpInstance;
}
					
void
PcapFileManager::addTask(string FileName)
{	
		PcapFileManager* pcapfilemanager = pcapfilemanager->GetInstance();
		
		pcapfilemanager->getThread(mThreadCount)->addToQueue(FileName);
		
		pcapfilemanager->mThreadCount++;
		
		if(pcapfilemanager->mThreadCount > 3)
			pcapfilemanager->mThreadCount = 0;
}

void PcapFileManager::Finalize()
{
		mIsFinalized = true;
		
		cout<<"In PcapFileManger Finalize "<< endl;
		
		for(int i=0; i<4; i++)
		{
			getThread(i)->Finalize();
		}			
		cout<<"In PcapFileManager after for loop"<<endl;
		closedir(dir);
		FilesList.clear();
}
