 /* SCFS - A simple standard for managing game data
    Copyright (C) 2020 Spencer Smith

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "SCFS.h"

std::list<sc::Flag*> sc::SCFS::flags;

sc::Flag::Flag(std::string k, std::string v)
{
    setKey(k);
    setValue(v);
}

void sc::SCFS::init()
{
    loadGame("baseFlags");
}

void sc::SCFS::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)
{
    size_t start;
    size_t end = 0;

    while ((start = s.find_first_not_of(d, end)) != std::string::npos)
    {
        end = s.find(d, start);
        end > 32 ? o2.push_back(s.substr(start, end - start)) : o1.push_back(s.substr(start, end - start));
    }
}

void sc::SCFS::addFlag(std::string k, std::string v)
{
    Flag* f = new Flag(k, v);
    flags.push_back(f);
} 

void sc::SCFS::loadFlags()
{
    for (auto& f : flags)
    {
        // if (f->key == "KEY") VARIABLE = f->value;
    }
}

void sc::SCFS::updateFlag(std::string k, std::string v)
{
    for (auto& f : flags)
    {
        if (f->key == k)
        {
            f->setValue(v);
        }
    }
}

std::string sc::SCFS::viewFlags()
{
    std::string fs;
    for (auto& f : flags) fs.append(f->key + "|" + f->value + "\n");
    return fs;
}

void sc::SCFS::loadGame(std::string sf)
{
    std::string line;
    std::ifstream file(sf + ".scfs");
    try
    {
        while(std::getline(file, line))
        {
            std::vector<std::string> keys;
            std::vector<std::string> values;
            parse(line, '|', keys, values);
            for (auto& k : keys)
            {  
                if (k == "ENDFLAGS") break;
                std::string value;
                for (auto& v : values) value = v;
                if (sf == "baseFlags") addFlag(k, value);
                else                   updateFlag(k, value);
            }
        }
    }
    catch(const std::exception& e) { std::cerr << "SAVE FILE CORRUPTED" << '\n'; }
    file.close();
    loadFlags();
}

void sc::SCFS::saveGame(std::string sf)
{
    std::ofstream saveFile(sf + ".scfs");
    saveFile << viewFlags() << "ENDFLAGS";
    saveFile.close();
}

// Uncomment and compile for basic testing
/*int main()
{
    int t1, t2, t3;
    sc::SCFS::init();
    sc::SCFS::loadGame("test");
    std::cout << sc::SCFS::viewFlags();
    std::cin >> t1;
    std::cin >> t2;
    std::cin >> t3;
    sc::SCFS::updateFlag("FLAG_A", std::to_string(t1));
    sc::SCFS::updateFlag("FLAG_B", std::to_string(t2));
    sc::SCFS::updateFlag("FLAG_C", std::to_string(t3));
    sc::SCFS::saveGame("test");
    return 0;
}*/
