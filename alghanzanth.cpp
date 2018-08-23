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
	SpriteSheet* creaturesFrame1 = new SpriteSheet("./resources/monsframe1.png");
	SpriteSheet* creaturesFrame2 = new SpriteSheet("./resources/monsframe2.png");
	SpriteSheet* portraits = new SpriteSheet("./resources/portraits.png");
	SpriteSheet* items = new SpriteSheet("./resources/items.png");
	SpriteSheet* tiles = new SpriteSheet("./resources/world.png");

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
	displayFeatures(floor);
	SDL_UpdateWindowSurface(gameWindow);
	SDL_Delay(500);
}