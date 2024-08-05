#include "../include/Invalid.h"
#include "../include/Value.h"

Invalid::Invalid() : Value() {};

Invalid::Invalid(const MyString& str) : Value(str) {};

Value* Invalid::clone() const {
	Value* newObj = new Invalid(*this);
	return newObj;
}
