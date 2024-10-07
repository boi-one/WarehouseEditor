#pragma once
#include "imgui.h"

class Mouse
{
public:
	Mouse()
	{
		SelectedPoint = ImVec2(-1000, 0);
	}

public:
	bool clicked = false;
	bool clickedMiddle = false;
	bool clickedRight = false;
	bool canvasFocus = true;
	
	ImVec2 liveMousePosition;
	ImVec2 previousMousePosition;
	ImVec2 SelectedPoint;
	
	ImVec2 rightMouseStartPos;
	ImVec2 middleMouseClickPos;
	ImVec2 lastPlacedPoint;
	ImVec2 snapPosition;
};