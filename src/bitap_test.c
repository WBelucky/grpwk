#include <stdio.h>
#include <string.h>

#include "bitap.h"

int main(void) {
    char t[] = "axcdabbcdddccbaaaaaa";
    char s[4][10] = {"abc", "bc", "ddc", "aaaa"};
    printf("bm_test\n");
    int ans[] = {0, 1, 9, 14};
    for (int i = 0; i < 4; i++) {
        int index = bitmap_search(t, strlen(t), s[i], strlen(s[i]));
        printf("test%d: %s\n", i, (index == ans[i] ? "ok" : "ng"));
    }
}