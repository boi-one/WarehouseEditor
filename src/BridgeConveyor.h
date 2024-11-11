#include "point.h"
#include "Conveyor.h"
#include <vector>

class BridgeConveyor
{
public:
	static inline std::vector<BridgeConveyor> allBridgeConveyors;
	Conveyor conveyor1;
	point bridgePoint1;
	Conveyor conveyor2;
	point bridgePoint2;

public:
	void DrawBridgeConveyor(ImDrawList draw_list, Camera camera);

};