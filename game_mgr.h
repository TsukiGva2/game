#ifndef __GAME_MGR_H__GAME_
#define __GAME_MGR_H__GAME_

#include "common.h"
#include "game_state.h"
#include "button.h"

typedef void (*SetPropertyCallback)(Game*);

typedef struct {
	void* value;
	GameObject* button;
	SetPropertyCallback callback;
} GameProperty;

typedef struct {
	GameProperty textspeed_inc;
	GameProperty textspeed_dec;
} GameMgr;

GameMgr* gameMgrGetManager(GameObject* gm);

void gameMgrInitialize(void* vp_go, void* vp_game);
void gameMgrUpdate(void* vp_go, void* vp_game);

void gameMgrAttachButtonToProperty(GameProperty* gp, GameObject* button);

#endif

