#include "FileSystemException.h"

namespace filesystem {

FileSystemException::FileSystemException(void) : message( "default error" )
{
}

FileSystemException::FileSystemException( FS_STRING mess ) : message( mess )
{
}

FileSystemException::FileSystemException( FS_STRING fileName, FS_STRING mess ) : message( "File [" )
{
	message.append( fileName );
	message.append( "]. " );
	message.append( mess );
}

FileSystemException::~FileSystemException(void)
{
}

FS_STRING & FileSystemException::getMessage()
{
	return message;
}

}