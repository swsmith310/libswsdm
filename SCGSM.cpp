 /* SCGSM - A simple standard for managing game data
  * Copyright (C) 2020 Spencer Smith <spenny@geniuspiece.com>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
  */

#include "SCGSM.h"

std::list<sc::Flag*> sc::GSM::flags;

sc::Flag::Flag(std::string k, std::string v)
{
    set_key(k);
    set_value(v);
}

sc::GSM::GSM()
{
    load_flags("baseflags");
}

void sc::GSM::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)
{
    size_t start;
    size_t end = 0;

    while ((start = s.find_first_not_of(d, end)) != std::string::npos)
    {
        end = s.find(d, start);
        end > 32 ? o2.push_back(s.substr(start, end - start)) : o1.push_back(s.substr(start, end - start));
    }
}

void sc::GSM::add_flag(std::string k, std::string v)
{
    Flag* f = new Flag(k, v);
    flags.push_back(f);
} 

void sc::GSM::update_flag(std::string k, std::string v)
{
    for (auto& f : flags)
    {
        if (f->key == k)
        {
            f->set_value(v);
        }
    }
}

std::string sc::GSM::view_flags()
{
    std::string fs;
    for (auto& f : flags) fs.append(f->key + "|" + f->value + "\n");
    return fs;
}

void sc::GSM::load_flags(std::string sf)
{
    std::string line;
    std::ifstream file(sf + ".scgs");
    try
    {
        while(std::getline(file, line))
        {
            std::vector<std::string> keys;
            std::vector<std::string> values;
            parse(line, '|', keys, values);
            for (auto& k : keys)
            {  
                std::string value;
                for (auto& v : values) value = v;
                if (sf == "baseflags") add_flag(k, value);
                else                   update_flag(k, value);
            }
        }
    }
    catch(const std::exception& e) { std::cerr << "SAVE FILE CORRUPTED" << '\n'; }
    file.close();
}

void sc::GSM::save_flags(std::string sf)
{
    std::ofstream saveFile(sf + ".scgs");
    saveFile << view_flags();
    saveFile.close();
}

// Uncomment and compile for basic testing
/*int main()
{
    int t1, t2, t3;
    sc::GSM();
    sc::GSM::load_flags("test");
    std::cout << sc::GSM::view_flags();
    std::cin >> t1;
    std::cin >> t2;
    std::cin >> t3;
    sc::GSM::update_flag("FLAG_A", std::to_string(t1));
    sc::GSM::update_flag("FLAG_B", std::to_string(t2));
    sc::GSM::update_flag("FLAG_C", std::to_string(t3));
    sc::GSM::save_flags("test");
    return 0;
}*/
