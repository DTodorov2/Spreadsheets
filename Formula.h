#pragma once
#include "Value.h"
#include <stack>

class Formula : public Value {
	void executeTheOperation(std::stack<double>& outputStack, std::stack<char>& operands) const;
	double getResult(char ch, double num1, double num2) const;
public:
	Formula();
	Formula(const MyString& str);
	Value* clone() const override;
	void calculateFormula(const MyString& str);
	void setValue(const MyString& str) override;
};