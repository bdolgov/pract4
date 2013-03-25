#include <vector>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

void process(const vector<int>& v, list<int>& l, int k)
{
    auto i = v.begin();
    auto j = l.begin();
    for (; i < v.end() && j != l.end(); i += k, ++j)
    {
        *j = *i;
    }
    copy(l.rbegin(), l.rend(), ostream_iterator<int>(cout, "\n"));
}
