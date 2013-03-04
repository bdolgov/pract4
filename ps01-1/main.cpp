#include <ostream>

class Avg
{
    private:
        int n;
        double sum;
        double squares;
    public:
        Avg();
        Avg& operator+=(double x);
    friend std::ostream& operator<<(std::ostream& stream, const Avg& avg);
};

Avg::Avg(): n(0), sum(0), squares(0)
{
}

Avg& Avg::operator+=(double x)
{
    ++n;
    sum += x;
    squares += x * x;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Avg& avg)
{
    double a = avg.sum / avg.n;
    double b = (double(avg.n) / (avg.n - 1)) * (avg.squares / avg.n - (avg.sum / avg.n) * (avg.sum / avg.n));
    stream << a << std::endl << b << std::endl;
    return stream;
}
