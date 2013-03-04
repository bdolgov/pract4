#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using std::cin; using std::cout; using std::vector;
using std::sort;
struct Function
{
    typedef double (*fn_t)(double);
    fn_t f;
    int n;
    Function(fn_t _f, int _n): f(_f), n(_n) {}
};

double f3(double x) { return x * x; }
double f6(double x) { return sqrt(42 + x * x); }
double f7(double x) { return x * x * x; }
double f8(double x) { return cos(x + M_PI / 3); }
double f9(double x) { return sin(x - M_PI / 42); }
double f10(double x) { return log(2 + x * x); }

class Compar1
{
    public:
        Compar1(double _x, double _eps = 1e-6): x(_x), eps(_eps) {}
        bool operator()(const Function& f1, const Function& f2)
        {
            double val1 = f1.f(x), val2 = f2.f(x);
            if (fabs(val1 - val2) < eps) return f1.n < f2.n;
            return val1 < val2;
        }

    private:
        double x;
        double eps;
};

class Compar2
{
    public:
        Compar2(double _x, double _eps = 1e-6): x(_x), eps(_eps) {}
        bool operator()(const Function& f1, const Function& f2)
        {
            double val1 = fabs(f1.f(x)), val2 = fabs(f2.f(x));
            if (fabs(val1 - val2) < eps) return f1.n > f2.n;
            return val1 < val2;
        }

    private:
        double x;
        double eps;
};


int main()
{
    Function::fn_t fns0[] = { sin, cos, f3, fabs, exp, f6, f7, f8, f9, f10 };
    vector<Function> fns;
    int n;
    double y, z; 
    std::cin >> n >> y >> z;
    for (unsigned i = 0; i < sizeof(fns0) / sizeof(fns0[0]); ++i)
    {
        fns.emplace_back(fns0[i], i);
    }

    if (n == 1)
        sort(fns.begin(), fns.end(), Compar1(y));
    else
        sort(fns.begin(), fns.end(), Compar2(y));
    
    double val = z;
    std::reverse(fns.begin(), fns.end());
    for (const auto &i : fns)
    {
        val = i.f(val);
    }
    cout.precision(20);
    cout << val << std::endl;
}
