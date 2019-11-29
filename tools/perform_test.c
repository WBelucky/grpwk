#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T_MAX 1000000

char out[T_MAX];
char ans[T_MAX];

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: perform_test <out_file> <answer_file>\n");
        exit(1);
    }
    FILE * fp_out = fopen(argv[1], "r");
    if (fp_out == NULL) {
        printf("could not open %s\n", argv[1]);
        exit(1);
    }
    FILE * fp_ans = fopen(argv[2], "r");
    if (fp_ans == NULL) {
        printf("could not open %s\n", "r");
        exit(1);
    }

    fscanf(fp_out, "%s", out);
    fscanf(fp_ans, "%s", ans);
    int out_len = strlen(out);
    int ans_len = strlen(ans);
    if (out_len != ans_len) {
        printf("incorrect length of string\n");
        printf("out: %d, ans: %d\n", out_len, ans_len);
        exit(1);
    }
    int count = 0;
    for (int i = 0; i < out_len; i++) {
        if (out[i] == ans[i]) {
            count ++;
        }
    }
    printf("accuracy: %lf %% \n", (double)count / out_len * 100);
    return 0;
}