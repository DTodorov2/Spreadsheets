#include "../include/Number.h"

Number::Number() : Value() {};

Number::Number(const MyString& str) : Value(str) {};

Value* Number::clone() const {
	Value* newObj = new Number(*this);
	return newObj;
}
