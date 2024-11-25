#include "Layer.h"
#include "LayerManager.h"
#include "Settings.h"
#include "BridgeConveyor.h"

bool selected;

void Layer::ClearSelection()
{
	this->UnselectAllConveyors();
	Conveyor::createNewConveyor = true;
}

void Layer::UnselectAllConveyors()
{
	for (Conveyor& c : allConveyors)
	{
		c.selected = false;
		c.edit = false;
	}
}

void Layer::DrawNewLine(ImDrawList* draw_list, ImVec2& endPosition, Camera& camera, bool focusedWindow)
{
	ImVec4 newLineColor = ImVec4(0, 1, 0, 1);

	if (connecting)
		newLineColor = ImVec4(0.6f, 0.5f, 0.1f, 1);

	if (focusedWindow && LayerManager::currentLayer->selectedConveyor &&
		LayerManager::currentLayer->selectedConveyor->edit &&
		LayerManager::currentLayer->selectedConveyor->selected)
	{
		if (endPosition.x != Mouse::liveMousePosition.x && endPosition.y != Mouse::liveMousePosition.y)
		{
			endPosition = camera.ToWorldPosition(endPosition);
		}
		//! TODO: FIX THSI DONT DIRECTLY DELETE LAYERS BC THSI WILL CRASH
		//! only delete after all the layers are looped over do something similar to the deletion layer used with the conveyors
		ImGui::GetWindowDrawList()->AddLine(camera.ToWorldPosition(LayerManager::currentLayer->selectedConveyor->selectedPoint->position),
			endPosition, ImColor(newLineColor), 20 * camera.zoom);
		//works when not using the mouse position or the other way around depending on if you use world or screen position
	}
}

void Layer::DrawConveyors(ImDrawList* draw_list, Camera& camera, ImVec4& color, bool snapping)
{
	for (Conveyor& c : allConveyors)
	{
		ImVec4 currentColor = color;

		if (c.edit)
		{
			currentColor = ImVec4(0, 0, 1, 1);
		}
		else if (c.selected)
		{
			currentColor = ImVec4(1, 1, 0, 1);
		}

		ImVec2 mouseWorldPos;
		if (snapping) mouseWorldPos = Mouse::snapPosition;
		else mouseWorldPos = Mouse::liveMousePosition;

		c.Draw(currentColor, 20 * camera.zoom, mouseWorldPos, camera);
	}
}

void Layer::DrawLayerHeader(Camera& camera, std::vector<int>& deletionList)
{
	ImVec2& SelectedPoint = Mouse::SelectCursorPosition;

	for (int i = 0; i < allConveyors.size(); i++)
	{
		Conveyor& loopedConveyor = allConveyors.at(i);

		char subHeaderLabel[64];
		snprintf(subHeaderLabel, sizeof(subHeaderLabel), "Conveyor %d", allConveyors.at(i).id);

		ImGui::PushID(allConveyors.at(i).id);
		if (allConveyors.at(i).selected)
			ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(1.f, 0.3f, 0.2f, 1.f));
		else
			ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.3f, 0.2f, 1.f));
		if (ImGui::CollapsingHeader(subHeaderLabel))
		{
			ImVec2 conveyorPosition = Conveyor::AveragePointsPosition(allConveyors.at(i).path);

			char conveyorPositionLabel[64];
			snprintf(conveyorPositionLabel, sizeof(conveyorPositionLabel), "Conveyor Position %d %d", (int)conveyorPosition.x, (int)conveyorPosition.y);
			ImGui::Text(conveyorPositionLabel);
			if (ImGui::Button("Select") && this == LayerManager::currentLayer)
			{
				UnselectAllConveyors();

				allConveyors.at(i).selected = true;
				ImVec2 averageConveyorPos = Conveyor::AveragePointsPosition(allConveyors.at(i).path);
				camera.position = Tools::AddImVec2(ImVec2(-averageConveyorPos.x / camera.zoom, -averageConveyorPos.y / camera.zoom), camera.center);
			}
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0, 1));
			if (ImGui::Button("Delete"))
			{
				deletionList.push_back(i);
			}
			ImGui::PopStyleColor();

			if (allConveyors.size() > 0)
			{
				ImGui::Text("Points %d", allConveyors.at(i).path.size());
				for (int j = 0; j < allConveyors.at(i).path.size(); j++)
				{
					char buttonLabel[64];
					snprintf(buttonLabel, sizeof(buttonLabel), "Point %d", j);

					if (ImGui::Button(buttonLabel))
					{
						SelectedPoint = allConveyors.at(i).path.at(j).position;
						camera.position = Tools::AddImVec2(ImVec2(-SelectedPoint.x / camera.zoom, -SelectedPoint.y / camera.zoom), camera.center);
					}
					ImGui::SameLine();
					ImGui::Text("X: %d, Y: %d", -(int)loopedConveyor.path.at(j).position.x, -(int)loopedConveyor.path.at(j).position.y);
				}
			}
		}
		ImGui::PopStyleColor();
		ImGui::PopID();
		for (int& i : deletionList)
		{
			ClearSelection();
			Tools::DeleteFromList(allConveyors, allConveyors.at(i));
		}
		deletionList.clear();
	}
}

