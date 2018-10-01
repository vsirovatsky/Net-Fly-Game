#pragma once

#include "Logger.h"
#include "iusermovementinformationdispatcher.h"
#include <hash_map>

namespace simpleserver {

class UserMovementInformationDispatcher :
	public IUserMovementInformationDispatcher
{
public:
	UserMovementInformationDispatcher(void);
	virtual ~UserMovementInformationDispatcher(void);

	virtual void process( OBJECT_IDENTITY, UserMovementInformation * );

	void addProcessor( OBJECT_IDENTITY, IUserMovementInformationProcessor * );
	void clearProcessor( OBJECT_IDENTITY );
private:
	std::hash_map<OBJECT_IDENTITY, IUserMovementInformationProcessor *> processors;
};

}