#include "common.h"
#include "uwugirl.h"
#include <math.h>

// code for the demon girl

typedef struct SpriteSheet {
	int showw;
	int showx;
} SpriteSheet;

void uwuGirlInitialize(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	SpriteSheet* sprite = (SpriteSheet*)malloc(sizeof(SpriteSheet));

	go->extension = (void*)sprite;

	sprite->showw = 256; // img is 256x256
	sprite->showx = 0;

	go->partrect.w = sprite->showw;
	go->partrect.x = sprite->showx;
	go->partrect.h = sprite->showw; // assume sprite is a square
	go->partrect.y = 0;

	go->rect.w = sprite->showw;

	int vmiddle = ((WINH-(go->rect.h))/2);
	go->initialy = vmiddle;
}

void uwuGirlSetSprite(void* vp_go, int index) {
	GameObject* go = (GameObject*)vp_go;
	SpriteSheet* sprite = (SpriteSheet*)go->extension;

	int i = index % 8;


}

void uwuGirlUpdate(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;	

	double ypos = go->initialy + sin((double)SDL_GetTicks() * 0.005) * 10;
	go->rect.y = (int)ypos;
}

