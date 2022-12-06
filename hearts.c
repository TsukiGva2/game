#include "hearts.h"

typedef struct {
	SDL_Texture* redheart;
	SDL_Texture* blackheart;
} HeartTextures;

typedef struct {
	HeartTextures ht;
	uint8_t life;
} Hearts;

void heartsSetLife(GameObject* go, uint8_t life) {
	Hearts* hearts = (Hearts*)go->extension;

	hearts->life = life;
}

void heartsCleanup(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	HeartTextures ht = ((Hearts*)go->extension)->ht;

	SDL_DestroyTexture(ht.redheart);
	SDL_DestroyTexture(ht.blackheart);
}

void heartsInitialize(void* vp_go, void* vp_game) {
	Game* game = (Game*)vp_game;
	GameObject* go = (GameObject*)vp_go;

	Hearts* hearts = (Hearts*)malloc(sizeof(Hearts));
	if (!hearts) {
		setGameError(game, ALLOC_ERR);
		return;
	}

	hearts->life = HEARTS;

	setGameError(game, SDL_ERR);

	SDL_Surface* red = IMG_Load(RED_HEART_RES);
	SDL_Surface* black = IMG_Load(BLACK_HEART_RES);

	if (!(red && black)) {
		if (red) SDL_FreeSurface(red);
		if (black) SDL_FreeSurface(black);

		free(hearts);
		return;
	}

	hearts->ht.redheart = SDL_CreateTextureFromSurface(game->renderer, red);
	hearts->ht.blackheart = SDL_CreateTextureFromSurface(game->renderer, black);

	SDL_FreeSurface(red);
	SDL_FreeSurface(black);

	if (!(hearts->ht.redheart && hearts->ht.blackheart)) {
		free(hearts);
		return;
	}

	SDL_QueryTexture(hearts->ht.redheart, NULL, NULL, &go->rect.w, &go->rect.h);

	setGameError(game, ALLGOOD);

	go->cleanup = &heartsCleanup;
	go->draw = &heartsDraw;

	go->extension = (void*)hearts;

	go->partrect.w = HEART_SIZE;
	go->partrect.h = HEART_SIZE;
	go->rect.w = HEART_SIZE;
	go->rect.h = HEART_SIZE;
}

void heartsDraw(void* vp_go, void* vp_game) {
	Game* game = (Game*)vp_game;
	GameObject* go = (GameObject*)vp_go;
	Hearts* hearts = (Hearts*)go->extension;
	HeartTextures ht = hearts->ht;

	int initialx = go->rect.x;

	uint8_t redhearts = hearts->life;

	Uint8 colors = (Uint8)(fabs(sin((double)SDL_GetTicks()*0.001))*255);
	SDL_SetTextureColorMod(ht.redheart, 255, colors, colors);

	for (uint8_t i = 0; i < HEARTS; i++) {
		go->rect.x = DRAW_START + (i * HEART_SIZE);

		if (i > redhearts) {
			SDL_RenderCopy(game->renderer, ht.blackheart, NULL, &(go->rect));
		} else {
			SDL_RenderCopy(game->renderer, ht.redheart, NULL, &(go->rect));
		}
	}

	go->rect.x = initialx;
}

void heartsUpdate(void* vp_go, void* vp_game) {
	// TODO
}

