#pragma once

#include "DataLoadManager.h"
#include "fileSystemTypeDefs.h"
#include "helpFunctions.h"

namespace filesystem {

class FileSystemFacade
{
public:
	static FileSystemFacade * INSTANCE();
	~FileSystemFacade(void);

	FS_STRING & getValueInFile( FS_STRING fileName, FS_STRING key );
	FS_STRING & getValueInResource( FS_STRING resourceId, FS_STRING key );
	int getIntInFile( FS_STRING fileName, FS_STRING key );
	int getIntInResource( FS_STRING resourceId, FS_STRING key );
	float getFloatInFile( FS_STRING fileName, FS_STRING key );
	float getFloatInResource( FS_STRING resourceId, FS_STRING key );
	bool getBoolInFile( FS_STRING fileName, FS_STRING key );
	bool getBoolInResource( FS_STRING resourceId, FS_STRING key );

	void setValueInFile( FS_STRING fileName, FS_STRING key, FS_STRING value );
	void preloadFile( FS_STRING fileName );
	void saveFile( FS_STRING fileName );
	
	void setValueInResource( FS_STRING resourceId, FS_STRING key, FS_STRING value );
	void preloadResource( FS_STRING resourceId );
	void saveResource( FS_STRING resourceId );

	void addToRegisterRecord( FS_STRING resourceId, FS_STRING fileName );
	void addToRegisterFile( FS_STRING fileName );

private:
	FileSystemFacade(void);
	static FileSystemFacade * pInstance;
	DataLoadManager * manager;
};

}