#pragma once
#include <iostream>
#include "SimpleNetTypes.h"

#define GUID_NUMBER unsigned long long int
#define SERVER_TIME long
#define SERVER_FLOAT float

// Movement Strategies codes
typedef unsigned char MOVEMENT_STRATEGY_TYPE;
#define MOVEMENT_STRATEGY_BLANK 0
#define MOVEMENT_STRATEGY_USER_FLY 1

struct vector3df
{
public:
	vector3df() : x(0), y(0), z(0) {}
	vector3df(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}
	vector3df( const vector3df & other ) : x(other.x), y(other.y), z(other.z) {}
	float length(){ return std::sqrt(x*x + y*y + z*z);}
	bool equals( vector3df & other ){ return ((other.x==x)&&(other.y==y)&&(other.z==z));}
	vector3df getLeftPerpendicularXY(){
		vector3df p(-y,x,0);
		p.normalize();
		return p;
	}
	vector3df getRightPerpendicularXY(){
		vector3df p(y,-x,0);
		p.normalize();
		return p;
	}
	void normalize(){
		float l = length();
		if ( l == 0 )
			return;
		x /= l;
		y /= l;
		z /= l;
	}
	float x;
	float y;
	float z;
};