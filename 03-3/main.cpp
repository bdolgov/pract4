#include <iostream>
#include <iomanip>
#include <utility>
#include <fstream>
#include <string>
#include <map>
#include <set>

class Date final
{
    unsigned int day;
    unsigned int year;
    unsigned int month;
public:
    Date() : day(0), year(0), month(0) {}
    Date(unsigned int, unsigned int, unsigned int);
    
    friend bool operator<(const Date&, const Date&);
    friend bool operator==(const Date&, const Date&);
    friend std::ostream& operator<<(std::ostream&, const Date&);
};

Date::Date(unsigned int _day, unsigned int _year, unsigned int _month)
    : day(_day), year(_year), month(_month)
{}

bool operator<(const Date& date1, const Date& date2)
{
    if (date1.year < date2.year) {
        return true;
    } else if (date1.year > date2.year) {
        return false;
    } else if (date1.month < date2.month) {
        return true;
    } else if (date1.month > date2.month) {
        return false;
    } else if (date1.day < date2.day) {
        return true;
    } else if (date1.day > date2.day) {
        return false;
    } else {
        return false;
    }
}

bool operator==(const Date& date1, const Date& date2)
{
    if (date1.year == date2.year and date1.month == date2.month
        and date1.day == date2.day) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& target, const Date& date)
{
    using std::setfill;
    using std::setw;
    target << setfill('0');
    target << setw(4) << date.year << '/';
    target << setw(2) << date.month  << '/';
    target << setw(2) << date.day << " ";
    return target;
}

int main()
{
    using std::string;
    using std::map;
    using std::set;

    using std::make_pair;
    using std::pair;

    map<pair<string, Date>, int> students;
    set<Date> dates;

    std::ifstream source;
    source.open("02-3.in");

    Date date;
    int grade;
    string name;
    char delimiter;
    unsigned int year, month, day;
    while (source >> name >> year >> delimiter >> month >> delimiter >>
            day >> grade) {
        date = Date(day, year, month);
        dates.insert(date);
        auto result = students.insert(make_pair(make_pair(name, date), grade));
        if (not result.second) {
            result.first->second = grade;
        }
    }
    
    std::ofstream target;
    target.open("02-3.out");
    target << ". ";
    for (auto i : dates) {
        target << i;
    }
    target << std::endl;

    auto iStudent = students.begin();
    auto iDate = dates.begin();
    if (iStudent != students.end()) {
        name = iStudent->first.first;
        target << name << " ";
    }
    for (; iStudent != students.end(); ++iStudent) {
        if (name != iStudent->first.first) {
            name = iStudent->first.first;
            for (; iDate != dates.end(); ++iDate) {
                target << ". ";
            }
            iDate = dates.begin();
            target << std::endl << name << " ";
        }
        for (; iDate != dates.end(); ++iDate) {
            if (*iDate == iStudent->first.second) {
                target << iStudent->second << " ";
                ++iDate;
                break;
            } else {
                target << ". ";
            }
        }
    }
    for (; iDate != dates.end(); ++iDate) {
        target << ". ";
    }
    return 0;
}
