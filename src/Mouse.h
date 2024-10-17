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
	static inline bool clicked = false;
	static inline bool clickedMiddle = false;
	static inline bool clickedRight = false;
	static inline bool canvasFocus = true;

	static inline ImVec2 liveMousePosition;
	static inline ImVec2 previousMousePosition;
	static inline ImVec2 SelectedPoint;

	static inline ImVec2 rightMouseClickPos;
	static inline ImVec2 middleMouseClickPos;
	static inline ImVec2 leftMouseClickPos;
	static inline ImVec2 snapPosition;
};