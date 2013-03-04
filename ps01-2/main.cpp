#include <string>
#include <vector>
#include <iostream>
#include <iterator>

class StringStack;

class StackInserter
{
    private:
        StringStack& st;
    public:
        StackInserter(StringStack &_s);
        StackInserter& operator,(const std::string& s);
        StackInserter& operator,(const char* s);
};

class StringStack
{
    private:
        std::vector<std::string> a;
    public:
        void push(const std::string& s);
        void clear();
        std::string pop();
        StringStack();
        StringStack(const std::string& str);
        explicit StringStack(const char* str);
        StackInserter operator=(const std::string& str);
        StackInserter operator+=(const std::string& str);
        friend std::ostream& operator<<(std::ostream& i, const StringStack& s);
};

StackInserter::StackInserter(StringStack& _s): st(_s)
{
}

StackInserter& StackInserter::operator,(const std::string& s)
{
    this->st.push(s);
    return *this;
}

StackInserter& StackInserter::operator,(const char* s)
{
    this->st.push(s);
    return *this;
}

void StringStack::push(const std::string& s)
{
    a.push_back(s);
}

void StringStack::clear()
{
    a.clear();
}

std::string StringStack::pop()
{
    std::string x = *a.rbegin();
    a.resize(a.size() - 1);
    return x;
}

StringStack::StringStack(): a()
{
}

StringStack::StringStack(const char* str)
{
    push(str);
}

StringStack::StringStack(const std::string& str)
{
    push(str);
}

StackInserter StringStack::operator=(const std::string& str)
{
    clear();
    push(str);
    return StackInserter(*this);
}

StackInserter StringStack::operator+=(const std::string& str)
{
    push(str);
    return StackInserter(*this);
}

std::ostream& operator<<(std::ostream& i, const StringStack& s)
{
    std::copy(s.a.rbegin(), s.a.rend(), std::ostream_iterator<std::string>(i, "\n"));
    return i;
}

#include <iostream>

int main()
{
	StringStack x, y;
	x, y = "a";
	std::cout << y;
}
