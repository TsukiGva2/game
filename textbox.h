#ifndef __TEXTBOX_H__GAME__
#define __TEXTBOX_H__GAME__

#include "common.h"
#include "game_state.h"
#include <SDL2/SDL_ttf.h>

void textBoxInitialize(void* vp_go, void* vp_game);
void textBoxUpdate(void* vp_go, void* vp_game);
void textBoxSetSize(void* vp_go, int w, int h);
void textBoxSetText(void* vp_go, void* vp_game, const char* str);
void textBoxSetColor(void* vp_go, SDL_Color color);
void textBoxReRender(void* vp_go, void* vp_game);

#endif
