#include "utilsString.h"

using namespace std;

template <typename T>
string util::NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T util::StringToNumber ( const string &Text )//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

void testing(){
	int i = util::StringToNumber<int>( "5" );
	string ss = util::NumberToString<int>( 800 );
}