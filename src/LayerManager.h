#include "Layer.h"

class LayerManager 
{
public:
	inline static std::vector<Layer> allLayers;
	inline static Layer* currentLayer;
public:
	static void ManageLayers(ImDrawList* draw_list, Camera& camera, std::vector<int>& deletionList);
	static void RemoveLayer();
	static void AddLayer();
};