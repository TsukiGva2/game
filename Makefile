CC := clang
CFLAGS := `sdl2-config --cflags` -ggdb3 -O0 --std=c99 -Wall
LDFLAGS := `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
SRCS := game.c gameobjs.c game_state.c uwugirl.c textbox.c debug.c button.c game_mgr.c hearts.c roguelike.c
OBJS := $(SRCS:.c=.o)
HDRS := common.h $(SRCS:.c=.h)
EXEC := game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(CFLAGS)

$(OBJS): $(HDRS) $(SRCS)
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean

