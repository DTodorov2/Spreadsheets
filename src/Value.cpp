#include "../include/Value.h"
#include <sstream>

void Value::setValue(const MyString& str)
{
	this->str = str;
}

const MyString& Value::getString() const
{
	return str;
}

Value::Value() : Value("") {};

Value::Value(const MyString& str)
{
	setValue(str);
}