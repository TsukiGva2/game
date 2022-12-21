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
		if (!it->next) go->prev = it;

		it = it->next;
	}

	if (it->next) {
		setGameError(game, MAXOBJS_ERR);
		return NULL;
	}

	it->next = go;

	return go;
}

void delGameObject(Game* game, int id) {
	GameObject* it = game->gObjs_head;
	GameObject* prev;

	for (int i = 0; (it->next) && it->id != id; i++) {
		if (it->id == (id - 1)) {
			prev = it;
		}
		it = it->next;
	}

	if (!it) {
		setGameError(game, NOID_ERR);
		return;
	}

	GameObject* next = freeGameObject(it);
	
	if (next) next->prev = prev;
	prev->next = next;
}

void gameDestroy(Game* game) {
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->win);
	SDL_Quit();
}

void gameCleanup(Game* game) {
	freeGameObjects(game->gObjs_head);
}

void initializeGame(Game* game) {
	game->gObjs_head = (GameObject*)malloc(sizeof(GameObject));
	setGameError(game, ALLGOOD);
	if (!game->gObjs_head) {
		setGameError(game, ALLOC_ERR);
		return;
	}

	game->gObjs_head->next   = NULL;
	game->gObjs_head->update = NULL; // ALWAYS initialize please (this line not being here caused like 5 segfaults ffs)
	game->gObjs_head->prev   = NULL;
	game->gObjs_head->id     = 0;
	game->gObjs_head->type   = TYPE_HEAD;

	game->options.textspeed = 2;
}

void gameDraw(Game* game) {
	SDL_SetRenderDrawColor(game->renderer, 20, 19, 26, 255);
	SDL_RenderClear(game->renderer);

	drawGameObjects(game->gObjs_head, game);

	SDL_RenderPresent(game->renderer);
}

void gameUpdate(Game* game) {
	updateGameObjects(game->gObjs_head, game);
	if (getGameError(game)) return;

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

		if (game->event.type == SDL_MOUSEBUTTONDOWN || game->event.type == SDL_MOUSEBUTTONUP) {
			if (game->event.button.button == SDL_BUTTON_LEFT) {
				game->mouseheld = !game->mouseheld;
			}

			gameObjectsOnMouseEvent(game->gObjs_head, game);
		}
	}

	gameDraw(game);
}



