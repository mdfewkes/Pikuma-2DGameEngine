CXX := g++

CXXFLAGS += -std=c++17 -Ilibs/SDL/include
LDFLAGS += -Llibs/SDL/lib -Wl,-rpath,@executable_path/libs/SDL/lib
LDLIBS += -lSDL2

.PHONY: all deps clean

all: main

main: main.cpp $(SDL_STAMP)
	$(CXX) $(CXXFLAGS) main.cpp -o main $(LDFLAGS) $(LDLIBS)

SDL_VERSION := 2.32.10
SDL_URL := https://github.com/libsdl-org/SDL/releases/download/release-$(SDL_VERSION)/SDL2-$(SDL_VERSION).tar.gz
SDL_ARCHIVE := libs/.SDL2-$(SDL_VERSION).tar.gz
SDL_SRC := libs/.sdl-src
SDL_PREFIX := $(CURDIR)/libs/SDL
SDL_STAMP := $(SDL_PREFIX)/.built

deps: $(SDL_STAMP)

$(SDL_STAMP):
	mkdir -p libs
	curl -L --fail -o $(SDL_ARCHIVE) $(SDL_URL)
	rm -rf $(SDL_SRC)
	mkdir -p $(SDL_SRC)
	tar -xzf $(SDL_ARCHIVE) --strip-components=1 -C $(SDL_SRC)
	cmake -S $(SDL_SRC) -B $(SDL_SRC)/build \
		-DCMAKE_INSTALL_PREFIX=$(SDL_PREFIX) \
		-DSDL_SHARED=ON -DSDL_STATIC=OFF
	cmake --build $(SDL_SRC)/build
	cmake --install $(SDL_SRC)/build
	rm -rf $(SDL_ARCHIVE) $(SDL_SRC)
	touch $(SDL_STAMP)

clean:
	rm -f main
	rm -rf $(SDL_PREFIX) $(SDL_ARCHIVE) $(SDL_SRC)
