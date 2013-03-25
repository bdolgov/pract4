#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
    std::for_each(std::istream_iterator<std::string>(std::cin),
        std::istream_iterator<std::string>(),
        [](std::string s)
        {
            for (std::string::iterator i = s.end(); i != s.begin(); --i)
            {
                if (std::equal(s.begin(), i, s.rbegin() + (s.end() - i)))
                {
                    s.erase(i, s.end());
                    std::cout << s << std::endl;
                    break;
                }
            }
        });
}
