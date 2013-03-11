#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>

class MasterMind
{
    private:
        typedef std::vector<int> numbers;
        int positions, colors;
        numbers answer;
        bool finished;
        bool correct(const numbers& suggestion);
    public:
        MasterMind(int _positions, int _colors);
        bool running() const;
        bool iteration(const std::vector<int>& suggestion, std::ostream& out, std::ostream& err);
};

MasterMind::MasterMind(int _positions, int _colors): positions(_positions), colors(_colors), finished(false)
{
    std::generate_n(std::inserter(answer, answer.begin()), positions, [_colors]() { return rand() % _colors; });
}

bool MasterMind::running() const
{
    return !finished;
}

bool MasterMind::correct(const MasterMind::numbers& suggestion)
{
    return suggestion.size() == positions && std::find_if(suggestion.begin(), suggestion.end(), [this](int val) { return !(1 <= val && val <= colors); }) == suggestion.end();
}

bool MasterMind::iteration(const std::vector<int>& suggestion, std::ostream& out, std::ostream& err)
{
    int w = 0, b = 0;
    if (!correct(suggestion))
    {
        err << "Wrong input, please, try again" << std::endl;
		return false;
    }
	std::inner_product(suggestion.begin(), suggestion.end(), answer.begin(), 0, 
			[](int, int) { return 0; },
			[&](int sug, int ans) { b += sug == ans; w += std::find(answer.begin(), answer.end(), sug) != answer.end(); return 0;} );
    out << b << " " << w << std::endl;
    if (b == positions) finished = true;
	return finished;
}

template<class T, int n>
class VectorReader
{
	public:
		std::vector<T> result;
};

template<class T, int n>
std::istream& operator>>(std::istream& stream, VectorReader<T, n>& vr)
{
	vr.result.clear();
	std::copy_n(std::istream_iterator<T>(stream), n, std::inserter(vr.result, vr.result.begin()));
}

enum { N = 4, M = 6 };

int main(int ac, char** av)
{
    MasterMind game(N, M);
	std::find_if(std::istream_iterator<VectorReader<int, N>>(std::cin),
	    std::istream_iterator<VectorReader<int, N>>(),
		[&](const VectorReader<int, N>& sug) { return game.iteration(sug.result, std::cout, std::cerr); });
}
