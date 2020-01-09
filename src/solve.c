#include <stdlib.h>
#include <string.h>
#include "params.h"
#include "bm.h"
#include "KMP.h"
#include "markov.h"
#include "bitap.h"

void fill_by_simple_bm(char* t, int t_length, char **s, int n, int limit_length);
void fill_by_multimatch_bm(char* t, int t_length, char **s, int n, int limit_length);
void fill_by_kmp(char* t, int t_length, char **s, int n, int limit_length);
void fill_with_a(char* t, int t_length);
void fill_by_markov_nearby1(char* t, int t_length);
void sort_by_match_count(char * t, int t_length, char** s, int limit_length);

// qsortのための比較関数
int str_len_cmp_r(const void * a, const void * b) {
    return (int)strlen(*(char**)b) - (int)strlen(*(char**)a);
}

// マルコフ則に使う. 確率はアバウト.
// after[i][j] で一つ前に 文字 "'a' + i" があるとき, 次に "'a' + j" が現れる確率
//               一つ後 a   b    c    d
double after[4][4] = {{0.4, 0.2, 0.2, 0.2}, // 一つ前がa
                      {0.4, 0.2, 0.1, 0.3}, // b
                      {0.3, 0.3, 0.1, 0.3}, // c
                      {0.5, 0.4, 0, 0.1}};  // d


// before[j][i] で 文字 "'a' + i" があるとき, その前に "'a' + j" が現れる確率
double before[4][4] = {
  // 一つ後がaのとき
  { 
    0.401769, // a
    0.24885, // b
    0.0874049, // c
    0.261977, // d
  },
  // 一つ後がb
  { 0.319099, // a
    0.199251, // b
    0.140945, // c
    0.340705, // d
  },
  // 一つ後がc
  {
    0.688417, // a
    0.211503, // b
    0.10008, // c
    0, // d
  },
  // 一つ後がd
  {
    0.380197, // a
    0.35621, // b
    0.16468, // c
    0.0989126, // d
  },
};
// 後前
// aa 0.401769
// ab 0.24885
// ac 0.0874049
// ad 0.261977
// ba 0.319099
// bb 0.199251
// bc 0.140945
// bd 0.340705
// ca 0.688417
// cb 0.211503
// cc 0.10008
// cd 0
// da 0.380197
// db 0.35621
// dc 0.16468
// dd 0.0989126



