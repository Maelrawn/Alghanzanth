struct Entity{
	int x;
	int y;
	GraphicSetCreature* graphics = NULL;
	Entity(){};
	Entity(int x, int y, GraphicSetCreature* graphic)
		:x(x),
		y(y),
		graphics(graphic)
	{};
};