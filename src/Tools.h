#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include "imgui.h"

/// <summary>
/// A collection of handy functions so I do not need to write them each time I need them.
/// </summary>
class Tools
{
public:
	/// <summary>
	/// Calculates the magnitude between two points
	/// </summary>
	/// <param name="p1"> is point 1</param>
	/// <param name="p2"> is point 2</param>
	/// <returns> the distance between those points </returns>
	static float  Magnitude(ImVec2 p1, ImVec2 p2);

	/// <summary>
	/// Adds a float value to an ImVec2
	/// </summary>
	/// <param name="v1"> is the original vector</param>
	/// <param name="f"> is the amount you want to add to the vector</param>
	/// <returns> the new vector</returns>
	static ImVec2 AddImVec2(ImVec2 v1, float f);

	/// <summary>
	/// Adds two vectors together
	/// </summary>
	/// <param name="v1"> is the first vector</param>
	/// <param name="v2"> is the second vector</param>
	/// <returns>the new vector</returns>
	static ImVec2 AddImVec2(ImVec2 v1, ImVec2 v2);

	/// <summary>
	/// Multiplies an ImVec2 with a float value
	/// </summary>
	/// <param name="v"> is the vector </param>
	/// <param name="f"> is the float value</param>
	/// <returns> the vector * the float</returns>
	static ImVec2 MultImVec2(ImVec2 v, float f);

	/// <summary>
	/// Multiplies two vectors with eachother
	/// </summary>
	/// <param name="v1"> is the first vector</param>
	/// <param name="v2"> is the second vector </param>
	/// <returns> the two vectors multiplied </returns>
	static ImVec2 MultImVec2(ImVec2 v1, ImVec2 v2);

	/// <summary>
	/// Subtracts two vectors from eachother
	/// </summary>
	/// <param name="v1"> is the first vector</param>
	/// <param name="v2"> is the second vector</param>
	/// <returns> the two vectors subtracted </returns>
	static ImVec2 SubImVec2(ImVec2 v1, ImVec2 v2);

	/// <summary>
	/// Calculates the distance between two vectors as a vector
	/// </summary>
	/// <param name="v1"> is the first vector</param>
	/// <param name="v2"> is the second vector</param>
	/// <returns> a new vector which is the distance between the two vectors</returns>
	static ImVec2 ImVec2Distance(ImVec2 v1, ImVec2 v2);
	
	/// <summary>
	/// Compare two vectors with eachother to check if they are the same
	/// </summary>
	/// <param name="v1"> is the first vector</param>
	/// <param name="v2"> is the second vector</param>
	/// <returns> true or false depending on if the vectors are the same or different</returns>
	static bool	  CompareImVec(const ImVec2 v1, const ImVec2 v2);

	/// <summary>
	/// Compare two vectors with eachother to check if they are the same. ImVec4 is mostly used for colors
	/// </summary>
	/// <param name="v1"> is the first vector</param>
	/// <param name="v2"> is the second vector</param>
	/// <returns> true or false depending on if the vectors are the same or different</returns>
	static bool	  CompareImVec(const ImVec4 v1, const ImVec4 v2);

	/// <summary>
	/// returns the average out of all of the vectors in the list
	/// </summary>
	/// <param name="list">a vector containing ImVec2's</param>
	/// <returns> the average </returns>
	static ImVec2 AverageVec2(std::vector<ImVec2>& list);

	/// <summary>
	/// Finds the closest distance to the origin
	/// </summary>
	/// <param name="list"> a vector of ImVec2's</param>
	/// <param name="origin"> the point used to check which ImVec2 is the closest </param>
	/// <param name="range"> is how big the area to search in is</param>
	/// <returns> the distance between the closest point and the origin </returns>
	static float  FindClosestDistance(std::vector<ImVec2>& list, const ImVec2& origin, float range = 999'999);

	/// <summary>
	/// Finds anything in a vector independent of the type of the vector
	/// </summary>
	/// <typeparam name="T"> is the type of the vector and the item being searched for</typeparam>
	/// <param name="list"> the list is a list where the item possibly could be in</param>
	/// <param name="item"> is the instance being looked for</param>
	/// <returns> the position in the list, if -1 is being returned that means the instance is not present in the vector</returns>
	template<typename T> static int FindInList(std::vector<T>& list, const T& item)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (&list[i] == &item) return i;
		}
		return -1;
	}

	/// <summary>
	/// Deletes anything in a vector independent of the type of the vector
	/// </summary>
	/// <typeparam name="T">is the type of the vector and the item being deleted</typeparam>
	/// <param name="list"> the list is a list where the item possibly could be in</param>
	/// <param name="item"> the instance to be deleted</param>
	template<typename T> static void DeleteFromList(std::vector<T>& list, const T& item)
	{
		int placeInList = FindInList<T>(list, item);
		if (placeInList == -1) return;
		if (list.size() > 0)
			list.erase(list.begin() + placeInList);
	}

	/// <summary>
	/// moves an element from one vector into a new vector
	/// </summary>
	/// <typeparam name="T"> is the type of the vector</typeparam>
	/// <param name="oldList"> is the old list you want to copy the element from</param>
	/// <param name="newList"> is the new list you want to put the element into</param>
	/// <param name="item"> is the instance you want to move over</param>
	template<typename T> static void MoveToList(std::vector<T>& oldList, std::vector<T>& newList, const T& item)
	{
		int placeInOldList = FindInList<T>(oldList, item);
		if (placeInOldList == -1) return;
		if (oldList.size() > 0)
			newList.push_back(std::move(oldList.at(placeInOldList)));
	}

	/// <summary>
	/// Converts an array to a vector
	/// </summary>
	/// <typeparam name="T"> the type being used </typeparam>
	/// <typeparam name="S"> the size of the array</typeparam>
	/// <param name="arr"> the array that should be converted to a vector</param>
	/// <returns> a new vector containing all of the values from the array</returns>
	template<typename T, int S> static std::vector<T> ArrayToVector(T(&arr)[S])
	{
		std::vector<T> vec;

		for (int i = 0; i < S; i++)
		{
			vec.at(i) = arr.at(i);
		}

		return vec;
	}

	/// <summary>
	/// Converts a vector to and array
	/// </summary>
	/// <typeparam name="T"> the type being used</typeparam>
	/// <typeparam name="S"> the size of the array</typeparam>
	/// <param name="vec"> the vector that should be converted to an array</param>
	/// <returns> a new array containing all of the values from the vector</returns>
	template<typename T, int S> static std::array<T, S> VectorToArray(std::vector<T> vec)
	{
		T arr[S];

		for (int i = 0; i < S; i++)
		{
			arr.at(i) = vec.at(i);
		}
		return arr;
	}
};

