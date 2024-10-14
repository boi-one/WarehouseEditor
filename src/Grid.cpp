#include "Grid.h"

void Grid::Update(const Camera& camera)
{
	zoomedSize = tileSize * camera.zoom;
}

void Grid::Draw(ImDrawList* draw_list, const Camera& camera)
{
	position = Tools::SubImVec2(camera.position, padding);
	size.x = camera.size.x + padding;
	size.y = camera.size.y + padding;

	for (int x = position.x; x < size.x; x += zoomedSize)
	{
		ImVec2 start = ImVec2(x, 0);
		ImVec2 end = ImVec2(x, size.y);
		draw_list->AddLine(start, end, ImU32(ImColor(255, 255, 255, 255)), 1);
	}

	for (int y = position.y; y < size.y; y += zoomedSize)
	{
		ImVec2 start = ImVec2(0, y);
		ImVec2 end = ImVec2(size.x, y);
		draw_list->AddLine(start, end, ImU32(ImColor(255, 255, 255, 255)), 1);
	}
}