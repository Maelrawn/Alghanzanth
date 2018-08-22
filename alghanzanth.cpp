#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
#include "render.hpp"
#include "item.hpp"
#include "dungeon.hpp"
#include "entity.hpp"

int main(){
	srand(time(NULL));
	if(!initSDL()){
		printf("SDL has encountered an error and must close. SDL Error: %s\n", SDL_GetError());
		return -1;
	}
	grassGraphic->loadTexture();
	wallGraphic->loadTexture();
	Floor floor = Floor("default");
	generateFeatures(floor);
	displayFeatures(floor);
	SDL_UpdateWindowSurface(gameWindow);
	SDL_Delay(5000);
}