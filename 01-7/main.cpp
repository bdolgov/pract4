#include <string>

class Exp
{
    private:
        mutable int value;
        mutable bool cached;
        std::string exp;
    public:
        Exp(const std::string &_exp);
        int calc() const;
};

Exp::Exp(const std::string& _exp): value(0), cached(false), exp(_exp)
{
}

int Exp::calc() const
{
    if (cached) return value;
    cached = 1;
    int n = 0;
    int sgn = 1;
    for (std::string::const_iterator i = exp.begin(); i != exp.end(); ++i)
    {
        if (*i == '-' || *i == '+')
        {
            value += n * sgn;
            sgn = *i == '-' ? -1 : 1;
            n = 0;
        }
        else
        {
            n = n * 10 + (*i - '0');
        }
    }
    value += n * sgn;
    return value;
}
