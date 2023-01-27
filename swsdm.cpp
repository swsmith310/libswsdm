 /* libswsdm - A simple and lightweight library for saving and loading game data
  * Copyright (C) 2020-2023 Spencer W. Smith <spencerwayne310@gmail.com>
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

std::unordered_map<std::string,sws::data*> sws::DM::data;

std::ostream& operator<<(std::ostream& os, const std::pair<const std::string,sws::data*> &d) {
   os << d.first << ":" << d.second->type << "=" << d.second->value << std::endl;
   return os;
}

void parse(std::string const& s, const char d, std::vector<std::string>& outputs, size_t numOutputs) {
    size_t start; size_t end = 0; size_t i = 0;
    while ((start = s.find_first_not_of(d, end)) != std::string::npos && i < numOutputs) {
        end = s.find(d, start);
        outputs.emplace_back(s.substr(start, end - start));
        ++i;
    }
}

std::string ltrim(const std::string &s) {
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

sws::INT::INT(int i) {
    this->i = i;
}

auto sws::INT::get(char v) { return i; }

sws::FLT::FLT(float f) {
    this->f = f;
}

auto sws::FLT::get(char v) { return f; }

sws::V2D::V2D(float x, float y) {
    this->x = x;
    this->y = y;
}

auto sws::V2D::get(char v) {
    switch(v) {
        case 'x':
            return x;
        case 'y':
            return y;
        default:
            return 0.0f;
    }
}

std::string sws::V2D::to_string() {
    return std::to_string(x) + "," + std::to_string(y);
}

sws::V3D::V3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

auto sws::V3D::get(char v) {
    switch(v) {
        case 'x':
            return x;
        case 'y':
            return y;
        case 'z':
            return z;
        default:
            return 0.0f;
    }
}

std::string sws::V3D::to_string() {
    return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);
}

sws::data::data(std::string value, std::string type) {
    this->value = value;
    if (type == "STR" || type == "0") {
        this->type = 0;
        // raw value is redundant for strings so just null this
        this->raw_value = nullptr; 
    }
    if (type == "INT" || type == "1") {
        this->type = 1;
        this->raw_value = new sws::INT(std::stoi(this->value, NULL));
    }
    if (type == "FLT" || type == "2") {
        this->type = 2;
        this->raw_value = new sws::FLT(std::stof(this->value, NULL));
    }
    if (type == "V2D" || type == "3") {
        this->type = 3;
        std::vector<std::string> v2;
        parse(value, ',', v2, 2);
        this->raw_value = new sws::V2D(std::stof(v2[0]), std::stof(v2[1]));
    }
    if (type == "V3D" || type == "4") {
        this->type = 4;
        std::vector<std::string> v3;
        parse(value, ',', v3, 3);
        this->raw_value = new sws::V3D(std::stof(v3[0]), std::stof(v3[1]), std::stof(v3[2]));
    }
}

sws::DM::DM() { load_init(); }

void sws::DM::update_data(const std::string &k, sws::data &v) { data.insert_or_assign(k, &v); }

void sws::DM::load_init() {
    std::string prefix;
    std::ifstream file("saves/init.swsd");
    std::string line;
    while(std::getline(file, line)) {
        std::vector<std::string> dset;
        std::vector<std::string> dkt;
        if (ltrim(line)[0] == '#' || line.find("END") != std::string::npos) continue;
        if (line.find("DEF") != std::string::npos) {
            std::vector<std::string> p;
            parse(line, ' ', p, 2);
            prefix = p[1];
            continue;
        }
        parse(ltrim(line), '=', dset, 2);
        parse(dset[0], ':', dkt, 2);
        sws::data* d = new sws::data(dset[1], dkt[1]);
        update_data(prefix + dkt[0], *d);
    }
    file.close();
}

void sws::DM::load_data(const std::string &sf) {
    std::ifstream file("saves/" + sf + ".swsd");
    std::string line;
    while(std::getline(file, line)) {
        std::vector<std::string> dset;
        std::vector<std::string> dkt;
        parse(line, '=', dset, 2);
        parse(dset[0], ':', dkt, 2);
        sws::data* d = new sws::data(dset[1], dkt[1]);
        update_data(dkt[0], *d);
    }
    file.close();
}

void sws::DM::save_data(const std::string &sf) {
    std::ofstream saveFile("saves/" + sf + ".swsd");
    for (const std::pair<const std::string, sws::data*> &d : data) {
        saveFile << d;
    }
}

sws::INT* sws::DM::get_int(const std::string &k) {
    return (sws::INT*)data[k]->raw_value;
}

sws::FLT* sws::DM::get_flt(const std::string &k) {
    return (sws::FLT*)data[k]->raw_value;
}

sws::V2D* sws::DM::get_v2d(const std::string &k) {
    return (sws::V2D*)data[k]->raw_value;
}

sws::V3D* sws::DM::get_v3d(const std::string &k) {
    return (sws::V3D*)data[k]->raw_value;
}
// Uncomment and compile for basic testing
int main() {
    int t1; float t2, t3, t4; std::string t5;
    sws::DM();
    sws::DM::load_data("test");

    sws::INT* i = sws::DM::get_int("FLAG_A");
    sws::FLT* f = sws::DM::get_flt("FLAG_B");
    sws::V2D* x = sws::DM::get_v2d("FLAG_C");
    sws::V3D* y = sws::DM::get_v3d("FLAG_D");
    std::string s = sws::DM::data["FLAG_E"]->value;

    std::cout << "INT: " << i->get() << std::endl;
    std::cout << "FLT: " << f->get() << std::endl;
    std::cout << "V2D_X: " << x->get('x') << std::endl;
    std::cout << "V3D_Y: " << y->get('y') << std::endl;
    std::cout << "STR: " << s << std::endl;

    for (const std::pair<const std::string, sws::data*>& d: sws::DM::data)
        std::cout << d;
    std::cin >> t1; std::cin >> t2; std::cin >> t3; std::cin >> t4; std::cin >> t5;
    
    sws::data* d1 = new sws::data(std::to_string(t1), "INT");
    sws::data* d2 = new sws::data(std::to_string(t2), "FLT");
    sws::data* d3 = new sws::data(std::to_string(t3) + "," + std::to_string(t2), "V2D");
    sws::data* d4 = new sws::data(std::to_string(t4) + "," + std::to_string(t3) + "," + std::to_string(t2), "V3D");
    sws::data* d5 = new sws::data(t5, "STR");

    sws::DM::update_data("FLAG_A", *d1);
    sws::DM::update_data("FLAG_B", *d2);
    sws::DM::update_data("FLAG_C", *d3);
    sws::DM::update_data("FLAG_D", *d4);
    sws::DM::update_data("FLAG_E", *d5);

    sws::DM::save_data("test");
    return 0;
}
