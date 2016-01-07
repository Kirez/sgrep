#ifndef SGREP_H
#define SGREP_H

#include <stdio.h>

typedef char* string;
typedef unsigned char byte;

/*
    Option flags to be stored in a unsigned char / byte
    Example:
        options =   0000 0101
                         ||||
                         |||+- OPT_CASE_SENSITIVE is set
                         ||+-- OPT_COUNT is not set
                         |+--- OPT_LINE_NUMBER is set
                         +---- OPT_HELP is not set
    Usage:
        Adding:
            options = options | OPT_CASE_SENSITIVE; --options now contain OPT_CASE_SENSITIVE
        Checking:
            if (options & OPT_CASE_SENSITIVE) {do case sensitive stuff}
*/
typedef enum option_flags {
    OPT_CASE_SENSITIVE  = 0x01,
    OPT_COUNT           = 0x02,
    OPT_LINE_NUMBER     = 0x04,
    OPT_HELP            = 0x08
}   option_flags;

/*sgrep runnable state*/
typedef struct sgrep_state {
    byte options; /*User supplied flag option byte*/
    string search_string;
    FILE *data_stream; /*defaults to stdin but could be a file from the filesystem*/
}   sgrep_state;

#endif
