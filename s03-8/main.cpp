#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>

template<class T>
class Ptr
{
    private:
        T* ptr;
    public:
        T* operator*() const { return ptr; }
        T* operator->() const { return ptr; }
        ~Ptr() { if (ptr) delete ptr; }
        explicit Ptr(T* _ptr): ptr(_ptr) {}
        Ptr(Ptr&& other): ptr(other.ptr)
        {
            other.ptr = NULL;
        }
        Ptr(const Ptr&) = delete;
        Ptr& operator=(const Ptr&) = delete;
        Ptr() = delete;
};

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

Ptr<DateFormatter> createDateFormatter(int formatterNum)
{
    return Ptr<DateFormatter>(DateFormatter::create(formatterNum));
}

Ptr<TimeFormatter> createTimeFormatter(int formatterNum)
{
    return Ptr<TimeFormatter>(TimeFormatter::create(formatterNum));
}
