#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ntris.h"

WINDOW *create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);
    
    return local_win;
}

void destroy_win(WINDOW *local_win) {
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wclear(local_win);
    wrefresh(local_win);
    delwin(local_win);
}

void delete_menu(WINDOW **items, int count) {
    int i;
    for (i=0;i<count;i++) {
        wclear(items[i]);
        wrefresh(items[i]);
        /*delwin(items[i]);*/
    }
    destroy_win(items[0]);
    free(items);
}

int scroll_menu(WINDOW **items) {
    int i=1;
    int cmd;
    wbkgd(items[i],COLOR_PAIR(26));
    wrefresh(items[i]);
    while ((cmd=getch())>0) {
        wbkgd(items[i],COLOR_PAIR(0));
        wrefresh(items[i]);
        switch(cmd) {
            case KEY_UP:
            case 'W':
            case 'w':
                i--;
                if (i<1) {
                    i = 4;
                }
            break;
            case KEY_DOWN:
            case 'S':
            case 's':
                i++;
                if (i>4) {
                    i = 1;
                }
            break;
            case ENTER:
                return i-1;
            break;
        }
        wbkgd(items[i],COLOR_PAIR(26));
        wrefresh(items[i]);
    }
}

WINDOW **draw_menu() {
    int i;
    WINDOW **items;
    items = (WINDOW **)malloc(5*sizeof(WINDOW *));
    items[0] = create_newwin(6,22,5+0+(LINES-6)/2,0+(COLS-22)/2);
    for (i=1;i<5;i++) {
        items[i] = subwin(items[0],1,20,5+i+(LINES-6)/2,1+(COLS-22)/2);
    }
    wprintw(items[1],"PLAY");
    wprintw(items[2],"HIGH SCORES");
    wprintw(items[3],"HELP");
    wprintw(items[4],"EXIT");
    for (i=1;i<5;i++) {
        wrefresh(items[i]);
    }
    return items;
}

