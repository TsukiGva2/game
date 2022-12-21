#include "game.h"

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
	
	MAKE_OBJ(demon_girl, 0, 0, uwuGirlInitialize, uwuGirlUpdate, TYPE_SPRITE, "resources/demonsheet.png");
	MAKE_OBJ(main_tb,
			(demon_girl->rect.x + demon_girl->partrect.w), ((WINH-100)/2),
			textBoxInitialize, textBoxUpdate, TYPE_TEXTBOX, NULL);

	textBoxSetSize(main_tb, 100, 100);
	textBoxSetText(main_tb, &game, "hello! i am satan.");
	CHECK_ERR(&game);

	uwuGirlAttachTextBox(demon_girl, main_tb);

	int demon_girl_right = (demon_girl->rect.x + demon_girl->partrect.w);
	int vmiddle = ((WINH-100)/2);

	// roguelike
	GameObject* up;
	GameObject* down;
	GameObject* left;
	GameObject* right;
	GameObject* attack;
	/* draw:
	 *    ^
	 *   < >   ATTACK
	 *    v
	 */

	MAKE_BUTTON(up, demon_girl_right+50, vmiddle+30, "^");
	MAKE_BUTTON(down, demon_girl_right+50, vmiddle+70, "v");
	MAKE_BUTTON(left, demon_girl_right+30, vmiddle+50, "<");
	MAKE_BUTTON(right, demon_girl_right+70, vmiddle+50, ">");
	MAKE_BUTTON(attack, demon_girl_right+100, vmiddle+50, "ATTACK");

	GameObject* roguelike;
	MAKE_OBJ(roguelike,
		demon_girl_right+100, vmiddle+30,
		roguelikeInitialize, roguelikeUpdate,
		TYPE_ROGUELIKE, "resources/knight.png");

	roguelikeAttachButtons(roguelike, up, down, left, right, attack);
	roguelikeAttachMaster(roguelike, demon_girl, uwuGirlGetRoguelikeCallback(demon_girl));
	// end roguelike


	// game manager
	GameObject* gamemgr;
	GameObject* speedincbutton;
	GameObject* speeddecbutton;
	
	GameObject* info_text;
	MAKE_OBJ(info_text, 10, 10, textBoxInitialize, textBoxUpdate, TYPE_TEXTBOX, NULL);
	
	textBoxSetText(info_text, &game, "TEXT SPEED:");
	CHECK_ERR(&game);

	MAKE_OBJ(gamemgr, 0, 0, gameMgrInitialize, gameMgrUpdate, TYPE_MANAGER, NULL);

	// button 1
	MAKE_BUTTON(speedincbutton, 45, 30, ">");
	gameMgrAttachButtonToProperty( &gameMgrGetManager(gamemgr)->textspeed_inc,  speedincbutton);

	// button 2
	MAKE_BUTTON(speeddecbutton, 20, 30, "<");
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
	gameDestroy(&game);
}

