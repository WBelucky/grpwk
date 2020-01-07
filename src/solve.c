#include <stdlib.h>
#include <string.h>
#include "params.h"
#include "bm.h"
#include "KMP.h"
#include "markov.h"

void fill_by_simple_bm(char* t, int t_length, char **s, int n, int limit_length);
void fill_by_multimatch_bm(char* t, int t_length, char **s, int n, int limit_length);
void fill_by_kmp(char* t, int t_length, char **s, int n, int limit_length);
void fill_with_a(char* t, int t_length);
void fill_by_markov_nearby1(char* t, int t_length);

// qsortのための比較関数
int str_len_cmp_r(const void * a, const void * b) {
    return (int)strlen(*(char**)b) - (int)strlen(*(char**)a);
}

double after[4][4] = {{0.4, 0.2, 0.2, 0.2},
                      {0.4, 0.2, 0.1, 0.3},
                      {0.3, 0.3, 0.1, 0.3},
                      {0.5, 0.4, 0, 0.1}};


void solve(char *t, char **s, int n, Params* params) {
  // これには0.01秒程度しかかからないので, ここのソートの高速化は後回しでいい
  qsort(s, (size_t)n, sizeof(char *), str_len_cmp_r);
  int t_length = (int)strlen(t);

  // 大まかに埋める.
  switch(params->searchMethod) {
    case SIMPLE_BM:
      fill_by_simple_bm(t, t_length, s, n, params->search_limit);
      break;
    case MULTIMATCH_BM:
      fill_by_multimatch_bm(t, t_length, s, n, params->search_limit);
      break;
    case KMP:
      fill_by_kmp(t, t_length, s, n, params->search_limit);
      break;
    default:
      fill_by_multimatch_bm(t, t_length, s, n, params->search_limit);
      break;
  }

  // 残りを適当に埋めとく
  switch (params->remaining) {
    case FILL_WITH_A:
      fill_with_a(t, t_length);
      break;
    case MARKOV1:
      fill_by_markov_nearby1(t, t_length);
      break;
    case MARKOV3:
      // 正直遅いだけ
      super_markov(t, t_length); // 前後3文字を見てやるマルコフ.
      break;
    default:
      fill_by_markov_nearby1(t, t_length);
      break;
  }
}

void fill_with_a(char* t, int t_length) {
  for(int i = 0; i < t_length; i++) {
    if(t[i] == 'x') {
      t[i] = 'a';
    }
  }
}

double markov(char *t, int i, int j) {
  double ret = 0;
  if(i) {
    int a = (int)t[i - 1] - 'a';
    ret += after[a][j];
  }
  if(t[i + 1]) {
    int a = (int)t[i + 1] - 'a';
    ret += after[j][a];
  }
  return ret;
}

void fill_by_markov_nearby1(char* t, int t_length) {
  for(int i = 0; i < t_length; i++) {
    if(t[i] == 'x') {
      int index = 0;
      double maxp = 0;
      for(int j = 0; j < 4; j++) {
        double p = markov(t, i, j);
        if(p > maxp) {
          maxp = p;
          index = j;
        }
      }
      t[i] = (char)('a' + index);
    }
  }
}

void fill_by_simple_bm(char* t, int t_length, char **s, int n, int limit_length) {
  char *tt = (char *)malloc((size_t)((int)sizeof(char) * t_length + 5));
  strcpy(tt, t);
  for (int i = 0; i < limit_length; i++) {
    int s_length = (int)strlen(s[i]);
    char * match = bm_search(tt, t_length, s[i], s_length);
    if (match == NULL) {
      continue;
    }
    int index = (int)(match - tt);
    for(int j = 0; j < s_length; j++) {
      t[j + index] = s[i][j];
      tt[j + index] = 'z';
    }
  }
}

void fill_by_multimatch_bm(char* t, int t_length, char **s, int n, int limit_length) {
  char *tt = (char *)malloc((size_t)((int)sizeof(char) * t_length + 5));
  strcpy(tt, t);
  for (int i = 0; i < limit_length; i++) {
    int s_length = (int)strlen(s[i]);

    int x_count_min = 1e9;
    char * most_match = NULL;
    char * match = tt;
    while(1) {
      int index = (int)(match - tt);
      // 次にマッチするものを調べる 文字列の長さに注意しないとめっちゃバグる.
      match = bm_search(match, t_length - index, s[i], s_length);
      if (match == NULL) {
        break;
      }
      // xの数が少ないほど正確性は高いはずなのでxを数えてmost_matchを更新
      // TODO: bm_searchに埋め込む
      int x_count = 0;
      for(int j = 0; j < s_length; j++) {
        if (match[j] == 'x') {
          x_count ++;
        }
      }
      // 更新
      if (x_count < x_count_min) {
        x_count_min = x_count;
        most_match = match;
      }
      // これ以上の一致率を持つ文字列はないのでbreak
      if (x_count_min == 0) {
        break;
      }
      // 同じところから始まってもらうと困るので...
      match ++;
    }
    if (most_match == NULL) {
      continue;
    }

    // most_matchしたもので書き換え
    int index = (int)(most_match - tt);
    for(int j = 0; j < s_length; j++) {
      // tはそのまま答えになる
      t[j + index] = s[i][j];
      // ttはどこまで埋めたかを記録するもの
      // すでに埋めたものを'z'で埋めておけば以降はマッチしない.
      tt[j + index] = 'z';
    }
  }

}

void fill_by_kmp(char* t, int t_length, char **s, int n, int limit_length) {
  char *tt = (char *)malloc((size_t)((int)sizeof(char) * t_length + 5));
  strcpy(tt, t);

  for(int i = 0; i < limit_length; i++) {
    int s_len = (int)strlen(s[i]);
    int index = KmpSearch(tt, t_length, s[i], s_len);
    if(index != -1) {
      for(int j = 0; j < s_len; j++) {
        t[index + j] = s[i][j];
        tt[index + j] = 'z';
      }
    }
  }
}
