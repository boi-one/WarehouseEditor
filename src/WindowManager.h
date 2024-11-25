#pragma once
#include <iostream>
#include "LayerManager.h"
#include "Grid.h"

using std::cout;
using std::endl;

/// <summary>
/// The class which needs the most refactoring. for now it is just a mess but the goal for this class is to divide all the ImGui code for the different windows. 
/// for example the settings and the canvas window.
/// </summary>
class WindowManager
{
public:
	static inline bool focusedWindow;

	WindowManager()
	{
		LayerManager::AddLayer();
		LayerManager::currentLayer = &LayerManager::allLayers.at(0);
	}

	/// <summary>
	/// Draw the canvas window
	/// </summary>
	void DrawCanvas();

	/// <summary>
	/// Draw the settings window
	/// </summary>
	void DrawSettings();

	/// <summary>
	/// Draw everything
	/// </summary>
	void Draw();

	/// <summary>
	/// Used to draw all of the things to the screen such as conveyors the grid
	/// </summary>
	void Render();

public:
	Camera camera;
	Grid grid;
};

