bool drawGraphicAtCoords(Camera camera, Sprite* graphic, int x, int y){
	SDL_Rect srcrect = graphic->rect;
	dstrect.x = (x - camera.x) * 48;
	dstrect.y = (y - camera.y) * 48;
	return SDL_RenderCopy(gameRenderer, graphic->sheet->texture, &srcrect, &dstrect);
};
bool drawGraphicAtCoords(Camera camera, Tile tile, int x, int y){
	SDL_Rect srcrect = tile.type->sprite->rect;
	dstrect.x = (x - camera.x) * 48;
	dstrect.y = (y - camera.y) * 48;
	return SDL_RenderCopy(gameRenderer, tile.type->sprite->sheet->texture, &tile.type->sprite->rect, &dstrect);
};
// bool drawGraphicAtCoords(SpriteSetCreature* graphic, int x, int y){
// 	SDL_Rect srcrect = graphic->activeFrame->rect;
// 	dstrect.x = x;
// 	dstrect.y = y;
// 	return SDL_RenderCopy(gameRenderer, graphic->activeFrame->sheet->texture, &srcrect, &dstrect);
// }
bool initSDL(){
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	gameWindow = SDL_CreateWindow("Alghanzanth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gameWindow == NULL){
		printf("SDL could not be initialized! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gameRenderer == NULL){
		printf("Global renderer could not initialize! SDL error: %s/n", SDL_GetError());
		success = false;
	}
	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0x00);
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) && imgFlags)){
		printf("SDL_Image could not initialize! SDL_Image error: %s\n", IMG_GetError());
		success = false;
	}
	gameSurface = SDL_GetWindowSurface(gameWindow);
	dstrect.w = 48;
	dstrect.h = 48;
	return success;
};
void displayFeatures(Floor& floor){
	SDL_RenderClear(gameRenderer);
	for(int i = 0; i < 80; i++){
		for(int j = 0; j < 80; j++){
			drawGraphicAtCoords(camera, floor.map[i][j], i, j);
				//printf("SDL Error in drawing routine: %s\n", SDL_GetError());
		}
	}
	for(int i = 0 - camera.width; i < floor.x + camera.width; i++){
		for(int j = 0 - camera.height; j < floor.y + camera.height; j++){
			if(!floor.inBounds(i, j))
				drawGraphicAtCoords(camera, wallSprite, i, j);
		}
	}
	SDL_RenderPresent(gameRenderer);
};
void close(){
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = NULL;
	SDL_FreeSurface(gameSurface);
	gameSurface = NULL;
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
	SDL_Quit();
};