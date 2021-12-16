#include <ncurses.h>
#include "termview.h"


bool TermView::inbounds(int x, int y){
    int miny = tlcorner.first;
    int minx = tlcorner.second;
    int maxy = miny + GAMEHEIGHT-1;
    int maxx = minx + GAMEWIDTH-1;
    if (x <= minx || x >= maxx || y <= miny || y >= maxy){
        return false;
    }
    return true;
}


void TermView::render(const Environment& env){
    int coloridx = freecolor;
    for (size_t i = 0; i < env.prefab->colors.size(); ++i){
        init_pair(freecolor, env.prefab->colors[i].first, env.prefab->colors[i].second);
        ++freecolor;
    }
    for (size_t i = 0; i < env.prefab->bitmap.size(); ++i){
        int y = std::get<1>(env.prefab->bitmap[i]);
        int x = std::get<0>(env.prefab->bitmap[i]);
        char c = std::get<2>(env.prefab->bitmap[i]);
        int coloroffset = std::get<3>(env.prefab->bitmap[i]);
        if (!has_colors && c == ' ') c = 'O';
        if (inbounds(x, y)){
            wattron(game, COLOR_PAIR(coloridx + coloroffset));
            mvwaddch(game, y-tlcorner.first, x-tlcorner.second, c);
        }
    }
}

void TermView::render(const GameObject<>& obj){
    int coloridx = freecolor;
    for (size_t i = 0; i < obj.prefab->colors.size(); ++i){
        init_pair(freecolor, obj.prefab->colors[i].first, obj.prefab->colors[i].second);
        ++freecolor;
    }
    for (size_t i = 0; i < obj.prefab->bitmap.size(); ++i){
        int y = std::get<1>(obj.prefab->bitmap[i]) + obj.pos.second;
        int x = std::get<0>(obj.prefab->bitmap[i]) + obj.pos.first;
        char c = std::get<2>(obj.prefab->bitmap[i]);
        if (!has_colors && c == ' ') c = 'O';
        char coloroffset = std::get<3>(obj.prefab->bitmap[i]);
        // object bitmaps are relative to object pos
        if (inbounds(x, y)){
            wattron(game, COLOR_PAIR(coloridx + coloroffset));
            mvwaddch(game, y-tlcorner.first, x-tlcorner.second, c);
        }
    }
}

void TermView::display(const State& state) {
    tlcorner.first = state.env->viewport.first;
    tlcorner.second = state.env->viewport.second;
    freecolor = 1;
    werase(game);
    werase(status);
    render(*state.env);
    init_pair(freecolor, COLOR_WHITE, COLOR_BLACK);
    wattron(game, COLOR_PAIR(freecolor));
    box(game, 0, 0);
    ++freecolor;
    for (size_t i = 0; i < state.ents.size(); ++i){
        render(*state.ents[i]);
    }
    render(*state.player);
    state.renderStatus(status);
    wrefresh(game);
    wrefresh(status);
    for (int i = 1; i < freecolor; ++i){
        wattroff(game, COLOR_PAIR(freecolor));
    }
}

void TermView::close() {
    endwin();
}

