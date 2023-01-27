/* libswsdm - A simple library for saving and loading game data
 * Copyright (C) 2020-2023 Spencer W. Smith (spencerwayne310@gmail.com)
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

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef SWSDM_H
#define SWSDM_H

namespace sws
{
    struct type {
        auto get(char v='\0') { return nullptr; }
    };

    struct INT : public type {
        int i;
        INT(int i);
        auto get(char v='\0');
    };

    struct FLT : public type {
        float f;
        FLT(float f);
        auto get(char v='\0');
    };

    struct V2D : public type {
        float x;
        float y;
        V2D(float x, float y);
        std::string to_string();
        auto get(char v='\0');
    };

    struct V3D : public type {
        float x;
        float y;
        float z;
        V3D(float x, float y, float z);
        std::string to_string();
        auto get(char v='\0');
    };

    struct data {
        std::string value;
        int type;
        sws::type* raw_value;
        data(std::string value, std::string type);
    };

    struct DM
    {
        static std::unordered_map<std::string, sws::data*> data;
        DM();
        static void update_data(const std::string &k, sws::data &v);
        static void load_init();
        static void load_data(const std::string &sf);
        static void save_data(const std::string &sf);
        static sws::INT* get_int(const std::string &k);
        static sws::FLT* get_flt(const std::string &k);
        static sws::V2D* get_v2d(const std::string &k);
        static sws::V3D* get_v3d(const std::string &k);
    };
}
#endif
