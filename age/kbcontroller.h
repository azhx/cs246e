#ifndef KBCONTROLLER_H
#define KBCONTROLLER_H

#include <ncurses.h>
#include <chrono>
#include <vector>
#include <utility>
#include "controller.h"

class KBController: public Controller{
    std::vector<int> buffer;
    int tickrate = 450;
    public:
    KBController(int tickrate): tickrate{tickrate} {}
    const std::vector<int>& getInput() override {
        buffer = {};
        auto start = std::chrono::steady_clock::now();
        while(std::chrono::steady_clock::now()-start < std::chrono::milliseconds(tickrate)){
            int tmp = getch();
            if (tmp != -1) buffer.push_back(tmp);
        }
        return buffer;
    }

};

#endif