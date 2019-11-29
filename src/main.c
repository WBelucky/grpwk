#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

int main_prg(int, char **);

int main(int argc, char **argv) {

  struct rusage u;
  struct timeval start, end;

  getrusage(RUSAGE_SELF, &u);
  start = u.ru_utime;

  main_prg(argc, argv);

  getrusage(RUSAGE_SELF, &u);
  end = u.ru_utime;

  fprintf(stderr, "%lf\n",
          (double)(end.tv_sec - start.tv_sec) +
              (double)(end.tv_usec - start.tv_usec) * 1e-6);

  return (0);
}

int main_prg(int argc, char **argv) {
  if (argc != 3) {
    printf("usage: grpwk <input file> <output file>\n");
    exit(1);
  }
  FILE *fp_in = fopen(argv[1], "r");
  if (fp_in == NULL) {
    printf("error: could not open %s\n", argv[1]);
    exit(1);
  }
  FILE *fp_out = fopen(argv[2], "w");
  if (fp_out == NULL) {
    printf("error: could not open %s\n", argv[2]);
    exit(1);
  }

  /** implement here
   *
   * read input values from fp_in
   * write output values to fp_out
   **/

  return 0;
}
