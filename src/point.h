#pragma once
#include <vector>
#include "imgui.h"
class point
{
public:
	ImVec2 position;
	std::vector<point> connections;

	point(ImVec2 position = ImVec2(0, 0))
	{
		this->position = position;
	}

	void Draw(const ImVec4& color, const float thickness);
};