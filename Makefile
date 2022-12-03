# A simple Makefile for compiling small SDL projects

# set the compiler
CC := clang

# set the compiler flags
CFLAGS := `sdl2-config --cflags` -ggdb3 -O0 --std=c99 -Wall
LDFLAGS := `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

# add source files here
SRCS := game.c gameobjs.c game_state.c uwugirl.c textbox.c debug.c button.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

HDRS := common.h

# name of executable
EXEC := game

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(HDRS) $(SRCS)
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean

