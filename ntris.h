#ifndef NTRIS_H
#define NTRIS_H

#define ESCAPE 27
#define ENTER 10
#define DELETE 7

struct Tblock {
    int ax;
    int ay;
    int bx;
    int by;
    int cx;
    int cy;
    int dx;
    int dy;
    int type;
    int offset_x;
    int offset_y;
    int rotate_positions;
    int rotate_status;
};

struct Hscores {
    int num;
    int score;
    char name[9];
};

char *itoa(int i);

int tetris_init();

WINDOW *create_newwin(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);

void delete_menu(WINDOW **items, int count);

int scroll_menu(WINDOW **items);

WINDOW **draw_menu();

WINDOW **draw_logo();

WINDOW **draw_matrix();

void redraw_matrix(WINDOW **items, int matrix_B[20][10], struct Tblock current_block, int level);
    
WINDOW **draw_next_block_window();

void redraw_next_block_window(WINDOW **items, struct Tblock next_block);

WINDOW *draw_score_window();

void redraw_score_window(WINDOW *win, int score);

WINDOW *draw_hiscore_window();

void redraw_hiscore_window(WINDOW *win, int hiscore);

WINDOW *draw_level_window();

void redraw_level_window(WINDOW *win, int level);

WINDOW *draw_stats_lines_window();

void redraw_stats_lines_window(WINDOW *win, int lines, int Single, int Double, int Triple, int Tetris);

WINDOW **draw_stats_blocks_window();

void redraw_stats_blocks_window(WINDOW **items, int blocks, int O, int I, int S, int Z, int L, int J, int T);

WINDOW *draw_message_window(int message);

void draw_hiscores(int mode, int score);

void draw_help();

struct Tblock create_new_block();

int tetris_gravity(int matrix_B[20][10], struct Tblock current_block);

int check_borders(int matrix_B[20][10], struct Tblock current_block);

struct Tblock tetris_rotate(int matrix_B[20][10], struct Tblock current_block);

int check_lines(int matrix_B[20][10], struct Tblock current_block);

void sort_scores(struct Hscores winners[6]);

#endif // NTRIS_H
