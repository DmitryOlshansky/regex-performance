#include <stdio.h>

#include "main.h"

#include "dlang.h"

int d_find_all(char * pattern, char * subject, int subject_len, int repeat, struct result * res)
{
    TIME_TYPE start, end;
    int found = 0;

    struct D_Regex* regex = new_regex(pattern);
    if (regex == NULL) {
        fprintf(stderr, "ERROR: Unable to compile pattern \"%s\"\n", pattern);
        return -1;
    }

    double * times = calloc(repeat, sizeof(double));
    int const times_len = repeat;

    do {
        GET_TIME(start);
        found = find_matches(regex, subject, subject_len);
        GET_TIME(end);

        times[repeat - 1] = TIME_DIFF_IN_MS(start, end);

    } while (--repeat > 0);

    res->matches = found;
    get_mean_and_derivation(times, times_len, res);

    free(times);

    return 0;
}
