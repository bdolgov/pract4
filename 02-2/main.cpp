#include <vector>
#include <iostream>

using namespace std;

void process(const vector<int>& v1, vector<int>& v2)
{
    vector<int> add;
    for (auto i = v1.begin(), j = const_cast<const vector<int>&>(v2).begin(); i != v1.end() && j != v2.end(); ++i, ++j)
    {
        if (*i > *j) add.push_back(*i);
    }
    v2.insert(v2.end(), add.begin(), add.end());
    for (auto i : v2) cout << i << endl;
}
