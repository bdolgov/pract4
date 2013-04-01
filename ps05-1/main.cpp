#include <iostream>
using namespace std;

class A
{
    private:
        int x;
    public:
        A(): x()
        {
            cin >> x;
            if (!cin.good()) throw 0;
        }
        ~A()
        {
            cout << x << endl;
        }
};

void f()
{
    A a;
    f();
}

int main()
{
    try
    {
        f();
    }
    catch(...)
    {
    }
    return 0;
}
