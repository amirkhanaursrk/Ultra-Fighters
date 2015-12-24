TARGET=../../bin/Win64/Ultra-Fighters.exe
C_FLAGS=-Wall -pedantic -I../../include/ -m64 -DDEBUG=1 -DFULLSCREEN
COMPILE_C=gcc $(C_FLAGS) -std=c11 -c $<
COMPILE_CPP=g++ $(C_FLAGS) -std=c++1y -c $<
OBJECTS=game_node.o game_scene.o getline.o hud.o logger.o loop.o main.o miscutils.o myglutils.o physics_body.o player.o projectile.o wavefront_object.o
RES_SOURCE=../../Resources
RES_DEST=../../bin/Win64/Resources
LIB_FLAGS=../../lib/Win64/glew32s.lib ../../lib/Win64/glew32.lib ../../lib/Win64/libglfw3.a -lopengl32 -lglu32 -lgdi32 -static

all: $(TARGET) $(RES_DEST)

$(TARGET): $(OBJECTS)
	g++ -m64 $^ -o $@ $(LIB_FLAGS)

game_node.o: ../../src/game_node.cpp ../../src/logger.h ../../src/miscutils.hpp ../../src/loop.hpp ../../src/game_node.hpp
	$(COMPILE_CPP)

game_scene.o: ../../src/game_scene.cpp ../../src/miscutils.hpp ../../src/player.hpp ../../src/physics_body.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/game_node.hpp ../../src/myglutils.h ../../src/loop.hpp
	$(COMPILE_CPP)

getline.o: ../../src/getline.c ../../src/getline.h
	$(COMPILE_C)

hud.o: ../../src/hud.cpp ../../src/player.hpp ../../src/physics_body.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/game_node.hpp ../../src/hud.hpp ../../src/myglutils.h ../../src/loop.hpp
	$(COMPILE_CPP)

logger.o: ../../src/logger.c ../../src/logger.h
	$(COMPILE_C)

loop.o: ../../src/loop.cpp ../../src/logger.h ../../src/loop.hpp
	$(COMPILE_CPP)

main.o: ../../src/main.cpp ../../src/player.hpp ../../src/physics_body.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/game_node.hpp ../../src/hud.hpp ../../src/myglutils.h ../../src/wavefront_object.hpp ../../src/loop.hpp
	$(COMPILE_CPP)

miscutils.o: ../../src/miscutils.cpp ../../src/logger.h ../../src/miscutils.hpp ../../src/loop.hpp ../../src/game_node.hpp
	$(COMPILE_CPP)

myglutils.o: ../../src/myglutils.c ../../src/myglutils.h ../../src/getline.h ../../src/logger.h
	$(COMPILE_C)

physics_body.o: ../../src/physics_body.cpp ../../src/physics_body.hpp
	$(COMPILE_CPP)

player.o: ../../src/player.cpp ../../src/miscutils.hpp ../../src/projectile.hpp ../../src/player.hpp ../../src/physics_body.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/game_node.hpp ../../src/myglutils.h ../../src/loop.hpp
	$(COMPILE_CPP)

projectile.o: ../../src/projectile.cpp ../../src/projectile.hpp ../../src/player.hpp ../../src/physics_body.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/game_node.hpp ../../src/myglutils.h ../../src/loop.hpp
	$(COMPILE_CPP)

wavefront_object.o: ../../src/wavefront_object.cpp ../../src/player.hpp ../../src/physics_body.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/game_node.hpp ../../src/myglutils.h ../../src/wavefront_object.hpp ../../src/loop.hpp
	$(COMPILE_CPP)

.PHONY: $(RES_DEST) clean

$(RES_DEST):
	robocopy $(RES_SOURCE) $(RES_DEST) /MIR > nul

clean:
	DEL $(OBJECTS) /Q
