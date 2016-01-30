from os import chdir, listdir
from os.path import dirname

DEBUG = True
FULLSCREEN = True

""" THIS IS THE GENERAL MAKEFILE CONSTRUCTOR """
""" Use this ONLY when a new file is added to the ../../src/ folder """

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

    return sorted(set(deps)) # Sorted so that the Makefiles are more consistent

def constructMakefile(makefile, target, res_dest, c_flags, link_flags, copy_cmd, clean_cmd, exclude=['getline.c']):
    proj_root = '..'
    target = proj_root + target
    res_source = proj_root + '/Resources'
    res_dest = proj_root + res_dest
    sources = [f for f in listdir(proj_root + '/src') if '.h' not in f];
    sources = [s for s in sources if s not in exclude]
    objects = [s.split('.')[0] + '.o' for s in sources]
    c_flags = '-Wall -Werror -pedantic -I../include/ -DDEBUG=' + str(int(DEBUG)) + (' -DFULLSCREEN ' if FULLSCREEN else ' ') + c_flags

    makefile.write('TARGET=' + target + '\n')
    makefile.write('C_FLAGS=' + c_flags + '\n')
    makefile.write('COMPILE_C=gcc -std=c11 $(C_FLAGS) -c $<\n')
    makefile.write('COMPILE_CPP=g++ -std=c++1y $(C_FLAGS) -c $<\n')
    makefile.write('OBJECTS=' + ' '.join(objects) + '\n')
    makefile.write('RES_SOURCE=' + res_source + '\n')
    makefile.write('RES_DEST=' + res_dest + '\n')
    makefile.write('LIB_FLAGS=' + link_flags + '\n')
    makefile.write('\n')

    makefile.write('all: $(TARGET) $(RES_DEST)\n')
    makefile.write('\n')

    makefile.write('$(TARGET): $(OBJECTS)\n')
    makefile.write('\tg++ $^ -o $@ $(LIB_FLAGS)\n')
    makefile.write('\n')

    src_folder = proj_root + '/src/'
    for i, o in enumerate(objects):
        source = src_folder + sources[i]
        makefile.write(o + ': ' + source + ' ' + ' '.join(getDependencies(source)) + '\n')

        if source.endswith('.c'):
            makefile.write('\t$(COMPILE_C)\n\n')
        else:
            makefile.write('\t$(COMPILE_CPP)\n\n')

    makefile.write('.PHONY: $(RES_DEST) clean\n')
    makefile.write('\n')

    makefile.write('$(RES_DEST):\n')
    makefile.write('\t' + copy_cmd + '\n')
    makefile.write('\n')

    makefile.write('clean:\n')
    makefile.write('\t' + clean_cmd + '\n')

    makefile.close()
