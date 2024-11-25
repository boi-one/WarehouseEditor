#pragma once
#include "Conveyor.h"
#include "Mouse.h"

/// <summary>
/// A layer is a collection of conveyors
/// </summary>
class Layer
{
public:
	static inline int layerCount;
	int id;
	std::string name = "layer name";
	bool renameLayer = false;
	bool selected = false;
	bool hidden = false;
	std::vector<Conveyor> allConveyors;
	Conveyor* selectedConveyor = 0;
	static inline bool connecting = false;
	static inline ImVec2 newLineEnd;

public:
	Layer()
	{
		layerCount++;
		this->id = layerCount;
	}

	/// <summary>
	/// unselects and set all the bools to default for all of the conveyors in the layer and makes it possible to create a new conveyor
	/// </summary>
	void ClearSelection();

	/// <summary>
	/// unselects all of the conveyors (selected and edit are both set to false)
	/// </summary>
	void UnselectAllConveyors();

	/// <summary>
	/// Draws the green line on the screen when editing or creating a conveyor
	/// </summary>
	/// <param name="draw_list"> is the way ImGui draws to windows, this is needed to display the new line</param>
	/// <param name="endPosition"> is the position for the new line to end. Most of the time this is just the mouse position but in certain cases like the snapping 
	/// and while connecting to other conveyors the new line ends at other positions than the mouse</param>
	/// <param name="camera"> is used to convert the start point to world position</param>
	/// <param name="focusedWindow"> if the window is focused or not so the green line only shows when you are actually working on the canvas </param>
	void DrawNewLine(ImDrawList* draw_list, ImVec2& endPosition, Camera& camera, bool focusedWindow);

	/// <summary>
	/// Draws the conveyors onto the screen
	/// </summary>
	/// <param name="draw_list"> is the way ImGui draws to windows, this is needed to display the conveyors</param>
	/// <param name="camera"> is used to convert the points to world position</param>
	/// <param name="color"> is the color value of the conveyor</param>
	/// <param name="snapping"> is used to tell if snapping is enabled or not </param>
	void DrawConveyors(ImDrawList* draw_list, Camera& camera, ImVec4& color, bool snapping);

	/// <summary>
	/// draws the layer UI in the settings window
	/// </summary>
	/// <param name="camera"> is used to center the camera on a certain point or on a conveyor</param>
	/// <param name="deletionList"> is a list that keeps track of all the points that will need to be deleted after the loop ends</param>
	void DrawLayerHeader(Camera& camera, std::vector<int>& deletionList);

	/// <summary>
	/// returns the closest conveyor from the origin
	/// </summary>
	/// <param name="camera"> is used to convert to the world position</param>
	/// <param name="origin"> the point which will be used to check which conveyor is closest to it </param>
	/// <returns> a pointer of the closest conveyor</returns>
	Conveyor* ReturnClosestConveyor(Camera& camera, ImVec2& origin);

	/// <summary>
	/// returns the closest conveyor from the origin
	/// </summary>
	/// <param name="camera"> is used to convert to the world position </param>
	/// <param name="origin"> the point which will be used to check which conveyor is closest to it </param>
	/// <param name="selected"> if selected is passed to the function this conveyor will be excluded</param>
	/// <returns></returns>
	Conveyor* ReturnClosestConveyor(Camera& camera, ImVec2& origin, Conveyor& selected);

	/// <summary>
	/// Creates a new conveyor and adds it to the allConveyors list in the currentLayer
	/// </summary>
	/// <param name="position"> is the position where the conveyor should be created</param>
	void CreateConveyor(ImVec2 position);

	/// <summary>
	/// Edit an already existing conveyor
	/// </summary>
	/// <param name="camera"> is used to convert to the world position</param>
	/// <param name="position"> is used to check if the mouse is close enough to the conveyor so it can be edited</param>
	/// <returns> true or false depending on if the conveyor is found or can be edited </returns>
	bool EditConveyor(Camera& camera, ImVec2& position);

	/// <summary>
	/// is used to merge multiple conveyor to eachother
	/// </summary>
	/// <param name="camera"> is used for converting to world position</param>
	/// <param name="newLineEnd"> is the position where the new line (green line) should end</param>
	/// <returns> true or false depending if a connection could be made </returns>
	bool FindConnection(Camera& camera, ImVec2 newLineEnd);

	/// <summary>
	/// WIP!!!!!!! connects 2 conveyors to eachother on different layers
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="position"></param>
	void CreateBridgePoint(Camera& camera, ImVec2& position);

	friend void to_json(json& j, const Layer& l);
};

/// <summary>
/// Finds the closest point in all of the layers
/// </summary>
/// <param name="camera"> is used to convert to world position</param>
/// <param name="position"> the position closest to the closest point </param>
/// <returns> a pointer of the closeset point</returns>
point* ClosestPointInLayers(Camera& camera, ImVec2& position);
