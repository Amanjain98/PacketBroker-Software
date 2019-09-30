#include "PacketParser.h"
#include "ReaderThread.h"
using namespace std;
	
PacketParser::PacketParser() : mWriterFinalize(false)
{
	 for(int i=0;i<4;i++)
		{
			mReader[i] = new ReaderThread(i);
		}
}
	
bool
PacketParser::Initialize(string FileName, string FileLocation)
{
		cout<< "Insisde PacketParser Initialize function" << endl;
		
		char errbuf[PCAP_ERRBUF_SIZE];

		pcap_t* Handle = pcap_open_offline(FileLocation.c_str(),errbuf);
		
		for(int i=0;i<4;i++)
		{
			mReader[i]->Initialize();
		}	
	
		Run(Handle,errbuf);

	return true;
}

string
PacketParser::IntToChar(const u_int16_t value)
{
	ostringstream ss;
	ss<<value;
	string s = ss.str();
	return (s);
}
	
bool
PacketParser::Run(pcap_t* handle, char errbuf[])
{
	int dl_ret = pcap_datalink(handle);
	
	cout<<"datalink return "<<dl_ret <<endl;
	
	if(pcap_loop(handle,-1,PacketParser::PacketHandler,(u_char*)this) < 0)
	{
		cout<< "Pcap loop Failed! "<< endl;
		return true;
	}
	return true;
}

void
PacketParser::PacketHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{		
	PacketParser* parser = (PacketParser*)userData;
    static int count=0; 
    printf("Packet Count: %d\n", ++count);    /* Number of Packets */
    printf("Recieved Packet Size: %d\n", pkthdr->len);    /* Length of header */
    printf("Payload:\n");                     /* And now the data */
    for(unsigned i=0; i<pkthdr->len; i++) 
	{ 
        if(isprint(packet[i]))                /* Check if the packet data is printable */
            {	
				printf("%c ",packet[i]);
			}         						 /* Print it */
                  							 /* If not print a . */
        if((i%16==0 && i!=0) || i==pkthdr->len-1) 
            printf("\n"); 
    }
	parser->addToQueue(((char*)packet));
	parser->CallingReaderThread(((char*)packet), (word32)pkthdr->len);
}
bool PacketParser::addToQueue(char* packet)
{
	pushInQueue(packet);
	return true;
}


void PacketParser::CallingReaderThread(char* packet, word32 bufferlen)
{
		for(int i=0;i<4;i++)
		{
			mReader[i]->addToQueue(packet, bufferlen);
			popFromQueue();
			if(i == 3)
				i = 0;
		}
}

void PacketParser::Finalize(string Path, string FileName)
{
		string File_Name = Path + "/" + FileName;		
		string WritedFilePath = "/home/aarav/Cataleya/WritedFilePath";
		string renamefile = WritedFilePath + "/executed_" + FileName; 
		int rval = rename(File_Name.c_str(),renamefile.c_str());
		cout<< "rename return value "<< renamefile << " " <<rval << endl;
		for(int i=0;i<3;i++)
		{
			mReader[i]->Finalize();
		}
}
