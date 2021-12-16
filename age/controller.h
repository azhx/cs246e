#include <vector>

#ifndef CONTROLLER_H
#define CONTROLLER_H

struct Controller {
    public:
        virtual const std::vector<int>& getInput() = 0;
};

#endif