#include <iostream>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

int GetLcsLength(const string& str1, const string& str2) 
{
    size_t len1 = str1.size();
    size_t len2 = str2.size();
    assert(len1 > 0 && len2 > 0);
    int res = 0; 
 
    int start1, start2;
    start1 = start2 = -1;
    vector<vector<int> > vec(len1, vector<int>(len2, 0));
    
 
    int count = 0;
    for (int j = 0; j < len2; ++j)
    {
        ++count;
        vec[0][j] = (str1[0] == str2[j] ? 1 :0);
    }
 
    for (int i = 1; i < len1; ++i)
    {
        ++count;
        vec[i][0] = (str1[i] == str2[0] ? 1 :0);
 
        for (int j = 1; j < len2; ++j)
        {
            ++count;
            if (str1[i] == str2[j])
            {
                vec[i][j] = vec[i-1][j-1]+1;
            }
        }
    }
 
    for (int i = 0; i < len1; ++i)
    {
        for (int j = 0; j < len2; ++j)
        {
            if (res < vec[i][j])
            {
                res = vec[i][j];
                start1 = i-res+1;
                start2 = j-res+1;
            }
        }
    }
 
    return res;
}

int main()
{
    string str1 = "acbac";
    string str2 = "acaccbabb";
    cout << GetLcsLength(str1, str2) << endl;
}
