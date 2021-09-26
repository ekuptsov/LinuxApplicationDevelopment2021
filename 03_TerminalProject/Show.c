#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#define DX 3


int min(int a, int b) {
    return (a < b) ? a : b;
}


void draw_win(WINDOW* win, char* text, size_t offset, int line_nmb, int height) {
    for (int i = 0; i < height; i++) {
        /* '%.6s' print 6 chars of string
           len of printing string is constant
           and equals ~to the number of columns because
           line_nmb from 1 to 99999 (hold from 1 to 5 positions)
        */
        wprintw(win, " %d: %.*s\n", line_nmb+1, COLS-3*DX+1-8, text + offset);
        offset += (size_t)strlen(text + offset) + 1;
        line_nmb += 1;
        wrefresh(win);
    }
    box(win, 0, 0);
}


int main (int argc, char* argv[])
{

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {;
        printf("File not found!\n");
        exit(-1);
    }

    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* text = malloc((fsize+1) * sizeof(char));

    char *line = NULL;
    size_t len = 0;
    ssize_t n;
    int pos = 0;
    int num_lines = 0;
    while ((n = getline(&line, &len, fp)) != -1) {
        /* read n bytes from fp and store them in line */
        if (line[n-1] == '\n') {
            line[n-1] = '\0';
        }
        strncpy(&text[pos], line, n);
        pos += n;
        num_lines += 1;
    }
    if (line) {
        free(line);
    }

    int retval = fclose(fp);
    if (retval == -1) {
        printf("Cant't close file!");
        exit(-1);
    }

    WINDOW* win;

    initscr();
    noecho();
    cbreak();
    printw("File: %s; size: %d", argv[1], num_lines);
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);
    box(win, 0, 0);
    wmove(win, 1, 0);

    size_t offset = 0;
    int num_space_keys = 0;
    draw_win(win, text, offset, num_space_keys, min(num_lines, LINES-3*DX+1));
    offset += (size_t)strlen(text + offset) + 1;
    num_space_keys += 1;

    char key;
    while (key = wgetch(win)) {
        if (key == 32) {
            // if press space key
            if (num_space_keys <= num_lines - (LINES-3*DX+1)) {
                werase(win);
                wmove(win, 1, 0);
                draw_win(win, text, offset, num_space_keys, LINES-3*DX+1);
                offset += (size_t)strlen(text + offset) + 1;
                num_space_keys += 1;
            }
        } else if (key == 27) {
            // if press esc key
            endwin();
            break;
        }
    }

    free(text);
}