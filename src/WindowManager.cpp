#include "WindowManager.h"
#include "Grid.h"

void WindowManager::DrawCanvas()
{
	ImGuiIO& io = ImGui::GetIO();
	Tools::camPos = camera.position;
	Mouse& mouse = Layer::mouse;

	camera.UpdateCamera();

	mouse.previousMousePosition = mouse.liveMousePosition;
	mouse.liveMousePosition = ImGui::GetMousePos();
	std::vector<Conveyor>& allConveyors = LayerManager::currentLayer->allConveyors;

	ImGui::SetNextWindowSize(ImVec2(1080, 720));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0.1f, 1));
	ImGui::Begin("Canvas", 0, window_flags);
	bool focusedWindow = ImGui::IsWindowFocused();
	const char* selectWindow = focusedWindow ? "selected window: Canvas" : "selected window: Settings";
	ImGui::Text(selectWindow);
	ImGui::PopStyleColor();

	if (ImGui::IsWindowFocused() && editMode)
	{
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			if (!mouse.clicked) mouse.clicked = true;
			showNewLine = true;
		}
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			if (mouse.clicked && mouse.canvasFocus)
			{
				if (newConveyor)
				{
					newConveyor = false;
					Conveyor newConveyor(Conveyor::alltimeConveyorCount);
					LayerManager::currentLayer->UnselectAllConveyors();
					allConveyors.push_back(newConveyor);
					allConveyors[allConveyors.size() - 1].selected = true;
				}

				Conveyor& currentConveyor = allConveyors[allConveyors.size() - 1];
				if (!snapping)
					currentConveyor.points.push_back(camera.ToScreenPosition(mouse.liveMousePosition));
				else
					currentConveyor.points.push_back(camera.ToScreenPosition(mouse.snapPosition));
				mouse.lastPlacedPoint = currentConveyor.points[currentConveyor.points.size() - 1];
			}

			if (!mouse.canvasFocus) mouse.canvasFocus = true;
			mouse.clicked = false;
		}

		if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
		{
			showNewLine = false;
			if (!mouse.clickedRight)
			{
				mouse.clickedRight = true;
				mouse.rightMouseStartPos = mouse.liveMousePosition;
			}

			//find closest point of conveyor
			float closestPointDistance = 999'999;
			mouse.SelectedPoint = mouse.liveMousePosition;
			ImVec2 closestPoint;
			for (Conveyor& c : allConveyors)
			{
				for (ImVec2& p : c.points)
				{
					ImVec2 convertedP = camera.ToWorldPosition(p);
					float distance = Tools::Magnitude(convertedP, mouse.SelectedPoint);
					if (distance < closestPointDistance)
					{
						closestPointDistance = distance;
						closestPoint = p;
					}
				}
			}

			for (Conveyor& c : allConveyors)
			{
				c.selected = false;

				for (ImVec2& p : c.points)
				{
					if (closestPointDistance < 30 * camera.zoom)
					{
						mouse.SelectedPoint = closestPoint;
						if (mouse.SelectedPoint.x == p.x && mouse.SelectedPoint.y == p.y)
						{
							c.selected = true;
							break;
						}
					}
					else
					{
						mouse.SelectedPoint = ImVec2(camera.position.x + 100000000, camera.position.x + 100000000);
						c.selected = false;
					}
				}
			}
		}

		if (!ImGui::IsMouseDown(ImGuiMouseButton_Right))
		{
			std::vector<Conveyor>& allConveyors = LayerManager::currentLayer->allConveyors;

			if (mouse.clickedRight)
			{
				if (allConveyors.size() > 0 && allConveyors.at(allConveyors.size() - 1).points.size() < 2)
					allConveyors.pop_back(); //verwijderd de conveyor als er minder dan 2 punten op zitten anders krijg je ontzichtbare conveyors
				newConveyor = true;
				Conveyor::alltimeConveyorCount++;
			}
			mouse.clickedRight = false;
			if (!mouse.canvasFocus) mouse.canvasFocus = true; //! doet vgm niks?

		}
		static ImVec2 dragOffset;
		static Conveyor* selectedConveyor = 0;
		if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
		{
			if (!mouse.clickedMiddle)
			{
				mouse.middleMouseClickPos = mouse.liveMousePosition;
				mouse.clickedMiddle = true;

				dragOffset = ImGui::GetMousePos();

				for (Conveyor& c : allConveyors)
				{
					if (c.selected)
					{
						selectedConveyor = &c;
						break;
					}
				}
			}
			if (selectedConveyor)
			{
				ImVec2 currentMousePos = ImGui::GetMousePos();
				ImVec2 delta = ImVec2(currentMousePos.x - dragOffset.x, currentMousePos.y - dragOffset.y);
				for (ImVec2& p : selectedConveyor->points)
				{
					p.x += delta.x;
					p.y += delta.y;
				}
				mouse.SelectedPoint.x += delta.x;
				mouse.SelectedPoint.y += delta.y;
				dragOffset = currentMousePos;
			}
		}
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Middle) && mouse.clickedMiddle)
		{
			mouse.clickedMiddle = false;
		}
	}
	else
	{
		mouse.canvasFocus = false;
	}
	if (ImGui::IsWindowFocused())
	{
		if (ImGui::IsKeyDown(ImGuiKey_UpArrow))
			camera.position.y += camera.speed / camera.zoom;
		if (ImGui::IsKeyDown(ImGuiKey_DownArrow))
			camera.position.y -= camera.speed / camera.zoom;
		if (ImGui::IsKeyDown(ImGuiKey_LeftArrow))
			camera.position.x += camera.speed / camera.zoom;
		if (ImGui::IsKeyDown(ImGuiKey_RightArrow))
			camera.position.x -= camera.speed / camera.zoom;

		if (io.MouseWheel > 0 && camera.zoom < 2.9f)
			camera.zoom += 0.1f;
		if (io.MouseWheel < 0 && camera.zoom > 0.5f)
			camera.zoom -= 0.1f;
	}
	if (ImGui::IsMouseDown(1))
		ImGui::SetWindowFocus("Canvas");

	if (ImGui::IsKeyPressed(ImGuiKey_R))
	{
		camera.position = ImVec2(0, 0);
		camera.zoom = 1.0f;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		for (Layer& l : LayerManager::allLayers)
		{
			l.UnselectAllConveyors();
			mouse.SelectedPoint = ImVec2(camera.position.x - 1000, camera.position.y);
		}
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Slash))
	{
		showShortcuts = !showShortcuts;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_H))
	{
		LayerManager::currentLayer->hidden = !LayerManager::currentLayer->hidden;
	}

	if (!showNewLine) mouse.lastPlacedPoint = mouse.liveMousePosition;

	Render();

	ImGui::End();
}

