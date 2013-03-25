#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

int f(int x)
{
    int ret = 0;
    while (x)
    {
        ret += (x & 1);
        x /= 2;
    }
    return ret;
}

bool cmp(int a, int b)
{
    return f(a) < f(b);
}

int main()
{
    vector<int> a;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(a));
    stable_sort(a.begin(), a.end(), cmp);
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, "\n"));
    return 0;
}
