#pragma once
#include "Value.h"
#include <fstream>
#include "myVector.hpp"

class Row {
	Vector<Value*> values; //to pri vector default-niq constructor si go suzdava s capacity 4

	void addValueToRow(MyString& str, size_t columnIndex, size_t rowIndex);
	bool checkForMissedCommas(const MyString& str, char& symbolForComma);

	void free();
	void copyFrom(const Row& other);
	void moveFrom(Row&& other);

public:
	Row() = default;
	Row(const Row& other);
	Row& operator=(const Row& other);
	~Row();
	Row(Row&& other) noexcept;
	Row& operator=(Row&& other) noexcept;

	const size_t getValuesCount() const;

	void readRow(std::fstream& fs, size_t& rowIndex);
	void saveRow(std::fstream& fs) const;
	void removeValueAtIndex(int index);
	void addValueAtIndex(Value* value, int index);

	Value* operator[](int index);
	const Value* operator[](int index) const;
};

