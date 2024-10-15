#pragma once
#include <imgui.h>
#include <vector>
#include "Camera.h"

class Conveyor
{
public:
	int id;
	static inline int alltimeConveyorCount = 0;
	std::vector<ImVec2> points;
	bool selected = false;
	bool edit = false;

	Conveyor() = default;

	Conveyor(int id)
	{
		this->id = id;
	}

	void DrawConveyorHeader();

	void EditConveyor();

	bool operator==(const Conveyor& other) const
	{
		if (points.size() != other.points.size())
		{
			std::cout << "not the same size" << std::endl;
			return false;
		}

		for (size_t i = 0; i < points.size(); i++)
		{
			if(!Tools::CompareImVec(points.at(i), other.points.at(i)))
				return false;
		}

		return selected == other.selected &&
			points.size() == other.points.size();
	}
};