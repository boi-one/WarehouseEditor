#include "point.h"
#include "Conveyor.h"
#include <vector>
/// <summary>
/// A link between two conveyors on different layers
/// </summary>
class BridgeConveyor
{
public:
	static inline std::vector<BridgeConveyor> allBridgeConveyors;
	point* bridgePoint1;
	point* bridgePoint2;

public:
	/// <summary>
	/// Draws the bridge conveyor so you can see which conveyors are connected together
	/// </summary>
	/// <param name="draw_list"> is the way ImGui draws to windows, this is needed to display the conveyor</param>
	/// <param name="camera"> is used to convert the points possitions to the world position so they actually stay still instead of move with the screen.</param>
	void DrawBridgeConveyor(ImDrawList* draw_list, Camera& camera);
};