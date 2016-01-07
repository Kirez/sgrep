#include "../state_parser.h"
#include "../matcher.h"

typedef enum test_result {
    TEST_PASSED,
    TEST_FAILED
}   test_result;

test_result test_options(int argc, char **argv, byte expected);
test_result test_matcher(string search_string, string data, find_result expected);

int main(int argc, char **argv) {
    const unsigned int num_tests = 4;
    unsigned int passed = 0;

    printf("%s%d%s\n", "Performing ", num_tests, " tests...");

    /*TEST #1------------------------------------------------------------------*/

    int targc = 4;
    char *targv[4];
    targv[0] = "-i";
    targv[1] = "-n";
    targv[2] = "-c";
    targv[3] = "regex";

    byte b_expected = 0 | OPT_CASE_SENSITIVE | OPT_LINE_NUMBER | OPT_COUNT;

    printf("%s", "Performing test...");
    if (test_options(targc, targv, b_expected) == TEST_PASSED) {
        passed++;
        printf("%s\n", "passed!");
    }
    else {
        printf("%s\n", "failed!");
    }

    /*TEST #2------------------------------------------------------------------*/

    targc = 1;
    targv[0] = "regex";

    b_expected = 0;

    printf("%s", "Performing test...");
    if (test_options(targc, targv, b_expected) == TEST_PASSED) {
        passed++;
        printf("%s\n", "passed!");
    }
    else {
        printf("%s\n", "failed!");
    }

    /*TEST #3------------------------------------------------------------------*/

    printf("%s", "Performing test...");
    if (test_matcher("hello", "hello world", RESULT_MATCH) == TEST_PASSED) {
        passed++;
        printf("%s\n", "passed!");
    }
    else {
        printf("%s\n", "failed!");
    }

    /*TEST #4------------------------------------------------------------------*/

    printf("%s", "Performing test...");
    if (test_matcher("hello", "you shall not pass", RESULT_NO_MATCH) == TEST_PASSED) {
        passed++;
        printf("%s\n", "passed!");
    }
    else {
        printf("%s\n", "failed!");
    }

    if (passed == num_tests) {
        printf("%s%d%s\n", "Passed all ", num_tests, " tests.");
    }
    else {
        printf("%s%d%s%d%s\n", "Passed ", passed, " out of ", num_tests, " tests.");
    }

    return 0;
}

test_result test_options(int argc, char **argv, byte expected) {
    sgrep_state state;
    parse_state(argc, argv, &state);
    if (state.options != expected) {
        return TEST_FAILED;
    }

    return TEST_PASSED;
}

test_result test_matcher(string search_string, string data, find_result expected) {
    if (find(search_string, data) != expected) {
        return TEST_FAILED;
    }

    return TEST_PASSED;
}
