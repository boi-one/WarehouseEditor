#pragma once
#include "Camera.h"

/// <summary>
/// the grid in the background so you can easily see that you are moving
/// </summary>
class Grid 
{
public:
	bool active = true;
	float gridSize = 100;
	float tileScaled;
	ImVec2 position;

	/// <summary>
	/// Updates the grid so it moves on the screen
	/// </summary>
	/// <param name="camera"> is used for the position of the camera to calculate how much of a tile to draw</param>
	void Update(const Camera& camera);

	/// <summary>
	/// draws the grid to the screen
	/// </summary>
	/// <param name="draw_list"> is the way ImGui draws to windows, this is needed to display the grid</param>
	/// <param name="camera"> is used to know how big the screen is</param>
	void DrawGrid(ImDrawList* draw_list, const Camera& camera);
};
