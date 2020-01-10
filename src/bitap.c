#include <stdlib.h>

void make_bitmask(char * p, int p_length, long long * p_mask, int mask_size) {
    for (int i = 0; i < mask_size; ++i) {
        p_mask[i] = ~0; // fill all with 1
    }
    for (int i = 0; i < p_length; ++i) {
        // 文字p[i]が来たときのマスクを作る
        p_mask[(int)(p[i])] &= ~(1LL << i);
    }
    p_mask[(int)('x')] = 0;
}

char* bitmap_search(char * t, int t_length, long long * p_mask, int p_length) {
    long long A = ~1;
    for (int i = 0; i < t_length; ++i) {
        A |= p_mask[(int)(t[i])];
        A <<=1;
        // Aはほとんど1だったけど, ゴニョゴニョした結果, 積が0になればOk
        if (!(A & (1LL << p_length))) {
            return t + (i - p_length + 1);
        }
    }
    return NULL;
}

void make_bitmask128(char * p, int p_length, __int128_t * p_mask, int mask_size) {
    for (int i = 0; i < mask_size; ++i) {
        p_mask[i] = ~0; // fill all with 1
    }
    for (int i = 0; i < p_length; ++i) {
        // 文字p[i]が来たときのマスクを作る
        p_mask[(int)(p[i])] &= ~(1LL << i);
    }
    p_mask[(int)('x')] = 0;
}

char* bitmap_search128(char * t, int t_length, __int128_t * p_mask, int p_length) {
    __int128_t A = ~1;
    for (int i = 0; i < t_length; ++i) {
        A |= p_mask[(int)(t[i])];
        A <<=1;
        // Aはほとんど1だったけど, ゴニョゴニョした結果, 
        if ((A & (1LL << p_length)) == 0) {
            return t + (i - p_length + 1);
        }
    }
    return NULL;
}

int make_bitmask_and_bitmap_search(char * t, int t_length, char * p, int p_length) {
    long long p_mask[300];
    long long A = ~1;
    if (p_length < 0 || 63 < p_length) {
        return -1; // 失敗
    }
    for (int i = 0; i < 300; ++i) {
        p_mask[i] = ~0; // fill all with 1
    }
    for (int i = 0; i < p_length; ++i) {
        // 文字p[i]が来たときのマスクを作る
        p_mask[(int)(p[i])] &= ~(1LL << i);
    }
    p_mask[(int)('x')] = 0;
    for (int i = 0; i < t_length; ++i) {
        A |= p_mask[(int)(t[i])];
        A <<=1;
        // Aはほとんど1だったけど, ゴニョゴニョした結果, 
        if ((A & (1LL << p_length)) == 0) {
            return i - p_length + 1;
        }
    }
    return -1;
}