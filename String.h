#pragma once
#include "Value.h"

class String : public Value {
public:
	String();
	String(const MyString& str);
	Value* clone() const override;
	void setValue(const MyString& str) override;
};