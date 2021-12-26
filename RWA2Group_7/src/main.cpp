#include <iostream>
#include <array>
#include "../include/mouse/mouse.h"
#include "../include/api/api.h"

int main() {
	
	rwa2::Mouse mouse;  	//object for class Mouse created
	
	mouse.display_walls();	// display the boundary wall

	std::pair<int,int> G_position{std::make_pair(0,15)}; 	// define goal position
	mouse.set_g_position(G_position);   

	API::clearAllColor();		// clear color in the simulator if any

	mouse.clear_stack_vector();		//empty stack and list before calling search maze to discard garbage value

    if(mouse.search_maze())  	// search the path for the first time
	{
		mouse.move_to_goal();   // move robot to goal position
	}
	else 
	{
		std::cout<< "Path not found" << '\n';  // return path not found if path not availble
	}

}

