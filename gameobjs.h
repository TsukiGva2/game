#ifndef __GAMEOBJS_H__GAME__
#define __GAMEOBJS_H__GAME__
#include "common.h"

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

GameObject* freeGameObject(GameObject* go);
void freeGameObjects(GameObject* go);
void drawGameObjects(GameObject* go, Game* game);
void updateGameObjects(GameObject* go, Game* game);
void gameObjectsOnMouseEvent(GameObject* go, Game* game);

#endif
