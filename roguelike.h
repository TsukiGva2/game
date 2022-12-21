#ifndef __ROGUELIKE_H__GAME__
#define __ROGUELIKE_H__GAME__

#include "common.h"
#include <time.h>

#include "button.h"

typedef enum {
	EVENT_WALL,
	EVENT_OUT_OF_BOUNDS,
	EVENT_DIE,
	EVENT_KILL,
	EVENT_FINE
} RoguelikeEvent;

typedef void (*RoguelikeCallback)(GameObject* master, GameObject* roguelike, RoguelikeEvent e);

void roguelikeInitialize(void* vp_go, void* vp_game);
void roguelikeUpdate(void* vp_go, void* vp_game);

void roguelikeAttachButtons(GameObject* go, GameObject* up,
			    GameObject* down, GameObject* left,
			    GameObject* right, GameObject* attack);
void roguelikeAttachMaster(GameObject* go, GameObject* master, RoguelikeCallback callback);

#endif
