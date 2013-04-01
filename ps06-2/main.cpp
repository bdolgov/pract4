#include <algorithm>

template<class Iter>
void myreverse(Iter begin, Iter end)
{
    while (begin != end && begin != --end)
    {
        std::swap(*begin, *end);
        ++begin;
    }
}
