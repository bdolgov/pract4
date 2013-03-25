#include <set>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a;
    std::multiset<int> s;
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(a));
    std::copy_n(a.begin(), k, std::inserter(s, s.begin()));
    std::inner_product(a.begin(), a.end() - k, a.begin() + k, 0, [](int A, int b) { return 0; },
        [&s](int A, int b) {
        std::cout << *s.begin() << std::endl;
        s.erase(s.find(A));
        s.insert(b);
        return 0;
    });
    std::cout << *s.begin() << std::endl;
    return 0;
}
