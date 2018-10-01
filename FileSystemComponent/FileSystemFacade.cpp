#include "FileSystemFacade.h"

namespace filesystem {

FileSystemFacade * FileSystemFacade::pInstance = 0;

FileSystemFacade * FileSystemFacade::INSTANCE(){
	if ( pInstance == 0 ) {
		pInstance = new FileSystemFacade();
	}
	return pInstance;
}

FileSystemFacade::FileSystemFacade(void)
{
	manager = new DataLoadManager();
}


FileSystemFacade::~FileSystemFacade(void)
{
	delete (manager);
}

FS_STRING & FileSystemFacade::getValueInFile( FS_STRING fileName, FS_STRING key )
{
	return manager->getValueInFile( fileName, key );
}

int FileSystemFacade::getIntInFile( FS_STRING fileName, FS_STRING key )
{
	return StringToNumber<int>( manager->getValueInFile( fileName, key ) );
}

float FileSystemFacade::getFloatInFile( FS_STRING fileName, FS_STRING key )
{
	return StringToNumber<float>( manager->getValueInFile( fileName, key ) );
}

bool FileSystemFacade::getBoolInFile( FS_STRING fileName, FS_STRING key )
{
	return (manager->getValueInFile( fileName, key ) == "true");
}

void FileSystemFacade::setValueInFile( FS_STRING fileName, FS_STRING key, FS_STRING value )
{
	manager->setValueInFile(fileName, key, value);
}

void FileSystemFacade::preloadFile( FS_STRING fileName )
{
	manager->preloadFile( fileName );
}

void FileSystemFacade::saveFile( FS_STRING fileName )
{
	manager->saveFile( fileName );
}

FS_STRING & FileSystemFacade::getValueInResource( FS_STRING resourceId, FS_STRING key )
{
	return manager->getValueInResource( resourceId, key );
}

int FileSystemFacade::getIntInResource( FS_STRING resourceId, FS_STRING key )
{
	return StringToNumber<int>( manager->getValueInResource( resourceId, key ) );
}

float FileSystemFacade::getFloatInResource( FS_STRING resourceId, FS_STRING key )
{
	return StringToNumber<float>( manager->getValueInResource( resourceId, key ) );
}

bool FileSystemFacade::getBoolInResource( FS_STRING fileName, FS_STRING key )
{
	return (manager->getValueInResource( fileName, key ) == "true");
}

void FileSystemFacade::setValueInResource( FS_STRING resourceId, FS_STRING key, FS_STRING value )
{
	manager->setValueInResource( resourceId, key, value );
}

void FileSystemFacade::preloadResource( FS_STRING resourceId )
{
	manager->preloadResource( resourceId );
}

void FileSystemFacade::saveResource( FS_STRING resourceId )
{
	manager->saveResource( resourceId );
}

void FileSystemFacade::addToRegisterRecord( FS_STRING resourceId, FS_STRING fileName )
{
	manager->addToRegisterRecord( resourceId, fileName );
}

void FileSystemFacade::addToRegisterFile( FS_STRING fileName )
{
	manager->addToRegisterFile( fileName );
}

}