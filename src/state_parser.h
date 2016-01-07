#include "sgrep.h"
#include <string.h>
#include <stdio.h>

typedef enum parse_state_result {
    PARSE_STATE_OK,
    PARSE_STATE_BAD_INDATA,
    PARSE_STATE_MALFORMED_ARGS,
    PARSE_STATE_NO_STREAM_CONNECTION,
    PARSE_STATE_UNKOWN_ERROR
}   parse_state_result;

parse_state_result parse_state(int argc, string *argv, sgrep_state *state_dst);
