# SCFS v1.15
## Developed by Spencer Smith (spencerwayne310@gmail.com)
### Last updated 26 April 2020

*SCFS* is a very simple specification for saving and managing game data. Just how simple is it? Well, there is only one keyword, and only one operator.

## Syntax
The structure of an *SCFS* file is as follows:

```
FLAG_A|0
FLAG_B|0
FLAG_C|0
ENDFLAGS 
```

The pipe operator (|) takes two parameters, a flag key on the left, and a flag value on the right. Flag keys should be kept at a maximum of 16 characters and must not exceed 32 characters. Flag values can be any type, as they will be stored as a `std::string` variable in the actual flag object, meaning that it's up to you to typecast values when applying them to variables in the C++ code. 

There must be only one key/value pair per line, and there must be no spaces between the parameters and pipe. The final line of the script is `ENDFLAGS`, the keyword that tells the program to stop reading the file. Any flags written after this line will be ignored.

## Usage Summary
*SCFS* is used to initialize, save, and load all data in the game. The data for a fresh game is saved in the file *baseFlags.scfs*, located by default in the project's root directory. This file is loaded in the `sc::FS::init()` constructor function and used to instantiate all of the flags. As such, it should be the first function called in `main`.

*SCFS* is interpreted by the *SCFS Parser*, defined in the function `sc::FS::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)`. This function splits the key/value pairs in the *SCFS* script into two `std::vector<std::string>` objects, which are then iterated through, generating the `sc::Flag` objects into the game.

The game is saved by calling `sc::FS::saveGame(std::string sf)`, which creates a file with the name *sf.scfs* in the *saves* folder in the game directory containing the current value of every flag in the game. This file can then be read and loaded into the game by calling `sc::FS::loadGame(std::string sf)`, where `sf` is the name of the file without the *.scfs* suffix. 

## Glossary
`struct sc::Flag` - Structure which defines all of the in-game flags. Has two member variables, `std::string key` and `std::string value`, as well as setter functions for each.

`struct sc::FS` - Static structure which defines objects and functions for saving, loading, and managing game data. 

`std::list<sc::Flag*> flags` - A list object that stores all of the in-game flags.

`void sc::FS::FS()` - This function should be the very first thing you call in the main method of your game. This function calls `sc::FS::loadGame(std::string sf)` on *baseFlags.scfs*, populating the `flags` object and initializing all of the data in the game.

`void sc::FS::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)` - The function that interprets *FS* scripts. Uses a modified string splitting algorithm to separate flag keys and values into separate `std::vector<std::string>` variables which are then iterated through to add or manipulate flags. 

`void sc::FS::addFlag(std::string k, std::string v)` - This function creates a `new sc::Flag(std::string k, std::string v)` object `f` and then calls `flags.push_back(f)`.

`void sc::FS::loadFlags()` - This skeleton function is used to apply the values of flags to C++ variables by following a very simple structure:

`if (f.key == "KEY") VARIABLE = f.value`

Where `f` refers to the iterator over the `std::list<FS::Flag*> flags` list. This function is to be redefined by any classes that need to use it for object-specific flags, such as your player character, but the structure should always remain the same. You will never need to call this function from the `sc::FS` struct itself.

`void sc::FS::updateFlag(std::string k, std::string v)` - This function modifies the value of `FS::Flag` objects by iterating through the `flags` list to find the key that matches `k` and changing the value of that flag to `v`. If the flag key cannot be found, the function will fail. 

`std::string sc::FS::viewFlags()` - This function returns the entire `flags` list as a `std::string` object. 

`void sc::FS::loadGame(std::string sf)` - This function loads the file *sf.scfs* into the `std::ifstream file` object, which is then iterated through line by line. `sc::FS::parse(args)` is called on every line, and then the resulting vectors are iterated through to either `sc::FS::addFlags(args)` if `sf` is equal to `"baseFlags"`; otherwise, `sc::FS::updateFlags(args)` is called instead. 

`void sc::FS::saveGame(std::string sf)` - This function loads the file *sf.scfs* into the `std::ofstream file` object, creating it if it does not already exist, and then writes the return value of `sc::FS::viewFlags()` followed by the `ENDFLAGS` keyword to the file.
