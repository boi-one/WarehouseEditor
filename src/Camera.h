#pragma once
#include "ImGui.h"
#include "Tools.h"

class Camera
{
public:
	static inline int screenWidth = 1280;
	static inline int screenHeight = 720;
	float speed = 5.0f;
	float zoom = 1.0f;

	ImVec2 position = ImVec2(0, 0);
	ImVec2 size = ImVec2(0, 0);

	ImVec2 center;
	ImVec2 cameraOrigin;

	float Width;
	float Height;

	Camera()
	{
		cameraOrigin = position;
	}

	

	ImVec2 ToWorldPosition(ImVec2 pos);
	ImVec2 ToScreenPosition(ImVec2 pos);
	
	void UpdateCamera();
};