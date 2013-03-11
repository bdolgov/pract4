#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>

class DateFormatter
{
    public:
        virtual ~DateFormatter() {}
        virtual std::string printDate(const std::tm& tm) const = 0;
        static DateFormatter* create(int mode);
    protected:
        static int mday(const std::tm& tm) { return tm.tm_mday; }
        static int mon(const std::tm& tm) { return tm.tm_mon + 1; }
        static int year(const std::tm& tm) { return tm.tm_year + 1900; }
        static std::string monName(const std::tm& tm)
        {
            char buf[4];
            strftime(buf, sizeof(buf), "%b", &tm);
            return buf;
        }
};

class DateFormatter1 : public DateFormatter
{
    public:
        std::string printDate(const std::tm& tm) const;
        static DateFormatter* create() { return new DateFormatter1; }
};

class DateFormatter2 : public DateFormatter
{
    public:
        std::string printDate(const std::tm& tm) const;
        static DateFormatter* create() { return new DateFormatter2; }
};

class DateFormatter3 : public DateFormatter
{
    public:
        std::string printDate(const std::tm& tm) const;
        static DateFormatter* create() { return new DateFormatter3; }
        
};

DateFormatter* DateFormatter::create(int mode)
{
    typedef DateFormatter* (*ctor_t)();
    static ctor_t DFs[] = { DateFormatter1::create, DateFormatter2::create, DateFormatter3::create };
    return DFs[mode - 1]();
}

std::string DateFormatter1::printDate(const std::tm& tm) const
{
    std::stringstream result;
    result << std::setfill('0') << std::setw(2) << mday(tm) << "."
        << std::setfill('0') << std::setw(2) << mon(tm) << "." << year(tm);
    return result.str();
}

std::string DateFormatter2::printDate(const std::tm& tm) const
{
    std::stringstream result;
    result << year(tm) << "-" << std::setfill('0') << std::setw(2) << mon(tm) << "-"
        << std::setfill('0') << std::setw(2) << mday(tm);
    return result.str();
}

std::string DateFormatter3::printDate(const std::tm& tm) const
{
    std::stringstream result;
    result << mday(tm) << " " << monName(tm) << " " << year(tm);
    return result.str();
}

void f(DateFormatter *df);
void run(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    int mode;
    file >> mode;
    DateFormatter *df = DateFormatter::create(mode);
    f(df);
    delete df;
}
