#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <utility>
#include <chrono>
#include <ncurses.h>
#include "controller.h"

class Model {
    std::unique_ptr<View> view;
    std::unique_ptr<Controller> controller;
    std::shared_ptr<State> state;

    public:
    Model(std::unique_ptr<View> view, std::unique_ptr<Controller> controller, std::shared_ptr<State> state)
        : view{std::move(view)}, controller{std::move(controller)}, state{std::move(state)} {}
    
    void go() {
        while (!state->quit) {
            view->display(*state);
            state->next(controller->getInput());
        }
        view->close();
    }
};


#endif 