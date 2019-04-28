#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Renderer* globalRenderer;
SDL_Window* gameWindow;
SDL_Surface* gameSurface;
SDL_Rect dstrect;
int SCREEN_HEIGHT = 720;
int SCREEN_WIDTH = 1280;

struct Camera{
	int x = 0;
	int y = 0;
	int width = 27;
	int height = 15;
};

Camera camera;

struct SpriteSheet{
	std::string imagePath = NULL;
	SDL_Texture* texture = NULL;
	SpriteSheet(std::string imagePath)
	:imagePath(imagePath){
	};
	void initialize(){
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
	}
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


enum class Creature;

struct SpriteSetCreature{
	int frame = 0;
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
	Sprite* sprites[FrameTotal];
	Sprite* activeFrame;
	SpriteSetCreature(int xindex, int yindex, SpriteSheet* sheet1, SpriteSheet* sheet2){
		sprites[Right1] = new Sprite(xindex, yindex, sheet1);
		sprites[Right2] = new Sprite(xindex, yindex, sheet2);
		sprites[Down1] = new Sprite(xindex + 1, yindex, sheet1);
		sprites[Down2] = new Sprite(xindex + 1, yindex, sheet2);
		sprites[Up1] = new Sprite(xindex + 2, yindex, sheet1);
		sprites[Up2] = new Sprite(xindex + 2, yindex, sheet2);
		sprites[Left1] = new Sprite(xindex + 3, yindex, sheet1);
		sprites[Left2] = new Sprite(xindex + 3, yindex, sheet2);
	}
};

