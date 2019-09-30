#ifndef _PACKETPARSER_H
#define _PACKETPARSER_H
#include "CommonIncludes.h"
#include "ReaderThread.h"
#include<pcap/pcap.h>
#include<sstream>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<dirent.h>
#include<vector>
#include<net/ethernet.h>
#include<netinet/tcp.h>
#include<arpa/inet.h>
#include<list>
#include<netinet/ether.h>
#include<fstream>
#include<algorithm>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>

using namespace std;

class PacketParser
{
	public:
	
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
		PacketParser();

		~PacketParser(){};

		bool Initialize(string,string);

		void Finalize(string, string);
		
	
	private:
		ReaderThread* mReader[3];

		bool mWriterFinalize;

		bool addToQueue(char*);

		void CallingReaderThread(char*, word32); 

		static void PacketHandler(u_char *userData, const struct pcap_pkthdr* pkthdr,const u_char* packet);

		bool Run(pcap_t*, char*);

		string IntToChar(const u_int16_t );

		queue <char*> PacketQueue;

		bool popFromQueue(){PacketQueue.pop(); return true; };

		char* getQueueFront(){ return PacketQueue.front(); };

		bool pushInQueue(char* packet){PacketQueue.push(packet); return true; };	
};
#endif





/*
		struct etherHeader{
			char* ether_src;
			char* ether_dest;
			char srchostname[32];
			char desthostname[32];
			int ether_type;	
		};
	
		struct ipHeader{
			char* source_ip;
			char* dest_ip;
			//u_char* tos;
			u_int ip_len;
			u_int ip_hlen; 
			u_int off;
			u_int version;
			u_int ip_p;
		};
	
		struct tcpHeader{
			u_int source_port, dest_port;
			u_long seq, ack;
			u_char *data;
			int data_length;
			string data_str;
		};

		struct packet{
			struct etherHeader ether_data;
			struct ipHeader ip_data;
			struct tcpHeader tcp_data;
		};
		*/
