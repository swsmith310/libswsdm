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