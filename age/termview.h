#ifndef TERMVIEW_H
#define TERMVIEW_H

#include <utility>
#include "view.h"
#include "gameobject.h"
#include "environment.h"
#include "prefab.h"
#include "state.h"

#define GAMEHEIGHT 22
#define GAMEWIDTH 80
#define STATUSHEIGHT 3
#define STATUSWIDTH 80

class Environment;


class TermView : public View{
    WINDOW* game;
    WINDOW* status;
    int freecolor = 1;
    bool has_colors;
    // y, x 
    std::pair<int, int> tlcorner;


    bool inbounds(int x, int y);
    void render(const Environment& env);
    void render(const GameObject<>& obj);

    public:
    TermView(bool has_colors): has_colors{has_colors}, tlcorner{std::make_pair(0, 0)}{
        initscr();
        cbreak();
        noecho();
        if (has_colors) start_color();
        keypad(stdscr, true);
        curs_set(0);
        nodelay(stdscr, true);
	    game= newwin(GAMEHEIGHT, GAMEWIDTH, 1, 1);
	    status = newwin(STATUSHEIGHT, STATUSWIDTH, 24, 1);
	    refresh();
	    box(game, 0, 0);
    } 

    void display(const State& state) override;
    void close() override;
};

#endif