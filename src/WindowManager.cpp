#include "WindowManager.h"
#include "Grid.h"
#include "Settings.h"
#include "WindowManager.h"

void WindowManager::DrawCanvas()
{

	ImGuiIO& io = ImGui::GetIO();

	camera.UpdateCamera();

	Mouse::liveMousePosition = ImGui::GetMousePos();
	std::vector<Conveyor>& allConveyors = LayerManager::currentLayer->allConveyors;

	ImGui::SetNextWindowSize(ImVec2(1080, 720));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0.1f, 1));
	ImGui::Begin("Canvas", 0, window_flags);
	focusedWindow = ImGui::IsWindowHovered();
	const char* selectWindow = focusedWindow ? "active window: Canvas" : "active window: Settings";
	ImGui::Text(selectWindow);
	ImGui::PopStyleColor();

	if (focusedWindow && LayerManager::currentLayer->selected)
	{
		LayerManager::currentLayer->FindConnection(camera, { 0, 0 });

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && Mouse::canvasFocus && LayerManager::currentLayer->selected && Settings::currentMode == Settings::Mode::edit)
		{
			ImVec2 position;
			if (Settings::snapping)
				position = camera.ToScreenPosition(Mouse::snapPosition);
			else
				position = camera.ToScreenPosition(Mouse::liveMousePosition);
			if (ImGui::IsKeyDown(ImGuiKey_LeftShift))
			{
				LayerManager::currentLayer->EditConveyor(camera, Mouse::liveMousePosition);
			}
			else //regular click without lshift
			{
				LayerManager::currentLayer->CreateConveyor(position);
			}
		}

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && focusedWindow)
		{
			Mouse::rightMouseClickPos = Mouse::liveMousePosition;
			ImVec2 worldPosRightClick = camera.ToScreenPosition(Mouse::rightMouseClickPos);

			switch (Settings::currentMode)
			{
			case Settings::Mode::view:
			{

			} break;
			case Settings::Mode::move:
			{
				if (LayerManager::currentLayer->allConveyors.size() < 1) break;
				LayerManager::currentLayer->ClearSelection();
				LayerManager::currentLayer->selectedConveyor = LayerManager::currentLayer->ReturnClosestConveyor(camera, Mouse::liveMousePosition);
				LayerManager::currentLayer->selectedConveyor->selected = true;
			} break;
			case Settings::Mode::edit:
			{
				if (Conveyor::createNewConveyor && LayerManager::currentLayer)
				{
					if (LayerManager::currentLayer->allConveyors.size() < 1) break;
					LayerManager::currentLayer->selectedConveyor = LayerManager::currentLayer->ReturnClosestConveyor(camera, Mouse::liveMousePosition);
					Conveyor::createNewConveyor = false;
					LayerManager::currentLayer->selectedConveyor->selected = true;
					LayerManager::currentLayer->selectedConveyor->edit = true;
				}
				else
				{
					LayerManager::currentLayer->selectedConveyor->selectedPoint = Conveyor::FindClosestPointInWorld(LayerManager::currentLayer->selectedConveyor->path, worldPosRightClick, camera, 9'999);
				}
			} break;
			}
		}
		static ImVec2 dragOffset;
		if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
		{
			if (!Mouse::clickedMiddle)
			{
				Mouse::middleMouseClickPos = Mouse::liveMousePosition;
				Mouse::clickedMiddle = true;

				dragOffset = ImGui::GetMousePos();
			}
			if (LayerManager::currentLayer->selectedConveyor && LayerManager::currentLayer->selectedConveyor->selected)
			{
				ImVec2 currentMousePos = ImGui::GetMousePos();
				ImVec2 difference = ImVec2(currentMousePos.x - dragOffset.x, currentMousePos.y - dragOffset.y);
				for (point& basePoint : LayerManager::currentLayer->selectedConveyor->path)
				{
					basePoint.position.x += difference.x;
					basePoint.position.y += difference.y;

					for (point& p : basePoint.connections)
					{
						p.position.x += difference.x;
						p.position.y += difference.y;
					}
				}

				Mouse::SelectCursorPosition.x += difference.x;
				Mouse::SelectCursorPosition.y += difference.y;

				dragOffset = currentMousePos;
			}
		}
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Middle) && Mouse::clickedMiddle)
		{
			Mouse::clickedMiddle = false;
		}
	}

	//keyboard controls
	if (ImGui::IsWindowFocused())
	{
		if (!Settings::snapping)
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
		if (Settings::snapping)
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
		if (ImGui::IsWindowHovered())
		{
			if (io.MouseWheel > 0 && camera.zoom < 2.9f)
				camera.zoom += 0.1f;
			if (io.MouseWheel < 0 && camera.zoom > 0.5f)
				camera.zoom -= 0.1f;
		}
	}
	if (ImGui::IsMouseDown(1))
		ImGui::SetWindowFocus("Canvas");

	if (ImGui::IsKeyPressed(ImGuiKey_R)) //resets the camera to 0
	{
		camera.position = ImVec2(0, 0);
		camera.zoom = 1.0f;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_E))
	{
		if (LayerManager::currentLayer->selectedConveyor)
		{
			LayerManager::currentLayer->selectedConveyor->edit = true;
		}
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		if (LayerManager::currentLayer->selectedConveyor)
		{
			bool& edit = LayerManager::currentLayer->selectedConveyor->edit;
			if (!edit)
			{
				LayerManager::currentLayer->selectedConveyor->selected = false;
				Conveyor::createNewConveyor = true;
			}
			edit = false;

		}

		/*for (Layer& l : LayerManager::allLayers)
		{
			l.UnselectAllConveyors();
			Mouse::SelectCursorPosition = ImVec2(camera.position.x - 1000, camera.position.y);
		}*/
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Slash))
	{
		Settings::showShortcuts = !Settings::showShortcuts;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_H))
	{
		LayerManager::currentLayer->hidden = !LayerManager::currentLayer->hidden;
	}

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
		Settings::appRunning = false;
	}
	if (ImGui::Button("Shortcuts and Help"))
	{
		Settings::showShortcuts = !Settings::showShortcuts;
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

	const char* snappingLabel = Settings::snapping ? "Snapping  Enabled" : "Snapping  Disabled";
	if (ImGui::Button(snappingLabel) && grid.active)
	{
		camera.position.x = round(camera.position.x / grid.tileScaled) * grid.tileScaled;
		camera.position.y = round(camera.position.y / grid.tileScaled) * grid.tileScaled;

		Settings::snapping = !Settings::snapping;
	}

	int selectedMode = (int)Settings::currentMode;

	const char* modeLabels[] = { "View", "Move", "Edit" };
	if (ImGui::Combo("Mode", &selectedMode, modeLabels, IM_ARRAYSIZE(modeLabels)))
	{
		Settings::currentMode = (Settings::Mode)selectedMode;
		LayerManager::currentLayer->UnselectAllConveyors();
	}

	const char* gridLabel = grid.active ? "Show Grid Enabled" : "Show Grid Disabled";
	if (ImGui::Button(gridLabel))
	{
		grid.active = !grid.active;
		if (!grid.active) Settings::snapping = false;
	}

	LayerManager::ManageLayers(camera, deletionList);

	ImGui::End();

	if (Settings::showShortcuts)
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
			Settings::showShortcuts = false;
		}
		if (!ImGui::IsWindowFocused()) Settings::showShortcuts = false;
		ImGui::End();
	}
}

