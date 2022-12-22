#include "roguelike.h"

#define MAPW 10
#define MAPH 5

#define MOVE(dx, dy) do{\
		r->x += dx;\
		r->y += dy;\
		RoguelikeEvent e = getEvent(r);\
		if (e != EVENT_FINE) {\
			r->x -= dx;\
			r->y -= dy;\
		}\
		if (r->callback) {\
			r->callback(r->master, go, e);\
		}}while(0);

typedef struct Roguelike {
	/* map */
	char map[MAPH][MAPW];
	char* mapstr;
	int x, y;
	int dx, dy;
	GameObject* map_textbox;

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
	if (r->x > MAPW || r->y > MAPH || r->x < 0 || r->y < 0) return EVENT_OUT_OF_BOUNDS;
	if (r->map[r->y][r->x]) return EVENT_WALL;
	return EVENT_FINE;
}

void roguelikeCleanup(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	Roguelike* r = (Roguelike*)go->extension;

	free(r->mapstr); // need to manually free this
}

void roguelikeInitialize(void* vp_go, void* vp_game) {
	GameObject* go = (GameObject*)vp_go;
	Game* game = (Game*)vp_game;

	Roguelike* r = (Roguelike*)malloc(sizeof(Roguelike)); // freed automatically by gameobjs.c
	go->extension = (void*)r;                             // setting it as the extension
	go->cleanup = &roguelikeCleanup;

	if (!r) {
		setGameError(game, ALLOC_ERR);
		return;
	}

	// + MAPH to account for each newline
	r->mapstr = (char*)malloc((MAPH * MAPW) + MAPH + 1); // +1 for the '\0'
	if (!r->mapstr) {
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

	r->x = 2;
	r->y = 2;

	r->map[r->y][r->x] = 0;

	r->dx = 32;
	r->dy = 32;

	go->initialx = go->rect.x + r->x * r->dx;
	go->initialy = go->rect.y + r->y * r->dy;
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

	go->rect.x = go->initialx + r->x*r->dx;
	go->rect.y = go->initialy + r->y*r->dy;
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

void roguelikeDrawMap(GameObject* go, Game* game) {
	Roguelike* r = (Roguelike*)go->extension;

	if (!r->map_textbox) return;

	for (int i = 0; i < MAPH; i++) {
		for (int j = 0; j < MAPW; j++) {
			r->mapstr[(i*MAPW)+j] = r->map[i][j] ? '#' : ' ';
		}
		r->mapstr[(i*MAPW)+MAPW-2] = '#';
		r->mapstr[(i*MAPW)+MAPW-1] = '\n';
	}
	r->mapstr[MAPH*MAPW-1] = '\0';

	printf("%s\n", r->mapstr);

	textBoxSetText(r->map_textbox, game, r->mapstr);
}

void roguelikeAttachMap(GameObject* go, GameObject* map, Game* game) {
	Roguelike* r = (Roguelike*)go->extension;

	r->map_textbox = map;

	roguelikeDrawMap(go, game);
}

