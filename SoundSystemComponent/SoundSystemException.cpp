#include "StdAfx.h"
#include "SoundSystemException.h"


namespace soundsystem {

SoundSystemException::SoundSystemException(void) : message("default")
{
}

SoundSystemException::SoundSystemException(SS_STRING mess) : message(mess)
{
}

SoundSystemException::~SoundSystemException(void)
{
}

SS_STRING & SoundSystemException::getMessage()
{
	return message;
}

SoundSystemException * SoundSystemException::addMessage( SS_STRING mess )
{
	message.append( mess );
	return this;
}

}