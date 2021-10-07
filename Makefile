CC=gcc
CFLAGS_BASE=-Wall -pedantic -ggdb
PKGS=sdl2
CFLAGS=$(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS=$(shell pkg-config --libs $(PKGS))

all: graph

graph: src/main.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@
