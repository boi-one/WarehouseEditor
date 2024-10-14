#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include "imgui.h"

class Tools
{
public:
	static inline ImVec2 camPos;
	static float  Magnitude(ImVec2 p1, ImVec2 p2);
	static ImVec2 AddOffset(ImVec2 start);
	static ImVec2 AddImVec2(ImVec2 v1, float f);
	static ImVec2 AddImVec2(ImVec2 v1, ImVec2 v2);
	static ImVec2 MultImVec2(ImVec2 v, float f);
	static ImVec2 MultImVec2(ImVec2 v1, ImVec2 v2);
	static ImVec2 SubImVec2(ImVec2 v1, ImVec2 v2);
	static ImVec2 SubImVec2(ImVec2 v1, float f);
	static ImVec2 ImVec2Distance(ImVec2 v1, ImVec2 v2);
	static float  GetClosestPoint(ImVec2 start, std::vector<ImVec2>& points);
	static ImVec2 Snap(ImVec2 mousePosition, int grid);
	static bool	  CompareImVec(const ImVec2 v1, const ImVec2 v2);
	static bool	  CompareImVec(const ImVec4 v1, const ImVec4 v2);
	static ImVec2 AverageVec2(std::vector<ImVec2>& list);

	template<typename T> static int FindInList(std::vector<T>& list, const T& item)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (&list[i] == &item) return i;
		}
		return -1;
	}

	template<typename T> static void DeleteFromList(std::vector<T>& list, const T& item)
	{
		int placeInList = FindInList<T>(list, item);
		if (placeInList == -1) return;
		if (list.size() > 0)
			list.erase(list.begin() + placeInList);
	}

	template<typename T> static void MoveToList(std::vector<T>& oldList, std::vector<T>& newList, const T& item)
	{
		int placeInOldList = FindInList<T>(oldList, item);
		if (placeInOldList == -1) return;
		if (oldList.size() > 0)
			newList.push_back(std::move(oldList.at(placeInOldList)));
	}
};

