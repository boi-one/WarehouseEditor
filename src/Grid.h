#pragma once
#include "Camera.h"

class Grid 
{
public:
	bool active = true;
	float padding = 200;
	float tileSize = 100;
	float zoomedSize = 0;
	ImVec2 position;
	ImVec2 size;
	void Update(const Camera& camera);
	void Draw(ImDrawList* draw_list, const Camera& camera);
};
