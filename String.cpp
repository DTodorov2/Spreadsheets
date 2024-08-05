#include "String.h"
#include "Value.h"
#include "Helper.h"

String::String() : Value() {};

String::String(const MyString& str) {
	MyString finalValue(str);
	Helper::removeUselessSlashes(finalValue);
	setValue(finalValue);
};

Value* String::clone() const {
	Value* newObj = new String(*this);
	return newObj;
}

void String::setValue(const MyString& str)
{
	MyString newStr(str);
	Helper::removeUselessSlashes(newStr);
	this->str = newStr;
}