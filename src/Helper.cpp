#include "../include/Helper.h"
#include <sstream>
#include "../include/Menu.h"

//removes slashes before " and the reversed slash
void Helper::removeUselessSlashes(MyString& str)
{
	size_t strLength = str.length() - 2; // -2, because of the the Quotation Marks at the end and the beginning
	for (size_t i = 1; i < strLength; i++)
	{
		char firstChar = str[i];
		char secondChar = str[i + 1];
		if ((firstChar == '\\' && secondChar == '\"') || (firstChar == '\\' && secondChar == '\\'))
		{
			for (size_t j = i; j <= strLength; j++)
			{
				str[j] = str[j + 1];
			}
			str[strLength + 1] = '\0'; 
			strLength--; 
			i--;
		}
	}
	str = str.c_str();
}

//count how many symbols (without digits) have the number
size_t Helper::countSymbols(const MyString& str)
{
	size_t counter = 0;
	size_t strLength = str.length();
	for (size_t i = 0; i < strLength; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			counter++;
		}
	}
	return counter;
}

//removes spaces before and after the string
void Helper::removeSpaces(MyString& str)
{
	size_t index = 0;
	while (str[index] == ' ') //remove leading spaces
	{
		index++;
	}
	size_t lengthWithoutFrontSpaces = str.length() - index;
	for (size_t i = 0; i < lengthWithoutFrontSpaces; i++)
	{
		str[i] = str[index + i];
	}
	str[lengthWithoutFrontSpaces] = '\0';
	while (str[lengthWithoutFrontSpaces - 1] == ' ') //remove afterward spaces
	{
		str[lengthWithoutFrontSpaces - 1] = '\0';
		--lengthWithoutFrontSpaces;
	}
	str = str.c_str(); 
}

bool Helper::containsTheSameCell(const MyString& currString, const MyString& checkStr)
{
	std::stringstream ss(checkStr.c_str());
	ss.ignore(2);
	MyString newStr;
	while (!ss.eof())
	{
		ss >> newStr;
		if (currString == newStr)
		{
			return true;
		}
	}
	return false;
}

bool Helper::isCell(const MyString& str)// not static, because I am using it in table.cpp for calculating a formula
{
	size_t i = 2;
	bool cOccured = false;
	if (str[0] == 'R' && (str[1] >= '1' && str[1] <= '9'))
	{
		while (str[i] != '\0')
		{
			if ((str[i] < '0' || str[i] > '9') && str[i] != 'C')
			{
				return false;
			}
			if (str[i] == 'C' && i != str.length() - 1)
			{
				cOccured = true;
			}
			i++;
		}
		if (!cOccured)
			return false;
		else
			return true;
	}
	else
		return false;
}

void Helper::ValidateAndConvertStringToInt(unsigned& num, MyString& strNum, const char* str, char* buffer)
{
	std::cout << "Enter number of a " << str << ": ";
	std::cin.getline(buffer, MAX_LENGTH_CHANGE);
	strNum = buffer;
	while (!Menu::isOnlyDigits(strNum))
	{
		std::cout << "Enter number of a " << str << ": ";
		std::cin.getline(buffer, MAX_LENGTH_CHANGE);
		strNum = buffer;
	}
	num = Helper::StringToInt(strNum);
}

bool Helper::isNumber(const MyString& str)
{
	MyString copyStr(str);
	if (str[0] == '(' && str[str.length() - 1] == ')')
	{
		copyStr = str.substr(1, str.length() - 2);
	}
	std::stringstream ss(copyStr.c_str());

	double num;
	char c;

	if (!(ss >> num))
	{
		return false;
	}

	if (ss >> c)
	{
		return false;
	}
	return true;
}

