#include "state.h"
#include "gameobject.h"

bool State::compareHeight (std::shared_ptr<GameObject<>> i, std::shared_ptr<GameObject<>> j){
    return i->height < j->height;
}
void State::destroyObjects(std::vector<int>remove){
    std::vector<size_t> tmp = {}; 
    for (int i = ents.size()-1; i >= 0; --i){
        for (size_t j = 0; j < remove.size(); ++j){
            if (ents[i]->id == remove[j]){
                tmp.push_back((size_t) i);
                // this should only match one
                break;
            }
        }
    }
    for (auto idx: tmp){
        ents.erase(ents.begin()+idx);
    }
};

