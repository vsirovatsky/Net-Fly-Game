#pragma once

#include "CommunicationsFacade.h"
#include "FileSystemFacade.h"

namespace simpleclient {

class ISimpleMainComponentPanel {
public:
	ISimpleMainComponentPanel(){};
	virtual ~ISimpleMainComponentPanel(){};
	virtual communications::AbstractPostOffice * getPostOffice() = 0;
	virtual filesystem::FileSystemFacade * getFileSystem() = 0;
};

}