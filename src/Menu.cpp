#include "../include/Menu.h"
//Using MSVC compiler

void Menu::validateOption(MyString& option)
{
	char optionInput[MAX_LENGTH_CHANGE]{};
	std::cin.getline(optionInput, MAX_LENGTH_CHANGE);
	option = optionInput;

	while ((option.length() != 1) || (option[0] - '0' <= 0 || option[0] - '0' >= 8))
	{
		std::cout << "The number must be between 1 and 7: ";
		std::cin.getline(optionInput, MAX_LENGTH_CHANGE);
		option = optionInput;
	}
}

int Menu::chooseKey()
{
	std::cout << "-------------------" << std::endl;
	std::cout << "1 - Open file" << std::endl;
	std::cout << "2 - Close file" << std::endl;
	std::cout << "3 - Save file" << std::endl;
	std::cout << "4 - Save file as" << std::endl;
	std::cout << "5 - Edit cell" << std::endl;
	std::cout << "6 - Print table" << std::endl;
	std::cout << "7 - Exit program" << std::endl;
	std::cout << "-------------------" << std::endl;

	std::cout << "Choose an option: ";
	MyString optionStr;
	validateOption(optionStr);
	int optionInt = optionStr[0] - '0';
	return optionInt;
}

bool Menu::checkEmptyFile(std::fstream& myFile)
{
	int currPos = myFile.tellg();
	MyString ch;
	myFile >> ch;
	myFile.seekg(currPos);
	if (ch[0] == '\0')
	{
		return true;
	}
	return false;
}

bool Menu::isOnlyDigits(const MyString& str)
{
	if (str[0] == '-')
	{
		std::cout << "The number must be positive!" << std::endl;
		return false;
	}
	size_t strLen = str.length();
	if (strLen == 0)
	{
		std::cout << "You must enter a value!" << std::endl;
		return false;
	}
	for (size_t i = 0; i < strLen; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			std::cout << "Must contain only digits!" << std::endl;
			return false;
		}
		else if (str[i] == '0' && strLen == 1)
		{
			std::cout << "The number must be grater than 0!" << std::endl;
			return false;
		}
	}
	return true;
}

void Menu::validateNewFileName(MyString& str)
{
	char fileName[MAX_LENGTH_CHANGE]{};
	std::cout << "Enter the name of the file you want to open (.txt only): ";
	std::cin.getline(fileName, MAX_LENGTH_CHANGE);
	str = fileName;

	while (str.substr(str.length() - 4, 4) != ".txt")
	{
		std::cout << "The file name must have \".txt\" extension" << std::endl;
		Sleep(1500);
		system("cls");
		std::cout << "Enter the name of the file you want to open (.txt only) or \"exit\" if you want to exit the program: ";
		std::cin.getline(fileName, MAX_LENGTH_CHANGE);
		str = fileName;
		if (strcmp(str.c_str(), "exit") == 0)
		{
			system("cls");
			std::cout << "Thank you for using our platform!";
			exit(0);
		}
	}
}

void Menu::saveAs(Table& newTable)
{
	MyString newFileNameStr;
	validateNewFileName(newFileNameStr);
	std::fstream newFile(newFileNameStr.c_str(), std::ios::out);
	if (!newFile.is_open())
	{
		std::cout << "Could not open file!" << std::endl;
		Sleep(1000);
		system("cls");
		return;
	}
	newTable.saveDataToFile(newFile);
	newFile.close();
	std::cout << "File saved as " << newFileNameStr << std::endl;
	Sleep(1000);
	system("cls");
}

void Menu::edit(Table& newTable)
{
	MyString editStr;
	try
	{
		newTable.editCell(editStr);
		std::cout << "Cell edited successfully!" << std::endl;
		return;
	}
	catch (const std::invalid_argument& exe)
	{
		std::cout << editStr.c_str() << exe.what() << std::endl;
		std::cout << "\nThe value must be:\n1. String (starts and ends with \")\n2. Number (decimal or double, written with . not ,)\n3. Formula, following the given pattern: = (value) (operand) (value) ...\n" << std::endl;
	}
	catch (const std::exception& exe)
	{
		std::cout << exe.what() << std::endl;
	}
	std::cout << "Cell edit failed!" << std::endl;
}

void Menu::closeFile(std::fstream& fs)
{
	char answer[1024]{};
	fs.close();
	std::cout << "File closed successfully!" << std::endl;
	Sleep(1500);
	system("cls");
	std::cout << "Do you want to exit the program?" << std::endl;
	do 
	{
		std::cout << "Your answer must be \"yes\" or \"no\": ";
		std::cin.getline(answer, 1024);
	} 
	while (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0);
	if (strcmp(answer, "yes") == 0)
	{
		system("cls");
		std::cout << "Thank you for using our platform!" << std::endl;
		exit(0);
	}
	else
	{
		std::cout << "You must open a new file, if you want to proceed with the actions!" << std::endl;
	}
	Sleep(2000);
	system("cls");
}

void Menu::executeOption(Table& newTable, int option, std::fstream& fs, const MyString& str)
{
	switch (option)
	{
	case 1:
		std::cout << "File already opened!" << std::endl;
		Sleep(1500);
		system("cls");
		break;
	case 2:
		closeFile(fs);
		break;
	case 3:
		fs.close();
		fs.open(str.c_str(), std::ios::in | std::ios::out | std::ios::trunc);
		newTable.saveDataToFile(fs);
		std::cout << "File saved successfully!" << std::endl;
		Sleep(1500);
		system("cls");
		break;
	case 4:
		saveAs(newTable);
		break;
	case 5:
		edit(newTable);
		system("pause");
		system("cls");
		break;
	case 6:
		newTable.printTable();
		system("pause");
		system("cls");
		break;
	case 7:
		fs.close();
		std::cout << "File closed successfully!" << std::endl;
		Sleep(1500);
		system("cls");
		std::cout << "Thank you for using our platform!";
		exit(0);
		break;
	default:
		break;
	}
}

void Menu::runProgram()
{
	int key = 0;
	key = chooseKey();
	MyString fileName;
	while (key != 1 && key != 7)
	{
		std::cout << "You must open a file first!" << std::endl;
		Sleep(1000);
		system("cls");
		key = chooseKey();
	}
	if (key == 7)
	{
		std::cout << "Thank you for using our platform!" << std::endl;
		exit(0);
	}
	while (true)
	{
		validateNewFileName(fileName);
		std::fstream myFile(fileName.c_str(), std::ios::in | std::ios::out | std::ios::_Nocreate);

		if (checkEmptyFile(myFile))
		{
			std::cout << "Such file does not exist!" << std::endl;
			Sleep(1000);
			system("cls");
			continue;
		}

		Table newTable;
		newTable.exportDataFromFile(myFile);

		int option = chooseKey();

		while (option < 8)
		{
			executeOption(newTable, option, myFile, fileName);
			if (option == 2)
			{
				break;
			}
			option = chooseKey();
		}
	}
}
