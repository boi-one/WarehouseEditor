#include "Conveyor.h"

//change the conveyor draw code so every conveyor draws their own lines

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

point* Conveyor::FindClosestPoint(std::vector<point>& list, ImVec2& origin, Camera& camera, float range = 999'999)
{
	point* closestPoint = &list[0];

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

void Conveyor::Edit(Camera& camera)
{
	selectedPoint = FindClosestPoint(path, Mouse::rightMouseClickPos, camera, 999'999);

	/*if (Mouse::clickedRight && Tools::Magnitude(selectedPoint->position, Mouse::liveMousePosition) > 60)
	{
		this->edit = false;
	}*/
}

ImVec2 Conveyor::CloseToPoint(Camera& camera, std::vector<point>& path, ImVec2 mouseWorldPos)
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

void Conveyor::NewPoint(ImVec2 mouseWorldPos) //laat het snappen als het in de buurt is van een point en laat het werken in snapping mode
{
	point newPoint(Mouse::liveMousePosition);
	selectedPoint->connections.push_back(newPoint);
	selectedPoint = &newPoint;
	path.push_back(*selectedPoint);
}


void Conveyor::Update(Camera& camera)
{
	if (edit)
	{
		Edit(camera);
	}
}

void Conveyor::Draw(ImVec4& color, float thickness, ImVec2& mouseWorldPos, Camera& camera)
{
	if (edit) //draw newline
	{
		ImGui::GetWindowDrawList()->AddLine(camera.ToWorldPosition(selectedPoint->position), mouseWorldPos, ImColor(ImVec4(0, 1, 0, 1)), thickness);
	}

	for (point& p : path)
	{
		ImGui::GetWindowDrawList()->AddCircleFilled(p.position, 10 * camera.zoom, ImColor(color), 100);
		p.Draw(color, thickness);
	}
}

