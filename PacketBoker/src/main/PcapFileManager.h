#ifndef _PCAPFILEMANAGER_H
#define _PCAPFILEMANAGER_H
#include "CommonIncludes.h"
#include "Thread.h"
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<queue>
#include<dirent.h>
#include<vector>
#include<algorithm>
#include<sys/stat.h>
#include<time.h>
#include<signal.h>	

using namespace std;
class PcapFileManager
{
	public:
		virtual ~PcapFileManager() {};
		struct FileNameModificationDateComparator
		{
			bool operator() (const std::string& lhs, const std::string& rhs)
			{
				struct stat attribLhs;
				struct stat attribRhs;  //File attribute structs
				stat( lhs.c_str(), &attribLhs);
				stat( rhs.c_str(), &attribRhs);                      
				return attribLhs.st_mtime < attribRhs.st_mtime;
			}
		};
		//void signal_callback_handler(int);
		DIR *dir; 
		static PcapFileManager* GetInstance();
		bool Initialize(char**);
		void Finalize();
		
		pthread_t& getThreadId() { return mThreadId; }
		bool getIsFinalized() { return mIsFinalized; }
		Thread* getThread(int32_t i) { if (i > 3) return NULL; return mThread[i]; }
		
		void setIsFinalized(bool val) { mIsFinalized = val; }
		void addTask(string);
		void ReadDir(char** argv);
		vector<string> FilesList;


	private:
		PcapFileManager();
		Thread* mThread[4];
		pthread_t mThreadId;
		static PcapFileManager* mpInstance;
		bool mIsFinalized;
		int mThreadCount;
		bool threadInitializer();
		
};

#endif
