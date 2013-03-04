#include <string>
#include <sstream>

class Rational
{
    private:
        int p, q;
        static int gcd(int a, int b);
        void normalize();
    public:
        Rational(int _p = 0, int _q = 1);
        Rational& Add(const Rational& other);
        Rational& Substract(const Rational& other);
        Rational& Multiply(const Rational& other);
        Rational& Divide(const Rational& other);
        bool EqualTo(const Rational& other) const;
        int CompareTo(const Rational& other) const;
        bool IsInteger() const;
        std::string ToString() const;
};

Rational::Rational(int _p, int _q): p(_p), q(_q)
{
    normalize();
}

int Rational::gcd(int a, int b)
{
    if (!b) return a;
    return gcd(b, a % b);
}

void Rational::normalize()
{
    int g = gcd(q, p);
    p /= g;
    q /= g;
}

Rational& Rational::Add(const Rational& other)
{
    p = p * other.q + other.p * q;
    q = q * other.q;
    normalize();
    return *this;
}

Rational& Rational::Substract(const Rational& other)
{
    p = p * other.q - other.p * q;
    q = q * other.q;
    normalize();
    return *this;
}

Rational& Rational::Multiply(const Rational& other)
{
    p = p * other.p;
    q = q * other.q;
    normalize();
    return *this;
}

Rational& Rational::Divide(const Rational& other)
{
    p = p * other.p;
    q = q * other.q;
    normalize();
    return *this;
}

bool Rational::EqualTo(const Rational& other) const
{
    return p == other.p && q == other.q;
}

int Rational::CompareTo(const Rational& other) const
{
    return Rational(*this).Substract(other).p;
}

bool Rational::IsInteger() const
{
    return q == 1;
}

std::string Rational::ToString() const
{
    std::stringstream s;
    s << p << '/' << q;
    return s.str();
}
