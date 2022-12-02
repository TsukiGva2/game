#include "textbox.h"

typedef struct TextAnimator {
	double part;
	int img_width;
	TTF_Font* fn;
} TextAnimator;

void textBoxCleanup(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;

	TTF_CloseFont( ((TextAnimator*)go->extension)->fn );
}

void textBoxInitialize(void* vp_go, void* vp_game) { // TODO
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;

	go->cleanup = &textBoxCleanup;


	setGameError(game, ALLOC_ERR);

	TextAnimator* textanim = (TextAnimator*)malloc(sizeof(TextAnimator));
	if (!textanim) return;

	setGameError(game, ALLGOOD);


	setGameError(game, SDL_ERR);

	textanim->fn = TTF_OpenFont(GAMEFON, GAMEFONSZ);
	if (!textanim->fn) return;

	setGameError(game, ALLGOOD);


	go->extension = (void*)textanim;
}

void textBoxUpdate(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	TextAnimator* textanim = (TextAnimator*)go->extension;

	if ((int)textanim->part >= textanim->img_width) {
		return;
	}

	go->rect.w = textanim->part;

	textanim->part += 2;
}

void textBoxSetSize(void* vp_go, int w, int h) {
	GameObject* go = (GameObject*)vp_go;

	go->rect.w = w;
	go->rect.h = h;
}

void textBoxSetText(void* vp_go, void* vp_game, const char* str) {
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;
	TextAnimator* textanim = (TextAnimator*)go->extension;

	textanim->part = 10;

	SDL_Color white = {255,255,255};

	setGameError(game, SDL_ERR);

	SDL_Surface* msg = TTF_RenderText_Solid(textanim->fn, str, white);
	if (!msg) return;

	go->tex = SDL_CreateTextureFromSurface(game->renderer, msg);
	if (!go->tex) return;

	setGameError(game, ALLGOOD);

	SDL_QueryTexture(go->tex, NULL, NULL, &go->rect.w, &go->rect.h);
	textanim->img_width = go->rect.w;
}

