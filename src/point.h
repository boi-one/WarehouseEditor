#pragma once
#include <vector>
#include "imgui.h"
#include "Camera.h"

class point
{
public:
	ImVec2 position;
	std::vector<point> connections;
	bool selected;

	point(ImVec2 position = ImVec2(0, 0))
	{
		this->position = position;
	}

	void Draw(const ImVec4& color, Camera& camera, const float thickness);
};