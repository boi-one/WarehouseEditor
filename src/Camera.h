#pragma once
#include "ImGui.h"
#include "Tools.h"

class Camera
{
public:
	int screenWidth = 1280;
	int screenHeight = 720;
	float speed = 5.0f;
	float zoom = 1.0f;

	ImVec2 position = ImVec2(0, 0);
	ImVec2 center;
	ImVec2 cameraOrigin;
	ImVec2 gridOrigin = ImVec2(-400, -400);

	Camera()
	{
		center = ImVec2((screenWidth * 0.5f) + 200, screenHeight * 0.5f);
		cameraOrigin = position;
	}

	ImVec2 ToWorldPosition(ImVec2 pos);
	ImVec2 ToWorldPositionOLD(ImVec2 pos);
	ImVec2 ToScreenPosition(ImVec2 pos);
	ImVec2 ToScreenPositionOLD(ImVec2 pos);
};