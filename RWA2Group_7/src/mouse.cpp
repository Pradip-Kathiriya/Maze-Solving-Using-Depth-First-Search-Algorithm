#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include <algorithm>
#include <iostream>


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
            API::setText(g_position.first,g_position.second,"G1");
            
        }
    }
}

void rwa2::Mouse::clear_stack_vector() {
	 while(!m_stack.empty()) 		//empty stack and list before calling search maze to discard garbage value
    {m_stack.pop();}
	                        
    m_vector.clear();
}


bool rwa2::Mouse::search_maze() {

    if(m_position!=g_position)   //executes when current position is not goal
    {      
        if(m_stack.empty())
        {
            m_stack.push(m_position);   //current position inserted to stack
        }
    }
    else   //executes when current position is goal
    {
        while(!m_reverse.empty())  //clearing stack
        {   
            m_reverse.pop();
        }                          
        while(!m_stack.empty())      //reversing the output stack
		{
			std::pair<int,int>temp;
			temp=m_stack.top();
            API::setColor(temp.first, temp.second, 'G');
			m_reverse.push(temp);
			m_stack.pop();
		}
        m_position = m_reverse.top();    // resetting position coordinates for upcoming functions in mouse.cpp
       
        API::setColor(g_position.first,g_position.second,'o');
        return true;   //exits search_maze
    }

    if (!(std :: find(m_vector.begin(),m_vector.end(),m_position) != m_vector.end()))  //executes when current position is not in list of vectors
    {
        m_vector.push_back(m_position);    //element added to list
    }
    
    if(!(m_maze.at(m_position.first).at(m_position.second).is_wall(direction::NORTH)) && !(std :: find(m_vector.begin(),m_vector.end(),m_trial_pair=std::make_pair(m_position.first,m_position.second+1)) != m_vector.end()))
    {
        //executes when 2 conditions are satisfied: 1) No wall present at north side and 2) Upcoming node at north has not been visited yet 
        m_position.second=m_position.second+1;    
        m_stack.push(m_position);
        
    }
    
    else if(!(m_maze.at(m_position.first).at(m_position.second).is_wall(direction::EAST)) && !(std :: find(m_vector.begin(),m_vector.end(),m_trial_pair=std::make_pair(m_position.first+1,m_position.second)) != m_vector.end()))
    {
        //executes when 2 conditions are satisfied: 1) No wall present at east side and 2) Upcoming node at east has not been visited yet
        m_position.first=m_position.first+1;
        m_stack.push(m_position);
    
    }

    else if(!(m_maze.at(m_position.first).at(m_position.second).is_wall(direction::SOUTH)) && !(std :: find(m_vector.begin(),m_vector.end(),m_trial_pair=std::make_pair(m_position.first,m_position.second-1)) != m_vector.end()))
    {
        //executes when 2 conditions are satisfied: 1) No wall present at south side and 2) Upcoming node at south has not been visited yet    
        m_position.second=m_position.second-1;
        m_stack.push(m_position);
    
    }

    else if(!(m_maze.at(m_position.first).at(m_position.second).is_wall(direction::WEST)) && !(std :: find(m_vector.begin(),m_vector.end(),m_trial_pair=std::make_pair(m_position.first-1,m_position.second)) != m_vector.end()))
    {
        //executes when 2 conditions are satisfied: 1) No wall present at west side and 2) Upcoming node at west has not been visited yet 
        m_position.first=m_position.first-1;
        m_stack.push(m_position);
    
    }
    
    else 
    {
        if(!m_stack.empty())   //Backtracking
        {
            m_stack.pop();
        }
        else 
        {
            return false;  //Path not found
        }
    }
    if(!m_stack.empty())
    {
        m_position=m_stack.top();  //current robot position is top of the stack
        search_maze();
    }
    else 
    {
        return false;  //no path found
    }

		
}

// Move the robot in the simulator
void rwa2::Mouse::move_forward() {
    API::moveForward();
}

// rotate the robot 90 degree CCW
void rwa2::Mouse::turn_left() {
    API::turnLeft();
}

// rotate the robot 90 degree CW
void rwa2::Mouse::turn_right() {
    API::turnRight();
}

