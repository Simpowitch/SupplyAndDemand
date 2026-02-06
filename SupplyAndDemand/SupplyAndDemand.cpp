#include "InputManager.h"
#include "World.h"

int main()
{
	char ch = 0;

	World world = {};
	world.Init(100.0f, 100.0f, 10);

	while (true)
	{
		auto key = Input::ReadCharInput();

		if (key == 'q')
			break;

		world.Tick();
	}

	return 0;
}

