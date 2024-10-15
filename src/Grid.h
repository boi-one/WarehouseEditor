#pragma once
#include "Camera.h"

class Grid 
{
public:
	bool active = true;
	float gridSize = 100;
	float tileScaled;
	ImVec2 position;
	void Update(const Camera& camera);
	void DrawGrid(ImDrawList* draw_list, const Camera& camera);
};
