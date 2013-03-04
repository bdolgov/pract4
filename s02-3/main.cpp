#include <string>

class StringData
{
    private:
        int refs;
        bool broken;
    public:
        StringData(const std::string& _str);
        std::string str;
        StringData* ref();
        StringData* detach();
        void deref();
        void setBroken(bool _broken);
};

StringData::StringData(const std::string& _str): refs(1), broken(false), str(_str)
{
}

StringData* StringData::ref()
{
    ++refs;
    return this;
}

StringData* StringData::detach()
{
    if (refs == 1 || broken) return this;
    deref();
    return new StringData(this->str);
}

void StringData::deref()
{
    if (!--refs)
    {
        delete this;
    }
}

void StringData::setBroken(bool _broken)
{
    broken = _broken;
}

class String
{
    private:
        StringData* data;

    public:
        String(const char* str = "");
        String(const String& str);
        String& operator=(const String& str);
        char& operator[](int idx);
        char operator[](int idx) const;
        String& operator+=(const char* what);
        ~String();
        void swap(String& other);
        operator std::string() const;
};

String::operator std::string() const
{
    return data->str;
}

String::String(const char* str): data()
{
    data = new StringData(str);
}

String::String(const String& str): data()
{
    data = str.data->ref();
}

String& String::operator=(const String& str)
{
    String tmp(str);
    std::swap(tmp.data, data);
    return *this;
}

String& String::operator+=(const char* what)
{
    data = data->detach();
    data->str += what;
    return *this;
}

char& String::operator[](int idx)
{
    data = data->detach();
    data->setBroken(true);
    return data->str[idx];
}

char String::operator[](int idx) const
{
    return data->str[idx];
}

String::~String()
{
    data->deref();
}
