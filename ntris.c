#include <ncurses.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include "ntris.h"

static char buf[12];
char *itoa(int i) {
    char *ptr = buf + sizeof(buf) - 1;
    unsigned int u;
    int minus = 0;

    if (i < 0) {
        minus = 1;
        u = ((unsigned int)(-(1+i))) + 1;
    } else
        u = i;
    *ptr = 0;
    do
        *--ptr = '0' + (u % 10);
    while(u/=10);

    if (minus)
        *--ptr = '-';
    return ptr;
}

int tetris_init() {
    int matrix_B[20][10];
    int i, j, score, hiscore, level, lines, Single, Double, Triple, Tetris, blocks, O, I, S, Z, L, J, T, message;

    for(i=0; i<20; i++) {
        for(j=0; j<10; j++) {
            matrix_B[i][j]=0;
        }
    }
    
    WINDOW **matrix_F;
    matrix_F = draw_matrix();
    
    WINDOW **next_block_window;
    struct Tblock new_block;
    next_block_window = draw_next_block_window();

    score = 0;
    WINDOW *score_window;
    score_window = draw_score_window();

    hiscore = 0;
    WINDOW *hiscore_window;
    hiscore_window = draw_hiscore_window();

    level = 0;
    WINDOW *level_window;
    level_window = draw_level_window();
    
    lines = 0;
    Single = 0;
    Double = 0;
    Triple = 0;
    Tetris = 0;
    WINDOW *lines_window;
    lines_window = draw_stats_lines_window();

    blocks = 0;
    O = 0;
    I = 0;
    S = 0;
    Z = 0;
    L = 0;
    J = 0;
    T = 0;
    WINDOW **blocks_window;
    blocks_window = draw_stats_blocks_window();

    message = 0;
    WINDOW *message_window;

    struct timespec tm;
    tm.tv_sec=0;
    tm.tv_nsec=2000000;
    int timer=0;
    
    int cmd;

    struct Tblock next_block, current_block;

    current_block = create_new_block();
    next_block = create_new_block();

    int fd=fileno(stdin);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0)|O_NONBLOCK);
                
    int lines_deleted, bonus;
    
    redraw_next_block_window(next_block_window, next_block);
    redraw_score_window(score_window, score);
    redraw_hiscore_window(hiscore_window, hiscore);
    redraw_stats_lines_window(lines_window, lines, Single, Double, Triple, Tetris);
    redraw_stats_blocks_window(blocks_window, blocks, O, I, S, Z, L, J, T);
    redraw_level_window(level_window, level);

    while (1) {
        nanosleep(&tm,NULL);
        timer++;

        if (timer%50 == 0) {
            redraw_matrix(matrix_F, matrix_B, current_block, level);
            if (message != 0) {
                message_window = draw_message_window(message);
            }
            
        }
        if (timer%350 == 0) {
            if (message == 0) {
                current_block.offset_y++;
            }
            if (tetris_gravity(matrix_B,current_block)==1) {
                lines_deleted = check_lines(matrix_B,current_block);
                
                if (lines_deleted > 1) {
                    bonus = 50 * (lines_deleted - 1);
                }
                else
                    if (lines_deleted > 0) {
                        bonus = level * 20;
                    }
                    else {
                        bonus = 0;
                    }
                score += 100 * lines_deleted + bonus;
                score += 10;
                
                switch(lines_deleted) {
                    case 1:
                        Single++;
                    break;
                    case 2:
                        Double++;
                    break;
                    case 3:
                        Triple++;
                    break;
                    case 4:
                        Tetris++;
                    break;
                }
                lines += lines_deleted;
                
                switch (current_block.type) {
                    case 0:
                        O++;
                    break;
                    case 1:
                        I++;
                    break;
                    case 2:
                        S++;
                    break;
                    case 3:
                        Z++;
                    break;
                    case 4:
                        L++;
                    break;
                    case 5:
                        J++;
                    break;
                    case 6:
                        T++;
                    break;
                }
                blocks++;

                current_block = next_block;
                next_block = create_new_block();
                
                redraw_next_block_window(next_block_window, next_block);
                redraw_score_window(score_window, score);
                redraw_hiscore_window(hiscore_window, hiscore);
                redraw_stats_lines_window(lines_window, lines, Single, Double, Triple, Tetris);
                redraw_stats_blocks_window(blocks_window, blocks, O, I, S, Z, L, J, T);
                
                if ((score >= 1000) && (score < 5000))
                    level = 1;
                else 
                    if ((score >= 5000) && (score < 10000))
                        level = 2;
                    else
                        if ((score >= 10000) && (score < 15000))
                            level = 3;
                        else 
                            if ((score >= 15000) && (score < 20000))
                                level = 4;
                            else
                                if ((score >= 20000) && (score < 25000))
                                    level = 5;
                                else 
                                    if ((score >= 25000) && (score < 30000))
                                        level = 6;
                                    else
                                        if ((score >= 30000) && (score < 35000))
                                            level = 7;
                                        else 
                                            if ((score >= 35000) && (score < 40000))
                                                level = 8;
                                            else
                                                if ((score >= 40000) && (score < 45000))
                                                    level = 9;
                
                redraw_level_window(level_window, level);
                
                switch (level) {
                    case 1: 
                        tm.tv_nsec = 1500000;
                    break;
                    case 2: 
                        tm.tv_nsec = 1000000;
                    break;
                    case 3: 
                        tm.tv_nsec = 900000;
                    break;
                    case 4: 
                        tm.tv_nsec = 800000 ;
                    break;
                    case 5: 
                        tm.tv_nsec = 700000;
                    break;
                    case 6: 
                        tm.tv_nsec = 800000;
                    break;
                    case 7: 
                        tm.tv_nsec = 500000;
                    break;
                    case 8: 
                        tm.tv_nsec = 400000;
                    break;
                    case 9: 
                        tm.tv_nsec = 300000;
                    break;

                }
                
    
                /*[>FILE *file;<]*/
                /*[>int i, j;<]*/
                /*[>file = fopen("1.txt","w");<]*/
                /*[>for (i = 0; i < 20; i++) {<]*/
                    /*[>for (j = 0; j < 10; j++) {<]*/
                        /*[>fprintf(file,"%x",matrix_B[i][j]);<]*/
                    /*[>}<]*/
                    /*[>fprintf(file,"\n");<]*/
                /*[>}<]*/
                /*[>fclose(file);<]*/
            }
            else if (tetris_gravity(matrix_B,current_block)==2) {
                message = 2;
            }
        }

        while ((cmd=getch())>0) {
            if (message == 2) {
                fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 1) & ~O_NONBLOCK);
                delete_menu(blocks_window,9);
                destroy_win(lines_window);
                destroy_win(level_window);
                destroy_win(hiscore_window);
                destroy_win(score_window);
                delete_menu(next_block_window,5);
                delete_menu(matrix_F,205);
                return score;
            }
            switch (cmd) {
                case KEY_UP:
                case (int)'W':
                case (int)'w':
                    if (message == 0) {
                        current_block = tetris_rotate(matrix_B, current_block);
                    }
                break;
                case KEY_LEFT:
                case (int)'A':
                case (int)'a':
                    if (message == 0) {
                        current_block.offset_x-=2;
                        if ((current_block.offset_x+current_block.ax*2<=0) || 
                            (current_block.offset_x+current_block.bx*2<=0) || 
                            (current_block.offset_x+current_block.cx*2<=0) ||
                            (current_block.offset_x+current_block.dx*2<=0) ||
                            (check_borders(matrix_B,current_block) == 1))
                            current_block.offset_x+=2;
                    }
                break;
                case KEY_RIGHT:
                case (int)'D':
                case (int)'d':
                    if (message == 0) {
                        current_block.offset_x+=2;
                        if ((current_block.offset_x+current_block.ax*2>=22) || 
                            (current_block.offset_x+current_block.bx*2>=22) || 
                            (current_block.offset_x+current_block.cx*2>=22) ||
                            (current_block.offset_x+current_block.dx*2>=22) ||
                            (check_borders(matrix_B,current_block) == 1))
                            current_block.offset_x-=2;
                    }
                break;
                case KEY_DOWN:
                case (int)'S':
                case (int)'s':
                    if (message == 0) {
                        current_block.offset_y++;
                        if ((current_block.offset_y+current_block.ay*(-1)>=21) || 
                            (current_block.offset_y+current_block.by*(-1)>=21) || 
                            (current_block.offset_y+current_block.cy*(-1)>=21) ||
                            (current_block.offset_y+current_block.dy*(-1)>=21) ||
                            (check_borders(matrix_B,current_block) == 1))
                            current_block.offset_y--;
                    }
                break;
                case (int)'P':
                case (int)'p':
                    if (message == 0) {
                        message = 1;
                    }
                    else if (message == 1) {
                        message = 0;
                    }
                break;
                case ESCAPE:
                    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 1) & ~O_NONBLOCK);
                    delete_menu(blocks_window,9);
                    destroy_win(lines_window);
                    destroy_win(level_window);
                    destroy_win(hiscore_window);
                    destroy_win(score_window);
                    delete_menu(next_block_window,5);
                    delete_menu(matrix_F,205);
                    return 0;
                break;
                    
            }
        }
    }
}

