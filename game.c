#include "common.h"

#include "gameobjs.h"
#include "game_state.h"
#include "game_mgr.h"

#include "textbox.h"
#include "uwugirl.h"
#include "button.h"
#include "hearts.h"

#include <SDL2/SDL_ttf.h>

#define MAKE_OBJ(objname, x, y, initfn, updatefn, ty, res) do{if (!(objname = makeAndAdd(\
					&game, x, y, &initfn, &updatefn, ty, res))) {\
		CHECK_ERR(&game);\
	}}while(0)

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
	GameObject* button_tb;
	GameObject* button;
	
	MAKE_OBJ(demon_girl, 0, 0, uwuGirlInitialize, uwuGirlUpdate, TYPE_SPRITE, "resources/demonsheet.png");
	MAKE_OBJ(main_tb,
			(demon_girl->rect.x + demon_girl->partrect.w), ((WINH-100)/2),
			textBoxInitialize, textBoxUpdate, TYPE_TEXTBOX, NULL);

	textBoxSetSize(main_tb, 100, 100);
	textBoxSetText(main_tb, &game, "hello! i am satan.");
	CHECK_ERR(&game);

	MAKE_OBJ(button, 0, 0, buttonInitialize, buttonUpdate, TYPE_BUTTON, NULL);
	MAKE_OBJ(button_tb,
			(demon_girl->rect.x + demon_girl->partrect.w), ((WINH-100)/2)+30,
			textBoxInitialize, textBoxUpdate, TYPE_TEXTBOX, NULL);

	textBoxSetText(button_tb, &game, "button");
	CHECK_ERR(&game);

	buttonAttachTextBox(button, button_tb);

	uwuGirlAttachTextBox(demon_girl, main_tb);
	uwuGirlAttachButton(demon_girl, button);

	// game manager
	GameObject* gamemgr;
	GameObject* speedincbutton;
	GameObject* speeddecbutton;
	GameObject* speedincbutton_text;
	GameObject* speeddecbutton_text;
	
	GameObject* info_text;
	MAKE_OBJ(info_text, 10, 10, textBoxInitialize, textBoxUpdate, TYPE_TEXTBOX, NULL);
	
	textBoxSetText(info_text, &game, "TEXT SPEED:");
	CHECK_ERR(&game);

	MAKE_OBJ(gamemgr, 0, 0, gameMgrInitialize, gameMgrUpdate, TYPE_MANAGER, NULL);

	// button 1
	MAKE_OBJ(speedincbutton, 0, 0, buttonInitialize, buttonUpdate, TYPE_BUTTON, NULL);
	MAKE_OBJ(speedincbutton_text, 45, 30, textBoxInitialize, textBoxUpdate, TYPE_TEXTBOX, NULL);

	textBoxSetText(speedincbutton_text, &game, ">");
	CHECK_ERR(&game);

	buttonAttachTextBox(speedincbutton, speedincbutton_text);
	gameMgrAttachButtonToProperty( &gameMgrGetManager(gamemgr)->textspeed_inc,  speedincbutton);

	// button 2
	MAKE_OBJ(speeddecbutton, 0, 0, buttonInitialize, buttonUpdate, TYPE_BUTTON, NULL);
	MAKE_OBJ(speeddecbutton_text, 20, 30, textBoxInitialize, textBoxUpdate, TYPE_TEXTBOX, NULL);

	textBoxSetText(speeddecbutton_text, &game, "<");
	CHECK_ERR(&game);

	buttonAttachTextBox(speeddecbutton, speeddecbutton_text);
	gameMgrAttachButtonToProperty( &gameMgrGetManager(gamemgr)->textspeed_dec,  speeddecbutton);
	// end game manager

	GameObject* hearts;
	MAKE_OBJ(hearts, 0, 0, heartsInitialize, heartsUpdate, TYPE_SPRITE, NULL);

	game.close_game = 0;
	while (!game.close_game) {
		Uint64 starttime = SDL_GetTicks64();

		gameUpdate(&game);
		CHECK_ERR(&game);

		Uint64 elapsed = SDL_GetTicks64() - starttime;

		if (elapsed < 1000) SDL_Delay((1000-elapsed)/60);
	}

	gameCleanup(&game);
}

