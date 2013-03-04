#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

class Permutation
{
    private:
        std::vector<double> a;
    public:
        Permutation(const std::string& s);
        operator std::string() const;
        const Permutation& operator++();
        Permutation operator++(int);
};

Permutation::Permutation(const std::string& s) : a()
{
    std::stringstream stream(s);
    std::copy(std::istream_iterator<double>(stream), std::istream_iterator<double>(), std::inserter(a, a.begin()));
}

Permutation::operator std::string() const
{
    std::stringstream stream;
    std::copy(a.begin(), a.end(), std::ostream_iterator<double>(stream, " "));
    return stream.str();
}

const Permutation& Permutation::operator++()
{
    std::next_permutation(a.begin(), a.end());
    return *this;
}

Permutation Permutation::operator++(int)
{
    Permutation tmp = *this;
    ++(*this);
    return tmp;
}
