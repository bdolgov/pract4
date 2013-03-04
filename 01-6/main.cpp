#include <cstdio>
#include <unistd.h>

class File
{
    private:
        FILE *f;
        File(const File&);
        File& operator=(const File&);
    public:
        enum Mode { READ, WRITE, READWRITE };
        File(const char* filename, Mode mode = READWRITE);
        ~File();
        int read(char* what, int n);
        int write(const char* what, int n);
};

File::File(const char* filename, Mode mode) : f()
{
    const char* fopenMode = NULL;
    if (mode == READWRITE)
    {
        fopenMode = 0 == access(filename, R_OK | W_OK) ? "r+" : "w+";
    }
    else
    {
        fopenMode = mode == READ ? "r" : "w";
    }
    f = fopen(filename, fopenMode);
}

File::~File()
{
    fclose(f);
}

int File::read(char* what, int n)
{
    return fread(what, 1, n, f);
}

int File::write(const char* what, int n)
{
    return fwrite(what, 1, n, f);
}