/// <summary>
/// returns the closest conveyor on the screen
/// </summary>
/// <param name="camera"> is used to convert the mouse position into worldspace </param>
/// <param name="origin"> is the point closest to the conveyor </param>
/// <returns></returns>
Conveyor* Layer::ReturnClosestConveyor(Camera& camera, ImVec2& origin)
{
	float smallestDistance = 99999;
	point* closestPoint = 0;

	int closestConveyorIndex = -1;
	int closestPointIndex = -1;

	for (int c = 0; c < allConveyors.size(); c++)
	{
		Conveyor& conveyor = allConveyors[c];
		for (int p = 0; p < allConveyors[c].path.size(); p++)
		{
			point& point = conveyor.path[p];
			ImVec2 position = camera.ToWorldPosition(point.position);
			float distance = Tools::Magnitude(position, Mouse::liveMousePosition);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				closestPoint = &point;

				closestConveyorIndex = c;
				closestPointIndex = p;
			}
		}
	}

	//selected point word geselecteerd hier zodat als je ee nieuwe conveyor selecteerd hij gelijk de closestpoint returned
	allConveyors[closestConveyorIndex].selectedPoint = &allConveyors[closestConveyorIndex].path[closestPointIndex];
	return &allConveyors[closestConveyorIndex];
}

Conveyor* Layer::ReturnClosestConveyor(Camera& camera, ImVec2& origin, Conveyor& selected)
{
	float smallestDistance = 99999;
	point* closestPoint = 0;

	int closestConveyorIndex = -1;
	int closestPointIndex = -1;

	for (int c = 0; c < allConveyors.size(); c++)
	{
		Conveyor& conveyor = allConveyors[c];
		for (int p = 0; p < allConveyors[c].path.size(); p++)
		{
			point& point = conveyor.path[p];

			ImVec2 position = camera.ToScreenPosition(point.position);
			float distance = Tools::Magnitude(position, origin);
			if (distance < smallestDistance)
			{
				smallestDistance = distance;
				closestPoint = &point;

				if (&allConveyors[c] == &selected) continue;
				closestConveyorIndex = c;
				closestPointIndex = p;
				std::cout << "World Position: (" << position.x << ", " << position.y << ") " << "Distance to origin: " << distance << std::endl;
			}
		}
	}

	//selected point gets selected here so when you select a new conveyor it instantly returns the closest point
	if (closestConveyorIndex > -1 || closestPointIndex > -1)
	{
		allConveyors[closestConveyorIndex].selectedPoint = &allConveyors[closestConveyorIndex].path[closestPointIndex];
		return &allConveyors[closestConveyorIndex];
	}
	return 0;
}


void Layer::CreateConveyor(ImVec2 position)
{
	if (Conveyor::createNewConveyor)
	{
		LayerManager::currentLayer->UnselectAllConveyors();
		Conveyor newConveyor(Conveyor::alltimeConveyorCount++);
		allConveyors.push_back(newConveyor);

		LayerManager::currentLayer->selectedConveyor = &allConveyors[allConveyors.size() - 1];
		Conveyor& currentConveyor = *LayerManager::currentLayer->selectedConveyor;
		currentConveyor.selected = true;
		currentConveyor.edit = true;
		currentConveyor.path.emplace_back(position);
		currentConveyor.selectedPoint = &currentConveyor.path[0];
	}
	////////////////////////////////////////////////////////////////////////
	// move to 2 different functions

	//edits an existing conveyor or a new conveyor
	if (!Conveyor::createNewConveyor && LayerManager::currentLayer->selectedConveyor->edit)
	{
		Conveyor& currentConveyor = *LayerManager::currentLayer->selectedConveyor;
		currentConveyor.NewPoint(position);
	}
	Conveyor::createNewConveyor = false;
}

bool Layer::EditConveyor(Camera& camera, ImVec2& position)
{
	if (LayerManager::currentLayer->allConveyors.size() < 2) return false;

	//find closest point
	Conveyor& temp = *LayerManager::currentLayer->ReturnClosestConveyor(camera, position, *LayerManager::currentLayer->selectedConveyor);
	point* closest = 0;

	if (&temp)
		closest = Conveyor::FindClosestPointInWorld(temp.path, position, camera, 100);

	if (!closest)
		return false;

	//add closest point to the connections of the selected point (the point where newline originates from)
	if (selectedConveyor)
		LayerManager::currentLayer->selectedConveyor->selectedPoint->connections.emplace_back(*closest);
	else return false;

	for (int rootPointIndex = 0; rootPointIndex < temp.path.size(); rootPointIndex++)
	{
		point& rootPoint = temp.path.at(rootPointIndex);

		//copy the point over to the path of the selected conveyor (the conveyor currently being edited)
		point& copiedRootPoint = LayerManager::currentLayer->selectedConveyor->path.emplace_back(rootPoint);
		for (point& connectedPoint : rootPoint.connections)
		{
			//copy over all the connection points the "branches" that aren't connected to any path point
			copiedRootPoint.connections.emplace_back(connectedPoint);
		}
	}

	Tools::DeleteFromList(LayerManager::currentLayer->allConveyors, temp);

	Layer::ClearSelection();
	LayerManager::currentLayer->selectedConveyor = 0;
	return true;
}

