bool drawGraphicAtCoords(Sprite* graphic, int x, int y){
	SDL_Rect srcrect = graphic->rect;
	SDL_Rect dstrect;
	dstrect.x = x * 48;
	dstrect.y = y * 48;
	return SDL_RenderCopy(globalRenderer, graphic->sheet->texture, &srcrect, &dstrect);
}
// bool drawGraphicAtCoords(SpriteSetCreature* graphic, int x, int y){
// 	SDL_Rect srcrect = graphic->activeFrame->rect;
// 	dstrect.x = x;
// 	dstrect.y = y;
// 	return SDL_RenderCopy(globalRenderer, graphic->activeFrame->sheet->texture, &srcrect, &dstrect);
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
	globalRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	if(globalRenderer == NULL){
		printf("Global renderer could not initialize! SDL error: %s/n", SDL_GetError());
		success = false;
	}
	SDL_SetRenderDrawColor(globalRenderer, 0x00, 0x00, 0x00, 0x00);
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) && imgFlags)){
		printf("SDL_Image could not initialize! SDL_Image error: %s\n", IMG_GetError());
		success = false;
	}
	gameSurface = SDL_GetWindowSurface(gameWindow);
	dstrect.w = 48;
	dstrect.h = 48;
	return success;
}

void close(){
	SDL_DestroyRenderer(globalRenderer);
	globalRenderer = NULL;
	SDL_FreeSurface(gameSurface);
	gameSurface = NULL;
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
	SDL_Quit();
}