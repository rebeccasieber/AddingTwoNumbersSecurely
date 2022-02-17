/*
Rebecca Sieber
CSC129 - 470
Project : BufferOverflow
Description : This program adds two positive integers and prints their sum.
			  This program focuses on input validation and confirming that input
			  is infact a positive integer and properly hadling situations where
			  input is not valid. This program also checks for int
			  overflow not only on the user input side, but also when adding two 
			  integers. UPDATE: This version now accepts and removes commas from inputted
			  integers. It also adds commas as needed to the ending printout for better
			  readability. Finally, this version protects from buffer overflow and
			  off-by-one errors by adding two integers as strings into a stack container
			  of integers.

			  
Due: 11/28/2021
*/

#include <iostream>													//std::cin and std::count
#include <iomanip>													//for formatting text to the screen
#include <string>													//string class
#include <stack>													//if adding two integers results in overflow, storing sum in stack instead of int

/*FUNCTION DECLARATIONS*/
void printIntAddProblem(std::string int1, std::string int2);
bool checkIfPosInt(std::string someString);
std::stack<int> add2NumAsStrings(std::string int1, std::string int2);
std::string addCommas(std::string& someInt);
void printStackWithCommas(std::stack<int> someStack);

int main()
{
	std::string userInput1;											//Holds user input as string since getline is used and not cin
	std::string userInput2;											//Holds user input as string since getline is used and not cin
	int threeStrikes = 0;											//Counter keeps track of how many wrong inputs have been recieved and terminates program if input is incorrect 3 times.
	std::stack<int> sum2Ints;										//Stores the sum of two integers as a stack to avoid buffer/integer overflow

	std::cout << "This program adds two positive integers" << std::endl;

	/*Starting while loop to continue to request numnber from user until they input the number correctly, or they
	incorrectly input a number 3 times*/
	while (threeStrikes <= 3)
	{
		std::cout << "Enter num1: ";
		std::getline(std::cin, userInput1);															//using getline so if user included space the whole input is considered.

		userInput1.erase(std::remove(userInput1.begin(), userInput1.end(), ','), userInput1.end()); //removing commas from user input in case user enteres integer in the form of 1,234,567
		
		if (checkIfPosInt(userInput1) == true)														//using function to see if whole input is positive integer, if it is then breaking from loop
			break;

		/*Else User did not enter a positive integer, increasing wrong guess counter. Printing error message and forcing
		user to guess again. If it's their 3rd strike, printing error message and terminating the program*/
		else
		{
			threeStrikes++;

			if (threeStrikes == 3)
			{
				std::cout << "I'm sorry, you've entered incorrectly 3 times. \nProgram terminating." << std::endl;
				return -1;
			}
			else
			{
				std::cout << "I'm sorry, please enter a positive integer." << std::endl;
				continue;
			}
		}
	}

	threeStrikes = 0;												//resetting wrong input counter for input next number

	/*Starting while loop to continue to request numnber from user until they input the number correctly, or they
	incorrectly input a number 3 times*/
	while (threeStrikes <= 3)
	{
		std::cout << "Enter num2: ";
		std::getline(std::cin, userInput2);															//using getline so if user included space the whole input is considered.

		userInput2.erase(std::remove(userInput2.begin(), userInput2.end(), ','), userInput2.end()); //removing commas from user input in case user enteres integer in the form of 1,234,567

		if (checkIfPosInt(userInput2) == true )														//using function to see if whole input is positive integer, if it is then breaking from loop
			break;																					

		/*Else User did not enter a positive integer, increasing wrong guess counter. Printing error message and forcing
		user to guess again. If its their 3rd strike, printing error message and terminating the program*/
		else
		{
			threeStrikes++;

			if (threeStrikes == 3)
			{
				std::cout << "I'm sorry, you've entered incorrectly 3 times. \nProgram terminating." << std::endl;
				return -1;
			}
			else
			{
				std::cout << "I'm sorry, please enter a positive integer." << std::endl;
				continue;
			}
		}
	}

	sum2Ints = add2NumAsStrings(userInput1, userInput2);	//calulating the sum of the two int strings and saving into a stack

    printIntAddProblem(userInput1, userInput2);				//Calling function to print solution in a pretty fashion
	printStackWithCommas(sum2Ints);							//Printing the sum stack with commas for readability

	return 0;
}


/*FUNCTION DEFINITIONS*/

/*This fucntion will confirm that every character in an input string is in fact a number. Therefore
it will automatically check for negative and float values as '-' and '.' are not numbers as well as for spaces*/
bool checkIfPosInt(std::string someString)
{
	//int strAsInt;

	if (someString == "")											//If string is empty, return false
		return false;
	for (int i = 0; i < someString.length(); i++)					//looping through each character int the string
		if (isdigit(someString[i]) == 0)							//checking to see if char is a digit or not
			return false;											//when one non numeric value is found, return false
	return true;													//No non digit characters found in string, and string is not too large to be converted to an int, return true

}

