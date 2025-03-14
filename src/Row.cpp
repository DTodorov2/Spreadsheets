#include "../include/Row.h"
#include "../include/ValueFactory.h"

void Row::free()
{
	size_t valuesCount = getValuesCount();
	for (size_t i = 0; i < valuesCount; i++)
	{
		delete values[i];
	}
}

void Row::copyFrom(const Row& other)
{
	size_t valuesCount = other.values.getSize();
	values.clear();
	for (size_t i = 0; i < valuesCount; i++)
		values.pushBack(other.values[i]->clone());
}

void Row::moveFrom(Row&& other)
{
	values = std::move(other.values); //dostatuchno li e?
}


Row::Row(const Row& other)
{
	copyFrom(other);
}

Row& Row::operator=(const Row& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Row::~Row()
{
	free();
}

Row::Row(Row&& other) noexcept {
	moveFrom(std::move(other));
}

Row& Row::operator=(Row&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

//checks for missed commas in file
bool Row::checkForMissedCommas(const MyString& str, char& symbolForComma)
{
	size_t strLen = str.length();
	MyString result, reversedStr;
	for (size_t i = 0; i < strLen; i++)
	{
		result += str[i];
		reversedStr += str[strLen - 1 - i];
		if (Helper::isValid(reversedStr))
		{
			symbolForComma = str[strLen - 2 - i];
		}
		
		if (Helper::isValid(result))
		{
			symbolForComma = str[i]; //it won't execute this line, when i is equal to strLen - 1
		}
	}
	if (symbolForComma != '\0' && symbolForComma >= 0 && symbolForComma <= 127)
	{
		throw std::exception("Missed comma after ");
	}
}

const size_t Row::getValuesCount() const {
	return values.getSize();
}

void Row::addValueToRow(MyString& str, size_t columnIndex, size_t rowIndex)
{
	Types type = Types::invalid;
	char symbolForComma = '\0';
	try
	{
		type = Helper::determineType(str);
	}
	catch (const std::exception&)
	{
		try
		{
			checkForMissedCommas(str, symbolForComma);
		}
		catch (const std::exception& exe)
		{
			std::cout << exe.what() << symbolForComma << " on line " << rowIndex << ", column " << columnIndex << std::endl;
			char answer[MAX_LENGTH_CHANGE]{};
			do
			{
				std::cout << "Do you want to continue? - y/n" << std::endl;
				std::cin.getline(answer, MAX_LENGTH_CHANGE);
			} while (strcmp(answer, "y") != 0 && strcmp(answer, "n") != 0);

			if (strcmp(answer, "n") == 0)
			{
				exit(0);
			}
		}
		std::cout << "Error: row " << rowIndex << ", col " << columnIndex << ", " << str << " is unknown data type!" << std::endl;
		std::cout << "\nThe value must be:\n1. String (starts and ends with \")\n2. Number (decimal or double, written with . not ,)\n3. Formula, following the given pattern: = (value) (operand) (value) ...\n" << std::endl;
		str = "Invalid";
	}
	values.pushBack(valueFactory(str, type, 'n')); //push back the new value
}

void Row::readRow(std::fstream& fs, size_t& rowIndex)
{
	const static int MAX_LENGTH_ROW = 1024;
	char buff[MAX_LENGTH_ROW]{};
	fs.getline(buff, MAX_LENGTH_ROW);//can't insert MyString in getline
	std::stringstream ss(buff);
	size_t columnIndex = 0;

	while (!ss.eof())
	{
		columnIndex++;
		char currWord[MAX_LENGTH_ROW]{};
		ss.getline(currWord, MAX_LENGTH_ROW, ',');
		MyString currStr(currWord);
		addValueToRow(currStr, columnIndex, rowIndex);
	}
}

void Row::saveRow(std::fstream& fs) const
{
	size_t valuesCount = getValuesCount();
	for (size_t i = 0; i < valuesCount; i++)
	{
		if (i == valuesCount - 1)
			fs << values[i]->getString();
		else
			fs << values[i]->getString() << ", ";
	}
	fs.flush();
}

Value* Row::operator[](int index) {
	return values[index];
}

const Value* Row::operator[](int index) const {
	return values[index];
}

void Row::removeValueAtIndex(int index)
{
	values.popAt(index);
}

void Row::addValueAtIndex(Value* value, int index)
{
	values.pushAt(value, index);
}
