#pragma once
#include "Camera.h"

class Grid 
{
public:
	bool active = true;
	int gridSize = 100;
	void DrawGrid(ImDrawList* draw_list, Camera& camera);
};
