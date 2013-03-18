#include <stdexcept>
#include <vector>
#include <memory>
#include <algorithm>

template<class T>
class PointerMatrix
{
    private:
        int rows;
        int cols;
        std::vector<std::vector<std::unique_ptr<T> > > m;
        class Ref
        {
            private:
                std::unique_ptr<T>& x;
            public:
                Ref(std::unique_ptr<T>& _x): x(_x) {}
                Ref& operator=(T* y) { x.reset(y); return *this;}
                operator T*() { return x.get(); }
        };
    public:
        static const int ROWS_MAX = 16384, COLS_MAX = 16384;
        int get_rows() const { return rows; }
        int get_cols() const { return cols; }
        PointerMatrix(const PointerMatrix&) = delete;
        PointerMatrix& operator=(const PointerMatrix&) = delete;
        Ref at(int row, int col)
        {
            if (row >= rows || col >= cols) throw std::range_error("Range error");
            return Ref(m[row][col]);
        }
        T* at(int row, int col) const 
        {
            if (row >= rows || col >= cols) throw std::range_error("Range error");
            return m[row][col].get();
        }
        PointerMatrix(int _rows, int _cols, T* obj): rows(_rows), cols(_cols), m()
        {
            if (rows <= 0 || cols <= 0 || rows > ROWS_MAX || cols > COLS_MAX || !obj)
                throw std::invalid_argument("Invalid argument");
            std::generate_n(std::back_inserter(m), rows, [obj, _cols]() {
                    std::vector<std::unique_ptr<T> > tmp;
                    std::generate_n(std::back_inserter(tmp), _cols, [obj]() {
                        return std::unique_ptr<T>(obj->clone()); });
                    return tmp;
            });
        }
};
