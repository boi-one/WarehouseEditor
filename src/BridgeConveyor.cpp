#include "BridgeConveyor.h"

void BridgeConveyor::DrawBridgeConveyor(ImDrawList* draw_list, Camera& camera, std::vector<Layer>& allLayers)
{

	if (conveyorIndex1 < 0 || conveyorIndex2 < 0) return;

	ImColor color = ImColor(ImVec4(0.2f, 0.2f, 1.f, 1.f)); //V path is size 0???
		
	draw_list->AddLine(camera.ToWorldPosition(allLayers[layerIndex1].allConveyors[conveyorIndex1].path[pointIndex1].position),
		camera.ToWorldPosition(allLayers[layerIndex2].allConveyors[conveyorIndex2].path[pointIndex2].position),
		color, 20 * camera.zoom);
}

void to_json(json& j, const BridgeConveyor& bg)
{
	j = json
	{
		{ "conveyorindex1", bg.conveyorIndex1 },
		{"conveyorindex2", bg.conveyorIndex2},
		{"layerindex1", bg.layerIndex1},
		{"layerindex2", bg.layerIndex2},
		{"pointindex1", bg.pointIndex1},
		{"pointindex2", bg.pointIndex2}
	};
}

void from_json(const json& j, BridgeConveyor& bg)
{
	bg.conveyorIndex1 = j.at("conveyorindex1").get<int>();
	bg.conveyorIndex2 = j.at("conveyorindex2").get<int>();
	bg.layerIndex1 = j.at("layerindex1").get<int>();
	bg.layerIndex2 = j.at("layerindex2").get<int>();
	bg.pointIndex1 = j.at("pointindex1").get<int>();
	bg.pointIndex2 = j.at("pointindex2").get<int>();
}
