#include "Layer.h"
#include "LayerManager.h"
#include "Settings.h"
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
		ImGui::GetWindowDrawList()->AddLine(camera.ToWorldPosition(LayerManager::currentLayer->selectedConveyor->selectedPoint->position),
			endPosition, ImColor(newLineColor), 20 * camera.zoom); //getting an error because selectedPoint or conveyor is 0?
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
/// returns the closest conveyor in this layer
/// </summary>
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
	allConveyors[closestConveyorIndex].selectedPoint = &allConveyors[closestConveyorIndex].path[closestPointIndex];
	return &allConveyors[closestConveyorIndex];
}

void Layer::CreateConveyor(ImVec2 position, Camera& camera)
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

	//edits an existing conveyor or a new conveyor
	if (!Conveyor::createNewConveyor && LayerManager::currentLayer->selectedConveyor->edit)
	{
		Conveyor& currentConveyor = *LayerManager::currentLayer->selectedConveyor;
		currentConveyor.NewPoint(position);
	}
	Conveyor::createNewConveyor = false;
}
