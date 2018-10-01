#pragma once

#include "stdafx.h"
#include <iostream>
#include "CommonTypeDefs.h"


namespace common {

class CommonException
{
public:
	CommonException(void);
	CommonException( COMMON_STRING mess );
	CommonException( COMMON_STRING fileName, COMMON_STRING mess );
	~CommonException(void);
	COMMON_STRING & getMessage();
private:
	COMMON_STRING message;
};

}