void WindowManager::DrawSettings()
{
	Mouse& mouse = Layer::mouse;

	std::vector<Conveyor>& allConveyors = LayerManager::currentLayer->allConveyors;
	std::vector<int> deletionList;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1));
	ImGui::SetNextWindowPos(ImVec2(1080, 0));
	ImGui::SetNextWindowSize(ImVec2(200, 720));
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	ImGui::Begin("settings", 0, window_flags);
	ImGui::PopStyleColor();

	ImGui::Text("Application average\n%.3f ms/frame\n%.1f FPS\n", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	if (ImGui::Button("Quit"))
	{
		running = false;
	}
	if (ImGui::Button("Shortcuts"))
	{
		showShortcuts = !showShortcuts;
	}
	char mousePositionLabel[64];
	snprintf(mousePositionLabel, sizeof(mousePositionLabel), "Mouse Position:\nX:%d Y:%d", (int)ImGui::GetMousePos().x, (int)ImGui::GetMousePos().y);
	ImGui::Text(mousePositionLabel);

	char cameraPositionLabel[64];
	snprintf(cameraPositionLabel, sizeof(cameraPositionLabel), "Camera Position:\nX:%.0f Y:%.0f", camera.position.x / camera.zoom, camera.position.y / camera.zoom);
	ImGui::Text(cameraPositionLabel);

	char cameraZoomLabel[64];
	snprintf(cameraZoomLabel, sizeof(cameraZoomLabel), "Camera Zoom:\n%.1f", camera.zoom);
	ImGui::Text(cameraZoomLabel);

	ImGui::PushItemWidth(100);
	ImGui::Text("Camera Speed: ");
	ImGui::SliderFloat(" ", &camera.speed, 1.f, 10.f);
	if (ImGui::Button("Reset Camera"))
	{
		camera.speed = 5.f;
		camera.zoom = 1.f;
		camera.position = ImVec2(0, 0);
	}
	ImGui::PopItemWidth();

	const char* snappingLabel = snapping ? "Snapping  Enabled" : "Snapping  Disabled";
	if (ImGui::Button(snappingLabel) && grid.active)
	{
		snapping = !snapping;
	}

	const char* editLabel = editMode ? "Edit Mode Enabled" : "Edit Mode Disabled";
	if (ImGui::Button(editLabel))
	{
		editMode = !editMode;
		LayerManager::currentLayer->UnselectAllConveyors();
		mouse.SelectedPoint = ImVec2(camera.position.x - 1000, camera.position.x - 1000);
	}

	const char* gridLabel = grid.active ? "Show Grid Enabled" : "Show Grid Disabled";
	if (ImGui::Button(gridLabel))
	{
		grid.active = !grid.active;
		if (!grid.active) snapping = false;
	}

	//! TODO: 
	//! !!! de posities van alles fixen
	// //bugs zoeken: conveyor position fixen, conveyor select naar midden van camera fixen
	//
	 //name layers fixen 
	 //gridsnapping fixen
	 //edit conveyor path
	 //connect conveyors
	 //cross conveyors

	LayerManager::ManageLayers(camera, deletionList);

	ImGui::End();

	if (showShortcuts)
	{
		ImGui::Begin("Warehouse Editor Shortcuts");
		ImGui::Text("Esc      : Unselect conveyor");
		ImGui::Text("R        : Reset camera");
		ImGui::Text("?        : Open/close this menu");
		ImGui::Text("Alt + F4 : Close program");
		ImGui::Text("H        : Hide current layer");

		if (ImGui::Button("Close"))
		{
			showShortcuts = false;
		}
		if (!ImGui::IsWindowFocused()) showShortcuts = false;
		ImGui::End();
	}
}

