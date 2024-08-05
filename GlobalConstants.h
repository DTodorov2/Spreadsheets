#pragma once
#include <sstream>
#include <fstream>
#include "MyString.h"
#include "myVector.hpp"

static const int MAX_LENGTH_CHANGE = 1024;

enum class Types {
	number,
	string,
	formula,
	empty,
	invalid
};
