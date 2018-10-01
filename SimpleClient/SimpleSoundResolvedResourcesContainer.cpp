#include "StdAfx.h"
#include "SimpleSoundResolvedResourcesContainer.h"

using namespace simpleclient;

SimpleSoundResolvedResourcesContainer::SimpleSoundResolvedResourcesContainer(void)
{
}

SimpleSoundResolvedResourcesContainer::~SimpleSoundResolvedResourcesContainer(void)
{
}

COMMON_STRING * SimpleSoundResolvedResourcesContainer::getAddress( COMMON_STRING & resourceId, COMMON_STRING & soundId )
{
	COMMON_STRING key = COMMON_STRING("");
	key.append( resourceId );
	key.append( ":" );
	key.append( soundId );
	std::hash_map<COMMON_STRING, COMMON_STRING>::iterator it = mData.find( key );
	if ( it == mData.end() )
		return 0;
	return &(it->second);
}

void SimpleSoundResolvedResourcesContainer::addAddress( COMMON_STRING & resourceId, COMMON_STRING & soundId,  COMMON_STRING & address )
{
	COMMON_STRING key = COMMON_STRING("");
	COMMON_STRING value = COMMON_STRING( address );
	key.append( resourceId );
	key.append( ":" );
	key.append( soundId );
	mData.insert( std::pair<COMMON_STRING, COMMON_STRING>( key, value ) ); 
}
