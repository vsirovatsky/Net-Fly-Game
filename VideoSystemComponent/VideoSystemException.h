#pragma once

#include "stdafx.h"
#include "VideoSystemTypeDefs.h"

namespace videosystem {

	class VideoSystemException
	{
	public:
		VideoSystemException() : message("default") {}
		VideoSystemException( VS_STRING mess ) : message(mess) {}
		~VideoSystemException(){}
		VS_STRING & getMessage(){return message;}
		VideoSystemException * addMessage( VS_STRING mess ){
			message.append( mess );
			return this;
		}
	private:
		VS_STRING message;
	};

	class VideoSystemInitializeException : public VideoSystemException
	{
	public:
		VideoSystemInitializeException() : VideoSystemException() {}
		VideoSystemInitializeException( VS_STRING mess ) : VideoSystemException(mess) {}
	};

	class VideoSystemNoResourceException : public VideoSystemException
	{
	public:
		VideoSystemNoResourceException() : VideoSystemException() {}
		VideoSystemNoResourceException( VS_STRING mess ) : VideoSystemException(mess) {}
	};

	class VideoSystemNoSimpleTypeException : public VideoSystemException
	{
	public:
		VideoSystemNoSimpleTypeException() : VideoSystemException() {}
		VideoSystemNoSimpleTypeException( VS_STRING mess, VS_SIMPLE_OBJECT_TYPES type ) : VideoSystemException(mess) {
			appendNameOfEnum( getMessage(), type );
		}
	private:
		void appendNameOfEnum( VS_STRING mess, VS_SIMPLE_OBJECT_TYPES type )
		{
			switch (type){
			case VS_SIMPLE_OBJECT_TYPE_SPHERE:
				mess.append( " : Simple sphere" );
				return;
			default:
				mess.append( " : Unknown" );
				return;
			}
		}
	};
}