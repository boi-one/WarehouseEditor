#include "JsonSerialization.h"
#include "LayerManager.h"

void JsonSerialization::Serialize(std::vector<Layer>& allLayers, std::vector<BridgeConveyor>& allBridgeConveyors)
{
	json jsonFile;

	jsonFile = 
	{
		{"allLayers", allLayers},
		{"allBridgeConveyors", allBridgeConveyors}
	};

	std::ofstream file("save.json");

	if (file.is_open())
	{
		file << jsonFile.dump(4);
		file.close();
		std::cout << "success" << std::endl;
	}
	else
	{
		std::cout << "failed serialization" << std::endl;
	}

}

void JsonSerialization::Deserialize(std::string& filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		json data;
		file >> data;

		std::vector<Layer> allLayers = data.at("allLayers").get<std::vector<Layer>>();
		LayerManager::allLayers = allLayers;
		std::vector<BridgeConveyor> allBridgeConveyors = data.at("allBridgeConveyors").get < std::vector<BridgeConveyor>>();
		LayerManager::allBridgeConveyors = allBridgeConveyors;
	}

}
