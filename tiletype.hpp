struct TileType{
	//int framecounter = 0;
	Graphic* graphic;
	bool collision = NULL;
	bool opaque = NULL;

	TileType(Graphic* graphic, bool collision, bool opacity)
		:graphic(graphic),
		opaque(opacity),
		collision(collision)
	{};
	TileType& operator=(const TileType& other){
		this->graphic = other.graphic;
		this->graphic->texture = other.graphic->texture;
		this->opaque = other.opaque;
		this->collision = other.collision;
		return *this;
	}
	~TileType(){}
};
