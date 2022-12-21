#ifndef __UWUGIRL_H__GAME__
#define __UWUGIRL_H__GAME__
#include <math.h>
#include "common.h"
#include "textbox.h"
#include "button.h"
#include "roguelike.h"

void uwuGirlUpdate(void* vp_go, void* vp_game);
void uwuGirlInitialize(void* vp_go, void* vp_game);
void uwuGirlSetSprite(void* vp_go, int index);
void uwuGirlAttachTextBox(void* vp_go, GameObject* tb);
void uwuGirlAttachButton(void* vp_go, GameObject* button);

RoguelikeCallback uwuGirlGetRoguelikeCallback(GameObject* go);

#endif

