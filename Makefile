BIN_FILE = world3d

SRC_FILES += main.cpp
SRC_FILES += window.cpp
SRC_FILES += scene.cpp
SRC_FILES += actor.cpp
SRC_FILES += camera.cpp
SRC_FILES += 

VPATH += src

INSTALL_DIR = /usr/local/bin

override CFLAGS += -Iinclude
override CFLAGS += -Wall -Wextra -Wuninitialized
override CFLAGS += -std=c++14
override CFLAGS += -pipe
build: override CFLAGS += -g0 -s -O3
debug: override CFLAGS += -g3 -ggdb3 -O0 -DDEBUG

override LDFLAGS += -lglut
build: override LDFLAGS +=

CXX = g++

ifeq ($(CXX), g++)
	override CFLAGS +=
	override LDFLAGS += -lGL -lGLU
endif

ifeq ($(CXX), clang++)
	override CFLAGS +=
	override LDFLAGS += -lGL -lGLU
endif

ifeq ($(CXX), i686-w64-mingw32-g++)
	override CFLAGS +=
	override LDFLAGS += -L/usr/i686-w64-mingw32/sys-root/mingw/lib
	override LDFLAGS += -lopengl32 -lglu32
endif

ifeq ($(CXX), x86_64-w64-mingw32-g++)
	override CFLAGS += 
	override LDFLAGS += -L/usr/x86_64-w64-mingw32/sys-root/mingw/lib
	override LDFLAGS += -lopengl32 -lglu32
endif


OBJ_FILES := $(patsubst %.cpp,obj/%.o, $(SRC_FILES))
QUIET_CXX = @echo '   ' CXX $(notdir $@);

#.ONESHELL:
.PHONY: build debug test docs

all: build

build: mkdirs _build

debug: mkdirs _debug

_build: $(OBJ_FILES)
	$(CXX) $^ -o bin/$(BIN_FILE) $(LDFLAGS)

_debug: $(OBJ_FILES)
	$(CXX) $^ -o bin/$(BIN_FILE) $(LDFLAGS)

test:
docs:

obj/%.o: %.cpp
	$(QUIET_CXX) $(CXX) -c $< -o $@ $(CFLAGS)

install: mkdirs build
	install bin/$(BIN_FILE) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(BIN_FILE)

clean:
	@rm -f obj/*
	@rm -f bin/*

mkdirs: 
	@if [ ! -d bin ]; then \
		mkdir bin; \
	fi

	@if [ ! -d obj ]; then \
		mkdir obj; \
	fi
