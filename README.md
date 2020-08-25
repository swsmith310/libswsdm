# SCFS C++ Edition v1.2.0
## Developed by Spencer Smith (spenny@geniuspiece.com)
### Last updated 25 August 2020

*SCFS* is a very simple specification for saving and managing game data. 

## Syntax
The structure of an *SCFS* file is as follows:

```
FLAG_A|0
FLAG_B|0
FLAG_C|0
```

The pipe operator (|) takes two parameters, a flag key on the left, and a flag value on the right. Flag keys should be kept at a maximum of 16 characters and must not exceed 32 characters. Flag values can be any type, as they will be stored as a `std::string` variable in the actual flag object, meaning that it's up to you to typecast values when applying them to variables in the C++ code. 

There must be only one key/value pair per line, and there must be no spaces between the parameters and pipe. 

## Changes from previous version

Originally *.scfs* files would end with the line "ENDFLAGS", however this was decided to be redundant and thus removed from this version of the specification.

## Usage Summary
*SCFS* is used to initialize, save, and load all data in the game. The data for a fresh game is saved in the file *baseFlags.scfs*, located by default in the project's root directory. This file is loaded in the `sc::FS::init()` constructor function and used to instantiate all of the flags. As such, it should be the first function called in `main`.

*SCFS* is interpreted by the function `sc::FS::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)`. This function splits the key/value pairs in the *SCFS* script into two `std::vector<std::string>` objects, which are then iterated through, generating the `sc::Flag` objects into the game.

The game is saved by calling `sc::FS::save_flags(std::string sf)`, which creates a file with the name *sf.scfs* in the *saves* folder in the game directory containing the current value of every flag in the game. This file can then be read and loaded into the game by calling `sc::FS::load_flags(std::string sf)`, where `sf` is the name of the file without the *.scfs* suffix. 

## Glossary
`struct sc::Flag` - Structure which defines all of the in-game flags. Has two member variables, `std::string key` and `std::string value`, as well as setter functions for each.

`struct sc::FS` - Static structure which defines objects and functions for saving, loading, and managing game data. 

`std::list<sc::Flag*> flags` - A list object that stores all of the in-game flags.

`void sc::FS::FS()` - This function should be the very first thing you call in the main method of your game. This function calls `sc::FS::load_flags(std::string sf)` on *baseFlags.scfs*, populating the `flags` object and initializing all of the data in the game.

`void sc::FS::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)` - The function that interprets *FS* scripts. Uses a modified string splitting algorithm to separate flag keys and values into separate `std::vector<std::string>` variables which are then iterated through to add or manipulate flags. 

`void sc::FS::add_flag(std::string k, std::string v)` - This function creates a `new sc::Flag(std::string k, std::string v)` object `f` and then calls `flags.push_back(f)`.

`void sc::FS::update_flag(std::string k, std::string v)` - This function modifies the value of `FS::Flag` objects by iterating through the `flags` list to find the key that matches `k` and changing the value of that flag to `v`. If the flag key cannot be found, the function will fail. 

`std::string sc::FS::view_flags()` - This function returns the entire `flags` list as a `std::string` object. 

`void sc::FS::load_flags(std::string sf)` - This function loads the file *sf.scfs* into the `std::ifstream file` object, which is then iterated through line by line. `sc::FS::parse(args)` is called on every line, and then the resulting vectors are iterated through to either `sc::FS::add_flags(args)` if `sf` is equal to `"baseFlags"`; otherwise, `sc::FS::update_flags(args)` is called instead. 

`void sc::FS::save_flags(std::string sf)` - This function loads the file *sf.scfs* into the `std::ofstream file` object, creating it if it does not already exist, and then writes the return value of `sc::FS::view_flags()` followed by the `ENDFLAGS` keyword to the file.
