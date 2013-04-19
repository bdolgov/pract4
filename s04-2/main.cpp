template<typename T>
struct HasX
{
    struct Fallback
    {
        int x;
    };
    
    struct Derived: T, Fallback {};
    // if T has x, there will be a name clash

    template<typename C, C>
    class CheckT;
    
    template <typename C>
    static int f(CheckT<int Fallback::*, &C::x>*);
    
    template <typename C>
    static char f(...);

    static const bool value = sizeof(f<Derived>(nullptr)) == 1;
};

// struct test
// {
//     int x;
//     virtual ~test(){};
// };

// struct test2
// {
//     int y;
// };

// #include <string>
// #include <iostream>

// int main()
// {
//     std::cout << HasX<test>::value << std::endl;
//     std::cout << HasX<test2>::value << std::endl;
// }
// http://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class
