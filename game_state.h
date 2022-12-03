#ifndef __GAME_STATE_H__GAME__
#define __GAME_STATE_H__GAME__
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
			if (err == NOID_ERR) {\
				printf("no object with the specified id\n");\
				gameCleanup(g);\
				return 1;\
			}\
		}\
	}while(0)

void setGameError(Game* game, GameError err);
GameError getGameError(Game* game);

void initializeGame(Game* game);

GameObject* addGameObject(Game* game, GameObject* go);
void delGameObject(Game* game, int id);

void gameDraw(Game* game);
void gameUpdate(Game* game);

void gameCleanup(Game* game);

#endif

