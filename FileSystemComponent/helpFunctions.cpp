#include "helpFunctions.h"

namespace filesystem {

using namespace std;

template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T StringToNumber ( const string &Text )//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

void testing(){
	int i = StringToNumber<int>( "5" );
	string ss = NumberToString<int>( 800 );
	float f = StringToNumber<float>( "5.0" );
	string ss2 = NumberToString<float>( 800.0f );
}

}