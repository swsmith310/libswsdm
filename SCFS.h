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
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#ifndef SCFS_H
#define SCFS_H

namespace SCFS
{
    struct Flag
    {
        std::string   key;
        std::string   value;
        Flag(std::string k="", std::string v=0);
        void          setKey(std::string k)   { key = k; }
        void          setValue(std::string v) { value = v; }
    };
    int t1, t2, t3;
    std::list<SCFS::Flag*> flags;
    void                   init();
    void                   parse(std::string const& s, const char d, 
                                 std::vector<std::string>& o1, std::vector<std::string>& o2);
    static void            addFlag(std::string k, std::string v=0);
    void                   loadFlags();
    void                   updateFlag(std::string k, std::string v=0);
    static std::string     viewFlags();
    void                   loadGame(std::string sf);
    void                   saveGame(std::string sf);
}

#endif