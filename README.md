# COLLIDE
## Overview
This repository contains a custom game engine developed using SDL2 and a robust physics framework with broad-phase collision detection. The engine includes a dynamic neon blaster game, which features randomly generated objects with varying health levels and a player-controlled gun for an engaging and challenging gameplay experience. This project was undertaken as part of the Summer of Code at IIT Bombay.

## Features
### Game Engine: 
The custom game engine is built using SDL2, providing a foundation for creating 2D games with efficient rendering and input handling.

### Physics Framework:
The physics framework includes a broad phase collision detection algorithm and efficient detection and resolution algorithms. This ensures accurate collision detection and smooth interactions between objects and the player's projectiles.

### Dynamic Neon Blaster Game: 
The game showcases stunning graphics and an innovative gameplay concept. Players control a neon blaster and face waves of randomly generated objects with various health levels. The objective is to survive and achieve the highest score possible.

## SDL Installation 
- ### Linux 
    ``` 
    sudo apt-get install libsdl2-2.0-0 
    sudo apt-get install libsdl2-dev 
    ```
- ### Mac
    #### Install the .dmg binary from https://github.com/libsdl-org/SDL/releases/tag/release-2.26.5
    #### As told in Readme.txt, copy the folder ```SDL2.framwork``` into ```/Library/Frameworks```
- ### Windows
    #### Install the mingw zip file from https://github.com/libsdl-org/SDL/releases/tag/release-2.26.5
    #### unzip it and copy include and lib folders from x86 folder into the parent folder of this repository
    #### Copy the SDL2.dll file from bin folder into the code folder
## Running the code 
> Go into code folder and type ```make``` on terminal
> Now after entering ```make```, enter the ```./run```, and now you can see that game has been rendered on your screen.
## Controls of the game
#### After the screen has been rendered, the game automatically starts after 3 seconds.
#### The random object starts generating.
#### There are two random objects of different health/same health at a time. 
#### You need to release a bullet from the lower bar gun to destroy an object.
#### Press space to release the bullet, after pressing the gun release two bullets at a time and each bullet decreases 1 health of the object.
#### You are able to move gun left or right by left and right arrow keys respectively.

## References for SDL 
- [SDL Wiki](https://wiki.libsdl.org/SDL2/FrontPage)
- [API reference](https://wiki.libsdl.org/SDL2/CategoryAPI)
- [A simple game tutorial](https://www.parallelrealities.co.uk/tutorials/#shooter)
## Thank you for giving your valuable time here

