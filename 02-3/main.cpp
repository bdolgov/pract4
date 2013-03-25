#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

void process(vector<int>& v1, const vector<int>& v2, int k)
{
    for (auto i : v2)
    {
        auto j = v1.begin() + (i - 1);
        if (j >= v1.end() || j < v1.begin()) continue;
        *j *= k;
    }
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\n"));
}
