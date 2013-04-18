#include <vector>
#include <memory>
#include <utility>

#include <iostream>

template<typename T>
class smart_ptr final
{
    std::unique_ptr<T> p;
public:
    smart_ptr(T*);
    
    smart_ptr<T>& operator=(T*);

    operator T* ();
    operator T* () const;
};

template<typename T>
smart_ptr<T>::smart_ptr(T* t)
    : p(t)
{
    std::cerr << "construted smart pointer" << std::endl;
}

template<typename T>
smart_ptr<T>& smart_ptr<T>::operator=(T* q)
{
    p.reset(q);
    return *this;
}

template<typename T>
smart_ptr<T>::operator T* ()
{
    return p.get();
}

template<typename T>
smart_ptr<T>::operator T* () const
{
    return p.get();
}

template<typename T>
class PointerMatrix final
{
    int rows;
    int cols;
    std::vector<std::vector<smart_ptr<T>>> m;
public:
    PointerMatrix(int, int, T*);

    PointerMatrix(const PointerMatrix&) = delete;
    PointerMatrix& operator=(const PointerMatrix&) = delete;

    int get_rows() const {return rows;}
    int get_cols() const {return cols;}

    T* at(int, int) const;
    smart_ptr<T>& at(int, int);

    static const int ROWS_MAX = 16384;
    static const int COLS_MAX = 16384;
};

template<typename T>
PointerMatrix<T>::PointerMatrix(int inRows, int inCols, T* instance)
    : rows(inRows), cols(inCols), m()
{
    if (rows <= 0 or cols <= 0 or rows > ROWS_MAX or cols > COLS_MAX
        or instance == nullptr) {
            throw std::invalid_argument("Invalid argument");
    }
    for (auto i = 0; i < rows; ++i) {
        m.emplace_back(std::vector<smart_ptr<T>>());
        for (auto j = 0; j < cols; ++j) {
            m[i].emplace_back(smart_ptr<T>(instance->clone()));
        }
    }
}

template<typename T>
T* PointerMatrix<T>::at(int row, int col) const
{
    if (row < 0 or row >= rows or col < 0 or col >= cols) {
        throw std::range_error("Out of range");
    }
    return m[row][col];
}

template<typename T>
smart_ptr<T>& PointerMatrix<T>::at(int row, int col)
{
    if (row < 0 or row >= rows or col < 0 or col >= cols) {
        throw std::range_error("Out of range");
    }
    return m[row][col];
}

// class Digit
// {
//     int x = 42;
// public:
//     Digit(int inX) : x(inX)
//     {std::cerr << "creating another Digit" << std::endl;}
//     ~Digit()
//     {std::cerr << "another one bites the dust" << std::endl;}

//     int getX() const {return x;}

//     Digit* clone();
// };

// Digit* Digit::clone()
// {
//     std::cerr << "cloning" << std::endl;
//     return new Digit(this->x);
// }

// int main()
// {
//     Digit* digit = new Digit(43);
//     Digit* funny = new Digit(1535);
    
//     try {
//         PointerMatrix<Digit> matrix(0, 0, digit);
//     } catch (std::invalid_argument e) {
//         std::cerr << e.what() << std::endl;
//     }

//     PointerMatrix<Digit>* matrix = new PointerMatrix<Digit>(3, 3, digit);
    
//     Digit* test = matrix->at(0, 0);

//     delete matrix;
//     std::cerr << "test " << test->getX() << std::endl; 
    
//     delete funny;
//     delete digit;
//     return 0;
// }
