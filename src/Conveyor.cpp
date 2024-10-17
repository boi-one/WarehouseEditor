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

point Conveyor::FindClosestPoint(std::vector<point>& list, ImVec2& origin, Camera& camera, float range = 999'999)
{
	point closestPoint;

	for (point& p : list)
	{
		ImVec2 convertedP = camera.ToWorldPosition(p.position);
		float distance = Tools::Magnitude(convertedP, origin);
		if (distance < range)
		{
			range = distance;
			closestPoint = p;
		}
	}

	return closestPoint;
}

void Conveyor::Edit(Camera& camera)
{
	if (path.size() > 1)
		selectedPoint = FindClosestPoint(path, Mouse::leftMouseClickPos, camera);
	else
		selectedPoint = path[0];

	/*if (Mouse::clickedRight && Tools::Magnitude(selectedPoint.position, Mouse::liveMousePosition) > 30)
	{
		this->edit = false;
	}*/
}

void Conveyor::NewPoint()
{
	std::cout << "click " << std::endl;
	point newPoint(Mouse::liveMousePosition);
	path.push_back(newPoint);
	selectedPoint.connections.push_back(newPoint);
	selectedPoint = newPoint;
}


void Conveyor::Update(Camera& camera)
{	
	for (point& p : path)
	{
		ImGui::GetWindowDrawList()->AddCircleFilled(p.position, 20, ImColor(255, 255, 255, 255), 100);
	}

	if (edit)
	{
		Edit(camera);
	}
}

void Conveyor::Draw(ImVec4& color, float conveyorThickness, ImVec2& mouseWorldPos, Camera& camera)
{
	if (edit)
	{
		ImGui::GetWindowDrawList()
			->AddLine(camera.ToWorldPosition(selectedPoint.position), mouseWorldPos, ImColor(ImVec4(0, 1, 0, 1)), conveyorThickness);
	}
	
	for (point& p : path)
	{
		p.Draw(color, conveyorThickness);
	}
}

