#pragma once

#include <iostream>
#include <fstream>
#include <hash_map>
#include "helpFunctions.h"
#include "DataCache.h"
#include "fileSystemTypeDefs.h"

namespace filesystem {

class DataLoadManager
{
public:
	DataLoadManager(void);
	~DataLoadManager(void);
	FS_STRING & getValueInFile( FS_STRING fileName, FS_STRING key );
	void setValueInFile( FS_STRING fileName, FS_STRING key, FS_STRING value );
	void preloadFile( FS_STRING fileName );
	void saveFile( FS_STRING fileName );
	FS_STRING & getValueInResource( FS_STRING resourceId, FS_STRING key );
	void setValueInResource( FS_STRING resourceId, FS_STRING key, FS_STRING value );
	void preloadResource( FS_STRING resourceId );
	void saveResource( FS_STRING resourceId );
	void addToRegisterRecord( FS_STRING resourceId, FS_STRING fileName );
	void addToRegisterFile( FS_STRING fileName );
	int getSizeCaches(){
		return mCaches.size();
	}
	int getSizeRegister(){
		return mRegister.size();
	}
private:
	FS_STRING & getMappedFileForResource( FS_STRING resourceId );
	std::hash_map<FS_STRING, DataCache> mCaches;
	std::hash_map<FS_STRING, FS_STRING> mRegister;
};

}