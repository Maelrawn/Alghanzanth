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