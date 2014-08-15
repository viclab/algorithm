//常用字符串函数实现
//Wed Aug 13 01:06:50 PDT 2014
#include <stdio.h>
#include <string.h>
#include <assert.h>

//实现strcpy方法一
char* mystrcpy(char* strDes, const char* strSrc)
{
    if (strDes == strSrc)
        return strDes;
    assert(strDes != NULL && strSrc != NULL);
    char* des = strDes;
    while ((*strDes++ = *strSrc++) != '\0');
    return strDes;
}

//实现strncpy方法一
char* mystrncpy(char *dst, const char *src, size_t size)
{
    assert((src != NULL) && (dst != NULL));
    char *add = dst;
    //int i = 0; // 控制复制的个数
    while ((*dst++ = *src++)!='\0' && size-- > 0)
    {
        /*do nothing*/
    }
    if (*(--dst) != '\0') //注意字符串以'\0'结尾
    {
        *dst = '\0';
    }
    return add;
}

//char* mystrncpy(char* dest, const char* src, int len)
//{
//    assert(dest!=NULL && src!=NULL);
//
//    char* temp=dest;
//    //int i=0;
//
//    //while(i++ < len  && (*temp++ = *src++)!='\0');
//    while(len-->0  && (*temp++ = *src++)!='\0');    //要么长度限制，此时设*temp = '\0',
//
//    if (*temp != '\0')
//        *temp='\0';
//
//    return dest;
//}

//char* strncpy(char* strDes, const char* strSrc, size_t n)
//{
//    assert(strDes != NULL && strSrc != NULL && n > 0);
//    if (strDes == strSrc)
//        return strDes;
//    char *des = strDes;
//    for (; strSrc && n > 0; ++des, ++strSrc, --n)
//        *des = *strSrc;
//    for (; n > 0; --n)
//        *des = '\0';
//    return strDes;
//}

//C标准库实现strcpy
//没有处理空指针，原字符串与目标字符串相同
char* mystrcpy2(char *s1, const char *s2)
{
    char *s;
    for (s = s1; (*s++ = *s2++) != '\0'; )
        ;
    return s1;
}

//C标准库实现strncpy
//没有处理空指针
char* mystrncpy2(char *s1, const char *s2, size_t n)
{
    char* s;
    for (s = s1; 0 < n && *s2 != '\0'; --n)
        *s++ = *s2++;
    for (; 0 < n; --n)
        *s++ = '\0';
    return s1;
}

//没有考虑到内存重叠的情况
void* mymemcpy(void *des, void *src, size_t n)
{
    assert(des != NULL && src != NULL && n > 0);
    char *pdes = (char*) des;
    const char *psrc = (const char*) src;
    while (n-- > 0)
    {
        *pdes++ = *psrc++;
    }
    return des;
}

//考虑内存重叠的情况，类似memmove
void* mymemcpy2(void *des, void *src, size_t n)
{
    assert(des != NULL && src != NULL && n > 0);
    if ( src < des && (char*)src + n > (char*)des)
    {
        char *pdes = (char*)des + n - 1;
        const char *psrc = (const char*)src + n - 1;
        while (n-- > 0)
        {
            *pdes-- = *psrc--;
        }
    }
    else
    {
        char *pdes = (char*)des;
        const char *psrc = (const char*)src;
        while (n-- > 0)
        {
            *pdes++ = *psrc++;
        }
    }
    return des;
}

int main()
{
    char str1[10];
    char str2[10];
    //mystrcpy(str1, "hello");
    mystrncpy(str1, "hello", 3);
    //mystrcpy2(str2, "World");
    //mystrncpy2(str2, "World", 2000000);
    strncpy(str2, "hello", 3);
    
    printf("str1=%s\n", str1);
    printf("str2=%s\n", str2);

    return 0;
}
   