WINDOW **draw_logo() {
    WINDOW **pixels;
    pixels = (WINDOW **)malloc(169*sizeof(WINDOW *)); /* 8x21 */
    pixels[0] = newwin(8,38,(LINES-8)/2-3,(COLS-38)/2);
    int i,j;
    for (i=0;i<8;i++) {
        for (j=0;j<21;j++) {
            pixels[1+i*(21)+j] = subwin(pixels[0],1,2,(i+2)+LINES/2-9,(j*2+2)+COLS/2-25);
            wrefresh(pixels[1+i*(21)+j]);
        }
    }
    
    wbkgd(pixels[1+2*(21)+2],COLOR_PAIR(10));
    wbkgd(pixels[1+3*(21)+2],COLOR_PAIR(10));
    wbkgd(pixels[1+4*(21)+2],COLOR_PAIR(10));
    wbkgd(pixels[1+5*(21)+2],COLOR_PAIR(10));
    wbkgd(pixels[1+6*(21)+2],COLOR_PAIR(10));
    wbkgd(pixels[1+2*(21)+3],COLOR_PAIR(10));
    wbkgd(pixels[1+3*(21)+4],COLOR_PAIR(10));
    wbkgd(pixels[1+4*(21)+5],COLOR_PAIR(10));
    wbkgd(pixels[1+0*(21)+6],COLOR_PAIR(10));
    wbkgd(pixels[1+1*(21)+6],COLOR_PAIR(10));
    wbkgd(pixels[1+2*(21)+6],COLOR_PAIR(10));
    wbkgd(pixels[1+3*(21)+6],COLOR_PAIR(10));
    wbkgd(pixels[1+4*(21)+6],COLOR_PAIR(10));
   
    wbkgd(pixels[1+2*(21)+9],COLOR_PAIR(15));
    wbkgd(pixels[1+3*(21)+8],COLOR_PAIR(15));
    wbkgd(pixels[1+3*(21)+9],COLOR_PAIR(15));
    wbkgd(pixels[1+3*(21)+10],COLOR_PAIR(15));
    wbkgd(pixels[1+4*(21)+9],COLOR_PAIR(15));
    wbkgd(pixels[1+5*(21)+9],COLOR_PAIR(15));

    wbkgd(pixels[1+2*(21)+12],COLOR_PAIR(16));
    wbkgd(pixels[1+3*(21)+12],COLOR_PAIR(16));
    wbkgd(pixels[1+4*(21)+12],COLOR_PAIR(16));
    wbkgd(pixels[1+5*(21)+12],COLOR_PAIR(16));
    wbkgd(pixels[1+2*(21)+13],COLOR_PAIR(16));
    wbkgd(pixels[1+3*(21)+14],COLOR_PAIR(16));
    wbkgd(pixels[1+4*(21)+13],COLOR_PAIR(16));
    wbkgd(pixels[1+5*(21)+14],COLOR_PAIR(16));

    wbkgd(pixels[1+0*(21)+16],COLOR_PAIR(11));
    wbkgd(pixels[1+2*(21)+16],COLOR_PAIR(11));
    wbkgd(pixels[1+3*(21)+16],COLOR_PAIR(11));
    wbkgd(pixels[1+4*(21)+16],COLOR_PAIR(11));
    wbkgd(pixels[1+5*(21)+16],COLOR_PAIR(11));
    
    wbkgd(pixels[1+3*(21)+18],COLOR_PAIR(10));
    wbkgd(pixels[1+3*(21)+19],COLOR_PAIR(10));
    wbkgd(pixels[1+3*(21)+20],COLOR_PAIR(10));
    wbkgd(pixels[1+4*(21)+18],COLOR_PAIR(10));
    wbkgd(pixels[1+5*(21)+18],COLOR_PAIR(10));
    wbkgd(pixels[1+5*(21)+19],COLOR_PAIR(10));
    wbkgd(pixels[1+5*(21)+20],COLOR_PAIR(10));
    wbkgd(pixels[1+6*(21)+20],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+20],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+19],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+18],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+17],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+16],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+15],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+14],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+13],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+12],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+11],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+10],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+9],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+8],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+7],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+6],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+5],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+4],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+3],COLOR_PAIR(10));
    wbkgd(pixels[1+7*(21)+2],COLOR_PAIR(10));
    for (i=0;i<8;i++) {
        for (j=0;j<21;j++) {
            wrefresh(pixels[1+i*(21)+j]);
        }
    }
    return pixels;
}

WINDOW **draw_matrix() {
    int i, j;
    WINDOW **items;
    items = (WINDOW **)malloc(205*sizeof(WINDOW *));
    items[0] = create_newwin(22,22,(LINES-22)/2,(COLS-22)/2);
    for (i=0;i<20;i++) {
        for (j=0;j<10;j++) {
            items[1+i*(10)+j] = subwin(items[0],1,2,(i+2)+LINES/2-12,(j*2+2)+COLS/2-12);
            wrefresh(items[1+i*(10)+j]);
        }
    }
    return items;
}

void redraw_matrix(WINDOW **items, int matrix_B[20][10], struct Tblock current_block, int level) {
    int i, j;
    wbkgd(items[0],COLOR_PAIR(0));
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 10; j++) {
            /*wbkgd(items[1+i*10+j],COLOR_PAIR(0));*/
            if (matrix_B[i][j] == 1) {
                wbkgd(items[1+i*10+j],COLOR_PAIR(10+level));
                wrefresh(items[1+i*(10)+j]);
            }
        }
    }
    wrefresh(items[0]);
    items[201]=subwin(items[0],1,2,LINES/2-12+1+current_block.ay*(-1)+current_block.offset_y,COLS/2-13+1+current_block.ax*2+current_block.offset_x);
    items[202]=subwin(items[0],1,2,LINES/2-12+1+current_block.by*(-1)+current_block.offset_y,COLS/2-13+1+current_block.bx*2+current_block.offset_x);
    items[203]=subwin(items[0],1,2,LINES/2-12+1+current_block.cy*(-1)+current_block.offset_y,COLS/2-13+1+current_block.cx*2+current_block.offset_x);
    items[204]=subwin(items[0],1,2,LINES/2-12+1+current_block.dy*(-1)+current_block.offset_y,COLS/2-13+1+current_block.dx*2+current_block.offset_x);
    for (i=201; i<205; i++) {
        wbkgd(items[i],COLOR_PAIR(10+current_block.type));
        wrefresh(items[i]);
    }
}

