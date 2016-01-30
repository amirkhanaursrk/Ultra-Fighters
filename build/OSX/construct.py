import sys
import os

from genconst import constructMakefile

""" This file makes the Makefile for the 'OSX' platform """ 
""" This file imports ../genconst.py for most of its functionality """
""" To use this file as a main script, you cannot do relative imports and
therefore must have ../genconst in your PYTHONPATH """
""" Since the author was lazy I just made a soft link in this directoy to
../genconst.py """

if __name__ == '__main__':
    if '/' in __file__:
        os.chdir(os.path.dirname(__file__))

    makefile = open('Makefile.make', 'w')
    target = '/bin/Ultra-Fighters.app/Contents/MacOS/Ultra-Fighters_osx'
    res_dest = '/bin/Ultra-Fighters.app/Contents/Resources/'
    c_flags = ''
    link_flags = '../../lib/OSX/libGLEW.a ../../lib/OSX/libglfw3.a -framework OpenGL -framework CoreVideo -framework Cocoa -framework IOKit'
    copy_cmd = 'rm -rf $(RES_DEST)\n\tcp -R $(RES_SOURCE) $@'
    clean_cmd = 'rm -f $(OBJECTS)'

    constructMakefile(makefile, target, res_dest, c_flags, link_flags, copy_cmd, clean_cmd)
