#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bm.h"
#include "bitap.h"

void fill_by_multimatch_bm(char* t, int t_length, char **s, int n, int limit_length) {
  char *tt = (char *)malloc((size_t)((int)sizeof(char) * t_length + 5));
  strcpy(tt, t);
  for (int i = 0; i < limit_length; i++) {
    int s_length = (int)strlen(s[i]);

    int x_count_min = 1e9;
    char * most_match = NULL;
    char * match = tt;
    if (s_length < 64) {
      long long s_mask[128];
      make_bitmask(s[i], s_length, s_mask, 128);
      while((match = bitmap_search(match, t_length - (int)(match - tt), s_mask, s_length))) {
        int x_count = 0;
        for(int j = 0; j < s_length; j++) {
          x_count += (match[j] == 'x');
        }
        // 更新
        if(x_count < x_count_min) {
          x_count_min = x_count;
          most_match = match;
        }
        // これ以上の一致率を持つ文字列はないのでbreak
        if(!x_count_min) {
          break;
        }
        // 同じところから始まってもらうと困るので...
        ++match;
      }
    } else {

      int table[26];
      make_bm_table(s[i], s_length, table, 26);
      
      while((match = bm_search_with_table(match, t_length - (int)(match - tt), s[i], s_length, table))) {
        int x_count = 0;
        for(int j = 0; j < s_length; j++) {
          x_count += (match[j] == 'x');
        }
        // 更新
        if(x_count < x_count_min) {
          x_count_min = x_count;
          most_match = match;
        }
        // これ以上の一致率を持つ文字列はないのでbreak
        if(!x_count_min) {
          break;
        }
        // 同じところから始まってもらうと困るので...
        ++match;
      }
    }
    if (!most_match) {
      continue;
    }
    // most_matchしたもので書き換え
    int index = (int)(most_match - tt);
    for(int j = 0; j < s_length; ++j) {
      // tはそのまま答えになる
      t[j + index] = s[i][j];
      // ttはどこまで埋めたかを記録するもの
      // すでに埋めたものを'z'で埋めておけば以降はマッチしない.
      tt[j + index] = 'z';
    }
  }
  free(tt);
}