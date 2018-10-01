#pragma once

#include <iostream>
#include "BitStream.h"

#define NS_STRING std::string
#define NS_INT int
#define NS_FLOAT float
#define NS_MESSAGE_TYPE unsigned char 
#define NS_GUID RakNet::RakNetGUID
#define NS_TO_ALL_GUID RakNet::UNASSIGNED_RAKNET_GUID
#define NS_FROM_NONE_GUID RakNet::UNASSIGNED_RAKNET_GUID

#define NS_SERIALIZE_STREAM RakNet::BitStream
#define NS_WRITE(stream,data) stream->Write(data)
#define NS_READ(stream,data) stream->Read(data)