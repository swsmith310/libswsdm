 /* swsDM - A simple standard for managing game data
  * Copyright (C) 2020-2022 Spencer Smith <spencerwayne310@gmail.com>
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

#include "swsDM.h"

std::vector<sws::Data*> sws::DM::data;

sws::Data::Data(const std::string &k, const std::string &v)
{
    set_key(k);
    set_value(v);
}

void sws::Data::set_key(const std::string &k) { key = k; }
void sws::Data::set_value(const std::string &v) { value = v; }

int sws::Data::vtoi() { return std::stoi(value, NULL); }
long sws::Data::vtol() { return std::stol(value, NULL); }
unsigned int sws::Data::vtou() { return std::stoul(value, NULL); }
float sws::Data::vtof() { return std::stof(value, NULL); }
double sws::Data::vtod() { return std::stod(value, NULL); }

sws::DM::DM()
{
    load_data("init");
}

void sws::DM::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)
{
    size_t start;
    size_t end = 0;

    while ((start = s.find_first_not_of(d, end)) != std::string::npos)
    {
        end = s.find(d, start);
        end > 32 ? o2.push_back(s.substr(start, end - start)) : o1.push_back(s.substr(start, end - start));
    }
}

void sws::DM::add_data(const std::string &k, const std::string &v)
{
    Data* f = new Data(k, v);
    data.push_back(f);
} 

void sws::DM::update_data(const std::string &k, const std::string &v)
{
    for (auto& f : data)
    {
        if (f->key == k)
        {
            f->set_value(v);
        }
    }
}

std::string sws::DM::view_data()
{
    std::string fs;
    for (auto& f : data) fs.append(f->key + "|" + f->value + "\n");
    return fs;
}

void sws::DM::load_data(const std::string &sf)
{
    std::ifstream file("saves/" + sf + ".swsd");
    try
    {
        std::string line;
        while(std::getline(file, line))
        {
            if (line[0] == '#') continue;
            std::vector<std::string> keys;
            std::vector<std::string> values;
            parse(line, '|', keys, values);
            for (auto& k : keys)
            {  
                std::string value;
                for (auto& v: values) value = v;
                if (sf == "init") add_data(k, value);
                else              update_data(k, value);
            }
        }
    }
    catch(const std::exception& e) { std::cerr << "SAVE FILE CORRUPTED" << '\n'; }
    file.close();
}

void sws::DM::save_data(const std::string &sf)
{
    std::ofstream saveFile("saves/" + sf + ".swsd");
    saveFile << view_data();
    saveFile.close();
}

// Uncomment and compile for basic testing
/*int main()
{
    int t1, t2, t3;
    sws::DM();
    sws::DM::load_data("test");
    int x = sws::DM::data[0]->vtoi();
    std::cout << "CAST TO INT: " << x << std::endl;
    std::cout << sws::DM::view_data();
    std::cin >> t1;
    std::cin >> t2;
    std::cin >> t3;
    sws::DM::update_data("FLAG_A", std::to_string(t1));
    sws::DM::update_data("FLAG_B", std::to_string(t2));
    sws::DM::update_data("FLAG_C", std::to_string(t3));
    sws::DM::save_data("test");
    return 0;
}*/
