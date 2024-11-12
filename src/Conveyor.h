#pragma once
#include <vector>
#include "Camera.h"
#include "Mouse.h"
#include "point.h"

class Conveyor
{
public:
	int id;
	static inline int alltimeConveyorCount = 0;
	std::vector<point> path;
	bool selected = false;
	bool edit = false;
	point* selectedPoint;
	static inline bool createNewConveyor = true;

	Conveyor() = default;
	Conveyor(int id)
	{
		this->id = id;
	}

	static ImVec2 AveragePointsPosition(std::vector<point> path);

	static point* FindClosestPoint(std::vector<point*>& list, ImVec2& origin, Camera& camera, float range);

	static point* FindClosestPoint(std::vector<point>& list, ImVec2& origin, Camera& camera, float range);

	void DrawConveyorHeader();

	void Draw(ImVec4& color, float thickness, ImVec2& mouseWorldPos, Camera& camera);
	
	bool operator==(const Conveyor& other) const
	{
		if (path.size() != other.path.size())
		{
			std::cout << "not the same size" << std::endl;
			return false;
		}

		for (size_t i = 0; i < path.size(); i++)
		{
			if(!Tools::CompareImVec(path.at(i).position, other.path.at(i).position))
				return false;
		}

		return selected == other.selected &&
			path.size() == other.path.size();
	}

	static ImVec2 ClosestVector(Camera& camera, std::vector<point>& path, ImVec2 mouseWorldPos);

	void NewPoint(ImVec2 mouseWorldPos);
};