// Update the wall in the maze and highlight the wall in the simulator
void rwa2::Mouse::update_wall(){
    // check whether robot is facing NORTH or not
    if (m_direction == direction::NORTH){
        // update the wall in the maze when robot is facing NORTH in the current node
		if (API::wallFront()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::NORTH,true);
		}
		if (API::wallRight()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::EAST,true);
		}
		if (API::wallLeft()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::WEST,true);
		}
    // highlight the walls in the simultor according to upated wall in the maze
	rwa2::Mouse::display_walls();
	}

    // check whetherrobot is facing EAST or not
	if (m_direction == direction::EAST){
        // update the wall in the maze when robot is facing EAST in the current node
		if (API::wallFront()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::EAST,true);
		}
		if (API::wallRight()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::SOUTH,true);
		}
		if (API::wallLeft()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::NORTH,true);
		}
    // highlight the walls in the simultor according to upated wall in the maze
	display_walls();

	}
    
    // check whether robot is facing SOUTH or not
	if (m_direction == direction::SOUTH){
        // update the wall in the maze when robot is facing SOUTH in the current node
		if (API::wallFront()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::SOUTH,true);
		}
		if (API::wallRight()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::WEST,true);
		}
		if (API::wallLeft()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::EAST,true);
		}
    // highlight the walls in the simultor according to upated wall in the maze
	display_walls();
	}

    // check whether robot is facing WEST or not
	if (m_direction == direction::WEST){
        // update the wall in the maze when robot is facing WEST in the current node
		if (API::wallFront()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::WEST,true);
		}
		if (API::wallRight()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::NORTH,true);
		}
		if (API::wallLeft()){
			m_maze.at(m_position.first).at(m_position.second).set_wall(direction::SOUTH,true);
		}
    // highlight the walls in the simultor according to upated wall in the maze
	display_walls();
	}
}

