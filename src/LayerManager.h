#include "Layer.h"
#include "BridgeConveyor.h" 

/// <summary>
/// The LayerManager keeps track and manages all of the layers
/// </summary>
class LayerManager 
{
public:
	inline static std::vector<Layer> allLayers;
	inline static std::vector<BridgeConveyor> allBridgeConveyors;
	inline static Layer* currentLayer;
public:
	/// <summary>
	/// Manages the layers in the allLayers vector
	/// </summary>
	/// <param name="camera"> is used to center the camera on a certain point or on a conveyor</param>
	/// <param name="deletionList"> is a list that keeps track of all the points that will need to be deleted after the loop ends</param>
	static void ManageLayers(Camera& camera, std::vector<int>& deletionList);
	
	/// <summary>
	/// Removes the last added layer
	/// </summary>
	static void RemoveLayer();

	/// <summary>
	/// Adds a new layer
	/// </summary>
	static void AddLayer();
};