#ifndef __BUTTON_H__GAME_
#define __BUTTON_H__GAME_

#include "common.h"
#include "textbox.h"
#include "game_state.h"

typedef enum {
	STATE_HOVERED = 1<<0,
	STATE_NORMAL = 1<<1,
	STATE_CLICKED = 1<<2,
	STATE_HOLDING = 1<<3
} ButtonState;

typedef struct Button {
	ButtonState state;
	GameObject* textbox;
	SDL_Rect rect;
} Button;

void buttonUpdate(void* vp_go, void* vp_game);
void buttonInitialize(void* vp_go, void* vp_game);
void buttonCleanup(void* vp_go, void* vp_game);
void buttonAttachTextBox(void* vp_go, GameObject* tb);
bool buttonIsClicked(void* vp_go);

#endif

