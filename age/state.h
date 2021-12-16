
#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>
#include <algorithm>
#include <ncurses.h>

#include "environment.h"
template<typename...> class GameObject;

class State {

    /*void doCollisions(){
        for (size_t i = 0; i < ents.size(); ++i){
            player->Collide(*ents[i]);
        }
        for (size_t i = 0; i < ents.size(); ++i){
            for (size_t j = i+1; j < ents.size(); ++j){
                ents[i]->Collide(*ents[j]);
            }
        }
    };
*/  int freeid = 1;

    static bool compareHeight (std::shared_ptr<GameObject<>> i, std::shared_ptr<GameObject<>> j);
    protected:    
        virtual void update(const std::vector<int>& input) = 0;
        virtual void doCollisions() =0;

    public:
        bool stopped = 0;
        bool quit = 0;
        std::shared_ptr<Environment> env;
        std::vector<std::shared_ptr<GameObject<>>> ents;
        std::unordered_map<std::string, int> globals;
        std::shared_ptr<GameObject<>> player;

        State(std::shared_ptr<Environment> env, 
            std::vector<std::shared_ptr<GameObject<>>> ents, 
            std::unordered_map<std::string, int> globals, 
            std::shared_ptr<GameObject<>> player):
            env{env}, ents{ents}, globals{globals}, player{player} {}

        void next(const std::vector<int>& input) {
            std::sort(ents.begin(), ents.end(), compareHeight);
            update(input);
            doCollisions();
        }
        void stop(){
            stopped =1 ;
        }
        void spawnObjects(std::vector<std::shared_ptr<GameObject<>>>newents){
            ents.reserve(ents.size() + newents.size());
            ents.insert(ents.end(), newents.begin(), newents.end());
        };
        
        void destroyObjects(std::vector<int>remove);

        int getFreeId(){ 
            int tmp = freeid;
            ++freeid;
            return tmp;
        }
        
        void setVariable(std::string s, int val){
            globals[s] = val;
        };

        virtual void renderStatus(WINDOW* status) const = 0;
};

#endif