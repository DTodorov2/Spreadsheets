#pragma once
#include "MyString.h"
#include "GlobalConstants.h"
#include "Value.h"

class Helper {
public:
	static bool isValidString(const MyString& str);
	static bool isValidFormula(const MyString& str);
	static bool isNumber(const MyString& str);
	static size_t countSymbols(const MyString& str);
	static bool isCell(const MyString& str);
	static bool isValid(const MyString& str);
	static void removeSpaces(MyString& str);
	static void addSpaces(int conditionValue);
	static Types determineType(MyString& str);
	static void removeUselessSlashes(MyString& str);
	static void ValidateAndConvertStringToInt(unsigned& num, MyString& strNum , const char* str, char* buffer);
	static unsigned StringToInt(const MyString& str);
	static bool containsTheSameCell(const MyString& currString, const MyString& checkStr);
	static void getIndexColumn(const MyString& str, size_t& index);
	static void getIndexRow(const MyString& str, size_t& index);
	static size_t checkLengthOfDouble(double num);
	static size_t prec(char c);
};