#include "roguelike.h"

#define MAPW 10
#define MAPH 10

#define MOVE(dx, dy) do{\
		r->x += dx;\
		r->y += dy;\
		if (r->callback) {\
			r->callback(r->master, go, getEvent(r));\
		}}while(0);

typedef struct Roguelike {
	/* map */
	char map[MAPW][MAPH];
	int x, y;

	/* buttons */
	GameObject* up;
	GameObject* down;
	GameObject* left;
	GameObject* right;
	GameObject* attack;

	/* master */
	GameObject* master;
	RoguelikeCallback callback;
} Roguelike;

RoguelikeEvent getEvent(Roguelike* r) {
	if (r->map[r->y][r->x]) return EVENT_WALL;
	if (r->x > MAPW || r->y > MAPH || r->x < 0 || r->y < 0) return EVENT_OUT_OF_BOUNDS;
	return EVENT_FINE;
}

void roguelikeInitialize(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;

	Roguelike* r = (Roguelike*)malloc(sizeof(Roguelike)); // freed automatically by gameobjs.c
	go->extension = (void*)r;                             // setting it as the extension

	if (!r) {
		setGameError(game, ALLOC_ERR);
		return;
	}


	srand(time(NULL));

	memset(r->map, 0, MAPW*MAPH);     // set map to all zeros to start
	memset(r->map, 1, MAPW);          // set first row to all 1s
	memset(r->map+(MAPH-1), 1, MAPW); // set last row to 1s

	int xoffset, howmuch;
	for (int i = 1; i < MAPH - 1; i++) {
		r->map[i][MAPW - 1] = 1;  // set last column to 1
		memset(r->map+i, 1, 1);      // set the first column to 1
		
		// width of the wall (line of 1s)
		howmuch = rand() % (MAPW - 1);

		xoffset = 0;		  // the offset of the wall (cannot be greater than wall width)
		if (howmuch > 0) xoffset = rand() % howmuch;

		// memsetting what i just explained

		/*
			example:
				let howmuch = 5 ...
				 and xoffset = 2;

				the result would be (showing only the relevant row):

				memset(map[i]+1, 1, howmuch); ->
				  {1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
				      ^  ^  ^  ^  ^
				      1  2  3  4  5

				memset(map[i]+1, 0, xoffset); ->
				  {1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
				      ^  ^
				      1  2
		*/

		memset(r->map[i]+1, 1, howmuch);
		memset(r->map[i]+1, 0, xoffset);
	}

	r->x = 5;
	r->y = 5;

	r->map[r->y][r->x] = 0;
}

void roguelikeUpdate(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;

	Roguelike* r = (Roguelike*)go->extension;

	if (buttonIsClicked(r->up)) {
		MOVE(0, -1);
	}
	if (buttonIsClicked(r->down)) {
		MOVE(0, 1);
	}
	if (buttonIsClicked(r->right)) {
		MOVE(1, 0);
	}
	if (buttonIsClicked(r->left)) {
		MOVE(-1, 0);
	}
	if (buttonIsClicked(r->attack)) {

	}
}

void roguelikeAttachButtons(GameObject* go, GameObject* up,
			    GameObject* down, GameObject* left,
			    GameObject* right, GameObject* attack) {
	Roguelike* r = (Roguelike*)go->extension;

	r->up = up;
	r->down = down;
	r->left = left;
	r->right = right;
	r->attack = attack;
}

void roguelikeAttachMaster(GameObject* go, GameObject* master, RoguelikeCallback callback) {
	Roguelike* r = (Roguelike*)go->extension;

	r->master = master;
	r->callback = callback;
}

