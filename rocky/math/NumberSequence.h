#ifndef ROCKY_MATH_NUMBER_SEQUENCE_H
#define ROCKY_MATH_NUMBER_SEQUENCE_H


#include <type_traits>


template <typename F>
class number_seq_generator
{
public:
    number_seq_generator(F const& f)
        : x_{ 0 }
        , f_{ f }
    { }
    
    number_seq_generator(F && f)
        : x_{ 0 }
        , f_{ std::move(f) }
    { }

public:
    auto operator () ()
    { return f_(x_++); }

private:
    int x_;
    F f_;
};


template <typename F>
auto number_seq(F && f)
{
    return number_seq_generator<std::decay_t<F>>{ std::forward<F>(f) };
}

#endif // ROCKY_MATH_NUMBER_SEQUENCE_H
