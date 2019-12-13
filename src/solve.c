#include <stdlib.h>
#include <string.h>
#include "bm.h"
#include "KMP.h"
#include <stdio.h>

// qsortのための比較関数
int str_len_cmp_r(const void * a, const void * b) {
    return (int)strlen(*(char**)b) - (int)strlen(*(char**)a);
}

double after[4][4] = {
0.4,0.2,0.2,0.2,
0.4,0.2,0.1,0.3,
0.3,0.3,0.1,0.3,
0.5,0.4,0,0.1
};


double markov(char * t,int i, int j){
	double ret = 0;
	if(i){
	    int a = t[i-1] - 'a';
	    ret += after[a][j]; 
	}
	if(t[i+1]){
	    int a = t[i+1] - 'a';
	    ret += after[j][a];
	}
	return ret;
}






void solve(char * t, char** s, int n) {

  // // 文字列の長さでソートしたらチョット(2%程度)精度が上がった
    qsort(s, (size_t)n , sizeof(char*), str_len_cmp_r);

    int t_length = (int)strlen(t);
    char *tt = (char *)malloc(sizeof(char) * t_length + 5);
    strcpy(tt,t);
    
    
    for(int i = 0 ; i < 6000; i++){
        int index = KmpSearch(t,s[i]);
        int s_len = strlen(s[i]);
        if(index != -1){
            for(int j = 0;j < s_len;j++){
                t[index+j] = s[i][j];
            }
            
            for(int j = 0;j < s_len;j++){
                tt[index+j] = 'z';
            }
            
        }
    }
    
  // // s[i]をそれぞれ見ていって, tのある部分とマッチしたらそこを書き換え.
//   for (int i = 0; i < n; i++) {
//     int s_length = (int)strlen(s[i]);
//     char * match = bm_search(t, t_length, s[i], s_length);
//     if (match == NULL) {
//       continue;
//     }
//     for (int j = 0; j < s_length; j++) {
//       match[j] = s[i][j];
//     }
//   }

  // xが残っていたら取り合えずaに置き換え
  for (int i = 0; i < t_length; i ++) {
   	 if (t[i] == 'x') {
		int index = 0;
		double maxp = 0;
      		for(int j = 0; j < 4;j++){
			double p = markov(t,i,j);
			if(p > maxp){
				maxp = p;
				index = j;
			}
		}
		t[i] = 'a' + index;
    	}
  }
  

}