void solve(char *t, char **s, int n, Params* params) {
  // これには0.01秒程度しかかからないので, ここのソートの高速化は後回しでいい
  int t_length = (int)strlen(t);

  qsort(s, (size_t)n, sizeof(char *), str_len_cmp_r);

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
    case MATCH_COUNT_SORTED:
      sort_by_match_count(t, t_length, s, params->search_limit);
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


double prob[4] = {0.40, 0.25, 0.11, 0.21};

double markov(char *t, int t_length, int i, int j) {
  double ret = 1;
  if(i) {
    // i-1はもう埋まってると仮定する
    int a = (int)t[i - 1] - 'a';
    ret *= after[a][j];
  }
  if(i < t_length - 1) {
    if (t[i + 1] == 'x') {
      ret *= prob[j];
    } else {
      int a = (int)t[i + 1] - 'a';
      ret *= after[j][a];
    }
  }
  return ret;
}

void fill_by_markov_nearby1(char* t, int t_length) {
  for(int i = 0; i < t_length; i++) {
    if(t[i] == 'x') {
      int index = 0;
      double maxp = 0;
      for(int j = 0; j < 4; j++) {
        double p = markov(t, t_length, i, j);
        if(p > maxp) {
          maxp = p;
          index = j;
        }
      }
      t[i] = (char)('a' + index);
    }
  }
}

int * match_count;
int compare_match_count(const void *a, const void *b) {
    return match_count[*(int*)a] - match_count[*(int*)b];
}

// tにマッチする数でsをソートしてから当てはめていく.
void sort_by_match_count(char * t, int t_length, char** s, int limit_length) {

  // 構造体を使えばいいんだろうけど遅くなりそうで...
  int * index = (int *)malloc(sizeof(int) * (size_t)limit_length + 5);
  match_count = (int *)malloc(sizeof(int) * (size_t)limit_length + 5);
  int * s_length = (int *)malloc(sizeof(int) * (size_t)limit_length + 5);
  for (int i = 0; i < limit_length; i++) {
    index[i] = i;
    s_length[i] = (int)strlen(s[i]);
  }

  char *tt = (char *)malloc((size_t)((int)sizeof(char) * t_length + 5));
  strcpy(tt, t);

  for (int i = 0; i < limit_length; i++) {
    int x_count_min = 1e9;
    char * most_match = NULL;
    char * match = tt;
    match_count[i] = 0;
    while(1) {
      int len = t_length - (int)(match - tt);
      // 次にマッチするものを調べる 文字列の長さに注意しないとめっちゃバグる.
      match = bm_search(match, len, s[i], s_length[i]);
      if (match == NULL) {
        break;
      }
      ++(match_count[i]);
      // xの数が少ないほど正確性は高いはずなのでxを数えてmost_matchを更新
      // TODO: 先にすべてのマッチの数を求めておく マッチの数が少ないものorマッチの中のxが少ないものから埋めていく
      // TODO: bm_searchに埋め込む
      int x_count = 0;
      for(int j = 0; j < s_length[i]; j++) {
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
    int index_match = (int)(most_match - tt);
    for(int j = 0; j < s_length[i]; j++) {
      // ttはどこまで埋めたかを記録するもの
      // すでに埋めたものを'z'で埋めておけば以降はマッチしない.
      tt[j + index_match] = 'z';
    }
  }
  qsort(index, (size_t)limit_length, sizeof(int), compare_match_count);

  strcpy(tt, t);
  for (int i = 0; i < limit_length; i++) {
    int x_count_min = 1e9;
    char * most_match = NULL;
    char * match = tt;
    int count = 0;
    while(1) {
      int len = t_length - (int)(match - tt);
      // 次にマッチするものを調べる 文字列の長さに注意しないとめっちゃバグる.
      match = bm_search(match, len, s[index[i]], s_length[index[i]]);
      if (match == NULL) {
        break;
      }
      count ++;
      // xの数が少ないほど正確性は高いはずなのでxを数えてmost_match[を更新
      // TODO: 先にすべてのマッチの数を求めておく マッチの数が少ないものorマッチの中のxが少ないものから埋めていく
      // TODO: bm_searchに埋め込む
      int x_count = 0;
      for(int j = 0; j < s_length[index[i]]; j++) {
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
    int index_match = (int)(most_match - tt);
    for(int j = 0; j < s_length[index[i]]; j++) {
      // tはそのまま答えになる
      t[j + index_match] = s[index[i]][j];
      // ttはどこまで埋めたかを記録するもの
      // すでに埋めたものを'z'で埋めておけば以降はマッチしない.
      tt[j + index_match] = 'z';
    }
  }
  free(tt);
  free(index);
  free(s_length);
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
  free(tt);
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
      int len = t_length - (int)(match - tt);
      // 次にマッチするものを調べる 文字列の長さに注意しないとめっちゃバグる.

      if (s_length < 64) {
        int bitap_index = bitmap_search(match, len, s[i], s_length);
        if (bitap_index == -1) {
          break;
        }
        match = (char*)(match + bitap_index);
      } else {
        match = bm_search(match, len, s[i], s_length);
        if (match == NULL) {
          break;
        }
      }

      // xの数が少ないほど正確性は高いはずなのでxを数えてmost_matchを更新
      // TODO?: だめだった=> 先にすべてのマッチの数を求めておく マッチの数が少ないものorマッチの中のxが少ないものから埋めていく
      // TODO: xだけでなく前後の文字列とのマルコフ則も考慮して最もアリそうな位置を選ぶ
      // TODO: bm_searchに処理を埋め込む
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
  free(tt);
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
  free(tt);
}
