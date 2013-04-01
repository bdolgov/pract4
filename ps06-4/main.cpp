template<int N>
struct Fib
{
    enum { VAL = Fib<N - 1>::VAL + Fib<N - 2>::VAL };
};

template<>
struct Fib<0>
{
    enum { VAL = 0 };
};

template<>
struct Fib<1>
{
    enum { VAL = 1 };
};
