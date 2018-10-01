#include "StdAfx.h"
#include "SimpleUsersRegister.h"

using namespace simpleserver;

SimpleUsersRegister::SimpleUsersRegister(void)
{
}

SimpleUsersRegister::~SimpleUsersRegister(void)
{
}

bool SimpleUsersRegister::isUserExists(  NS_GUID guid )
{
	if ( regGuids.find(guid.g) == regGuids.end() )
		return false;
	else
		return true;
}

void SimpleUsersRegister::addUser( NS_GUID guid )
{
	OBJECT_IDENTITY oi = identetyGenerator.getNextOI();
	if (regGuids.find(guid.g) != regGuids.end()){
		regGuids.erase(guid.g);
	}
	regGuids.insert( std::pair<GUID_NUMBER, NS_GUID>( guid.g, guid ) );

	if (regObjects.find(guid.g) != regObjects.end()){
		regObjects.erase(guid.g);
	}
	regObjects.insert( std::pair<GUID_NUMBER, OBJECT_IDENTITY>( guid.g, oi ) );

}

void SimpleUsersRegister::removeUser( NS_GUID guid )
{
	if (regGuids.find(guid.g) != regGuids.end()){
		regGuids.erase(guid.g);
	}
	if (regObjects.find(guid.g) != regObjects.end()){
		regObjects.erase(guid.g);
	}
}

OBJECT_IDENTITY SimpleUsersRegister::getIdentity( NS_GUID guid )
{
	return regObjects[guid.g];
}

void SimpleUsersRegister::populateOtherGuids( std::vector<NS_GUID> & guids, NS_GUID guidToExclude )
{
	for ( std::hash_map<GUID_NUMBER, NS_GUID>::iterator it = regGuids.begin(); it!=regGuids.end(); ++it) {
		if (it->first != guidToExclude.g)
			guids.push_back( it->second );
	}
}