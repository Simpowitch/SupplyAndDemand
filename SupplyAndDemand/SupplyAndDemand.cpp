#include "InputManager.h"
#include "GameWorld.h"

int main()
{
	char ch = 0;

	GameWorld gameWorld = {};
	gameWorld.Init(100.0f, 100.0f, 10);

	while (true)
	{
		auto key = Input::ReadCharInput();

		if (key == 'q')
			break;

		gameWorld.Tick();
	}

	return 0;
}

