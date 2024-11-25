#include "Conveyor.h"

ImVec2 Conveyor::AveragePointsPosition(std::vector<point> path)
{
	ImVec2 Average;

	std::vector<ImVec2> positions;

	for (int i = 0; i < path.size(); i++)
	{
		positions.push_back(path[i].position);
	}

	return Tools::AverageVec2(positions);
}

point* Conveyor::FindClosestPointInWorld(std::vector<point>& list, ImVec2& origin, Camera& camera, float range)
{
	point* closestPoint = 0;

	for (point& p : list)
	{
		ImVec2 convertedP = camera.ToWorldPosition(p.position);
		float distance = Tools::Magnitude(convertedP, origin);
		if (distance < range)
		{
			range = distance;
			closestPoint = &p;
		}
	}

	return closestPoint;
}

void Conveyor::NewPoint(ImVec2 mouseWorldPos)
{
	point& temp = selectedPoint->connections.emplace_back(mouseWorldPos);
	path.emplace_back(temp);
	selectedPoint = &path[path.size() - 1];
}

void Conveyor::Draw(ImVec4& color, float thickness, ImVec2& mouseWorldPos, Camera& camera)
{
	for (point& p : path)
	{
		ImGui::GetWindowDrawList()->AddCircleFilled(camera.ToWorldPosition(p.position), 10 * camera.zoom, ImColor(color), 100);
		p.Draw(color, camera, thickness);
	}
}
