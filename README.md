# libswsdm v1.0.0
## Developed by Spencer W. Smith (spencerwayne310@gmail.com)
### Last updated 6 December 2022

*libswsdm* is a very simple scripting language designed primarily for saving and loading game data. This implementation uses only standard C++17 and is therefore highly portable. By default this project is compiled using clang, however you can also use gcc if you prefer.

Implementations in other languages are currently in the works.

## Syntax
*swsd* scripts are written to a special file known as *init.swsd*, which will be used to initialize the game data. The structure of *init.swsd* is as follows:

```
# COMMENT
DEF FLAG:
    A=0
    B=0
    C=0
END FLAG
```

The DEF line defines a prefix, which will be attached to each name within the definition block. These are the data keys, and anything after an assignment operator (=) will be a data value. The definition block ends with the END line.

Comments can be added to *init.swsd* files using the hashtag character (#). These will be ignored by the load function and will not be written to the generated save file.

Save files generated will contain one key/value pair per line, and there must be no spaces between the parameters and assignment operator. For the example above, the generated save file would appear as:

```
FLAG:C=0
FLAG:B=0
FLAG:A=0
```

## Changelog

### 1.0.0

- Developed a more formal scripting language for initialization files.
- Replaced pipe operator (|) with a more traditional assignment operator (=).
- Removed `sws::DM::parse()` from the struct, instead defined as a separate function.

### 0.9.0

- Removed `sws::Data` struct.
- Replaced `std::vector` with `std::unordered_map` for improved performance.
- Removed `sws::DM::add_data()` due to redundancy.
- Modified `sws::DM::parse()` parameters.

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

*libswsdm* is interpreted by the function `sws::DM::parse(args)`. This function splits the key/value pairs in the *.swsd* file into `std::string` objects, which are then iterated through to populate the `std::unordered_map`.

The game is saved by calling `sws::DM::save_data(const std::string &sf)`, which creates a file with the name *sf.swsd* in the *saves* folder in the game directory containing the current value of every data in the game. This file can then be read and loaded into the game by calling `sws::DM::load_data(const std::string &sf)` (the *saves/* directory and *.swsd* file extension are automatically applied and therefore should not be included in `sf`). Note that any comments in your *init.swsd* file will not be included in the save file created by the save function.

As an interesting quirk of the recent change to `std::unordered_map`, the save files created list flags in the reverse order that they were set in the *saves/init.swsd* file. This does not have any impact on loading data.

## Glossary
`std::unordered_map<std::string, std::string> sws::DM::data` - Unordered map containing all the key/value pairs representing game data.

`void sws::DM::DM()` - This function should be the very first thing you call in the main method of your game. Initializes all game data. 

`int sws::DM::vtoi(const std::string &k)` - Static function that casts `sws::DM::data[k]` value to int. 

`long sws::DM::vtol(const std::string &k)` - Static function that casts `sws::DM::data[k]` value to long. 

`unsigned int sws::DM::vtou(const std::string &k)` - Static function that casts `sws::DM::data[k]` value to unsigned int. 

`float sws::DM::vtof(const std::string &k)` - Static function that casts `sws::DM::data[k]` value to float. 

`double sws::DM::vtod(const std::string &k)` - Static function that casts `sws::DM::data[k]` value to double. 

`void sws::DM::update_data(const int &k, const std::string &v)` - This function allows you to update an individual data object's value by key.

`void sws::DM::load_init()` - This function is used by the constructor to load in the initial file.

`void sws::DM::load_data(const std::string &sf)` - This function loads the file *saves/sf.swsd* into the `std::ifstream file` object, which is then iterated through line by line. `sws::DM::parse(args)` is called on every line, and then the resulting vectors are iterated through to either `sws::DM::add_data(args)` if `sf` is equal to `"init"`; otherwise, `sws::DM::update_data(args)` is called instead. 

`void sws::DM::save_data(const std::string &sf)` - This function loads the file *saves/sf.swsd* into the `std::ofstream file` object, creating it if it does not already exist and then prints the key/value pairs from `sws::DM::data` to the file.
