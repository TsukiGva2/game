#ifndef __GAMEOBJS_H__GAME__
#define __GAMEOBJS_H__GAME__
#include "common.h"

#define CHECK_ERR(g) do{GameError err = getGameError(g);\
		if (err) {\
			if (err == ALLOC_ERR) {\
				printf("Error allocating memory\n");\
				return 1;\
			}\
			if (err == MAXOBJS_ERR) {\
				printf("you are dumb and made more objs than the max: %d\n", MAX_OBJS);\
				gameCleanup(g);\
				return 1;\
			}\
			if (err == SDL_ERR) {\
				printf("sdl says: '%s'\n", SDL_GetError());\
				gameCleanup(g);\
				return 1;\
			}\
		}\
	}while(0)

GameObject* addGameObject(Game* game, GameObject* go);
GameObject* makeGameObject(Game* game,
		int x, int y,
		GameFn init,
		GameFn update,
		ObjType type,
		const char* image);
GameObject* makeAndAdd(Game* game,
		int x, int y,
		GameFn init,
		GameFn update,
		ObjType type,
		const char* image);

void freeGameObjects(GameObject* go);
void drawGameObjects(GameObject* go, Game* game);
void updateGameObjects(GameObject* go, Game* game);

#endif
