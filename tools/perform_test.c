#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T_MAX 1000000

char in[T_MAX];
char out[T_MAX];
char ans[T_MAX];

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("argument error!\n");
        printf("usage: perform_test <input_file> <out_file> <answer_file>\n");
        exit(1);
    }

    FILE * fp_in = fopen(argv[1], "r");
    if (fp_in == NULL) {
        printf("could not open %s\n", argv[1]);
        exit(1);
    }

    FILE * fp_out = fopen(argv[2], "r");
    if (fp_out == NULL) {
        printf("could not open %s\n", argv[2]);
        exit(1);
    }
    FILE * fp_ans = fopen(argv[3], "r");
    if (fp_ans == NULL) {
        printf("could not open %s\n", argv[3]);
        exit(1);
    }

    FILE * fp_log = fopen("log.txt", "w");
    if (fp_log == NULL) {
        printf("could not open %s\n", "log.txt");
        exit(1);
    }


    fscanf(fp_in, "%s", in);
    fscanf(fp_out, "%s", out);
    fscanf(fp_ans, "%s", ans);
    fprintf(fp_log, "%s\n", in);
    fprintf(fp_log, "%s\n", out);
    fprintf(fp_log, "%s\n", ans);
    int in_len = strlen(in);
    int out_len = strlen(out);
    int ans_len = strlen(ans);
    if (out_len != ans_len || in_len != out_len) {
        printf("incorrect length of string\n");
        printf("in: %d,out: %d, ans: %d\n", in_len, out_len, ans_len);
        exit(1);
    }
    int in_count = 0;
    int out_count = 0;
    for (int i = 0; i < out_len; i++) {
        if (out[i] == ans[i]) {
            out_count ++;
        }
        if (in[i] == ans[i]) {
            in_count ++;
        }
    }
    printf("accuracy: %lf%%(output) <= %lf%%(input) \n", (double)out_count / out_len * 100, (double)in_count / out_len * 100);
    return 0;
}