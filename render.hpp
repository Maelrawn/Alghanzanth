#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Renderer* globalRenderer;
SDL_Window* gameWindow;
SDL_Surface* gameSurface;
SDL_Rect dstrect;
int SCREEN_HEIGHT = 720;
int SCREEN_WIDTH = 1280;

struct SpriteSheet{
	std::string imagePath = NULL;
	SDL_Texture* texture = NULL;
	SpriteSheet(std::string imagePath)
	:imagePath(imagePath){
		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(this->imagePath.c_str());
		if(loadedSurface == NULL){
			printf("Failed to load image! SDL_Image error: %s\n", IMG_GetError());
		}
		newTexture = SDL_CreateTextureFromSurface(globalRenderer, loadedSurface);
		if(newTexture == NULL){
			printf("Failed to create texture! SDL error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
		texture = newTexture;
	};
};

struct Sprite{
	int xindex;
	int yindex;
	SDL_Rect rect;
	SpriteSheet* sheet;
	Sprite(int x, int y, SpriteSheet* sheet)
	:xindex(x),
	yindex(y),
	sheet(sheet){
		rect.w = 48;
		rect.h = 48;
		rect.x = xindex * 48;
		rect.y = yindex * 48;
	};
};

#include "graphics.hpp"

enum class Creature;

// struct SpriteSetCreature{
// 	enum Frames{	
// 		Right1,
// 		Right2,
// 		Down1,
// 		Down2,
// 		Up1,
// 		Up2,
// 		Left1,
// 		Left2,
// 		FrameTotal
// 	};
// 	Sprite* sprites[FrameTotal];
// 	Sprite* activeFrame;
// 	SpriteSetCreature(int xindex, int yindex){
// 		sprites[Right1] = new Sprite(xindex, yindex, creaturesFrame1);
// 		sprites[Right2] = new Sprite(xindex, yindex, creaturesFrame2);
// 		sprites[Down1] = new Sprite(xindex + 1, yindex, creaturesFrame1);
// 		sprites[Down2] = new Sprite(xindex + 1, yindex, creaturesFrame2);
// 		sprites[Up1] = new Sprite(xindex + 2, yindex, creaturesFrame1);
// 		sprites[Up2] = new Sprite(xindex + 2, yindex, creaturesFrame2);
// 		sprites[Left1] = new Sprite(xindex + 3, yindex, creaturesFrame1);
// 		sprites[Left2] = new Sprite(xindex + 3, yindex, creaturesFrame2);
// 	}
// };

bool drawGraphicAtCoords(Sprite* graphic, int x, int y){
	SDL_Rect srcrect = graphic->rect;
	SDL_Rect dstrect;
	dstrect.x = x * 48;
	dstrect.y = y * 48;
	return SDL_RenderCopy(globalRenderer, graphic->sheet->texture, &srcrect, &dstrect);
}
// bool drawGraphicAtCoords(SpriteSetCreature* graphic, int x, int y){
// 	SDL_Rect srcrect = graphic->activeFrame->rect;
// 	dstrect.x = x;
// 	dstrect.y = y;
// 	return SDL_RenderCopy(globalRenderer, graphic->activeFrame->sheet->texture, &srcrect, &dstrect);
// }
bool initSDL(){
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	gameWindow = SDL_CreateWindow("Alghanzanth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gameWindow == NULL){
		printf("SDL could not be initialized! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	globalRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	if(globalRenderer == NULL){
		printf("Global renderer could not initialize! SDL error: %s/n", SDL_GetError());
		success = false;
	}
	SDL_SetRenderDrawColor(globalRenderer, 0x00, 0x00, 0x00, 0x00);
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) && imgFlags)){
		printf("SDL_Image could not initialize! SDL_Image error: %s\n", IMG_GetError());
		success = false;
	}
	gameSurface = SDL_GetWindowSurface(gameWindow);
	dstrect.w = 48;
	dstrect.h = 48;
	return success;
}