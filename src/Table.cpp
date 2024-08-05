#include "../include/Table.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include "../include/GlobalConstants.h"
#include "../include/Helper.h"
#include <cstdlib>

//makes array with max width from each column in a row
void Table::fillArrayWithLenghtOfEachRow(Row& row, Vector<size_t>& arr) const
{
	size_t valuesCount = row.getValuesCount();
	for (size_t i = 1; i <= valuesCount; i++)
	{
		size_t lengthValue = 0;
		lengthValue = row[i - 1]->getString().length();
		size_t arrSize = arr.getSize();
		if (valuesCount > arrSize && (i > arrSize || arrSize == 0)) // if we don't have a certain value on this exact index, then add
		{
			arr.pushBack(lengthValue);
		}
		else if (lengthValue > arr[i - 1]) // if we already have a certain value, remove it and add the new one
		{
			arr.pushAt(lengthValue, i - 1);
			arr.popAt(i);
		}
	}
}

void Table::getMaxLengthFromEachColumn(Vector<size_t>& arr)
{
	size_t rowsCount = rows.getSize();
	for (size_t i = 0; i < rowsCount; i++)
	{
		fillArrayWithLenghtOfEachRow(rows[i], arr);
	}
}

void Table::exportDataFromFile(std::fstream& fs)
{
	size_t index = 0;
	size_t rowIndex = 0;
	while (!fs.eof())
	{
		Row currRow;
		rowIndex++;
		try
		{
			currRow.readRow(fs, rowIndex);
			if (currRow.getValuesCount() == 1 && strcmp(currRow[0]->getString().c_str(), "") == 0)
			{
				rows.pushBack(Row());
			}
			else
			{
				rows.pushBack(currRow);
			}
		}
		catch (const std::exception& exe)
		{
			std::cout << "On line " << rowIndex << exe.what() << std::endl;
			std::cout << "Line " << rowIndex << " will not be printed!" << std::endl;
		}

	}
	size_t rowSize = rows.getSize();
	for (size_t i = 0; i < rowSize; i++)
	{
		for (size_t j = 0; j < rows[i].getValuesCount(); j++)
		{
			if (rows[i][j]->getString()[0] == '=')
			{
				MyString newStr = rows[i][j]->getString();
				changeCellsToValues(newStr);
				rows[i][j]->setValue(newStr);
			}
		}
	}
	std::cout << "Table loaded!" << std::endl;
	system("pause");
	system("cls");
}

void Table::saveDataToFile(std::fstream& fs) const
{
	size_t rowsCount = rows.getSize();
	for (size_t i = 0; i < rowsCount; i++)
	{
		rows[i].saveRow(fs);
		if (i != rows.getSize() - 1)
		{
			fs << std::endl;
		}
	}
}

void Table::getValueFromCell(MyString& str) const
{
	size_t ind1 = 0, ind2 = 0;
	Helper::getIndexRow(str, ind1);
	Helper::getIndexColumn(str, ind2);
	MyString copyStr(str);
	try
	{
		str = rows[ind1 - 1][ind2 - 1]->getString(); // tuka se bugvashe,shtoto vuv vectora imashe proverka s assertIndex \
																koqto ni hvurlqshe greshka samo ako index > size, a nie iskame da hvurlq i ako index == size, shtoto togava index-a \
																pak e nevaliden
		if (str[0] == '=') //това правилно ли е, щото все едно проверявам дали е формула, пък си имам valueFactory
		{
			getValueFromCell(str);
		}
		else if((str[0] < '0' || str[0] > '9')) //тук проверявам дали стойността ми е число, ако не е - правя стринга да е 0 -> как мога
		{										//да го направя по-добре
			if (str[0] == '-' || str[0] == '+')
			{
				if (str[1] < '0' || str[1] > '9')
				{
					str = "0";
				}
			}
		}
	}
	catch (const std::exception&)
	{
		std::cout << "The current cell is not valid and this value will be considered as 0." << std::endl;
		str = "0";
	}
}

