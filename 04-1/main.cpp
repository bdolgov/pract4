#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>

template<typename T>
class smart_pointer
{
    std::unique_ptr<T> pointer;
public:
    smart_pointer(T*);
    smart_pointer& operator=(T*);
    operator T*();
};

template<typename T>
smart_pointer<T>::smart_pointer(T* from)
    : pointer(from)
{}

template<typename T>
smart_pointer<T>& smart_pointer<T>::operator=(T* target)
{
    pointer.reset(target);
    return *this;
}

template<typename T>
smart_pointer<T>::operator T*()
{
    return pointer.get();
}

template<typename T>
class PointerMatrix final
{

    int rows, cols;
    std::vector<std::vector<smart_pointer<T>>> m;
public:
    static const int ROWS_MAX = 16384;
    static const int COLS_MAX = 16384;

    PointerMatrix(int, int, T*);

    PointerMatrix(const PointerMatrix&) = delete;
    PointerMatrix& operator=(const PointerMatrix&) = delete;

    int get_rows() const {return rows;}
    int get_cols() const {return cols;}

    T* at(int, int) const;
    smart_pointer<T>& at(int, int);
};

template<typename T>
PointerMatrix<T>::PointerMatrix(int _rows, int _cols, T* t)
    : rows(_rows), cols(_cols), m()
{
    if (_rows <= 0 or _cols <= 0 or _rows > ROWS_MAX
        or _cols > COLS_MAX or t == nullptr) {
        throw std::invalid_argument("Hello, sweetie!");
    }
    for (auto i = 0; i < _cols; ++i) {
        m.emplace_back(std::vector<smart_pointer<T>>());
        for (auto j = 0; j < _rows; ++j) {
            m[i].emplace_back(smart_pointer<T>(t->clone() ));
        }
    }
}

template<typename T>
smart_pointer<T>& PointerMatrix<T>::at(int row, int col)
{
    if (row < 0 or col < 0 or row >= rows or col >= cols) {
        throw std::range_error("Allons-y, Alonso!");
    }
    return m[row][col];
}

template<typename T>
T* PointerMatrix<T>::at(int row, int col) const
{
    if (row < 0 or col < 0 or row >= rows or col >= cols) {
        throw std::range_error("Fantastic!");
    }
    return m[row][col].get();
}

class Digit final
{
public:
    int x;
    Digit(int y) : x(y) {}
    virtual ~Digit() {}
    virtual Digit* clone() {
        return new Digit(this->x);
    }
};

// #include <iostream>

// int main()
// {
//     PointerMatrix<Digit> matrix(100, 100, &mydigit);
//     matrix.at(0, 0) = &my_other_digit;
//     // Digit* ppointer = matrix.at(0, 0);
//     // std::cout << ppointer->x << std::endl;
//     // matrix.at(0, 0) = &my_other_digit;
//     return 0;
// }
