#ifndef __BUTTON_H__GAME_
#define __BUTTON_H__GAME_

#include "common.h"
#include "textbox.h"
#include "game_state.h"

void buttonUpdate(void* vp_go, void* vp_game);
void buttonInitialize(void* vp_go, void* vp_game);
void buttonCleanup(void* vp_go, void* vp_game);
void buttonAttachTextBox(void* vp_go, GameObject* tb);

#endif

