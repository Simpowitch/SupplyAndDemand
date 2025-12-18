#include "InputManager.h"
#include "iostream"

namespace Input
{
	static constexpr int INPUT_BUFFER_SIZE = 1000;

	int ReadNumericInput()
	{
		int input;
		while (true)
		{
			std::cin >> input;
			if (std::cin.fail())
			{
				std::cin.clear(); // clear the error flags
				std::cin.ignore(INPUT_BUFFER_SIZE, '\n'); // discard input
				std::cout << "Invalid input. Please only insert numbers\n";
				continue;
			}
			std::cin.ignore(INPUT_BUFFER_SIZE, '\n'); // discard input
			return input;
		}
	}


	bool ReadYesNoInput()
	{
		char inputChar;
		while (true)
		{
			inputChar = ReadCharInput();

			if (inputChar == 'Y' || inputChar == 'y')
			{
				return true;
			}
			else if (inputChar == 'N' || inputChar == 'n')
			{
				return false;
			}
			else
			{
				std::cout << "Invalid input. Please enter Y or N\n";
			}
		}
	}

	char ReadCharInput()
	{
		char inputChar;
		while (true)
		{
			std::cin >> inputChar;
			if (std::cin.fail())
			{
				std::cin.clear(); // clear the error flags
				std::cin.ignore(INPUT_BUFFER_SIZE, '\n'); // discard input
				std::cout << "Invalid input. Please enter a character\n";
				continue;
			}
			std::cin.ignore(INPUT_BUFFER_SIZE, '\n'); // discard input
			return inputChar;
		}
	}
}
