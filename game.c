#include "common.h"
#include "gameobjs.h"
#include "game_state.h"

#include "textbox.h"
#include "uwugirl.h"

#include <SDL2/SDL_ttf.h>

int main(void) {
	Game game;
	Uint32 render_flags;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	if (!(game.win = SDL_CreateWindow(GAMENAME,
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					WINW, WINH, 0))) {
		printf("error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	render_flags = SDL_RENDERER_ACCELERATED;
	if (!(game.renderer = SDL_CreateRenderer(game.win, -1, render_flags))) {
		printf("error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(game.win);
		SDL_Quit();
		return 1;
	}

	TTF_Init();

	initializeGame(&game);

	GameObject* demon_girl;
	GameObject* main_tb; // main textbox

	if (!(demon_girl = makeAndAdd(
					&game, 0, 0, &uwuGirlInitialize, &uwuGirlUpdate, TYPE_SPRITE, "resources/she.png"))) {
		CHECK_ERR(&game);
	}

	if (!(main_tb = makeAndAdd(
					&game, (demon_girl->rect.x + demon_girl->rect.w), ((WINH-100)/2),
					&textBoxInitialize, &textBoxUpdate, TYPE_TEXTBOX, NULL))) {
		CHECK_ERR(&game);
	}

	textBoxSetSize(main_tb, 100, 100);

	textBoxSetText(main_tb, &game, "hello! i am satan.");
	CHECK_ERR(&game);

	game.close_game = 0;
	while (!game.close_game) {
		gameUpdate(&game);
	}

	gameCleanup(&game);
}

