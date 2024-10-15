#include "Layer.h"
#include "LayerManager.h"

bool selected;

void Layer::UnselectAllConveyors()
{
	for (Conveyor& c : allConveyors)
	{
		c.selected = false;
	}
}

void Layer::DrawConveyors(ImDrawList* draw_list, Camera& camera, ImVec4 color)
{
	for (Conveyor& c : allConveyors)
	{
		ImVec4 currentColor = color;

		if (c.selected)
		{
			currentColor = ImVec4(1, 1, 0, 1);
		}

		if (c.points.size() >= 2)
		{
			for (int i = 0; i < c.points.size() - 1; i++)
			{
				draw_list->AddLine(camera.ToWorldPosition(c.points[i]), camera.ToWorldPosition(c.points[i + 1]), ImColor(currentColor), 20.0f * camera.zoom);
			}
		}
	}
}

void Layer::DrawLayerHeader(Camera& camera, std::vector<int>& deletionList)
{	
	ImVec2& SelectedPoint = mouse.SelectedPoint;

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
			ImVec2 conveyorPosition = Tools::AverageVec2(allConveyors.at(i).points);

			char conveyorPositionLabel[64];
			snprintf(conveyorPositionLabel, sizeof(conveyorPositionLabel), "Conveyor Position %d %d", (int)conveyorPosition.x, (int)conveyorPosition.y);
			ImGui::Text(conveyorPositionLabel);
			if (ImGui::Button("Select") && this == LayerManager::currentLayer)
			{
				UnselectAllConveyors();

				allConveyors.at(i).selected = true;
				ImVec2 averageConveyorPos = Tools::AverageVec2(allConveyors.at(i).points);
				//deze camera.zoom hier niet
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
				ImGui::Text("Points %d", allConveyors.at(i).points.size());
				for (int j = 0; j < allConveyors.at(i).points.size(); j++)
				{
					char buttonLabel[64];
					snprintf(buttonLabel, sizeof(buttonLabel), "Point %d", j);

					if (ImGui::Button(buttonLabel))
					{
						SelectedPoint = allConveyors.at(i).points.at(j);
						camera.position = Tools::AddImVec2(ImVec2(-SelectedPoint.x / camera.zoom, -SelectedPoint.y / camera.zoom), camera.center);
					}
					ImGui::SameLine();
					ImGui::Text("X: %d, Y: %d", -(int)loopedConveyor.points.at(j).x, -(int)loopedConveyor.points.at(j).y);
				}
			}
		}
		ImGui::PopStyleColor();
		ImGui::PopID();
		for (int& i : deletionList)
		{
			Tools::DeleteFromList(allConveyors, allConveyors.at(i));
		}
		deletionList.clear();
	}
}
