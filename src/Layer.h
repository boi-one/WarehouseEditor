#pragma once
#include "Conveyor.h"
#include "Mouse.h"

class Layer
{
public:
	static inline int layerCount;
	static inline Mouse mouse;
	int id;
	std::string name = "layer name";
	bool renameLayer = false;
	bool selected = false;
	bool hidden = false;
	std::vector<Conveyor> allConveyors;

public:
	Layer()
	{
		layerCount++;
		this->id = layerCount;
	}

	void UnselectAllConveyors();
	void DrawConveyors(ImDrawList* draw_list, Camera& camera, ImVec4 color);
	void DrawLayerHeader(Camera& camera, std::vector<int>& deletionList);
};