#pragma once

#include <sstream>

namespace filesystem {

template <typename T> std::string NumberToString ( T Number );

template <typename T> T StringToNumber ( const std::string &Text );

}

