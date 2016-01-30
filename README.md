# Ultra-Fighters

A 3D Super Fighters Remake

[The Original that Inspired Me](http://www.twoplayergames.org/play/592-Super_Fighters.html)

This game is just a prototype so far and its developing pretty slowly, but steadily. As this is my first time with 
a 3D game, I'm learning at every turn so don't expect this to be the next Black Ops or whatever (It's still cool). 
So far this program doesn't work on Linux (Sorry!). I have a theory that with just a little effort on the building and 
compiling side of things that this would work on Linux as well though.


How to Compile
----

First Note: I have already compiled the source for Mac OS X. You can find it in the "bin/" folder.

Second Note: These instructions assume that you already have a compiler installed on your system.

Third Note: On step 3, if the "make" command is not on your system, replace "make" with whatever eqivalent command is.

### Steps:
    1. Open Shell
    2. "cd" into "bin" folder in the project folder
    3. Type "make Make<System>.make", and replace <System> with either OSX, Win32, or Win64 depending on your system.
    4. If there were no problems, the new executable file should be in the "bin" folder


Controls
----

To move: WASD

To Look around: Use the mouse

To jump: Spacebar

To close: Escape

To shoot: left click


Todos
----
 - Clean up GameNode inclusions
 - Port to Linux
 - More comments and docs (ugh!)
 - Make Wavefront parser not dumb
 - Add quality level(s)
 - Add enemies
 - Add collision detection/resolution


License
----

MIT


**Free Software, Oh Yeah!**


See LICENSE.txt for more info.
