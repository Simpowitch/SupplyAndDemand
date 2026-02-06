#pragma once
#include <array>
#include <limits>

class InputManager
{
public:
	void Update();
	bool WasKeyPressed(const unsigned char key) const
	{
		return currentState[key] && !lastState[key];
	}
	bool WasKeyReleased(const unsigned char key) const
	{
		return !currentState[key] && lastState[key];
	}
	bool IsKeyHeld(const unsigned char key) const
	{
		return currentState[key];
	}

private:
	std::array<bool, std::numeric_limits<unsigned char>::max() + 1> currentState{};
	std::array<bool, std::numeric_limits<unsigned char>::max() + 1> lastState{};
};

//int ReadNumericInput();
//bool ReadYesNoInput();
//char ReadCharInput();

