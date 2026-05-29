#include "View.h"
#include <iostream>

void View::ParseInput(const InputManager* inputManager)
{
	if (inputManager->WasKeyPressed('0'))
	{
		currentSubView = -1;
	}
	else
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			char key = '1' + i;
			if (inputManager->WasKeyPressed(key))
			{
				currentSubView = i;
				break;
			}
		}
	}
}

void View::Draw()
{
	system("cls");
	buffer.str("");
	buffer.clear();

	if (currentSubView >= 0)
	{
		auto& view = GetChildByIndex(currentSubView);
		view.Draw();
	}
	else
	{
		DrawSelf();
	}

	std::cout << buffer.str();
}

void View::DrawSelf()
{
	PrintLine("Navigation:");
	PrintLine("0: Back");

	PrintLine("");
	PrintLine("--------------");
	PrintLine("");

	PrintLine(name.c_str());
	PrintLine("");

	int childSize = children.size();
	if (childSize > 0)
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			buffer << (i + 1) << ": " << children[i]->name << std::endl;
		}
	}
}

void View::PrintLine(const char* message)
{
	buffer << message << '\n';
}