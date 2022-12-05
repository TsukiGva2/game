#ifndef __COMMON_H__GAME_
#define __COMMON_H__GAME_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
//#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINW 640
#define WINH 480

// object id stuff
#define MAX_OBJS 255
#define ID_UINT Uint8

#define GAMEFON "resources/PixelGameFont.ttf"
#define GAMEFONSZ 24

#define GAMENAME "cool game"

//debugging stuff
#define malloc(x) my_malloc(x, __FILE__, __LINE__, __FUNCTION__)
#define free(x) my_free(x, __FILE__, __LINE__, __FUNCTION__)
void* my_malloc(size_t size, const char* file, int line, const char* func);
void* my_free(void* ptr, const char* file, int line, const char* func);
//end

typedef void (*GameFn)(void* vp_go, void* vp_game); // vp_ -> void*_

typedef enum {
	TYPE_HEAD,
	TYPE_BUTTON,
	TYPE_SPRITE,
	TYPE_TEXTBOX,
	TYPE_MANAGER
} ObjType;

typedef struct GameObject {
	SDL_Texture* tex;
	SDL_Rect rect;
	SDL_Rect partrect;
	int initialx;
	int initialy;
	ID_UINT id;
	ObjType type;
	GameFn update;
	GameFn cleanup;
	GameFn onMouse;
	void* extension;
	struct GameObject* next;
	struct GameObject* prev;
} GameObject;

typedef enum {
	ALLGOOD,
	ALLOC_ERR,
	SDL_ERR,
	NOID_ERR,
	MAXOBJS_ERR
} GameError;

typedef struct {
	uint8_t textspeed;
} GameProperties;

typedef struct {
	SDL_Window* win;
	SDL_Renderer* renderer;
	GameObject* gObjs_head;
	GameError err;
	SDL_Event event;
	int close_game;
	bool mouseheld;
	GameProperties options;
} Game;

#endif
