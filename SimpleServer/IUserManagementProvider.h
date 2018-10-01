#pragma once

#include "SimpleServerTypeDefs.h"
#include "SimpleNetMessages.h"
#include "netSystemTypeDefs.h"

namespace simpleserver {

class IUserManagementProvider {
public:
	IUserManagementProvider(){}
	virtual ~IUserManagementProvider(){}
	virtual bool isUserExists( NS_GUID guid ) = 0;
	virtual void addUser( NS_GUID guid ) = 0;
	virtual void removeUser( NS_GUID guid ) = 0;
	virtual OBJECT_IDENTITY getIdentity( NS_GUID guid ) = 0;
};

}