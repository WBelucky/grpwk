#ifndef PARAMS_H
#define PARAMS_H

typedef enum {
  SIMPLE_BM,
  MULTIMATCH_BM,
  KMP,
  MATCH_COUNT_SORTED,
} SearchMethod;

typedef enum {
  MARKOV1,
  MARKOV3,
  FILL_WITH_A,
} RemainingMethod;

typedef struct  {
  int search_limit;
  SearchMethod searchMethod;  // true => KMP, false => bm_search
  RemainingMethod remaining;
} Params;
#endif // PARAMS_H