void Table::changeCellsToValues(MyString& str)
{
	std::stringstream ss(str.c_str());
	MyString convertedStr;
	while (true)
	{
		MyString currStr;
		if (ss.eof())
		{
			convertedStr[convertedStr.length() - 1] = '\0';
			break;
		}
		ss >> currStr;
		if (Helper::isCell(currStr)) // to tova mai vuobshte ne mi trqq
		{
			try
			{
				getValueFromCell(currStr);
			}
			catch (const std::exception&)
			{
				std::cout << "The current cell is not valid and this value will be considered as 0." << std::endl;
				currStr = "0";
			}
		}
		convertedStr += currStr;
		convertedStr += " ";
	}
	str = convertedStr.c_str();
}

void Table::editCell(const MyString& str)
{
	MyString columnNum, rowNum, editStr;
	unsigned numColumn, numRow;
	char buffer[MAX_LENGTH_CHANGE]{};

	Helper::ValidateAndConvertStringToInt(numRow, rowNum, "row", buffer);
	while (numRow - 1 >= rows.getSize() || numRow < 1) {
		std::cout << "Invalid row index!" << std::endl;
		Helper::ValidateAndConvertStringToInt(numRow, rowNum, "row", buffer);
	}

	size_t valuesCount = rows[numRow - 1].getValuesCount();
	Helper::ValidateAndConvertStringToInt(numColumn, columnNum, "column", buffer);
	while (numColumn - 1 >= valuesCount || numColumn < 1) {
		std::cout << "Invalid column index!" << std::endl;
		Helper::ValidateAndConvertStringToInt(numRow, rowNum, "column", buffer);
	}

	std::cout << "Enter what you want to change it to: ";
	std::cin.getline(buffer, MAX_LENGTH_CHANGE);
	editStr = buffer;

	MyString currStr(editStr);
	Types type = Helper::determineType(currStr);
	if (!Helper::isValid(currStr))
	{
		throw std::exception(" is invalid data type!");
	}
	if (currStr[0] == '=')
	{
		changeCellsToValues(currStr);
	}

	rows[numRow - 1].removeValueAtIndex(numColumn - 1);
	Value* newValue = valueFactory(currStr, type);
	rows[numRow - 1].addValueAtIndex(newValue, numColumn - 1);
}

//gets max number of values from all rows
unsigned Table::getMaxValueInRows() const
{
	size_t maxValues = 0;
	size_t rowsCount = rows.getSize();
	for (size_t i = 0; i < rowsCount; i++)
	{
		size_t currRowValuesCount = rows[i].getValuesCount();
		if (currRowValuesCount > maxValues)
		{
			maxValues = currRowValuesCount;
		}
	}
	return maxValues;
}

void Table::printRow(const Row& row, Vector<size_t>& numberOfSpaces) const {
	size_t countValuesInRow = row.getValuesCount();
	std::cout << "| ";
	for (size_t i = 0; i < numberOfSpaces.getSize(); i++)
	{
		if (i < countValuesInRow)
		{
			size_t spacesTaken = row[i]->getString().length();
			int spacesLeftToPrint = numberOfSpaces[i] - spacesTaken;
			Helper::addSpaces(spacesLeftToPrint);
			std::cout << row[i]->getString();
			if (i == numberOfSpaces.getSize() - 1)
			{
				std::cout << " |";
				std::cout << std::endl;
				break;
			}
			std::cout << " | ";
		}
		else
		{
			Helper::addSpaces(numberOfSpaces[i]);
			if (i + 1 == numberOfSpaces.getSize())
			{
				std::cout << " |";
				std::cout << std::endl;
			}
			else
			{
				std::cout << " | ";
			}
		}
	}
}

void Table::printTable() {
	unsigned maxValuesOnRow = getMaxValueInRows();
	Vector<size_t> numberOfSpaces(maxValuesOnRow);//how many spaces should I put before and after the value
	getMaxLengthFromEachColumn(numberOfSpaces);
	unsigned rowsCount = rows.getSize();
	for (size_t i = 0; i < rowsCount; i++)
	{
		printRow(rows[i], numberOfSpaces);
	}
}