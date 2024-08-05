#pragma once
#include "Value.h"

class Number : public Value {
public:
	Number();
	Number(const MyString& str);
	Value* clone() const override;
};