// move the robot from start position to goal position
void rwa2::Mouse::move_to_goal() 
{
	while (true) 
	{
		std::pair <int,int> a = m_reverse.top();  // First element of the path (current position of the robot)
		m_reverse.pop();
		std::pair <int,int> b = m_reverse.top();  // Second elememt of the path (next position of robot)
		update_wall();
        //check whether robot facing NORTH or not
        if(m_direction == NORTH) 
		{
            // check whether the next position of robot is in NORTH direction or not
			if ((b.first - a.first == 0) && (b.second - a.second == 1))  
			{
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{

					 API::clearAllColor(); 
					 clear_stack_vector();
						if(!search_maze())
						{
							break;      // break loop if goal position is reached
						}
						move_to_goal();
						if ( m_position == g_position )  
						{
							break;     // break loop if goal position is reached
						}
				}
				else
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.second = m_position.second + 1 ; 
                    m_direction = (direction::NORTH);
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in EAST direction or not
			if ((b.first - a.first == 1) && (b.second - a.second == 0))
			{
                // rotate the robot to orient in the direction of movement and update current direction
				turn_right();
                m_direction = (direction::EAST);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
						if(!search_maze())
						{
							break;      // break loop if goal position is reached
						}
						move_to_goal();
						if ( m_position == g_position )
						{
							break;      // break loop if goal position is reached
						}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.first = m_position.first + 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in SOUTH direction or not
			if (b.first - a.first == 0 && b.second - a.second == -1)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_right();
				turn_right();
                m_direction = (direction::SOUTH);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{

					API::clearAllColor();
					clear_stack_vector();
						if(!search_maze())
						{
							break;      // break loop if goal position is reached
						}
						move_to_goal();
						if ( m_position == g_position )
						{
							break;      // break loop if goal position is reached
						}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.second = m_position.second - 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in WEST direction or not
			if (b.first - a.first == -1 && b.second - a.second == 0)
			{
				turn_left();
                m_direction = (direction::WEST);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{

					API::clearAllColor();		
					clear_stack_vector();		
						if(!search_maze())
						{
							break;      // break loop if goal position is reached
						}
						move_to_goal();
						if ( m_position == g_position )
						{
							break;      // break loop if goal position is reached
						}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.first = m_position.first - 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						update_wall();
						break;      // break loop if goal position is reached
					}
				}
			}

		}

        //check whether robot facing EAST or not
		if(m_direction == EAST)
		{
            // check whether the next position of robot is in NORTH direction or not
			if (b.first - a.first == 0 && b.second - a.second == 1)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_left();
                m_direction = (direction::NORTH);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;      // break loop if goal position is reached
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.second = m_position.second + 1 ;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						update_wall();
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in EAST direction or not
			if (b.first - a.first == 1 && b.second - a.second == 0)
			{
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method  to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;      // break loop if goal position is reached
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.first = m_position.first + 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in SOUTH direction or not
			if (b.first - a.first == 0 && b.second - a.second == -1)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_right();
                m_direction = (direction::SOUTH);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;      // break loop if goal position is reached
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.second = m_position.second - 1 ;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in WEST direction or not
			if (b.first - a.first == -1 && b.second - a.second == 0)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_right();
				turn_right();
                m_direction = (direction::WEST);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;      // break loop if goal position is reached
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.first = m_position.first - 1 ;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}

		}

        //check whether robot facing SOUTH or not
		if(m_direction == SOUTH)
		{
            // check whether the next position of robot is in NORTH direction or not
			if (b.first - a.first == 0 && b.second - a.second == 1)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_right();
				turn_right();
                m_direction = (direction::NORTH);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;      // break loop if goal position is reached
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.second = m_position.second + 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in EAST direction or not
			if (b.first - a.first == 1 && b.second - a.second == 0)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_left();
                m_direction = (direction::EAST);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;      // break loop if goal position is reached
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
				else
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.first = m_position.first + 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in SOUTH direction or not
			if (b.first - a.first == 0 && b.second - a.second == -1)
			{
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;      // break loop if goal position is reached
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.second = m_position.second - 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
			}
            // check whether the next position of robot is in WEST direction or not
			if (b.first - a.first == -1 && b.second - a.second == 0)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_right();
                m_direction = (direction::WEST);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;      // break loop if goal position is reached
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;      // break loop if goal position is reached
					}
				}
				else
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.first = m_position.first - 1 ;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						update_wall();
						break;      // break loop if goal position is reached
					}
				}
			}

		}

        //check whether robot facing WEST or not
		if(m_direction == WEST)
		{
            // check whether the next position of robot is in NORTH direction or not
			if (b.first - a.first == 0 && b.second - a.second == 1)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
			    turn_right();
                m_direction = (direction::NORTH);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;
					}
				}
				else
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.second = m_position.second + 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;
					}
				}
			}
            // check whether the next position of robot is in EAST direction or not
			if (b.first - a.first == 1 && b.second - a.second == 0)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_right();
				turn_right();
                m_direction = (direction::EAST);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;
					}
				}
				else
				{ 
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.first = m_position.first + 1;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;
					}
				}
			}
            // check whether the next position of robot is in SOUTH direction or not
			if (b.first - a.first == 0 && b.second - a.second == -1)
			{   
                // rotate the robot to orient in the direction of movement and update current direction
				turn_left();
                m_direction = (direction::SOUTH);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method  to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;
					}
				}
				else
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.second = m_position.second - 1 ;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						break;
					}
				}
			}
            // check whether the next position of robot is in WEST direction or not
			if (b.first - a.first == -1 && b.second - a.second == 0)
			{
                m_direction = (direction::WEST);
                // If robot encounter wall in its movement direction
                // call clear_stack_vector method to empty the stack and list
                // call search_maze method to find new path
                // call move_to_goal method to move robot in the new path
				if (API::wallFront())
				{
					API::clearAllColor();
					clear_stack_vector();
					if(!search_maze())
					{
						break;
					}
					move_to_goal();
					if ( m_position == g_position )
					{
						break;
					}
				}
				else 
				{
                    // if no wall in robot's movement direction
                    // move robot 1 unit forward in the current path
                    // update current position, current direction
                    // call update_wall method to update wall for maze and simulator
                    // call move_to_goal method to execute next robot movement
					move_forward();
					API::clearColor(m_position.first,m_position.second);
                    m_position.first = m_position.first - 1 ;
                    update_wall();
					move_to_goal();
					if ( m_position == g_position )
					{
						update_wall();
						break;
					}
				}
			}
		}

	}
	
}
