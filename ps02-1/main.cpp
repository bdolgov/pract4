#include <vector>
#include <iostream>
#include <list>
using namespace std;

int process(vector<int>& a, const list<int>& b, int c)
{
    int ret = 0;
    auto i = a.begin();
    auto j = b.begin();
    for (; i < a.end() && j != b.end(); i += c, ++j)
    {
        if (*j < 0)
        {
            ++ret;
            *i = *j;
        }
    }
    for (auto k : a)
    {
        cout << k << endl;
    }
    return ret;
}
