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
* The project reads data from a file and process the data, or the program writes data to a file. (see line 40 in [renderer.cpp](https://github.com/lian999111/CppND-Capstone-Snake-Game/blob/master/src/renderer.cpp))

| _Done_  	| _Criteria_                                                                                     	| _Meets Specifications_                                                                                                   	| 
|:-------:	|:-----------------------------------------------------------------------------------------------	|:-------------------------------------------------------------------------------------------------------------------------	|
| &#9745; 	| The project demonstrates an understanding of C++ functions and control structures.             	| A variety of control structures are used in the project.<br><br>The project code is clearly organized into functions.     | 
| &#9745; 	| The project reads data from a file and process the data, or the program writes data to a file. 	| The project reads data from an external file or writes data to a file as part of the necessary operation of the program. (see line 40) 	|
| &#9745; 	| The project accepts user input and processes the input.                                        	| The project accepts input from a user as part of the necessary operation of the program.                                 	| 


### Object Oriented Programming

| _Done_  	| _Criteria_                                                                       	| _Meets Specifications_                                                                                                                                                                       	| 
|:-------:	|:---------------------------------------------------------------------------------	|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	|
| &#9745; 	| The project uses Object Oriented Programming techniques.                         	| The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.                                                                       	|
| &#9745; 	| Classes use appropriate access specifiers for class members.                     	| All class data members are explicitly specified as public, protected, or private.                                                                                                            	| 
| &#9745; 	| Class constructors utilize member initialization lists.                          	| All class members that are set to argument values are initialized through member initialization lists.                                                                                       	|
| &#9745; 	| Classes abstract implementation details from their interfaces.                   	| All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.      	| 
| &#9745; 	| Classes encapsulate behavior.                                                    	| Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.                        	| 
| &#9745; 	| Classes follow an appropriate inheritance hierarchy.                             	| Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified. 	|
| &#9744; 	| Overloaded functions allow the same function to operate on different parameters. 	| One function is overloaded with different signatures for the same function name.                                                                                                             	|                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
| &#9744; 	| Derived class functions override virtual base class functions.                   	| One member function in an inherited class overrides a virtual base class member function.                                                                                                    	|
| &#9744; 	| Templates generalize functions in the project.                                   	| One function is declared with a template that allows it to accept a generic parameter.                                                                                                       	| 


### Memory Management

| _Done_  	| _Criteria_                                                                       	| _Meets Specifications_                                                                                                                                                                       	| 
|:-------:	|:---------------------------------------------------------------------------------	|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	|
| &#9745; 	| The project makes use of references in function declarations.                             	| At least two variables are defined as references, or two functions use pass-by-reference in the project code.  | 
| &#9745; 	| The project uses destructors appropriately.                                               	| At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.| 
| &#9744; 	| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. 	| The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction. 	|
 | &#9744; 	| The project follows the Rule of 5.                                                        	| For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.                                         	| 
 | &#9744; 	| The project uses move semantics to move data, instead of copying it, where possible.      	| For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object. | 
 | &#9744; 	| The project uses smart pointers instead of raw pointers.                                  	| The project uses at least one smart pointer:  `unique_ptr`,  `shared_ptr`, or  `weak_ptr`. The project does not use raw pointers.| 


### Concurrency

| _Done_  	| _Criteria_                                                                       	| _Meets Specifications_                                                                                                                                                                       	| 
|:-------:	|:---------------------------------------------------------------------------------	|:----------------------------------------------------------------------------------------------------------------- |
| &#9744;  | The project uses multi-threading.             	| The project uses multiple threads in the execution.                                                                                                 	|
| &#9744;  | A promise and future is used in the project. 	| A promise and future is used to pass data from a worker thread to a parent thread in the project code.                                              	|
| &#9744;  | A mutex or lock is used in the project.      	| A mutex or lock (e.g.  `std::lock_guard` or `std::unique_lock`) is used to protect data that is shared across multiple threads in the project code. 	|
| &#9744;  | A condition variable is used in the project. 	| A  `std::condition_variable` is used in the project code to synchronize thread execution.                                                           	|
