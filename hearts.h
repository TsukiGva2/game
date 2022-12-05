#ifndef __HEARTS_H__GAME__
#define __HEARTS_H__GAME__

#include "common.h"
#include "game_state.h"

#define BLACK_HEART_RES "resources/blackheart.png"
#define RED_HEART_RES "resources/redheart.png"

// 4 hearts by default no fucking customization on that because i = lazy
#define HEARTS 4
#define HEART_SIZE 64
#define DRAW_START (WINW-((HEARTS+1)*HEART_SIZE))

void heartsInitialize(void* vp_go, void* vp_game);
void heartsUpdate(void* vp_go, void* vp_game);
void heartsDraw(void* vp_go, void* vp_game);
void heartsCleanup(void* vp_go, void* vp_game);

void heartsSetLife(GameObject* go, uint8_t life);

#endif

