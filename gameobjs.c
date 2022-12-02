#include "common.h"
#include "gameobjs.h"
#include "game_state.h"

void freeGameObjects(GameObject* go) {
	if (!go) return;

	if (go->type == TYPE_HEAD) {
		freeGameObjects(go->next);
		free(go);
		return;
	}

	GameObject* next = go->next;

	if (go->tex) SDL_DestroyTexture(go->tex);
	if (go->extension) {
		if (go->cleanup) go->cleanup(go, NULL);
		free(go->extension);
	}

	free(go);

	freeGameObjects(next);
}

GameObject* makeAndAdd(Game* game,
		int x, int y,
		GameFn init,
		GameFn update,
		ObjType type,
		const char* image) {
	GameObject* go;

	if (!(go = makeGameObject(game, x, y, init, update, type, image))) return NULL;
	return addGameObject(game, go);
}

GameObject* makeGameObject(Game* game,
		int x, int y,
		GameFn init,
		GameFn update,
		ObjType type,
		const char* image) {
	GameObject* go = (GameObject*)malloc(sizeof(GameObject));
	if (!go) {
		setGameError(game, ALLOC_ERR);
		return NULL;
	}

	go->extension = NULL;
	go->cleanup = NULL;
	go->tex = NULL;

	if (!image) goto skipimg;

	setGameError(game, SDL_ERR); // if function returns on any of these then sdl err

	SDL_Surface* sfc = IMG_Load(image);
	if (!sfc) return NULL;

	go->tex = SDL_CreateTextureFromSurface(game->renderer, sfc);
	SDL_FreeSurface(sfc);
	if (!go->tex) return NULL;

	SDL_QueryTexture(go->tex, NULL, NULL, &go->rect.w, &go->rect.h);

	setGameError(game, ALLGOOD);

skipimg:
	go->rect.x = x;
	go->rect.y = y;

	static ID_UINT id = 1;
	go->id = id++;

	go->update = update;
	go->type = type;

	go->next = NULL;

	init(go, game);

	return go;
}

void drawGameObjects(GameObject* go, Game* game) {
	if (!go) return;

	if (go->type == TYPE_HEAD) {
		drawGameObjects(go->next, game);
		return;
	}

	if (go->tex) SDL_RenderCopy(game->renderer, go->tex, NULL, &(go->rect));
	//if (go->type == TYPE_TEXTBOX) SDL_RenderDrawRect(game->renderer, &(go->rect));

	drawGameObjects(go->next, game);
}

void updateGameObjects(GameObject* go, Game* game) {
	if (!go) return;

	if (!(go->update) || go->type == TYPE_HEAD) {
		updateGameObjects(go->next, game);
		return;
	}

	go->update(go, game);

	updateGameObjects(go->next, game);
}