WINDOW **draw_next_block_window() {
    WINDOW **items;
    items = (WINDOW **)malloc(5*sizeof(WINDOW *));
    items[0] = create_newwin(6,12,(LINES-6)/2-8,(COLS-12)/2+18);
    wattron(items[0],A_BOLD);
    mvwprintw(items[0],5,4,"NEXT");
    wrefresh(items[0]);
    return items;
}

void redraw_next_block_window(WINDOW **items, struct Tblock next_block) {
    int i;
    int symmetric_offset = 0;
    if (next_block.type <= 1)
        symmetric_offset = 1;
    for (i=1; i<5; i++) {
        wbkgd(items[i],COLOR_PAIR(0));
        wrefresh(items[i]);
    }
    items[1]=subwin(items[0],1,2,(LINES-6)/2+next_block.ay*(-1)+2-8,(COLS-12)/2+next_block.ax*2+5+18+symmetric_offset);
    items[2]=subwin(items[0],1,2,(LINES-6)/2+next_block.by*(-1)+2-8,(COLS-12)/2+next_block.bx*2+5+18+symmetric_offset);
    items[3]=subwin(items[0],1,2,(LINES-6)/2+next_block.cy*(-1)+2-8,(COLS-12)/2+next_block.cx*2+5+18+symmetric_offset);
    items[4]=subwin(items[0],1,2,(LINES-6)/2+next_block.dy*(-1)+2-8,(COLS-12)/2+next_block.dx*2+5+18+symmetric_offset);
    for (i=1; i<5; i++) {
        wbkgd(items[i],COLOR_PAIR(10+next_block.type));
        wrefresh(items[i]);
    }
}

WINDOW *draw_score_window() {
    WINDOW *win;
    win = create_newwin(5,12,(LINES-4)/2-2,(COLS-12)/2+18);
    wattron(win,A_BOLD);
    mvwprintw(win,4,4,"SCORE");
    wrefresh(win);
    return win;
}

void redraw_score_window(WINDOW *win, int score) {
    char *score_string;
    char buffer[9] = "";
    score_string = itoa(score);
    int n=0;
    while(n<7) {
        strcat(buffer,"0");
        if ((strlen(buffer)+strlen(score_string)) == 8) {
            strcat(buffer,score_string);
            strcpy(score_string,buffer);
        }
        n++;
    }
    mvwprintw(win,2,2,score_string);
    wrefresh(win);
}

WINDOW *draw_hiscore_window() {
    WINDOW *win;
    win = create_newwin(5,12,(LINES-4)/2+3,(COLS-12)/2+18);
    wattron(win,A_BOLD);
    mvwprintw(win,4,2,"HI-SCORE");
    wrefresh(win);
    return win;
}

void redraw_hiscore_window(WINDOW *win, int hiscore) {
    char *hiscore_string;
    char buffer[9] = "";
    hiscore_string = itoa(hiscore);
    int n=0;
    while(n<7) {
        strcat(buffer,"0");
        if ((strlen(buffer)+strlen(hiscore_string)) == 8) {
            strcat(buffer,hiscore_string);
            strcpy(hiscore_string,buffer);
        }
        n++;
    }
    mvwprintw(win,2,2,hiscore_string);
    wrefresh(win);
}

WINDOW *draw_level_window() {
    WINDOW *win;
    win = create_newwin(4,12,(LINES-4)/2+9,(COLS-12)/2+18);
    wattron(win,A_BOLD);
    mvwprintw(win,3,4,"LEVEL");
    wrefresh(win);
    return win;
}

void redraw_level_window(WINDOW *win, int level) {
    char *level_string;
    level_string = itoa(level);
    mvwprintw(win,1,6,level_string);
    wrefresh(win);
}

WINDOW *draw_stats_lines_window() {
    WINDOW *win;
    win = create_newwin(9,12,(LINES-10)/2-6,(COLS-12)/2-18);
    wattron(win,A_BOLD);
    mvwprintw(win,8,4,"LINES");
    wrefresh(win);
    return win;
}

