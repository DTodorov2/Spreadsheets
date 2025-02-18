# Spreadsheets

The "__Spreadsheets__" project works with files, requiring a file to be opened before any operations can be performed. If the specified file does not exist, the message "__Such file does not exist!__" is displayed, and the user is prompted to enter another filename. Once a file is opened, several actions can be performed, including __printing, closing, saving, saving as a new file, and editing__ a cell. The program does not allow working with multiple files simultaneously.

For a cell value to be valid, it must be one of the following types: a number (integer or floating point), a formula, or a string. A valid string must begin and end with quotation marks. If a string contains " or ,, a \ must be placed before them to be included in the string.<br>

_Example of a __valid__ string_: "eX\amp\"le" → Interpreted as "eX\amp"le"<br>
_Example of an __invalid__ string_: "eX\amp"le"<br>
### Formulas
A valid formula must follow the format: value operation value…, where there must be spaces between each value and operator (except for numbers with a leading sign).<br>

_Example of a __valid__ formula_: = ( R1C2 + R2C2 ) * 3 ^ 2 – ( -2 )<br>
_Example of an __invalid__ formula_: = (-2) * 3^3 + (R1C2+R2C2)<br>
Numbers must use a dot (.) as the decimal separator and must not contain spaces between the number and its sign.

___Printing function___: Displays the file's contents in the console. The number of columns in each row is determined by the maximum number of cells in all rows. If a cell contains invalid data, the program checks for a missing comma and notifies the user. <br>
_Example_: If the value 123”example” is entered, the program will indicate a missing comma and prompt the user with "_Do you want to continue? – y/n_". If yes, "__Invalid__" is recorded in the cell; if no, the program terminates.<br>
If a cell contains a formula, its evaluated result is displayed. The program creates a vector of all numbers and another vector of all operations in the formula. Once two numbers are used, they and their corresponding operator are removed from the vectors. Formulas must be written with spaces between symbols, otherwise, they will be considered invalid.
_Example of a __valid__ formula_: "__= 3 ^ 2 + ( -2 ) * R1C2__"
If a formula contains division by zero (__= 2 / 0__) or exponentiation of a number to a negative power, the result will be "__ERROR__".
Numbers can be written with or without leading signs (e.g., +23).
### File Operations:
___Close file___: Closes the opened file and asks the user if they want to continue. If no, the program exits; otherwise, a new filename is requested.<br>
___Save file___: Saves changes to the currently opened file.<br>
___Save file as___: Saves the data to a new file, requiring the user to provide a filename with a .txt extension.<br>
___Edit cell___: Allows the user to modify a specific cell by entering the column and row number, followed by the new value. The program provides different messages based on the input:<br>
"_Invalid index!_" → The specified cell does not exist.<br>
" _is invalid data type!_" → The entered value is not a valid data type; an explanation is displayed, followed by "_Cell edit failed!_".<br>
"_Cell edited successfully!_" → The cell has been successfully updated.<br>
___Exit program___: closes the application, ensuring that the opened file is properly closed before termination.
