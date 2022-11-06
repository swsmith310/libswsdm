/* libswsdm - A simple library for saving and loading game data
 * Copyright (C) 2020-2022 Spencer W. Smith (spencerwayne310@gmail.com)
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
#include <unordered_map>

#ifndef SWSDM_H
#define SWSDM_H

namespace sws
{
    struct DM
    {
        DM();
        static std::unordered_map<std::string, std::string> data;
        static void               parse(std::string const& s, const char d, std::string& o1, std::string& o2);
        static void               update_data(const std::string &k, const std::string &v=0);
        static void               load_data(const std::string &sf);
        static void               save_data(const std::string &sf);
        static int                vtoi(const std::string &k);
        static long               vtol(const std::string &k);
        static unsigned int       vtou(const std::string &k);
        static float              vtof(const std::string &k);
        static double             vtod(const std::string &k);
    };
}
#endif
