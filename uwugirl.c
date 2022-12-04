#include "uwugirl.h"

// code for the demon girl

typedef struct SpriteSheet {
	int showw;
	int showx;
} SpriteSheet;

typedef struct DemonGirl {
	SpriteSheet sprite;
	GameObject* textbox;
	GameObject* button;
} DemonGirl;

void uwuGirlInitialize(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	DemonGirl* self = (DemonGirl*)malloc(sizeof(DemonGirl)); // TODO: handle this pls
	SpriteSheet sprite = self->sprite;

	go->extension = (void*)self;

	sprite.showw = 256; // img is 256x256
	sprite.showx = 0;

	self->textbox = NULL;
	self->button  = NULL;

	go->partrect.w = sprite.showw;
	go->partrect.x = sprite.showx;
	go->partrect.h = sprite.showw; // assume sprite is a square
	go->partrect.y = 0;

	go->rect.w = sprite.showw;

	int vmiddle = ((WINH-(go->rect.h))/2);
	go->initialy = vmiddle;
}

void uwuGirlAttachTextBox(void* vp_go, GameObject* tb) {
	GameObject* go = (GameObject*)vp_go;
	DemonGirl* self = (DemonGirl*)go->extension;
	
	self->textbox = tb;
}

void uwuGirlAttachButton(void* vp_go, GameObject* button) {
	GameObject* go = (GameObject*)vp_go;
	DemonGirl* self = (DemonGirl*)go->extension;
	
	self->button = button;
}

void uwuGirlSetSprite(void* vp_go, int index) {
	GameObject* go = (GameObject*)vp_go;
	DemonGirl* self = (DemonGirl*)go->extension;

	int i = index % 8;

	self->sprite.showw = 256;
	self->sprite.showx = i*256;

	go->partrect.w = self->sprite.showw;
	go->partrect.x = self->sprite.showx;
}

void uwuGirlUpdate(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;	
	DemonGirl* self = (DemonGirl*)go->extension;
	Game* game = (Game*)vp_game;

	double ypos = go->initialy + sin((double)SDL_GetTicks() * 0.005) * 10;
	go->rect.y = (int)ypos;

	if (buttonIsClicked(self->button)) { // this function also unsets STATE_CLICKED
		if (self->textbox) {
			textBoxSetText(self->textbox, game, "you clicked a button!");
		}

		uwuGirlSetSprite(go, SDL_GetTicks());
	}
}