void WindowManager::Render()
{
	//de enige plek waar to world en to screen gebruikt mogen worden (nadat alle punten in de code geconvert zijn naar to world(?))
	//!! TODO: to world en screen position op centrale plek uitvoeren voor ALLES dus niet zoom op door berekeningen heen gebruiken
		//! want het bebeurt al in de screen/world position. (alle berekeningen doen in world position en dan converten zonder zoom etc.)
		//! denk aan het schaakbord dat wordt ingezoomt maar nogsteeds de zelfde posities erop heeft

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	Grid grid;

	grid.Update(camera);

	std::vector<Conveyor>& allConveyors = LayerManager::currentLayer->allConveyors;
	Mouse& mouse = Layer::mouse;

	if (grid.active)
	{
		grid.DrawGrid(draw_list, camera);
	}

	for (Layer l : LayerManager::allLayers)
	{
		if (!l.hidden)
		{
			ImVec4 color = ImVec4(0, 0, 0, 0);

			if (l.selected)
				color = ImVec4(1, 1, 1, 1);
			else
				color = ImVec4(0.4f, 0.4f, 0.4f, 1.f);

			l.DrawConveyors(draw_list, camera, color);
		}
	}

	if (allConveyors.size() > 0 && allConveyors[0].points.size() > 0)
	{
		int rectSize = 20 * camera.zoom;
		draw_list->AddRect(camera.ToWorldPosition(ImVec2(mouse.SelectedPoint.x - rectSize, mouse.SelectedPoint.y - rectSize)),
			camera.ToWorldPosition(ImVec2(mouse.SelectedPoint.x + rectSize, mouse.SelectedPoint.y + rectSize)),
			ImColor(ImVec4(1, 0, 0, 1)), 2.0f * camera.zoom);

		//Draw newline
		if (editMode && showNewLine && ImGui::IsWindowFocused())
		{
			ImVec2 lineStart = mouse.lastPlacedPoint;
			ImVec2 mouseWorldPos;

			if (!snapping)
				mouseWorldPos = mouse.liveMousePosition;
			else
				mouseWorldPos = mouse.snapPosition;

			draw_list->AddLine(camera.ToWorldPosition(lineStart), mouseWorldPos, ImColor(ImVec4(0, 1, 0, 1)), 20.0f * camera.zoom);
		}
	}

	//grid Cursor
	if (snapping && editMode)
	{
		ImVec2 worldPos = mouse.liveMousePosition;

		float relativePosX = worldPos.x - grid.position.x;
		float relativePosY = worldPos.y - grid.position.y;

		mouse.snapPosition.x = round(relativePosX / grid.zoomedGridSpacing) * grid.zoomedGridSpacing;
		mouse.snapPosition.y = round(relativePosY / grid.zoomedGridSpacing) * grid.zoomedGridSpacing;

		draw_list->AddCircleFilled(mouse.snapPosition, 10.f, ImColor(255, 0, 255, 255), 12);
	}
}

void WindowManager::Draw()
{
	DrawCanvas();
	DrawSettings();
}
