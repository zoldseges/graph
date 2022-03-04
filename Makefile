CC :=g++
CFLAGS_BASE := -pedantic-errors -Weffc++ -Wall -Wextra -Wsign-conversion -Werror -std=c++20
SRC_FILES := $(wildcard src/*.cpp)
PKGS := gtk4
CFLAGS := $(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS := $(shell pkg-config --libs $(PKGS))

all: graph

graph: $(SRC_FILES)
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@
