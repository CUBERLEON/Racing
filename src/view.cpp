#define PDC_WIDE
#include <curses.h>

#include <json/json.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "world.h"

using json=nlohmann::json;

void clean_scr(WINDOW* win = stdscr);
void mvwaddcircle(WINDOW* win, unsigned y, unsigned x, char c, unsigned r);

int main(int argc, char** argv) {
    try {
        if (argc < 2)
            throw std::invalid_argument("There are no passed arguments!");

        std::string text;
            
        std::fstream in;
        in.open(argv[1], std::fstream::in);
        std::stringstream buf;
        buf << in.rdbuf();
        text = buf.str();
        in.close();
        
        json data = json::parse(text);
        unsigned int ticksCnt = data["states"].size();
        if (ticksCnt < 1)
            throw std::invalid_argument("List of states cannot be empty!");
        unsigned int cockroachesCnt = data["states"][0].size();
        std::vector< std::vector<State> > states(ticksCnt);
        for (unsigned int i = 0; i < ticksCnt; ++i) {
            if (data["states"][i].size() != cockroachesCnt)
                throw std::invalid_argument("List of states contains corrupted data!");
            for (unsigned int j = 0; j < cockroachesCnt; ++j)
                states[i].push_back(State(data["states"][i][j]));
        }
        World world(data["world"]);

        initscr();
        if (has_colors() == FALSE) {
            endwin();
            throw std::runtime_error("Your terminal does not support colors!");
        }
        start_color();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);
        
        unsigned TPS = 20;
        unsigned TRACK_X = 140, TRACK_Y = unsigned(world.getWidth() / world.getLength() * TRACK_X);
        unsigned MAX_X = TRACK_X, MAX_Y = TRACK_Y + 2;
        
        resize_term(MAX_Y, MAX_X);
        
        WINDOW *track = newwin(TRACK_Y, TRACK_X, 2, 0);
        box(track, ' ' , ' ');
        wrefresh(track);
        
        float x_factor = (TRACK_X-1) / world.getLength();
        float y_factor = (TRACK_Y-1) / world.getWidth();
        
        for (unsigned tick = 0; tick < ticksCnt; ++tick) {
            clean_scr();
            clean_scr(track);
            
            mvprintw(0, 0, "Tick: %d/%d, Cockroaches: %d", tick+1, ticksCnt, cockroachesCnt);
            move(1, 0);
            for (unsigned i = 0; i < cockroachesCnt; ++i) {
                printw("%d:speed(%.1f, %.1f) ", i+1, states[tick][i].getSpeed().first, states[tick][i].getSpeed().second);
            }
            
            for (unsigned i = 0; i < cockroachesCnt; ++i) {
                mvwaddch(track, states[tick][i].getPos().second * y_factor, states[tick][i].getPos().first * x_factor,
                'X');
            }
            
            for (unsigned i = 0; i < world.getObstacles().size(); ++i) {
                mvwaddcircle(track, world.getObstacles()[i].getPosY() * y_factor, world.getObstacles()[i].getPosX() * x_factor,
                'O', 2);
            }
            
            refresh();
            wrefresh(track);
            napms(1000/TPS);
        }
        
        getch();
        endwin();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

void clean_scr(WINDOW* win) {
    unsigned int MAX_X, MAX_Y;
    getmaxyx(stdscr, MAX_Y, MAX_X);
    for (unsigned int i = 0; i < MAX_X; ++i)
        for (unsigned int j = 0; j < MAX_Y; ++j)
            mvwaddch(win, j, i, ' ');
}

void mvwaddcircle(WINDOW* win, unsigned y, unsigned x, char c, unsigned r) {
    // for (unsigned y=-radius; y<radius; y++) {
    //     half_row_width=sqrt(radius*radius-y*y);
    //     for(unsigned x=-half_row_width; x< half_row_width; x++)
    //         WritePixel(centre_x+x, centre_y+y, colour);
    // }
}