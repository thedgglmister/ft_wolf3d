# ft_wolf3d
The 3rd project of the 42us graphics branch

### --Project Description--

ft_wolf3d is Wolfenstein3D gaming engine that implements a ray-casting algorithm. Multiple wall/ceiling/floor textures are supported, as well as unlimited sprites and object collision detection. To facilitate quick frame rendering, I've employed both multithreading and principle of efficient calculating.

#### --Coding Style--

At 42, we follow a strict norm in order to teach us to follow style guides. This norm also prevents us from using many built-in functions. In this project, we are limited to using a barebones graphic library called minilibx. This library limits the functionality to creating windows, handling input hooks, and coloring specific pixels.

The allowed functions are : ```exit, malloc, free, and the functions of minilibx and math.h```.

The Project is written in C and in accordance with "The Norm".

#### --The Norm--

    • Functions must not exceed 25 lines
    • No more than 5 function-definitions in a .c file
    • One instruction per line
    • One single variable declaration per line; cannot stick declaration and initialisation on the same line
    • No more than 5 variables per bloc
    • No more than 4 parameters per function
    • Forbidden functions are: [for] [do ... while] [switch] [case] [goto]
    
### --Demo Instructions (Mac OSX Sierra)--

    • Open Terminal and run the following commands:
    • git clone https://github.com/thedigglemister/ft_wolf3d ft_wolf3d
    • cd ft_wolf3d
    • make && ./wolf3d "garden"
    • Additionally, you might try "room" in place of "garden"

#### --User Controls--

    • WASP keys are used to move forward, backwards, and sideways
    • Left and Right arrow keys are used to rotate 
    • Space is used to jump
    • C is used to crouch
    • esc to exit
    
<img src="/images/garden.png" width="800">
<img src="/images/buddha.png" width="800">
<img src="/images/bulbasaur.png" width="800">
<img src="/images/room.png" width="800">
