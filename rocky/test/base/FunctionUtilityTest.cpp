#include "../catch.hpp"

#include "rocky/base/FunctionUtility.h"


namespace
{
    int f(int a, int b, int c)
    {
        return a * b + c;
    }

    struct A { };

    struct B
    {
        operator int () const
        { return 0; }
    };

    struct C
    {
        operator std::string () const
        { return ""; }
    };

    /**
     * NOTE: D is not DefaultConstructable.
     */
    struct D
    {
        D(int, int)
        { }

        operator int () const
        { return 0; }
    };

    int g(int a, int b, int c)
    {
        return a * b + c;
    }

    int g(int a, int b)
    {
        return a * b;
    }
} // un-named namespace


TEST_CASE("decltype on overloaded functions", "[FunctionUtility]")
{
    //decltype(g) g_;
}

TEST_CASE("FunctionParameterListSize", "[FunctionUtility]")
{
    static_assert(1 == FunctionParameterListSize<decltype(fclose)>(), "");
    static_assert(1 == FunctionParameterListSize<decltype((fclose))>(), "");
    static_assert(1 == FunctionParameterListSize<decltype(&fclose)>(), "");

    static_assert(2 == FunctionParameterListSize<decltype(fopen)>(), "");

    static_assert(0 == FunctionParameterListSize<decltype(getchar)>(), "");
}

TEST_CASE("IsCallableWith for normal function", "[FunctionUtility]")
{
    // NOTE: f requires exactly three arguments compatible with int type.

    static_assert(IsCallableWith<decltype(f), TypeList<int, int, int>>(), "");
    static_assert(IsCallableWith<decltype(f), TypeList<B, int, int>>(), "");

    // A and C are not convertable to int.
    static_assert(!IsCallableWith<decltype(f), TypeList<A, int, int>>(), "");
    static_assert(!IsCallableWith<decltype(f), TypeList<C, int, int>>(), "");

    // less arguments
    static_assert(!IsCallableWith<decltype(f), TypeList<int, int>>(), "");

    // more arguments
    static_assert(!IsCallableWith<decltype(f), TypeList<int, int, int, int>>(), "");
}

TEST_CASE("IsCallableWith for Function-like Object", "[FunctionUtility]")
{
    // TODO: need to add more cases.

    struct F
    {
        int operator () (int a, int b, int c) const
        { return a * b + c; }

        int operator () (int a, int b) const
        { return a * b; }
    };

    static_assert(IsCallableWith<decltype(F()), TypeList<int, int, int>>(), "");
    static_assert(IsCallableWith<decltype(F()), TypeList<B, int, int>>(), "");

    // A and C are not convertable to int.
    static_assert(!IsCallableWith<decltype(F()), TypeList<A, int, int>>(), "");
    static_assert(!IsCallableWith<decltype(F()), TypeList<C, int, int>>(), "");

    // F also has an overloaded function operator member function for two int arguments.
    static_assert(IsCallableWith<decltype(F()), TypeList<int, int>>(), "");

    // more arguments
    static_assert(!IsCallableWith<decltype(F()), TypeList<int, int, int, int>>(), "");
}

TEST_CASE("IsCallableWith for Lambda Expression Closure Object", "[FunctionUtility]")
{
    // NOTE: compile error: lambda expression in an unevaluated operand
    //decltype([](int a, int b, int c) { return a * b + c; });

    auto l = [](int a, int b, int c) { return a * b + c; };

    static_assert(IsCallableWith<decltype(l), TypeList<int, int, int>>(), "");
    static_assert(IsCallableWith<decltype(l), TypeList<B, int, int>>(), "");

    static_assert(!IsCallableWith<decltype(l), TypeList<A, int, int>>(), "");
    static_assert(!IsCallableWith<decltype(l), TypeList<C, int, int>>(), "");

    static_assert(!IsCallableWith<decltype(l), TypeList<int, int>>(), "");
    static_assert(!IsCallableWith<decltype(l), TypeList<int, int, int, int>>(), "");

    auto gl1 = [](auto a, auto b, auto c) { return a * b + c; };

    static_assert(IsCallableWith<decltype(gl1), TypeList<int, int, int>>(), "");
    static_assert(IsCallableWith<decltype(gl1), TypeList<B, int, int>>(), "");

    // SFINAE succeeds.
    // But this results in a compile error because A object can't be multiplied by an int value.
    //static_assert(!IsCallableWith<decltype(gl1), TypeList<A, int, int>>(), "");

    // Same reason here.
    // error: invalid operands to binary expression ('(anonymous namespace)::C' and 'int')
    //static_assert(!IsCallableWith<decltype(gl1), TypeList<C, int, int>>(), "");

    // Variadic Generic Lambda Expression with C++17 fold expression
    auto gl2 = [](auto... xs) { return (xs + ...); };

    static_assert(IsCallableWith<decltype(gl2), TypeList<int, int, int>>(), "");
    static_assert(IsCallableWith<decltype(gl2), TypeList<B, int, int>>(), "");

    // Same reason here.
    // THINK: Is there a way to make it safely fail without compile errors?
    //static_assert(!IsCallableWith<decltype(gl2), TypeList<A, int, int>>(), "");
    //static_assert(!IsCallableWith<decltype(gl2), TypeList<C, int, int>>(), "");
}

TEST_CASE("IsCallableWith for an object which is not DefaultConstructable", "[FunctionUtility]")
{
    // NOTE: D is not DefaultConstructable.
    static_assert(IsCallableWith<decltype(f), TypeList<D, int, int>>(), "");
}

