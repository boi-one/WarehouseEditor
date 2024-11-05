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
	static inline bool connecting = false;
	static inline ImVec2 newLineEnd;

public:
	Layer()
	{
		layerCount++;
		this->id = layerCount;
	}

	void ClearSelection();

	void UnselectAllConveyors();
	void DrawNewLine(ImDrawList* draw_list, ImVec2& endPosition, Camera& camera, bool focusedWindow);
	void DrawConveyors(ImDrawList* draw_list, Camera& camera, ImVec4& color, bool snapping);
	void DrawLayerHeader(Camera& camera, std::vector<int>& deletionList);
	Conveyor* ReturnClosestConveyor(Camera& camera, ImVec2& origin);
	void CreateConveyor(ImVec2 position, Camera& camera);
};