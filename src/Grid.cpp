#include "Grid.h"

void Grid::DrawGrid(ImDrawList* draw_list, Camera& camera)
{
	zoomedGridSpacing = gridSize * camera.zoom;

	float startX = fmod(camera.position.x, zoomedGridSpacing);
	float startY = fmod(camera.position.y, zoomedGridSpacing);

	for (float x = startX; x < camera.size.x; x += zoomedGridSpacing)
	{

		ImVec2 startLine = ImVec2(x, 0);
		ImVec2 endLine = ImVec2(x, camera.size.y);
		draw_list->AddLine(startLine, endLine, ImColor(200, 0, 0, 255), .5f);
	}
	for (float y = startY; y < camera.size.y; y += zoomedGridSpacing)
	{
		ImVec2 startLine = ImVec2(0, y);
		ImVec2 endLine = ImVec2(camera.size.x, y);

		draw_list->AddLine(startLine, endLine, ImColor(0, 200, 0, 255), .5f);
	}
}