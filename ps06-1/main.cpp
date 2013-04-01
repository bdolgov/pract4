template<class T>
typename T::value_type process(const T& x)
{
    int n = 0;
    typename T::value_type ret = typename T::value_type();
    for (auto i = x.rbegin(); i != x.rend() && n != 3; ++i, ++n)
    {
        ret += *i;
    }
    return ret;
}
