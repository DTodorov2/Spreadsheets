#pragma once
#include "Row.h"
#include "myVector.hpp"
#include "ValueFactory.h"
#include <stack>

class Table {
	Vector<Row> rows;

	void getValueFromCell(MyString& str) const;
	void fillArrayWithLenghtOfEachRow(Row& row, Vector<size_t>& arr) const;
	void getMaxLengthFromEachColumn(Vector<size_t>& arr);
	unsigned getMaxValueInRows() const;
	void printRow(const Row& row, Vector<size_t>& numberOfSpaces) const;
	void changeCellsToValues(MyString& str);

public:
	Table() = default;

	void printTable();
	void exportDataFromFile(std::fstream& fs);
	void saveDataToFile(std::fstream& fs) const;

	void editCell(/*size_t numberRow, size_t numberColumn, */const MyString& str);
};

