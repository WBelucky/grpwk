#include <stdlib.h>
#include <string.h>
#include "params.h"
#include "bm.h"
#include "KMP.h"
#include "markov.h"
// qsortのための比較関数
int str_len_cmp_r(const void * a, const void * b) {
    return (int)strlen(*(char**)b) - (int)strlen(*(char**)a);
}

double after[4][4] = {{0.4, 0.2, 0.2, 0.2},
                      {0.4, 0.2, 0.1, 0.3},
                      {0.3, 0.3, 0.1, 0.3},
                      {0.5, 0.4, 0, 0.1}};

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

void solve(char *t, char **s, int n, Params* params) {
  // これには0.01秒程度しかかからないので, ここのソートの高速化は後回しでいい
  qsort(s, (size_t)n, sizeof(char *), str_len_cmp_r);

  int t_length = (int)strlen(t);
  char *tt = (char *)malloc((size_t)((int)sizeof(char) * t_length + 5));
  strcpy(tt, t);

  // for(int i = 0; i < params->bm_search_limit_length; i++) {
  //   int s_len = (int)strlen(s[i]);
  //   int index = KmpSearch(tt, t_length, s[i], s_len);
  //   if(index != -1) {
  //     for(int j = 0; j < s_len; j++) {
  //       t[index + j] = s[i][j];
  //       tt[index + j] = 'z';
  //     }
  //   }
  // }

  // s[i]をそれぞれ見ていって, tのある部分とマッチしたらそこを書き換え.
  // ttにはどこが埋まっているかを記録するために, 文字列で埋めたところに'z'を入れる. こうすれば, すでにマッチした部分に再びマッチすることはない.
  for (int i = 0; i < params->bm_search_limit_length; i++) {
    int s_length = (int)strlen(s[i]);

    int x_count_min = 1e9;
    char * most_match = NULL;
    char * match = tt;
    while(1) {
      // 次にマッチするものを調べる
      match = bm_search(match, t_length, s[i], s_length);
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

  // xが残っていたら取り合えずaに置き換え
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
  //super_markov(t, t_length);
}
