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

void to_json(json& j, const point& p)
{
	j = json
	{
		{"x", p.position.x}, {"y", p.position.y},
		{"connections", p.connections}
	};
}

void from_json(const json& j, point& p)
{
	p.position.x = j.at("x").get<float>();
	p.position.y = j.at("y").get<float>();

	//deserialize the connections vector
	if (j.contains("connections")) {
		j.at("connections").get_to(p.connections);
	}
}
