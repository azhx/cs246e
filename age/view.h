#ifndef VIEW_H
#define VIEW_H

class State;

class View {
    public:
        virtual void display(const State& state) = 0;
        virtual void close() = 0;
};

#endif