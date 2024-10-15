#include "Grid.h"

void Grid::Update(const Camera& camera)
{
	begin = Tools::AddImVec2(position, ImVec2(-padding, -padding));
	end = Tools::AddImVec2(begin, 2600);

	//tileScaled = tileSize * camera.zoom;
	//
	//float offsetX = fabs((position.x + 200) - camera.position.x);
	//
	//std::cout << offsetX << std::endl;
	//
	//if (offsetX > 100)
	//	position.x = camera.position.x - 200;
}

void Grid::Draw(ImDrawList* draw_list, Camera& camera)
{
	//-200			//width+200
	//  0	  1		 2	  3		  4		  5	      6		  7		  8		  9		 10		 11		  12	  13	  14
	//-200	-100	 0	 100	 200	 300	 400	 500	 600	 700	 800	 900	 1000	 1100	 1200
	//
	//1 -100
	//
	//2 0
	//
	//3 100
	//
	//4 200
	//
	//5 300
	//
	//6 400
	//
	//7 500
	//
	//8 600
	//
	//9 700
	//
	//10 800
	//
	//11 900
	for (float x = begin.x; x < end.x; x += tileSize) 
	{
		ImVec2 start = ImVec2(x, position.y);
		ImVec2 stop = ImVec2(x, end.y);

		draw_list->AddLine(
			camera.ToWorldPosition(start), 
			camera.ToWorldPosition(stop), 
			ImColor(200, 200, 200));
	}

	for (float y = begin.x; y < end.y; y += tileSize)
	{
		ImVec2 start = ImVec2(position.x, y);
		ImVec2 stop = ImVec2(end.x, y);

		draw_list->AddLine(
			camera.ToWorldPosition(start),
			camera.ToWorldPosition(stop),
			ImColor(200, 200, 200));
	}
}