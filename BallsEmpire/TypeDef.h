#pragma once

#include "Logger.h"

typedef int BE_INT;
typedef float BE_FLOAT;
typedef long BE_ID;

class vector2d {
public:
	vector2d() : x(0), y(0) {}
	vector2d( BE_FLOAT _x, BE_FLOAT _y ) : x(_x), y(_y) {}
	vector2d( vector2d & _other ) : x(_other.x), y(_other.y) {}
	BE_FLOAT x;
	BE_FLOAT y;
	BE_FLOAT getDistance( vector2d & _other ){
		return std::sqrt( (x - _other.x) * (x - _other.x) + ( y - _other.y ) * ( y - _other.y ) );
	}
};