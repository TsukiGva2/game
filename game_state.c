#include "common.h"
#include "game_state.h"
#include "gameobjs.h"
#include "textbox.h"

void setGameError(Game* game, GameError err) {
	game->err = err;
}

GameError getGameError(Game* game) {
	return game->err;
}

GameObject* addGameObject(Game* game, GameObject* go) {
	GameObject* it = game->gObjs_head;
	for (int i = 0; (it->next) && i < MAX_OBJS; i++) {
		it = it->next;
	}

	if (it->next) {
		setGameError(game, MAXOBJS_ERR);
		return NULL;
	}

	it->next = go;

	return go;
}

void gameCleanup(Game* game) {
	freeGameObjects(game->gObjs_head);

	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->win);
	SDL_Quit();
}

void initializeGame(Game* game) {
	game->gObjs_head = (GameObject*)malloc(sizeof(GameObject));
	setGameError(game, ALLGOOD);
	if (!game->gObjs_head) {
		setGameError(game, ALLOC_ERR);
		return;
	}

	game->gObjs_head->next = NULL;
	game->gObjs_head->update = NULL; // ALWAYS initialize please (this line not being here caused like 5 segfaults ffs)
	game->gObjs_head->type = TYPE_HEAD;
	game->gObjs_head->id   = 0;
}

void gameDraw(Game* game) {
	SDL_SetRenderDrawColor(game->renderer, 20, 19, 26, 255);
	SDL_RenderClear(game->renderer);

	drawGameObjects(game->gObjs_head, game);

	SDL_RenderPresent(game->renderer);
}

void gameUpdate(Game* game) {
	updateGameObjects(game->gObjs_head, game);

	while (SDL_PollEvent( &(game->event) )) {
		if (game->event.type == SDL_QUIT) {
			game->close_game = 1;
			return;
		}

		if (game->event.type == SDL_KEYDOWN) {
			switch (game->event.key.keysym.scancode) {
				case SDL_SCANCODE_Q:
					game->close_game = 1;
					return;
				default:
					break;
			}
		}
	}

	gameDraw(game);

	SDL_Delay(1000/60);
}



