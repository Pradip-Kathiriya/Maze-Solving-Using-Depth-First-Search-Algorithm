#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}

bool search_maze(){ 

};

void rwa2::Mouse::move_forward(){
    return API::moveForward();
};

void rwa2::Mouse::turn_left(){
    return API::turnLeft();

};

void rwa2::Mouse::turn_right(){
    return API::turnRight();

};

void rwa2::Mouse::update_wall(int m_x, int m_y,int direction){
    if (direction == NORTH){
		if (API::wallFront()){
			m_maze.at(m_x).at(m_y).set_wall(NORTH,true);
		}
		if (API::wallRight){
			m_maze.at(m_x).at(m_y).set_wall(EAST,true);
		}
		if (API::wallLeft){
			m_maze.at(m_x).at(m_y).set_wall(WEST,true);
		}
	rwa2::Mouse::display_walls();
	}

	if (direction == EAST){
		if (API::wallFront()){
			m_maze.at(m_x).at(m_y).set_wall(EAST,true);
		}
		if (API::wallRight){
			m_maze.at(m_x).at(m_y).set_wall(SOUTH,true);
		}
		if (API::wallLeft){
			m_maze.at(m_x).at(m_y).set_wall(NORTH,true);
		}
	rwa2::Mouse::display_walls();

	}

	if (direction == SOUTH){
		if (API::wallFront()){
			m_maze.at(m_x).at(m_y).set_wall(SOUTH,true);
		}
		if (API::wallRight){
			m_maze.at(m_x).at(m_y).set_wall(WEST,true);
		}
		if (API::wallLeft){
			m_maze.at(m_x).at(m_y).set_wall(EAST,true);
		}
	rwa2::Mouse::display_walls();
	}

	if (direction == WEST){
		if (API::wallFront()){
			m_maze.at(m_x).at(m_y).set_wall(WEST,true);
		}
		if (API::wallRight){
			m_maze.at(m_x).at(m_y).set_wall(NORTH,true);
		}
		if (API::wallLeft){
			m_maze.at(m_x).at(m_y).set_wall(SOUTH,true);
		}
	rwa2::Mouse::display_walls();
	}
}