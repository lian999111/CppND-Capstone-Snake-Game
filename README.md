# CPPND: Capstone 2-Player Snake Game

This project extends the [C++ Nanodegree Capstone Project](https://github.com/udacity/CppND-Capstone-Snake-Game). It is a 2-player snake game where 2 players compete to get higher scores without bumping into themselves or each other. The blue snake shall go after the blue food and the orange snake shall go after the orange food.

## Keyboard Control Guide:
| Key             | Action                                  | 
| :-------------: |:----------------------------------------|
| Up              | 1P goes up                              |
| Down            | 1P goes down                            |
| Left            | 1P goes left                            |
| Right           | 1P goes right                           | 
| W               | 2P goes up                              |
| S               | 2P goes down                            |
| A               | 2P goes left                            |
| D               | 2P goes right                           | 
| SPACE           | Pause the game                          |


<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2 TTF >= 2.0
  * All installation instructions can be found [here](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
    * e.g. sudo apt-get install libsdl2-dev
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Project Class Structure
### Snake: 
Maintains the head and body of the snake. The moving and status checking of the snake are separated into different methods to decouple the behaviors. It uses std::mutex to be thread-safe since different threads in Game2P may be updating and checking the status of the snake at the same time. 

### Controller: 
Rresponsible for receiving user's input and change the state of the game accrodingly. When the game is in pause mode, it waits for only SPACE to be pressed then continues the game while other key strokes are ignored to avoid state changine during a pause.

### Renderer: 
Responsible for rendering the state of the game. The rendering of the "Pause" message is achieved using the [SDL2_TTF](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html) library.

### Game2P: 
Controls the flow of the game and maintains the 2 snakes and their foods. The "Run()" method runs the game loop, which involves __Input__, __Update__, and __Render__ steps. The __Update__ step first moves the 2 snakes using 2 tasks, then check the necessary updates incurred by the movements again using 2 tasks. 

## Project Specification

## Rubrics Fulfilled 
### Loops, Functions, I/O
* The project demonstrates an understanding of C++ functions and control structures.
* The project reads data from a file and process the data, or the program writes data to a file. (see [renderer.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/renderer.cpp#L40-L44))
* The project accepts user input and processes the input. (see [controller.h](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/controller.h), [controller.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/controller.cpp))

### Object Oriented Programming
* The project uses Object Oriented Programming techniques.
* Classes use appropriate access specifiers for class members.
* Class constructors utilize member initialization lists. (see [renderer.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/renderer.cpp#L8-L9), [snake.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/snake.h#L13-L17), [game2p.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/game2p.cpp#L8-L9))
* Classes abstract implementation details from their interfaces.
* Classes encapsulate behavior.                                                                         	| 

### Memory Management
* The project makes use of references in function declarations. (e.g. [snake.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/snake.cpp#L25), [controller.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/controller.cpp#L13-L15))
* The project uses destructors appropriately. (e.g. [renderer.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/renderer.cpp#L55-L62))
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. (see [game2p.h](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/game2p.h#L22-L23), [game2p.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/game2p.cpp#L11-L15))
* The project uses smart pointers instead of raw pointers. (see [game2p.h](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/game2p.h#L22-L23), [game2p.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/game2p.cpp#L11-L15))

### Concurrency

