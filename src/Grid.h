#pragma once
#include "Camera.h"

class Grid 
{
public:
	bool active = true;
	float padding = 200;
	float tileSize = 100;
	float tileScaled = 0;
	ImVec2 position;
	ImVec2 snapPosition;
	ImVec2 begin;
	ImVec2 end;

	bool temp = false; 

	void Update(const Camera& camera);
	void Draw(ImDrawList* draw_list, Camera& camera);
};
