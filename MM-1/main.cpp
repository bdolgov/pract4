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
        void iteration(std::istream& in, std::ostream& out, std::ostream& err);
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

void MasterMind::iteration(std::istream& in, std::ostream& out, std::ostream& err)
{
    numbers suggestion;
    int w = 0, b = 0;
start:
    if (!in.good()) throw std::runtime_error("Input cannot be read");
    err << "> ";
    std::copy_n(std::istream_iterator<int>(in), positions, std::inserter(suggestion, suggestion.begin()));
    if (!correct(suggestion))
    {
        err << "Wrong input, please, try again" << std::endl;
        goto start;
    }
    for (int i = 0; i < positions; ++i)
    {
        b += suggestion[i] == answer[i];
        w += std::find(answer.begin(), answer.end(), suggestion[i]) != answer.end();
    }
    out << b << " " << w << std::endl;
    if (b == positions) finished = true;
}


int main(int ac, char** av)
{
    MasterMind game(4, 6);
    while (game.running())
    {
        game.iteration(std::cin, std::cout, std::cerr);
    }
}
