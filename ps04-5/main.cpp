#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
    std::vector<double> x;
    std::copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), std::back_inserter(x));
    int size = x.size();
    x.erase(x.begin(), x.begin() + size / 10);
    x.erase(x.end() - size / 10, x.end());
    std::sort(x.begin(), x.end());
    size = x.size();
    x.erase(x.begin(), x.begin() + size / 10);
    x.erase(x.end() - size / 10, x.end());
    class Summer
    {
        public:
            double sum;
            Summer(): sum(0) {}
            void operator()(double x) { sum += x; }
    } s;
    s = std::for_each(x.begin(), x.end(), s);
    std::cout.precision(10);
    std::cout << s.sum / x.size() << std::endl;
}
