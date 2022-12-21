#ifndef __GAME_H__GAME__
#define __GAME_H__GAME__

#include "common.h"

// essentials
#include "gameobjs.h"
#include "game_state.h"
#include "game_mgr.h" // not so essential but it has game on its name so it kinda belongs here

// extensions
#include "roguelike.h"
#include "textbox.h"
#include "uwugirl.h"
#include "button.h"
#include "hearts.h"

#include <SDL2/SDL_ttf.h>

#define MAKE_OBJ(objname, x, y, initfn, updatefn, ty, res) do{\
	if (!(objname = makeAndAdd(&game, x, y, &initfn, &updatefn, ty, res))) {\
		CHECK_ERR(&game);\
	}}while(0)

#define MAKE_BUTTON(bt, x, y, text) do{\
	GameObject* bt##_text;\
	MAKE_OBJ(bt, 0, 0, buttonInitialize, buttonUpdate, TYPE_BUTTON, NULL);\
	MAKE_OBJ(bt##_text, x, y, textBoxInitialize, textBoxUpdate, TYPE_TEXTBOX, NULL);\
	textBoxSetText(bt##_text, &game, text);\
	CHECK_ERR(&game);\
	buttonAttachTextBox(bt, bt##_text);\
	}while(0)

#endif

