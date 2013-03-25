template<class T>
class HasX
{
    private:
        struct A { int x; };
        template<class U> struct B : U, A {};
        template<int A::* u> struct C {};

        struct char2 { char x[2]; };
        template<class U> static char test(...) { }
        template<class U> static char2 test(C<&U::x>*) {  }
    public:
        enum { value = sizeof(test<B<T> >(0)) == sizeof(char) };
};
