#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <hash_map>
#include "helpFunctions.h"
#include "FileSystemException.h"
#include "fileSystemTypeDefs.h"

namespace filesystem {

class DataCache
{
public:
	DataCache( FS_STRING fileName );
	~DataCache(void);
	FS_STRING & getValue( FS_STRING & key );
	void setValue( FS_STRING & key, FS_STRING & value );
	void saveToFile();
	int getCacheLevel();
private:
	int mCacheLevel;
	FS_STRING mFileName;
	std::hash_map<FS_STRING, FS_STRING> mData;
	void load();
};

}