void WindowManager::Render()
{
	//de enige plek waar to world en to screen gebruikt mogen worden (nadat alle punten in de code geconvert zijn naar to world(?))
	//world en screen position op centrale plek uitvoeren voor ALLES dus niet zoom op door berekeningen heen gebruiken (alle berekeningen doen in world position en dan converten zonder zoom etc.)
	// denk aan het schaakbord dat wordt ingezoomt maar nogsteeds de zelfde posities erop heeft

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	std::vector<Conveyor>& allConveyors = LayerManager::currentLayer->allConveyors;

	if (grid.active)
	{
		grid.DrawGrid(draw_list, camera);
	}

	for (BridgeConveyor bc : LayerManager::allBridgeConveyors)
		bc.DrawBridgeConveyor(draw_list, camera);

	LayerManager::currentLayer->DrawNewLine(draw_list, Layer::newLineEnd, camera, focusedWindow);

	for (Layer l : LayerManager::allLayers)
	{
		if (!l.hidden)
		{
			ImVec4 color = ImVec4(0, 0, 0, 0);

			if (l.selected)
				color = ImVec4(1, 1, 1, 1);
			else
				color = ImVec4(0.4f, 0.4f, 0.4f, 1.f);

			l.DrawConveyors(draw_list, camera, color, Settings::snapping);
		}
	}

	//grid Cursor
	if (Settings::snapping && Settings::currentMode == Settings::Mode::edit)
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
	//need to rename it
}
