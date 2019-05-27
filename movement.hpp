struct Direction{
	int dx;
	int dy;
	Direction(int dx, int dy)
		:dx(dx),
		dy(dy),
	{};
};
Direction North = Direction(0, -1);
Direction Northeast = Direction(1, -1);
Direction East = Direction(1, 0);
Direction Southeast = Direction(1, 1);
Direction South = Direction(0, 1);
Direction Southwest = Direction(-1, 1);
Direction West = Direction(-1, 0);
Direction Northwest = Direction(-1, -1);

bool moveEntity(Entity entity, Direction direction, Floor floor){
	if(entity.x + direction.dx >= 0 && entity.x + direction.dx < 81 && entity.y + direction.dy >= 0 && entity.y + direction.dy < 81){
		Tile endPosition = floor.map[entity.x + direction.dx][entity.y + direction.dy];
		if(!endPosition.collision){
			entity.x = endPosition.x;
			entity.y = endPosition.y;
			return true;
		}
	}
	return false;
};