struct Tblock create_new_block() {
    struct Tblock new_block;
    srand(time(NULL));
    new_block.type = rand()%7;
    switch(new_block.type) {
        case 0:
            new_block.ax = -1; new_block.ay = 0;    /*    */
            new_block.bx = 0;  new_block.by = 0;    /* ## */
            new_block.cx = -1; new_block.cy = -1;   /* ## */
            new_block.dx = 0;  new_block.dy = -1;   /*    */
            new_block.rotate_positions = 0;
        break;
        case 1:
            new_block.ax = -2; new_block.ay = 0;    /*    */
            new_block.bx = -1; new_block.by = 0;    /*####*/
            new_block.cx = 0;  new_block.cy = 0;    /*    */
            new_block.dx = 1;  new_block.dy = 0;    /*    */
            new_block.rotate_positions = 2;
        break;
        case 2:
            new_block.ax = 0;  new_block.ay = 0;    /*    */
            new_block.bx = 1;  new_block.by = 0;    /*  ##*/
            new_block.cx = -1;  new_block.cy = -1;  /* ## */
            new_block.dx = 0;  new_block.dy = -1;   /*    */
            new_block.rotate_positions = 2;
        break;
        case 3:
            new_block.ax = -1; new_block.ay = 0;    /*    */
            new_block.bx = 0;  new_block.by = 0;    /* ## */
            new_block.cx = 0;  new_block.cy = -1;   /*  ##*/
            new_block.dx = 1;  new_block.dy = -1;   /*    */
            new_block.rotate_positions = 2;
        break;
        case 4:
            new_block.ax = -1; new_block.ay = 0;    /*    */
            new_block.bx = 0;  new_block.by = 0;    /* ###*/
            new_block.cx = 1;  new_block.cy = 0;    /* #  */
            new_block.dx = -1; new_block.dy = -1;   /*    */
            new_block.rotate_positions = 4;
        break;
        case 5:
            new_block.ax = -1; new_block.ay = 0;    /*    */
            new_block.bx = 0;  new_block.by = 0;    /* ###*/
            new_block.cx = 1;  new_block.cy = 0;    /*   #*/
            new_block.dx = 1;  new_block.dy = -1;   /*    */
            new_block.rotate_positions = 4;
        break;
        case 6:
            new_block.ax = -1; new_block.ay = 0;    /*    */
            new_block.bx = 0;  new_block.by = 0;    /* ###*/
            new_block.cx = 1;  new_block.cy = 0;    /*  # */ 
            new_block.dx = 0;  new_block.dy = -1;   /*    */
            new_block.rotate_positions = 4;
        break;
    }
    new_block.rotate_status = 1;
    new_block.offset_x=12;
    new_block.offset_y=0;
    
