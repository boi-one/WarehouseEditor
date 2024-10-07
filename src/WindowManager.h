#pragma once
#include <iostream>
#include "LayerManager.h"

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
	void DrawGrid(int gridSize, int row, int column, ImVec2 startPos, Camera& camera);
	void Draw();

public:
	inline static bool running = true;
	Camera camera;

private:
	bool editMode = true;
	bool snapping = false;
	bool newConveyor = true;
	bool showNewLine = true;
	bool grid = true;
	bool showShortcuts = false;
};

