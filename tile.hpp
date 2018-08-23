#include "tiletype.hpp"

struct Tile{
	int x;
	int y;
	TileType* type;
	Tile(){};
	Tile(int x, int y, TileType* type)
		:x(x),
		y(y),
		type(type)
	{};

	bool operator==(Tile& other){
		if(other.x != this->x || other.y != this->y || other.type != this->type)
			return false;
		return true;
	}

};
bool drawGraphicAtCoords(Tile tile, int x, int y){
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	initializeRects(srcrect, dstrect);
	dstrect.x = x;
	dstrect.y = y;
	srcrect.x = tile.type->graphic->x;
	srcrect.y = tile.type->graphic->y;
	return SDL_RenderCopy(globalRenderer, tile.type->graphic->texture, &srcrect, &dstrect);
}