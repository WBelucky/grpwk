void make_bm_table(char* s, int s_length, int * table, int table_size);
char* bm_search_with_table(char* t, int t_length, char* s, int s_length, int* table);
char* bm_search(char * t, int t_length, char* s, int s_length);