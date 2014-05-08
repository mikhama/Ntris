#include <ncurses.h>
#include "ntris.h"

int main(int argc, char *argv[]) {
    int mode = 0;
    initscr();  /* Start curses mode */
    start_color(); /* Start color functionality */
    
    init_pair(10,COLOR_WHITE,COLOR_WHITE);
    init_pair(11,COLOR_YELLOW,COLOR_YELLOW);
    init_pair(12,COLOR_MAGENTA,COLOR_MAGENTA);
    init_pair(13,COLOR_CYAN,COLOR_CYAN);
    init_pair(14,COLOR_GREEN,COLOR_GREEN);
    init_pair(15,COLOR_RED,COLOR_RED);
    init_pair(16,COLOR_BLUE,COLOR_BLUE);
    init_pair(17,COLOR_WHITE,COLOR_WHITE);
    init_pair(18,COLOR_YELLOW,COLOR_YELLOW);
    init_pair(19,COLOR_MAGENTA,COLOR_MAGENTA);
    init_pair(20,COLOR_BLACK,COLOR_WHITE);
    init_pair(21,COLOR_BLACK,COLOR_YELLOW);
    init_pair(22,COLOR_WHITE,COLOR_MAGENTA);
    init_pair(23,COLOR_WHITE,COLOR_CYAN);
    init_pair(24,COLOR_WHITE,COLOR_GREEN);
    init_pair(25,COLOR_WHITE,COLOR_RED);
    init_pair(26,COLOR_WHITE,COLOR_BLUE);
    
    curs_set(0);
    noecho();
    keypad(stdscr,TRUE);
    refresh();
    
    WINDOW **logo;
    WINDOW **menu;

    int i = 0;
    int score = 0;
    while (i == 0) {
        logo = draw_logo();
        menu = draw_menu();
        if (score > 0 ) {
            mode = 1;
        }
        else {
            mode = scroll_menu(menu);
        }
        switch (mode) {
            case 0:
                delete_menu(menu,5);
                delete_menu(logo,169);
                score = tetris_init();
                break;
            case 1:
                delete_menu(menu,5);
                if (score > 0) {
                    draw_hiscores(1,score);
                } 
                else {
                    draw_hiscores(0,score);
                }
                score = 0;
                break;
            case 2:
                delete_menu(menu,5);
                draw_help();
                break;
            case 3:
                delete_menu(menu,5);
                delete_menu(logo,169);
                i = 1;
                break;
        }
    }

    /*getch();*/
    
    endwin(); /* End curses mode */
}
