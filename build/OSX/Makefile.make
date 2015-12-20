all: ../../bin/OSX/Ultra-Fighters.app/Contents/MacOS/Ultra-Fighters.osx ../../bin/OSX/Ultra-Fighters.app/Contents/Resources

.PHONY: clean ../../bin/OSX/Ultra-Fighters.app/Contents/Resources

../../bin/OSX/Ultra-Fighters.app/Contents/MacOS/Ultra-Fighters.osx: game_node.o game_scene.o hud.o logger.o loop.o main.o miscutils.o myglutils.o physics_body.o player.o projectile.o wavefront_object.o
	g++ -std=c++1y -Wall -pedantic $^ ../../lib/OSX/libGLEW.a ../../lib/OSX/libglfw3.a -framework OpenGL -framework CoreVideo -framework Cocoa -framework IOKit -o $@

../../bin/OSX/Ultra-Fighters.app/Contents/Resources: ../../Resources
	 rm -rf ../../bin/OSX/Ultra-Fighters.app/Contents/Resources/*
	 cp -r ../../Resources/* ../../bin/OSX/Ultra-Fighters.app/Contents/Resources

game_node.o: ../../src/game_node.cpp ../../src/loop.hpp ../../src/miscutils.hpp ../../src/logger.h ../../src/game_node.hpp
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

game_scene.o: ../../src/game_scene.cpp ../../src/loop.hpp ../../src/miscutils.hpp ../../src/logger.h ../../src/game_scene.hpp ../../src/game_node.hpp ../../src/physics_body.hpp ../../src/player.hpp ../../src/myglutils.h
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

hud.o: ../../src/hud.cpp ../../src/loop.hpp ../../src/wininfo.h ../../src/hud.hpp ../../src/logger.h ../../src/game_node.hpp ../../src/myglutils.h
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

logger.o: ../../src/logger.c ../../src/logger.h
	gcc -std=c11 -Wall -pedantic -I../../include/ -c $<

loop.o: ../../src/loop.cpp ../../src/loop.hpp ../../src/logger.h
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

main.o: ../../src/main.cpp ../../src/loop.hpp ../../src/wininfo.h ../../src/hud.hpp ../../src/logger.h ../../src/game_scene.hpp ../../src/wavefront_object.hpp ../../src/game_node.hpp ../../src/physics_body.hpp ../../src/player.hpp ../../src/myglutils.h
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

miscutils.o: ../../src/miscutils.cpp ../../src/loop.hpp ../../src/miscutils.hpp ../../src/logger.h ../../src/game_node.hpp
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

myglutils.o: ../../src/myglutils.c ../../src/logger.h ../../src/myglutils.h
	gcc -std=c11 -Wall -pedantic -I../../include/ -c $<

physics_body.o: ../../src/physics_body.cpp ../../src/physics_body.hpp
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

player.o: ../../src/player.cpp ../../src/loop.hpp ../../src/wininfo.h ../../src/logger.h ../../src/game_scene.hpp ../../src/projectile.hpp ../../src/game_node.hpp ../../src/physics_body.hpp ../../src/player.hpp ../../src/myglutils.h
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

projectile.o: ../../src/projectile.cpp ../../src/loop.hpp ../../src/logger.h ../../src/game_scene.hpp ../../src/projectile.hpp ../../src/game_node.hpp ../../src/physics_body.hpp ../../src/player.hpp ../../src/myglutils.h
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

wavefront_object.o: ../../src/wavefront_object.cpp ../../src/loop.hpp ../../src/logger.h ../../src/game_scene.hpp ../../src/wavefront_object.hpp ../../src/game_node.hpp ../../src/physics_body.hpp ../../src/player.hpp ../../src/myglutils.h
	g++ -std=c++1y -Wall -pedantic -I../../include/ -c $<

clean:
	rm -f game_node.o game_scene.o hud.o logger.o loop.o main.o miscutils.o myglutils.o physics_body.o player.o projectile.o wavefront_object.o
