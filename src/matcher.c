/*
    © 2015-2016 Erik Källberg - kalerik@studen.chalmers.se
*/

#include "matcher.h"

find_result find(string search_string, string data) {
if (strcmp(search_string, "") == 0) {return RESULT_MATCH;}

int ss_len = strlen(search_string);
int d_len = strlen(data);

if (ss_len > d_len) {return RESULT_NO_MATCH;}

for (int i = 0; i < d_len - ss_len + 1; i++) {
    for (int c = 0; c < ss_len; c++) {
        if (search_string[c] != data[i+c]) {break;}
        else if (c+1 == ss_len) {
            if (search_string[c] == data[i+c]) {
                return RESULT_MATCH;
            }
        }
    }
}

    return RESULT_NO_MATCH;
}
