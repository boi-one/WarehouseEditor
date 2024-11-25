#pragma once
#include <vector>
#include "Camera.h"
#include "Mouse.h"
#include "point.h"

/// <summary>
/// A conveyor contains a list of points which get connected together so it looks like a line or a "conveyor"
/// </summary>
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

	/// <summary>
	/// Calculates the average position of all of the points in the conveyor
	/// </summary>
	/// <param name="path"> is the vector which contains all of the points</param>
	/// <returns> The average position of the given path</returns>
	static ImVec2 AveragePointsPosition(std::vector<point> path);

	/// <summary>
	/// Finds the closest point to the origin out of all of the points in the list
	/// </summary>
	/// <param name="list"> is the vector which contains all of the points </param>
	/// <param name="origin"> is the position from where you want to calculate the closest point</param>
	/// <param name="camera"> is used for to convert the points to world position </param>
	/// <param name="range"> is the area you want to check for points, points outside of this area do not get checked </param>
	/// <returns> a pointer to the closest point </returns>
	static point* FindClosestPointInWorld(std::vector<point>& list, ImVec2& origin, Camera& camera, float range);

	void DrawConveyorHeader();
	
	/// <summary>
	/// creates a new point for the specific conveyor selected or created
	/// </summary>
	/// <param name="mouseWorldPos"> is the position of the mouse position (or if you want any other place where you want to place a new point for a given conveyor)</param>
	void NewPoint(ImVec2 mouseWorldPos);

	/// <summary>
	/// draws the conveyor onto the screen
	/// </summary>
	/// <param name="color"> is  the color of the conveyor</param>
	/// <param name="thickness"> is the thickness of the conveyor</param>
	/// <param name="mouseWorldPos"> is the position of the mouse</param>
	/// <param name="camera"> is used to convert to world position</param>
	void Draw(ImVec4& color, float thickness, ImVec2& mouseWorldPos, Camera& camera);
	
	friend void to_json(json& j, const Conveyor& c);

	/// <summary>
	/// used to compare two conveyors which eachother to check if they are the same
	/// </summary>
	/// <param name="other">the other conveyor you want to compare with</param>
	/// <returns>true or false depending on if the values of the conveyors matched</returns>
	bool operator==(const Conveyor& other) const
	{
		if (path.size() != other.path.size())
		{
			//std::cout << "not the same path size" << std::endl;
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
};