# SCGSM C++ Edition v1.2.0
## Developed by Spencer Smith (spenny@geniuspiece.com)
### Last updated 25 August 2020

*SCGSM* is a very simple specification for saving and managing game data. 

## Syntax
The structure of an *SCGSM* file is as follows:

```
FLAG_A|0
FLAG_B|0
FLAG_C|0
```

The pipe operator (|) takes two parameters, a flag key on the left, and a flag value on the right. Flag keys should be kept at a maximum of 16 characters and must not exceed 32 characters. Flag values can be any type, as they will be stored as a `std::string` variable in the actual flag object, meaning that it's up to you to typecast values when applying them to variables in the C++ code. 

There must be only one key/value pair per line, and there must be no spaces between the parameters and pipe. 

## Changes from previous version

Originally *.scgs* files would end with the line "ENDFLAGS", however this was decided to be redundant and thus removed from this version of the specification.

## Usage Summary
*SCGSM* is used to initialize, save, and load all data in the game. The data for a fresh game is saved in the file *baseFlags.scgs*, located by default in the project's root directory. This file is loaded in the `sc::GSM::init()` constructor function and used to instantiate all of the flags. As such, it should be the first function called in `main`.

*SCGSM* is interpreted by the function `sc::GSM::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)`. This function splits the key/value pairs in the *SCGSM* script into two `std::vector<std::string>` objects, which are then iterated through, generating the `sc::Flag` objects into the game.

The game is saved by calling `sc::GSM::save_flags(std::string sf)`, which creates a file with the name *sf.scgs* in the *saves* folder in the game directory containing the current value of every flag in the game. This file can then be read and loaded into the game by calling `sc::GSM::load_flags(std::string sf)`, where `sf` is the name of the file without the *.scgs* suffix. 

## Glossary
`struct sc::Flag` - Structure which defines all of the in-game flags. Has two member variables, `std::string key` and `std::string value`, as well as setter functions for each.

`struct sc::GSM` - Static structure which defines objects and functions for saving, loading, and managing game data. 

`std::list<sc::Flag*> flags` - A list object that stores all of the in-game flags.

`void sc::GSM::GSM()` - This function should be the very first thing you call in the main method of your game. This function calls `sc::GSM::load_flags(std::string sf)` on *baseFlags.scgs*, populating the `flags` object and initializing all of the data in the game.

`void sc::GSM::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)` - The function that interprets *GSM* scripts. Uses a modified string splitting algorithm to separate flag keys and values into separate `std::vector<std::string>` variables which are then iterated through to add or manipulate flags. 

`void sc::GSM::add_flag(std::string k, std::string v)` - This function creates a `new sc::Flag(std::string k, std::string v)` object `f` and then calls `flags.push_back(f)`.

`void sc::GSM::update_flag(std::string k, std::string v)` - This function modifies the value of `GSM::Flag` objects by iterating through the `flags` list to find the key that matches `k` and changing the value of that flag to `v`. If the flag key cannot be found, the function will fail. 

`std::string sc::GSM::view_flags()` - This function returns the entire `flags` list as a `std::string` object. 

`void sc::GSM::load_flags(std::string sf)` - This function loads the file *sf.scgs* into the `std::ifstream file` object, which is then iterated through line by line. `sc::GSM::parse(args)` is called on every line, and then the resulting vectors are iterated through to either `sc::GSM::add_flags(args)` if `sf` is equal to `"baseFlags"`; otherwise, `sc::GSM::update_flags(args)` is called instead. 

`void sc::GSM::save_flags(std::string sf)` - This function loads the file *sf.scgs* into the `std::ofstream file` object, creating it if it does not already exist, and then writes the return value of `sc::GSM::view_flags()` followed by the `ENDFLAGS` keyword to the file.
