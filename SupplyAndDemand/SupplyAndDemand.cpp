#include <iostream>
#include "Settings.h"
#include "Timer.h"
#include "InputManager.h"
#include "WorldModel.h"
#include "WorldController.h"
#include "WorldView.h"
#include "Database.h"
#include "Goods.h"

int main()
{
	LoadSettings();

	Database<Goods> goodsDatabase;
	goodsDatabase.Load("resources/goods");
	InputManager inputManager;
	Timer timer;
	WorldModel worldModel(500.0f, 1500.0f);
	WorldController worldController(&worldModel, &inputManager);
	WorldView worldView(&worldModel, &inputManager, &goodsDatabase);
	

	while (true)
	{
		auto deltaTime = timer.Update();
		inputManager.Update();
		if (inputManager.WasKeyPressed('Q'))
		{
			std::cout << "Q was pressed, exiting...\n";
			break;
		}

		worldController.ParseInput();
		worldController.Update(deltaTime);
		worldView.Draw();

		//std::cout << "Time between frames: " << deltaTime << " seconds\n";
	}

	return 0;
}

