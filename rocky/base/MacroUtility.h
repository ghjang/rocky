#ifndef ROCKY_BASE_MACRO_UTILITY_H
#define ROCKY_BASE_MACRO_UTILITY_H


#define CREATE_PLACEHOLDER_FILLER_0(...)  \
            ((__VA_ARGS__)) CREATE_PLACEHOLDER_FILLER_1
#define CREATE_PLACEHOLDER_FILLER_1(...)  \
            ((__VA_ARGS__)) CREATE_PLACEHOLDER_FILLER_0
#define CREATE_PLACEHOLDER_FILLER_0_END
#define CREATE_PLACEHOLDER_FILLER_1_END



#define TO_STR_IMPL(s) #s
#define TO_STR(s) TO_STR_IMPL(s)


#endif // ROCKY_BASE_MACRO_UTILITY_H