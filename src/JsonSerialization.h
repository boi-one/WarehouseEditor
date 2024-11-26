#include <string>
#include "Layer.h"
#include "BridgeConveyor.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


class JsonSerialization
{
public:

	static void Serialize(std::vector<Layer>& allLayers, std::vector<BridgeConveyor>& allBridgeConveyors);
	static void Deserialize(std::string& filePath);
};