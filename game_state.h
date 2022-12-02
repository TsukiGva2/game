#ifndef __GAME_STATE_H__GAME__
#define __GAME_STATE_H__GAME__
#include "common.h"

void setGameError(Game* game, GameError err);
GameError getGameError(Game* game);

void initializeGame(Game* game);

void gameDraw(Game* game);
void gameUpdate(Game* game);

void gameCleanup(Game* game);

#endif