void redraw_stats_lines_window(WINDOW *win, int lines, int Single, int Double, int Triple, int Tetris) {
    char *string;
    char buffer[8] = "";
    
    string = itoa(lines);
    mvwprintw(win,6,2,string);
    
    strcpy(buffer,"1x");
    string = itoa(Single);
    strcat(buffer,string);
    mvwprintw(win,1,2,buffer);
    
    strcpy(buffer,"2x");
    string = itoa(Double);
    strcat(buffer,string);
    mvwprintw(win,2,2,buffer);
    
    strcpy(buffer,"3x");
    string = itoa(Triple);
    strcat(buffer,string);
    mvwprintw(win,3,2,buffer);
    
    strcpy(buffer,"4x");
    string = itoa(Tetris);
    strcat(buffer,string);
    mvwprintw(win,4,2,buffer);

    wrefresh(win);
}

WINDOW **draw_stats_blocks_window(int blocks, int O, int I, int S, int Z, int L, int J, int T) {
    WINDOW **items;
    int i;
    items = (WINDOW **)malloc(8*sizeof(WINDOW *));
    items[0] = create_newwin(12,12,(LINES-12)/2+5,(COLS-12)/2-18);
    
    wattron(items[0],A_BOLD);
    mvwprintw(items[0],11,3,"PIECES");
    
    for (i=1;i<8;i++) {
        items[i] = subwin(items[0],1,10,(LINES-12)/2+i+5,(COLS-12)/2+1-18);
        wrefresh(items[i]);
    }
    wrefresh(items[0]);
    for (i = 0; i< 7; i++) {
        wbkgd(items[i+1],COLOR_PAIR(20+i));
        wrefresh(items[i+1]);
    }
    return items;
}

void redraw_stats_blocks_window(WINDOW **items, int blocks, int O, int I, int S, int Z, int L, int J, int T) {
    int i;
    char *string;
    char buffer[9] = "";

    string = itoa(blocks);
    mvwprintw(items[0],9,2,string);
    
    strcpy(buffer,"Ox");
    string = itoa(O);
    strcat(buffer,string);
    mvwprintw(items[1],0,0,buffer);
    
    strcpy(buffer,"Ix");
    string = itoa(I);
    strcat(buffer,string);
    mvwprintw(items[2],0,0,buffer);
    
    strcpy(buffer,"Sx");
    string = itoa(S);
    strcat(buffer,string);
    mvwprintw(items[3],0,0,buffer);
    
    strcpy(buffer,"Zx");
    string = itoa(Z);
    strcat(buffer,string);
    mvwprintw(items[4],0,0,buffer);
    
    strcpy(buffer,"Lx");
    string = itoa(L);
    strcat(buffer,string);
    mvwprintw(items[5],0,0,buffer);
    
    strcpy(buffer,"Jx");
    string = itoa(J);
    strcat(buffer,string);
    mvwprintw(items[6],0,0,buffer);
    
    strcpy(buffer,"Tx");
    string = itoa(T);
    strcat(buffer,string);
    mvwprintw(items[7],0,0,buffer);
    
    wrefresh(items[0]);
    for (i = 0; i< 7; i++) {
        wrefresh(items[i+1]);
    }

}

WINDOW *draw_message_window(int message) {
    WINDOW *win;
    win = create_newwin(3,16,(LINES-4)/2,(COLS-16)/2);
    switch(message) {
        case 1:
            wbkgd(win,COLOR_PAIR(26));
            wattron(win,A_BOLD);
            mvwprintw(win,1,6,"PAUSE");
        break;
        case 2:
            wbkgd(win,COLOR_PAIR(25));
            wattron(win,A_BOLD);
            mvwprintw(win,1,4,"GAME OVER");
        break;
    }
    wrefresh(win);
    return win;
}

