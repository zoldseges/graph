CC=gcc
CFLAGS_BASE=-Werror -Wall -pedantic -std=c99
PKGS=sdl2 SDL2_ttf
CFLAGS=$(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS=$(shell pkg-config --libs $(PKGS))

all: graph

graph: src/main.c
#	$(CC) $^ $(CFLAGS) -ggdb -O0 -fsanitize=address $(LIBS) -o $@
	$(CC) $^ $(CFLAGS) -ggdb -O0 $(LIBS) -o $@

release: src/main.c
	$(CC) $^ $(CFLAGS) -O3 $(LIBS) -o graph
