#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>
#include "solve.h"
#include "params.h"

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

int main_prg(int argc, char **argv) {
  if (argc < 3) {
    printf("usage: grpwk <input file> <output file> (<params...>)\n");
    exit(1);
  }
  FILE *fp_in = fopen(argv[1], "r");
  if (fp_in == NULL) {
    printf("error: could not open %s\n", argv[1]);
    exit(1);
  }

  // 虫食い文字tの入力
  char* t = (char *)malloc(sizeof(char) * T_MAX);
  if (fscanf(fp_in, "%s", t) == EOF) {
    printf("could not read T");
    exit(1);
  }

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


  // 出力ファイルを作る
  FILE *fp_out = fopen(argv[2], "w");
  if (fp_out == NULL) {
    printf("error: could not open %s\n", argv[2]);
    exit(1);
  }

  // 解析用のパラメータを適用する
  Params p;
  // 何も指定しない時(本番) これが一番うまく行ったやで.
  p.search_limit = 12500;
  p.searchMethod = MULTIMATCH_BM;
  p.markov = NEARBY1;

  // オプションを指定した時にparamsを変更
  if (argc != 3) {
    for (int i = 3; i < argc; i++) {
      if (strcmp(argv[i], "--search-limit") == 0) {
        if (i + 1 >= argc) {
          printf("error:\n");
          printf("usage: ./grpwk <inputfile> <outputfile> --search-limit <length>");
          exit(1);
        }
        
        p.search_limit = atoi(argv[++i]);
      } else if (strcmp(argv[i], "--search-method") == 0) {
        if (i + 1 >= argc) {
          printf("error:\n");
          printf("usage: ./grpwk <inputfile> <outputfile> --search-method <SIMPLE_BM | KMP | MULTIMATCH_BM>");
          exit(1);
        }
        ++i;
        if (strcmp(argv[i], "KMP") == 0) {
          p.searchMethod = KMP;
        } else if (strcmp(argv[i], "SIMPLE_BM") == 0) {
          p.searchMethod = SIMPLE_BM;
        } else if (strcmp(argv[i], "MULTIMATCH_BM") == 0) {
          p.searchMethod = MULTIMATCH_BM;
        } 
      } else if (strcmp(argv[i], "--markov") == 0) {
        if (i + 1 >= argc) {
          printf("error:\n");
          printf("usage: ./grpwk <inputfile> <outputfile> --markov <FILL_WITH_A | NEARBY1 | NEARBY3>");
          exit(1);
        }
        ++i;
        if (strcmp(argv[i], "FILL_WITH_A") == 0) {
          p.markov = FILL_WITH_A;
        } else if (strcmp(argv[i], "NEARBY1") == 0) {
          p.markov = NEARBY1;
        } else if (strcmp(argv[i], "NEARBY3") == 0) {
          p.markov = NEARBY3;
        }
      }
    }
  }

  // 解く
  solve(t, s, n, &p);

  // 出力
  fprintf(fp_out, "%s\n", t);

  // 一応ファイルとか閉じといてみた
  fclose(fp_out);
  fclose(fp_in);
  free(t);
  for (int i = 0; i < n; i ++) {
    free(s[i]);
  }
  free(s);
  return 0;
}