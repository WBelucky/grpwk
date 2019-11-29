#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>
// 虫食い文字列Tの最大の長さ
#define T_MAX 1000000

int main_prg(int, char **);

int main(int argc, char **argv) {

  struct rusage u;
  struct timeval start, end;

  getrusage(RUSAGE_SELF, &u);
  start = u.ru_utime;

  main_prg(argc, argv);

  getrusage(RUSAGE_SELF, &u);
  end = u.ru_utime;

  fprintf(stderr, "%lf\n",
          (double)(end.tv_sec - start.tv_sec) +
              (double)(end.tv_usec - start.tv_usec) * 1e-6);

  return (0);
}

/**
 * bm_searchはBoyer Moore法を実装したものです.
 * 文字列tの中に文字列sがあるかどうか探して, マッチした部分の先頭の位置のインデックスを返します
 */
char* bm_search(char * t, int t_length, char* s, int s_length) {

  // ずらしはばを記録するtableを作ります.
  int table[4] = {-1};
  for (int i = 0; i < s_length; i++) {
    int table_i = s[s_length - 1 - i] - 'a';
    if (table[table_i] != -1) {
      table[table_i] = i;
    }
  }

  int t_i = s_length - 1;
  int s_i = s_length - 1;
  while(t_i < t_length && s_i >= 0) {
    if (t[t_i] != s[s_i] && t[t_i] != 'x') {
      int shift = table[t[t_i] - 'a'];
      t_i += (shift + s_i > s_length ? shift : s_length - s_i);
      s_i = s_length - 1;
    } else {
      t_i --;
      s_i --;
    }
  }
  if (s_i < 0) return &t[t_i + 1];
  return NULL;
}

int main_prg(int argc, char **argv) {
  if (argc != 3) {
    printf("usage: grpwk <input file> <output file>\n");
    exit(1);
  }
  FILE *fp_in = fopen(argv[1], "r");
  if (fp_in == NULL) {
    printf("error: could not open %s\n", argv[1]);
    exit(1);
  }

  // 虫食い文字tの入力
  char* t = (char *)malloc(sizeof(char) * T_MAX);
  fscanf(fp_in, "%s", t);

  // 部分文字列s[i]の入力
  char** s = (char**)malloc(sizeof(char*) * T_MAX);
  int n = 0;
  for (; n < T_MAX; n++) {
    s[n] = (char*)malloc(sizeof(char) * T_MAX);

    // debug
    if (s[n] == NULL) {
      printf("could not allocate");
      exit(1);
    }
    if (fscanf(fp_in, "%s", s[n]) == EOF) {
      break;
    }
  }

  for (int i = 0; i < n; i++) {
    printf("bm_search index: %d\n", i);
    char * match = bm_search(t, (int)strlen(t), s[i], (int)strlen(s[i]));
    if (match == NULL) {
      continue;
    }
    for (int j = 0; j < (int)strlen(s[i]); j++) {
      match[j] = s[i][j];
    }
  }

  FILE *fp_out = fopen(argv[2], "w");
  if (fp_out == NULL) {
    printf("error: could not open %s\n", argv[2]);
    exit(1);
  }

  // とりあえず入力データをそのまま出力している.
  fprintf(fp_out, "%s\n", t);
  /** implement here
   *
   * read input values from fp_in
   * write output values to fp_out
   **/
  return 0;
}
