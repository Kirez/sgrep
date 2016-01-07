/*
    © 2015-2016 Erik Källberg - kalerik@studen.chalmers.se
*/

#include "state_parser.h"

/*
    Turns user supplied arguments into a runnable sgrep_state struct
    See sgrep.h for structure
*/

parse_state_result parse_state(int argc, string *argv, sgrep_state *state_dst) {
    if (argc < 1 || argv == NULL || state_dst == NULL) {return PARSE_STATE_BAD_INDATA;}

    byte opts = 0;

    string search_string = NULL;
    FILE *stream = stdin;

    for (int i = 0; i < argc; i++) {
        string arg = argv[i];

        if (strcmp(arg, "-i") == 0) {
            opts = opts | OPT_CASE_SENSITIVE;
        }
        else if (strcmp(arg, "-n") == 0) {
            opts = opts | OPT_LINE_NUMBER;
        }
        else if (strcmp(arg, "-c") == 0) {
            opts = opts | OPT_COUNT;
        }
        else if (strcmp(arg, "--help") == 0) {
            opts = OPT_HELP;
            state_dst->options = opts;
            return PARSE_STATE_BAD_INDATA;
        }
        else if (i+2 == argc) { /*Assume format sgrep [OPTIONS] [PATTERN] [FILE]*/
            search_string = arg;
        }
        else if (i+1 == argc) {
            if (search_string == NULL) { /*This means that the format is: sgrep [OPTIONS] PATTERN*/
                search_string = arg;
            }
            else {
                stream = fopen(arg, "r"); /*format sgrep [OPTIONS] [PATTERN] [FILE] was correct*/
            }
        }
        else {
            return PARSE_STATE_MALFORMED_ARGS;
        }
    }

    if (stream == NULL) {
        return PARSE_STATE_NO_STREAM_CONNECTION;
    }
    else if (search_string == NULL) {
        return PARSE_STATE_UNKOWN_ERROR;
    }

    state_dst->search_string = search_string;
    state_dst->data_stream = stream;
    state_dst->options = opts;

    return PARSE_STATE_OK;
}
