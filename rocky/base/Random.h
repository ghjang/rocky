#ifndef ROCKY_BASE_RANDOM_H
#define ROCKY_BASE_RANDOM_H


constexpr auto staticRand()
{
    int sum = 0;
    constexpr char s[] = __DATE__ __FILE__ __TIME__ __TIMESTAMP__;
    for (auto c : s) {
        sum += c;
    }
    for (auto c : __func__) {
        sum += c;
    }
    sum += __LINE__;
    sum += __STDC__;
    return sum;
}


#endif //ROCKY_BASE_RANDOM_H

