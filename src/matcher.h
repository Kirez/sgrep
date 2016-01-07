#include <string.h>
#include "sgrep.h"

typedef enum find_result {
    RESULT_MATCH,
    RESULT_NO_MATCH
}  find_result;

find_result find(string search_string, string data);
