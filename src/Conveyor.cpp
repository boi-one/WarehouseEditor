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

point* Conveyor::FindClosestPoint(std::vector<point>& list, ImVec2& origin, Camera& camera, float range)
{
	point* closestPoint = 0;

	range = 9999999; //bad fix

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

ImVec2 Conveyor::ClosestVector(Camera& camera, std::vector<point>& path, ImVec2 mouseWorldPos)
{
	ImVec2 endPosition;
	ImVec2 closestPointToMouse = Conveyor::FindClosestPoint(path, Mouse::liveMousePosition, camera, 999'999)->position;

	if (Tools::Magnitude(closestPointToMouse, Mouse::liveMousePosition) < 30)
	{
		endPosition = closestPointToMouse;
	}
	else
		endPosition = Mouse::liveMousePosition;

	return endPosition;
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

