class C
{
    public:
        C operator+(const C&) const { return C(); }
        C operator~() const { return C(); }
        operator int() const { return 0; }
        C& operator++() { return *this; }
        C operator*(const C&) { return C(); }
        C(const C&, const C&) { }
        C() { }
        C(int) {}
        C(const C*) {}
};
/*
C func1(const C &v1, int v2)
{
        return C(v2 + v1, ~v1);
}

void func2(const C *p1, double p2)
{
        C v1 = p2;
            C v2[2][2];
                C v3 = func1(func1(func1(&p1[3], p2), ~p1[2]), ++v1 * v2[1]);
}
*/
