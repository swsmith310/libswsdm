# swsDM C++ Edition v0.5.0
## Developed by Spencer Smith (spencerwayne310@gmail.com)
### Last updated 18 June 2022

*swsDM* is a very simple specification for saving and managing program data. 

## Syntax
The structure of a *.swsd* file is as follows:

```
# COMMENT
FLAG_A|0
FLAG_B|0
FLAG_C|0
```

The pipe operator (|) takes two parameters, a data key on the left, and a data value on the right. Data keys should be kept at a maximum of 16 characters and must not exceed 32 characters. Data values can be any type, as they will be stored as a `std::string` variable in the actual data object, meaning that it's up to you to typecast values when applying them to variables in the C++ code. As of version 0.5.0 a collection of methods are provided for casting basic numeric types (see glossary for more information).

Comments can be added to *.swsd* files using the hashtag character (#).

There must be only one key/value pair per line, and there must be no spaces between the parameters and pipe. 

## Changelog

### 0.5.0

- Changed name once again.
- Changed namespace from `sc::` to `sws::`.
- Changed file extension to *.swsd*.
- Changed `sws::Flag` to `sws::Data`.
- Added comments.
- Added functions for casting data values to numeric types.
- Changed parameters to constant references where necessary.

### 0.4.0

- Changed type of `sws::DM::data` from `std::list` to `std::vector` to allow more direct access to elements rather than having to constantly iterate to populate fields.

### 0.3.0

- Changed name to SCDM to reflect the project's shift away from game data to more general program data management.

### 0.2.0

- Originally *.swsd* files would end with the line "ENDFLAGS", however this was decided to be redundant and thus removed from this version of the specification.

## Usage Summary
*swsDM* is used to initialize, save, and load all data in the program. The data for a fresh game is saved in the file *baseDatas.swsd*, located by default in the project's root directory. This file is loaded in the `sws::DM::init()` constructor function and used to instantiate all of the data. As such, it should be the first function called in `main`.

*swsDM* is interpreted by the function `sws::DM::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)`. This function splits the key/value pairs in the *swsDM* script into two `std::vector<std::string>` objects, which are then iterated through, generating the `sws::Data` objects into the game.

The game is saved by calling `sws::DM::save_data(const std::string &sf)`, which creates a file with the name *sf.swsd* in the *saves* folder in the game directory containing the current value of every data in the game. This file can then be read and loaded into the game by calling `sws::DM::load_data(const std::string &sf)`, where `sf` is the name of the file without the *.swsd* suffix. 

## Glossary
`struct sws::Data` - Structure which defines all of the in-game data. Has two member variables, `std::string key` and `std::string value`, as well as setter functions for each.

`struct sws::DM` - Static structure which defines objects and functions for saving, loading, and managing game data. 

`int sws::Data::vtoi()` - Function that casts a data object's value to int. 

`long sws::Data::vtol()` - Function that casts a data object's value to long. 

`unsigned int sws::Data::vtou()` - Function that casts a data object's value to unsigned int. 

`float sws::Data::vtof()` - Function that casts a data object's value to float. 

`double sws::Data::vtod()` - Function that casts a data object's value to double. 

`std::vector<sws::Data*> data` - A vector object that stores all of the in-game data.

`void sws::DM::DM()` - This function should be the very first thing you call in the main method of your game. This function calls `sws::DM::load_data(const std::string &sf)` on *baseDatas.swsd*, populating the `data` object and initializing all of the data in the game.

`void sws::DM::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)` - The function that interprets *swsDM* scripts. Uses a simple string splitting algorithm to separate data keys and values into separate `std::vector<std::string>` variables which are then iterated through to add or manipulate data. 

`void sws::DM::add_data(const std::string &k, const std::string &v)` - This function creates a `new sws::Data(const std::string &k, const std::string &v)` object `f` and then calls `data.push_back(f)`.

`void sws::DM::update_data(const std::string &k, const std::string &v)` - This function modifies the value of `sws::Data` objects by iterating through the `data` list to find the key that matches `k` and changing the value of that data to `v`. If the data key cannot be found, the function will fail. 

`std::string sws::DM::view_data()` - This function returns the entire `data` list as a `std::string` object. 

`void sws::DM::load_data(const std::string &sf)` - This function loads the file *sf.swsd* into the `std::ifstream file` object, which is then iterated through line by line. `sws::DM::parse(args)` is called on every line, and then the resulting vectors are iterated through to either `sws::DM::add_data(args)` if `sf` is equal to `"baseDatas"`; otherwise, `sws::DM::update_data(args)` is called instead. 

`void sws::DM::save_data(const std::string &sf)` - This function loads the file *sf.swsd* into the `std::ofstream file` object, creating it if it does not already exist, and then writes the return value of `sws::DM::view_data()` to the file. 
