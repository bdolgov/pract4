#include <tuple>
#include <iostream>
namespace Game
{
    template<class T>
    class Coord
    {
        private:
            std::tuple<T, T> c;
        public:
            Coord(): c() {}
            Coord(const T& _row, const T& _col): c(std::make_tuple(_row, _col)) {}
            bool operator<(const Coord& other) const { return c < other.c; }
            bool operator<=(const Coord& other) const { return c <= other.c; }
            bool operator>(const Coord& other) const { return c > other.c; }
            bool operator>=(const Coord& other) const { return c >= other.c; }
            bool operator==(const Coord& other) const { return c == other.c; }
            bool operator!=(const Coord& other) const { return c != other.c; }
            T get_row() const { return std::get<0>(c); }
            T get_col() const { return std::get<1>(c); }
            typedef T value_type;
    };

    template<class T>
    std::ostream& operator<<(std::ostream& stream, const Coord<T>& coord)
    {
        stream << "(" << coord.get_row() << "," << coord.get_col() << ")";
        return stream;
    }

    typedef Coord<int> IntCoord;
};

using namespace std;
