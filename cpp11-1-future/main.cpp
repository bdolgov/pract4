#include <future>
#include <thread>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <iterator>
#include <iostream>
#include <iterator>
#include <queue>
#include <algorithm>

using namespace std;

mutex mgr;
condition_variable cond;

queue<unordered_map<string, int>> q;
int n = 0;
int main(int ac, char** av)
{
    n = (ac - 1) * 2 - 1;
    for (int i = 1; i < ac; ++i)
    {
        thread t([av, i]()
        {
            ifstream f(av[i]);
            unordered_map<string, int> ret;
            for_each(istream_iterator<string>(f), istream_iterator<string>(), [&ret](const string &s)
            {
                ret[s]++;
            });
            {
                lock_guard<mutex> g(mgr);
                q.emplace(move(ret));
                --n;
            }
            cond.notify_all();
        });
        t.detach();
    }
    mutex cond0;
    std::unique_lock<std::mutex> lk(cond0);
    while (n)
    {
        cond.wait(lk);
        {
            lock_guard<mutex> g(mgr);
            while (q.size() >= 2)
            {
                unordered_map<string, int> q1(move(q.front()));
                q.pop();
                unordered_map<string, int> q2(move(q.front()));
                q.pop();
                std::thread t([](unordered_map<string, int> a, unordered_map<string, int> b)
                {
                    if (a.size() > b.size()) swap(a, b);
                    for (auto &i : a)
                    {
                        b[i.first] += i.second;
                    }
                    {
                        lock_guard<mutex> grd(mgr);
                        q.emplace(move(b));
                        --n;
                    }
                    cond.notify_all();
                }, move(q1), move(q2));
                t.detach();
            }
        }
    }
    vector<pair<int, string>> x;
    unordered_map<string, int> q1(move(q.front()));
    cout << q1.size() << endl;
    q.pop();
    x.reserve(q1.size());
    for (auto& i : q1)
    {
        x.emplace_back(make_pair(i.second, i.first));
    }
    auto reverse_sorter = [](const pair<int, string>& a, const pair<int, string>& b)
        { return a.first == b.first ? a.second < b.second : a.first > b.first; };
    partial_sort(x.begin(), x.begin() + 20, x.end(), reverse_sorter);
    sort(x.begin(), x.begin() + 20, reverse_sorter);
    for (int i = 0; i < 20; ++i)
    {
        cout << x[i].second << " " << x[i].first << endl;
    }
}
