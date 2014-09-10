//字符串排列组合问题
//Wed Sep 10 07:24:46 PDT 2014
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

//根据字符串输出其组合
//设置容器vector,从第一个字符a开始：
//          1. vector加入a，递归调用i-1
//          2. vector不加a，递归调用i
void CombineCore(char* str, int num, vector<char> &vec)
{
    if (*str == '\0')
        return;
    if (num == 0)
    {
        vector<char>::iterator ite = vec.begin();
        for (; ite != vec.end(); ++ite)
            cout << *ite << "\t";
        cout << endl;
        return;
    }
    vec.push_back(*str);
    CombineCore(str+1, num-1, vec);
    vec.pop_back();
    CombineCore(str+1, num, vec);
}

void Combine(char* str)
{
    int len = strlen(str);
    vector<char> vec;
    for (int i = 1; i < len; ++i)
        CombineCore(str, i, vec);
}

//根据字符串,输出其排列
void PermutationCore(char *str, int index)
{
    if (index == strlen(str))
    {
        cout << str << endl;
        return;
    }

    for (int i = index; i < strlen(str); ++i)
    {
        swap(str[i], str[index]);
        //char temp = str[i];
        //str[i] = str[index];
        //str[index] = temp;

        PermutationCore(str, index + 1);

        swap(str[i], str[index]);
        //temp = str[i];
        //str[i] = str[index];
        //str[index] = temp;
    }
}

void Permutation(char *str)
{
    //int len = strlen(str);
    //for (int i = 0; i < len; i++)
        PermutationCore(str, 0);
}

int main()
{
    char str[] = "abc";
    //Combine(str);
    Permutation(str);

    return 0;
}
