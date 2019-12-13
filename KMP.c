
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
    int x_index = -1;
    int first_x = 1;
    
    while (i < sLen && j < pLen)
    {
        if (j == -1 || s[i] == p[j] || s[i] == 'x')
        {
            i++;
            j++;
            if(!first_x && x_index == -1 && s[i] == 'x'){
                x_index = i;
            }
            first_x = 0;
        }
        else
        {
            if(x_index == -1)
                j = next[j];
            else{
                i = x_index;
                j = 0;
                first_x = 1;
                x_index = -1;
            }
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
    
}

