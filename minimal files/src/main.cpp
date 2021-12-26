#include <iostream>
#include <array>
#include "../include/api/api.h"
#include "../include/mouse/mouse.h"
#include "../include/node/node.h"
#include <utility>
#include <stack>

void reach_goal (std::pair<int,int> , int, std::stack<std::pair<int,int>>);

int main() {
	rwa2::Mouse mouse;
	mouse.display_walls();
	std::pair <int,int> g;
	g = std::make_pair(7,7);
	std::pair <int,int> n;
	n = std::make_pair(mouse.get_mx(),mouse.get_my());
	mouse.search_maze(n);

	if(mouse.search_maze(n)){

	void reach_goal(n, mouse.get_direction(), mouse.r){
		while (!n = g){

			std::pair <int,int> a = mouse.r.top();
			r.pop();
			std::pair <int,int> b = mouse.r.top();

			mouse.update_wall(n.first, n.second, mouse.get_direction());

			if(mouse.get_direction() == NORTH){
				if (b.first - a.first == 0 && b.second - a.second == 1){
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx());
					mouse.set_my((mouse.get_my()) + 1);
					mouse.set_direction(NORTH);
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == 1 && b.second - a.second == 0){
					mouse.turn_left();
					mouse.set_direction(EAST);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx()+1);
					mouse.set_my(mouse.get_my());
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == 0 && b.second - a.second == -1){
					mouse.turn_left();
					mouse.turn_left();
					mouse.set_direction(SOUTH);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx());
					mouse.set_my(mouse.get_my()-1);
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == -1 && b.second - a.second == 0){
					mouse.turn_right();
					mouse.set_direction(WEST);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx()-1);
					mouse.set_my(mouse.get_my());
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}

			}

			if(mouse.get_direction() == EAST){
				if (b.first - a.first == 0 && b.second - a.second == 1){
					mouse.turn_left();
					mouse.set_direction(NORTH);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx());
					mouse.set_my((mouse.get_my()) + 1);
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == 1 && b.second - a.second == 0){
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx()+1);
					mouse.set_my(mouse.get_my());
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == 0 && b.second - a.second == -1){
					mouse.turn_right();
					mouse.set_direction(SOUTH);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx());
					mouse.set_my(mouse.get_my()-1);
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == -1 && b.second - a.second == 0){
					mouse.turn_left();
					mouse.turn_left();
					mouse.set_direction(WEST);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx()-1);
					mouse.set_my(mouse.get_my());
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}

			}

			if(mouse.get_direction() == SOUTH){
				if (b.first - a.first == 0 && b.second - a.second == 1){
					mouse.turn_left();
					mouse.turn_left();
					mouse.set_direction(NORTH);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx());
					mouse.set_my((mouse.get_my()) + 1);
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == 1 && b.second - a.second == 0){
					mouse.turn_left();
					mouse.set_direction(EAST);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx()+1);
					mouse.set_my(mouse.get_my());
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == 0 && b.second - a.second == -1){
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx());
					mouse.set_my(mouse.get_my()-1);
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == -1 && b.second - a.second == 0){
					mouse.turn_right();
					mouse.set_direction(WEST);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx()-1);
					mouse.set_my(mouse.get_my());
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}

			}

			if(mouse.get_direction() == WEST){
				if (b.first - a.first == 0 && b.second - a.second == 1){
					mouse.turn_right();
					mouse.set_direction(NORTH);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx());
					mouse.set_my((mouse.get_my()) + 1);
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == 1 && b.second - a.second == 0){
					mouse.turn_left();
					mouse.turn_left();
					mouse.set_direction(EAST);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx()+1);
					mouse.set_my(mouse.get_my());
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == 0 && b.second - a.second == -1){
					mouse.turn_left();
					mouse.set_direction(SOUTH);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx());
					mouse.set_my(mouse.get_my()-1);
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}
				if (b.first - a.first == -1 && b.second - a.second == 0){
					mouse.set_direction(WEST);
					if (API::wallFront()){
						mouse.search_maze(n);
						if(!mouse.search_maze(n)){
							break;
						};
						reach_goal(n, mouse.get_direction(), mouse.r);
						if ( n==g ){
							break;
						};
					else mouse.move_forward();
					};
					mouse.set_mx(mouse.get_mx()-1);
					mouse.set_my(mouse.get_my());
					n.first = mouse.get_mx();
					n.second = mouse.get_my();
					reach_goal(n, mouse.get_direction(), mouse.r);
					if ( n==g ){
						break;
					}
				}

			}




		}

	}
		

}
}
break
}

