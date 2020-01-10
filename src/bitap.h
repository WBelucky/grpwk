void make_bitmask(char * p, int p_length, long long * p_mask, int mask_size);
char* bitmap_search(char * t, int t_length, long long * p_mask, int p_length);
char* bitmap_search128(char * t, int t_length, __int128_t * p_mask, int p_length);
void make_bitmask128(char * p, int p_length, __int128_t * p_mask, int mask_size);
int make_bitmask_and_bitmap_search(char * t, int t_length, char * p, int p_length);