#include "common.h"
#include "uwugirl.h"
#include <math.h>

// code for the demon girl

void uwuGirlInitialize(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;

	int vmiddle = ((WINH-(go->rect.h))/2);
	go->initialy = vmiddle;
}

void uwuGirlUpdate(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;	

	double ypos = go->initialy + sin((double)SDL_GetTicks() * 0.005) * 10;
	go->rect.y = (int)ypos;
}

