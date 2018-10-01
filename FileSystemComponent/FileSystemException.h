#pragma once

#include <iostream>
#include "fileSystemTypeDefs.h"

namespace filesystem {

class FileSystemException
{
public:
	FileSystemException(void);
	FileSystemException( FS_STRING mess );
	FileSystemException( FS_STRING fileName, FS_STRING mess );
	~FileSystemException(void);
	FS_STRING & getMessage();
private:
	FS_STRING message;
};

}