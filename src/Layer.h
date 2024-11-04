#pragma once
#include "Conveyor.h"
#include "Mouse.h"

class Layer
{
public:
	static inline int layerCount;
	int id;
	std::string name = "layer name";
	bool renameLayer = false;
	bool selected = false;
	bool hidden = false;
	std::vector<Conveyor> allConveyors;
	Conveyor* selectedConveyor = 0;

public:
	Layer()
	{
		layerCount++;
		this->id = layerCount;
	}

	void ClearSelection();

	void UnselectAllConveyors();
	void DrawConveyors(ImDrawList* draw_list, Camera& camera, ImVec4& color, bool snapping);
	void DrawLayerHeader(Camera& camera, std::vector<int>& deletionList);
	Conveyor* ReturnClosestConveyor(Camera& camera, ImVec2& origin);
	void CreateConveyor(ImVec2 position, Camera& camera);
};