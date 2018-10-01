#pragma once;
#if !defined(_UTILS_STRING_)
#define _UTILS_STRING_

#include <sstream>

namespace util {

template <typename T> std::string NumberToString ( T Number );

template <typename T> T StringToNumber ( const std::string &Text );

}

#endif // _UTILS_STRING_