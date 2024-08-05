#pragma once
#include "Helper.h"

class Value {
protected:
	MyString str;

public:
	Value();
	Value(const MyString& str);
	const MyString& getString() const;
	virtual void setValue(const MyString& str);

	virtual Value* clone() const = 0;
	virtual ~Value() = default;
};