bool Helper::isValidString(const MyString& str)
{
	size_t strLen = str.length();
	if (strLen < 2 || str[0] != '"' || str[strLen - 1] != '"')
	{
		return false;
	}
	int counterFollowingSlashes = 0;
	size_t len = str.length() - 2;
	for (int i = 1; i <= len; i++)
	{
		char secondSymbol = str[i];
		char firstSymbol = str[i - 1];
		if (secondSymbol == '\"')
		{
			if (firstSymbol != '\\')
			{
				return false;
			}
			else
			{
				counterFollowingSlashes--;
			}
		}
		else if (secondSymbol == '\\')
		{
			counterFollowingSlashes++;
		}
		else
		{
			if (counterFollowingSlashes % 2 != 0)
			{
				return false;
			}
			counterFollowingSlashes = 0;
		}
	}
	return counterFollowingSlashes % 2 == 0;
}

bool Helper::isValidFormula(const MyString& str)
{
	std::stringstream line(str.c_str());
	char buff[64]{};
	bool isOperation = false; 
	int counterBrackets = 0;
	line >> buff;
	//if the first symbol is not = or str finishes with an operation
	if (strcmp(buff, "=") != 0 || str[str.length() - 1] == '+' || str[str.length() - 1] == '-' || str[str.length() - 1] == '*' || str[str.length() - 1] == '/' || str[str.length() - 1] == '^')
	{
		return false;
	}
	else
	{
		while (true)
		{
			if (line.eof())
			{
				break;
			}
			line >> buff;
			if (buff[0] == '(') 
			{
				counterBrackets++;
			}
			else if (buff[0] == ')')
			{
				counterBrackets--;
				if (counterBrackets < 0)
				{
					return false;
				}
			}
			else if ((isNumber(buff) || isCell(buff)) && isOperation == false)
			{
				isOperation = true;
			}
			else if ((buff[0] == '+' || buff[0] == '-' || buff[0] == '*' || buff[0] == '/' || buff[0] == '^') && isOperation) {
				isOperation = false;
			}
			else
			{
				return false;
			}
		}
		if (!isOperation)
		{
			return false;
		}
		return true;
	}
}

bool Helper::isValid(const MyString& str)
{
	if (isNumber(str) || isValidFormula(str) || isValidString(str) || str == "")
	{
		return true;
	}
	return false;
}

Types Helper::determineType(MyString& str)
{
	removeSpaces(str);
	if (isValidFormula(str))
	{
		return Types::formula;
	}
	else if (isValidString(str))
	{
		return Types::string;
	}
	else if (isNumber(str))
	{
		return Types::number;
	}
	else if (str == "")
	{
		return Types::empty;
	}
	else
	{
		throw std::invalid_argument(" is invalid data type!");
	}
}

unsigned Helper::StringToInt(const MyString& str)
{
	size_t result = 0;
	size_t stringLength = str.length();
	for (size_t i = 0; i < stringLength; i++)
	{
		size_t currDigit = str[i] - '0';
		result = result * 10 + currDigit;
	}
	return result;
}

//Gets the index of a column in a cell
void Helper::getIndexColumn(const MyString& str, size_t& index)
{
	size_t ind = 1;
	while (str[ind] != 'C')
	{
		ind++;
	}
	++ind;
	while (str[ind] != '\0')
	{
		index *= 10;
		index += (str[ind] - '0');
		ind++;
	}
}

//Gets the index of the row in a cell
void Helper::getIndexRow(const MyString& str, size_t& index)
{
	unsigned ind = 1;
	while (str[ind] != 'C')
	{
		if (str[ind] >= '0' && str[ind] <= '9')
		{
			index *= 10;
			index += (str[ind] - '0');
		}
		ind++;
	}
}

//gets the length of a double
size_t Helper::checkLengthOfDouble(double num)
{
	size_t digitsBeforeDot = 0;
	while (num >= 1)
	{
		num /= 10;
		digitsBeforeDot++;
	}
	return digitsBeforeDot;
}

size_t Helper::prec(char c)
{
	if (c == '^')
		return 3;
	else if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

//adds spaces for alignement
void Helper::addSpaces(int conditionValue)
{
	while (conditionValue > 0)
	{
		std::cout << " ";
		conditionValue--;
	}
}
