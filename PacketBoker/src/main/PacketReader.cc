#include "CommonIncludes.h"
#include "PacketReader.h"
#include<string.h>
bool PacketReader::Initialize()
{
	message = NULL;
	address = NULL;
	return true;
}
bool PacketReader::Run(char* Packet, word32 bufferlen)
{
	GetFromDisplayTag(Packet,bufferlen);
	GetToTag(Packet,bufferlen);
	GetCallId(Packet,bufferlen);
	//setHashing(FromTag, ToTag);
	return true;
	
}

bool PacketReader::GetFromDisplayTag(char* buffer, word32 bufferlen)
{	
	message.getFromAddressSpec(address);
	address.getUser(buffer,bufferlen);
	printf("%s", buffer);	
	return true;
}

bool PacketReader::GetToTag(char* buffer, word32 bufferlen)
{
	message.getToAddressSpec(address);
	address.getHost(buffer, bufferlen);
	return true;
}

bool PacketReader::GetCallId(char* buffer, word32 bufferlen)
{
	message.getCallId(buffer,bufferlen);
	return true;
}
/*
bool PacketReader::setHashing(string FromTag, string ToTag)
{
	return true;
}
*/
bool PacketReader::Finalize()
{
	//AppSipStackDestruct();
	return true;
}
