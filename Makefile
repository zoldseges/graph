CC := gcc
DEBUG_FLAGS := -g -DDEBUG
RELEASE_FLAGS := -O3 -Werror
CFLAGS_BASE := -pedantic-errors -Wall -Wextra
SRCS := $(wildcard src/*.c)
HEADERS := $(wildcard src/*.h)
OBJS := $(patsubst src/%.c,build/%.o,$(SRCS))
PKGS := gtk4
CFLAGS := $(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS := $(shell pkg-config --libs $(PKGS)) -lm

debug: $(OBJS)
	$(CC) -o $@    $^ $(CFLAGS) $(LIBS) $(DEBUG_FLAGS) 

build/main.o: src/main.c $(HEADERS)
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(DEBUG_FLAGS)

build/%.o: src/%.c src/%.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS) $(DEBUG_FLAGS)

release: $(SRCS) $(HEADERS)
	$(CC) $(filter %.c,$^) -o graph $(CFLAGS) $(LIBS) $(RELEASE_FLAGS) 

test: $(wildcard test/src/*) $(SRCS) $(HEADERS)
	$(CC) test/src/main.c -o test/$@ $(CFLAGS) $(LIBS) $(DEBUG_FLAGS) 
