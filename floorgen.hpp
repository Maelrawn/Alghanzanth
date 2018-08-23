void generateFeatures(Floor& floor, TileType* types[2]){
	for(int i = 0; i <= 80; i++){
		for(int j = 0; j <= 80; j++){
			switch(rand()%2){
				case 0:
					floor.map[i][j] = Tile(i, j, types[0]);
				break;
				case 1:
					floor.map[i][j] = Tile(i, j, types[1]);
				break;
			}
		}
	}
}