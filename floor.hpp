struct Floor{
	int x = 80;
	int y = 80;
	Tile map[81][81];
	std::string name;	
	Floor(std::string name){
		this->name = name;
	};
	// void fillFloor(){
	// 	for(int i = 0; i <= this->x; i++){
	// 		for(int j = 0; j <= this->y; j++){
	// 			map[i][j] = 
	// 		}
	// 	}
	// }
	bool inBounds(int x, int y){
		return (x > 0 && x < this->x && y > 0 && y < this->y);
	};
};