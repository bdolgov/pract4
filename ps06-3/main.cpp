#include <type_traits>

template<class T>
struct Dereference
{
    typedef typename std::remove_reference<decltype(*T())>::type type;
};

template<class Iter, class Pred>
int myfilter(Iter begin, Iter end, Pred pred,
    typename Dereference<Iter>::type init =
    typename Dereference<Iter>::type())
{
    int ret = 0;
    while (begin != end)
    {
        if (pred(*begin))
        {
            *begin = init;
            ++ret;
        }
        ++begin;
    }
    return ret;
}
