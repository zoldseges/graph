CC :=gcc
CFLAGS_BASE := -pedantic-errors -Wall -Wextra -Werror 
SRC_FILES := $(wildcard src/*.c)
PKGS := gtkmm-4.0
CFLAGS := $(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS := $(shell pkg-config --libs $(PKGS))

all: graph

graph: $(SRC_FILES)
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@
