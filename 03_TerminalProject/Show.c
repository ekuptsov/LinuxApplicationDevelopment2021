#include <curses.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
        line[n-1] = '\0';
        strncpy(&text[pos], line, n);
        pos += n;
        num_lines += 1;
    }
    if (line) {
        free(line);
    }

    pos = 0;
    n = 0;
    for (int i = 0; i < num_lines; i++) {
        n = printf("%s\n", &text[pos]);
        pos += n;
    }

    // setlocale(LC_ALL, "ru_RU.utf8");
    // initscr ();
    // move (LINES/2 - 1, COLS/2 - 4);
    // addstr ("Па русски гавари");
    // getch ();
    // endwin ();
    free(text);
    int retval = fclose(fp);
    if (retval == -1) {
        printf("Cant't close file!");
        exit(-1);
    }
}