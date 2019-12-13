#include <stdio.h>
#include <stdlib.h>

void GetNext(char* p, int next[])
{
    int pLen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1)
    {
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            if (p[j] != p[k])
                next[j] = k;
            else
                next[j] = next[k];
        }
        else
        {
            k = next[k];
        }
    }
    
}

int KmpSearch(char* s, char* p)
{
    int next[300];
    GetNext(p,next);
    int i = 0;
    int j = 0;
    int sLen = strlen(s);
    int pLen = strlen(p);
    int index = 0;
    int first_x = 1;
    
    while (i < sLen && j < pLen)
    {
        if (j == -1 || s[i] == p[j] || s[i] == 'x')
        {
            i++;
            j++;
            if(first_x && s[i] == 'x'){
                index = i-j;
		first_x = 0;
            }
         
        }
        else
        {
            if(first_x)
                j = next[j];
            else{
                i = index+1;
                j = 0;
                first_x = 1;
                index = -1;
            }
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
    
}

