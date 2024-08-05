#pragma once
#include "MyString.h"
#include "Value.h"
#include "Number.h"
#include "Empty.h"
#include "Formula.h"
#include "String.h"
#include "Invalid.h"
#include "Helper.h"

Value* valueFactory(const MyString& str, Types type, char ch = 'r');
