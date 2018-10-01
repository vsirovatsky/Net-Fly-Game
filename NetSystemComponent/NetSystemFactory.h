#pragma once

#include "NetSystemAbstractManager.h"
#include "NetSystemAbstractServerManager.h"
#include "NetSystemManager.h"
#include "NetSystemServerManager.h"

namespace netsystem {

	class NetSystemFactory 
	{
	public:
		static NetSystemAbstractManager * createNetSystemClientManager()
		{
			return new NetSystemManager();
		}

		static NetSystemAbstractServerManager * createNetSystemServerManager()
		{
			return new NetSystemServerManager();
		}
	};

}