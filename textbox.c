#include "textbox.h"

typedef struct TextAnimator {
	int img_width;
	TTF_Font* fn;
	SDL_Color color;
	Uint64 timer;
	const char* str;
} TextAnimator;

void textBoxCleanup(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;

	TTF_CloseFont( ((TextAnimator*)go->extension)->fn );
}

void textBoxInitialize(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;

	go->cleanup = &textBoxCleanup;


	setGameError(game, ALLOC_ERR);

	TextAnimator* textanim = (TextAnimator*)malloc(sizeof(TextAnimator));
	if (!textanim) return;

	setGameError(game, ALLGOOD);


	setGameError(game, SDL_ERR);

	textanim->color = (SDL_Color){255,255,255}; // compound literals wtf
	textanim->str = NULL;

	textanim->fn = TTF_OpenFont(GAMEFON, GAMEFONSZ);
	if (!textanim->fn) return;

	setGameError(game, ALLGOOD);


	go->extension = (void*)textanim;
}

void textBoxUpdate(void* vp_go, void* vp_game) {
	Game* game = (Game*)vp_game;
	GameObject* go = (GameObject*)vp_go;
	TextAnimator* textanim = (TextAnimator*)go->extension;

	if (go->partrect.w >= textanim->img_width) {
		go->partrect.w = INT_MAX; // entire image
		return;
	}

	go->partrect.w += game->options.textspeed;
	go->rect.w = go->partrect.w;
}

void textBoxSetSize(void* vp_go, int w, int h) {
	GameObject* go = (GameObject*)vp_go;

	go->rect.w = w;
	go->rect.h = h;
}

void textBoxReRender(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;
	TextAnimator* textanim = (TextAnimator*)go->extension;

	setGameError(game, SDL_ERR);

	SDL_Surface* msg = TTF_RenderText_Solid(textanim->fn, textanim->str, textanim->color);
	if (!msg) return;

	go->tex = SDL_CreateTextureFromSurface(game->renderer, msg);
	if (!go->tex) return;

	setGameError(game, ALLGOOD);
}

void textBoxSetColor(void* vp_go, SDL_Color color) {
	GameObject* go = (GameObject*)vp_go;
	TextAnimator* textanim = (TextAnimator*)go->extension;

	textanim->color = color;
}

void textBoxSetText(void* vp_go, void* vp_game, const char* str) {
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;
	TextAnimator* textanim = (TextAnimator*)go->extension;

	textanim->str = str;

	setGameError(game, SDL_ERR);

	SDL_Surface* msg = TTF_RenderText_Solid(textanim->fn, str, textanim->color);
	if (!msg) return;

	go->tex = SDL_CreateTextureFromSurface(game->renderer, msg);
	if (!go->tex) return;

	setGameError(game, ALLGOOD);

	SDL_QueryTexture(go->tex, NULL, NULL, &go->rect.w, &go->rect.h);
	textanim->img_width = go->rect.w;

	go->partrect.w = 0;
	go->partrect.h = go->rect.h;

	go->partrect.x = 0;
	go->partrect.y = 0;
}

