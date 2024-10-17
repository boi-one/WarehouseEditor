#include "WindowManager.h"
#include "Grid.h"

void WindowManager::DrawCanvas()
{
	ImGuiIO& io = ImGui::GetIO();
	Tools::camPos = camera.position;

	camera.UpdateCamera();

	Mouse::previousMousePosition = Mouse::liveMousePosition;
	Mouse::liveMousePosition = ImGui::GetMousePos();
	std::vector<Conveyor>& allConveyors = LayerManager::currentLayer->allConveyors;

	ImGui::SetNextWindowSize(ImVec2(1080, 720));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0.1f, 1));
	ImGui::Begin("Canvas", 0, window_flags);
	bool focusedWindow = ImGui::IsWindowFocused();
	const char* selectWindow = focusedWindow ? "active window: Canvas" : "active window: Settings";
	ImGui::Text(selectWindow);
	ImGui::PopStyleColor();

	if (ImGui::IsWindowFocused() && editMode)
	{
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			if (!Mouse::clicked) Mouse::clicked = true;
			showNewLine = true;
		}
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			//nieuwe conveyor functie maken hier

			if (Mouse::clicked && Mouse::canvasFocus && LayerManager::currentLayer->selected)
			{
				if (createNewConveyor)
				{
					createNewConveyor = false;
					//create a new conveyor
					Conveyor newestConveyor(Conveyor::alltimeConveyorCount);
					LayerManager::currentLayer->UnselectAllConveyors();
					allConveyors.push_back(newestConveyor);
					Conveyor& currentConveyor = allConveyors[allConveyors.size() - 1];
					currentConveyor.selected = true;
					currentConveyor.edit = true;
					currentConveyor.path.push_back(point(Mouse::liveMousePosition)); //dit misschien in conveyor ipv hier
					currentConveyor.selectedPoint = currentConveyor.path[0];
				}
				Conveyor& currentConveyor = allConveyors[allConveyors.size() - 1];
				currentConveyor.NewPoint();
			}

			/*if (Mouse::clicked && Mouse::canvasFocus && LayerManager::currentLayer->selected)
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
					currentConveyor.points.push_back(camera.ToScreenPosition(Mouse::liveMousePosition));
				else
					currentConveyor.points.push_back(camera.ToScreenPosition(Mouse::snapPosition));
				Mouse::leftMouseClickPos = currentConveyor.points[currentConveyor.points.size() - 1];
			}*/

			if (!Mouse::canvasFocus) Mouse::canvasFocus = true;
			Mouse::clicked = false;
		}
	}
	else
	{
		Mouse::canvasFocus = false;
	}

	for (Conveyor& c : LayerManager::currentLayer->allConveyors)
	{
		c.Update(camera);
	}

	if (ImGui::IsWindowFocused())
	{
		if (!snapping)
		{
			if (ImGui::IsKeyDown(ImGuiKey_UpArrow))
				camera.position.y += camera.speed / camera.zoom;
			if (ImGui::IsKeyDown(ImGuiKey_DownArrow))
				camera.position.y -= camera.speed / camera.zoom;
			if (ImGui::IsKeyDown(ImGuiKey_LeftArrow))
				camera.position.x += camera.speed / camera.zoom;
			if (ImGui::IsKeyDown(ImGuiKey_RightArrow))
				camera.position.x -= camera.speed / camera.zoom;
		}
		if(snapping)
		{ 
			io.KeyRepeatDelay = 1000.f;

			if (ImGui::IsKeyPressed(ImGuiKey_UpArrow, true))
				camera.position.y += grid.gridSize * camera.zoom;
			if (ImGui::IsKeyPressed(ImGuiKey_DownArrow, true))
				camera.position.y -= grid.gridSize * camera.zoom;
			if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow, true))
				camera.position.x += grid.gridSize * camera.zoom;
			if (ImGui::IsKeyPressed(ImGuiKey_RightArrow, true))
				camera.position.x -= grid.gridSize * camera.zoom;
		}

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
			Mouse::SelectedPoint = ImVec2(camera.position.x - 1000, camera.position.y);
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

	if (!showNewLine) Mouse::leftMouseClickPos = Mouse::liveMousePosition;
	
	grid.Update(camera);

	Render();

	ImGui::End();
}

