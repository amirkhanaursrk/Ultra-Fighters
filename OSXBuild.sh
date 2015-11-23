EXE=Ultra-Fighters
CC=gcc
CPPC=g++
CFLAGS="-std=c11 -Wall -pedantic -c"
CPPFLAGS="-std=c++11 -Wall -pedantic"
C_FILES="lib/logger.c lib/myglutils.c lib/key_store.c"
CPP_FILES="main.cpp loop.cpp game_scene.cpp parent_game_object.cpp cube.cpp player.cpp"
INC="-I include/"
LIBS="lib/libglfw.dylib lib/libGLEW.dylib lib/libglfw.3.dylib -framework OpenGL"
OBJECTS=($C_FILES)

for (( i=0; i<${#OBJECTS[@]}; i++ )); do
  OBJECTS[i]=$(basename ${OBJECTS[i]} .c).o
done

OBJECTS=${OBJECTS[@]}

OLD_DIR="$(pwd)"
cd `dirname $0`
echo "Compiling C files..."
$CC $CFLAGS $C_FILES $INC &&
echo "Compiled C files!" &&
echo "Compiling C++ files..." &&
$CPPC $CPPFLAGS $CPP_FILES $OBJECTS -o $EXE $INC $LIBS &&
echo "Finished compiling!"
rm -f $OBJECTS
cd "$OLD_DIR"
