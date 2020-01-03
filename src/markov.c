#include <stdio.h>
#include <stdlib.h>

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

void markov(char* t, const int t_len) {
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
    printf("%d\n", len);
    char** pattern = (char**)malloc(sizeof(char*) * p);
    for (int i = 0; i < p; i++) {
        pattern[i] = (char*)malloc(sizeof(char) * len + 1);
    }
    
    for (int i = 0; i < num_of_pattern; i++) {
        char key[1000];
        fscanf(fp, "%s", key);
        int index = to_radix5_index(key, len);
        fscanf(fp, "%s", pattern[index]);
        printf("%d: %s\n", index, pattern[index]);
    }
    fclose(fp);
}