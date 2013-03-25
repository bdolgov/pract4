#include <vector>
#include <iostream>

void process(std::vector<int>& x)
{
    int n = 0;
    for (auto i = x.begin(); i != x.end();)
    {
        if ((n = ~n))
        {
            i = x.erase(i);
        }
        else
        {
            ++i;
        }
    }
    for (auto i = x.rbegin(); i != x.rend(); ++i)
    {
        std::cout << *i << std::endl;
    }
}
/*
int main()
{
    std::vector<int> a{1,2,3,4,5,6,7,8,9,10};
    std::vector<int> b(1, 1);
    process(a);
}*/
