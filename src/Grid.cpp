#include "Grid.h"

void Grid::Update(const Camera& camera)
{
	zoomedGridSpacing = gridSize * camera.zoom;

	//position.x = fmod(camera.position.x, zoomedGridSpacing);
	//position.y = fmod(camera.position.y, zoomedGridSpacing);

	position.x = fmod(camera.position.x, gridSize) * zoomedGridSpacing;
	position.y = fmod(camera.position.y, gridSize) * zoomedGridSpacing;
}

void Grid::DrawGrid(ImDrawList* draw_list, const Camera& camera)
{
	for (float x = position.x; x < camera.size.x; x += zoomedGridSpacing)
	{
		ImVec2 startLine = ImVec2(x, 0);
		ImVec2 endLine = ImVec2(x, camera.size.y);
		draw_list->AddLine(startLine, endLine, ImColor(200, 0, 0, 255), .5f);
	}
	for (float y = position.y; y < camera.size.y; y += zoomedGridSpacing)
	{
		ImVec2 startLine = ImVec2(0, y);
		ImVec2 endLine = ImVec2(camera.size.x, y);

		draw_list->AddLine(startLine, endLine, ImColor(0, 200, 0, 255), .5f);
	}
}