#pragma once
#include <iostream>
#include "LayerManager.h"
#include "Grid.h"

using std::cout;
using std::endl;

class WindowManager
{
public:
	static inline bool focusedWindow;

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
	Camera camera;
	Grid grid;
};

