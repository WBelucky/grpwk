#include <stdlib.h>
#include <stdio.h>
#include "bm.h"
#include "bitap.h"

void fill_by_multimatch_bm_and_bitap(char* t, int t_length, char **s, int n, int limit_length) {
  char *tt = (char *)malloc((size_t)((int)sizeof(char) * t_length + 5));
  strcpy(tt, t);
  for (int i = 0; i < limit_length; i++) {
    int s_length = (int)strlen(s[i]);

    int x_count_min = 1e9;
    char * most_match = NULL;
    char * match = tt;
    fflush(stdout);

    if (s_length < 64) {
        long long s_mask[300];
        make_bitmap_mask(s, s_length, s_mask, 300);
        while(1) {
            // 次にマッチするものを調べる 文字列の長さに注意しないとめっちゃバグる.
            int len = t_length - (int)(match - tt);
            int bitap_index = bitmap_search(match, len, s_mask, s_length);
            if (bitap_index == -1) {
                break;
            }
            printf("%d\n", bitap_index);
            match = (char*)(match + bitap_index);
            int x_count = 0;
            for(int j = 0; j < s_length; j++) {
                if (match[j] == 'x') {
                    x_count ++;
                }
            }
            if (x_count < x_count_min) {
                x_count_min = x_count;
                most_match = match;
            }
            if (x_count_min == 0) {
                break;
            }
            match ++;
        }

    } else {
        while(1) {
            int len = t_length - (int)(match - tt);
            // 次にマッチするものを調べる 文字列の長さに注意しないとめっちゃバグる.

            // 64bit未満だったらbitapアルゴリズムを使う.
            match = bm_search(match, len, s[i], s_length);
            if (match == NULL) {
                break;
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