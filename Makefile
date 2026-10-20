CXX := g++

CXXFLAGS += -std=c++17 -Isrc -Ilibs/SDL/include -Ilibs/GLM/include -Ilibs/Lua/include -Ilibs/Sol/include -Ilibs/ImGui
LDFLAGS += -Llibs/SDL/lib -Wl,-rpath,@executable_path/libs/SDL/lib -Llibs/lua/lib
LDLIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua

DEPS := libs/SDL/include/SDL2/SDL.h \
        libs/glm/include/glm/glm.hpp \
        libs/lua/include/lua.h \
        libs/lua/lib/liblua.a \
        libs/sol/include/sol/sol.hpp \
        libs/imgui/imgui.h

build: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp src/*.cpp $(LDFLAGS) $(LDLIBS) -o gameengine

run:
	./gameengine

clean:
	rm -f gameengine

mr:
	make build
	make run

cmr:
	make clean
	make build
	make run


deps: $(DEPS)

libs/SDL/include/SDL2/SDL.h:
	# SDL2
	mkdir -p libs
	curl -L --fail -o libs/.SDL2.tar.gz https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/SDL2-2.32.10.tar.gz
	rm -rf libs/.sdl-src
	mkdir -p libs/.sdl-src
	tar -xzf libs/.SDL2.tar.gz --strip-components=1 -C libs/.sdl-src
	cmake -S libs/.sdl-src -B libs/.sdl-src/build \
		-DCMAKE_INSTALL_PREFIX="$(PWD)/libs/SDL" \
		-DSDL_SHARED=ON -DSDL_STATIC=OFF
	cmake --build libs/.sdl-src/build
	cmake --install libs/.sdl-src/build
	rm -rf libs/.SDL2.tar.gz libs/.sdl-src
	# SDL_Image
	curl -L --fail -o libs/.SDL2_image.tar.gz https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.8.12.tar.gz
	rm -rf libs/.sdl-image-src
	mkdir -p libs/.sdl-image-src
	tar -xzf libs/.SDL2_image.tar.gz --strip-components=1 -C libs/.sdl-image-src
	cmake -S libs/.sdl-image-src -B libs/.sdl-image-src/build \
		-DCMAKE_PREFIX_PATH="$(PWD)/libs/SDL" \
		-DCMAKE_INSTALL_PREFIX="$(PWD)/libs/SDL"
	cmake --build libs/.sdl-image-src/build
	cmake --install libs/.sdl-image-src/build
	rm -rf libs/.SDL2_image.tar.gz libs/.sdl-image-src
	# SDL_TTF
	curl -L --fail -o libs/.SDL2_ttf.tar.gz https://github.com/libsdl-org/SDL_ttf/archive/refs/tags/release-2.24.0.tar.gz
	rm -rf libs/.sdl-ttf-src
	mkdir -p libs/.sdl-ttf-src
	tar -xzf libs/.SDL2_ttf.tar.gz --strip-components=1 -C libs/.sdl-ttf-src
	cd libs/.sdl-ttf-src/external && sh download.sh
	cmake -S libs/.sdl-ttf-src -B libs/.sdl-ttf-src/build \
		-DCMAKE_PREFIX_PATH="$(PWD)/libs/SDL" \
		-DCMAKE_INSTALL_PREFIX="$(PWD)/libs/SDL" \
		-DSDL2TTF_VENDORED=ON
	cmake --build libs/.sdl-ttf-src/build
	cmake --install libs/.sdl-ttf-src/build
	rm -rf libs/.SDL2_ttf.tar.gz libs/.sdl-ttf-src
	# SDL_Mixer
	curl -L --fail -o libs/.SDL2_mixer.tar.gz https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.8.2.tar.gz
	rm -rf libs/.sdl-mixer-src
	mkdir -p libs/.sdl-mixer-src
	tar -xzf libs/.SDL2_mixer.tar.gz --strip-components=1 -C libs/.sdl-mixer-src
	cd libs/.sdl-mixer-src/external && sh download.sh
	cmake -S libs/.sdl-mixer-src -B libs/.sdl-mixer-src/build \
		-DCMAKE_PREFIX_PATH="$(PWD)/libs/SDL" \
		-DCMAKE_INSTALL_PREFIX="$(PWD)/libs/SDL" \
		-DSDL2MIXER_VENDORED=ON
	cmake --build libs/.sdl-mixer-src/build
	cmake --install libs/.sdl-mixer-src/build
	rm -rf libs/.SDL2_mixer.tar.gz libs/.sdl-mixer-src

# GLM — header-only
libs/glm/include/glm/glm.hpp:
	mkdir -p libs
	curl -L --fail -o libs/.glm.tar.gz https://github.com/g-truc/glm/archive/refs/tags/1.0.3.tar.gz
	rm -rf libs/.glm-src
	mkdir -p libs/.glm-src
	tar -xzf libs/.glm.tar.gz --strip-components=1 -C libs/.glm-src
	mkdir -p libs/glm/include
	cp -a libs/.glm-src/glm libs/glm/include/
	rm -rf libs/.glm.tar.gz libs/.glm-src

# Lua 5.3 — build a local static library
libs/lua/include/lua.h libs/Lua/lib/liblua.a:
	mkdir -p libs
	curl -L --fail -o libs/.lua.tar.gz https://www.lua.org/ftp/lua-5.3.6.tar.gz
	rm -rf libs/.lua-src
	mkdir -p libs/.lua-src
	tar -xzf libs/.lua.tar.gz --strip-components=1 -C libs/.lua-src
	$(MAKE) -C libs/.lua-src macosx
	mkdir -p libs/lua/include libs/Lua/lib
	cp libs/.lua-src/src/*.h libs/lua/include/
	cp libs/.lua-src/src/liblua.a libs/lua/lib/
	rm -rf libs/.lua.tar.gz libs/.lua-src

# sol — header-only
libs/sol/include/sol/sol.hpp:
	mkdir -p libs
	curl -L --fail -o libs/.sol.tar.gz https://github.com/ThePhD/sol2/archive/refs/tags/v3.3.0.tar.gz
	rm -rf libs/.sol-src
	mkdir -p libs/.sol-src
	tar -xzf libs/.sol.tar.gz --strip-components=1 -C libs/.sol-src
	mkdir -p libs/sol/include
	cp -a libs/.sol-src/include/sol libs/sol/include/
	rm -rf libs/.sol.tar.gz libs/.sol-src

# Dear ImGui — retain its .cpp files for compiling into your app later
libs/imgui/imgui/imgui.h:
	mkdir -p libs
	curl -L --fail -o libs/.imgui.tar.gz https://github.com/ocornut/imgui/archive/refs/tags/v1.93.0.tar.gz
	rm -rf libs/imgui/imgui
	mkdir -p libs/imgui/imgui
	tar -xzf libs/.imgui.tar.gz --strip-components=1 -C libs/imgui/imgui
	rm -f libs/.imgui.tar.gz

clean-deps:
	rm -f gameengine
	rm -rf libs/SDL libs/glm libs/lua libs/sol libs/imgui
	rm -rf libs/.*.tar.gz libs/.*-src

.PHONY: run clean mr cmr deps clean-deps