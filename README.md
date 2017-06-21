Breakout
Author: Ighor Augusto

Based on: https://github.com/valeriangalliat/breakout
Thanks Valerian! ;)

Dependecies: ----------------------------------------------

- ncurses

# apt-get install libncurses5 libncurses5-dev

Compilação: -----------------------------------------------

# git clone breakout
# cd breakout
# make
# cd bin
# ./breakout

Controles: ------------------------------------------------

Left and Right Arrow moves the Bat
Up and Down Arrow moves the Bat faster

Bricks: ---------------------------------------------------

4 bricks types:

- 1 hit to destroy, 2 points,
- 2 hits to destroy, 4 points,
- 3 hits to destroy, 8 points,
- 4 hits to destroy, 16 points.

The color indicates how many hits are left to destroy:

- green:	1 hit,
- blue:		2 hits,
- yellow:	3 hits,
- red:		4 hits.

The points are got only if the brick are destroyed!

Lives: ---------------------------------------------------

You have 3 lives, starting from 0 to 2. When some mistakes
are done, you lost one life and the ball returns to the
center as well the bat.

When you win, each extra life will give 2 extra points.