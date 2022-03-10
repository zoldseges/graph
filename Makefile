CC := gcc
RELEASE_FLAGS := -Werror
DEBUG_FLAGS := -g
CFLAGS_BASE := -pedantic-errors -Wall -Wextra
SRCS := $(wildcard src/*.c)
HEADERS := $(wildcard src/*.h)
PKGS := gtk4
CFLAGS := $(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS := $(shell pkg-config --libs $(PKGS))

all: graph

graph: $(SRCS) $(HEADERS)
	$(CC) $(filter %.c,$^) -o $@ $(CFLAGS) $(LIBS) $(DEBUG_FLAGS) 
