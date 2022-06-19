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

#include "libswsdm.h"

std::vector<sws::Data*> sws::DM::data;
sws::Data::Data(const std::string &k, const std::string &v) { set_key(k); set_value(v); }
void sws::Data::set_key(const std::string &k) { key = k; }
void sws::Data::set_value(const std::string &v) { value = v; }

int sws::DM::vtoi(const int &i) { return std::stoi(data[i]->value, NULL); }
long sws::DM::vtol(const int &i) { return std::stol(data[i]->value, NULL); }
unsigned int sws::DM::vtou(const int &i) { return std::stoul(data[i]->value, NULL); }
float sws::DM::vtof(const int &i) { return std::stof(data[i]->value, NULL); }
double sws::DM::vtod(const int &i) { return std::stod(data[i]->value, NULL); }

sws::DM::DM() { load_data("init"); }

void sws::DM::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2) {
    size_t start; size_t end = 0;
    while ((start = s.find_first_not_of(d, end)) != std::string::npos) {
        end = s.find(d, start);
        end > 32 ? o2.push_back(s.substr(start, end - start)) : o1.push_back(s.substr(start, end - start));
    }
}

void sws::DM::add_data(const std::string &k, const std::string &v) {
    Data* f = new Data(k, v); data.push_back(f);
} 

void sws::DM::update_data(const std::string &k, const std::string &v) {
    std::transform(data.begin(), data.end(), data.begin(),
            [k,v](auto& f){ if (f->key == k) f->set_value(v); return f; });
}

void sws::DM::update_data(const int &i, const std::string &v) { data[i]->set_value(v); }

std::string sws::DM::view_data() {
    std::string fs;
    for (auto& f : data) fs.append(f->key + "|" + f->value + "\n");
    return fs;
}

void sws::DM::load_data(const std::string &sf) {
    std::ifstream file("saves/" + sf + ".swsd");
    try {
        std::string line;
        while(std::getline(file, line)) {
            if (line[0] == '#') continue;
            std::vector<std::string> keys;
            std::vector<std::string> values;
            parse(line, '|', keys, values);
            for (auto& k : keys) {  
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

void sws::DM::save_data(const std::string &sf) {
    std::ofstream saveFile("saves/" + sf + ".swsd");
    saveFile << view_data(); saveFile.close();
}

// Uncomment and compile for basic testing
/*int main() {
    int t1, t2, t3;
    sws::DM();
    sws::DM::load_data("test");
    int x = sws::DM::vtoi(0);
    std::cout << "CAST TO INT: " << x << std::endl;
    std::cout << sws::DM::view_data();
    std::cin >> t1; std::cin >> t2; std::cin >> t3;
    // UPDATE BY KEY
    sws::DM::update_data("FLAG_A", std::to_string(t1));
    // UPDATE BY INDEX
    sws::DM::update_data(1, std::to_string(t2));
    sws::DM::update_data("FLAG_C", std::to_string(t3));
    sws::DM::save_data("test");
    return 0;
}*/