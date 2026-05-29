#include <iostream>
#include "Settings.h"
#include "Timer.h"
#include "InputManager.h"
#include "WorldModel.h"
#include "WorldController.h"
#include "WorldView.h"
#include "Database.h"
#include "Goods.h"
#include "TransporterView.h"
#include "ManufacturerView.h"
#include <memory>

int main()
{
	LoadSettings();

	Database<Goods> goodsDatabase;
	goodsDatabase.Load("resources/goods");
	InputManager inputManager;
	Timer timer;
	WorldModel worldModel(500.0f, 1500.0f);
	WorldController worldController(&worldModel);
	WorldView root_view(&worldModel, &goodsDatabase);
	root_view.name = "Main Menu";
	
	auto manufacturerView = std::make_unique<ManufacturerView>(&worldModel, &goodsDatabase);
	manufacturerView->name = "Manufacturers";
	auto transporterView = std::make_unique<TransporterView>(&worldModel, &goodsDatabase);
	transporterView->name = "Transporters";
	root_view.AddChild(std::move(manufacturerView));
	root_view.AddChild(std::move(transporterView));

	while (true)
	{
		auto deltaTime = timer.Update();
		inputManager.Update();
		if (inputManager.WasKeyPressed('Q'))
		{
			std::cout << "Q was pressed, exiting...\n";
			break;
		}

		worldController.ParseInput(&inputManager);
		worldController.Update(deltaTime);
		root_view.ParseInput(&inputManager);
		root_view.Draw();

		//std::cout << "Time between frames: " << deltaTime << " seconds\n";
	}

	return 0;
}

