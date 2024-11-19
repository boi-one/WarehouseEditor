#include "Layer.h"
#include "BridgeConveyor.h" 

class LayerManager 
{
public:
	inline static std::vector<Layer> allLayers;
	inline static std::vector<BridgeConveyor> allBridgeConveyors;
	inline static Layer* currentLayer;
public:
	static void ManageLayers(Camera& camera, std::vector<int>& deletionList);
	static void RemoveLayer();
	static void AddLayer();
	static Conveyor* FindClosestPointInLayers(std::vector<Layer>& list, ImVec2& origin, Camera& camera, float range);
};