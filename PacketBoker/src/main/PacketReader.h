#ifndef PACKETREADER_H
#define PACKETREADER_H
#include "CommonIncludes.h"
#include "SipMessage.h"
#include "SipAddress.h"
#include "SipCommon.h"


class PacketReader{	
	public:
		bool Initialize();
		bool GetFromDisplayTag(char*,word32);
        bool GetToTag(char*,word32);
        bool GetCallId(char*, word32);
		bool Finalize();
		bool Run(char*,word32);
	private:
		string FromTag;
		string ToTag;
		string CallIDTag;
		RvSipStackCfg stackCfg;
		RvSipStackHandle hStack;
		SipMessage message;
		SipAddress address;
  	    //bool setHashing(string, string, string);
		
};

#endif
