#include<stdlib.h>

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