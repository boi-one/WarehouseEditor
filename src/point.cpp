#include "point.h"

void point::Draw(const ImVec4& color, Camera& camera, const float thickness)
{
	for (point& connection : connections)
	{
		ImGui::GetWindowDrawList()->AddLine(
			camera.ToWorldPosition(position), 
			camera.ToWorldPosition(connection.position),
			ImColor(color), thickness);
	}
}
