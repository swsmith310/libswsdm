# libswsdm v0.7.0
## Developed by Spencer Smith (spencerwayne310@gmail.com)
### Last updated 9 October 2022

*libswsdm* is a very simple specification designed primarily for saving and loading game data. The project uses only standard C++17 and is therefore highly portable. By default this project is compiled using clang, however you can also use gcc if you prefer.

## Syntax
The structure of a *.swsd* file is as follows:

```
# COMMENT
FLAG_A|0
FLAG_B|0
FLAG_C|0
```

The pipe operator (|) takes two parameters, a data key on the left, and a data value on the right. Data keys should be kept at a maximum of 16 characters and must not exceed 32 characters. Data values can be any type, as they will be stored as a `std::string` variable in the actual data object, meaning that it's up to you to typecast values when applying them to variables in the C++ code. As of version 0.5.0 a collection of static methods are provided for casting basic numeric types (see glossary for more information).

Comments can be added to *.swsd* files using the hashtag character (#).

There must be only one key/value pair per line, and there must be no spaces between the parameters and pipe. 

## Changelog

### 0.8.0

- Added build script.
- Switched to clang as primary compiler as it produces smaller optimized shared library.
- Removed the more bloated version of `sws::DM::update_data`

### 0.7.0

- Added STL memory header to improve performance.
- Changed `sws::DM::data` vector to `std::unique_ptr<sws::Data>`type.
- Removed `sws::DM::view_data()` in favor of operator overloading.

### 0.6.0

- Added STL algorithm header to improve performance.
- Added second form of `sws::DM::update_data` to update by index.
- Moved value casting functions to `sws::DM` for cleaner code.

### 0.5.0

- Changed name once again.
- Changed namespace from `sc::` to `sws::`.
- Changed file extension to *.swsd*.
- Changed `sws::Flag` to `sws::Data`.
- Added comments.
- Added functions for casting data values to numeric types.

### 0.4.0

- Changed type of `sws::DM::data` from `std::list` to `std::vector` to allow more direct access to elements rather than having to constantly iterate to populate fields.

### 0.3.0

- Changed name to SCDM to reflect the project's shift away from game data to more general program data management.

### 0.2.0

- Originally *.swsd* files would end with the line "ENDFLAGS", however this was decided to be redundant and thus removed from this version of the specification.

## Usage Summary
*libswsdm* is used to initialize, save, and load all data in the program. The data for a fresh game is written in the file *saves/init.swsd*, which should be located in your game's root directory. This file is loaded in the `sws::DM::init()` constructor function and used to instantiate all of the data. As such, it should be the first function called in `main`.

*libswsdm* is interpreted by the function `sws::DM::parse(args)`. This function splits the key/value pairs in the *.swsd* file into two `std::vector<std::string>` objects, which are then iterated through, generating the `sws::Data` objects into the game.

The game is saved by calling `sws::DM::save_data(const std::string &sf)`, which creates a file with the name *sf.swsd* in the *saves* folder in the game directory containing the current value of every data in the game. This file can then be read and loaded into the game by calling `sws::DM::load_data(const std::string &sf)` (the *saves/* directory and *.swsd* file extension are automatically applied and therefore should not be included in `sf`). Note that any comments in your *init.swsd* file will not be included in the save file created by the save function.

## Glossary
`struct sws::Data` - Structure which defines all of the in-game data. Has two member variables, `std::string key` and `std::string value`, as well as setter functions for each.

`struct sws::DM` - Static structure which defines objects and functions for saving, loading, and managing game data. 

`std::vector<std::unique_ptr<sws::Data>> data` - A vector object that stores all of the in-game data as unique pointers.

`void sws::DM::DM()` - This function should be the very first thing you call in the main method of your game. This function calls `sws::DM::load_data(const std::string &sf)` on *init.swsd*, populating the `data` object and initializing all of the data in the game.

`int sws::DM::vtoi(const int &i)` - Static function that gets a data object by index `i` and casts that object's value to int. 

`long sws::DM::vtol(const int &i)` - Static function that gets a data object by index `i` and casts that object's value to long. 

`unsigned int sws::DM::vtou(const int &i)` - Static function that gets a data object by index `i` and casts that object's value to unsigned int. 

`float sws::DM::vtof(const int &i)` - Static function that gets a data object by index `i` and casts that object's value to float. 

`double sws::DM::vtod(const int &i)` - Static function that gets a data object by index `i` and casts that object's value to double. 

`void sws::DM::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)` - The function that interprets *.swsd* files. Uses a simple string splitting algorithm to separate data keys and values into separate `std::vector<std::string>` variables which are then iterated through to add or manipulate data. 

`void sws::DM::add_data(const std::string &k, const std::string &v)` - This function creates a `new std::unique_ptr<sws::Data>` and pushes it onto the vector.

`void sws::DM::update_data(const int &i, const std::string &v)` - This function allows you to update an individual data object's value by index. This version of the function should be preferred in most cases.

`void sws::DM::load_data(const std::string &sf)` - This function loads the file *saves/sf.swsd* into the `std::ifstream file` object, which is then iterated through line by line. `sws::DM::parse(args)` is called on every line, and then the resulting vectors are iterated through to either `sws::DM::add_data(args)` if `sf` is equal to `"init"`; otherwise, `sws::DM::update_data(args)` is called instead. 

`void sws::DM::save_data(const std::string &sf)` - This function loads the file *saves/sf.swsd* into the `std::ofstream file` object, creating it if it does not already exist, and then uses the overloaded `<<` operator to write key value pairs to the script in the proper format.
