#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class MyCompare
{
public:
    bool operator()(const string &s1, const string &s2)
    {
        if (s1.length() < s2.length()) return true;
        if (s1.length() > s2.length()) return false;
        return s1 < s2;
    }
    static void do_work(vector<string> &vec, vector<string> &vec2);
};

void
MyCompare::do_work(vector<string> &vec, vector<string> &vec2)
{
    sort(vec.begin(), vec.end(), MyCompare());

    vector<string>::const_iterator i1 = vec.begin();
    vector<string>::const_iterator i2 = vec.begin() + 1;
    for (; i1 < vec.end() && i2 < vec.end(); ++i1, ++i2) {
        vec2.push_back(*i1 + " " + *i2);
    }
}

int
main()
{
    string s;
    vector<string> v1, v2;

    while (cin >> s) {
        v1.push_back(s);
    }
    MyCompare::do_work(v1, v2);
    for (vector<string>::const_iterator i = v2.begin(); i != v2.end(); ++i) {
        cout << *i << endl;
    }
    return 0;
}
