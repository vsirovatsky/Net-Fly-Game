#include "DataLoadManager.h"

namespace filesystem {

DataLoadManager::DataLoadManager(void) : mCaches(), mRegister()
{
}

DataLoadManager::~DataLoadManager(void)
{
}

FS_STRING & DataLoadManager::getValueInFile( FS_STRING fileName, FS_STRING key )
{
	std::hash_map<FS_STRING, DataCache>::iterator it = mCaches.find(fileName);
	if (it == mCaches.end()){
		mCaches.insert( std::pair<FS_STRING, DataCache>( fileName, DataCache(fileName) ) );
		return mCaches.find(fileName)->second.getValue( key );
	} else {
		return it->second.getValue( key );
	}
}

void DataLoadManager::setValueInFile( FS_STRING fileName, FS_STRING key, FS_STRING value )
{
	try {
		mCaches.find(fileName)->second.setValue(key, value);
	} catch (...) {
		throw FileSystemException( fileName, "File not exists. On operation save value in file. Key: [" + key + "], value: [" + value + "]" );
	}
}

void DataLoadManager::preloadFile( FS_STRING fileName )
{
	if (mCaches.find(fileName) == mCaches.end()){
		mCaches.insert( std::pair<FS_STRING, DataCache>( fileName, DataCache(fileName) ) );
	}
}

void DataLoadManager::saveFile( FS_STRING fileName )
{
	try {
		mCaches.find(fileName)->second.saveToFile();
	} catch (...) {
		throw FileSystemException( fileName, "File not exists. On operation save file" );
	}
}

FS_STRING & DataLoadManager::getValueInResource( FS_STRING resourceId, FS_STRING key )
{
	FS_STRING resFile = getMappedFileForResource( resourceId );
	return getValueInFile( resFile, key );
}

void DataLoadManager::setValueInResource( FS_STRING resourceId, FS_STRING key, FS_STRING value )
{
	FS_STRING resFile = getMappedFileForResource( resourceId );
	setValueInFile( resFile, key, value );
}

void DataLoadManager::preloadResource( FS_STRING resourceId )
{
	FS_STRING resFile = getMappedFileForResource( resourceId );
	preloadFile( resFile );
}

void DataLoadManager::saveResource( FS_STRING resourceId )
{
	FS_STRING resFile = getMappedFileForResource( resourceId );
	saveFile( resFile );
}

void DataLoadManager::addToRegisterRecord( FS_STRING resourceId, FS_STRING fileName )
{
	// TODO: maybe dublicates
	mRegister.insert( std::pair<FS_STRING, FS_STRING>( resourceId, fileName ) );
}

void DataLoadManager::addToRegisterFile( FS_STRING fileName )
{
	try {
		std::ifstream myfile ( fileName );
		if (myfile.is_open())
		{
			std::pair<FS_STRING, FS_STRING> p;
			FS_STRING line;
			while (! myfile.eof() )
			{
				std::getline (myfile,line);
				int i = line.find(':');
				if ( i > 0 ) {
					FS_STRING key = line.substr( 0, i );
					FS_STRING value = line.substr( i+1, line.length() );
					p = std::pair<FS_STRING, FS_STRING>( key, value );
					// TODO: maybe dublicates
					mRegister.insert( p );
				}
			}
			myfile.close();
		}
	} catch (...) {
		throw FileSystemException( fileName, "Error in loading register from file" );
	}
}

FS_STRING & DataLoadManager::getMappedFileForResource( FS_STRING resourceId )
{
	std::hash_map<FS_STRING, FS_STRING>::iterator it = mRegister.find(resourceId);
	if ( it == mRegister.end() ) {
		throw FileSystemException("No mapping for resource id: " + resourceId);
	}
	return it->second;
}

}