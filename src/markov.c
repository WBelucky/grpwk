#include <stdio.h>

int to_radix4_index(char * s, int s_len) {
    int index = 0;
    int radix = 1;
    for (int j = s_len - 1; j >= 0; j--) {
        index += (s[j] - 'a') * radix;
        radix *= 4;
    }
    return index;
}

void markov(char* t, const int t_len) {
    char filename[] = "../tools/markov.txt";
    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("cannot open %s", filename);
        return;
    }
    int len = 1;
    fscanf(fp, "%d", &len);
    int p = 1;
    for (int i = 0; i < len; i++) {
        p *= 4;
    }
    printf("%d\n", len);
    int prob[p];
    
    for (int i = 0; i < p; i++) {
        char s[1000];
        int num;
        fscanf(fp, "%s%d", s, &num);
        prob[to_radix4_index(s, len)] = num;
    }
    fclose(fp);
    // for (int i = 0; i < p; i++) {
    //     printf("%d\n", prob[i]);
    // }
}