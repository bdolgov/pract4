#include <algorithm>
#include <iostream>
#include <vector>

bool isCorrect(const std::vector<int>& word)
{
    auto i = word.cbegin();
    for (; i != word.cend(); ++i) {
        if (*i != 3 and *i != 4) {
            break;
        }
    }
    for (; i != word.cend(); ++i) {
        if (*i != 1 and *i != 2) {
            break;
        }
    }
    if (i == word.cend()) {
        return true;
    }
    return false;
}

bool addOne(std::vector<int>& word)
{
    auto i = word.rbegin();
    for (; i != word.rend(); ++i) {
        *i += 1;
        if (*i > 4) {
            *i = 1;
        } else {
            break;
        }
    }
    if (i == word.rend()) {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, std::vector<int> v)
{
    for (auto i : v) {
        out << i;
    }
    out << std::endl;
    return out;
}

int main()
{
    using std::vector;

    unsigned int K;
    std::cin >> K;
    vector<int> word;
    for (unsigned int i = 0; i < K; ++i) {
        word.push_back(1);
    }

    std::cout << word;
    while (addOne(word)) {
        if (isCorrect(word)) {
            std::cout << word;
        }
    }
    return 0;
}
