#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <hash_map>
#include "Logger.h"

namespace simpleclient {

class SimpleSoundResolvedResourcesContainer
{
public:
	SimpleSoundResolvedResourcesContainer(void);
	~SimpleSoundResolvedResourcesContainer(void);
	COMMON_STRING * getAddress( COMMON_STRING & resourceId, COMMON_STRING & soundId );
	void addAddress( COMMON_STRING & resourceId, COMMON_STRING & soundId,  COMMON_STRING & address );
private:
	std::hash_map<COMMON_STRING, COMMON_STRING> mData;
};

}