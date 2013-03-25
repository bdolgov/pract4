#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void process(vector<int> v, list<int>& lst)
{
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    auto i = v.begin();
    auto j = lst.begin();
    int ji = 1;
    int size = lst.size();
    while (i != v.end() && *i <= size)
    {
        if (*i < ji)
        {
            ++i;
        }
        else if (*i == ji)
        {
            lst.erase(j++);
            ++ji;
        }
        else
        {
            ++j;
            ++ji;
        }
    }
}
