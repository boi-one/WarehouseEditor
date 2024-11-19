#include "point.h"
#include "Conveyor.h"
#include <vector>

class BridgeConveyor
{
public:
	static inline std::vector<BridgeConveyor> allBridgeConveyors;
	point* bridgePoint1;
	point* bridgePoint2;

public:
	void DrawBridgeConveyor(ImDrawList* draw_list, Camera& camera);
};