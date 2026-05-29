#pragma once
#include <vector>
#include <string>
#include "InputManager.h"
#include <memory>
#include <sstream>

class View
{
public:
	virtual ~View() = default;

	void Draw();
	virtual void ParseInput(const InputManager* inputManager);
	void AddChild(std::unique_ptr<View> view) { children.push_back(std::move(view)); }
	int GetChildCount() const { return children.size(); } 
	View& GetChildByIndex(int index) { return *children[index]; }

	std::string name;
protected:
	virtual void DrawSelf();
	void PrintLine(const char* message);

	std::ostringstream buffer;
private:
	std::vector<std::unique_ptr<View>> children;
	int currentSubView = -1;
};

