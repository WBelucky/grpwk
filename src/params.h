#ifndef PARAMS_H
#define PARAMS_H

typedef enum {
  SIMPLE_BM,
  MULTIMATCH_BM,
  KMP,
} SearchMethod;

typedef enum {
  NEARBY1,
  NEARBY3,
  FILL_WITH_A,
} Markov;

typedef struct  {
  int bm_search_limit_length;
  SearchMethod searchMethod;  // true => KMP, false => bm_search
  Markov markov;
} Params;
#endif // PARAMS_H