    return new_block;
}

int tetris_gravity(int matrix_B[20][10], struct Tblock current_block) {
    if ((current_block.offset_y+current_block.ay*(-1)>=21) || 
        (current_block.offset_y+current_block.by*(-1)>=21) || 
        (current_block.offset_y+current_block.cy*(-1)>=21) ||
        (current_block.offset_y+current_block.dy*(-1)>=21) ||
        (check_borders(matrix_B,current_block) == 1)) {
        matrix_B[current_block.offset_y-1+current_block.ay*(-1)-1][current_block.offset_x/2+current_block.ax-1] = 1;
        matrix_B[current_block.offset_y-1+current_block.by*(-1)-1][current_block.offset_x/2+current_block.bx-1] = 1;
        matrix_B[current_block.offset_y-1+current_block.cy*(-1)-1][current_block.offset_x/2+current_block.cx-1] = 1;
        matrix_B[current_block.offset_y-1+current_block.dy*(-1)-1][current_block.offset_x/2+current_block.dx-1] = 1;
    if ((current_block.offset_y+current_block.ay*(-1)==1) || 
        (current_block.offset_y+current_block.by*(-1)==1) || 
        (current_block.offset_y+current_block.cy*(-1)==1) ||
        (current_block.offset_y+current_block.dy*(-1)==1)) {
            return 2;
        }
        return 1;
    }
    else
        return 0;
}

