#pragma once
#if !defined(__PREFERENCES__)
#define __PREFERENCES__

#include <ClanLib/core.h>

class Preferences
{
public:
	Preferences(void);
	~Preferences(void);
	const CL_String getIp() const
	{
		return ip;
	}
	const CL_String getPort() const
	{
		return port;
	}
private:
	CL_String ip;
	CL_String port;
};

#endif