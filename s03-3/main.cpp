#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>

class DateFormater
{
    public:
        virtual ~DateFormater() {}
        virtual std::string printDate(const std::tm& tm) const = 0;
    protected:
        static int mday(const std::tm& tm) { return tm.tm_mday; }
        static int mon(const std::tm& tm) { return tm.tm_mon + 1; }
        static int year(const std::tm& tm) { return tm.tm_year + 1900; }
};

class DateFormater1 : public DateFormater
{
    public:
        std::string printDate(const std::tm& tm) const;
};

class DateFormater2 : public DateFormater
{
    public:
        std::string printDate(const std::tm& tm) const;
};

std::string DateFormater1::printDate(const std::tm& tm) const
{
    std::stringstream result;
    result << std::setfill('0') << std::setw(2) << mday(tm) << "."
        << std::setfill('0') << std::setw(2) << mon(tm) << "." << year(tm);
    return result.str();
}

std::string DateFormater2::printDate(const std::tm& tm) const
{
    std::stringstream result;
    result << year(tm) << "-" << std::setfill('0') << std::setw(2) << mon(tm) << "-"
        << std::setfill('0') << std::setw(2) << mday(tm);
    return result.str();
}
void f(DateFormater *df);
void run(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    int mode;
    file >> mode;
    DateFormater *df;
    if (mode == 1)
        df = new DateFormater1;
    else
        df = new DateFormater2;
    f(df);
    delete df;
}
