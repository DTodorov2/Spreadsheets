#include "../include/ValueFactory.h"

Value* valueFactory(const MyString& str, Types type, char ch)
{
	switch (type)
	{
	case Types::number:
		return new Number(str);
	case Types::string:
		return new String(str);
	case Types::formula:
	{
		Formula* newFormula = new Formula(str);
		if (ch == 'r') // if ch == r, then we must calculate the formula -> do it, when edit a cell
			newFormula->setValue(str);
		return newFormula;
	}
	case Types::empty:
		return new Empty(str);
	}
	return new Invalid(str);
}
