from os import chdir, listdir
from os.path import dirname

DEBUG = True

""" THIS IS THE MAKEFILE CONSTRUCTOR FOR >>> Win64 <<<"""
""" This file makes ./Makefile.make """
""" Call this ONLY when a new file is added to the ../../src/ folder """

def getDependencies(fileName, depth=0):
    if (depth >= 10):
        print('Too deep, maybe there are circular dependencies?')
        return []

    f = open(fileName)
    deps = []
    base_folder = dirname(fileName) + '/'

    for line in f:
        if line.strip().startswith('#include "'):
            dep = base_folder + line.split('"')[1]
            deps.append(dep)
            deps += getDependencies(dep, depth + 1)

    return set(deps)

if __name__ == '__main__':
    if '/' in __file__:
        chdir(dirname(__file__)) # we are in the '.../Ultra\ Fighters/build/Win64/' folder

    makefile = open('Makefile.make', 'w')

    proj_root = '../..'
    target = proj_root + '/bin/Win64/Ultra-Fighters.exe'
    res_source = proj_root + '/Resources'
    res_dest = proj_root + '/bin/Win64/Resources'
    sources = [f for f in listdir(proj_root + '/src') if '.h' not in f];
    objects = [s.split('.')[0] + '.o' for s in sources]
    lib_flags = '../../lib/Win64/glew32s.lib ../../lib/Win64/glew32.lib ../../lib/Win64/libglfw3.a -lopengl32 -lglu32 -lgdi32 -static'

    makefile.write('TARGET=' + target + '\r\n')
    makefile.write('C_FLAGS=-Wall -pedantic -I../../include/ -DDEBUG=' + str(int(DEBUG)) + '\r\n')
    makefile.write('COMPILE_C=gcc $(C_FLAGS) -std=c11 -c $<\r\n')
    makefile.write('COMPILE_CPP=g++ $(C_FLAGS) -std=c++1y -c $<\r\n')
    makefile.write('OBJECTS=' + ' '.join(objects) + '\r\n')
    makefile.write('RES_SOURCE=' + res_source + '\r\n')
    makefile.write('RES_DEST=' + res_dest + '\r\n')
    makefile.write('LIB_FLAGS=' + lib_flags + '\r\n')
    makefile.write('\r\n')

    makefile.write('all: $(TARGET) $(RES_DEST)\r\n')
    makefile.write('\r\n')

    makefile.write('$(TARGET): $(OBJECTS)\r\n')
    makefile.write('\tg++ -std=c++1y -Wall -pedantic $^ -o $@ $(LIB_FLAGS)\r\n')
    makefile.write('\r\n')

    src_folder = proj_root + '/src/'
    for i, o in enumerate(objects):
        source = src_folder + sources[i]
        makefile.write(o + ': ' + source + ' ' + ' '.join(getDependencies(source)) + '\r\n')

        if source.endswith('.c'):
            makefile.write('\t$(COMPILE_C)\r\n\r\n')
        else:
            makefile.write('\t$(COMPILE_CPP)\r\n\r\n')

    makefile.write('.PHONY: $(RES_DEST) clean\r\n')
    makefile.write('\r\n')

    makefile.write('$(RES_DEST):\r\n')
    makefile.write('\trobocopy $(RES_SOURCE) $(RES_DEST) /MIR > nul\r\n')
    makefile.write('\r\n')

    makefile.write('clean:\r\n')
    makefile.write('\tDEL $(OBJECTS) /Q\r\n')

    makefile.close()
