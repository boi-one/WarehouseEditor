#pragma once
#include <iostream>
#include "LayerManager.h"
#include "Grid.h"

using std::cout;
using std::endl;

class WindowManager
{
public:
	WindowManager()
	{
		LayerManager::AddLayer();
		LayerManager::currentLayer = &LayerManager::allLayers.at(0);
	}
	void DrawCanvas();
	void DrawSettings();
	void Draw();

	void Render();

public:
	inline static bool running = true;
	Camera camera;
	Grid grid;

private:
	bool editMode = true;
	bool snapping = false;
	bool newConveyor = true;
	bool showNewLine = true;
	bool showShortcuts = false;
};

