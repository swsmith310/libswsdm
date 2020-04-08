#include "SCFS.h"

SCFS::Flag::Flag(std::string k, std::string v)
{
    setKey(k);
    setValue(v);
}

void SCFS::init()
{
    loadGame("baseFlags");
}

void SCFS::parse(std::string const& s, const char d, std::vector<std::string>& o1, std::vector<std::string>& o2)
{
    size_t start;
    size_t end = 0;

    while ((start = s.find_first_not_of(d, end)) != std::string::npos)
    {
        end = s.find(d, start);
        end > 32 ? o2.push_back(s.substr(start, end - start))
                 : o1.push_back(s.substr(start, end - start));
    }
}

void SCFS::addFlag(std::string k, std::string v)
{
    SCFS::Flag* f = new Flag(k, v);
    flags.push_back(f);
} 

void SCFS::loadFlags()
{
    for (auto& f : flags)
    {
        // if (f->key == "KEY") VARIABLE = f->value;
    }
}

void SCFS::updateFlag(std::string k, std::string v)
{
    for (auto& f : flags)
    {
        if (f->key == k)
        {
            f->setValue(v);
        }
    }
}

std::string SCFS::viewFlags()
{
    std::string fs;
    for (auto& f : flags) fs.append(f->key + "|" + f->value + "\n");
    return fs;
}

void SCFS::loadGame(std::string sf)
{
    std::string line;
    std::ifstream file(sf + ".scfs");
    try
    {
        while(std::getline(file, line))
        {
            std::vector<std::string> keys;
            std::vector<std::string> values;
            parse(line, '|', keys, values);
            for (auto& k : keys)
            {  
                if (k == "ENDFLAGS") break;
                std::string value;
                for (auto& v : values) value = v;
                if (sf == "baseFlags") addFlag(k, value);
                else                   updateFlag(k, value);
            }
        }
    }
    catch(const std::exception& e) { std::cerr << "SAVE FILE CORRUPTED" << '\n'; }
    file.close();
    loadFlags();
}

void SCFS::saveGame(std::string sf)
{
    std::ofstream saveFile(sf + ".scfs");
    saveFile << viewFlags() << "ENDFLAGS";
    saveFile.close();
}

// Uncomment and compile for basic testing
/*int main()
{
    int t1, t2, t3;
    SCFS::init();
    SCFS::loadGame("test");
    std::cout << SCFS::viewFlags();
    std::cin >> t1;
    std::cin >> t2;
    std::cin >> t3;
    SCFS::updateFlag("FLAG_A", std::to_string(t1));
    SCFS::updateFlag("FLAG_B", std::to_string(t2));
    SCFS::updateFlag("FLAG_C", std::to_string(t3));
    SCFS::saveGame("test");
    return 0;
}*/