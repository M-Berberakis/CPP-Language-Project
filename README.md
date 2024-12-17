THESE ARE INSTRUCTIONS ON HOW TO PROPERLY EXECUTE THE SOURCE CODE:

1. The user must have the latest version of Visual Studio Community 2022

2. The user will have to click the "Compiler.sln", which will open Visual Studio

3. It is likely that the user will be propmpted via a pop-up window to use a certain version
it is impportant that the user click the "OK" button. Otherwise issues might arrise.

4. Then the user will have to head to the Solution Explorer which by default is located
on the right side of the IDE. Then the user should click on the "Grammar Files" folder, which 
will reveal two files, "Lexer.l" and "Parser.y"

5. The user must firstly, right click on the "Lexer.l" file and should click the properties option
from the pop-up menu.

6. A window named "Lexer.l Property Pages" should open
	- The user must head to the left side and click on the "Configuration Properties" from the left side menu.
	- In the General menu, the user should click on the "Excluded from Build" option and select "No"
	- Then they should click on the item type and select "Custom Build Tool"
	- Afterwards the user should head to the Custom Build Too option from the left side menu and click on General.
	- In the Compiler Line field, the user should fill it out with the following command: 
	"SolutionDir Compiler_Tools bin flex" oLexer.c Lexer.l"
	- In the Description field, the following text should be typed out:
	"Running Flex"
	- Finally in the Outputs field, the user should type of the following text:
	"Lexer.c"
	- The user should then click "Apply" and close the window.
	
7. The user must then right-click on the "Parser.y" file and click on the properties option.

8. A window name "Parser.y Property Pages" should open
	- The user must head to the left side and click on the "Configuration Properties" from the left side menu.
	- In the General menu, the user should click on the "Excluded from Build" option and select "No"
	- Then they should click on the item type and select "Custom Build Tool"
	- Afterwards the user should head to the Custom Build Too option from the left side menu and click on General.
	- In the Compiler Line field, the user should fill it out with the following command: 
	"set PATH=$( SolutionDir Compiler_Tools bin;% PATH%bison d Parser.y"
	- In the Description field, the following text should be typed out:
	"Running Bison".
	- Finally in the Outputs field, the user should type of the following text:
	"Parser.tab.h;Parser.tab.c;%(;%(Outputs)".
	- The user should then click "Apply" and close the window.

9. Afterwards, the user should click on the "Tools" option which is located on the top menu of the IDE and
click on the option "Options...".

10. A new window will pop-up named "Options"
	- From the left side-menu, the user should head to the "Text Editor" option and
	click on the "File Extensions" option.
	- On the sligh right side of the window, there should be a field name "Extensions:"
	- The user must type the character "L" in lowercase and click on the "Add" button.
	- The user must type the character "Y" in lowercase and click on the "Add" button.
	- The user should then click on the "OK" button which will close the pop-up window.
	
11. Then, the user should choose from the drop-down menu the "Debug" option, which is located
underneath the "Debug" option in the top-menu.

12. The user should also select the drop-down menu which is located to the right of the previous
drop-down menu and select "x86".

13. Finally the user should click on the "Build" option in the top-menu and click on "Rebuild Solution".

14. The user can now click on the "Local Windows Debugger", which will create the "Build" folder in path of the project.

15. In order to further understand how to use the program, the reader should read the "README.txt" file.


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Syntax
What follows are the syntax rules in order for the language to be correctly:
The instructions are strictly case-sensitive, which means that all instructions should be written in uppercase only!
In order for the user to end each statement, they will have to use the vertical bar character (“|”).
The comments in this case are similar to python, meaning that a single lined comment is stated with a pound sign (“#”) .
The code block logic is similar to that of the C programming language, which means that in order to open a block a left curly bracket (“{“) and a right curly bracket in order to close the code block (“}”).
It is important that whitespace is properly used in between keywords and identifiers for the proper use of the language.
The language does now allow for the declaration of variable names that are similar to those of keywords, the only supported variable name is the letter “x”.
If a syntax error is present in the code file, the parser will present an error in the syntax of the code and will close.
LAG Language TOKENS
These are the instructions tokens that should be used for this particular language:
{ - Opening Code Block.
} – Closing Code Block.
PRINT - Prints value inserted inside parentheses.
( - Opening Left Parentheses.
) – Closing Right Parentheses.
IF - Logical if Statement.
INCASE - Loops code that is within the code blocks if a statement is true.
REPEAT - It is used in combination with the INCASE Token.
>> - Assignment of variable value.
TRUE  - Returns true if statement is correct.
FALSE - Returns false if statement is incorrect.
LAG Language Logic Operators
>= -Checks whether the value is greater or equal to another value.
<= - Checks whether the value is lesser or equal to another value.
?= - Checks whether the value is equal to another value.
< - Checks whether the value is greater than another value.
> - Checks whether the value is less than another value.
! – Logical NOT operator.
|| - Logical OR operator.
&& - Logical AND operator.
<> - Logical NEQ operator.
LAG Language Arithmetic Operators
+ - Adds two values together.
“-” - Subtracts a value from another. 
* - Multiplies two values. 
/ – Divides two values.


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


LAG LANGUAGE FUNCTIONALITY INSTRUCTIONS
=======================================

In order to use the program correctly, the user has to follow these instructions:

1. Place the contents from the "Examples" folder to the "Executables" folder.
2. Once the uesr user clicks the compile.bat file, the first code example will be executed.
3. If the user wants to test out the rest of the code examples that are provided, they will have to
right click on the "compile.bat" file and edit it with their preffered text editor. They will be presented
with the following contents inside the text file: "Compiler example_code_1.LAG". The user will have to write the
name of the example_code file they want to run, for example "Compiler example_code_3.LAG".
4. Once these changes have been made, the user can click to execute the "compile.bat" file in order for the code 
to be executed.
5. Some of the code examples have errors in purpose in order to show the ability of the language of recognizing 
syntax error and halting the execution of the program.