void WindowManager::DrawSettings()
{
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
	if (ImGui::Button("Shortcuts and Help"))
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
		camera.position.x = round(camera.position.x / grid.tileScaled) * grid.tileScaled;
		camera.position.y = round(camera.position.y / grid.tileScaled) * grid.tileScaled;

		snapping = !snapping;
	}

	const char* editLabel = editMode ? "Edit Mode Enabled" : "Edit Mode Disabled";
	if (ImGui::Button(editLabel))
	{
		editMode = !editMode;
		LayerManager::currentLayer->UnselectAllConveyors();
		Mouse::SelectedPoint = ImVec2(camera.position.x - 1000, camera.position.x - 1000);
	}

	const char* gridLabel = grid.active ? "Show Grid Enabled" : "Show Grid Disabled";
	if (ImGui::Button(gridLabel))
	{
		grid.active = !grid.active;
		if (!grid.active) snapping = false;
	}

	//! TODO: 
	//  edit conveyor path
	//  connect conveyors
	//  cross conveyors
	//  name layers fixen 
	//! BUGS:
	//  wanneer je een conveyor maakt, de layer verwijderd en dan weer op het canvas drukt is er een vector subscript out of range error.

	LayerManager::ManageLayers(camera, deletionList);

	ImGui::End();

	if (showShortcuts)
	{
		float windowWidth = ImGui::GetWindowSize().x;
		ImGui::Begin("Warehouse Editor Shortcuts");
		ImGui::PushTextWrapPos(windowWidth);
		ImGui::TextWrapped("If you can't move or place conveyors you are probably in the settings menu (when opening the program this is the active window). Left or right click on the canvas window to make it your active window.");
		ImGui::Separator();
		ImGui::TextWrapped("You can check which window is currently active in the top left corner.");
		ImGui::Separator();
		ImGui::TextWrapped("If you can't place a conveyor but do see a green line you've probably not selected a layer.");
		ImGui::PopTextWrapPos();
		ImGui::SeparatorText("Shortcuts");
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
	//oude todo:
	//world en screen position op centrale plek uitvoeren voor ALLES dus niet zoom op door berekeningen heen gebruiken
		// want het bebeurt al in de screen/world position. (alle berekeningen doen in world position en dan converten zonder zoom etc.)
		// denk aan het schaakbord dat wordt ingezoomt maar nogsteeds de zelfde posities erop heeft

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	std::vector<Conveyor>& allConveyors = LayerManager::currentLayer->allConveyors;

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
			
			l.DrawConveyors(draw_list, camera, color, snapping);
		}
	}




	////oude conveyor draw code
	//if (allConveyors.size() > 0 && allConveyors[0].points.size() > 0)
	//{
	//	int rectSize = 20 * camera.zoom;
	//	draw_list->AddRect(camera.ToWorldPosition(ImVec2(Mouse::SelectedPoint.x - rectSize, Mouse::SelectedPoint.y - rectSize)),
	//		camera.ToWorldPosition(ImVec2(Mouse::SelectedPoint.x + rectSize, mouse.SelectedPoint.y + rectSize)),
	//		ImColor(ImVec4(1, 0, 0, 1)), 2.0f * camera.zoom);

	//	//Draw newline
	//	if (editMode && showNewLine && ImGui::IsWindowFocused())
	//	{
	//		

	//		draw_list->AddLine(camera.ToWorldPosition(lineStart), mouseWorldPos, ImColor(ImVec4(0, 1, 0, 1)), 20.0f * camera.zoom);
	//	}
	//}

	//grid Cursor
	if (snapping && editMode)
	{
		ImVec2 worldPos = Mouse::liveMousePosition;

		float relativePosX = worldPos.x - grid.position.x;
		float relativePosY = worldPos.y - grid.position.y;

		Mouse::snapPosition.x = round(relativePosX / grid.tileScaled) * grid.tileScaled;
		Mouse::snapPosition.y = round(relativePosY / grid.tileScaled) * grid.tileScaled;

		draw_list->AddCircleFilled(Mouse::snapPosition, 10.f, ImColor(255, 0, 255, 255), 12);
	}
}

void WindowManager::Draw()
{
	DrawCanvas();
	DrawSettings();
}
