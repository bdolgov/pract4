template<class T>
class HasX
{
    private:
		struct A { int X; };
		template<class U> struct B : U, A {};
		template<class U, U u> struct C {};

        struct char2 { char x[2]; };
        template<class U> static char test(...) { }
        template<class U> static char2 test(C<int A::*, &U::X>*) {  }
    public:
        enum { value = sizeof(test<B<T> >(0)) == sizeof(char) };
};
