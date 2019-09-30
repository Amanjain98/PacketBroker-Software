#include "CommonIncludes.h"
#include "PcapFileManager.h"

using namespace std;


int main(int argc, char** argv)
{
	
	PcapFileManager *pcapfilemanager = pcapfilemanager->GetInstance();

	pcapfilemanager->Initialize(argv);

	printf("main end\n");
	return 0;
}
