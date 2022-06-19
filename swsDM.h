/* swsDM - A simple standard for managing program data
 * Copyright (C) 2020-2022 Spencer Smith (spencerwayne310@gmail.com)
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

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef SWSDM_H
#define SWSDM_H

namespace sws
{
    struct Data
    {
        std::string           key;
        std::string           value;
        Data(const std::string &k="", const std::string &v=0);
        void                  set_key(const std::string &k);   
        void                  set_value(const std::string &v); 
        static int            vtoi(const sws::Data *f);
        static long           vtol(const sws::Data *f);
        static unsigned int   vtou(const sws::Data *f);
        static float          vtof(const sws::Data *f);
        static double         vtod(const sws::Data *f);
    };
    struct DM
    {
        DM();
        static std::vector<Data*>     data;
        static void                   parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2);
        static void                   add_data(const std::string &k, const std::string &v=0);
        static void                   update_data(const std::string &k, const std::string &v=0);
        static std::string            view_data();
        static void                   load_data(const std::string &sf);
        static void                   save_data(const std::string &sf);
    };
}
#endif
