#include "InputManager.h"
#include "World.h"
#include <iostream>
#include <Windows.h>
#include "Timer.h"
#include "Settings.h"

int main()
{
	LoadSettings();

	World world(500.0f, 1500.0f);
	world.Init();

	InputManager inputManager;
	Timer timer;
	while (true)
	{
		auto deltaTime = timer.Update();
		inputManager.Update();
		if (inputManager.WasKeyPressed('Q'))
		{
			std::cout << "Q was pressed, exiting...\n";
			break;
		}
		
		world.Update(deltaTime);
		//std::cout << "Time between frames: " << deltaTime << " seconds\n";
	}

	return 0;
}

