# TODO: UPDATE EXAMPLE

# libswsdm v0.7.0
## Developed by Spencer Smith (spencerwayne310@gmail.com)
### Last updated 24 June 2022

*libswsdm* is a very simple specification designed primarily for saving and loading game data. The project uses only standard C++ and is therefore highly portable. 

This example is meant as a demonstration of how *libswsdm* can be used in your project. Building this example requires Raylib, which can be found at https://github.com/raysan5/raylib.git. The example also expects that the required headers and libraries are in your system's include and lib paths, respectively.

## Build

A simple build command for this example is as follows:

`g++ -std=c++17 -o example example.cpp -lraylib -lGL -lpthread -ldl -lrt -lX11 -lswsdm`
