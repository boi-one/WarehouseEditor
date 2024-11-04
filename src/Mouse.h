#pragma once
#include "imgui.h"

class Mouse
{
public:
	static inline bool clicked = false;
	static inline bool holdClick = false;

	static inline bool clickedMiddle = false;
	static inline bool holdMiddleClick = false;

	static inline bool clickedRight = false;
	static inline bool holdRightClick = false;

	static inline bool canvasFocus = true;


	static inline ImVec2 liveMousePosition;

	static inline ImVec2 placePointPosition;

	static inline ImVec2 leftMouseClickPos;
	static inline ImVec2 rightMouseClickPos;
	static inline ImVec2 middleMouseClickPos;

	static inline ImVec2 SelectCursorPosition;
	static inline ImVec2 snapPosition;

public:
	Mouse()
	{
		SelectCursorPosition = ImVec2(-5000, 0);
		placePointPosition = liveMousePosition;
	}
};