void draw_help() {
    WINDOW *win;
    win = create_newwin(8,27,6+(LINES-8)/2,(COLS-27)/2);
    mvwprintw(win,1,2,"W    UP       rotate");
    mvwprintw(win,2,2,"A    LEFT     move left");
    mvwprintw(win,3,2,"D    RIGHT    move right");
    mvwprintw(win,4,2,"S    DOWN     move down");
    mvwprintw(win,5,2,"P             pause");
    mvwprintw(win,6,2,"ESC           exit");
    wrefresh(win);

    while(getch()!=ESCAPE) {}
    
    destroy_win(win);
}

void draw_hiscores(int mode, int score) {
    WINDOW *win;
    win = create_newwin(7,30,6+(LINES-8)/2,(COLS-30)/2);
    struct Hscores winners[6];
    struct Hscores buffer;
    int i;

    FILE *f = fopen("save", "rb");
    if (f == NULL) {
        f = fopen("save", "wb");
        buffer.score = 0;
        strcpy(buffer.name,"anonymus");
        for (i=0; i<5; i++) {
            fwrite(&buffer.score,sizeof(int),1,f);
        }
        for (i=0; i<5; i++) {
            fwrite(&buffer.name,sizeof(char),9,f);
        }
        fclose(f);
        f = fopen("save", "rb");
    }
    
    for (i=0; i<5; i++) {
        fread(&buffer.score,sizeof(int),1,f);
        winners[i].score = buffer.score;
        winners[i].num = i+1;
        mvwprintw(win,i+1,1,itoa(1+i));
        mvwprintw(win,i+1,5,itoa(buffer.score));
    }
    for (i=0; i<5; i++) {
        fread(&buffer.name,sizeof(char),9,f);
        strcpy(winners[i].name,buffer.name);
        mvwprintw(win,i+1,21,buffer.name);
    }
    fclose(f);
    
    if (mode == 1) {
        winners[5].num = 6;
        strcpy(winners[5].name,"        ");
        winners[5].score = score;
        
        sort_scores(winners);
        int count = 0;
        int b = 0;
        for (i=0;i<5;i++) {
            if (winners[i].num == 6) {
                count = i;
                b = 1;
                break;
            }
        }

        if (b == 1) {
            for (i=0; i<5; i++) {
                mvwprintw(win,i+1,1,itoa(1+i));
                mvwprintw(win,i+1,5,itoa(winners[i].score));
                mvwprintw(win,i+1,21,winners[i].name);
            }
            wrefresh(win);
        
            char ch=' ';
            static char str[8] = "";
            for (i=0; i<8; i++) {
                str[i] = ' ';
            }
            i = 0;
            mvprintw(LINES/2+10,COLS/2-15,"Enter your name: ");
            mvprintw(LINES/2+9,COLS/2-15,"Your score: ");
            mvaddch(LINES/2+10,COLS/2+6+i,'_');
            mvprintw(LINES/2+9,COLS/2+6,itoa(score));
            while ((ch!=ENTER)) {
                if ((i>=0) && (i<9)) {
                    ch=getch();
                    if (ch==DELETE) {
                        if (i>0) {
                            mvdelch(LINES/2+10,COLS/2+6+i-1);
                            mvaddch(LINES/2+10,COLS/2+6+i-1,'_');
                            str[i-1] = ' ';
                            i--;
                        }
                    }
                    else {
                        if ((i<8) && (ch!=ENTER)) {
                            mvaddch(LINES/2+10,COLS/2+6+i+1,'_');
                            mvaddch(LINES/2+10,COLS/2+6+i,ch);
                            str[i] = ch;
                            i++;
                        }
                    }
                }
            }
            if (strcmp(str,"        ")==0) {
                strcpy(winners[count].name,"anonymus");
            }
            else {
                strcpy(winners[count].name,str);
            }
            mvwprintw(win,count+1,21,winners[count].name);
            wrefresh(win);
            
            f = fopen("save", "wb");
            for (i=0; i<5; i++) {
                buffer.score = winners[i].score;
                fwrite(&buffer.score,sizeof(int),1,f);
            }
            for (i=0; i<5; i++) {
                strcpy(buffer.name,winners[i].name);
                fwrite(&buffer.name,sizeof(char),9,f);
            }
            fclose(f);
        }
    }
    wrefresh(win);
    
    while(getch()!=ESCAPE) {}
    
    destroy_win(win);
    clear();
    refresh();
}
