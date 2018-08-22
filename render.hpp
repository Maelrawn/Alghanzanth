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
	std::string imagePath = NULL;
	SDL_Texture* texture = NULL;
	Graphic(int xIndex, int yIndex, std::string imagePath)
	:imagePath(imagePath){
		x = xIndex * 48;
		y = yIndex * 48;
	};
	~Graphic(){
	}
	void operator=(const Graphic& other){
		this->x = other.x;
		this->y = other.y;
		this->imagePath = other.imagePath;
		texture = other.texture;
	}
	void loadTexture(){
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

#include "graphics.hpp"

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