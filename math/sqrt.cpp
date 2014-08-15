//实现sqrt：求一个数的平方根
//Wed Aug 13 01:39:54 PDT 2014

#include <iostream>
using namespace std;

//牛顿迭代法实现
double sqrt(int n)
{
    double last = 0;
    double res = 1;
    while(res != last)
    {
        last = res;
        res = (res + n/res)/2;
    }
    
    return res;
}
        
int main()
{
    for (int i = 1; i < 50; ++i)
        cout << i << "的平方根为：" << sqrt(i) << endl;

    return 0;
}
