#include <vector>
#include <algorithm>
#include <stdexcept>
#include <numeric>

template<class T>
class HexTopology
{
    private:
        int row_count, col_count;
        bool coord_incorrect(const std::pair<int,int>& p) const
        {
            return p.first < 0 || p.second < 0 || p.first >= row_count || p.second >= col_count;
        }
    public:
        HexTopology(const T &m):
            HexTopology(m.get_rows(), m.get_cols())
        {
        }
        HexTopology(int row_count_, int col_count_):
            row_count(row_count_), col_count(col_count_)
        {
        }
        typedef std::vector<std::pair<int,int> > List;
        List operator() (int row, int col) const
        {
            static int dy[6] = { -1, 0, +1, +1, 0, -1 };
            static int dx[2][6] = { { 0, -1, 0, +1, +1, +1 }, { -1, -1, -1, 0, +1, 0 } };
            if (coord_incorrect(std::make_pair(row, col))) throw std::range_error("range error");

            List ret =
            std::inner_product(dx[col], dx[col] + sizeof(dx[col]), dy, List(),
                [](List v, const std::pair<int,int>& p) { v.push_back(p); return v; },
                [](int a, int b) { return std::make_pair(a, b); });
            
            ret.erase(std::remove_if(ret.begin(), ret.end(),
                [this](const std::pair<int,int>& p) { return this->coord_incorrect(p); }),
                ret.end());

            std::sort(ret.begin(), ret.end());
            return ret;
        }
};
