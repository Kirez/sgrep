/*
    © 2015-2016 Erik Källberg - kalerik@student.chalmers.se
*/

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "sgrep.h"
#include "state_parser.h"
#include "matcher.h"

typedef enum RETURN_CODES {
    MATCH       = 0,
    NO_MATCH    = 1,
    FAILURE     = 2,
}   RETURN_CODES;

void print_usage();
string lower_case();
int run_state(sgrep_state *state);

int main(int argc, char **argv) {

    /*Exclude the first, in this case useless, argument*/
    argc--;
    argv++;

    /*sgrep state container*/
    sgrep_state state;

    /*try parsing user supplied arguments into a runnable state*/
    int ps_result = parse_state(argc, argv, &state);


    if (state.options & OPT_HELP) {
        print_usage();
        return NO_MATCH; /*in case the user asked for help there will not be a run of sgrep*/
    }
    else if (ps_result == PARSE_STATE_OK) {
        return run_state(&state); /*user supplied arguments were successfully parsed and will now run*/
    }
    else if (ps_result == PARSE_STATE_MALFORMED_ARGS) {
        print_usage(); /*user supplied arguments were not understandable -> FAILURE*/
        return FAILURE;
    }
    else {
        printf("%s\n", "Parse failed!");
        return FAILURE;
    }
}

void print_usage() {
    printf("%s\n", "Usage: sgrep [OPTION]... PATTERN [FILE]");
    printf("%s\n", "Options:");
    printf("%s\n", "    -i      ignore case distinctions");
    printf("%s\n", "    -n      print line number with output lines");
    printf("%s\n", "    -c      print only a count of matching lines");
    printf("%s\n", "If no [FILE] is specified sgrep reads standard input instead");
}

string lower_case(string src) { /*Returns a lowercase [COPY] of src*/
    string lower = malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(lower, src);

    for (int i = 0; lower[i]; i++) {
        lower[i] = tolower(lower[i]);
    }

    return lower;
}

int run_state(sgrep_state *state) { /*The DO part of sgrep*/
    string line = NULL;
    size_t size = 0;

    /*Overkill ensurance that sgrep won't crash on by ridiculous amount of lines*/
    unsigned long long line_number = 0;
    unsigned long long match_count = 0;

    while (getline(&line, &size, state->data_stream) != -1) {
        int l_len = strlen(line);

        if (line[l_len - 1] == '\n') { /*getline may or may not give a line with a newline at end*/
            line[l_len - 1] = '\0'; /*This ensures there is none*/
        }

        string ss, l;

        if (state->options & OPT_CASE_SENSITIVE) {
            ss = lower_case(state->search_string);
            l = lower_case(line);
        }
        else {
            ss = state->search_string;
            l = line;
        }

        if (find(ss, l) == RESULT_MATCH) {
            match_count++;
            if (!(state->options & OPT_COUNT)) {
                if (state->options & OPT_LINE_NUMBER) {
                    printf("%llu%c", line_number, ':');
                }
                printf("%s\n", line);
            }
        }

        line_number++;

        free(line); /*getline allocated this for us automatically but must be freed manually*/

        if (state->options & OPT_CASE_SENSITIVE) { /*only if copies were made*/
            free(ss);
            free(l);
        }

        line = NULL;
    }

    free(line);

    if (state->options & OPT_COUNT) {
        printf("%llu\n", match_count);
    }

    if (match_count > 0) { return MATCH; }
    else { return NO_MATCH; }
}
