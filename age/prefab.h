#ifndef PREFAB_H
#define PREFAB_H

#include <memory>
#include <vector>

class Prefab {
    public:
        std::vector<std::pair<int,int>> colors;
        //x, y, char, color index.
        std::vector<std::tuple<int, int, char, int>> bitmap;    
};

#endif