/** @file roman_binsearch.c
 * Main source file
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

/*! \def _(STRING)
    \brief A macro to translate programm output.
*/
#define _(STRING) gettext(STRING)
/*! \def N_(msgid)
    \brief A macro to translate --help.
*/
#define N_(msgid) msgid

#include <argp.h>

/*! \def MIN
    \brief A minimum guessed number.
*/

/*! \def MAX
    \brief A maximum guessed number.
*/

/*! \def ROMAN_LEN
    \brief A lenght of roman strings.
*/

#define MIN 1
#define MAX 100
#define ROMAN_LEN 8

// #define OPT_USAGE       -3

/* Program version. */
const char *argp_program_version = "roman_binsearch 0.0.1";

/* Program documentation. */
static char doc[] =
    N_("Roman binsearch -- a program guessing number from 1..100 (support roman output ex. I - 1, V - 5, C - 100).");

/*! \struct options
    \brief The options we understand.
*/
static struct argp_option options[] = {
    {"roman",         'r', 0, 0,  N_("Print numbers in roman numerial notation")},
    // {"help",          '?', 0, OPTION_HIDDEN,  N_("Give this help list"), -1},
    // {"usage",   OPT_USAGE, 0, OPTION_HIDDEN,  N_("Give a short usage message"), 0},
    // {"version",       'V', 0, OPTION_HIDDEN,  N_("Print program version")},
    { 0 }
};

/*! \struct arguments
    \brief Used by main to communicate with parse_opt.
*/
struct arguments
{
    char is_roman;           /*!< Flag to use roman. */
};

/*  */
/**
 * Parse a single option.
 *
 * @param key CommandLine option
 * @param arg Optional  key argument
 * @param state Internal parser state
 *
 *@returns Error status
 */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    // case '?':
    //   argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP);
    //     break;
    // case OPT_USAGE:
    //   argp_state_help(state, state->out_stream,
    //                      ARGP_HELP_USAGE | ARGP_HELP_EXIT_OK);
    //   break;
    case 'r':
        arguments->is_roman = 1;
        break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, 0, doc };

static char* roman_table[] = {
    "I       ", "II      ", "III     ", "IV      ", "V       ",
    "VI      ", "VII     ", "VIII    ", "IX      ", "X       ",
    "XI      ", "XII     ", "XIII    ", "XIV     ", "XV      ",
    "XVI     ", "XVII    ", "XVIII   ", "XIX     ", "XX      ",
    "XXI     ", "XXII    ", "XXIII   ", "XXIV    ", "XXV     ",
    "XXVI    ", "XXVII   ", "XXVIII  ", "XXIX    ", "XXX     ",
    "XXXI    ", "XXXII   ", "XXXIII  ", "XXXIV   ", "XXXV    ",
    "XXXVI   ", "XXXVII  ", "XXXVIII ", "XXXIX   ", "XL      ",
    "XLI     ", "XLII    ", "XLIII   ", "XLIV    ", "XLV     ",
    "XLVI    ", "XLVII   ", "XLVIII  ", "XLIX    ", "L       ",
    "LI      ", "LII     ", "LIII    ", "LIV     ", "LV      ",
    "LVI     ", "LVII    ", "LVIII   ", "LIX     ", "LX      ",
    "LXI     ", "LXII    ", "LXIII   ", "LXIV    ", "LXV     ",
    "LXVI    ", "LXVII   ", "LXVIII  ", "LXIX    ", "LXX     ",
    "LXXI    ", "LXXII   ", "LXXIII  ", "LXXIV   ", "LXXV    ",
    "LXXVI   ", "LXXVII  ", "LXXVIII ", "LXXIX   ", "LXXX    ",
    "LXXXI   ", "LXXXII  ", "LXXXIII ", "LXXXIV  ", "LXXXV   ",
    "LXXXVI  ", "LXXXVII ", "LXXXVIII", "LXXXIX  ", "XC      ",
    "XCI     ", "XCII    ", "XCIII   ", "XCIV    ", "XCV     ",
    "XCVI    ", "XCVII   ", "XCVIII  ", "XCIX    ", "C       ",
}; /* Table to map roman <-> decimal */

/**
 * Convert from roman numberical to decimal.
 *
 * @param raw_roman String of roman number
 * @param deciaml Pointer to store decimal equvalent
 *
 *@returns Error status
*/
int roman2decimal(char* raw_roman, int* decimal) {
    char* roman = raw_roman;
    if (strlen(roman) != ROMAN_LEN) {
        char tmp[ROMAN_LEN];
        strncpy(tmp, roman, strlen(roman));
        for (int i = strlen(roman); i < ROMAN_LEN; i++) tmp[i] = ' ';
        roman = tmp;
    }
    for (int i = 0; i < MAX; i++) {
        if (!strcmp(roman, roman_table[i])) {
            *decimal = i + 1;
            return 0;
        }
    }
    return 1;
}

/**
 * Convert from decimal to roman.
 *
 * @param raw_roman String of roman number
 * @param deciaml Pointer to store decimal equvalent
 *
 *@returns Pointer on roman string
*/
char* decimal2roman(int decimal, char* roman) {
    if (0 < decimal && decimal < 101) {
        // *roman = roman_table[decimal - 1];
        strncpy(roman, roman_table[decimal - 1], ROMAN_LEN);
        strtok(roman, " ");
        return roman;
    }
    return NULL;
}

/**
 * Convert int to str.
 *
 * @param value Input value
 * @param output Buffer to store str equivalent
 *
 * @returns Pointer on buffer
 */
char* itoa(int value, char* output) {
    int printed = sprintf(output, "%d", value);
    output[printed] = '\0';
    return output;
}


int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "");
    bindtextdomain("roman_binsearch", "po");
    textdomain("roman_binsearch");

    struct arguments arguments;

    /* Default values. */
    arguments.is_roman = 0;

    /* Parse our arguments; every option seen by parse_opt will
       be reflected in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    char* (*convert)(int, char*);
    convert = arguments.is_roman ? &decimal2roman : &itoa;

    char min[ROMAN_LEN], max[ROMAN_LEN];
    printf(_("Pick a number from %s to %s\n"),
           (*convert)(MIN, min), (*convert)(MAX, max));

    char* line = NULL;
    size_t len = 0;
    while (getchar() != '\n') {}
    int r = 101, l = -1, m;
    int repeat = 0;
    char tmpstr[ROMAN_LEN];
    while (r-l > 1) {
        if (!repeat)
            m = (r + l) / 2;
        printf(_("Is number greater or equal than %s? (y/n)\n"),
               (*convert)(m, tmpstr));
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
    printf(_("You pick a number: %s\n"), (*convert)(r-1, tmpstr));
    return 0;
}