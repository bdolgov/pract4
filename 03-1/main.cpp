#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct User
{
	string name, file;
	double mark;
	static bool read(User& u);
};

bool User::read(ostream& in, User& u)
{

}

int main(int ac, char** av)
{

}
