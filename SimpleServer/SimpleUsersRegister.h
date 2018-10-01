#pragma once

#include <vector>
#include <hash_map>
#include "SimpleServerTypeDefs.h"
#include "SimpleNetMessages.h"
#include "netSystemTypeDefs.h"
#include "IUserManagementProvider.h"
#include "SimpleObjectIdentetyGenerator.h"


namespace simpleserver {

class SimpleUsersRegister : public IUserManagementProvider
{
public:
	SimpleUsersRegister(void);
	~SimpleUsersRegister(void);

	virtual bool isUserExists( NS_GUID guid );
	virtual void addUser( NS_GUID guid );
	virtual void removeUser( NS_GUID guid );
	virtual OBJECT_IDENTITY getIdentity( NS_GUID guid );

	void populateOtherGuids( std::vector<NS_GUID> & guids, NS_GUID guidToExclude );
private:
	SimpleObjectIdentetyGenerator identetyGenerator;
	std::hash_map<GUID_NUMBER, NS_GUID> regGuids;
	std::hash_map<GUID_NUMBER, OBJECT_IDENTITY> regObjects;
};

}