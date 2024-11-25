#include "JsonSerialization.h"

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

void JsonSerialization::Deserialize()
{
	std::cout << "load" << std::endl;
}
