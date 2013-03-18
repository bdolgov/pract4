template<class T>
class IsClass
{
    private:
        struct char2 { char x[2]; };
        template<class U> static char test(void(U::*)()) {}
        template<class U> static char2 test(...) { }
    public:
        enum { value = sizeof(test<T>(nullptr)) == sizeof(char) };
};
