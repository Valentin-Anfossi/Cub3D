*This project has been created as part of the 42 curriculum by jelucian, vanfossi*

		   █████████  █████  █████ ███████████   ████████  ██████████  
		  ███░░░░░███░░███  ░░███ ░░███░░░░░███ ███░░░░███░░███░░░░███ 
		 ███     ░░░  ░███   ░███  ░███    ░███░░░    ░███ ░███   ░░███
		░███          ░███   ░███  ░██████████    ██████░  ░███    ░███
        ░███          ░███   ░███  ░███░░░░░███  ░░░░░░███ ░███    ░███
        ░░███     ███ ░███   ░███  ░███    ░███ ███   ░███ ░███    ███ 
         ░░█████████  ░░████████   ███████████ ░░████████  ██████████  
          ░░░░░░░░░    ░░░░░░░░   ░░░░░░░░░░░   ░░░░░░░░  ░░░░░░░░░░   

- [Description :](#description-)
- [How does it work ?](#how-does-it-work-)
- [Instructions :](#instructions-)
- [Ressources :](#ressources-)
- [TLDR](#tldr)

# Description :

Cub3D is a simple raycaster first-person game based on classics like wolfenstein3D
& DOOM.

It reads a map (in the .cub format) and renders it as an explorable world in 3D ! (wow)

In its mandatory form, you move with WASD and use the arrow keys to look left and right.

The bonus part brings some additional features like wall collisions (with sliding (wow))
a map that can be displayed in fullscreen (diablo style), sprinting, mouse view and interactable
doors.

# How does it work ?

The main rendering part uses a DDA algorithm (Digital Differential Analysis).
But how does it work exactly ?

Well lemme tell you :
For each vertical line of your little window, we send a ray from the player position
using a vector that represents your field of view (ie: leftmost ray goes at a leftward angle 
while the one at the center goes straight ahead), we then use the DDA to quickly compute 
where this ray will hit a wall. When it does, we store the distance value and use
it to draw centered vertical lines with a height corresponding to the distance.

And voila ! With some additional simple math we look into a texture file, plop
down some pixels of the appropriate colors and you got a wall (wow)

That way of rendering 3D worlds brings limitations, the biggest one is that your world
must be full of cubes. The DDA needs integers to do its comparison magic therefore a uniform
scale is not negotiable. 
It can be improved but we're going to be expelled in 3 weeks so we can't be bothered (wow).

# Instructions :

**make**		>> builds the mandatory part

**make bonus**	>> builds the bonus part

Both executables share the same name so remember to **make fclean** before rebuilding !
It needs the minilibx and libft to work but they're included and get built with make

to execute : **./cub3D path/to/map.cub**

**Maps for the bonus part are in maps/bonus/**

In the **config.h** you'll find multiple defines for changing keybinds, window resolution
and other settings.

There's also usable maps in the maps/ maps_bonus/ folders and textures in the tiles/ folder.

# Ressources :

https://lodev.org/cgtutor/ 

an amazing collections of blog articles covering everything you could ever need
for this project (and more). Mostly in CPP but explanations and diagrams makes it
easy to port to C.


https://www.geeksforgeeks.org/computer-graphics/dda-line-generation-algorithm-computer-graphics/

https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)

Main ressources used to understand apply and debug the DDA algo in our project.


https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

https://medium.com/@jalal92/understanding-the-minilibx-a-practical-dive-into-x-window-programming-api-in-c-cb8a6f72bec3

Minilibx docs, probably the most obscure part of this project. Doc is sparse and doesn't
cover everything there is to know but what can you do.


https://flakdeau19.itch.io/high-resolution-pixel-art-textures?download

Cool free texture pack ✨

**About AI use** : I asked it to fix my makefile once and it didn't work :/

# TLDR 

make bonus
./cub3d maps/bonus/01.cub

have fun !