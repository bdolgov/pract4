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

class TimeFormatter
{
    public:
        virtual ~TimeFormatter() {}
        virtual std::string printTime(const std::tm& tm) const = 0;
        static TimeFormatter* create(int mode);
};

class DateTimeFormatter : public DateFormatter, public TimeFormatter
{
    private:
        DateFormatter *df;
        TimeFormatter *tf;
        DateTimeFormatter(const DateTimeFormatter&);
        DateTimeFormatter& operator=(const DateTimeFormatter&);
    public:
        DateTimeFormatter(DateFormatter *_df, TimeFormatter *_tf): df(_df), tf(_tf) {}
        ~DateTimeFormatter() { delete df; delete tf; }
        static DateTimeFormatter* create(int mode);
        std::string printDate(const std::tm& tm) const { return df->printDate(tm); }
        std::string printTime(const std::tm& tm) const { return tf->printTime(tm); }
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

class TimeFormatter1 : public TimeFormatter
{
    public:
        std::string printTime(const std::tm& tm) const;
        static TimeFormatter* create() { return new TimeFormatter1; }
};

class TimeFormatter2 : public TimeFormatter
{
    public:
        std::string printTime(const std::tm& tm) const;
        static TimeFormatter* create() { return new TimeFormatter2; }
};

DateFormatter* DateFormatter::create(int mode)
{
    typedef DateFormatter* (*ctor_t)();
    static ctor_t DFs[] = { DateFormatter1::create, DateFormatter2::create, DateFormatter3::create };
    return DFs[mode - 1]();
}

TimeFormatter* TimeFormatter::create(int mode)
{
    typedef TimeFormatter* (*ctor_t)();
    static ctor_t DFs[] = { TimeFormatter1::create, TimeFormatter2::create };
    return DFs[mode - 1]();
}

DateTimeFormatter* DateTimeFormatter::create(int mode)
{
    return new DateTimeFormatter(DateFormatter::create(mode), TimeFormatter::create(mode));
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

std::string TimeFormatter1::printTime(const std::tm& tm) const
{
    char buf[256];
    strftime(buf, sizeof(buf), "%H:%M", &tm);
    return buf;
}

std::string TimeFormatter2::printTime(const std::tm& tm) const
{
    char buf[256];
    strftime(buf, sizeof(buf), "%I:%M %p", &tm);
    return buf;
}

void f(DateFormatter *df, TimeFormatter* tf);
void run(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    int mode;
    file >> mode;
    DateTimeFormatter *df = DateTimeFormatter::create(mode);
    f(df, df);
    delete df;
}
