#include "Camera.h"

ImVec2 Camera::ToWorldPosition(ImVec2 pos)
{
	ImVec2 screenPosition;
	screenPosition.x = (pos.x * zoom) + position.x;
	screenPosition.y = (pos.y * zoom) + position.y;
	return screenPosition;
}

ImVec2 Camera::ToScreenPosition(ImVec2 pos)
{
	ImVec2 worldPosition;
	worldPosition.x = (pos.x - position.x) / zoom;
	worldPosition.y = (pos.y - position.y) / zoom;
	return worldPosition;
}

void Camera::UpdateCamera()
{
	Width = (screenWidth - 200);
	Height = screenHeight;

	size = ImVec2(Width, Height);
	center = ImVec2(size.x * 0.5f, size.y * 0.5f);

	ImVec2 WidthHeightWorld = ImVec2(Width, Height);
	Width = WidthHeightWorld.x;
	Height = WidthHeightWorld.y;
}
