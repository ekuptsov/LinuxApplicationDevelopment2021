#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

#define MAX 100

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "");
    bindtextdomain("binsearch", "po");
    textdomain("binsearch");

    printf(_("Pick a number from 0 to %d\n"), MAX);
    char* line = NULL;
    size_t len = 0;
    char c;
    while ((c = getchar()) != '\n') {;}
    int r = 101, l = -1;
    int m;
    int repeat = 0;
    while (r-l > 1) {
        if (!repeat)
            m = (r + l) / 2;
        printf(_("Is number greater or equal than %d? (y/n)\n"), m);
        getline(&line, &len, stdin);
        if (!strcmp(line, _("y\n"))) {
            l = m;
            repeat = 0;
        } else if (!strcmp(line, _("n\n"))) {
            r = m;
            repeat = 0;
        } else {
            repeat = 1;
        }
    }
    printf(_("You pick a number: %d\n"), r-1);
    return 0;
}