#include "DataCache.h"

namespace filesystem {

DataCache::DataCache( FS_STRING fileName ) : mFileName( fileName ), mData()
{
	load();
}

DataCache::~DataCache(void)
{
}

std::string & DataCache::getValue( FS_STRING & key )
{
	try {
		return mData[key];
	} catch (...) {
		throw FileSystemException( mFileName, "Not contains key [" + key + "]" );
	}
}

int DataCache::getCacheLevel()
{
	return mCacheLevel;
}

void DataCache::load()
{
	try {
		std::ifstream myfile ( mFileName );
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
					mData.insert( p );
				}
			}
			myfile.close();
		} else {
			throw FileSystemException( mFileName, "File not found" );
		}
	} catch (FileSystemException ex) {
		throw ex;
	} catch (...) {
		throw FileSystemException( mFileName, "Error in loading data" );
	}
	mCacheLevel = 1;
	/*try {
		FS_STRING c = mData.at( std::string("cacheLevel") );
		mCacheLevel = StringToNumber<int>( c );
	} catch (...) {
		throw FileSystemException( mFileName, "No cacheLevel record" );
	}*/
}

void DataCache::setValue( FS_STRING & key, FS_STRING & value )
{
	if (mData.find(key) == mData.end()){
		mData.insert( std::pair<FS_STRING, FS_STRING>( key, value ) );
	} else {
		mData.erase(key);
		mData.insert( std::pair<FS_STRING, FS_STRING>( key, value ) );
	}
}

void DataCache::saveToFile()
{
	try {
		std::ofstream myfile ( mFileName );
		if (myfile.is_open())
		{
			for ( std::hash_map<FS_STRING, FS_STRING>::iterator it = mData.begin(); it!=mData.end(); ++it) {
				FS_STRING str(it->first); 
				str.append(":");
				str.append(it->second);
				str.append("\n");
				myfile << str;
			}
			myfile.close();
		} else {
			throw FileSystemException( mFileName, "File cannot be opened for save" );
		}
	} catch (FileSystemException ex) {
		throw ex;
	} catch (...) {
		throw FileSystemException( mFileName, "Error in saving data" );
	}
}

}