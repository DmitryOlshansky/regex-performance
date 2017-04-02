#include <stdint.h>

struct D_Regex;

struct D_Regex* new_regex(const char* pattern);
uint64_t find_matches(struct D_Regex* regex, const char* input, uint64_t length);
