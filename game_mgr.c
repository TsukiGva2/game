#include "game_mgr.h"

static void incTextSpeedCallback(Game* game) {
	game->options.textspeed += 1;
}
static void decTextSpeedCallback(Game* game) {
	if (game->options.textspeed > 0) game->options.textspeed -= 1;
}

GameMgr* gameMgrGetManager(GameObject* gm) {
	return (GameMgr*)gm->extension;
}

void gameMgrInitialize(void* vp_go, void* vp_game) { // TODO
	GameObject* go = (GameObject*)vp_go;
	GameMgr* gamemgr = malloc(sizeof(GameMgr));

	if (!gamemgr) {
		setGameError((Game*)vp_game, ALLOC_ERR);
		return;
	}

	gamemgr->textspeed_inc.callback = &incTextSpeedCallback;
	gamemgr->textspeed_dec.callback = &decTextSpeedCallback;

	gamemgr->textspeed_inc.button = NULL;
	gamemgr->textspeed_dec.button = NULL;

	go->extension = (void*)gamemgr;
}

void gameMgrUpdate(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	GameMgr* gamemgr = (GameMgr*)go->extension;

	GameProperty speedinc = gamemgr->textspeed_inc;
	GameProperty speeddec = gamemgr->textspeed_dec;

	if (buttonIsClicked(speedinc.button)) {
		speedinc.callback((Game*)vp_game);
	}

	if (buttonIsClicked(speeddec.button)) {
		speeddec.callback((Game*)vp_game);
	}
}

void gameMgrAttachButtonToProperty(GameProperty* gp, GameObject* button) {
	gp->button = button;
}

