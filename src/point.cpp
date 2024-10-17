#include "point.h"

void point::Draw(const ImVec4& color, const float thickness)
{
	for (point& connection : connections)
	{
		ImGui::GetWindowDrawList()->AddLine(position, connection.position, ImColor(color), thickness);
	}
}
