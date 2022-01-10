#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

// echo 'string' | sed -E 's/regexp/substitution/'

#define MAX_MATCH 5

char* geterror(int errcode, regex_t *compiled) {
    size_t len = regerror(errcode, compiled, NULL, 0);
    char* buffer = (char*) malloc(len);
    regerror(errcode, compiled, buffer, len);
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Wrong parameters\n");
        printf("Usage: {regexp} {substitution} {string}\n");
    }

    regex_t input_re;
    regmatch_t pm_regex[MAX_MATCH];

    int ret;

    // match regex
    ret = regcomp(&input_re, argv[1], REG_EXTENDED);
    if (ret) {
        char* buffer = geterror(ret, &input_re);
        printf("Wrong regex: %s\n", buffer);
        regfree(&input_re);
        free(buffer);
        return 1;
    }
    ret = regexec(&input_re, argv[3], MAX_MATCH, pm_regex, 0);
    if (ret) {
        // return original string
        printf("%s\n", argv[3]);
        regfree(&input_re);
        return 1;
    }
    int i;
    int size_pm_regex;
    for (int i = 0; i < MAX_MATCH && pm_regex[i].rm_so != -1;) {
        size_pm_regex = i++;
    }

    // collapse double slashed
    i = 0;
    for (int j = 0; j < strlen(argv[2]); i++, j++) {
        if ((j < strlen(argv[2]) - 1) && (argv[2][j] == '\\') && (argv[2][j+1] == '\\')) {
            j++;
        }
        argv[2][i] = argv[2][j];
    }
    argv[2][i] = '\0';

    // match substitution
    regex_t subst_re;
    regmatch_t pm_sub[MAX_MATCH];

    // search pockets in substitution
    ret = regcomp(&subst_re, "[0-9]+", REG_EXTENDED);
    if (ret) {
        char* buffer = geterror(ret, &subst_re);
        printf("Wrong regex: %s\n", buffer);
        regfree(&input_re);
        regfree(&subst_re);
        free(buffer);
        return 1;
    }

    i = 0;
    int num_pockets = 0;
    regmatch_t tmp[1];
    while (i < strlen(argv[2])) {
        ret = regexec(&subst_re, &argv[2][i], 1, tmp, 0);
        if (ret) {
            break;
        } else {
            if (argv[2][i + tmp[0].rm_so - 1] == '\\') {
                pm_sub[num_pockets].rm_so = i + tmp[0].rm_so;
                pm_sub[num_pockets].rm_eo = i + tmp[0].rm_eo;
                num_pockets += 1;
            }
            i = i + tmp[0].rm_eo;
        }
    }
    // printf("%d\n", size_pm_regex);

    // check pocket values (must be less than pm_regex size)
    for (int i = 0; i < num_pockets; i++) {
        char* start = &argv[2][pm_sub[i].rm_so], *end;
        // printf("strol %ld\n", strtol(start, &end, 10));
        if (strtol(start, &end, 10) > size_pm_regex) {
            printf("Invalid pocket number: %ld\n", strtol(start, &end, 10));
            regfree(&input_re);
            regfree(&subst_re);
            return 1;
        }
    }

    // subtitute pm_regex[0] by substitution
    int end_idx = 0;
    char* changed_str = (char*) malloc(strlen(argv[3] + strlen(argv[2])));
    strncpy(changed_str, argv[3], pm_regex[0].rm_so);
    end_idx = pm_regex[0].rm_so;

    int sub_idx = 0;
    fflush(stdout);
    for (int i = 0; i < num_pockets; i++) {
        // copy all berfore pocket and paste pocket
        int n_chars = pm_sub[i].rm_so - sub_idx - 1;
        strncpy(&changed_str[end_idx], &argv[2][sub_idx], n_chars);
        end_idx += n_chars;
        sub_idx += n_chars;

        char* end;
        int pocket_idx = strtol(&argv[2][pm_sub[i].rm_so], &end, 10);
        int start_pocket = pm_regex[pocket_idx].rm_so;
        int end_pocket = pm_regex[pocket_idx].rm_eo;
        n_chars = end_pocket - start_pocket;
        strncpy(&changed_str[end_idx], &argv[3][start_pocket], n_chars);
        end_idx += n_chars;
        sub_idx = pm_sub[i].rm_eo;
    }
    // copy all after last pocket
    strncpy(&changed_str[end_idx], &argv[2][sub_idx], strlen(argv[2]) - sub_idx);
    end_idx += strlen(argv[2]) - sub_idx;

    // copy residual of source string
    strncpy(&changed_str[end_idx], &argv[3][pm_regex[0].rm_eo], strlen(argv[3]) - pm_regex[0].rm_eo);
    end_idx += strlen(argv[3]) - pm_regex[0].rm_eo;
    changed_str[end_idx] = '\0';
    printf("%s\n", changed_str);

    regfree(&input_re);
    regfree(&subst_re);
    free(changed_str);
}