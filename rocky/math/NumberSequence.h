#ifndef ROCKY_MATH_NUMBER_SEQUENCE_H
#define ROCKY_MATH_NUMBER_SEQUENCE_H


#include <type_traits>
#include <limits>


template <typename F, typename T>
class number_seq_generator
{
public:
    number_seq_generator(F const& f, T init, T increment, T max)
        : f_{ f }
        , x_{ init }
        , increment_{ increment }
        , max_{ max }
    { }

    number_seq_generator(F && f, T init, T increment, T max)
        : f_{ std::move(f) }
        , x_{ init }
        , increment_{ increment }
        , max_{ max }
    { }

public:
    auto operator () ()
    {
        if (x_ > max_) {
            // TODO: need to throw an exception
        }
        
        auto tmp{ f_(x_) };

        // TODO: need to check overflow.
        x_ += increment_;
        
        return tmp;
    }

private:
    F f_;
    T x_;
    T const increment_;
    T const max_;
};


template <typename F, typename T = int, typename U = T, typename V = T>
auto number_seq(F && f, T init = 0, U increment = 1, V max = std::numeric_limits<V>::max())
{
    assert(init <= max);
    if (init > max) {
        // TODO: throw an exception
    }
    return number_seq_generator<
                std::decay_t<F>,
                std::common_type_t<T, U, V>
           >{ std::forward<F>(f), init, increment, max };
}

#endif // ROCKY_MATH_NUMBER_SEQUENCE_H
