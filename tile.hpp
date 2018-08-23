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
	SDL_Rect srcrect = tile.type->sprite->rect;
	dstrect.x = x * 48;
	dstrect.y = y * 48;
	return SDL_RenderCopy(globalRenderer, tile.type->sprite->sheet->texture, &tile.type->sprite->rect, &dstrect);
}