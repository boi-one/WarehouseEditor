#pragma once
#include <vector>
#include "imgui.h"
#include "Camera.h"

/// <summary>
/// The point is what a conveyor is made up of. each conveyor is just a list of points and the branches of the conveyors are points which are in the connections vector of the specific point.
/// </summary>
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

	/// <summary>
	/// Draws the point and all of the connections of this specific point
	/// </summary>
	/// <param name="color"> is the color of this point</param>
	/// <param name="camera"> is used to convert to world position</param>
	/// <param name="thickness"> is how thick the lines between the points are </param>
	void Draw(const ImVec4& color, Camera& camera, const float thickness);
};