int check_borders(int matrix_B[20][10], struct Tblock current_block) {
    if ((matrix_B[current_block.offset_y+current_block.ay*(-1)-1][current_block.offset_x/2+current_block.ax-1] == 1) || 
        (matrix_B[current_block.offset_y+current_block.by*(-1)-1][current_block.offset_x/2+current_block.bx-1] == 1) || 
        (matrix_B[current_block.offset_y+current_block.cy*(-1)-1][current_block.offset_x/2+current_block.cx-1] == 1) || 
        (matrix_B[current_block.offset_y+current_block.dy*(-1)-1][current_block.offset_x/2+current_block.dx-1] == 1))
        return 1;
    else
        return 0;
}

struct Tblock tetris_rotate(int matrix_B[20][10], struct Tblock current_block) {
    int buffer;
    struct Tblock buffer_block;

    buffer_block = current_block;
    if (current_block.rotate_positions > 0) {
        if (current_block.rotate_status == 1) {
            buffer = current_block.ax;
            current_block.ax = (-1)*current_block.ay;
            current_block.ay = buffer;
            
            buffer = current_block.bx;
            current_block.bx = (-1)*current_block.by;
            current_block.by = buffer;

            buffer = current_block.cx;
            current_block.cx = (-1)*current_block.cy;
            current_block.cy = buffer;
            
            buffer = current_block.dx;
            current_block.dx = (-1)*current_block.dy;
            current_block.dy = buffer;
        }
        else {
            buffer = current_block.ay;
            current_block.ay = (-1)*current_block.ax;
            current_block.ax = buffer;
            
            buffer = current_block.by;
            current_block.by = (-1)*current_block.bx;
            current_block.bx = buffer;

            buffer = current_block.cy;
            current_block.cy = (-1)*current_block.cx;
            current_block.cx = buffer;
            
            buffer = current_block.dy;
            current_block.dy = (-1)*current_block.dx;
            current_block.dx = buffer;
        }
        if (current_block.rotate_positions == 2) {
            current_block.rotate_status*=(-1); 
        }
    }
    if ((current_block.offset_x+current_block.ax*2<=0) || 
        (current_block.offset_x+current_block.bx*2<=0) || 
        (current_block.offset_x+current_block.cx*2<=0) ||
        (current_block.offset_x+current_block.dx*2<=0) ||
        (current_block.offset_x+current_block.ax*2>=22) || 
        (current_block.offset_x+current_block.bx*2>=22) || 
        (current_block.offset_x+current_block.cx*2>=22) ||
        (current_block.offset_x+current_block.dx*2>=22) ||
        (current_block.offset_y+current_block.ay*(-1)>=21) || 
        (current_block.offset_y+current_block.by*(-1)>=21) || 
        (current_block.offset_y+current_block.cy*(-1)>=21) ||
        (current_block.offset_y+current_block.dy*(-1)>=21) ||
        (check_borders(matrix_B,current_block) == 1))
        return buffer_block;
    else
        return current_block;
}

int check_lines(int matrix_B[20][10], struct Tblock current_block) {
    int i, j, n, counter, deleted_lines_counter;
    counter = 0;
    deleted_lines_counter = 0;
    i = 19;
    while (i>=0) {
        for (j=0;j<10;j++) {
            if(matrix_B[i][j] == 1) {
                counter++;
            }
            else {
                break;
            }
        }
        if (counter == 10) {
            for (j=0;j<10;j++) {
                n = i;
                matrix_B[i][j] = 0;
                while(n>0) {
                    matrix_B[n][j] = matrix_B[n-1][j];
                    n--;
                }
            }
            i++;
            deleted_lines_counter++;
        }
        i--;
        counter = 0;
    }
    return deleted_lines_counter;
}

void sort_scores(struct Hscores winners[6]) {
    struct Hscores buffer;
    int i, j;
    for(i=1;i<6;i++) {
        for(j=5;j>=i;j--) {
            if(winners[j-1].score < winners[j].score) {
                buffer.num = winners[j-1].num;
                buffer.score = winners[j-1].score;
                strcpy(buffer.name,winners[j-1].name);

                winners[j-1].num= winners[j].num;
                winners[j-1].score= winners[j].score;
                strcpy(winners[j-1].name,winners[j].name);
                
                winners[j].num = buffer.num;
                winners[j].score = buffer.score;
                strcpy(winners[j].name,buffer.name);
                
            }
        }
    }
}
