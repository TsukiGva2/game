#ifndef __MAP_H__GAME_
#define __MAP_H__GAME_

#include "common.h"

void mapInitialize(void* vp_go, void* vp_game);
void mapUpdate(void* vp_go, void* vp_game);
void mapAttachButtons(GameObject* go,
		GameObject* left, GameObject* right,
		GameObject* up, GameObject* down);

#endif

