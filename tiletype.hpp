struct TileType{
	//int framecounter = 0;
	Sprite* sprite;
	bool collision = NULL;
	bool opaque = NULL;

	TileType(Sprite* sprite, bool collision, bool opacity)
		:sprite(sprite),
		opaque(opacity),
		collision(collision)
	{};
};
