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
    struct Flag
    {
        std::string           key;
        std::string           value;
        Flag(const std::string &k="", const std::string &v=0);
        void                  set_key(const std::string &k);   
        void                  set_value(const std::string &v); 
        static int            vtoi(const sws::Flag *f);
        static long           vtol(const sws::Flag *f);
        static unsigned int   vtou(const sws::Flag *f);
        static float          vtof(const sws::Flag *f);
        static double         vtod(const sws::Flag *f);
    };
    struct DM
    {
        DM();
        static std::vector<Flag*>     flags;
        static void                   parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2);
        static void                   add_flag(const std::string &k, const std::string &v=0);
        static void                   update_flag(const std::string &k, const std::string &v=0);
        static std::string            view_flags();
        static void                   load_flags(const std::string &sf);
        static void                   save_flags(const std::string &sf);
    };
}
#endif