void to_json(json& j, const Layer& l)
{
	j = json
	{
		{"layerCount", l.layerCount},
		{"id", l.id},
		{"name", l.name},
		{"allConveyors", l.allConveyors}
	};
}

point* ClosestPointInLayers(Camera& camera, ImVec2& position)
{
	Conveyor* temp = 0;
	point* closest = 0;
	point* current = 0;
	for (Layer& l : LayerManager::allLayers)
	{
		if (&l == LayerManager::currentLayer) continue;

		temp = l.ReturnClosestConveyor(camera, position);

		if (temp)
			current = Conveyor::FindClosestPointInWorld(temp->path, position, camera, 100);

		if (!closest)
			closest = current;

		if (closest && current && Tools::Magnitude(current->position, Mouse::liveMousePosition) < Tools::Magnitude(closest->position, Mouse::liveMousePosition))
		{
			closest = current;
		}
	}

	return closest;
}

void Layer::CreateBridgePoint(Camera& camera, ImVec2& position)
{
	if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && !ImGui::IsKeyDown(ImGuiKey_LeftShift) && LayerManager::allLayers.size() > 1 && LayerManager::currentLayer->selectedConveyor->selectedPoint)
	{
		BridgeConveyor newBridge;

		std::cout << "new bridge created" << std::endl;

		newBridge.conveyorIndex1 = Tools::FindInList(LayerManager::currentLayer->allConveyors, *LayerManager::currentLayer->selectedConveyor);
		newBridge.pointIndex1 = Tools::FindInList(LayerManager::currentLayer->selectedConveyor->path, *LayerManager::currentLayer->selectedConveyor->selectedPoint);
		newBridge.layerIndex1 = Tools::FindInList(LayerManager::allLayers, *LayerManager::currentLayer);
		point* closest = ClosestPointInLayers(camera, Mouse::liveMousePosition);

		int index = -1;
		int closestConveyorIndex = -1;
		for (int layerIndex = 0; layerIndex < LayerManager::allLayers.size() - 1; layerIndex++)
		{
			Layer& l = LayerManager::allLayers[layerIndex];

			for (Conveyor& c : l.allConveyors)
			{
				index = Tools::FindInList(c.path, *closest);
				closestConveyorIndex = Tools::FindInList(l.allConveyors, c);

				if (index > -1)
				{
					newBridge.conveyorIndex2 = closestConveyorIndex;
					newBridge.pointIndex2 = index;
					newBridge.layerIndex2 = layerIndex;
				}
			}
		}
		if (newBridge.conveyorIndex2 > -1)
		{
			std::cout << "emplace back bridge" << std::endl;
			BridgeConveyor::allBridgeConveyors.emplace_back(newBridge);
		}
	}
}

bool Layer::FindConnection(Camera& camera, ImVec2 newLineEnd)
{
	if (!LayerManager::currentLayer->selectedConveyor) return false;

	ImVec2 position = Mouse::liveMousePosition;

	if (!ImGui::IsKeyDown(ImGuiKey_LeftShift))
	{
		if (!Settings::snapping)
			Layer::newLineEnd = Mouse::liveMousePosition;
		else
			Layer::newLineEnd = Mouse::snapPosition;
	}
	else if (LayerManager::currentLayer->allConveyors.size() > 1 && !ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) //when pressing lshift find closest point
	{
		Conveyor* temp = LayerManager::currentLayer->ReturnClosestConveyor(camera, position, *LayerManager::currentLayer->selectedConveyor);
		point* closest = 0;
		if (temp)
			closest = Conveyor::FindClosestPointInWorld(temp->path, position, camera, 100);

		if (closest)
			Layer::newLineEnd = closest->position;
		else
			Layer::newLineEnd = Mouse::liveMousePosition;
	}
	if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && LayerManager::allLayers.size() > 0 && LayerManager::currentLayer->allConveyors.size() > 0)
	{
		point* closest = ClosestPointInLayers(camera, position);

		if (closest)
			Layer::newLineEnd = closest->position;
		else
			Layer::newLineEnd = Mouse::liveMousePosition;
	}

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		CreateBridgePoint(camera, position);
	}

	return false;
}
