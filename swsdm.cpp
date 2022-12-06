 /* libswsdm - A simple and lightweight library for saving and loading game data
  * Copyright (C) 2020-2022 Spencer W. Smith <spencerwayne310@gmail.com>
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

#include "swsdm.h"

std::unordered_map<std::string, std::string> sws::DM::data;

int sws::DM::vtoi(const std::string &k) { return std::stoi(data[k], NULL); }
long sws::DM::vtol(const std::string &k) { return std::stol(data[k], NULL); }
unsigned int sws::DM::vtou(const std::string &k) { return std::stoul(data[k], NULL); }
float sws::DM::vtof(const std::string &k) { return std::stof(data[k], NULL); }
double sws::DM::vtod(const std::string &k) { return std::stod(data[k], NULL); }

sws::DM::DM() { load_init(); }

// Maybe more efficient if it returned a pair?
void parse(std::string const& s, const char d, std::string& o1, std::string& o2) {
    size_t start; size_t end = 0;
    while ((start = s.find_first_not_of(d, end)) != std::string::npos) {
        end = s.find(d, start);
        end > 32 ? o2.assign(s.substr(start, end - start)) : o1.assign(s.substr(start, end - start));
    }
}

std::string ltrim(const std::string &s) {
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

void sws::DM::update_data(const std::string &k, const std::string &v) { data.insert_or_assign(k, v); }

void sws::DM::load_init() {
    std::string prefix;
    std::string key;
    std::string value;
    std::ifstream file("saves/init.swsd");
    try {
        std::string line;
        while(std::getline(file, line)) {
            if (ltrim(line)[0] == '#' || line.find("END") != std::string::npos) continue;
            if (line.find("DEF") != std::string::npos) {
                std::string d;
                std::string p;
                parse(line, ' ', d, p);
                prefix = p;
                continue;
            }
            parse(ltrim(line), '=', key, value);
            update_data(prefix + key, value);
        }
    }
    catch(const std::exception& e) { std::cerr << "SAVE FILE CORRUPTED" << '\n'; }
    file.close();
}

void sws::DM::load_data(const std::string &sf) {
    std::ifstream file("saves/" + sf + ".swsd");
    try {
        std::string line;
        while(std::getline(file, line)) {
            if (line[0] == '#') continue;
            std::string k;
            std::string v;
            parse(line, '=', k, v);
            update_data(k, v);
        }
    }
    catch(const std::exception& e) { std::cerr << "SAVE FILE CORRUPTED" << '\n'; }
    file.close();
}

void sws::DM::save_data(const std::string &sf) {
    std::ofstream saveFile("saves/" + sf + ".swsd");
    for (const std::pair<const std::string, std::string>& d : data) {
        saveFile << d.first << "=" << d.second << std::endl;
    }
}

// Uncomment and compile for basic testing
/*int main() {
    int t1, t2, t3;
    sws::DM();
    sws::DM::load_data("test");
    //int x = sws::DM::vtoi("FLAG_A");
    //std::cout << "CAST TO INT: " << x << std::endl;
    for (const std::pair<const std::string, std::string>& d: sws::DM::data)
        std::cout << d.first << "=" << d.second << std::endl; 
    std::cin >> t1; std::cin >> t2; std::cin >> t3;
    
    sws::DM::update_data("FLAG:A", std::to_string(t1));
    sws::DM::update_data("FLAG:B", std::to_string(t2));
    sws::DM::update_data("FLAG:C", std::to_string(t3));
    sws::DM::save_data("test");
    return 0;
}*/
