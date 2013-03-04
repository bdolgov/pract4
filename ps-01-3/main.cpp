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
