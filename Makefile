CC := gcc
DEBUG_FLAGS	:= -g -DDEBUG
RELEASE_FLAGS	:= -O3 -Werror
CFLAGS_BASE	:= -pedantic-errors -Wall -Wextra

SRCS		:= $(wildcard src/*.c)
HEADERS		:= $(wildcard src/*.h)
#headers w/o implementation
UNIMP_HEADERS	:= src/types.h
OBJS		:= $(patsubst src/%.c,build/%.o,$(SRCS))
PKGS		:= gtk4

R_CFLAGS	:= $(CFLAGS_BASE) $(shell pkg-config --cflags $(PKGS))
R_LIBS		:= $(shell pkg-config --libs $(PKGS)) -lm

DEBUG_LIB	:= /opt/gtk

all: set_debug_gtk_lib debug

debug: $(OBJS)
	$(CC) -o $@    $^ $(D_CFLAGS) $(D_LIBS) $(DEBUG_FLAGS) 

build/main.o: src/main.c $(HEADERS)
	$(CC) -o $@ -c $< $(D_CFLAGS) $(D_LIBS) $(DEBUG_FLAGS)

build/%.o: src/%.c src/%.h $(UNIMP_HEADERS)
	$(CC) -o $@ -c $< $(D_CFLAGS) $(D_LIBS) $(DEBUG_FLAGS)

release: $(SRCS) $(HEADERS)
	$(CC) $(filter %.c,$^) -o graph $(R_CFLAGS) $(R_LIBS) $(RELEASE_FLAGS) 

test: $(wildcard test/src/*) $(SRCS) $(HEADERS)
	$(CC) test/src/main.c -o test/$@ $(R_CFLAGS) $(R_LIBS) $(DEBUG_FLAGS) 

clean:
	rm -f build/*
	rm -f debug
	rm -f release


# set alternative lib for debug if exsists on machine
set_debug_gtk_lib:
ifneq ($(wildcard $(DEBUG_LIB)),)
	@echo "Set libgtk to locally compiled lib"
	$(eval D_CFLAGS := $(shell PKG_CONFIG_PATH=$(DEBUG_LIB)/lib/pkgconfig pkg-config --cflags $(PKGS)))
	$(eval D_LIBS := $(shell PKG_CONFIG_PATH=$(DEBUG_LIB)/lib/pkgconfig pkg-config --libs $(PKGS)) -lm)
else
	$(eval D_CFLAGS := $(R_CFLAGS))
	$(eval D_LIBS := $(R_LIBS))
endif

.PHONY: all clean set_debug_gtk_lib
