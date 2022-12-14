#include "button.h"

void buttonOnMouse(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;
	Button* button = (Button*)go->extension;

	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	if ((mouse_x > button->rect.x && mouse_x < button->rect.x+button->rect.w) &&
			(mouse_y > button->rect.y && mouse_y < button->rect.y+button->rect.h)) {
		if (game->mouseheld) {
			button->state |= STATE_CLICKED;
		}
	}
}

void buttonCleanup(void* vp_go, void* vp_game) { // TODO
	/*
	GameObject* go = (GameObject*)vp_go;
	Button* button = (Button*)go->extension;
	Game* game = (Game*)vp_game;
	*/
}

void buttonAttachTextBox(void* vp_go, GameObject* tb) {
	GameObject* go = (GameObject*)vp_go;
	Button* button = (Button*)go->extension;

	button->textbox = tb;
	button->rect = tb->rect;
}

bool buttonIsClicked(void* vp_go) {
	/*
	 * THIS FUNCTION ALSO UNSETS STATE_CLICKED
	 */
	if (!vp_go) return false;

	GameObject* go = (GameObject*)vp_go;
	Button* button = (Button*)go->extension;

	bool isClicked = button->state & STATE_CLICKED;
	button->state &= ~STATE_CLICKED;

	return isClicked;
}

void buttonInitialize(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	Button* button = (Button*)malloc(sizeof(Button));

	button->textbox = NULL;
	button->state = STATE_NORMAL;
	button->rect.x = 0;
	button->rect.y = 0;
	button->rect.w = 0;
	button->rect.h = 0;

	go->extension = (void*)button;
	go->cleanup = &buttonCleanup;
	go->onMouse = &buttonOnMouse;
}

void buttonUpdate(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;
	Button* button = (Button*)go->extension;

	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	if ((mouse_x > button->rect.x && mouse_x < button->rect.x+button->rect.w) &&
			(mouse_y > button->rect.y && mouse_y < button->rect.y+button->rect.h)) {
		if (button->state & ~STATE_HOVERED) {
			button->state = button->state | STATE_HOVERED;
			button->state = button->state & ~STATE_NORMAL;
			textBoxSetColor((void*)button->textbox, (SDL_Color){255, 255, 0} /* C99 compound literal */);
			textBoxReRender((void*)button->textbox, game);
		}
	} else {
		if (button->state & ~STATE_NORMAL) {
			button->state = button->state | STATE_NORMAL;
			button->state = button->state & ~STATE_HOVERED;
			textBoxSetColor((void*)button->textbox, (SDL_Color){255, 255, 255});
			textBoxReRender((void*)button->textbox, game);
		}
	}
}

