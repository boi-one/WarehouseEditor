#pragma once
#include "imgui.h"
#include "Tools.h"

/// <summary>
/// The camera keeps track of the width and the height of the screen
/// </summary>
class Camera
{
public:
	int screenWidth = 1280;
	int screenHeight = 720;
	float speed = 5.f;
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

	
	/// <summary>
	/// Converts the given position to world position
	/// </summary>
	/// <param name="pos"> is the position you want to convert to world position</param>
	/// <returns></returns>
	ImVec2 ToWorldPosition(ImVec2 pos);
	
	/// <summary>
	/// Converts the given position to screen position
	/// </summary>
	/// <param name="pos"> is the position you want to convert to screen position</param>
	/// <returns></returns>
	ImVec2 ToScreenPosition(ImVec2 pos);
	
	/// <summary>
	/// Updates the camera values every time it is called
	/// </summary>
	void UpdateCamera();
};