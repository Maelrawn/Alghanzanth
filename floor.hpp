

struct Floor{
	int x = 80;
	int y = 80;
	Tile map[81][81];
	std::string name;	
	Floor(std::string name){
		this->name = name;
	};
	// void fillFloor(){
	// 	for(int i = 0; i <= this->x; i++){
	// 		for(int j = 0; j <= this->y; j++){
	// 			map[i][j] = 
	// 		}
	// 	}
	// }
};

void displayFeatures(Floor& floor){
	SDL_RenderClear(globalRenderer);
	for(int i = 0; i < 80; i++){
		for(int j = 0; j < 80; j++){
			drawGraphicAtCoords(camera, floor.map[i][j], i, j);
				//printf("SDL Error in drawing routine: %s\n", SDL_GetError());
		}
	}
	SDL_RenderPresent(globalRenderer);
}

#include "floorgen.hpp"
