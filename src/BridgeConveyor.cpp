#include "BridgeConveyor.h"

void BridgeConveyor::DrawBridgeConveyor(ImDrawList* draw_list, Camera& camera)
{
	if (!&this->bridgePoint1 && !&this->bridgePoint2) return;
	
	draw_list->AddLine(camera.ToWorldPosition(bridgePoint1->position), camera.ToWorldPosition(bridgePoint2->position), ImColor(ImVec4(0.2f, 0.2f, 1.f, 1.f)), 20 * camera.zoom);
}
