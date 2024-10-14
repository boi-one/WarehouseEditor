#include "Grid.h"

void Grid::DrawGrid(ImDrawList* draw_list, Camera& camera)
{
	float gridSpacing = gridSize * camera.zoom;

	float startX = fmod(camera.position.x, gridSpacing);
	float startY = fmod(camera.position.y, gridSpacing);

	for (float x = startX; x < camera.size.x; x += gridSpacing)
	{

		ImVec2 startLine = camera.ToScreenPosition(ImVec2(x, 0));
		ImVec2 endLine = camera.ToScreenPosition(ImVec2(x, camera.size.y));
		draw_list->AddLine(startLine, endLine, ImColor(200, 0, 0, 255), .5f);
	}
	for (float y = startY; y < camera.size.y; y += gridSpacing)
	{
		ImVec2 startLine = camera.ToScreenPosition(ImVec2(0, y));
		ImVec2 endLine = camera.ToScreenPosition(ImVec2(camera.size.x, y));

		draw_list->AddLine(startLine, endLine, ImColor(0, 200, 0, 255), .5f);
	}
}