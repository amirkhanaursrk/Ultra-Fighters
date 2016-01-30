TARGET=../../bin/Win64/Ultra-Fighters.exe
C_FLAGS=-Wall -Werror -pedantic -I../../include/ -DDEBUG=1 -DFULLSCREEN -m64
COMPILE_C=gcc -std=c11 $(C_FLAGS) -c $<
COMPILE_CPP=g++ -std=c++1y $(C_FLAGS) -c $<
OBJECTS=aabb.o game_node.o game_scene.o getline.o hud.o logger.o loop.o main.o miscutils.o myglutils.o physics_body.o player.o projectile.o set_uniform.o sphere.o sphere_node.o triangle.o wavefront_object.o
RES_SOURCE=../../Resources
RES_DEST=../../bin/Win64/Resources
LIB_FLAGS=../../lib/Win64/glew32s.lib ../../lib/Win64/glew32.lib ../../lib/Win64/libglfw3.a -lopengl32 -lglu32 -lgdi32 -m64 -static

all: $(TARGET) $(RES_DEST)

$(TARGET): $(OBJECTS)
	g++ $^ -o $@ $(LIB_FLAGS)

aabb.o: ../../src/aabb.cpp ../../src/aabb.hpp ../../src/intersect.hpp ../../src/miscutils.hpp ../../src/sphere.hpp ../../src/triangle.hpp
	$(COMPILE_CPP)

game_node.o: ../../src/game_node.cpp ../../src/game_node.hpp ../../src/logger.h ../../src/loop.hpp ../../src/miscutils.hpp ../../src/triangle.hpp
	$(COMPILE_CPP)

game_scene.o: ../../src/game_scene.cpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/loop.hpp ../../src/miscutils.hpp ../../src/myglutils.h ../../src/physics_body.hpp ../../src/player.hpp ../../src/triangle.hpp
	$(COMPILE_CPP)

getline.o: ../../src/getline.c ../../src/getline.h
	$(COMPILE_C)

hud.o: ../../src/hud.cpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/hud.hpp ../../src/logger.h ../../src/loop.hpp ../../src/myglutils.h ../../src/physics_body.hpp ../../src/player.hpp
	$(COMPILE_CPP)

logger.o: ../../src/logger.c ../../src/logger.h
	$(COMPILE_C)

loop.o: ../../src/loop.cpp ../../src/logger.h ../../src/loop.hpp
	$(COMPILE_CPP)

main.o: ../../src/main.cpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/hud.hpp ../../src/logger.h ../../src/loop.hpp ../../src/myglutils.h ../../src/physics_body.hpp ../../src/player.hpp ../../src/sphere.hpp ../../src/sphere_node.hpp ../../src/wavefront_object.hpp
	$(COMPILE_CPP)

miscutils.o: ../../src/miscutils.cpp ../../src/game_node.hpp ../../src/loop.hpp ../../src/miscutils.hpp ../../src/triangle.hpp
	$(COMPILE_CPP)

myglutils.o: ../../src/myglutils.c ../../src/getline.h ../../src/logger.h ../../src/myglutils.h
	$(COMPILE_C)

physics_body.o: ../../src/physics_body.cpp ../../src/physics_body.hpp
	$(COMPILE_CPP)

player.o: ../../src/player.cpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/loop.hpp ../../src/miscutils.hpp ../../src/myglutils.h ../../src/physics_body.hpp ../../src/player.hpp ../../src/projectile.hpp ../../src/triangle.hpp
	$(COMPILE_CPP)

projectile.o: ../../src/projectile.cpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/loop.hpp ../../src/myglutils.h ../../src/physics_body.hpp ../../src/player.hpp ../../src/projectile.hpp
	$(COMPILE_CPP)

set_uniform.o: ../../src/set_uniform.cpp ../../src/logger.h ../../src/myglutils.h ../../src/set_uniform.hpp
	$(COMPILE_CPP)

sphere.o: ../../src/sphere.cpp ../../src/sphere.hpp
	$(COMPILE_CPP)

sphere_node.o: ../../src/sphere_node.cpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/loop.hpp ../../src/miscutils.hpp ../../src/myglutils.h ../../src/physics_body.hpp ../../src/player.hpp ../../src/set_uniform.hpp ../../src/sphere.hpp ../../src/sphere_node.hpp ../../src/triangle.hpp
	$(COMPILE_CPP)

triangle.o: ../../src/triangle.cpp ../../src/triangle.hpp
	$(COMPILE_CPP)

wavefront_object.o: ../../src/wavefront_object.cpp ../../src/game_node.hpp ../../src/game_scene.hpp ../../src/logger.h ../../src/loop.hpp ../../src/myglutils.h ../../src/physics_body.hpp ../../src/player.hpp ../../src/wavefront_object.hpp
	$(COMPILE_CPP)

.PHONY: $(RES_DEST) clean

$(RES_DEST):
	robocopy $(RES_SOURCE) $(RES_DEST) /MIR > nul

clean:
	DEL $(OBJECTS) /Q
