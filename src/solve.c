#include <stdlib.h>
#include <string.h>
#include "bm.h"

void solve(char * t, char** s, int n) {

  int t_length = (int)strlen(t);

  // s[i]をそれぞれ見ていって, tのある部分とマッチしたらそこを書き換え.
  for (int i = 0; i < n; i++) {
    char * match = bm_search(t, t_length, s[i], (int)strlen(s[i]));
    if (match == NULL) {
      continue;
    }
    for (int j = 0; j < (int)strlen(s[i]); j++) {
      match[j] = s[i][j];
    }
  }

  // xが残っていたら取り合えずaに置き換え
  for (int i = 0; i < t_length; i ++) {
    if (t[i] == 'x') {
      t[i] = 'a';
    }
  }
}