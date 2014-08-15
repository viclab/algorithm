//实现C++中string类
//Tue Aug 12 23:04:12 PDT 2014
#include <iostream>
#include <cstring>
using namespace std;

class String
{
    public:
        String(const char* str = NULL);             //通用构造函数
        String(const String& rhs);                  //拷贝构造函数
        ~String();                                  //析构函数

        String operator+(const String &rhs) const;  //重载+
        String& operator=(const String &rhs);       //重载=
        String& operator+=(const String &rhs);      //重载+=
        bool operator==(const String &rhs) const;   //重载==
        char& operator[](int n);                    //重载[]
        
        size_t size() const;                        //获取长度
        const char* c_str() const;                  //获取c字符串
        
        friend istream& operator>>(istream &is, String &rhs);   //输入
        friend ostream& operator<<(ostream &os, String &rhs);   //输出

    private:
        char *m_data;
        size_t len;
};

String::String(const char* str)
{
    if (!str)
    {
        m_data = new char[1];
        *m_data = '\0';
    }
    else
    {
        len = strlen(str);
        m_data = new char[len + 1];
        strcpy(m_data, str);
    }
}

String::String(const String &rhs)
{
    len = rhs.size();
    m_data = new char[len + 1];
    strcpy(m_data, rhs.c_str());
}

String::~String()
{
    delete[] m_data;
    len = 0;
}

String String::operator+(const String &rhs) const
{
    String newStr;
    newStr.len = len + rhs.size();
    newStr.m_data = new char[len + 1];
    strcpy(newStr.m_data, m_data);
    strcat(newStr.m_data, rhs.m_data);
    return newStr;
}

String& String::operator=(const String &rhs)
{
    if (this == &rhs)
        return *this;
    delete[] m_data;
    len = rhs.len;
    m_data = new char[len + 1];
    strcpy(m_data, rhs.c_str());
    return *this;
}

String& String::operator+=(const String &rhs)
{
    len += rhs.size();
    char * newData = new char[len + 1];
    strcpy(newData, m_data);
    strcat(newData, rhs.c_str());
    delete[] m_data;
    m_data = newData;
    return *this;
}

inline bool String::operator==(const String &rhs) const
{
    if (len != rhs.size())
        return false;
    return strcmp(m_data, rhs.c_str())? false : true;
}

inline char& String::operator[](int n)
{
    if (n >= len)
        return m_data[len - 1];
    else
        return m_data[n];
}

inline size_t String::size() const
{
    return len;
}

inline const char* String::c_str() const
{
    return m_data;
}

istream& operator>>(istream &is, String &rhs)
{
    char tem[1000];
    is >> tem;
    rhs.len = strlen(tem);
    rhs.m_data = new char[rhs.len + 1];
    strcpy(rhs.m_data, tem);
    return is;
}

ostream& operator<<(ostream &os, String &rhs)
{
    os << rhs.c_str();
    return os;
}

int main()
{
    String a;
    String b("hello");
    String c(b);
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;

    c = b + "world";
    c += ",VIC";
    c[0] = 'H';

    cout << "c=" << c << endl;
    
    return 0;
}


