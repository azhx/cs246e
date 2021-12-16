#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <vector>

class State;
class Prefab;

class Environment{
    State& state;
    public:
        std::shared_ptr<Prefab> prefab;
        const std::pair<int, int> dims;
        std::pair<int, int> viewport;

        Environment(State& state, std::shared_ptr<Prefab> prefab, const std::pair<int, int> dims, std::pair<int, int> viewport):
            state{state}, prefab{prefab}, dims{dims}, viewport{viewport} {}

        virtual void update(const std::vector<int>& input) = 0;
};

#endif