/*This function takes two integers and prints the problem/solution in a nice and
easy to read fashion as per the instruction guidlines */
void printIntAddProblem(std::string int1, std::string int2)
{
	std::string bigIntString = "";
	std::string littleIntString = "";

	//Figuring out which string is bigger to help figure out how big the print board should be
	if (int1.length() > int2.length())
	{
		bigIntString = int1;
		littleIntString = int2;
	}
	else
	{
		bigIntString = int2;
		littleIntString = int1;
	}
	std::cout << "\n" << std::setw(bigIntString.length()+8);
	std::cout << addCommas(int1) << std::endl;
	std::cout << "+" << std::setw(bigIntString.length()+7) << addCommas(int2) << std::endl;
	for (int i = 0; i < bigIntString.length()+9; i++)
		std::cout << "-";
	std::cout << std::endl;
	std::cout << "=";

	/*Formatting sum to line up with the rest of the numbers. There should have been a nicer way to do this but i couldnt figure it out*/
	if (bigIntString.length() < 4)
		std::cout << "       ";
	else if (bigIntString.length() < 7)
		std::cout << "      ";
	else if (bigIntString.length() < 10)
		std::cout << "     ";
	else if (bigIntString.length() < 13)
		std::cout << "    ";
	else if (bigIntString.length() < 16)
		std::cout << "   ";
	else if (bigIntString.length() < 19)
		std::cout << "  ";
	else
		std::cout << " ";
}

/*This function takes two integers as strings, and adds the integers, saving the sum into a stack. This is so buffer and
integer overflow do not occur when adding 2 large numbers*/
std::stack<int> add2NumAsStrings(std::string int1, std::string int2)
{
	std::string bigIntString = "";															//Keeps track of which of the 2 provided integers as strings is bigger
	std::string littleIntString = "";														//Keeps track of which of the 2 provided integers as strings is smaller
	std::stack<int> mySumStack;																//Storing sum integer, which is too big to be stored as an int into a stack.
	int sumDigit = 0;																		//stores sum of 2 digits in big and small ints
	int carryBit = 0;																		//this will = either 1 or zero if adding for sumdigit requires "carrying the one"
		
	/*Determining which of the 2 integers is the bigger one and assigning accordingly*/
	if (int1.length() >= int2.length()) { bigIntString = int1; littleIntString = int2;}
	else{littleIntString = int1; bigIntString = int2;}


	/*Forcing strings to be the same length by adding the correct number of 0s to the front of the smallest string*/
	while (littleIntString.length() < bigIntString.length())
	{
		littleIntString = "0" + littleIntString;
	}

	/*Adding each character/int to each other starting with last char/ints and working up to the first*/
	for (int i = littleIntString.length() - 1; i >= 0; i--)
	{
		sumDigit = carryBit + ((int)littleIntString[i] - 48) + ((int)bigIntString[i] - 48); //convering char to int
		if (sumDigit > 9)																	//if the sum of the two ints is >9 then 1 must be "carried"
		{
			carryBit = 1;																	//carrying the one for next digits
			sumDigit = sumDigit - 10;														//Taking only the second number
		}
		else
			carryBit = 0;																	//resetting carry bit back to zero for the next loop

		mySumStack.push(sumDigit);															//Adding sum digit the stack
	}

	/*If the last 2 numbers added needs to carry, adding the one to the top of the stack*/
	if (carryBit == 1)
		mySumStack.push(1);

	return mySumStack;

}
/*This function adds commas to a number (saved as a string) to improve readabilty when printing*/
std::string addCommas(std::string& someInt)
{

	for (int i = someInt.length() - 3; i >= 1; i = i - 3)
		someInt.insert(i, 1, ',');
	
	return someInt;

}

/*This function prints a stack of integetrs and adds commas as needed for readability like 123,456,789*/
void printStackWithCommas(std::stack<int> someStack)
{
	//saving size of the stack before popping to print top
	int stackSize = someStack.size();

	//Adding a comma if needed
	for (int i = 0; i < stackSize; i++)
	{

		if (stackSize % 3 == 0)						//123,346,789
		{
			if (i != 0 && i % 3 == 0)
				std::cout << ',';
		}
		else if (stackSize % 3 == 1)				//1,234,567
		{
			if (i % 3 == 1)
				std::cout << ',';
		}
		else										//stackSize % 3 == 2 //12,345,678
		{
			if (i % 3 == 2)
				std::cout << ',';
		}

		//Printing top and popping to show next as top
		std::cout << someStack.top();
		someStack.pop();
	}

}