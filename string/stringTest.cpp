//C++中string类方法使用测试
//Fri Aug 15 00:01:59 PDT 2014
#include <iostream>
#include <string>
//#include <assert.h>
using namespace std;

int main()
{
    //string的7种构造方法
    string one("hello ");               //（一）#1为C风格字符串
    cout << one << endl;
    string two(20, '$');                //（二）#1为个数，#2为重复的字符
    cout << two << endl;
    string three(one);                  //（三）#1为string对象
    cout << three << endl;
    three[0] = 'H';
    two = "Vic!";
    string four;                        //（四）空对象
    four = one + two;
    cout << four << endl;;
    char alls[] = "This is a string class test";
    string five(alls, 15);              //（五）#1为C风格字符串，#2为拷贝字符个数
    cout << five << endl;
    string six(alls+7, alls+15);        //（六）#1为起始迭代器，#2为结束迭代器
    cout << six << endl; 
    string seven(five, 2, 10);          //（七）#1为string对象，#2为起始位置，#3为拷贝字符个数
    cout << seven << endl;

    //c_str方法
    cout << one.c_str() << endl;
    //one.c_str()[0] = 'V';             //非法，因为string类的c_str()函数返回的是一个const指针
    //cout << one.c_str() << endl;

    cout << one.size() << "|" << one.length() << endl;
    cout << "string::npos=" << string::npos << endl;    //string::npos表示string对象的最大允许长度，通常是unsigned int值
    
    //find方法
    //原型有:   1. size_t find(const string &str, size_t pos = 0) const;
    //          2. size_t find(const char* s, size_t pos = 0) const;
    //          3. size_t find(const char* s, size_t pos = 0, size_t n);
    //          4. size_t find(char ch, size_t pos = 0) const;
    //此外，string库还提供其他相关方法，其重载特征标与find相同,有：
    //      rfind           //查找模式串最后一次出现的位置
    //      find_first_of   //查找模式串中任何一个字符第一次出现的位置.
    //      find_first_of   //查找模式串中任何一个字符最后一次出现的位置.
    //      find_first_not_of   //查找模式串中第一个不包含的字符.
    //      find_last_not_of   //查找模式串中最后一个不包含的字符.

    string str = "hello every one, hello my name is vic, i like hello every one, what is hello your name?";
    string::size_type where = str.find("hello");      //这里必须要设置为string::size_type,否则容量不足以存在string::npos
    cout << str.size() << endl;
    cout << str.capacity() << endl;
    //cout << "where=" << where << endl;
    //cout << str.find("hello") << endl;
    //if (where == string::npos)
    //    cout << "where == string:npos)";
    
    while (where != string::npos)
    {
        cout << str << "出现的位置为：" << where << endl;
        where = str.find("hello", where + 1);
    }
    cout << "where|npos:" << where << " | " << string::npos << endl;

    //rfind
    where = str.rfind("hello");
    cout << "where=" << where << endl;

    str = "abcdef";
    where = str.find_first_of("chmnaxycdz");
    while (where != string::npos)
    {
        cout << str << "出现的字符位置为：" << where << endl;
        where = str.find_first_of("chmnaxycdz", where + 1);
    }

    //---------------------------------------------------------
    //字符串操作函数：
    //  1. compare
    //  2. append
    //  3. insert
    //  4. erase()
    //  5. replace()
    //  6. copy()
    //  7. swap()

    //每一个运算法都被重载，使之将string与string，string与C风格字符串进行比较，当然其他操作也都类似
    string s1("bellflower");
    string s2("bell");
    string s3("cat");
    string s4("isflowinto");
    int a13 = s1.compare(s3);       //-1                //#1为要比较的string对象
    int a12 = s1.compare("bell");       //6             //#1为要比较的C风格字符串
    int a2 = s1.compare(0, 4, s2);  //0                 //#1为this对象起始位置，#2为this待比较字符个数
    int a14 = s1.compare(4, 4, s4, 2, 4); //0           //#1为this对象起始位置，#2为this待比较字符个数
                                                        //#3为待比较string对象，#4为该对象起始位置，#5为该对象待比较字符个数

    cout << "a13,a12:" << a13 << "," << a12 << endl;
    cout << "a2,a14:" << a2 << "," << a14 << endl;

    //append
    s2.append(s1);
    cout << s2 << endl;
    s2.append(3, '!');                              //#1为个数，#2为待添加字符
    s2.append("vic");
    cout << s2 << endl;

    //insert
    string st3("The banker.");
    st3.insert(4, "former ");                       //#1为起始索引号，#2为待插字符串
    st3.insert(st3.size() - 1, " waltzed!", 8);     //#1为起始索引号，#2为待插字符串，#3为待插字符个数
    cout << st3 << endl;
    
    //erase
    st3.erase(st3.size() - 1);
    st3.erase(4, 7);                        //#1为起始索引号，#2为个数
    st3.erase(++st3.begin(), st3.end());    //#1为迭代器起始值，#2为迭代器结束值
    cout << st3 << endl;

    //replace
    string test("Take a right turn at Main Street.");
    test.replace(7, 5, "left");         //#1为起始位置，#2为个数
    cout << test << endl;

    //substr
    string test2 = test.substr(7, 5);                  //#1为起始位置，#2为个数
    string test3 = test.substr(7);                    //#1为起始位置，默认到string对象末尾
    cout << test2 << endl;
    cout << test3 << endl;

    //结合find来找出要replace的位置
    string s11 = "old";
    string s22 = "mature";
    string s33 = "The old man and the sea";
    string::size_type pos = s33.find(s11);          //貌似size_t类型也可以,ubuntu测试
    //size_t pos = s33.find(s11);
    if (pos != string::npos)
        s33.replace(pos, s11.size(), s22);
    cout << s33 << endl;

    //总结：string或STL中表示范围通常有两种方式：
    //          1. 使用整形索引号(size_t pos)和个数(size_t n)
    //          2. 使用两个迭代器，一个表示起始位置，一个标示结束位置,通常是[begin,end)

    //copy
    char abc[10 + 1];
    s33.copy(abc, 10, 4);
    abc[10] = '\0';
    cout << abc << endl;
}
    

