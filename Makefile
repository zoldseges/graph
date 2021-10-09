CC=gcc
CFLAGS_BASE=-Wall -pedantic -ggdb -std=c99
PKGS=sdl2 SDL2_ttf
CFLAGS=$(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS=$(shell pkg-config --libs $(PKGS))

all: graph

graph: src/main.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@
