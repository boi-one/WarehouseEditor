#include "BridgeConveyor.h"

void BridgeConveyor::DrawBridgeConveyor(ImDrawList* draw_list, Camera& camera, std::vector<Layer>& allLayers)
{

	if (conveyorIndex1 < 0 || conveyorIndex2 < 0) return;

	ImColor color = ImColor(ImVec4(0.2f, 0.2f, 1.f, 1.f)); //V path is size 0???

	/*std::cout << " conveyor 1: path size, index " << conveyor1->path.size() << ", " << index1 <<
				 " conveyor 2: path size, index " << conveyor2->path.size() << ", " << index2 << std::endl;*/

	//draw_list->AddLine(camera.ToWorldPosition(conveyor1->path[index1].position), camera.ToWorldPosition(conveyor2->path[index2].position), color, 20 * camera.zoom);
	draw_list->AddLine(camera.ToWorldPosition(allLayers[layerIndex1].allConveyors[conveyorIndex1].path[pointIndex1].position),
					   camera.ToWorldPosition(allLayers[layerIndex2].allConveyors[conveyorIndex2].path[pointIndex2].position), 
						color, 20 * camera.zoom);
}

void to_json(json& j, const BridgeConveyor& bg)
{
	j = json
	{
		{"conveyorindex1", bg.conveyorIndex1},
		{"conveyorindex2", bg.conveyorIndex2},
		{"layerindex1", bg.layerIndex1},
		{"layerindex2", bg.layerIndex2},
		{"pointindex1", bg.pointIndex1},
		{"pointindex2", bg.pointIndex2}
	};
}
