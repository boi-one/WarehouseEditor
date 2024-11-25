#include <iostream>
#include "Tools.h"

float Tools::Magnitude(ImVec2 p1, ImVec2 p2)
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;

	return sqrt(dx * dx + dy * dy);
}

ImVec2 Tools::AddImVec2(ImVec2 v1, float f)
{
	return ImVec2(v1.x + f, v1.y + f);
}

ImVec2 Tools::AddImVec2(ImVec2 v1, ImVec2 v2)
{
	return ImVec2(v1.x + v2.x, v1.y + v2.y);
}

ImVec2 Tools::MultImVec2(ImVec2 v, float f)
{
	return ImVec2(v.x * f, v.y * f);
}

ImVec2 Tools::MultImVec2(ImVec2 v1, ImVec2 v2)
{
	return ImVec2(v1.x * v2.x, v1.y * v2.y);
}

ImVec2 Tools::SubImVec2(ImVec2 v1, ImVec2 v2)
{
	return ImVec2(v1.x - v2.x, v1.y - v2.y);
}

ImVec2 Tools::ImVec2Distance(ImVec2 v1, ImVec2 v2)
{
	return ImVec2(v2.x - v1.x, v2.y - v1.y);
}

bool Tools::CompareImVec(const ImVec2 v1, const ImVec2 v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

bool Tools::CompareImVec(const ImVec4 v1, const ImVec4 v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w);
}

ImVec2 Tools::AverageVec2(std::vector<ImVec2>& list)
{
	ImVec2 Average;

	for (ImVec2 v : list)
	{
		Average.x += v.x;
		Average.y += v.y;
	}

	Average.x = Average.x / list.size();
	Average.y = Average.y / list.size();

	return Average;
}

float Tools::FindClosestDistance(std::vector<ImVec2>& list, const ImVec2& origin, float range)
{
	ImVec2 closestPoint;

	for (ImVec2& v : list)
	{
		float distance = Tools::Magnitude(v, origin);
		if (distance < range)
		{
			range = distance;
		}
	}

	return range;
}

