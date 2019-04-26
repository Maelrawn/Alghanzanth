#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
#include "render.hpp"
#include "item.hpp"
#include "dungeon.hpp"
#include "entity.hpp"

void generateFeatures(Floor& floor);

int main(){
	srand(time(NULL));
	if(!initSDL()){
		printf("SDL has encountered an error and must close. SDL Error: %s\n", SDL_GetError());
		return -1;
	}
	#include "graphics.hpp"
	Sprite* wallSprite = new Sprite(0, 0, tiles);
	Sprite* grassSprite = new Sprite(9, 5, tiles);
	TileType* wallType = new TileType(wallSprite, true, true);
	TileType* grassType = new TileType(grassSprite, false, false);
	Floor floor = Floor("default");
	for(int i = 0; i <= 80; i++){
		for(int j = 0; j <= 80; j++){
			switch(rand()%2){
				case 0:
					floor.map[i][j] = Tile(i, j, wallType);
				break;
				case 1:
					floor.map[i][j] = Tile(i, j, grassType);
				break;
			}
		}
	}			
	bool quit = false;
	SDL_Event event;
	while(!quit){
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT)
				quit = true;
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){		
					case SDLK_UP:
						if(camera.y > 0)
							camera.y -= 1;
						break;
					case SDLK_RIGHT:
						if(camera.x < 100)
							camera.x += 1;
						break;
					case SDLK_DOWN:
						if(camera.y < 100)
							camera.y += 1;
						break;
					case SDLK_LEFT:
						if(camera.x > 0)
							camera.x -= 1;
						break;
				}
			}
		}
	displayFeatures(floor);
	SDL_UpdateWindowSurface(gameWindow);
	}
}