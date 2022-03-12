CC := gcc
RELEASE_FLAGS := -Werror
DEBUG_FLAGS := -O0 -g
RELEASE_FLAGS := -O3
CFLAGS_BASE := -pedantic-errors -Wall -Wextra
SRCS := $(wildcard src/*.c)
HEADERS := $(wildcard src/*.h)
PKGS := gtk4
CFLAGS := $(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS := $(shell pkg-config --libs $(PKGS)) -lm

all: graph

graph: $(SRCS) $(HEADERS)
	$(CC) $(filter %.c,$^) -o $@ $(CFLAGS) $(LIBS) $(DEBUG_FLAGS) 

release: $(SRCS) $(HEADERS)
	$(CC) $(filter %.c,$^) -o $@ $(CFLAGS) $(LIBS) $(RELEASE_FLAGS) 
