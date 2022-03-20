CC := gcc
CFLAGS_BASE	:= -pedantic-errors -Wall -Wextra
DEBUG_FLAGS	:= $(CFLAGS_BASE) -g -DDEBUG
RELEASE_FLAGS	:= $(CFLAGS_BASE) -O3 -Werror

OBJS := $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))
PKGS := gtk4

#flags, changed to alternative in set_debug_gtk
CFLAGS := $(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
LIBS   := $(shell pkg-config --libs $(PKGS)) -lm

DEBUG_LIB := /opt/gtk

INCLUDE_PREQS := $(patsubst src/%.c, build/%.d, $(wildcard src/*.c))

all: set_debug_gtk_lib debug

debug: $(OBJS)
	@echo $(OBJS)
	$(CC) -o $@    $^ $(D_CFLAGS) $(D_LIBS) $(DEBUG_FLAGS) 

build/%.o: src/%.c
	$(CC) -o $@ -c $< $(D_CFLAGS) $(D_LIBS) $(DEBUG_FLAGS)

# gen header prequisites
build/%.d: src/%.c
	gcc -MM -MT $(patsubst build/%.d,build/%.o,$@) $< > $@

release:
	$(CC) $(wildcard src/*.c) -o graph $(CFLAGS) $(LIBS) $(RELEASE_FLAGS) 

test : set_debug_gtk_lib
test: $(wildcard test/src/*)
	$(CC) test/src/main.c -o test/$@ $(D_CFLAGS) $(D_LIBS) $(DEBUG_FLAGS) 

.PHONY:
clean:
	rm -f build/*
	rm -f debug
	rm -f release


# set alternative lib for debug if exsists on machine
.PHONY:
set_debug_gtk_lib:
ifneq ($(wildcard $(DEBUG_LIB)),)
	@echo "Set libgtk to locally compiled lib"
	$(eval D_CFLAGS := $(shell PKG_CONFIG_PATH=$(DEBUG_LIB)/lib/pkgconfig pkg-config --cflags $(PKGS)))
	$(eval D_LIBS := $(shell PKG_CONFIG_PATH=$(DEBUG_LIB)/lib/pkgconfig pkg-config --libs $(PKGS)) -lm)
else
	$(eval D_CFLAGS := $(CFLAGS))
	$(eval D_LIBS := $(LIBS))
endif

include $(INCLUDE_PREQS)
