TARGET=../../bin/OSX/Ultra-Fighters.app/Contents/MacOS/Ultra-Fighters.osx
C_FLAGS=-Wall -pedantic -I../../include/ -DDEBUG=1 -DFULLSCREEN 
COMPILE_C=gcc -std=c11 $(C_FLAGS) -c $<
COMPILE_CPP=g++ -std=c++1y $(C_FLAGS) -c $<
OBJECTS=game_node.o game_scene.o hud.o logger.o loop.o main.o miscutils.o myglutils.o physics_body.o player.o projectile.o wavefront_object.o
RES_SOURCE=../../Resources
RES_DEST=../../bin/OSX/Ultra-Fighters.app/Contents/Resources/
LIB_FLAGS=../../lib/OSX/libGLEW.a ../../lib/OSX/libglfw3.a -framework OpenGL -framework CoreVideo -framework Cocoa -framework IOKit

all: $(TARGET) $(RES_DEST)

$(TARGET): $(OBJECTS)
	g++ $^ -o $@ $(LIB_FLAGS)

game_node.o: ../../src/game_node.cpp ../../src/miscutils.hpp ../../src/game_node.hpp ../../src/logger.h ../../src/loop.hpp
	$(COMPILE_CPP)

game_scene.o: ../../src/game_scene.cpp ../../src/myglutils.h ../../src/player.hpp ../../src/logger.h ../../src/miscutils.hpp ../../src/physics_body.hpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/loop.hpp
	$(COMPILE_CPP)

hud.o: ../../src/hud.cpp ../../src/myglutils.h ../../src/player.hpp ../../src/logger.h ../../src/physics_body.hpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/hud.hpp ../../src/loop.hpp
	$(COMPILE_CPP)

logger.o: ../../src/logger.c ../../src/logger.h
	$(COMPILE_C)

loop.o: ../../src/loop.cpp ../../src/logger.h ../../src/loop.hpp
	$(COMPILE_CPP)

main.o: ../../src/main.cpp ../../src/myglutils.h ../../src/wavefront_object.hpp ../../src/player.hpp ../../src/logger.h ../../src/physics_body.hpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/hud.hpp ../../src/loop.hpp
	$(COMPILE_CPP)

miscutils.o: ../../src/miscutils.cpp ../../src/miscutils.hpp ../../src/game_node.hpp ../../src/logger.h ../../src/loop.hpp
	$(COMPILE_CPP)

myglutils.o: ../../src/myglutils.c ../../src/myglutils.h ../../src/logger.h ../../src/getline.h
	$(COMPILE_C)

physics_body.o: ../../src/physics_body.cpp ../../src/physics_body.hpp
	$(COMPILE_CPP)

player.o: ../../src/player.cpp ../../src/myglutils.h ../../src/player.hpp ../../src/logger.h ../../src/miscutils.hpp ../../src/physics_body.hpp ../../src/game_node.hpp ../../src/projectile.hpp ../../src/game_scene.hpp ../../src/loop.hpp
	$(COMPILE_CPP)

projectile.o: ../../src/projectile.cpp ../../src/myglutils.h ../../src/player.hpp ../../src/logger.h ../../src/physics_body.hpp ../../src/game_node.hpp ../../src/projectile.hpp ../../src/game_scene.hpp ../../src/loop.hpp
	$(COMPILE_CPP)

wavefront_object.o: ../../src/wavefront_object.cpp ../../src/myglutils.h ../../src/wavefront_object.hpp ../../src/player.hpp ../../src/logger.h ../../src/physics_body.hpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/loop.hpp
	$(COMPILE_CPP)

.PHONY: $(RES_DEST) clean

$(RES_DEST):
	rm -rf $(RES_DEST)
	cp -R $(RES_SOURCE) $@

clean:
	rm -f $(OBJECTS)
