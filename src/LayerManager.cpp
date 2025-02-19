#include "LayerManager.h"

void LayerManager::ManageLayers(Camera& camera, std::vector<int>& deletionList)
{
	if (ImGui::Button("+"))
	{
		AddLayer();
	}
	ImGui::SameLine();
	if (ImGui::Button("-"))
	{
		RemoveLayer();
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::Text("Removes the last layer added.");
		ImGui::EndTooltip();
	}
	ImGui::SameLine();
	ImGui::Text("Layers: ");
	if (ImGui::Button("Unhide all Layers"))
	{
		for (Layer& l : allLayers)
		{
			l.hidden = false;
		}
	}
	for (int i = 0; i < allLayers.size(); ++i)
	{
		Layer& loopedLayer = allLayers.at(i);

		char layerLabel[64];
		snprintf(layerLabel, sizeof(layerLabel), "%d. Layer: %s\nitems %d", i, loopedLayer.name.c_str(), (int)loopedLayer.allConveyors.size());

		if (loopedLayer.selected)
		{
			ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0.3f, 0.2f, 1));
		}
		if (ImGui::CollapsingHeader(layerLabel))
		{
			loopedLayer.DrawLayerHeader(camera, deletionList);
		}
		if (loopedLayer.selected)
		{
			ImGui::PopStyleColor();
		}
		ImGui::Separator();
		ImGui::PushID(allLayers[i].id);
		if (ImGui::Button("move up") && i > 0)
		{
			if (&loopedLayer == LayerManager::currentLayer)
				LayerManager::currentLayer->ClearSelection();
			Layer tempLayer = allLayers[i];
			Layer tempLayerPrev = allLayers[i - 1];
			allLayers[i - 1] = tempLayer;
			allLayers[i] = tempLayerPrev;

		}
		ImGui::SameLine();
		if (ImGui::Button("move down") && i < allLayers.size() - 1)
		{
			LayerManager::currentLayer->ClearSelection();
			Layer tempLayer = allLayers[i];
			Layer tempLayerPrev = allLayers[i + 1];
			allLayers[i + 1] = tempLayer;
			allLayers[i] = tempLayerPrev;
		}
		ImGui::SameLine();
		ImGui::Checkbox("", &loopedLayer.hidden);
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Hide/Unhide layer");
			ImGui::EndTooltip();
		}
		if (ImGui::Button("rename layer"))
		{
			for (Layer l : allLayers)
				l.renameLayer = false;
			loopedLayer.renameLayer = !loopedLayer.renameLayer;
		}
		const char* selectLabel = loopedLayer.selected ? "unselect" : "select";
		ImGui::SameLine();
		if (ImGui::Button(selectLabel))
		{
			LayerManager::currentLayer->ClearSelection();
			for (Layer& l : allLayers)
			{
				l.UnselectAllConveyors();

				if (&l != &loopedLayer)
				{
					l.selected = false;
				}
			}
			loopedLayer.selected = !loopedLayer.selected;

			for (Layer& l : allLayers)
			{
				if (l.selected)
					LayerManager::currentLayer = &l;
			}
		}
		if (loopedLayer.renameLayer)
		{
			char renameLabel[64];
			snprintf(renameLabel, sizeof(renameLabel), "edit layer %d", loopedLayer.id);

			char input[128] = "";
			if (ImGui::Begin(renameLabel))
			{
				//strncpy(loopedLayer.name.data(), (char*)&input, sizeof(input));
				ImGui::InputText("Enter layer name", input, IM_ARRAYSIZE(input));
				//! todo: fix the naming so you can actually rename layers
				if (ImGui::Button("Apply"))
				{
					loopedLayer.name = input;
					loopedLayer.renameLayer = false;
				}
				ImGui::SameLine();
				if (ImGui::Button("Close"))
					loopedLayer.renameLayer = false;
				std::cout << "layername  " << loopedLayer.name << std::endl;
				ImGui::End();
			}
		}
		ImGui::PopID();
		ImGui::Separator();
	}
}

void LayerManager::RemoveLayer()
{
	if (allLayers.size() > 0)
		allLayers.pop_back();
}

void LayerManager::AddLayer()
{
	Layer layer;
	if (allLayers.size() < 1)
		allLayers.reserve(5);
	allLayers.push_back(layer);
	if (allLayers.size() < 2)
		allLayers.at(0).selected = true;
}

void to_json(json& j, const LayerManager& lm)
{
	j = json{ "allBridgeConveyors", lm.allBridgeConveyors };
}

void from_json(const json& j, LayerManager& lm)
{
	j.at("allBridgeConveyors").get_to(lm.allBridgeConveyors);
}
