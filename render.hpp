#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Renderer* globalRenderer;
SDL_Window* gameWindow;
SDL_Surface* gameSurface;
int SCREEN_HEIGHT = 720;
int SCREEN_WIDTH = 1280;

struct Graphic{
	int x;
	int y;
	SDL_Texture* texture = NULL;
	Graphic(int xIndex, int yIndex, SDL_Texture* texture)
	:texture(texture){
		x = xIndex * 48;
		y = yIndex * 48;
	};
};

SDL_Texture* loadTexture(std::string imagePath){
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
	if(loadedSurface == NULL){
		printf("Failed to load image! SDL_Image error: %s\n", IMG_GetError());
	}
	newTexture = SDL_CreateTextureFromSurface(globalRenderer, loadedSurface);
	if(newTexture == NULL){
		printf("Failed to create texture! SDL error: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);
	return newTexture;
};
bool loadMedia(SDL_Texture* texture, std::string imagePath){
	bool success = true;
	texture = loadTexture(imagePath);
	if(texture == NULL){
		printf("Texture failed to load! IMG_Error: %s\n", IMG_GetError());
	}
	return success;
}
#include "graphics.hpp"

enum class Creature;

struct GraphicSetCreature{
	enum Frames{	
		Right1,
		Right2,
		Down1,
		Down2,
		Up1,
		Up2,
		Left1,
		Left2,
		FrameTotal
	};
	Graphic* graphics[FrameTotal];
	Graphic* activeFrame;
	GraphicSetCreature(int xindex, int yindex){
		graphics[Right1] = new Graphic(xindex, yindex, creaturesFrame1);
		graphics[Right2] = new Graphic(xindex, yindex, creaturesFrame2);
		graphics[Down1] = new Graphic(xindex + 1, yindex, creaturesFrame1);
		graphics[Down2] = new Graphic(xindex + 1, yindex, creaturesFrame2);
		graphics[Up1] = new Graphic(xindex + 2, yindex, creaturesFrame1);
		graphics[Up2] = new Graphic(xindex + 2, yindex, creaturesFrame2);
		graphics[Left1] = new Graphic(xindex + 3, yindex, creaturesFrame1);
		graphics[Left2] = new Graphic(xindex + 3, yindex, creaturesFrame2);
	}
};

void initializeRects(SDL_Rect &srcrect, SDL_Rect &dstrect){
	srcrect.w = 48;
	srcrect.h = 48;
	dstrect.w = 48;
	dstrect.h = 48;
}
bool drawGraphicAtCoords(Graphic* graphic, int x, int y){
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	initializeRects(srcrect, dstrect);
	dstrect.x = x * 48;
	dstrect.y = y * 48;
	srcrect.x = graphic->x;
	srcrect.y = graphic->y;
	return SDL_RenderCopy(globalRenderer, graphic->texture, &srcrect, &dstrect);
}
bool drawGraphicAtCoords(GraphicSetCreature* graphic, int x, int y){
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	initializeRects(srcrect, dstrect);
	dstrect.x = x;
	dstrect.y = y;
	srcrect.x = graphic->activeFrame->x;
	srcrect.y = graphic->activeFrame->y;
	return SDL_RenderCopy(globalRenderer, graphic->activeFrame->texture, &srcrect, &dstrect);
}
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
	return success;
}