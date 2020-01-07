#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// abcd => 0123, x => 4とした5進数に変換する
// mapを実装するのがめんどくさいので必要だった.
int to_radix5_index(char * s, int s_len) {
    int index = 0;
    int radix = 1;
    for (int j = s_len - 1; j >= 0; j--) {
        if (s[j] == 'x') {
            index += 4 * radix;
        } else {
            index += (s[j] - 'a') * radix;
        }
        radix *= 5;
    }
    return index;
}

void super_markov(char* t, const int t_len) {
    char filename[] = "./src/markov.txt";
    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("cannot open %s", filename);
        return;
    }
    int len, num_of_pattern;
    fscanf(fp, "%d%d", &len, &num_of_pattern);

    int p = 1;
    for (int i = 0; i < len; i++) {
        p *= 5;
    }
    char** pattern = (char**)malloc(sizeof(char*) * p + 5);
    for (int i = 0; i < p; i++) {
        pattern[i] = (char*)malloc(sizeof(char) * len + 1);
        pattern[i][0] = '\0';
    }
    
    for (int i = 0; i < num_of_pattern; i++) {
        char key[100];
        fscanf(fp, "%s", key);
        int index = to_radix5_index(key, len);
        fscanf(fp, "%s", pattern[index]);
        // printf("%d: %s\n", index, pattern[index]);
    }
    fclose(fp);
    for (int i = 0; i < t_len - len; i++) {
        int index = to_radix5_index(t + i, len);
        if (strcmp(pattern[index], "\0") == 0) {
            int j = len / 2;
            if (t[i + j] == 'x') {
                t[i + j] = 'a';
            }
        } else {
            int j = len / 2;
            t[i + j] = pattern[index][j];
        }
    }
}