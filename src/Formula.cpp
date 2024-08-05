#include "../include/Formula.h"
#include "../include/Value.h"
#include <cmath>

Formula::Formula() : Value() {};

Formula::Formula(const MyString& str) : Value(str) {};

Value* Formula::clone() const {
	Value* newObj = new Formula(*this);
	return newObj;
}

void Formula::setValue(const MyString& str)
{
	calculateFormula(str);
}

double Formula::getResult(char ch, double num1, double num2) const
{
	int pow = num2;
	int copyNum1 = num1;

	switch (ch)
	{
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '^':
		if (num2 < 0)
		{
			num2 *= -1;
			num1 = 1/std::pow(num1, num2);
			return num1;
		}
		num1 = std::pow(num1, num2);
		return num1;
	case '*':
		return num1 * num2;
	case '/':
		if (num2 == 0)
		{
			throw std::invalid_argument("Operation cannot be done. The divisor is equal to 0. ");
		}
		return num1 / num2;
	default:
		return -1;
	}
}

void Formula::executeTheOperation(std::stack<double>& outputStack, std::stack<char>& operands) const
{
	char operand = operands.top();
	operands.pop();
	double val2 = outputStack.top();
	outputStack.pop();
	double val1 = outputStack.top();
	outputStack.pop();

	outputStack.push(getResult(operand, val1, val2));
}

void Formula::calculateFormula(const MyString& str)
{
	std::stack<double> outputStack;
	std::stack<char> operands;

	std::stringstream ss(str.c_str());
	ss.ignore(2);
	try
	{
		while (true)
		{
			MyString currNum;
			if (ss.eof())
			{
				break;
			}
			ss >> currNum;
			if (strcmp(currNum.c_str(), "(") == 0)
			{
				operands.push(currNum.c_str()[0]);
			}
			else if (strcmp(currNum.c_str(), ")") == 0)
			{
				while (operands.top() != '(')
				{
					executeTheOperation(outputStack, operands);
				}
				operands.pop(); // remove the last standing (
			}
			else if (strcmp(currNum.c_str(), "*") == 0 || strcmp(currNum.c_str(), "+") == 0 || strcmp(currNum.c_str(), "-") == 0 || strcmp(currNum.c_str(), "^") == 0 || strcmp(currNum.c_str(), "/") == 0) //pravq taka proverkite, shtoto ako imam -1, to shte vlezne tuka, a ne trqq
			{
				if (operands.empty() || Helper::prec(operands.top()) < Helper::prec(currNum[0]))
				{
					operands.push(currNum[0]);
				}
				else //obratnoto e da ne e prazen I da prioriteta na noviq operand da e po-maluk ili raven na prioriteta na top-a
				{
					int priorityCurrOperand = Helper::prec(currNum[0]);
					int priorityOperandsTop = Helper::prec(operands.top());
					while (!operands.empty() && (priorityCurrOperand <= priorityOperandsTop))
					{
						executeTheOperation(outputStack, operands);
					}
					operands.push(currNum[0]);
				}
			}
			else
			{
				outputStack.push(std::atof(currNum.c_str()));
			}
		}
		while (!operands.empty())
		{
			executeTheOperation(outputStack, operands);
		}
		std::stringstream ss1;
		ss1 << outputStack.top();
		MyString strCurr;
		ss1 >> strCurr;
		this->str = strCurr;
	}
	catch (const std::invalid_argument& exe)
	{
		std::cout << exe.what() << std::endl;
		this->str = "ERROR";
		return;
	}
}